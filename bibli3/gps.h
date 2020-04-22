#include <TinyGPS.h>
#include <HardwareSerial.h>
#include <DS3231.h>
/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
#define GPS_Tx 4   // TX1
#define GPS_Rx 15  // RX1

HardwareSerial MySerial(1);
static const uint32_t GPSBaud = 9600;
void gps_setup();

RTCDateTime get_time_gps();