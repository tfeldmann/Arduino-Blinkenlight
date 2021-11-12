#include <FadePinIndicator.h>

FadePinIndicator led(13);

void setup()
{
    led.blink();
}

void loop()
{
    led.update();
}
