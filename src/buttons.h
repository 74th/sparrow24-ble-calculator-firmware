#include "sdkconfig.h"
#include <Arduino.h>

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

#define KC_OFFSET 136
#define KC_SAFE_OFFSET 0
#define KC_NUMLOCK 0x53 + KC_OFFSET
#define KC_NUM_SLASH 0x54 + KC_OFFSET
#define KC_NUM_MULTI 0x55 + KC_OFFSET
#define KC_NUM_MINUS 0x56 + KC_OFFSET
#define KC_NUM_PLUS 0x57 + KC_OFFSET
#define KC_NUM_ENTER 0x58 + KC_OFFSET
#define KC_NUM_1 0x59 + KC_OFFSET
#define KC_NUM_2 0x5a + KC_OFFSET
#define KC_NUM_3 0x5b + KC_OFFSET
#define KC_NUM_4 0x5c + KC_OFFSET
#define KC_NUM_5 0x5d + KC_OFFSET
#define KC_NUM_6 0x5e + KC_OFFSET
#define KC_NUM_7 0x5f + KC_OFFSET
#define KC_NUM_8 0x60 + KC_OFFSET
#define KC_NUM_9 0x61 + KC_OFFSET
#define KC_NUM_0 0x62 + KC_OFFSET
#define KC_NUM_DOT 0x63 + KC_OFFSET
#define KC_NONE 0x00 + KC_SAFE_OFFSET
#define KC_FN 0x01 + KC_SAFE_OFFSET
#define KC_SEND 0x02 + KC_SAFE_OFFSET
#define KC_MODE_CALCULATOR 0x03 + KC_SAFE_OFFSET
#define KC_MODE_KEYBOARD 0x04 + KC_SAFE_OFFSET

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
