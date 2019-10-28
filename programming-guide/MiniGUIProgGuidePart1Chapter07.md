# Scrollbar

## Concept of Scrollbar

__NOTE__ The scrollbar in this chapter is a part of MiniGUI main window and
controls. In MiniGUI 3.0, independent scrollbar control is added, please refer
to [Chapter 39](MiniGUIPGENV301Chapter38) in this guide for details.

Scrollbar is one of the best functions in GUI, which is easy to use and
provides good effect of vision feedback. You can use scrollbar to display any
thing - whatever text, graph, table, database record, image, or web page, if
only the needed space of which exceeds the display region of the window.

Both vertical-direction (for moving up and down) and horizontal-direction (for
moving right and left) scrollbars are available. The user can use mouse to
click on the arrows or in the region between the arrows of the scrollbar, here,
the movement of the thumb in the scrollbar is proportional to the movement of
the displayed information in the whole file. The user can also use mouse to
drag the thumb to a specified position. Figure 1 shows the suggested using
method of the vertical scrollbar.


##### Figure 1 Suggested using method of the vertical scrollbar

Sometimes, the programs fell difficult to understand the scrolling concept,
because their opinion is different from that of the users: the user intends to
see the lower part of the file by scrolling downward; however, the program
actually moves the file upward relative to the display window. MiniGUI is
according to the user’s opinion: scrolling upward means moving to the start of
the file; scrolling downwards means moving to the end of the file.

It is easy to include horizontal or vertical scrollbar in the application. The
program need only to include window style `WS_VSCROL` and/or `WS_HSCROLL` in 
the 
third argument of `CreateWindow` or `CreateMainWindow`. These scrollbars are
commonly placed in the right side and bottom side of the window, extending to
the whole length or width of the display region. The client area does not
include the space filled by scrollbar. If you want to set scrollbar at the left
side of the window, please use `WS_EX_LEFTSCROLLBAR` extended style.

In MiniGUI, mouse click is automatically transformed into corresponding
message; however, you must treat the keyboard message by yourself.

## Enabling or Disabling a Scrollbar

```
```
`EnableScrollBar` function can be used to enable or disable the scrollbar, and
its second parameter specifies which (vertical or horizontal) scrollbar will be
operated.

## Range and Position of a Scrollbar

Each scrollbar has a related “range” (which is a pair of integer, representing
the minimum and the maximum) and “position” (which is the position of thumb in
the range). When the thumb is positioned at the top (or left) of the scrollbar,
the position of the scroll bar is the minimum of the range; when the thumb is
positioned at the bottom (or right) of the scrollbar, the position of the
scroll bar is the maximum of the range.

In a default case, the range of the scrollbar is from 0 (top or left) to 100
(bottom or right), while we can also change the range to values, which are easy
to treat by a program:

```
```

The argument Bar is `SB_VERT` or `SB_HORZ`, and `nMin` and `nMax` is the 
minimum and
maximum of the range, respectively. If you want MiniGUI redraw the scrollbar
according to the new range, `bRedraw` should be set to `TRUE` (if you recall
other 
functions which influence the position of the scrollbar after recalling
`SetScrollRange`, `bRedraw` should be set to `FALSE` to prevent the scrollbar
from 
being redrew excessively). The position of the thumb is always discrete
integer. For example, a scrollbar with range from 0 to 4 has five positions of
thumb, as shown in Figure 2.


##### Figure 2 A scrollbar with range from 0 to 4 has five positions of thumb

When the scrollbar is used in a program, the program together with MiniGUI is
in charge of maintaining the scrollbar and updating the position of the thumb.
Following is the handling of the scrollbar by MiniGUI:

Handling all the scrollbar mouse events.
- When the user drags the thumb in the scrollbar, move the thumb.
- Sending scrollbar message to the window procedure of the window containing
the scrollbar. Following are the tasks remained for the program:
- Initializing the range and position of the scrollbar.
- Handling the scrollbar message in the window procedure.
- Refreshing the position of the scroll thumb in the scrollbar.
- Changing the content in the display region responding the change of the
scrollbar.

## Messages of Scrollbar

When the user clicks the scrollbar or drags the thumb by mouse, MiniGUI sends
message of `MSG_VSCROLL` (for moving up and down) and `MSG_HSCROLL` (for moving
left and right) to the window procedure.

Like all other messages, `MSG_VSCROLL` and `MSG_HSCROLL` also have message
parameter `lParam` and `wParam`. In most cases, we can ignore the parameter
`lParam`. 

`WParam` is a value, which specifies the operation to the scrollbar by the
mouse. 
The value is regarded as a “Notification code”. The notification code is
defined with a prefix “SB_“. Table 1 illustrates the notification codes
defined by MiniGUI.

##### Table 1 The scrollbar notification codes defined by MiniGUI

| *Notification code identifier* | *Meaning* |
| --------------------------------|-----------|
| `SB_LINEUP` | Click once the up arrow in the vertical scrollbar by mouse. |
| `SB_LINEDOWN` | Click once the down arrow in the vertical scrollbar by mouse. |
| `SB_LINELEFT` | Click once the left arrow in the horizontal scrollbar by mouse. |
| `SB_LINERIGHT` | Click once the right arrow in the horizontal scrollbar by mouse. |
| `SB_PAGEUP` | Click once the region between the up arrow and the thumb of the vertical scrollbar by mouse. |
| `SB_PAGEDOWN` | Click once the region between the down arrow and the thumb of the vertical scrollbar by mouse. |
| `SB_PAGELEFT` | Click once the region between the left arrow and the thumb of the horizontal scrollbar by mouse. |
| `SB_PAGERIGHT` | Click once the region between the right arrow and the thumb of the horizontal scrollbar by mouse. |
| `SB_THUMBTRACK` | Message received by the window when the user drags the thumb. It should be noted that the value passed through `lParam` presents the corresponding numerical value. |
| `SB_THUMBPOSITION` | The user finished dragging the thumb. |

The identifiers including `LEFT` and `RIGHT` are used to horizontal scrollbar,
and 
the identifiers including `UP` and `DOWN` is used to vertical scrollbar. The
identifiers generated by the mouse clicking in different regions of the
scrollbar are shown in Figure 3.

##### Figure 3 Identifiers generated by the mouse clicking in different regions
of the scrollbar

Program can receive multiple scrollbar messages if you press the mouse button
at many different scrollbar parts.

When you put the mouse cursor on the thumb and press the mouse button, you can
move the thumb. Scrollbar message including notification code of 
`SB_THUMBTRACK` 
is thus generated. When `wParam` is `SB_THUMBTRACK`, `lParam` is the present
position 
when the user drags the thumb. This position is between the minimum and the
maximum. As for other scrollbar operations, `lParam` should be ignored.

For providing feedback to the user, window system moves the thumb when you move
it with mouse, and at the same time your program will receive message of
`SB_THUMBTRACK`. However, if you do not recall `SetScrollPos` to handle 
messages of
`SB_THUMBTRACK` or `SB_THUMBPOSITION`, the thumb will jump back to its original
position after the user releases the mouse button.

Program can handle message of `SB_THUMBTRACK`. If the message of 
`SB_THUMBTRACK` is
handled, you need move the content in the display region when the user drags
the thumb.

## Sample Program

List 1 presents a simple scrollbar-handling program. The complete code of this
program is available in scrollbar.c in the sample program package mg-samples.

##### List 1 Scrollbar and its handling

```
```
Figure 4 is the running effect of the program in List 1.


##### Figure 4 Handling of scrollbar

----

[&lt;&lt; Menu](MiniGUIProgGuidePart1Chapter06.md) |
[Table of Contents](README.md) |
[Keyboard and Mouse &gt;&gt;](MiniGUIProgGuidePart1Chapter08.md)

[Release Notes for MiniGUI 3.2]:
/supplementary-docs/Release-Notes-for-MiniGUI-3.2.md 
[Release Notes for MiniGUI 4.0]:
/supplementary-docs/Release-Notes-for-MiniGUI-4.0.md 
[Showing Text in Complex or Mixed Scripts]:
/supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md 
[Supporting and Using Extra Input Messages]:
/supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md 
[Using `CommLCD` `NEWGAL` Engine and Comm `IAL` Engine]:
/supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md 
[Using Enhanced Font Interfaces]:
/supplementary-docs/Using-Enhanced-Font-Interfaces.md 
[Using Images and Fonts on System without File System]:
/supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md 
[Using `SyncUpdateDC` to Reduce Screen Flicker]:
/supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md 
[Writing `DRI` Engine Driver for Your `GPU]`:
/supplementary-docs/Writing-DRI-Engine-Driver-for-Your-GPU.md 
[Writing MiniGUI Apps for 64-bit Platforms]:
/supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md 

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building `MiniGUI]`: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]:
/user-manual/MiniGUIUserManualCompiletimeConfiguration.md 
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md

[MiniGUI Overview]: /MiniGUI-Overview.md
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI Supplementary Documents]: /supplementary-docs/README.md
[MiniGUI `API` Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing `FMSoft` Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/

