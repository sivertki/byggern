#include "DEFINITIONS.h"
#include <stdio.h>
void OLED_init();
void oled_write_single_char(uint8_t data);
void OLED_reset();
void OLED_printf(char str[]);

struct OLED_position {
  uint8_t row;
  uint8_t column;
  uint8_t line;
};

//typedef enum Direction {UP, DOWN, LEFT, RIGHT, NONE} Direction;
//enum name {  };
