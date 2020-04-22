#include <TinyGPS.h>
#include <HardwareSerial.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
#define GPS_Tx 4   // TX1
#define GPS_Rx 15  // RX1

// The serial connection to the GPS device
HardwareSerial MySerial(1);
static const uint32_t GPSBaud = 9600;
void gps_setup()
{  
  MySerial.begin(GPSBaud, SERIAL_8N1, GPS_Rx, GPS_Tx);    //set  gps serial port
}

RTCDateTime get_time_gps(){
  RTCDateTime date; 
  unsigned long _date;
  unsigned long _time;
  unsigned long age;
  
  //gps.get_datetime(&_date,&_time,&age);
  _date=20200309;
  _time=112040;
  date.year=_date/10000; 
  date.month=_date/100-date.year*100;
  date.day=_date-date.year*10000-date.month*100;
  date.hour=_time/10000;  
  date.minute=_time/100-date.hour*100;
  date.second=_time-date.hour*10000-date.minute*100;
  return date;
}