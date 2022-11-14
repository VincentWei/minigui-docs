# 图标、光标和插入符

## 1.1 图标

图标是一张小的图片，通常用来代表一个应用程序，或者用于警告消息框等窗口中。它是由一个位图和一个位屏蔽位图组合而成，可以在图片中产生透明图像区域。一个图标文件中可以包含一个以上的图标映像，应用程序可以根据各个图标映像的大小和颜色位数来选择其中之一来使用。

MiniGUI 中提供了对单色和 16 色和 256 色 Windows 图标的载入、显示、创建和销毁的支持。

### 1.1.1 图标的装载和显示

应用程序可以使用 `LoadIconFromFile` 函数来装载图标文件，函数的原型如下：

```
HICON GUIAPI LoadIconFromFile (HDC hdc, const char* filename, int which);
```

各参数含义如下：

- `hdc` 设备上下文句柄
- `filename` 图标文件名
- `which` 所选择图标的索引值

`LoadIconFromFile` 函数从一个 Windows 图标文件（*.ico）中载入图标，图标可以是单色、16 色或 256 色的。某些 Windows 图标文件包含两个不同大小的图标，你可以通过给定不同的 `which` 值来告诉 `LoadIconFromFile` 函数载入哪一个图标，0 是第一个，1 是第二个。`LoadIconFromFile` 函数从图标文件中读入图标的大小、颜色位数和位图映像数据等信息，并调用 `CreateIcon` 函数创建一个图标对象，然后返回一个代表该图标对象的图标句柄。
也可以通过 `LoadIconFromMem` 函数从内存中装载图标，函数原型如下：

```c
HICON GUIAPI LoadIconFromMem (HDC hdc, const void* area, int which);
```
`area` 所指的内存区域应该和 Windows ICO 文件具有相同的布局。

应用程序在装载完图标对象之后，就可以调用 `DrawIcon` 函数在指定的位置绘制图标。`DrawIcon` 函数在一个矩形内绘制一个图标对象，该图标对象可以是由 `LoadIconFromFile` 函数或 `CreateIcon` 函数创建的。`DrawIcon` 函数原型如下：

```c
void GUIAPI DrawIcon (HDC hdc, int x, int y, int w, int h, HICON hicon);
```

各参数含义如下：

- hdc 设备上下文句柄
- x, y 图标所在矩形的左上角坐标
- w, h 矩形的宽和高
- hicon 图标对象的句柄

__清单 1.1__ 中的程序 drawicon.c 说明了如何由图标文件装载图标，然后在窗口的客户区内绘制图标。该程序的完整源代码见本指南示例程序包 `mg-samples` 中的 drawicon.c 程序。

__清单 1.1__ 绘制图标

```c
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

static int DrawiconWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        static HICON myicon_small, myicon_large;
        HDC hdc;
        
        switch (message) {
                case MSG_CREATE:
                /* 调用 LoadIconFromFile 函数从 myicon.ico 文件中装载大小两个图标 */
                myicon_small = LoadIconFromFile(HDC_SCREEN, "myicon.ico", 0);
                if (myicon_small == 0)
                fprintf (stderr, "Load icon file failure!");
                myicon_large = LoadIconFromFile(HDC_SCREEN, "myicon.ico", 1);
                if (myicon_large == 0)
                fprintf (stderr, "Load icon file failure!");
                break;
                
                case MSG_PAINT:
                /* 在窗口不同位置显示两个图标 */
                hdc = BeginPaint(hWnd);
                if (myicon_small != 0)
                DrawIcon(hdc, 10, 10, 0, 0, myicon_small);
                if (myicon_large != 0)
                DrawIcon(hdc, 60, 60, 0, 0, myicon_large);
                EndPaint(hWnd, hdc);
                return 0;
                
                case MSG_CLOSE:
                /* 销毁图标及主窗口本身 */
                DestroyIcon(myicon_small);
                DestroyIcon(myicon_large);
                DestroyMainWindow (hWnd);
                PostQuitMessage (hWnd);
                return 0;
        }
        
        return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* 以下创建窗口的代码从略 */
```
程序的输出如__图 1.1__ 所示。

__图 1.1__ 图标的绘制

上述程序从图标文件 myicon.ico 中载入两个尺寸分别为 32x32 像素和 16x16 像素的 16 色图标。序号为 0 的图标为 32x32 像素的大图标，存放在图标对象 `myicon_large` 中；序号为 1 的图标为 16x16 像素的小图标，存放在图标对象 `myicon_small`中。程序在处理 `MSG_PAINT` 消息时使用 `DrawIcon` 函数把这两个图标绘制到窗口的客户区之上。我们注意到程序调用 `DrawIcon` 函数时传给它的w和h参数均为 0，这种情况下 `DrawIcon` 函数将按图标的原始大小绘制图标，没有缩放。

### 1.1.2 图标的销毁

应用程序不再需要某个在运行时创建的图标时就应该销毁它。上述程序在即将退出时（收到 `MSG_CLOSE` 消息）调用 `DestroyIcon` 函数销毁了先前使用 `LoadIconFromFile` 函数所载入的两个图标。`DestroyIcon` 函数销毁图标句柄，并释放它所占用的内存。该函数的定义如下：

```c
BOOL GUIAPI DestroyIcon(HICON hicon);
```

`DestroyIcon` 函数只有一个参数 `hicon`，指定所要销毁的图标对象。由 `LoadIconFromFile` 函数载入的图标要用 `DestroyIcon` 来销毁。下面我们还将看到，应用程序使用 `CreateIcon` 函数动态创建的图标也由 `DestroyIcon` 来销毁。

### 1.1.3 图标的创建

除了从图标文件中载入图标之外，应用程序还可以使用 `CreateIcon` 函数在运行时动态创建图标。由该函数创建的图标同样需要用 `DestroyIcon` 函数来销毁。`CreateIcon` 函数的原型如下：

```c
MG_EXPORT HICON GUIAPI CreateIconEx (HDC hdc, int w, int h,
const BYTE* AndBits, const BYTE* XorBits, int colornum,
const RGB* pal);


#define CreateIcon(hdc, w, h, AndBits, XorBits, colornum) \
CreateIconEx(hdc, w, h, AndBits, XorBits, colornum, NULL)
```

各参数的含义如下：

```c
hdc      设备上下文句柄
w, h      图标的宽和高
pAndBits  AND位屏蔽图标位图映像指针
pXorBits  XOR位屏蔽图标位图映像指针
colornum  XOR位屏蔽图标位图映像的颜色位数
pal         图标调色板
```

`CreateIcon` 按照指定的图标尺寸、颜色和内存中的位屏蔽位图映像等数据创建图标。w 和 h 参数所指定的图标宽度和高度必须是系统支持的尺寸，如 16x16 像素或 32x32 像素。`pAndBits` 指向一个字节数组，该数组包含图标的AND位屏蔽位图的映像数据，AND 位屏蔽位图是一个单色位图。`pXorBits` 指向一个包含图标的 XOR 位屏蔽位图映像数据的字节数组，XOR 位屏蔽位图可以是单色位图，也可以是彩色位图。MiniGUI目前支持单色、16 色和 256 色的三种图标。`colornum` 指定图标的颜色位数，或者说 XOR 位屏蔽位图（彩色位图）的颜色位数。对于单色图标，它应该为 1，对于 16 色图标，它应该为 4，对于 256 色图标，它应该是 8。

__清单 1.2__ 中的代码描述了如何使用 `CreateIcon` 函数在运行时创建自定义图标。该程序的完整源代码见本指南示例程序包 `mg-samples` 中的 createicon.c 程序。

__清单 1.2__ 创建图标

```c
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

/* 定义图标的 AND 掩码数据和 XOR 掩码数据 */
static BYTE ANDmaskIcon[] = {
        0xff, 0x9f, 0x00, 0x00, 
        0xff, 0x1f, 0x00, 0x00, 
        0xfc, 0x1f, 0x00, 0x00, 
        0xf0, 0x1f, 0x00, 0x00, 
        0xe0, 0x0f, 0x00, 0x00, 
        0xc0, 0x07, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 
        0xc0, 0x07, 0x00, 0x00, 
        0xf0, 0x1f, 0x00, 0x00
};

static BYTE XORmaskIcon[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x8f, 0xff, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x8f, 0xff, 0xff, 0x00, 0x00, 0x00, 
        0x00, 0x08, 0xff, 0xf8, 0xff, 0xf8, 0x00, 0x00, 
        0x00, 0xff, 0xff, 0x80, 0x8f, 0xff, 0xf0, 0x00, 
        0x00, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 
        0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x00, 
        0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0x00, 
        0x0f, 0xff, 0xff, 0xf8, 0x00, 0xff, 0xff, 0x00, 
        0x0f, 0xff, 0xf0, 0x0f, 0x00, 0xff, 0xff, 0x00, 
        0x00, 0xff, 0xf8, 0x00, 0x08, 0xff, 0xf0, 0x00, 
        0x00, 0x8f, 0xff, 0x80, 0x8f, 0xff, 0xf0, 0x00, 
        0x00, 0x00, 0x8f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xff, 0x9f, 0x00, 0x00, 0xff, 0x1f, 0x00, 0x00, 
        0xfc, 0x1f, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 
        0xe0, 0x0f, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
        0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
        0x80, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 
        0xc0, 0x07, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 
        0x26, 0x00, 0x00, 0x00, 0xf4, 0xd9, 0x04, 0x08, 
        0xa8, 0xf8, 0xff, 0xbf, 0xc0, 0xf7, 0xff, 0xbf, 
        0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
        0xc0, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x00, 0x00, 
        0x28, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
        0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
        0xf0, 0x10, 0x04, 0x00, 0x70, 0xe1, 0x04, 0x08, 
        0xd8, 0xf8, 0xff, 0xbf, 0x41, 0x90, 0x04, 0x08
};

static int CreateiconWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        static HICON new_icon;
        HDC hdc;
        
        switch (message) {
                case MSG_CREATE:
                /* 用自定义数据创建图标 */
                new_icon = CreateIcon(HDC_SCREEN, 16, 16, ANDmaskIcon, XORmaskIcon, 4);
                break;
                
                case MSG_PAINT:
                hdc = BeginPaint(hWnd);
                if (new_icon != 0) {
                        /* 用实际大小显示图标 */
                        DrawIcon(hdc, 0, 0, 0, 0, new_icon);
                        /* 放大显示图标 */
                        DrawIcon(hdc, 50, 50, 64, 64, new_icon);
                }
                EndPaint(hWnd, hdc);
                return 0;
                
                case MSG_CLOSE:
                /* 销毁图标和主窗口 */
                DestroyIcon(new_icon);
                DestroyMainWindow (hWnd);
                PostQuitMessage (hWnd);
                return 0;
        }
        
        return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* 以下创建主窗口的代码从略 */
```

程序的输出如__图 1.2__ 所示。

__图 1.2__ 图标的创建

__清单 1.2__ 中的程序根据 `ANDmaskIcon` 和 `XORmaskIcon` 位屏蔽字节数组中的数据，调用 `CreateIcon` 函数在运行时创建了一个自定义图标 new_icon，图标的大小为 16x16 像素，颜色位数为 4。程序然后使用 `DrawIcon` 函数把所创建的“问号”图标分别以原始尺寸和放大的尺寸绘制在窗口的客户区内。最后，在 `MSG_CLOSE` 消息中，程序调用 `DestroyIcon` 函数把由 `CreateIcon` 函数所创建的自定义图标销毁掉。

### 1.1.4 使用系统图标

MiniGUI 的配置文件 MiniGUI.cfg 中的各个渲染器部分定义了系统所使用和提供的所有图标，下面是 Classic 渲染器所使用的图标：

```c
[classic]
# Note that max number defined in source code is 5.
iconnumber=5
icon0=form.ico
icon1=failed.ico
icon2=help.ico
icon3=warning.ico
icon4=excalmatory.ico
```

>【注意】系统所使用图标的最大数目为 5，这是在 MiniGUI 的源代码中定义的。所以，如果你要修改配置文件中的 iconnumber 项的话，它的值只能小于或等于 5，大于 5 以后的图标将被忽略掉。

MiniGUI 的配置文件 MiniGUI.cfg 文件中定义了四个渲染器：classic、flat、fashion、skin（fashion 渲染器必须配合 `mgplus` 组建才能正常使用）。每个渲染器里面都定义了对应渲染风格下系统所使用的图标。 MiniGUI 在渲染器初始化时根据配置文件中渲染器里面系统图标的设置，把所有的系统图标从图标文件中载入内存。应用程序可以通过 `GetLargeSystemIcon` 函数和 `GetSmallSystemIcon` 函数来获取内存中的系统图标来使用。这两个函数的定义如下：

```c
HICON GUIAPI GetLargeSystemIcon (int id);
HICON GUIAPI GetSmallSystemIcon (int id);
```

`GetLargeSystemIcon` 用来获取一个 32x32 像素的系统大图标，`GetSmallSystemIcon` 获取一个 16x16 像素的系统小图标。这两个函数返回内存中系统图标对象的句柄。所得图标是可能的 5 个系统图标中的一个，由 `id` 指定。`id` 是一个整数值，可以是以下值中的一个：

```c
#define IDI_APPLICATION         0
#define IDI_HAND                1
#define IDI_STOP                IDI_HAND
#define IDI_QUESTION            2
#define IDI_EXCLAMATION         3
#define IDI_ASTERISK            4
#define IDI_INFORMATION         IDI_ASTERISK
```

可见，它们分别代表 MiniGUI.cfg 中序号从 0 到 4 的 5 个图标文件。

由 `GetLargeSystemIcon` 和 `GetSmallSystemIcon` 函数获取的图标为系统预定义的图标，属于系统共享资源，不需要由应用程序来销毁。

此外，应用程序还可以使用 `LoadSystemIcon` 函数直接从 MiniGUI.cfg 配置文件中定义的图标文件中载入所需的系统图标。该函数定义如下：

```c
HICON GUIAPI LoadSystemIcon (const char* szItemName, int which);
```

`szItemName` 参数指明所需载入的图标在 MiniGUI.cfg 的 `iconinfo` 部分定义的图标文件符号名，如 `icon0`，代表 `form.ico` 图标文件。`which` 参数指定载入图标文件中的第几个图标。该函数返回所获取图标对象的句柄。

`LoadSystemIcon` 实际上是通过调用 `LoadIconFromFile` 来载入图标的。显然，由它所创建的图标在不再需要的时候也必须使用 `DestroyIcon` 函数来销毁。

## 1.2 光标

光标是一个小的位图，它在屏幕上的位置由鼠标等定点设备控制，用来指示定点的位置。当用户移动鼠标时，光标在屏幕上作相应的移动。如果光标移动到了窗口的不同区域或不同的窗口内时，系统很可能会改变光标的外形。光标内一个称为热点的像素标志光标的准确屏幕位置，系统用这个点来跟踪和识别光标的位置。例如，箭头光标的热点一般是它的箭头位置。光标的热点通常就是光标的焦点。如果有一个鼠标输入事件发生，系统将把包含热点坐标的鼠标消息发送给光标热点所在的窗口或捕获到鼠标的窗口。

MiniGUI 中提供了对单色和 16 色光标的装载、创建、显示、销毁和移动等操作的函数。MiniGUI 目前不支持 256 色光标和动画光标。

### 1.2.1 光标的载入和创建

应用程序可以使用 `LoadCursorFromFile` 函数从一个 Windows 光标文件中载入光标。该函数的原型如下：

```c
HCURSOR GUIAPI LoadCursorFromFile (const char* filename);
```

`LoadCursorFromFile` 函数从光标文件中读入光标的大小、热点位置、颜色位数和位图映像数据等信息，创建一个光标对象，返回代表该光标对象的光标句柄。

`LoadCursorFromMem` 函数从内存中读入光标。

```c
HCURSOR GUIAPI LoadCursorFromMem (const void* area);
```

该函数从指定的内存区域中载入一个光标，`area` 所指的光标内存区域和 Windows 光标文件的布局应该是一样的。

应用程序也可以在运行时调用 `CreateCursor` 函数动态创建光标。`CreateCursor` 函数的定义如下：

```c
HCURSOR GUIAPI CreateCursor (int xhotspot, int yhotspot, int w, int h,const BYTE* pANDBits, const BYTE* pXORBits, int colornum);
```

各参数含义如下：

```c
xhotspot, yhotspot    光标热点的水平和垂直坐标
w, h                    光标的宽和高
pAndBits               AND位屏蔽光标位图映像指针
pXorBits               XOR位屏蔽光标位图映像指针
colornum               XOR位屏蔽光标位图映像的颜色位数
```

和 `CreateIcon` 函数创建图标的方式类似，`CreateCursor` 函数按照指定的光标尺寸、颜色和内存中的位屏蔽位图映像等数据创建光标，不同的是使用 `CreateCursor` 函数还必须指定所创建光标的热点位置。`xhotspot` 和 `yhotspot` 参数分别指定所创建光标的热点在光标图片中的水平坐标和垂直坐标。w 和 h 参数所指定的光标宽度和高度必须是系统支持的尺寸，而 MiniGUI 中只能使用 32x32 像素的光标。因此，w和h参数的值只能为 32。`pAndBits` 指向一个包含光标的 AND 位屏蔽位图映像数据的字节数组， AND 位屏蔽位图是一个单色位图。`pXorBits` 指向一个包含光标的 XOR 位屏蔽位图映像数据的字节数组，XOR 位屏蔽位图可以是单色位图，也可以是彩色位图。MiniGUI 目前支持单色的和 16 色的两种光标。`colornum` 指定光标的颜色位数，或者说 XOR 位屏蔽位图（彩色位图）的颜色位数。对于单色光标，它应该为 1，对于 16 色光标，它应该为 4。

### 1.2.2 光标的销毁

应用程序不再需要某个在运行时创建的光标时就应该销毁它。`DestroyCursor`函数可以用来销毁由 `LoadCursorFromFile` 函数和 `CreateCursor` 函数创建的光标，并释放光标对象所占用的内存。该函数的定义如下：

```c
BOOL GUIAPI DestroyCursor (HCURSOR hcsr);
```

`DestroyCursor` 函数的参数 `hcursor` 指定所要销毁的光标对象。

### 1.2.3 光标的定位和显示

如果系统包含鼠标，系统将自动地显示光标，并根据鼠标移动指定的位置更新它在屏幕上的位置，重新绘制光标。应用程序可以通过调用 `GetCursorPos` 函数来获取光标的当前屏幕位置，通过调用 `SetCursorPos` 函数来把光标移动到屏幕上的指定位置。

```c
void GUIAPI GetCursorPos (POINT* ppt);
void GUIAPI SetCursorPos (int x, int y);
```

应用程序可以调用 `GetCurrentCursor` 获取当前光标句柄，调用 `SetCursorEx` 设置当前光标。这两个函数的定义如下：

```c
HCURSOR GUIAPI GetCurrentCursor (void);
HCURSOR GUIAPI SetCursorEx (HCURSOR hcsr, BOOL set_def);
```

`SetCursorEx` 函数把由hcsr指定的光标设置为当前光标。如果 `set_def` 为 `TRUE`，`SetCursorEx` 还将把该光标设置为缺省光标，缺省光标为移动到桌面之上时显示的光标。该函数返回老的当前光标句柄。`SetCursorEx` 还有两个简化版本：`SetCursor` 和 `SetDefaultCursor`。`SetCursor` 设置当前光标，不改变缺省光标；`SetDefaultCursor` 把给定光标设置为当前光标和缺省光标。

```c
#define SetCursor(hcsr) SetCursorEx (hcsr, FALSE);#define SetDefaultCursor(hcsr) SetCursorEx (hcsr, TRUE);
```

当用户移动鼠标时，MiniGUI 将把 `MSG_SETCURSOR` 消息发送给光标下面的窗口，光标应用程序可以在处理 `MSG_SETCURSOR` 消息时改变当前的光标。如果窗口过程函数在处理该消息时改变了光标，应该立即返回。

系统自动显示与光标所在窗口相关的类光标。应用程序可以在注册窗口类时给该窗口类赋一个类光标。在登记这个窗口类之后，该窗口类的每个窗口都具有相同的类光标，也就是说，当鼠标移动到这些窗口之上时，系统所显示的光标都是相同的指定光标。应用程序可以通过 `GetWindowCursor` 来获取给定窗口的当前光标，通过 `SetWindowCursor` 来设置新的窗口光标。

```c
#define SetCursor(hcsr) SetCursorEx (hcsr, FALSE);
#define SetDefaultCursor(hcsr) SetCursorEx (hcsr, TRUE);
```

下面的代码来自 MiniGUI 源代码中的 listview.c，它说明了如何通过给 `WNDCLASS` 结构的 `hCursor` 成员赋予一个光标句柄来指定该窗口类的类光标。

```c
WNDCLASS WndClass;

WndClass.spClassName = CTRL_LISTVIEW;
WndClass.dwStyle = WS_NONE;
WndClass.dwExStyle = WS_EX_NONE;
WndClass.hCursor = GetSystemCursor (0);
WndClass.iBkColor = PIXEL_lightwhite;
WndClass.WinProc = sListViewProc;

return RegisterWindowClass (&WndClass);
```

上述代码中类光标是由 `GetSystemCursor` 函数获得的系统缺省光标，即箭头光标。`GetSystemCursor (0) `和 `GetSystemCursor (IDC_ARROW)` 是一样的。

应用程序可以调用S `howCursor` 函数来显示或隐藏光标。

```c
int GUIAPI ShowCursor (BOOL fShow);
```

参数 `fshow` 为 `FALSE` 时 `ShowCursor` 函数隐藏光标，为`TRUE` 时显示光标。`ShowCursor` 并不改变当前光标的外形。该函数在内部使用一个光标显示计数器来决定是否隐藏或显示光标。每次调用 `ShowCursor` 函数试图显示光标都使该计数器加 1 而试图隐藏光标则使计数器减 1。只有当这个计数器大于或等于 0 时光标才是可见的。

### 1.2.4 光标限定

应用程序使用 `ClipCursor` 函数把光标限定在屏幕的某个矩形区域内，这常用于响应某一特定的限制矩形区域内的事件。函数定义如下：

```c
void GUIAPI ClipCursor (const RECT* prc);
```

`prc` 指向给定的限定矩形。如果 `prc` 为 `NULL`，`ClipCursor` 函数将取消光标限制。`ClipCursor` 函数在把光标限定在屏幕的某个矩形区域内的同时，将把光标移动到该矩形区域的中心点处。

`GetClipCursor` 函数获取当前的光标限定矩形，该函数可以用来在设置新的限定矩形之前保存原始限定矩形，需要时把它用于恢复原始区域。函数的定义如下：

```c
void GUIAPI GetClipCursor (RECT* prc);
```

### 1.2.5 使用系统光标

MiniGUI 的配置文件 MiniGUI.cfg 中的 `cursorinfo` 部分定义了系统所使用和提供的所有光标，如下：

```c
[cursorinfo]
# Edit following line to specify cursor files path
cursorpath=/usr/local/lib/minigui/res/cursor/
cursornumber=23
cursor0=d_arrow.cur
cursor1=d_beam.cur
cursor2=d_pencil.cur
cursor3=d_cross.cur
cursor4=d_move.cur
cursor5=d_sizenesw.cur
cursor6=d_sizens.cur
cursor7=d_sizenwse.cur
cursor8=d_sizewe.cur
cursor9=d_uparrow.cur
cursor10=d_none.cur
cursor11=d_help.cur
cursor12=d_busy.cur
cursor13=d_wait.cur
cursor14=g_rarrow.cur
cursor15=g_col.cur
cursor16=g_row.cur
cursor17=g_drag.cur
cursor18=g_nodrop.cur
cursor19=h_point.cur
cursor20=h_select.cur
cursor21=ho_split.cur
cursor22=ve_split.cur
```

MiniGUI 源代码中定义的系统所使用光标的最大数目为 `MAX_SYSCURSORINDEX + 1`。`MAX_SYSCURSORINDEX` 为最大的系统光标索引值，定义为 22，因此系统预定义的光标最大数目为 23。

MiniGUI 在系统初始化时根据 MiniGUI.cfg 配置文件中 `cursorinfo` 部分的设置，把所有的系统光标从所指定的光标文件中载入内存。应用程序可以通过 `GetSystemCursor` 函数来获取内存中的系统光标。此函数定义如下：

```c
HCURSOR GUIAPI GetSystemCursor (int csrid);
```

`GetSystemCursor` 函数返回内存中系统光标对象的句柄。所得光标是可能的 23 个系统预定义光标中的一个，由标识符 `csrid` 指定。`csrid` 是一个整数值，可以是以下值中的一个：

```c
IDC_ARROW             系统缺省的箭头光标
IDC_IBEAM             ‘I’ 形光标，指示输入区域
IDC_PENCIL            笔形光标
IDC_CROSS             十字光标
IDC_MOVE              移动光标
IDC_SIZENWSE          西北－东南方向的调整大小光标
IDC_SIZENESW          东北－西南方向的调整大小光标
IDC_SIZEWE            东西方向的调整大小光标
IDC_SIZENS            南北方向的调整大小光标
IDC_UPARROW           向上箭头光标
IDC_NONE              空光标
IDC_HELP              带问号光标
IDC_BUSY              忙光标
IDC_WAIT              等待光标
IDC_RARROW            右箭头光标
IDC_COLOMN            列光标
IDC_ROW               行光标
IDC_DRAG              拖动光标，用于拖放操作
IDC_NODROP            不可放下光标，用于拖放操作
IDC_HAND_POINT        手形指点光标
IDC_HAND_SELECT       手形选择光标
IDC_SPLIT_HORZ        水平分割光标
IDC_SPLIT_VERT        垂直分割光标
```

这些光标索引值在 minigui.h 中的定义如下：

```c
/* System cursor index. */
#define IDC_ARROW       0
#define IDC_IBEAM       1
#define IDC_PENCIL      2
#define IDC_CROSS       3
#define IDC_MOVE        4
#define IDC_SIZENWSE    5
#define IDC_SIZENESW    6
#define IDC_SIZEWE      7
#define IDC_SIZENS      8
#define IDC_UPARROW     9
#define IDC_NONE        10
#define IDC_HELP        11
#define IDC_BUSY        12
#define IDC_WAIT        13
#define IDC_RARROW      14
#define IDC_COLOMN      15
#define IDC_ROW         16
#define IDC_DRAG        17
#define IDC_NODROP      18
#define IDC_HAND_POINT  19
#define IDC_HAND_SELECT 20
#define IDC_SPLIT_HORZ  21
#define IDC_SPLIT_VERT  22
```

它们分别代表 MiniGUI.cfg 中序号从 0 到 22 的 23 个系统预定义光标。

由 `GetSystemCursor` 函数获取的光标为系统预定义的光标，属于系统共享资源，不需要由应用程序来销毁。

### 1.2.6 示例程序

__清单 1.3__ 中的代码说明了 MiniGUI 中光标的使用。该程序的完整源代码见本指南示例程序包 `mg-samples` 中的 cursordemo.c 程序。

__清单 1.3__ 鼠标光标的使用

```c
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDC_TRAP    100

static HWND hTrapWin, hMainWnd;
static RECT rcMain, rc;

/* “trap”控件类的窗口过程 */
static int TrapwindowProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        static BOOL bTrapped = FALSE;
        
        switch (message) {
                case MSG_MOUSEMOVE:
                /* 当鼠标进入该控件范围时，进一步限制在控件范围内 */
                if (!bTrapped) {
                        GetWindowRect(hWnd, &rc);
                        ClientToScreen(hMainWnd, &rc.left, &rc.top);
                        ClientToScreen(hMainWnd, &rc.right, &rc.bottom);
                        ClipCursor(&rc);
                        bTrapped = TRUE;
                }
                break;
                
                case MSG_DESTROY:
                return 0;
        }
        
        return DefaultControlProc(hWnd, message, wParam, lParam);
}

/* 注册“trap”控件类 */
BOOL RegisterTrapwindow (void)
{
        WNDCLASS WndClass;
        
        WndClass.spClassName = "trap";
        WndClass.dwStyle     = 0;
        WndClass.dwExStyle   = 0;
        WndClass.hCursor     = GetSystemCursor(IDC_HAND_POINT);
        WndClass.iBkColor    = PIXEL_black;
        WndClass.WinProc     = TrapwindowProc;
        
        return RegisterWindowClass (&WndClass);
}

static int CursordemoWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        switch (message) {
                case MSG_CREATE:
                /* 注册“trap”控件类 */
                RegisterTrapwindow();
                /* 创建“trap”控件类的一个实例 */
                hTrapWin = CreateWindow("trap", "", WS_VISIBLE | WS_CHILD, IDC_TRAP, 
                10, 10, 100, 100, hWnd, 0);
                break;
                
                case MSG_LBUTTONDOWN:
                /* 在鼠标左键按下时将鼠标活动范围剪切在主窗口范围内 */
                GetWindowRect(hWnd, &rcMain);
                ClipCursor(&rcMain);
                /* 并隐藏鼠标光标 */
                ShowCursor(FALSE);
                break;
                
                case MSG_RBUTTONDOWN:
                /* 右键按下时显示鼠标光标 */
                ShowCursor(TRUE);
                break;
                
                case MSG_SETCURSOR:
                /* 设置鼠标形状为“I”形 */
                SetCursor (GetSystemCursor (IDC_IBEAM));
                return 0;
                
                case MSG_CLOSE:
                /* 销毁控件及主窗口本身 */
                DestroyAllControls (hWnd);
                DestroyMainWindow (hWnd);
                PostQuitMessage (hWnd);
                return 0;
        }
        
        return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* 以下创建主窗口的代码从略 */
```

图 1.3 光标的使用

上面的示例程序的运行主界面如__图 1.3__ 所示。主窗口过程调用 `RegisterTrapwindow` 函数注册一个窗口类 “trap”，然后在窗口的左上角（10, 10）处创建了一个大小为 100x100 的 “trap” 类型的子窗口。`RegisterTrapwindow` 函数在注册 “trap” 窗口类时，把窗口的背景色设置为黑色，窗口类光标设置为手形指点光标（IDC_HAND_POINT）。`trap` 窗口类的窗口过程函数在处理 `MSG_MOUSEMOVE` 消息时，调用 `ClipCursor` 函数把光标限定在本窗口之内。

主窗口过程在处理 `MSG_LBUTTONDOWN` 消息时首先调用 `GetWindowRect` 函数取得主窗口矩形，使用 `ClipCursor` 函数把光标限定在主窗口范围之内，然后调用 `ShowCursor` 函数把光标隐藏掉。在处理 `MSG_RBUTTONDOWN` 消息时，调用 `ShowCursor` 函数把光标显示出来。主窗口过程在处理 `MSG_SETCURSOR` 消息时调用 `SetCursor` 函数把当前光标（箭头光标）重新设置为“I”形光标。

程序运行时，当用户在主窗口内点击鼠标左键时，光标的移动范围将被限制在主窗口之内，而且被隐藏掉。用户可以通过点击设备右键来重新显示光标。当光标被移动到 `trap` 窗口上时，光标将被“抓住”在这个黑色的窗口范围之内。

## 1.3 插入符

插入符是指窗口客户区之内一个闪烁的符号，通常用于指示键盘输入的位置。常见的插入符外形为下划线、垂直线和方块等。

MiniGUI 为应用程序提供了插入符的创建、销毁、显示、隐藏、定位和改变插入符闪烁时间等函数。

### 1.3.1 插入符的创建和销毁

`CreateCaret` 函数创建一个插入符，并把它赋给指定的窗口。

```c
BOOL GUIAPI CreateCaret (HWND hWnd, PBITMAP pBitmap, int nWidth, int nHeight);
```

各参数含义如下：

```c
hWnd       拥有插入符的窗口
pBitmap    插入符位图
nWidth     插入符的宽
nHeight    插入符的高
```

如果 `pBitmap` 不为 `NULL`，则根据该位图句柄来创建插入符；如果 `pBitmap` 为 `NULL`，则用插入点处宽度和高度分别为 `nWidth和nHeight` 的矩形反显像素点的颜色形成插入符。插入符矩形的宽度和高度 `nWidth` 和 `nHeight` 是以像素值为单位的。

插入符在刚创建完之后是隐藏的。如果想使插入符可见，那么在调用 `CreateCaret` 函数创建插入符之后，还必须调用 `ShowCaret` 函数使之显示在屏幕上。

`DestroyCaret` 函数销毁由 `CreateCaret` 所创建的插入符，它的定义如下：

```c
BOOL GUIAPI DestroyCaret (HWND hWnd);
```

`DestroyCaret` 函数销毁一个窗口的插入符，并把它从屏幕上删除。 如果程序中需要插入符，我们可以在 `MSG_CREATE` 消息中调用 `CreateCaret` 函数创建它，然后在收到 `MSG_DESTROY` 消息时调用 `DestroyCaret` 函数销毁。

### 1.3.2 显示和隐藏插入符

在某一个时刻只能有一个窗口拥有键盘输入焦点。通常接收键盘输入的窗口在接收到输入焦点时显示插入符，在失去输入焦点时隐藏插入符。
系统给收到输入焦点的窗口发送 `MSG_SETFOCUS` 消息，应用程序应该在收到该消息时调用 `ShowCaret` 函数显示插入符。窗口失去键盘输入键盘时，系统给这个窗口发送一个 `MSG_KILLFOCUS` 消息，应用程序在处理这个消息时要调用 `HideCaret` 函数把插入符隐藏掉。这两个函数的定义如下：

```c
BOOL GUIAPI ShowCaret (HWND hWnd);
BOOL GUIAPI HideCaret (HWND hWnd);
```

`ShowCaret` 函数使给定窗口的插入符可见，插入符出现后将自动地开始闪烁。`HideCaret` 函数从屏幕上删除插入符。如果应用程序在处理 `MSG_PAINT` 以外的消息时必须重新绘制屏幕，同时又要保留插入符，那么可以在绘制前使用 `HideCaret` 函数先隐藏插入符，在绘制结束后再使用 `ShowCaret` 函数重新显示插入符。如果应用程序处理的是 `MSG_PAINT` 消息，就不需要去隐藏和重新显示插入符，因为 `BeginPaint` 和 `EndPaint` 函数会自动地完成这些操作。

### 1.3.3 插入符的定位

应用程序使用 `GetCaretPos` 函数来获取插入符的所在位置，使用 `SetCaretPos` 函数在一个窗口之内移动插入符。

```c
BOOL GUIAPI GetCaretPos (HWND hWnd, PPOINT pPt);
BOOL GUIAPI SetCaretPos (HWND hWnd, int x, int y);
```
`GetCaretPos` 函数把窗口的插入符在客户区内的位置复制到由 `pPt` 指定的 `POINT` 结构变量中。`SetCaretPos` 函数把窗口的插入符移动到由 x 和 y 指定的客户区内位置，该函数不管插入符是否可见都移动它。

### 1.3.4 调整插入符的闪烁时间

反向显示插入符所消耗的时间称为反转时间。闪烁时间是指显示、反向显示、再恢复所消耗的时间。应用程序使用 `GetCaretBlinkTime` 函数来获取插入符的反转时间，该时间以毫秒计数。系统缺省的插入符反转时间为 500 毫秒。如果要定义插入符的反转时间，可以使用 `SetCaretBlinkTime`。插入符反转时间最小不能小于 100 毫秒。这两个函数的定义如下:

```c
UINT GUIAPI GetCaretBlinkTime (HWND hWnd);
BOOL GUIAPI SetCaretBlinkTime (HWND hWnd, UINT uTime);
```

### 1.3.5 示例——简单编辑框窗口

__清单 1.4__ 中的程序使用本节所讨论的插入符函数创建了一个简单的文本输入窗口，你可以把它看作是一个简单的编辑框控件。在“myedit”控件中，你可以输入 10 个以内的字符，用左右箭头键（插入符移动键）来移动插入符，用退格键删除窗口中的字符。该程序的完整源代码见本指南示例程序包 `mg-samples` 中的 caretdemo.c 程序。

__清单 1.4__ 插入符的使用

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDC_MYEDIT    100

/* 简单编辑框控件类的窗口过程 */
static int MyeditWindowProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        /* 用静态变量保存控件的信息。
        * 在实际控件中，不应该使用静态变量保存这些信息，
        * 因为一个控件类可能同时存在多个控件实例 
        */
        static char *pBuffer = NULL;
        static int pos = 0, len = 0;
        HDC hdc;
        
        switch (message) {
                case MSG_CREATE:
                /* 设置控件字体为系统默认字体 */
                SetWindowFont(hWnd, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
                /* 创建插入符 */
                if (!CreateCaret (hWnd, NULL, 1, GetSysCharHeight())) {
                        return -1;
                }
                /* 分配编辑缓冲区 */
                pBuffer = (char *) malloc(10);
                *pBuffer = 0;
                break;
                
                case MSG_SETFOCUS:
                /* 在获得输入焦点时设置插入符位置 */
                SetCaretPos(hWnd, pos*GetSysCharWidth(), 0);
                /* 显示插入符 */
                ShowCaret(hWnd);
                break;
                
                case MSG_KILLFOCUS:
                /* 失去输入焦点时隐藏插入符 */
                HideCaret(hWnd);
                break;
                
                case MSG_CHAR:
                switch (wParam) {
                        case '\t':
                        case '\b':
                        case '\n':
                        {
                                /* 输入这些字符时改变插入符的翻转时间间隔 */
                                SetCaretBlinkTime(hWnd, GetCaretBlinkTime(hWnd)-100);
                        }
                        break;
                        
                        default:
                        {
                                /* 在缓冲区中插入字符 */
                                char ch, buf[10];
                                char *tmp;
                                ch = wParam;
                                if (len == 10)
                                break;
                                tmp = pBuffer+pos;
                                if (*tmp != 0) {
                                        strcpy(buf, tmp);
                                        strcpy (tmp+1, buf);
                                }
                                *tmp = ch;
                                pos++;
                                len++;
                                break;
                        }
                        break;
                }
                break;
                
                case MSG_KEYDOWN:
                switch (wParam) {
                        case SCANCODE_CURSORBLOCKLEFT:
                        /* 向左移动插入符 */
                        pos = MAX(pos-1, 0);
                        break;
                        case SCANCODE_CURSORBLOCKRIGHT:
                        /* 向右移动插入符 */
                        pos = MIN(pos+1, len);
                        break;
                        case SCANCODE_BACKSPACE:
                        {
                                /* 删除插入符所在位置的字符 */
                                char buf[10];
                                char *tmp;
                                if (len == 0 || pos == 0)
                                break;
                                tmp = pBuffer+pos;
                                strcpy(buf, tmp);
                                strcpy(tmp-1, buf);
                                pos--;
                                len--;
                        }
                        break;
                }
                /* 更新插入符位置，并重绘 */
                SetCaretPos(hWnd, pos*GetSysCharWidth(), 0);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
                
                case MSG_PAINT:
                hdc = BeginPaint(hWnd);
                /* 输出文本 */
                TextOut(hdc, 0, 0, pBuffer);
                EndPaint(hWnd, hdc);
                return 0;
                
                case MSG_DESTROY:
                /* 销毁插入符并释放缓冲区 */
                DestroyCaret (hWnd);
                if (pBuffer)
                free(pBuffer);
                return 0;
        }
        
        return DefaultControlProc(hWnd, message, wParam, lParam);
}

/* 注册简单编辑框控件 */
BOOL RegisterMyedit(void)
{
        WNDCLASS WndClass;
        
        WndClass.spClassName = "myedit";
        WndClass.dwStyle     = 0;
        WndClass.dwExStyle     = 0;
        WndClass.hCursor     = GetSystemCursor(IDC_IBEAM);
        WndClass.iBkColor    = PIXEL_lightwhite;
        WndClass.WinProc     = MyeditWindowProc;
        
        return RegisterWindowClass (&WndClass);
}

/* main windoww proc */
static int CaretdemoWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        HWND hMyedit;
        
        switch (message) {
                case MSG_CREATE:
                /* 注册简单编辑框控件类并创建实例 */
                RegisterMyedit();
                hMyedit = CreateWindow("myedit", "", WS_VISIBLE | WS_CHILD, IDC_MYEDIT, 
                30, 50, 100, 20, hWnd, 0);
                SetFocus(hMyedit);
                break;
                
                case MSG_CLOSE:
                /* 销毁控件及主窗口本身 */
                DestroyAllControls (hWnd);
                DestroyMainWindow (hWnd);
                PostQuitMessage (hWnd);
                return 0;
        }
        
        return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* 以下创建主窗口的代码从略 */
```

__图 1.4__ 一个简单的编辑框

为了简单起见，我们在“myedit”中使用了等宽字体，因为其它字体的处理要困难得多。`myedit` 的窗口过程函数使用 `GetSystemFont` (`SYSLOGFONT_WCHAR_DEF`) 获取系统缺省的等宽字体，然后调用 `SetWindowFont` 设置文本输入窗口的字体。`myedit` 在 `MSG_CREATE` 消息中调用 `CreateCaret` 函数创建了一个与字符同高、宽度为 1 的插入符。

`pBuffer` 所指的缓冲区用于存储输入文本窗口的字符，`len` 记录字符的个数，`pos` 记录插入符的当前字符位置。

在收到 `MSG_SETFOCUS` 消息时，`myedit` 的窗口过程调用 `ShowCaret` 函数把它显示出来。在收到 `MSG_KILLFOCUS` 消息时，调用 `HideCaret` 把文本输入窗口的插入符隐藏掉。

`myedit` 在 `MSG_CHAR` 消息中处理普通字符的输入，相应地调整缓冲区以及 `pos` 和 `len` 的值。而且，`myedit` 在每次收到换行等特殊字符时，就调用 `SetCaretBlinkTime` 把插入符的反转时间减少 100 毫秒。

`myedit` 在 `MSG_KEYDOWN` 消息中处理左右箭头键和退格键，调用 `SetCaretPos` 调整插入符的位置。在 `MSG_PAINT` 消息中进行绘制，在收到 `MSG_DESTROY` 消息时把插入符销毁。
