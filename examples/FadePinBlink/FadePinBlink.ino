#include <FadingIndicatorPin.h>

FadingIndicatorPin led(13, true, 10);

void setup()
{
    led.count(2, 3);
}

void loop()
{
    led.update();
}
