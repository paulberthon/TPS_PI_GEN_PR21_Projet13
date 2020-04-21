#include "pluvio.h"


#define _switch GPIO_NUM_32

#define INT1_PIN_BITMASK 0x100000000


void pluvio_setup(int last_level) {
  gpio_set_direction(_switch, GPIO_MODE_INPUT);
  gpio_pullup_en(_switch);
  gpio_pulldown_dis(_switch);
  gpio_intr_enable(_switch);
  gpio_int_type_t intr_level;
  esp_sleep_ext1_wakeup_mode_t wakeup_level;
  if (last_level==1){
     wakeup_level=ESP_EXT1_WAKEUP_ALL_LOW;
     intr_level=GPIO_INTR_LOW_LEVEL;
  }
  else{
     wakeup_level=ESP_EXT1_WAKEUP_ANY_HIGH;
     intr_level=GPIO_INTR_HIGH_LEVEL;      
  }
  gpio_wakeup_enable(_switch, intr_level);
  esp_sleep_enable_ext1_wakeup(INT1_PIN_BITMASK,wakeup_level);
}
