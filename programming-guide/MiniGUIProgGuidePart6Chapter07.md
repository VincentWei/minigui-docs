# 25 Progress Bar Control

The progress bar is generally used to prompt the progress of a task for the user, and is frequently used for tasks such as copying file, installing software. Calling CreateWindow function with CTRL_PROGRESSBAR as the control class name can create a progress bar. Fig. 25.1 is the typical running effect of a progress bar.

<center>
<img src="%ATTACHURLPATH%/25.1.jpeg" alt="25.1.jpeg"  ALIGN="CENTER" /> <br>
Fig. 25.1 Progress bar control
</center>

## 25.1 Styles of Progress Bar

Progress bar has only the following two styles available:
- PBS_NOTIFY: The progress bar control with this style can generate notification messages.。
- PBS_VERTICAL: Display the progress bar vertically, as shown in Fig. 25.2.

<center>
<img src="%ATTACHURLPATH%/25.2.jpeg" alt="25.2.jpeg"  ALIGN="CENTER" /> <br>
Fig. 25.2 Vertical progress bar control
</center>

The combination of styles commonly used by a progress bar controls is:

```cplusplus
WS_CHILD | WS_VISIBLE | PBS_NOTIFY
```

## 25.2 Messages of Progress Bar
### 25.2.1 Setting Range of Progress Bar

The range of a progress bar is 0 to 100 by default, and an application can set its own progress bar range by calling PBM_SETRANGE message:

```cplusplus
SendMessage (hwndEdit, PBM_SETRANGE, min, max) ;
```

***
[Prompt] The range of a progress bar can be set to be a negative value.
***

### 25.2.2 Setting Step Value of Progress Bar

We can set the step value for a progress bar, and make the progress bar stepping forward when each stage task is complete. The step value is 10 by default, and can be changed by sending PBM_SETSTEP message, as shown in the following:

```cplusplus
SendMessage (hwndEdit, PBM_SETSTEP, 5, 0) ;
```

The above message changes the step value of a progress bar to be 5.

***
[Prompt] The step value of a progress bar can be set to be a negative value.
***

You should set the position of the progress bar as the max value of its range when the step value is a negative and the progress bar will decrease from its max range to min. 

### 25.2.3 Setting Position of Progress Bar

We can also set the current position of a progress bar optionally with PBM_SETPOS message:

```cplusplus
SendMessage (hwndEdit, PBM_SETPOS, 50, 0) ;
```

The above message sets the current position of a progress bar to be 50.

### 25.2.4 Setting Offset Based-on Current Position

We can also set the offset of the new position based on the current position to change the progress position:

```cplusplus
SendMessage (hwndEdit, PBM_DELTAPOS, 10, 0) ;
```

The above message will add 10 to the new position based on the current position, i.e., new position is the current position plus 10.

***
[Prompt] The offset of a progress bar can be set to be a negative value.
***

### 25.2.5 Advancing Position by One Step 

PBM_STEPIT can be sent to advance the current position, and the new position equals the result of the current position plus the step value:

```cplusplus
SendMessage (hwndEdit, PBM_STEPIT, 0, 0) ;
```

***
[Note] The present progress bar control does not provide any messages for getting the current position, the current step increment, and the current position range.
***

## 25.3 Notification Codes of Progress Bar

Progress bar with PBS_NOTIFY style may possibly generate the following notification codes:
- PBN_REACHMAX: Reach the maximum position.
- PBN_REACHMIN: Reach the minimum position.

## 25.4 Sample Program

List 25.1 gives an example of using the progress bar control. This program provides two functions. Calling createProgressWin function will create a main window with a progress bar and then return. We can control the progress bar of the main window in our own program, and call destroyProgressWin function to destroy the progress main window after completing the task. The two functions actually come from MiniGUIExt library of MiniGUI. List 25.1 gives the example of the implementation and the usage of these two functions, and the running effect is as shown in Fig. 25.3. Please refer to progressbar.c of the sample program package mg-samples of this guide for the complete source code.

<center>List 25.1 Example of using progress bar</center>

```cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

static HWND createProgressWin (HWND hParentWnd, char * title, char * label,
        int id, int range)
{
    HWND hwnd;
    MAINWINCREATE CreateInfo;
    int ww, wh;
    HWND hStatic, hProgBar;

    /* 根据窗口客户区宽度计算窗口宽度 */
    /* Calculate the window width according to the width of the window client region */
    ww = ClientWidthToWindowWidth (WS_CAPTION | WS_BORDER, 400);
    /* 根据窗口客户区高度计算窗口高度 */
    /* Calculate the window height according to the height of the window client region */
    wh = ClientHeightToWindowHeight (WS_CAPTION | WS_BORDER, 
            (range > 0) ? 70 : 35, FALSE);
    
    /* 创建主窗口 */
    /* Create the main window */
    CreateInfo.dwStyle = WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_VISIBLE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = title;
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(IDC_WAIT);
    CreateInfo.hIcon = 0;
    /* 该主窗口的窗口过程取默认的主窗口过程 */
    /* The window procedure of the main window is set to 
     * be the default main window procedure
     */
    CreateInfo.MainWindowProc = DefaultMainWinProc;
#ifndef _LITE_VERSION
    CreateInfo.lx = (GetGDCapability (HDC_SCREEN, GDCAP_MAXX) - ww) >> 1;
    CreateInfo.ty = (GetGDCapability (HDC_SCREEN, GDCAP_MAXY) - wh) >> 1;
#else
    CreateInfo.lx = g_rcExcluded.left + (RECTW(g_rcExcluded) - ww) >> 1;
    CreateInfo.ty = g_rcExcluded.top + (RECTH(g_rcExcluded) - wh) >> 1;
#endif
    CreateInfo.rx = CreateInfo.lx + ww;
    CreateInfo.by = CreateInfo.ty + wh;
    CreateInfo.iBkColor = COLOR_lightgray;
    CreateInfo.dwAddData = 0L;
    CreateInfo.hHosting = hParentWnd;

    hwnd = CreateMainWindow (&CreateInfo);
    if (hwnd == HWND_INVALID)
        return hwnd;

    /* 在主窗口中创建提示用静态框控件 */
    /* Create a static control for prompting in the main window */
    hStatic = CreateWindowEx ("static", 
                  label, 
                  WS_VISIBLE | SS_SIMPLE, 
                  WS_EX_USEPARENTCURSOR,
                  IDC_STATIC, 
                  10, 10, 380, 16, hwnd, 0);
    
    /* 在主窗口中创建进度条控件 */
    /* Create the progress bar control in the main window */
    if (range > 0) {
        hProgBar = CreateWindowEx ("progressbar", 
                  NULL, 
                  WS_VISIBLE,
                  WS_EX_USEPARENTCURSOR,
                  id,
                  10, 30, 380, 30, hwnd, 0);
        SendDlgItemMessage (hwnd, id, PBM_SETRANGE, 0, range);
    }
    else
        hProgBar = HWND_INVALID;

    /* 更新控件 */
    /* Update the controls */
    UpdateWindow (hwnd, TRUE);

    /* 返回主窗口句柄 */
    /* Return the handle of the main window */
    return hwnd;
}

static void destroyProgressWin (HWND hwnd)
{
    /* 销毁控件以及主窗口 */
    /* Destroy the controls and the main window  */
    DestroyAllControls (hwnd);
    DestroyMainWindow (hwnd);
    ThrowAwayMessages (hwnd);
    MainWindowThreadCleanup (hwnd);
}

int MiniGUIMain (int argc, const char* argv[])
{
    int i, sum;
    HCURSOR hOldCursor;
    HWND hwnd;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "progressbar" , 0 , 0);
#endif

    /* 设置“沙漏”鼠标，以表示系统正忙 */
    /* Set “sandglass” mouse to indicate the system is busy */
    hOldCursor = SetDefaultCursor (GetSystemCursor (IDC_WAIT));

    /* 创建进度条窗口，指定进度条控件的标识符和范围值 */
    /* Create the progressbar window, and specify the 
     * identifier and range of the progress bar control */
    hwnd = createProgressWin (HWND_DESKTOP, "进度条",
            "正在计算，请稍候...", 100, 2000);

    while (HavePendingMessage (hwnd)) {
         MSG msg;
         GetMessage (&msg, hwnd);
         DispatchMessage (&msg);
    }

    /* 进入长时计算过程，完成大循环时更新进度条控件的位置 */
    /* Begin the long time calculating progress,and 
     * refresh the position of the progressbar when completing 
     * the external loop.
     */
    for (i = 0; i < 2000; i++) {
        unsigned long j;
        
        if (i % 100 == 0) {
            SendDlgItemMessage (hwnd, 100, PBM_SETPOS, i, 0L);
            while (HavePendingMessage (hwnd)) {
                MSG msg;
                GetMessage (&msg, hwnd);
                DispatchMessage (&msg);
            }
        }

        sum = i*5000;
        for (j = 0; j < 500000; j++)
            sum *= j;
        sum += sum;
    }

    /* 销毁进度条窗口 */
    /* Destroy the progressbar window */
    destroyProgressWin (hwnd);
    /* 恢复原有鼠标 */
    /* Recover the original mouse */
    SetDefaultCursor (hOldCursor);

    return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif
```

<center>
<img src="%ATTACHURLPATH%/25.3.jpeg" alt="25.3.jpeg"  ALIGN="CENTER" /> <br>
Fig. 25.3 Example of progress bar control
</center>

-- Main.XiaodongLi - 26 Oct 2009

