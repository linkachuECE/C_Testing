#include "headers.h"

#define ERROR 1
#define NOERROR 0

int hasError(char s1[]);
int isValidCharacter(char c);
int isNumber(char c);
int isLowerCase(char c);
int isUpperCase(char c);
int getType(char c);
char getRangeEnd(int charType);
char getRangeBegin(int charType);
int addRange(char s[], int startIndex, char startRange, char endRange);


enum charType {NONE, NUM, UCHAR, LCHAR}; // To hold the character type
enum state {BEGIN, AFTERCHAR, AFTERMIDDASH, AFTERLONEDASH, AFTERSPACE}; // To hold the current state

// Expands a range of characters to a second string
int expand(char s1[], char s2[]){
    int i = 0; // s1 increment
    int j = 0; // s2 increment

    char rangeBegin; // To designate the beginning of the range
    char rangeEnd; // To designate the end of the range
    enum charType currentType; // To designate the type of the current character

    if (hasError(s1))    // Check for any bad characters
        return 0;

    while (s1[i] != '\0'){
        // Checks if the current character is a range-able character
        if (isValidCharacter(s1[i])){
            currentType = getType(s1[i]);
            rangeBegin = s1[i];
            // Checks if the following character is a dash
            if(s1[i+1] == '-'){
                // Checks if there's an end to the range
                if(isValidCharacter(s1[i+2])){
                    rangeEnd = s1[i+2];
                    j = addRange(s2, j, rangeBegin, rangeEnd);
                    i += 3;
                // If there isn't an end, get the end using the chartype
                } else {
                    rangeEnd = getRangeEnd(currentType);
                    j = addRange(s2, j, rangeBegin, rangeEnd);
                    i += 2;
                }
            // If there's no dash, just add the character to string 2
            } else {
                s2[j++] = s1[i++];
                s2[j++] = '\n';
            }
        // If the current character is a dash, then determine the beginning of the range
        } else if (s1[i] == '-'){
             currentType = getType(s1[i+1]); // Get the type of character
             rangeBegin = getRangeBegin(currentType); // Get the beginning of the range
             rangeEnd = s1[i+1];  // set the character as the end of the range
             j = addRange(s2, j, rangeBegin, rangeEnd); // Add the range to s2 and update j
             i += 2;
        } else if (s1[i] == ' '){
            i++;
        }
    }

    s2[j] = '\0';
    return 1;
}

char getRangeEnd(int charType){
    enum charType type = charType;

    if (type == NUM){
        return '9';
    } else if (type == LCHAR){
        return 'z';
    } else if (type == UCHAR){
        return 'Z';
    }
}

char getRangeBegin(int charType){
    enum charType type = charType;

    if (type == NUM){
        return '0';
    } else if (type == LCHAR){
        return 'a';
    } else if (type == UCHAR){
        return 'A';
    }
}

int addRange(char s[], int startIndex, char startRange, char endRange){
    int i; // increments through the string
    int j; // increments through the range

    // Checks if the range is ascending
    if (startRange <= endRange){
        for(j = startRange, i = startIndex; j <= endRange; j++, i++){
            s[i] = j;
        }
    
    // Checks if the range is descending
    } else {
        for(j = startRange, i = startIndex; j >= endRange; j--, i++){
            s[i] = j;
        }
    }
    s[i] = '\n';

    // Returns the current index of the string
    return ++i;
}

int hasError(char s[]){

    enum state currentState = BEGIN;
    enum charType currentType = NONE;
    enum charType previousType = NONE;

    // Cycle through string
    for(int i = 0; s[i] != '\0'; i++){
        // Checks for if the current character is a dash
        if (s[i] == '-'){
            // If there are two dashes in a row, there's an error
            if (currentState == AFTERMIDDASH || currentState == AFTERLONEDASH)
                return ERROR;
            // If there's a dash after a blank or at the beginning of the line, it's a lone dash
            else if (currentState == AFTERSPACE || currentState == BEGIN)
                currentState = AFTERLONEDASH;
            // If there's a dash after a character, it's a mid-range dash
            else if (currentState == AFTERCHAR)
                currentState = AFTERMIDDASH;
        // Checks for if the current character is a space
        } else if (s[i] == ' '){
            currentState = AFTERSPACE;
            currentType = NONE;
            previousType = NONE;
        
        // Checks for if the current character is a valid character
        } else if (isValidCharacter(s[i])){
            // If this is a new range, delete the previous type
            if (currentState == AFTERCHAR || currentState == AFTERSPACE || currentState == BEGIN){     
                currentType = getType(s[i]);
                previousType = NONE;
                currentState = AFTERCHAR;
            } 
            // If this is a range with a mid-dash, check if the types on either side of the dash are equal
            else if(currentState == AFTERMIDDASH){
                previousType = currentType;
                currentType = getType(s[i]);
                if (currentType != previousType)
                    return ERROR;
                currentState = AFTERCHAR;
            } 
            // If this is a range with lone dash, set the type anyway
            else if(currentState == AFTERLONEDASH){
                currentType = getType(s[i]);
                currentState = AFTERCHAR;
            }

        } else
            return ERROR;
    }

    return NOERROR;
}

int getType(char c){
    enum charType thisType;
    if (isNumber(c))
        thisType = NUM;
    else if (isLowerCase(c))
        thisType = LCHAR;
    else if (isUpperCase(c))
        thisType = UCHAR;
    
    return thisType;
}

int isValidCharacter(char c){
    if (isUpperCase(c) || isLowerCase(c) || isNumber(c))
        return 1;
    else
        return 0;
}

int isNumber(char c){
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

int isLowerCase(char c){
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}

int isUpperCase(char c){
    if (c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}