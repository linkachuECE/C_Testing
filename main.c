#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(){
    double atof(char s[]);
    double test = atof("12.6e1e2");

    printf("%.9f\n", test);
}