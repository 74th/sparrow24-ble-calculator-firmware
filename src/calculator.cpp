#include "iostream"
#include "string.h"
#include "./buttons.h"
#include "./calculator.h"

// #include "gmp.h"
#define DEBUG true

#include "gmp-ino.h"
// #define DEBUG false

template <typename... Args>
void wprintf(const char *format, Args const &...args)
{
    if (DEBUG)
    {
        printf(format, args...);

        // Serial.printf(format, args...);
    }
}

const int CHARACTER_LENGTH = 64;
const int CHARACTER_BUFFER_SIZE = 130;

const int DISPLAY_LENGTH = 16;
const int DECIMAL_SIZE = DISPLAY_LENGTH - 2;

const int OP_FIRST = 0;
const int OP_ADD = 1;
const int OP_SUB = 2;
const int OP_MUL = 3;
const int OP_DIV = 4;
const int OP_RESULT = 5;

const char *OVERFLOW_MES = "overflow";
const char *UNDEFINED_MES = "undefined";

char *_b = (char *)malloc(1024);
void print_mpz(mpz_t *num)
{
    mpz_get_str(_b, 10, *num);
    wprintf("%s", _b);
}

void print_mpq(mpq_t *num)
{
    mpq_get_str(_b, 10, *num);
    wprintf("%s", _b);
}

void display_message(char *dst, const char *message)
{
    int n = 0;
    for (int i = 0; message[i] != '\0'; i++)
    {
        dst[i] = message[i];
        n++;
    }
    for (int i = n; i < DISPLAY_LENGTH; i++)
    {
        dst[i] = ' ';
    }
    dst[DISPLAY_LENGTH] = '\0';
}

void fill_suffix_space(char *line)
{
    bool suffix = false;
    for (int i = 0; i < DISPLAY_LENGTH; i++)
    {
        if (!suffix && line[i] == '\0')
        {
            suffix = true;
        }
        if (suffix)
        {
            line[i] = ' ';
        }
    }
    line[DISPLAY_LENGTH] = '\0';
}

mpz_t _buf_num, _buf_den, _buf_out, _buf_shift, _buf_neg_shift, _mpz_zero;
mpq_t _mpq_zero;

void init_buf()
{
    mpz_init(_buf_num);
    mpz_init(_buf_den);
    mpz_init(_buf_out);
    mpz_init(_buf_shift);
    mpz_init(_buf_neg_shift);
    mpz_init(_mpz_zero);
    mpz_set_si(_buf_num, 1);
    for (int i = 0; i < DECIMAL_SIZE - 1; i++)
    {
        mpz_mul_si(_buf_out, _buf_num, 10);
        mpz_set(_buf_num, _buf_out);
    }
    mpz_set(_buf_neg_shift, _buf_num);
    mpz_mul_si(_buf_shift, _buf_neg_shift, 10);
    mpz_set_ui(_mpz_zero, 0);

    mpq_init(_mpq_zero);
    mpq_set_d(_mpq_zero, 0);
}

void parse_input(char *input, int input_length, mpq_t *num)
{
    if (input_length == 0)
    {
        mpq_set_str(*num, "0", 10);
        return;
    }
    int dot = 0;
    int decimal_size = 0;
    for (int i = 0; i < input_length; i++)
    {
        if (input[i] == '.')
        {
            dot = i;
            decimal_size = input_length - 1 - dot;
            break;
        }
    }
    if (decimal_size > 0)
    {
        for (int i = dot; i < input_length - 1; i++)
        {
            input[i] = input[i + 1];
        }
        input[input_length - 1] = '/';
        input[input_length] = '1';
        for (int i = 0; i < decimal_size; i++)
        {
            input[input_length + 1 + i] = '0';
        }
        input[input_length + decimal_size + 1] = '\0';
    }
    wprintf("@@10 [%s]\n", input);
    mpq_set_str(*num, input, 10);
    wprintf("@@11 [");
    print_mpq(num);
    wprintf("]\n");
}

Calculator::Calculator(void)
{
    mpq_init(this->input);
    mpq_init(this->current);
    mpq_set_si(this->current, 0, 0);
    mpq_init(this->result);
    init_buf();

    input_numchar = (char *)malloc(CHARACTER_BUFFER_SIZE);
    input_numchar_length = 0;
    result_numchar = (char *)malloc(CHARACTER_BUFFER_SIZE);
    result_numchar_length = 0;
    current_operation = 0;
}

void Calculator::type_numeric(int key)
{
    bool has_decimal = false;
    for (int i = 0; i < this->input_numchar_length; i++)
    {
        if (this->input_numchar[i] == '.')
        {
            has_decimal = true;
        }
    }

    if (this->input_numchar_length >= CHARACTER_LENGTH)
    {
        return;
    }

    switch (key)
    {
    case KC_NUM_0:
        this->input_numchar[this->input_numchar_length] = '0';
        this->input_numchar_length++;
        break;
    case KC_NUM_1:
        this->input_numchar[this->input_numchar_length] = '1';
        this->input_numchar_length++;
        break;
    case KC_NUM_2:
        this->input_numchar[this->input_numchar_length] = '2';
        this->input_numchar_length++;
        break;
    case KC_NUM_3:
        this->input_numchar[this->input_numchar_length] = '3';
        this->input_numchar_length++;
        break;
    case KC_NUM_4:
        this->input_numchar[this->input_numchar_length] = '4';
        this->input_numchar_length++;
        break;
    case KC_NUM_5:
        this->input_numchar[this->input_numchar_length] = '5';
        this->input_numchar_length++;
        break;
    case KC_NUM_6:
        this->input_numchar[this->input_numchar_length] = '6';
        this->input_numchar_length++;
        break;
    case KC_NUM_7:
        this->input_numchar[this->input_numchar_length] = '7';
        this->input_numchar_length++;
        break;
    case KC_NUM_8:
        this->input_numchar[this->input_numchar_length] = '8';
        this->input_numchar_length++;
        break;
    case KC_NUM_9:
        this->input_numchar[this->input_numchar_length] = '9';
        this->input_numchar_length++;
        break;
    case KC_NUM_DOT:
        if (!has_decimal)
        {
            if (input_numchar_length == 0)
            {
                input_numchar[0] = '0';
                input_numchar[1] = '.';
                this->input_numchar_length = 2;
            }
            else
            {
                input_numchar[this->input_numchar_length] = '.';
                this->input_numchar_length++;
            }
        }
        break;
    }
    this->input_numchar[this->input_numchar_length] = '\0';
}

void Calculator::type_operation(int key)
{
    this->message = NULL;

    if (this->input_numchar_length > 0)
    {
        parse_input(this->input_numchar, this->input_numchar_length, &this->input);
    }

    switch (this->current_operation)
    {
    case OP_FIRST:
        if (this->input_numchar_length > 0)
        {
            mpq_set(this->current, this->input);
        }
        else if (key == KC_NUM_ENTER)
        {
            // AC
            mpq_set(this->current, _mpq_zero);
        }
        break;
    case OP_ADD:
        mpq_add(this->result, this->current, this->input);
        mpq_set(this->current, this->result);
        break;
    case OP_SUB:
        mpq_sub(this->result, this->current, this->input);
        mpq_set(this->current, this->result);
        break;
    case OP_MUL:
        mpq_mul(this->result, this->current, this->input);
        mpq_set(this->current, this->result);
        break;
    case OP_DIV:
        if (mpq_equal(this->input, _mpq_zero))
        {
            this->message = (char *)UNDEFINED_MES;
        }
        else
        {
            mpq_div(this->result, this->current, this->input);
            mpq_set(this->current, this->result);
        }
        break;
    }
    char *text = (char *)malloc(128);
    mpq_get_str(text, 10, this->current);
    wprintf("@@4 [%s]\n", text);
    switch (key)
    {
    case KC_NUM_PLUS:
        this->current_operation = OP_ADD;
        break;
    case KC_NUM_MINUS:
        this->current_operation = OP_SUB;
        break;
    case KC_NUM_MULTI:
        this->current_operation = OP_MUL;
        break;
    case KC_NUM_SLASH:
        this->current_operation = OP_DIV;
        break;
    case KC_NUM_ENTER:
        this->current_operation = OP_FIRST;
        break;
    }
    this->input_numchar[0] = '\0';
    this->input_numchar_length = 0;
}

void Calculator::Type(int key)
{
    switch (key)
    {
    case KC_NUM_1:
    case KC_NUM_2:
    case KC_NUM_3:
    case KC_NUM_4:
    case KC_NUM_5:
    case KC_NUM_6:
    case KC_NUM_7:
    case KC_NUM_8:
    case KC_NUM_9:
    case KC_NUM_0:
    case KC_NUM_DOT:
        this->type_numeric(key);
        return;
    case KC_NUM_PLUS:
    case KC_NUM_MINUS:
    case KC_NUM_MULTI:
    case KC_NUM_SLASH:
    case KC_NUM_ENTER:
        this->type_operation(key);
        return;
    }
}

void Calculator::Type(const char *keys)
{
    int i = 0;
    while (1)
    {
        switch (keys[i])
        {
        case '\0':
            return;
        case '1':
            this->type_numeric(KC_NUM_1);
            break;
        case '2':
            this->type_numeric(KC_NUM_2);
            break;
        case '3':
            this->type_numeric(KC_NUM_3);
            break;
        case '4':
            this->type_numeric(KC_NUM_4);
            break;
        case '5':
            this->type_numeric(KC_NUM_5);
            break;
        case '6':
            this->type_numeric(KC_NUM_6);
            break;
        case '7':
            this->type_numeric(KC_NUM_7);
            break;
        case '8':
            this->type_numeric(KC_NUM_8);
            break;
        case '9':
            this->type_numeric(KC_NUM_9);
            break;
        case '0':
            this->type_numeric(KC_NUM_0);
            break;
        case '.':
            this->type_numeric(KC_NUM_DOT);
            break;
        case '+':
            this->type_operation(KC_NUM_PLUS);
            break;
        case '-':
            this->type_operation(KC_NUM_MINUS);
            break;
        case '*':
            this->type_operation(KC_NUM_MULTI);
            break;
        case '/':
            this->type_operation(KC_NUM_SLASH);
            break;
        case '=':
            this->type_operation(KC_NUM_ENTER);
            break;
        }
        i++;
    }
}

void mpq_to_string(mpq_t *num, char *line)
{
    int sgn = mpq_sgn(*num);
    int display_length = DISPLAY_LENGTH;
    int decimal_size = DECIMAL_SIZE;
    if (sgn < 0)
    {
        display_length = DISPLAY_LENGTH - 1;
        decimal_size = DECIMAL_SIZE - 1;
    }
    for (int i = 0; i < display_length; i++)
    {
        line[i] = ' ';
    }
    line[display_length] = '\0';
    wprintf("@@00[");
    print_mpq(num);
    wprintf("]\n");
    mpq_get_num(_buf_num, *num);
    if (mpz_cmp(_buf_num, _mpz_zero) == 0)
    {
        line[display_length - 1] = '0';
        return;
    }
    if (sgn < 0)
    {
        mpz_neg(_buf_out, _buf_num);
        mpz_set(_buf_num, _buf_out);
    }
    wprintf("@@01[");
    print_mpz(&_buf_num);
    wprintf("]\n");
    mpq_get_den(_buf_den, *num);
    wprintf("@@02[");
    print_mpz(&_buf_den);
    wprintf("]\n");
    if (sgn < 0)
    {
        mpz_mul(_buf_out, _buf_num, _buf_neg_shift);
    }
    else
    {
        mpz_mul(_buf_out, _buf_num, _buf_shift);
    }
    wprintf("@@03[");
    print_mpz(&_buf_out);
    wprintf("]\n");
    mpz_set(_buf_num, _buf_out);
    mpz_fdiv_q(_buf_out, _buf_num, _buf_den);
    wprintf("@@05[");
    print_mpz(&_buf_out);
    wprintf("]\n");
    int length = 0;
    int num_length = 0;
    int decimal_length = 0;
    int space = 0;
    bool dot = true;
    bool to_float = false;
    int top_zeros = 0;
    if (mpz_cmp(_buf_out, _mpz_zero) == 0)
    {
        to_float = true;
    }
    mpz_get_str(_b, 10, _buf_out);
    wprintf("@@06[%s]\n", _b);
    while (1)
    {
        if (_b[length] == '\0')
        {
            break;
        }
        length++;
    }
    for (int i = 0; i < decimal_size; i++)
    {
        if (_b[length - i - 1] != '0')
        {
            decimal_length = decimal_size - i;
            length -= i;
            break;
        }
        if (i == decimal_size - 1)
        {
            decimal_length = 0;
            length -= decimal_size;
        }
    }
    if (length > decimal_length)
    {
        num_length = length - decimal_length;
    }
    wprintf("@@07 length=%d num=%d decimal=%d\n", length, num_length, decimal_length);
    _b[length] = '\0';

    if (decimal_length == 0)
    {
        if (length <= display_length)
        {
            space = display_length - length;
            dot = false;
        }
        else
        {
            to_float = true;
        }
    }
    else if (length > decimal_length)
    {
        if (num_length <= display_length - 1)
        {
            space = display_length - length - 1;
            if (space < 0)
            {
                space = 0;
            }
            dot = true;
        }
        else
        {
            to_float = true;
        }
    }
    else
    {
        top_zeros = decimal_length - length + 1;
        space = display_length - top_zeros - length - 1;
    }
    wprintf("@@08 space=%d top_zeros=%d dot=%d to_float=%d\n", space, top_zeros, dot, to_float);
    if (to_float)
    {
        double d = mpq_get_d(*num);
        sprintf(line, "%+1.8e", d);
        fill_suffix_space(line);
        return;
    }
    int n = 0;
    for (int i = 0; i < space; i++)
    {
        line[n] = ' ';
        n++;
    }
    if (sgn < 0)
    {
        line[n] = '-';
        n++;
    }
    for (int i = 0; i < length - decimal_length; i++)
    {
        line[n] = _b[i];
        n++;
    }
    if (top_zeros > 0)
    {
        line[n] = '0';
        n++;
    }
    if (dot)
    {
        line[n] = '.';
        n++;
    }
    for (int i = 1; i < top_zeros; i++)
    {
        line[n] = '0';
        n++;
    }
    for (int i = num_length; i < length && n < DISPLAY_LENGTH; i++)
    {
        line[n] = _b[i];
        n++;
    }
}

void Calculator::Display(char *line1, char *line2)
{
    if (this->message == NULL)
    {
        mpq_to_string(&this->current, line1);
    }
    else
    {
        display_message(line1, this->message);
    }
    switch (this->current_operation)
    {
    case OP_FIRST:
        line2[0] = ' ';
        break;
    case OP_ADD:
        line2[0] = '+';
        break;
    case OP_SUB:
        line2[0] = '-';
        break;
    case OP_MUL:
        line2[0] = '*';
        break;
    case OP_DIV:
        line2[0] = '/';
        break;
    case OP_RESULT:
        line2[0] = '=';
        break;
    }
    int n = 1;
    for (int i = this->input_numchar_length; i < DISPLAY_LENGTH - 1; i++)
    {
        line2[n] = ' ';
        n++;
    }
    for (int i = this->input_numchar_length - (DISPLAY_LENGTH - 1); i < this->input_numchar_length; i++)
    {
        if (i < 0)
        {
            continue;
        }
        line2[n] = this->input_numchar[i];
        n++;
    }
};
