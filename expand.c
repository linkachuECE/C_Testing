#include "headers.h"

#define ERROR 1
#define NOERROR 0

int hasError(char s1[]);
int isValidCharacter(char c);
int isNumber(char c);
int isLowerCase(char c);
int isUpperCase(char c);
int getType(char c);

enum charType {NONE, NUM, UCHAR, LCHAR}; // To hold the character type
enum state {BEGIN, AFTERCHAR, AFTERMIDDASH, AFTERLONEDASH, AFTERSPACE}; // To hold the current state

/*
int expand(char s1[], char s2[]){
    int i = 0; // s1 increment
    int j = 0; // s2 increment

    char rangeBegin, rangeEnd; // To designate the beginning and end of the range

    if (hasError(s1))    // Check for any bad characters
        return -1;

    while (s1[i] != '\0'){
        if (s1[i] == '-'){
            int k = i + 1; // Check if the following pattern is valid
            
        }
        else if (s1[i])
    }
}
*/

int hasError(char s[]){

    enum state currentState = BEGIN;
    enum charType currentType = NONE;
    enum charType previousType = NONE;

    // Cycle through string
    for(int i = 0; s[i] != '\0'; i++){
        if (s[i] == '-'){
            // If there are two dashes in a row, there's an error
            if (currentState == AFTERMIDDASH || currentState == AFTERLONEDASH)
                return ERROR;
            // If there's a dash after a blank or at the beginning of the line, it's a lone dash
            else if (currentState == NONE || currentState == AFTERSPACE)
                currentState = AFTERLONEDASH;
            // If there's a dash after a character, it's a mid-range dash
            else if (currentState == AFTERCHAR)
                currentState = AFTERMIDDASH;
            //  
        } else if (s[i] == ' '){
            currentState = AFTERSPACE;
            currentType = NONE;
            previousType = NONE;
        } else if (isValidCharacter(s[i])){
            // If this is a new range, delete the previous type
            if (currentState == AFTERCHAR){     
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

            else if(currentState == BEGIN){
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
    if (c >= 'A' && c <= 'zZ')
        return 1;
    else
        return 0;
}