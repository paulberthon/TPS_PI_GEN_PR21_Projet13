#include "RTC.h"
#include "pluvio.h"
#include "anemo.h"
//#include "mcp.h"
#include <my_eeprom_I2C.h>
#include "BluetoothSerial.h"

#define CONFIG_PARTITION_TABLE_OFFSET 0x10000
RTC_DATA_ATTR int bootCount = 0;



DS3231 RTC_DATA_ATTR Clock;
RTCDateTime RTC_DATA_ATTR date;



long int RTC_DATA_ATTR rain=0;

void toggle(){
  ++rain;
}

struct data_struct{
  long wind;
  long cap; 
  RTCDateTime dat;
};

union {
   struct data_struct datas;
   byte wrap[sizeof(data_struct)];
} RTC_DATA_ATTR wrapper;

union {
   struct data_struct datas;
   byte wrap[sizeof(data_struct)];
}RTC_DATA_ATTR buff;
I2Ceeprom eeprom(0x50);  

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

 ///////////////////////////////////////////////



int RTC_DATA_ATTR delais;
RTCDateTime RTC_DATA_ATTR next_date;
bool RTC_DATA_ATTR first_boot=true;
int RTC_DATA_ATTR wakeup_count;
int RTC_DATA_ATTR struct_nb;
struct data_struct RTC_DATA_ATTR ram_datas;
int RTC_DATA_ATTR addr;
MCP342x adc;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  Serial.println("Bonjour");
  
  pinMode(_switch,INPUT);
  if(esp_sleep_get_wakeup_cause()==ESP_SLEEP_WAKEUP_EXT1){
    /*if the wakeup is caused by yhe pluviometter then no operation is done, only the increment
     * of the rain counter
     */
    delay(500);
    ++rain;
      }
  else{/*else the wakeup is caused by the RTC and the default processes are ran*/
  attachInterrupt(_switch,toggle,CHANGE);
  /*allows the pluviometer to trigger a classic interrupt while the daefault measures are done*/
  adc=mcp_setup(adc);
    if (first_boot) {
      /*if this is the first boot from the Lopy this code
       * sets up the position and the RTC reference Time
       */
      //gps_setup();
      ram_datas.dat=get_time_gps();
      clock_init(ram_datas.dat);
      first_boot=false;
      struct_nb=0;
      addr=0;
      delais=1;
      wakeup_count=0;
      ram_datas.wind=0;
      ram_datas.cap=0;
    }
  //ram_datas.wind += get_frequency_anemo();
  ram_datas.cap +=get_direction(); 
  ram_datas.wind += 10;
  Serial.println("cap test");
  Serial.println(ram_datas.cap);
  next_date=date;
  next_date.minute=(next_date.minute+delais)%60;
  
  
  ++wakeup_count;
  
 
  if((wakeup_count%4)==0){
    /*writes datas on memory and sends them via LoRa every wk_number
     * wakeups
     */
    Serial.println(ram_datas.cap);
     ram_datas.wind=ram_datas.wind/4;
     ram_datas.cap=ram_datas.cap/4;
     ram_datas.dat=Clock.getDateTime();
     wrapper.datas=ram_datas;
     Serial.println(ram_datas.cap);
     Serial.println(wrapper.datas.cap);
     eeprom.WritePage(addr, wrapper.wrap, sizeof(wrapper.datas));
     eeprom.ReadBuffer(addr, buff.wrap,sizeof(wrapper.datas));
     addr+=sizeof(wrapper.datas);
     Serial.println(addr);
     Serial.println(buff.datas.wind);
  Serial.println(buff.datas.cap);
     ++struct_nb;
     Serial.println("reset");
     
     Serial.print(ram_datas.wind);
     Serial.print(ram_datas.cap);
     ram_datas.wind=0;
     ram_datas.cap=0;
     Serial.print("----------------");
  }
  Serial.println("test3");
  if(wakeup_count==30){
    for(int i=0;i<struct_nb;i++){
     eeprom.ReadBuffer(i*sizeof(wrapper.datas), buff.wrap,sizeof(wrapper.datas));
     Serial.print("data:");
     Serial.println(i);
     Serial.println(buff.datas.wind);
     Serial.println(ram_datas.cap);
    }
  }
  }
  eeprom.ReadBuffer(addr-sizeof(wrapper.datas), buff.wrap,sizeof(wrapper.datas));
  Serial.println("test4");
  Serial.println(buff.datas.wind);
  Serial.println(buff.datas.cap);
  Serial.print("Wakeups:");
  Serial.println(wakeup_count);
  int last_level=digitalRead(_switch);
  /*sets the wake-up reasons for the next wakeup*/
  clock_setup(next_date);
  pluvio_setup(last_level);
  esp_deep_sleep_start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
