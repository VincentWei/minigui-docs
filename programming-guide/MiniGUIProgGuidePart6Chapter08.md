# 26 Track Bar Control

The track bar is generally used for adjusting brightness, volume, etc. In the situation for adjusting the value in a range, track bar can be used. Calling CreateWindow function with CTRL_TRACKBAR as the control class name can create a track bar. Fig. 26.1 shows the typical running effect of a track bar.

<center>
<img src="%ATTACHURLPATH%/26.1.jpeg" alt="26.1.jpeg"  ALIGN="CENTER" /> <br>
Fig. 26.1 Track bar control
</center>

## 26.1 Styles of Track Bar

The frequently used combination of styles for a track bar is:

```cplusplus
WS_CHILD | WS_VISIBLE | TBS_NOTIFY
```

Specifying TBS_NOTIFY style can make a track bar generating notification messages.

A track bar is horizontal by default. To create a vertical track bar, you can specify TBS_VERTICAL style. The track bar in Fig. 26.2 is a vertical track bar.


<center>
<img src="%ATTACHURLPATH%/26.2.jpeg" alt="26.2.jpeg"  ALIGN="CENTER" /> <br>
Fig. 26.2 A vertical track bar
</center>

Other styles of track bar are illustrated as follow:
- TBS_TIP: Display the tip string beside the track bar (as “Min” and “Max” in Fig. 26.1). A track bar with this style will also display the current position value in the center of the control.
- TBS_NOTICK: Do not display the tick lines.
- TBS_BORDER: This style makes a track bar having bordered, which is not used frequently.

## 26.2 Messages of Track Bar

Messages of a track bar are relatively simple, as summarized in the following:
- TBM_SETRANGE: Set the minimum and maximum positions for the track bar through wParam and lParam parameters. The default range is 0~10.
- TBM_GETMIN: Get the minimum position for the track bar.
- TBM_GETMAX: Get the maximum position for the track bar.
- TBM_SETMIN: Set the minimum position for the track bar.
- TBM_SETMAX: Set the maximum position for the track bar.
- TBM_SETLINESIZE: Sets the step value by wParam parameter. When the user presses up or down arrow key during the track bar has input focus, the slider will be moved up or down the step value. The default step value is 1.
- TBM_GETLINESIZE: Gets the step value of the slider.
- TBM_SETPAGESIZE: Set the page step value by wParam parameter. When the user presses PageUp or PageDown key during the track bar has input focus, the slider will be moved up or down the page step value. The default page step value is 1.
- TBM_GETPAGESIZE: Get the page step value of the track bar.
- TBM_SETPOS: Set the position of the slider.
- TBM_GETPOS: Get the position of the slider.
- TBM_SETTICKFREQ: Set the interval value of tick marks in a track bar, the default interval is 1.
- TBM_GETTICKFREQ: Get the interval value of tick marks in a track bar.
- TBM_SETTIP: Set the tip string at the minimum and maximum positions.
- TBM_GETTIP: Set the tip strings at the minimum and maximum positions.

## 26.3 Notification Codes of Track Bar

The track bar with TBS_NOTIFY style may generate the following notification codes:
- TBN_CHANGE: The position of the slider has changed.
- TBN_REACHMAX: The slider has reached the maximum position.
- TBN_REACHMIN: The slider has reached the minimum position.

## 26.4 Sample Program

List 26.1 gives an example program of track bar. The program draws a circle with the corresponding size according to the current slider position. When the user changes the position of the slider, the circle will also be refreshed. The running effect of the program is shown in Fig. 26.3. Please refer to trackbar.c file of the demo program package mg-samples of this guide for the complete source code. 

<center>List 26.1 Use of track bar</center>

```cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

static int radius = 10;
static RECT rcCircle = {0, 60, 300, 300};

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == TBN_CHANGE) {

        /* When the position of the slider has changed, 
         * save the current position, and inform the main window to redraw */
        radius = SendMessage (hwnd, TBM_GETPOS, 0, 0);
        InvalidateRect (GetParent (hwnd), &rcCircle, TRUE);
    }
}

static int TrackBarWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HWND hwnd;
    switch (message) {
    case MSG_CREATE:
        /* Create a track bar */
        hwnd = CreateWindow (CTRL_TRACKBAR, 
                          "", 
                          WS_VISIBLE | TBS_NOTIFY, 
                          100, 
                          10, 10, 280, 50, hWnd, 0);

        /* Set the range, step vaue, interval value and current position */
        SendMessage (hwnd, TBM_SETRANGE, 0, 100);
        SendMessage (hwnd, TBM_SETLINESIZE, 1, 0);
        SendMessage (hwnd, TBM_SETPAGESIZE, 10, 0);
        SendMessage (hwnd, TBM_SETTICKFREQ, 10, 0);
        SendMessage (hwnd, TBM_SETPOS, radius, 0);

        /* Set the notification callback function of the slider */
        SetNotificationCallback (hwnd, my_notif_proc);
        break;

    case MSG_PAINT:
    {
        HDC hdc = BeginPaint (hWnd);

        /* Draw a circle with radius of the the current position of the slider */
        ClipRectIntersect (hdc, &rcCircle);
        Circle (hdc, 140, 120, radius);

        EndPaint (hWnd, hdc);
        return 0;
    }

    case MSG_DESTROY:
        DestroyAllControls (hWnd);
        return 0;

    case MSG_CLOSE:
        DestroyMainWindow (hWnd);
        PostQuitMessage (hWnd);
        return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* Following codes to create the main window are omitted */
```

<center>
<img src="%ATTACHURLPATH%/26.3.jpeg" alt="26.3.jpeg"  ALIGN="CENTER" /> <br>
Fig. 26.3 Use of track bar
</center>


-- Main.XiaodongLi - 26 Oct 2009

