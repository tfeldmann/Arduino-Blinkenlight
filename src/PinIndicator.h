#pragma once
#include <Arduino.h>

#include "Indicator.h"

class PinIndicator : public Indicator
{
public:
    PinIndicator(int pin, bool invert = false)
    {
        Indicator();
        pin_ = pin;
        invert_ = invert;
        pinMode(pin_, OUTPUT);
    }

    bool update()
    {
        bool state = Indicator::update();
        digitalWrite(pin_, state ^ invert_);
    }

private:
    int pin_;
    bool invert_;
};
