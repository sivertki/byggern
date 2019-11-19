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

// A CANMessage struct used to contain the recieved message.
static volatile struct CANMessage receivedMessage;

void main(){
    cli();
    SPI_init();
    _delay_ms(20);
    can_init();
    _delay_ms(20);
    MCP_init();
    _delay_ms(20);

    IO_init();
    //IO pin used to blink LED, for heartbeat
    DDRC |= (1<<PC0);

    sei();
    while(1){
        //Heartbeat
        PORTC ^= (1<<PC0);
        _delay_ms(1000);
    }
}


// interrupt triggered by recieving a CAN message.
ISR(INT0_vect){
    uint8_t int_flags = MCP_reads(MCP_CANINTF);

    //clear interrupt flags in CAN controller
    MCP_writes(MCP_CANINTF, 0x00);

    uint8_t bufferZero = int_flags & 0b01;
    uint8_t bufferOne = int_flags & 0b10;

    if(bufferOne) {
        receivedMessage = can_data_receive(BufferOne);

    } else if(bufferZero) {
        receivedMessage = can_data_receive(bufferZero);
    }
    if(receivedMessage.id == 3) {
            //Turn on buzzer
            IO_sound_buzzer();
            _delay_ms(200);
            IO_silence_buzzer();
    }
}
