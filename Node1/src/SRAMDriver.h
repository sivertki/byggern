/**
 * \file SRAMDriver.h
 * \brief A file containing the driver for the SRAM.
 */

/**
 * \brief A function that initilaizes the SRAM for use.
 */
void SRAM_init(void);

/**
 * \brief A function that runs a test on the SRAM.
 */
void SRAM_test(void);

/**
 * \brief A function that writes a highscore to the position specified by the parameter.
 * \param score An uint8_t containing the highscore that is to be written.
 * \param position An uint8_t containing the position in the memory that the score should be written.
 */
void SRAM_highscoreW(uint8_t score, uint8_t position);

/**
 * \brief A function that reads and returns the score located in the position specified in the parameter.
 * \param position An uint8_t containing the position where the score should be written.
 * \return Returns the score located at the position.
 */
uint8_t SRAM_highscoreR(uint8_t position);
