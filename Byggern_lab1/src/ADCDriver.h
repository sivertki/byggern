#include <stdio.h>
#include "DEFINITIONS.h"

struct Percentage {
    int xPercentage;
    int yPercentage;
};

struct QuadChannel get_adc_values(void);

struct ButtonStruct get_button_values(void);

void joy_cal(void);

Direction joy_dir(void);

struct Percentage joy_pos(void);
