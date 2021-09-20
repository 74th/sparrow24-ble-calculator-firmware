// #include "keyboard.h"
#include "BleKeyboard.h"
#include "buttons.h"
#include "calculator.h"

const int MODE_KEYBOARD = 0;
const int MODE_CALCULATOR = 1;

class Sparrow24
{
private:
    Calculator *calcurator;
    BleKeyboard *keyboard;
    char *line1, *line2;
    int mode;
    void work_as_keyboard(ButtonEvent ev);
    void work_as_calculator(ButtonEvent ev);
    void send_calculator_result();
    void set_led_color();

public:
    void Setup();
    void Loop();
};
