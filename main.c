#include "headers.h"
#include "testFunctions.c"
#include "expand.c"

int main(int argc, char* argv[]){
    if(argc == 1){
        printf("No command line arguments passed.\n");
        return 0;
    }

    printf("You passed the following arguments:\n");
    for(int i = 1; i < argc; i++){
        printf("%s\n",argv[i]);
    }

    return 0;
}