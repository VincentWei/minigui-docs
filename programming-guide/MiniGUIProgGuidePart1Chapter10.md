# Look-and-feel and UI effects

## Look and Feel Renderer and attributes of window elements

MiniGUI 3.0 has totally different window and control's look and feel
implementation mechanism than previous version. The old version must configure
options and select UI style before compile the program, and it can only select
one of three styles, fashion, classic and flat. MiniGUI 3.0 has look and feel
renderer to draw the look-and-feel of window and control. MiniGUI 3.0 provides
four renderers for application, user can select any one when needs a renderer.
The advantage of renderer technology is, we can change look and feel of
application by modifying MiniGUI configuration file, but also by `APIs`.
Application can even customize its own renderer. It is very convenience for
customized UI. The implementation of renderer has two parts as follow:

- Attributes of window elements, include the information of window elements,
such as color, size, font and so on.
- Rendering method of window elements, it defines how to draw window elements.

MiniGUI renderer creates categories for attributes of each part of window and
control, defines drawing interface, so as to get a complete look and feel
renderer mechanism. MiniGUI 3.0 has four renderers, classic, flat, fashion and
skin. `Classic` is default renderer, that means, application draws window and
control's look and feel by using classic renderer when MiniGUI is initializing.
Fashion renderer is supported by mGPlus component.

Application can select a specified renderer for certain window and define
attribute of window element's look and feel. Application can also define its
own renderer to draw the UI.

### Attributes of Window Elements

MiniGUI defines the following window elements:

##### Table 1 Window elements and their names in configuration file and codes

| *Name in config file* | *Code Name* | *Meaning* |
| -----------------------|-------------|-----------|
| caption | `WE_METRICS_CAPTION` | Window caption size |
| |WE_FONT_CAPTION|Window caption font|
| `fgc_active_caption` |WE_FGC_ACTIVE_CAPTION| Foreground color of active window caption |
| `bgca_active_caption` |WE_BGCA_ACTIVE_CAPTION| Gradient start color of active window caption background color|
| `bgcb_active_caption` |WE_BGCB_ACTIVE_CAPTION|Gradient end color of active window caption background color|
| `fgc_inactive_caption` |WE_FGC_INACTIVE_CAPTION | Foreground color of inactive window caption |
| `bgca_inactive_caption` |WE_BGCA_INACTIVE_CAPTION|Gradient start color of inactive window caption background color|
| `bgcb_inactive_caption` |WE_BGCB_INACTIVE_CAPTION|Gradient end color of inactive window caption background color|
| menu |WE_METRICS_MENU| Height of menu item and menu bar|
| |WE_FONT_MENU| Menu font |
| `fgc_menu` |WE_FGC_MENU| Foreground color of menu |
| `bgc_menu` |WE_BGC_MENU| Background color of menu |
| border |WE_METRICS_WND_BORDER| Width of window border |
| `fgc_active_border` |WE_FGC_ACTIVE_WND_BORDER| Border color of active window |
| `fgc_inactive_border` |WE_FGC_INACTIVE_WND_BORDER| Border color of inactive window |
| scrollbar |WE_METRICS_SCROLLBAR| Scrollbar size |
| `fgc_msgbox` |WE_FGC_MESSAGEBOX| Foreground color of message box|
| |WE_FONT_MESSAGEBOX| Font of message box |
| `fgc_tip` |WE_FGC_TOOLTIP| Foreground color of tooltip |
| `bgc_tip` |WE_BGC_TOOLTIP| Background color of tooltip |
| |WE_FONT_TOOLTIP| Tooltip font |
| `fgc_window` |WE_FGC_WINDOW| Foreground color of window |
| `bgc_window` |WE_BGC_WINDOW| Background color of window |
| `fgc_3dbox` |WE_FGC_THREED_BODY| Color of symbols on 3D body, such as check mark and arrow |
| `mainc_3dbox` |WE_MAINC_THREED_BODY| Color of 3D body (border and face) |
| `fgc_selected_item` |WE_FGC_SELECTED_ITEM| Foreground color of selected menu item (list item) |
| `bgc_selected_item` |WE_BGC_SELECTED_ITEM| Background color of selected menu item (list item) |
| `bgc_selected_lostfocus` |WE_BGC_SELECTED_LOSTFOCUS| Background color when selected menu item (list item) lost focus |
| `fgc_disabled_item` |WE_FGC_DISABLED_ITEM| Foreground color of disabled menu item (list item) |
| `bgc_disabled_item` |WE_BGC_DISABLED_ITEM| Background color of disabled menu item (list item) |
| `fgc_hilight_item` |WE_FGC_HIGHLIGHT_ITEM| Foreground color of highlighted menu item (list item) |
| `bgc_hilight_item` |WE_BGC_HIGHLIGHT_ITEM| Background color of highlighted menu item (list item) |
| `fgc_significant_item` |WE_FGC_SIGNIFICANT_ITEM| Foreground color of significant menu item (list item) |
| `bgc_significant_item` |WE_BGC_SIGNIFICANT_ITEM| Background color of significant menu item (list item) |
| `bgc_desktop` |WE_BGC_DESKTOP| Background color of desktop |

Above table introduces all window elements. The name in configuration means
this element's name in `MiniGUI.cfg` (MiniGUI configuration file). User can
modify the value of attributes of window element in the configuration file to
change window's look and feel. Code name is to specify the window element when
modifying the attribute of window element by using function interface.

### Attributes of skin renderer's window skin

To replace `SKIN` `APIs` in `MGExt` library with renderer, MiniGUI 3.0 uses 
skin 
renderer. Skin renderer has not only window attributes of other renderers, but
also attributes of window skin. The descriptions of attributes of window skin
are as follow:

##### Table 2 Attributes of window skin and their names in configuration file
and codes

| *Name in config file* | *Code Name* | *Meaning* |
| -----------------------|-------------|-----------|
| `skin_bkgnd` |WE_LFSKIN_WND_BKGND| Skin image of desktop background |
| `skin_caption` |WE_LFSKIN_CAPTION| Skin image of window caption |
| `skin_caption_btn` |WE_LFSKIN_CAPTION_BTN| Skin image of window caption button |
| `skin_scrollbar_hshaft` |WE_LFSKIN_SCROLLBAR_HSHAFT| Skin image of horizontal scrollbar shaft |
| `skin_scrollbar_vshaft` |WE_LFSKIN_SCROLLBAR_VSHAFT| Skin image of vertical scrollbar shaft |
| `skin_scrollbar_hthumb` |WE_LFSKIN_SCROLLBAR_HTHUMB| Skin image of horizontal scrollbar thumb |
| `skin_scrollbar_vthumb` |WE_LFSKIN_SCROLLBAR_VTHUMB| Skin image of vertical scrollbar thumb |
| `skin_scrollbar_arrows` |WE_LFSKIN_SCROLLBAR_ARROWS| Skin image of scrollbar arrow |
| `skin_tborder` |WE_LFSKIN_BORDER_TOP| Skin image of top border |
| `skin_bborder` |WE_LFSKIN_BORDER_BOTTOM| Skin image of bottom border |
| `skin_lborder` |WE_LFSKIN_BORDER_LEFT| Skin image of left border |
| `skin_rborder` |WE_LFSKIN_BORDER_RIGHT| Skin image of right border |
| `skin_arrows` |WE_LFSKIN_ARROWS| Skin image of arrow |
| `skin_arrows_shell` |WE_LFSKIN_ARROWS_SHELL| Skin image of arrow's shell |
| `skin_pushbtn` |WE_LFSKIN_PUSHBUTTON| Skin image of push button |
| `skin_radiobtn` |WE_LFSKIN_RADIOBUTTON| Skin image of radio button |
| `skin_checkbtn` |WE_LFSKIN_CHECKBUTTON| Skin image of check button |
| `skin_tree` |WE_LFSKIN_TREE| Skin image of tree control |
| `skin_header` |WE_LFSKIN_HEADER| Skin image of header |
| `skin_tab` |WE_LFSKIN_TAB| Skin image of tab on property sheet |
| `skin_tbslider_h` |WE_LFSKIN_TBSLIDER_H| Skin image of horizontal sliderbar |
| `skin_tbslider_v` |WE_LFSKIN_TBSLIDER_V| Skin image of vertical sliderbar |
| `skin_trackbar_horz` |WE_LFSKIN_TRACKBAR_HORZ| Skin image of horizontal trackbar |
| `skin_trackbar_vert` |WE_LFSKIN_TRACKBAR_VERT| Skin image of vertical trackbar |
| `skin_progressbar_htrack` |WE_LFSKIN_PROGRESS_HTRACKBAR| Skin image of horizontal progress bar |
| `skin_progressbar_vtrack` |WE_LFSKIN_PROGRESS_VTRACKBAR| Skin image of vertical progress bar |
| `skin_progressbar_hchunk` |WE_LFSKIN_PROGRESS_HCHUNK| Skin image of horizontal progress chunk |
| `skin_progressbar_vchunk` |WE_LFSKIN_PROGRESS_VCHUNK| Skin image of vertical progress chunk |

### Operating function of window attribute

We can change window attribute before execute program and control look and feel
of window by changing MiniGUI configuration file. We can also customize look
and feel of window in the program by using `APIs`. To help with operating of
window attribute, MiniGUI defines the following `API` to implement operating of
window attribute.

```
```

`we_attr_id` in above all functions is attribute `ID` of window element. This 
`ID` 
must be one of code names in Table 1 and 2.

`GetWindowElementAttr` is to get certain element's attribute `ID` of specified
window. hwnd is window handle and `we_attr_id` is attribute `ID` of window
element. 

The following codes are for getting color of 3D body's border and face.

```
```

`SetWindowElementAttr` is to set certain element's attribute `ID` of specified
window. hwnd is window handle, `we_attr_id` is attribute `ID` of window element
and 
`we_attr` is attribute value.

In the following codes, it gets min height of menu first, then compares the
height with height of window. Window's min height will be set to menu's if
height of menu is greater than window's.

```
```

`GetWindowElementPixelEx` is to get color value of window element. hwnd is
window 
handle, hdc is `DC` handle and `we_attr_id` is attribute `ID` of window 
element. 

The following codes can get gradient start color of window caption background.

```
```

`SetWindowElementRenderer` is to set current renderer of window and change
attributes of window. `hWnd` is window handle, `werdr_name` is renderer's name
which will be set, `we_attrs` is structure array of modified attribute of
window. 
The `ID` of last element in array is -1, it means, this is the end.

`WINDOW_ELEMENT_ATTR` structure is as follow:

```
```

The first member in structure is attribute id of window element which needs to
be changed, the second one is needed attribute value.

The following codes set flat as current window renderer and modify some
attributes of window.

```
```

### Renderer Management

Renderer consists of two parts: attribute of window element and matches render
method. We have introduced attribute of window and relevant function
interfaces, and then we introduce render method and how to use renderer. The
structure which is used by renderer is `WINDOW_ELEMENT_RENDERER`, it consists 
of 
renderer name, pointer of render method interface and relevant attribute of
window.

```
```

The following table explains each member in the structure.

##### Table 3 Explanation of renderer structure member

| *Member Name* | *Meaning* |
| ---------------|-----------|
| name| Renderer name, length is `LEN_RENDERER_NAME`. Macro `LEN_RENDERER_NAME` is defined as 15 |
| init| Renderer initialization function pointer. It initializes basic renderer information which are window attribute information and private information, such as size, font and color of window element |
| deinit| Renderer destroy function pointer. It frees resources that were allocated by renderer |
| `calc_3dbox_color|` Calculating function pointer of 3D box's color. It gets color value according to calculating flat and color of 3D box's border and face |
| `draw_3dbox|` Drawing function pointer of 3D box |
| `draw_radio|` Drawing function pointer of radio box |
| `draw_checkbox|` Drawing function pointer of check box without check mark |
| `draw_checkmark|` Drawing function pointer of check box with check mark |
| `draw_arrow|` Drawing function pointer of arrow |
| `draw_fold|` Drawing function pointer of fold/unfold |
| `draw_focus_frame|` Drawing function pointer of focus frame |
| `draw_normal_item|` Drawing function pointer of list item in normal state |
| `draw_hilite_item|` Drawing function pointer of list item in highlighted state |
| `draw_disabled_item|` Drawing function pointer of disabled list item |
| `draw_significant_item|` Drawing function pointer of significant list item |
| `draw_push_button|` Drawing function pointer of push button |
| `draw_radio_button|` Drawing function pointer of radio button |
| `draw_check_button|` Drawing function pointer of check button |
| `draw_border|` Drawing function pointer of window border |
| `draw_caption|` Drawing function pointer of window caption |
| `draw_caption_button|` Drawing function pointer of window caption button. The buttons include minimize/maximize/close button |
| `draw_scrollbar|` Drawing function pointer of scrollbar |
| `calc_trackbar_rect|` Drawing function pointer of rectangle of track bar |
| `draw_trackbar|` Drawing function pointer of track bar |
| `calc_we_area|` Calculating function pointer of window element area. The areas include border, caption, caption buttons, toolbar, menu, client area and horizontal/vertical scrollbar |
| `calc_we_metrics|` Calculating function pointer of window element size. The elements are as same as elements in `calc_we_area` |
| `hit_test|` Function pointer of window element clicked by mouse |
| `on_click_hotspot|` Corresponding function pointer when mouse clicks hot spot |
| `draw_custom_hotspot|` Drawing function pointer of hot spot |
| `calc_thumb_area|` Calculating function pointer of thumb of horizontal/vertical scrollbar |
| `disabled_text_out|` Output function pointer of disabled area text |
| `draw_tab|` Drawing function pointer of tab on property sheet |
| `draw_progress|` Drawing function pointer of progress bar |
| `draw_header|` Drawing function pointer of header on listbox or grid view control |
| `on_get_rdr_attr|` Get function pointer of renderer's private information |
| `on_set_rdr_attr|` Set function pointer of renderer's private information |
| `erase_background|` Drawing function pointer of erasing window background |
| `draw_normal_menu_item|` Drawing function pointer of menu item in normal state |
| `draw_hilite_menu_item|` Drawing function pointer of menu item in highlighted state |
| `draw_disabled_menu_item|` Drawing function pointer of disabled menu item |
| `we_metrics|` Attribute of window size |
| `we_colors|` Attribute of window color |
| `we_fonts|` Attribute of window font |
| `we_icon|` Attribute of window icon handle |
| refcount| Attribute of window reference counter |
| `private_info|` Pointer of renderer's private information |

MiniGUI provides the following `API` to manage renderer:

- `GetWindowRendererFromName`: Get renderer from name. Function prototype is as
follows:

```
```

- `AddWindowElementRenderer`: Add renderer to MiniGUI. Function prototype is as
follows:

```
```

- `RemoveWindowElementRenderer`: Remove renderer from MiniGUI. Function
prototype 
is as follow:

```
```

- `GetDefaultWindowElementRenderer`: Get default renderer. Function prototype 
is 
as follow:

```
```

- `SetDefaultWindowElementRenderer`: Set default renderer. Function prototype 
is 
as follow:

```
```

- `SetWindowElementRenderer`: Specify renderer. Function prototype is as 
follow: 

```
```

### Creating main window

It needs more arguments to create main window after draw a window by using
renderer, for `API` compatible, MiniGUI created a new function,
`CreateMainWindowEx`, and packaged the old creating function. Function 
prototype 
is as follow.

```
```

- `pCreateInfo` Main window structure, we have introduced it in chapter 3,
Window and Message.
- `window_name` and `layer_name` are reserved arguments for later version.
- `werdr_name` The name of window element's renderer which will be used. Will
use default renderer if it is `NULL`.
- `we_attrs` Attribute table of window element's look and feel. Will use
default attribute table if it is `NULL`.

### Creating control

Similar with main window creating, there is also a new function,
`CreateWindowEx2`, to create control. MiniGUI also packaged old creating
function, `CreateWindowEx`.

```
```
These functions have be introduced in chapter 5, Foundation of Control
Programming. 

### Creating dialog box

- Modal dialog box creating

```
```

- Modeless dialog box creating

```
```

Above functions end in Ex are new added functions. They have been introduced in
chapter 4, Foundation of Dialog Box Programming.

## Double Buffering Main Window

Double buffering main window mechanism is a window rendering method which is
provide by MiniGUI. In this mechanism, when drawing main window, the window is
drawn in matched memory `DC` first, and then we can calculate the data in `DC`
by 
using various algorithms to get various special display effects, such as
push-pull, scrolling and page turning. Another function of the mechanism is
improving the efficient of window drawing and solving blinking issue when doing
window drawing.

### Extension Style of Double Buffering Main Window

We can create main window or dialog box with memory `DC` which matches window 
`DC` 
by using the extension style of double buffering main window. The definition is
as follow:

```
```

The following code is an example for creating main window with double buffer.
```
```

### Functions of double buffering window mechanism

- Double buffers `DC` creating function, `CreateSecondaryDC`, creates 
compatible 
memory `DC` and returns according to passed window's size.

```
```

- `SetSecondaryDC` sets already made memory `DC` as one of double buffers of
target 
main window. It also copies callback function from double buffer's screen `DC`.

```
```

It is necessary to note the following when invoking `SetSecondaryDC`:
- If main window has `WS_EX_AUTOSecondaryDC` style, it will disable this style
and invoke `DeleteSecondaryDC` to delete exist double buffers and return
`HDC_SCREEN`.
- If main window doesn't have `WS_EX_AUTOSecondaryDC` style, it will return
the handle of exist double buffers. The exist double buffers is managed by
application.
- If `HDC_SCREEN` is passed, it will cancel double buffering mechanism of
window.
- If passed `ON_UPDATE_SecondaryDC` is `NULL`, MiniGUI will not draw the
contents of screen `DC` to screen automatically, user needs to copy the
contents of double buffers to screen `DC` by using `BitBlt` function. Otherwise
the 
application takes responsibility of copying double buffers to screen `DC` to 
get 
UI effects.

In the following code, main window is drawn on double buffer after set double
buffer of main window.

```
```

- `GetSecondaryDC` can get the handle of double buffer.

```
```

- `GetSecondaryClientDC` is to get the `DC` of double buffering window's 
client. If
the window doesn't support double buffer, it returns the `DC` of window's
client, equal to `GetClientDC`.

```
```

- `ReleaseSecondaryDC` releases the `DC` of double buffer. It will do nothing,
it 
the `DC` is main window double buffer's `DC`.

```
```

- `DeleteSecondaryDC` deletes the `DC` created by `CreateSecondaryDC`.

```
```

- `GetSecondarySubDC` is only for double buffer, it creates sub-DC based on the
`DC` of private window, so the sub-DC can be the client `DC` of main window or
be 
regarded to control's `DC`. Both main window (or its control) with
`WS_EX_SecondaryDC` style is drawing non-client and the return value of
`BeginPaint` should use `GetSecondarySubDC` to get sub-DC of double buffer 
`DC`, 
to ensure that all drawings in main window is on double buffer `DC`.

```
```

- `ReleaseSecondarySubDC` releases sub-DC of private `DC`.

```
```

### Sample program of double buffering mechanism

- Create main window with double buffer, and then add the codes of UI effects
before message loop.

```
```

- The codes of three UI effects
```
```

- Invoke UI effects codes in window close message

```
```

- The codes of three UI effects when window is closing

```
```
- Three UI effects


##### Figure 1 UI effect of double buffering main window

## Customization of Desktop

MiniGUI provides a set of desktop window customization interfaces as callback
functions. Through these interfaces, application can control desktop window to
response each message, it is similar to the desktop of Windows.

### Structure of Desktop Customization

```
```
Members in the structure:
```
```

### Functions of Desktop Customization

- Customize the function which set the interface.

```
```

This function is to set assigned desktop customization structure. Desktop
window will invoke set function interface to handle the message later.

- Update function of desktop window:

```
```

This function updates all windows on desktop. It is convenience to repaint all
windows.

### Sample program

This sample program is in mginit, a directory of mg-samples. Due to limited
space, only key codes are listed here. Callback functions of desktop
customization interfaces are defined in desktop.c:

```
```

Callback functions of desktop customization interfaces are as follow:
```
```

There is a configuration file, mginit.rc. We can get relative resources of
desktop by loading this file. The contents of mginit.rc are as follow:

```
```

Initialized desktop customization structure in main function is set to MiniGUI.
The following code is in mginit.c (please refer to chapter 17):

```
```

The screenshot of the application.

##### Figure 2 Customization of Desktop

----

[&lt;&lt; Icon, Cursor, and Caret](MiniGUIProgGuidePart1Chapter09.md) |
[Table of Contents](README.md) |
[Other Programming Topic &gt;&gt;](MiniGUIProgGuidePart1Chapter11.md)

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
