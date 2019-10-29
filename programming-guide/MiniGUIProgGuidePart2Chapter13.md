# Edit Box and Derived Control

## Brief Introduction to Edit Box Control

Edit box control is one of the essential controls in GUI system, which is 
mainly used to receive character input of the users and realize the function of
user interaction and text edition. In Realization, it is divided into single
line edit and multi-line edit. Single line edit box is used to receive single
line text input with comparatively simple user content, in comparison, 
multi-line text is used to receive complicated and large volume of text input.

- Class hierarchical relation of edit box
- [`mWidget`](MStudioMGNCSV1dot0PGP2C3#mWidget)
   * [`mScrollWidget`](MStudioMGNCSV1dot0PGP2C7#m_ScrollWidget)
   * [`mItemView`](MStudioMGNCSV1dot0PGP2C)
   * [`mScrollView`](MStudioMGNCSV1dot0PGP2C)
   * [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit)
   * [`mSlEdit`](MStudioMGNCSV1dot0PGP2C12#m_SlEdit)
   * [`mMlEdit`](MStudioMGNCSV1dot0PGP2C12#m_MlEdit)

- Example diagram

![alt](figures/edit.png)

## `mEdit`

- *Control window class*: `NCSCTRL_EDIT`
- *Control English name*: Edit
- *Brief introduction*: Foundation class of edit box series controls, it is the
abstract parent class of single line edit box and multi-line edit box, which
defines the common use interface of the two.
- *Schematic diagram*: _Abstract class, and cannot be used directly_.

### Style of `mEdit`

It is inherited from the style of [`mScrollView`](MStudioMGNCSV1dot0PGP2C)

| *Style name* | *miniStudio property name* | *Explanation* |
|--------------|----------------------------|---------------|
| `NCSS_EDIT_LEFT` | `Align->Left` | Left aligned |
| `NCSS_EDIT_CENTER` | `Align->Center` | Horizontal centering |
| `NCSS_EDIT_RIGHT` | `Align->Right` | Right aligned |
| `NCSS_EDIT_UPPERCASE` | `Case->Upper` | The input content is automatically converted to capital letter |
| `NCSS_EDIT_LOWERCASE` | `Case->Lower` | The input content is automatically converted to lower case letter |
| `NCSS_EDIT_NOHIDESEL` | `HideSel->FALSE` | When the edit box loses focus, the selected content still remains selected status |
| `NCSS_EDIT_READONLY` | `ReadOnly->TRUE` | The content is read only |
| `NCSS_EDIT_BASELINE` | `BaseLine->TRUE` | Content underlined display |

### Property of `mEdit`

It is inherited from the property of [`mScrollView`](MStudioMGNCSV1dot0PGP2C).

| *Property* | *miniStudio property name* | *Type* | *Authority* | *Explanation*  |
|------------|----------------------------|--------|-------------|----------------|
| `NCSP_EDIT_LIMITTEXT` | `MaxLength` | int | `RW` | Character number limit value |
| `NCSP_EDIT_CARETPOS` | -- | int | `RW` | Cursor location |

### Event of `mEdit`

It is inherited from the event of [`mScrollView`](MStudioMGNCSV1dot0PGP2C).

| *Event ID* | *Parameter* | *Explanation* |
|------------|-------------|---------------|
| `NCSN_EDIT_CHANGE` | -- | Content changes |
| `NCSN_EDIT_CONTCHANGED` | -- | When edit loses the focus, the content changes |
| `NCSN_EDIT_UPDATE` | -- | The content is refreshed when changed through `setText` and `resetContent` method or the property is changed |
| `NCSN_EDIT_SELCHANGED` | -- | The selected part changes |
| `NCSN_EDIT_MAXTEXT` | -- | Character number is saturated |
| `NCSN_EDIT_SETFOCUS` | -- | Get the focus |
| `NCSN_EDIT_KILLFOCUS` | -- | Lose the focus |

### Method of `mEdit`

It is inherited from the method of[`mScrollView`](MStudioMGNCSV1dot0PGP2C).

#### `setContent`

```cpp
void setContent(mEdit *self, const char* str, int start, int len)
```

- Parameter
   - str -- literal content displayed in edi
   - start -- display starting location (relative to the starting location of 
     str), 0 represents starting from the beginning
   - len -- display character number, -1 represents ending till the end of str
- Explanation: 
Set the display content of the edit box. The method will get altogether
characters from No. character location from str character string, and replace
the existing content in edit.
- Example:

```cpp
// In edit, character string starting from the sixth character till the end of characterstring “dddd Show Me” will be displayed, and here it is “Show Me”
_c(edit)->setContent(edit, "dddd Show Me", 6, -1);
```

#### `replaceText`

```cpp
void replaceText(mEdit *self, const char* str, 
    int start, int len, int replace_start, int replace_end)
```

- Parameter
   - str -- source character string used for replacement
   - start -- deviation of the source text used for replacement relative to str, 0
   represents starting from the beginning
   - len -- length used to the source text, -1 represents starting from start and
   ending till str
   - `replace_start` -- replace the starting location (relative to the existing
   content in edit)
   - `replace_end` -- replace the ending location (relative to the existing 
   content in edit)
- Explanation: 
Replacement of character string, the method will get altogether characters
starting from No. character location from str character string, and replaces 
the existing content from to in edit. Str is the character string to be 
replaced to, start is the starting location relative to str, 0 represents
starting from the beginning, len is the length, -1 represents ending till the
end of str, `replace_start` and `replace_end` are the starting point and ending
point of the location to be replaced, and they are location deviation relative
to the existing text content in edit.
- Example:

```cpp
// In edit, character string starting from the sixth character to the end of the character string “dddd Show Me” will be used (here it is “Show Me”),
// To replace the characters from the second one to the tenth one of the existing text in edit
_c(edit)->replaceText(edit, "dddd Show Me", 6, -1, 2, 10);
```

#### insert

```cpp
void insert(mEdit *self, const char* str, int start, int len, int at)
```
- Parameter
   - str -- source character string to be inserted
   - start -- starting location of the source text used, 0 represents starting 
   from the beginning
   - len -- length of the source text used, -1 represents starting from start, and
   ending till str
   - at -- location of the insert point (relative to the existing content in 
   edit), -1 represents the end
- Explanation: 
Insert of the character string, the method will get altogether characters
starting from No. character location in str character string, and it is
inserting into location of No. character of the existing content in edit. Str 
is the character string to be inserted, start is the starting location relative
to str, 0 represents starting from the beginning, len is the length, -1
represents ending till the end of str, at parameter is the location to insert,
and it is the location deviation relative to the existing text content in edit
- Example:

```cpp
//In edit, character string starting from the sixth character till the end of the character string “dddd Show Me” will be used (here it is “Show Me”), 
// To insert to after the second character of the existing text in edit
_c(edit)->insert(edit, "dddd Show Me", 6, -1,  2);
```

#### append

```cpp
void append(mEdit *self, const char* str, int start, int len)
```
- Parameter
   - str -- source character string to append
   - start -- starting location of the source text used, 0 represents starting 
   from the beginning
   - len -- length of the source text used, -1 represents starting from start and
   ending till str
- Explanation: 
Append the character string, the method will get altogether characters starting
from No. character location from str character string, and append to after the
existing content in edit. str is the character string to append, start is the
starting location relative to str, 0 represents starting from the beginning, 
len is the length, and -1 represents ending till the end of str.
- Example:
```cpp
// In edit, character string starting from the sixth character till the end of the character string “dddd Show Me” will be used (here it is “Show Me”),
// To append till the end of the existing text in edit
_c(edit)->append(edit, "dddd Show Me", 6, -1);
```

#### `getTextLength`

```cpp
int getTextLength(mEdit *self)
```
- Explanation: Get length of the content of the character string in Edit
- Example:

```cpp
int text_len = _c(edit)->getTextLength(edit);
```

#### `getContent`

```cpp
int getContent(mEdit *self, char *strbuff, int buf_len, int start, int end)
```
- Parameter:
   - strbuff -- get storage location to the character string (storage space shall
   be distributed in advance)
   - `buff_len` -- size of strbuff
   - start -- starting location of the obtained content
   - end -- ending location of the obtained content
- Explanation:
Get character string content in edit, and get the content from to location from
the existing content and write into strbuff, and the maximum number to write in
is limited to `buff_len.`
- Example: 

```cpp
char buff[128];
_c(edit)->getContent(edit, buff, 127, 0, -1); // Get out all the content in edit, and buff stores 127 characters to the maximum
```

#### `setSel` and `getSel`

```cpp
    int setSel(mEdit *self, int start, int end)
    int getSel(mEdit *self, int *pstart, int *pend)
```

- Parameter: 
   - start \end -- starting point and ending point of the selected region
   - pstart\pend -- starting point and ending point of the selected region, used
   for function return
- Explanation: 
Set and get the region of the selected text, and the last two parameters
correspond to the starting point and ending point of the selected region
respectively 
- Example: 

```cpp
_c(edit)->setSel(edit, 2, 10); // Set No.2 to No.10 characters of edit as selected status

int ps,pe;
_c(edit)->getSel(edit, &ps, &pe); // Get the selected region
```

#### `setMargin`

```cpp
void setMargin(mEdit *self, int left, int top, int right, int bottom)
```
- Parameter: 
   - left,top,right,bottom -- margin of left, top, right and bottom, the parameter
   is not a concept of rectangle, and it just continues to use the data structure
   of rectangle for the convenience of parameter transmission
- Explanation: Set left, top, right and bottom margin of the edit region
- Example: 

```cpp
// Set margin
_c(edit)- >setMargin(edit, 10,10,10,10);
```

#### copy, paste, and cut

```cpp
    void copy(mEdit *self)
    void cut(mEdit *self)
    void paste(mEdit *self)
    TextCopyPaste * setCopyPaste(mEdit *self, TextCopyPaste* cp)
```

Cut, copy and paste aim at the operation of the selected region. In edit, a
group of operation set using minigui cut board is realized by default, and the
users can set operation set realized by itself through `setCopyPaste`.

#### makevisible

```cpp
    BOOL makevisible(mEdit *self, int pos)
```
- Parameter: 
   - pos -- location needs to be visible
- Explanation: 
Control scrolling of the edit region, making the characters of the location
`pos` become visible.
- Example: 

```cpp
// Visible at No. 201 character
_c(edit)- >makevisible(edit, 201);
```

## `mSlEdit`

- *Control window class*: `NCSCTRL_SLEDIT`
- *Control English name*: Single Line Edit Or SlEdit
- *Brief introduction*: Single line text edit box
- *Schematic diagram*:

![alt](figures/sledit.png)


### Style of `mSIEdit`

It is inherited from the style of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

| *Style name* | *miniStudio property name* | *Explanation* |
|--------------|----------------------------|---------------|
| `NCSS_SLEDIT_PASSWORD` | `Password->TRUE` | Content of the edit box is shield displayed in the mode of password input |
| `NCSS_SLEDIT_AUTOSELECT` | `AutoSelect->TRUE` | Automatic selected style, after the focus is obtained, the text automatically becomes selected status |


### Property of `mSIEdit`

It is inherited from the property of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

| *Property* | *miniStudio property name* | *Type* | *Authority* | *Explanation* |
|------------|----------------------------|--------|-------------|---------------|
| `NCSP_SLEDIT_TIPTEXT` | `ToolTip` | char * | `RW` | Prompt information character string, when there is no input, information used to prompt users |
| `NCSP_SLEDIT_PWDCHAR` | `PasswordChar` | char | `RW` | Character displayed by pass word, only `NCSS_SLEDIT_PASSWORD` style is valid, `*` by default |


### Event of `mSIEdit`

It is inherited from the event of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

| *Event ID* | *Parameter* | *explanation* |
|------------|-------------|---------------|
| `NCSN_SLEDIT_ENTER` | -- | Capture enter key information |


### Method of `mSIEdit`

It is inherited from the method of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).
_There is no newly introduced method_.

### Programming Example of `mSIEdit`

- `SlEdit` Example code:

```cpp
/*
** edit.c: Sample program for mGNCS Programming Guide
**      Using edit.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_NAME     104
#define ID_COUN     105
#define ID_CITY     106
#define ID_PSWD     107
#define ID_SPIN     108
#define ID_INFO     109

#define ID_REG      155
#define ID_CAN      156


static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    return TRUE;
}

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE,  mymain_onClose},
    {0, NULL}
};

static void btn_onClicked(mWidget* _this, int id, int nc, HWND hCtrl)
{
    if(nc == NCSN_WIDGET_CLICKED)
    {
        if (id == ID_CAN){
            PostMessage(GetParent(_this->hwnd), MSG_CLOSE, 0, 0);
        } else if (id == ID_REG){
            //TODO
        }

    }
};

static NCS_EVENT_HANDLER btn_handlers[] =
{
    {NCS_NOTIFY_CODE(NCSN_WIDGET_CLICKED), btn_onClicked},
    {0, NULL}
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"fashion","fashion", NULL}
};

static NCS_PROP_ENTRY static_props[] =
{
    {NCSP_STATIC_ALIGN, NCS_ALIGN_RIGHT},
    {0, 0}
};

static NCS_PROP_ENTRY spin_props [] =
{
    {NCSP_SPNBOX_MAXPOS, 99},
    {NCSP_SPNBOX_MINPOS, 0},
    {NCSP_SPNBOX_CURPOS, 25},
    {NCSP_SPNBOX_LINESTEP, 1},
    {0, 0}
};

#define HSTART  25
#define HSPACE  40

static NCS_WND_TEMPLATE _ctrl_templ[] =
{
//START_OF_SLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Name :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //左对齐
        NCSCTRL_SLEDIT,
        ID_NAME,
        100, HSTART, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LEFT,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Age :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SPINBOX,
        ID_SPIN,
        100, HSTART + HSPACE, 70, 25,
        WS_VISIBLE | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_AUTOLOOP,
        WS_EX_NONE,
        "",
        spin_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 2 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Country:",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //居中对齐， 大写字母
        NCSCTRL_SLEDIT,
        ID_COUN,
        100, HSTART + 2 * HSPACE, 130, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_CENTER | NCSS_EDIT_UPPERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 3 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "City :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //小写字母
        NCSCTRL_SLEDIT,
        ID_CITY,
        100, HSTART + 3 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LOWERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 4 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Passwd :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //密码输入形式的edit
        NCSCTRL_SLEDIT,
        ID_PSWD,
        100, HSTART + 4 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_SLEDIT_PASSWORD,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_SLEDIT_TEMPLATE
//START_OF_MLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 5 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Info :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //多行编辑框
        NCSCTRL_MLEDIT,
        ID_INFO,
        100, HSTART + 5 * HSPACE, 200, 160,
        WS_BORDER | WS_VISIBLE | WS_VSCROLL | NCSS_EDIT_BASELINE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_MLEDIT_TEMPLATE

    {
        NCSCTRL_BUTTON,
        ID_REG,
        240, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Register",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_CAN,
        120, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Cancel",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
};

static NCS_MNWND_TEMPLATE mymain_templ =
{
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 360, 480,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Register",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain (int argc, const char* argv[])
{
    ncsInitialize ();

    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal (mydlg, TRUE);

    ncsUninitialize ();

    return 0;
}

```

- We define use template of `SIEdit` in this way

```cpp
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Name :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //左对齐
        NCSCTRL_SLEDIT,
        ID_NAME,
        100, HSTART, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LEFT,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Age :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SPINBOX,
        ID_SPIN,
        100, HSTART + HSPACE, 70, 25,
        WS_VISIBLE | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_AUTOLOOP,
        WS_EX_NONE,
        "",
        spin_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 2 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Country:",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //居中对齐， 大写字母
        NCSCTRL_SLEDIT,
        ID_COUN,
        100, HSTART + 2 * HSPACE, 130, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_CENTER | NCSS_EDIT_UPPERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 3 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "City :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //小写字母
        NCSCTRL_SLEDIT,
        ID_CITY,
        100, HSTART + 3 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LOWERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 4 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Passwd :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //密码输入形式的edit
        NCSCTRL_SLEDIT,
        ID_PSWD,
        100, HSTART + 4 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_SLEDIT_PASSWORD,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
```

- *Control window class*: `NCSCTRL_MLEDIT`
- *Control English name*: Multiline Edit or `MlEdit`
- *Brief introduction*: Multiline text edit box
- *Schematic diagram*:

![alt](figures/mledit.png)

### Style of `mMIEdit`

It is inherited from the style of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

| *Style name* | *miniStudio property name* | *Explanation*  |
|--------------|----------------------------|----------------|
| `NCSS_MLEDIT_AUTOWRAP` | `AutoWrap->TRUE` | Automatic wrap |

### Property of `mMIEdit`

It is inherited from the property of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

| *Property* | *miniStudio property name* | *Type* | *Authority* | *Explanation* |
|------------|----------------------------|--------|-------------|---------------|
| `NCSP_MLEDIT_LINECOUNT`| -- | int | `RO` | Row number |
| `NCSP_MLEDIT_LINEHEIGHT`| `LineHeight` | int | `RW` | Row height |
| `NCSP_MLEDIT_LINEFEEDISPCHAR` | -- | char | `WO` | Line break is displayed by this character |
| `NCSP_MLEDIT_LINESEP` | `LineSeperator` | char | `RW` | Line break symbol, “\n” by default |
| `NCSP_MLEDIT_CARETSHAPE` | `CaretShap` | int | `RW` | Cursor shape `ED_CARETSHAPE_LINE` or `ED_CARETSHAPE_BLOCK` |
| `NCSP_MLEDIT_NUMOFPARAGRAPHS` | -- | int | `RO` | Number of paragraphs |


### Event of `mMIEdit`

It is inherited from the event of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).
_There is no newly introduced event_.

### Method of `mMIEdit`

It is inherited from the method of [`mEdit`](MStudioMGNCSV1dot0PGP2C12#mEdit).

### Programming Example of `mMIEdit`

- `MlEdit` Example code:

```cpp
/*
** edit.c: Sample program for mGNCS Programming Guide
**      Using edit.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_NAME     104
#define ID_COUN     105
#define ID_CITY     106
#define ID_PSWD     107
#define ID_SPIN     108
#define ID_INFO     109

#define ID_REG      155
#define ID_CAN      156


static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    return TRUE;
}

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE,  mymain_onClose},
    {0, NULL}
};

static void btn_onClicked(mWidget* _this, int id, int nc, HWND hCtrl)
{
    if(nc == NCSN_WIDGET_CLICKED)
    {
        if (id == ID_CAN){
            PostMessage(GetParent(_this->hwnd), MSG_CLOSE, 0, 0);
        } else if (id == ID_REG){
            //TODO
        }

    }
};

static NCS_EVENT_HANDLER btn_handlers[] =
{
    {NCS_NOTIFY_CODE(NCSN_WIDGET_CLICKED), btn_onClicked},
    {0, NULL}
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"fashion","fashion", NULL}
};

static NCS_PROP_ENTRY static_props[] =
{
    {NCSP_STATIC_ALIGN, NCS_ALIGN_RIGHT},
    {0, 0}
};

static NCS_PROP_ENTRY spin_props [] =
{
    {NCSP_SPNBOX_MAXPOS, 99},
    {NCSP_SPNBOX_MINPOS, 0},
    {NCSP_SPNBOX_CURPOS, 25},
    {NCSP_SPNBOX_LINESTEP, 1},
    {0, 0}
};

#define HSTART  25
#define HSPACE  40

static NCS_WND_TEMPLATE _ctrl_templ[] =
{
//START_OF_SLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Name :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //左对齐
        NCSCTRL_SLEDIT,
        ID_NAME,
        100, HSTART, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LEFT,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Age :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SPINBOX,
        ID_SPIN,
        100, HSTART + HSPACE, 70, 25,
        WS_VISIBLE | NCSS_SPNBOX_NUMBER | NCSS_SPNBOX_AUTOLOOP,
        WS_EX_NONE,
        "",
        spin_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 2 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Country:",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //居中对齐， 大写字母
        NCSCTRL_SLEDIT,
        ID_COUN,
        100, HSTART + 2 * HSPACE, 130, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_CENTER | NCSS_EDIT_UPPERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 3 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "City :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //小写字母
        NCSCTRL_SLEDIT,
        ID_CITY,
        100, HSTART + 3 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_EDIT_LOWERCASE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 4 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Passwd :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //密码输入形式的edit
        NCSCTRL_SLEDIT,
        ID_PSWD,
        100, HSTART + 4 * HSPACE, 150, 25,
        WS_BORDER | WS_VISIBLE | NCSS_SLEDIT_PASSWORD,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_SLEDIT_TEMPLATE
//START_OF_MLEDIT_TEMPLATE
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 5 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Info :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //多行编辑框
        NCSCTRL_MLEDIT,
        ID_INFO,
        100, HSTART + 5 * HSPACE, 200, 160,
        WS_BORDER | WS_VISIBLE | WS_VSCROLL | NCSS_EDIT_BASELINE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
//END_OF_MLEDIT_TEMPLATE

    {
        NCSCTRL_BUTTON,
        ID_REG,
        240, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Register",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_CAN,
        120, 400, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Cancel",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
};

static NCS_MNWND_TEMPLATE mymain_templ =
{
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 360, 480,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Register",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain (int argc, const char* argv[])
{
    ncsInitialize ();

    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal (mydlg, TRUE);

    ncsUninitialize ();

    return 0;
}

```

- We define the use template of `MIEdit` in this way

```cpp
    {
        NCSCTRL_STATIC,
        0,
        10, HSTART + 5 * HSPACE, 70, 25,
        WS_VISIBLE,
        WS_EX_NONE,
        "Info :",
        static_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {   //多行编辑框
        NCSCTRL_MLEDIT,
        ID_INFO,
        100, HSTART + 5 * HSPACE, 200, 160,
        WS_BORDER | WS_VISIBLE | WS_VSCROLL | NCSS_EDIT_BASELINE,
        WS_EX_NONE,
        "",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
```
----

[&lt;&lt; Property Sheet Control Class](MiniGUIProgGuidePart2Chapter12.md) |
[Table of Contents](README.md) |
[Animation Control Class &gt;&gt;](MiniGUIProgGuidePart2Chapter14.md)

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
