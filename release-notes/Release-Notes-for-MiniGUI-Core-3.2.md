# Release Notes for MiniGUI Core 3.2

Table of Contents

- [Version 3.2.2](#version-322)
  * [What's new in this version](#what-s-new-in-this-version)
- [Version 3.2.0](#version-320)
  * [What's new in this version](#what-s-new-in-this-version-1)
  * [Type changes](#type-changes)
    + [Changes of handle types](#changes-of-handle-types)
    + [Changes of integer types](#changes-of-integer-types)
    + [New integer types](#new-integer-types)
  * [API changes](#api-changes)
    + [Integer macros](#integer-macros)
    + [Structure and functions](#structure-and-functions)
      - [Message](#message)
      - [Window callback procedure](#window-callback-procedure)
      - [Notification callback procedure](#notification-callback-procedure)
      - [Time and timer](#time-and-timer)
      - [Miscellaneous](#miscellaneous)
  * [Configuration option changes](#configuration-option-changes)

## Version 3.2.2

MiniGUI 3.2.2 was released on April 16, 2019.

### What's new in this version

* ENHANCEMENTS:
  1. New API: `SyncUpdateDC`. You can use this function to synchronize
    the update rectangles of a surface to screen, if the surface
    represents the shadow frame buffer of the screen.
    * configure option: `--enable-syncupdate`
    * macro: `_MGUSE_SYNC_UPDATE`
  1. New API `UpdateInvalidClient`. You can use this function to update
    the invalid client region of a window instantly.
  1. New API `LoadDevFontFromIncoreData`. You can use this function to load
    a device font from incore data.
  1. Use different colors for the output of `_DBG_PRINTF` and `_ERR_PRINTF`.
  1. Add `__mg_save_jpg` function for storing MYBITMAP as JPEG file (10km).
  1. Modified logic for checking JPEG format (10km).
  1. Support BIDI for Unicode charsets and cleanup the implementation.
    * New API: `GetGlyphBIDIType` to get the glyph type in BIDI.
    * New DC attribute: BIDI flag.
  1. Add a new key `dpi` for NEWGAL engine to define the DPI of the screen.
     If it is absent, use 96 as the default DPI.
  1. Add an item for `GetGDCapability` to return DPI of the DC.
  1. New API `InitSlaveScreenEx` to specify the DPI of slave screen.
     Define `InitSlaveScreen` as an inline function calling `InitSlaveScreenEx`.
  1. Enhance commlcd engine to support more pixel type and synchronously update.
  1. New USVFB IAL engine and NEWGAL engine for web display server.
  1. New type `QDWORD` for a quauter of DWORD. This type is 16-bit long on
    64-bit architecture, and 8-bit long on 32-bit architecture.
  1. New macros for QDWORD:
    * `MAKEDWORD`: make a DWROD from four QDWORDs.
    * `FIRST_QDWORD`: get the first (LSB) QDWORD from a DWORD.
    * `SECOND_QDWORD`: get the second (LSB) QDWORD from a DWORD.
    * `THIRD_QDWORD`: get the third (LSB) QDWORD from a DWORD.
    * `FOURTH_QDWORD`: get the fourth (LSB) QDWORD from a DWORD.
  1. New header for CommLCD NEWGAL engine and COMM IAL engine:
    `<minigui/exstubs.h>`.

* BUGFIXING:
  1. handle `PNG_COLOR_TYPE_GRAY_ALPHA` color type of PNG files.
  1. Fix a bug to free a null pointer (ReleaseDC).
  1. No need to make the pitch of FT2 monobitmap single-byte aligned.
     This bug may generate dirty dots for monobitmap glyph from TTF.
  1. Skip null pixels for SUBPIXEL glyphs. This bug will always show background
     pixels of one SUBPIXEL glyph.
  1. Fix the bug of wrong bounding box handling for SUBPIXEL rendering of a glyph.
  1. Tune cache implementation of FreeType2 font engine.
    * Enable cache for rotated LOGFONT.

## Version 3.2.0

MiniGUI 3.2.0 was released on July 12, 2018.

### What's new in this version

  * Support for 64-bit platform. Note that the definitions of some types
    and APIs changed.
  * Compliant to the latest GCC, and eliminate all compilation warnings.

### Type changes

#### Changes of handle types

All handle types, including `GHANDLE`, `HWND`, `HDC`, etc.,
are now defined as aliases of `PVOID` (`typedef void* PVOID`).
You may need to check your code to reflect this change.

#### Changes of integer types

The type of `DWORD` now has pointer precision. That is,
the size of `DWORD` will be 4 bytes on 32-bit platform, and 8 bytes on
64-bit platform.

Similarly, `WPARAM` and `LPARAM` now have pointer precision.

`WORD` and `SWORD` has half of pointer precision. The size of these
two types is 2 bytes on 32-bit platform, and 4 bytes on 64-bit platform.

`RGBCOLOR` now is defined as an alias of `DWORD32` (see below).

Note that the type of `BYTE` always has the size of 8-bit on both
32-bit and 64-bit platforms.

#### New integer types

We introduced `DWORD32` and `SDWORD32` types,
which have the size of 4 bytes on both 32-bit and 64-bit platforms.
You should use these types when reading/writing 32-bit integers from
a binary files for portability. Of course, you can also use
`Uint32` or `Sint32` types.

Similarly, we introduced `WORD16` and `SWORD16` types,
which have the size of 2 bytes on both 32-bit and 64-bit platforms.
You should use these types when reading/writing 16-bit integers from
a binary file for the portability. Of course, you can also use
`Uint16` or `SUint16` types.

`LRESULT` is defined for window callback procedure, and it has
pointer precision.

`LINT` is a new integer type with pointer precision.

### API changes

#### Integer macros

`MAKEWPARAM`: this new macro makes a WPARAM value using four bytes.
On the contrary, `FIRSTBYTE`, `SECONDBYTE`, `THIRDBYTE`, and `FOURTH`
macros get four bytes from a `WPARAM` or a `Uint32` value.

`MAKEWORD16`: this new macro makes a 16-bit word using two bytes.
Meanwhile, `MAKEWORD` makes a 16-bit word on 32-bit platform, and a 32-bit
word on 64-bit platform.

Note that `MAKELONG` macro always makes a `DWORD` integer, which has pointer
precision. Meanwhile, `MAKELONG32` macro makes a `Uint32` integer.

Note that `MakeRGB` and `MakeRGBA` macros always make `DWORD32` integers.
In contract, `GetRValue`, `GetRValue`, `GetBValue`, `GetAValue` always
get red, green, blue, and alpha components from a `DWORD32` integer
respectively.

Note that you should use `(-1)` instead of `0xFFFFFFFF` for the invalid
integer or pointer type value for good portability.

#### Structures and functions

The main changes in structures and functions are:

 * We now use a `UINT` instead of an `int` integer for the message identifier.

 * We now use a `DWORD` integer for the time tick count. Meanwhile, you can
    create 64 timers on 64-bit platform.

 * We now use a `LRESULT` integer for the return value of a window callback
    procedure. Now it is safe to return a pointer from the callback procedure
    on 64-bit platform. This is a very important change, and it will break the
    source compatibilty of your code. You should check the source code (use
    gcc option `-Wall`) carefully.

 * We now use a `LINT` integer for the identifier of a timer. So you can pass
    a pointer as the identifier of the timer on 64-bit platform. mGNCS uses
    MiniGUI timer in this manner.

 * We now use a `LINT` integer for the identifier of a control/widget and a
    menu item. So you can pass a pointer as the identifier of the timer on
    64-bit platform. mGNCS works in this manner.

##### Messages

The strcuture `MSG` and all message-related functions changed.
For example, the prototype of `SendMessage` changed from

    int SendMessage (HWND hWnd, int nMsg, WPARAM wParam, LPARAM lParam)

to

    LRESULT SendMessage (HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)

_IMPORTANT NOTE_

For best portability, you should use `FIRSTBYTE` to `FOURTHBYTE` macros
to get the bytes of a character when you extract the bytes from `WPARAM`
parameter of a `MSG_CHAR` message:

    MSG_CHAR
    unsigned char ch_buff [4];
    unsigned char ch_buff [0] = FIRSTBYTE(wParam);
    unsigned char ch_buff [1] = SECONDBYTE(wParam);
    unsigned char ch_buff [2] = THIRDBYTE(wParam);
    unsigned char ch_buff [3] = FOURTHBYTE(wParam);

##### Window callback procedure

Furthermore, the structures and functions to register window class,
create main window, and create dialog box have changed. For example, the prototype
of `WNDPROC` changed from

    typedef int (* WNDPROC)(HWND, int, WPARAM, LPARAM)

to

    typedef LRESULT (* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

Therefore, the prototype of `DefaultWindowProc` changed from

    int DefaultWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)

to

    LRESULT DefaultWindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

All main window procedures, control class procedures, and dialog box procedures
defined by your app should change the implementation to reflect the changes
above.

_IMPORTANT NOTE_

Do not cast the result returned by a window procedure to `int` on 64-bit
platform, unless you know what your are doing.

##### Notification callback procedure

The type of notification callback changes from:

    typedef void (* NOTIFPROC) (HWND hwnd, int id, int nc, DWORD add_data);

to

    typedef void (* NOTIFPROC) (HWND hwnd, LINT id, int nc, DWORD add_data);

_IMPORTANT NOTE_

If you use `MSG_COMMAND` message to handle the notification sent from children
controls, you should make sure the identifier is small enough on 64-bit
platform. Because MiniGUI packs the identifier and the notification code
in the `WPARAM` parameter:

    MSG_COMMAND
    int id = LOWORD(wParam);
    int code = HIWORD(wParam);
    HWND hwnd = (HWND)lParam;

The code above will not work on 64-bit if you use a pointer as the identifier
of the control.

Therefore, we strongly recommend that you use a `NOTIFYPOROC` callback to
handle the notification sent from controls. To do this, please call
`SetNotificationCallback` function to set the notification callback function.

##### Time and timer

The prototype of `GetTickCount` changed from

    unsigned int GetTickCount (void)

to

    DWORD GetTickCount (void);

And the prototye of `TIMERPROC` changed from

    typedef BOOL (* TIMERPROC)(HWND, int, DWORD)

to

    typedef BOOL (* TIMERPROC)(HWND, LINT, DWORD)

##### Miscellaneous

In addition, we corrected the bad or wrong definitions of some APIs:

  * `DWORD2PIXEL` to `DWORD2Pixel`. The old one had a bad name.
  * `GetWindowRendererFromName`: The return type changed from
    `const WINDOW_ELEMENT_RENDERER*` to `WINDOW_ELEMENT_RENDERER*`.
    So you can overload some methods directly of a renderer.
  * `GetDefaultWindowElementRenderer`: The return type changed from
    `const WINDOW_ELEMENT_RENDERER*` to `WINDOW_ELEMENT_RENDERER*`.
    So you can overload some methods directly of the default renderer.

### Configuration option changes

We added some new options for autoconf script (`configure`):

  * `--with-runmode`: Now you can use this option to specify the runtime
    mode of MiniGUI. The old enable options for runmode were removed.
    Note that MiniGUI-Processes now is the default runtime mode.

  * `--enable-develmode`: You should use this option to define `_DEBUG` macro,
    enable `-Wall -Werror` option, and enable all features of MiniGUI,
    if you were a MiniGUI developer.

