
//anemometer functions
#ifndef ANEMO_H
#define ANEMO_H

#include "Arduino.h"
#include "mcp.h"
#define anemo_pin 20


  float get_frequency_anemo();
/*returns the frequency of a pwm signal recieved on pin GPIO_20
 * this functions uses interuptions to minimize edge detection latency and 
 * blocks the process as long as the frequency has not been established
 */
  int get_direction();
/*gets the tension of the potentiometer included in the anemometer
 * needs the use of the mcp differential amplifier plugged on channel 1
 */
 
  void cycle_mesure();  
  /*the interrupt handler used in the get_frequency function 
   * to register the rising edges on the pwm signal
   */

//End of anemometre
//

#endif
