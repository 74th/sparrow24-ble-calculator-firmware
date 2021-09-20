#include <Arduino.h>
#include "sparrow24.h"

static Sparrow24 *instance;
static char *line1, *line2;

void setup()
{
    Serial.begin(115200);
    instance = new Sparrow24();
    instance->Setup();
    Serial.printf("initialized\n");
}

void loop()
{
    instance->Loop();
}
