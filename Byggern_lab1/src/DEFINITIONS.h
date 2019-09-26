#ifndef ENUMS
#define ENUMS
#include <stdbool.h>
#include <stdio.h>

typedef enum Direction {UP, DOWN, LEFT, RIGHT, NONE} Direction;

struct QuadChannel {
    uint8_t chan1;
    uint8_t chan2;
    uint8_t chan3;
    uint8_t chan4;
};

struct ButtonStruct {
    bool lb;
    bool rb;
    bool jb;
};

#endif
