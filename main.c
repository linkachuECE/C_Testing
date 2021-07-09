#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(){
    char s1[1000];
    char s2[1000];

    int i = 0;
    char c;
    while((c = getchar()) != EOF && c != '\n'){
        s1[i++] = c;
    }
    s1[i] = '\0';

    if(expand(s1, s2))
        printf("%s\n", s2);
    else
        printf("You fucked it up.");
}