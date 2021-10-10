#include <buttons.h>
#include <utils.h>

uint8_t char_to_numkey(char c)
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

uint8_t char_to_key(char c)
{
    if (c == '0')
        return KC_0;
    if ('1' <= c && c <= '9')
        return c - '1' + KC_1;
    if (c == '+')
        return 0x33 + KC_OFFSET;
    if (c == '-')
        return 0x2d + KC_OFFSET;
    if (c == '*')
        return 0x34 + KC_OFFSET;
    if (c == '/')
        return 0x38 + KC_OFFSET;
    if (c == '.')
        return 0x37 + KC_OFFSET;
    return KC_NONE;
}
