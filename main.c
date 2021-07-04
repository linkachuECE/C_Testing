#include <stdio.h>

void foldLines(int lineLength, int strLength);

#define STRLENGTH 100
#define LINELENGTH 30

int main(){
    foldLines(LINELENGTH, STRLENGTH);
}

void foldLines(int lineLength, int strLength){
    int c, i = 0;
    char str[STRLENGTH];
    while((c = getchar()) != '\n'){
        str[i++] = c;
    }
    str[i] = '\0';

    int k, letterCount = 0;
    char temp;

    while(str[k] != '\0'){
        if (str[k] == '\n'){
            letterCount = 0;
        }
        else if(letterCount >= lineLength){
            for(int j = strLength - 1; j > k; j--){
                str[j] = str[j-1];
            }
            str[k] = '\n';
            letterCount = 0;
        }
        else
            letterCount++;
        k++;
    }

    printf("%s\n",str);
}