#pragma once
#include <Arduino.h>

#include "BaseIndicator.h"

class Indicator : public BaseIndicator
{
public:
    Indicator(int pin, bool invert = false)
        : BaseIndicator(), pin_(pin), invert_(invert)
    {
        pinMode(pin_, OUTPUT);
    }

    void write(int state) override
    {
        digitalWrite(pin_, state ^ invert_);
        Serial.println(state);
    }

private:
    int pin_;
    bool invert_;
};
