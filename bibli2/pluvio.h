#ifndef PLUVIO_H
#define PLUVIO_H


#include "Arduino.h"

#define _switch GPIO_NUM_39

#define INT1_PIN_BITMASK 0x8000000000

void pluvio_setup(int last_level);
/*sets the next interruption to be recieved on pin GPIO_39
 * to wake the controller up to be on the level !last_level
 */

#endif
