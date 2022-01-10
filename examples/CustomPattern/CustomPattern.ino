#include <Blinkenlight.h>

Blinkenlight led(13);

CustomPattern my_pattern[4] = {
    {.duration = 100, .value = HIGH},
    {.duration = 233, .value = LOW},
    {.duration = 100, .value = HIGH},
    {.duration = 233, .value = LOW},
};

void setup()
{
    led.custom(my_pattern, 4);
}

void loop()
{
    led.update();
}
