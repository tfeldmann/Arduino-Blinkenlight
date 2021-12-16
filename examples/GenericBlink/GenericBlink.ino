/*
This example shows how to use a generic Blinkenlight.
The `update()` method returns HIGH or LOW that you can use however you want.

Of course this example would be easer with a `Blinkenlight` which handles the
digital output automatically.
*/
#include <BaseBlinker.h>

BaseBlinker myBlinkenlight;

void setup()
{
    pinMode(13, OUTPUT);
    myBlinkenlight.blink();
}

void loop()
{
    bool isOn = myBlinkenlight.update();
    digitalWrite(13, isOn);
}
