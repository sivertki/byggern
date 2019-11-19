/**
 * \file ServoDriver.h
 * \brief A file that enables the servo motor and controlling it.
 */

#ifndef _SERVO_DRIVER
#define _SERVO_DRIVER

/**
 * \brief A function that initializes the servo motor on the pingpong game.
 * Sets up a timer on OC1A and a PWM output on pin 24 on the Atmega2560,
 * which corresponds to pin 11 on SHIELD.
 */
void SERVO_init();

/**
 * \brief A function that sets the duty cycle of the PWM signal controlling the servo motor.
 * \param controlIn An uint8_t containing a value for controlling the PWM signal.
 * This function also contains a check that makes sure that it does not produce a PWM
 * signal with too large duty cycle.
 */
void SERVO_setDutyCycle(uint8_t controlIn);

#endif
