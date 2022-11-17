# 其他相关类

本章介绍一些被 mGNCS 非控件类。它们是被设计出来提供给控件类使用。

## 1 `mReferencedObj`

该类封装一个自动计数，允许对象被传递时通过自动引用来控制该对象的生命周期。

该类主要用于一些非控件类上，例如 `mToolItem`, `mPropMenuMgr` 等类

- 继承关系
   - `mObject`
      - `mRefrencedObj`
- 直接子类
   - [mPropMenuMgr](#2-mpropmenumgr)
   - [mToolItem](#4-mtoolitem)
   - [mToolImage](#3-mtoolimage)

### 1.1 `mReferencedObj` 方法

- 引用相关的接口，有两个：

```c
   int addRef(mReferencedObj* self);
   int release(mReferencedObj* self);
```

`addRef` 自动给计数加1,并返回新的计数。 release 将自动给计数减 1,并返回新计数；如果计数为 0,自动调用 destroy 方法，删除该对象，包括该对象的内存。 `mReferenceObj` 及其派生类需要调用 `NEW` 或者 `NEWEX` 宏来创建 ，因为 release 方法会调用 `DELETE` 宏来释放创建的对象。 派生类可以通过覆盖 release 方法，来改变对象的释放方式。

### 1.2 `mReferencedObj` 示例

%RED%该类为抽象类，不能直接使用%ENDCOLOR%

## 2 `mPopMenuMgr`

`mPopMenuMgr` 保存了 `PropMenu` 的信息，它能够：

- 随时创建一个 `PopMenu` 供使用
- 可以取得部分 `MenuItem` 的信息，填充到 `MENUITEMINFO` 结构中，提供给 MiniGUI 的相关函数使用

- 继承关系
   - `mObject`
      - [mReferencedObj](#1-mreferencedobj)
         - `mPopMenuMgr`

### 2.1 `mPopMenuMgr` 方法

- 向 `mPopMenuMgr` 添加一个 `MenuItem` 的方法

```c
BOOL addItem(mPropMenuMgr *self , \
                          int type, \
                          const char * str, \
                          PBITMAP bmp, \
                          int id, \
                          int state,  \
                          mPopMenuMgr *subMenu, \
                          DWORD add_data);
```
-  - 参数
      - `type` - 菜单项类型，同 MiniGUI `MENUITEMINFO` 的定义
         - `MTF_STRING`     
         - `MTF_BITMAP`
         - `MTF_BMPSTRING`
         - `MTF_RADIOCHECK`
         - `MTF_MARKCHECK`
         - `MTF_SEPARATOR`
      - `str` - `Item` 的 `caption`，在 `type` == `MTF_STRING` 或 `MTF_BMPSTRING` 有效
      - `bmp` - `item` 的位图，在 `type` == `MTF_BITMAP` 或 `MTF_BMPSTRING` 有效
      - `id` - `item` 的 `id`, 必须标记一个 `id`
      - `state` - `item` 状态，同 MiniGUI `MENUITEMINFO` 的定义
         - `MFS_GRAYED`
         - `MFS_DISABLED`
         - `MFS_CHECKED`
         - `MFS_ENABLED`
         - `MFS_UNCHECKED`
      - `subMenu` -  子菜单管理器
      - `add_data` - 用户附件数据
   - `return` : `TRUE`/`FALSE`
-  创建一个 `PopMenu`，返回该 `Menu` 的句柄

```c
HMENU createMenu(mPopMenuMgr *self);
```

-  自动创建并弹出一个 `PopMenu`

```c
void popMenu(mPopMenuMgr *self, mObject *owner);
```
-  - `params`:
      - `owner` 指出 `PopMenu` 相关关联的对象，它必须是一个 `mWidget` 或者其子类。`PopMenu` 将发送 `MSG_COMMAND` 给 `owner`
   -  `return` : 无

-  添加一个分割条到 `MenuItem` 中去

```c
BOOL addSeparator(mPopMenuMgr * self);
```

-  获取指定 `MenuItem` 的信息

```c
 BOOL getMenuItem(mPopMenuMgr * self, int idx, MENUITEMINFO *pmii, BOOL byCommand);
```
-  - 将指定 `MenuItem` 的信息填充到 `MENUITEMINFO` 中去
   - `params`:
      - `idx` - `menuitem` 的索引或者 `id`
      - `pmii` - 输出参数
      - `byCommand` : `TRUE - idx` 为 `menu item` 的 id; `FALSE - idx` 为 `menu item` 的索引
   - `return` : `TRUE` / `FALSE`

### 2.2 `mPopMenuMgr` 示例

参见 [mMenuButton](p2c06#mMenuButton) 的示例

## 3 `mToolImage`

`mToolImage` 是为 `mToolItem` 提供图片的类。该类封装了各种类型的图片，以方便用户选用

- 继承关系
   - `mObject`
      - [mReferencedObj](#1-mreferencedobj)
         -  `mToolImage`

### 3.1 `mToolImage` 方法

`mToolImage` 的方法是开放的，下面提供的函数都是可以直接调用的

- 从一个图片对象创建新的 `mToolImage` 对象

```c
mToolImage * ncsNewToolImage(PBITMAP pbmp, int cell_count, BOOL autoUnload, BOOL bVert);
```
-  - `params`
      - `pbmp` : 图像的源
      - `cell_count`: `pbmp` 包含的小图像的个数
      - `autoUnload` : 自动调用 `UnloadBitmap` 删除该图像
      - `bVert` : 小图像的排列是否是垂直的
   - `return` : `mToolImage` 指针

-  从一个图片文件创建 `mToolImage` 对象

```c
mToolImage * ncsNewToolImageFromFile(const char *fileName, \
                                                                       int cell_count, \
                                                                       BOOL autoUnload, \
                                                                       BOOL bVert);
```

- 释放一个 `mToolImage` 对象

```c
void ncsFreeToolImage(mToolImage *mti);
```

-  绘制 `mToolImage` 管理的指定位置的图片

```c
  BOOL ncsDrawToolImageCell(mToolImage *mti, HDC hdc, int idx, const RECT *prc);
```
-  - `params`:
      - `mti` : `mToolImage` 指针
      - `hdc` : 目标 `DC` 句柄
      - `idx` : 小图像索引
      - `prc`` : 目标矩形
   - `return` `TRUE`/`FALSE`

对于用户来说，主要使用创建和删除相关的函数, 绘制函数是由 `ToolItem` 使用的

### 3.2 `mToolImage` 示例

## 4 `mToolItem`

`mToolItem` 是 `mToolbar` 的 `item` 的基类。这个类以及它的派生类是不公开的。用户只需要通过对外提供的API，自动创建即可。

`mToolbar` 也将自动管理 `mToolItem` 的删除

### 4.1 `mToolItem` 的类型

`mToolItem` 有很多子类，对外接口上，表现为各种类型，这些定义如下：

```c
enum mToolItemType{
	NCS_UNKNOWNTOOLITEM = 0,
	NCS_PUSHTOOLITEM,
	NCS_MENUTOOLITEM,
	NCS_WIDGETTOOLITEM,
	NCS_SEPARATORTOOLITEM
};
```

可以通过以下函数来检测一个 `ToolItem` 的类型

- int ncsGetToolItemType(void *toolitem);
   - 获取 `ToolItem` 的类型

以下函数可以快速检测一个 item 的类型

- BOOL ncsIsPushToolItem(void *toolitem);
- BOOL ncsIsMenuToolItem(void *toolitem);
- BOOL ncsIsSeparatorToolItem(void *toolitem);
- BOOL ncsIsWidgetToolItem(void *toolitem);

### 4.2 `mToolItem` 创建和删除

-  创建一个 `PushToolItem`

```c
 void * ncsCreatePushToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
-  - `params`:
      - img : `mToolImage` 指针,可以为 `NULL`
      - str : 文字指针，可以为 `NULL`, 但，`img` 和 `str` 中必须有一个不为 `NULL`
      - flags: 定义 image 和 str 的关系
         - `NCS_TOOLITEM_FLAG_TEXT_LEFT`/`NCS_TOOLITEM_FLAG_TEXT_UP`, 文本在左或者上，默认为右或者下
         -  `NCS_TOOLITEM_FLAG_VERT`, image 和 str 垂直排列，默认是水平排列
   - `return` : item 指针
- 创建一个 Menu Tool Item

```c
void * ncsCreateMenuToolItem(int id, \
                                                     mToolImage * img, \
                                                     const char * str, \
                                                     UINT flags, \
                                                     mPopMenuMgr * menu);
```
-  - 创建一个 `MenuToolItem`, 参数 menu 为一个 [mPopMenuMgr](#2-mpopmenumgr), 其他参数同上
- 创建一个 Check Tool Item

```c
void * ncsCreateCheckToolItem(int id, \
                                                      mToolImage * img, \
                                                      const char * str, \
                                                      UINT flags, \
                                                      int state);
```
-  - 参数同 `ncsCreatePushToolItem`
- 创建一个 Radio Tool Item

```c
void * ncsCreateRadioToolItem(int id, mToolImage * img, const char * str, UINT flags);
```
-  - 参数同 `ncsCreatePushToolItem`。 `RadioToolItem` 是自动分组的，从第一个或者上一个分割符开始到最后一个或者下个分割符结束直接的所有 `RadioToolItem` 是互斥的 

- 创建一个包含 `mWidget` 指针的 `ToolItem`

```c
void * ncsCreateWidgetToolItem(mWidget * widget);
```
-  - `params`
      - `widget` : `mWidget` 对象指针 
   - `return` : `item` 指针
- 创建一个分割符

```c
void * ncsCreateSeparatorItem(void);
```
-  - return item 指针

### 4.3 其他 `mToolItem` 函数

`mToolItem` 还提供一些其他的函数，用于对 `ToolItem` 进行操作

- 获取或者设置 `ToolItem` 的 ID

```c
int ncsToolItem_getId(void *self)

int ncsToolItem_setId(void *self, int id);
```
-  - 如果不能设置或者不能获取，则返回 -1
- 获取或者设置 `CheckToolItem` 的 Check 状态

```c
BOOL ncsToolItem_setCheck(void *self, int check_state);
int ncsToolItem_getCheck(void *self);
```
-  - 只针对 `Check`/`RadioToolItem` 起效。当对其他 `ToolItem` 调用 `ncsToolItem_getCheck` 时，将永远返回 `unchecked` 状态
- 对 `MenuToolItem` 弹出菜单

```c
 BOOL ncsToolItem_showMenu(void*self, mObject *owner);
```
-  - 仅针对 menu Tool item, owner 为一个 `mWidgt*` 对象

### 4.4 `mToolItem` 示例
