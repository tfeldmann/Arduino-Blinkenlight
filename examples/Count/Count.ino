#include <Indicator.h>

Indicator led;

void setup()
{
    pinMode(13, OUTPUT);
    led.count(3);
}

void loop()
{
    digitalWrite(13, led.update());
}
