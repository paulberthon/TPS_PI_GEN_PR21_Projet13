#ifndef RTC_H
#define RTC_H

#include <DS3231.h>
#include <Wire.h>
#include "Arduino.h"


void clock_init(struct RTCDateTime date);
/* Initializes the clock to the time setted by the struct date
 *  for more informations consult the RTCDateTime struct format contained in the 
 *  DS3231.h librarie file
 */

void clock_setup(struct RTCDateTime alarmtime);
/* sets the clock to trigger an alarm at the time setted by the struct alarmtime
 * for more informations consult the RTCDateTime struct format contained in the 
 *  DS3231.h librarie file 
 */

#endif
