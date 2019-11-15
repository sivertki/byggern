#include "DEFINITIONS.h"

IO_init();

/**
 * \brief A function that returns the values of the buttons on the P1000.
 * \return Returns a ButtonStruct struct containing the values of the buttons in boolean form [0, 1].
 */
struct ButtonStruct IO_get_button_values(void);