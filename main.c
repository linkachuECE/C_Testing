#include "headers.h"
#include "logicGates.h"

int main(int argc, char *argv[])
{
    int a = 0, b = 0;
    if (argc == 3)
    {
        a = argv[1][0] - '0';
        b = argv[2][0] - '0';
    }

    int output = or (and(a, b), and(not(a), not(b)));
    printf("%s\n", output == 1 ? "true" : "false");
}