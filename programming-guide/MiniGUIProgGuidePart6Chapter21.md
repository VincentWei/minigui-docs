# 39 Independent Scrollbar Control

## 39.1 Definition of independent scrollbar
- Arrow, shaft and thumb are the components of scrollbar control. Some scrollbars don't have arrow, and some don't have shaft and thumb, as shown in Figure 39.1:<br />
<center>Fig. 39.1 Scrollbar structure<br /><br />
              <img src="%ATTACHURLPATH%/scrollbar_specific.gif" alt="scrollbar_specific.gif" width='225' height='167' /> </center>
- Scrollbar is rectangular, it sends message to parent window when mouse clicks on it, and parent window will refresh the content of window and the position of thumb. It also sends message to parent window and do refresh when mouse clicks on arrow.

## 39.2 Types of Scrollbar
There are two kinds of scrollbar: 
- A part of main window or other controls, application specifies the scrollbar is horizontal or vertical by changing the style, WS_HSCROLL or WS_VSCROLL. Main window or other controls can have both of these styles.
- Independent scrollbar, class name is CTRL_SCROLLBAR. Application specifies the scrollbar is horizontal or vertical by selecting SBS_HORZ or SBS_VERT when it is creating scrollbar control. It can only chose one of the styles.

The first one is not the topic of this chapter, but it is closely connected independent scrollbar, so we mentioned it.

## 39.3 Styles of Independent Scrollbar

Independent scrollbar has the following styles:
<center>
Table 39.1 The styles of independent scrollbar

| *Style Identifier* | *Meaning* |
| SBS_HORZ | Create a horizontal scrollbar. The range of scrollbar is decided by the arguments (x, y, w, h) of CreateWindowEx2 when don't specify SBS_BOTTOMALIGN or SBS_TOPALIGN. |
| SBS_VERT | Create a vertical scrollbar.  The range of scrollbar is decided by the arguments (x, y, w, h) of CreateWindowEx2 when don't specify SBS_LEFTALIGN or SBS_RIGHTALIGN. |
| SBS_BOTTOMALIGN | Be used with SBS_HORZ. Put horizontal scrollbar on the bottom of the range which is specified by CreateWindowEx2. |
| SBS_TOPALIGN | Be used with SBS_HORZ. Put horizontal scrollbar on the top of the range which is specified by CreateWindowEx2. |
| SBS_LEFTALIGN | Be used with SBS_VERT. Put vertical scrollbar on the left of the range which is specified by CreateWindowEx2. |
| SBS_RIGHTALIGN | Be used with SBS_VERT. Put vertical scrollbar on the right of the range which is specified by CreateWindowEx2. |
| SBS_NOARROWS | No arrow, can't be used with SBS_NOSHAFT | 
| SBS_NOSHAFT | No shaft, can't be used with SBS_NOARROWS | 
| SBS_FIXEDBARLEN | Thumb of horizontal or vertical scrollbar is fixed length | 
| SBS_NOTNOTIFYPARENT | Send message to parent window, not notification code. It sends notification code in default | 
</center>

## 39.4 Messages of Independent Scrollbar

Application can send following messages to scrollbar control:
- Get/set data information of scrollbar: SBM_GETSCROLLINFO, SBM_SETSCROLLINFO
- Get /set current position of thumb: SBM_GETPOS, SBM_SETPOS
- Get/set scroll range: SBM_GETRANGE, SBM_SETRANGE
- Get/set scroll range and redraw immediately: SBM_SETRANGEREDRAW
- Enable/disable arrow: SBM_ENABLE_ARROW

### 39.4.1 Get Scrollbar Information

Application can get scrollbar's information (max/min value, pages of scrollbar and current position) by sending SBM_GETSCROLLINFO and wParam argument which is SCROLLINFO * pointer to scrollbar. The information is stored in the memory pointed by wParam.

```cplusplus
/*
* Scroll bar information structure.
*/
typedef struct _SCROLLINFO
{
        /** Size of the structrue in bytes */
        UINT    cbSize;
        /**  
        * A flag indicates which fields contain valid values, 
        * can be OR'ed value of the following values:
        *      - SIF_RANGE\n
        *        Retrives or sets the range of the scroll bar.
        *      - SIF_PAGE\n
        *        Retrives or sets the page size of the scroll bar.
        *      - SIF_POS\n
        *        Retrives or sets the position of the scroll bar.
        *      - SIF_DISABLENOSCROLL\n
        *        Hides the scroll when disabled, not implemented so far.
        */
        UINT    fMask;
        /** The minimum position value of the scroll bar */
        int     nMin;
        /** The maximum position value of the scroll bar */
        int     nMax;
        /** The page size of the scroll bar */
        UINT    nPage;
        /** The position value of the scroll bar */
        int     nPos;
} SCROLLINFO, *PSCROLLINFO;
```
fMask in SBM_GETSCROLLINFO structure specifies the information which can be got by sending SBM_GETSCROLLINFO message, fMask's value can be:
<center>
| *Information Identifier* | *Meaning* |
|SIF_RANGE | Get values range of scrollbar |
|SIF_PAGE | Get the pages of scrollbar |
|SIF_POS  | Get scrollbar's current position |
|SIF_ALL | Get all information |
</center>

The following codes can get all information of scrollbar

```cplusplus
SCROLLINFO scinfo = {0};
scinfo.fMask = SIF_ALL;
SendMessage (hwnd_scrollbar, SBM_GETSCROLLINFO, (wParam)&scinfo,  0);
```

### 39.4.2 Set Information of Scrollbar

We can send SBM_SETSCROLLINFO to scrollbar control to set information of scrollbar. wParam is a pointer of SCROLLINFO structure, it stores the scrollbar information which needs to be stored. IParam is used to determine to (TRUE) or not to (FALSE) redraw immediately.
 
The following sample is setting scrollbar's information and not redrawing immediately:

```cplusplus
SCROLLINFO scinfo = {0};
scinfo.fMask = SIF_ALL;
scinfo.nMin = 0;
scinfo.nMax = 10;
scinfo.nPage = 2;
scinfo.nPos = 0;
BOOL redraw = FALSE;
SendMessage (hwnd_scrollbar, SBM_SETCROLLINFO, (wParam)&scinfo,  redraw);
```

### 39.4.3 Get Current Position of Thumb

We can send SBM_GETPOS message to scrollbar to get current position of thumb. Example is as follow:
```cplusplus
int pos = SendMessage (hwnd_scrollbar, SBM_GETPOS, 0, 0);
```

### 39.4.4 Set The Position of Thumb
We can send SBM_SETPOS message to scrollbar to set position of thumb. Target position is stored in wParam. IParam is used to determine to (TRUE) or not to (FALSE) redraw immediately.

```cplusplus
int pos = 10;
SendMessage (hwnd_scrollbar, SBM_SETPOS, pos, TRUE);
```

### 39.4.5 Get Scroll Range of Scrollbar

We can send SBM_GETRANGE message to get the scroll range of scrollbar. wParam stores min range and IParam stores max range.

```cplusplus
int min, max;
SendMessage (hwnd_scrollbar, SBM_GETRANGE, &min, &max);
```

### 39.4.6 Set Scroll Range of Scrollbar

We can send SBM_SETRANGE message to set the scroll range of scrollbar. wParam/IParam is min/max range to set. This message will not redraw scrollbar immediately.

The following codes set the scroll range of scroll bar from 0 to 100. But you can only see the change after other message or event redraws UI.

```cplusplus
SendMessage (hwnd_scrollbar, SBM_SETRANGE, 0, 100);
```

### 39.4.7 Set Scroll Range of Scrollbar and Redraw Immediately

We can send SBM_SETRANGEREDRAW message if we want to redraw scrollbar immediately after set the scroll range. wParam/IParam is min/max range to set.

The following codes set the scroll range of scroll bar from 0 to 100 and redraw immediately.
```cplusplus
SendMessage (hwnd_scrollbar, SBM_SETRANGEREDRAW, 0, 100);
```

### 39.4.8 Enable or Disable Arrow

Sending SBM_ENABLE_ARROW message can enable or disable arrow. Disable means the scrollbar can't scroll to the direction which is specified by disabled arrow. Arrow is enabled (disabled) when IParam is TRUE (FALSE). wParam's value is as follow:
<center>
| *Arrow Identifier* | *Meaning* |
|SB_ARROW_LTUP | Left arrow key of horizontal scrollbar or up arrow key of vertical scrollbar |
|SB_ARROW_BTDN | Right arrow key of horizontal scrollbar or down arrow key of vertical scrollbar |
|SB_ARROW_BOTH | All arrow keys |
</center>

The following codes disable all arrows of scrollbar:
```cplusplus
SendMessage (hwnd_scrollbar, SBM_ENABLE_ARROW, SB_ARROW_BOTH, FALSE);
```

## 39.5 Configurable Properties of Scrollbar

The following properties of scrollbar can be set by GetWindowElementAttr, SetWindowElementAttr, GetWindowElementPixelEx and SetWindowElementPixelEx functions:

<center>
Table 39.4 Notification codes table

| *Property Identifier* | *Meaning* | 
|WE_MAINC_THREED_BODY | Draw the colors of shaft and thumb |
|WE_FGC_THREED_BODY | Draw the color of arrow |
|WE_FGC_DISABLED_ITEM | Draw the color of disabled arrow |
|WE_METRICS_SCROLLBAR | The size of scrollbar, that is, the height of horizontal scrollbar or the width of vertical scrollbar |
</center>

The following codes is an example for above properties:

```cplusplus
    DWORD color_3d, fgc_3d, fgc_dis;
    gal_pixel old_brush_color;

    //Get color value for each part of scrollbar
    color_3d = GetWindowElementAttr(hWnd, WE_MAINC_THREED_BODY);
    fgc_3d = GetWindowElementAttr(hWnd, WE_FGC_THREED_BODY);
    fgc_dis = GetWindowElementAttr(hWnd, WE_FGC_DISABLED_ITEM);

    //Draw shaft of scrollbar
    old_brush_color = SetBrushColor(hdc,
                           RGBA2Pixel(hdc,GetRValue(color_3d),
                               GetGValue(color_3d), GetBValue(color_3d),
                               GetAValue(color_3d)));
     FillBox(hdc, rect.left, rect.top, RECTW(rect), RECTH(rect));
     SetBrushColor(hdc, old_brush_color);

     //Draw arrow of scrollbar
     draw_3dbox(hdc, &rect, color_3d,
                        bn_status | LFRDR_3DBOX_THICKFRAME | LFRDR_3DBOX_FILLED);

     if(sb_status & SBS_DISABLED_LTUP || sb_status & SBS_DISABLED)
           draw_arrow(hWnd, hdc, &rect, fgc_dis, LFRDR_ARROW_LEFT);
      else
           draw_arrow(hWnd, hdc, &rect, fgc_3d, LFRDR_ARROW_LEFT);
```

## 39.6 Notification Codes of Scrollbar

All notification codes of scrollbar are in the following table:

<center>
Table 39.5 Notification codes table

| *Notification Code Identifier* | *Meaning* |
|SB_LINEUP | Vertical scrollbar scrolls up one line |
|SB_LINEDOWN | Vertical scrollbar scrolls down one line |
|SB_PAGEUP | Vertical scrollbar scrolls up one page |
|SB_PAGEDOWN | Vertical scrollbar scrolls down one page |
|SB_LINELEFT | Horizontal scrollbar scrolls left one column |
|SB_LINERIGHT | Horizontal scrollbar scrolls right one column |
|SB_PAGELEFT | Horizontal scrollbar scrolls left one page |
|SB_PAGERIGHT | Horizontal scrollbar scrolls right one page |
|SB_THUMBPOSITION | Send the position of thumb to parent window by this notification code when mouse left button presses, drags and releases thumb |
|SB_THUMBTRACK | Keep sending the position of thumb to parent window by this notification code when mouse button is pressing and dragging the thumb |
|SB_TOP | Thumb arrives at left-most (top-most) of horizontal (vertical) scrollbar, that is, get the min value of scrollbar |
|SB_BOTTOM | Thumb arrives at right-most (bottom) of horizontal (vertical) scrollbar, that is, get the max value of scrollbar |
</center>

- After scrollbar specifies SBS_NOTNOTIFYPARENT style, parent window of horizontal (vertical) scrollbar will receive MSG_HSCROLL (MSG_VSCROLL) message. wParam is notification id, IParam is current position of thumb, curPos, when id is SB_THUMBPOSITION or SB_THUMBTRACK. In other cases, IParam doesn't have meaning.
- When scrollbar doesn't specify SBS_NOTNOTIFYPARENT style, parent window of scrollbar will receive notification code. wParam includes control ID and notification code. When notification code is SB_THUMBPOSITION or SB_THUMBTRACK, parent window can get current position of thumb, curPos, by sending SBM_GETPOS. Of course, the control doesn't send MSG_COMMAND to parent window if you have invoked SetNotificationCallback function to set callback function of scrollbar control, it invokes given callback function directly.

### 39.6.1 Trigger of Notification Message
Scrollbar can receive events of mouse and keyboard and trigger different notification message accroding to different situations.
- It triggers different notification message when mouse clicks different part of scrollbar. It is important to note, when dragging thumb by using mouse left button, scrollbar keeps sending SB_THUMBTRACK message, and it sends SB_THUMBPOSITION after mouse left button is released. The messages which are triggered by the part of scrollbar are as follow:

<center>Fig. 39.2 notification messages which are triggered by mouse<br /><br />
     <img src="%ATTACHURLPATH%/scrollbar_notif.gif" alt="scrollbar_notif.gif" width='403' height='246' /> </center>
- The key of keyboard triggers corresponding notification message, see the following table:
<center>
Table 39.6 Notification Code table
| *Key* | *Notification Code* |
| PAGEUP | Horizontal scrollbar sends SB_PAGELEFT; Vertical scrollbar sends SB_PAGEUP |
| PAGEDOWN | Horizontal scrollbar sends SB_PAGERIGHT ；Vertical scrollbar sends SB_PAGEDOWN |
| UpArrow | Vertical scrollbar sends SB_LINEUP |
| LeftArrow | Horizontal scrollbar sends SB_LINELEFT |
| DownArrow | Vertical scrollbar sends SB_LINEDOWN |
| RightArrow | Horizontal scrollbar sends SB_LINERIGHT |
</center>

## 39.7 Sample Program

The following codes show how to create scrollbar with multiple styles. By operating mouse or keyboard, you can do many operations on scrollbar, for example, clicking, draging and so on.  To make the demo more vivid, we put a circle and a box on right of the window. The circle will become larger or smaller and the box will moved up or down, just follow scrollbar's control. Figure 39.3 is the screenshot, the codes are from scrollbar_ctrl.c in mg-samples, please see this file for full codes.
<center> List 39.1 Scrollbar sample codes </center>
```cplusplus
#include <stdio.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#ifdef _LANG_ZHCN
#include "scrollbar_ctrl_res_cn.h"
#elif defined _LANG_ZHTW
#include "scrollbar_ctrl_res_tw.h"
#else
#include "scrollbar_ctrl_res_en.h"
#endif

/** define scrollbar data */
#define SB_MAX 20
#define SB_MIN 0
#define SB_PAGE 6

/** define circle data */
#define CC_CENTER_X    400
#define CC_CENTER_Y    100
#define CC_RADIUS_MAX   50
#define CC_RADIUS_MIN   0

/** define box data */
#define BOX_WIDTH   40
#define BOX_HEIGHT  20
#define BOX_Y_MAX   300
#define BOX_Y_MIN   200

/** x position of separator */
#define SEP   300

/** radius of circle */
int _radius;

/** y position of box */
int _box_pos_y;

/** invalidate rect */
RECT _rect_invalid;

static int ScrollbarProc(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
    /** IDC of SCROLLBAR control */
    static int _my_scroll_idc = 100;

    /** scrollbar handle of main window  */
    static HWND hwnd_sb_main;

    /** scrollbar handle of control */
    HWND hwnd_sb_ctrl;

    switch (message)
    {
        case MSG_CREATE:
            {
                _rect_invalid.left   = SEP;
                _rect_invalid.top    = 0;
                _rect_invalid.right  = g_rcScr.right;
                _rect_invalid.bottom = g_rcScr.bottom;

                SCROLLINFO scinfo = {0};
                scinfo.fMask = SIF_ALL;
                scinfo.nMin = SB_MIN;
                scinfo.nMax = SB_MAX;
                scinfo.nPage = SB_PAGE;
                scinfo.nPos = SB_MIN;

                calc_circle_pos (scinfo.nPos);
                calc_box_pos (scinfo.nPos);

                /** classic VSCROLL with SBS_NOTNOTIFYPARENT */

                hwnd_sb_main = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE |
                        SBS_VERT | SBS_LEFTALIGN
                        | SBS_NOTNOTIFYPARENT
                       ,
                        0,
                        ++_my_scroll_idc,
                        20, 50, 20, 150, hwnd, 
                        "classic", 0,
                        0);

                SendMessage (hwnd_sb_main, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_main, MSG_SETFOCUS, 0, 0);

                /** flat VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE |
                        SBS_VERT | SBS_LEFTALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        43, 50, 20, 150, hwnd, 
                        "flat", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** fashion VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE |
                        SBS_VERT | SBS_LEFTALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        66, 50, 20, 150, hwnd, 
                        "fashion", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** tiny VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE |
                        SBS_VERT | SBS_LEFTALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        92, 50, 20, 150, hwnd, 
                        "tiny", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** classic NOSHAFT VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOSHAFT | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        120, 50, 20, 34, hwnd, 
                        "classic", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** flat NOSHAFT VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOSHAFT | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        140, 50, 20, 34, hwnd, 
                        "flat", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** fashion NOSHAFT VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOSHAFT | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        160, 50, 20, 34, hwnd, 
                        "fashion", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** tiny NOSHAFT VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOSHAFT | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        184, 50, 20, 34, hwnd, 
                        "tiny", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** classic NOARROW VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOARROW | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        210, 50, 20, 150, hwnd, 
                        "classic", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** flat NOARROW VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOARROW | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        232, 50, 20, 150, hwnd, 
                        "flat", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** fashion NOARROW VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOARROW | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        254, 50, 20, 150, hwnd, 
                        "fashion", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** tiny NOARROW VSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_VERT | SBS_NOARROW | SBS_LEFTALIGN 
                       ,
                        0,
                        ++_my_scroll_idc,
                        276, 50, 20, 150, hwnd, 
                        "tiny", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** classic HSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_HORZ 
                        | SBS_TOPALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        20, 220, 150, 20, hwnd, 
                        "classic", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** flat HSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_HORZ 
                        | SBS_TOPALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        20, 240, 150, 20, hwnd, 
                        "flat", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** fashion HSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_HORZ 
                        | SBS_TOPALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        20, 260, 150, 20, hwnd, 
                        "fashion", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);

                /** tiny HSCROLL */

                hwnd_sb_ctrl = CreateWindowEx2 (CTRL_SCROLLBAR, "",
                        WS_VISIBLE | SBS_HORZ 
                        | SBS_TOPALIGN
                       ,
                        0,
                        ++_my_scroll_idc,
                        20, 280, 150, 20, hwnd, 
                        "tiny", 0,
                        0);

                SendMessage (hwnd_sb_ctrl, SBM_SETSCROLLINFO, (WPARAM)&scinfo, TRUE);
                SendMessage (hwnd_sb_ctrl, MSG_SETFOCUS, 0, 0);
            }
            break;

        case MSG_COMMAND:
            {
                int code = HIWORD(wParam);
                HWND scroll = (HWND)lParam;
                int pos = 0;

                switch (code) 
                {
                    case SB_LINELEFT:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            SendMessage (scroll, SBM_SETPOS, --pos, TRUE);
                        }

                        break;

                    case SB_LINERIGHT:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            SendMessage (scroll, SBM_SETPOS, ++pos, TRUE);
                        }
                        break;

                    case SB_PAGELEFT:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            pos -= SB_PAGE;
                            SendMessage (scroll, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_PAGERIGHT:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            pos += SB_PAGE;
                            SendMessage (scroll, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_LINEUP:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            SendMessage (scroll, SBM_SETPOS, --pos, TRUE);
                        }

                        break;

                    case SB_LINEDOWN:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            SendMessage (scroll, SBM_SETPOS, ++pos, TRUE);
                        }
                        break;

                    case SB_PAGEUP:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            pos -= SB_PAGE;
                            SendMessage (scroll, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_PAGEDOWN:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);

                            pos += SB_PAGE;
                            SendMessage (scroll, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_THUMBPOSITION:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);
                        }
                        break;

                    case SB_THUMBTRACK:
                        {
                            pos = SendMessage (scroll, SBM_GETPOS, 0, 0);
                        }
                        break;

                    case SB_TOP:
                        {
                            pos = SB_MIN;
                        }
                        break;

                    case SB_BOTTOM:
                        {
                            pos = SB_MAX;
                        }
                        break;

                    default:
                        break;
                }

                draw_shape (hwnd, pos);
            }
            break;

        case MSG_HSCROLL:
            {
                int pos = 0;
                switch (wParam)
                {
                    case SB_LINELEFT:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            SendMessage (hwnd_sb_main, SBM_SETPOS, --pos, TRUE);
                        }

                        break;

                    case SB_LINERIGHT:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            SendMessage (hwnd_sb_main, SBM_SETPOS, ++pos, TRUE);
                        }
                        break;

                    case SB_PAGELEFT:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            pos -= SB_PAGE;
                            SendMessage (hwnd_sb_main, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_PAGERIGHT:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            pos += SB_PAGE;
                            SendMessage (hwnd_sb_main, SBM_SETPOS, pos, TRUE);
                        }
                        break;
                    case SB_THUMBPOSITION:
                        {
                            pos = (int)lParam;
                        }
                        break;

                    case SB_THUMBTRACK:
                        {
                            pos = (int)lParam;
                        }
                        break;

                    case SB_TOP:
                        {
                            pos = SB_MIN;
                        }
                        break;

                    case SB_BOTTOM:
                        {
                            pos = SB_MAX;
                        }
                        break;

                    default:
                        break;
                }
                draw_shape (hwnd, pos);
            }
            break;

        case MSG_VSCROLL:
            {
                int pos = 0;
                switch (wParam)
                {
                    case SB_LINEUP:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            SendMessage (hwnd_sb_main, SBM_SETPOS, --pos, TRUE);
                            
                        }

                        break;

                    case SB_LINEDOWN:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            SendMessage (hwnd_sb_main, SBM_SETPOS, ++pos, TRUE);
                        }
                        break;

                    case SB_PAGEUP:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            pos -= SB_PAGE;
                            SendMessage (hwnd_sb_main, SBM_SETPOS, pos, TRUE);
                        }
                        break;

                    case SB_PAGEDOWN:
                        {
                            pos = SendMessage (hwnd_sb_main, SBM_GETPOS, 0, 0);

                            pos += SB_PAGE;
                            SendMessage (hwnd_sb_main, SBM_SETPOS, pos, TRUE);
                        }
                        break;
                    case SB_THUMBPOSITION:
                        {
                            pos = (int)lParam;
                        }
                        break;

                    case SB_THUMBTRACK:
                        {
                            pos = (int)lParam;
                        }
                        break;

                    case SB_TOP:
                        {
                            pos = SB_MIN;
                        }
                        break;

                    case SB_BOTTOM:
                        {
                            pos = SB_MAX;
                        }
                        break;
                    default:
                        break;
                }
                draw_shape (hwnd, pos);
            }
            break;

        case MSG_PAINT:
            {
                HDC hdc = BeginPaint(hwnd); 

                /** separator */
                MoveTo (hdc, SEP, 0);
                LineTo (hdc, SEP, g_rcScr.bottom);

                /** circle */
                Circle (hdc, CC_CENTER_X, CC_CENTER_Y, _radius);

                /** top and bottom line of box */
                MoveTo (hdc, SEP + 20, BOX_Y_MIN);
                LineTo (hdc, SEP + 20 + BOX_WIDTH + 40, BOX_Y_MIN);

                MoveTo (hdc, SEP + 20, BOX_Y_MAX);
                LineTo (hdc, SEP + 20 + BOX_WIDTH + 40, BOX_Y_MAX);

                /** box */
                SetBrushColor (hdc, PIXEL_black);
                FillBox (hdc, SEP + 40, _box_pos_y, BOX_WIDTH, BOX_HEIGHT);

                EndPaint (hwnd, hdc);
            }
            break;

        case MSG_CLOSE:
            {
                DestroyMainWindow (hwnd);
                PostQuitMessage (hwnd);
                return 0;
            }
    }

    return DefaultMainWinProc(hwnd, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "scrollbar" , 0 , 0);
#endif

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = SCB_ST_CAP;
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = ScrollbarProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = g_rcScr.right;
    CreateInfo.by = g_rcScr.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindowEx (&CreateInfo, "flat", 0, 0, 0);

    if (hMainWnd == HWND_INVALID)
    {
        return -1;
    }

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);

    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
```
<br />
<center>Fig. 39.3 Scrollbar control<br /><br />
     <img src="%ATTACHURLPATH%/scrollbar_sample.png" alt="scrollbar_sample.png" width='800' height='604' /> </center>

-- Main.XiaodongLi - 26 Oct 2009

