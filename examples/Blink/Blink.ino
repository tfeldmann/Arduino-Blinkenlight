#include <Indicator.h>

led = PinIndicator(13);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
