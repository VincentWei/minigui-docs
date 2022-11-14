# 控件编程基础

较为复杂的 GUI 系统中，都带有预定义的控件集合，它们是人机交互的主要元素。本章将说明什么是控件、控件类，并简单介绍 MiniGUI 中的预定义控件类。

# 1.1 控件和控件类

许多人对控件（或者部件）的概念已经相当熟悉了。控件可以理解为主窗口中的子窗口。这些子窗口的行为和主窗口一样，既能够接收键盘和鼠标等外部输入，也可以在自己的区域内进行输出――只是它们的所有活动被限制在主窗口中。MiniGUI 也支持子窗口，并且可以在子窗口中嵌套建立子窗口。我们将 MiniGUI 中的所有子窗口均称为控件。

在 Windows 或 X Window 中，系统会预先定义一些控件类，当利用某个控件类创建控件之后，所有属于这个控件类的控件均会具有相同的行为和外观。利用这些技术，可以确保一致的人机操作界面，而对程序员来讲，可以像搭积木一样地组建图形用户界面。MiniGUI 使用了控件类和控件的概念，并且可以方便地对已有控件进行重载，使得它有一些特殊效果。比如，需要建立一个只允许输入数字的编辑框时，就可以通过重载已有编辑框而实现，而不需要重新编写一个新的控件类。

如果读者曾经编写过 Windows 应用程序的话，应该记得在建立一个窗口之前，必须确保系统中存在新窗口所对应的窗口类。在 Windows 中，程序所建立的每个窗口，都对应着某种窗口类。这一概念和面向对象编程中的类、对象的关系类似。借用面向对象的术语，Windows 中的每个窗口实际都是某个窗口类的一个实例。在 X Window 编程中，也有类似的概念，比如我们建立的每一个 `Widget`，实际都是某个 `Widget` 类的实例。

这样，如果程序需要建立一个窗口，就首先要确保选择正确的窗口类，因为每个窗口类决定了对应窗口实例的表象和行为。这里的表象指窗口的外观，比如窗口边框宽度，是否有标题栏等等，行为指窗口对用户输入的响应。每一个 GUI 系统都会预定义一些窗口类，常见的有按钮、列表框、滚动条、编辑框等等。如果程序要建立的窗口很特殊，就需要首先注册一个窗口类，然后建立这个窗口类的一个实例。这样就大大提高了代码的可重用性。

在 MiniGUI 中，我们认为主窗口通常是一种比较特殊的窗口。因为主窗口代码的可重用性一般很低，如果按照通常的方式为每个主窗口注册一个窗口类的话，则会导致额外不必要的存储空间，所以我们并没有在主窗口提供窗口类支持。但主窗口中的所有子窗口，即控件，均支持窗口类（控件类）的概念。MiniGUI 提供了常用的预定义控件类，包括按钮（包括单选钮、复选钮）、静态框、列表框、进度条、滑块、编辑框等等。程序也可以定制自己的控件类，注册后再创建对应的实例。

__表 1.1__ 给出了 MiniGUI 预先定义的控件类和相应类名称定义。

__表 1.1__ MiniGUI 预定义的控件类和对应类名称

| 控件类	| 类名称	| 宏定义	| 备注 |
|:------|:------|:-----|:-----|
| 静态框	| "static"	| CTRL_STATIC	| 见第19章 |
| 按钮	| "button"	| CTRL_BUTTON	| 见第20章 |
| 列表框	| "listbox"	| CTRL_LISTBOX	| 见第21章 |
| 单行编辑框	| "sledit"	| CTRL_SLEDIT	| 见第22章 |
| 多行编辑框	| "mledit"	| CTRL_MLEDIT	| （同 `CTRL_TEXTEDIT` 控件） |
| 文本编辑框	| “textedit”	| CTRL_TEXTEDIT	| 见第22章 |
| 组合框	| “combobox”	| CTRL_COMBOBOX	| 见第23章 |
| 菜单按钮	| "menubutton"	| CTRL_MENUBUTTON	| 见第24章 |
| 进度条	| "progressbar"	| CTRL_PRORESSBAR	| 见第25章 |
| 滑块	| "trackbar"	| CTRL_TRACKBAR	| 见第26章 |
| 工具栏	| "newtoolbar"	| CTRL_NEWTOOLBAR	| 见第27章 |
| 属性表	| "propsheet"	| CTRL_PROPSHEET	| 见第28章 |
| 滚动窗口控件	| "ScrollWnd"	| CTRL_SCROLLWND	| 见第29章 |
| 滚动型控件	| "ScrollView"	| CTRL_SCROLLVIEW	| 见第30章 |
| 树型控件	| "treeview"	| CTRL_TREEVIEW	| 见第31章 |
| 列表型控件	| "listview"	| CTRL_LISTVIEW	| 见第32章 |
| 月历	| "MonthCalendar"	| CTRL_MONTHCALENDAR |	见第33章 |
| 旋钮控件	| "SpinBox"	| CTRL_SPINBOX	| 见第34章 |
| 酷工具栏	| "CoolBar"	| CTRL_COOLBAR	| 见第35章 |
| 动画控件	| "Animation"	| CTRL_ANIMATION	| 见第36章 |
| 网格控件	| “gridview”	| CTRL_GRidVIEW	| 见第37章 |
| 图标型控件	| “IconView”	| CTRL_ICONVIEW	| 见第38章 |
| 滚动条控件	| "ScrollBar"	| CTRL_SCROLLBAR	| 见第39章 |

## 1.2 利用预定义控件类创建控件实例

在 MiniGUI 中，通过调用 `CreateWindow` 函数（`CreateWindow` 其实是 `CreateWindowEx` 函数的宏），可以建立某个控件类的一个实例。控件类既可以是__表 1.1__ 中预定义 MiniGUI 控件类，也可以是用户自定义的控件类。下面是与 `CreateWindow` 函数相关的几个函数的原型（<minigui/window.h>）：

```c
HWND GUIAPI CreateWindowEx2 (const char* spClassName,
const char* spCaption, DWORD dwStyle, DWORD dwExStyle,
int id, int x, int y, int w, int h, HWND hParentWnd,
const char* werdr_name, const WINDOW_ELEMENT_ATTR* we_attrs,
DWORD dwAddData);

static inline HWND GUIAPI CreateWindowEx (const char* spClassName,
const char* spCaption, DWORD dwStyle, DWORD dwExStyle,
int id, int x, int y, int w, int h, HWND hParentWnd,
DWORD dwAddData)
{
        return CreateWindowEx2 (spClassName, spCaption, dwStyle, dwExStyle,
        id, x, y, w, h, hParentWnd, NULL, NULL, dwAddData);
}

#define CreateWindow(class_name, caption, style, id, x, y, w, h, parent, add_data) \
CreateWindowEx(class_name, caption, style, 0, id, x, y, w, h, parent, add_data)

BOOL GUIAPI DestroyWindow (HWND hWnd);
```

`CreateWindow` 函数建立一个子窗口，即控件。它指定了控件类`class_name`、控件标题 `caption`、控件风格 `style`、控件的标识符 `id`、以及窗口的初始位置和大小 `x, y, w, h`。该函数同时指定子窗口的父窗口 `parent` 。参数 `add_data` 用来向控件传递其特有数据的指针，该指针所指向的数据结构随控件类的不同而不同。

`CreateWindow`Ex 函数的功能和 `CreateWindow` 函数一致，不过，可以通过 `CreateWindow`Ex 函数指定控件的扩展风格`dwExstyle`。

`CreateWindowEx2` 函数是 MiniGUI 3.0 新增的函数，该函数在 `CreateWindowEx` 基础之上增加了两个新的参数：`werdr_name` 和 `we_attrs`，分别用来指定控件所使用的渲染器名称以及渲染器属性。

`DestroyWindow` 函数用来销毁用上述两个函数建立的控件或者子窗口。

__清单 1.1__ 中的程序利用预定义控件类创建了几种控件：静态框、按钮和单行编辑框。其中 `hStaticWnd1` 是建立在主窗口 `hWnd` 中的静态框；`hButton1`、`hButton2`、`hEdit1`、`hStaticWnd2` 则是建立在 `hStaicWnd1` 内部的几个控件，并作为 `hStaticWnd1` 的子控件而存在；而 `hEdit2` 是 `hStaicWnd2` 的子控件，是 `hStaticWnd1` 的子子控件。

__清单 1.1__ 利用预定义控件类创建控件

```c
#define IDC_STATIC1     100
#define IDC_STATIC2     150
#define IDC_BUTTON1     110
#define IDC_BUTTON2     120
#define IDC_EDIT1       130
#define IDC_EDIT2       140

/* 创建一个静态框 */
hStaticWnd1 = CreateWindow (CTRL_STATIC, 
"This is a static control", 
WS_CHILD | SS_NOTIFY | SS_SIMPLE | WS_VISIBLE | WS_BORDER,
IDC_STATIC1, 
10, 10, 180, 300, hWnd, 0);

/* 在 hStaticWnd1 中创建两个按钮控件 */
hButton1  = CreateWindow (CTRL_BUTTON,
"Button1", 
WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 
IDC_BUTTON1, 
20, 20, 80, 20, hStaticWnd1, 0);
hButton2  = CreateWindow (CTRL_BUTTON,
"Button2", 
WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 
IDC_BUTTON2, 
20, 50, 80, 20, hStaticWnd1, 0);

/* 在 hStaticWnd1 中创建一个编辑框控件 */
hEdit1   = CreateWindow (CTRL_EDIT,
"Edit Box 1", 
WS_CHILD | WS_VISIBLE | WS_BORDER, 
IDC_EDIT1, 
20, 80, 100, 24, hStaticWnd1, 0);

/* 在 hStaticWnd1 中创建一个静态框 hStaticWnd2 */
hStaticWnd2 = CreateWindow (CTRL_STATIC, 
"This is child static control", 
WS_CHILD | SS_NOTIFY | SS_SIMPLE | WS_VISIBLE | WS_BORDER,
IDC_STATIC1, 
20, 110, 100, 50, hStaticWnd1, 0);

/* 在 hStaticWnd2 中创建一个编辑框 hEdit2，这时，hEdit2 是 hStaticWnd1 的孙窗口 */
hEdit2   = CreateWindow (CTRL_EDIT,
"Edit Box 2", 
WS_CHILD | WS_VISIBLE | WS_BORDER, 
IDC_EDIT2, 
0, 20, 100, 24, hStaticWnd2, 0);
```

## 1.3 控件编程涉及的内容

在控件编程中，所涉及到的内容除了控件的创建和销毁之外，一般还涉及到如下主题：

- 控件具有自己的窗口风格定义，需要在创建控件时指定需要的风格，不同的风格将使得控件具有不同的表象和行为。
- 获取或设置控件的状态、内容等。一般可通过向控件发送一些通用或者特有的消息来完成。另外，针对窗口的通用函数一般都适用于控件，例如：`ShowWindow`、`MoveWindow`、`EnableWindow`、`SetWindowFont` 等等。
- 控件内部发生某种事件时，会通过通知消息通知其父窗口。通知消息一般通过 `MSG_COMMAND` 消息发送，该消息的 `wParam` 参数由子窗口标识符和通知码组成，`lParam` 参数含有发出通知消息的控件句柄。例如，当用户修改编辑框中的内容时，编辑框会向父窗口发出 `EN_CHANGE` 通知消息。如果父窗口的窗口过程需要了解这一变化，则应该在父窗口的窗口过程中如下处理该通知消息：

```c
switch (message) {
        case MSG_COMMAND:
        {
                int id = LOWORD(wParam);
                int nc = HIWORD(wParam);
                if (id == ID_MYEDIT && nc == EN_CHANGE) {
                        /* 用户修改了子窗口 ID_MYEDIT 编辑框的内容，现在做进一步处理... */
                }
        }
        break;
}
```

- MiniGUI v1.2.6 及其后版本中针对控件的通知消息处理引入了`SetNotificationCallback` 函数，该函数可以为控件设置一个通知消息的回调函数。当控件有通知消息时，将调用该函数，而不是发送通知消息到父窗口。新的应用程序应尽量使用这个函数来处理控件的通知消息，以便获得良好的程序结构。本指南示例程序全部使用这一接口来处理控件的通知消息。

__清单 1.2__ 中的函数使用预定义控件类建立了一个简单的对话框。当用户在编辑框中输入以毫米为单位的数据时，系统将在编辑框之下的静态框中显示对应的以英寸为单位的数据，并在用户选择“确定”按钮时将用户输入的数据返回到调用该对话框的程序。

__清单 1.2__ 使用预定义控件实现简单输入对话框

```c
#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

/* 定义对话框模板 */
static DLGTEMPLATE DlgBoxInputLen =
{
        WS_BORDER | WS_CAPTION, 
        WS_EX_NONE,
        120, 150, 400, 160, 
        "请输入长度",
        0, 0,
        4, NULL,
        0
};

#define IDC_SIZE_MM     100
#define IDC_SIZE_INCH   110

/* 
* 该对话框一共含有 4 个控件，分别用于显示提示信息、
* 用户输入框、显示转换后的长度值以及关闭程序用的“确定”按钮。
*/
static CTRLDATA CtrlInputLen [] =
{ 
        {
                CTRL_STATIC,
                WS_VISIBLE | SS_SIMPLE,
                10, 10, 380, 18, 
                IDC_STATIC, 
                "请输入长度（单位：毫米）",
                0
        },
        {
                CTRL_EDIT,
                WS_VISIBLE | WS_TABSTOP | WS_BORDER,
                10, 40, 380, 24,
                IDC_SIZE_MM,
                NULL,
                0
        },
        {
                CTRL_STATIC,
                WS_VISIBLE | SS_SIMPLE,
                10, 70, 380, 18, 
                IDC_SIZE_INCH, 
                "相当于 0.00 英寸",
                0
        },
        {
                CTRL_BUTTON,
                WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
                170, 100, 60, 25,
                IDOK, 
                "确定",
                0
        }
};

/* 这是输入框的通知回调函数。*/
static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
        /* 当输入框中的值发生变化时，取出值并转换成英寸显示在英寸框中。
        */
        if (id == IDC_SIZE_MM && nc == EN_CHANGE) {
                char buff [60];
                double len;
                
                GetWindowText (hwnd, buff, 32);
                len = atof (buff);
                len = len / 25.4;
                
                sprintf (buff, "相当于 %.5f 英寸", len);
                SetDlgItemText (GetParent (hwnd), IDC_SIZE_INCH, buff);
        }
}       

/* 该对话框的窗口过程 */
static int InputLenDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
        switch (message) {
                case MSG_INITDIALOG:
                /* 将通过 DialogBoxIndirectParam 的最后一个参数传递进入的指针
                * 以窗口附加数据的形式保存下来，以便在以后使用。
                */
                SetWindowAdditionalData (hDlg, lParam);
                /* 设置控件的通知回调函数。
                */
                SetNotificationCallback (GetDlgItem (hDlg, IDC_SIZE_MM), my_notif_proc);
                return 1;
                
                case MSG_COMMAND:
                switch (wParam) {
                        case IDOK:
                        {
                                char buff [40];
                                /* 从输入框中获得数据，并保存在传入的指针中。
                                */
                                double* length = (double*) GetWindowAdditionalData (hDlg);
                                GetWindowText (GetDlgItem (hDlg, IDC_SIZE_MM), buff, 32);
                                *length = atof (buff);
                        }
                        case IDCANCEL:
                        EndDialog (hDlg, wParam);
                        break;
                }
                break;
        }
        
        return DefaultDialogProc (hDlg, message, wParam, lParam);
}

static void InputLenDialogBox (HWND hWnd, double* length)
{
        DlgBoxInputLen.controls = CtrlInputLen;
        
        DialogBoxIndirectParam (&DlgBoxInputLen, hWnd, InputLenDialogBoxProc, (LPARAM)length);
}

int MiniGUIMain (int argc, const char* argv[])
{
        double length;
        
        #ifdef _MGRM_PROCESSES
        JoinLayer(NAME_DEF_LAYER , "input" , 0 , 0);
        #endif
        
        InputLenDialogBox (HWND_DESKTOP, &length);
        
        /* 把用户在对话框中输入的值打印在终端上。
        */
        printf ("The length is %.5f mm.\n", length);
        
        return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif
```

__清单 1.2__ 程序的运行效果见图 1.1。该程序的完整源代码请见本指南示例程序包 `mg-samples` 中的 input.c 文件。

图 1.1 简单输入对话框

在本指南第 4 篇中，我们将详细介绍 MiniGUI 的各个预定义控件，我们将主要从三个方面介绍所有预定义控件：控件的用途、控件风格、控件消息以及控件的通知消息，并给出控件的编程实例。

## 1.4 控件专用的操作函数

MiniGUI 提供了一些控件专用的操作函数，见__表 1.2__。

__表 1.2__ 通用控件操作函数

| 函数名称	| 用途	| 备注 |
|:------|:------|:------|
| `GetNotificationCallback` |	获取控件的通知消息回调函数	| 在 MiniGUI 1.2.6 版本中出现 |
| `SetNotificationCallback`	 | 设置控件的通知消息回调函数	| （同上） |
| `NotifyparentEx`	| 发送控件通知消息	 | |
