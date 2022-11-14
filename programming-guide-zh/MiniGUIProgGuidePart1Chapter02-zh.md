# 窗口和消息

窗口和消息（或者说事件）是图形用户界面编程中的两个重要概念。窗口是显示器屏幕上的一个矩形区域，应用程序使用窗口来显示输出信息并接受用户的输入。流行的 GUI 编程一般都采用事件驱动机制。事件驱动的含义就是，程序的流程不再是只有一个入口和若干个出口的串行执行线路；相反，程序会一直处于一个循环状态，在这个循环当中，程序不断从外部或内部获取某些事件，比如用户的按键或者鼠标的移动，然后根据这些事件作出某种响应，并完成一定的功能，这个循环直到程序接收到某个消息为止。“事件驱动”的底层设施，就是常说的“消息队列”和“消息循环”。

本章将具体描述 MiniGUI 中的窗口模型和消息处理机制，以及用来处理消息的几个重要函数，并描述 MiniGUI-Threads 和 MiniGUI-Processes 在消息循环实现上的一些不同。

## 1.1 窗口系统和窗口

### 1.1.1 什么是窗口系统

拥有图形用户界面的计算机通过窗口系统（Window System）来管理应用程序在屏幕上的显示。一个图形用户界面系统的组成一般有图 1.1 所示的关系。

![图形用户界面系统的组成](figures/Part1Chapter02-1-1.jpeg)

__图 1.1__ 图形用户界面系统的组成

窗口系统是一个软件系统，它通过把显示屏幕分隔为不同的部分来帮助用户管理和控制不同的显示环境。窗口系统提供基于窗口的工作模式，每个窗口是屏幕上的一个矩形区域，平行于屏幕的边界。应用程序可以拥有一个或多个窗口，窗口系统通常采用“重叠窗口”的概念和机制来管理窗口的显示，各个窗口在屏幕上是相互重叠的。窗口系统克服了老式终端机上字符工作模式下一次只能在一个屏幕做一件工作的的缺点，它使得用户在一个屏幕上可以同时看到几件工作，还可以方便地切换工作项目。

### 1.1.2 窗口的概念

窗口是屏幕上的一个矩形区域。在传统的窗口系统模型中，应用程序的可视部分由一个或多个窗口构成。每一个窗口代表屏幕上的一块绘制区域，窗口系统控制该绘制区域到实际屏幕的映射，也就是控制窗口的位置、大小以及可见区域。每个窗口被分配一个屏幕绘制区域来显示本窗口的部分或全部，也许根本没有分配到屏幕区域（该窗口完全被其它的重叠窗口所覆盖和隐藏）。

屏幕上的重叠窗口通常具有如下的关系：

- 窗口一般组织为层次体系结构的形式（或者说，树的形式）。
- 根窗口（root window）是所有窗口的祖先，占满整个屏幕的表面，也称为桌面窗口。
- 除了根窗口以外的所有窗口都有父窗口，每一个窗口都可能有子窗口、兄弟窗口、祖先窗口和子孙窗口等。
- 子窗口含在父窗口内，同一个父窗口内的子窗口为同级窗口。
- 重叠窗口的可见性取决于它们之间的关系，一个窗口只有当它的父窗口可见时才是可见的，子窗口可以被父窗口剪切。
- 同级窗口可以重叠，但是某个时刻只能有一个窗口输出到重叠区域。
- 框架窗口（frame window/main window）包括可用的客户区和由窗口系统管理的修饰区（也称为“非客户区”）。
- 桌面窗口的子窗口通常为框架窗口。
- 窗口有从属关系，也就是说，某些窗口的生命周期和可见性由它的所有者决定。父窗口通常拥有它们的子窗口。
- 一个应用程序窗口一般包括如下部分：
- 一个可视的边界。
- 一个窗口ID，客户程序使用该ID来操作窗口，MiniGUI 中称为“窗口句柄”。
- 一些其它特性：高、宽、背景色等。
- 可能有菜单和滚动条等附加窗口元素。

## 1.2 MiniGUI 的窗口

### 1.2.1 窗口类型

MiniGUI 中有三种窗口类型：主窗口、对话框和控件窗口（子窗口）。每一个MiniGUI 应用程序一般都要创建一个主窗口，作为应用程序的主界面或开始界面。主窗口通常包括一些子窗口，这些子窗口通常是控件窗口，也可以是自定义窗口类。应用程序还会创建其它类型的窗口，例如对话框和消息框。对话框本质上就是主窗口，应用程序一般通过对话框提示用户进行输入操作。消息框是用于给用户一些提示或警告的主窗口，属于内建的对话框类型。

![MiniGUI 典型主窗口（经典风格）](figures/Part1Chapter02-1-2.jpeg)

图 1.2 MiniGUI 典型主窗口（经典风格）

> 【提示】你可以在程序里面改变 MiniGUI 显示窗口的渲染风格。图 1.2、图 1.3 给出了不同渲染风格下的显示效果。有关 MiniGUI 渲染风格的设置，请参考后面的章节。

![Hello world 程序的输出](figures/Part1Chapter02-1-3.jpeg)

图 1.3 MiniGUI 典型对话框（FLAT风格）

### 1.2.2 主窗口的创建

MiniGUI 中的主窗口没有窗口类的概念，应通过初始化一个 `MAINWINCREATE` 结构，然后调用 `CreateMainWindow` 或者是 `CreateMainWindowEx` 函数来创建一个主窗口。`MAINWINCREATE` 结构的成员解释如下：

```
CreateInfo.dwStyle           窗口风格
CreateInfo.spCaption         窗口的标题
CreateInfo.dwExStyle         窗口的附加风格
CreateInfo.hMenu             附加在窗口上的菜单句柄
CreateInfo.hCursor           在窗口中所使用的鼠标光标句柄
CreateInfo.hIcon             程序的图标
CreateInfo.MainWindowProc    该窗口的消息处理函数指针
CreateInfo.lx                窗口左上角相对屏幕的绝对横坐标,以象素点表示
CreateInfo.ty                窗口左上角相对屏幕的绝对纵坐标,以象素点表示
CreateInfo.rx                窗口右下角相对屏幕的绝对横坐标,以象素点表示
CreateInfo.by                窗口右下角相对屏幕的绝对纵坐标,以象素点表示
CreateInfo.iBkColor          窗口背景颜色
CreateInfo.dwAddData         附带给窗口的一个 32 位值
CreateInfo.hHosting          窗口消息队列的托管窗口
```

其中有如下几点要特别说明：

1. `CreateInfo.dwAddData`：在程序编制过程中，应该尽量减少静态变量，但是如何不使用静态变量而给窗口传递参数呢？这时可以使用这个域。该域是一个 32 位的值，因此可以把所有需要传递给窗口的参数编制成一个结构，而将结构的指针赋予该域。在窗口过程中，可以使用 `GetWindowAdditionalData` 函数获取该指针，从而获得所需要传递的参数。

2. `CreateInfo.hHosting`：该域表示的是将要建立的主窗口使用哪个主窗口的消息队列。使用其他主窗口消息队列的主窗口，我们称为“被托管”的主窗口。在 MiniGUI 中，托管的概念非常重要，一般要遵循如下规则：

- MiniGUI-Threads 中每个线程创建的第一个主窗口，其托管窗口必须是桌面，即 `HWND_DESKTOP`，该线程的其他窗口，必须由属于同一线程的已有主窗口作为托管窗口。系统在托管窗口为 `HWND_DESKTOP` 时创建新的消息队列，而在指定非桌面的窗口作为托管窗口时，使用该托管窗口的消息队列，也就是说，同一线程中的所有主窗口应该使用同一个消息队列。
- MiniGUI-Processes 中的所有主窗口也应该以类似的规则指定托管窗口，将所有主窗口看成是属于同一线程就可以了。

上面提到有两个函数可以用来创建一个主窗口，一个是 `CreateMainWindow` ， 一个是 `CreateMainWindowEx`。 `CreateMainWindow` 函数的原型如下：

```cpp
HWND GUIAPI CreateMainWindow (PMAINWINCREATE pCreateInfo)
```

只要传入赋值好的结构体指针 `pCreateInfo`，就可以创建一个主窗口了。
`CreateMainWindowEx` 函数的原型如下：

```cpp
HWND GUIAPI CreateMainWindowEx (PMAINWINCREATE pCreateInfo,
const char* werdr_name, const WINDOW_ELEMENT_ATTR* we_attrs,
const char* window_name, const char* layer_name);
```

这个函数除了结构体指针 `pCreateInfo` 不能为空外，其他参数都可以传入空值。当后面四个参数都传入空值时，等效于 `CreateMainWindow` 函数。`CreateMainWindowEx` 可以让你指定渲染器的名称，并修改某些渲染参数。有关这方面的内容将在 11 章“界面外观及特效”里面的“外观渲染器及窗口元素属性”一节，详细介绍。参数 `window_name` 和 `layer_name` 是保留参数，调用函数，赋空值即可。

### 1.2.3 窗口风格

窗口风格用来控制窗口的一些外观及行为方式，比如窗口的边框类型、窗口是否可见、窗口是否可用等等。在 MiniGUI 中，窗口风格又划分为普通风格和扩展风格，在创建窗口或者控件时，分别通过 `dwStyle` 和 `dwExStyle` 参数指定。我们将在后面讨论控件的章节中描述控件特有的风格，表 1.1 给出的风格是一些通用风格，这些风格的标识定义在 `<minigui/window.h>` 中，通常以 `WS_` 或者 `WS_EX` 的形式开头。

__表 1.1__ 窗口的通用风格

| 风格标识 | 含义	| 备注 | 
|:---|:--|:---|
| `WS_NONE` |未指定任何风格 | |
| `WS_VISIBLE`	| 创建初始可见的窗口| |
| `WS_DISABLED` | 创建初始被禁止的窗口| |
| `WS_CAPTION`	| 创建含标题栏的主窗口	| 仅用于主窗口 |
| `WS_SYSMENU`	| 创建含系统菜单的主窗口 |	仅用于主窗口 |
| `WS_BORDER`	| 创建有边框的窗口 | |
| `WS_THICKFRAME`	| 创建具有厚边框的窗口 | |
| `WS_THINFRAME`	| 创建具有薄边框的窗口 | |
| `WS_VSCROLL`	| 创建带垂直滚动条的窗口 | |
| `WS_HSCROLL`	创建带水平滚动条的窗口 | |
| `WS_MINIMIZEBOX`	| 标题栏上带最小化按钮	| 仅用于主窗口 |
| `WS_MAXIMIZEBOX`	| 标题栏上带最大化按钮	| 仅用于主窗口 |
| `WS_EX_NONE`	| 无扩展风格 | |
| `WS_EX_USEPRIVATECDC`	| 使用私有 `DC`	| 仅用于主窗口 |
| `WS_EX_TOPMOST`	| 建立始终处于顶层的主窗口	| 仅用于主窗口 |
| `WS_EX_TOOLWINDOW	`| 建立 `Tooltip` 主窗口	 | 仅 用 于 主 窗 口 。`Tooltip` 主 窗 口 将不会拥有输入焦点,但仍接收鼠标消息 |
| `WS_EX_TRANSPARENT`	| 透明窗口风格	| 仅用于控件 |
| `WS_EX_USEPARENTFONT`	| 使用父窗口字体作为默认字体 | |
| `WS_EX_USEPARENTCURSOR`	| 使用父窗口光标作为默认光标 | |
| `WS_EX_NOCLOSEBOX`	| 主窗口标题栏上不带关闭按钮 | |
| `WS_EX_CTRLASMAINWIN`	| 建立可显示在主窗口之外的控件	| 仅用于控件 |
| `WS_EX_TROUNDCNS`	| 建立左上角和右上角是圆角的窗口	 | |
| `WS_EX_BROUNDCNS`	| 建立左下角和右下角是圆角的窗口	 | |
| `WS_EX_CLIPCHILDREN`	| 调用 `BegainPaint` 获 得 `DC` 并刷新窗口客户区时, 子窗口所占区域将被剪切;也就是说,向窗口客户区的输出不会输出到子窗口所在位置。	| 该风格将导致额外的内存占用并影响绘制效率。只有窗口的输出和其子窗口的输出发生重叠时才应使用该风格,一般的对话框窗口、属性页控件无需使用该风格。 |

### 1.2.4 不规则窗口的创建

要创建不规则窗口或者控件，可以在窗口或者控件创建完成之后，调用 `SetWindowMask` 来实现不规则窗口或控件。

```cpp
BOOL GUIAPI SetWindowMask (HWND hWnd, const MYBITMAP* new_mask)
```

`new_mask` 参数是一个 `MYBITMAP` 结构，应用程序应使用 `MYBITMAP` 结构中的透明值表示掩码，即透明像素点在创建后的主窗口之外，透明像素点所在的位置将显示背景色。
下面的代码是创建不规则窗口的代码示例。

```cpp
pal = (RGB *)malloc (256 * sizeof (RGB));
LoadMyBitmap (&mybmp, pal, "11.bmp");

//设置调色板中需要透明颜色的序号，这里白色的序号是255
mybmp.transparent = 255;

hMainWnd = CreateMainWindow (&CreateInfo);
if (!SetWindowMask(hMainWnd, &mybmp))
return -1;
InvalidateRect(hMainWnd, NULL, TRUE);
if (hMainWnd == HWND_INVALID)
return -1;
```

![设置透明色为白色生成的不规则窗口](figures/Part1Chapter02-1-4.jpeg)

__图 1.4__ 设置透明色为白色生成的不规则窗口

下面的代码是创建一个不规则控件的代码示例。

```cpp
pal = (RGB *)malloc (256 * sizeof (RGB));
LoadMyBitmap (&mybmp, pal, "./33.bmp");

//设置调色板中需要透明颜色的序号，这里白色的序号是255
mybmp.transparent = 255;
btn1 = CreateWindowEx(
CTRL_MLEDIT,"",
WS_VISIBLE | WS_BORDER | WS_VSCROLL 
| ES_BASELINE | ES_AUTOWRAP | ES_NOHIDESEL | ES_NOHIDESEL,
WS_EX_TROUNDCNS,
0,
0, 0, mybmp.w, mybmp.h,
hWnd, 0);

if (!SetWindowMask(btn1, &mybmp))
return -1;
SetWindowBkColor(btn1, PIXEL_red); 
```

![背景色为红色的多行编辑框](figures/Part1Chapter02-1-5.jpeg)

__图 1.5__ 背景色为红色的多行编辑框

除了上面的方法，还可以调用下面的函数改变已有主窗口或者控件的可显示区域，达到实现不规则窗口或者控件的目的：

```cpp
HWND GUIAPI SetWindowRegion (HWND hwnd, const REGION* region);
```

例如：

```cpp
HWND btn;
btn = CreateWindow (CTRL_BUTTON,
0, 
WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_SORT | LBS_MULTIPLESEL | WS_VSCROLL, 
0, 
100, 140, 200, 100, hWnd, 0);

BLOCKHEAP cliprc_heap;
CLIPRGN circle_rgn;

InitFreeClipRectList (&cliprc_heap, 50);
InitClipRgn (&circle_rgn, &cliprc_heap);
InitCircleRegion (&circle_rgn, 20, 20, 20);

if (!SetWindowRegion (btn, &circle_rgn))
printf ("Error calling SetWindowRegion. \n");

EmptyClipRgn (&circle_rgn);
DestroyFreeClipRectList (&cliprc_heap);
```

![圆形按钮](figures/Part1Chapter02-1-6.jpeg)

__图 1.6__ 圆形按钮

为了方便使用，MiniGUI 创建了两个扩展风格 `WS_EX_TROUNDCNS` 和 `WS_EX_BROUNDCNS`，用于实现圆角窗口。当要实现此种不规则窗口时，只要添加此两种扩展风格即可，不需要再调用 `SetWindowMask` 和 `SetWindowRegion` 函数。

例如：

```cpp
int MiniGUIMain (int argc, const char* argv[])
{
        MSG Msg;
        HWND hMainWnd;
        MAINWINCREATE CreateInfo;
        
        CreateInfo.dwStyle = 
        WS_VISIBLE | WS_BORDER | WS_CAPTION;
        CreateInfo.dwExStyle = WS_EX_NONE | WS_EX_TROUNDCNS | WS_EX_BROUNDCNS;
        CreateInfo.spCaption = HL_ST_CAP;
        CreateInfo.hMenu = 0;
        CreateInfo.hCursor = GetSystemCursor(0);
        CreateInfo.hIcon = 0;
        CreateInfo.MainWindowProc = HelloWinProc;
        CreateInfo.lx = 0;
        CreateInfo.ty = 0;
        CreateInfo.rx = 320;
        CreateInfo.by = 240;
        CreateInfo.iBkColor = COLOR_lightwhite;
        CreateInfo.dwAddData = 0;
        CreateInfo.hHosting = HWND_DESKTOP;
        
        hMainWnd = CreateMainWindow (&CreateInfo);
        
        if (hMainWnd == HWND_INVALID)
        return -1;
        
        ShowWindow(hMainWnd, SW_SHOWNORMAL);
        
        while (GetMessage(&Msg, hMainWnd)) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
        }
        
        MainWindowThreadCleanup (hMainWnd);
        
        return 0;
}
```

![为圆角窗口](figures/Part1Chapter02-1-7.jpeg)
__图 1.7__ 为圆角窗口

### 1.2.5 主窗口的销毁

要销毁一个主窗口，可以利用 `DestroyMainWindow` (hWnd) 函数。该函数将向窗口过程发送 `MSG_DESTROY` 消息，并在该消息返回非零值时终止销毁过程。

应用程序一般在主窗口过程中接收到 `MSG_CLOSE` 消息时调用这个函数销毁主窗口，然后调用 `PostQuitMessage` 消息终止消息循环。如下所示：

```cpp
case MSG_CLOSE:
// 销毁主窗口
DestroyMainWindow (hWnd);
// 发送 MSG_QUIT 消息
PostQuitMessage(hWnd);
return 0;
```

`DestroyMainWindow` 销毁一个主窗口，但不会销毁主窗口所使用的消息队列以及窗口对象本身。因此，应用程序要在线程或进程的最后使用`MainWindowCleaup` 最终清除主窗口所使用的消息队列以及窗口对象本身。

在销毁一个主窗口时，MiniGUI 将调用 `DestroyMainWindow` 函数销毁所有的被托管窗口。

### 1.2.6 对话框

对话框是一种特殊的主窗口，应用程序一般通过`DialogBoxIndirectParam` 函数创建对话框：

```cpp
int  GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate,
HWND hOwner, WNDPROC DlgProc, LPARAM lParam);
```

该函数建立的对话框称为模态对话框。用户需要为此函数准备对话框模板和对话框的窗口过程函数。上面的函数其实是函数 `DialogBoxIndirectParamEx` 兼容版本。

```cpp
MG_EXPORT int GUIAPI DialogBoxIndirectParamEx (PDLGTEMPLATE pDlgTemplate,
HWND hOwner, WNDPROC DlgProc, LPARAM lParam,
const char* werdr_name, WINDOW_ELEMENT_ATTR* we_attrs,
const char* window_name, const char* layer_name);

static inline int GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate,
HWND hOwner, WNDPROC DlgProc, LPARAM lParam)
{
        return DialogBoxIndirectParamEx (pDlgTemplate, hOwner, DlgProc, lParam,
        NULL, NULL, NULL, NULL);
}
```

`DialogBoxIndirectParamEx` 是一个功能更加强大的对话框创建函数，它除了需要指定对话框模板和对话框的窗口过程函数，还可以指定渲染器的名称和相关的渲染参数，获得不同风格的对话框外观。关于渲染器，我们将在后面详细介绍。

本指南第 4 章讲述对话框的基本编程技术。

### 1.2.7 控件和控件类

MiniGUI 的每个控件都是某个控件类的实例，每个控件类有一个与之对应的控件过程，由所有同类的控件实例共享。

MiniGUI 中控件类的定义如下：

```cpp
typedef struct _WNDCLASS
{
        /** the class name */
        char*   spClassName;
        
        /** internal field, operation type */
        DWORD   opMask;
        
        /** window style for all instances of this window class */
        DWORD   dwStyle;
        
        /** extended window style for all instances of this window class */
        DWORD   dwExStyle;
        
        /** cursor handle to all instances of this window class */
        HCURSOR hCursor;
        
        /** background color pixel value of all instances of this window class */
        int     iBkColor;
        
        /** window callback procedure of all instances of this window class */
        int     (*WinProc) (HWND, int, WPARAM, LPARAM);
        
        /** the private additional data associated with this window class */
        DWORD dwAddData;
} WNDCLASS;
typedef WNDCLASS* PWNDCLASS;
```

控件类的主要元素如下：

- 类名 `spClassName`：区别于其它控件类的类名称。
- 窗口过程函数指针 `WinProc`：该类控件的实例均使用该窗口过程函数，它处理所有发送到控件的消息并定义控件的行为和特征。
- 类风格 `dwStyle`：定义窗口的外观和行为等的风格，该类的所有实例将具有该普通风格。
- 扩展的类风格 `dwExStyle`：定义窗口的扩展风格，该类的所有实例将具有该扩展风格。
- 类光标 `hCursor`：定义该类窗口中光标的形状。
- 背景色 `iBkColor`：定义该类窗口的背景颜色象素值。
- 类的私有附加数据 `dwAddData`：系统为该类保留的附加空间。

MiniGUI 中控件类操作的相关函数如下：

```cpp
BOOL GUIAPI RegisterWindowClass (PWNDCLASS pWndClass) ;

```

该函数注册一个控件类。

```cpp
BOOL GUIAPI UnregisterWindowClass (const char *szClassName) ;
```

该函数注销一个控件类。

```cpp
const char* GUIAPI GetClassName (HWND hWnd) ;
```

该函数获取指定控件的类名。

```cpp
BOOL GUIAPI GetWindowClassInfo (PWNDCLASS pWndClass) ;
```

该函数获取指定控件类的类信息。

```cpp
BOOL GUIAPI SetWindowClassInfo (const WNDCLASS *pWndClass) ;
```

该函数设置指定控件类的类信息。

下面的代码演示了在应用程序中如何使用 `WNDCLASS` 结构、`RegisterWindowClass` 函数和 `UnregisterWindowClass` 函数注册自定义控件类：

```cpp
/* 定义控件类的名字 */
#define MY_CTRL_NAME "mycontrol"

static int MyControlProc (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
        HDC hdc;
        
        switch (message) {
                case MSG_PAINT:
                /* 仅仅输出“hello, world! – from my control” */
                hdc = BeginPaint (hwnd);
                TextOut (hdc, 0, 0, "Hello, world! – from my control");
                EndPaint (hwnd, hdc);
                return 0;
        }
        
        return DefaultControlProc (hwnd, message, wParam, lParam);
}

/* 该函数向系统中注册“mycontrol”控件 */
static BOOL RegisterMyControl (void)
{
        WNDCLASS MyClass;
        
        MyClass.spClassName = MY_CTRL_NAME;
        MyClass.dwStyle     = 0;
        MyClass.hCursor     = GetSystemCursor (IDC_ARROW);
        MyClass.iBkColor    = COLOR_lightwhite;
        MyClass.WinProc     = MyControlProc;
        
        return RegisterWindowClass (&MyClass);
}

/* 从系统中注销该控件 */
static void UnregisterMyControl (void)
{
        UnregisterWindowClass (MY_CTRL_NAME);
}
```

上面建立的这个控件类在创建控件实例后，仅仅完成一件工作，就是在自己的客户区输出“Hello, world!”。在自己的应用程序中，使用这个自定义控件类的一般过程如下：

```cpp
/* 注册控件类 */
RegisterMyControl();

...

/* 在某个主窗口中建立该控件类的实例 */
hwnd = CreateWindow (MY_CTRL_NAME, “”, WS_VISIBLE, IDC_STATIC, 0, 0, 200, 20, parent, 0);

...

/* 使用完毕后销毁控件并注销控件类 */
DestroyWindow (hwnd);
UnregisterMyControl();
```

__图 1.8__ 显示的窗口中建立了一个上述自定义控件类的实例，其中显示了“Hello, world！ - from my control.”。该程序的完整清单请参阅本指南示例程序包 `mg-samples` 中的 `mycontrol.c` 文件。

![用自定义的控件显示 Hello, world!](figures/Part1Chapter02-1-8.jpeg)
__图 1.8__ 用自定义的控件显示 Hello, world!

本指南第 5 章中将讲述控件编程的基础知识,第 6 章讲述控件相关的高级编程技术; 在第 4 篇介绍所有的 MiniGUI 预定义控件。

### 1.2.8 输入法支持

输入法是 MiniGUI 为支持中文、韩文、日文等多字节字符集而引入的机制，和 Windows 系统下的输入法类似，输入法通常以顶层窗口的形式出现，并截获系统中的按键信息，经过适当的处理，将翻译之后的字符发送到当前活动窗口。在MiniGUI3.0版本中，输入法内容被重新增强并单独提出作为一个组件来提供给客户进行使用。详细请见mgi组件相关介绍

## 1.3 消息与消息处理

### 1.3.1 消息

MiniGUI 应用程序通过接收消息来和外界交互。消息由系统或应用程序产生，系统对输入事件产生消息，系统对应用程序的响应也会产生消息，应用程序可以通过产生消息来完成某个任务，或者与其它应用程序的窗口进行通讯。总而言之，MiniGUI 是消息驱动的系统，一切运作都围绕着消息进行。

系统把消息发送给应用程序窗口过程，窗口过程有四个参数：窗口句柄、消息标识以及两个 32 位的消息参数。窗口句柄决定消息所发送的目标窗口，MiniGUI 可以用它来确定向哪一个窗口过程发送消息。消息标识是一个整数常量，由它来标明消息的类型。如果窗口过程接收到一条消息，它就通过消息标识来确定消息的类型以及如何处理。消息的参数对消息的内容作进一步的说明，它的意义通常取决于消息本身，可以是一个整数、位标志或数据结构指针等。比如，对鼠标消息而言，`lParam` 中一般包含鼠标的位置信息，而 `wParam` 参数中则包含发生该消息时，对应的 SHIFT 键的状态信息等。对其他不同的消息类型来讲，`wParam` 和 `lParam` 也具有明确的定义。应用程序一般都需要检查消息参数以确定如何处理消息。

在第 2 章已经提到，在 MiniGUI 中，消息被如下定义 `<minigui/window.h>` ：

```cpp
typedef struct _MSG
{
        HWND             hwnd;
        int              message;
        WPARAM           wParam;
        LPARAM           lParam;
        unsigned int    time;
        #ifndef _LITE_VERSION
        void*            pAdd;
        #endif
}MSG;
typedef MSG* PMSG;
```

MSG 消息结构的成员包括该消息所属的窗口 `hwnd` 、消息标识 `message` 、消息的 `WPARAM` 型参数 `wParam` 、消息的 `LPARAM` 型参数 `lParam` 以及消息发生的时间。

### 1.3.2 消息的种类

MiniGUI 中预定义的通用消息有以下几类：

- 系统消息：包括 `MSG_IDLE`、`MSG_TIMER` 和 `MSG_FDEVENT` 等。
- 对话框消息：包括 `MSG_COMMAND`、`MSG_INITDIALOG`、`MSG_ISDIALOG`、`MSG_SETTEXT`、`MSG_GETTEXT`、和 `MSG_FONTCHANGED` 等。
- 窗口绘制消息：包括 `MSG_PAINT` 和 `MSG_ERASEBKGND` 等。
- 窗口创建和销毁消息：包括 `MSG_CREATE`、`MSG_NCCREATE`、`MSG_DESTROY` 和 `MSG_CLOSE` 等。
- 键盘和鼠标消息：包括 `MSG_KEYDOWN`、`MSG_CHAR`、`MSG_LBUTTONDOWN` 和 `MSG_MOUSEMOVE` 等。
- 鼠标/键盘后处理消息：包括 `MSG_SETCURSOR`、`MSG_SETFOCUS`、`MSG_KILLFOCUS`、`MSG_MOUSEMOVEIN` 等，指由于鼠标/键盘消息而引发的窗口事件消息。

用户也可以自定义消息，并定义消息的 `wParam` 和 `lParam` 意义。为了使用户能够自定义消息，MiniGUI 定义了 `MSG_USER` 宏，应用程序可如下定义自己的消息：

```cpp
#define MSG_MYMESSAGE1    (MSG_USER + 1)
#define MSG_MYMESSAGE2    (MSG_USER + 2)
```

用户可以在自己的程序中使用自定义消息，并利用自定义消息传递数据。

### 1.3.3 消息队列

MiniGUI 有两种向窗口过程发送消息的办法：

- 把消息投递到一个先进先出的消息队列中，它是系统中用于存储消息的一块内存区域，每个消息存储在一个消息结构中。
- 或是把消息直接发送给窗口过程，也就是通过消息发送函数直接调用窗口过程函数。

投递到消息队列中的消息主要是来自于键盘和鼠标输入的鼠标和键盘消息，如 `MSG_LBUTTONDOWN`、`MSG_MOUSEMOVE`、`MSG_KEYDOWN` 和 `MSG_CHAR` 等消息。投递到消息队列中的消息还有定时器消息 `MSG_TIMER`、绘制消息 `MSG_PAINT` 和退出消息 `MSG_QUIT` 等。

为什么需要消息队列呢？我们知道系统在同一时间显示多个应用程序窗口，用户移动鼠标或点击键盘时，设备驱动程序不断产生鼠标和键盘消息，这些消息需要发送给相应的应用程序和窗口进行处理。有了消息队列，系统就可以更好地管理各种事件和消息，系统和应用程序的交互就更加方便。

系统向应用程序消息队列投递消息是通过填充一个 `MSG` 消息结构，再把它复制到消息队列中，`MSG` 结构中的信息如上所述，包括接收消息的句柄、消息标识、两个消息参数以及消息时间。

应用程序可以通过 `GetMessage` 函数从它的消息队列中取出一条消息，该函数用所取出消息的信息填充一个MSG消息结构。应用程序还可以调用 `HavePendingMessage` 函数来检查消息队列中是否有消息而不取出消息。

```cpp
int GUIAPI GetMessage (PMSG pMsg, HWND hWnd);
BOOL GUIAPI HavePendingMessage (HWND hMainWnd);
```

非排队消息不通过消息队列而直接发送到目标窗口的窗口过程。系统一般通过发送非排队消息通知窗口完成一些需要立即处理的事件，比如 `MSG_ERASEBKGND` 消息。

### 1.3.4 消息的处理

应用程序必须及时处理投递到它的消息队列中的消息，程序一般在 `MiniGUIMain` 函数中通过一个消息循环来处理消息队列中的消息。

消息循环就是一个循环体，在这个循环体中，程序利用 `GetMessage` 函数不停地从消息队列中获得消息，然后利用 `DispatchMessage` 函数将消息发送到指定的窗口，也就是调用指定窗口的窗口过程，并传递消息及其参数。典型的消息循环如下所示：

```cpp
MSG  Msg;
HWND hMainWnd;
MAINWINCREATE CreateInfo;

InitCreateInfo (&CreateInfo);

hMainWnd = CreateMainWindow (&CreateInfo);
if (hMainWnd == HWND_INVALID)
return -1;

while (GetMessage (&Msg, hMainWnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
}
```

如上所示，应用程序在创建了主窗口之后开始消息循环。`GetMessage` 函数从 `hMainWnd` 窗口所属的消息队列当中获得消息，然后调用 `TranslateMessage` 函数将击键消息 `MSG_KEYDOWN` 和 `MSG_KEYUP` 翻译成字符消息 `MSG_CHAR`，最后调用 `DispatchMessage` 函数将消息发送到指定的窗口。

`GetMessage` 函数直到在消息队列中取到消息才返回，一般情况下返回非 0 值；如果取出的消息为 `MSG_QUIT`，`GetMessage` 函数将返回 0，从而使消息循环结束。结束消息循环是关闭应用程序的第一步，应用程序一般在主窗口的窗口过程中通过调用 `PostQuitMessage` 来退出消息循环。

在 MiniGUI-Threads 中，当我们需要在等待消息时立即返回以便处理其他事务时，可以使用 `HavePendingMessage` 函数。比如：

```cpp
do {
        /* It is time to read from master pty, and output. */
        ReadMasterPty (pConInfo);
        
        if (pConInfo->terminate)
        break;
        
        while (HavePendingMessage (hMainWnd)) {
                if (!GetMessage (&Msg, hMainWnd))
                break;
                DispatchMessage (&Msg);
        }
} while (TRUE);
```

上面的程序在没有任何消息或得到 `MSG_QUIT` 消息时立即返回并调用 `ReadMasterPty` 函数从某个文件描述符中读取数据。

在 MiniGUI-Threads 版本中，每个建立有窗口的 GUI 线程都有自己的消息队列，而且，所有属于同一线程的窗口共享同一个消息队列。因此，`GetMessage` 函数将获得所有与 `hMainWnd` 窗口在同一线程中的窗口的消息。而在 MiniGUI-Processes 版本中只有一个消息队列，`GetMessage` 将从该消息队列当中获得所有的消息，并忽略 `hMainWnd` 参数。一个消息队列只需要一个消息循环，不管应用程序有多少个窗口，因为MSG消息结构中含有消息的目标窗口句柄，`DispatchMessage` 函数就可以把消息发送到它的目标窗口。

`DispatchMessage` 函数所做的工作就是获取消息的目标窗口的窗口过程，然后直接调用该窗口过程函数对消息进行处理。

窗口过程是一个特定类型的函数，用来接收和处理所有发送到该窗口的消息。每个控件类有一个窗口过程，属于同一控件类的所有控件共用同一个窗口过程来处理消息。

窗口过程如果不处理某条消息，一般必须把这条消息传给系统进行默认处理。主窗口过程通常调用 `DefaultMainWinProc`（MiniGUI 默认为 `PreDefMainWinProc`）来完成消息的默认处理工作，并返回该函数的返回值。

```cpp
int PreDefMainWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```

绝大多数的窗口过程只处理几种类型的消息，其它的大部分消息则通过 `DefaultMainWinProc` 交由系统处理。

对话框的缺省消息处理由 `DefaultDialogProc` 函数（MiniGUI 默认为 `PreDefDialogProc`）完成。

```cpp
int PreDefDialogProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```

控件窗口的缺省消息处理由 `DefaultControlProc` 函数（MiniGUI 默认为 `PreDefControlProc`）完成。

```cpp
int PreDefControlProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```

### 1.3.5 发送和投递消息

投递（邮寄）一条消息就是把消息复制到消息队列中，发送消息则是直接把消息发送到窗口过程函数。

下面列出了 MiniGUI 中几个重要的消息处理函数。

`PostMessage`：该函数将消息放到指定窗口的消息队列后立即返回。这种发送方式称为“邮寄”消息。如果消息队列中的邮寄消息缓冲区已满，则该函数返回错误值。在下一个消息循环中，由 `GetMessage` 函数获得这个消息之后，窗口才会处理该消息。`PostMessage` 一般用于发送一些非关键性的消息。比如在 MiniGUI 中，鼠标和键盘消息就是通过 `PostMessage` 函数发送的。

`SendMessage`：应用程序一般通过发送一条消息来通知窗口过程立即完成某项任务。该函数和 `PostMessage` 函数不同，它把一条消息发送给指定窗口的窗口过程，而且等待该窗口过程完成消息的处理之后才会返回。当需要知道某个消息的处理结果时，使用该函数发送消息，然后根据其返回值进行处理。在 MiniGUI-Threads 当中，如果发送消息的线程和接收消息的线程不是同一个线程，发送消息的线程将阻塞并等待另一个线程的处理结果，然后继续运行；如果发送消息的线程和接收消息的线程是同一个线程，则与 MiniGUI-Processes 的 `SendMessage` 一样，直接调用接收消息窗口的窗口过程函数。

`SendNotifyMessage`：该函数和 `PostMessage` 消息类似，也是不等待消息被处理即返回。但和 `PostMessage` 消息不同，通过该函数发送的消息不会因为缓冲区满而丢失，因为系统采用链表的形式处理这种消息。通过该函数发送的消息称为“通知消息”，一般用来从控件向其父窗口发送通知消息。

`PostQuitMessage`：该消息在消息队列中设置一个 `QS_QUIT` 标志。`GetMessage` 在从指定消息队列中获取消息时，会检查该标志，如果有 `QS_QUIT` 标志，`GetMessage` 消息将返回 `FALSE`，从而可以利用该返回值终止消息循环。

其它的消息处理函数还有：

```cpp
int GUIAPI BroadcastMessage ( int iMsg, WPARAM wParam, LPARAM lParam );
```

该函数将指定消息广播给桌面上的所有主窗口。

```cpp
int GUIAPI ThrowAwayMessages (  HWND pMainWnd );
```

该函数丢弃和指定窗口相关的消息队列中的所有消息，并返回所丢弃的消息个数。

```cpp
BOOL GUIAPI WaitMessage ( PMSG pMsg, HWND hMainWnd );
```

该函数等待主窗口消息队列中的消息，消息队列中一有消息就返回。不同于 `GetMessage`， 这个函数并不从消息队列中移走消息。

### 1.3.6 MiniGUI-Processes 的专用消息处理函数

MiniGUI 还定义了一些 MiniGUI-Processes 的专用函数，可用于从 MiniGUI-Processes 服务器程序向其他客户程序发送消息。

```CPP
int GUIAPI Send2Client ( MSG * msg,  int cli );
```

`Send2Client` 函数发送一个消息给指定的客户。该函数定义在MiniGUI-Processes 中，而且只能被服务器程序 mginit 所调用。

`msg` 为消息结构指针；`cli` 可以是目标客户的标识符或下列特殊标识值中的一个：

- `CLIENT_ACTIVE`：顶层中的当前活动客户
- `CLIENTS_TOPMOST`：顶层中的所有客户
- `CLIENTS_EXCEPT_TOPMOST`：除了顶层中的客户以外的所有客户
- `CLIENTS_ALL`：所有的客户

返回值： 如果成功返回 `SOCKERR_OK`，否则返回 < 0 的值。

- `SOCKERR_OK`：读取数据成功
- `SOCKERR_IO`：发生 IO 错误
- `SOCKERR_CLOSED`：通讯所用的套接字已被关闭
- `SOCKERR_INVARG`：使用非法的参数

```CPP
BOOL GUIAPI Send2TopMostClients (  int iMsg, WPARAM wParam, LPARAM lParam );
```

`Send2TopMostClients` 函数发送一个消息给顶层中的所有客户。该函数定义在 MiniGUI-Processes 中，而且只能被服务器程序 mginit 所调用。

```cpp
BOOL GUIAPI Send2ActiveWindow (const MG_Layer* layer,
int iMsg, WPARAM wParam, LPARAM lParam); 
```

`Send2ActiveWindow1` 函数发送一个消息给指定层中的当前活动窗口。该函数定义在 MiniGUI-Processes 中，而且只能被服务器程序 mginit 所调用。

通常而言，由服务器发送给客户的消息最终会发送到客户的桌面，并由桌面处理程序继续进行处理，就好像 MiniGUI-Threads 程序收到来自键盘和鼠标的事件一样。

MiniGUI-Processes 还定义了一个特殊消息—— `MSG_SRVNOTIFY`，服务器可以将该消息及其参数发送给某个特定客户，客户在收到该消息之后，将把该消息广播到所有的客户主窗口。

## 1.4 几个重要的消息及其处理

在窗口（包括主窗口和子窗口在内）的生存周期当中，有几个重要的消息需要仔细处理。下面描述这些消息的概念和典型处理。

### 1.4.1 MSG_NCCREATE

该消息在 MiniGUI 建立主窗口的过程中发送到窗口过程。`lParam` 中包含了由 `CreateMainWindow` 传递进入的 `pCreateInfo` 结构指针。你可以在该消息的处理过程中修改 `pCreateInfo` 结构中的某些值。需要注意的是，系统向窗口过程发送此消息时，窗口对象尚未建立，因此，在处理该消息时不能使用 `GetDC` 等函数获得该窗口的设备上下文，也不能在 `MSG_NCCREATE` 消息中建立子窗口。

对输入法窗口来讲，必须在该消息的处理中进行输入法窗口的注册工作，比如：

```cpp
case MSG_NCCREATE:
if (hz_input_init())
/* Register before show the window. */
SendMessage (HWND_DESKTOP, MSG_IME_REGISTER, (WPARAM)hWnd, 0);
else
return -1;
break;
```

### 1.4.2 MSG_SIZECHANGING

该消息窗口尺寸发生变化时，或者建立窗口时发送到窗口过程，用来确定窗口大小。`wParam` 包含预期的窗口尺寸值，而 `lParam` 用来保存结果值。MiniGUI 的默认处理如下：

```cpp
case MSG_SIZECHANGING:
memcpy ((PRECT)lParam, (PRECT)wParam, sizeof (RECT));
return 0;
```

你可以截获该消息的处理，从而让即将创建的窗口位于指定的位置，或者具有固定的大小，比如在旋钮控件中，就处理了该消息，使之具有固定的大小：

```cpp
case MSG_SIZECHANGING:
{
        const RECT* rcExpect = (const RECT*) wParam;
        RECT* rcResult = (RECT*) lPraram;
        
        rcResult->left = rcExpect->left;
        rcResult->top = rcExpect->top;
        rcResult->right = rcExpect->left +  _WIDTH;
        rcResult->bottom = rcExpect->left +  _HEIGHT;
        return 0;
}
```

### 1.4.3 MSG_SIZECHANGED 和 MSG_CSIZECHANGED

`MSG_SIZECHANGED` 消息在窗口尺寸发生变化后发送到窗口过程，以确定窗口客户区的大小，其参数和 `MSG_SIZECHANGING` 消息类似。`wParam` 参数包含窗口大小信息，`lParam` 参数是用来保存窗口客户区大小的 `RECT` 指针，并且具有默认值。如果该消息的处理返回非零值，则将采用 `lParam` 当中包含的大小值作为客户区的大小；否则，将忽略该消息的处理。比如在 `SPINBOX` 控件中，就处理了该消息，并使客户区占具所有的窗口范围：

```cpp
case MSG_SIZECHANGED
{
        RECT* rcClient = (RECT*) lPraram;
        
        rcClient->right = rcClient->left  +  _WIDTH;
        rcClient->bottom = rcClient->top +  _HEIGHT;
        return 0;
}
```

`MSG_CSIZECHANGED` 消息是窗口客户区的尺寸发生变化后发送到窗口过程的通知消息，应用程序可以利用该消息对窗口客户区尺寸发生变化的事件做进一步处理。该消息的 `wParam` 和 `lParam` 参数分别包含新的客户区宽度和高度。

### 1.4.4 MSG_CREATE

该消息在窗口成功创建并添加到 MiniGUI 的窗口管理器之后发送到窗口过程。这时，应用程序可以在其中创建子窗口。如果该消息返回非零值，则将销毁新建的窗口。

### 1.4.5 MSG_FONTCHANGING

当应用程序调用 `SetWindowFont` 改变窗口的默认字体时，将发送该消息到窗口过程。通常情况下，应用程序应该将此消息传递给默认的窗口过程处理；但如果窗口不允许用户改变默认字体的话，就可以截获该消息并返回非零值。比如，MiniGUI 的简单编辑框只能处理等宽字体，因此，可如下处理该消息：

```cpp
case MSG_FONTCHANGING:
return -1;
```

应用程序处理该消息并返回非零值之后，`SetWindowFont` 函数将中止继续处理而返回，也就是说，窗口的默认字体不会发生改变。

### 1.4.6 MSG_FONTCHANGED

当应用程序调用 `SetWindowFont` 改变了窗口的默认字体后，将发送该消息到窗口过程。此时，窗口过程可以进行一些处理以便反映出新的字体设置。比如，MiniGUI 的编辑框就要处理这个消息，并最终重绘编辑框：

```cpp
case MSG_FONTCHANGED:
{
        sled =(PSLEDITDATA) GetWindowAdditionalData2 (hWnd);
        
        sled->startPos = 0;
        sled->editPos = 0;
        edtGetLineInfo (hWnd, sled);
        
        /* 重新建立适合新字体大小的插入符 */
        DestroyCaret (hWnd);
        CreateCaret (hWnd, NULL, 1, GetWindowFont (hWnd)->size);
        SetCaretPos (hWnd, sled->leftMargin, sled->topMargin);
        /* 重绘编辑框 */
        InvalidateRect (hWnd, NULL, TRUE);
        return 0;
}
```

### 1.4.7 MSG_ERASEBKGND

当系统需要清除窗口背景时，将发送该消息到窗口过程。通常情况下，应用程序调用 `InvalidateRect` 或者 `UpdateWindow` 等函数并为 `bErase` 参数传递 `TRUE` 时，系统将发送该消息通知窗口清除背景。默认窗口过程将以背景色刷新窗口客户区。某些窗口比较特殊，往往会在 `MSG_PAINT` 消息中重绘所有的窗口客户区，就可以忽略对该消息的处理：

```cpp
MSG_EARSEBKGND:
return 0;
```

还有一些窗口希望在窗口背景上填充一个图片，则可以在该消息的处理中进行填充操作:

```cpp
MSG_EARSEBKGND:
HDC hdc = (HDC)wParam;
const RECT* clip = (const RECT*) lParam;
BOOL fGetDC = FALSE;
RECT rcTemp;

if (hdc == 0) {
        hdc = GetClientDC (hDlg);
        fGetDC = TRUE;
}       

if (clip) {
        rcTemp = *clip;
        ScreenToClient (hDlg, &rcTemp.left, &rcTemp.top);
        ScreenToClient (hDlg, &rcTemp.right, &rcTemp.bottom);
        IncludeClipRect (hdc, &rcTemp);
}

/* 用图片填充背景 */
FillBoxWithBitmap (hdc, 0, 0, 0, 0, &bmp_bkgnd);

if (fGetDC)
ReleaseDC (hdc);
return 0;
```

用图片填充窗口背景的完整实现可参阅本指南示例程序包 `mg-samples` 中的 `bmpbkgnd.c` 程序，该程序的运行效果如图 1.9 所示。

![Hello world 程序的输出](figures/Part1Chapter02-1-9.jpeg)
__图 1.9__ 使用图片作为窗口背景

### 1.4.8 MSG_PAINT

该消息在需要进行窗口重绘时发送到窗口过程。MiniGUI 通过判断窗口是否含有无效区域来确定是否需要重绘。当窗口在初始显示、从隐藏状态变化为显示状态、从部分不可见到可见状态，或者应用程序调用 `InvalidateRect` 函数使某个矩形区域变成无效时，窗口将具有特定的无效区域。这时，MiniGUI 将在处理完所有的邮寄消息、通知消息之后处理无效区域，并向窗口过程发送 `MSG_PAINT` 消息。该消息的典型处理如下：

```cpp
case MSG_PAINT:
{
        HDC hdc;
        
        hdc = BeginPaint (hWnd);
        
        /* 使用 hdc 绘制窗口 */
        ...
        
        EndPaint (hWnd, hdc);
        return 0;
}
```

需要注意的是，应用程序在处理完该消息之后，应该直接返回，而不应该传递给默认窗口过程处理。在本指南第 2 篇中将详细讲述 MiniGUI 的设备上下文以及绘图函数。

### 1.4.9 MSG_CLOSE

当用户点击窗口上的“关闭”按钮时，MiniGUI 向窗口过程发送 `MSG_CLOSE` 消息。应用程序应在响应该消息时调用 `DestroyMainWindow` 销毁主窗口。如果窗口具有 `WS_MINIMIZEBOX` 和 `WS_MAXMIZEBOX` 风格，窗口标题栏上还将显示“最小化”和“最大化”按钮。目前，MiniGUI 尚未实现对这些风格的处理，但应用程序可以利用这两个风格显示其他的按钮，比如“确定”和“帮助”按钮，然后在窗口过程中处理 `MSG_MINIMIZE` 和 `MSG_MAXIMIZE` 消息。

### 1.4.10 MSG_DESTROY

该消息在应用程序调用 `DestroyMainWindow` 或者 `DestroyWindow` 时发送到窗口过程当中，用来通知系统即将销毁一个窗口。如果该消息的处理返回非零值，则将取消销毁过程。

当应用程序销毁某个托管主窗口时，`DestroyMainWindow` 函数将首先销毁被托管的主窗口。当然，在通常使用模式对话框的情况下，模式对话框的逻辑将保证在销毁托管主窗口时，该主窗口没有被托管的主窗口存在。但在使用非模式对话框或者普通主窗口时，应用程序应该遵循如下策略处理被托管的主窗口，以便在用户销毁某个托管主窗口时，能够正确销毁被托管的主窗口及其相关资源：

- 应用程序应在 `MSG_DESTROY` 消息中销毁被托管主窗口的位图、字体等资源：

```cpp
case MSG_DESTROY:
DestroyIcon (icon1);
DestroyIcon (icon2);
DestroyAllControls (hWnd);
return 0;
```

- 在被托管主窗口响应 `MSG_CLOSE` 消息时，调用 `DestroyMainWindow` 函数并调用 `MainWindowCleanup` 函数：

```cpp
case MSG_CLOSE:
DestroyMainWindow (hWnd);
MainWindowCleanup (hWnd);
return 0;
```

- 在托管主窗口中，处理 `MSG_CLOSE` 消息，并调用 `DestroyMainWindow` 函数。

我们也可以将托管主窗口的资源释放代码放在 `MSG_DESTROY` 消息中。 这样，不管用户关闭的是托管主窗口还是被托管主窗口，窗口本身以及相关资源均可以被完整释放。

## 1.5 通用窗口操作函数

MiniGUI 提供了一些通用的窗口操作函数，可用于主窗口和控件，__表 1.2__ 汇总了这些函数。在本指南中，我们用“窗口”这一术语来泛指主窗口和控件。如果没有特指，用于窗口的函数可用于主窗口或者控件。

__表 1.2__ 通用窗口操作函数

| 函数名称	| 用途	| 备注 |
|:---|:--|:---|
| `UpdateWindow`	| 立即更新某个窗口 | |
| `ShowWindow`	| 显示或隐藏某个窗口
| `IsWindowVisible |	判断某个窗口是否可见	| 控件和主窗口均可用 |
| `EnableWindow`	| 使能或禁止某个窗口 | |
| `IsWindowEnabled`	| 判断某个窗口是否可用 | |
| `GetClientRect`	| 获取窗口客户区矩形 | |
| `GetWindowRect`	| 获取窗口矩形	| 屏幕坐标系中的窗口尺寸 |
| `GetWindowBkColor`	| 获取窗口背景色 | |
| `SetWindowBkColor`	| 设置窗口背景色 | |
| `GetWindowFont`	| 获取窗口默认字体 | |
| `SetWindowFont`	| 设置窗口默认字体 | |
| `GetWindowCursor`	| 获取窗口光标 | |
| `SetWindowCursor`	| 设置窗口光标 | |
| `GetWindowStyle`	| 获取窗口风格 | |
| `GetWindowExStyle`	| 获取窗口扩展风格 | |
| `GetFocusChild`	| 获取拥有输入焦点的子窗口	| |
| `SetFocusChild`	| 设置焦点子窗口	| | 
| `GetWindowCallbackProc`	| 获取窗口过程函数 | |
| `SetWindowCallbackProc`	| 设置窗口过程函数 | |
| `GetWindowAdditionalData`	| 获取窗口附加数据一 | |
| `SetWindowAdditionalData`	| 设置窗口附加数据一 | |
| `GetWindowAdditionalData2` |	获取窗口附加数据二	| 对话框和控件在内部已使用附加数据二,保留附加数据一给应用程序使用 |
| `SetWindowAdditionalData2	`| 设置窗口附加数据二 | |
| `GetWindowCaption`	| 获取窗口标题	| 通常用于主窗口 |
| `SetWindowCaption`	| 设置窗口标题 | |
| `InvalidateRect`	| 使窗口的给定矩形区域无效	| 将引发窗口重绘 |
| `GetUpdateRect`	| 获取窗口当前的无效区域外包矩形 | |
| `ClientToScreen`	| 将窗口客户区坐标转换为屏幕坐标 | |
| `ScreenToClient`	| 将屏幕坐标转换为客户区坐标 | |
| `WindowToScreen`	| 将窗口坐标转换为屏幕坐标 | |
| `ScreenToWindow`	| 将屏幕坐标转换为窗口坐标 | |
| `IsMainWindow`	| 判断给定窗口是否为主窗口 | |
| `IsControl`	| 判断给定窗口是否为控件 | |
| `IsDialog`	| 判断给定窗口是否为对话框 | |
| `GetParent`	| 获取窗口的父窗口句柄	| 主 窗 口 的 父 窗 口 永 远 为 `HWND_DESKTOP` |
| `GetMainWindowHandle`	| 返回包含某个窗口的主窗口句柄 | |
| `GetNextChild`	| 获取下一个子窗口	| 用于遍历某个窗口的所有子窗口 |
| `GetNextMainWindow`	| 获取下一个主窗口句柄	| 用于遍历所有主窗口 |
| `GetHosting`	| 获取某个主窗口的托管窗口 | |	 
| `GetFirstHosted`	| 获取某个主窗口的第一个被托管窗口	| 用于遍历某个主窗口的所有被托管窗口 |
| `GetNextHosted`	| 获取下一个被托管窗口 | |
| `GetActiveWindow` |	获取当前活动主窗口 | |
| `SetActiveWindow` |	设置当前活动主窗口 | |
| `GetCapture`	| 获取当前捕获鼠标的窗口 | |
| `SetCapture`	| 捕获鼠标	| 第 9 章讲述鼠标捕获相关内容 |
| `ReleaseCapture`	| 释放鼠标 | |
| `MoveWindow`	| 移动窗口或改变窗口大小 | |
| `ScrollWindow`	| 自 1.6.8 版 本 , `ScrollWindow` 函滚动窗口客户区的内容	| 数可根据客户区的滚动情况自动调整窗口内子窗口的位置。具体来说 , 当 子 窗 口 所 在 位 置 在 `ScrollWindow` 第 二 个 传 入 参 数 指定的矩形内时,将相应调整子窗口位置;如果该参数为 `NULL`,则调整所有子窗口位置。 |
