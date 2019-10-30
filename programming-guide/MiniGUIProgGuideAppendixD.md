# Specification for the mGNCS-compliant Widget Components

## Terms

- MiniGUI new control set (mGNCS). The new control set not only realizes
  multiple customizable and extensible control classes, but also realizes
resources management function, and object-oriented encapsulation for other
common functions, such as main window, dialog box and menu etc.
- Style. Symbol used for controlling window or control basic look and feel and
  behavior.
   - Control style of the new control set, only used for control properties
     that cannot be modified dynamically, such as if the progress bar is
vertical or horizontal can be realized with style. In the realization of all
the controls, use of style shall be reduced as much as possible.
   - Besides system global styles such as `WS_` and `WS_EX_` etc. are reserved,
     the control styles defined by MiniGUI intrinsic control set are not used
in the new control set. Control styles in the new control set will be defined
again.
   - In the new control set, control no longer has extension style.
- Property. Control property is a newly added concept, which is used for the
  control features that can be dynamically set (such as intercalator location
  in the edit box) or dynamically changed (such as list item number in the list
  box). mGNCS provides uniform interface (`getProperty`/`setProperty`) to get or set
  property of control.
- Renderer. In mGNCS, it refers to the drawing method set of controlling the
  main window or control look and feel, the full name is “look and feel
  renderer”, generally referred to as “renderer” in short.
   - In the new control set, each visible control will have its own renderer.
     In order to distinguish from renderers introduced by MiniGUI 3.0, we refer
     to the renderers of MiniGUI 3.0 as “global renderer”, and the renderers
     introduced by the new control set is referred to as “control renderer”:
   - The global renderer acts on the main window, old control set and system
     components of the new control set (such as non client area elements such
     as border, title bar and scroll bar etc.).
   - Control renderer only acts on the client area drawing of each control of
     the new control set.
- Window class name. In order to distinguish from the name of control class, we
  refer to the class name used by MiniGUI for child window as “window class
  name”. For example, control class name of static box is `mStatic`, while the
  window class name of static box is `static_`.
- Event. In the traditional programming mode of MiniGUI, there exist two
  concepts, message and notification; they have their own effect, but for
  application developers, the nature of notification is the same as that of the
  message. Therefore, mGNCS abstracts the message and notification as event.
  Looking from the angle of application developers, each event correspond to an
  event handler.

## Interface Naming Norm of the New Control Set

Interface naming of the new control set is usually related to the name of
class, therefore, in the later norm description, the all lower case letter
mode, all capital letter mode, lower case and capital letter mixture mode and
capital letter abbrev mode of the class name are represented by `<classname>`,
`<CLASSNAME>`, `<ClassName>`, and `<CLSNM>`.

- Class name (refers to containing method, which is structure of function
  pointer). Although the new control adopts C language to realize, because OOP
idea is adopted, the mode of capital letter and lower case letter mixture is
adopted to represent the name of “class”, and lower case letter m is used as
prefix, such as `mWidget` and corresponding `mWidgetClass`.
- General structure. Use all capital letter modes similar to MiniGUI interface
  to name, and use `NCS<CLSNM>_`  as the prefix.
- Naming rules for functions and parameters
   - The new control set newly adds global general function, and uses `nc` as
     the function name prefix. Afterwards, it is the verb object phrase
describing the function function, and the method of capital letter and lower
case letter mixture is used to name, such as `ncsCreateWindow`.
   - Function interface facing the control developers, the first parameter
     shall be `mWidget*`  or corresponding child class type pointer.
   - Method naming of the control class: verb object phrase, word link writing,
     except the first word, the first letter of other words is capital letter,
such as `void (*moveContent) (mWidget *)`  .
   - Naming norm for the message callback function in control class is:
     `on<MessageName>` ，such as `void (*onSetFocus) (mWidget *)` .
   - Parameter sequence and engagement of control message: according to the
     message criteria defined by MiniGUI, define its sequence and name.
   - Naming norm for control renderer interface is: `<className>Renderer`.
   - Internal function parameter engagement of renderer interface: the first is
     `mWidget*`  or corresponding child class type pointer, and the second
parameter is generally `HDC` .
   - In the new control set, for the functions equivalent to C++ member
     function, pointer variable representing the object is named as `self` ,
while the class pointer that the object corresponds to is `_class` .
   - For the parameter names in the function interface, Java JDK style is
     adopted to name (the first word is all lower case letter, and afterwords,
they are all capital letter and lower case letter mixture), and Hungarian
naming method is no longer used.
   - Read only pointer parameter type and returned value type must use `const`
     key word for modification.
- Window class name. In order to avoid confliction with the window class name
  of the old control set, the new control set uses under line (`_`) as the
suffix of window class name, such as `static_` . The reason for not using
prefix is to try to avoid hash conflict under the algorithm of existing MiniGUI
core management window class code. For the C language macro name of window
class name,  `NCSCTRL_` is used as prefix, such as `NCSCTRL_STATIC` .

It needs to be noted that because we adopt C language to realize rule-oriented
feature similar to C++ language. In order to avoid unnecessary errors, we need
to obey the naming norm as grammar norm, the purpose is:

- Simplify programming through all kinds of macros.
- Convenient for fixing programming mode through macro, according to fixed
  programming mode, it is easy to read and realize and not easy to make
mistakes.
- Generation and index of compiled documents.
- Reduce study time of the developers to the maximum extent.

## Defining Rule for the Class Name and Its Identifier

The table below gives the class name, corresponding window class name and their abbrevs

|*Class name*       |*C class name*       |*Window classname*| *Class name abbrev<br>CLSNM* | *Remark*   |
|-------------------|---------------------|------------------|----------------------------|-----------|
| Super class           | mObject      | - | OBJ    | Non control class, the most foundational class in NCS class hierarchical relations |
| List item basic class     | mItem        | - | ITEM   | Non control class, used to state the foundation class of list item |
| List item manager   | mItemManager | - | ITMMNG | Non control class, used to manage the method class of list item set |
| Column information class       | mListColumn  | - | LSTCLM | Non control class, describes column information class |
| Row list item class     | mListItem    | - | LSTITM | Non control class, manages list item set in a row |
| Component basic class       | mComponent   | - | CMPT   | Non control class |
| Invisible component basic class | mInvsbComp   | - | IVCMPT | Non control class |
| Timer         | mTimer       | - | TIMER  | Non control class |
| Control basic class       | mWidget      | `widget_`       | WIDGET | |
| Static box         | mStatic      | `static_`       | STATIC | |
| Image box         | mImage       | `image_`        | IMAGE  | |
| Rectangular box        | mRect        | `rect_`         | RECT   | |
| Led label | mLEDLabel    | `ledlabel_`     | LEDLBL | |
| Group box         | mGroupBox    | `groupbox_`     | GRPBOX | |
| Button group         | mButtonGroup | `buttongroup_`  | BTNGRP | |
| Button           | mButton      | `button_`       | BUTTON | |
| Check button         | mCheckButton | `checkbutton_`  | CHKBTN | |
| Single selection button         | mRadioButton | `radiobutton_`  | RDOBTN | |
| Panel           | mPanel       | `panel_`        | PANEL  | |
| Combination box         | mCombobox    | `combobox_`     | CMBOX  | |
| Main window         | mMainWnd     | `mainwnd_`      | MNWND  | |
| Dialog box         | mDialogBox   | `dialogbox_`    | DLGBOX | |
| Scrollable basic class     | mScrollWidget| `scrollwidget_` | SWGT   | |
| Container           | mContainer   | `container_`    | CTNR   | |
| Property page         | mPage        | `page_`         | PAGE   | |
| List basic class     | mItemView    | `itemview_`     | ITEMV  | |
| List type         | mListView    | `listview_`     | LISTV  | |
| Icon type         | mIconView    | `iconview_`     | ICONV  | |
| Scroll type         | mScrollView  | `scrollview_`   | SCRLV  | |
| List box         | mListBox     | `listbox_`      | LSTBOX | |
| Progress bar         | mProgressBar | `progressbar_`  | PRGBAR | |
| Property sheet         | mPropSheet   | `propsheet_`    | PRPSHT | |
| Slider basic class     | mSlider      | `slider_`       | SLIDER | |
| Slide bar         | mTackBar     | `trackbar_`     | TRKBAR | |
| Spinner basic class       | mSpinner     | `spinner_`      | SPNR   | |
| Spin box         | mSpinBox     | `spinbox_`      | SPNBOX | |
| Separator         | mSeperator   | `seperator_`    | SPRTR  | |
| Month calendar           | mMonthCalendar | `monthcalendar_` | CDR | |
| Animation           | mAnimation   | `animation_`    | ANMT   | |
| Tool bar         | mToolBar     | `toolbar_`      | TLBAR  | |
| Scroll bar         | mScrollBar     | `scrollbar_`      | SCRLBR  | |
| Edit box basic class     | mEdit        | `edit_`         | EDIT   | |
| Single line edit box     | mSLEdit      | `sledit_`       | SLEDIT | |
| Multi line edit box     | mMLEdit      | `mledit_`       | MLEDIT | |

Naming rule for the identifier is as below:

- Window class name identifier. In order to avoid confliction with the
  identifier of the old control set, the new control set uses
`NCSCTRL_<CLASSNAME>` as the window class name identifier.
- Control style identifier. In order to avoid confliction with the style name
  of the old control set, the new control set uses `NCSS_<CLSNM>_` as the
prefix of the style identifier.
- Control property identifier. The new control set uses `NCSP_<CLSNM>_` as the
  prefix of control property identifier.
- Control notification code identifier. In order to avoid confliction with the
  notification code name of the old control set, the new control set uses
`NCSN_<CLSNM>_` as the prefix of control notification identifier.
- Class specific data identifier. The new control set uses `NCSSPEC_<CLSNM>_`
  as the identifier prefix of class specific data, and specific data of `mObject`
class uses `NCSSPEC_OBJ_` as the prefix.
- Parameter of class method and symbol and status used by the returned value
  etc. The new control set uses `NCSF_<CLSNM>_` as the prefix of this
identifier.
- Return value identifier of function interface and class method. The new
  control set uses `NCSE_<CLSNM>_`  as the prefix of the identifier.
- Other identifiers. Besides the above identifiers, identifiers of other types
  are determined with reference to the above method.

### Defining Rule of Control Style Identifier

In the new control set, number of control styles shall be kept to the minimum,
and the value range of the control style is 0x00000000 ~ 0x0000FFFF, so as to
avoid confusion with the window style defined by MiniGUI.

### Defining Rule of Control Property Identifier

Rule of control property identifier:
1. In the direct inheritance relation, value of property identifier cannot be
repeated, that is, property identifier of the child class cannot cover the
property identifier of the parent class and its ancestor.
1. In the collateral inheritance relation, property identifier can be repeated,
that is, property identifier of a control class can be repeated with the
property identifier of its brother control class.

In technology, enumeration type of C language is utilized to define the
property identifier. For the property identifier prefixes of the controls, see
the table above.
1. In the property identifier enumeration variable of each control, the last
item is defined as `NCSP_<CLSNAM>_MAX` .
1. Property identifier of each control is defined from the value of the maximum
property identifier of its parent class plus one.
1. Define each property by sequence by utilizing the feature of enumeration
being able to plus one automatically.

For example:

```cpp
// mWidget
enum mWidgetProp {
    NCSP_WIDGET_RDR,
    NCSP_WIDGET_MAX
};

// mStatic
enum mStaticProp {
    NCSP_STATIC_HALIGN = NCSP_WIDGET_MAX + 1,
    NCSP_STATIC_VALIGN,
    NCSP_STATIC_MAX
};
```

### Defining Rule of Control Notification Code

Rule for control notification code is similar to the rule for property
identifier. But it needs to be noted that in mGNCS, 0 cannot be used as the
notification code.

## Function Library and Head File of the New Control Set

Although mGNCS is introduced in the process of developing miniStudio, it can be
used singularly as a component in MiniGUI 3.0. Therefore, we manage the new
control set as a component of MiniGUI, and name it mGNCS. Name of the function
library is `libmgncs`, and the current edition is 1.0.0. The head file is stored
under mGNCS/ directory of the system head file path, and the main head file
name is mGNCS.h.

Current mGNCS defines a lot of universal controls, and in the near future, we
will form extension control set aiming at specific field based on the current
mGNCS. Then, an independent function library will be formed, and it is named by
adopting `libmgncs4*`, and the head file will be still stored under `mgncs/`
directory of the system head file path.

----

[&lt;&lt; Public Structures and Definitions of mGNCS](MiniGUIProgGuideAppendixC.md) |
[Table of Contents](README.md)

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
