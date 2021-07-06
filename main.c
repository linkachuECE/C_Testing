#include "headers.h"
#include "usefulFunctions.c"

int main(){
    int n = 0b00000000;
    printf("%d\n", n);

    n = n | 0x0f;
    printf("%d\n", n);
}