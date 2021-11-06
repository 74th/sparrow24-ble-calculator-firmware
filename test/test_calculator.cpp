#include <unity.h>
#include <string.h>

#include "./calculator.h"

char *line1;
char *line2;
Calculator *calc;

void setUp()
{
    line1 = (char *)malloc(1024);
    line2 = (char *)malloc(1024);
    calc = new Calculator();
}

void tearDown()
{
    free(line1);
    free(line2);
    free(calc);
}

void test_simple()
{
    const char *type = "12";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "               0"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "              12"));

    type = "+";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              12"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "+               "));

    type = "12=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              24"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "13+14=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              27"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "13-18=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              -5"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));
}

void test_complex()
{
    const char *type = "12+12=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              24"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "+";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              24"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "+               "));

    type = "12=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "              36"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "               0"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));
}

void decimal()
{
    const char *type = "13.234+5.678=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "          18.912"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "1/125=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "           0.008"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "100/3=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "33.3333333333333"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "10/3=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "3.33333333333333"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "10/3000=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "0.00333333333333"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));
}

void test_float_point()
{
    const char *type = "9999999999999998+1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "9999999999999999"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "9999999999999999+1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "+1.00000000e+16 "));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0-999999999999998-1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "-999999999999999"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0-999999999999999-1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "-1.00000000e+15 "));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0.0000000000001*0.1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "0.00000000000001"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0.00000000000001*0.1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "+1.00000000e-15 "));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0-0.000000000001*0.1=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "-0.0000000000001"));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "0-0.0000000000001*0.1=";
    calc->Type(type);
    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "-1.00000000e-14 "));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));

    type = "10/0=";
    calc->Type(type);

    calc->Display(line1, line2);
    printf("[%s] [%s] %s\n", line1, line2, type);
    TEST_ASSERT_EQUAL_INT(0, strcmp(line1, "undefined       "));
    TEST_ASSERT_EQUAL_INT(0, strcmp(line2, "                "));
}

int run_test(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_simple);
    RUN_TEST(test_complex);
    RUN_TEST(test_float_point);
    return UNITY_END();
}

#ifdef ESP_PLATFORM

void setup()
{
    delay(2000);
    run_test();
}

void loop()
{
    delay(1000);
}

#else

int main(void)
{
    return run_test();
}

#endif
