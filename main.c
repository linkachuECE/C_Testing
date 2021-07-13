#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int switchStrings(char* s1, char* s2);

int main(){
    char s1[] = "Howdy howdy!!!";
    char s2[] = "Howdy yourself";

    printf("%s\n", s1);
    printf("%s\n\n", s2);

    switchStrings(s1, s2);

    printf("%s\n", s1);
    printf("%s\n", s2);
}

int switchStrings(char* s1, char* s2){
  
    if (stringLength(s1) != stringLength(s2))
        return 0;
    
    int length = stringLength(s1);

    char temp[length];

    for(int i = 0; i < length; i++){
        temp[i] = s1[i];
        s1[i] = s2[i];
        s2[i] = temp[i];
    }

    return 1;
}