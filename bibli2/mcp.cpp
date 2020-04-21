#include "mcp.h"
//MCP2434 functions
MCP342x mcp_setup(MCP342x adc)
{
  byte error, address;
      int nDevices;
     
      Serial.println("Scanning...");
     
      nDevices = 0;
      for(address = 1; address < 127; address++ )
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
     
        if (error == 0)
        {
          Serial.print("I2C device found at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.print(address,HEX);
          Serial.println("  !");
     
          nDevices++;
        }
        else if (error==4)
        {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
        }    
      }
      if (nDevices == 0)
        Serial.println("No I2C devices found\n");
      else
        Serial.println("done\n");
        
   address = 0x6E;
  adc = MCP342x(address);


  // Reset devices
  MCP342x::generalCallReset();
  delay(1); // MC342x needs 300us to settle, wait 1ms
  
  // Check device present
  Wire.requestFrom(address, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print("No device found at address ");
    Serial.println(address, HEX);
    while (1)
      ;
  }
  return adc;

}

long int get_channel(MCP342x adc,int channel,MCP342x::Gain gain)
{
  uint8_t err;
  long int value = 0;
  MCP342x::Config status;
  // Initiate a conversion; convertAndRead() will wait until it can be read
  switch(channel){
      case(1):
        err = adc.convertAndRead(MCP342x::channel1, MCP342x::oneShot,
           MCP342x::resolution18, gain,
           1000000, value, status);
        break;
      case(2):
        err = adc.convertAndRead(MCP342x::channel2, MCP342x::oneShot,
           MCP342x::resolution18, gain,
           1000000, value, status);
        break;
      case(3):
        err = adc.convertAndRead(MCP342x::channel3, MCP342x::oneShot,
           MCP342x::resolution18, gain,
           1000000, value, status);
        break;
      case(4):
        err = adc.convertAndRead(MCP342x::channel4, MCP342x::oneShot,
           MCP342x::resolution18, gain,
           1000000, value, status);
        break;
      default:
        break;
     }
  if (err) {
    Serial.print("Convert error: ");
    Serial.println(err);
  }
  else {
    Serial.print("Value: ");
    Serial.println(value,BIN);
  }
  return value;
}
//end of MCP
//
//
//
//
