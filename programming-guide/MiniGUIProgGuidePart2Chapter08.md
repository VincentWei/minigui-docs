# Chapter 7 of Part 2 Container and Its Derived Class


## Brief Introduction of Container Class Control

This class of control is the container class control accommodating other classes of controls, and the difference from panel class control is that this class of control provides default window scroll processing.

Class inheritance relation of the window and its derived class is as below:

- [mWidget ](MStudioMGNCSV1dot0PGENP2C3#mWidget)
   - [mScrollWidget](MiniGUIProgGuidePart2Chapter08#m_ScrollWidget.md)
         * [mContainer](MiniGUIProgGuidePart2Chapter08#mContainer.md)
            * [mPage](MiniGUIProgGuidePart2Chapter08#mPage.md)


## mScrollWidget

- *Control name*:  NCSCTRL_SCROLLWIDGET
- *English name*: ScrollWidget
- *Brief introduction*: All abstract basic classes including scroll function control class 
- *Schematic diagram*: %RED%Abstract class, cannot be used directly%ENDCOLOR%

### Style of mScrollWidget

It is inherited from the style of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

### Property of mScrollWidget

It is inherited from the property of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

| *Property ID* | *miniStudio name* | *Type* | *Permission* | *Explanation* |
| NCSP_SWGT_CONTWIDTH |   -   | unsigned int | RW | Content width |
| NCSP_SWGT_CONTHEIGHT |   -   | unsigned int | RW | Content height |
| NCSP_SWGT_CONTX | ContentX | int | RW | Offset value of the content in horizontal direction |
| NCSP_SWGT_CONTY | ContentY | int | RW | Offset value of the content in vertical direction |
| NCSP_SWGT_HSTEPVALUE | HStepValue | unsigned int | RW | Horizontal step value when scrolling content | 
| NCSP_SWGT_VSTEPVALUE | VStepValue | unsigned int | RW | Vertical step value when scrolling content | 
| NCSP_SWGT_VISWIDTH |   -   | unsigned int | RW | Width of the visible region |
| NCSP_SWGT_VISHEIGHT |   -   | unsigned int | RW | Height of the visible region |
| NCSP_SWGT_MARGINRECT |   -   | unsigned int | RW | Boundary rectangle |
| NCSP_SWGT_DRAWMODE | ScrollBarMode | ncsSwgtDrawMode | RW | Display mode of the scroll bar |

### Event of mScrollWidget

It is inherited from the event of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

### Method of mScrollWidget

It is inherited from the method of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

All the methods of ScrollWidget? are provided for the child class to use, please avoid using the class interface in the concrete control application.  

---++++ Coordinate Transformation Related Method

When handling scrolled window content, three kinds of coordinates are involved:
- content: coordinate with the appointed content in all the content.
- viewpoint: coordinate with the appointed content in the visible region. Influenced by the content scroll.
- window: display coordinate with the appointed content in the window. Influenced by margin region.

Content is the original coordinate of the display content, and window is the coordinate in MiniGUI  window. If you want to convert a content coordinate of the original content to window coordinate for display use, transformation is needed between the two, that is, it is necessary to firstly transform the content coordinate to viewpoint coordinate. It is like content of several pages, if displaying the content of a certain page as the current content, coordinate of a certain part of the page will start from the starting position comparative to the overall content to the starting position comparative to the page. When finally displaying the content to the window, it is necessary to carry out further transformation from viewpoint to window. That is because in the client area of the window, often a part of margin will be added to adjust the display effect. On the contrary, to transform the position of the content displayed in MiniGUI  window to the position in all the content, reversed two steps of work are necessary. 

Relation schematic diagram of the three kinds of coordinates:

<img src="%ATTACHURLPATH%/coordinate_trans.png" alt="coordinate_trans.png"/><br>

Corresponding interface of transformation between the three kinds of coordinates are:
```cplusplus
void contentToViewport(mScrollWidget *self, int *x, int *y); 
void viewportToWindow(mScrollWidget *self, int *x, int *y);
void contentToWindow(mScrollWidget *self, int *x, int *y);

void windowToViewport(mScrollWidget *self, int *x, int *y);
void viewportToContent(mScrollWidget *self, int *x, int *y);
void windowToContent(mScrollWidget *self, int *x, int *y);
```

---++++ Initialization Related Method

ScrollWidget  control class configures margin as all 0 value by default. When the child class based on the control class needs to be configured with margin different from the parent class, initMargins method can be used in constructor function to configure again. 

```cplusplus
void initMargins(mScrollWidget *self, int l, int t, int r, int b);
```

Iconview control class in construct method uses the following codes to initialize the margin of top, bottom, left and right, and the values are all 5.

```cplusplus
    _c(self)->initMargins(self, 5, 5, 5, 5);
```

---++++ Refreshment Related Method

When automatically adjusting the scroll bar region and setting configuration related to the display region, ScrollWidget needs to refresh the screen. In order to meet processing need of different controls, two callbacks are provided for the convenience of upper layer control processing. At the same time, ScrollWidget also provides realization of default processing:

```cplusplus
void moveContent(mScrollWidget *self);
void refreshRect(mScrollWidget *self, const RECT *rc);
```

- moveContent is mainly used for the update after scrolling content, such as full screen refreshment after scrolling the window.
- refreshRect is used to refresh the content of the appointed region.

---++++ Method to Getting Information

ScrollWidget provides isVisible method for child class to judge if a certain content position is visible in the current display region, so as to make the child class judge if operations such as screen scrolling etc. are necessary. At the same time, when the child class is carrying out content drawing, the content needs to be drawn in the appointed visible region. getVisRect method provides convenience for getting the maximum range of permissible drawing.

```cplusplus
BOOL (*isVisible)(mScrollWidget *self, int x, int y);
void (*getVisRect)(mScrollWidget *self, RECT *rcVis);
```

- isVisible is used to judge if the appointed content position is currently in the visible region.
- getVisRect is used to get the current visible region.

---++++ Setting Related Method

ScrollWidget and its derived class needs to carry out corresponding setting to different information when the window size changes or the content changes, therefore ScrollWidget provides the following methods:

```cplusplus
void resetViewPort(mScrollWidget *self, unsigned int visW,unsigned int visH);
void setScrollInfo(mScrollWidget *self, BOOL reDraw);
BOOL makePosVisible(mScrollWidget *self, int x, int y);
```

- resetViewport is used to readjust the size of the visible region. When the window size changes, it is necessary to use the interface to adjust the visible region.
- setScrollInfo method is provided for child class control to use. When the size of the visible region or the content region changes, carry out corresponding scroll bar information setting.
- makePosVisible is used to automatically display the appointed content position in the visible region. 

### Renderer of mScrollWidget

It is inherited from renderer of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget)

mScrollWidget does not have newly added renderer method.

## mContainer

- *Control name*:  NCSCTRL_CONTAINER
- *English name*: Container
- *Brief introduction*: Container class control with scroll support

### Style of mContainer

It is inherited from the style of <a href="#Style of m_ScrollWidget">style of mScrollWidget</a>.

### Property of mContainer

It is inherited from the <a href="#Property of m_ScrollWidget">property of mScrollWidget</a>.

### Event of mContainer

It is inherited from the <a href="#Event of m_ScrollWidget">event of mScrollWidget</a>.

### Method of mContainer

It is inherited from the <a href="#Method of m_ScrollWidget">method of mScrollWidget</a>.

---++++ Method of Adding Controls

Container provides support to mGNCS control and MiniGUI intrinsic control. If it is necessary to add a group of mGNCS controls to Container, addChildren method inherited from mWidget class can be used.

```cplusplus
BOOL addChildren(mContainer *self, NCS_WND_TEMPLATE* children, int count); 
```

```cplusplus
%INCLUDE{"%ATTACHURL%/container.c.txt" pattern="^.*?// START_OF_NCSCTRLS(.*?)// END_OF_NCSCTRLS.*"}%
```

To add a group of MiniGUI  intrinsic controls to Container, addintrinsicControls method can be used:

```cplusplus
BOOL addIntrinsicControls(mContainer *self, const PCTRLDATA pCtrl, int nCount);
```


```cplusplus
%INCLUDE{"%ATTACHURL%/container.c.txt" pattern="^.*?// START_OF_INTRINSICCTRLS(.*?)// END_OF_INTRINSICCTRLS.*"}%
```

---++++ Focus Related Method

In Container, it is often necessary to set and get the current focus control, the two methods below are provided for this:

```cplusplus
HWND setFocus(mContainer *self, int id);
HWND getFocus(mContainer *self);
```

- setFocus sets focus control through control ID.
- getFocus gets the sentence handle of the current focus control.

---++++ Other Methods

Container provides adjustContent method to allow the application to carry out the function of adjusting its own size through its content instead of displaying range through Container control control. getPanel method can get the hosting window sentence handle of the current Container content.

```cplusplus
HWND getPanel(mContainer *self);
void adjustContent(mContainer *self);
```

### Renderer of mContainer

It is inherited from the <a href="#Renderer of m_ScrollWidget">renderer of mScrollWidget</a>.

mContainer does not have newly added renderer method.

### Example of mContainer

This example demonstrates how to use Container to realize jumping between multiple controls exceeding the window size to the users.

<p align=center>
<img src="%ATTACHURLPATH%/container_demo.png" alt="container_demo.png"/><br>
Figure p2c6-1 Output of Container Program
</p>

<p align=center>List p2c7-1 container.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/container.c.txt"}%
```

## mPage

- *Control name*:  NCSCTRL_PAGE
- *English name*: Page
- *Brief introduction*: Property page control, used to display same class information and window content.

### Style of mPage

It is inherited from <a href="#Style of mContainer">style of mContainer</a>.

### Property of mPage

It is inherited from <a href="#Property of mContainer">propertyof mContainer</a>.

### Event of mPage

It is inherited from <a href="#Event of mContainer">event of mContainer</a>.

### Method pf mPage

It is inherited from <a href="#Method of mContainer">methodof mContainer</a>.

### Renderer of mPage

It is inherited from <a href="#Renderer of mContainer">renderer of mContainer</a>.

mPage does not have newly added renderer method

### Example of mPage


[Next](MStudioMGNCSV1dot0PGENP2C6][Previous]] < [[MStudioMGNCSV1dot0PGEN][Index]] > [[MStudioMGNCSV1dot0PGENP2C8)




-- Main.XiaodongLi - 28 Feb 2010

