# Arduino-Indicator

[![tests](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml/badge.svg)](https://github.com/tfeldmann/Arduino-Indicator/actions/workflows/tests.yml)

## 🚨 Supercharge your status-LEDs 🚨

> This library gives you non-blocking blinking patterns and smooth fade effects.

## Features

- Basics: On / off / toggle
- Supports blink patterns in the style of "Blink x times, pause, blink y times, repeat"
- Supports infinite blinking
- Supports single flashes
- Parameters for pause- / off- / on-time duration can be adjusted on the fly
- Super-nice fading effects (optional)
- Lightweight
- Good-looking defaults (at least I tried)
- Easily extendable
- Non-blocking (no `delay()`), no dynamic allocations

## Available classes

- `Indicator`
- `IndicatorPin`
- `FadeIndicator`
- `FadeIndicatorPin`
