#include <Fadinglight.h>

Fadinglight led(13);

uint32_t lastSwitch;
bool isFast;

void setup()
{
    isFast = false;
    lastSwitch = millis();

    led.blink(SPEED_SLOW);
}

void loop()
{
    led.update();

    // toggle speed every 3 seconds
    if (millis() - lastSwitch > 3000)
    {
        lastSwitch = millis();
        isFast = !isFast;
        led.blink(isFast ? SPEED_FAST : SPEED_SLOW);
    }
}
