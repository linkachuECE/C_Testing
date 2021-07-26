#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(int argc, char* argv[]){
    char *s = "Hi hello it's me";

    char **sp = (char*)malloc(sizeof s);

    *sp = s;

    printf("%s\n", **sp);
    free(sp);

    return 0;
}