#include <BleKeyboard.h>

class Keyboard
{
private:
    BleKeyboard *bleKeyboard;

public:
    void setup();
    bool connected();
    bool write(uint8_t k);
    bool press(uint8_t k);
    bool release(uint8_t k);
    void release_all();
};
