#include "headers.h"

int stoi(char s[]){
    int i, n;
    n = 0;

    for(i = 0; s[i] >= '0' && s[i] <= '9'; i++){
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

void titleCase(char s[]){
    enum inOrOut{OUT, IN} wordState = OUT;
    
    for(int i = 0; s[i] != '\0'; i++){
        
        if((s[i] >= 'A') && (s[i] <= 'z')){
            if (wordState == OUT){
                wordState = IN;
                if(s[i] >= 'a' && s[i] <= 'z')
                    s[i] = toupper(s[i]);
            }
        } else
            wordState = OUT;
    }
}

int htoi(char s[], int length){
    int stopPoint = 0;
    int i = length - 1;
    int total = 0;
    int currentVal;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        stopPoint = 2;

    for(i; i >= stopPoint; i--){
        currentVal = s[i];
        if(s[i] >= 'a' && s[i] <= 'f')
            currentVal = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            currentVal = s[i] - 'A' + 10;
        else
            currentVal = s[i] - '0';
        
        total += currentVal * pow(16, (length-1) - i);
    }

    return total;
}

void strSqueeze(char s1[], char s2[]){
    for (int i = 0; s2[i] != '\0'; i++){
        for(int j = 0; s1[j] != '\0'; j++){
            if (s2[i] == s1[j]){
                for (int k = j; s1[k] != '\0'; k++){
                    s1[k] = s1[k+1];
                }
                j--;
            }
        }
    }
}