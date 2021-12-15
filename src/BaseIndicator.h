#pragma once
#include <Arduino.h>

typedef struct
{
    uint16_t on_ms;
    uint16_t off_ms;
    uint16_t pause_ms;
    uint16_t ending_ms;
} SpeedSetting;

const SpeedSetting SPEED_SLOW = {
    .on_ms = 800,
    .off_ms = 800,
    .pause_ms = 1600,
    .ending_ms = 3200,
};

const SpeedSetting SPEED_FAST = {
    .on_ms = 200,
    .off_ms = 200,
    .pause_ms = 400,
    .ending_ms = 800,
};

class BaseIndicator
{
public:
    BaseIndicator();

    void setSpeed(uint16_t on_ms);
    void setSpeed(
        uint16_t on_ms,
        uint16_t off_ms,
        uint16_t pause_ms,
        uint16_t ending_ms);
    void setSpeed(SpeedSetting setting);

    bool isOn();

    void on();
    void off();
    void toggle();
    void permanent(bool enable);
    void blink(SpeedSetting speed = SPEED_FAST);
    void pattern(uint8_t num, bool repeat = true, SpeedSetting speed = SPEED_FAST);
    void pattern(uint8_t num1, uint8_t num2, bool repeat = true, SpeedSetting speed = SPEED_FAST);
    void flash(uint16_t duration_ms);
    void pause(uint16_t duration_ms);

    virtual int update();
    virtual void write(int state);

    SpeedSetting setting;

private:
    bool state_;
    bool prev_state_;
    enum Mode
    {
        OFF,
        ON,
        BLINKING,
        PATTERN,
    } mode_;
    uint8_t counter1_;
    uint8_t counter2_;

    // used for remembering repeating PATTERN settings
    bool repeat_;
    uint8_t num1_;
    uint8_t num2_;

    // flash
    uint32_t flash_start_;
    uint16_t flash_duration_;
    bool flash_state_;

    uint32_t lastToggle_;
    void set_(bool en);
    bool isFlashing();
};
