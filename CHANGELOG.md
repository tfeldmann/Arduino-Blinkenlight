# Changelog

## WIP

- `BaseFader` now supports custom value ranges (default = 255)
- Small code speedup in `BaseFader`

## v2.1.0 (2021-12-16)

- Removed default speeds from methods

## v2.0.1 (2021-12-16)

- Renamed library to `Blinkenlight`

## v2.0.0 (2021-12-16)

- **Revamped API!**
- New: writes the state only on changes, not on every update
- Renamed the classes and header files:
  - `BlinkenlightPin` -> `Blinkenlight`
  - `FadingBlinkenlightPin` -> `Fadinglight`
  - `Blinkenlight` -> `BaseBlinker`
  - `FadingBlinkenlight` -> `BaseFader`
- Code cleanups
- Uses GitHub Actions for tests

## v1.2.0 (2021-11-15)

- Renamed `configure`-method

## v1.1.0 (2021-11-12)

- renamed `count()` method to `pattern()`

## v1.0.1 (2021-11-12)

- Initial release
