#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(int argc, char* argv[]){
    int c;

    while ((c = getchar()) != EOF){
        printf("%c", c);
    }
    printf("\n");
}