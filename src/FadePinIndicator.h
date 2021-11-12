#pragma once
#include <Arduino.h>

#include "Indicator.h"

class FadePinIndicator : public Indicator
{
public:
    FadePinIndicator(int pin, int fade_speed = 5)
    {
        Indicator();
        configure(500, 500, 1000, 2000, 1000, 1000, 2000, 4000);
        pin_ = pin;
        value_ = 0;
        fade_speed_ = abs(fade_speed);
        lastUpdate_ = millis();
        pinMode(pin_, OUTPUT);
    }

    bool update()
    {
        bool state = Indicator::update();
        if (millis() - lastUpdate_ > 10)
        {
            int diff = constrain(state * 255 - value_, -fade_speed_, fade_speed_);
            value_ += diff;
            analogWrite(pin_, value_);
            lastUpdate_ = millis();
        }
        return state;
    }

private:
    int pin_;
    int value_;
    int fade_speed_;
    unsigned long long lastUpdate_;
};
