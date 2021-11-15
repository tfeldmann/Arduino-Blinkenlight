/*
Start a blinking pattern on the built-in LED with a smooth fading effect.
*/
#include <FadingIndicatorPin.h>

FadingIndicatorPin led(13);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
