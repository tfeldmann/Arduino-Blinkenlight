#pragma once
#include <Arduino.h>

#include "BaseFader.h"

class Fadinglight : public BaseFader
{
public:
    Fadinglight(int pin, bool logarithmic = true, int fade_speed = 30)
        : BaseFader(logarithmic, fade_speed), pin_(pin)
    {
        pinMode(pin_, OUTPUT);
        analogWrite(pin_, 0);
    }

    void write(int state) override
    {
        analogWrite(pin_, state);
    }

private:
    int pin_;
};
