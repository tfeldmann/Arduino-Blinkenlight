#include "BaseBlinker.h"

BaseBlinker::BaseBlinker()
    : prevState_(LOW)
{
    permanent(LOW);
    write(LOW);
    setSpeed(SPEED_FAST);
}

void BaseBlinker::setSpeed(uint16_t on_ms)
{
    setting.on_ms = on_ms;
    setting.off_ms = on_ms;
    setting.pause_ms = on_ms * 2;
    setting.ending_ms = on_ms * 4;
}

void BaseBlinker::setSpeed(
    uint16_t on_ms,
    uint16_t off_ms,
    uint16_t pause_ms,
    uint16_t ending_ms)
{
    setting.on_ms = on_ms;
    setting.off_ms = off_ms;
    setting.pause_ms = pause_ms;
    setting.ending_ms = ending_ms;
}

void BaseBlinker::setSpeed(SpeedSetting setting)
{
    this->setting = setting;
}

bool BaseBlinker::isOn()
{
    return isFlashing() || mode_ != Mode::OFF;
}

void BaseBlinker::on()
{
    permanent(HIGH);
}

void BaseBlinker::off()
{
    permanent(LOW);
}

void BaseBlinker::toggle()
{
    permanent(!isOn());
}

void BaseBlinker::permanent(bool enable)
{
    mode_ = enable ? Mode::ON : Mode::OFF;
    set(enable);
    update();
}

void BaseBlinker::blink()
{
    // only switch mode if we are not blinking already
    if (mode_ != Mode::BLINKING)
    {
        mode_ = Mode::BLINKING;
        lastToggle_ = millis();
        set(HIGH);
    }
    update();
}

void BaseBlinker::blink(SpeedSetting speed)
{
    setSpeed(speed);
    blink();
}

void BaseBlinker::pattern(int num, bool repeat)
{
    pattern(num, 0, repeat);
}

void BaseBlinker::pattern(int num, SpeedSetting speed, bool repeat)
{
    setSpeed(speed);
    pattern(num, 0, repeat);
}

void BaseBlinker::pattern(int num1, int num2, bool repeat)
{
    repeat_ = repeat;

    if (mode_ != Mode::PATTERN || num1_ != num1 || num2_ != num2)
    {
        mode_ = Mode::PATTERN;
        num1_ = num1;
        num2_ = num2;
        counter1_ = num1;
        counter2_ = num2;
        lastToggle_ = millis();
        set(HIGH);
    }
    update();
}

void BaseBlinker::pattern(int num1, int num2, SpeedSetting speed, bool repeat)
{
    setSpeed(speed);
    pattern(num1, num2, repeat);
}

void BaseBlinker::flash(uint16_t duration_ms)
{
    flashStart_ = millis();
    flashDuration_ = duration_ms;
    flashState_ = HIGH;
    update();
}

void BaseBlinker::pause(uint16_t duration_ms)
{
    flashStart_ = millis();
    flashDuration_ = duration_ms;
    flashState_ = LOW;
    update();
}

int BaseBlinker::update()
{
    // flash overlay - returns to previous mode when finished
    if (isFlashing())
    {
        set(flashState_);
        return state_;
    }

    // permanent mode
    if (mode_ == Mode::ON || mode_ == Mode::OFF)
        return state_;

    uint32_t time = millis();

    // blinking mode
    if (mode_ == Mode::BLINKING)
    {
        if (state_ == HIGH && ((time - lastToggle_) >= setting.on_ms))
        {
            set(LOW);
            lastToggle_ = time;
        }
        else if (state_ == LOW && ((time - lastToggle_) >= setting.off_ms))
        {
            set(HIGH);
            lastToggle_ = time;
        }
    }

    // pattern mode
    else if (mode_ == Mode::PATTERN)
    {
        // reduce counter 1
        if (counter1_ > 0)
        {
            if (state_ == HIGH && ((time - lastToggle_) >= setting.on_ms))
            {
                set(LOW);
                lastToggle_ = time;
                counter1_--;
            }
            else if (state_ == LOW && ((time - lastToggle_) >= setting.off_ms))
            {
                set(HIGH);
                lastToggle_ = time;
            }
        }
        // counter 1 is empty
        else
        {
            if (counter2_ > 0)
            {
                if ((time - lastToggle_) >= setting.pause_ms)
                {
                    set(HIGH);
                    counter1_ = counter2_;
                    counter2_ = 0;
                    lastToggle_ = time;
                }
            }
            // counter 2 is empty, too
            else if (repeat_)
            {
                // reset counters to starting values
                if ((time - lastToggle_) >= setting.ending_ms)
                {
                    set(HIGH);
                    counter1_ = num1_;
                    counter2_ = num2_;
                    lastToggle_ = time;
                }
            }
            else
            {
                permanent(LOW);
            }
        }
    }

    return state_;
}

void BaseBlinker::write(int state)
{
    // do nothing. can be overwritten.
    (void)state;
}

void BaseBlinker::set(int state)
{
    state_ = state;
    // only write changes
    if (prevState_ != state_)
    {
        write(state_);
        prevState_ = state_;
    }
}

bool BaseBlinker::isFlashing()
{
    return !((millis() - flashStart_) > flashDuration_);
}
