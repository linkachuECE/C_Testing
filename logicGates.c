#include <stdbool.h>
#include "logicGates.h"

bool not(bool x)
{
    return !x;
}

bool and (bool x, bool y)
{
    return x & y;
}

bool nand(bool x, bool y)
{
    return !(x & y);
}

bool or (bool x, bool y)
{
    return x | y;
}

bool nor(bool x, bool y)
{
    return !(x | y);
}

bool xor (bool x, bool y) {
    return x ^ y;
}

    bool xnor(bool x, bool y)
{
    return !(x ^ y);
}
