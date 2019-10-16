# 21 List Box Control

A list box generally provides a series of options, which are shown in a scroll window. The user can select one or more items with the keyboard or mouse operation. The selected items are usually highlighted. The most typical use of list box is the open file dialog box, as shown in Fig. 21.1.

<center>
<img src="%ATTACHURLPATH%/21.1.jpeg" alt="21.1.jpeg"  ALIGN="CENTER" /> <br>
Fig. 21.1 Typical use of list box: “Open File” dialog box
</center>

We can create a list box control by calling CreateWindow function with CTRL_LISTBOX as the control class name.

## 21.1 Types and Styles of List Box

List box controls of MiniGUI can be divided into three types: single-selection list box, multiple-selection list box and bitmap list box. A list box is single-selection style by default; namely, the user can only select one item. To create a multiple-selection list box, you should use LBS_MULTIPLESEL style. When using this style, the user can select an item by clicking this item, and cancel the selection by clicking it again. When the list box has the input focus, you can also use the space key to select or cancel selection of an item. The effect of running a multiple-selection list box is as shown in Fig. 21.2.

<center>
<img src="%ATTACHURLPATH%/21.2.jpeg" alt="21.2.jpeg"  ALIGN="CENTER" /> <br>
Fig. 21.2 Multiple-selection list box
</center>

Besides the two list box types described above, MiniGUI also provides an advanced list box type. In this type of list box, the list item can be not only text string, but also attached by a bitmap or an icon. With such a list box, we can also display a check box besides the list item to represent checked or uncheck status. To create such an advanced list box, LBS_USEICON or LBS_CHECKBOX style should be specified. Fig 21.3 shows the running effect of the advanced list box. If you want the selection state auto-switched when the user clicks the check box, you can use LBS_AUTOCHECK style. The advanced list box can also have LBS_MULTIPLESEL style.

<center>
<img src="%ATTACHURLPATH%/21.3.jpeg" alt="21.3.jpeg"  ALIGN="CENTER" /> <br>
Fig. 21.3 Advanced list box control
</center>

Except the styles described above to distinguish the type of list box, you can also specify other general styles when creating a list box.

By default, the message handler of a list box only shows the list items, with no border around them. You can add border by using the window style WS_BORDE. In addition, you can also add a vertical scroll bar with window style WS_VSCROLL to scroll the list items by the mouse and add a horizontal scroll bar with window style WS_HSCROLL.

The default list box styles does not generate notification message when the user select a list item, so the program must send a message to the list box to get the selection state of item. Therefore, a list box control generally includes LBS_NOTIFY style, which can feed back some state information in time to the application during the user’s operation.

In addition, if you want the list box control sort the list items, you can use another commonly used style LBS_SORT.

Generally, the most commonly used style combination for creating list box is as follows:


```cplusplus
(LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)
```

## 21.2 Messages of List Box
### 21.2.1 Adding Item into List Box

After a list box is created, the next step is to add text strings to it. You can realize this by sending messages to the window message handler of the list box by calling SendMessage. The items in a list box can be referred to by an index value; the top-most item has index value of zero. In the following example, hwndList is the handle of the list box control, and index is the index value. When SendMessage is used to pass the text string, lParam is the pointer to the NULL-terminated string. 

When the stored content of the list box exceeds the available memory space, SendMessage returns LB_ERRSPACE. If error is caused by other reasons, SendMessage returns LB_ERR. If the operation is successful, SendMessage returns LB_OKAY. We can determine above two errors by testing the non-zero value of SendMessage.

If you adopt LBS_SORT style, or just want to append the new text string as the last item of a list box, the simplest approach to append string into the list box is using LB_ADDSTRING message:

```cplusplus
SendMessage (hwndList, LB_ADDSTRING, 0, (LPARAM)string) ;
```

We can also use LB_INSERTSTRING to specify an index, and insert a text string to the specified position of the list box.

```cplusplus
SendMessage (hwndList, LB_INSERTSTRING, index, (LPARAM)string) ;
```

For example, if index value is 4, string would be a text string with index 4: the fifth string counting from the beginning (due to zero-based), and all the text strings after this position will move backward. When the index is -1, the string will append to the last position. We can also use LB_INSERTSTRING for a list box with LBS_SORT style, but at this time the list box will ignore the index, and insert the new item according to the sorted result.

It should be noted that, after specifying LBS_CHECKBOX or LBS_USEICON style, when you add an item to a list box, you must use LISTBOXITEMINFO structure, and cannot use the string address directly, for example:


```cplusplus
HICON hIcon1;           /* Declare an icon handle */
LISTBOXITEMINFO lbii;  /* Declare a structure variable of the list box item*/

hIcon1 = LoadIconFromFile (HDC_SCREEN, "res/audio.ico", 1);  /* Load an icon */

/* Set the structure information, and add an item */
lbii.hIcon = hIcon1;
lbii.cmFlag = CMFLAG_CHECKED;
lbii.string = "abcdefg";
SendMessage (hChildWnd3, LB_ADDSTRING, 0, (LPARAM)&lbii);
```

Here, the value of cmFlag can be CMFLAG_CHECKED, CMFLAG_BLANK, or CMFLAG_PARTCHECKED, indicating checked, unchecked, and partly checked, respectively.

We can also display bitmaps in an advanced list box, rather than icons by default. If you want a list box item display a bitmap instead of an icon, you can include IMGFLAG_BITMAP in the flag, and specify the pointer to the bitmap object:


```cplusplus
/* Set structure information, and add an item */
lbii.hIcon = (DWORD) GetSystemBitmap (SYSBMP_MAXIMIZE);
lbii.cmFlag = CMFLAG_CHECKED | IMGFLAG_BITMAP;
lbii.string = "abcdefg";
SendMessage (hChildWnd3, LB_ADDSTRING, 0, (LPARAM)&lbii);
```

### 21.2.2 Deleting Item from List Box

Send LB_DELETESTRING message and specify the index value, and then you can delete an item with the index from the list box:

```cplusplus
SendMessage (hwndList, LB_DELETESTRING, index, 0) ;
```

We can even use LB_RESETCONTENT message to clear all contents in the list box:

```cplusplus
SendMessage (hwndList, LB_RESETCONTENT, 0, 0) ;
```

### 21.2.3 Selecting and Getting Item

Send LB_GETCOUNT to get the number of items in the list box:

```cplusplus
count = SendMessage (hwndList, LB_GETCOUNT, 0, 0) ;
```

When you need to get the text string of a certain item, you can send LB_GETTEXTLEN message to get the length of the string of the specified item in a list box:

```cplusplus
length = SendMessage (hwndList, LB_GETTEXTLEN, index, 0) ;
```

And then, copy the item to a text buffer by sending the message MSG_GETTEXT:

```cplusplus
length = SendMessage (hwndList, LB_GETTEXT, index, (LPARAM)buffer) ;
```

In these two conditions, the length value returned by above messages is the length of the text. For the length of a NULL-terminate string, the buffer must be big enough. You can use the string length returned by LB_GETTEXTLEN message to allocate some local memory for storing the string.

If we need to set the string of list item, you can send LB_SETTEXT message:

```cplusplus
SendMessage (hwndList, LB_SETTEXT, index, buffer) ;
```

For an advanced list box, we must use LB_GETITEMDATA and LB_SETITEMDATA to get other information of a list item, such as the bitmap object or the handle to icon, state of check box, and these messages also can be used to get or set the text string of item:

```cplusplus
HICON hIcon1;           /* Declare an icon handle */
LISTBOXITEMINFO lbii;   /* Declare a struct variable of the list box item info */

hIcon1 = LoadIconFromFile (HDC_SCREEN, "res/audio.ico", 1);  /* Load an icon */

/* Set the structure information, and set an item */
lbii.hIcon = hIcon1;
lbii.cmFlag = CMFLAG_CHECKED;
lbii.string = "new item";
SendMessage (hChildWnd3, LB_SETITEMDATA, index, (LPARAM)&lbii);
```

The following messages are used to retrieve the selection state of list items; these messages have different calling method for single-selection list box and multiple-selection list box. Let us to look at the single-selection list box first.

Generally, the user selects an item by mouse and keyboard. But we also can control the current selected item by program, at this time, we need send LB_SETCURSEL message:


```cplusplus
SendMessage (hwndList, LB_SETCURSEL, index, 0) ;
```

In contrast, we can use LB_GETCURSEL to get the current selected item:

```cplusplus
index = SendMessage (hwndList, LB_GETCURSEL, 0, 0) ;
```

If no item is selected, then the message returns LB_ERR.

For multiple-selection list box, LB_SETCURSEL and LB_GETCURSEL can only be used to set or get the current highlighted item, but cannot get all selected items. But we can use LB_SETSEL to set the selection state of a certain item without affecting other items:

```cplusplus
SendMessage (hwndList, LB_SETSEL, wParam, (LPARAM)index) ;
```

If wParam is not 0, this function selects and highlights an item; if wParam is 0, this function cancels the selection. In contrast, we can use LB_GETSEL to get the selection state of a certain item: 

```cplusplus
select = SendMessage (hwndList, LB_GETSEL, index, 0) ;
```

Here, if the item specified by index is selected, select is a non-zero value, else select is 0.

In addition, you can also use LB_GETSELCOUNT message to get the number of all selected items in a multiple-selection list box. Then you can send LB_GETSELITEMS message to get the index values of all the selected items. The following is an example:

```cplusplus
int i, sel_count;
    int* sel_items;

    sel_count = SendMessage (hwndList, LB_GETSELCOUNT, 0, 0L) ;
    if (sel_count == 0)
       return;

     sel_items = alloca (sizeof(int)*sel_count);
     SendMessage (hwndList, LB_GETSELITEMS, sel_count, sel_items);
     for (i = 0; i < sel_count; i++) {
          /* sel_items [i] is the index of one selected item */
}
```

### 21.2.4 Searching Item Including a Text String

```cplusplus
index = SendMessage (hwndList, LB_FINDSTRING, (LPARAM)string) ;
```

Here, string is the pointer to a string, which should be found; the message returns the index of the fuzzy matched string, and LB_ERR means failure. Using LB_FINDSTRINGEXACT message will search the matched item exactly.

### 21.2.5 Setting/Getting the Status of Check Mark

```cplusplus
status = SendMessage (hwndList, LB_GETCHECKMARK, index, 0) ;
```

The message LB_GETCHECKMARK returns the check mark status of the check box specified by index. If corresponding item is not found, LB_ERR returned. CMFLAG_CHECKED indicates the check box of the item is checked. CMFLAG_PARTCHECKED indicates the check box of the item is partly checked. CMFLAG_BLANK indicates the check box of the item is not checked.

```cplusplus
ret = SendMessage (hwndList, LB_SETCHECKMARK, index, (LPARAM)status) ;
```

The message LB_SETCHECKMARK sets the check mark status of the check box specified by index to be the value of status. If the item specified by the index is not found, it returns LB_ERR for failure, else returns LB_OKAY for success.

### 21.2.6 Setting the Bold Status of Item

```cplusplus
ret = SendMessage (hwndList, LB_SETITEMBOLD, index, (LPARAM)status) ;
```

The message LB_ SETITEMBOLD sets the bold status of the item specified by index to be the value of status (TRUE or FALSE). If the item specified by the index is not found, it returns LB_ERR for failure. 

### 21.2.7 Setting/Getting the Disable Status of Item

```cplusplus
status = SendMessage (hwndList, LB_GETITEMDISABLE, index, 0) ;
```

The message LB_GETI	TEMDISABLE returns the disable status of the item specified by index. If corresponding item is not found, LB_ERR returned. 1 indicates the item is disabled. 0 indicates the item is not disabled. 

```cplusplus
ret = SendMessage (hwndList, LB_SETITEMDISABLE, index, (LPARAM)status) ;
```

The message LB_SETITEMDISABLE sets the disable status of the item specified by index to be the value of status. If the item specified by the index is not found, it returns LB_ERR for failure.

### 21.2.8 Adding Multiple Items into List Box

The message LB_MULTIADDITEM is used to adding multiple items into List Box. When the stored content of the list box exceeds the available memory space, SendMessage returns LB_ERRSPACE. If error is caused by other reasons, SendMessage returns LB_ERR. If the operation is successful, SendMessage returns LB_OKAY. We can determine above two errors by testing the non-zero value of SendMessage.

If you adopt LBS_SORT style, or just want to append the new text string array as the last items of a list box, sample is as follows:

```cplusplus
int num = 2;
const char text[num][] = {“item1”, “item2”};

SendMessage (hwndList, LB_MULTIADDITEM, num, (LPARAM)text);
```

Parameter hwndList is the handle of the list box control; num is the number of item added, and text is the string text array address. 

It should be noted that, after specifying LBS_CHECKBOX or LBS_USEICON style, when you add multiple items to a list box, you must use LISTBOXITEMINFO structure, and cannot use the string array address directly, for example:

```cplusplus
int num = 2;
HICON hIcon1;           /* Declare an icon handle */
LISTBOXITEMINFO lbii[num];   /* Declare a struct variable of the list box item info */

hIcon1 = LoadIconFromFile (HDC_SCREEN, "res/audio.ico", 1);  /* Load an icon */

/* Set the structure information, and add items */
lbii[0].hIcon = hIcon1;
lbii[0].cmFlag = CMFLAG_CHECKED;
lbii[0].string = "item1";

lbii[1].hIcon = hIcon1;
lbii[1].cmFlag = CMFLAG_CHECKED;
lbii[1].string = "item2";

SendMessage (hwndList, LB_MULTIADDITEM, num, (LPARAM)lbii);
```

### 21.2.9 Other Messages

A list box with style of LBS_SORT uses the standard C function strncmp to sort items. But we can overload the default sort method by using LB_SETSTRCMPFUNC in order to sort items according to the expected method. For example:

```cplusplus
static int my_strcmp (const char* s1, const char* s2, size_t n)
{
    int i1 = atoi (s1);
    int i2 = atoi (s2);
    return (i1 – i2);
}

    SendMessage (hwndList, LB_SETSTRCMPFUNC, 0, (LPARAM)my_strcmp);
```

Thus, the list box will use the user-defined function to sort items. Sort function described above can be used to sort the items in form as 1, 2, 3, 4, 10, 20 etc. according to integer values, while the default sort rule would sort the items above as 1, 10, 2, 20, 3, and 4. Generally speaking, application should use the message to set a new string comparison function before adding any item.

We also can associate an additional 32-bit data with each list item, and get the value at appropriate time. For doing this, we can use LB_SETITEMADDDATA and LB_GETITEMADDDATA messages. The values operated by the two messages have no meaning for the list box control. The control only takes charge to store the value and return the value when needed.

In addition, we can also use LB_SETITEMHEIGHT message to set the height of items, and use LB_GETITEMHEIGHT to get the height. Generally, height of items depends on the size of control font, and varies when the control font changes (call SetWindowFont to change). The users can also set themselves height of items. The actual height will be the maximum of the height set and control font size.


## 21.3 Notification Codes of List Box

Notification codes generated by a list box with LBS_NOTIFY style and their meanings are shown in Table 21.1.

<center>
Table 21.1 Notification codes of list box<br>
|*Notification code identifier*       |*Meaning*|
|LBN_ERRSPACE       |Indicates that memory allocation failure.|
|LBN_SELCHANGE      |Indicates the current selected item changes|
|LBN_CLICKED        |Indicates click on an item|
|LBN_DBLCLK         |Indicates double click on an item|
|LBN_SELCANCEL      |Indicates cancel of the selection|
|LBN_SETFOCUS       |Indicates gain of input focus|
|LBN_KILLFOCUS      |Indicates loss of input focus|
|LBN_CLICKCHECKMARK |Indicates click on the check mark|
|LBN_ENTER          |Indicates the user has pressed the ENTER key|
</center>

A list box control will not send notification messages described above unless the window style of the list box have LBS_NOTIFY style. Certainly, if you have called SetNotificationCallback function to set the notification callback function, the control will not send MSG_COMMAND notification message to its parent window, but call the specified notification callback function directly.

LBN_ERRSPACE indicates that the memory allocation fails. LBN_SELCHANGE indicates the currently selected item has been changed, which occurs in the following cases: the user changes the highlighted item with the keyboard or mouse, or the user switches the selection status with the Space key or mouse. LBN_CLICKED indicates the mouse, which occurs when the user uses the mouse to click an item, clicks the list box. LBN_DBLCLK indicates an item is double clicked by the user if LBS_CHECKBOX style is set, LBN_CLICKCHECKMARK indicates the user clicked the check mark, and if LBS_AUTOCHECK style is set at the same time, the check box will be auto-switched between the checked or unchecked status.

Based on the requirements of applications, either LBN_SELCHANGE or LBN_DBLCLK might be used, or both might be used. Program will receive many messages of LBN_SELCHANGE, but the message of LBN_DBLCLK will be received only when users double click.

## 21.4 Sample Program

The program in List 21.1 provides an example for the use of list box controls. The program imitates the “Open File” dialog box to realize the file deleting function. Initially, the program lists all the files in the current directory, and the user can also change to other directories through the directory list box. The user can select multiple files to be deleted in the file list box by select the check marks. When the user pushes the “Delete” button, the program will prompt the user. Of course, to protect the user’s files, the program does not delete the files really. The effect of the dialog box created by this program is shown in Fig. 21.4. Please refer to listbox.c file of the demo program package of this guide for complete source code.

<center>List 21.1 The use of list box controls</center>

```cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDL_DIR    100
#define IDL_FILE   110
#define IDC_PATH   120

/* Define dialog box template */
static DLGTEMPLATE DlgDelFiles =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    100, 100, 304, 225,
    "删除文件",
    0, 0,
    7, NULL,
    0
};

static CTRLDATA CtrlDelFiles[] =
{ 
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        10, 10, 130, 15,
        IDC_STATIC,
        "目录列表框",
        0
    },
    /* This list box displays directories */
    {
        CTRL_LISTBOX,
        WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_NOTIFY,
        10, 30, 130, 100,
        IDL_DIR,
        "",
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        150, 10, 130, 15, 
        IDC_STATIC, 
       "文件列表框",
        0
    },
    /* This list box displays files with a check box in front for each file */
    {
        CTRL_LISTBOX,
        WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX,
        150, 30, 130, 100,
        IDL_FILE,
        "",
        0
    },
    /* This static control is used to display the current path information */
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        10, 150, 290, 15, 
        IDC_PATH, 
       "路径：",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        10, 170, 130, 25,
        IDOK, 
        "删除",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        150, 170, 130, 25,
        IDCANCEL,
        "取消",
        0
    },
};

/* This function gets all the directory items in the current directory, 
 * and adds them to the directory list box and file list box, respectively
 */
static void fill_boxes (HWND hDlg, const char* path)
{
    struct dirent* dir_ent;
    DIR*   dir;
    struct stat ftype;
    char   fullpath [PATH_MAX + 1];

    SendDlgItemMessage (hDlg, IDL_DIR, LB_RESETCONTENT, 0, (LPARAM)0);
    SendDlgItemMessage (hDlg, IDL_FILE, LB_RESETCONTENT, 0, (LPARAM)0);
    SetWindowText (GetDlgItem (hDlg, IDC_PATH), path);
    
    if ((dir = opendir (path)) == NULL)
         return;

    while ( (dir_ent = readdir ( dir )) = NULL ) {

        /* Assemble full path name. */
        strncpy (fullpath, path, PATH_MAX);
        strcat (fullpath, "/");
        strcat (fullpath, dir_ent->d_name);
        
        if (stat (fullpath, &ftype) < 0 ) {
           continue;
        }

        if (S_ISDIR (ftype.st_mode))
            SendDlgItemMessage (hDlg, IDL_DIR, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
        else if (S_ISREG (ftype.st_mode)) {
            /* When using the list box of a checkbox, 
             * the following structure need to be used */
            LISTBOXITEMINFO lbii;

            lbii.string = dir_ent->d_name;
            lbii.cmFlag = CMFLAG_BLANK;
            lbii.hIcon = 0;
            SendDlgItemMessage (hDlg, IDL_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);
        }
    }

    closedir (dir);
}

static void dir_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    /* When the user double clicked the directory name or 
     * pressed the ENTER key, he will enter the corresponding directory */
    if (nc == LBN_DBLCLK || nc == LBN_ENTER) {
        int cur_sel = SendMessage (hwnd, LB_GETCURSEL, 0, 0L);
        if (cur_sel >= 0) {
            char cwd [MAX_PATH + 1];
            char dir [MAX_NAME + 1];
            GetWindowText (GetDlgItem (GetParent (hwnd), IDC_PATH), cwd, MAX_PATH);
            SendMessage (hwnd, LB_GETTEXT, cur_sel, (LPARAM)dir);

            if (strcmp (dir, ".") == 0)
                return;
            strcat (cwd, "/");
            strcat (cwd, dir);
            /* Fill the two list boxes again */
            fill_boxes (GetParent (hwnd), cwd);
        }
    }
}

static void file_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    /* Do nothing */
}

static void prompt (HWND hDlg)
{
    int i;
    char files [1024] = "你选择要删除的文件是：\n";

    /* Get all the checked files */
    for (i = 0; i < SendDlgItemMessage (hDlg, IDL_FILE, LB_GETCOUNT, 0, 0L); i++) {
    char file [MAX_NAME + 1];
        int status = SendDlgItemMessage (hDlg, IDL_FILE, LB_GETCHECKMARK, i, 0);
        if (status == CMFLAG_CHECKED) {
            SendDlgItemMessage (hDlg, IDL_FILE, LB_GETTEXT, i, (LPARAM)file);
            strcat (files, file);
            strcat (files, "\n");
        }
    }

    /* Prompt the user */
    MessageBox (hDlg, files, "确认删除", MB_OK | MB_ICONINFORMATION);

    /* Here these files are actually deleted */
}

static int DelFilesBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
    {
        char cwd [MAX_PATH + 1];
        SetNotificationCallback (GetDlgItem (hDlg, IDL_DIR), dir_notif_proc);
        SetNotificationCallback (GetDlgItem (hDlg, IDL_FILE), file_notif_proc);
        fill_boxes (hDlg, getcwd (cwd, MAX_PATH));
        return 1;
    }
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
            prompt (hDlg);
        case IDCANCEL:
            EndDialog (hDlg, wParam);
            break;
        }
        break;
        
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "listbox" , 0 , 0);

#endif
    
    DlgDelFiles.controls = CtrlDelFiles;
    
    DialogBoxIndirectParam (&DlgDelFiles, HWND_DESKTOP, DelFilesBoxProc, 0L);

    return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif
```

<center>
<img src="%ATTACHURLPATH%/21.4.jpeg" alt="21.4.jpeg"  ALIGN="CENTER" /> <br>
Fig. 21.4  “Delete File” dialog box
</center>


-- Main.XiaodongLi - 26 Oct 2009

