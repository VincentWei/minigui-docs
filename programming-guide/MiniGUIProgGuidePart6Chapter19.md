# `GridView` Control

`GridView` displays a series of data items (cells) in table form, and the
contents of every cell are independent each other. The contents of gridview
header, including a column of header and a row of header, usually express the
meanings of the column and the row. From the appearance, gridview is a 
rectangle box including header cells. You can adjust the height of the row and
the width of the column in the gridview by dragging the header, and use the
scrollbar to display the content, which was out of the display window.

`GridView` is a convenient and effective tool, which can arrange and display 
the data item. It suits to deal with a great deal of datum with different
attribute, such as experiment data or account table.

You can call `CreateWindow` function and use the control name `CTRL_GRID` to
create a `GridView.` Applications usually add, delete or operate the table 
items by sending messages to the `GridView.` Like other controls, `GridView`
will not generate messages until it responds user clicking or other operations.

## Styles of Gridview

By default, `GridView` window only displays header and cell, and there is no
border in the display region. When creating `GridView` with `CreateWindow`
function, you can use window style `WS_BORDER` to add the border in it.
Otherwise, use window style `WS_VSCROLL` and `WS_HSCROLL` to add upright and
horizontal scroll bars. It is convenient for using mouse to display all 
contents in the `GridView` by scrolling the bar.

## Messages of `GridView`

When creating `GridView,` you can set a structure `GRIDVIEWDATA` and transfer
this structure as a parameter. The definition of this structure and the 
meanings of every member are:

```
```

### Column Operations

After creating the `GridView,` user demands to add a column to the control,
which can be finished by application sending `GRIDM` `ADDCOLUMN` message to the
control. 

```
```

Here celldata is a `GRIDCELLDATA` structure, including the information about 
the new added column. The `GRIDCELLDATA` structure definition and the meanings
of every member are:

```
```

content field in the above structure points to the address of another structure
`GRIDCELLDATAHEADER.` The definition of this structure and the meanings of 
every member are:

```
```

Before adding a new column, you should set the number size of the structure
`GRIDCELLDATAHEADE` and the number buff point to the caption of the column. The
number `len_buff` is the length of the caption. Adding a row is same as adding 
a column. But the number size is the height of the new row.

`GRIDCELLDATA` structure is to set the attributes of the row, column and cell 
in `GridView,` which is used by many messages, such as `GRIDM_SETCELLPROPERTY`,
`GRIDM_GETCELLPROPERTY`, `GRIDM_ADDROW` and `GRIDM_ADDCOLUMN` etc.

style field in the `GRIDCELLDATA` structure is the style of cell. Every times,
when you set, you should point out which type is among below options:
`GV_TYPE_HEADER`, `GV_TYPE_TEXT`, `GV_TYPE_NUMBER`, `GV_TYPE_SELECTION` and
`GV_TYPE_CHECKBOX`. It can be used with cell style, such as `GVS_READONLY` etc.

content field also can point to other structures, which are
`GRIDCELLDATATEXT（text` cell）, `GRIDCELLDATANUMBER（data` cell）,
`GRIDCELLDATASELECTION（combo` boxes cell）, `GRIDCELLDATACHECKBOX(selection`
cell). The definition and the meaning of every member are:

```
```

`GRIDM_SETCOLWIDTH` can be used to set the width of the control column:

```
```

Here index is the integral index value of the column needed to set, and width 
is the width of the column.

`GRIDM_GETCOLWIDTH` can get the width of the control column:

```
```

Here index is the integral index value of the column needed to get, and the
return value of the `SendMessage` function is the width of column. If error
occurs, returns –1.

`GRIDM_ADDCOLUMN` message is used to add a column.

```
```

Here index is the integral index value of the column upon the added column, and
celldata is a pointer of `GRIDCELLDATA` structure, which is used to set initial
value for new column.

`GRIDM_DELCOLUMN` message is used to delete a column in `GridView.`

```
```

Here index is the index value of the deleted column.

`GRIDM_GETCOLCOUNT` message is used to get the number of columns in `GridView.`

```
```

The return value of `SendMessage` function is the number of columns. This
message will return –1 on error.

### Row Operations

Row operations are same as column operations.

`GRIDM_SETROWHEIGHT` can be used to set the height of the row.

```
```

Here, index is the integral index value of the row needed to set, and height is
the set height.

`GRIDM_GETROWHEIGHT` can get the width of the row.

```
```

Here, index is the integral index value of the row needed to get, and the 
return value of the `SendMessage` function is the height of the row. The 
message will return –1 on error.

`GRIDM_ADDROW` message is used to add a new row in `GridView.`

```
```

Here, index is the integral index value of row upon the added row; celldata is 
a pointer of `GRIDCELLDATA` structure, which is used to set the initial value 
of the new row.

`GRIDM_DELROW` message is used to delete a row in `GridView.`

```
```

Here index is the index value of the deleted row.

`GRIDM_GETROWCOUNT` is used to get the number of the rows in `GridView.`

```
```

The return value of `SendMessage` function is the number of the rows.

### Cell Operations

`GRIDM_SETCELLPROPERTY` message is used to set one or many cell.

```
```

Here, cells is a pointer of `GRIDCELLS` structure, which expresses the range of
the cell needed to set. The definition of the `GRIDCELLS` structure and the
meanings of every member are:

```
```

If `SendMessage` function is ok, return `GRID_OKAY;` otherwise, return 
`GRID_ERR`. 

`GRIDM_GETCELLPROPERTY` message is used to obtain the attribute of cell.

```
```

Here, cells is an idiographic cell, which is not multi-cell. After the content
of certain cell is set successfully, the function `SendMessage` will return
`GRID_OKAY`. The structure celldata contains the information of the certain
cell. If error occurred, the message will return `GRID_ERR`.

Otherwise, there are some other messages for cells with different format, such
as `GRIDM_SETNUMFORMAT` message, which is used to set the data format of data
cell (GRIDCELLDATANUMBER).

```
```

Here, cells is the cell to be set, and format is the data format to be set.

For all kinds of cells, `GRIDM_SETSELECTED` is used to set highlighted cell.

```
```

Here, cells is the cell to be set highlighted. If the cell is set highlighted
successfully, the function `SendMessage` will return `GRID_OKAY`, otherwise it
will return `GRID_ERR`.

`GRIDM_GETSELECTED` is used to get all highlighted cells.

```
```

With this option, the function `SendMessage` will return all the highlighted
cells. 

## Other Messages

When user presses the up/down or left/right arrow key, the selected cell will
change, and the new selected option will turn visible (if it has been
invisible). When user presses the `PAGEUP/PAGEDOWN` key, the column cell will
turn to another page. The page change range is the same as the scrollbar; the
last item on first page will turn to second one’s first item. If `HOME` key is
pressed, the first cell in the column will be selected and become visible. If
`END` key is pressed, the last cell will be selected and become visible. When
all the above keys are pressed with `SHIFT` on the same time, the operation on
highlighted area will be carried out. When cell is double clicked or selected,
it will edit the content of the cell to input character.

The grid control is also able to associate some cells (source cells) with other
cells (target cells). Then the target cells will refresh themselves according 
to the given operation function when the source cells’ data is changed. The
structure to carry out this operation is listed below:

```
```

The message, `GRIDM_ADDDEPENDENCE`, is used to add an association of cells.(It
should be noted that source cell and target cell can not intersect and target
cell also can not intersect with other target cells of the control).

```
```

If success, the message will return the index of the association; otherwise it
will return `GRID_ERR`.

The message `GRIDM_DELDEPENDENCE` is used to delete a cell association in the
`GridView.` 

```
```

Here the `dependence_id` is the index of the associated cell to be deleted. The
message function will return `GRID_OKAY` when deletion is successful, otherwise
it will return `GRID_ERR`.

## Notification Codes of `GridView`

The `GridView` will generate notification code when it responds to user's
operation such as clicking or some status is changed. The notification codes
include: 
- `GRIDN_HEADLDOWN:` the left buttuon of the user's mouse is pressed on the
table head
- `GRIDN_HEADLUP:` the left buttuon of the user’s mouse is released on the 
table head
- `GRIDN_KEYDOWN:` key is pressed down
- `GRIDN_CELLDBCLK:` user double click one cell
- `GRIDN_CELLCLK:` user single click one cell
- `GRIDN_FOCUSCHANGED:` the focus cell is changed
- `GRIDN_CELLTEXTCHANGED:` the content of the cell is changed

When the left button of the user’s mouse is pressed on some cell, the cell will
be selected, and two notification codes `GRIDN_FOCUSCHANGED` and 
`GRIDN_CELLCLK` will be generated.

If an application needs to know the notification code of the grid control, a
notification handle function should be registered using 
`SetNotificationCallback` to handle all the received notification code.

## Sample Program

Code in List 1 illustrates the use of a `GridView` control. Please refer to
grid.c file of the demo program package `mg-samples` of this guide for complete
source code.


List 1 Use of `GridView` Control

```
```



![alt](figures/37.1.jpeg)

Figure 1 Use of a `GridView` control


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
