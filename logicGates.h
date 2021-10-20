#ifndef LOGICGATES_H
#define LOGICGATES_H
#include <stdbool.h>

bool not(bool x);

bool and (bool x, bool y);

bool nand(bool x, bool y);

bool or (bool x, bool y);

bool nor(bool x, bool y);

bool xor (bool x, bool y);

bool xnor(bool x, bool y);

#endif