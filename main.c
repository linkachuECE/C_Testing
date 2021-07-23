#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(int argc, char* argv[]){
    char s[1000];
    int c, lCase = -1, i = 0;

    while ((c = getchar()) != EOF)
        s[i++] = c;
    s[i] = '\0';

    if(argc > 1){
        if(argv[1][0] == '-' && (argv[1][1] == 'u' || argv[1][1] == 'U'))
            lCase = LOWERCASE;
        if(argv[1][0] == '-' && (argv[1][1] == 'l' || argv[1][1] == 'L'))
            lCase = UPPERCASE;
        else {
            fprintf(stderr, "Invalid argument");
            return 0;
        }
    }

    convertCase(s, lCase);
    printf("%s", s);

    return 0;
}