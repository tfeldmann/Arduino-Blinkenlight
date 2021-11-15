#pragma once
#include <Arduino.h>

class Indicator
{
public:
    enum Speed
    {
        SLOW = 0,
        FAST = 1,
    };

    // settings
    uint16_t fast_on_ms;
    uint16_t fast_off_ms;
    uint16_t fast_pause_ms;
    uint16_t fast_ending_ms;
    uint16_t slow_on_ms;
    uint16_t slow_off_ms;
    uint16_t slow_pause_ms;
    uint16_t slow_ending_ms;

    // realtime state of the indicator

    Indicator();

    void setTiming(uint16_t on_ms);
    void setTiming(
        uint16_t fast_on_ms,
        uint16_t fast_off_ms,
        uint16_t fast_pause_ms,
        uint16_t fast_ending_ms,
        uint16_t slow_on_ms,
        uint16_t slow_off_ms,
        uint16_t slow_pause_ms,
        uint16_t slow_ending_ms);

    bool isOn();

    void toggle();
    void permanent(bool enable);
    void blink(Speed speed = Speed::FAST);
    void pattern(int num, bool repeat = true, Speed speed = Speed::FAST);
    void pattern(int num1, int num2, bool repeat = true, Speed speed = Speed::FAST);
    void flash(uint16_t duration_ms);

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
    uint32_t flash_start_;
    uint16_t flash_duration_;

    uint32_t lastToggle_;
    void set_(bool en);
    bool isFlashing();
};
