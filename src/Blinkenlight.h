#pragma once
#include <Arduino.h>

#include "BaseBlinker.h"

class Blinkenlight : public BaseBlinker
{
public:
    Blinkenlight(int pin, bool invert = false)
        : BaseBlinker(), pin_(pin), invert_(invert)
    {
        pinMode(pin_, OUTPUT);
    }

    void write(int state) override
    {
        digitalWrite(pin_, state ^ invert_);
    }

private:
    int pin_;
    bool invert_;
};
