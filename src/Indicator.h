#pragma once

#include <Arduino.h>

class Indicator
{
public:
    enum Speed
    {
        SLOW,
        FAST,
    };

    // settings
    unsigned int fast_on_ms;
    unsigned int fast_off_ms;
    unsigned int fast_pause_ms;
    unsigned int fast_ending_ms;
    unsigned int slow_on_ms;
    unsigned int slow_off_ms;
    unsigned int slow_pause_ms;
    unsigned int slow_ending_ms;

    // realtime state of the indicator

    Indicator();
    void configure(
        unsigned int fast_on_ms,
        unsigned int fast_off_ms,
        unsigned int fast_pause_ms,
        unsigned int fast_ending_ms,
        unsigned int slow_on_ms,
        unsigned int slow_off_ms,
        unsigned int slow_pause_ms,
        unsigned int slow_ending_ms);

    bool isOn();

    void toggle();
    void permanent(bool enable);
    void blink(Speed speed = Speed::FAST);
    void pattern(int num, bool repeat = true, Speed speed = Speed::FAST);
    void pattern(int num1, int num2, bool repeat = true, Speed speed = Speed::FAST);
    void flash(unsigned long duration);

    virtual int update();

private:
    bool state_;
    Speed speed_;
    enum Mode
    {
        OFF,
        ON,
        BLINKING,
        PATTERN,
    } mode_;
    int counter1_;
    int counter2_;
    bool repeat_;

    // used for remembering PATTERN settings
    int num1_;
    int num2_;

    // flash
    unsigned long long flash_start_;
    unsigned long flash_duration_;

    unsigned long long lastToggle_;
    void set_(bool en);
};
