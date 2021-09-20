#include <Arduino.h>
#include <BleKeyboard.h>
#include "power.h"
#include "display.h"
#include "led.h"
#include "utils.h"
#include "sparrow24.h"

void Sparrow24::Setup()
{
    init_power();
    calcurator = new Calculator();
    init_buttons_pins();
    init_led();
    display_setup();
    keyboard = new BleKeyboard("Sparrow24");
    keyboard->begin();

    line1 = (char *)malloc(16 + 1);
    line2 = (char *)malloc(16 + 1);
    for (int i = 0; i < 16; i++)
    {
        line1[i] = ' ';
        line2[i] = ' ';
    }
    line1[16] = '\0';
    line2[16] = '\0';

    mode = MODE_KEYBOARD;
    set_led_color();
}

void Sparrow24::set_led_color()
{
    switch (mode)
    {
    case MODE_CALCULATOR:
        set_blue_led();
        break;
    case MODE_KEYBOARD:
        set_orange_led();
        break;
    }
}

void Sparrow24::work_as_keyboard(ButtonEvent ev)
{
    bool pushed = false;
    if (this->keyboard->isConnected())
    {
        Serial.printf("pushed! %d %d\n", ev.with_fn, ev.key);
        if (!ev.with_fn)
        {
            keyboard->press(ev.key);
            pushed = true;
        }
        else
        {
            keyboard->release(ev.key);
        }
        if (pushed && ev.all_buttons_released)
        {
            keyboard->releaseAll();
            pushed = false;
        }
    }
}
void Sparrow24::work_as_calculator(ButtonEvent ev)
{
    if (ev.is_pushed)
    {
        calcurator->Type(ev.key);
        calcurator->Display(line1, line2);
        write_line0(line1, 16);
        write_line1(line2, 16);
        Serial.printf("[%s][%s]\n", line1, line2);
    }
}

void Sparrow24::send_calculator_result()
{
    Serial.printf("send key [%s]", line1);
    for (int i = 0; i < 16; i++)
    {
        uint8_t key = char_to_key(line1[i]);
        if (key != KC_NONE)
        {
            keyboard->write(key);
        }
    }
}

void Sparrow24::Loop()
{
    ButtonEvent ev = read_buttons_event();
    if (!ev.ok)
    {
        return;
    }
    Serial.printf("pushed %d %d\n", ev.with_fn, ev.key);

    switch (ev.key)
    {
    case KC_MODE_KEYBOARD:
        if (ev.is_pushed)
        {
            Serial.printf("mode set keyboard");
            mode = MODE_KEYBOARD;
            set_led_color();
        }
        break;
    case KC_MODE_CALCULATOR:
        if (ev.is_pushed)
        {
            Serial.printf("mode set keyboard");
            mode = MODE_CALCULATOR;
            set_led_color();
        }
        break;
    case KC_SEND:
        if (ev.is_pushed)
        {
            send_calculator_result();
        }
        break;
    default:
        if (mode == MODE_KEYBOARD)
        {
            work_as_keyboard(ev);
        }
        else if (mode == MODE_CALCULATOR)
        {
            work_as_calculator(ev);
        }
        break;
    }
}
