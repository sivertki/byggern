#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ADCDriver.h"


#define BASE_ADDRESS 0x1000
#define BASE_ADC_ADDRESS 0x1400

#define F_CPU 4915200 // Clock frequency in Hz

#define CHAN1_SELECT 0x0004
#define CHAN2_SELECT 0x0005
#define CHAN3_SELECT 0x0006
#define CHAN4_SELECT 0x0007

void set_channel(int channel);
uint8_t read_channel(void);
//struct DualChannel get_dual_inputs(int in1, int in2);

int xCenter;
int yCenter;

struct QuadChannel get_adc_values() {
    struct QuadChannel val;
    set_channel(1);
    _delay_ms(40);
    val.chan1 = read_channel();

    set_channel(2);
    _delay_ms(40);
    val.chan2 = read_channel();

    set_channel(3);
    _delay_ms(40);
    val.chan3 = read_channel();

    set_channel(4);
    _delay_ms(40);
    val.chan4 = read_channel();
    return val;
}

struct ButtonStruct get_button_values() {
    struct ButtonStruct buttonValue;

    uint8_t read_port_b = PINB;

    bool left_button = read_port_b & (1<<PB1);
    bool right_button = read_port_b & (1<<PB0);
    bool joy_button = !(read_port_b & (1<<PB2));

    buttonValue.lb = left_button;
    buttonValue.rb = right_button;
    buttonValue.jb = joy_button;

    return buttonValue;
}

 void set_channel(int channel) {
     volatile char *ext_adc = (char*) BASE_ADC_ADDRESS;
     if(channel == 1) {
         ext_adc[0] = CHAN1_SELECT;
     }
     else if(channel == 2) {
         ext_adc[0] = CHAN2_SELECT;
     }
     else if(channel == 3){
         ext_adc[0] = CHAN3_SELECT;
     }
     else if(channel == 4) {
         ext_adc[0] = CHAN4_SELECT;
     }
     else {
         printf("Cannot set channel %d \n", channel);
     }
 }

uint8_t read_channel(void) {
     volatile char *ext_adc = (char*) BASE_ADC_ADDRESS;
     uint8_t read_value = ext_adc[0];
     return read_value;
 }

void joy_cal() {
     struct QuadChannel joy_values = get_adc_values();

     yCenter = joy_values.chan3;
     xCenter = joy_values.chan4;

     printf("Calibration complete. Center Y = %d & Center X = %d\n\r", yCenter, xCenter);

     _delay_ms(500);
 }

Direction joy_dir() {
   struct QuadChannel joy_values = get_adc_values();

    if(joy_values.chan3 >= yCenter*1.6) {
         //printf("UP\n\r");
         return(UP);
    } else if(joy_values.chan3 < yCenter*0.6) {
         //printf("DOWN\n\r");
         return(DOWN);
       }

    if(joy_values.chan4 >= xCenter*1.6) {
         //printf("RIGHT\n\r");
         return(RIGHT);
    } else if(joy_values.chan4 < xCenter*0.6) {
         //printf("LEFT\n\r");
         return(LEFT);
       }

    return(NONE);
 }

/*
struct Percentage joy_pos() {
    struct Percentage returnPercentage;

    float positive_y = (100 / (255 - yCenter));
    float positive_x = (100 / (255 - xCenter));

    struct QuadChannel current_values = get_adc_values();

    if(current_values.chan3 >= yCenter) {
        float printYPercentage = positive_y * (current_values.chan3 - yCenter);
        returnPercentage.yPercentage = (int)printYPercentage;
    }
    else if(current_values.chan3 < yCenter) {
        float printYPercentage = (100 / yCenter) * (current_values.chan3 - yCenter);
        returnPercentage.yPercentage = (int)printYPercentage;
    }

    if(current_values.chan4 >= xCenter) {
        float printXPercentage = positive_x * (current_values.chan4 - xCenter);
        returnPercentage.xPercentage = (int)printXPercentage;
    }
    else if(current_values.chan4 < xCenter) {
        float printXPercentage = (100 / xCenter) * (current_values.chan4 - xCenter);
        returnPercentage.xPercentage = (int)printXPercentage;
    }

    return returnPercentage;
}
*/
