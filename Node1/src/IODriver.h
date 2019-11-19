/**
 * \file IODriver.h
 * \brief A file enabling the IO functionality for the buttons on the IO card.
 */
#include "DEFINITIONS.h"

/**
 * \brief A function initializing the IO functionality.
 * Setting the correct ports as inputs for the buttons on the joystick and the
 * touch buttons on the card.
 */
IO_init();

/**
 * \brief A function that returns the values of the buttons on the P1000.
 * \return Returns a ButtonStruct struct containing the values of the buttons in boolean form [0, 1].
 */
struct ButtonStruct IO_get_button_values(void);
