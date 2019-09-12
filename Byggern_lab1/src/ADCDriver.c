#include <stdio.h>
#include "ADCDriver.h"
#include <util/delay.h>

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

/*
struct DualChannel get_slider_inputs(void) {
    return get_dual_inputs(1, 2);
 }

struct DualChannel get_joystick_inputs(void) {
    return get_dual_inputs(3,4);
}

struct DualChannel get_dual_inputs(int in1, int in2) {
    struct DualChannel val;
    set_channel(in1);
    _delay_ms(40);
    val.chan1 = read_channel();

    set_channel(in2);
    _delay_ms(40);
    val.chan2 = read_channel();

    return val;
}
*/

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
