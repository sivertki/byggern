#include "fonts.h"

#define BASE_OLED_C_ADDRESS 0x1000
#define BASE_OLED_D_ADDRESS 0x1200
#define TOTAL_PAGE_NUMBERS 8

#define F_CPU 4915200

volatile char *ext_oled_d = (char*) BASE_OLED_D_ADDRESS;
volatile char *ext_oled_c = (char*) BASE_OLED_C_ADDRESS;

void OLED_write_command(uint8_t data);

void OLED_init() {
  OLED_write_command(0xae);        //  display  off
  OLED_write_command(0xa1);        //segment  remap
  OLED_write_command(0xda);        //common  pads  hardware:  alternative
  OLED_write_command(0x12);
  OLED_write_command(0xc8);        //common  output scan direction:com63~com0
  OLED_write_command(0xa8);        //multiplex  ration  mode:63
  OLED_write_command(0x3f);
  OLED_write_command(0xd5);        //display  divide ratio/osc. freq. mode
  OLED_write_command(0x80);
  OLED_write_command(0x81);        //contrast  control
  OLED_write_command(0x50);
  OLED_write_command(0xd9);        //set  pre-charge  period
  OLED_write_command(0x21);
  OLED_write_command(0x20);        //Set  Memory  Addressing  Mode
  OLED_write_command(0x02);       //PAge addressing mode
  OLED_write_command(0xdb);        //VCOM  deselect  level  mode
  OLED_write_command(0x30);
  OLED_write_command(0xad);        //master  configuration
  OLED_write_command(0x00);
  OLED_write_command(0xa4);        //out  follows  RAM  content
  OLED_write_command(0xa6);        //set  normal  display
  OLED_write_command(0xaf);        //  display  on

  OLED_write_command(0x40);       //set display star tline
  //OLED_write_command(0xa5);       //Set entire display on
}

void OLED_write_data(uint8_t data) {
  ext_oled_d[0] = data;
}

void OLED_write_command(uint8_t data) {
  ext_oled_c[0] = data;
}

void OLED_goto_line(uint8_t line) {

  //Set page address
  uint8_t page_start = 0xB0 + line;
  OLED_write_command(page_start);

}

void OLED_goto_column(uint8_t col) {
  uint8_t temp = col;
  uint8_t high_nibble = 0x10;
  uint8_t low_nibble = 0x00;

  low_nibble += temp & 0x0f;

  high_nibble += col >> 4;

  OLED_write_command(low_nibble);
  OLED_write_command(high_nibble);

}

void OLED_clear_line(uint8_t line) {
  OLED_goto_line(line);
  for(uint8_t i = 0; i < 128; i ++) {
    OLED_write_data(0x00);
  }
}

void OLED_goto_pos(uint8_t row, uint8_t column) {
  //TODO
  OLED_goto_line(row);
  OLED_goto_column(column);
}

void OLED_set_brightness(uint8_t lvl) {
  OLED_write_command(0x81);
  OLED_write_command(lvl);
}

void OLED_reset() {
  for(uint8_t i = 0; i < TOTAL_PAGE_NUMBERS; i++) {
    OLED_clear_line(i);
  }
  OLED_goto_pos(0, 0);
}

void OLED_home() {
  //TODO
}

void oled_write_single_char(char data) {
  uint8_t char_out = data - 32;
  //TODO check for different fonts
  for(uint8_t i = 0; i < 4; i++) {
    //OLED_write_data(pgm_read_byte(&font4[char_out][i]));
    OLED_write_data(0xff);
    //printf("writing single line %d \n\r", i);
  }

}
