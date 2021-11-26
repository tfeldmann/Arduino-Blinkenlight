#include <Indicator.h>

Indicator led(13);

void setup()
{
    // blink three times, then pause and repeat.
    led.pattern(3);
}

void loop()
{
    led.update();
}
