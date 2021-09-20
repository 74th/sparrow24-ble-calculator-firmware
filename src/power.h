#include <Arduino.h>

#define OLED_POWER_SW_PIN 4
#define MCU_POWER_DOWN_PIN 23

void init_power();
void oled_power_off();
void mcu_power_off();
