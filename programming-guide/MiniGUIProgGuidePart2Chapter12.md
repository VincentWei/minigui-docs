# Property Sheet Control Class

## Brief Introduction to Property Sheet Control Class

Property Sheet control class is composed of independent property pages, and 
each property page has a tongue. We can click the tongue to switch between
different property pages. The property pages here are the page controls that 
can accommodate other controls. We usually use the method similar to
establishing dialog box, which is the method of defining the dialog box
template, to add property page to the property sheet.

The most common purpose of property sheet control class is placing interaction
content of different categories into the same dialog box by category, and
displaying different content through category switch. On the one hand, it saves
the space of dialog box, on the other hand, it makes it easier to use the
interaction interface.

The class inheritance relation of the window and its derived class is as
follows: 

- [mWidget ](MStudioMGNCSV1dot0PGP2C3#mWidget)
- [mPropSheet](MStudioMGNCSV1dot0PGP2C11#m_PropSheet)

## `mPropSheet`

- *Control name*: `NCSCTRL_PROPSHEET`
- *English name*: `PropSheet`
- *Brief introduction*: It is composed of multiple independent property pages.
Each property page has a tongue, and switching between the property pages are
carried out through the tongue.
- *Schematic diagram*: <br/>


![alt](figures/propsheet.png)

### Style of `mPropSheet`

It is inherited from the style of [`mWidget`](MStudioMGNCSV1dot0PGP2C3#mWidget).

| *Style name* | *miniStudio property name* | *Explanation* |
|--------------|----------------------------|---------------|
| `NCSS_PRPSHT_SIMPLE` | `style->Simple` | Style of controlling the tongue width of the property page: tongues of all the property pages have the same width.|
| `NCSS_PRPSHT_COMPACTTAB` | `style->Compact` | Style of controlling the tongue width of the property page: tongue width of the property page is decided by the length of the title text of the property page.|
| `NCSS_PRPSHT_SCROLLABLE` | `style->Scrollable` | Style of controlling the tongue width of the property page: tongue width of the property page is decided by the length of the title text of the property page. When there are too many property page tongues, left and right arrows will automatically appear to adjust the currently visible property page tongue.|
| `NCSS_PRPSHT_TOP` | `TabPos->Top` | Style of controlling the display direction of the property page tongue in the property sheet: property page tongue is displayed on the top of the property sheet.|
| `NCSS_PRPSHT_BOTTOM` | `TabPos->Bottom` | Style of controlling the display direction of the property page tongue in the property sheet: property page tongue is displayed on the bottom of the property sheet.|

### Property of `mPropSheet`

It is inherited from the property of [`mWidget`](MStudioMGNCSV1dot0PGP2C3#mWidget).

| *Property ID*| *miniStudio name* | *Type* | *Authority* | *Explanation* |
|--------------|-------------------|--------|-------------|---------------|
| `NCSP_PRPSHT_MINTABWIDTH` | `TabMinWidth` | int | `RW` | Minimum width of the tongue |
| `NCSP_PRPSHT_TABMARGIN` | `TabMargin` | int | `RW` | Tongue boundary value. Under normal condition, the value plus the literal width is the tongue width |
| `NCSP_PRPSHT_ACTIVEPAGE` | - | `mPage*` | `RW` | Pointer of the current active page |
| `NCSP_PRPSHT_ACTIVEPAGEIDX` | `ActivePageIndex` | int | `RW` | Index of the current active page |
| `NCSP_PRPSHT_FIRSTVIEWPAGE` | - | `mPage*` | `RO` | Pointer of the currently first visible page |
| `NCSP_PRPSHT_FIRSTVIEWPAGEIDX` | - | int | `RO` | Index of the currently first visible page |
| `NCSP_PRPSHT_PAGECOUNT` | - | int | `RO` | Current property page number |

### Event of `mPropSheet`


It is inherited from the event of [mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget).

| *Event ID* | *Parameter* | *Explanation* |
|------------|-------------|---------------|
| `NCSN_PRPSHT_ACTIVECHANGED` | -- | The active property page has changed |


### Method of `mPropSheet`

It is inherited from the method of [mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget).

#### Add property page

After creating property sheet control, property page can be added to the
property sheet through `addPage` method. `dlgTemplate` of the method is used to
transfer dialog box template, and handlers is used to transfer event callback
handling function of the property page. Prototype of the function is as below:

```cpp
mPage* addPage(mPropSheet *self, \
                              PDLGTEMPLATE dlgTemplate,  \
                              const NCS_EVENT_HANDLER* handlers);
```

As shown in the Instance program, the codes below are utilized to add multiple
property pages to the property sheet control:

```cpp
    PageSysInfo.controls = CtrlSysInfo;
    PageSysInfo.caption = "Version Info";
    PageSysInfo.dwAddData = PAGE_VERSION;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "CPU Info";
    PageSysInfo.dwAddData = PAGE_CPU;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "MEM Info";
    PageSysInfo.dwAddData = PAGE_MEMINFO;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "Partition Info";
    PageSysInfo.dwAddData = PAGE_PARTITION;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "MiniGUI Info";
    PageSysInfo.dwAddData = PAGE_MINIGUI;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);
```

Events of the property pages are handled as:

```cpp
static void mypage_onInitPage(mWidget* self, DWORD add_data)
{
    get_systeminfo ((mPage*)self);
}

static int mypage_onShowPage(mWidget* self, HWND hwnd, int show_cmd)
{
    return 1;
}

static int mypage_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam)
{
    if (wParam == IDC_REFRESH) {
        get_systeminfo ((mPage*)self);
    }

    return 0;
}

static NCS_EVENT_HANDLER mypage_handlers[] = {
    {MSG_INITPAGE, mypage_onInitPage},
    {MSG_SHOWPAGE, mypage_onShowPage},
    {MSG_SHEETCMD, mypage_onSheetCmd},
    {0 , NULL }
};
```

#### Remove the Property Page

To remove certain property page, it is only necessary to call the `removePage`
or `removePageByIndex` method of the property sheet control. It needs to be
noted that after a property page is removed, it may change the index value of
other property pages. `removePage` removes the appointed page through the class
pointer of the property page, and `removePageByIndex` removes the appointed 
page through property page index.

Prototype of the function is as below:

```cpp
BOOL removePageByIndex(mPropSheet *self, int pageIndex);
BOOL removePage(mPropSheet *self, mPage* page);
```

If you want to remove the first property page in the property sheet, you can
implement the following operation:

```cpp
_c(propsheet)->removePageByIndex(propsheet, 0);
```

#### Index Property Page

To get the index page class pointer of the appointed index, it is necessary to
call `getPageByIndex` method of property sheet control; while to get index of
certain appointed property page, it is only necessary to call `getPageIndex`
method of property sheet control. Prototype of the function is as below:

```cpp
int getPageIndex(mPropSheet *self, mPage* page);
mPage* getPageByIndex(mPropSheet *self, int pageIndex);
```

Such as get index of the appointed property page:

```cpp
mPage *page;
... ...
_c(propsheet)->getPageIndex(propsheet, page);
```

Or get the class pointer of the first property page, and then operate the
property page through the method of [mPage](MStudioMGNCSV1dot0PGP2C7#mPage)
control:

```cpp
mPage *page = _c(propsheet)->getPageByIndex(propsheet, 0);
HWND hPanel = _c(page)->getPanel(page);
... ...
```

#### Traverse Property Page

In the property sheet control, traversal find function to all the property 
pages can be realized through `getNextPage` and `getPrevPage` method.
`getNextPage` is used to traverse property pages from the appointed property
page towards the back; `getPrevPage` is used to traverse the property pages 
from the appointed property page towards the front.

```cpp
mPage* getNextPage(mPropSheet *self, mPage* page);
mPage* getPrevPage(mPropSheet *self, mPage* page);
```

For example:

```cpp
mPage *page = _c(propsheet)->getNextPage(propsheet, NULL);

while (page) {
    ... ...
    page = _c(propsheet)->getNextPage(propsheet, page);
}
```

#### Broadcast Message

Property sheet control can broadcast message to all the property pages through
`broadCastMsg` method. Content of the message is transmitted through `param1` and
`param2`. When the property sheet control receives non null value returned by any
property page after handling the broadcast message, the returned value of the
property sheet will plus one for the index value of the property page with
message broadcasting interrupted. Through this method, function operations such
as invalid input processing etc. can be realized.

```cpp
int broadCastMsg(mPropSheet *self, DWORD param1, DWORD param2);
```

### Renderer of `mPropSheet`

It is inherited from the renderer of [`mWidget`](MStudioMGNCSV1dot0PGP2C3#mWidget).

### Instance of `mPropSheet`

This Instance demonstrates how to use propsheet to display some system
information of the computer to the users, such as `CPU` type and memory size
etc.

![alt](figures/propsheet_demo.png)

##### Figure 1 Output of propsheet Program

##### List 1 propsheet.c

```cpp
/*
** propsheet.c: Sample program for mGNCS Programming Guide
**      The demo application for PropSheet.
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
#include <minigui/control.h>

#include <mgncs/mgncs.h>
// END_OF_INCS

#define PAGE_VERSION    1
#define PAGE_CPU        2
#define PAGE_MEMINFO    3
#define PAGE_PARTITION  4
#define PAGE_MINIGUI    5

#define BUF_LEN         10240
#define IDC_PROPSHEET    100
#define IDC_SYSINFO     101
#define IDC_REFRESH     102

static size_t read_sysinfo (const char* file, char* buff, size_t buf_len)
{
     size_t size;
     FILE   *fp = fopen (file, "r");

     if (fp == NULL) return 0;

     size = fread (buff, 1, buf_len, fp);

     fclose (fp);
     return size;
}

static void get_systeminfo (mPage* page)
{
    int     type;
    HWND    hwnd;
    char    buff [BUF_LEN + 1];
    size_t  size = 0;

    type = (int)GetWindowAdditionalData (page->hwnd);
    hwnd = GetDlgItem(_c(page)->getPanel(page), IDC_SYSINFO);
    buff [BUF_LEN] = 0;

    switch (type) {
    case PAGE_VERSION:
        size = read_sysinfo ("/proc/version", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_CPU:
        size = read_sysinfo ("/proc/cpuinfo", buff, BUF_LEN);
            buff [size] = 0;
        break;

    case PAGE_MEMINFO:
        size = read_sysinfo ("/proc/meminfo", buff, BUF_LEN);
            buff [size] = 0;
        break;

    case PAGE_PARTITION:
        size = read_sysinfo ("/proc/partitions", buff, BUF_LEN);
        buff [size] = 0;
        break;

    case PAGE_MINIGUI:
        size = snprintf (buff, BUF_LEN,
                    "MiniGUI version %d.%d.%d.\n"
                    "Copyright (C) 1998-2009 ~ 2019 FMSoft Technologies.\n\n"
                    "MiniGUI is a mature, rich-featured, embedded "
                    "GUI support system.\n\n"
                    "For more information, please visit\n\n"
                    "http://www.minigui.com\n",
                    MINIGUI_MAJOR_VERSION, MINIGUI_MINOR_VERSION, MINIGUI_MICRO_VERSION);
        break;
    }

    if (size) {
        SetWindowText (hwnd, buff);
    }
    GetWindowText(hwnd, buff, BUF_LEN+1);
}

// START_OF_PAGEHANDLERS
static void mypage_onInitPage(mWidget* self, DWORD add_data)
{
    get_systeminfo ((mPage*)self);
}

static int mypage_onShowPage(mWidget* self, HWND hwnd, int show_cmd)
{
    return 1;
}

static int mypage_onSheetCmd(mWidget* self, DWORD wParam, DWORD lParam)
{
    if (wParam == IDC_REFRESH) {
        get_systeminfo ((mPage*)self);
    }

    return 0;
}

static NCS_EVENT_HANDLER mypage_handlers[] = {
    {MSG_INITPAGE, mypage_onInitPage},
    {MSG_SHOWPAGE, mypage_onShowPage},
    {MSG_SHEETCMD, mypage_onSheetCmd},
    {0 , NULL }
};
// END_OF_PAGEHANDLERS

static void btn_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    mPropSheet *obj =
        (mPropSheet *)ncsGetChildObj(GetParent(self->hwnd), IDC_PROPSHEET);

    if (obj) {
        _c(obj)->broadCastMsg(obj, IDC_REFRESH, 0);
    }
}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
    {0, NULL}
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"classic","classic", NULL}
};

static NCS_WND_TEMPLATE _ctrl_tmpl[] = {
    {
        NCSCTRL_BUTTON,
        IDC_REFRESH,
        10, 240, 70, 25,
        WS_VISIBLE | WS_TABSTOP,
        WS_EX_NONE,
        "Refresh",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDCANCEL,
        330, 240, 70, 25,
        WS_VISIBLE | WS_TABSTOP,
        WS_EX_NONE,
        "Close",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    },
};

static DLGTEMPLATE PageSysInfo =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 0, 0,
    "",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA CtrlSysInfo [] =
{
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_LEFT,
        10, 10, 370, 180,
        IDC_SYSINFO,
        "test",
        0
    }
};

static NCS_RDR_INFO prop_rdr_info[] =
{
    {"classic", "classic", NULL},
};

static int init_propsheet (mDialogBox* self)
{
// START_OF_CREATEPRPSHT
    mPropSheet *propsheet =
        (mPropSheet*) ncsCreateWindow (NCSCTRL_PROPSHEET,
                       "", WS_VISIBLE | NCSS_PRPSHT_SCROLLABLE, WS_EX_NONE,
                       IDC_PROPSHEET,
                       10, 10, 390, 225, self->hwnd,
                       NULL, prop_rdr_info, NULL, 0);
// END_OF_CREATEPRPSHT

    if (!propsheet) {
        fprintf (stderr, "Error> Create propsheet failure.\n");
        return 1;
    }

// START_OF_ADDPAGES
    PageSysInfo.controls = CtrlSysInfo;
    PageSysInfo.caption = "Version Info";
    PageSysInfo.dwAddData = PAGE_VERSION;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "CPU Info";
    PageSysInfo.dwAddData = PAGE_CPU;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "MEM Info";
    PageSysInfo.dwAddData = PAGE_MEMINFO;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "Partition Info";
    PageSysInfo.dwAddData = PAGE_PARTITION;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);

    PageSysInfo.caption = "MiniGUI Info";
    PageSysInfo.dwAddData = PAGE_MINIGUI;
    _c(propsheet)->addPage(propsheet, &PageSysInfo, mypage_handlers);
// END_OF_ADDPAGES

    return 0;
}

static NCS_MNWND_TEMPLATE mymain_tmpl = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 420, 305,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "PropSheet Demo",
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
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                                (&mymain_tmpl, HWND_DESKTOP);

    init_propsheet(mydlg);
    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);
    ncsUninitialize();
    return 0;
}
```
----

[&lt;&lt; Progress Bar Control Class](MiniGUIProgGuidePart2Chapter11.md) |
[Table of Contents](README.md) |
[Edit Box and Derived Classes &gt;&gt;](MiniGUIProgGuidePart2Chapter13.md)

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
