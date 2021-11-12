# Arduino-Indicator

## 🚨 Supercharge your status-LEDs 🚨

> [The LED] should first blink two times, then pause for a moment and then blink three times.

> The device beeps three times in a row to indicate an error. A single beep means it is turned on.

Ever had one of these? Then this library is for you. You'll want to use this for every single
LED you will ever control.

- Basics: On / off / toggle
- Supports counted (!) and infinite blinking
- Super-nice fading effects (optional)
- Super lightweight
- Sane defaults (I tried)
- Easily extendable
- Non-blocking (no `delay()`)

## Available classes

- `Indicator`
- `IndicatorPin`
- `FadeIndicator`
- `FadeIndicatorPin`
