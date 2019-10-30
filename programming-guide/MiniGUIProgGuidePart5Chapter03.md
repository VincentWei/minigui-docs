# `GAL` and `IAL` Engines

In the development of MiniGUI version 0.3.xx, we introduce the concepts of
Graphics and Input Abstract Layer (GAL and `IAL`). Abstract layer is similar to
Linux kernel virtual file system. It defines a group of abstract interfaces
that do not rely on any special hardware. All top-layer graphics operations and
input handling are based on abstract interfaces. The code used to realize the
abstract interfaces are called graphic engine and input engine, similar to the
driver of operating system. Actually it is an object-oriented programming
technology. By using this abstract interface, we can easily port MiniGUI to
other operating systems. Generally speaking, Linux-based embedded system kernel
will provide `FrameBuffer` support, thus existed `FBCON` graphics engine of
MiniGUI can run on normal `PC`, and also can run on special embedded systems.
Therefore, we usually do not need to develop a graphics engines for special
embedded devices, but use `FBCON` graphics engine. At the same time, MiniGUI
also offers Shadow and `CommLCD` `GAL` engines for different situations. There
will be simple introduction in the first and second sections of this chapter.

Compared to graphics engine, it is more important to separate the bottom input
handling and top input handling of MiniGUI. In Linux-based embedded systems,
graphics engine can get from `FrameBuffer`, while input device does not have
the uniformed interface. We usually use keyboard and mouse on `PC`, but we may
only use touch screen and keypad on embedded systems. Considering this
situation, we have to say that it is very important for MiniGUI to provide an
abstract input layer.

Therefore, the following sections will introduce Custom `IAL` interface of
MiniGUI 3.0, and focus on how to develop an input engine (Custom `IAL`).

## Shadow `NEWGAL` Engine

The main functions of this engine are:
- Support for asynchronous update of graphics device, such as `YUV` output,
indirect access to `FrameBuffer`, etc.
- Support for display modes of lower than 8-bpp on `NEWGAL`. At present, it can
support all kinds of display modes of `QVFB` and all packed-pixel modes of
`FrameBuffer` console.

Shadow engine uses the conception of sub-driver. MiniGUI uses the name of
target board to determine which sub-driver to be included. Only one sub-driver
can be included at one time, which is determined by the configuration option
–-with-targetname.

Some child drivers are implemented in the Shadow engine now, for example:
- --with-targetname=vfanvil: The sub-driver for `VisualFone` Anvil board. This
sub-driver runs on ThreadX operation system.
- --with-targetname=qvfb: The sub-driver for all kinds of Linux `QVFB` display
modes.
- --with-targetname=wvfb: The sub-driver for all kinds of Windows `QVFB`
display modes.
- Without target (__TARGET_UNKNOWN__): The default sub-driver. This sub-driver
operates similarly to the Dummy `GAL` engine. You can modify this sub-driver to
implement operations on the underlayer graphics device.

When configure rotating screen, Shadow engine can be configured in
`MiniGUI.cfg` as follow:

```
[shadow]
real_engine=pc_xvfb
defaultmode=800x600-16bpp
rotate_screen=normal
```
- `real_engine` Real engine, it means the name of device which draws graphic.
Here is `pc_xvfb`
- defaultmode Default display mode
- `rotate_screen` Whether or not rotate the screen when virtual screen is draw
on real screen. If so, how to rotate. It has the following values:
- normal Don't rotate
- cw Rotate it 90 degrees clockwise
- ccw Rotate it 90 degrees counterclockwise
- hflip Flip horizontal
- vflip Flip vertical

When configure N (N is lower than 8) bits per pixel display mode, Shadow engine
can be configured in `MiniGUI.cfg` as follow:
```
[pc_xvfb]
defaultmode=800x600-1bpp

[shadow]
real_engine=pc_xvfb
defaultmode=800x600-8bpp
rotate_screen=normal
```
- shadow engine's color depth is greater than 8, so real engine's color depth
configuration (more than or equal to 8) is real color depth.

## `MLShadow` `GAL` Engine

`MLShadow` engine implements multi-display-layer in many product solutions,
such as set-top box and `PMP`. Multi-display-layer is similar with overlay
display layer which is provided by hardware, it can implement
transparence/translucent display between layers.

MiniGUI provides the operation functions on virtual graphic layer in `MLShadow`
engine to implement controls for different graphic layers.

```cpp
BOOL mlsSetSlaveScreenInfo (HDC dc_mls, DWORD mask, int offset_x, int offset_y,
DWORD blend_flags, gal_pixel color_key, int alpha, int z_order);
```
This function can get corresponding graphic layer, and set this graphic layer's
offset, blend flag, transparent color, alpha and overlay order relative to real
graphic layer by given `dc_mls` argument. The details of arguments are as
follow:
- `dc_mls` the corresponding `DC` handler of graphic layer
- mask To determine which properties should be set, ignore passed other
properties's value. For example, only set `offset_x` and `offset_y` when mask =
`MLS_INFOMASK_OFFSET`; set all properties when mask is `MLS_INFOMASK_ALL`. The
range of mask's value is:
- `MLS_INFOMASK_OFFSET` only set offset of display layer
- `MLS_INFOMASK_BLEND` only set blend flag of display layer
- `MLS_INFOMASK_ZORDER` only set overlay order of display layers
- `MLS_INFOMASK_ENABLE` only set whether display layer is visible
- `MLS_INFOMASK_ALL` set all properties
- `offset_x` and `offset_y` set offset of given display layer on main screen
- `blend_flag` To show the display layer is transparent or has alpha channel,
flags can be:
- `MLS_BLENDMODE_COLORKEY` Remove transparent color when blending.
- `MLS_BLENDMODE_ALPHA` Remove alpha blend when blending.
- `color_key` value of transparent color
- alpha value of alpha channel
- `z_order` overlay order, `z_order` is greater, display layer is wider.

```cpp
BOOL mlsGetSlaveScreenInfo (HDC dc_mls,  DWORD mask, int *offset_x, int *offset_y,
DWORD *blend_flags, gal_pixel *color_key, int *alpha, int *z_order);
```
This function gets overlay information of display layer which is given by
`dc_mls.` mask means to get all or partial information, its value has been
explained in argument description of `mlsSetSlaveScreenInfo`.
```cpp
BOOL mlsEnableSlaveScreen (HDC dc_mls, BOOL enable)；
```
This function set whether display layer which is give by `dc_mls` is visible.
In other words, it means whether or not participate overlay operation of
display layer. It is visible (invisible) when enable is `TRUE` (FALSE).

## `pc_xvfb` `GAL` Engine
This engine's main functions are:
- Using unified parameters startup options, so MiniGUI can start xvfb
automatically when it is initializing.
- Using unified shared memory ???, so `pc_xvfb` engine can use same key value
to get framebuffer's system shared memory instance without caring about using
Qt vfb, Window vfb or Gtk+ vfb.
- Using unified pipe/Unix socket object and input data transfer protocol, so
`pc_xvfb` input engine can use same mechanism to get the data which is entered
by user in the window without caring about using Qt vfb, Window vfb or Gtk+
vfb.

Configurations of `pc_xvfb` engine in `MiniGUI.cfg` are as follow:
```
[pc_xvfb]
defaultmode=800x600-16bpp
window_caption=XVFB-for-MiniGUI-3.0-(Qt-Version)
exec_file=/usr/local/bin/qvfb2
```
- defaultmode Default display mode
- `window_caption` The text of window caption
- `exec_file` Executable file of virtual framebuffer program. For qvfb, it is
qvfb2. wvfb2 is for wvfb. mvfb2 is for mvfb.

## `rtos_xvfb` `GAL` Engine
By using of `rtos_xvfb` engine, we can run MiniGUI on an exist GUI of RTOS,
such as `uC/GUI`, Gtk+ and Tilcon. The principle is as follows:
- `rtos_xvfb` program model creates window, allocates virtual frame buffer, and
starts MiniGUI application with thread mode, so that MiniGUI application can be
draw on virtual frame buffer.

`APIs` of Creating and destroying virtual frame buffer are as follow:
```cpp
XVFBHeader* xVFBAllocVirtualFrameBuffer (int width, int height, int depth,
        Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask, BOOL MSBLeft);

void xVFBFreeVirtualFrameBuffer (XVFBHeader *fb);
```
- Store input data which is generated by `rtos_xvfb` engine in ring buffer
refers to agreed standard. `rtos_xvfb` input engine of MiniGUI provides related
interfaces:
- The interfaces of creating and destroying ring buffer

```cpp
void* xVFBCreateEventBuffer (int nr_events);
void xVFBDestroyEventBuffer (void* buf);
```
- Put input event into ring buffer and notify `rtos_xvfb` engine to read
function interface.
```cpp
int xVFBNotifyNewEvent (const void* xvfb_event_buffer, XVFBEVENT* event);
```

The configuration of `rtos_xvfb` in `MiniGUI.cfg` is quite simple. Only need to
set default display mode as follow:
```
[rtos_xvfb]
defaultmode=800x600-16bpp
```

## `CommLCD` `NEWGAL` Engine
This engine provides the support for direct access to `LCD` `FrameBuffer`
(video memory) on conditional real-time operation systems like VxWorks,
Nucleus, uC/OS-II, and `eCos`. The `LCD`’s pixel format should be above 8-bpp
(bits-per-pixel), and in packed-pixel mode.

`CommLCD` engine also uses the conception of sub-driver. The sub-drivers
already implemented in `CommLCD` engine include:
- --with-targetname=vxi386/vxppc (`__TARGET_VXi386__` and `__TARGET_VXPPC__`): The
sub-driver for VxWorks i386/PowerPc target.
- --with-targetname=c33l05(`__TARGET_C33L05__`)：The sub-driver for `EPSON` C33L05
target.
- --with-targetname=mx21(`__TARGET_MX21__`)：The sub-driver for `OSE` mx21 target.
- Without target (`__TARGET_UNKNOWN__`): The default sub-driver. If it is `eCos`
operation system, MiniGUI will use the standard interfaces to implement the
sub-driver. Otherwise, you should define the sub-driver by yourself. For more
information, please see `src/newgal/commlcd/unknown.c`. There is a default
implementation for uC/OS-II in `rtos/ucos2_startup.c` and it is similar to dummy
graphics engine.

In every sub-drive of `CommLCD`, we need to implement the following interfaces
according to the operating system and lower-level API.

```cpp
int __commlcd_drv_init (void);
int __commlcd_drv_getinfo (struct commlcd_info *li);
int __commlcd_drv_release (void);
int __commlcd_drv_setclut (int firstcolor, int ncolors, GAL_Color *colors);
```
- `__commlcd_drv_init` function is used to initialize the `LCD` device.
- `__commlcd_drv_release` function is used to release the `LCD` device.
- `__commlcd_drv_getinfo` function is used to get information of the `LCD`
device.
- `__commlcd_drv_setclut` is used to set color palette.

The structure `commlcd_info` is defined as follows:
```cpp
struct commlcd_info {
    short height, width;  // Pixels
    short bpp;            // Depth (bits-per-pixel)
    short type;           // Pixel type
    short rlen;           // Length of one raster line in bytes
    void  *fb;            // Address of the frame buffer
};
```

Sub driver implementation sample is as follow:

```cpp
……
struct commlcd_info {
    short height, width;  // Pixels
    short bpp;            // Depth (bits-per-pixel)
    short type;           // Pixel type
    short rlen;           // Length of one raster line in bytes
    void  *fb;            // Address of the frame buffer
};

int __commlcd_drv_init (void)
{
    if (uglInitialize() == UGL_STATUS_ERROR)
        return 1;

    return 0;
}

int __commlcd_drv_getinfo (struct commlcd_info *li)
{
    UGL_MODE_INFO modeInfo;


    /* Obtain display device identifier */
    devId = (UGL_DEVICE_ID) uglRegistryFind (UGL_DISPLAY_TYPE,
                    0, 0, 0)->id;

    /* Create a graphics context */
    gc = uglGcCreate (devId);

……
    uglPcBiosInfo (devId, UGL_MODE_INFO_REQ, &modeInfo);
    li->type = COMMLCD_TRUE_RGB565;

    li->height = modeInfo.height;
    li->width = modeInfo.width;
    li->fb = modeInfo.fbAddress;
    li->bpp = modeInfo.colorDepth;
    li->rlen = (li->bpp*li->width + 7) / 8;
    return 0;
}

int __commlcd_drv_release (void)
{
    return 0;
}

int __commlcd_drv_setclut (int firstcolor, int ncolors, GAL_Color *colors)
{
    return 0;
}
……
```

## Comm Input Engine

MiniGUI provides comm `IAL` for conditional real-time operation systems like
VxWorks, Nucleus, uC/OS-II, and `eCos`. Based on this engine, you can easily
add the support for input device such as keyboard, mouse, and touch screen.

The comm ial engine needs the OS or low-level device driver to provide five
functions as follows:

```cpp
int __comminput_init (void);
void __comminput_deinit (void);
int __comminput_ts_getdata (short *x, short *y, short *button);
int __comminput_kb_getdata (short *key, short *status);
int __comminput_wait_for_input (void);
```

- `__comminput_init` is used to initialize the input device.
- `__comminput_deinit` is used to release the input device.
- `__comminput_ts_getdata` get the input data of the touch screen. The "x" and
"y" returns the position data, and "button" returns the pressed state (if pen
is pressed, return a non-zero value). It returns 0 while getting data
successfully, otherwise returns -1.
- `__comminput_kb_getdata` gets the input data of the keyboard. "key" returns the
key code of corresponding key; "status" returns the key status (1 for key-down,
0 for key-up). `__comminput_kb_getdata` returns 0 while getting data successfully,
otherwise returns -1. The key code here is the `MiniGUI-defined` scan code of a
keyboard key. The low-level keyboard driver needs to translate a keyboard scan
code to a corresponding MiniGUI key code and return this key code.
- `__comminput_wait_for_input` enquires whether there are input data. If no input
events comes, this function returns 0; if mouse events or touch screen events
comes, the return value's first position is set to 1; if keyboard events comes,
the return value's second position is set to 1.
The control of the external events in MiniGUI is implemented as a single system
thread. This event thread sleeps while no external events come. So,
`__comminput_wait_for_input` should provide a waiting mechanism, such as using
semaphore. `__comminput_wait_for_input` waits on an input semaphore while
enquiring about input data, and makes the MiniGUI input task which calls this
function go to sleep. When input events come, the low-level drivers (or
interrupt routines) should post a semaphore to wake up the MiniGUI event task.

When migrating MiniGUI to new hardware, we need to implement the above five
functions interface according to OS or hardware driver.

Custom input engine provides user message handle interfaces of customized
keyboard and mouse. User can handle message after implements the following
interfaces:

```cpp
BOOL InitCustomInput (INPUT* input, const char* mdev, const char* mtype);
void TermCustomInput (void);
```

When we need to customize input engine for specified embedded device, firstly,
set value for member of input engine structure in initializing function. These
members are function pointers, they are called by `MiniGUI`'s upper-level to
get input device's status and data. Definition of `INPUT` structure is as
follow:

```cpp
typedef struct tagINPUT
{
    char*   id;

    // Initialization and termination
    BOOL (*init_input) (struct tagINPUT *input, const char* mdev, const char* mtype);
    void (*term_input) (void);

    // Mouse operations
    int  (*update_mouse) (void);
    void (*get_mouse_xy) (int* x, int* y);
    void (*set_mouse_xy) (int x, int y);
    int  (*get_mouse_button) (void);
    void (*set_mouse_range) (int minx, int miny, int maxx, int maxy);
    void (*suspend_mouse) (void);
    int (*resume_mouse) (void);

    // Keyboard operations
    int  (*update_keyboard) (void);
    const char* (*get_keyboard_state) (void);
    void (*suspend_keyboard) (void);
    int (*resume_keyboard) (void);
    void (*set_leds) (unsigned int leds);

    // Event
    int (*wait_event) (int which, int maxfd, fd_set *in, fd_set *out,
            fd_set *except, struct timeval *timeout);

    char mdev [MAX_PATH + 1];
}INPUT;
```

These members' function are:
- `update_mouse` inform bottom-layer engine to update new mouse information
- `get_mouse_xy` calling this function by upper-layer to get x and y
coordinates of mouse
- `set_mouse_xy` calling function by upper-layer to set the new mouse position.
For those engines not supporting this function, the member can be null.
- `get_mouse_button` get mouse button state. Return value can be
`IAL_MOUSE_LEFTBUTTON`, `IAL_MOUSE_MIDDLEBUTTON`, `IAL_MOUSE_RIGHTBUTTON` to
respectively represent the pressed states: mouse left key, middle key, and
right key.
- `set_mouse_range` set range of mouse movement. For engines not supporting
this function, can be set as `NULL`.
- `update_keyboard` inform bottom-layer to update keyboard information
- `get_keyboard_state` get keyboard state, return a byte array, including
keyboard pressed state indexed by scan code. Pressed is 1, released is 0.
- `suspend_keyboard` pause keyboard device read/write, used for switch of
virtual console. Usually set as `NULL` for embedded device.
- `resume_keyboard` resume keyboard device read/write, used for switch of
virtual console. Usually set as `NULL` for embedded device.
- `set_leds` set keyboard status `LEDs`, used for `CapLock`, `NumLock`, and
`ScrollLock` statues.
- `wait_event` calling this function by upper-layer to wait for an event from
input devices. This function has different interfaces for MiniGUI-Threads and
MiniGUI-Processes, and must implement with select or poll system calls.

## Custom `IAL` engine sample

Actually developing a new `IAL` engine is not difficult. We use `iPAQ` as an
example to illustrate the design of a customized input engine.

`IPAQ` produced by `COMPAQ` is a `StrongARM-based` high-end hand-held product,
which includes touch screen and several control keys. The touch screen is
similar to the mouse of `PC`, but it can only differentiate left button. For
the control keys, we can emulate them as some keys in `PC` keyboard, such as
cursor keys, `ENTER` key, and function keys. The source code of this engine is
showed in List 1.


List 2 The customized input engine for `iPAQ` (custom `IAL`)
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <minigui/mgconfig.h>
#include <minigui/common.h>
#include <minigui/customial.h>
#ifdef _MGIAL_CUSTOM


/* for data reading from /dev/hs3600_ts */
typedef struct {
    unsigned short b;
    unsigned short x;
    unsigned short y;
    unsigned short pad;
} POS;

static unsigned char state [NR_KEYS];
static int ts = -1;
static int btn_fd = -1;
static unsigned char btn_state=0;
static int mousex = 0;
static int mousey = 0;
static POS pos;

#undef _DEBUG

/************************  Low Level Input Operations **********************/
/*
 * Mouse operations -- Event
 */
static int mouse_update(void)
{
    return 1;
}

static void mouse_getxy(int *x, int* y)
{
#ifdef _DEBUG
    printf ("mousex = %d, mousey = %d\n", mousex, mousey);
#endif

    if (mousex < 0) mousex = 0;
    if (mousey < 0) mousey = 0;
    if (mousex > 319) mousex = 319;
    if (mousey > 239) mousey = 239;

#ifdef _COOR_TRANS
#if _ROT_DIR_CCW
    *x = mousey;
    *y = 319 - mousex;
#else
    *x = 239 - mousey;
    *y = mousex;
#endif
#else
    *x = mousex;
    *y = mousey;
#endif
}

static int mouse_getbutton(void)
{
    return pos.b;
}

static int keyboard_update(void)
{
    char *statinfo;
    int status;
    int key;

    //Attention!
    statinfo = (btn_state & KEY_RELEASED)? "UP":"DOWN";
    status = (btn_state & KEY_RELEASED)? 0 : 1;
    key = btn_state & KEY_NUM;
#ifdef _DEBUG
    fprintf(stderr, "key %d is %s", key, statinfo);
#endif

    switch (key)
    {
    case 1:
        //state[H3600_SCANCODE_RECORD] = status;
        state[SCANCODE_LEFTSHIFT] = status;
    break;
    case 2:
        state[H3600_SCANCODE_CALENDAR] = status;
    break;
    case 3:
        state[H3600_SCANCODE_CONTACTS] = status;
    break;
    case 4:
        state[H3600_SCANCODE_Q] = status;
    break;
    case 5:
        state[H3600_SCANCODE_START] = status;
    break;
    case 6:
        state[H3600_SCANCODE_UP] = status;
    break;
    case 7:
        state[H3600_SCANCODE_RIGHT] = status;
    break;
    case 8:
        state[H3600_SCANCODE_LEFT] = status;
    break;
    case 9:
        state[H3600_SCANCODE_DOWN] = status;
    break;
    case 10:
        state[H3600_SCANCODE_ACTION] = status;
    break;
    case 11:
        state[H3600_SCANCODE_SUSPEND] = status;
    break;
    }

    return NR_KEYS;
}

static const char* keyboard_getstate(void)
{
    return (char *)state;
}

#ifdef _LITE_VERSION
static int wait_event (int which, int maxfd, fd_set *in, fd_set *out, fd_set *except,
                struct timeval *timeout)
#else
static int wait_event (int which, fd_set *in, fd_set *out, fd_set *except,
                struct timeval *timeout)
#endif
{
    fd_set rfds;
    int    retvalue = 0;
    int    e;

    if (!in) {
        in = &rfds;
        FD_ZERO (in);
    }

    if ((which & IAL_MOUSEEVENT) && ts >= 0) {
        FD_SET (ts, in);
#ifdef _LITE_VERSION
        if (ts > maxfd) maxfd = ts;
#endif
    }
    if ((which & IAL_KEYEVENT) && btn_fd >= 0){
        FD_SET (btn_fd, in);
#ifdef _LITE_VERSION
        if(btn_fd > maxfd) maxfd = btn_fd;
#endif
    }

#ifdef _LITE_VERSION
    e = select (maxfd + 1, in, out, except, timeout) ;
#else
    e = select (FD_SETSIZE, in, out, except, timeout) ;
#endif

    if (e > 0) {
        if (ts >= 0 && FD_ISSET (ts, in))
        {
            FD_CLR (ts, in);
            pos.x=0;
            pos.y=0;
            // FIXME: maybe failed due to the struct alignment.
            read (ts, &pos, sizeof (POS));
            //if (pos.x = -1 && pos.y = -1) {
        if (pos.b > 0) {
                mousex = pos.x;
                mousey = pos.y;
        }
            //}
#ifdef _DEBUG
        if (pos.b > 0) {
        printf ("mouse down: pos.x = %d, pos.y = %d\n", pos.x, pos.y);
        }
#endif
            pos.b = ( pos.b > 0 ? 4:0);
            retvalue |= IAL_MOUSEEVENT;
        }

        if (btn_fd >= 0 && FD_ISSET(btn_fd, in))
        {
            unsigned char key;
            FD_CLR(btn_fd, in);
            read(btn_fd, &key, sizeof(key));
            btn_state = key;
            retvalue |= IAL_KEYEVENT;
        }

    } else if (e < 0) {
        return -1;
    }

    return retvalue;
}

BOOL InitCustomInput (INPUT* input, const char* mdev, const char* mtype)
{
    ts = open ("/dev/h3600_ts", O_RDONLY);
    if (ts < 0) {
        fprintf (stderr, "IPAQ: Can not open touch screen!\n");
        return FALSE;
    }

    btn_fd = open ("/dev/h3600_key", O_RDONLY);
    if (btn_fd < 0 ) {
        fprintf (stderr, "IPAQ: Can not open button key!\n");
        return FALSE;
    }

    input->update_mouse = mouse_update;
    input->get_mouse_xy = mouse_getxy;
    input->set_mouse_xy = NULL;
    input->get_mouse_button = mouse_getbutton;
    input->set_mouse_range = NULL;

    input->update_keyboard = keyboard_update;
    input->get_keyboard_state = keyboard_getstate;
    input->set_leds = NULL;

    input->wait_event = wait_event;
    mousex = 0;
    mousey = 0;
    pos.x = pos.y = pos.b = 0;

    return TRUE;
}

void TermCustomInput (void)
{
    if (ts >= 0)
        close(ts);
    if (btn_fd >= 0)
    close(btn_fd);
}

#endif /* _MGIAL_CUSTOM */
```

We now analyze how some important interface functions implement:
- The function `IInitCustomInput` is the initializing function of input engine
defined in customial.h of MiniGUI 3.0. This function opens two devices:
/dev/h3600_ts and /dev/h3600_key. The former is the device file for touch
screen; the latter is the device for control keys. They are similar to device
/dev/psaux and device /dev/tty on `PCs`. After successfully opening these two
device files, the function sets `INPUT` structure and other members, some of
which is assigned with `NULL`.
- The function `mouse_update` returns 1, indicating that the mouse state is
ready.
- The function `mouse_getxy` returns mouse position data prepared by other
functions and performs proper boundary examination.
- The function `mouse_getbutton` returns touch screen state, that is, whether
the user have touched the screen. It is similar to whether the user has pressed
the left button of mouse.
- The function `keyboard_update` properly fills state array according to the
keyboard information prepared by other functions.
- The function `keyboard_state` directly returns the address of state array.
- The function `wait_event` is the core function of the input engine. This
function first combines the two opened device file descriptors within the
descriptor set in. Then it calls select system call. When the value returned by
select is more than 0, this function will examine if there is any readable data
waiting to read in the two file descriptors, if so, it will read touch screen
and key stroke data separately from the two file descriptors.

----

[&lt;&lt; Developing Customized MiniGUI-Processes Server Program](MiniGUIProgGuidePart5Chapter02.md) |
[Table of Contents](README.md) |
[Universal Startup API for RTOSes &gt;&gt;](MiniGUIProgGuidePart5Chapter04.md)

[Release Notes for MiniGUI 3.2]: /supplementary-docs/Release-Notes-for-MiniGUI-3.2.md
[Release Notes for MiniGUI 4.0]: /supplementary-docs/Release-Notes-for-MiniGUI-4.0.md
[Showing Text in Complex or Mixed Scripts]: /supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md
[Supporting and Using Extra Input Messages]: /supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md
[Using CommLCD NEWGAL Engine and Comm IAL Engine]: /supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md
[Using Enhanced Font Interfaces]: /supplementary-docs/Using-Enhanced-Font-Interfaces.md
[Using Images and Fonts on System without File System]: /supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md
[Using SyncUpdateDC to Reduce Screen Flicker]: /supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md
[Writing DRI Engine Driver for Your GPU]: /supplementary-docs/Writing-DRI-Engine-Driver-for-Your-GPU.md
[Writing MiniGUI Apps for 64-bit Platforms]: /supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building MiniGUI]: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]: /user-manual/MiniGUIUserManualCompiletimeConfiguration.md
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md

[MiniGUI Overview]: /MiniGUI-Overview.md
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI Supplementary Documents]: /supplementary-docs/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
