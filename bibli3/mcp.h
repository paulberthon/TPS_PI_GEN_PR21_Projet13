#ifndef MCP_H
#define MCP_H

#include "Arduino.h"
#include <MCP342x.h>
#include <Wire.h>


MCP342x mcp_setup(MCP342x adc);
/*initializes the mcp amplifier component on the I2C serial link
 * for its future use in the reste of the process
 */

 
long int get_channel(MCP342x adc,int channel,MCP342x::Gain gain);
/*get the tension on the channel n° "channel" on the previously initialyzed
 * Mcp object "adc" while applying the gain "gain" on the entry signal.
 * available channels are 1 to 4 and gains are 1,2,4 and 8
 * gain syntaxe is MCP342x::gainx where x is the gain value
 */

#endif
