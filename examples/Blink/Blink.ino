/*
Start a blinking pattern on the built-in LED with a smooth fading effect.
*/

#include <FadingIndicatorPin.h>

// Use `FadingIndicatorPin` for a smooth fade.
// If you want hard blinking, use `IndicatorPin`.
FadingIndicatorPin led(13);

void setup()
{
    // blink two times, pause, blink three times, longer pause, repeat
    led.pattern(2, 3);
}

void loop()
{
    led.update();
}
