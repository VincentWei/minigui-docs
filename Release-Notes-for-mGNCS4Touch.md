# Release Notes

## Version 1.5.0

The MiniGUI development team announces the availability of mGNCS4Touch 1.5.0.

All users of MiniGUI are encouraged to use this version, and report any bugs
and incompatibilities on GitHub:

<https://github.com/VincentWei/mgncs4touch/tree/rel-5-0>

### What's new in this version

- Tune code to comply with MiniGUI 5.0.0 and mGEff 1.5.0.
- Enhance the implementation of `ScrollViewPiece` and `HScrollViewPiece`:
   - Capture the mouse.
   - Use speed meter.

The following API changed:

- `QueryMouseMoveVelocity` is now a dummy implementation for backward compatibility,
  you should use `mSpeedMeter_query_velocity` instead.
- `SpeedMeterProc` and `SpeedMeterMessageHandler` are also dummy implementations just
  for backward compatibility. Both do nothing and return 0.

## Version 1.2.4

The MiniGUI development team announces the availability of mGNCS4Touch 1.2.4.

All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

<https://github.com/VincentWei/mgncs4touch>

### What's new in this version

This version mainly fixed some minor issues:

- Fix errors in API description.

## Version 1.2.3

The MiniGUI development team announces the availability of mGNCS4Touch 1.2.3.

All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

https://github.com/VincentWei/mgncs4touch

### What's new in this version

This version mainly fixed some minor issues:

- Tune some API description.
- Tune format string for `size_t` values.

## Version 1.2.2

The MiniGUI development team announces the availability of mGNCS4Touch 1.2.2.

All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

https://github.com/VincentWei/mgncs4touch

### What's new in this version

* BUGFIXING:
  1. Use screen width to define the `NAVIGATIONBAR_W`.
  1. Always close the polygon region for mShapeTransRoundPiece.
  1. Change screen width in MiniGUI.cfg to 360 from 800.

Please use MiniGUI core V3.4.0 or later.

## Version 1.2.1

The MiniGUI development team announces the availability of mGNCS4Touch 1.2.1.
All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

https://github.com/VincentWei/mgncs4touch

### What's new in this version

  * Use UpdateInvalidClient instead of UpdateInvalidRect.

Please use MiniGUI core V3.2.1 or later.

## Version 1.2.0

The MiniGUI development team announces the availability of mGNCS4Touch 1.2.0.
All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

https://github.com/VincentWei/mgncs4touch

### What's new in this version

  * Renamed to mGNCS4Touch.
  * Tune code to comply with MiniGUI 3.2.x and mGNCS 1.2.x.
  * Tune code for 64-bit platform.
  * Tune code to eliminate all warnings.

### API changes

(none).

## Version 1.0.1

The MiniGUI development team announces the availability of mGNCS4Touch 1.0.1.
All users of MiniGUI are encouraged to test this version carefully, and
report any bugs and incompatibilities on GitHub:

https://github.com/VincentWei/mgncs4touch

### What's new in this version

  * Renamed to mGNCS4Touch.
  * The autoconf/automake config scripts are cleaned up.

### API changes

(none).
