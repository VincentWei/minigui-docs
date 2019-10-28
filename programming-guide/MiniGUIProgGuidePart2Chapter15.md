# 其他高级控件类
# Chapter 14 of Part 2 Other Advanced Control Classes


## 其他高级控件类简介
## Brief Introduction of Other Advanced Control Classes

该类控件主要是视图系列控件，多用于显示各种不同类型的列表项信息。

其他高级控件类的类继承关系如下：

The class of controls are mainly view series controls, mainly used to display list item information of different types.

Class inheritance relations of other advanced control classes are as below:

- [mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget)
   - [mScrollWidget](MStudioMGNCSV1dot0PGP2C7#m_ScrollWidget)
         * [mItemView](MStudioMGNCSV1dot0PGP2C14#mItemView)
            * [mListBox](MStudioMGNCSV1dot0PGP2C14#mListBox)
            * [mScrollView](MStudioMGNCSV1dot0PGP2C14#mScrollView)
            * [mIconview](MStudioMGNCSV1dot0PGP2C14#mIconView)
            * [mListview](MStudioMGNCSV1dot0PGP2C14#mListView)

在高级控件类中将列表项作为一个对象来管理，不同控件使用到的列表项对象不同，各自的继承关系如下：

In the advanced control class, list item is managed as an object. Different controls use different list item objects, and the inheritance relations are as below:

- [mObject](MStudioMGNCSV1dot0PGP2C3#mObject)
   - [mItem](MStudioMGNCSV1dot0PGP2C14#mItem)
         * [mItemManager](MStudioMGNCSV1dot0PGP2C14#mItemManager)
            * [mListItem](MStudioMGNCSV1dot0PGP2C14#mListItem)
         * [mListColumn](MStudioMGNCSV1dot0PGP2C14#mListColumn)

我们首先介绍各列表项对象，再具体介绍各控件类。

Let’s firstly introduce the list item objects, and then concretely introduce the control classes.

## mItem

mItem 对象是所有列表项的基类，提供一系列基本的访问方法。直接使用该对象的有 mListBox, mScrollView 和 mIconView 等控件类。

mItem object is the basic class of all list items, providing a series of basic accessing methods. Control classes such as mListBox, mScrollView and mIconView etc. directly use this object.

### mItem 状态
### Status of mItem

|* 状态名 * | *说明* |
| NCSF_ITEM_NORMAL | 条目状态：正常 |
| NCSF_ITEM_SELECTED | 条目状态：选中 |
| NCSF_ITEM_DISABLED | 条目状态：禁用 |
| NCSF_ITEM_USEBITMAP | 条目状态：包含位图，与NCSF_ITEM_USEICON 互斥 |
| NCSF_ITEM_USEICON | 条目状态：包含图标，与 NCSF_ITEM_USEBITMAP 互斥 |

|* Status name * | *Explanation* |
| NCSF_ITEM_NORMAL | Item status: normal |
| NCSF_ITEM_SELECTED | Item status: selected |
| NCSF_ITEM_DISABLED | Item status: banned |
| NCSF_ITEM_USEBITMAP | Item status: contain bit map, and mutually exclude with NCSF_ITEM_USEICON |
| NCSF_ITEM_USEICON | Item status: contain icon, and mutually exclude with NCSF_ITEM_USEBITMAP |


### mItem 属性
### Property of mItem

|* 属性ID *| *类型* | *权限* |* 说明 *|
| NCSP_ITEM_HEIGHT | int | RW | 条目当前高度 |
| NCSP_ITEM_FLAGS | DWORD | RW | 条目状态 |

| *Property* | *Type* | *Authority* | *Explanation* |
| NCSP_ITEM_HEIGHT | int | RW | Item current height |
| NCSP_ITEM_FLAGS | DWORD | RW | Item status |


### mItem 方法
### Method of mItem

继承自[mObject的方法](MStudioMGNCSV1dot0PGP2C3#mObject)

It is inherited from [the method of mObject](MStudioMGNCSV1dot0PGP2C3#mObject)

一个条目可以包含多种内容信息，如文本、图片等等。提供的基础方法主要有：

An item can contain multiple kinds of content information, such as text and image etc. Basic methods provided are:
```cplusplus
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
- isSelectedItem：判断当前条目是否处于选中状态。
- isEnabledItem：判断当前条目是否处于使能状态。
- setItemString：设置条目文本。
- getItemString：获取条目当前文本。
- setItemHeight：设置条目高度。
- getItemHeight：获取条目高度。
- setItemFlags：设置条目状态。
- getItemFlags：获取条目状态。
- setItemImage：设置条目图标。
- getItemImage：获取条目图标。
- setItemAddData：设置条目附加数据。
- getItemAddData：获取条目附加数据。
- setItemEditor：设置条目编辑器。
- getItemEditor：获取条目编辑器。

- isSelectedItem：judge if the current item is in selected status.。
- isEnabledItem：judge if the current item is in enabled status.
- setItemString: set item text.
- getItemString: get item current text.
- setItemHeight：set item height.
- getItemHeight：get item height.
- setItemFlags：set item status
- getItemFlags：get item status.
- setItemImage：set item icon.
- getItemImage：get item icon.
- setItemAddData：set item additional data.
- getItemAddData：get item additional data.
- setItemEditor：set item editor.
- getItemEditor：get item editor.

## mItemManager

通过链表管理 mItem 及其子类的基类管理器，提供对列表项的添加、删除和设置等方法。

Basic class manager managing mItem and its child class through linked list, providing methods of addling, removing and setting list items.

### mItemManager 状态
### Status of mItemManager

继承自 <a href="#mItem 状态">mItem 状态</a>

It is inherited from <a href="#Status of mItem">the status of mItem</a>

|* 状态名 * | *说明* |
| NCSF_ITMMNG_AUTOSORT | 条目插入时自动排序 |
| NCSF_ITMMNG_FROZEN | 禁止或使能条目刷新功能 |

|* Status name * | *Explanation* |
| NCSF_ITMMNG_AUTOSORT | Automatic sorting when the item is inserted |
| NCSF_ITMMNG_FROZEN | Forbidden or enabled item refreshing function |


### mItemManager 属性
### Property of mItemManager

继承自 <a href="#mItem 属性">mItem 属性</a>
It is inherited from <a href="#Property of mItem">the property of mItem</a>

|* 属性ID *| *类型* | *权限* |* 说明 *|
| NCSP_ITMMNG_ITEMCOUNT | int | RO | 包含的条目数 |
| NCSP_ITMMNG_FLAGS | DWORD | RW | 条目状态 |
| NCSP_ITMMNG_TOTALHEIGHT | int | RO | 所有条目总高度 |


| *Property* | *Type* | *Authority* | *Explanation* |
| NCSP_ITMMNG_ITEMCOUNT | int | RO | Item number contained |
| NCSP_ITMMNG_FLAGS | DWORD | RW | Item status |
| NCSP_ITMMNG_TOTALHEIGHT | int | RO | Total height of all the items |

### mItemManager 方法
### Method of mItemManager

继承自 <a href="#mItem 方法">mItem 方法</a>
It is inherited from <a href="#Method of mItem">the method of mItem</a>

---++++ 回调方法
---++++ Callback Method

mItemManager 类支持根据列表项或列表项字符串进行比较的2个回调方法。其中根据列表项比较的方法优先于根据列表项字符串比较的方法。

mItemManager class supports the two callback methods of carrying out comparison according to list item or list item character string. The method of carrying out comparison according to list item prevails to the method of carrying out comparison according to list item character string.

```cplusplus
typedef int (*NCS_CB_CMPITEM) (mItemManager *manager, HITEM hItem1, HITEM hItem2);
typedef int (*NCS_CB_CMPSTR) (const char* s1, const char* s2, size_t n);
NCS_CB_CMPITEM setItemCmpFunc(mItemManager *self, NCS_CB_CMPITEM func); 
NCS_CB_CMPSTR setStrCmpFunc(mItemManager *self, NCS_CB_CMPSTR func);
NCS_CB_CMPSTR getStrCmpFunc(mItemManager *self);
```
- setItemCmpFunc：用于设置根据列表项自身进行比较的回调方法，同时返回先前设置的方法。
- setStrCmpFunc：用于设置根据列表项字符串进行比较的回调方法，同时返回先前设置或默认的方法。
- getStrCmpFunc：用于获取当前使用的字符串比较方法。

- setItemCmpFunc：used to set the callback method of carrying out comparison according to the list item itself, and at the same time, previous setting method is returned.
- setStrCmpFunc：used to set the callback method of carrying out comparison according to the list item character string, and at the same time, the previous setting or default method is returned.
- getStrCmpFunc：used to get the character string comparison method in current use.

---++++ 排序方法
---++++ Sorting Method

```cplusplus
void setAutoSortItem(mItemManager *self, BOOL sort);    
int sortItems(mItemManager *self, NCS_CB_CMPITEM pfn);  
```
- setAutoSortItem：在添加所有列表项前设置或取消排序标记。当排序标记设置成功后，在其后添加的所有列表项将和已有的列表项进行相应比较后确定插入位置。
- sortItems：按照指定的列表项比较方法对所有列表项进行重新排序。

- setAutoSortItem: set or cancel sorting symbol before adding all the list items. After the sorting symbol setting is successful, all the list items added afterwards will be compared to the existing list items and insert location is determined.
- sortItems: sort all the list items again according to the specified list item comparison method.

---++++ 刷新方法
---++++ Refreshing Method

```cplusplus
BOOL freeze(mItemManager *self, BOOL lock);     
BOOL isFrozen(mItemManager *self);
int adjustItemsHeight(mItemManager *self, int diff);
```
- freeze：冻结或恢复对列表项的刷新。
- isFrozen：判断当前是否处于可刷新状态。
- adjustItemsHeight：调整列表项总高度变化值，在管理器处理可刷新状态时，该方法在调整完大小后会将变化立即反映到 UI 上，否则将不刷新 UI。

- freeze: freeze or recover refreshment to the list item.。
- isFrozen: judge if it is in refreshable status currently.
- adjustItemsHeight: adjust the list item total height change value. When the manager handles refreshable status, after the method adjusts the size, it will immediately reflect the changes to UI, otherwise UI will not be refreshed.

---++++ 创建/删除/移动列表项
---++++ Create/Remove/Move List Items

在对列表项进行插入时，首先确认是否是自动排序支持，如果是，则按照自动排序算法计算排序插入位置；否则根据前、后列表项或指定索引依次进行插入尝试，尝试成功则返回正确位置。

When inserting the list item, firstly confirm if it is automatic sorting supported, if so, calculate the sorting insert location according the automatic sorting calculation method; otherwise, conduct insert tries by sequence according to front and back list items or specified index, if the try is successful, return to the correct location. 

```cplusplus
HITEM createItem(mItemManager *self, HITEM prev, HITEM next, int index, int *pos);
int insertItem(mItemManager *self, HITEM hItem, HITEM prev, HITEM next, int index, int *pos);
int moveItem(mItemManager *self, mItem *curItem, int count, mItem* prevItem);
int removeItem(mItemManager *self, HITEM hItem);           
BOOL removeAll(mItemManager *self);
```
- createItem：创建一个新的列表项并插入到指定位置，同时通过最后的参量返回已插入的位置。
- insertItem：将已创建的列表项插入到管理器镮的指定位置，同时通过最后的参量返回已插入的位置。
- moveItem：将当前列表项及其后指定数目的列表项移动到某一列表项位置之后。
- removeItem：删除某一指定列表项。
- removeAll：删除所有列表项。

- createItem: create a new list item and insert to the specified location, and at the same time, return to the inserted location through the final parameter.
- insertItem: insert the created list item to the specified location of the manager, and at the same time, return to the inserted location through the final parameter. 
- moveItem: move the current list items and the list items of specified number afterwards to behind a certain list item location.
- removeItem: remove a certain specified list item
- removeAll: remove all the list items.
  
---++++ 遍历列表项
---++++ Traverse List Items

```cplusplus
list_t* getQueue(mItemManager *self);                              
HITEM getListEntry(list_t* entry);

HITEM getFirstItem(mItemManager *self);
HITEM getNext(mItemManager *self, HITEM hItem);       
HITEM getPrev(mItemManager *self, HITEM hItem);
```
- getQueue：获取管理器的列表项列首。
- getListEntry：获取指定链表项的列表项指针。
- getFirstItem：获取管理器中的第一个列表项。
- getNext：获取指定列表项的后一个列表项。
- getPrev：获取指定列表项的前一个列表项。

- getQueue: get the list item column header of the manager.
- getListEntry: get the list item pointer of the specified linked list item.
- getFirstItem: get the first list item in the manager.
- getNext: get the next list item of the specified list item.
- getPrev: get the previous list item of the specified list item.

---++++ 获取列表项信息
---++++ Get List Item Information

```cplusplus
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
- getItem：获取指定索引的列表项。
- indexOf：获取指定列表项的索引。
- inItem：获取指定鼠标位置下的列表项，并返回列表项的起始位置。
- getItemYPos：获取指定列表项的起始纵向坐标。
- getTotalHeight：获取列表项管理器的整体高度。
- getItemCount：获取列表项总数目。
- isEmpty：判断列表项是否为空。
- getSelectionCount：获取选中列表项数目。
- getSelection：获取指定数目的选中列表项信息。

- getItem: get the list item of the specified index.
- indexOf: get index of the specified list item.
- inItem: get list item under the specified mouse location, and return to the starting location of the list item.
- getItemYPos: get starting vertical coordinate of the specified list item.
- getTotalHeight: get total height of the list item manager.
- getItemCount: get total number of the list items.。
- isEmpty: judge if the list item is empty.
- getSelectionCount: get number of the selected list items.
- getSelection: get information of the selected list items of specified number.

---++++ 设置/获取列表项状态
---++++ Set/Get List Item Status

```cplusplus
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

- isEnabled：判断指定列表项是否处于使能状态。
- enable：使能或禁止指定列表项。
- isSelected：判断指定列表项是否处于选择状态。
- select：选择或取消选择指定列表项。
- selectAll：选中所有列表项。
- deselectAll：取消所有列表项的选中状态。
- hilight：高亮选择指定的列表项。
- getHilight：获取当前高亮选择列表项。
- isHilight：判断指定列表项是否处于高亮状态。
- setHeight：设置列表项高度。
- getHeight：获取列表项高度。
- setAddData：设置列表项附加数据。
- getAddData：获取列表项附加数据。
- setImage：设置列表项位图信息。
- getImage：获取列表项位图信息。
- setFlags：设置列表项状态标志。
- getFlags：获取列表项状态标志。
- setText：设置列表项文本字符串。
- getText：获取列表项文本字符串。
- getTextLen：获取列表项文本字符串长度。

- isEnabled: judge if the specified list item is in enabled status.。
- enable: enable of forbid the specified list item.
- isSelected: judge if the specified list item is in selected status.
- select: select or deselect the specified list item.
- selectAll: select all the list items.
- deselectAll: Cancel the selected status of all the list items.
- hilight: high light select the specified list item.
- getHilight: get the current high light selected list item.
- isHilight: judge if the specified list item is in high light status.
- setHeight: set height of the list item.
- getHeight: get height of the list item.
- setAddData: set additional data of the list item.
- getAddData: get additional data of the list item.
- setImage: set bit map information of the list item.
- getImage: get bit map information of the list item.
- setFlags: set status symbol of the list item.
- getFlags: get status symbol of the list item.
- setText: set text character string of the list item.
- getText: get text character string of the list item.
- getTextLen: get length of the text character string of the list item.

## mListItem
## mListItem

mListItem 对象用于描述 mListView 控件的行对象。

mListItem object is used to describe the row object of mListView control.

### mListItem 状态
### Status of mListItem

继承自 <a href="#m_ItemManager 状态">mItemManger 状态</a>

It is inherited from <a href="#Status of m_ItemManager">the status of mItemManger </a>

|* 状态名 * | *说明* |
| NCSF_LSTITM_FOLD | 折叠条目 |
| NCSF_LSTITM_PRIVBKCOL | 条目包含私有背景色 |
| NCSF_LSTITM_PRIVBKCOL | 条目包含私有前景色 |


|* Status name * | *Explanation* |
| NCSF_LSTITM_FOLD | Folded item |
| NCSF_LSTITM_PRIVBKCOL | The item contains private background color |
| NCSF_LSTITM_PRIVBKCOL | The item contains private foreground color |

### mListItem 属性
### Property of mListItem

继承自 <a href="#m_ItemManager 属性">mItemManager 属性</a>

It is inherited from <a href="#Property of m_ItemManager"> the property of mItemManager </a>

|* 属性ID *| *类型* | *权限* |* 说明 *|
| NCSP_LSTITM_NRCHILD | int | RO | 包含的子条目数 |
| NCSP_LSTITM_DEPTH | int | RO | 条目的深度 |
| NCSP_LSTITM_RHEIGHT | int | RO | 条目可见时的实际高度 |


| *Property* | *Type* | *Authority* | *Explanation* |
| NCSP_LSTITM_NRCHILD | int | RO | Child item number contained |
| NCSP_LSTITM_DEPTH | int | RO | Depth of the item |
| NCSP_LSTITM_RHEIGHT | int | RO | Actual height when the item is visible |


### mListItem 方法
### Method of mListItem

继承自 <a href="#m_ItemManager 方法">mItemManager 方法</a>

It is inherited from <a href="#Method of m_ItemManager">the method of mItemManager</a>

mListItem 对象提供了一系列操作方法：

mListItem object provides a series of operation methods:

```cplusplus
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
- setBackground：用于设置单元背景色。当 _color_ 为空时对原设置进行清空处理；当 _index_ 索引无效时，设置默认行背景色，否则设置指定单元背景色。
- getBackground：用于获取单元背景色。当 _index_ 索引无效时，通过 _color_ 返回默认行背景色，否则返回指定单元背景色。
- setForeground：用于设置单元前景色。当 _color_ 为空时对原设置进行清空处理；当 _index_ 索引无效时，设置默认行前景色，否则设置指定单元前景色。
- getForeground：用于获取单元前景色， 当 _index_ 索引无效时，通过 _color_ 返回默认行前景色，否则返回指定单元前景色。
- addChild：添加指定的子条目。
- delChild：删除指定的子条目。
- setFold：用于折叠或展开指定条目。
- getparent：用于获取指定条目的父条目。
- getChildCount：获取包含的子条目数目。
- getDepth：获取条目深度。
- isFold：判断条目是否处于折叠状态。

- setBackground: used to set unit background color. When the color is empty, empty the original setting; when the index is invalid, set default row background color, otherwise set the specified unit background color. 
- getBackground: used to get unit background color. When the index is invalid, return the default row background color through color, otherwise return the specified unit background color.
- setForeground: used to set unit foreground color. When the color is empty, empty the original setting; when the index is invalid, set the default row foreground color, otherwise set the specified unit foreground color.
- getForeground: used to get the unit foreground color. When the index is invalid, return the default row foreground color through color, otherwise return the specified unit foreground color. 
- addChild: add the specified child item.
- delChild: delete the specified child item.
- setFold: used to fold or unfold the specified item.
- getparent: used to get the parent item of the specified item.
- getChildCount: get the number of the child item contained.
- getDepth: get the item depth.
- isFold: judge if the item is in folded status.

## mListColumn

mListColumn 对象用于描述 mListView 控件的列对象。

mListColumn object is used to describe the column object of mListView Control.

### mListColumn 状态
### Status of mListColumn

继承自 <a href="#mItem 状态">mItem 状态</a>

It is inherited from <a href="#Status of mItem">the status of mItem</a>

|* 状态名 * | *说明* |
| NCSF_LSTCLM_LEFTALIGN | 文本对齐方式：左对齐 |
| NCSF_LSTCLM_RIGHTALIGN | 文本对齐方式：右对齐 |
| NCSF_LSTCLM_CENTERALIGN | 文本对齐方式：居中对齐 |

|* Status name * | *Explanation* |
| NCSF_LSTCLM_LEFTALIGN | Text alignment mode: left aligned |
| NCSF_LSTCLM_RIGHTALIGN | Text alignment mode: right aligned |
| NCSF_LSTCLM_CENTERALIGN | Text alignment mode: center aligned |

### mListColumn 属性
### Property of mListColumn

继承自 <a href="#mItem 属性">mItem 属性</a>

It is inherited from <a href="#Property of mItem">the property of mItem</a>

|* 属性ID *| *类型* | *权限* |* 说明 *|
| NCSP_LSTCLM_POSX | int | RW | 列起始位置横坐标 |
| NCSP_LSTCLM_WIDTH | int | RW | 列宽 |
| NCSP_LSTCLM_SORTTYPE | ncsLstClmSortType | RW | 列表项排序方式：值为升序、降序或不排序三者选其一 |
| NCSP_LSTCLM_CMPFUNC | NCS_CB_LISTV_CMPCLM | RW | 两列表项比较的回调方法 |

| *Property* | *Type* | *Authority* | *Explanation* |
| NCSP_LSTCLM_POSX | int | RW | Column starting position horizontal coordinate |
| NCSP_LSTCLM_WIDTH | int | RW | Column width |
| NCSP_LSTCLM_SORTTYPE | ncsLstClmSortType | RW | List item sorting mode: the values are ascending, descending or not sorted  |
| NCSP_LSTCLM_CMPFUNC | NCS_CB_LISTV_CMPCLM | RW | Callback method of comparison of the two list items |


下面是属性中涉及的数据结构定义：

The following is the data structure definition involved in the property

```cplusplus
typedef enum
{
    NCSID_LSTCLM_NOTSORTED = 0,  //不排序// Not sorted
    NCSID_LSTCLM_HISORTED, //升序// Ascending
    NCSID_LSTCLM_LOSORTED //降序// Descending
}ncsLstClmSortType;

typedef struct _NCS_LSTCLM_SORTDATA
{
    int     column;  //排序列索引// Sorted column index
    int     losorted; //排序列排序方式// Sorted column sorting mode
    mWidget *obj; //包含比较项的控件类// Control class containing comparison items
}NCS_LSTCLM_SORTDATA;

typedef int (*NCS_CB_LISTV_CMPCLM)(HITEM nItem1, HITEM nItem2, NCS_LSTCLM_SORTDATA *sortData);
```

## mItemView

基类，不允许直接使用。

Basic class, direct use is not allowed

### mItemView 风格
### Style of mItemView

继承自[mScrollWidget的风格](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

It is inherited from [the style of mScrollWidget](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

|* 风格名 * | *miniStudio属性名* | *说明* |
| NCSS_ITEMV_AUTOSORT | - | 条目自动排序 |
| NCSS_ITEMV_LOOP | - | 条目可循环浏览 |
| NCSS_ITEMV_SINGLE | - | 条目单选支持，默认风格 |
| NCSS_ITEMV_MULTIPLE | - | 条目多选支持 |


| *Style name* | *mstudio property name* | *Explanation* |
| NCSS_ITEMV_AUTOSORT | - | Item automatic sorting |
| NCSS_ITEMV_LOOP | - | Item circulative browsing |
| NCSS_ITEMV_SINGLE | - | Item single selection supported, default style |
| NCSS_ITEMV_MULTIPLE | - | Item multi selection supported |

### mItemView 属性
### Property of mItemView

继承自[mScrollWidget的属性](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

Inherited from [the property of mScrollWidget](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

|* 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_ITEMV_DEFITEMHEIGHT | - | int | RW | 条目默认高度 |
| NCSP_ITEMV_ITEMCOUNT | - | int | RO | 条目总数目 |

| *Property ID* | *mstudio name* | *Type* | *Authority* | *Explanation* |
| NCSP_ITEMV_DEFITEMHEIGHT | - | int | RW | Item default height |
| NCSP_ITEMV_ITEMCOUNT | - | int | RO | Item total number |


### mItemView 事件
### Event of mItemView

继承自[mScrollWidget的事件](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)
It is inherited from [the event of mScrollWidget](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

|* 事件通知码 *|* 说明 *|* 参数 *|
| NCSN_ITEMV_CLICKED | 鼠标点击事件 | 被点击的条目句柄 |
| NCSN_ITEMV_SELCHANGING | 正在改变选择的条目 | 处于高亮状态的条目句柄 |
| NCSN_ITEMV_SELCHANGED | 选择条目已改变 | 新的选择条目句柄 |
| NCSN_ITEMV_ENTER | Enter 键被按下 | - |
| NCSN_ITEMV_SETFOCUS | 获取焦点 | - |
| NCSN_ITEMV_KILLFOCUS | 失去焦点 | - |

|* Event notification code *|* Explanation *|* Parameter *|
| NCSN_ITEMV_CLICKED | Mouse clicking event | Clicked item sentence handle |
| NCSN_ITEMV_SELCHANGING | Item changing selection | Item sentence handle in high light status |
| NCSN_ITEMV_SELCHANGED | The selected item has changed | New selected item sentence handle |
| NCSN_ITEMV_ENTER | Enter key is pressed down | - |
| NCSN_ITEMV_SETFOCUS | Get focus | - |
| NCSN_ITEMV_KILLFOCUS | Lose focus | - |


### mItemView 方法
### Method of mItemView

继承自[mScrollWidget的方法](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

It is inherited from [the method of mScrollWidget](MStudioMGNCSV1dot0PGP2C3#mScrollWidget)

---++++ 回调方法
---++++ Callback Method

mItemView 提供了初始化、绘制和销毁列表项3个回调方法，同时还有比较列表项的回调方法。

mItemView provides three callback methods, initialization, drawing and destroying list item, at the same time, there is the callback method of comparing list items.

```cplusplus
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

---++++ 排序方法
---++++ Sorting Method

```cplusplus
void setAutoSortItem(mItemView *self, BOOL sort);    
int sortItems(mItemView *self, NCS_CB_CMPITEM pfn);  
```
- setAutoSortItem：在添加所有列表项前设置或取消排序标记。当排序标记设置成功后，在其后添加的所有列表项将和已有的列表项进行相应比较后确定插入位置。
- sortItems：按照指定的列表项比较方法对所有列表项进行重新排序。

- setAutoSortItem: Set or cancel sorting symbol before adding all the list items. After the sorting symbol setting is successful, after comparing all the list items added afterwards and the existing list items, confirm the insert position.
- sortItems: according to the specified list item comparison method, sort all the list items again.

---++++ 刷新方法
---++++ Refreshing Method

```cplusplus
void freeze(mItemView *self, BOOL lock);
BOOL isFrozen(mItemView *self);
int adjustItemsHeight(mItemView *self, int diff);
```
- freeze：冻结或恢复对列表项的刷新。
- isFrozen：判断当前是否处于可刷新状态。
- adjustItemsHeight：调整列表项总高度变化值，该方法在控件调整完列表项大小后会将变化立即反映到 UI 上，否则将不刷新 UI。

- freeze: Freeze or recover refreshment to the list item.。
- isFrozen: judge if it is in refreshable status currently.
- adjustItemsHeight: adjust the list item total height change value. The method will immediately reflect the change to UI after the control adjusts the list item size, otherwise UI will not be refreshed.

---++++ 创建/删除/移动列表项
---++++ Create/Remove/Move List Item

在对列表项进行插入时，首先确认是否是自动排序支持，如果是，则按照自动排序算法计算排序插入位置；否则根据前、后列表项或指定索引依次进行插入尝试，尝试成功则返回正确位置。

When inserting to the list item, firstly determine if it is automatic sorting supported, if so, calculate the sorting insert position according to the automatic sorting calculation method; otherwise conduct insert tries by sequence according to the front and back list item or specified index; after the try is successful, return to the correct position.

```cplusplus
HWND createItem(mItemView *self, HITEM prev, HITEM next, int index,
        int height, DWORD addData, int *pos, BOOL adjust);
int insertItem(mItemView *self, HITEM hItem, HITEM prev, HITEM next,
        int index, int *pos);
int removeItem(mItemView *self, HITEM hItem);

BOOL removeAll(mItemView *self);
```
- createItem：创建一个新的列表项并插入到指定位置，同时通过最后的参量返回已插入的位置。
- insertItem：将已创建的列表项插入到管理器镮的指定位置，同时通过最后的参量返回已插入的位置。
- removeItem：删除某一指定列表项。
- removeAll：删除所有列表项。

- createItem: create a new list item and insert to the specified position, and at the same time, return to the inserted position according to the final parameter.
- insertItem: insert the created list item to the specified position of the manager, and at the same time, return to the inserted position according to the final parameter.
- removeItem: remove certain specified list item.
- removeAll: remove all the list items.
  
---++++ 遍历列表项
---++++ Traverse List Item

```cplusplus
list_t* getQueue(mItemView *self);
HITEM getListEntry(mItemView *self, list_t* entry);
HITEM getFirstItem(mItemView *self);
HITEM getNext(mItemView *self, HITEM hItem);
HITEM getPrev(mItemView *self, HITEM hItem);
```
- getQueue：获取管理器的列表项列首。
- getListEntry：获取指定链表项的列表项指针。
- getFirstItem：获取管理器中的第一个列表项。
- getNext：获取指定列表项的后一个列表项。
- getPrev：获取指定列表项的前一个列表项。

- getQueue: get the list item column header of the manager.。
- getListEntry: get the list item pointer of the specified linked list item.
- getFirstItem: get the first list item in the manager.
- getNext: get the next list item of the specified list item.
- getPrev: get the previous list item of the specified list item.

---++++ 获取列表项信息
---++++ Get List Item Information

```cplusplus
HITEM getItem(mItemView *self, int index);
int indexOf(mItemView *self, HITEM hItem);

int inItem(mItemView *self, int mouseX, int mouseY, HITEM *pRet, POINT *pt);

int getTotalHeight(mItemView *self);
int getItemCount(mItemView *self);
int isEmpty(mItemView *self);
int getSelectionCount(mItemView *self);
BOOL getSelection(mItemView *self, HITEM *pRet, int count);
```
- getItem：获取指定索引的列表项。
- indexOf：获取指定列表项的索引。
- inItem：获取指定鼠标位置下的列表项，并返回列表项的起始位置。
- getTotalHeight：获取列表项管理器的整体高度。
- getItemCount：获取列表项总数目。
- isEmpty：判断列表项是否为空。
- getSelectionCount：获取选中列表项数目。
- getSelection：获取指定数目的选中列表项信息。

- getItem: get list item of the specified index.
- indexOf: get index of the specified list item. 
- inItem: get the list item under the specified mouse position, and return to the starting position of the list item.
- getTotalHeight: get the total height of the list item manager.
- getItemCount: get the total number of the list items.
- isEmpty: judge if the list item is empty.
- getSelectionCount: get number of the selected list items.
- getSelection: get the selected list item information of specified number.

---++++ 设置/获取列表项状态
---++++ Set/Get List Item Status

```cplusplus
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

- isEnabled：判断指定列表项是否处于使能状态。
- enable：使能或禁止指定列表项。
- isSelected：判断指定列表项是否处于选择状态。
- select：选择指定的列表项。
- deselect：取消选择指定的列表项。
- selectAll：选中所有列表项。
- deselectAll：取消所有列表项的选中状态。
- hilight：高亮选择指定的列表项。
- getHilight：获取当前高亮选择列表项。
- isHilight：判断指定列表项是否处于高亮状态。
- setItemHeight：设置列表项高度。
- getItemHeight：获取列表项高度。
- setAddData：设置列表项附加数据。
- getAddData：获取列表项附加数据。
- setImage：设置列表项位图信息。
- getImage：获取列表项位图信息。
- setFlags：设置列表项状态标志。
- getFlags：获取列表项状态标志。
- setText：设置列表项文本字符串。
- getText：获取列表项文本字符串。
- getTextLen：获取列表项文本字符串长度。


- isEnabled: judge if the specified list item is in enabled status.
- enable: enable or forbid specified list item.
- isSelected: judge if the specified list item is in selected status.
- select: select specified list item.
- deselect: deselect the specified list item.
- selectAll: select all the list items.
- deselectAll: cancel the selected status of all the list items.
- hilight: high light select the specified list item.
- getHilight: get the currently high light selected list item.
- isHilight: judge if the specified list item is in high light status.
- setItemHeight: set height of the list item.
- getItemHeight: get height of the list item.
- setAddData: set additional data of the list item.
- getAddData: get additional data of the list item.
- setImage: set bit map information of the list item.
- getImage: get bit map information of the list item.
- setFlags: set status symbol of the list item.
- getFlags: get status symbol of the list item.
- setText: set text character string of the list item.
- getText: get text character string of the list item.
- getTextLen: get length of the text character string of the list item.

---++++ 其它
---++++ Others
```cplusplus
int getFirstVisItem(mItemView *self);
void resetContent(mItemView *self);
int getRect(mItemView *self, HITEM hItem, RECT *rcItem, BOOL bConv);
int getCurSel(mItemView *self);
int setCurSel(mItemView *self, int newSel);
void refreshItem(mItemView *self, HITEM hItem, const RECT *rcInv);
BOOL showItemByIdx(mItemView *self, int index);
BOOL showItem(mItemView *self, HITEM hItem);
```
- getFirstVisItem：获取第一个可见的列表项。
- resetContent：删除所有列表项，并恢复所有信息配置到初始值。
- getRect：获取指定列表项的矩形区域，并通过最后参数决定是否将坐标转换为相对于屏幕的坐标。
- getCurSel：获取当前选中列表项索引。
- setCurSel：对通过索引设置指定列表项为选中项并将其显示出来，成功返回0，失败返回-1。
- refreshItem：刷新指定列表项的指定区域，若指定区域为空，则刷新整个列表项。
- showItemByIdx：根据索引显示指定列表项。
- showItem：显示指定列表项。

- getFirstVisItem: get the first visible list item.
- resetContent: remove all the list items, and reset all the information configuration to the initial value.
- getRect: get the rectangular region of the specified list item, and decide if converting the coordinate to the coordinate relative to the screen through the final parameter.
- getCurSel: get the currently selected list item index.
- setCurSel: set the specified list item as selected item through index and display it, if it is successful, return 0; if it is failed, return -1.
- refreshItem: refresh the specified region of the specified list item; if the specified region is empty, refresh the whole list item.
- showItemByIdx: show the specified list item according to the index.
- showItem: show the specified list item


## mScrollView

- *控件窗口类*: NCSCTRL_SCROLLVIEW
- *控件英文名*: ScrollView
- *简介*: 用于显示和处理列表项，其中列表项的内容绘制完全是由应用程序自己确定。
- *示意图*: 


- *Control window class*: NCSCTRL_SCROLLVIEW
- *Control English name*: ScrollView
- *Brief introduction*: Used to show and handle list item, and content drawing of the list item is decided by the applications themselves.
- *Schematic diagram*: 

### mScrollView 风格
### Style of mScrollView

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

It is inherited from  <a href="#Style of m_ItemView">the style of mItemView</a>

|* 风格名 * | *miniStudio属性名* | *说明* |
| NCSS_SCRLV_LOOP | - | 条目可循环浏览 |
| NCSS_SCRLV_SORT | - | 条目自动排序 |


| *Style name* | *mstudio property name* | *Explanation* |
| NCSS_SCRLV_LOOP | - | Item circulative browsing |
| NCSS_SCRLV_SORT | - | Item automatic sorting |

### mScrollView 属性
### Property of mScrollView

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>

it is inherited from  <a href="#Property of mItemView"> the property of mItemView </a>

### mScrollView 事件
### Event of mScrollView
继承自 <a href="#m_ItemView 事件">mItemView 事件</a>
It is inherited from  <a href="#Event of mItemView">the event of mItemView</a>

|* 事件通知码 *|* 说明 *|* 参数 *|
| NCSN_SCRLV_CLICKED | 鼠标点击事件 | 被点击的条目句柄 |
| NCSN_SCRLV_SELCHANGING | 正在改变选择的条目 | 处于高亮状态的条目句柄 |
| NCSN_SCRLV_SELCHANGED | 选择条目已改变 | 新的选择条目句柄 |


|* Event notification code *|* Explanation *|* Parameter *|
| NCSN_SCRLV_CLICKED | Mouse clicking event | Clicked item sentence handle |
| NCSN_SCRLV_SELCHANGING | Item changing selection | Item sentence handle in high light status |
| NCSN_SCRLV_SELCHANGED | The selected item has changed | New selected item sentence handle |


### mScrollView 方法
### Method of mScrollView
继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

It is inherited from <a href="#Method of mItemView">the method of mItemView</a>

mScrollView 继承自 mItemView，提供了控件自身的 addItem 方法，该方法通过列表项信息创建并插入列表项，同时返回插入位置给接口调用者。

mScrollView in inherited from mItemView, which provides addItem method of the control itself. The method creates and inserts list item through list item information, and at the same time, returns the insert position to the interface caller.

```cplusplus
typedef struct _NCS_SCRLV_ITEMINFO
{
    int     index;
    int     height;
    DWORD   addData;
}NCS_SCRLV_ITEMINFO;

HITEM addItem(mScrollView *self, NCS_SCRLV_ITEMINFO *info, int *pos);
```    

在添加列表项内容前通过进行一些基础回调方法的设置等内容，如：

Before adding list item content, carry out setting of some basic callback method, such as:

```cplusplus
%INCLUDE{"%ATTACHURL%/scrollview" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```


### mScrollView 实例
### Instance of mScrollView

<p align=center>
<img src="%ATTACHURLPATH%/scrollview_demo.png" alt="scrollview_demo.png"/><br>
图 p2c6-1  scrollview 程序的输出

Figure p2c6-1 Output of scrollview Program
</p>

<p align=center>清单 p214-1  scrollview.c</p>
<p align=center>List p214-1 scrollview.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/scrollview"}%
```

## mListBox

- *控件窗口类*: NCSCTRL_LISTBOX
- *控件英文名*: ListBox
- *简介*: 将用户提供的一系列可选项显示在可滚动的子窗口中，用户可通过键盘及鼠标操作来选中某一项或者多个项，选中的列表项通常高亮显示。列表框的最典型用法就是文件打开对话框。
- *示意图*:  

- *Control window class*: NCSCTRL_LISTBOX
- *Control English name*: ListBox
- *Brief introduction*: Display a series of options provided by the users in the child window that can scroll. Users can select certain item or multiple items through keyboard and mouse operation, and the selected list item is usually high light displayed. The most typical usage of list box is file opening dialog box. 
- *Schematic diagram*: 
<img src="%ATTACHURLPATH%/listbox.png" alt="listbox.png"/>

### mListBox 风格
### Style of mListBox

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>
It is inherited from <a href="#Style of mItemView">the style of mItemView </a>

|* 风格名 * | *miniStudio属性名* | *说明* |
| NCSS_LSTBOX_SINGLE | Multi->FALSE | 单选列表项支持 |
| NCSS_LSTBOX_MULTIPLE | Multi->TRUE | 多选列表项支持 |
| NCSS_LSTBOX_SORT | AutoSort | 列表项排序支持 |
| NCSS_LSTBOX_MOUSEFOLLOW | MouseFollow | 列表项支持鼠标跟随 |
| NCSS_LSTBOX_STRING | - | 带有字符串的列表项 |
| NCSS_LSTBOX_USEBITMAP | UseBitmap | 列表项带有位图 |
| NCSS_LSTBOX_CHECKBOX | Checkable | 列表项包含 checkbox |
| NCSS_LSTBOX_AUTOCHECK | AutoCheck | 列表项中的 checkbox 支持自动选择 |
| NCSS_LSTBOX_AUTOCHECKBOX | - | 同时包含 NCSS_LSTBOX_CHECKBOX 和 NCSS_LSTBOX_AUTOCHECK 2种风格 |


| *Style name* | *mstudio property name* | *Explanation* |
| NCSS_LSTBOX_SINGLE | Multi->FALSE | Single selection list item supported |
| NCSS_LSTBOX_MULTIPLE | Multi->TRUE | Multi selection list item supported |
| NCSS_LSTBOX_SORT | AutoSort | List item sorting supported |
| NCSS_LSTBOX_MOUSEFOLLOW | MouseFollow | The list item supports mouse following |
| NCSS_LSTBOX_STRING | - | List item with character string |
| NCSS_LSTBOX_USEBITMAP | UseBitmap | The list item has bit map |
| NCSS_LSTBOX_CHECKBOX | Checkable | The list item contains checkbox |
| NCSS_LSTBOX_AUTOCHECK | AutoCheck | checkbox in the list item supports automatic selection |
| NCSS_LSTBOX_AUTOCHECKBOX | - | Simultaneously contain NCSS_LSTBOX_CHECKBOX and NCSS_LSTBOX_AUTOCHECK styles |

### mListBox 属性
### Property of mListBox

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>

It is inherited from <a href="#Property of mItemView">the property of mItemView</a>

|* 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_LSTBOX_ITEMWIDTH | - | int | RO | 列表项最大宽度 |
| NCSP_LSTBOX_ITEMCOUNT | - | int | RO | 列表项总数目 |
| NCSP_LSTBOX_ITEMHEIGHT | - | int | RW | 列表项高度 |
| NCSP_LSTBOX_TOPITEM | - | int | RW | 第一个可见列表项索引 |
| NCSP_LSTBOX_HILIGHTEDITEM | - | int | RW | 高亮列表项索引 |


| *Property ID* | *mstudio name* | *Type* | *Authority* | *Explanation* |
| NCSP_LSTBOX_ITEMWIDTH | - | int | RO | Maximum width of the list item |
| NCSP_LSTBOX_ITEMCOUNT | - | int | RO | Total number of the list item |
| NCSP_LSTBOX_ITEMHEIGHT | - | int | RW | Height of the list item |
| NCSP_LSTBOX_TOPITEM | - | int | RW | The first visible list item index |
| NCSP_LSTBOX_HILIGHTEDITEM | - | int | RW | High light list item index |


### mListBox 事件
### Event of mListBox

继承自 <a href="#m_ItemView 事件">mItemView 事件</a>

It is inherited from <a href="#Event of mItemView">event of mItemView</a>

|* 事件通知码 *|* 说明 *|* 参数 *|
| NCSN_LSTBOX_CLICKED | 鼠标点击事件 |  |
| NCSN_LSTBOX_SELCHANGED | 选择条目已改变 | 新的选择条目句柄 |
| NCSN_LSTBOX_ENTER | Enter 键被按下 | - |
| NCSN_LSTBOX_SETFOCUS | 获取焦点 | - |
| NCSN_LSTBOX_KILLFOCUS | 失去焦点 | - |
| NCSN_LSTBOX_ERRSPACE | 空间不足 | - |
| NCSN_LSTBOX_DBCLK | 双击列表项 | - |
| NCSN_LSTBOX_SELCANCEL | 取消选择条目 | - |
| NCSN_LSTBOX_CLKCHKMARK | check mark 被点击 | - |


|* Event notification code *|* Explanation *|* Parameter *|
| NCSN_LSTBOX_CLICKED | Mouse clicking event |  |
| NCSN_LSTBOX_SELCHANGED | The selected item has changed | New selected item sentence handle |
| NCSN_LSTBOX_ENTER | Enter key is pressed down | - |
| NCSN_LSTBOX_SETFOCUS | Get focus | - |
| NCSN_LSTBOX_KILLFOCUS | Lose focus | - |
| NCSN_LSTBOX_ERRSPACE | Space is insufficient | - |
| NCSN_LSTBOX_DBCLK | Double click list item | - |
| NCSN_LSTBOX_SELCANCEL | Deselect the item | - |
| NCSN_LSTBOX_CLKCHKMARK | check mark is clicked | - |

### mListBox 方法
### Method of mListBox

继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

It is inherited from <a href="#Method of mItemView">the method of mItemView</a>

---++++ 将字符串加入列表框
---++++ Add the character string to the list box 

建立 listbox 控件之后，下一步是将字符串放入其中，这可以通过调用 addString 方法来完成，添加成功后该方法将返回列表项所在的索引值。字符串通常通过以0开始计数的索引数来引用，其中0对应于最顶上的条目。 

After establishing listbox control, the next step is placing the character string in it, which can be completed through calling addString method. After adding is successful, the method will return the index value of the list item. The character string is usually quoted through the index number counting from 0, and 0 corresponds to the top item.

```cplusplus
int addString(mListBox *self, const char* string, DWORD addData);
```

也可以使用 insertString 指定一个索引值，将字符串插入到列表框中的指定位置，但在 NCSS_LISTBOX_SORT 风格下，会根据排序结果插入到相应位置，将忽略索引值设置： 

insertString can be used to appoint an index value, and insert the character string to the specified position in the list box. But under NCSS_LISTBOX_SORT style, it will insert to the corresponding position according to the sorting result, and index value setting will be ignored.

```cplusplus
int insertString(mListBox *self, const char* string, DWORD addData, int index);
```

如：

For Example:

```cplusplus
%INCLUDE{"%ATTACHURL%/listbox" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```

如果添加的列表项除了包含字符串以外，还包含位图等信息，可通过 addItems 方法来完成。

If the added list item contains bit map etc. besides character string, it can be completed through addItems method.

```cplusplus
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

For Example:

```cplusplus
    int count = 3;
    mListItemInfo   lbii[count];

    lbii[0].string = "test list";
    lbii[0].flag = 0;
    lbii[0].image = 0;
    ... ...
    _c(listFile)->addItems(listFile, lbii, count);
```

---++++ 删除列表框条目
---++++ Remove List Box Item 

列表框控件通过 delString 或 removeItemByIdx 方法可以删除指定索引值的列表项或通过 removeItem 方法删除指定列表项；同时也可以通过 resetContent 清空列表框中的所有内容。函数原型如下：

List box control can remove the list item of specified index value through delString or removeItemByIdx method or the specified list item is removed through removeItem method; at the same time, all the content in the list box can be emptied through resetContent. Prototype of the function is as below: 

```cplusplus
BOOL delString(mListBox *self, int index);  
int removeItemByIdx(mListBox *self, int index);
```

如：

For Example:

```cplusplus
%INCLUDE{"%ATTACHURL%/listbox" pattern="^.*?// START_OF_DELITEMS(.*?)// END_OF_DELITEMS.*"}%
```


---++++ 选择和获取条目
---++++ Select and Get Item  

对于单项选择列表框和多项选择列表框在检索列表框条目的选中状态时需要使用不同的方法，下面先看单项选择列表框。选择条目除了通过鼠标和键盘操作外，还可以通过方法 setCurSel 来控制：

For single selection list box and multi selection list box, in the selected status of index list item, different methods need to be used, below let’s firstly look at the single selection list box. The selected item can control through setCurSel besides through mouse and keyboard operation.

```cplusplus
_c(listFile)->setCurSel(listFile, 1);
```

反之，可通过 getCurSel 来获取当前选定的索引项，如果没有选定项， 将返回 -1。

On the contrary, currently selected index item can be obtained through getCurSel, if there is no selected item, -1 will be returned.

```cplusplus
_c(listFile)->getCurSel(listFile);
```

另外也可以通过 _selectByIdx_ 或 _deselectByIdx_ 设置或取消选中状态。

In addition, selected status can be set or canceled through selectByIdx or deselectByIdx. 

```cplusplus
int selectByIdx(mListBox *self, int index);
int deselectByIdx(mListBox *self, int index);                          
```

对于多项选择列表框来说，通过 setCurSel 和 getCurSel 方法只能用来设置和获取当前高亮项，无法获得所有具有选中状态的条目。但我们可以使用 setSel 来设定某特定条目的选择状态，而不影响其他项，其中 flag的取值有三种含义：
- -1：时对指定列表项进行相反操作，即原状态未选中则选中它，否则取消选中状态。
- 0：取消对列表项的选中。
- 其它：选中列表项。

For multi selection list box, setCurSel and getCurSel method can only be used to set and get current high light item, and all the items with selected status cannot be obtained. However, we can use setSel to set selection status of specific item without influencing other items, and value of flag has three meanings:
- -1: carry out reversed operation to the specified list item, that is, if the original status is not selected, select it, otherwise cancel the selected status.
- 0: cancel selection to the list item.
- Others: select the list item.

方法原型：

Prototype of the method:

```cplusplus
int setSel(mListBox *self, int newSel, int flag);
```
使用示例如：

Example is as following:

```cplusplus
_c(listFile)->setSel(listFile, 0, 1);
```

反之，我们可以用 isSelected 方法确定某特定条目的选择状态：

On the contrary, we can use isSelected method to determine selection status of specific item:

```cplusplus
_c(listFile)->isSelected(listFile, 0);
```

另外对于多选列表框，可以通过 getSelectionCount 方法获取当前选中的条目个数，并通过 getSelection 获得所有被选中条目的索引值：

In addition, for multi selection list box, we can get the currently selected item number through getSelectionCount method, and get index values of all the selected items through getSelection method.

```cplusplus
HITEM* selItems;
int selCount = _c(listFile)->getSelectionCount(listFile);
if (selCount == 0)
return;

selItem = alloca (sizeof(HITEM)*selCount);
_c(listFile)->getSelection(listFile, selItem, selCount);
```

---++++ 查找含有字符串的条目
---++++ Find Items Containing Character String 

列表框通过 findString 方法提供了在指定范围内精确或模糊查找包含某一指定字符串的列表项的方法： 

The list box provides the method to accurately or vaguely find list item containing certain specified character string within the specified range through findString method:

```cplusplus
int findString(mListBox *self, int start, char* string, BOOL bExact);
```

下面的操作将从第3个列表项开始精确查找字符串为 test 的列表项。成功会返回查找到的列表项索引，否则返回 -1：

The following operation will start to accurately find the list item with character string as test from the third list item. If it is successful, the list item index found will be returned, otherwise -1 will be returned:

```cplusplus
_c(listFile)->findString(listFile, 2, "test", TRUE);
```

---++++ 设置和获取某条目的检查框的当前状态
---++++ Set and get current status of the check box of certain item 

```cplusplus
    _c(listFile)->getCheckMark(listFile, index);
```
返回由 index 指定索引处条目的检查框的状态。如果没有找到相应条目，将返回 -1。NCSF_LSTITEM_CMCHECKED 表示该条目的检查框处于选择状态。NCSF_LSTITEM_CMPARTCHECKED 表示该条目的检查框处于部分选择状态。NCSF_LSTITEM_CMBLANK 表示该条目的检查框处于未选择状态。 

Return the status of the check box of the item at the specified index. If corresponding item is not found, -1 will be returned. NCSF_LSTITEM_CMCHECKED represents that the check box of the item is in selected status. NCSF_LSTITEM_CMPARTCHECKED represents that the check box of the item is in partial selected status. NCSF_LSTITEM_CMBLANK represents that the check box of the item is in unselected status.

```cplusplus
    _c(listFile)->setCheckMark(listFile, index, (DWORD)status);
```

设置由 index 指定索引处条目的检查框的状态为 status 中指定的值。当没有找到 index 指定的条目时，返回 FALSE，成功返回 TRUE。 

Set the status of the check box of the item at the index specified by index as the value specified in status. When the item specified by index is not found, FALSE will be returned, if it is successful, TRUE will be returned.

---++++ 设置某列表框条目加粗显示状态
---++++ Set Certain List Box Item as Bold Display Status 

```cplusplus
    _c(listFile)->bold(listFile, index, TRUE);
```
该操作将指定索引项的内容进行加粗设置。

The operation will carry out bold setting to the content of the specified index item.

---++++ 设置或获取某列表框条目选择状态
---++++ Set or Get Selection Status of Certain List Box Item 

列表框通过 _isEnabled_ 方法确定某特定条目是否处于禁止选中状态：

The list box determines if a specific item is in forbid selected status through isEnabled method.
 
 %CODE{"cpp"}%
    _c(listFile)->isEnabled(listFile, 0);
```

通过 _enableByIdx_ 或 _enable_ 方法可以支持条目选中或禁止条目选中。

Item selected or forbid item selected can be supported through enableByIdx or enable method. 

 %CODE{"cpp"}%
    _c(listFile)->enableByIdx(listFile, 0, TRUE);
or
    _c(listFile)->enableByIdx(listFile, 0, FALSE);
```

---++++ 设置字符串比较函数
---++++ Set Character String Comparison Function

列表框控件通过 _setStrCmpFunc_ 方法来使用用户设置的排序方法排列列表项。

The list box control uses the sorting method set by the user to arrange the list items through setStrCmpFunc method.

```cplusplus
static int my_strcmp (const char* s1, const char* s2, size_t n)
{
        int i1 = atoi (s1);
        int i2 = atoi (s2);
        return (i1 – i2);
}
_c(listFile)->setStrCmpFunc(listFile, my_strcmp);
```

### mListBox 实例
### Instance of mListBox
<p align=center>
<img src="%ATTACHURLPATH%/listbox_demo.png" alt="listbox_demo.png"/><br>
图 p2c6-1  listbox 程序的输出

Figure p2c6-1 Output of listbox Program
</p>

<p align=center>清单 p2c14-3  listbox.c</p>
<p align=center>List p2c14-3 listbox.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/listbox"}%
```

## mIconView

- *控件窗口类*: NCSCTRL_ICONVIEW
- *控件英文名*: IconView
- *简介*: 将用户提供的一系列可选项以图标加标签文字的方式供其浏览，用户可通过键盘及鼠标操作来选中某一项或者多个项，选中的列表项通常高亮显示。标型控件的典型用法是作为桌面图标的容器和目录下文件的显示。 
- *示意图*:  

- *Control window class*: NCSCTRL_ICONVIEW
- *Control English name*: IconView
- *Brief introduction*: a series of options provided by the users is offered in the mode of icon plus label literal for browsing. Users can select certain item or multiple items through keyboard and mouse operation, and the selected item is usually high light displayed. The typical usage of icon control is as the display of the container of desktop icon and documents under the directory. 
- *Schematic diagram*:  
<img src="%ATTACHURLPATH%/iconview.png" alt="iconview.png"/>

### mIconView 风格
### Style of mIconView

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>
It is inherited from <a href="#Style of mItemView">the style of mItemView</a>

|* 风格名 * | *miniStudio属性名* | *说明* |
| NCSS_ICONV_LOOP | Loop | 条目可循环浏览 |
| NCSS_ICONV_SORT | AutoSort | 条目自动排序 |


| *Style name* | *mstudio property name* | *Explanation* |
| NCSS_ICONV_LOOP | Loop | Item circulative browsing |
| NCSS_ICONV_SORT | AutoSort | Item automatic sorting |

### mIconView 属性
### Property of mIconView

继承自 <a href="#m_ItemView 属性">mItemView 属性</a>

|* 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_ICONV_DEFICONHEIGHT | - | int |  RW | 列表项高度 |
| NCSP_ICONV_DEFICONWIDTH | - | int | RW | 列表项宽度 |


It is inherited from <a href="#Property of mItemView">the property of mItemView</a>

| *Property ID* | *mstudio name* | *Type* | *Authority* | *Explanation* |
| NCSP_ICONV_DEFICONHEIGHT | - | int |  RW | Height of the list item |
| NCSP_ICONV_DEFICONWIDTH | - | int | RW | Width of the list item |

### mIconView 方法
### Method of mIconView

继承自 <a href="#m_ItemView 方法">mItemView 方法</a>

It is inherited from <a href="#Method of ,mItemView">the method of ,mItemView</a>

iconview 控件通过 setIconSize 方法来初始化列表项的大小，并通过 addItem 方法根据列表项信息添加列表项。

Iconview control initializes the size of the list item through setIconSize method, and adds list item according to list item information through addItem method.

```cplusplus
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

Example codes of adding list item are:

```cplusplus
%INCLUDE{"%ATTACHURL%/iconview" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```

### mIconView 实例
### Instance of mIconView

<p align=center>
<img src="%ATTACHURLPATH%/iconview_demo.png" alt="iconview_demo.png"/><br>
图 p2c6-1  iconview 程序的输出

Figure p2c6-1 Output of iconview Program
</p>

<p align=center>清单 p2c14-3  iconview.c</p>
<p align=center>List p2c14-3 iconview.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/iconview"}%
```

## mListView

- *控件窗口类*: NCSCTRL_LISTVIEW
- *控件英文名*: ListView
- *简介*: 以列表的方式显示一系列的数据项（列表项），不同列表项的相同类型子项以列的方式组织，列表型控件的表头（header）内容通常反映了列表项不同子项的意义。列表型控件经常用来作为文件浏览框，它可以在一个区域内显示包括文件名、文件类型、大小和修改日期在内的诸多文件属性。 
- *示意图*: 

- *Control window class*: NCSCTRL_LISTVIEW
- *Control English name*: ListView
- *Brief introduction*:Display a series of data items (list items) in the list mode. Same type of child items of different list items are organized in the column mode, and content of the header of the list control usually reflect the meanings of different child items of the list item. List control is usually used as file browsing box, which can show many file properties including file name, file type, size and modification date in a region. 
- *Schematic diagram*: 
<img src="%ATTACHURLPATH%/listview.png" alt="listview.png"/>

### mListView 风格
### Style of mListView

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>

|* 风格名 * | *miniStudio属性名* | *说明* |
| NCSS_LISTV_NOTIFY | Notify | 通知事件支持 |
| NCSS_LISTV_LOOP | Loop | 循环浏览支持 |
| NCSS_LISTV_MULTIPLE | Multi->TRUE | 多选支持 |
| NCSS_LISTV_SINGLE |  | Multi->FALSE | 单选支持 |
| NCSS_LISTV_CHECKBOX | CheckBox | 列表项包含 checkbox |
| NCSS_LISTV_AUTOCHECK | AutoCheck | 列表项中的 checkbox 支持自动选择 |
| NCSS_LISTV_AUTOCHECKBOX | - | 同时包含 NCSS_LSTBOX_CHECKBOX 和 NCSS_LSTBOX_AUTOCHECK 2种风格 |
| NCSS_LISTV_TREE | Tree | 支持树状列表 |
| NCSS_LISTV_WITHICON | WithIcon |  |
| NCSS_LISTV_SORT | Sort | 排序支持 |

It is inherited from <a href="#Style of mItemView">the style of mItemView</a>

| *Style name* | *mstudio property name* | *Explanation* |
| NCSS_LISTV_NOTIFY | Notify | Notification event supported |
| NCSS_LISTV_LOOP | Loop | Circulative browsing supported |
| NCSS_LISTV_MULTIPLE | Multi->TRUE | Multiple selection supported |
| NCSS_LISTV_SINGLE |  | Multi->FALSE | Single selection supported |
| NCSS_LISTV_CHECKBOX | CheckBox | The list item contains checkbox|
| NCSS_LISTV_AUTOCHECK | AutoCheck | checkbox in the list item supports automatic selection |
| NCSS_LISTV_AUTOCHECKBOX | - | Contain NCSS_LSTBOX_CHECKBOX and NCSS_LSTBOX_AUTOCHECK styles simultaneously. |
| NCSS_LISTV_TREE | Tree | Support tree list |
| NCSS_LISTV_WITHICON | WithIcon |  |
| NCSS_LISTV_SORT | Sort | Sorting supported |

### mListView 属性
### Property of mListView

继承自[mItemView的属性](MStudioMGNCSV1dot0PGP2C3#mItemView)

|* 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_LISTV_DEFITEMHEIGHT | - | int | RW | 列表项默认高度 |
| NCSP_LISTV_ROWCOUNT | - | RO | int | 列表项行数 |
| NCSP_LISTV_HDRHEIGHT | HeadHeight | int | RW | 列表头高度 |
| NCSP_LISTV_HDRWIDTH | HeadWidth | int | RW | 列表头总宽度 |
| NCSP_LISTV_HDRVISIBLE | - | BOOL | RW | 列表头是否可见 |
| NCSP_LISTV_SORTCOLUMN | - | int | RW | 排序列索引 |
| NCSP_LISTV_GRIDLINEWIDTH | GridLineWidth | int | RW | 网格宽度 |
| NCSP_LISTV_GRIDLINECOLOR | GridLineColor | int | RW | 网格颜色 |
| NCSP_LISTV_COLCOUNT | - | int | RO | 列表项列数 |

It is inherited from [the property of mItemView](MStudioMGNCSV1dot0PGP2C3#mItemView)

| *Property ID* | *mstudio name* | *Type* | *Authority* | *Explanation* |
| NCSP_LISTV_DEFITEMHEIGHT | - | int | RW | Default height of the list item |
| NCSP_LISTV_ROWCOUNT | - | RO | int | Row number of the list item |
| NCSP_LISTV_HDRHEIGHT | HeadHeight | int | RW | height of the list header |
| NCSP_LISTV_HDRWIDTH | HeadWidth | int | RW | Total width of the list header |
| NCSP_LISTV_HDRVISIBLE | - | BOOL | RW | If the list header is visible |
| NCSP_LISTV_SORTCOLUMN | - | int | RW | Index of the sorted columns |
| NCSP_LISTV_GRIDLINEWIDTH | GridLineWidth | int | RW | Grid width |
| NCSP_LISTV_GRIDLINECOLOR | GridLineColor | int | RW | Grid color |
| NCSP_LISTV_COLCOUNT | - | int | RO | Column number of the list item |


### mListView 事件
### Event of mListView    
    /** Double click in item. */
    NCSN_LISTV_ITEMDBCLK,
    /** Fold item.  */
    ,
    /** Unfold item.  */
    NCSN_LISTV_UNFOLDITEM,



继承自 <a href="#m_ItemView 事件">mItemView 事件</a>

|* 事件通知码 *|* 说明 *|* 参数 *|
| NCSN_LISTV_CLICKED | 鼠标点击事件 |  |
| NCSN_LISTV_SELCHANGED | 选择条目已改变 | 新的选择项句柄 |
| NCSN_LISTV_ITEMRDOWN | 鼠标右键在列表项上按下 | 被点击的行索引 |
| NCSN_LISTV_ITEMRUP | 鼠标右键在列表项上弹起 | 被点击的行索引 |
| NCSN_LISTV_HDRRDOWN | 鼠标右键在表头上按下 | 被点击的列索引 |
| NCSN_LISTV_HDRRUP | 鼠标右键在列表项上弹起 | 被点击的列索引 |
| NCSN_LISTV_ITEMDBCLK | 双击列表项 | - |
| NCSN_LISTV_FOLDITEM | 树列表项折叠子节点 | 被点击的列表项句柄 |
| NCSN_LISTV_UNFOLDITEM | 树列表项打开子节点 | 被点击的列表项句柄 |

It is inherited from <a href="#Event of mItemView">the event of mItemView</a>

|* Event notification code *|* Explanation *|* Parameter *|
| NCSN_LISTV_CLICKED | Mouse clicking event |  |
| NCSN_LISTV_SELCHANGED | The selected item has changed | New selection item sentence handle |
| NCSN_LISTV_ITEMRDOWN | The mouse right key presses down on the list item | Indexed by the clicked row |
| NCSN_LISTV_ITEMRUP | The mouse right key pops up on the list item | Indexed by the clicked row |
| NCSN_LISTV_HDRRDOWN | The mouse right key presses down on the header | Indexed by the clicked column |
| NCSN_LISTV_HDRRUP | The mouse right key pops up on the list item | Indexed by the clicked column |
| NCSN_LISTV_ITEMDBCLK | Double click the list item | - |
| NCSN_LISTV_FOLDITEM | The tree list item folds the child node | Clicked list item sentence handle |
| NCSN_LISTV_UNFOLDITEM | The tree list item opens the child node | Clicked list item sentence handle |

### mListView 方法
### Method of mListView

继承自 <a href="#m_ItemView 风格">mItemView 风格</a>
It is inherited from  <a href="#Style of mItemView">the style of mItemView</a>

---++++ 列操作
---++++ Column Operation

在向该控件中添加列表项前，首先需要通过 addColumn 方法添加列：

before adding list item to the control, it is necessary to firstly add column through addColumn method:

```cplusplus
%INCLUDE{"%ATTACHURL%/listview" pattern="^.*?// START_OF_ADDCLMS(.*?)// END_OF_ADDCLMS.*"}%
```

其中 lstv_clminfo 是一个 NCS_LISTV_CLMINFO 结构，它包含了列表型控件的列信息。在添加列后，若需要设置或获取列的相关信息时，可通过如下方法来完成：

lstv_clminfo is a NCS_LISTV_CLMINFO structure, which contains the column information of the list control. After adding column, if it is necessary to set or get information related to column, it can be completed through the following method:

```cplusplus
void setColumnWidth(mListView *self, int index, int width); 
BOOL setHeadText(mListView *self, int col, const char* text);

mListColumn* getColumn(mListView *self, int index);         
int getColumnIndex(mListView *self, mListColumn *column);   
int getColumnWidth(mListView *self, int index);
int getColumnCount(mListView *self);                     
void showColumn(mListView *self, mListColumn *column);      
```

此外，删除指定列可通过 delColumn 方法实现：

In addition, deleting specified column can be realized through delColumn:

```cplusplus
BOOL delColumn(mListView *self, int index);
```

---++++ 列表项操作
---++++ List Item Operation

列表型控件由许多纵向排列的列表项组成，每个列表项由列分为多个子项，列表项可以包含特定的应用程序定义的附加数据。应用程序可以通过相应的方法来添加、修改和设置、删除列表项或获取列表项的属性信息。 

List control is composed of many vertically arranged list items, and each list item is divided into many child items by the column. List item can contain additional data defined by specific applications. Applications can add, modify, set and remove list item or get property information of the list item through corresponding method.

控件创建并添加列后，还没有列表项，此时需要通过 _addItem_ 向其添加列表项：

After the control creates and adds column, there is no list item, and now it is necessary to add list item to it through addItem:

```cplusplus
%INCLUDE{"%ATTACHURL%/listview" pattern="^.*?// START_OF_ADDITEMS(.*?)// END_OF_ADDITEMS.*"}%
```

每个列表项包括一个或多个子项，子项的数目和列表型控件的列数相同。一个子项中包括字符串和图像，可以使用下列方法来获取和设置子项的信息：

Each list item includes one or multiple child item, and number of the child items is the same as the column number of the list control. A child item includes character string and image, and the following method can be used to get and set the information of child item:

```cplusplus
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

---++++ 查找列表项
---++++ Find List Item 

findItem 用于在列表型控件中查找一个特定的列表项。如果查找成功的话，返回列表项句柄。

findItem is used to find a specific list item in the list control. If the finding is successful, list item sentence handle is returned.

```cplusplus
HITEM findItem(mListView *self, NCS_LISTV_FINDINFO *info);
```

---++++ 比较和排序
---++++ Comparison and Sorting 

除了继承自基类的排序功能支持外，该控件还可以指定某一列作为其排序的依照列，同时还可以设定排序类型是升序还是降序，或无序（不排列）。

Besides the sorting function inherited from the basic class is supported, the control can appoint certain column as the accordance column of the sorting, and at the same time, it can set the sorting type as ascending, descending, or unsorted (not arranged).

```cplusplus
void sort(mListView *self, NCS_CB_LISTV_CMPCLM func, int col, ncsLstClmSortType sort);
void setSortDirection(mListView *self, ncsLstClmSortType direction);  
ncsLstClmSortType getSortDirection(mListView *self);
mListColumn* getSortColumn(mListView *self);                
void setSortColumn(mListView *self, mListColumn* column);   
```

---++++ 回调方法
---++++ Callback Method

对列表头的绘制包括了背景色和内容绘制2部分，控件对此提供了回调方法供上层应用处理表头的绘制。方法：

Drawing of the list header includes drawing of background color and content, and control provides callback method for the upper layer application to process drawing of header. Method:

```cplusplus
void setCustomDrawHeader(mListView *self, NCS_CB_LISTV_CSTMHDROPS *func);
```

---++++ 树型节点的操作
---++++ ---++++ 树型节点的操作 

树型节点的操作包括获取相关节点和折叠一个节点。 相关方法有：

Operation of tree node includes getting related nodes and folding a node, and the related method is:

```cplusplus
HITEM getRelatedItem(mListView *self,HITEM hItem,ncsListVIRType type);
HITEM getChildItem(mListView *self, HITEM parent, int index);
int getChildCount(mListView *self, HITEM hItem);
int foldItem(mListView *self, HITEM hItem, BOOL fold);
```

- getRelatedItem 用于获取一个节点的相关树型节点，如父节点，兄弟节点或第一个子节点。ncsListVIRType 指定相关节点和目标节点的关系，包括： 
   - NCSID_LISTV_IR_PARENT：父节点
   - NCSID_LISTV_IR_FIRSTCHILD：第一个子节点
   - NCSID_LISTV_IR_LASTCHILD：最后一个节点
   - NCSID_LISTV_IR_NEXTSIBLING：下一个兄弟节点
   - NCSID_LISTV_IR_PREVSIBLING：上一个兄弟节点
- foldItem 用来折叠或者展开一个包含子节点的节点项。 
- getChildItem：用于获取指定父节点下的子节点。
- getChildCount：用于获取指定节点的子节点数目。


- getRelatedItem is used to get the related tree nodes of a node, such as parent node, brother node or the first child node.  ncsListVIRType appoints the relations between the related nodes and the objective nodes, including:
   - NCSID_LISTV_IR_PARENT：parent node
   - NCSID_LISTV_IR_FIRSTCHILD：first child node
   - NCSID_LISTV_IR_LASTCHILD：last node
   - NCSID_LISTV_IR_NEXTSIBLING：next brother node
   - NCSID_LISTV_IR_PREVSIBLING：previous brother node
- foldItem is used to fold or unfold a node item containing child node. 
- getChildItem: used to get the child nodes under the specified parent node.
- getChildCount: used to get the number of the child nodes of the specified node.

### mListView 实例
### Instance of mListView

<p align=center>
<img src="%ATTACHURLPATH%/listview_demo.png" alt="listview_demo.png"/><br>
图 p2c6-1  listview 程序的输出

Figure p2c6-1 Output of listview Program
</p>

<p align=center>清单 p2c14-4  listview.c</p>
<p align=center>List p2c14-4 listview.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/listview"}%
```

[Next](MStudioMGNCSV1dot0PGP2C13][Previous]] < [[MStudioMGNCSV1dot0PG][Index]] > [[MStudioMGNCSV1dot0PGP2C15)




-- Main.XiaodongLi - 22 Feb 2010

