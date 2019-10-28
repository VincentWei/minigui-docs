# Scroll View Control

Scroll View (ScrollView) control is also a scroll window control, and different
from `ScrollWnd` control in that `ScrollView` control displays list items
instead of controls.

The major usage of `ScrollView` is to display and handle list items; this 
aspect is similar to list box and list view control. However the height of a
list item in `ScrollView` can be specified by the user, so different list item
can have different height. The most important is, draw of list items in
`ScrollView` is completely determined by application. Totally speaking,
`ScrollView` is a control easy to be customized, and give great free for
applications, using `ScrollView` can perform much work that list box and list
view control cannot do.

## Styles of Scroll View Control

A `ScrollView` control with `SVS_AUTOSORT` style will automatically sort the
list items; the precondition is that you have already set the item comparison
function of the `ScrollView` control by using `SVM_SETITEMCMP` message:

```
```

Here, `myItemCmp` is the item comparison function specified by an application.

List item comparison function of `ScrollView` control has the prototype of
`VM_SETITEMCMP`, which is defined as follows:

```
```

Here, hsvi1 and hsvi2 are the handles of the two list items to be compared. If
the comparison function returns a negative value, the list item hsvi1 will be
displayed before the list item hsvi2.

In addition, you can also use `SVM_SORTITEMS` message to sort list items in a
`ScrollView` control without `SVS_AUTOSORT` style:

```
```

Here, `myItemCmp` is the item comparison function used for sorting which is
specified by an application.

## Messages of Scroll View Control

Except responds to some general scroll window message as `ScrollWnd,` related
messages of `ScrollView` control are mainly used to add, delete, and access 
list item.

### Draw of List Item

Draw of list items in a `ScrollView` control is totally determined your
application itself, so you must specify the content draw method of list item
first before adding any list item. `SVM_SETITEMDRAW` message is used to set the
draw function for list items:

```
```

Content draw function of a list item has the prototype of `SVITEM_DRAWFUNC`,
which is defined as follows:

```
```

The arguments passed to the draw function are the handle to the `ScrollView`
control (hWnd), the handle of list item to be drawn (hsvi), the graphics device
context (hdc), and the rectangle area in which the item be drawn (rcDraw).

According to the actual usage of `ScrollView` control, content draw function 
can draw user-defined content, which can be text or picture, all decided by an
application itself, in the specified rectangle area.

### Set Operation Functions of List Item

`SVM_SETITEMOPS` message can be used to set some callback function related to
list item operations, including initializing, drawing and destroying:

```
```

Here, myops is a structure of `SVITEMOPS` type, and specifies the related
operation functions for list items of `ScrollView,` as follows:

```
```

The member `initItem` is the initialization function, which is called during
creating list items, and its prototype is defined as follows:

```
```

The arguments are the handle to the control window (hWnd), and the handle to 
the created list item (hsvi). This function can be used to perform some
operations relevant to the items during creating them.

The member `destroyItem` is the destroying function called during destroying 
the list items; its prototype is defined as follows:

```
```

The arguments are the handle to the control window (hWnd), and the handle to 
the list item being destroyed. This function can be used to perform some
cleaning up work during destroying them, such as release related resource.

The member `drawItem` specifies the draw function of the list items. Its effect
is completely the same as using `SVM_SETITEMDRAW` message to set the draw
function. 

### Operations on List Item

`SVM_ADDITEM` and `SVM_DELITEM` messages are used to add and delete a list item
respectively: 

```
```

Here, svii is a structure of `SVITEMINFO` type, defined as follows:

```
```

The field `nItem` is the desired index of the list item; if `nItem` is 
negative, the list item will be appended to the end. The field `nItemHeight` is
the height of the list item; `addData` is the additional data value of the list
item. 

Hsvi is used to store the handle to a list item, and this handle can be used to
access the list item. `SVM_ADDITEM` message returns the actual index value of
the list item after inserted.

`SVM_DELITEM` message is used to delete a list item:

```
```

Here, hsvi is used to specify the handle of the list item to be deleted. If 
hsvi is 0, you should specify the index value of the list item to be deleted
through idx.

`SVM_REFRESHITEM` message is used to refresh the area of a list item:

```
```

Here, hsvi is uesed to specify the handle of the list item to be refreshed. If
hsvi is 0, you should specify the index value of the list item to be refreshed
through idx.

`SVM_GETITEMADDDATA` message is used to get the additional data of a list item:

```
```

Here, hsvi is used to specify the handle of the list item to be accessed. If
hsvi is 0, you should specify the index value of the list item to be accessed
through idx.

`SVM_SETITEMADDDATA` message is used to set the additional data of a list item:

```
```

Here, idx is used to specify the index value of the list item to be accessed,
and `addData` is the additional data to be set.

`SVM_GETITEMCOUNT` message is used to get the number of all list items:

```
```

`SVM_RESETCONTENT` message is used to delete all the list items in the control:

```
```

### Get/Set Current Highlighted Item

`ScrollView` control has highlight property, that is to say, only one list item
in list items is the current highlighted list item. An application can set and
get the current highlighted list item.

It should be noted that highlight is only a property of `ScrollView` control.
Being the current highlighted item does not mean the list item must have some
specialty in appearance (such as highlighted display), and this is completely
determined by the application itself.

`SVM_SETCURSEL` message is used to set the highlighted list item of a 
`ScrollView` control:

```
```

Here, idx is used to specify the index value of the list item to be set as the
highlighted item, and if `bVisible` is `TRUE,` the list item becomes a visible
item. 

`SVM_GETCURSEL` message is used to get the current highlighted list item of a
`ScrollView` control:

```
```

The return value of `SVM_GETCURSEL` message is the index value of current
highlighted list item.

### Selection and Display of List Item

Besides highlight property, `ScrollView` also has selection property. The
highlight is unique, but selection is not unique, in other words, there may be
multiple list items of `ScrollView` control to be selected. An application can
set the selection state of list items.

Like highlight property, we should be noted that selection is only a state of a
list item. Being selected does not mean the list item must have some specialty
in appearance (such as highlight display), this is also completely determined 
by the application itself.

`SVM_SELECTITEM` message is used to select a list item:

```
```

Here, idx is used to specify the index value of the list item to be operated,
and if `bSel` is `TRUE,` the list item will be selected; otherwise will not be
selected. 

`SVM_SHOWITEM` message is used to make sure a list item is visible:

```
```

Here, hsvi is used to specify the handle of list item to be displayed, while 
idx is used to specify the index value of the list item to be displayed, and 
idx only works when hsvi is 0.

`SVM_CHOOSEITEM` message is combination of `SVM_SELECTITEM` and `SVM_SHOWITEM`
messages, and is used to select a list item and make

```
```

Here, hsvi is the handle of list item to be selected and displayed, and idx is
used to specify the index value of the list item to be selected and displayed,
and idx only works when hsvi is 0.

### Optimization of Display

When using `SVM_ADDITEM` message or `SVM_DELITEM` message to add or delete many
list items in one time, you can use `MSG_FREEZE` to perform certain
optimization. The usage is to freeze a control before operating, and de-freeze
the control after operating.

When parameter `wParam` of `MSG_FREEZE` message is `TRUE,` the control is
frozen, otherwise de-frozen.

### Set Range of Visible Area

A window of a `ScrollView` control not only contains a visible area, but also a
margin area, as shown in Figure 1.



![alt](figures/30.1_T.jpeg)

Figure 1 Visible area of a `ScrollView` control


`SVM_SETMARGINS` message can be used to set the margin range of a `ScrollView`
control: 

```
```

The left, top, right, and bottom field of `rcMargin` are the size of left, top,
right, and bottom margin respectively to be set, if some a margin value is
negative, the corresponding set will not work.

`SVM_GETMARGINS` message can get the margin range of a `ScrollView` control:

```
```

`SVM_GETLEFTMARGIN`, `SVM_GETTOPMARGIN`, `SVM_GETRIGHTMARGIN`, and
`SVM_GETBOTTOMMARGIN` messages are used to getting left, top, right, bottom
margin value respectively.

## Notification Codes of Scroll View Control

A `ScrollView` control will generate notification codes when responding to the
operation such as the user clicks and some state changing happen, and the
notification codes include:
- `SVN_SELCHANGED:` Currently highlighted list item changes.
- `SVN_CLICKED:` The user clicks a list item.
- `SVN_SELCHANGING:` Currently highlighted list item is changing.

An application should use `SetNotificationCallback` function to register a
notification callback function, and handling on each received notification code
in the function.

When you handle `SVN_CLICKED` and `SVN_SELCHANGE` in the notification callback
function, the additional data passed in is the handle of the list item clicked
or currently highlighted.

For `SVN_SELCHANGING`, the additional data passed in is the handle of the list
item clicked or currently highlighted.

## Sample Program

Code in List 1 illustrates the use of `ScrollView` control. The program
constructs a simple contact person list by using `ScrollView` control. Please
refer to scrollview.c program in the sample program package for the complete
source code of the program.


List 1 Example program of `ScrollView` control

```
```

This program displays the contact person in list form, and sorts them by their
names. 



![alt](figures/30.2.jpeg)

Figure 2 Contact person list


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
