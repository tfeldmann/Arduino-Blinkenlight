#pragma once
#include <Arduino.h>

#include "BaseFadeIndicator.h"

class FadeIndicator : public BaseFadeIndicator
{
public:
    FadeIndicator(int pin, bool logarithmic = true, int fade_speed = 20)
        : BaseFadeIndicator(logarithmic, fade_speed), pin_(pin)
    {
        pinMode(pin_, OUTPUT);
        analogWrite(pin_, 0);
    }

    void write(int state) override
    {
        analogWrite(pin_, state);
        Serial.print("Fade: ");
        Serial.println(state);
    }

private:
    int pin_;
};
