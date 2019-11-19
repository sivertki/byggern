/**
 * \file IODriver.h
 * \brief A file that enables the IO functionality on node 3.
 */

#ifndef BUZZER_PIN
#define BUZZER_PIN PC3
#endif

/**
 * \brief A function that initializes the IO functionality.
 */
void IO_init();

/**
 * \brief A function that turns the sound ON.
 */
void IO_sound_buzzer();

/**
 * \brief A function that turns the sound OFF.
 */
void IO_silence_buzzer();
