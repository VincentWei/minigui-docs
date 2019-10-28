# Chapter 4 of Part 2 Static Box Series Control Class

## Brief Introduction of Static Box Series

Static box is used to display information of figure, literal and image etc. at
specific locations of the window, such as company profile and company product
trademark etc., and it is one of the most common controls. Generally speaking,
control row of static box series does not need to conduct dynamic response to
input of the users, that is to say, it is not necessary to receive any input
(such as keyboard and mouse etc.), and there is no event of itself.

| *Control Name* | *Control name (miniStudio display name)* | *Purpose* | *NCS class name* | *Control window class `ID*` |
| Static box | Label | Display single row or multiple rows of texts | `mStatic` | `NCSCTRL_STATIC` |
| Image box | Image | Display image | `mImage` | `NCSCTRL_IMAGE` |
| Rectangle box | Rectangle | Draw rectangles | `mRect` | `NCSCTRL_RECTANGLE` |
| Group box | Group Box| Region control that can contain other controls | `mGroupbox` | `NCSCTRL_GROUPBOX` |
| Button group | Button Group| Manage `RadioButton,` realize single selection function | `mButtonGroup` | `NCSCTRL_BUTTONGROUP` |
| `LED` label | `LEDLabel|` Display `LED` characters | `mLEDLabel` | `NCSCTRL_LEDLABEL` |
| Separator | Horz/Vert Separator | Separation line, realize regional division visually | `mSeparator` | `NCSCTRL_SEPARATOR` |

The inheritance relations of static box series controls are as follows:
- `mStatic`
- `mImage`
- `mRect`
- `mGroupbox`
* `mButtonGroup`
- `mLEDLabel`
- `mSeparator`

Static box of each type inherits the property, event and method of the parent
class, therefore, in the following introduction, the inheritance part will be
ignored automatically.

## `mStatic`

![alt](figures/static_show.png)

- Function: `mStatic` is the static region control used to draw content
including texts and images etc.
- Parent class: `mWidget`
- Direct child class:
- `mImage`
- `mRect`
- `mGroupbox`
- `mLEDLabel`
- `mSeparator`

### Style of `mStatic`
None

### Property of `mStatic`
| *Property name* | *Type* | *Permission* | *Property explanation* | *Mode value* |
| `NCSP_STATIC_ALIGN` | int | `RW` | Control content horizontal alignment mode | `NCS_ALIGN_LEFT`, `NCS_ALIGN_RIGHT`, `NCS_ALIGN_CENTER` |
| `NCSP_STATIC_VALIGN` | int | `RW` | Control content vertical alignment mode | `NCS_VALIGN_TOP`, `NCS_VALIGN_BOTTOM`, `NCS_VALIGN_CENTER` |
| `NCSP_STATIC_AUTOWRAP` | int | `RW` | Control content automatic wrap | 1, 0 |

- `NCSP_STATIC_ALIGN：Set` control content as horizontal alignment mode, and
there are three kinds of values
- `NCS_ALIGN_LEFT：left` aligned, default value of horizontal alignment mode - 0
- `NCS_ALIGN_RIGHT：right` aligned – 1
- `NCS_ALIGN_CENTER：center` aligned – 2
- `NCSP_STATIC_VALIGN：set` control content as vertical alignment mode, and 
there are three kinds of values
- `NCS_VALIGN_TOP：top` aligned – 0
- `NCS_VALIGN_BOTTOM：bottom` aligned, default value of vertical alignment mode 
– 1
- `NCS_VALIGN_CENTER：center` aligned – 2
- `NCSP_STATIC_AUTOWRAP：set` static box content as automatic wrap mode or not, 
0 is single row mode, which is closing automatic wrap mode, and 1 is automatic
wrap mode


Developers can set the property of `mStatic` through the following methods
```
```

### Event of `mStatic`

At present, the static box series controls don‘t respond to any event

### Method of `mStatic`

None

### Renderer of `mStatic`

None

### Example of `mStatic`

This example demonstrates how to create static boxes of different modes to the
users. <br/>

![alt](figures/static.png)

<p align=center>List p2c4-1 static.c</p>
```
```

## `mImage`

![alt](figures/image_show.png)


- Function: load display image control in a region
- Inherited from `mStatic`
- Direct child class: none

### Property of `mImage`
| *Property Name* | *Type* | *Permission* | *Property explanation* | *Value* |
| `NCSP_IMAGE_IMAGE` | `PBITMAP` | `RW` | image control content image id, corresponds to pbmp image file pointer in mimage | None |
| `NCSP_IMAGE_IMAGEFILE` | char* | `RW` | image control content image name id, corresponds to name pointer of pbmp image | None |
| `NCSP_IMAGE_DRAWMODE` | enum | `RW` | image control drawing mode, corresponds to `mImageDrawMode` | `NCS_DM_NORMAL`, `NCS_DM_SCALED`, `NCS_DM_SCALED` |
| `NCSP_STATIC_ALIGN` | int | `RW` | Set horizontal alignment mode of image control content | `NCS_ALIGN_LEFT`, `NCS_ALIGN_RIGHT`, `NCS_ALIGN_CENTER` |
| `NCSP_STATIC_VALIGN` | int | `RW` | Set vertical alignment mode of image control content | `NCS_VALIGN_TOP`, `NCS_VALIGN_BOTTOM`, `NCS_VALIGN_CENTER` |

- `NCSP_IMAGE_DRAWMODE：set` image drawing mode, and there are three modes.
- `NCS_DM_NORMAL：display` image according to the original condition, and 
default value of the drawing mode – 0
- `NCS_DM_SCALED：stretch,` stretch the image to cover the whole static box-1
- `NCS_DM_TILED：tile,` display the image repeatedly in the whole static box-2
- `NCSP_STATIC_ALIGN：refer` to `mStatic`
- `NCSP_STATIC_VALIGN：refer` to `mStatic`

The following codes demonstrate how to set properties such as drawing mode etc.

```
```

### Event of `mImage`
None

### Method of `mImage`

None

### Example of `mImage`

This example demonstrates how to display and create image static boxes of
different drawing modes to the users<br/>

![alt](figures/image.png)

<p align=center>List p2c4-2 image.c</p>
```
```

## `mRect`

![alt](figures/rect_show.png)

- Function: this control provides the function of drawing rectangles to the
users. Through the method of setting properties, rectangles with features of
fill color, round corner and border etc. can be drawn conveniently and rapidly
- Inherited from `mStatic`
- Direct child class: none

### Property of `mRect`

| *Property name* | *Type* | *Permission* | *Explanation* ||
| `NCSP_RECT_BORDERSIZE` | int | `RW` | Thickness of rect control border, border thickness of the corresponding rectangle control, and the type is int |
| `NCSP_RECT_BORDERCOLOR` | dword | `RW` | Color of rect control border, border color of corresponding rectangle control, and the type is dword |
| `NCSP_RECT_FILLCOLOR` | dword | `RW` | Fill color of rect control, fill color of corresponding rectangle control, and the type is dword |
| `NCSP_RECT_XRADIUS` | int | `RW` | Round corner horizontal x radius of rect control, round corner radius of corresponding rectangle control, and the type is int |
| `NCSP_RECT_YRADIUS` | int | `RW` | Round corner vertical y radius of rect control, round corner radius of corresponding rectangle control, and the type is int |
| `NCSP_RECT_FILLCLR_RED` | | | |
| `NCSP_RECT_FILLCLR_GREEN` | | | |
| `NCSP_RECT_FILLCLR_BLUE` | | | |
| `NCSP_RECT_FILLCLR_ALPHA` | | | |
| `NCSP_RECT_BRDCLR_RED` | | | |
| `NCSP_RECT_BRDCLR_GREEN` | | | |
| `NCSP_RECT_BRDCLR_BLUE` | | | |
| `NCSP_RECT_BRDCLR_ALPHA` | | | |

The following codes demonstrate how to set the properties of rectangles
```
```

### Event of `mRect`
None

### Method of `mRect`
None

### Example of `mRect`

This example demonstrate how to draw all kinds of rectangles to the users<br/>

![alt](figures/rect.png)

<p align=center>List p2c4-3 rectangle.c</p>
```
```

## `mGroupbox`

![alt](figures/groupbox_show.png)


- Function: group box, this control is used to provide recognizable groups for
the other controls. Normally, group box is used to subdivide the forms 
according to functions, and grouping all the options in the group box can
provide logicalized visible prompt to the users.
- Inherited from `mStatic`
- Direct child class:
- `mButtongroup`

### Property of `mGroupbox`
None

### Event of `mGroupbox`

None

### Method of `mGroupbox`

None

### Renderer of `mGroupbox`


![alt](figures/groupbox_rdr.png)

Users can set classic, fit and fashion renderers as shown in the figure above
for group box conveniently, and for the concrete method, see the codes below,
```
```
### Example of `mGroupbox`


![alt](figures/groupbox.png)

This example demonstrate how to generate group box with renderers to the users
<p align=center>List p2c4-4 groupbox.c</p>
```
```
## `mButtonGroup`

![alt](figures/buttongroup_show.png)

- Function: this control is used to manage a group of `radioButton,` enabling
the group of `RadioButton` to mutually exclude, thus realizing single selection
function. 
- Inherited from `mGroupbox`
- Direct child class: none

### Property of `mButtonGroup`

| *Property Name* | *Type* | *Permission* | *Property explanation* |
| `NCSP_BTNGRP_SELID` | int | `RW` | Currently selected `radioButton` `ID` number |
| `NCSP_BTNGRP_SELIDX` | idx | `RW` | Currently selected `radioButton` index number |
| `NCSP_BTNGRP_SELOBJ` | `mWidget*` | `RW` | Currently selected `radioButton` pointer |


### Method of `mButtonGroup`

```
```
- Function: add a `radioButton`
- Returned value: `BOOL`

```
```
- Function: select a `radioButton`
- Returned value: `BOOL`

### Example of `mButtonGroup`

![alt](figures/buttongroup.png)

Please refer to `mRadioButton` in [Chapter 5 Button Series Control
Class](Products/MStudioMGNCSV1dot0PGENP2C5#m_RadioButton). 

## `mLEDLabel`

![alt](figures/ledstatic_show.png)

- Function: `mLEDLabel` class is the static box imitating `LED` digital nixie
tube, which is used to display `LED` characters and can be used in multiple
fields such as industrial control etc.
- Inherited from `mStatic`
- Direct child class: none

### Property of `mLEDLabel`

| *Property name* | *Type* | *Permission* | *Property explanation* |
| `NCSP_LEDLBL_COLOR` | `DWORD` | `RW` | Set the color of `LED` font, such as red is 0xFF0000FF |
| `NCSP_LEDLBL_WIDTH` | int | `RW` | Set the width of `LED` font |
| `NCSP_LEDLBL_HEIGHT` | int | `RW` | Set the height of `LED` font |

Users can use the following method to set the properties:
```
```

### Style of `mLEDLabel`

None

### Method of `mLEDLabel`

None

### Renderer of `mLEDLabel`

None

### Example of `mLEDLabel`


![alt](figures/ledlabel.png)

This example demonstrates how to display `LED` characters to the users
```
```

## `mSeparator`

![alt](figures/separator_show.png)

- Function: used to separate the item controls and conduct horizontal or
vertical separation lines of region division
- Inherited from `mStatic`
- Direct child class: none

### Property of `mSeparator`

None

### Style of `mSeparator`

| *Property name* | *Explanation* |
| `NCSS_SPRTR_VERT` | Set as vertical separation line, default by default |

Users can use the following method to set the style:
```
```

### Event of `mSeparator`

None

### Method of `mSeparator`

None

### Renderer of `mSeparator`

None

### Example of `mSeparator`


![alt](figures/separator.png)

This example demonstrates how to generate horizontal and vertical separation
lines to the users
```
```

[Next](MStudioMGNCSV1dot0PGENP2C3][Previous]] <
[[MStudioMGNCSV1dot0PGEN][Index]] > [[MStudioMGNCSV1dot0PGENP2C5)


-- Main.XiaodongLi - 24 Feb 2010


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
