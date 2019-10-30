# Panel and Derived Classes

- [Brief Introduction of Panel Class Control](#brief-introduction-of-panel-class-control)
- [`mPanel`](#mpanel)
   + [Style of `mPanel`](#style-of-mpanel)
   + [Property of `mPanel`](#property-of-mpanel)
   + [Event of `mPanel`](#event-of-mpanel)
   + [Method of `mPanel`](#method-of-mpanel)
   + [Renderer of `mPanel`](#renderer-of-mpanel)
   + [Example of `mPanel`](#example-of-mpanel)
- [`mCombobox`](#mcombobox)
   + [Style of `mCombobox`](#style-of-mcombobox)
   + [Property of `mCombobox`](#property-of-mcombobox)
   + [Event of `mCombobox`](#event-of-mcombobox)
   + [Method of `mCombobox`](#method-of-mcombobox)
   + [Renderers of `mCombobox`](#renderers-of-mcombobox)
   + [Example of `mCombobox`](#example-of-mcombobox)


## Brief Introduction of Panel Class Control

This class of control is the container class controls that accommodate other
classes of controls, which are generally combination control class and main
window class.

The class inheritance relation of panel and its derived class is as follows:

- [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget)
   - [mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel)
      - [mComboBox](MiniGUIProgGuidePart2Chapter07.md#mcombobox)
      - [mMainWnd](MiniGUIProgGuidePart2Chapter07.md#mmainwnd)
         - [mDialogBox](MiniGUIProgGuidePart2Chapter07.md#mdialogbox)

## `mPanel`

- *Control name*: `NCSCTRL_PANEL`
- *English name*: Panel
- *Brief introduction*: Container of other controls, mainly used for carrying
out grouped operation to the controls. Through grouping the controls into the
panel control, a group of controls can be conveniently displayed or hidden.
- *Schematic diagram*: <br/>

![alt](figures/panel.png)

Panel must exist in `MainWnd`, `DialogBox`, another Panel control or other
controls. Besides other controls, it can contain content such as texts and
images etc.

### Style of `mPanel`

It is inherited from the style of [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget).

### Property of `mPanel`

It is inherited from the property of [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget).

### Event of `mPanel`

It is inherited from the event of [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget).

### Method of `mPanel`

It is inherited from the method of [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget).

The class does not have newly added methods

### Renderer of `mPanel`

It is inherited from the renderer of [mWidget](MiniGUIProgGuidePart2Chapter04.md#mwidget). 

`mPanel` does not have newly added renderer method

### Example of `mPanel`

This example demonstrates how to use panel to group multiple controls to the
users.

![alt](figures/panel_demo.png)

__Figure 1__ Output of panel Program

__List 1__ panel.c

```cpp
/*
** panel.c: Sample program for mGNCS Programming Guide
**      The demo application for Panel.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
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

#define     ID_PANEL_GROUP1     101
#define     ID_PANEL_GROUP2     102

#define     ID_RED1             201
#define     ID_RED2             202
#define     ID_BLUE1            301
#define     ID_BLUE2            302

// START_OF_REDGROUP
static NCS_WND_TEMPLATE _ctrl_group1[] = {
    {
        NCSCTRL_BUTTON,
        ID_RED1,
        30, 40, 80, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "RED 1",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NCSCTRL_BUTTON,
        ID_RED2,
        30, 110, 80, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "RED 2",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};
// END_OF_REDGROUP

// START_OF_BLUEGROUP
static NCS_WND_TEMPLATE _ctrl_group2[] = {
    {
        NCSCTRL_BUTTON,
        ID_BLUE1,
        30, 40, 80, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "BLUE 1",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NCSCTRL_BUTTON,
        ID_BLUE2,
        30, 110, 80, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "BLUE 2",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};
// END_OF_BLUEGROUP

// START_OF_PANEL
static NCS_WND_TEMPLATE panel_tmpl[] = {
    {
        NCSCTRL_PANEL,
        ID_PANEL_GROUP1,
        10, 10, 140, 180,
        WS_VISIBLE,
        WS_EX_NONE,
        "Red Group",
        NULL,
        NULL,
        NULL,
        _ctrl_group1,
        sizeof(_ctrl_group1)/sizeof(NCS_WND_TEMPLATE),
        0,
        0xFF0000FF,
    },
    {
        NCSCTRL_PANEL,
        ID_PANEL_GROUP2,
        160, 10, 140, 180,
        WS_VISIBLE,
        WS_EX_NONE,
        "Blue Group",
        NULL,
        NULL,
        NULL,
        _ctrl_group2,
        sizeof(_ctrl_group2)/sizeof(NCS_WND_TEMPLATE),
        0,
        0xFFFF0000,
    },
};
// END_OF_PANEL

// START_OF_HANDLERS
static BOOL mainwnd_onCreate(mWidget* self, DWORD add_data)
{
    _c(self)->addChildren(self, panel_tmpl, \
        sizeof(panel_tmpl)/sizeof(NCS_WND_TEMPLATE));
    return TRUE;
}

static void mainwnd_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}


static NCS_EVENT_HANDLER mainwnd_handlers[] = {
    {MSG_CREATE, mainwnd_onCreate},
    {MSG_CLOSE, mainwnd_onClose},
    {0, NULL}
};
// END_OF_HANDLERS

int MiniGUIMain(int argc, const char* argv[])
{
    MSG Msg;

    ncsInitialize ();

    mWidget* mainwnd = ncsCreateMainWindow (
        NCSCTRL_MAINWND, "Panel Demo",
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        1,
        0, 0, 320,240,
        HWND_DESKTOP,
        0, 0,
        NULL,
        NULL,
        mainwnd_handlers,
        0);

// START_OF_MSGLOOP
    while (GetMessage (&Msg, mainwnd->hwnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }
// END_OF_MSGLOOP

    MainWindowThreadCleanup (mainwnd->hwnd);
    ncsUninitialize ();

    return 0;
}
```
## `mCombobox`

- *Control name*: `NCSCTRL_COMBOBOX`
- *English name*: Combobox
- *Brief introduction*: An edit box and a list box are integrated. Users can
directly key text in the edit box and can select an existing item from the
options listed in the list box. Input and selection functions of users can be
well completed. Address column in general browser is a good application.

![alt](figures/combo.png)


### Style of `mCombobox`

It is inherited from the style of [mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel).

| *Style name* | *miniStudio property name* | *Explanation* |
|--------------|----------------------------|---------------|
| `NCSS_CMBOX_SIMPLE` | Type->Simple | Simple combination box |
| `NCSS_CMBOX_DROPDOWNLIST` | Type->DropDownList | Dropdown combination box |
| `NCSS_CMBOX_SORT` | Sort->TRUE | Character string automatic sorting |
| `NCSS_CMBOX_EDITNOBORDER` | `EditHasBorder->FALSE` | The edit box does not have border |
| `NCSS_CMBOX_EDITBASELINE` | `EditHasBaseLine->TRUE` | The edit box displays underlined characters |
| `NCSS_CMBOX_READONLY` | `ReadOnly` | Content displayed by the edit box is read only |
| `NCSS_CMBOX_UPPERCASE` | Case->Upper | All the display content of the edit box is converted to capital letter display |
| `NCSS_CMBOX_LOWERCASE` | Case->Lower | All the display content of the edit box is converted to lowercase letter display |
| `NCSS_CMBOX_AUTOFOCUS` | `AutoFocus->TRUE` | The control gets focus and automatically transfers to the edit box |

### Property of `mCombobox`

It is inherited from the property of
[mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel). 

| *Property name* | *miniStudio property name* | *Type* | *RW* | *Explanation* |
|-----------------|----------------------------|--------|------|---------------|
| `NCSP_COMB_DROPDOWNHEIGHT` | `DropDownHeight` | int | `RW` | Height of the dropdown list |
| `NCSP_COMB_ITEMHEIGHT` | `ItemHeight` | int | `RW` | Height of the list item |
| `NCSP_COMB_ITEMCOUNT` | `ItemCount` | int | `RO` | Number of the list items |
| `NCSP_COMB_TEXTLIMIT`| `TextLimit` | int | `RW` | Limit of the edit box |
| `NCSP_COMB_SELECT` | -- | int | `RW` | Selection items index |

### Event of `mCombobox`

It is inherited from the event of
[mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel). 

| *Event ID* | *Parameter* | *Explanation* |
|------------|-------------|---------------|
| `NCSN_CMBOX_SELCHANGE` | -- | The selected item changes |
| `NCSN_CMBOX_SETFOCUS` | -- | Get focus |
| `NCSN_CMBOX_KILLFOCUS` | -- | Lose focus |
| `NCSN_CMBOX_EDITCHANGE` | -- | Content of the edit box changes |
| `NCSN_CMBOX_DROPDOWN` | -- | Dropdown list pops up |
| `NCSN_CMBOX_CLOSEUP` | -- | Dropdown list is closed |
| `NCSN_CMBOX_SELECTOK` | -- | Select an item when the dropdown list is closed |
| `NCSN_CMBOX_SELECTCANCEL` | -- | No selection when the dropdown list is closed |

### Method of `mCombobox`

It is inherited from the method of
[mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel). 

#### `addItem`

```cpp
BOOL addItem(mCombobox *self, const char *item, DWORD addData);
```
- Parameter:<BR>
- item – add the content of selected item
- `addData` – additional data of the item
- Explanation:<BR>
Add selected items to the dropdown list of combobox
- Example:<BR>

```cpp
char *items = {
    "first item --- Chinese",
    "second item --- German",
    "third item -- English"
};
//Add three items to the dropdown list
for (i = 0; i < 3; i++)
{
    _c(combo)->addItem(combo, items[i]， 0);
}
```

#### `removeItem`

```cpp
 BOOL removeItem(mCombobox *self, int index);
```
- Parameter:<BR>
- index – index of the items to be deleted
- Explanation:<BR>
Delete certain selected item from the dropdown list of combobox
- Example:<BR>

```cpp
//Delete the first item of the dropdown list
_c(combo)->removeItem(combo, 0);
```

#### `setItem`

```cpp
BOOL setItem(mCombobox *self, int index, const char *item); 
```
- Parameter:<BR>
- index – index of the items to be modified
- Explanation:<BR>
Modify content of certain selected item in the dropdown list of combobox
- Example:<BR>

```cpp
//Modify the content of the first item in the dropdown list to "new content"
_c(combo)->setItem(combo, 0, "new content");
```

#### `getItem`

```cpp
const char* getItem(mCombobox *self, int index); 
```
- Parameter:<BR>
- index – index of the items to get
- Explanation:<BR>
Get content of certain selected item in the dropdown list of combobox
- Example:<BR>

```cpp
const char *item_1 = _c(combo)->getItem(combo, 0);
```

#### `setAddData`
```cpp
void* setAddData(mCombobox *self, int index, DWORD addData); 
```
- Parameter:<BR>
- index – index of the items to set additional data
- `addData` – information of additional data
- Explanation:<BR>
Set additional data of certain selected item in the dropdown list of combobox
- Example:<BR>

```cpp
PBITMAP pbmp;
LoadBitmap (......);
_c(combo)->setAddData(combo, 0, (DWORD)pbmp);
```

#### `getAddData`
```cpp
DWORD getAddData(mCombobox *self, int index); 
```
- Parameter:<BR>
- index – index of the items to get additional data
- Explanation:<BR>
Get additional data of certain selected item in the dropdown list of combobox
- Example:<BR>

```cpp
DWORD add = _c(combo)->getAddData(combo, 0);
```

### Renderers of `mCombobox`

They are inherited from the renderers of
[mPanel](MiniGUIProgGuidePart2Chapter07.md#mpanel). 

#### `mCombobox` Classic Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
|-----------------|----------------------------|--------|---------------------|---------------|
| `NCS_BGC_3DBODY` | `ColorBg3DBody` | `DWORD(ARGB`) | | Draw color of the dropdown button |
| `NCS_FGC_WINDOW` | `ColorFgWindow` | `DWORD(ARGB`) | | Draw color of the arrow of the dropdown button |

#### `mCombobox` Fashion Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
| `NCS_BGC_3DBODY` | `ColorBg3DBody` | `DWORD(ARGB`) | | Draw color of the dropdown button |
| `NCS_FGC_WINDOW` | `ColorFgWindow` | `DWORD(ARGB`) | | Draw color of the arrow of the dropdown button |
| `NCS_METRICS_3DBODY_ROUNDX` | `RoundX` | int | | Round corner x radius of the dropdown button |
| `NCS_METRICS_3DBODY_ROUNDY` | `RoundY` | int | | Round corner y radius of the dropdown button |
| `NCS_MODE_BGC` | `GradientMode` | int | | Drawing mode of the gradual change effect (horizontal gradual change or vertical gradual change) |

#### `mCombobox` Skin Renderer

Refer to [Appendix B](MStudioMGNCSV1dot0PGENAppB][Image Specification]] in the
Specification for the Image Resource Used by Skin Renderer
([[MStudioMGNCSV1dot0PGENAppB)). 

#### `mCombobox` Flat Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
|-----------------|----------------------------|--------|---------------------|---------------|
| `NCS_BGC_3DBODY` | `ColorBg3DBody` | `DWORD(ARGB`) | | Draw color of the dropdown button |
| `NCS_FGC_WINDOW` | `ColorFgWindow` | `DWORD(ARGB`) | | Draw color of the arrow of the dropdown button |

### Example of `mCombobox`


![alt](figures/com.png)


__List 1__ combobox.c

```cpp
/*
** combobox.c: Sample program for mGNCS Programming Guide
**      Using Combobox.
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


#define ID_BTN  201
#define ID_NAME 202
#define ID_TYPE 203
#define ID_LOCA 204

static const char *file_type[] =
{
    "All File(*.*)",
    "Text File(*.txt)",
    "Bin File(*.bin)",
};

static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    int i;

    // get combobox
    mCombobox *com = (mCombobox *)ncsGetChildObj(_this->hwnd, ID_TYPE);

    // add items
    for (i = 0; i < sizeof(file_type)/sizeof(file_type[0]); i++)
    {
        _c(com)->addItem(com, file_type[i], 0);
    }

    // set the selected item
    _c(com)->setProperty(com, NCSP_COMB_SELECT, 1);

    return TRUE;
}

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static void mymain_onPaint(mWidget *self, HDC hdc, const CLIPRGN* inv)
{
    SetBkMode (hdc, BM_TRANSPARENT);
    TextOut (hdc, 40, 10, "New File Wizard ...");
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE,  mymain_onClose},
    {MSG_PAINT,  mymain_onPaint},
    {0, NULL}
};

static void btn_onClicked(mWidget* _this, int id, int nc, HWND hCtrl)
{
    if(nc == NCSN_WIDGET_CLICKED)
    {
        PostMessage(GetParent(_this->hwnd), MSG_CLOSE, 0, 0);
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

//START_OF_INITIAL_PROPS
static NCS_PROP_ENTRY combo_props[] =
{
    { 0, 0 }
};
//END_OF_INITIAL_PROPS

//START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] =
{
    {
        NCSCTRL_STATIC,
        0,
        10, 40, 70, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "Name:",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SLEDIT,
        ID_NAME,
        85, 45, 160, 25,
        WS_VISIBLE | WS_BORDER,
        WS_EX_NONE,
        "",
        combo_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, 80, 70, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "Type:",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_COMBOBOX,
        ID_TYPE,
        85, 85, 160, 25,
        WS_VISIBLE | NCSS_CMBOX_DROPDOWNLIST,
        WS_EX_NONE,
        "",
        combo_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_STATIC,
        0,
        10, 120, 70, 30,
        WS_VISIBLE,
        WS_EX_NONE,
        "Location:",
        NULL,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_SLEDIT,
        ID_LOCA,
        85, 125, 160, 25,
        WS_VISIBLE | WS_BORDER,
        WS_EX_NONE,
        "",
        combo_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_BTN,
        50, 170, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Finish",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_BTN,
        170, 170, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Cancel",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },

};
//END_OF_TEMPLATE

static NCS_MNWND_TEMPLATE mymain_templ =
{
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 320, 240,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Combobox",
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
----

[&lt;&lt; Button and Derived Classes](MiniGUIProgGuidePart2Chapter06.md) |
[Table of Contents](README.md) |
[Container and Derived Classes &gt;&gt;](MiniGUIProgGuidePart2Chapter08.md)

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
