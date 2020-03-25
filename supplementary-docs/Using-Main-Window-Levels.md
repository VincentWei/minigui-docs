# Using Main Window Levels

_How to use different main window levels for special main windows._

Table of Contents

## Overview

In this version, we also enhanced the window manager of MiniGUI Core
to support some special main window types.

Before 5.0.0, you can create a topmost main window with the style
`WS_EX_TOPMOST` in order to show the main window above all normal main windows,
and if you use MiniGUI-Processes runtime mode, the server (`mginit`) will
always create global main windows, which are shown on other main windows
created by clients.

Since 5.0.0, we introduce a concept of z-order levels for main windows.
There are eight levels in MiniGUI from top to bottom:

- The tooltip level (`WS_EX_WINTYPE_TOOLTIP`).
- The system/global level (`WS_EX_WINTYPE_GLOBAL`).
- The screen lock level (`WS_EX_WINTYPE_SCREENLOCK`).
- The docker level (`WS_EX_WINTYPE_DOCKER`).
- The higher level (`WS_EX_WINTYPE_HIGHER`).
- The normal level (`WS_EX_WINTYPE_NORMAL`).
- The launcher level (`WS_EX_WINTYPE_LAUNCHER`).
- The desktop or wallpaper.

We use new extended styles like `WS_EX_WINTYPE_GLOBAL` to create main windows
in different levels. For historical reasons, you can still use the legacy style
`WS_EX_TOPMOST`, but MiniGUI will create a main window in the higher
level for this style.

By default, without the style `WS_EX_TOPMOST` or a style like
`WS_EX_WINTYPE_GLOBAL`, MiniGUI will create a main window in
the normal level.

The main windows in the desktop level are managed by MiniGUI.
Any MiniGUI process instance has a virtual desktop window. The desktop
window is an internal object, so no API is provided for app to create
or manage the desktop window.

Note that, under MiniGUI-Processes runtime mode, only the first client
creates the first main window in a z-order level other than higher and normal
levels can create another main window in the same z-order level. And only
the server can create a main window in the global z-order level.

This is a security design for the multi-process runtime environment.

In this version, we also introduce a new extended style called
`WS_EX_AUTOPOSITION`.

If a main window has this extended style when creating it, MiniGUI will
determine the position in the screen for the main window. If the width
or the height of the window specified in `MAINWINCREATE` structure is zero,
MiniGUI will also determine a default size for the main window.

Under the compositing schema, the compositor is responsible to calculate
the position and the size for a main window.

The new `WS_ALWAYSTOP` style can be used to pin a main window on
the top of other main windows in the same z-order level.

