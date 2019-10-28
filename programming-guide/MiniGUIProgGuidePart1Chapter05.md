# Advanced Programming of Control

## User-Defined Control

You can also register your own control class by calling `RegisterWindowClass`
function, and create an instance of your control class. If the program will not
use a certain user-defined control class any more, it should use
`UnregisterWindowClass` function to unregister this user-defined control class.
Please refer to “control class” of section 3.2.4 of this guide for the usage of
the above two functions.

## Subclassing of Control

Using the framework of a control class and control instance can not only
improve the code reusability, but also extend the existing control class
conveniently. For example, when you need to create an edit box which only
allows inputting digits, you can realize by overriding the existing edit box
control class rather than write a new control class. In MiniGUI, this technique
is called subclassing or window derived. Methods of subclassing have three
types:

- The first one is to perform subclassing on the created control instance, and
the result of subclassing only affects this control instance.
- The second one is to perform subclassing on a certain control class, which
will affect all the control instances created later of this control class.
- The last one is to register a subclassing control class based on a certain
control class, which will not affect the original control class. In Windows,
this technique is also called super-subclassing.

In MiniGUI, the subclassing of a control is actually implemented by replacing
the existing window procedure. The codes in List 1 create two subclassing
edit boxes by subclassing: one only allows inputting digits, and the other only
allows inputting letters:


List 1 Subclassing of control

```
```

## Combined Use of Controls

We can also combine two different controls together to achieve a certain
special effect. In fact, the predefined control class of the combo box is a
typical one of combining controls. When we combine different controls, we can
encapsulate and register the combined control to be a new control class, and
can also use it directly without encapsulation.

To illustrate the method to combine controls more clearly, we can assume that
we want to implement a time editor. This time editor displays the time in form
of “08:05:30”, and we need further add a method to edit the time neatly
according the user’s requirement. To meet this requirement, we combine the edit
box and the spin box together which implement the following functions,
respectively:
- The edit box displays the time in form of “HH:MM:SS”.
- When the input focus is in the edit box, the user can not edit the time
directly, but must control the time value where the caret is with the arrow
keys and `PageDown` and `PageUp` keys. So we must subclass this edit box to
catch 
the key-pressed in it and perform the appropriate handling.
- Place a spin box beside the edit box. The user can adjust the time element
where the caret is to increase or decrease by clicking the spin box. To
achieve this goal, we can use the function of the spin box, and set the handle
of the target window to be the edit box.

Thus, the time editor can work normally. Partial codes of this program are
listed in List 2, and please refer to timeeditor.c file of the sample program
package of this guide for the complete source code. Fig 6.1 shows the running
effect of the timeeditor.

##### List 2 Time Editor

```
```


##### Figure 1 Running effect of time editor

----

[&lt;&lt; Foundation of Control Programming](MiniGUIProgGuidePart1Chapter03.md)
| 
[Table of Contents](README.md) |
[Menu &gt;&gt;](MiniGUIProgGuidePart1Chapter06.md)

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
