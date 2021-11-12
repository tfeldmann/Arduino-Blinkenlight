#pragma once
#include <Arduino.h>

#include "Indicator.h"

class IndicatorPin : public Indicator
{
public:
    IndicatorPin(int pin, bool invert = false)
    {
        Indicator();
        pin_ = pin;
        invert_ = invert;
        pinMode(pin_, OUTPUT);
        write(LOW);
    }

    int update()
    {
        int state = Indicator::update();
        write(state);
    }

    void write(bool state)
    {
        digitalWrite(pin_, state ^ invert_);
    }

private:
    int pin_;
    bool invert_;
};
