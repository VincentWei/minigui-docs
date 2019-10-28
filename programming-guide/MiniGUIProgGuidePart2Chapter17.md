# 其他相关类
# Chapter 16 of Part 2 Other Related Classes


本章介绍一些被mGNCS非控件类。它们是被设计出来提供给控件类使用。

This chapter introduces some mGNCS non control classes. They are designed to
provide for the control class to use.

## `mReferencedObj`
该类封装一个自动计数，允许对象被传递时通过自动引用来控制该对象的生命周期。

The class encapsulate an automatic counting, allowing to control the life 
circle of the object through automatic quoting when the object is transferred.

该类主要用于一些非控件类上，例如mToolItem, `mPropMenuMgr等类`

The class is mainly used on some non control classes, such as the class of
`mToolItem` and `mPropMenuMgr` etc.

- 继承关系

- Inheritance relation

- `mObject`
* `mRefrencedObj`

- 直接子类

- Direct child class

- <a href="#m_PopMenuMgr">mPropMenuMgr</a>
- <a href="#m_ToolItem">mToolItem</a>
- <a href="#m_ToolImage">mToolImage</a>

### `mReferencedObj方法`
### Method of `mReferencedObj`

- 引用相关的接口，有两个：

- Quote related ports, and there are two:

```cpp
   int addRef(mReferencedObj* self);
   int release(mReferencedObj* self);
```
`addRef自动给计数加1,并返回新的计数`。
release将自动给计数减1,并返回新计数；如果计数为0,自动调用destroy方法，删除该对象，包括该对象的内存。 
*mReferenceObj及其派生类需要调用 ==NEW== 或者 ==NEWEX== 宏来创建* ，因为release方法会调用 ==DELETE==
宏来释放创建的对象。 派生类可以通过覆盖release方法，来改变对象的释放方式。

`addRef` automatically adds 1 to the counting, and returns new counting. 
release will automatically reduce 1 for the counting, and returns new counting;
if the counting is 0, automatically call destroy method, delete the object,
including memory of the object. `mReferenceObj` and its derived class need to
call `NEW` or `NEWEX` macro to create, because release method will call 
`DELETE` macro to release the created object. The derived class can change the
release mode of the object through covering release method.

### `mReferencedObj示例`
### Example of `mReferencedObj`
%RED%该类为抽象类，不能直接使用%ENDCOLOR%

%RED%The class is abstract class, and cannot be used directly%ENDCOLOR%

## `mPopMenuMgr`

`mPopMenuMgr保存了PropMenu的信息，它能够`：
- 随时创建一个PopMenu供使用
- 可以取得部分MenuItem的信息，填充到MENUITEMINFO结构中，提供给MiniGUI的相关函数使用

`mPopMenuMgr` stores the information of `PropMenu`, and it can:
- Create a `PopMenu` at any time for use
- Partial `MenuItem` information can be obtained to fill into `MENUITEMINFO`
structure, and provide for the related functions of MiniGUI to use

- 继承关系

- Inheritance relation

- `mObject`
* <a href="#m_ReferencedObj">mReferencedObj</a>
* `mPopMenuMgr`

### `mPopMenuMgr方法`
### Method of `mPopMenuMgr`

- 向mPopMenuMgr添加一个MenuItem的方法

- Method of adding a `MenuItem` to `mPopMenuMgr`

```cpp
BOOL addItem(mPropMenuMgr *self , \
                          int type, \
                          const char * str, \
                          PBITMAP bmp, \
                          int id, \
                          int state,  \
                          mPopMenuMgr *subMenu, \
                          DWORD add_data);
```
- 参数
* type - 菜单项类型，同MiniGUI `MENUITEMINFO的定义`
* `MTF_STRING`
* `MTF_BITMAP`
* `MTF_BMPSTRING`
* `MTF_RADIOCHECK`
* `MTF_MARKCHECK`
* `MTF_SEPARATOR`
* str - Item 的caption，在type == `MTF_STRING或MTF_BMPSTRING有效`
* bmp - item的位图，在type == `MTF_BITMAP或MTF_BMPSTRING有效`
* id - item的id, *必须* 标记一个id
* state - item状态，同 MiniGUI `MENUITEMINFO的定义`
* `MFS_GRAYED`
* `MFS_DISABLED`
* `MFS_CHECKED`
* `MFS_ENABLED`
* `MFS_UNCHECKED`
* `subMenu` - 子菜单管理器
* `add_data` - 用户附件数据
- return : `TRUE/FALSE`

- 创建一个PopMenu，返回该Menu的句柄

- Parameter
* type – menu item type, same as the definition of MiniGUI `MENUITEMINFO`
* `MTF_STRING`
* `MTF_BITMAP`
* `MTF_BMPSTRING`
* `MTF_RADIOCHECK`
* `MTF_MARKCHECK`
* `MTF_SEPARATOR`
* caption of str – Item, valid when type == `MTF_STRING` or `MTF_BMPSTRING`
* Bit map of bmp – item, valid when type == `MTF_BITMAP` or `MTF_BMPSTRING`
* id of id – item, it is a must to mark an id
* state – item status, same as the definition of MiniGUI `MENUITEMINFO`
* `MFS_GRAYED`
* `MFS_DISABLED`
* `MFS_CHECKED`
* `MFS_ENABLED`
* `MFS_UNCHECKED`
* `subMenu` - sub menu manager
* `add_data` – additional data of the user
- return : `TRUE/FALSE`

- Create a `PopMenu`, return the sentence handle of the Menu

```cpp
HMENU createMenu(mPopMenuMgr *self);
```

- 自动创建并弹出一个PopMenu

- Automatically create and pop up a Pop Menu

```cpp
void popMenu(mPopMenuMgr *self, mObject *owner);
```
- params:
* owner 指出PopMenu 相关关联的对象， 它必须是一个mWidget或者其子类。*PopMenu将发送MSG_COMMAND给owner*
- return : 无

- 添加一个分割条到MenuItem中去

- params:
* owner points out `PopMenu` related object, which must be a `mWidget` or its
child class, *PopMenu will send `MSG_COMMAND` to owner*
- return : None

- Add a segmentation bar to `MenuItem`

```cpp
BOOL addSeparator(mPopMenuMgr * self);
```

- 获取指定MenuItem的信息

- Get information of appointed `MenuItem`

```cpp
 BOOL getMenuItem(mPopMenuMgr * self, int idx, MENUITEMINFO *pmii, BOOL byCommand);
```
- 将指定MenuItem的信息填充到MENUITEMINFO中去
- params:
* idx - menuitem的索引或者id
* pmii - 输出参数
* `byCommand` : `TRUE` - idx为menu item的id; `FALSE` - idx为 menu item的索引
- return : `TRUE` / `FALSE`

- Fill information of appointed `MenuItem` to `MENUITEMINFO`
- params:
* idx - index or id of menuitem
* pmii – output parameter
* `byCommand` : `TRUE` – idx is id of menu item; `FALSE` – idx is index of menu
item 
- return : `TRUE` / `FALSE`

### `mPopMenuMgr示例`
### Example of `mPopMenuMgr`
参见<a href="MStudioMGNCSV1dot0PGP2C5#m_MenuButton">mMenuButton</a>的示例

Refer to the example of <a
href="MStudioMGNCSV1dot0PGP2C5#m_MenuButton">mMenuButton</a> 

## `mToolImage`
`mToolImage是为mToolItem提供图片的类。该类封装了各种类型的图片，以方便用户选用`

`mToolImage` is the class providing images to `mToolItem`. The class
encapsulates all types of images for the convenience of the users to select

- 继承关系

- Inheritance relation

- `mObject`
* <a href="#m_ReferencedObj">mReferencedObj</a>
* `mToolImage`

### `mToolImage方法`
### Method of `mToolImage`

`mToolImage的方法是开放的，下面提供的函数都是可以直接调用的`

The method of `mToolImage` is open, and the functions provided below can be
called directly

- 从一个图片对象创建新的mToolImage对象

- Create new `mToolImage` object from an image object
```cpp
mToolImage * ncsNewToolImage(PBITMAP pbmp, int cell_count, BOOL autoUnload, BOOL bVert);
```
- params
* pbmp : 图像的源
* `cell_count:` pbmp包含的小图像的个数
* `autoUnload` : 自动调用UnloadBitmap删除该图像
* `bVert` : 小图像的排列是否是垂直的
- return : `mToolImage指针`

- 从一个图片文件创建mToolImage对象

- params
* pbmp : source of image
* `cell_count:` number of small images that pbmp contains
* `autoUnload` : automatically call `UnloadBitmap` to delete the image
* `bVert` : if arrangement of small images is vertical
- return : `mToolImage` pointer

- Create `mToolImage` object from an image file

```cpp
mToolImage * ncsNewToolImageFromFile(const char *fileName, \
                                                                       int cell_count, \
                                                                       BOOL autoUnload, \
                                                                       BOOL bVert);
```

- 释放一个mToolImage对象

- Release a `mToolImage` object
```cpp
void ncsFreeToolImage(mToolImage *mti);
```

- 绘制mToolImage管理的指定位置的图片

- Draw image of appointed position managed by `mToolImage`
```cpp
  BOOL ncsDrawToolImageCell(mToolImage *mti, HDC hdc, int idx, const RECT *prc);
```
- params:
* mti : `mToolImage指针`
* hdc : 目标DC句柄
* idx : 小图像索引
* prc: 目标矩形
- return `TRUE/FALSE`

- params:
* mti : `mToolImage` pointer
* hdc : objective `DC` sentence handle
* idx : small image index
* prc: objective rectangle
- return `TRUE/FALSE`


对于用户来说，主要使用创建和删除相关的函数, 绘制函数是由ToolItem使用的

For the users, mainly creating and deleting related functions are used, and 
draw function is used by `ToolItem`

### `mToolImage示例`
### Example of `mToolImage`

## `mToolItem`

`mToolItem是mToolbar的item的基类。这个类以及它的派生类是不公开的。用户只需要通过对外提供的API，自动创建即可`。

`mToolItem` is the basic class of item of `mToolbar`. The class and its derived
class are not public. Users only need to automatically create through `API`
provided externally.

`mToolbar也将自动管理mToolItem的删除`

`mToolbar` also delete the ones automatically managing `mToolItem`

### `mToolItem的类型`
### Type of `mToolItem`
`mToolItem有很多子类，对外接口上，表现为各种类型，这些定义如下`：

`mToolItem` has many child classes. In external interface, it is manifested as
all kinds of types, and these definitions are as below:

```cpp
enum mToolItemType{
    NCS_UNKNOWNTOOLITEM = 0,
    NCS_PUSHTOOLITEM,
    NCS_MENUTOOLITEM,
    NCS_WIDGETTOOLITEM,
    NCS_SEPARATORTOOLITEM
};
```
可以通过以下函数来检测一个ToolItem的类型

Type of a `ToolItem` can be detected through the function below

- int `ncsGetToolItemType(void` *toolitem);
- 获取ToolItem的类型

- int `ncsGetToolItemType(void` *toolitem);
- Get the type of `ToolItem`

以下函数可以快速检测一个item的类型

The function below can rapidly detect the type of an item

- `BOOL` `ncsIsPushToolItem(void` *toolitem);
- `BOOL` `ncsIsMenuToolItem(void` *toolitem);
- `BOOL` `ncsIsSeparatorToolItem(void` *toolitem);
- `BOOL` `ncsIsWidgetToolItem(void` *toolitem);

### `mToolItem创建和删除`
### Creation and Deletion of `mToolItem`

- 创建一个PushToolItem

- Create a `PushToolItem`

```cpp
 void * ncsCreatePushToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
- params:
* img : `mToolImage` 指针,可以为NULL
* str : 文字指针，可以为NULL, 但，*img和str中必须有一个不为NULL*
* flags: 定义image和str的关系
* `NCS_TOOLITEM_FLAG_TEXT_LEFT/NCS_TOOLITEM_FLAG_TEXT_UP`, 文本在左或者上，默认为右或者下
* `NCS_TOOLITEM_FLAG_VERT`, image和str垂直排列，默认是水平排列
- return : item 指针
- 创建一个Menu Tool Item

- params:
* img : `mToolImage` pointer, can be `NULL`
* str : literal pointer, can be `NULL`, but either *img or str must not be 
`NULL`* 
* flags: define the relation between image and str
* `NCS_TOOLITEM_FLAG_TEXT_LEFT/NCS_TOOLITEM_FLAG_TEXT_UP`, the text is on the
left or top, default is right or bottom
* `NCS_TOOLITEM_FLAG_VERT`, image and str are vertically arranged, and it is
horizontal arrangement by default
- return : item pointer
- Create a Menu Tool Item

```cpp
void * ncsCreateMenuToolItem(int id, \
                                                     mToolImage * img, \
                                                     const char * str, \
                                                     UINT flags, \
                                                     mPopMenuMgr * menu);
```
- 创建一个MenuToolItem, 参数menu为一个<a href="#m_PopMenuMgr">mPopMenuMgr</a>, 其他参数同上

- 创建一个Check Tool Item

- Create a `MenuToolItem`, parameter menu is a `mPopMenuMgr`, and other
parameters are as above

- Create a Check Tool Item
```cpp
void * ncsCreateCheckToolItem(int id, \
                                                      mToolImage * img, \
                                                      const char * str, \
                                                      UINT flags, \
                                                      int state);
```
- 参数同ncsCreatePushToolItem

- 创建一个Radio Tool Item

- Parameter is same as `ncsCreatePushToolItem`

- Create a radio Tool Item
```cpp
void * ncsCreateRadioToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
- 参数同ncsCreatePushToolItem。
*RadioToolItem是自动分组的，从第一个或者上一个分割符开始到最后一个或者下个分割符结束直接的所有RadioToolItem是互斥的* 

- 创建一个包含mWidget指针的ToolItem

- Parameter is same as `ncsCreatePushToolItem`. *RadioToolItem is automatically
grouped, starting from the first or previous separator and ending to the final
or next separator, direct all `RadioToolItem` are mutually excluding*

- Create a `ToolItem` containing `mWidget` pointer
```cpp
void * ncsCreateWidgetToolItem(mWidget * widget);
```
- params
* widget : `mWidget对象指针`
- return : item指针

- 创建一个分割符

- params
* widget : `mWidget` object pointer
- return : item pointer

- Create a separator
```cpp
void * ncsCreateSeparatorItem(void);
```
- return item指针

- return item pointer

### 其他mToolItem函数
### Other `mToolItem` Functions
`mToolItem还提供一些其他的函数，用于对ToolItem进行操作`

`mToolItem` provides some other functions, used to operate `ToolItem`

- 获取或者设置ToolItem的ID

- Get or set `ID` of `ToolItem`
```cpp
int ncsToolItem_getId(void *self)

int ncsToolItem_setId(void *self, int id);
```
- 如果不能设置或者不能获取，则返回-1

- 获取或者设置CheckToolItem的Check状态

- If it cannot set or cannot get, return -1

- Get or set Check status of `CheckToolItem`

```cpp
BOOL ncsToolItem_setCheck(void *self, int check_state);
int ncsToolItem_getCheck(void *self);
```
- 只针对Check/RadioToolItem起效。当对其他ToolItem调用ncsToolItem_getCheck时，将永远返回unchecked状态

- 对MenuToolItem弹出菜单

- Only valid aiming at Check/RadioToolItem. When calling `ncsToolItem_getCheck`
for other `ToolItem`, unchecked status will be returned forever

- Pop up menu for `MenuToolItem`
```cpp
 BOOL ncsToolItem_showMenu(void*self, mObject *owner);
```
- 仅针对menu Tool item, owner为一个mWidgt*对象

- Only aim at menu Tool item, owner is a `mWidgt`* object

### `mToolItem示例`
### Example of `mToolItem`



[Index](MStudioMGNCSV1dot0PGP2C15][Previous]] < [[MStudioMGNCSV1dot0PG) > 



-- Main.XiaodongLi - 22 Feb 2010

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
