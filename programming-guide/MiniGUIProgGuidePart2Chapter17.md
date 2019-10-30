# Other Classes

- [`mReferencedObj`](#mreferencedobj)
   + [Method of `mReferencedObj`](#method-of-mreferencedobj)
   + [Example of `mReferencedObj`](#example-of-mreferencedobj)
- [`mPopMenuMgr`](#mpopmenumgr)
   + [Method of `mPopMenuMgr`](#method-of-mpopmenumgr)
   + [Example of `mPopMenuMgr`](#example-of-mpopmenumgr)
- [`mToolImage`](#mtoolimage)
   + [Method of `mToolImage`](#method-of-mtoolimage)
   + [Example of `mToolImage`](#example-of-mtoolimage)
- [`mToolItem`](#mtoolitem)
   + [Type of `mToolItem`](#type-of-mtoolitem)
   + [Creation and Deletion of `mToolItem`](#creation-and-deletion-of-mtoolitem)
   + [Other `mToolItem` Functions](#other-mtoolitem-functions)
   + [Example of `mToolItem`](#example-of-mtoolitem)


This chapter introduces some mGNCS non control classes. They are designed to
provide for the control class to use.

## `mReferencedObj`

The class encapsulate an automatic counting, allowing to control the life
circle of the object through automatic quoting when the object is transferred.

The class is mainly used on some non control classes, such as the class of
`mToolItem` and `mPropMenuMgr` etc.

- Inheritance relation
- `mObject`
   * `mRefrencedObj`

- Direct child classes
   - `mPropMenuMgr`
   - `mToolItem`
   - `mToolImage`

### Method of `mReferencedObj`

- Quote related ports, and there are two:

```cpp
   int addRef(mReferencedObj* self);
   int release(mReferencedObj* self);
```

`addRef` automatically adds 1 to the counting, and returns new counting.
release will automatically reduce 1 for the counting, and returns new counting;
if the counting is 0, automatically call destroy method, delete the object,
including memory of the object. `mReferenceObj` and its derived class need to
call `NEW` or `NEWEX` macro to create, because release method will call
`DELETE` macro to release the created object. The derived class can change the
release mode of the object through covering release method.

### Example of `mReferencedObj`

The class is an abstract class, and cannot be used directly.

## `mPopMenuMgr`

`mPopMenuMgr` stores the information of `PropMenu`, and it can:
- Create a `PopMenu` at any time for use
- Partial `MenuItem` information can be obtained to fill into `MENUITEMINFO`
structure, and provide for the related functions of MiniGUI to use

- Inheritance relation

- `mObject`
   * `mReferencedObj`
   * `mPopMenuMgr`

### Method of `mPopMenuMgr`

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
- return: `TRUE` or `FALSE`

- Create a `PopMenu`, return the sentence handle of the Menu

```cpp
HMENU createMenu(mPopMenuMgr *self);
```

- Automatically create and pop up a Pop Menu

```cpp
void popMenu(mPopMenuMgr *self, mObject *owner);
```
- params:
   * owner points out `PopMenu` related object, which must be a `mWidget` or its
child class, *PopMenu will send `MSG_COMMAND` to owner*
- return : None

- Add a segmentation bar to `MenuItem`

```cpp
BOOL addSeparator(mPopMenuMgr * self);
```

- Get information of appointed `MenuItem`

```cpp
 BOOL getMenuItem(mPopMenuMgr * self, int idx, MENUITEMINFO *pmii, BOOL byCommand);
```

- Fill information of appointed `MenuItem` to `MENUITEMINFO`
- params:
   * idx - index or id of menuitem
   * pmii – output parameter
   * `byCommand` : `TRUE` – idx is id of menu item; `FALSE` – idx is index of menu
   item
- return : `TRUE` / `FALSE`

### Example of `mPopMenuMgr`

Refer to the example of [`mMenuButton`](MiniGUIProgGuidePart2Chapter06.md#mmenubutton)

## `mToolImage`

`mToolImage` is the class providing images to `mToolItem`. The class
encapsulates all types of images for the convenience of the users to select

- Inheritance relation

- `mObject`
   * `mReferencedObj`
      * `mToolImage`

### Method of `mToolImage`

The method of `mToolImage` is open, and the functions provided below can be
called directly.

- Create new `mToolImage` object from an image object

```cpp
mToolImage * ncsNewToolImage(PBITMAP pbmp, int cell_count, BOOL autoUnload, BOOL bVert);
```
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

- Release a `mToolImage` object

```cpp
void ncsFreeToolImage(mToolImage *mti);
```

- Draw image of appointed position managed by `mToolImage`

```cpp
  BOOL ncsDrawToolImageCell(mToolImage *mti, HDC hdc, int idx, const RECT *prc);
```

- params:
   * mti : `mToolImage` pointer
   * hdc : objective `DC` sentence handle
   * idx : small image index
   * prc: objective rectangle
- return `TRUE` or `FALSE`

For the users, mainly creating and deleting related functions are used, and
draw function is used by `ToolItem`

### Example of `mToolImage`

## `mToolItem`

`mToolItem` is the basic class of item of `mToolbar`. The class and its derived
class are not public. Users only need to automatically create through API
provided externally.

`mToolbar` also delete the ones automatically managing `mToolItem`

### Type of `mToolItem`

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

Type of a `ToolItem` can be detected through the function below

```cpp
int ncsGetToolItemType(void *toolitem);
```
- Get the type of `ToolItem`

The function below can rapidly detect the type of an item

```cpp
BOOL ncsIsPushToolItem(void *toolitem);
BOOL ncsIsMenuToolItem(void *toolitem);
BOOL ncsIsSeparatorToolItem(void *toolitem);
BOOL ncsIsWidgetToolItem(void *toolitem);
```

### Creation and Deletion of `mToolItem`

- Create a `PushToolItem`

```cpp
 void * ncsCreatePushToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
- params:
   * img: `mToolImage` pointer, can be `NULL`
   * str: literal pointer, can be `NULL`, but either `img` or `str` must not be `NULL`
   * flags: define the relation between `img` and `str`
      - `NCS_TOOLITEM_FLAG_TEXT_LEFT/NCS_TOOLITEM_FLAG_TEXT_UP`, the text is on the
      left or top, default is right or bottom
      - `NCS_TOOLITEM_FLAG_VERT`, image and str are vertically arranged, and it is
      horizontal arrangement by default
- return: item pointer

- Create a Menu Tool Item

```cpp
void * ncsCreateMenuToolItem(int id, \
                        mToolImage * img, \
                        const char * str, \
                        UINT flags, \
                        mPopMenuMgr * menu);
```

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

- Parameter is same as `ncsCreatePushToolItem`.

- Create a radio Tool Item

```cpp
void * ncsCreateRadioToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
- Parameter is same as `ncsCreatePushToolItem`. `RadioToolItem` is automatically
grouped, starting from the first or previous separator and ending to the final
or next separator, direct all `RadioToolItem` are mutually excluding.

- Create a `ToolItem` containing `mWidget` pointer

```cpp
void * ncsCreateWidgetToolItem(mWidget * widget);
```

- params
   * widget : `mWidget` object pointer
- return : item pointer

- Create a separator

```cpp
void * ncsCreateSeparatorItem(void);
```
- return item pointer

### Other `mToolItem` Functions

`mToolItem` provides some other functions, used to operate `ToolItem`

- Get or set ID of `ToolItem`

```cpp
int ncsToolItem_getId(void *self)

int ncsToolItem_setId(void *self, int id);
```

- If it cannot set or cannot get, return -1.

- Get or set Check status of `CheckToolItem`:

```cpp
BOOL ncsToolItem_setCheck(void *self, int check_state);
int ncsToolItem_getCheck(void *self);
```

- Only valid aiming at Check/RadioToolItem. When calling `ncsToolItem_getCheck`
for other `ToolItem`, unchecked status will be returned forever

- Pop up menu for `MenuToolItem`

```cpp
 BOOL ncsToolItem_showMenu(void*self, mObject *owner);
```

- Only aim at menu Tool item, owner is a `mWidgt*` object

### Example of `mToolItem`

----

[&lt;&lt; Invisible Control Class](MiniGUIProgGuidePart2Chapter16.md) |
[Table of Contents](README.md) |
[Graphics Device Interfaces &gt;&gt;](MiniGUIProgGuidePart3Chapter01.md)

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
