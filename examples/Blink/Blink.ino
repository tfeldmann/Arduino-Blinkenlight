/*
Start a blinking pattern on the built-in LED.
*/

#include <Blinkenlight.h>

Blinkenlight led(13);

void setup()
{
    // blink two times, pause, blink three times, longer pause, repeat
    led.pattern(2, 3);
}

void loop()
{
    led.update();
}
