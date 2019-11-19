/**
 * \file IRDriver.h
 * \brief A file that enables the detection of "goals" in the pingpong game.
 * Although we have called it "goal" in the implementation of this file, the
 * "goal" is in reality a fail-state for the game.
 */

 /**
  * \brief A function that initializes the IR goal detection functionality.
  */
void IR_init();

/**
 * \brief A function that disables the IR goal detection functionality.
 */
void IR_disable();

/**
 * \brief A function that detects if there has been scored a goal.
 * \return Returns an int [0, 1] if there has been scored a goal or not.
 */
int IR_detect_goal();
