#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(){
    char s[1000];
    int i = 0;
    char c;
    while((c = getchar()) != EOF && c != '\n'){
        s[i++] = c;
    }

    printf("\n%d\n", hasError(s));
}