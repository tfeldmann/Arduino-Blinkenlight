#include <Blinkenlight.h>

Blinkenlight led(13);
SpeedSetting mySettings = {
    .on_ms = 100,
    .off_ms = 100,
    .pause_ms = 2000,
    .ending_ms = 2000,
};

void setup()
{
    // blink 2x on repeat with custom settings
    led.setSpeed(mySettings);
    led.pattern(2, true);
}

void loop()
{
    led.update();
}
