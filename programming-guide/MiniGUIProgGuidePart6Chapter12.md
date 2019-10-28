# 30 Scroll View Control

Scroll View (ScrollView) control is also a scroll window control, and different from ScrollWnd control in that ScrollView control displays list items instead of controls.

The major usage of ScrollView is to display and handle list items; this aspect is similar to list box and list view control. However the height of a list item in ScrollView can be specified by the user, so different list item can have different height. The most important is, draw of list items in ScrollView is completely determined by application. Totally speaking, ScrollView is a control easy to be customized, and give great free for applications, using ScrollView can perform much work that list box and list view control cannot do.

## 30.1 Styles of Scroll View Control

A ScrollView control with SVS_AUTOSORT style will automatically sort the list items; the precondition is that you have already set the item comparison function of the ScrollView control by using SVM_SETITEMCMP message:

```cplusplus
SVM_SETITEMCMP myItemCmp;
SendMessage (hScrWnd, SVM_SETITEMCMP, 0, (LPARAM)myItemCmp);
```

Here, myItemCmp is the item comparison function specified by an application.

List item comparison function of ScrollView control has the prototype of VM_SETITEMCMP, which is defined as follows:

```cplusplus
typedef int (*SVITEM_CMP) (HSVITEM hsvi1, HSVITEM hsvi2);
```

Here, hsvi1 and hsvi2 are the handles of the two list items to be compared. If the comparison function returns a negative value, the list item hsvi1 will be displayed before the list item hsvi2.

In addition, you can also use SVM_SORTITEMS message to sort list items in a ScrollView control without SVS_AUTOSORT style:

```cplusplus
SVM_SETITEMCMP myItemCmp;
SendMessage (hScrWnd, SVM_SORTITEMS, 0, (LPARAM)myItemCmp);
```

Here, myItemCmp is the item comparison function used for sorting which is specified by an application.

## 30.2 Messages of Scroll View Control

Except responds to some general scroll window message as ScrollWnd, related messages of ScrollView control are mainly used to add, delete, and access list item.

### 30.2.1 Draw of List Item

Draw of list items in a ScrollView control is totally determined your application itself, so you must specify the content draw method of list item first before adding any list item. SVM_SETITEMDRAW message is used to set the draw function for list items:

```cplusplus
SVITEM_DRAWFUNC myDrawItem;
SendMessage (hScrWnd, SVM_SETITEMDRAW, 0, (LPARAM)myDrawItem);
```

Content draw function of a list item has the prototype of SVITEM_DRAWFUNC, which is defined as follows:

```cplusplus
typedef void (*SVITEM_DRAWFUNC) (HWND hWnd, HSVITEM hsvi, HDC hdc, RECT *rcDraw);
```

The arguments passed to the draw function are the handle to the ScrollView control (hWnd), the handle of list item to be drawn (hsvi), the graphics device context (hdc), and the rectangle area in which the item be drawn (rcDraw).

According to the actual usage of ScrollView control, content draw function can draw user-defined content, which can be text or picture, all decided by an application itself, in the specified rectangle area.

### 30.2.2 Set Operation Functions of List Item

SVM_SETITEMOPS message can be used to set some callback function related to list item operations, including initializing, drawing and destroying:

```cplusplus
SVITEMOPS myops;
SendMessage (hScrWnd, SVM_SETITEMOPS, 0, (LPARAM)&myops);
```

Here, myops is a structure of SVITEMOPS type, and specifies the related operation functions for list items of ScrollView, as follows:

```cplusplus
typedef struct _svitem_operations
{
    SVITEM_INITFUNC     initItem;     /** called when an ScrollView item is created */
    SVITEM_DESTROYFUNC  destroyItem;  /** called when an item is destroied */
    SVITEM_DRAWFUNC     drawItem;     /** call this to draw an item */
} SVITEMOPS;
```

The member initItem is the initialization function, which is called during creating list items, and its prototype is defined as follows: 

```cplusplus
typedef int  (*SVITEM_INITFUNC)    (HWND hWnd, HSVITEM hsvi);
```

The arguments are the handle to the control window (hWnd), and the handle to the created list item (hsvi). This function can be used to perform some operations relevant to the items during creating them.

The member destroyItem is the destroying function called during destroying the list items; its prototype is defined as follows: 

```cplusplus
typedef void (*SVITEM_DESTROYFUNC) (HWND hWnd, HSVITEM hsvi);
```

The arguments are the handle to the control window (hWnd), and the handle to the list item being destroyed. This function can be used to perform some cleaning up work during destroying them, such as release related resource.

The member drawItem specifies the draw function of the list items. Its effect is completely the same as using SVM_SETITEMDRAW message to set the draw function. 

### 30.2.3 Operations on List Item 

SVM_ADDITEM and SVM_DELITEM messages are used to add and delete a list item respectively:

```cplusplus
int idx;
HSVITEM hsvi;
SVITEMINFO svii;
Idx = SendMessage (hScrWnd, SVM_ADDITEM, (WPARAM)&hsvi, (LPARAM)&svii);
```

Here, svii is a structure of SVITEMINFO type, defined as follows: 

```cplusplus
typedef struct _SCROLLVIEWITEMINFO
{
    int        nItem;           /** index of item */
    int        nItemHeight;     /** height of an item */
    DWORD      addData;         /** item additional data */
} SVITEMINFO;
```

The field nItem is the desired index of the list item; if nItem is negative, the list item will be appended to the end. The field nItemHeight is the height of the list item; addData is the additional data value of the list item.

Hsvi is used to store the handle to a list item, and this handle can be used to access the list item. SVM_ADDITEM message returns the actual index value of the list item after inserted.

SVM_DELITEM message is used to delete a list item:

```cplusplus
int idx;
HSVITEM hsvi;
SendMessage (hScrWnd, SVM_DELITEM, idx, hsvi);
```

Here, hsvi is used to specify the handle of the list item to be deleted. If hsvi is 0, you should specify the index value of the list item to be deleted through idx.

SVM_REFRESHITEM message is used to refresh the area of a list item: 

```cplusplus
int idx;
HSVITEM hsvi;
SendMessage (hScrWnd, SVM_REFRESHITEM, idx, hsvi);
```

Here, hsvi is uesed to specify the handle of the list item to be refreshed. If hsvi is 0, you should specify the index value of the list item to be refreshed through idx.

SVM_GETITEMADDDATA message is used to get the additional data of a list item:

```cplusplus
SendMessage (hScrWnd, SVM_GETITEMADDDATA, idx, hsvi);
```

Here, hsvi is used to specify the handle of the list item to be accessed. If hsvi is 0, you should specify the index value of the list item to be accessed through idx.

SVM_SETITEMADDDATA message is used to set the additional data of a list item:

```cplusplus
int idx;
DWORD addData;
SendMessage (hScrWnd, SVM_SETITEMADDDATA, idx, addData);
```

Here, idx is used to specify the index value of the list item to be accessed, and addData is the additional data to be set.

SVM_GETITEMCOUNT message is used to get the number of all list items:

```cplusplus
int count = SendMessage (hScrWnd, SVM_GETITEMCOUNT, 0, 0);
```

SVM_RESETCONTENT message is used to delete all the list items in the control:

```cplusplus
SendMessage (hScrWnd, SVM_RESETCONTENT, 0, 0);
```

### 30.2.4 Get/Set Current Highlighted Item

ScrollView control has highlight property, that is to say, only one list item in list items is the current highlighted list item. An application can set and get the current highlighted list item.

It should be noted that highlight is only a property of ScrollView control. Being the current highlighted item does not mean the list item must have some specialty in appearance (such as highlighted display), and this is completely determined by the application itself.

SVM_SETCURSEL message is used to set the highlighted list item of a ScrollView control:

```cplusplus
SendMessage (hScrWnd, SVM_SETCURSEL, idx, bVisible);
```

Here, idx is used to specify the index value of the list item to be set as the highlighted item, and if bVisible is TRUE, the list item becomes a visible item.

SVM_GETCURSEL message is used to get the current highlighted list item of a ScrollView control:

```cplusplus
int hilighted_idx = SendMessage (hScrWnd, SVM_GETCURSEL, 0, 0);
```

The return value of SVM_GETCURSEL message is the index value of current highlighted list item. 

### 30.2.5 Selection and Display of List Item

Besides highlight property, ScrollView also has selection property. The highlight is unique, but selection is not unique, in other words, there may be multiple list items of ScrollView control to be selected. An application can set the selection state of list items.

Like highlight property, we should be noted that selection is only a state of a list item. Being selected does not mean the list item must have some specialty in appearance (such as highlight display), this is also completely determined by the application itself.

SVM_SELECTITEM message is used to select a list item:

```cplusplus
SendMessage (hScrWnd, SVM_SELECTITEM, idx, bSel);
```

Here, idx is used to specify the index value of the list item to be operated, and if bSel is TRUE, the list item will be selected; otherwise will not be selected.

SVM_SHOWITEM message is used to make sure a list item is visible:

```cplusplus
SendMessage (hScrWnd, SVM_SHOWITEM, idx, hsvi);
```

Here, hsvi is used to specify the handle of list item to be displayed, while idx is used to specify the index value of the list item to be displayed, and idx only works when hsvi is 0.

SVM_CHOOSEITEM message is combination of SVM_SELECTITEM and SVM_SHOWITEM messages, and is used to select a list item and make

```cplusplus
SendMessage (hScrWnd, SVM_CHOOSEITEM, idx, hsvi);
```

Here, hsvi is the handle of list item to be selected and displayed, and idx is used to specify the index value of the list item to be selected and displayed, and idx only works when hsvi is 0.

### 30.2.6 Optimization of Display

When using SVM_ADDITEM message or SVM_DELITEM message to add or delete many list items in one time, you can use MSG_FREEZE to perform certain optimization. The usage is to freeze a control before operating, and de-freeze the control after operating. 

When parameter wParam of MSG_FREEZE message is TRUE, the control is frozen, otherwise de-frozen.

### 30.2.7 Set Range of Visible Area

A window of a ScrollView control not only contains a visible area, but also a margin area, as shown in Fig. 30.1.

<center>
<img src="%ATTACHURLPATH%/30.1_T.jpeg" alt="30.1_T.jpeg"  ALIGN="CENTER" /> <br>
Fig. 30.1 Visible area of a ScrollView control
</center>

SVM_SETMARGINS message can be used to set the margin range of a ScrollView control:

```cplusplus
RECT rcMargin;
SendMessage (hScrWnd, SVM_SETMARGINS, 0, (LPARAM)&rcMargin);
```

The left, top, right, and bottom field of rcMargin are the size of left, top, right, and bottom margin respectively to be set, if some a margin value is negative, the corresponding set will not work.

SVM_GETMARGINS message can get the margin range of a ScrollView control:

```cplusplus
RECT rcMargin;
SendMessage (hScrWnd, SVM_GETMARGINS, 0, (LPARAM)&rcMargin);
```

SVM_GETLEFTMARGIN, SVM_GETTOPMARGIN, SVM_GETRIGHTMARGIN, and SVM_GETBOTTOMMARGIN messages are used to getting left, top, right, bottom margin value respectively. 

## 30.3 Notification Codes of Scroll View Control

A ScrollView control will generate notification codes when responding to the operation such as the user clicks and some state changing happen, and the notification codes include:
- SVN_SELCHANGED: Currently highlighted list item changes.
- SVN_CLICKED: The user clicks a list item.
- SVN_SELCHANGING: Currently highlighted list item is changing.

An application should use SetNotificationCallback function to register a notification callback function, and handling on each received notification code in the function.

When you handle SVN_CLICKED and SVN_SELCHANGE in the notification callback function, the additional data passed in is the handle of the list item clicked or currently highlighted.

For SVN_SELCHANGING, the additional data passed in is the handle of the list item clicked or currently highlighted.

## 30.4 Sample Program

Code in List 30.1 illustrates the use of ScrollView control. The program constructs a simple contact person list by using ScrollView control. Please refer to scrollview.c program in the sample program package for the complete source code of the program.

<center>List 30.1 Example program of ScrollView control</center>

```cplusplus
#define IDC_SCROLLVIEW    100
#define IDC_BT          200
#define IDC_BT2         300
#define IDC_BT3         400
#define IDC_BT4         500

static HWND hScrollView;

static const char *people[] =
{
    "Peter Wang",
    "Michael Li",
    "Eric Liang",
    "Hellen Zhang",
    "Tomas Zhao",
    "William Sun",
    "Alex Zhang"
};

static void myDrawItem (HWND hWnd, HSVITEM hsvi, HDC hdc, RECT *rcDraw)
{
    const char *name = (const char*)ScrollView_get_item_adddata (hsvi);

    SetBkMode (hdc, BM_TRANSPARENT);
    SetTextColor (hdc, PIXEL_black);

    if (ScrollView_is_item_hilight(hWnd, hsvi)) {
        SetBrushColor (hdc, PIXEL_blue);
        FillBox (hdc, rcDraw->left+1, rcDraw->top+1, RECTWP(rcDraw)-2, RECTHP(rcDraw)-1);
        SetBkColor (hdc, PIXEL_blue);
        SetTextColor (hdc, PIXEL_lightwhite);
    }

    Rectangle (hdc, rcDraw->left, rcDraw->top, rcDraw->right - 1, rcDraw->bottom);
    TextOut (hdc, rcDraw->left + 3, rcDraw->top + 2, name);
}

static int myCmpItem (HSVITEM hsvi1, HSVITEM hsvi2)
{
    const char *name1 = (const char*)ScrollView_get_item_adddata (hsvi1);
    const char *name2 = (const char*)ScrollView_get_item_adddata (hsvi2);

    return strcmp (name1, name2);
}

static int
BookProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {

    case MSG_INITDIALOG:
    {
        SVITEMINFO svii;
        static int i = 0;

        hScrollView = GetDlgItem (hDlg, IDC_SCROLLVIEW);
        SetWindowBkColor (hScrollView, PIXEL_lightwhite);

        SendMessage (hScrollView, SVM_SETITEMCMP, 0, (LPARAM)myCmpItem);
        SendMessage (hScrollView, SVM_SETITEMDRAW, 0, (LPARAM)myDrawItem);

        for (i = 0; i < TABLESIZE(people); i++) {
            svii.nItemHeight = 32;
            svii.addData = (DWORD)people[i];
            svii.nItem = i;
            SendMessage (hScrollView, SVM_ADDITEM, 0, (LPARAM)&svii);
        }
        break;
    }

    case MSG_COMMAND:
    {
        int id = LOWORD (wParam);
        int code = HIWORD (wParam);

        switch (id) {
        case IDC_SCROLLVIEW:
            if (code == SVN_CLICKED) {
                int sel;
                sel = SendMessage (hScrollView, SVM_GETCURSEL, 0, 0);
                InvalidateRect (hScrollView, NULL, TRUE);
            }
            break;

        }
        break;
    }

    case MSG_CLOSE:
    {
        EndDialog (hDlg, 0);
        return 0;
    }

    }

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

static CTRLDATA CtrlBook[] =
{
    {
        "ScrollView",
        WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
                SVS_AUTOSORT,
         10, 10, 320, 150,
        IDC_SCROLLVIEW,
        "",
        0
    },
};

static DLGTEMPLATE DlgBook =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 350, 200,
    "My Friends",
    0, 0,
    TABLESIZE(CtrlBook), NULL,
    0
};
```

This program displays the contact person in list form, and sorts them by their names.

<center>
<img src="%ATTACHURLPATH%/30.2.jpeg" alt="30.2.jpeg"  ALIGN="CENTER" /> <br>
Fig. 30.2 Contact person list
</center>

-- Main.XiaodongLi - 26 Oct 2009

