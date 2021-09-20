#include "BleKeyboard.h"
#include "Arduino.h"
#include "keyboard.h"

void Keyboard::setup()
{
    this->bleKeyboard = new BleKeyboard("Sparrow24");
    this->bleKeyboard->begin();
}

bool Keyboard::connected()
{
    return this->bleKeyboard->isConnected();
};
bool Keyboard::press(uint8_t k)
{
    return this->bleKeyboard->press(k);
};
bool Keyboard::write(uint8_t k)
{
    return this->bleKeyboard->write(k);
};
bool Keyboard::release(uint8_t k)
{
    return this->bleKeyboard->release(k);
};

void Keyboard::release_all()
{
    return this->bleKeyboard->releaseAll();
}
