#pragma once
#include <Arduino.h>

typedef struct
{
    uint16_t on_ms;
    uint16_t off_ms;
    uint16_t pause_ms;
    uint16_t ending_ms;
} SpeedSetting;

const SpeedSetting SPEED_RAPID = {
    .on_ms = 100,
    .off_ms = 100,
    .pause_ms = 200,
    .ending_ms = 400,
};

const SpeedSetting SPEED_FAST = {
    .on_ms = 200,
    .off_ms = 200,
    .pause_ms = 400,
    .ending_ms = 800,
};

const SpeedSetting SPEED_SLOW = {
    .on_ms = 800,
    .off_ms = 800,
    .pause_ms = 1600,
    .ending_ms = 3200,
};

class BaseBlinker
{
public:
    BaseBlinker();

    // `true` if it is currently blinking, showing a pattern, flashing or pausing
    bool isOn();

    // set permanently ON
    void on();

    // set permanently OFF
    void off();

    // toggle between on / off
    void toggle();

    // set permanently to `enable`
    void permanent(bool enable);

    // blink infinitely
    void blink();

    // blink infinitely with new speed setting
    void blink(SpeedSetting speed);

    // blink `num` times, then long pause
    // repeats if `repeat` is set, otherwise it is OFF afterwards
    void pattern(int num, bool repeat = true);

    // same as before, but accepts a speed setting
    void pattern(int num, SpeedSetting speed, bool repeat = true);

    // blink `num1` times, short pause, blink `num2` times, long pause
    // repeats if `repeat` is set, otherwise it is OFF afterwards
    void pattern(int num1, int num2, bool repeat = true);

    // same as before, but accepts a speed setting
    void pattern(int num1, int num2, SpeedSetting speed, bool repeat = true);

    // turn ON for the given duration in ms. Continues in the previous mode afterwards.
    void flash(uint16_t duration_ms);

    // turn OFF for the given duration in ms. Continues in the previous mode afterwards.
    void pause(uint16_t duration_ms);

    // different methods to set the speed settings
    void setSpeed(uint16_t on_ms);
    void setSpeed(
        uint16_t on_ms,
        uint16_t off_ms,
        uint16_t pause_ms,
        uint16_t ending_ms);
    void setSpeed(SpeedSetting setting);

    // You must call this in your loop!
    // Returns the current value of the indiciator (LOW / HIGH)
    virtual int update();

    // this is called on state changes and can be implemented in your subclasses
    virtual void write(int state);

    SpeedSetting setting;

protected:
    bool state_;
    bool prevState_;
    virtual void set(int state);
    bool isFlashing();

private:
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
    int num1_;
    int num2_;

    // flash
    uint32_t flashStart_;
    uint16_t flashDuration_;
    bool flashState_;

    uint32_t lastToggle_;
};
