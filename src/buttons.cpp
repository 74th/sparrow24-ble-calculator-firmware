#include "buttons.h"
#include <Arduino.h>

uint8_t COL_PINS[N_COLS] = {COL0_PIN, COL1_PIN, COL2_PIN, COL3_PIN};
uint8_t ROW_PINS[N_ROWS] = {ROW0_PIN, ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN, ROW5_PIN};

uint8_t KEY_ASSIGNS[N_ROWS][N_COLS] = {
    {KC_MODE_KEYBOARD, KC_SEND, KC_SEND, KC_MODE_CALCULATOR},
    {KC_NUMLOCK, KC_NUM_SLASH, KC_NUM_MULTI, KC_NUM_MINUS},
    {KC_NUM_7, KC_NUM_8, KC_NUM_9, KC_NUM_PLUS},
    {KC_NUM_4, KC_NUM_5, KC_NUM_6, KC_NUM_PLUS},
    {KC_NUM_1, KC_NUM_2, KC_NUM_3, KC_NUM_ENTER},
    {KC_NUM_0, KC_NUM_0, KC_NUM_DOT, KC_NUM_ENTER},
};

bool push_state[N_ROWS][N_COLS];

void init_buttons_pins()
{
    pinMode(COL_PINS[0], INPUT_PULLUP);
    pinMode(COL_PINS[1], INPUT_PULLUP);
    pinMode(COL_PINS[2], INPUT_PULLUP);
    pinMode(COL_PINS[3], INPUT_PULLUP);
    pinMode(ROW_PINS[0], OUTPUT);
    pinMode(ROW_PINS[1], OUTPUT);
    pinMode(ROW_PINS[2], OUTPUT);
    pinMode(ROW_PINS[3], OUTPUT);
    pinMode(ROW_PINS[4], OUTPUT);
    pinMode(ROW_PINS[5], OUTPUT);
    for (int r = 0; r < N_ROWS; r++)
    {
        for (int c = 0; c < N_COLS; c++)
        {
            push_state[r][c] = false;
        }
    }
}

ButtonEvent read_buttons_event()
{
    ButtonEvent result = {false, false, false, true, 0};
    for (int r = 0; r < N_ROWS; r++)
    {
        for (int i = 0; i < N_ROWS; i++)
        {
            digitalWrite(ROW_PINS[i], i == r ? LOW : HIGH);
        }
        delay(1);

        for (int c = 0; c < N_COLS; c++)
        {
            bool pushed = digitalRead(COL_PINS[c]) == LOW;
            if (KEY_ASSIGNS[r][c] == KC_FN)
            {
                result.with_fn = pushed;
            }
            else if (pushed != push_state[r][c])
            {
                push_state[r][c] = pushed;
                if (pushed)
                {
                    result.ok = true;
                    result.key = KEY_ASSIGNS[r][c];
                    result.is_pushed = true;
                }
                else
                {
                    result.ok = true;
                    result.key = KEY_ASSIGNS[r][c];
                    result.is_pushed = false;
                }
            }
            if (pushed)
            {
                result.all_buttons_released = false;
            }
        }
    }
    return result;
}

void show_buttons_status()
{
    for (int r = 0; r < N_ROWS; r++)
    {
        Serial.printf("%d:", ROW_PINS[r]);
        for (int i = 0; i < N_ROWS; i++)
        {
            digitalWrite(ROW_PINS[i], i == r ? LOW : HIGH);
        }
        delay(10);

        for (int c = 0; c < N_COLS; c++)
        {
            bool pushed = digitalRead(COL_PINS[c]) == LOW;
            Serial.printf("%d,%d ", COL_PINS[c], pushed);
        }
        Serial.printf("/");
    }
    Serial.printf("\n");
}
