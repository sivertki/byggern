/**
 * \file ADCDriver.h
 * \brief A file containing the driver for the ADC.
 */

#include <stdio.h>
#include "DEFINITIONS.h"

/**
 * \brief A function that enables the interrupt for the joystick button.
 */
void ADC_interrupt_enable();

/**
 * \brief A function that disables the interrupt for the joystick button.
 */
void ADC_interrupt_disable();

/**
 * \brief A function that returns the values of the sliders and the joystick positions.
 * \return Returns a QuadADCChannels struct containing the values of the sliders and joystick X/Y in range [0, 255].
 */
struct QuadADCChannels ADC_get_adc_values(void);

/**
 * \brief A function that calibrates the joystick center positions.
 * Since the center of the joystick axis can drift around a bit this is needed to
 * make sure that the center is known. Sets the xCenter and yCenter variables.
 */
void ADC_joystick_calibration(void);

/**
 * \brief A function that returns the direction that the joystick is being pushed.
 * \return Returns a Direction (specified by the Direction enum) which can be [LEFT, RIGH, UP, DOWN].
 */
Direction ADC_get_joystick_direction(void);
