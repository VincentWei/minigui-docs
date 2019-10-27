# Writing MiniGUI Apps for 64-bit Platforms

_Describe the things you need to be aware of when developing MiniGUI apps for 64-bit platforms._

Table of Contents

- [Overview](#overview)
- [Changes of Data Types](#changes-of-data-types)
  * [Changes of handle types](#changes-of-handle-types)
  * [Changes of integer types](#changes-of-integer-types)
  * [New integer types](#new-integer-types)
- [API changes](#api-changes)
  * [Integer macros](#integer-macros)
  * [Structures and functions](#structures-and-functions)
    + [Message](#message)
    + [Window callback procedure](#window-callback-procedure)
    + [Notification callback procedure](#notification-callback-procedure)
    + [Time and timer](#time-and-timer)
- [Write Portable Code](#write-portable-code)
  * [Use correct data types](#use-correct-data-types)
  * [Invalid pointer values](#invalid-pointer-values)

## Overview

In MiniGUI 3.2.0, we enhanced MiniGUI to support 64-bit platforms.

Although many embedded devices or IoT devices are still using 32-bit
processors, we often need to develope MiniGUI apps on a desktop computer
(almost all desktop computer are now using 64-bit CPUs), and then build
the code for the target system through cross compilation. Therefore,
the code of a MiniGUI App needs to be portable, regardless of whether
the target system is 32-bit or 64-bit, or even big-endian or little-endian.

This document focuses on some of the changes that MiniGUI introduced to
support 64-bit systems and what you need to be aware of when writing
portable code.

## Changes of Data Types

### Changes of handle types

All handle types, including `GHANDLE`, `HWND`, `HDC`, etc.,
are now defined as aliases of `PVOID` (`typedef void* PVOID`).
You may need to check your code to reflect this change.

### Changes of integer types

The type of `DWORD` now has pointer precision. That is,
the size of `DWORD` will be 4 bytes on 32-bit platform, and 8 bytes on
64-bit platform.

Similarly, `WPARAM` and `LPARAM` now have pointer precision.

`WORD` and `SWORD` have a half of pointer precision. The size of these
two types is 2 bytes on 32-bit platform, and 4 bytes on 64-bit platform.

`RGBCOLOR` now is defined as an alias of `DWORD32` (see below).

Note that the type of `BYTE` always has the size of 8-bit on both
32-bit and 64-bit platforms.

### New integer types

We introduced `DWORD32` and `SDWORD32` types,
which have the size of 4 bytes on both 32-bit and 64-bit platforms.
You should use these types when reading/writing 32-bit integers from
binary files for the portability. Of course, you can also use
`Uint32` or `Sint32` types.

Similarly, we introduced `WORD16` and `SWORD16` types,
which have the size of 2 bytes on both 32-bit and 64-bit platforms.
You should use these types when reading/writing 16-bit integers from
binary files for portability. Of course, you can also use
`Uint16` or `SUint16` types.

`LRESULT` is defined for window callback procedure, and it has
pointer precision.

`LINT` is a new integer type with pointer precision.

`QDWORD` is a new integer type for a quarter of DWORD. This type is
16-bit long on 64-bit architecture, and 8-bit long on 32-bit.

## API changes

### Integer macros

`MAKEWPARAM`: this new macro makes a WPARAM value using four bytes.
On the contrary, `FIRSTBYTE`, `SECONDBYTE`, `THIRDBYTE`, and `FOURTH`
macros get four bytes from a `WPARAM` or a `Uint32` value.

`MAKEWORD16`: this new macro makes a 16-bit word by using two bytes.
Meanwhile, `MAKEWORD` makes a 16-bit word on 32-bit platform, and a 32-bit
word on 64-bit platform.

Note that `MAKELONG` macro always makes a `DWORD` integer, which has pointer
precision. Meanwhile, `MAKELONG32` macro makes a `Uint32` integer.

Note that `MakeRGB` and `MakeRGBA` macros always make `DWORD32` integers.
In contract, `GetRValue`, `GetRValue`, `GetBValue`, `GetAValue` always
get red, green, blue, and alpha components from a `DWORD32` integer
respectively.

New macros for QDWORD:
 * `MAKEDWORD`: make a DWROD from four QDWORDs.
 * `FIRST_QDWORD`: get the first (LSB) QDWORD from a DWORD.
 * `SECOND_QDWORD`: get the second (LSB) QDWORD from a DWORD.
 * `THIRD_QDWORD`: get the third (LSB) QDWORD from a DWORD.
 * `FOURTH_QDWORD`: get the fourth (LSB) QDWORD from a DWORD.

### Structures and functions

The main changes in structure and functions:

 * We now use a `UINT` instead of an `int` integer for the message identifier.

 * We now use a `DWORD` integer for the time tick count. Meanwhile, you can
    create 64 timers on 64-bit platforms.

 * We now use a `LRESULT` integer for the return value of a window callback
    procedure. Now it is safe to return a pointer from the callback procedure
    on 64-bit platforms. This is a very important change, and it will break
    source compatibilty of your code. You should check the source code (use
    gcc option `-Wall`) carefully.

 * We now use a `LINT` integer for the identifier of a timer. So you can pass
    a pointer as the identifier of the timer on 64-bit platform. mGNCS uses
    MiniGUI timer in this manner.

 * We now use a `LINT` integer for the identifier of a control/widget and a
    menu item. So you can pass a pointer as the identifier of the timer on
    64-bit platform. mGNCS works in this manner.

#### Message

The strcuture `MSG` and all message-related functions have changed.
For example, the prototype of `SendMessage` changed from

```cpp
int SendMessage (HWND hWnd, int nMsg, WPARAM wParam, LPARAM lParam)
```

to

```cpp
LRESULT SendMessage (HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
```

_IMPORTANT NOTE_

For best portability, you should use `FIRSTBYTE` to `FOURTHBYTE` macros
to get the bytes of a character when you extract the bytes from `WPARAM`
parameter of a `MSG_CHAR` message:

```cpp
case MSG_CHAR:
unsigned char ch_buff [4];
unsigned char ch_buff [0] = FIRSTBYTE(wParam);
unsigned char ch_buff [1] = SECONDBYTE(wParam);
unsigned char ch_buff [2] = THIRDBYTE(wParam);
unsigned char ch_buff [3] = FOURTHBYTE(wParam);
```

#### Window callback procedure

Furthermore, the structure and functions to register window class,
create main window, and create dialog box have changed. For example, the prototype
of `WNDPROC` changed from

```cpp
typedef int (* WNDPROC)(HWND, int, WPARAM, LPARAM)
```

to

```cpp
typedef LRESULT (* WNDPROC)(HWND, UINT, WPARAM, LPARAM)
```

Therefore, the prototype of `DefaultWindowProc` changed from

```cpp
int DefaultWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
```

to

```cpp
LRESULT DefaultWindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
```

All main window procedures, control class procedures, and dialog box procedures
defined by your app should change the implementation to reflect the changes
above.

_IMPORTANT NOTE_

Do not cast the result returned by a window procedure to `int` on 64-bit
platform, unless you know what your are doing.

#### Notification callback procedure

The type of notification callback changed from:

```cpp
typedef void (* NOTIFPROC) (HWND hwnd, int id, int nc, DWORD add_data);
```

to

```cpp
typedef void (* NOTIFPROC) (HWND hwnd, LINT id, int nc, DWORD add_data);
```

_IMPORTANT NOTE_

If you use `MSG_COMMAND` message to handle the notification sent from children
controls, you should make sure the identifier is small enough on 64-bit
platforms. Because MiniGUI packs the identifier and the notification code
in the `WPARAM` parameter:

```cpp
MSG_COMMAND
int id = LOWORD(wParam);
int code = HIWORD(wParam);
HWND hwnd = (HWND)lParam;
```

The code above will not work on 64-bit if you use a pointer as the identifier
of the control.

Therefore, we recommend strongly that you use a `NOTIFYPOROC` callback to
handle the notification sent from controls. To do this, please call
`SetNotificationCallback` function to set the notification callback function.

#### Time and timer

The prototype of `GetTickCount` changed from

```cpp
unsigned int GetTickCount (void)
```

to

```cpp
DWORD GetTickCount (void);
```

And the prototye of `TIMERPROC` changed from

```cpp
typedef BOOL (* TIMERPROC)(HWND, int, DWORD)
```

to

```cpp
typedef BOOL (* TIMERPROC)(HWND, LINT, DWORD)
```

## Write Portable Code

In this section, we give some tips to write portable code.

### Use correct data types

When we read/write data from/to a file, we must use the data types suffixed
by 16, 32, or 64. For example, the following code writes a Windows BMP
file header to a file:

```cpp
    MGUI_RWwrite (fp, &bmfh.bfType, sizeof (WORD16), 1);
    MGUI_RWwrite (fp, &bmfh.bfSize, sizeof (DWORD32), 1);
    MGUI_RWwrite (fp, &bmfh.bfReserved1, sizeof (WORD16), 1);
    MGUI_RWwrite (fp, &bmfh.bfReserved2, sizeof (WORD16), 1);
    MGUI_RWwrite (fp, &bmfh.bfOffBits, sizeof (DWORD32), 1);
```

### Invalid pointer values

We often use `NULL` for an invalid pointer type value. However, we may
also use `0xFFFFFFFF` for this purpose. This works on 32-bit architecture,
but not on 64-bit.

Instead, we sugguest to use `(-1)` instead of `0xFFFFFFFF` for the invalid
integer or pointer type value for good portability:

```cpp
#define HDC_INVALID         ((HDC)-1)
```

