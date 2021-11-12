#include <IndicatorPin.h>

IndicatorPin led(13);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
