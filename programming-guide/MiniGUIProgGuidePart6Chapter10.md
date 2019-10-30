# Property Sheet Control

The most familiar usage of property sheet is to place the interaction content
belonging to different dialog boxes into one dialog box according to their
catalogues. This can save space of the dialog box on the one hand, and can make
the interaction interface more convenient to use on the other hand. Figure 1 is
a typical use of the property sheet control of MiniGUI.

![alt](figures/28.1.jpeg)

__Figure 1__ Property sheet control


The property sheet is comprised of a group of property pages. Each property
page has a tab, and we can click the tab to switch among different property
pages. We can interpret the property page as a container control, in which
other controls can be contained. From the point of view of an application
developer, we can also interpret the property page as a dialog box in a dialog
box - each property page has its own window procedure, and we can use the
method similar to create a dialog box, i.e. the method to define a dialog box
template, to add a property page into a property sheet control.

In an application, calling `CreateWindow` with `CTRL_PROPSHEET` as the control
class name can create a property sheet control.

## Styles of Property Sheet

At present, there are only the following two styles of property sheet, which
are used to control the width of a tab of the property sheet:
- `PSS_SIMPLE`: All tabs of the control will have the same width.
- `PSS_COMPACTTAB`: The width of a tab depends on the length of the tab title
of the property sheet.
- `PSS_SCROLLABLE`: The width of a tab depends on the length of the tab title
of the property sheet. There will be two of navigation button for scroll the
tabs when the count of tab is too many.
- `PSS_BOTTOM`: Tabs are displayed at the bottom of the property sheet. This
style can be used to with other three styles.

## Messages of Property Sheet
### Adding Property Page

After the property sheet control has been created, we can send `PSM_ADDPAGE`
message to add a property page to the property sheet. `WParam` of the message
is used to pass the dialog box template, and `lParam` is used to pass the
window procedure function of the property page, as shown in the following code:

```cpp
    HWND pshwnd = GetDlgItem (hDlg, IDC_PROPSHEET);

    /* Prepare the dialog box template */
    DlgStructParams.controls = CtrlStructParams;

    /* Add a property page */
    SendMessage (pshwnd, PSM_ADDPAGE,
                            (WPARAM)&DlgStructParams, (LPARAM)PageProc1);
```

The return value of this message is the index of the newly added property page,
and the index is base-on zero.

### Procedure Function of Property Page

Similar to the dialog box, each property page has its own procedure function to
handle the related messages of the property page. The prototype of the
procedure function is the same with a normal window procedure function, but the
followings are different:
- The procedure function of a property page should call `DefaultPageProc`
function for the message needing default handling.
- The procedure function of a property page need handle two messages specific
to the property page: `MSG_INITPAGE` and `MSG_SHOWPAGE`. The former is similar
to `MSG_INITDIALOG` message of a dialog box; and the latter is sent to the
procedure of the property page when the property page is hidden or showed,
where `lParam` parameter is `SW_HIDE` and `SW_SHOW`, respectively. When the
property page is displayed, the procedure function of the property page returns
1 to make the first control with `WS_TABSTOP` has the input focus.
- If you send `PSM_SHEETCMD` message to the property sheet control, the control
will broadcast `MSG_SHEETCMD` message to all pages it contains. At this time,
the page callback procedure can check the validity of the user input and save
the valid input. If the input is invalid or other problems occur, the page can
return -1 to break the continued broadcast of this message. After receiving a
non-zero value from any property page, the property sheet control will make
`PSM_SHEETCMD` message return a non-zero value, and this is equal to the page
index plus one. In such a way, we can know which page includes invalid input
during handling the property pages of the property sheet, and then terminate
the handling and switch to this property page.

List 1 gives a typical procedure function of a property page, and the procedure
function of the dialog box of the property sheet. When the user clicks the “OK”
button of the dialog box containing the property sheet, the dialog box sends
`PSM_SHEETCMD` message to the property sheet control, and according to the
return value of the message, determines to close the dialog box or switch to a
property page to correct the invalid input. After receiving `MSG_SHEETCMD`
message, the procedure function of the property page will determine whether the
user input is valid, and returns 0 or -1 correspondingly.


__List 1__ A typical procedure function of property page and a procedure function
of dialog box containing property sheet

```cpp
static int PageProc1 (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITPAGE:
        break;

    case MSG_SHOWPAGE:
        return 1;

    case MSG_SHEETCMD:
        if (wParam == IDOK) {
            char buffer [20];
            GetDlgItemText (hDlg, IDC_EDIT1, buffer, 18);
            buffer [18] = '\0';

             /* When the user clicked the “OK” button in
              * the dialog box containing the property sheet,
              * determine whether the user input is valid
              */
            if (buffer [0] == '\0') {
                MessageBox (hDlg,
                            "Please input something in the first edit box.",
                            "Warning!",
                            MB_OK | MB_ICONEXCLAMATION | MB_BASEDONPARENT);
                /* The user input is invalid, return a non-zero value */
                return -1;
            }
        }
        return 0;

    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
        case IDCANCEL:
            break;
        }
        break;
    }

    return DefaultPageProc (hDlg, message, wParam, lParam);
}

static int PropSheetProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case MSG_INITDIALOG:
        {
            HWND pshwnd = GetDlgItem (hDlg, IDC_PROPSHEET);

            /* Add property pages to the property sheet control */

            DlgStructParams.controls = CtrlStructParams;
            SendMessage (pshwnd, PSM_ADDPAGE,
                            (WPARAM)&DlgStructParams, (LPARAM)PageProc1);

            DlgPassword.controls = CtrlPassword;
            SendMessage ( pshwnd, PSM_ADDPAGE,
                            (WPARAM)&DlgPassword,(LPARAM) PageProc2);

            DlgStartupMode.controls = CtrlStartupMode;
            SendMessage ( pshwnd, PSM_ADDPAGE,
                            (WPARAM)&DlgStartupMode,(LPARAM)PageProc3);

            DlgInitProgress.controls = CtrlInitProgress;
            SendMessage ( pshwnd, PSM_ADDPAGE,
                            (WPARAM)&DlgInitProgress, (LPARAM) PageProc4);

            break;
        }

        case MSG_COMMAND:
        switch (wParam)
        {
            case IDC_APPLY:
            break;

            case IDOK:
            {
                /* Send PSM_SHEETCMD messaeg to the property sheet control to
                 * inform it that the “OK” button is clicked
                 */
                int index = SendDlgItemMessage (hDlg, IDC_PROPSHEET,
                                PSM_SHEETCMD, IDOK, 0);
                if (index) {
                    /* A property page returns a non-zero value,
                     * switch to this property page and prompt to input again
                     */
                    SendDlgItemMessage (hDlg, IDC_PROPSHEET,
                                    PSM_SETACTIVEINDEX, index - 1, 0);
                }
                else
                    /* Every thing is ok, close the dialog box */
                    EndDialog (hDlg, wParam);

                break;
            }
            case IDCANCEL:
                EndDialog (hDlg, wParam);
            break;
        }
        break;
    }

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}
```

### Deleting Property Page

To delete a property page, you need only send `PSM_REMOVEPAGE` message to the
property sheet control, and pass the index of the property page to be deleted
through `wParam` parameter:

```cpp
SendDlgItemMessage (hDlg, IDC_PROPSHEET, PSM_REMOVEPAGE, 0, 0);
```

This message will delete the first property page in the property sheet.

__NOTE__ Deleting a property page may change the indices of other property pages.

### Handle and Index of Property Page

The handle of a property page is actually the handle of the parent window of
the controls in the property page, i.e. the window handle passed by the
procedure function of the property page, and this window is actually a child
window of the property sheet control. Sending `PSM_GETPAGE` message to the
property sheet control can get the handle of a property page with a certain
index:

```cpp
hwnd = SendDlgItemMessage (hDlg, IDC_PROPSHEET, PSM_GETPAGE, index, 0);
```

This message will return the handle of the property page with index value of
“index”. While the following message call returns the index of a page based on
the handle of the property page:

```cpp
  index = SendDlgItemMessage (hDlg, IDC_PROPSHEET, PSM_GETPAGEINDEX, hwnd, 0);
```

After getting the handle of the property page, we can call functions such as
`CreateWindow` to add a new control to the page conveniently. Of course, in the
procedure function of the property page, we can complete the similar task.

### Messages Relevant Property Page

MiniGUI provides the following messages to get the relevant information of
property pages:：
- `PSM_GETPAGECOUNT:returns` the number of pages in the property sheet.
- `PSM_GETTITLELENGTH`: gets the length of the page title according to the
index value passed by `wParam` parameter, like the `MSG_GETTEXTLENGTH` message
of a window.
- `PSM_GETTITLE`: gets the page title according to the index value passed by
`wParam` parameter, and save it in the buffer passed by `lParam` parameter,
like the `MSG_GETTEXT` message of a window.
- `PSM_SETTITLE`: sets the property page title according to the string passed
by `lParam`, like `MSG_SETTEXT` message of a window.

The active property page is the property page currently displayed in the
property sheet, and every time only one-property page is displayed in the
property sheet. MiniGUI provides the following messages to handle the active
property page:
- `PSM_GETACTIVEPAGE`: returns the handle of the current active page.
- `PSM_GETACTIVEINDEX`: returns the index of the current active page
- `PSM_SETACTIVEINDEX`: sets the active property page according to the index
passed by `wParam`.

## Notification Codes of Property Sheet

At present, there is only one notification code for property sheet control:
- `PSN_ACTIVE_CHANGED`: When the active property page of the property sheet
changed, the property sheet control will generate this notification code.

## Sample Program

List 2 gives a sample program for property sheet control. This program displays
some system information of the computer, such as `CPU` type, memory size, etc.
The running effect of this program is shown in Figure 2. Please refer to
`propsheet.c` of the sample program package of this guide for the complete source
code.

__List 2__ A sample program of property sheet control

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define PAGE_VERSION    1
#define PAGE_CPU        2
#define PAGE_MEMINFO    3
#define PAGE_PARTITION  4
#define PAGE_MINIGUI    5

#define IDC_PROPSHEET   100

#define IDC_SYSINFO     100

/* 定义系统信息属性页的模板 */
/* Define the template of the system information property page  */
static DLGTEMPLATE PageSysInfo =
{
    WS_NONE,
    WS_EX_NONE,
    0, 0, 0, 0,
    "",
    0, 0,
    1, NULL,
    0
};

/*系统信息属性页中只有一个用来显示信息的静态控件 */
/* There is only one static control to display the information
 * in the system information property page
 */
static CTRLDATA CtrlSysInfo [] =
{
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_LEFT,
        10, 10, 370, 160,
        IDC_SYSINFO,
        "测试\n测试\n测试\n测试\n测试\n测试\n",
        0
    }
};

/* 从指定文件中读取系统信息 */
/* Read the system information from the specified file */
static size_t read_sysinfo (const char* file, char* buff, size_t buf_len)
{
     size_t size;
     FILE* fp = fopen (file, "r");

     if (fp == NULL) return 0;

     size = fread (buff, 1, buf_len, fp);

     fclose (fp);
     return size;
}

#define BUF_LEN 10240

/*
 * 初始化和刷新时调用该函数刷新对应的窗口。
 * 注意，这个函数被所有的属性页调用。
 */
/*
 * Call this function to refresh the corresponding window
 * when initializing and refreshing
 * Note, this function is called by all the property pages.
 */
static void get_systeminfo (HWND hDlg)
{
    int type;
    HWND hwnd;
    char buff [BUF_LEN + 1];
    size_t size = 0;

    /* 根据 type 判断是哪个属性页 */
    /* Determine which property page according to “type”  */
    type = (int)GetWindowAdditionalData (hDlg);

    /* 获取属性页中静态框的句柄 */
    /* Get the handle of the static control of the property page */
    hwnd = GetDlgItem (hDlg, IDC_SYSINFO);

    buff [BUF_LEN] = 0;
    switch (type) {
    case PAGE_VERSION:
        size = read_sysinfo ("/proc/version", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_CPU:
        size = read_sysinfo ("/proc/cpuinfo", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_MEMINFO:
        size = read_sysinfo ("/proc/meminfo", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_PARTITION:
        size = read_sysinfo ("/proc/partitions", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_MINIGUI:
        size = snprintf (buff, BUF_LEN,
              "MiniGUI version %d.%d.%d.\n"
              "Copyright (C) 1998-2003 FMSoft and others.\n\n"
              "MiniGUI is free software, covered by the GNU General Public License, "
              "and you are welcome to change it and/or distribute copies of it “
              “under certain conditions. "
              "Please visit\n\n"
              "http://www.minigui.org\n\n"
              "to know the details.\n\n"
              "There is absolutely no warranty for MiniGUI.",
              MINIGUI_MAJOR_VERSION, MINIGUI_MINOR_VERSION, MINIGUI_MICRO_VERSION);
              break;
    }

    if (size) {
        SetWindowText (hwnd, buff);
    }
}

/* 所有的属性页使用同一个窗口过程函数 */
/* All the property pages use the same window procedure function */
static int SysInfoPageProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITPAGE:
        /* 获取属性页中静态框的句柄 */
        /* return the handle of the static control of the property page */
        get_systeminfo (hDlg);
        break;

    case MSG_SHOWPAGE:
        return 1;

    case MSG_SHEETCMD:
        if (wParam == IDOK)
            /* 用户单击对话框中的“刷新”按钮时，将调用该函数刷新 */
            /* When the user clicked the “refresh” button of the
             * dialog box, call this function to refresh.
             */
            get_systeminfo (hDlg);
        return 0;
    }

    return DefaultPageProc (hDlg, message, wParam, lParam);
}

static int PropSheetProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case MSG_INITDIALOG:
        {
            HWND pshwnd = GetDlgItem (hDlg, IDC_PROPSHEET);

            PageSysInfo.controls = CtrlSysInfo;

            /* 添加属性页，注意每个属性页具有不同的附加数据 */
            /* Add property pages. Note that each property page
             * has different additional data
             */

            PageSysInfo.caption = "版本信息";
            PageSysInfo.dwAddData = PAGE_VERSION;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
            PageSysInfo.caption = "CPU 信息";
            PageSysInfo.dwAddData = PAGE_CPU;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);

            PageSysInfo.caption = "内存信息";
            PageSysInfo.dwAddData = PAGE_MEMINFO;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);

            PageSysInfo.caption = "分区信息";
            PageSysInfo.dwAddData = PAGE_PARTITION;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);

            PageSysInfo.caption = "MiniGUI 信息";
            PageSysInfo.dwAddData = PAGE_MINIGUI;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
            break;
        }

        case MSG_COMMAND:
        switch (wParam) {
            case IDOK:
                /* 用户按“刷新”按钮时，向所有属性表控件发送 PSM_SHEETCMD 消息 */
                /* When the user clicked the “refresh” button,
                 * send PSM_SHEETCMD message to the property sheet control
                 */
                SendDlgItemMessage (hDlg, IDC_PROPSHEET, PSM_SHEETCMD, IDOK, 0);
                break;

            case IDCANCEL:
                EndDialog (hDlg, wParam);
            break;
        }
        break;
    }

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

/* 主对话框的模板 */
/* Template of the main dialog box */
static DLGTEMPLATE DlgPropSheet =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 410, 275,
    "系统信息",
    0, 0,
    3, NULL,
    0
};

/* 该对话框只有三个控件：属性表、“刷新”按钮和“关闭”按钮 */
/* The dialog box has only three controls:
 * the property sheet, “refresh” button and “close” button
 */
static CTRLDATA CtrlPropSheet[] =
{
    {
        CTRL_PROPSHEET,
        WS_VISIBLE | PSS_COMPACTTAB,
        10, 10, 390, 200,
        IDC_PROPSHEET,
        "",
        0
    },
    {
        CTRL_BUTTON,
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        10, 220, 140, 25,
        IDOK,
        "刷新",
        0
    },
    {
        CTRL_BUTTON,
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        260, 220, 140, 25,
        IDCANCEL,
        "关闭",
        0
    },
};

int MiniGUIMain (int argc, const char* argv[])
{
#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "propsheet" , 0 , 0);
#endif

    DlgPropSheet.controls = CtrlPropSheet;

    DialogBoxIndirectParam (&DlgPropSheet, HWND_DESKTOP, PropSheetProc, 0L);

    return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif
```

![alt](figures/28.2.jpeg)

__Figure 2__ Use of property sheet control

----

[&lt;&lt; Toolbar Control](MiniGUIProgGuidePart6Chapter09.md) |
[Table of Contents](README.md) |
[Scroll Window Control &gt;&gt;](MiniGUIProgGuidePart6Chapter11.md)

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
