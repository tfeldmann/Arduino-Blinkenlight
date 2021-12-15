#include "BaseIndicator.h"

BaseIndicator::BaseIndicator()
    : prevState_(LOW)
{
    permanent(LOW);
    write(LOW);
}

void BaseIndicator::setSpeed(uint16_t on_ms)
{
    setting.on_ms = on_ms;
    setting.off_ms = on_ms;
    setting.pause_ms = on_ms * 2;
    setting.ending_ms = on_ms * 4;
}

void BaseIndicator::setSpeed(
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

void BaseIndicator::setSpeed(SpeedSetting setting)
{
    this->setting = setting;
}

bool BaseIndicator::isOn()
{
    return isFlashing() || mode_ != Mode::OFF;
}

void BaseIndicator::on()
{
    permanent(HIGH);
}

void BaseIndicator::off()
{
    permanent(LOW);
}

void BaseIndicator::toggle()
{
    permanent(!isOn());
}

void BaseIndicator::permanent(bool enable)
{
    mode_ = enable ? Mode::ON : Mode::OFF;
    set(enable);
    update();
}

void BaseIndicator::blink(SpeedSetting speed)
{
    setSpeed(speed);

    // only switch mode if we are not blinking already
    if (mode_ != Mode::BLINKING)
    {
        mode_ = Mode::BLINKING;
        lastToggle_ = millis();
        set(HIGH);
    }
    update();
}

void BaseIndicator::pattern(int num, bool repeat, SpeedSetting speed)
{
    setSpeed(speed);
    pattern(num, 0, repeat, speed);
}

void BaseIndicator::pattern(int num1, int num2, bool repeat, SpeedSetting speed)
{
    setSpeed(speed);
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

void BaseIndicator::flash(uint16_t duration_ms)
{
    flashStart_ = millis();
    flashDuration_ = duration_ms;
    flashState_ = HIGH;
    update();
}

void BaseIndicator::pause(uint16_t duration_ms)
{
    flashStart_ = millis();
    flashDuration_ = duration_ms;
    flashState_ = LOW;
    update();
}

int BaseIndicator::update()
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

void BaseIndicator::write(int state)
{
    // do nothing. can be overwritten.
}

void BaseIndicator::set(int state)
{
    state_ = state;
    // only write changes
    if (prevState_ != state_)
    {
        write(state_);
        prevState_ = state_;
    }
}

bool BaseIndicator::isFlashing()
{
    return !((millis() - flashStart_) > flashDuration_);
}
