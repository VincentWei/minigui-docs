_How to define external stubs to implement your CommLCD engine and
Comm IAL engine outside MiniGUI Core._

Table of Contents

- [Introduction](#introduction)
- [Key Points](#key-points)
- [Functions to be Implemented](#functions-to-be-implemented)
  * [CommLCD NEWGAL engine](#commlcd-newgal-engine)
    + [Initializing the engine](#initializing-the-engine)
    + [Setting video mode](#setting-video-mode)
    + [Setting palette](#setting-palette)
    + [Update method](#update-method)
    + [Releasing the engine](#releasing-the-engine)
  * [Comm IAL engine](#comm-ial-engine)
    + [Initializing the engine](#initializing-the-engine)
    + [Waiting for an event](#waiting-for-an-event)
    + [Getting mouse/touch event](#getting-mousetouch-event)
    + [Getting keyboard event](#getting-keyboard-event)
    + [Terminating the engine](#terminating-the-engine)
- [Restrictions](#restrictions)
- [References](#references)

## Introduction

Since MiniGUI 3.2.2, you can use MiniGUI's built-in CommLCD NEWGAL engine
and Comm IAL engine to support your video output device and input device.
By using these two engines, you do not need to change the source code of
MiniGUI core. Instead, you implement the engines outside the MiniGUI core
by defining some external functions.

In this document, we describe the usage and the interfaces about these
two engines.

## Key Points

* Use MiniGUI 3.2.2 or later.
* Enable the engines when configuring MiniGUI:
   * `--enable-videocommlcd`: enable CommLCD NEWGAL engine.
   * `--enable-commial`: enable Comm IAL engine.
   * `--with-targetname=external`: define target name to be `external`.
* Implement the external stubs in your app side:
   * `#include <minigui/exstubs.h>`
* Specify the following runtime configuration options:
  * `gal_engine=commlcd`: use CommLCD NEWGAL engine.
  * `ial_engine=comm`: use comm IAL engine.
* Sample code: [`comm-engines` in `mg-tests`](https://github.com/VincentWei/mg-tests/tree/master/comm-engines)

## Functions to be Implemented

In MiniGUI header file `<minigui/exstubs.h>`, we declare the function
prototypes you need to implement for these two engines. You must
include this header in your C source file(s), and implement all
of the functions correctly.

In the `comm-engines` directory of `mg-tests` repository, the file `commlcd_ops.c`
implements the functions for CommLCD NEWGAL engine, and the file `comminput_ops.c`
implements the functions for Comm IAL engine:

* [`comm-engines_ops.c`](https://github.com/VincentWei/mg-tests/blob/master/comm-engines/comm-engines_ops.c)
* [`comminput_ops.c`](https://github.com/VincentWei/mg-tests/blob/master/comm-engines/comminput_ops.c)

The former implementation does not connect to any real device; it creates
an anonymous memory map and returns the address of the memory map as
the frame buffer to MiniGUI. However, when there is a update, this engine
will save the whole frame buffer content to a Windows bitmap file. So you
can observe the behaviors of the engine.

The latter implementation gives you a sample which gets input events
from a touch screen on Linux, and passed the events to MiniGUI. If you
have no such device, the engine will fails to initialize.

### CommLCD NEWGAL engine

#### Initializing the engine

`__commlcd_drv_init` will be called when initializing your
CommLCD engine implementation. In the `comm-engines` sample, it does nothing
and just returns zero:

```cpp
int __commlcd_drv_init (void)
{
    return 0;
}
```

Note that, all external methods for CommLCD engine should return zero for success.

#### Setting video mode

`__commlcd_drv_getinfo` will be called when MiniGUI tries to set the video
mode according to your settings in the MiniGUI runtime configuration, e.g.,
`defaultmode=240x320-32bpp`.

In our sample, it creates an anonymous memory map by calling `mmap` system
call and returns the video information via `struct commlcd_info* li`:

```cpp
int __commlcd_drv_getinfo (struct commlcd_info *li, int width, int height, int depth)
{
    sg_fb = (BYTE*) mmap (0, FB_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (sg_fb == MAP_FAILED) {
        perror ("Failed calling __commlcd_drv_getinfo: ");
        return -1;
    }

    li->type = COMMLCD_TRUE_ARGB8888;
    li->height = SCREEN_HEIGHT;
    li->width = SCREEN_WIDTH;
    li->bpp = COLOR_DEPTH;
    li->pitch = SCREEN_WIDTH * BYTES_PER_PIXEL;
    li->update_method = COMMLCD_UPDATE_ASYNC;
    li->fb = sg_fb;
    return 0;
}
```

You need to fill the all fields of `struct commlcd_info* li` with the correct
values:

* `type`: The video mode type. Currently, CommLCD supports the following modes:
  - `COMMLCD_PSEUDO_RGB332`: 256-color video mode.
  - `COMMLCD_TRUE_RGB555`: RGB555 15-bit video mode.
  - `COMMLCD_TRUE_RGB565`: RGB565 16-bit video mode.
  - `COMMLCD_TRUE_RGB888`: RGB888 24-bit video mode.
  - `COMMLCD_TRUE_RGB0888`: RGB0888 32-bit video mode (without alpha component).
  - `COMMLCD_TRUE_ARGB1555`: RGB1555 16-bit video mode (the alpha component use 1 bit only).
  - `COMMLCD_TRUE_ARGB8888`: RGB8888 32-bit video mode (the alpha, red, green, blue components all use 8 bits).
* `height`: The vertical resolution in pixels.
* `width`: The horizontal resolution in pixels.
* `bpp`: The color depth in bits per pixels. Actually, this field is a redundancy,
    because the type already contains the depth information.
* `pitch`: The length in bytes of one scan line. Generally, it should be a
    times of 4, i.e., the address of each scan line should be 4-byte aligned.
* `update_method`: The update method when there is a dirty rectangle, can be
    one of the following values:
    - `COMMLCD_UPDATE_NONE`: do not call `__commlcd_drv_update` (see below).
    - `COMMLCD_UPDATE_SYNC`: call `__commlcd_drv_update` synchronously.
    - `COMMLCD_UPDATE_ASYNC`: call `__commlcd_drv_update` asynchronously.
* `fb`: The address of the frame buffer.

#### Setting palette

If the color depth of the video mode is 8 (`COMMLCD_PSEUDO_RGB332`),
`__commlcd_drv_setclut` function will be called to set the palette.

In our sample, this method does nothing and returns zero:

```cpp
int __commlcd_drv_setclut (int firstcolor, int ncolors, GAL_Color *colors)
{
    return 0;
}
```

In practice, you should set the hardware palette (color look up table) in this
method if the color depth of your video device is only 256-color.

The arguments of this function have the following meanings:

* `firstcolor`: The first color index (the palette entry index) should be set.
* `ncolors`: The number of palette entries should be set.
* `colors`: The array of `GAL_Color` which define the RGB triples for each
    palette entries will be set.

`GAL_Color` is a structure defined in MiniGUI header:

```cpp
typedef struct _GAL_Color
{
    /**
     * The red component of a RGBA quarter.
     */
    gal_uint8 r;
    /**
     * The green component of a RGBA quarter.
     */
    gal_uint8 g;
    /**
     * The blue component of a RGBA quarter.
     */
    gal_uint8 b;
    /**
     * The alpha component of a RGBA quarter.
     */
    gal_uint8 a;
} GAL_Color;
```

#### Update method

If you specify the `update_method` to be `COMMLCD_UPDATE_SYNC` or
`COMMLCD_UPDATE_ASYNC`, the update method `__commlcd_drv_update` will
be called frequently or periodically.

In our sample, this method saves the whole frame buffer content to Windows
bitmap files by calling MiniGUI function:

```cpp
int __commlcd_drv_update (const RECT* rc_dirty)
{
    char filename [PATH_MAX + 1];
    struct timeval tv;

    MYBITMAP my_bmp = {
        flags: MYBMP_TYPE_RGB | MYBMP_FLOW_DOWN,
        frames: 1,
        depth: 32,
        w: SCREEN_WIDTH,
        h: SCREEN_HEIGHT,
        pitch: PITCH,
        size: FB_SIZE,
        bits: sg_fb
    };

    printf ("__commlcd_drv_update called (%d, %d, %d, %d)\n",
            rc_dirty->left, rc_dirty->top,
            rc_dirty->right, rc_dirty->bottom);

    gettimeofday (&tv, NULL);
    sprintf (filename, "screenshot-%d.%d.bmp", (int)tv.tv_sec, (int)tv.tv_usec);
    SaveMyBitmapToFile (&my_bmp, NULL, filename);
    return 0;
}
```

Note that, you can not call MiniGUI GDI functions here to draw something to
screen.

In practice, you may need to send an `ioctl` command to your video device driver
to update the content in our frame buffer to the real LCD controller.

For example, if you use SPI
to connect a LCD screen, you may create an off-screen frame buffer in memory,
and transfer the pixels to the LCD controller via SPI.

The argument `rc_dirty` contains the dirty rectangle, i.e., the rectangle need
to be updated to the real frame buffer or LCD controller.

Generally, you should set `update_mothod` to be `COMMLCD_UPDATE_ASYNC` in
`__commlcd_drv_init` method, and the method will be called asynchronously
in a different thread, about 20 times per second.

If you set `update_mothod` to be `COMMLCD_UPDATE_SYNC`, this update method
will be called synchronously when there is any update of the frame buffer.
For example, you call the MiniGUI function `SetPixel` to draw just one pixel
on the screen. Therefore, this will reduce the refresh performance of the
entire system. However, if you use MiniGUI's
[Synchronous Update Mechanism](https://github.com/VincentWei/minigui/wiki/Sync-Update),
it will be better to set `update_mothod` to be `COMMLCD_UPDATE_SYNC`.

If you can access the LCD frame buffer directly, and your LCD screen
do not need a refresh/update operation, you do not need to implement
the update method, and the function can just return zero:

```cpp
int __commlcd_drv_update (const RECT* rc_dirty)
{
    return 0;
}
```

If you specify the `update_mothod` to be `COMMLCD_UPDATE_NONE` in
`__commlcd_drv_init` method, this function will be never called.

#### Releasing the engine

When MiniGUI quits, it will call `__commlcd_drv_release` to release
the resource allocated or created by the engine.

In our sample, it destroys the anonymous memory map and returns zero:

```cpp
int __commlcd_drv_release (void)
{
    munmap (sg_fb, FB_SIZE);
    return 0;
}
```

### Comm IAL engine

#### Initializing the engine

When you specify MiniGUI runtime configuration option `system.ial_engine=comm`,
MiniGUI will call `__comminput_init` function to initialize the engine.

You can open your input devices in the function:

```cpp
#define POWER_EVENT_DEV "/dev/input/event0"
#define KB_EVENT_DEV "/dev/input/event1"
#define TP_EVENT_DEV "/dev/input/event5"

static int sg_power_event_fd;
static int sg_kb_event_fd;
static int sg_tp_event_fd;
static int sg_current_kb_event_fd;

int __comminput_init (void)
{
    sg_kb_event_fd = open (KB_EVENT_DEV, O_RDWR);
    if (sg_kb_event_fd < 0) {
        perror ("WARNING > __comminput_init: Failed when opening key-button event device file");
        return -1;
    }

    sg_tp_event_fd = open (TP_EVENT_DEV, O_RDWR /*| O_NONBLOCK */);
    if (sg_tp_event_fd < 0) {
        perror ("WARNING > __comminput_init: Failed when opening touch-panel event device file");
        close (sg_kb_event_fd);
        return -1;
    }

    sg_power_event_fd = open (POWER_EVENT_DEV, O_RDWR);
    if (sg_power_event_fd < 0) {
        perror ("WARNING > __comminput_init: Failed when opening power key-button event device file");
        return -1;
    }
    return 0;
}
```

In `comm-engines` sample, the engine opens three Linux input devices:

- `/dev/input/event0`: A power key.
- `/dev/input/event1`: Some buttons on the devices.
- `/dev/input/event5`: A touch panel.

The function returns zero for success.

Note that the real device file names may change according to your
implementation of the Linux device drivers.

The engine will translate the input events generated by the device into
MiniGUI input messages:

- The power key: The down and up message of the standard keyboard key with
  the scan code (key code) `SCANCODE_POWER`.
- The touch panel: The standard mouse messages such as mouse move,
  and left button down and up.
- Other buttons: Some standard keyboard keys with scan code
  `SCANCODE_ESCAPE` or others.

#### Waiting for an event

After MiniGUI starts up, your MiniGUI app will enter an event loop and call
`GetMessage` function continually. Eventually, MiniGUI calls
`__comminput_wait_for_input` function if you were using the Comm IAL engine.

As the name implies, `__comminput_wait_for_input` will give the engine a chance
to wait for a new event, but in a specified time interval. If there is no input
event in the time interval, the function should return 0 for timeout, and -1
for error.

Indeed, Comm IAL engine is a simplified implementation of a typical IAL engine.
When there is an event, you should return an integer with `COMM_KBINPUT`
and/or `COMM_MOUSEINPUT` set, in order to tell MiniGUI there is a mouse event
and/or a keyboard event. The sample implementation of `__comminput_wait_for_input`
uses the system call `select` to check the file descriptors opened by
`__comminput_init`, and return a suitable value to MiniGUI:

```cpp
int __comminput_wait_for_input (struct timeval *timeout)
{
    fd_set rfds;
    int retval;
    int event_flag = 0;

    FD_ZERO (&rfds);
    FD_SET (sg_kb_event_fd, &rfds);
    FD_SET (sg_tp_event_fd, &rfds);
    FD_SET (sg_power_event_fd, &rfds);

    retval = select (MAX(MAX (sg_kb_event_fd, sg_tp_event_fd), sg_power_event_fd) + 1, &rfds, NULL, NULL, timeout);

    if (retval > 0) {
        if (FD_ISSET (sg_kb_event_fd, &rfds)) {
            event_flag |= COMM_KBINPUT;
            sg_current_kb_event_fd = sg_kb_event_fd;
        }

        if (FD_ISSET (sg_tp_event_fd, &rfds)) {
            event_flag |= COMM_MOUSEINPUT;
        }

        if (FD_ISSET (sg_power_event_fd, &rfds)) {
            event_flag |= COMM_KBINPUT;
            sg_current_kb_event_fd = sg_power_event_fd;
        }
    }
    else if (retval < 0) {
        event_flag = -1;
    }

    return event_flag;
}
```

#### Getting mouse/touch event

If there is a keyboard event (the return value of `__comminput_wait_for_input`
has the bit `COMM_KBINPUT` set), MiniGUI will call `__comminput_kb_getdata`
immediately to get the real keyboard event data:

```cpp
int __comminput_kb_getdata (short *key, short *status)
{
    ...
}

```

The function returns zero for success, and the scan code of the key pressed
or released through the pointers of `key` and `status`.

For the detailed implementation, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/comm-engines/comminput_ops.c>

#### Getting keyboard event

If there is a mouse event (the return value of `__comminput_wait_for_input`
has the bit `COMM_MOUSEINPUT` set), MiniGUI will call `__comminput_ts_getdata`
immediately to get the real keyboard event data:

```cpp
int __comminput_ts_getdata (short *x, short *y, short *button)
{
    ...
}

```

The function returns zero for success, and the mouse position and button status
through the pointers of `x`, `y` and `status`.

For the detailed implementation, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/comm-engines/comminput_ops.c>

#### Terminating the engine

When MiniGUI quits, it will call `__comminput_deinit` to release
the resource allocated or created by the Comm IAL engine.

In our sample, it just closes the file descriptors:

```cpp
void __comminput_deinit (void)
{
    close (sg_tp_event_fd);
    close (sg_kb_event_fd);
    close (sg_power_event_fd);
}
```

## Restrictions

As we pointed out, these two engines are simplified implementations of
typical NEWGAL engine and IAL engine. Therefore, there are some restrictions
can not be implemented by these two engines:

- You can not implement the hardware-accelerated operations by using CommLCD engine.
- You can not implement the extra input events introduced by MiniGUI 4.0.

## References

* [GAL and IAL Engines](http://wiki.minigui.com/twiki/bin/view/Products/MiniGUIPGV32Part5Chapter03)

