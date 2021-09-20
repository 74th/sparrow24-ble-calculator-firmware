#include "power.h"

void init_power()
{
    pinMode(OLED_POWER_SW_PIN, OUTPUT);
    pinMode(MCU_POWER_DOWN_PIN, OUTPUT);
    delay(100);
    digitalWrite(OLED_POWER_SW_PIN, HIGH);
    digitalWrite(MCU_POWER_DOWN_PIN, LOW);
    delay(100);
    Serial.printf("power setup done\n");
}

void oled_power_off()
{
    digitalWrite(OLED_POWER_SW_PIN, LOW);
}

void mcu_power_off()
{
    digitalWrite(MCU_POWER_DOWN_PIN, HIGH);
}
