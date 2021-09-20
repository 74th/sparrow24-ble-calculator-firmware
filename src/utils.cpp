#include <buttons.h>
#include <utils.h>

uint8_t char_to_key(char c)
{
    if (c == '0')
        return KC_NUM_0;
    if ('1' <= c && c <= '9')
        return c - '1' + KC_NUM_1;
    if (c == '+')
        return KC_NUM_PLUS;
    if (c == '-')
        return KC_NUM_MINUS;
    if (c == '*')
        return KC_NUM_MULTI;
    if (c == '/')
        return KC_NUM_SLASH;
    if (c == '.')
        return KC_NUM_DOT;
    return KC_NONE;
}
