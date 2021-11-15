# Arduino-Indicator

[![tests](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml/badge.svg)](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml)

## 🚨 Supercharge your status-LEDs 🚨

> This library gives you non-blocking blinking patterns and smooth fade effects for your
> LEDs, buzzers or any other status indicators

## Features

- Basics: On / off / toggle
- Supports blink patterns in the style of "Blink x times, pause, blink y times, repeat"
- Supports infinite blinking
- Supports single flashes
- Parameters for pause- / off- / on-time duration can be adjusted on the fly
- Super-nice fading effects (optional) with logarithmic brightness compensation
- Lightweight
- Good-looking defaults (at least I tried)
- Easily extendable
- Non-blocking (no `delay()`), no dynamic allocations

## Example

This example blinks the built-in LED on pin 13 with a smooth fade effect and logarithmic
brightness compensation in the following pattern:

`Blink 2x -> Short pause -> Blink 3x -> Long pause -> Repeat`

```C
#include <FadingIndicatorPin.h>

FadingIndicatorPin led(13);

void setup()
{
    led.pattern(2, 3);  // blink 2x, then 3x
}

void loop()
{
    led.update();
}
```

## Full API

```C
// Without fading effect:
#include <IndicatorPin.h>
IndicatorPin myPin(13);

// With fading effect:
#include <FadingIndicatorPin.h>
FadingIndicatorPin myPin(13);

// now in your code you can do:
myPin.permanent(LOW);
myPin.blink();
// ... and so on.
```

```C
// toggle between on / off
void toggle();

// set ON / OFF permanently
void permanent(bool enable);

// blink infinitely. `speed` can be 0 (slow) or 1 (fast).
void blink(Speed speed = Speed::FAST);

// blink `num` times, then long pause
// repeats, if `repeat` is set, OFF otherwise.
void pattern(int num, bool repeat = true, Speed speed = Speed::FAST);

// blink `num1` times, short pause, blink `num2` times, long pause
// repeats, if `repeat` is set, OFF otherwise.
void pattern(int num1, int num2, bool repeat = true, Speed speed = Speed::FAST);

// turn ON for the given duration in ms. Continues in the previous mode afterwards.
void flash(uint16_t duration_ms);

// setup the timing parameters
void setTiming(
    uint16_t fast_on_ms,
    uint16_t fast_off_ms,
    uint16_t fast_pause_ms,
    uint16_t fast_ending_ms,
    uint16_t slow_on_ms,
    uint16_t slow_off_ms,
    uint16_t slow_pause_ms,
    uint16_t slow_ending_ms);

// Hint: You can also modify the values directly, e.g.:
myLed.fast_on_ms = 250;

// shorthand for setting up the timing parameters by defining the fast ON duration in ms.
// all other durations are derived from that with some internal factors.
void setTiming(uint16_t on_ms);

// `true` if the indicator is currently blinking, showing a pattern or flashing
bool isOn();

// You must call this in your loop!
// Returns the current value of the indiciator (LOW / HIGH).
// - You can ignore that if you want.
int update();
```

## My status indicator is controlled by CAN / I2C / SPI / ... What can I do?

No problem! Just subclass the generic `Indicator` class from `<Indicator.h>` or use it
directly. The `bool Indicator::update()`-method returns a boolean whether the status is
currently `HIGH` or `LOW`. You can then send this value to your status indicator.

Have a look at `IndicatorPin.h` for a subclassing example or look into
`examples/GenericBlink` for direct usage.
