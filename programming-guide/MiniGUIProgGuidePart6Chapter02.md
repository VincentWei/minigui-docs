# Button Control

Button control is the most frequently used control besides the static control. 
A button is usually used to provide switch selection for the user. The buttons
of MiniGUI can be classified into push button, check box, radio button, etc. 
The user can select or switch the status of a button with the keyboard or the
mouse. The user’s input will make a button generating notification messages, 
and an application can also send messages to a button to change the status of
it. 

Calling `CreateWindow` function with `CTRL_BUTTON` as the control class name 
can create a button control.

## Types and Styles of Button

### Push button

A push button is a rectangle, in which the window caption passed through
`CreateWindow` is displayed. The rectangle occupies the whole height and width
given when calling `CreateWindow` and the text locates in the center of the
rectangle. 

A push button control is mainly used to trigger an action, which responds
immediately, and does not keep the switch information for long. Such a button
has two window styles, namely `BS_PUSHBUTTON` and `BS_DEFPUSHBUTTON`. “DEF” in
`BS_DEFPUSHBUTTON` means “default”. `BS_PUSHBUTTON` and `BS_DEFPUSHBUTTON` have
different effects when used in a dialog box. No matter which control the input
focus locates on, the button with `BS_DEFPUSHBUTTON` style will take `ENTER` 
key input as the default input. However, the buttons of these two styles have
the same function when used as controls in a normal main window, except that 
the button with `BS_DEFPUSHBUTTON` has a thicker border.

When the mouse cursor is in the button, pressing the left button of the mouse
will make the button redraw itself with three-dimensional shadow, which looks
like being pushed down really. When the mouse button is released, the button
recovers to its original appearance, and generates `BN_CLICKED` notification.
When the button has the input focus, there are dashed lines around the text and
pressing or releasing the Space key or the left mouse button results in the 
same effect.

***
[Prompt] The description of the control behavior and appearance in this guide
takes the default classic style as the standard.
***

Generally, text on the push button would display in the central of the vertical
and horizontal directions with single-line form, and will not be wrapped
automatically. An application also can display multiple lines text by 
specifying `BS_MULTLINE` style.The following program creates two push buttons:

```
```

The appearance of the two push buttons created by the program above is as shown
in Figure 1. Note that the text is aligning up when `BS_MULTILINE` style is
used. 



![alt](figures/20.1.jpeg)

Figure 1 Push buttons


In addition, bitmaps or icons also can also be displayed on the push button. In
the case `BS_BITMAP` or `BS_ICON` style is used, the pointer to a bitmap object
or the handle to an icon should be passed through `dwAddData` argument of
`CreateWindow` function. The bitmap or icon will be scaled to fill the whole
button window in default; however, they are displayed in the center of the
control without any scaling when `BS_REALSIZEIMAGE` style is used. The 
following code fragment creates a button with a bitmap, and its effect is as
shown in Figure 2.

```
```



![alt](figures/20.2.jpeg)

Figure 2 Bitmap push button


### Check Box

A check box is a text block, and the text is usually on the right side of a
check mark (if you specify `BS_LEFTTEXT` style when creating the button, the
text will be on the left). A check box is usually used in the application, 
which allows the user to make a selection among options. The commonly used
function of a check box is as a switch: click once shows the checked mark, and
click again clears the mark.

The two most frequently used styles for check box are `BS_CHECKBOX` and
`BS_AUTOCHECKBOX`. When `BS_CHECKBOX` is used, the application need send
messages to the control to set the checked mark; and when `BS_AUTOCHECKBOX`
style is used, the control will switch the status between checked and 
unchecked. 

The other two styles of check box are `BS_3STAT` and `BS_AUTO3STATE`. As hinted
by their names, these two styles can show the third state - the color is gray
within the check box, indicating the check box cannot be selected or used.

The difference between `BS_3STATE` and `BS_AUTO3STATE` is the same as the 
above: the former need the application operates its state, while the latter 
lets the control to be in charge of the automatic state switch.

A check box is left aligned in the rectangle by default, and locates between 
the top and the bottom of the control window (centered vertically). Clicking 
the mouse button in any position in the rectangle will generate a notification
message. Using `BS_LEFTTEXT` style will right-align the check box, and place 
the text in the left of the check mark. Styles for justifying text, such as
`BS_LEFT`, `BS_CENTER`, `BS_RIGHT`, `BS_TOP`, `BS_VCENTER`, `BS_BOTTOM`, etc.
all can be used for the check box.

In addition, using `BS_PUSHLIKE` style will make a check box be displayed as a
push button: in pushed state when checked and normal state when unchecked.

The following program creates two check boxes, and the effect is shown in 
Figure 3.

```
```



![alt](figures/20.3.jpeg)

Figure 3 Check boxes


### Radio Button

A radio button is just like the channel selection buttons on a radio. Each
button corresponds to a channel, and each time only one button can be selected.
In a dialog box, the radio button group is usually used for representing
mutually exclusive options. A radio button is different from a check box, for
the work manner is not as a switch; that is to say, when pushing a radio button
again, its status will not change.

The shape of a radio button is a circle, not a rectangle. Except the shape
difference, the behavior of a radio button is very like a check box. The
enhanced dot in the circle means the radio button is already selected. The 
radio button has two styles, namely `BS_RADIOBUTTON` and `BS_AUTORADIOBUTTON`.
The latter will show the selection state of the user automatically, while the
former will not.

By default, a radio button is left justified in the control window, and locates
in the middle between the top and the bottom of the control window (centered
vertically). Pressing the mouse in any position in the rectangle will generate 
a notification message. Using `BS_LEFTTEXT` style will right-justify the combo
box, and place the text in the left of the radio button. Styles for justifying
text, such as `BS_LEFT`, `BS_CENTER`, `BS_RIGHT`, `BS_TOP`, `BS_VCENTER`,
`BS_BOTTOM`, etc., can be used for the radio button.

In addition, using `BS_PUSHLIKE` style will make a radio button be displayed as
a push button: in pushed state when selected and normal state when unselected.
The following program creates two radio buttons, and the effect is shown in 
Figure 4.

```
```



![alt](figures/20.4.jpeg)

Figure 4 Radio buttons


Radio buttons are generally used in a group, and only one button can be 
selected among the radio buttons in the same group. When creating a group of
radio buttons, we need set their status to be mutually exclusive, so `WS_GROUP`
style needs to be used when creating the first radio button in order to set it
as the “leader button” of the group.

## Messages of Button

The application can do the following works by sending messages to a button:
- To get/set the check state of a radio button or check box:
`BM_GETCHECK、BM_SETCHECK` 
- To get/set the pushed or released state of a push button or a check box:
`BM_GETSTATE、BM_SETSTATE` 
- To get/set the bitmap or icon on the bitmap button: `BM_GETIMAGE、BM_SETIMAGE`
- Sending `BM_CLICK` to simulate clicking operation of the mouse button.

The application sends `BM_SETCHECK` message with `wParam` equal to be
`BST_CHECKED` to a check box or radio box to make it to be the checked state:

```
```

In fact `wParam` can be one of the three possible values shown in Table 1. 
These values are also the checked state value returned through `BM_GETCHECK`
message. 


Table 1 States of check box or radio button<br>
| *State identifier* |*Meaning*|
| `BST_UNCHECKED(0)` |Indicates the button is unchecked|
| `BST_CHECKED(1)` |Indicates the button is checked|
| `BST_INDETERMINATE(2)` |Indicates the button is grayed because the state of the button is indeterminate|


We can simulate the button blinking by sending `BM_SETSTATE` message to the
control. The following operation will cause the button to be pushed:

```
```

The following operation will cause the button to be unpushed:

```
```

For a bitmap button, `BM_GETIMAGE` or `BM_SETIMAGE` message can be used to get
or set the bitmap object or handle of the icon:

```
```

In addition, in an application, we can simulate the click operation of the user
by sending `BM_CLICK` message to a button.

## Notification Codes of Button

The notification codes generated by a button with `BS_NOTIFY` style are as
follow: 
- `BN_CLICKED:` Indicate the user clicked the button. The value of this
notification code is zero, so if you want to handle `BN_CLICKED` notification
message sent by the button in the parent window, you need only determine 
whether `wParam` parameter of `MSG_COMMAND` message equals to the button
identifier. The generation of this notification is default and will ignore
`BS_NOTIFY` style of the button control.
- `BN_PUSHED:` Indicate the user pushed the button.
- `BN_UNPUSHED:` Indicate the user released the button.
- `BN_DBLCLK:` Indicate the user double-clicked a button.
- `BN_SETFOCUS:` Indicate the button received the keyboard focus.
- `BN_KILLFOCUS:` Indicate a button lost the keyboard focus.

## Sample Program

Generally, to get the click notification code of a push button, the application
need only handle `BN_CLICKED` notification code. Check boxes and radio buttons
are usually set to be the automatic state, and send `BM_GETCHECK` to get the
checked state when necessary. For dialog boxes, the application can also get 
the state information of a button control quickly with the functions listed in
Table 2


Table 2 Convenient functions handling button controls<br>
| *Function* |*Purpose* |*Note*|
| `CheckDlgButton` | Changes the check status of a button control by its identifier||
| `CheckRadioButton` |Adds a check mark to (checks) a specified radio button in a group and removes a check mark from (clears) all other radio buttons in the group |Ensure to check a button mutually exclusively|
| `IsDlgButtonChecked` |Determines whether a button control has a check mark next to it or whether a three-state button control is grayed, checked, or neither||


The program in List 1 gives a comprehensive example for using button controls.
This program uses a dialog box to ask the user about his taste, selects the
snack type by grouped radio buttons, and then selects some special tastes for
the user by check boxes. Please refer to button.c file in the demo program
package `mg-samples` of this guide to get the full source code of this program.
The running effect of this program is shown in Figure 5.


List 1 Example for using button controls

```
```



![alt](figures/20.5.jpeg)

Figure 5 Example for using button controls</center>


-- Main.XiaodongLi - 26 Oct 2009


----

[&lt;&lt; ](MiniGUIProgGuidePart.md) |
[Table of Contents](README.md) |
[ &gt;&gt;](MiniGUIProgGuidePart.md)

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
