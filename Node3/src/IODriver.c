
#include "IODriver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void IO_init() {
    //Set data direction of buzzer pin
    DDRC |= (1<<BUZZER_PIN);

    //Set up timer settings
    buzzer_timer_init();

}

void buzzer_timer_init() {
    //set mode to CTC
    TCCR2A |= (1<<WGM21);

    //With a 4MHz oscillator, fused prescaler of 8, each output compare match
    //with 1024 prescaler at 250 is equavalent to 512ms. 

    OCR2A = 0b11111010;
    
    //enable interrupt on ouput compare match A
    TIMSK2 |= (1<<OCIE2A);
}

void IO_buzzer_timer_enable() {
    //set prescaler to 1024. Enables timer
    TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
}

void IO_buzzer_timer_disable() {
    TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));
}