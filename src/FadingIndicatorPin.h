#pragma once
#include <Arduino.h>

#include "FadingIndicator.h"

class FadingIndicatorPin : public FadingIndicator
{
public:
    FadingIndicatorPin(int pin, bool logarithmic = true, int fade_speed = 10)
    {
        FadingIndicator(logarithmic, fade_speed);
        pin_ = pin;
        pinMode(pin_, OUTPUT);
        analogWrite(pin_, 0);
    }

    int update()
    {
        int value = FadingIndicator::update();
        analogWrite(pin_, value);
        return value;
    }

private:
    int pin_;
};
