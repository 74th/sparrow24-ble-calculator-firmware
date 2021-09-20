#include <Adafruit_NeoPixel.h>
#include "led.h"

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void init_led()
{
    pixels.begin();
}

void test_led()
{
    Serial.printf("Orange\n");
    set_orange_led();
    delay(1000);
    Serial.printf("Green\n");
    set_green_led();
    delay(1000);
    Serial.printf("Blue\n");
    set_blue_led();
    delay(1000);
}

void set_orange_led()
{
    set_color_led(255, 165, 0);
}

void set_blue_led()
{
    set_color_led(0, 0, 255);
}

void set_green_led()
{
    set_color_led(0, 128, 0);
}

void set_color_led(int r, int g, int b)
{
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();
}
