#include "headers.h"
#include "testFunctions.c"

#define VLENGTH 1000
#define X 600

int binsearch(int x, int v[], int n);
int linsearch(int x, int v[], int n);


clock_t start, end;

int main(){
    int c;
    int i = 0;
    char s[1000];
    char t[1000];
    char f[1000];

    while((c = getchar()) != EOF)
        s[i++] = c;
    
    s[i] = '\0';

    escape(s,t);

    printf("\n%s\n", t);

    realChars(t,f);

    printf("\n%s\n", f);
}