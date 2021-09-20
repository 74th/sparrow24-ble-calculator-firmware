#include "gmp-ino.h"

class Calculator
{
private:
    mpq_t input, current, result;
    char *input_numchar, *result_numchar;
    int input_numchar_length, result_numchar_length;
    int current_operation;
    char *message;
    void type_numeric(int key);
    void type_operation(int key);

public:
    Calculator(void);
    void Type(int key);
    void Type(const char *keys);
    void Display(char *line1, char *line2);
};
