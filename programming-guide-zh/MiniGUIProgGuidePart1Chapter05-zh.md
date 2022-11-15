# 控件高级编程

## 1 自定义控件

用户也可以通过 `RegisterWindowClass` 函数注册自己的控件类，并建立该控件类的控件实例。如果程序不再使用某个自定义的控件类，则应该使用 `UnRegisterWindowClass` 函数注销自定义的控件类。关于上述两个函数的用法，可参阅本指南 3.2.6 节“控件类”。

## 2 控件的子类化

采用控件类和控件实例的结构，不仅可以提高代码的可重用性，而且还可以方便地对已有控件类进行扩展。比如，在需要建立一个只允许输入数字的编辑框时，就可以通过重载已有编辑框控件类而实现，而不需要重新编写一个新的控件类。在 MiniGUI 中，这种技术称为子类化或者窗口派生。子类化的方法有三种：

- 一种是对已经建立的控件实例进行子类化，子类化的结果只会影响这一个控件实例。
- 一种是对某个控件类进行子类化，将影响其后创建的所有该控件类的控件实例。
- 最后一种是在某个控件类的基础上新注册一个子类化的控件类，不会影响原有控件类。在 Windows 中，这种技术又称为超类化。

在 MiniGUI 中，控件的子类化实际是通过替换已有的窗口过程实现的。__清单 1__ 中的代码就通过控件类创建了两个子类化的编辑框，一个只能输入数字，而另一个只能输入字母：

__清单 1__ 控件的子类化

```C
#define IDC_CTRL1     100
#define IDC_CTRL2     110
#define IDC_CTRL3     120
#define IDC_CTRL4     130

#define MY_ES_DIGIT_ONLY    0x0001
#define MY_ES_ALPHA_ONLY    0x0002

static WNDPROC old_edit_proc;

static int RestrictedEditBox (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
        if (message == MSG_CHAR) {
                DWORD my_style = GetWindowAdditionalData (hwnd);
                /* 确定被屏蔽的按键类型 */
                if ((my_style & MY_ES_DIGIT_ONLY) && (wParam < '0' || wParam > '9'))
                return 0;
                else if (my_style & MY_ES_ALPHA_ONLY)
                if (!((wParam >= 'A' && wParam <= 'Z') || (wParam >= 'a' && wParam <= 'z')))
                /* 收到被屏蔽的按键消息，直接返回 */
                return 0;
        }
        /* 由老的窗口过程处理其余消息 */
        return (*old_edit_proc) (hwnd, message, wParam, lParam);
}
static int ControlTestWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        switch (message) {
                case MSG_CREATE:
                {
                        HWND hWnd1, hWnd2, hWnd3;
                        CreateWindow (CTRL_STATIC, "Digit-only box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                        10, 10, 180, 24, hWnd, 0);
                        hWnd1 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER, IDC_CTRL1, 
                        200, 10, 180, 24, hWnd, MY_ES_DIGIT_ONLY);
                        CreateWindow (CTRL_STATIC, "Alpha-only box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                        10, 40, 180, 24, hWnd, 0);
                        hWnd2 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_BORDER | WS_VISIBLE, IDC_CTRL2, 
                        200, 40, 180, 24, hWnd, MY_ES_ALPHA_ONLY);
                        CreateWindow (CTRL_STATIC, "Normal edit box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                        10, 70, 180, 24, hWnd, 0);
                        hWnd3 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_BORDER | WS_VISIBLE, IDC_CTRL2, 
                        200, 70, 180, 24, hWnd, MY_ES_ALPHA_ONLY);
                        CreateWindow ("button", "Close", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, IDC_CTRL4, 
                        100, 100, 60, 24, hWnd, 0);
                        /* 用自定义的窗口过程替换编辑框的窗口过程，并保存老的窗口过程。*/
                        old_edit_proc = SetWindowCallbackProc (hWnd1, RestrictedEditBox);
                        SetWindowCallbackProc (hWnd2, RestrictedEditBox);
                        break;
                }
                ......
        }
        return DefaultMainWinProc (hWnd, message, wParam, lParam);
}
```

## 3 控件的组合使用

我们可以将两个不同的控件组合在一起使用，以达到某种特殊效果。其实，组合框这种预定义控件类就属于组合使用控件的典型。我们在组合不同控件时，可以将组合后的控件封装并注册为新的控件类，也可以不作封装而直接使用。

为了更好地说明组合使用控件的方法，假定我们要完成一个时间编辑器。这个时间编辑器以“08\:05\:30”的形式显示时间，根据用户需求，我们还要添加一种灵活编辑时间的方法。为了满足这种需求，我们可以将编辑框和旋钮框组合起来使用，它们分别实现如下功能：

- 编辑框中以“HH\:MM\:SS”的形式显示时间。
- 当输入焦点位于编辑框中时，用户不能直接编辑时间，而必须以光标键和 `PageDown` 及 `PageUp` 键来控制光标所在位置的时间单元值。为此，我们必须将该编辑框子类化，以捕获输入其中的按键，并做适当处理。
- 编辑框旁边安置一个旋钮控件，用户单击旋钮控件即可对光标所在的时间单元进行调整，增加或者减小。为实现这一目的，我们可以利用旋钮控件的功能，将其目标窗口句柄设置为编辑框。

这样，我们的时间编辑器就能正常工作了。该程序的部分代码见 __清单 2__，完整源代码可见本指南示例程序包 `mg-samples` 中的 `timeeditor.c` 文件。__图 1__ 给出了时间编辑器的运行效果。

__清单 2__ 时间编辑器

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>

#define IDC_EDIT    100
#define IDC_SPINBOX 110

/* 用于编辑框的字体。为了取得较好效果，本程序使用了 TrueType 字体 */
static PLOGFONT timefont;

/* 保存老的编辑框窗口过程 */
static WNDPROC old_edit_proc;

/* 本函数根据当前插入符的位置，修改相应的时间单元值 */
static void on_down_up (HWND hwnd, int offset)
{
        char time [10];
        int caretpos;
        int hour, minute, second;
        
        GetWindowText (hwnd, time, 8);
        caretpos = SendMessage (hwnd, EM_GETCARETPOS, 0, 0);
        
        hour = atoi (time);
        minute = atoi (time + 3);
        second = atoi (time + 6);
        
        if (caretpos > 5) { /* change second */
                /* 在秒的位置 */
                second += offset;
                if (second < 0)
                second = 59;
                if (second > 59)
                second = 0;
        }
        else if (caretpos > 2) { /* change minute */
                /* 在分的位置 */
                minute += offset;
                if (minute < 0)
                minute = 59;
                if (minute > 59)
                minute = 0;
        }
        else { /* change hour */
                /* 在时的位置 */
                hour += offset;
                if (hour < 0)
                hour = 23;
                if (hour > 23)
                hour = 0;
        }
        
        /* 将修改后的时间字符串置于编辑框 */
        sprintf (time, "%02d:%02d:%02d", hour, minute, second);
        SetWindowText (hwnd, time);
        
        /* 恢复插入符位置 */
        SendMessage (hwnd, EM_SETCARETPOS, 0, caretpos);
}

/* 这是编辑框的子类化窗口过程函数 */
static int TimeEditBox (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
        /* 只处理按键消息。下面这些键按下时，调用 on_down_up 函数修改时间值 */
        if (message == MSG_KEYDOWN) {
                switch (wParam) {
                        case SCANCODE_CURSORBLOCKUP:
                        on_down_up (hwnd, 1);
                        return 0;
                        case SCANCODE_CURSORBLOCKDOWN:
                        on_down_up (hwnd, -1);
                        return 0;
                        case SCANCODE_PAGEUP:
                        on_down_up (hwnd, 10);
                        return 0;
                        case SCANCODE_PAGEDOWN:
                        on_down_up (hwnd, -10);
                        return 0;
                        
                        case SCANCODE_CURSORBLOCKLEFT:
                        case SCANCODE_CURSORBLOCKRIGHT:
                        break;
                        default:
                        return 0;
                }
        }
        
        /* 忽略下面两个消息，用户只能通过上面的按键进行操作 */
        if (message == MSG_KEYUP || message == MSG_CHAR)
        return 0;
        
        return (*old_edit_proc) (hwnd, message, wParam, lParam);
}

static int TimeEditorWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        switch (message) {
                case MSG_CREATE:
                {
                        HWND hwnd;
                        HDC hdc;
                        HWND timeedit, spin;
                        SIZE size;
                        
                        /* 建立说明性静态框 */
                        hwnd = CreateWindow (CTRL_STATIC, 
                        "This is a time editor.\n\n"
                        "Pressing <Down-Arrow>, <Up-Arrow>, <PgDn>, and <PgUp> keys"
                        " when the box has input focus will change the time.\n\n"
                        "You can also change the time by clicking the SpinBox.\n",
                        WS_CHILD | WS_VISIBLE | SS_LEFT, 
                        IDC_STATIC, 
                        10, 10, 220, 200, hWnd, 0);
                        
                        /* 创建编辑框使用的逻辑字体 */
                        timefont = CreateLogFont (NULL, "Arial", "ISO8859-1", 
                        FONT_WEIGHT_BOOK, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
                        FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 
                        30, 0);
                        
                        /* 计算输出时间所用的大小和宽度 */
                        hdc = GetClientDC (hWnd);
                        SelectFont (hdc, timefont);
                        GetTextExtent (hdc, "00:00:00", -1, &size);
                        ReleaseDC (hdc);
                        
                        /* 按照计算出的值创建编辑框窗口 */
                        timeedit = CreateWindow (CTRL_SLEDIT, 
                        "00:00:00", 
                        WS_CHILD | WS_VISIBLE | ES_BASELINE, 
                        IDC_EDIT, 
                        40, 220, size.cx + 4, size.cy + 4, hWnd, 0);
                        
                        /* 设置编辑框字体 */
                        SetWindowFont (timeedit, timefont);
                        
                        /* 子类化编辑框 */
                        old_edit_proc = SetWindowCallbackProc (timeedit, TimeEditBox);
                        
                        /* 创建旋钮控件 */
                        spin = CreateWindow (CTRL_SPINBOX, 
                        "", 
                        WS_CHILD | WS_VISIBLE, 
                        IDC_SPINBOX, 
                        40 + size.cx + 6, 220 + (size.cy - 14) / 2, 0, 0, hWnd, 0);
                        
                        /* 
                        * 将旋钮控件的目标窗口设置为编辑框，这样，
                        * 当用户单击旋钮时，将模拟 MSG_KEYDOWN 消息
                        * 并发送到编辑框。
                        */
                        SendMessage (spin, SPM_SETTARGET, 0, timeedit);
                        break;
                }
                
                case MSG_DESTROY:
                DestroyAllControls (hWnd);
                DestroyLogFont (timefont);
                return 0;
                
                case MSG_CLOSE:
                DestroyMainWindow (hWnd);
                PostQuitMessage (hWnd);
                return 0;
        }
        
        return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

/* 以下创建主窗口的代码从略 */
```
![时间编辑器的运行效果](figures/Part2Chapter05-01.jpeg)

__图 1__ 时间编辑器的运行效果
