# Progress Bar Control Class

## Brief Introduction to Progress Bar Control

Progress bar control is an essential control in GUI system, which can visually
show progress of an item and is often used in file copying, software
installation and file transmission. Progress bar control in mGNCS is
strengthened and reconstructed based on the built-in progress bar control in
MiniGUI 3.0, and setting of renderer is added, making it easier to use and more
splendid.

- Class hierarchical relation of progress bar
- [ `mWidget` ](MStudioMGNCSV1dot0PGP2C3#mWidget)
   * [ `mProgressBar` ](MStudioMGNCSV1dot0PGP2C10#m_ProgressBar)

## `mProgressBar`

- *Control window class*: `NCSCTRL_PROGRESSBAR`
- *Control English name*: `ProgressBar`
- *Brief introduction*: Used to show progress, often used in file copying,
software installation and file transmission.
- *Schematic diagram*:

![alt](figures/prog.png)

### Style of `mProgressBar`

It is inherited from the style of [mWidget](MStudioMGNCSV1dot0PGP2C3)

| *Style ID* | *miniStudio property* | *Explanation* | *Comments* |
|------------|-----------------------|---------------|------------|
| `NCSS_PRGBAR_HORIZONTAL` | -- | In miniStudio, the two styles are divided into two controls to use, respectively corresponding to| Horz `ProgressBar` |
| `NCSS_PRGBAR_VERTICAL` | -- | ^ | Vert `ProgressBar` |
| `NCSS_PRGBAR_BLOCKS` | `BlockChunk->TRUE` | Block progress | <img src="figures/prog_block.png" alt="prog_block.png" width='111' height='30' /> |
| `NCSS_PRGBAR_SMOOTH` | `BlockChunk->FALSE` | Smooth progress, relative to the above block progress | <img src="figures/prog_smooth.png" alt="prog_smooth.png" width='111' height='30' /> |
| `NCSS_PRGBAR_SHOWPERCENT` | `ShowPercent` | Display the current progress value (percentage)| <img src="figures/prog_per.png" alt="prog_per.png" width='111' height='30' /> |

### Property of `mProgressBar`

It is inherited from the property of [mWidget](MStudioMGNCSV1dot0PGP2C3)

| *Property name* |*miniStudio property name* | *Type* | *RW* | *Explanation* |
|-----------------|---------------------------|--------|------|---------------|
| `NCSP_PROG_MAXPOS` | `MaxPos` | int | `RW` | Maximum value of the progress range |
| `NCSP_PROG_MINPOS` | `MinPos` | int | `RW` | Minimum value of the progress range |
| `NCSP_PROG_CURPOS` | `CurPos` | int | `RW` | Current progress value |
| `NCSP_PROG_LINESTEP` | `LineStep` | int | `RW` | Step length |

### Event of `mProgressBar`

It is inherited from the event of [mWidget](MStudioMGNCSV1dot0PGP2C3).

*The control class does not have newly added event*

### Method of `mProgressBar`

It is inherited from the method of [mWidget](MStudioMGNCSV1dot0PGP2C3)

#### increase

```cpp
int increase (mProgressBar *self, int delta);
```

- Parameter:
   - self ：control object pointer
   - delta ：increase amplitude
- Explanation: users can use the function to control increase of the progress
value; delta is used to appoint the increase amount, which is generally used to
control the increase effect of non even speed
- Example:

```cpp
_c(pb)->increase (pb, 5);    //The progress value increases 5
```

#### `stepIncrease`

```cpp
int stepIncrease (mProgressBar *_this);
```
- Parameter:
  - self ：control object pointer
- Explanation: the function can increase the progress value by step; calling
once, a step length value is increased, and even-speed increase effect can be
realized; setting of step length value is completed through corresponding
properties
- Example:

```cpp
// Set step length of ProgressBar
_c(pb)->setProperty(pb, NCSP_PROG_LINESTEP, 5);
......
_c(pb)->stepIncrease (pb);
```

### Renderer of `mProgressBar`

#### Classic Renderer

It is inherited from the classic renderer of [mWidget](MStudioMGNCSV1dot0PGP2C3).

| *Property name* | *miniStudio property* | *Type* | *Schematic diagram* | *Explanation* |
|-----------------|-----------------------|--------|---------------------|---------------|
| `NCS_BGC_HILIGHT_ITEM` | `ChunkColor` | `DWORD（ARGB`） | <img src="figures/classic_prog.png" alt="classic_prog.png"/> | Color of chunk part of the progress bar, and this renderer uses the color of highlight item to draw |

#### Fashion Renderer

It is inherited from the fashion renderer of [mWidget](MStudioMGNCSV1dot0PGP2C3).

| *Property name* |*miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
|-----------------|---------------------------|--------|---------------------|---------------|
| `NCS_BGC_PRGBAR_CHUNK` | `ChunkColor` | `DWORD（ARGB`） | <img src="figures/fsh_prog.png" alt="fsh_prog.png" /> | Foundation color of chunk part of the progress bar, and the renderer will lighten or darken according to this color to draw progress bar of gradual change effect |

#### Flat Renderer

It is inherited from flat renderer of [mWidget](MStudioMGNCSV1dot0PGP2C3).

| *Property name* |*miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
|-----------------|---------------------------|--------|---------------------|---------------|
| `NCS_FGC_WINDOW` | `ChunkColor` | `DWORD（ARGB`） | <img src="figures/flat_prog.png" alt="flat_prog.png" /> | Color of chunk part of the progress bar, here window foreground color is used |

#### Skin Renderer

Refer to [Specification for Image Resource Used by Skin Renderer](MStudioMGNCSV1dot0PGAppB#m_ProgressBar)

### Instance of `mProgressBar`

- `ProgressBar` Example code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>

#define ID_BTN  101
#define ID_PROG 200

static BOOL mymain_onCreate (mWidget* _this, DWORD add_data)
{
    SetTimer (_this->hwnd, 100, 20);
    return TRUE;
}

static void mymain_onClose (mWidget* _this, int message)
{
    DestroyMainWindow (_this->hwnd);
    PostQuitMessage (_this->hwnd);
}

static void mymain_onTimer (mWidget *_this, int id, DWORD count)
{
//START_OF_SET_PROPERTY
    static int pb_pos = 0;

    mProgressBar *pb = (mProgressBar*)ncsGetChildObj (_this->hwnd, ID_PROG);
    if (pb)
    {
        pb_pos++;
        _c(pb)->setProperty(pb, NCSP_PROG_CURPOS, pb_pos);

        if (pb_pos == _c(pb)->getProperty(pb, NCSP_PROG_MAXPOS))
        {
            DestroyMainWindow (_this->hwnd);
            PostQuitMessage (_this->hwnd);
        }
    }
//END_OF_SET_PROPERTY
}

static void mymain_onPaint(mWidget *self, HDC hdc, const CLIPRGN* inv)
{
    SetBkMode (hdc, BM_TRANSPARENT);
    TextOut (hdc, 10, 10, "Installing ......");
}

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE,  mymain_onClose},
    {MSG_PAINT,  mymain_onPaint},
    {MSG_TIMER,  mymain_onTimer},
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
static NCS_PROP_ENTRY progress_props[] =
{
    {NCSP_PROG_MAXPOS, 100},
    {NCSP_PROG_MINPOS, 0  },
    {NCSP_PROG_LINESTEP, 1},
    {NCSP_PROG_CURPOS, 0  },
    { 0, 0 }
};
//END_OF_INITIAL_PROPS

//START_OF_TEMPLATE
static NCS_WND_TEMPLATE _ctrl_templ[] =
{
    {
        NCSCTRL_PROGRESSBAR,
        ID_PROG,
        10, 33, 290, 25,
        WS_BORDER | WS_VISIBLE | NCSS_PRGBAR_SHOWPERCENT,
        WS_EX_NONE,
        "",
        progress_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_BTN,
        120, 70, 80, 25,
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
    0, 0, 320, 130,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Progressbar",
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

- `ProgressBar` template

```cpp
static NCS_WND_TEMPLATE _ctrl_templ[] =
{
    {
        NCSCTRL_PROGRESSBAR,
        ID_PROG,
        10, 33, 290, 25,
        WS_BORDER | WS_VISIBLE | NCSS_PRGBAR_SHOWPERCENT,
        WS_EX_NONE,
        "",
        progress_props,
        NULL,
        NULL, NULL, 0, 0
    },
    {
        NCSCTRL_BUTTON,
        ID_BTN,
        120, 70, 80, 25,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Cancel",
        NULL,
        btn_rdr_info,
        btn_handlers, NULL, 0, 0
    },
};
```

- Initialize the property of `ProgressBar`

```cpp
static NCS_PROP_ENTRY progress_props[] =
{
    {NCSP_PROG_MAXPOS, 100},
    {NCSP_PROG_MINPOS, 0  },
    {NCSP_PROG_LINESTEP, 1},
    {NCSP_PROG_CURPOS, 0  },
    { 0, 0 }
};
```

- In Timer message, change the property value of `ProgressBar`

```cpp
    static int pb_pos = 0;

    mProgressBar *pb = (mProgressBar*)ncsGetChildObj (_this->hwnd, ID_PROG);
    if (pb)
    {
        pb_pos++;
        _c(pb)->setProperty(pb, NCSP_PROG_CURPOS, pb_pos);

        if (pb_pos == _c(pb)->getProperty(pb, NCSP_PROG_MAXPOS))
        {
            DestroyMainWindow (_this->hwnd);
            PostQuitMessage (_this->hwnd);
        }
    }
```

----

[&lt;&lt; Spinner Control Class](MiniGUIProgGuidePart2Chapter10.md) |
[Table of Contents](README.md) |
[Property Sheet Control Class &gt;&gt;](MiniGUIProgGuidePart2Chapter12.md)

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
