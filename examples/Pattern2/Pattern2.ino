#include <IndicatorPin.h>

IndicatorPin led(13);

void setup()
{
    // This will set the LED to pattern mode:
    //
    // 1. blink three times
    // 2. pause
    // 3. blink five times
    // 4. longer pause
    //
    // (repeat)
    led.pattern(3, 5);
}

void loop()
{
    led.update();
}
