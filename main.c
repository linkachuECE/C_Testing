#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int switchStrings(char* s1, char* s2);

int main(){
    int x[100];

    for (int n = 0; n < 100 && getint(&x[n]) != EOF; n++)
        printf("%d\n", x[n]);

    return 0;
}