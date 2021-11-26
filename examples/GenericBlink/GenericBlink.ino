/*
This example shows how to use a generic indicator.
The `update()` method returns HIGH or LOW that you can use however you want.

Of course this example would be easer with a `IndicatorPin` which handles the
digital output automatically.
*/
#include <BaseIndicator.h>

BaseIndicator myIndicator;

void setup()
{
    pinMode(13, OUTPUT);
    myIndicator.blink();
}

void loop()
{
    digitalWrite(13, myIndicator.update());
}
