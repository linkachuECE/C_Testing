#include "headers.h"
#include "logicGates.h"
#include <stdbool.h>

typedef struct{
    bool (*gateFunc)(bool x, bool y);
    char *gateName;
} gate;

gate gates[6] = {
    {and, "AND"},
    {nand, "NAND"},
    {or, "OR"},
    {nor, "NOR"},
    {xor, "XOR"},
    {xnor, "XNOR"},
};

void printMenu(){
    printf("Welcome to the Simulator!\n");
    printf("Choose an option:\n\n");

    for (int i = 0; i < 6; i++){
        printf("%d. %s\n", i + 1, gates[i].gateName);
    }
}

int main(int argc, char *argv[]){
    printMenu();
    printf("%d\n", gates[0].gateFunc(1,1));
}