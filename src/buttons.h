#include "sdkconfig.h"
#include "keycode.h"
#ifdef ESP_PLATFORM
#include "Arduino.h"
#else
#include "ArduinoFake.h"
#endif

#define COL0_PIN 33
#define COL1_PIN 25
#define COL2_PIN 26
#define COL3_PIN 27
#define ROW0_PIN 32
#define ROW1_PIN 17
#define ROW2_PIN 5
#define ROW3_PIN 18
#define ROW4_PIN 19
#define ROW5_PIN 16
#define N_COLS 4
#define N_ROWS 6

struct ButtonEvent
{
    bool ok;
    bool with_fn;
    bool is_pushed;
    bool all_buttons_released;
    uint8_t key;
};

void init_buttons_pins();
ButtonEvent read_buttons_event();
void show_buttons_status();

extern uint8_t COL_PINS[N_COLS];
extern uint8_t ROW_PINS[N_ROWS];
