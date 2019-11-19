
#include "IODriver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void IO_init() {
    //Set data direction of buzzer pin
    DDRC |= (1<<BUZZER_PIN);
}

void IO_sound_buzzer() {
    PORTC |= (1<<PC3);
}

void IO_silence_buzzer() {
    PORTC &= ~(1<<PC3);
}
