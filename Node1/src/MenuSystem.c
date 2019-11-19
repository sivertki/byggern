#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include "OLEDDriver.h"
#include "MenuSystem.h"
#include "CANDriver.h"
#include "SRAMDriver.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

const uint8_t num_main_menu_items = 4;
const char *main_menu_items[4] = {"GAME JOY", "GAME SLIDE", "HIGHSCORES","CREDITS"};
//const char *sub_menus[5] = {*main_menu_items, *main_menu_items, *settings_menu_items *main_menu_items, *main_menu_items, };

const uint8_t num_credits_items = 3;
const char * credits_items[3] = {"Ida", "Sivert", "Nikolai" };

/**
 * \brief An uint8_t containing information about the current menu item selected.
 */
uint8_t current_menu_selection = 1;

/**
 * \brief A Direction containing information about the last / previous direction move that was executed in the menu system
 */
Direction previous_direction;

/**
 * \brief An uint8_t containing information about the last menu item that was selected in the menu system.
 */
uint8_t previous_menu_selection = 0;

void MENU_highscores();

void MENU_home() {
  OLED_reset();
  OLED_goto_line(0);
  OLED_set_font(8);
  OLED_printf("------MENU------");
  OLED_goto_pos(1, 0);
  for(uint8_t i = 0; i < num_main_menu_items; i ++) {
    if(i == 0) {
      menu_print_selected(main_menu_items[i]);
    }
    else {
      OLED_printf(" ");
      OLED_printf(main_menu_items[i]);
    }

    OLED_goto_pos(i + 2, 0);
  }
  OLED_goto_pos(0,0);
  current_menu_selection = 1;
}

/**
 * \brief A function that writes out the credits to the screen.
 */
void MENU_credits() {
  OLED_goto_line(0);
  OLED_set_font(8);
  OLED_printf("-----CREDITS----");
  OLED_goto_pos(1, 0);
  for(uint8_t i = 0; i < num_credits_items; i ++) {
      OLED_printf(credits_items[i]);

    OLED_goto_pos(i + 2, 0);
  }
}

/**
 * \brief A function that prints the indicators that shows the selected menu item.
 * \param str[] A char array containing the menu item selected.
 */
void menu_print_selected(char str[]) {
  OLED_printf(">");
  OLED_printf(str);
  OLED_printf("<");
}


State MENU_nav(Direction dir, struct ButtonStruct butt, State state) {
  struct CANMessage game_state_msg;

 switch (state)
 {
 case MENU:
    switch (dir) {
    case UP:
      if(current_menu_selection != 1) {
        OLED_goto_line(current_menu_selection);
        OLED_clear_line(current_menu_selection);
        OLED_printf(" ");
        OLED_printf(main_menu_items[current_menu_selection -1]);
        current_menu_selection -= 1;
        OLED_goto_line(current_menu_selection);
        OLED_clear_line(current_menu_selection);
        menu_print_selected(main_menu_items[current_menu_selection -1]);
      }
    break;
    case DOWN:
      if(current_menu_selection != num_main_menu_items) {
        OLED_goto_line(current_menu_selection);
        OLED_clear_line(current_menu_selection);
        OLED_printf(" ");
        OLED_printf(main_menu_items[current_menu_selection -1]);
        current_menu_selection += 1;
        OLED_goto_line(current_menu_selection);
        OLED_clear_line(current_menu_selection);
        menu_print_selected(main_menu_items[current_menu_selection -1]);
      }
    break;
    case RIGHT:
        //RIGHT means the menu item is selected. State needs to be changed accordingly.
        printf("Selected program: %s\n\r", main_menu_items[current_menu_selection - 1]);
        switch (current_menu_selection)
        {
        case 1: //PINGPONG JOY 1st alternative
          OLED_reset();
          OLED_printf("PING PONG GAME");
          OLED_goto_pos(2, 0);
          OLED_printf("ACTIVE!");
          OLED_goto_pos(4,0);
          OLED_printf("USING:");
          OLED_goto_pos(5,0);
          OLED_printf("JOYSTICK!");
          OLED_goto_pos(0, 0);

          game_state_msg.id = 4;
          game_state_msg.length = 1;
          game_state_msg.data[0] = 0;
          can_message_send(&game_state_msg);
          return PINGPONGJOY;
          break;
        case 2: //PINGONG SLIDER 2nd alternative
          OLED_reset();
          OLED_printf("PING PONG GAME");
          OLED_goto_pos(2, 0);
          OLED_printf("ACTIVE!");
          OLED_goto_pos(4,0);
          OLED_printf("USING:");
          OLED_goto_pos(5,0);
          OLED_printf("SLIDER!");
          OLED_goto_pos(0, 0);

          game_state_msg.id = 4;
          game_state_msg.length = 1;
          game_state_msg.data[0] = 1;
          can_message_send(&game_state_msg);
          return PINGPONGSLIDE;
          break;
        case 3:
          OLED_reset();
          MENU_highscores();
          return HIGHSCORES;
          break;
        case 4: //CREDITS 4rd alternative
          OLED_reset();
          MENU_credits();
          return CREDITS;
          break;
        }
    break;
    case NONE:
    return state;
    break;
    }
  break;
case HIGHSCORES:
    if(dir==LEFT) {
      MENU_home();
      return MENU;
    }
    else {
      return HIGHSCORES;
    }
  break;
 case CREDITS:
    if(dir==LEFT) {
      MENU_home();
      return MENU;
    }
    else {
      return CREDITS;
    }
  break;
  default:
  return state;
  }
}

/**
 * \brief A function that prints the highscore list stored in the SRAM to the screen.
 */
void MENU_highscores() {
  OLED_printf("-HIGHSCORES-");
  OLED_goto_pos(2,0);
  for (uint8_t i = 0; i < 5; i++) {
    OLED_goto_pos(i + 2, 0);
    char buffer[2];
    OLED_printf("#");
    sprintf(buffer, "%d", i + 1);
    OLED_printf(buffer);
    OLED_printf(" ");
    sprintf(buffer, "%d", SRAM_highscoreR(i));
    _delay_ms(5);
    OLED_printf(buffer);
  }
  _delay_ms(3000);
  OLED_goto_pos(0,0);
}

void MENU_print_score(uint8_t score) {
  OLED_reset();
  OLED_goto_pos(0,0);
  OLED_printf("GAME OVER!");
  OLED_goto_pos(2,0);
  OLED_printf("YOUR SCORE:");
  OLED_goto_pos(3,0);
  char buffer[13];
  sprintf(buffer, "%d", score);
  OLED_printf(buffer);
  _delay_ms(2000);

  for(uint8_t i = 0; i < 5; i++) {
    uint8_t highSRAM = SRAM_highscoreR(i);
    //printf("Highscore found in SRAM = %d, Your highscore = %d", highSRAM, score);

    char highStore[5];

    if(score > SRAM_highscoreR(i)) {
      for(uint8_t j = 0; j < 5; j++) {
        highStore[j] = SRAM_highscoreR(j);
        printf("Highstore #%d = %d\n\r", i, highStore[i]);
      }

      for(uint8_t k = 0; k < 4 - i; k++) {
        SRAM_highscoreW(highStore[k + i], (i + 1) + k);
      }

      _delay_ms(5);
      SRAM_highscoreW(score, i);
      _delay_ms(5);

      OLED_reset();
      OLED_printf("CONGRATZ!!!");
      OLED_goto_pos(2,0);
      OLED_printf("NEW HIGHSCORE");
      OLED_goto_pos(3,0);
      OLED_printf("YOU PLACED # ");
      char shortBuffer[2];
      sprintf(shortBuffer, "%d", i + 1);
      OLED_printf(shortBuffer);

      break;
    }
  }

  _delay_ms(2000);
}
