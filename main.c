#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
    int c, word, lc, state, maxWordLength;
    int wordArray[10];
    state = IN;
    lc = 0;
    maxWordLength = 0;
    word = 0;

    for(int i = 0; i < 10; i++)
        wordArray[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n' || c ==  ' ' || c == '\t') {
            if (state == IN){
                wordArray[word] = lc;
                if(lc > maxWordLength)
                    maxWordLength = lc;
                word++;
                lc = 0;
                state = OUT;
            }
        } else {
            state = IN;
            lc++;
        }
    }

    printf("\n");

    for(int i = 0; i < maxWordLength; i++){
        word = 0;
        while (wordArray[word] != 0){
            if (wordArray[word] > i)
                printf("|");
            else
                printf(" ");

            printf(" ");
            word++;
        }
        printf("\n");
    }

}