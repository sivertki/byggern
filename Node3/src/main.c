#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "MCPDriver.h"
#include "CANDriver.h"
#include "SPIDriver.h"
#include "IODriver.h"

#define BAUD 9600
#define MYUBBR 103 //TODO calculate FOSC/16/BAUD-1

static volatile struct CANMessage receivedMessage;

void main(){
    cli();
    SPI_init();
    _delay_ms(20);
    MCP_init();
    _delay_ms(20);
    can_init();
    _delay_ms(20);
    IO_init();
    //IO pin used to blink LED, for heartbeat
    DDRC |= (1<<PC0);

    //DDRB |= (1<<PB0)|(1<<PB2);
    //char a = 0xAA;
    
    sei();
    while(1){
        //Heartbeat
        PORTC ^= (1<<PC0);
        _delay_ms(1000);
    }
}

ISR(INT0_vect){
    
    uint8_t int_flags = MCP_reads(MCP_CANINTF);

    //clear interrupt flags in CAN controller
    MCP_writes(MCP_CANINTF, 0x00);

    uint8_t bufferZero = int_flags & 0b01;
    uint8_t bufferOne = int_flags & 0b10;

    if(bufferZero) {
        //TODO
        receivedMessage = can_data_receive();
        interpret_CAN_message(receivedMessage);
        //TODO check id of message, and act upon it

    } else if(bufferOne) {
        //TODO. Maybe do the same as with buffer zero? just run an external function
    }
    
    //clear interrupt flag
    EIFR &= ~(1<<0);
    
}

void interpret_CAN_message(struct CANMessage msg) {
    if(msg.id == 3) {//Goal message TODO is this still true?
        //Turn on buzzer
        PORTC |= (1<<PC3);
        //Enable timer
        IO_buzzer_timer_enable();
        
    }
}

ISR(TIMER2_COMP_vect){
    //Turn off buzzer
    PORTC &= ~(1<<PC3);

    //Disable timer
    IO_buzzer_timer_disable();
    //clear interrupt flag ??
    //Is done automatically
}

