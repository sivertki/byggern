#include "OLEDDriver.h"
#include "MenuSystem.h"
#include "CANDriver.h"
#include "SRAMDriver.h"
#include <string.h>
#include <stdio.h>

const uint8_t num_main_menu_items = 3;
const char *main_menu_items[3] = {"GAME JOY", "GAME SLIDE", "CREDITS"};
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
    //OLED_goto_line(pos.line + 1);

    // Goes to the topmost line BELOW menu, and therefore have to have +2.
    OLED_goto_pos(i + 2, 0);
  }
  OLED_goto_pos(0,0);
  current_menu_selection = 1;
}

void MENU_credits() {
  OLED_goto_line(0);
  OLED_set_font(8);
  OLED_printf("-----CREDITS----");
  OLED_goto_pos(1, 0);
  for(uint8_t i = 0; i < num_credits_items; i ++) {
      OLED_printf(credits_items[i]);
    //OLED_goto_line(pos.line + 1);

    // Goes to the topmost line BELOW menu, and therefore have to have +2.
    OLED_goto_pos(i + 2, 0);
  }
}

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
      //previous_direction = dir;
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
        case 3: //CREDITS 3rd alternative
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
 case CREDITS:
    if(dir==LEFT) {
      MENU_home();
      return MENU;
    }
    else {
      return state;
    }
  break;
  return state;
  }
}

void MENU_print_highscores() {
  OLED_reset();
  OLED_goto_pos(0,0);
  OLED_printf("--HIGHSCORES--")
  for (uint8_t i = 0; i < 6; i++) {
    char buffer[1];
    OLED_printf("#");
    sprintf(buffer, "%d", i)
    OLED_printf(buffer);
    OLED_printf(" ");
    sprintf(buffer, "%d", SRAM_highscoreR(i));
    OLED_printf(buffer);
  }
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

  for(uint8_t i = 0; i < 6; i++) {
    if(score > SRAM_highscoreR(i)) {
      SRAM_highscoreW(score, i);

      OLED_reset();
      OLED_goto_pos(0,0);
      OLED_printf("CONGRATULATIONS!!!");
      OLED_goto_pos(2,0);
      OLED_printf("NEW HIGHSCORE!")
      OLED_printf("YOU PLACED # ")
      sprintf(buffer, "%d", i);
      OLED_printf(buffer);

      MENU_print_highscores(i);
    }
  }
}
