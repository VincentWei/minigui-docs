# 其他高级控件类

## 1 其他高级控件类简介

该类控件主要是视图系列控件，多用于显示各种不同类型的列表项信息。

其他高级控件类的类继承关系如下：

- [mWidget](MiniGUIProgGuidePart2Chapter04-zh.md#3-mwidget)
   - [mScrollWidget](MiniGUIProgGuidePart2Chapter08-zh.md#3-mscrollwidget)
      - [mItemView](#6-mitemview)
         - [mListBox](#8-mlistbox)
         - [mScrollView](#7-mscrollview)
         - [mIconView](#9-miconview)
         - [mListView](#10-mlistview)

在高级控件类中将列表项作为一个对象来管理，不同控件使用到的列表项对象不同，各自的继承关系如下：

- [mObject](MiniGUIProgGuidePart2Chapter04-zh.md#1-mobject)
   - [mItem](#2-mItem)
      - [mItemManager](#3-mitemmanager)
         - [mListItem](#4-mlistitem)
      - [mListColumn](#5-mlistcolumn)

我们首先介绍各列表项对象，再具体介绍各控件类。

## 2 `mItem`

`mItem` 对象是所有列表项的基类，提供一系列基本的访问方法。直接使用该对象的有 `mListBox`, `mScrollView` 和 `mIconView` 等控件类。

### 2.1 `mItem` 状态

| 状态名 | 说明 |
|:------|:-----|
| `NCSF_ITEM_NORMAL` | 条目状态：正常 |
| `NCSF_ITEM_SELECTED` | 条目状态：选中 |
| `NCSF_ITEM_DISABLED` | 条目状态：禁用 |
| `NCSF_ITEM_USEBITMAP` | 条目状态：包含位图，与 `NCSF_ITEM_USEICON` 互斥 |
| `NCSF_ITEM_USEICON` | 条目状态：包含图标，与 `NCSF_ITEM_USEBITMAP` 互斥 |


### 2.2 `mItem` 属性

| 属性 ID | 类型 | 权限 | 说明 |
|:-------|:-----|:----|:-----|
| `NCSP_ITEM_HEIGHT` | int | `RW` | 条目当前高度 |
| `NCSP_ITEM_FLAGS` | `DWORD` | `RW` | 条目状态 |


### 2.3 `mItem` 方法

继承自[[MStudioMGNCSV1dot0PGP2C3#mObject][mObject的方法]]

一个条目可以包含多种内容信息，如文本、图片等等。提供的基础方法主要有：

```c
    BOOL isSelectedItem(mItem *self); 
    BOOL isEnabledItem(mItem *self);  
    void setItemEditor(mItem *self, hEditor editor); 
    hEditor getItemEditor(mItem *self);  
    void setItemAddData(mItem *self, DWORD addData);
    DWORD getItemAddData(mItem *self);             
    void setItemImage(mItem *self, DWORD image);   
    DWORD getItemImage(mItem *self);          
    void setItemFlags(mItem *self, DWORD flags);  
    DWORD getItemFlags(mItem *self);    
    BOOL setItemHeight(mItem *self, int height);
    int getItemHeight(mItem *self);   
    BOOL setItemString(mItem *self, const char* string);
    char* getItemString(mItem *self);
```

- `isSelectedItem`：判断当前条目是否处于选中状态。
- `isEnabledItem`：判断当前条目是否处于使能状态。
- `setItemString`：设置条目文本。
- `getItemString`：获取条目当前文本。
- `setItemHeight`：设置条目高度。
- `getItemHeight`：获取条目高度。
- `setItemFlags`：设置条目状态。
- `getItemFlags`：获取条目状态。
- `setItemImage`：设置条目图标。
- `getItemImage`：获取条目图标。
- `setItemAddData`：设置条目附加数据。
- `getItemAddData`：获取条目附加数据。
- `setItemEditor`：设置条目编辑器。
- `getItemEditor`：获取条目编辑器。

## 3 `mItemManager`

通过链表管理 `mItem` 及其子类的基类管理器，提供对列表项的添加、删除和设置等方法。

### 3.1 `mItemManager` 状态

继承自 <a href="#mItem 状态">mItem 状态</a>

| 状态名  | 说明 |
|:-------|:-----|
| `NCSF_ITMMNG_AUTOSORT` | 条目插入时自动排序 |
| `NCSF_ITMMNG_FROZEN` | 禁止或使能条目刷新功能 |

### 3.2 `mItemManager` 属性

继承自 <a href="#mItem 属性">mItem 属性</a>

| 属性 ID | 类型 | 权限 | 说明 |
|:-------|:-----|:----|:-----|
| `NCSP_ITMMNG_ITEMCOUNT` | int | `RO` | 包含的条目数 |
| `NCSP_ITMMNG_FLAGS` | `DWORD` | `RW` | 条目状态 |
| `NCSP_ITMMNG_TOTALHEIGHT` | int | `RO` | 所有条目总高度 |

### 3.3 `mItemManager` 方法

继承自 <a href="#mItem 方法">mItem 方法</a>

#### 3.3.1 回调方法

`mItemManager` 类支持根据列表项或列表项字符串进行比较的 2 个回调方法。其中根据列表项比较的方法优先于根据列表项字符串比较的方法。

```c
typedef int (*NCS_CB_CMPITEM) (mItemManager *manager, HITEM hItem1, HITEM hItem2);
typedef int (*NCS_CB_CMPSTR) (const char* s1, const char* s2, size_t n);
NCS_CB_CMPITEM setItemCmpFunc(mItemManager *self, NCS_CB_CMPITEM func); 
NCS_CB_CMPSTR setStrCmpFunc(mItemManager *self, NCS_CB_CMPSTR func);
NCS_CB_CMPSTR getStrCmpFunc(mItemManager *self);
```
- `setItemCmpFunc`：用于设置根据列表项自身进行比较的回调方法，同时返回先前设置的方法。
- `setStrCmpFunc`：用于设置根据列表项字符串进行比较的回调方法，同时返回先前设置或默认的方法。
- `getStrCmpFunc`：用于获取当前使用的字符串比较方法。

#### 3.3.2 排序方法

```c
void setAutoSortItem(mItemManager *self, BOOL sort);    
int sortItems(mItemManager *self, NCS_CB_CMPITEM pfn);  
```
- `setAutoSortItem`：在添加所有列表项前设置或取消排序标记。当排序标记设置成功后，在其后添加的所有列表项将和已有的列表项进行相应比较后确定插入位置。
- `sortItems`：按照指定的列表项比较方法对所有列表项进行重新排序。

#### 3.3.3 刷新方法

```c
BOOL freeze(mItemManager *self, BOOL lock);     
BOOL isFrozen(mItemManager *self);
int adjustItemsHeight(mItemManager *self, int diff);
```
- `freeze`：冻结或恢复对列表项的刷新。
- `isFrozen`：判断当前是否处于可刷新状态。
- `adjustItemsHeight`：调整列表项总高度变化值，在管理器处理可刷新状态时，该方法在调整完大小后会将变化立即反映到 UI 上，否则将不刷新 UI。

#### 3.3.4 创建/删除/移动列表项

在对列表项进行插入时，首先确认是否是自动排序支持，如果是，则按照自动排序算法计算排序插入位置；否则根据前、后列表项或指定索引依次进行插入尝试，尝试成功则返回正确位置。

```c
HITEM createItem(mItemManager *self, HITEM prev, HITEM next, int index, int *pos);
int insertItem(mItemManager *self, HITEM hItem, HITEM prev, HITEM next, int index, int *pos);
int moveItem(mItemManager *self, mItem *curItem, int count, mItem* prevItem);
int removeItem(mItemManager *self, HITEM hItem);           
BOOL removeAll(mItemManager *self);
```
- `createItem`：创建一个新的列表项并插入到指定位置，同时通过最后的参量返回已插入的位置。
- `insertItem`：将已创建的列表项插入到管理器镮的指定位置，同时通过最后的参量返回已插入的位置。
- `moveItem`：将当前列表项及其后指定数目的列表项移动到某一列表项位置之后。
- `removeItem`：删除某一指定列表项。
- `removeAll`：删除所有列表项。
 
#### 3.3.5 遍历列表项

```c
list_t* getQueue(mItemManager *self);                              
HITEM getListEntry(list_t* entry);

HITEM getFirstItem(mItemManager *self);
HITEM getNext(mItemManager *self, HITEM hItem);       
HITEM getPrev(mItemManager *self, HITEM hItem);
```
- `getQueue`：获取管理器的列表项列首。
- `getListEntry`：获取指定链表项的列表项指针。
- `getFirstItem`：获取管理器中的第一个列表项。
- `getNext`：获取指定列表项的后一个列表项。
- `getPrev`：获取指定列表项的前一个列表项。

#### 3.3.6 获取列表项信息

```c
HITEM getItem(mItemManager *self, int index);                      
int indexOf(mItemManager *self, HITEM hItem);

int inItem(mItemManager *self, int mouseX, int mouseY, HITEM *pRet, POINT *pt);
int getItemYPos(mItemManager *self, HITEM hItem);

int getTotalHeight(mItemManager *self);
int getItemCount(mItemManager *self);
int isEmpty(mItemManager *self);
BOOL getSelection(mItemManager *self, HITEM *pRet, int count);
int getSelectionCount(mItemManager *self);
```
- `getItem`：获取指定索引的列表项。
- `indexOf`：获取指定列表项的索引。
- `inItem`：获取指定鼠标位置下的列表项，并返回列表项的起始位置。
- `getItemYPos`：获取指定列表项的起始纵向坐标。
- `getTotalHeight`：获取列表项管理器的整体高度。
- `getItemCount`：获取列表项总数目。
- `isEmpty`：判断列表项是否为空。
- `getSelectionCount`：获取选中列表项数目。
- `getSelection`：获取指定数目的选中列表项信息。

#### 3.3.7 设置/获取列表项状态

```c
BOOL isEnabled(mItemManager *self, HITEM hItem);
BOOL enable(mItemManager *self, HITEM hItem, BOOL enable);

BOOL isSelected(mItemManager *self, HITEM hItem);
BOOL select(mItemManager *self, HITEM hItem, BOOL sel);
void selectAll(mItemManager *self);
void deselectAll(mItemManager *self);

HITEM hilight(mItemManager *self, HITEM hItem);
HITEM getHilight(mItemManager *self);
BOOL isHilight(mItemManager *self, HITEM hItem);


int setHeight(mItemManager *self, HITEM hItem, int height);
int getHeight(mItemManager *self, HITEM hItem);

void setAddData(mItemManager *self, HITEM hItem, DWORD addData);
DWORD getAddData(mItemManager *self, HITEM hItem);

void setImage(mItemManager *self, HITEM hItem, DWORD image);
DWORD getImage(mItemManager *self, HITEM hItem);

void setFlags(mItemManager *self, HITEM hItem, DWORD flags);
DWORD getFlags(mItemManager *self, HITEM hItem);

BOOL setText(mItemManager *self, HITEM hItem, const char* text);
const char* getText(mItemManager *self, HITEM hItem);
int getTextLen(mItemManager *self, HITEM hItem);
```

- `isEnabled`：判断指定列表项是否处于使能状态。
- `enable`：使能或禁止指定列表项。
- `isSelected`：判断指定列表项是否处于选择状态。
- `select`：选择或取消选择指定列表项。
- `selectAll`：选中所有列表项。
- `deselectAll`：取消所有列表项的选中状态。
- `hilight`：高亮选择指定的列表项。
- `getHilight`：获取当前高亮选择列表项。
- `isHilight`：判断指定列表项是否处于高亮状态。
- `setHeight`：设置列表项高度。
- `getHeight`：获取列表项高度。
- `setAddData`：设置列表项附加数据。
- `getAddData`：获取列表项附加数据。
- `setImage`：设置列表项位图信息。
- `getImage`：获取列表项位图信息。
- `setFlags`：设置列表项状态标志。
- `getFlags`：获取列表项状态标志。
- `setText`：设置列表项文本字符串。
- `getText`：获取列表项文本字符串。
- `getTextLen`：获取列表项文本字符串长度。

## 4 `mListItem`

`mListItem` 对象用于描述 `mListView` 控件的行对象。

### 4.1 `mListItem` 状态

继承自 <a href="#m_ItemManager 状态">mItemManger 状态</a>

| 状态名 | 说明 |
|:------|:-----|
| `NCSF_LSTITM_FOLD` | 折叠条目 |
| `NCSF_LSTITM_PRIVBKCOL` | 条目包含私有背景色 |
| `NCSF_LSTITM_PRIVBKCOL` | 条目包含私有前景色 |

### 4.2 `mListItem` 属性

继承自 <a href="#m_ItemManager 属性">mItemManager 属性</a>

| 属性 ID | 类型 | 权限 | 说明 |
|:-------|:-----|:----|:-----|
| `NCSP_LSTITM_NRCHILD` | int | `RO` | 包含的子条目数 |
| `NCSP_LSTITM_DEPTH` | int | `RO` | 条目的深度 |
| `NCSP_LSTITM_RHEIGHT` | int | `RO` | 条目可见时的实际高度 |

### 4.3 `mListItem` 方法

继承自 <a href="#m_ItemManager 方法">mItemManager 方法</a>

`mListItem` 对象提供了一系列操作方法：

```c
void setBackground(mListItem *self, int index, int *color);
void setForeground(mListItem *self, int index, int *color);
int getBackground(mListItem *self, int index, int *color);
int getForeground(mListItem *self, int index, int *color);
BOOL addChild(mListItem *self, mListItem *child);    
BOOL delChild(mListItem *self, mListItem *child);   
BOOL setFold(mListItem *self, BOOL fold);               
mListItem* getParent(mListItem *self);                  
int getChildCount(mListItem *self);                     
int getDepth(mListItem *self);                          
BOOL isFold(mListItem *self); 
``` 
- `setBackground`：用于设置单元背景色。当 `color` 为空时对原设置进行清空处理；当 `index` 索引无效时，设置默认行背景色，否则设置指定单元背景色。
- `getBackground`：用于获取单元背景色。当 `index` 索引无效时，通过 `color` 返回默认行背景色，否则返回指定单元背景色。
- `setForeground`：用于设置单元前景色。当 `color` 为空时对原设置进行清空处理；当 `index` 索引无效时，设置默认行前景色，否则设置指定单元前景色。
- `getForeground`：用于获取单元前景色， 当 `index` 索引无效时，通过 `color` 返回默认行前景色，否则返回指定单元前景色。
- `addChild`：添加指定的子条目。
- `delChild`：删除指定的子条目。
- `setFold`：用于折叠或展开指定条目。
- `getparent`：用于获取指定条目的父条目。
- `getChildCount`：获取包含的子条目数目。
- `getDepth`：获取条目深度。
- `isFold`：判断条目是否处于折叠状态。

## 5 `mListColumn`

`mListColumn` 对象用于描述 `mListView` 控件的列对象。

### 5.1 `mListColumn` 状态

继承自 <a href="#mItem 状态">mItem 状态</a>

| 状态名 | 说明 |
| `NCSF_LSTCLM_LEFTALIGN` | 文本对齐方式：左对齐 |
| `NCSF_LSTCLM_RIGHTALIGN` | 文本对齐方式：右对齐 |
| `NCSF_LSTCLM_CENTERALIGN` | 文本对齐方式：居中对齐 |

### 5.2 `mListColumn` 属性

继承自 <a href="#mItem 属性">mItem 属性</a>

| 属性 ID | 类型 | 权限 | 说明 |
|:-------|:-----|:----|:-----|
| `NCSP_LSTCLM_POSX` | int | `RW` | 列起始位置横坐标 |
| `NCSP_LSTCLM_WIDTH` | int | `RW` | 列宽 |
| `NCSP_LSTCLM_SORTTYPE` | `ncsLstClmSortType` | `RW` | 列表项排序方式：值为升序、降序或不排序三者选其一 |
| `NCSP_LSTCLM_CMPFUNC` | `NCS_CB_LISTV_CMPCLM` | `RW` | 两列表项比较的回调方法 |

下面是属性中涉及的数据结构定义：

```c
typedef enum
{
    NCSID_LSTCLM_NOTSORTED = 0,  //不排序
    NCSID_LSTCLM_HISORTED, //升序
    NCSID_LSTCLM_LOSORTED //降序
}ncsLstClmSortType;

typedef struct _NCS_LSTCLM_SORTDATA
{
    int     column;  //排序列索引
    int     losorted; //排序列排序方式
    mWidget *obj; //包含比较项的控件类
}NCS_LSTCLM_SORTDATA;

typedef int (*NCS_CB_LISTV_CMPCLM)(HITEM nItem1, HITEM nItem2, NCS_LSTCLM_SORTDATA *sortData);
```

## 6 `mItemView`

基类，不允许直接使用。

### 6.1 `mItemView` 风格

继承自[[MStudioMGNCSV1dot0PGP2C3#mScrollWidget][mScrollWidget的风格]]

| 风格名 | mStudio 属性名 | 说明 |
|:------|:--------------|:-----|
| `NCSS_ITEMV_AUTOSORT` | - | 条目自动排序 |
| `NCSS_ITEMV_LOOP` | - | 条目可循环浏览 |
| `NCSS_ITEMV_SINGLE` | - | 条目单选支持，默认风格 |
| `NCSS_ITEMV_MULTIPLE` | - | 条目多选支持 |

### 6.2 `mItemView` 属性

继承自[[MStudioMGNCSV1dot0PGP2C3#mScrollWidget][mScrollWidget的属性]]

| 属性 ID | mStudio 名 | 类型 | 权限 | 说明 |
|:-------|:-----------|:----|:-----|:----|
| `NCSP_ITEMV_DEFITEMHEIGHT` | - | int | `RW` | 条目默认高度 |
| `NCSP_ITEMV_ITEMCOUNT` | - | int | `RO` | 条目总数目 |

### 6.3 `mItemView` 事件

继承自[[MStudioMGNCSV1dot0PGP2C3#mScrollWidget][mScrollWidget的事件]]

| 事件通知码 | 说明 | 参数 |
|:---------|:-----|:----|
| `NCSN_ITEMV_CLICKED` | 鼠标点击事件 | 被点击的条目句柄 |
| `NCSN_ITEMV_SELCHANGING` | 正在改变选择的条目 | 处于高亮状态的条目句柄 |
| `NCSN_ITEMV_SELCHANGED` | 选择条目已改变 | 新的选择条目句柄 |
| `NCSN_ITEMV_ENTER` | `Enter` 键被按下 | - |
| `NCSN_ITEMV_SETFOCUS` | 获取焦点 | - |
| `NCSN_ITEMV_KILLFOCUS` | 失去焦点 | - |

### 6.4 `mItemView` 方法

继承自[[MStudioMGNCSV1dot0PGP2C3#mScrollWidget][mScrollWidget的方法]]

#### 6.4.1 回调方法

`mItemView` 提供了初始化、绘制和销毁列表项 3 个回调方法，同时还有比较列表项的回调方法。

```c
typedef int  (*NCS_CB_INITITEM)(mItemView *self, HITEM hItem);
typedef void (*NCS_CB_DSTRITEM)(mItemView *self, HITEM hItem);
typedef void (*NCS_CB_DRAWITEM)(mItemView *self, HITEM hItem, HDC hdc, RECT *rcDraw);

NCS_CB_DRAWITEM setItemDraw(mItemView *self, NCS_CB_DRAWITEM func);
NCS_CB_INITITEM setItemInit(mItemView *self, NCS_CB_INITITEM func);
NCS_CB_DSTRITEM setItemDestroy(mItemView *self, NCS_CB_DSTRITEM func);

NCS_CB_CMPITEM setItemCmpFunc(mItemView *self, NCS_CB_CMPITEM func);
NCS_CB_CMPSTR setStrCmpFunc(mItemView *self, NCS_CB_CMPSTR func);
NCS_CB_CMPSTR getStrCmpFunc(mItemView *self);
```

#### 6.4.2 排序方法

```c
void setAutoSortItem(mItemView *self, BOOL sort);    
int sortItems(mItemView *self, NCS_CB_CMPITEM pfn);  
```
- `setAutoSortItem`：在添加所有列表项前设置或取消排序标记。当排序标记设置成功后，在其后添加的所有列表项将和已有的列表项进行相应比较后确定插入位置。
- `sortItems`：按照指定的列表项比较方法对所有列表项进行重新排序。

#### 6.4.3 刷新方法

```c
void freeze(mItemView *self, BOOL lock);
BOOL isFrozen(mItemView *self);
int adjustItemsHeight(mItemView *self, int diff);
```
- `freeze`：冻结或恢复对列表项的刷新。
- `isFrozen`：判断当前是否处于可刷新状态。
- `adjustItemsHeight`：调整列表项总高度变化值，该方法在控件调整完列表项大小后会将变化立即反映到 UI 上，否则将不刷新 UI。

#### 6.4.4 创建/删除/移动列表项

在对列表项进行插入时，首先确认是否是自动排序支持，如果是，则按照自动排序算法计算排序插入位置；否则根据前、后列表项或指定索引依次进行插入尝试，尝试成功则返回正确位置。

```c
HWND createItem(mItemView *self, HITEM prev, HITEM next, int index,
        int height, DWORD addData, int *pos, BOOL adjust);
int insertItem(mItemView *self, HITEM hItem, HITEM prev, HITEM next,
        int index, int *pos);
int removeItem(mItemView *self, HITEM hItem);

BOOL removeAll(mItemView *self);
```
- `createItem`：创建一个新的列表项并插入到指定位置，同时通过最后的参量返回已插入的位置。
- `insertItem`：将已创建的列表项插入到管理器镮的指定位置，同时通过最后的参量返回已插入的位置。
- `removeItem`：删除某一指定列表项。
- `removeAll`：删除所有列表项。
 
#### 6.4.5 遍历列表项

```c
list_t* getQueue(mItemView *self);
HITEM getListEntry(mItemView *self, list_t* entry);
HITEM getFirstItem(mItemView *self);
HITEM getNext(mItemView *self, HITEM hItem);
HITEM getPrev(mItemView *self, HITEM hItem);
```
- `getQueue`：获取管理器的列表项列首。
- `getListEntry`：获取指定链表项的列表项指针。
- `getFirstItem`：获取管理器中的第一个列表项。
- `getNext`：获取指定列表项的后一个列表项。
- `getPrev`：获取指定列表项的前一个列表项。

#### 6.4.6 获取列表项信息

```c
HITEM getItem(mItemView *self, int index);
int indexOf(mItemView *self, HITEM hItem);

int inItem(mItemView *self, int mouseX, int mouseY, HITEM *pRet, POINT *pt);

int getTotalHeight(mItemView *self);
int getItemCount(mItemView *self);
int isEmpty(mItemView *self);
int getSelectionCount(mItemView *self);
BOOL getSelection(mItemView *self, HITEM *pRet, int count);
```
- `getItem`：获取指定索引的列表项。
- `indexOf`：获取指定列表项的索引。
- `inItem`：获取指定鼠标位置下的列表项，并返回列表项的起始位置。
- `getTotalHeight`：获取列表项管理器的整体高度。
- `getItemCount`：获取列表项总数目。
- `isEmpty`：判断列表项是否为空。
- `getSelectionCount`：获取选中列表项数目。
- `getSelection`：获取指定数目的选中列表项信息。

#### 6.4.7 设置/获取列表项状态

```c
BOOL isEnabled(mItemView *self, HITEM hItem);
BOOL enable(mItemView *self, HITEM hItem, BOOL enable);

BOOL isSelected(mItemView *self, HITEM hItem);
BOOL select(mItemView *self, HITEM hItem);
BOOL deselect(mItemView *self, HITEM hItem);

void selectAll(mItemView *self);
void deselectAll(mItemView *self);

int hilight(mItemView *self, HITEM hItem);
HITEM getHilight(mItemView *self);
BOOL isHilight(mItemView *self, HITEM hItem);

int setItemHeight(mItemView *self, HITEM hItem, int height);
int getItemHeight(mItemView *self, HITEM hItem);

DWORD getAddData(mItemView *self, HITEM hItem);
void setAddData(mItemView *self, HITEM hItem, DWORD addData);

void setImage(mItemView *self, HITEM hItem, DWORD image);
DWORD getImage(mItemView *self, HITEM hItem);

void setFlags(mItemView *self, HITEM hItem, DWORD flags);
DWORD getFlags(mItemView *self, HITEM hItem);

BOOL setText(mItemView *self, HITEM hItem, const char* text);
const char* getText(mItemView *self, HITEM hItem);
int getTextLen(mItemView *self, HITEM hItem);
```

- `isEnabled`：判断指定列表项是否处于使能状态。
- `enable`：使能或禁止指定列表项。
- `isSelected`：判断指定列表项是否处于选择状态。
- `select`：选择指定的列表项。
- `deselect`：取消选择指定的列表项。
- `selectAll`：选中所有列表项。
- `deselectAll`：取消所有列表项的选中状态。
- `hilight`：高亮选择指定的列表项。
- `getHilight`：获取当前高亮选择列表项。
- `isHilight`：判断指定列表项是否处于高亮状态。
- `setItemHeight`：设置列表项高度。
- `getItemHeight`：获取列表项高度。
- `setAddData`：设置列表项附加数据。
- `getAddData`：获取列表项附加数据。
- `setImage`：设置列表项位图信息。
- `getImage`：获取列表项位图信息。
- `setFlags`：设置列表项状态标志。
- `getFlags`：获取列表项状态标志。
- `setText`：设置列表项文本字符串。
- `getText`：获取列表项文本字符串。
- `getTextLen`：获取列表项文本字符串长度。

#### 6.4.8 其它

```c
int getFirstVisItem(mItemView *self);
void resetContent(mItemView *self);
int getRect(mItemView *self, HITEM hItem, RECT *rcItem, BOOL bConv);
int getCurSel(mItemView *self);
int setCurSel(mItemView *self, int newSel);
void refreshItem(mItemView *self, HITEM hItem, const RECT *rcInv);
BOOL showItemByIdx(mItemView *self, int index);
BOOL showItem(mItemView *self, HITEM hItem);
```
- `getFirstVisItem`：获取第一个可见的列表项。
- `resetContent`：删除所有列表项，并恢复所有信息配置到初始值。
- `getRect`：获取指定列表项的矩形区域，并通过最后参数决定是否将坐标转换为相对于屏幕的坐标。
- `getCurSel`：获取当前选中列表项索引。
- `setCurSel`：对通过索引设置指定列表项为选中项并将其显示出来，成功返回 0，失败返回 -1。
- `refreshItem`：刷新指定列表项的指定区域，若指定区域为空，则刷新整个列表项。
- `showItemByIdx`：根据索引显示指定列表项。
- `showItem`：显示指定列表项。

## 7 `mScrollView`

- 控件窗口类: `NCSCTRL_SCROLLVIEW`
- 控件英文名: `ScrollView`
- 简介: 用于显示和处理列表项，其中列表项的内容绘制完全是由应用程序自己确定。
- 示意图

### 7.1 `mScrollView` 风格

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

| 风格名 | mStudio 属性名 | 说明 |
|:------|:--------------|:-----|
| `NCSS_SCRLV_LOOP` | - | 条目可循环浏览 |
| `NCSS_SCRLV_SORT` | - | 条目自动排序 |

### 7.2 `mScrollView` 属性

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>


### 7.3 `mScrollView` 事件

继承自 <a href="#m_ItemView 事件">mItemView 事件</a>

| 事件通知码 | 说明 | 参数 |
|:----------|:----|:----|
| `NCSN_SCRLV_CLICKED` | 鼠标点击事件 | 被点击的条目句柄 |
| `NCSN_SCRLV_SELCHANGING` | 正在改变选择的条目 | 处于高亮状态的条目句柄 |
| `NCSN_SCRLV_SELCHANGED` | 选择条目已改变 | 新的选择条目句柄 |

### 7.4 `mScrollView` 方法

继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

`mScrollView` 继承自 `mItemView`，提供了控件自身的 `addItem` 方法，该方法通过列表项信息创建并插入列表项，同时返回插入位置给接口调用者。

```c
typedef struct _NCS_SCRLV_ITEMINFO
{
    int     index;
    int     height;
    DWORD   addData;
}NCS_SCRLV_ITEMINFO;

HITEM addItem(mScrollView *self, NCS_SCRLV_ITEMINFO *info, int *pos);
```    

在添加列表项内容前通过进行一些基础回调方法的设置等内容，如：

```c
%INCLUDE{"%ATTACHURL%/scrollview" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```

### 7.5 `mScrollView` 实例

![scrollview_demo](figures/scrollview_demo.png)

__图 1__  scrollview 程序的输出

__清单 1__  scrollview.c

```c
/*
** $Id: scrollview.c 595 2009-10-10 08:19:47Z xwyan $
**
** Listing P2C14.1
**
** scrollview.c: Sample program for mGNCS Programming Guide
**      The demo application for ScrollView.
**
** Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define IDC_SCROLLVIEW  100

static const char *people[] =
{
        "cao cao",
        "sun quan",
        "liu bei",
        "zhu ge liang",
        "guan yu",
        "pang tong",
        "si ma yu",
};

static NCS_RDR_INFO rdr_info = {
        "classic","classic",NULL
};

// START_OF_HANDLERS
static void scrlv_notify (mWidget *self, int id, int nc, DWORD add_data)
{
        if (nc == NCSN_SCRLV_CLICKED)
        {
                if (self) {
                        const char* info;
                        mIconView *cls = (mIconView*)self;
                        
                        info = (const char*)_c(cls)->getAddData(cls, (HITEM)add_data);
                        
                        fprintf (stderr, "current item's data %s \n", info);
                }
        }
}

static NCS_EVENT_HANDLER scrlv_handlers[] = {
        NCS_MAP_NOTIFY(NCSN_SCRLV_CLICKED, scrlv_notify),
        {0, NULL }
};
// END_OF_HANDLERS

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
        {
                NCSCTRL_SCROLLVIEW, 
                IDC_SCROLLVIEW,
                10, 10, 320, 150,
                WS_BORDER | WS_VISIBLE | NCSS_NOTIFY | NCSS_SCRLV_SORT,
                WS_EX_NONE,
                "",
                NULL,
                &rdr_info,
                scrlv_handlers,
                NULL,
                0,
                0
        },
};

static BOOL dialog_onKeyDown(mWidget* self, 
int message, int code, DWORD key_status)
{
        if (message == MSG_KEYDOWN) {
                if (code == SCANCODE_REMOVE) {
                        mScrollView *scrlvObj;
                        int         curSel, count;
                        HITEM       delItem;
                        
                        scrlvObj = 
                        (mScrollView*)ncsObjFromHandle(GetDlgItem(self->hwnd, IDC_SCROLLVIEW));
                        count = _c(scrlvObj)->getItemCount(scrlvObj);
                        
                        if (scrlvObj) {
                                curSel = _c(scrlvObj)->getCurSel(scrlvObj);
                                
                                if (curSel >= 0) {
                                        delItem = _c(scrlvObj)->getItem(scrlvObj, curSel);
                                        _c(scrlvObj)->removeItem(scrlvObj, delItem);
                                        if (curSel == count -1)
                                        curSel--;
                                        _c(scrlvObj)->setCurSel(scrlvObj, curSel);
                                }
                        }
                }
        }
        return FALSE;
}

static NCS_EVENT_HANDLER dialog_handlers[] = {
        {MSG_KEYDOWN, dialog_onKeyDown},
        {0, NULL }
};

static NCS_MNWND_TEMPLATE dialog_tmpl = {
        NCSCTRL_DIALOGBOX, 
        7,
        0, 0, 350, 200,
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "ScrollView Demo",
        NULL,
        &rdr_info,
        dialog_handlers,
        _ctrl_tmpl,
        sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
        0,
        0, 0,
};

// START_OF_ITEMFUNCS
static int scrlv_cmp_item (mItemManager *manager, HITEM hItem1, HITEM hItem2)
{
        mScrollView *scrlvObj = (mScrollView*)manager->obj;
        const char *name1;
        const char *name2;
        
        if (scrlvObj) {
                name1 = (const char*)_c(scrlvObj)->getAddData(scrlvObj, hItem1);
                name2 = (const char*)_c(scrlvObj)->getAddData(scrlvObj, hItem2);
                return strcmp (name1, name2);
        }
        return 0;
}

static void scrlv_draw_item (mItemView *self, HITEM hItem, HDC hdc, RECT *rcDraw)
{
        const char  *name = (const char*)_c(self)->getAddData(self, hItem);
        gal_pixel   oldBrushClr = 0, oldTextClr = 0;
        BOOL        isHilite = FALSE;
        int         top;
        RECT        rcText;
        
        SetBkMode (hdc, BM_TRANSPARENT);
        
        top = rcDraw->top;
        if (_c(self)->indexOf(self, hItem) > 0) {
                top --;
        }
        
        if (_c(self)->isHilight(self, hItem)) {
                isHilite = TRUE;
                oldBrushClr = SetBrushColor (hdc, PIXEL_blue);
                FillBox (hdc, rcDraw->left + 1, 
                top + 1, RECTWP(rcDraw) - 2, RECTHP(rcDraw) - 1);
                oldTextClr = SetTextColor (hdc, PIXEL_lightwhite);
        }
        
        Rectangle (hdc, rcDraw->left, top, rcDraw->right - 1, rcDraw->bottom - 1);
        
        CopyRect(&rcText, rcDraw);
        rcText.left += 5;
        DrawText(hdc, name, -1, &rcText, DT_VCENTER | DT_SINGLELINE);
        
        if (isHilite) {
                SetBrushColor (hdc, oldBrushClr);
                SetTextColor (hdc, oldTextClr);
        }
}
// END_OF_ITEMFUNCS

static BOOL scrlv_init(mDialogBox* self)
{
        int     i;
        HWND    scrlvWnd;
        mScrollView *scrlvObj;
        NCS_SCRLV_ITEMINFO info;
        
        scrlvWnd = GetDlgItem (self->hwnd, IDC_SCROLLVIEW);
        scrlvObj = (mScrollView*)ncsObjFromHandle(scrlvWnd);
        
        if (!scrlvObj)
        return FALSE;
        
        // START_OF_ADDITEMS
        _c(scrlvObj)->freeze(scrlvObj, TRUE);
        _c(scrlvObj)->setItemCmpFunc(scrlvObj, scrlv_cmp_item);
        _c(scrlvObj)->setItemDraw(scrlvObj, scrlv_draw_item);
        
        for (i = 0; i < TABLESIZE(people); i++) {         info.height  = 32;         info.index   = i;         info.addData = (DWORD)people[i];         _c(scrlvObj)->addItem(scrlvObj, &info, NULL);
        }
        _c(scrlvObj)->freeze(scrlvObj, FALSE);
        // END_OF_ADDITEMS
        return TRUE;
}

int MiniGUIMain(int argc, const char* argv[])
{
        ncsInitialize();
        mDialogBox* mydlg = 
        (mDialogBox *)ncsCreateMainWindowIndirect (&dialog_tmpl, HWND_DESKTOP);
        
        scrlv_init(mydlg);
        _c(mydlg)->doModal(mydlg, TRUE);
        
        MainWindowThreadCleanup(mydlg->hwnd);
        ncsUninitialize();
        return 0;
}
```

## 8 `mListBox`

- 控件窗口类: `NCSCTRL_LISTBOX`
- 控件英文名: `ListBox`
- 简介: 将用户提供的一系列可选项显示在可滚动的子窗口中，用户可通过键盘及鼠标操作来选中某一项或者多个项，选中的列表项通常高亮显示。列表框的最典型用法就是文件打开对话框。
- 示意图: 

![listbox](figures/listbox.png)

### 8.1 `mListBox` 风格

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

| 风格名 | mStudio 属性名 | 说明 |
|:------|:--------------|:-----|
| `NCSS_LSTBOX_SINGLE` | `Multi->FALSE` | 单选列表项支持 |
| `NCSS_LSTBOX_MULTIPLE` | `Multi->TRUE` | 多选列表项支持 |
| `NCSS_LSTBOX_SORT` | `AutoSort` | 列表项排序支持 |
| `NCSS_LSTBOX_MOUSEFOLLOW` | `MouseFollow` | 列表项支持鼠标跟随 |
| `NCSS_LSTBOX_STRING` | - | 带有字符串的列表项 |
| `NCSS_LSTBOX_USEBITMAP` | `UseBitmap` | 列表项带有位图 |
| `NCSS_LSTBOX_CHECKBOX` | `Checkable` | 列表项包含 checkbox |
| `NCSS_LSTBOX_AUTOCHECK` | `AutoCheck` | 列表项中的 checkbox 支持自动选择 |
| `NCSS_LSTBOX_AUTOCHECKBOX` | - | 同时包含 `NCSS_LSTBOX_CHECKBOX` 和 `NCSS_LSTBOX_AUTOCHECK` 2 种风格 |

### 8.2 `mListBox` 属性

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>

| 属性 ID | mStudio 名 | 类型 | 权限 | 说明 |
|:-------|:-----------|:----|:-----|:----|
| `NCSP_LSTBOX_ITEMWIDTH` | - | int | `RO` | 列表项最大宽度 |
| `NCSP_LSTBOX_ITEMCOUNT` | - | int | `RO` | 列表项总数目 |
| `NCSP_LSTBOX_ITEMHEIGHT` | - | int | `RW` | 列表项高度 |
| `NCSP_LSTBOX_TOPITEM` | - | int | `RW` | 第一个可见列表项索引 |
| `NCSP_LSTBOX_HILIGHTEDITEM` | - | int | `RW` | 高亮列表项索引 |

### 8.3 mListBox 事件

继承自 <a href="#m_ItemView 事件">mItemView 事件</a>

| 事件通知码 | 说明 | 参数 |
|:----------|:----|:----|
| `NCSN_LSTBOX_CLICKED` | 鼠标点击事件 |  |
| `NCSN_LSTBOX_SELCHANGED` | 选择条目已改变 | 新的选择条目句柄 |
| `NCSN_LSTBOX_ENTER` | `Enter` 键被按下 | - |
| `NCSN_LSTBOX_SETFOCUS` | 获取焦点 | - |
| `NCSN_LSTBOX_KILLFOCUS` | 失去焦点 | - |
| `NCSN_LSTBOX_ERRSPACE` | 空间不足 | - |
| `NCSN_LSTBOX_DBCLK` | 双击列表项 | - |
| `NCSN_LSTBOX_SELCANCEL` | 取消选择条目 | - |
| `NCSN_LSTBOX_CLKCHKMARK` | check mark 被点击 | - |

### 8.4 `mListBox` 方法

继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

#### 8.4.1 将字符串加入列表框 

建立 listbox 控件之后，下一步是将字符串放入其中，这可以通过调用 `addString` 方法来完成，添加成功后该方法将返回列表项所在的索引值。字符串通常通过以 0 开始计数的索引数来引用，其中 0 对应于最顶上的条目。 

```c
int addString(mListBox *self, const char* string, DWORD addData);
```

也可以使用 `insertString` 指定一个索引值，将字符串插入到列表框中的指定位置，但在 `NCSS_LISTBOX_SORT` 风格下，会根据排序结果插入到相应位置，将忽略索引值设置： 

```c
int insertString(mListBox *self, const char* string, DWORD addData, int index);
```

如：

```c
iteminfo.flag = NCSF_LSTBOX_CMBLANK;
iteminfo.image = 0;
for (i = 0; i < TABLESIZE(items); i++) {
	iteminfo.string = items[i];
	_c(lstboxObj)->addString (lstboxObj, &iteminfo);
}
```

如果添加的列表项除了包含字符串以外，还包含位图等信息，可通过 `addItems` 方法来完成。

```c
typedef struct _NCS_LSTBOX_ITEMINFO
{
    char*   string;
    DWORD   flag;
    DWORD   image;
    DWORD addData;
}NCS_LSTBOX_ITEMINFO;

void addItems(mListBox *self, NCS_LSTBOX_ITEMINFO *info, int count);
```

如：

```c
    int count = 3;
    mListItemInfo   lbii[count];

    lbii[0].string = "test list";
    lbii[0].flag = 0;
    lbii[0].image = 0;
    ... ...
    _c(listFile)->addItems(listFile, lbii, count);
```

#### 8.4.2 删除列表框条目 

列表框控件通过 `delString` 或 r`emoveItemByIdx` 方法可以删除指定索引值的列表项或通过 `removeItem` 方法删除指定列表项；同时也可以通过 `resetContent` 清空列表框中的所有内容。函数原型如下： 

```c
BOOL delString(mListBox *self, int index);  
int removeItemByIdx(mListBox *self, int index);
```

如：

```c
int sel     = _c(lstboxObj)->getCurSel(lstboxObj);
int count   = _c(lstboxObj)->getItemCount(lstboxObj);

if (sel >= 0) {
        _c(lstboxObj)->delString(lstboxObj, sel);
        
        if (sel == count -1)
        sel --;
        
        _c(lstboxObj)->setCurSel(lstboxObj, sel);
}
```


#### 8.4.3 选择和获取条目 

对于单项选择列表框和多项选择列表框在检索列表框条目的选中状态时需要使用不同的方法，下面先看单项选择列表框。选择条目除了通过鼠标和键盘操作外，还可以通过方法 `setCurSel` 来控制：

```c
_c(listFile)->setCurSel(listFile, 1);
```

反之，可通过 getCurSel 来获取当前选定的索引项，如果没有选定项， 将返回 -1。

```c
_c(listFile)->getCurSel(listFile);
```

另外也可以通过 `selectByIdx` 或 `deselectByIdx` 设置或取消选中状态。

```c
int selectByIdx(mListBox *self, int index);
int deselectByIdx(mListBox *self, int index);                          
```

对于多项选择列表框来说，通过 `setCurSel` 和 `getCurSel` 方法只能用来设置和获取当前高亮项，无法获得所有具有选中状态的条目。但我们可以使用 `setSel` 来设定某特定条目的选择状态，而不影响其他项，其中 flag 的取值有三种含义：

- -1：时对指定列表项进行相反操作，即原状态未选中则选中它，否则取消选中状态。
- 0：取消对列表项的选中。
- 其它：选中列表项。

方法原型：

```c
int setSel(mListBox *self, int newSel, int flag);
```

使用示例如：

```c
_c(listFile)->setSel(listFile, 0, 1);
```

反之，我们可以用 `isSelected` 方法确定某特定条目的选择状态：

```c
_c(listFile)->isSelected(listFile, 0);
```

另外对于多选列表框，可以通过 `getSelectionCount` 方法获取当前选中的条目个数，并通过 `getSelection` 获得所有被选中条目的索引值：

```c
HITEM* selItems;
int selCount = _c(listFile)->getSelectionCount(listFile);
if (selCount == 0)
return;

selItem = alloca (sizeof(HITEM)*selCount);
_c(listFile)->getSelection(listFile, selItem, selCount);
```

#### 8.4.4 查找含有字符串的条目 

列表框通过 `findString` 方法提供了在指定范围内精确或模糊查找包含某一指定字符串的列表项的方法：

```c
int findString(mListBox *self, int start, char* string, BOOL bExact);
```

下面的操作将从第 3 个列表项开始精确查找字符串为 test 的列表项。成功会返回查找到的列表项索引，否则返回 -1：

```c
_c(listFile)->findString(listFile, 2, "test", TRUE);
```

#### 8.4.5 设置和获取某条目的检查框的当前状态 

```c
_c(listFile)->getCheckMark(listFile, index);
```

返回由 index 指定索引处条目的检查框的状态。如果没有找到相应条目，将返回 -1。

`NCSF_LSTITEM_CMCHECKED` 表示该条目的检查框处于选择状态。

`NCSF_LSTITEM_CMPARTCHECKED` 表示该条目的检查框处于部分选择状态。

`NCSF_LSTITEM_CMBLANK` 表示该条目的检查框处于未选择状态。 

```c
_c(listFile)->setCheckMark(listFile, index, (DWORD)status);
```

设置由 index 指定索引处条目的检查框的状态为 status 中指定的值。当没有找到 index 指定的条目时，返回 `FALSE`，成功返回 `TRUE`。 

#### 8.4.6 设置某列表框条目加粗显示状态 

```c
_c(listFile)->bold(listFile, index, TRUE);
```

该操作将指定索引项的内容进行加粗设置。

#### 8.4.7 设置或获取某列表框条目选择状态 

列表框通过 `isEnabled` 方法确定某特定条目是否处于禁止选中状态： 

```c
_c(listFile)->isEnabled(listFile, 0);
```

通过 `enableByIdx` 或 `enable` 方法可以支持条目选中或禁止条目选中。

```c
_c(listFile)->enableByIdx(listFile, 0, TRUE);
or
_c(listFile)->enableByIdx(listFile, 0, FALSE);
```

#### 8.4.8 设置字符串比较函数

列表框控件通过 _setStrCmpFunc_ 方法来使用用户设置的排序方法排列列表项。

```c
static int my_strcmp (const char* s1, const char* s2, size_t n)
{
        int i1 = atoi (s1);
        int i2 = atoi (s2);
        return (i1 – i2);
}
_c(listFile)->setStrCmpFunc(listFile, my_strcmp);
```

### 8.5 `mListBox` 实例

![listbox_demo](figures/listbox_demo.png)

__图 3__  listbox 程序的输出

__清单 3__  listbox.c

```c
/**
* $Id: listbox.c 595 2009-10-10 08:19:47Z xwyan $
*
* Listing P2C14.2
*
* listbox.c: Sample program for mGNCS Programming Guide
*      The demo application for ListBox.
*
* Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define IDC_LIST    100
#define IDC_DELETE  200

static char* items[] = {
        "Apples",
        "Apricots",
        "Bananas",
        "Grapefruit",
        "Kiwi",
        "Oranges",
        "Peaches",
        "The Longest String"
};

static void lstbox_init(mDialogBox *dialog)
{
        NCS_LSTBOX_ITEMINFO iteminfo;
        mListBox *lstboxObj;
        int i;
        
        lstboxObj = (mListBox *)ncsGetChildObj(dialog->hwnd, IDC_LIST);
        
        // START_OF_ADDITEMS
        iteminfo.flag = NCSF_LSTBOX_CMBLANK;
        iteminfo.image = 0;
        for (i = 0; i < TABLESIZE(items); i++) {         iteminfo.string = items[i];         _c(lstboxObj)->addString (lstboxObj, &iteminfo);
        }
        // END_OF_ADDITEMS
}

// START_OF_BTNHANDLERS
static void btn_notify(mWidget *self, int id, int nc, DWORD add_data)
{
        mListBox    *lstboxObj = 
        (mListBox *)ncsGetChildObj(GetParent(self->hwnd), IDC_LIST);
        // START_OF_DELITEMS
        int sel     = _c(lstboxObj)->getCurSel(lstboxObj);
        int count   = _c(lstboxObj)->getItemCount(lstboxObj);
        
        if (sel >= 0) {
                _c(lstboxObj)->delString(lstboxObj, sel);
                
                if (sel == count -1)
                sel --;
                
                _c(lstboxObj)->setCurSel(lstboxObj, sel);
        }
        // END_OF_DELITEMS
}

static NCS_EVENT_HANDLER btn_handlers [] = {
        NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
        {0, NULL}	
};
// END_OF_BTNHANDLERS
static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
        {
                NCSCTRL_LISTBOX, 
                IDC_LIST,
                20, 15, 170, 200,
                WS_BORDER | WS_VISIBLE | NCSS_NOTIFY,
                WS_EX_NONE,
                "",
                NULL,
                NULL,
                NULL,
                NULL,
                0,
                0 
        },
        {
                NCSCTRL_BUTTON, 
                IDC_DELETE,
                15, 230, 80, 30,
                WS_VISIBLE | WS_TABSTOP,
                WS_EX_NONE,
                "Delete",
                NULL,
                NULL,
                btn_handlers, 
                NULL,
                0,
                0 
        },
        {
                NCSCTRL_BUTTON, 
                IDCANCEL,
                115, 230, 80, 30,
                WS_VISIBLE | WS_TABSTOP,
                WS_EX_NONE,
                "Cancel",
                NULL, 
                NULL,
                NULL,
                NULL,
                0,
                0
        },
};


static NCS_MNWND_TEMPLATE mainwnd_tmpl = {
        NCSCTRL_DIALOGBOX, 
        1,
        100, 100, 220, 300,
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "ListBox Demo",
        NULL,
        NULL,
        NULL,
        _ctrl_tmpl,
        sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
        0,
        0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
        ncsInitialize();
        
        mDialogBox* dialog = 
        (mDialogBox *)ncsCreateMainWindowIndirect (&mainwnd_tmpl, HWND_DESKTOP);
        
        lstbox_init(dialog);
        _c(dialog)->doModal(dialog, TRUE);
        
        MainWindowThreadCleanup(dialog->hwnd);
        ncsUninitialize();
        return 0;
}
```

## 9 `mIconView`

- 控件窗口类: `NCSCTRL_ICONVIEW`
- 控件英文名: `IconView`
- 简介: 将用户提供的一系列可选项以图标加标签文字的方式供其浏览，用户可通过键盘及鼠标操作来选中某一项或者多个项，选中的列表项通常高亮显示。标型控件的典型用法是作为桌面图标的容器和目录下文件的显示。 
- 示意图: 

![iconview](figures/iconview.png)

### 9.1 `mIconView` 风格

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

| 风格名 | mStudio 属性名 | 说明 |
|:------|:--------------|:-----|
| `NCSS_ICONV_LOOP` | `Loop` | 条目可循环浏览 |
| `NCSS_ICONV_SORT` | `AutoSort` | 条目自动排序 |

### 9.2 `mIconView` 属性

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>

| 属性 ID | mStudio 名 | 类型 | 权限 | 说明 |
|:-------|:-----------|:----|:-----|:----|
| `NCSP_ICONV_DEFICONHEIGHT` | - | int |  `RW` | 列表项高度 |
| `NCSP_ICONV_DEFICONWIDTH` | - | int | `RW` | 列表项宽度 |

### 9.3 `mIconView` 方法

继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

iconview 控件通过 `setIconSize` 方法来初始化列表项的大小，并通过 `addItem` 方法根据列表项信息添加列表项。

```c
typedef struct _NCS_ICONV_ITEMINFO
{
    int index;
    PBITMAP bmp;
    const char *label;
    DWORD addData;
}NCS_ICONV_ITEMINFO;

void setIconSize(mIconView *self, int width, int height);
HITEM addItem(mIconView *self, NCS_ICONV_ITEMINFO *info, int *pos);
```

添加列表项的示例代码如：

```c
%INCLUDE{"%ATTACHURL%/iconview" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```

### 9.4 `mIconView` 实例

![iconview_demo](figures/iconview_demo.png)

__图 1__  iconview 程序的输出

__清单 3__ iconview.c

```c
/**
* $Id: iconview.c 595 2009-10-10 08:19:47Z xwyan $
*
* Listing P2C14.3
*
* iconview.c: Sample program for mGNCS Programming Guide
*      The demo application for IconView.
*
* Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define IDC_ICONVIEW    100
#define IDC_ADD         600
#define IDC_DELETE      601

static BITMAP icon_demos [12];

static const char* iconfiles[12] =
{
        "./res/acroread.png",
        "./res/icons.png",
        "./res/looknfeel.png",
        "./res/package_games.png",
        "./res/tux.png",
        "./res/xemacs.png",
        "./res/gimp.png",
        "./res/kpilot.png",
        "./res/multimedia.png",
        "./res/realplayer.png",
        "./res/usb.png",
        "./res/xmms.png"
};

static const char *iconlabels[12] =
{
        "acroread",
        "icons",
        "looknfeel",
        "games",
        "tux",
        "xemacs",
        "gimp",
        "kpilot",
        "multimedia",
        "realplayer",
        "usb",
        "xmms"
};

static BOOL iconv_init(mDialogBox* self)
{
        NCS_ICONV_ITEMINFO info;
        static int i = 0, j = 0, pos = 0;
        mIconView *iconvObj;
        HWND iconvWnd;
        
        for(i = 0; i < TABLESIZE(icon_demos); i++)     {         LoadBitmap (HDC_SCREEN, &icon_demos[i], iconfiles[i]);     }     iconvWnd = GetDlgItem (self->hwnd, IDC_ICONVIEW);
        iconvObj = (mIconView*)ncsObjFromHandle(iconvWnd);
        
        if (!iconvObj)
        return FALSE;
        
        // START_OF_ADDITEMS
        _c(iconvObj)->setIconSize(iconvObj, 90, 80);
        
        for(i = 0; i < TABLESIZE(icon_demos); i++)     {         pos = 0;          memset (&info, 0, sizeof(NCS_ICONV_ITEMINFO));          info.bmp = &icon_demos[i];          info.index = TABLESIZE(icon_demos) * j + i;          info.label = iconlabels[i];          info.addData = (DWORD)iconlabels[i];          _c(iconvObj)->addItem(iconvObj, &info, &pos); 
        } 
        _c(iconvObj)->setCurSel(iconvObj, 0); 
        // END_OF_ADDITEMS 
        
        return TRUE;
}

// START_OF_WNDHANDLERS
static BOOL mainwnd_onKeyDown(mWidget* self, 
int message, int code, DWORD key_status)
{
        if (message == MSG_KEYDOWN) {
                if (code == SCANCODE_REMOVE) {
                        mIconView *iconView;
                        int curSel, count;
                        HITEM delItem;
                        
                        iconView = 
                        (mIconView*)ncsObjFromHandle(GetDlgItem (self->hwnd, IDC_ICONVIEW));
                        count = _c(iconView)->getItemCount(iconView);
                        
                        if (iconView) {
                                curSel = _c(iconView)->getCurSel(iconView);
                                
                                if (curSel >= 0) {
                                        delItem = _c(iconView)->getItem(iconView, curSel);
                                        _c(iconView)->removeItem(iconView, delItem);
                                        if (curSel == count -1)
                                        curSel--;
                                        _c(iconView)->setCurSel(iconView, curSel);
                                }
                        }
                }
        }
        return FALSE;
}

static NCS_EVENT_HANDLER mainwnd_handlers[] = {
        {MSG_KEYDOWN, mainwnd_onKeyDown},
        {0, NULL }
};
// END_OF_WNDHANDLERS

// START_OF_ICONVHANDLERS
static void iconv_notify (mWidget *self, int id, int nc, DWORD add_data)
{
        if (nc == NCSN_ICONV_CLICKED)
        {
                if (self) {
                        int idx;
                        const char  *text;
                        mIconView   *iconvObj = (mIconView*)self;
                        
                        idx = _c(iconvObj)->indexOf(iconvObj, (HITEM)add_data);
                        text = _c(iconvObj)->getText(iconvObj, (HITEM)add_data);
                        fprintf (stderr, "click icon[%d], text is %s \n", idx, text);
                }
        }
}

static NCS_EVENT_HANDLER iconv_handlers[] = {
        NCS_MAP_NOTIFY(NCSN_ICONV_CLICKED, iconv_notify),
        NCS_MAP_NOTIFY(NCSN_ICONV_SELCHANGED, iconv_notify),
        {0, NULL }
};
// END_OF_ICONVHANDLERS

// START_OF_BTNHANDLERS
static void btn_notify(mWidget *self, int id, int nc, DWORD add_data)
{
        mIconView *iconvObj = 
        (mIconView *)ncsGetChildObj(GetParent(self->hwnd), IDC_ICONVIEW);
        
        if (!iconvObj)
        return;
        
        switch (id)
        {
                case IDC_ADD:
                {
                        char    buff[12];
                        int     count, pos = 0;
                        NCS_ICONV_ITEMINFO info;
                        
                        count = _c(iconvObj)->getItemCount(iconvObj);
                        sprintf (buff, "icon%i", count+1);
                        
                        memset (&info, 0, sizeof(NCS_ICONV_ITEMINFO));
                        info.bmp = &icon_demos[0];
                        info.index = count;
                        info.label = buff;
                        info.addData = (DWORD)"icon";
                        
                        if (_c(iconvObj)->addItem(iconvObj, &info, &pos))
                        _c(iconvObj)->setCurSel(iconvObj, pos);
                        
                        break;
                }
                
                case IDC_DELETE:
                {
                        int     count, sel;
                        char    *label = NULL;
                        HITEM   hItem;
                        
                        sel     = _c(iconvObj)->getCurSel(iconvObj);
                        count   = _c(iconvObj)->getItemCount(iconvObj);
                        hItem   = _c(iconvObj)->getItem(iconvObj, sel);
                        
                        if (sel >= 0) {
                                label = (char*)_c(iconvObj)->getAddData(iconvObj, hItem);
                                _c(iconvObj)->removeItem(iconvObj, hItem);
                                
                                if (sel == count -1)
                                sel --;
                                
                                _c(iconvObj)->setCurSel(iconvObj, sel);
                        }
                        break;
                }
        }
}

static NCS_EVENT_HANDLER btn_handlers [] = {
        NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
        {0, NULL}	
};
// END_OF_BTNHANDLERS

static NCS_RDR_INFO iconv_rdr_info = {
        "classic", "classic", NULL
};

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
        {
                NCSCTRL_ICONVIEW, 
                IDC_ICONVIEW,
                15, 10, 220, 250,
                WS_BORDER | WS_CHILD | WS_VISIBLE | NCSS_NOTIFY | NCSS_ICONV_LOOP,
                WS_EX_NONE,
                "",
                NULL,
                &iconv_rdr_info,
                iconv_handlers,
                NULL,
                0,
                0
        },
        {
                NCSCTRL_BUTTON, 
                IDC_ADD,
                15, 280, 80, 30,
                WS_VISIBLE | NCSS_NOTIFY,
                WS_EX_NONE,
                "add",
                NULL,
                NULL,
                btn_handlers, 
                NULL,
                0,
                0 
        },
        {
                NCSCTRL_BUTTON, 
                IDC_DELETE,
                155, 280, 80, 30,
                WS_VISIBLE | NCSS_NOTIFY,
                WS_EX_NONE,
                "delete",
                NULL, 
                NULL,
                btn_handlers,
                NULL, 
                0,
                0 
        },
};

static NCS_MNWND_TEMPLATE mainwnd_tmpl = {
        NCSCTRL_DIALOGBOX, 
        7,
        0, 0, 260, 350,
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "IconView Demo",
        NULL,
        NULL,
        mainwnd_handlers,
        _ctrl_tmpl,
        sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
        0,
        0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
        ncsInitialize();
        mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect 
        (&mainwnd_tmpl, HWND_DESKTOP);
        
        iconv_init(mydlg);
        _c(mydlg)->doModal(mydlg, TRUE);
        
        MainWindowThreadCleanup(mydlg->hwnd);
        ncsUninitialize();
        return 0;
}
```

## 10 `mListView`

- 控件窗口类: `NCSCTRL_LISTVIEW`
- 控件英文名: `ListView`
- 简介: 以列表的方式显示一系列的数据项（列表项），不同列表项的相同类型子项以列的方式组织，列表型控件的表头（header）内容通常反映了列表项不同子项的意义。列表型控件经常用来作为文件浏览框，它可以在一个区域内显示包括文件名、文件类型、大小和修改日期在内的诸多文件属性。 
- 示意图: 

![listview](figures/listview.png)

### 10.1 `mListView` 风格

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

| 风格名 | mStudio 属性名 | 说明 |
|:------|:--------------|:----|
| `NCSS_LISTV_NOTIFY` | `Notify` | 通知事件支持 |
| `NCSS_LISTV_LOOP` | `Loop` | 循环浏览支持 |
| `NCSS_LISTV_MULTIPLE` | `Multi->TRUE` | 多选支持 |
| `NCSS_LISTV_SINGLE` |  | `Multi->FALSE` | 单选支持 |
| `NCSS_LISTV_CHECKBOX` | `CheckBox` | 列表项包含 checkbox |
| `NCSS_LISTV_AUTOCHECK` | `AutoCheck` | 列表项中的 checkbox 支持自动选择 |
| `NCSS_LISTV_AUTOCHECKBOX` | - | 同时包含 `NCSS_LSTBOX_CHECKBOX` 和 `NCSS_LSTBOX_AUTOCHECK` 2 种风格 |
| `NCSS_LISTV_TREE` | `Tree` | 支持树状列表 |
| `NCSS_LISTV_WITHICON` | `WithIcon` |  |
| `NCSS_LISTV_SORT` | `Sort` | 排序支持 |

### 10.2 `mListView` 属性

继承自[[MStudioMGNCSV1dot0PGP2C3#mItemView][mItemView的属性]]

| 属性 ID | mStudio 名 | 类型 | 权限 | 说明 |
|:-------|:-----------|:----|:-----|:----|
| `NCSP_LISTV_DEFITEMHEIGHT` | - | int | `RW` | 列表项默认高度 |
| `NCSP_LISTV_ROWCOUNT` | - | `RO` | int | 列表项行数 |
| `NCSP_LISTV_HDRHEIGHT` | HeadHeight | int | `RW` | 列表头高度 |
| `NCSP_LISTV_HDRWIDTH` | HeadWidth | int | `RW` | 列表头总宽度 |
| `NCSP_LISTV_HDRVISIBLE` | - | BOOL | `RW` | 列表头是否可见 |
| `NCSP_LISTV_SORTCOLUMN` | - | int | `RW` | 排序列索引 |
| `NCSP_LISTV_GRIDLINEWIDTH` | GridLineWidth | int | `RW` | 网格宽度 |
| `NCSP_LISTV_GRIDLINECOLOR` | GridLineColor | int | `RW` | 网格颜色 |
| `NCSP_LISTV_COLCOUNT` | - | int | `RO` | 列表项列数 |


### 10.3 `mListView` 事件    

继承自 <a href="#m_ItemView 事件">mItemView 事件</a>

| 事件通知码 | 说明 | 参数 |
|:---------|:-----|:----|
| `NCSN_LISTV_CLICKED` | 鼠标点击事件 |  |
| `NCSN_LISTV_SELCHANGED` | 选择条目已改变 | 新的选择项句柄 |
| `NCSN_LISTV_ITEMRDOWN` | 鼠标右键在列表项上按下 | 被点击的行索引 |
| `NCSN_LISTV_ITEMRUP` | 鼠标右键在列表项上弹起 | 被点击的行索引 |
| `NCSN_LISTV_HDRRDOWN` | 鼠标右键在表头上按下 | 被点击的列索引 |
| `NCSN_LISTV_HDRRUP` | 鼠标右键在列表项上弹起 | 被点击的列索引 |
| `NCSN_LISTV_ITEMDBCLK` | 双击列表项 | - |
| `NCSN_LISTV_FOLDITEM` | 树列表项折叠子节点 | 被点击的列表项句柄 |
| `NCSN_LISTV_UNFOLDITEM` | 树列表项打开子节点 | 被点击的列表项句柄 |

### 10.4 `mListView` 方法

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

#### 10.4.1 列操作

在向该控件中添加列表项前，首先需要通过 `addColumn` 方法添加列：

```c
for (i = 0; i < COL_NR; i++) {
	lstv_clminfo.index  = i;
	lstv_clminfo.text   = caption[i];
	lstv_clminfo.width  = 74;
	lstv_clminfo.pfnCmp = NULL;
	lstv_clminfo.flags  = NCSF_LSTCLM_CENTERALIGN | NCSF_LSTHDR_CENTERALIGN;         	_c(lstvObj)->addColumn(lstvObj, &lstv_clminfo);
}
```

其中 `lstv_clminfo` 是一个 `NCS_LISTV_CLMINFO` 结构，它包含了列表型控件的列信息。在添加列后，若需要设置或获取列的相关信息时，可通过如下方法来完成：

```c
void setColumnWidth(mListView *self, int index, int width); 
BOOL setHeadText(mListView *self, int col, const char* text);

mListColumn* getColumn(mListView *self, int index);         
int getColumnIndex(mListView *self, mListColumn *column);   
int getColumnWidth(mListView *self, int index);
int getColumnCount(mListView *self);                     
void showColumn(mListView *self, mListColumn *column);      
```

此外，删除指定列可通过 delColumn 方法实现：

```c
BOOL delColumn(mListView *self, int index);
```

#### 10.4.2 列表项操作

列表型控件由许多纵向排列的列表项组成，每个列表项由列分为多个子项，列表项可以包含特定的应用程序定义的附加数据。应用程序可以通过相应的方法来添加、修改和设置、删除列表项或获取列表项的属性信息。 

控件创建并添加列后，还没有列表项，此时需要通过 `addItem` 向其添加列表项：

```c
NCS_LISTV_ITEMDATA subdata;
HITEM   hItem;

subdata.row = info->index;
subdata.col = 0;
subdata.text= classes[info->index];
subdata.textColor = 0;
subdata.flags = 0;
subdata.image = 0;

info->dataSize = 1;
info->data = &subdata;

hItem = _c(self)->addItem (self, info);
```

每个列表项包括一个或多个子项，子项的数目和列表型控件的列数相同。一个子项中包括字符串和图像，可以使用下列方法来获取和设置子项的信息：

```c
void setBackground(mListView *self,int row,int col,int *color); 
void setForeground(mListView *self,int row,int col,int *color); 
int getBackground(mListView *self,int row,int col,int *color);
int getForeground(mListView *self,int row,int col,int *color);

BOOL setItemInfo(mListView *self, NCS_LISTV_ITEMDATA *info);
BOOL getItemInfo(mListView *self, NCS_LISTV_ITEMDATA *info);
const char* getItemText(mListView *self, int row, int col);
int getItemTextLen(mListView *self, int row, int col);
BOOL setItemText(mListView *self, int row, int col, const char* str);
```

#### 10.4.3 查找列表项 

`findItem` 用于在列表型控件中查找一个特定的列表项。如果查找成功的话，返回列表项句柄。

```c
HITEM findItem(mListView *self, NCS_LISTV_FINDINFO *info);
```

#### 10.4.4 比较和排序 

除了继承自基类的排序功能支持外，该控件还可以指定某一列作为其排序的依照列，同时还可以设定排序类型是升序还是降序，或无序（不排列）。

```c
void sort(mListView *self, NCS_CB_LISTV_CMPCLM func, int col, ncsLstClmSortType sort);
void setSortDirection(mListView *self, ncsLstClmSortType direction);  
ncsLstClmSortType getSortDirection(mListView *self);
mListColumn* getSortColumn(mListView *self);                
void setSortColumn(mListView *self, mListColumn* column);   
```

#### 10.4.5 回调方法

对列表头的绘制包括了背景色和内容绘制 2 部分，控件对此提供了回调方法供上层应用处理表头的绘制。方法：

```c
void setCustomDrawHeader(mListView *self, NCS_CB_LISTV_CSTMHDROPS *func);
```

#### 10.4.6 树型节点的操作 

树型节点的操作包括获取相关节点和折叠一个节点。相关方法有：

```c
HITEM getRelatedItem(mListView *self,HITEM hItem,ncsListVIRType type);
HITEM getChildItem(mListView *self, HITEM parent, int index);
int getChildCount(mListView *self, HITEM hItem);
int foldItem(mListView *self, HITEM hItem, BOOL fold);
```

- `getRelatedItem` 用于获取一个节点的相关树型节点，如父节点，兄弟节点或第一个子节点。`ncsListVIRType` 指定相关节点和目标节点的关系，包括： 
   - `NCSID_LISTV_IR_PARENT`：父节点
   - `NCSID_LISTV_IR_FIRSTCHILD`：第一个子节点
   - `NCSID_LISTV_IR_LASTCHILD`：最后一个节点
   - `NCSID_LISTV_IR_NEXTSIBLING`：下一个兄弟节点
   - `NCSID_LISTV_IR_PREVSIBLING`：上一个兄弟节点
- `foldItem` 用来折叠或者展开一个包含子节点的节点项。 
- `getChildItem`：用于获取指定父节点下的子节点。
- `getChildCount`：用于获取指定节点的子节点数目。

### 10.5 `mListView` 实例

![listview_demo](figures/listview_demo.png)

__图 1__  listview 程序的输出

__清单 4__  listview.c

```c
/**
 * listview.c: Sample program for mGNCS Programming Guide
 *      The demo application for ListView.
 *
 * Copyright (C) 2009 ~ 2019 FMSoft Technologies.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// START_OF_INCS
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define IDC_LISTVIEW    100
#define IDC_BTN1        101
#define IDC_SLEDIT      102

#define COL_NR       TABLESIZE(caption)
#define SCORE_NUM    TABLESIZE(scores)
#define CLASS_NUM    TABLESIZE(classes)
#define SUB_NUM      3

typedef struct _SCORE
{
    char *name;
    int scr[SUB_NUM];
} SCORE;
static char * caption [] =
{
    "Name", "Chinese", "Math", "English"
};

static char *classes [] =
{
    "Grade 1", "Grade 3", "Grade 2"
};

static SCORE scores[] =
{
    {"Tom",     {81, 96, 75}},
    {"Jack",    {98, 62, 84}},
    {"Merry",   {79, 88, 89}},
    {"Bob",     {79, 88, 89}},
};

static NCS_RDR_INFO rdr_info = {
    "classic","classic",NULL
};

static void btn_notify(mWidget *button, int id, int nc, DWORD add_data)
{
    mListView *lstvObj;
    mSlEdit *sleObj;
    HITEM   gradeItem, hItem;
    int     i, j, score;
    float   average = 0;
    char    buff[20];

    lstvObj = (mListView *)ncsGetChildObj(GetParent(button->hwnd), IDC_LISTVIEW);
    sleObj    = (mSlEdit *)ncsGetChildObj(GetParent(button->hwnd), IDC_SLEDIT);
    if (!lstvObj)
        return;


    gradeItem = _c(lstvObj)->getChildItem(lstvObj, 0, 0);
    for (i = 0; i < SCORE_NUM; i++) {
        hItem = _c(lstvObj)->getChildItem(lstvObj, gradeItem, i);

        for (j = 0; j < SUB_NUM; j++) {
            sscanf(_c(lstvObj)->getItemText(lstvObj, hItem, 0, j+1), "%d", &score);
            average += score;
        }
    }
    average = average / (SCORE_NUM * SUB_NUM);

    sprintf (buff, "%4.1f", average);

    _c(sleObj)->setContent(sleObj, buff, 0, strlen(buff));
}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_WIDGET_CLICKED, btn_notify),
    {0, NULL}
};

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
    {
        NCSCTRL_LISTVIEW,
        IDC_LISTVIEW,
        10, 10, 320, 220,
        WS_BORDER | WS_VISIBLE | NCSS_LISTV_SORT | NCSS_LISTV_LOOP,
        WS_EX_NONE,
        "score table",
        NULL,
        &rdr_info,
        NULL,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN1,
        240, 255, 80, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "everage score",
        NULL,
        NULL,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_SLEDIT,
        IDC_SLEDIT,
        100, 256, 80, 28,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
};

static NCS_EVENT_HANDLER mainwnd_handlers[] = {
    {0, NULL}
};

static NCS_MNWND_TEMPLATE mainwnd_tmpl = {
    NCSCTRL_DIALOGBOX,
    7,
    0, 0, 350, 340,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "ListView Demo",
    NULL,
    &rdr_info,
    mainwnd_handlers,
    _ctrl_tmpl,
    sizeof(_ctrl_tmpl)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

static HITEM add_class_item (mListView *self, NCS_LISTV_ITEMINFO *info)
{
// START_OF_ADDITEMS
    NCS_LISTV_ITEMDATA subdata;
    HITEM   hItem;

    subdata.row = info->index;
    subdata.col = 0;
    subdata.text= classes[info->index];
    subdata.textColor = 0;
    subdata.flags = 0;
    subdata.image = 0;

    info->dataSize = 1;
    info->data = &subdata;

    hItem = _c(self)->addItem (self, info);
// END_OF_ADDITEMS

    return hItem;
}

static HITEM add_score_item (mListView *self, NCS_LISTV_ITEMINFO *info)
{
    char    buff[3][20];
    HITEM   hItem;
    int     i = info->index, j;

// START_OF_ADDSUBITEMS
    NCS_LISTV_ITEMDATA subdata[4];

    for (j = 0; j < SCORE_NUM; j ++) {
        subdata[j].flags = 0;
        subdata[j].image = 0;
        subdata[j].row = info->index;
        subdata[j].col = j;
        if (j == 0) {
            subdata[j].text = scores[i].name;
            subdata[j].textColor = 0;
        }
        else {
            sprintf (buff[j-1], "%d", scores[i].scr[j-1]);
            subdata[j].text = buff[j-1];
            if (scores[i].scr[j-1] > 90)
                subdata[j].textColor = 0x0000FF;
            else
                subdata[j].textColor = 0;
        }
    }

    info->dataSize = SCORE_NUM;
    info->data = subdata;

    hItem = _c(self)->addItem (self, info);
// END_OF_ADDSUBITEMS

    if (!hItem)
        return 0;

    return hItem;
}

static BOOL lstv_init(mDialogBox* self)
{
    int     i, j;
    int     color;
    HITEM   hItem = 0, subItem;
    HWND    lstvWnd = GetDlgItem (self->hwnd, IDC_LISTVIEW);
    mListView *lstvObj;
    NCS_LISTV_ITEMINFO  info;
    NCS_LISTV_CLMINFO   lstv_clminfo;

    lstvObj = (mListView*)ncsObjFromHandle(lstvWnd);

    if (!lstvObj)
        return FALSE;

    _c(lstvObj)->freeze(lstvObj, TRUE);
    //add column

// START_OF_ADDCLMS
    for (i = 0; i < COL_NR; i++) {
        lstv_clminfo.index  = i;
        lstv_clminfo.text   = caption[i];
        lstv_clminfo.width  = 74;
        lstv_clminfo.pfnCmp = NULL;
        lstv_clminfo.flags  = NCSF_LSTCLM_CENTERALIGN | NCSF_LSTHDR_CENTERALIGN;
        _c(lstvObj)->addColumn(lstvObj, &lstv_clminfo);
    }
// END_OF_ADDCLMS

    info.height     = 25;
    info.flags      = 0;
    info.foldIcon   = 0;
    info.unfoldIcon = 0;
    for (i = 0; i < CLASS_NUM; i++) {
        info.parent = 0;
        info.index = i;
        hItem = add_class_item (lstvObj, &info);

        for (j = 0; j < SCORE_NUM; j++) {
            info.parent = hItem;
            info.index = j;
            subItem = add_score_item (lstvObj, &info);
        }

    }

// START_OF_SETBGCLR
    color = 0xFFFF00;
    _c(lstvObj)->setBackground(lstvObj, 1, 1, &color);
    color = 0xFF0000;
    _c(lstvObj)->setBackground(lstvObj, 3, 2, &color);
    color = 0x007777;
    _c(lstvObj)->setBackground(lstvObj, 5, -1, &color);
// END_OF_SETBGCLR

    _c(lstvObj)->freeze(lstvObj, FALSE);

    return TRUE;
}

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();
    mDialogBox* dialog =
        (mDialogBox *)ncsCreateMainWindowIndirect (&mainwnd_tmpl, HWND_DESKTOP);

    lstv_init(dialog);
    _c(dialog)->doModal(dialog, TRUE);

    MainWindowThreadCleanup(dialog->hwnd);
    ncsUninitialize();

    return 0;
}
```

