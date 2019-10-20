#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define GOAL_THRESHOLD 20
int abort = 0;

void IR_init() {

  //Using pin PA1, pin 77 on atmega, pin 23 on arduino Mega, to power IR emitter
  DDRA |= 1<<PA1;
  PORTA |= 1<<PA1;

  //using A15, pin 82 on Atmega, pin A15 on arduino Mega to IR receiver
  //ADCSRB |= (1<<MUX5);
  //ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);

  //Select Vref = AVcc
  ADMUX |= (1<<REFS0);

  //Enabling ADC and set prescaler
  ADCSRA |= (1 << ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

}

uint8_t IR_read() {
  //start ADC conversion
  ADCSRA |= 1<<ADSC;

  //Wait for result, flag to be cleared
  while(ADCSRA & (1<<ADSC));

  return ADC;
}

void IR_disable() {
  ADCSRA &= ~(1<<ADEN);
}

int IR_detect_goal(){
  uint8_t adc_val;
  adc_val = IR_read();
  //printf("adc_val: %u\n\r", adc_val);

  if(adc_val < GOAL_THRESHOLD) {
    uint16_t adc_val_sum = 0;
    for(int i = 0; i < 5; i++) {
      adc_val_sum += IR_read();
      printf("adc_val_sum: %hu\n\r", adc_val_sum);
      _delay_ms(50);
    }
    uint16_t average = adc_val_sum / 5;
    printf("Avreage: %hu\n\r", average);
    if(average < GOAL_THRESHOLD){
      //printf("average: %u\n\r", adc_val_sum / 5);
      return 1;
    }
  }
  return 0;

}
