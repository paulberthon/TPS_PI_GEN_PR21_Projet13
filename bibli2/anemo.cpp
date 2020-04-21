
//anemometer functions
#include "anemo.h"
#define anemo_pin 20
bool second;
bool done;
long unsigned t2;
long unsigned t_init;
#define tension_ref 3.3
extern MCP342x adc;
  int get_direction(){
    int tension=get_channel(adc,1,MCP342x::gain1);
    return tension;
  }
  
  void cycle_mesure(){
    if(!second){
      t_init=micros();
      second=true;
    }
     else{
     t2=micros();
     detachInterrupt(anemo_pin);
     second=false;
     }
}

float get_frequency_anemo(){
      second=false;
      attachInterrupt(anemo_pin,cycle_mesure,RISING);
      while(!done){}
      float cycle_time=t2-t_init;
      float frequency=1000000/cycle_time;
      return frequency;
      }


//End of anemometre
//
