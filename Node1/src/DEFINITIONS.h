/**
 * \file DEFINITIONS.h
 * \brief  Contains some key definitions that are required in various modules.
 */

#ifndef ENUMS
#define ENUMS
#include <stdbool.h>
#include <stdio.h>

/**
 * \brief An enum containing the various directions that the joystick can be in.
 */
typedef enum Direction {UP, DOWN, LEFT, RIGHT, NONE} Direction;

/**
 * \brief A struct containing the different values that we get from the sliders and joystick X/Y.
 */
struct QuadChannel {
    uint8_t chan1; /**< Values for the left slider [0, 255] */
    uint8_t chan2; /**< Values for the right slider [0, 255] */
    uint8_t chan3; /**< Values for the y-axis of the joystick [0, 255] */
    uint8_t chan4; /**< Values for the x-axis of the joystick [0, 255] */
};

/**
 * \brief A struct containing the values that we get from the buttons.
 */
struct ButtonStruct {
    bool lb; /**< A boolean describing the state of the left button on the P1000 card. */
    bool rb; /**< A boolean describing the state of the right button on the P1000 card. */
    bool jb; /**< A boolean describing the state of the clickable button on the joystick. */
};

#endif
