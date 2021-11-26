#include "BaseIndicator.h"

BaseIndicator::BaseIndicator()
{
    // some good looking defaults for LED lights
    setTiming(200, 200, 400, 800, 800, 800, 1600, 3200);
    permanent(LOW);
    prev_state_ = LOW;
    write(LOW);
}

void BaseIndicator::setTiming(uint16_t on_ms)
{
    fast_on_ms = on_ms;
    fast_off_ms = on_ms;
    fast_pause_ms = on_ms * 2;
    fast_ending_ms = on_ms * 4;
    slow_on_ms = on_ms * 2;
    slow_off_ms = on_ms * 2;
    slow_pause_ms = on_ms * 4;
    slow_ending_ms = on_ms * 8;
}

void BaseIndicator::setTiming(
    uint16_t fast_on_ms,
    uint16_t fast_off_ms,
    uint16_t fast_pause_ms,
    uint16_t fast_ending_ms,
    uint16_t slow_on_ms,
    uint16_t slow_off_ms,
    uint16_t slow_pause_ms,
    uint16_t slow_ending_ms)
{
    this->fast_on_ms = fast_on_ms;
    this->fast_off_ms = fast_off_ms;
    this->fast_pause_ms = fast_pause_ms;
    this->fast_ending_ms = fast_ending_ms;
    this->slow_on_ms = slow_on_ms;
    this->slow_off_ms = slow_off_ms;
    this->slow_pause_ms = slow_pause_ms;
    this->slow_ending_ms = slow_ending_ms;
}

bool BaseIndicator::isOn()
{
    return mode_ != Mode::OFF;
}

void BaseIndicator::permanent(bool enable)
{
    mode_ = enable ? Mode::ON : Mode::OFF;
    set_(enable);
}

void BaseIndicator::toggle()
{
    permanent(!isOn());
}

void BaseIndicator::flash(uint16_t duration_ms)
{
    flash_start_ = millis();
    flash_duration_ = duration_ms;
}

void BaseIndicator::blink(Speed speed)
{
    speed_ = speed;

    // only switch mode if we are not blinking already
    if (mode_ != Mode::BLINKING)
    {
        mode_ = Mode::BLINKING;
        lastToggle_ = millis();
        set_(HIGH);
    }
}

void BaseIndicator::pattern(int num, bool repeat, Speed speed)
{
    pattern(num, 0, repeat, speed);
}

void BaseIndicator::pattern(int num1, int num2, bool repeat, Speed speed)
{
    speed_ = speed;
    repeat_ = repeat;

    if (mode_ != Mode::PATTERN || num1_ != num1 || num2_ != num2)
    {
        mode_ = Mode::PATTERN;
        num1_ = num1;
        num2_ = num2;
        counter1_ = num1;
        counter2_ = num2;
        lastToggle_ = millis();
        set_(HIGH);
    }
}

int BaseIndicator::update()
{
    // flash overlay - returns to previous mode when finished
    if (isFlashing())
    {
        set_(HIGH);
        return state_;
    }

    // permanent mode
    if (mode_ == Mode::ON || mode_ == Mode::OFF)
        return state_;

    uint32_t time = millis();
    uint16_t on_ms = speed_ == Speed::FAST ? fast_on_ms : slow_on_ms;
    uint16_t off_ms = speed_ == Speed::FAST ? fast_off_ms : slow_off_ms;
    uint16_t pause_ms = speed_ == Speed::FAST ? fast_pause_ms : slow_pause_ms;
    uint16_t ending_ms = speed_ == Speed::FAST ? fast_ending_ms : slow_ending_ms;

    // blinking mode
    if (mode_ == Mode::BLINKING)
    {
        if (state_ == HIGH && ((time - lastToggle_) >= on_ms))
        {
            set_(LOW);
            lastToggle_ = time;
        }
        else if (state_ == LOW && ((time - lastToggle_) >= off_ms))
        {
            set_(HIGH);
            lastToggle_ = time;
        }
    }

    // pattern mode
    else if (mode_ == Mode::PATTERN)
    {
        // reduce counter 1
        if (counter1_ > 0)
        {
            if (state_ == HIGH && ((time - lastToggle_) >= on_ms))
            {
                set_(LOW);
                lastToggle_ = time;
                counter1_--;
            }
            else if (state_ == LOW && ((time - lastToggle_) >= off_ms))
            {
                set_(HIGH);
                lastToggle_ = time;
            }
        }
        // counter 1 is empty
        else
        {
            if (counter2_ > 0)
            {
                if ((time - lastToggle_) >= pause_ms)
                {
                    set_(HIGH);
                    counter1_ = counter2_;
                    counter2_ = 0;
                    lastToggle_ = time;
                }
            }
            // counter 2 is empty, too
            else if (repeat_)
            {
                // reset counters to starting values
                if ((time - lastToggle_) >= ending_ms)
                {
                    set_(HIGH);
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

void BaseIndicator::set_(bool en)
{
    state_ = en;
    // only write changes
    if (prev_state_ != state_)
    {
        write(state_);
        prev_state_ = state_;
    }
}

bool BaseIndicator::isFlashing()
{
    return !((millis() - flash_start_) > flash_duration_);
}
