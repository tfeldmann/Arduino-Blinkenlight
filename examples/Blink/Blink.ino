/*
Start a blinking pattern on the built-in LED with a smooth fading effect.
*/

#include <Fadinglight.h>

// We use `Fadinglight` for a smooth fade.
Fadinglight led(13);

void setup()
{
    // blink two times, pause, blink three times, longer pause, repeat
    led.pattern(2, 3);
}

void loop()
{
    led.update();
}
