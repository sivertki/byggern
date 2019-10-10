#include "OLEDDriver.h"
#include "DEFINITIONS.h"
#include "MenuSystem.h"
#include <string.h>

const uint8_t num_main_menu_items = 5;
const char *main_menu_items[5] = {"PING-PONG", "HIGH SCORES", "SETTINGS", "DRAW LINE", "ANIMATION"};
//const char *sub_menus[5] = {*main_menu_items, *main_menu_items, *settings_menu_items *main_menu_items, *main_menu_items, };

const uint8_t num_settings_menu_items = 5;
const char *settings_menu_items[5] = {"BRIGHTNESS", "INVERT SCREEN", "OPTION 3", "OPTION 4", "OPTION 5"};

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

void menu_home() {
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
}

/**
 * \brief A function that generates the sub menus.
 * This function will generate every menu below the main / home menu. 
 */
void generate_sub_menu() {
  OLED_goto_line(0);
  OLED_set_font(8);
  OLED_printf("----------------");
  uint8_t offset = 0;
  uint8_t diff = 16 - strlen(main_menu_items[previous_menu_selection]);

  //Prints the selected sub-menu in the middle of dashed lines
  while(diff > 1) {
    offset += 1;
    diff -= 2;
  }
  OLED_goto_pos(0, offset * 8);
  OLED_printf(main_menu_items[previous_menu_selection -1]);

  switch (previous_menu_selection) {
    case 2:

    break;
    case 4:
      for(uint8_t i = 0; i < num_settings_menu_items; i ++) {
        if(i == 0) {
          menu_print_selected(settings_menu_items[i -1]);
        }
        else {
          OLED_printf(" ");
          OLED_printf(settings_menu_items[i -1]);
        }
        //OLED_goto_line(pos.line + 1);

        // Goes to the topmost line BELOW menu, and therefore have to have +2.
        OLED_goto_pos(i + 2, 0);
      }
    break;
  }
}

void menu_print_selected(char str[]) {
  OLED_printf(">");
  OLED_printf(str);
  OLED_printf("<");
}

void menu_nav(Direction dir, struct ButtonStruct butt) {
  if(previous_direction == dir) {
    if (butt.jb && current_menu_selection != previous_menu_selection) {
      printf("%s\n\r", main_menu_items[current_menu_selection - 1]);
      previous_menu_selection = current_menu_selection;
      generate_sub_menu();
    }
    return;
  }

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
        //printf("%s\n\r", main_menu_items[current_menu_selection - 1]);
        generate_sub_menu();
    break;
    case LEFT:
        printf("%s\n\r", "LEFTINSWITCH");
    break;
  }

  previous_direction = dir;
}
