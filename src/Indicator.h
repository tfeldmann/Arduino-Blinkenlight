#pragma once
#include <Arduino.h>

// TODO: support pwm

class BaseLED
{
public:
    BaseLED()
    {
        this->_blinkPeriod = 0;
        this->_state = false;
        this->_stateIsKnown = false;
    }

    virtual void on()
    {
        this->set(HIGH);
    }

    virtual void off()
    {
        this->set(LOW);
    }

    virtual void toggle()
    {
        this->set(!this->_state);
    }

    virtual void set(bool state)
    {
        if (!this->_stateIsKnown || (state != this->_state))
        {
            this->_set(state);
        }
        this->_state = state;
        this->_stateIsKnown = true;
        this->_blinkPeriod = 0; // disable blinking
    }

    virtual void blinkSlow()
    {
        this->blink(800);
    }

    virtual void blinkFast()
    {
        this->blink(200);
    }

    virtual void blink(uint16_t period)
    {
        this->on();
        this->_lastToggle = millis();
        this->_blinkPeriod = period;
    }

    virtual void update()
    {
        if (!this->_blinkPeriod)
            return;

        unsigned long timestamp = millis();
        if (timestamp - this->_lastToggle > this->_blinkPeriod)
        {
            this->_lastToggle = timestamp;
            // toggle led without deactivating blinking
            this->_set(!this->_state);
            this->_state = !this->_state;
        }
    }

    virtual bool isOn()
    {
        return this->_state;
    }

    virtual bool isBlinking()
    {
        return this->_blinkPeriod != 0;
    }

    virtual void _set(bool state)
    {
        (void)state; // prevent compiler warning
    }

private:
    bool _state;
    bool _stateIsKnown;
    uint16_t _blinkPeriod;
    unsigned long _lastToggle;
};

class PinLED : public BaseLED
{
public:
    PinLED(int pin)
        : BaseLED()
    {
        this->_pin = pin;
        pinMode(this->_pin, OUTPUT);
        this->_set(LOW);
    }

    void _set(bool state)
    {
        digitalWrite(this->_pin, state);
    }

private:
    int _pin;
};
