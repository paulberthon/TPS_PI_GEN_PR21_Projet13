//RTC Setup
#include "RTC.h"

extern DS3231 Clock;

void clock_init(struct RTCDateTime date){
  Clock.begin();
  // Disarm alarms and clear alarms for this example, because alarms is battery backed.
  // Under normal conditions, the settings should be reset after power and restart microcontroller.
  Clock.enableOutput(false);
  Clock.armAlarm2(false);
  Clock.clearAlarm1();
  Clock.clearAlarm2();
  Clock.setDateTime(date.year, date.month, date.day, date.hour, date.minute,date.second);
}
void clock_setup(struct RTCDateTime alarmtime){
  Clock.begin();
  // Disarm alarms and clear alarms for this example, because alarms is battery backed.
  // Under normal conditions, the settings should be reset after power and restart microcontroller.
  Clock.enableOutput(false);
  Clock.armAlarm2(false);
  Clock.clearAlarm1();
  Clock.clearAlarm2();
  Clock.setAlarm1(alarmtime.dayOfWeek, alarmtime.hour, alarmtime.minute, alarmtime.second, DS3231_MATCH_S);
  Clock.armAlarm1(true);
  gpio_set_direction(GPIO_NUM_39, GPIO_MODE_INPUT);
  gpio_intr_enable(GPIO_NUM_39);
  gpio_wakeup_enable(GPIO_NUM_39, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_39,0); //1 = High, 0 = Low
}


bool check_creneaux(int** creneaux,RTCDateTime now)
{
  if (creneaux[now.dayOfWeek][0]!=NULL){
  int heure_debut=creneaux[now.dayOfWeek][0];
  int min_debut=creneaux[now.dayOfWeek][1];
  int heure_fin=creneaux[now.dayOfWeek][2];
  int min_fin=creneaux[now.dayOfWeek][3];
  if( heure_debut>now.hour || now.hour>heure_fin){
    return false;
  }
  else{
    if(heure_debut==hour){
      if(min_debut>now.minute) return false;
    }
    if(now.hour==heure_fin){
      if(min_fin<now.minute) return false;
    }
  }
  }
  return true;
}
