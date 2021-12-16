#include <Blinkenlight.h>

Blinkenlight led(13);

void setup()
{
    // This will set the LED to pattern mode:
    //
    // 1. blink two times
    // 2. pause
    // 3. blink three times
    // 4. longer pause
    //
    // (repeat)
    led.pattern(2, 3);
}

void loop()
{
    led.update();
}
