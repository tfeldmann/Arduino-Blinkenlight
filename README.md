# Arduino-Indicator

[![tests](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml/badge.svg)](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml)

## 🚨 Supercharge your status-LEDs 🚨

> This library gives you non-blocking blinking patterns and smooth fade effects for your
> LEDs, buzzers or any other status indicators

## Features

- Basics: On / off / toggle
- Supports blink patterns in the style of "Blink x times, pause, blink y times, repeat"
- Supports infinite blinking
- Supports single flashes and pauses, resuming the previous mode
- Completely non-blocking (no `delay()`)
- Parameters for pause- / off- / on-time duration can be adjusted on the fly
- Super-nice fading effects (optional) with logarithmic brightness compensation for LEDs
- Lightweight
- Easily extendable to control components over SPI / CAN / I2C / ...
- Comes with good-looking defaults (at least I tried)

## Example

This example blinks the built-in LED on pin 13 in the following pattern:

- Blink 2x
- Short pause
- Blink 3x
- Long pause
- Repeat

```C
#include <FadeIndicator.h>

FadeIndicator led(13);

void setup()
{
    led.pattern(2, 3);  // blink 2x, then 3x
}

void loop()
{
    led.update();
}
```

Easy, uh? It's not only blinking, it does so with smooth fading effects and
logarithmic LED brightness compensation. Your boards never looked more professional! /s

> Note: If you don't love the fading effects, just use the `Indicator`-class instead of
> `FadeIndicator`.

## Full API

```C
// Without fading effect:
#include <Indicator.h>
Indicator myPin(13);

// With fading effect:
#include <FadeIndicator.h>
FadeIndicator myPin(13);

// now in your code you can do:
myPin.permanent(LOW);
myPin.blink();
// ... and so on.
```

```C
// set permanently ON
void on();

// set permanently OFF
void off();

// toggle between on / off
void toggle();

// set ON / OFF permanently
void permanent(bool enable);

// blink infinitely. Speed is fast by default.
void blink(SpeedSetting speed = SPEED_FAST);

// blink `num` times, then long pause
// repeats, if `repeat` is set, OFF otherwise.
void pattern(int num, bool repeat = true, SpeedSetting speed = SPEED_FAST);

// blink `num1` times, short pause, blink `num2` times, long pause
// repeats, if `repeat` is set, OFF otherwise.
void pattern(int num1, int num2, bool repeat = true, SpeedSetting speed = SPEED_FAST);

// turn ON for the given duration in ms. Continues in the previous mode afterwards.
void flash(uint16_t duration_ms);

// turn OFF for the given duration in ms. Continues in the previous mode afterwards.
void pause(uint16_t duration_ms);

// setup the timing parameters
void setSpeed(SpeedSetting setting);
// Available by default: SPEED_RAPID, SPEED_FAST, SPEED_SLOW

// Or use your own settings. SpeedSetting is a struct:
typedef struct
{
    uint16_t on_ms;
    uint16_t off_ms;
    uint16_t pause_ms;
    uint16_t ending_ms;
} SpeedSetting;

// ... alternatively you can setup the speed settings directly
void setSpeed(
    uint16_t on_ms,
    uint16_t off_ms,
    uint16_t pause_ms,
    uint16_t ending_ms);

// ... or by providing a single value, the other values are inferred from that
void setSpeed(uint16_t on_ms);

// Hint: You can also modify the values directly - even on the fly - e.g.:
myLed.settings.on_ms = 250;
myLed.settings.pause_ms = 2000;

// `true` if the indicator is currently blinking, showing a pattern, flashing or pausing
bool isOn();

// You must call this in your loop!
// Returns the current value of the indiciator (LOW / HIGH).
// - You can ignore that if you want.
int update();
```

## My status indicator is controlled via CAN / I2C / SPI / ... What can I do?

No problem! You have two options.

- Use the generic `BaseIndicator` class from `<BaseIndicator.h>`. The `.update()`-method
  returns a boolean whether the status is currently `HIGH` or `LOW`. You can then send
  this value to your status indicator (see `examples/GenericBlink`).
  Use the `BaseFadeIndictor` class if you want fading effects. Here the `update` method
  returns an integer `0..255`.

- Subclass the `BaseIndicator` class with custom logic. This is what `Indicator` does
  internally (see `src/Indicator.h`). Have a look at the `SerialBlink` example!
