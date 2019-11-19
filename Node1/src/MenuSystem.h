/**
 * \file MenuSystem.h
 * \brief A file containing the menu system for navigating the OLED screen.
 */

#include "DEFINITIONS.h"

 /**
  * \brief A function that writes the home / main menu to the OLED screen.
  */
void MENU_home();

/**
 * \brief A function that facilitates navigation in the menu systems on the OLED screen.
 * \param dir A Direction containing the direction of the joystick [UP, DOWN, LEFT, RIGHT].
 * \param butt A struct ButtonStruct that containing the button presses.
 * \return Returns a State that the menu is in.
 */
State MENU_nav(Direction dir, struct ButtonStruct butt, State state);

/**
 * \brief A function that prints the score achieved at the end of the game.
 * \param score An uint8_t containing the score achieved.
 * This function also checks the highscores stored in the SRAM and saves the
 * achieved score in the correct spot in the SRAM memory if it is a new highscore.
 */
void MENU_print_score(uint8_t score);
