void OLED_init();
void oled_write_single_char(uint8_t data);
void OLED_reset();
void OLED_printf(char str[]);
void OLED_home();

struct OLED_position {
  uint8_t row;
  uint8_t column;
  uint8_t line;
};
//enum name {  };
