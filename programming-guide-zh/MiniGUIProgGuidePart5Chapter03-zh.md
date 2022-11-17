# 图形引擎及输入引擎

在 MiniGUI 0.3.xx 的开发过程中，我们引入了图形和输入抽象层（Graphics and Input Abstract Layer，`GAL` 和 `IAL`）的概念。抽象层的概念类似 Linux 内核虚拟文件系统的概念。它定义了一组不依赖于任何特殊硬件的抽象接口，所有顶层的图形操作和输入处理都建立在抽象接口之上。而用于实现这一抽象接口的底层代码称为“图形引擎”或“输入引擎”，类似操作系统中的驱动程序。这实际是一种面向对象的程序结构。利用这种抽象接口，我们可以将 MiniGUI 非常方便地移植到其他 POSIX 系统上，只需要根据我们的抽象层接口实现新的图形引擎和输入引擎即可。一般而言，基于 Linux 的嵌入式系统内核会提供 `FrameBuffer` 支持，这样 MiniGUI 已有的 `FBCON` 图形引擎可以运行在一般的 PC 上，也可以运行在特定的嵌入式系统上。因此，通常我们不需要开发针对特定嵌入式设备的图形引擎，而只要使用 `FBCON` 图形引擎即可。同时，MiniGUI 还提供了 `Shadow`、`CommLCD` 等应用于不同场合的图形引擎，本章的 1.1 和 1.2 小节将对其进行简要的介绍。

但相比图形来讲，将 MiniGUI 的底层输入与上层相隔显得更为重要。在基于 Linux 的嵌入式系统中，图形引擎可以通过 `FrameBuffer` 而获得，而输入设备的处理却没有统一的接口。在 PC 上，我们通常使用键盘和鼠标，而在嵌入式系统上，可能只有触摸屏和为数不多的几个键。在这种情况下，提供一个抽象的输入层，就显得格外重要。

因此，本章将介绍 MiniGUI 3.0 的 `Custom IAL` 接口，并重点介绍如何开发 `custom` 输入引擎。

## 1 `Shadow` 图形引擎

该引擎的主要功能是：

- 提供对异步更新图形设备的支持，比如无法直接访问 `FrameBuffer` 等的情况。
- 可用来在 `NEWGAL` 之上支持低于 8 位色的显示模式。目前提供了对 `QVFB` 各种显示模式的支持。

在配置旋转屏幕时，`Shadow` 引擎在 `MiniGUI.cfg` 文件中的配置方法如下：

```
[shadow]
real_engine=pc_xvfb
defaultmode=800x600-16bpp
rotate_screen=normal
```

- `real_engine` 表示真实的图形引擎，就是最终绘制图形的设备。这里使用的 `pc_xvfb`。
- `defaultmode` 表示默认模式
- `rotate_screen` 表示虚拟屏幕绘制真实屏幕上时，是否旋转，如果旋转的话，是如何旋转的。它有以下取值：
   - `normal` 不旋转
   - `cw` 顺时针旋转90度
   - `ccw` 逆时针旋转90度
   - `hflip` 水平翻转
   - `vflip` 垂直翻转

在配置低于 8 位色显示时，`Shadow` 引擎在 `MiniGUI.cfg` 文件中的配置方法如下:

```
[pc_xvfb]
defaultmode=800x600-1bpp

[shadow]
real_engine=pc_xvfb
defaultmode=800x600-8bpp
rotate_screen=normal
```

- `shadow` 引擎的色深配置在 8 位色以上，真实引擎的色深配置为真实的色深。

## 2 `MLShadow` 图形引擎

MLShadow 引擎是实现了在机顶盒、PMP 等产品的方案中提供多个显示层，以完成类似硬件提供的图形层叠加功能，自动实现层之间的透明、半透明的显示。该引擎的主要功能是：

- 可以实现多个虚拟图形层之间的透明或者半透明叠加
- 可以将 `Shadow` 引擎作为真实引擎，以实现对小于8位色的支持以及实现屏幕旋转的支持

MiniGUI 提供了对 `MLShadow` 引擎当中虚拟图形层的操作函数，以实现对不同图形层的控制：

```c
BOOL mlsSetSlaveScreenInfo (HDC dc_mls, DWORD mask, int offset_x, int offset_y, 
DWORD blend_flags, gal_pixel color_key, int alpha, int z_order);
```

此函数能够通过给定的 `dc_mls` 参数，找到对应的图形层，设置该图形层相对真实图形层的偏移量、混合标记、透明色、透明值以及叠加属性。下面是参数说明：

- `dc_mls` 是图形层所对应的 `DC` 句柄。
- `mask` 用于判断是设置某一个或者某些属性，其他属性的值传入无效。例如：当 `mask = MLS_INFOMASK_OFFSET` 时只对 `offset_x` 和 `offset_y` 进行设置，当为 `MLS_INFOMASK_ALL` 时，设置所有属性。`mask` 的取值范围如下：
   - `MLS_INFOMASK_OFFSET` 仅设置显示层偏移量
   - `MLS_INFOMASK_BLEND` 仅设置显示层混合标志
   - `MLS_INFOMASK_ZORDER` 仅设置显示层叠加顺序
   - `MLS_INFOMASK_ENABLE` 仅设置显示层是否可见
   - `MLS_INFOMASK_ALL ` 设置所有信息
- `offset_x` 和 `offset_y` 设置给定显示层在主屏上的偏移量。
- `blend_flags` 则表示该显示层是透明的还是带有 alpha 通道的，`flags` 可以取下列值：
   - `MLS_BLENDMODE_COLORKEY` 表示进行混合时，去掉透明色
   - `MLS_BLENDMODE_ALPHA` 表示进行混合时，是进行 ALPHA 混合
- `color_key` 指定透明色
- `alpha` 指定 ALPHA 通道值
- `z_order` 则指定叠加的顺序，`z_order` 值越大，则该显示层越靠外。 

```c
BOOL mlsGetSlaveScreenInfo (HDC dc_mls,  DWORD mask, int *offset_x, int *offset_y, 
DWORD *blend_flags, gal_pixel *color_key, int *alpha, int *z_order);
```
此函数获取由参数 `dc_mls` 指定的显示层的混合叠加信息，参数 `mask` 指定是获取所有信息还是部分信息，它的取值在函数 `mlsSetSlaveScreenInfo` 的参数说明里面已经说明过了。

```c
BOOL mlsEnableSlaveScreen (HDC dc_mls, BOOL enable)；
```
此函数设置显示层 `dc_mls` 是否可见，即是否参加图形层的混合叠加操作。`enable` 为 `TRUE` 时，为可见；为 `FALSE` 时，不可见。

## 3  `pc_xvfb` 图形引擎

该引擎的主要功能是：

- 使用统一的启动参数，使 MiniGUI 可以在初始化时自动启动该 `xvfb` 程序。
- 使用统一的共享内存对象键值；使得不论采用 Qt vfb 还是 Window vfb 还是 Gtk+ vfb 程序，都可以让 `pc_xvfb` 图形引擎使用同样的键值来获取帧缓冲区的系统共享内存对象。
- 使用统一的管道/Unix socket 对象及输入数据传输协议；使得不论采用 Qt vfb 还是 Window vfb 还是 Gtk+ vfb 程序，都可以让 `pc_xvfb` 输入引擎使用同样的机制获得用户在窗口中的输入数据。

`pc_xvfb` 引擎在 `MiniGUI.cfg` 文件的配置如下：

```
[pc_xvfb]
defaultmode=800x600-16bpp
window_caption=XVFB-for-MiniGUI-3.0-(Qt-Version)
exec_file=/usr/local/bin/qvfb2
```

- `defaultmode` 是引擎的默认显示模式
- `window_caption` 是标题栏文字
- `exec_file` 是虚拟帧缓冲区程序。`qvfb` 对应的程序是 `qvfb2`，`wvfb` 对应的程序是 `wvfb2`，`mvfb` 对应的程序是 `mvfb2`。

## 4  `rtos_xvfb` 图形引擎

借助 `rtos_xvfb` 引擎，可将 MiniGUI 运行在某个已有的 `RTOS` 图形系统之上，比如 uC/GUI、Gtk+、Tilcon 等。其原理如下：
- 由 `rtos_xvfb` 程序模块创建窗口，分配虚拟帧缓冲区，然后以线程方式启动 MiniGUI 程序，MiniGUI 程序在虚拟缓冲区中绘制。下面是创建和销毁虚拟帧缓冲区的接口：

```c
XVFBHeader* xVFBAllocVirtualFrameBuffer (int width, int height, int depth,
Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask, BOOL MSBLeft);

void xVFBFreeVirtualFrameBuffer (XVFBHeader *fb);
```
- 按约定的规范使用环形缓冲区存放 `rtos_xvfb` 引擎产生的输入数据，MiniGUI 的 `rtos_xvfb` 输入引擎提供相关接口：
   - 用于创建环形缓冲区的函数接口（基于 POSIX Threads 标准）以及释放函数。

```c
void* xVFBCreateEventBuffer (int nr_events);
void xVFBDestroyEventBuffer (void* buf);
```

-  - 用于向环形缓冲区放入输入事件，并通知 `rtos_xvfb` 引擎读取的函数接口。 

```c
int xVFBNotifyNewEvent (const void* xvfb_event_buffer, XVFBEVENT* event);
```

`rtos_xvfb` 在 `MiniGUI.cfg` 文件中的配置比较简单，只要确定一下默认显示模式就可以了，内容如下：

```
[rtos_xvfb]
defaultmode=800x600-16bpp
```

## 5 `CommLCD` 引擎

该引擎的主要功能是：

- 为各种操作系统上，提供可直接访问 LCD FrameBuffer（显示内存）设备的支持，需要像素位数为 8 及以上，采用线性模式（Packed Pixel）。
- 该引擎主要用来支持传统嵌入式操作系统如 vxworks, uc/OS2 等。

在 `CommLCD` 引擎的子驱动程序中均需客户按照自己的操作系统和底层函数实现如下几个接口： 

```c
int __commlcd_drv_init (void);
int __commlcd_drv_getinfo (struct commlcd_info *li);
int __commlcd_drv_release (void);
int __commlcd_drv_setclut (int firstcolor, int ncolors, GAL_Color *colors);
```
- `__commlcd_drv_init` 函数用于初始化 `LCD` 设备。
- `__commlcd_drv_release` 函数用于释放 `LCD` 设备。
- `__commlcd_drv_getinfo` 函数用于获取 `LCD` 设备的相关信息，如 `LCD` 分辨率，`bpp`，象素格式，一条扫描线所占字节数和 `framebuffer` 地址等。
- `__commlcd_drv_setclut` 用于设置调色板。

其中 `commlcd_info` 结构的定义如下：

```c
struct commlcd_info {
    short height, width;  // Pixels
    short bpp;            // Depth (bits-per-pixel)
    short type;           // Pixel type
    short rlen;           // Length of one raster line in bytes
    void  *fb;            // Address of the frame buffer
};
```

下面是一子驱动程序实现的参考示例：

```c
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

## 6 `Comm IAL` 引擎

MiniGUI 为传统嵌入式操作系统提供了 Common 输入引擎（comm），使用该引擎可以很方便地实现对键盘、鼠标或触摸屏等输入设备的支持。

该引擎提供了如下 5 个函数接口：

```c
int __comminput_init (void);
void __comminput_deinit (void);
int __comminput_ts_getdata (short *x, short *y, short *button);
int __comminput_kb_getdata (short *key, short *status);
int __comminput_wait_for_input (void);
```

- `__comminput_init` 函数用于初始化输入设备。
- `__comminput_deinit` 函数用于释放输入设备。
- `__comminput_ts_getdata` 函数用于返回当前鼠标或触摸屏信息，参数 x 和 y 是位置坐标，参数 `button` 为按下状态。该函数成功返回 0，失败返回 -1。
- `__comminput_kb_getdata` 函数用于返回键盘输入信息。参数 `key` 返回 MiniGUI 自定义的键盘扫描码，参数 `status` 返回接键状态（1 为按下，0 为抬起）。该函数成功返回 0，失败返回 -1。底层键盘驱动或该函数内部需要实现不同的输入设备键盘扫描码到 MiniGUI 键盘扫描码的转换功能。
- `__comminput_wait_for_input` 函数用于返回输入事件类型.该函数内部需要提供一种无事件发生则阻塞的机制（如使用信号量的方式），使得 MiniGUI 输入线程在无事件发生时处于 sleep 状态，事件来临时即被唤醒。当鼠标或触摸屏事件发生时，返回值为 1，当有键盘事件发生时，返回值为 2。 

在使用该引擎时，需要根据操作系统或底层驱动由客户自己为 MiniGUI 实现上述 5 个函数接口。 

## 7 `Custom IAL` 引擎

MiniGUI 3.0 专业版和标准版的输入和输出引擎都是飞漫软件定制实现的，当然如果客户需要自己定制IAL的话，我们也可以提供 `custom-ial` 的库由客户自定义 `ial` 引擎接口的实现。按照下面的方法编写好 `IAL` 源代码后，要将该源代码编译生成一个 `ial` 库，最后将实例、`minigui` 库和 `ial` 库一起编译，才可以生成正确的可执行文件。`custom` 输入引擎在 `customial.h` 中给用户提供了定制键盘和鼠标消息处理的接口。用户只要实现下面的接口，就可以实现对相关消息的处理了：

```c
BOOL InitCustomInput (INPUT* input, const char* mdev, const char* mtype);
void TermCustomInput (void);
```

当我们需要为特定的嵌入式设备编写输入引擎时，首先要在自己的初始化函数中，对输入引擎结构的成员进行赋值。这些成员基本上是函数指针，由 MiniGUI 的上层调用获得底层输入设备的状态和数据。`INPUT` 结构体定义如下：

```c
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

这些成员的功能如下：

- `update_mouse` 通知底层引擎更新鼠标信息
- `get_mouse_xy` 上层调用该函数可获得最新的鼠标 x,y 坐标值
- `set_mouse_xy` 上层调用该函数可以设置鼠标位置到新的坐标值。对不支持这一功能的引擎，该成员可为空
- `get_mouse_button` 获取鼠标按钮状态。返回值可以是 `IAL_MOUSE_LEFTBUTTON`、 `IAL_MOUSE_MIDDLEBUTTON`、`IAL_MOUSE_RIGHTBUTTON` 等值“或”的结果。 分别表示鼠标左键、中键、右键的按下状态
- `set_mouse_range` 设置鼠标的活动范围。对不支持这一功能的引擎，可设置该成员为空
- `update_keyboard` 通知底层引擎更新键盘信息
- `get_keyboard_state` 获取键盘状态，返回一个字符数组，其中包含以扫描码索引的键盘按键状态， 按下为 1，释放为 0
- `suspend_keyboard` 暂停键盘设备读取，用于虚拟控制台切换。对嵌入式设备来讲，通常可设置为空
- `resume_keyboard` 继续键盘设备读取，用于虚拟控制台切换。对嵌入式设备来讲，通常可设置为空
- `set_leds` 设置键盘的锁定 `LED`，用于设置大写锁定、数字小键盘锁定、滚动锁定等
- `wait_event` 上层调用该函数等待底层引擎上发生输入事件； 需要注意的是，该函数对 MiniGUI-Threads 和 MiniGUI-Processes 版本具有不同的接口，并且一定要利用 `select` 或者等价的 `poll` 系统调用实现这个函数

## 8 `Custom IAL` 引擎实例

其实开发一个新的 `IAL` 引擎并不困难。用户可通过 `customial.h` 定义的接口 来定制 `custom IAL` 输入引擎。下面以 `iPAQ` 为例，说明如何定制用户输入引擎（custom IAL）。

COMPAQ 公司生产的 `iPAQ` 是基于 `StrongARM` 的一款高端手持终端产品，它含有触摸屏以及几个控制键。触摸屏类似 PC 上的鼠标，但只能区分左键。对按键，我们可以将其模拟为 PC 键盘的某几个控制键，比如光标键、`ENTER` 键、功能键等等。该引擎的源代码见清单 1。

__清单 1__  以 `iPAQ` 为例的定制输入引擎（custom IAL）

```c
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
                        //if (pos.x != -1 && pos.y != -1) {
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

我们分析其中几个比较重要的接口函数实现：

- `IInitCustomInput` 函数就是我们在 MiniGUI 3.0 的 `customial.h` 中所定义的输入引擎的初始化函数。该函数打开了两个设备：`/dev/ h3600_ts` 和 `/dev/ h3600_key`。前者是触摸屏的设备文件，后者是按键的设备文件。类似 PC 上的 `/dev/psaux` 设备和 `/dev/tty` 设备。在成功打开这两个设备文件之后，该函数设置了 `INPUT` 结构的其它一些成员。注意，其中一些成员被赋值为 `NULL`。
- `mouse_update` 函数始终返回 1，表明更新鼠标状态成功。
- `mouse_getxy` 函数返回由其它函数准备好的鼠标位置数据，并做了适当的边界检查。
- `mouse_getbutton` 函数返回了触摸屏状态，即用户是否触摸了屏幕，相当于是否按下了左键。
- `keyboard_update` 函数根据其它函数准备好的键盘信息，适当填充了 `state` 数组。
- `keyboard_state` 函数直接返回了 `state` 数组的地址。
- `wait_event` 函数是输入引擎的核心函数。这个函数首先将先前打开的两个设备的文件描述符与传入的 `in` 文件描述符集合并在了一起，然后调用了 `select` 系统调用。当 `select` 系统调用返回大于 0 的值时，该函数检查在两个文件描述符上是否有可读的数据等待读取，如果是，则分别从两个文件描述符中读取触摸屏和按键数据。
