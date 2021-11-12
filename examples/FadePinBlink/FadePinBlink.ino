#include <FadePinIndicator.h>

FadePinIndicator led(13, true, 10);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
