#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ADCDriver.h"


#define BASE_ADDRESS 0x1000 // Start of the OLED (command) address partition.
#define BASE_ADC_ADDRESS 0x1400 // Start of the ADC address partition.

#define F_CPU 4915200 // Clock frequency in Hz

#define CHAN1_SELECT 0x0004 // Select the left slider value stored in the ADC partition of the SRAM.
#define CHAN2_SELECT 0x0005 // Select the right slider value stored in the ADC partition of the SRAM.
#define CHAN3_SELECT 0x0006 // Select the value for the Y-axis of the joystick stored in the ADC partition of the SRAM.
#define CHAN4_SELECT 0x0007 // Select the value for the X-axis of the joystick stored in the ADC partition of the SRAM.

void ADC_interrupt_enable() {
  //set up INT2 for joystick button
  //EMCUCR |= (1<<0);
  GICR |= (1<<5);
}

void ADC_interrupt_disable() {
  GICR &= ~(1<<5);
}

/**
 * \brief A function
 */
void set_channel(int channel);

/**
 * \brief A function
 */
uint8_t read_channel(void);

/**
 * \brief An int containing the center value for the joystick in the X-axis, [0, 255].
 */
int xCenter;
/**
 * \brief An int containing the center value for the joystick in the Y-axis, [0, 255].
 */
int yCenter;

struct QuadADCChannels ADC_get_adc_values() {
    struct QuadADCChannels val;
    set_channel(1);
    _delay_ms(5);
    val.chan1 = read_channel();

    set_channel(2);
    _delay_ms(5);
    val.chan2 = read_channel();

    set_channel(3);
    _delay_ms(5);
    val.chan3 = read_channel();

    set_channel(4);
    _delay_ms(5);
    val.chan4 = read_channel();
    return val;
}

/**
 * \brief A function
 */
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

/**
 * \brief A function
 */
uint8_t read_channel(void) {
     volatile char *ext_adc = (char*) BASE_ADC_ADDRESS;
     uint8_t read_value = ext_adc[0];
     return read_value;
 }

void ADC_joystick_calibration() {
     struct QuadADCChannels joy_values = ADC_get_adc_values();

     yCenter = joy_values.chan3;
     xCenter = joy_values.chan4;

     printf("Calibration complete. Center Y = %d & Center X = %d\n\r", yCenter, xCenter);

 }

Direction ADC_get_joystick_direction() {
   struct QuadADCChannels joy_values = ADC_get_adc_values();
   //printf("ADC values: %d, %d, %d, %d\n\r", joy_values.chan1, joy_values.chan2, joy_values.chan3, joy_values.chan4);
    if(joy_values.chan3 >= yCenter*1.4) {
         return(UP);
    } else if(joy_values.chan3 < yCenter*0.4) {
         return(DOWN);
       }

    if(joy_values.chan4 >= xCenter*1.4) {
         return(RIGHT);
    } else if(joy_values.chan4 < xCenter*0.4) {
         return(LEFT);
       }

    return(NONE);
 }
