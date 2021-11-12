#include "Indicator.h"
#include <Arduino.h>

Indicator::Indicator()
{
    // some sane defaults for LED lights
    configure(200, 200, 400, 800, 800, 800, 1600, 3200);
    permanent(false);
}

void Indicator::configure(
    int fast_on_ms,
    int fast_off_ms,
    int fast_pause_ms,
    int fast_ending_ms,
    int slow_on_ms,
    int slow_off_ms,
    int slow_pause_ms,
    int slow_ending_ms)
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

bool Indicator::isOn()
{
    return mode_ != Mode::OFF;
}

void Indicator::permanent(bool enable)
{
    mode_ = enable ? Mode::ON : Mode::OFF;
    set_(enable);
}

void Indicator::toggle()
{
    permanent(!isOn());
}

void Indicator::blink(Speed speed)
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

void Indicator::count(int num, bool repeat, Speed speed)
{
    count(num, 0, repeat, speed);
}

void Indicator::count(int num1, int num2, bool repeat, Speed speed)
{
    speed_ = speed;
    repeat_ = repeat;

    if (mode_ != Mode::COUNTING || num1_ != num1 || num2_ != num2)
    {
        mode_ = Mode::COUNTING;
        num1_ = num1;
        num2_ = num2;
        counter1_ = num1;
        counter2_ = num2;
        lastToggle_ = millis();
        set_(HIGH);
    }
}

int Indicator::update()
{
    if (mode_ == Mode::ON || mode_ == Mode::OFF)
        return state_;

    int on_ms = speed_ == Speed::FAST ? fast_on_ms : slow_on_ms;
    int off_ms = speed_ == Speed::FAST ? fast_off_ms : slow_off_ms;
    int pause_ms = speed_ == Speed::FAST ? fast_pause_ms : slow_pause_ms;
    int ending_ms = speed_ == Speed::FAST ? fast_ending_ms : slow_ending_ms;
    uint32_t time = millis();

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

    else if (mode_ == Mode::COUNTING)
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

void Indicator::set_(bool en)
{
    state_ = en;
}
