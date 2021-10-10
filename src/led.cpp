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
    set_color_led(LED_COLOR_ORANGE);
    delay(1000);
    Serial.printf("Green\n");
    set_color_led(LED_COLOR_GREEN);
    delay(1000);
    Serial.printf("Blue\n");
    set_color_led(LED_COLOR_BLUE);
    delay(1000);
}

void _set_color_led(int r, int g, int b)
{
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();
}

void set_color_led(int code)
{
    switch (code)
    {
    case LED_COLOR_RED:
        _set_color_led(255, 0, 0);

        break;
    case LED_COLOR_ORANGE:
        _set_color_led(255, 165, 0);

        break;
    case LED_COLOR_BLUE:
        _set_color_led(0, 0, 255);

        break;
    case LED_COLOR_GREEN:
        _set_color_led(0, 128, 0);
        break;
    case LED_COLOR_PURPLE:
        _set_color_led(128, 0, 128);
        break;
    }
}
