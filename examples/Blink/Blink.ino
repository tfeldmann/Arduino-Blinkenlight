#include <Indicator.h>

PinIndicator led(13);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
