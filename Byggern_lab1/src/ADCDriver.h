/**
 * \file ADCDriver.h
 * \brief A file containing the driver for the ADC.
 */

#include <stdio.h>
#include "DEFINITIONS.h"

/**
 * \brief A struct containing the percentage of movement in the joystick X/Y directions.
 */
struct Percentage {
    int xPercentage; /**< The percentage of change in x-direction. */
    int yPercentage; /**< The percentage of change in y-direction.*/
};

/**
 * \brief A function that returns the values of the sliders and the joystick positions.
 * \return Returns a QuadChannel struct containing the values of the sliders and joystick X/Y in range [0, 255].
 */
struct QuadChannel get_adc_values(void);

/**
 * \brief A function that returns the values of the buttons on the P1000.
 * \return Returns a ButtonStruct struct containing the values of the buttons in boolean form [0, 1].
 */
struct ButtonStruct get_button_values(void);

/**
 * \brief A function that calibrates the joystick center positions.
 */
void joy_cal(void);

/**
 * \brief A function that returns the direction that the joystick is being pushed.
 * \return Returns a Direction (specified by the Direction enum) which can be [LEFT, RIGH, UP, DOWN].
 */
Direction joy_dir(void);

/**
 * \brief A function that calculates the percentage displacement of the joystick in the X- and Y-axis.
 * \return Returns a Percentage struct containing the percentages of joystick displacement from the center.
 */
struct Percentage joy_pos(void);
