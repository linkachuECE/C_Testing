#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(){
    char s1[1000];
    char s2[1000];
    int c;
    int i = 0;
    int j = 0;

    printf("Enter the main string: ");
    while((c = getchar()) != EOF && c != '\n'){
        s1[i++] = c;
    }

    printf("Enter the string to look for: ");
    while((c = getchar()) != EOF && c != '\n'){
        s2[j++] = c;
    }

    s1[i] = '\0';
    s2[j] = '\0';

    int index = strrindex(s1, s2);

    if (index != -1)
        printf("The rightmost position of that string was found at position %d", index);
    else
        printf("That string wasn't found, you dumb fuck");
}