/**
 * \file MenuSystem.h
 * \brief A file containing the menu system for navigating the OLED screen.
 */

 /**
  * \brief A function that writes the home / main menu to the OLED screen.
  */
void menu_home();

/**
 * \brief A function that facilitates navigation in the menu systems on the OLED screen.
 * \param dir A Direction containing the direction of the joystick [UP, DOWN, LEFT, RIGHT].
 * \param butt A struct ButtonStruct that containing the button presses.
 */
void menu_nav(Direction dir, struct ButtonStruct butt);
