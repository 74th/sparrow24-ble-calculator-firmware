// https://akizukidenshi.com/download/ds/akizuki/so1602awwb-uc-wb-u_akizuki_manu.pdf
//
#ifdef ESP_PLATFORM
#include "Arduino.h"
#else
#include "ArduinoFake.h"
#endif
#include <Arduino.h>
#include <Wire.h>
#include <display.h>
#define OLED_ADRS 0x3C //SA0=L(SA0=H の場合は 0x3D)

int DisplayON = 0x0c,
    ClearDisplay = 0x01,
    ReturnHome = 0x02;

void writeData(uint8_t t_data)
{
    Wire.beginTransmission(OLED_ADRS);
    Wire.write(0x40);
    Wire.write(t_data);
    Wire.endTransmission();
    delay(1);
}
void writeCommand(uint8_t t_command)
{
    Wire.beginTransmission(OLED_ADRS);
    Wire.write(0x00);
    Wire.write(t_command);
    Wire.endTransmission();
    delay(10);
}
void contrast_max()
{
    writeCommand(0x2a); //RE=1
    writeCommand(0x79); //SD=1
    writeCommand(0x81); //コントラストセット
    writeCommand(0xFF); //輝度ＭＡＸ
    writeCommand(0x78); //SD を０にもどす
    writeCommand(0x28); //2C=高文字　28=ノーマル
    delay(100);
}
void init_oled()
{
    delay(100);
    writeCommand(ClearDisplay); // Clear Display
    delay(20);
    writeCommand(ReturnHome); // ReturnHome
    delay(2);
    writeCommand(DisplayON); // Send Display on command
    delay(2);
    writeCommand(ClearDisplay); // Clear Display
    delay(20);
}

void display_setup()
{

    Wire.begin(21, 22, 10000);
    init_oled();
}

void write_line0(char input[], int length)
{
    writeCommand(0x00 + 0x80);
    for (int i = 0; i < 16; i++)
    {
        if (i < length)
        {
            writeData(input[i]);
        }
        else
        {
            writeData(' ');
        }
    }
}

void write_line1(char input[], int length)
{
    writeCommand(0x20 + 0x80);
    for (int i = 0; i < 16; i++)
    {
        if (i < length)
        {
            writeData(input[i]);
        }
        else
        {
            writeData(' ');
        }
    }
}

void display_loop()
{
    char c1[] = "test1";
    char c2[] = "test2-1";
    while (1)
    {
        write_line0(c1, 5);
        delay(1000);
        write_line0(c2, 7);
        delay(1000);
        write_line1(c1, 5);
        delay(1000);
        write_line1(c2, 7);
        delay(1000);
    }
    char moji[] = "I2C OLED WHITE12345";
    for (int i = 0; i < 20; i++)
    {
        writeData(moji[i]);
    }

    writeCommand(0x20 + 0x80); //2 行目の先頭

    for (int i = 0; i < 20; i++)
    {
        writeData(i + 0xB1);
    }
    contrast_max(); //輝度を最大に設定
    while (1)
    {
    }
}
