/*
struct DualChannel {
    uint8_t chan1;
    uint8_t chan2;
};
*/

#include <stdbool.h>
#include <stdio.h>

struct QuadChannel {
    uint8_t chan1;
    uint8_t chan2;
    uint8_t chan3;
    uint8_t chan4;
};

struct ButtonStruct {
    bool lb;
    bool rb;
};

struct Percentage {
    int xPercentage;
    int yPercentage;
};

typedef enum Direction {UP, DOWN, LEFT, RIGHT, NONE} Direction;

//struct DualChannel get_slider_inputs(void);

struct QuadChannel get_adc_values(void);

struct ButtonStruct get_button_values(void);

void joy_cal(void);

Direction joy_dir(void);

struct Percentage joy_pos(void);
