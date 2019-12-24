# Animation Control Class

- [Brief Introduction to Animation Control](#brief-introduction-to-animation-control)
- [mAnimate](#manimate)
   + [Style of `mAnimate`](#style-of-manimate)
   + [Property of `mAnimate`](#property-of-manimate)
   + [Event of `mAnimate`](#event-of-manimate)
   + [Renderer of `mAnimate`](#renderer-of-manimate)
   + [Method of `mAnimate`](#method-of-manimate)
   + [Programming Example of `mAnimate`](#programming-example-of-manimate)


## Brief Introduction to Animation Control

Animation control provides rich visual experience to the users through drawing
and displaying image group and GIF dynamic images. Animation control in mGNCS
is derived from animation control of MiniGUI 3.0, and based on it, support to
image group play and GIF image play control is added. At the same time, users
can control the play speed through setting image play interval.

Animate class hierarchical relationship:

- [ `mStatic` ](MiniGUIProgGuidePart2Chapter05.md#mstatic)
   * [ `mAnimate` ](MiniGUIProgGuidePart2Chapter14.md#manimate)

Control creating method
- Automatic creation: through interface designer in miniStudio, drag
corresponding animation control, select `GIF` image or image directory that
need to load in the property column, and miniStudio will automatically create
control and provides visual control configuration, at the same time, creation
codes are generated automatically.
- Manual generation: according to mGNCS control creating process, through
programming, corresponding control window class ID is imported, and control
is generated. Manual programming sets control property and event handling.

## mAnimate

- *Control window class*: `NCSCTRL_ANIMATE`
- *Control English name*: Animate
- *Brief introduction*: Animation control. Display drawn dynamic images through
loading different image processing objects on the control.
- *Schematic diagram*:

### Style of `mAnimate`

It is inherited from the style of [mStatic](MiniGUIProgGuidePart2Chapter05.md)

| *Style name* | *miniStudio property name* | *Explanation* |
|--------------|-------------------------|---------------|
| `NCSS_ANMT_AUTOLOOP` | `Loop` | Set animation play as automatic circle or not. When setting as True, the images are played in circle. When setting as False, it will stop after the images are all played. |
| `NCSS_ANMT_SCALE` | `Scale->ImageScaled` | Set the image play area as control region area, and the images can be played enlarged or reduced |
| `NCSS_ANMT_AUTOFIT` | `Scale->AutoFit` | Set the control region automatic matched as image area |
| `NCSS_ANMT_AUTOPLAY` | `Autoplay` | Set images as automatic play or not. When it is True, the images are played automatically. When it is False, it is necessary for the users to send order to control the play |

### Property of `mAnimate`

It is inherited from the property of [mStatic](MiniGUIProgGuidePart2Chapter05.md)

| *Property* | *miniStudio property name* | *Type* | *Authority* | *Explanation* |
|------------|-------------------------|--------|-------------|---------------|
| `NCSP_ANMT_GIFFILE` | `GIFFile` | String | `RW` | Name of the `GIF` image file loaded by the animation control |
| `NCSP_ANMT_DIR` | Dir | String | `RW` | Name if the directory loaded by the animation control. The control loads all the images in the directory. Image play is according to the first letter ascii code sequence of the images supported |
| `NCSP_ANMT_INTERVAL` | Interval | `int` | `RW` | Time interval between the frames when the images are played |

### Event of `mAnimate`

It is inherited from the event of [mStatic](MiniGUIProgGuidePart2Chapter05.md)

### Renderer of `mAnimate`

For the drawing of non client area, please refer to the renderer of [mStatic](MiniGUIProgGuidePart2Chapter05.md#mstatic)

### Method of `mAnimate`

#### ncsAnimateStart

```cpp
BOOL ncsAnimateStart(mAnimate* self);
```
- Parameter:
   - self -- animation control pointer that needs operation
- Explanation:
Start to play the animation control that self corresponds to. If the animation
control is being played, then return to the animation starting point to begin
playing.
- Example:

```cpp
// Play anim animation
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStart(anim);
```

#### ncsAnimatePauseResume

```cpp
BOOL ncsAnimatePauseResume(mAnimate* self);
```
- Parameter:
    - self -- animation control pointer that needs operation
- Explanation:
If the current animation is paused, this method will continue to play the
animation. If the animation is in play, this method will pause to the
animation.
- Example:

```cpp
// Pause anim animation
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStart(anim);
    ncsAnimatePauseResume(anim);
```

#### ncsAnimateStop

```cpp
BOOL ncsAnimateStop(mAnimate* self);
```

- Parameter:
   - self -- animation control pointer that needs operation
- Explanation:
Stop the animation, and reset the animation back to the first frame.
- Example:

```cpp
// Stop anim animation
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStop(anim);
```

### Programming Example of `mAnimate`

__List 1__ animation.c

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "../include/mgncs.h"
#include "../include/mrdr.h"
#define IDC_ANI 100
#define IDC_BTN1 101
#define IDC_BTN2 102
#define IDC_BTN3 103
#define IDC_ANIM 104

static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //TODO : initialize
    return TRUE;
}

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

//START_OF_PIC
static NCS_PROP_ENTRY animate_props [] = {
    { NCSP_ANMT_GIFFILE, (DWORD)"tuzi1.gif" },
    { NCSP_ANMT_INTERVAL, 6 },
    {0, 0}
};

static NCS_PROP_ENTRY animate_props_ex [] = {
    { NCSP_ANMT_DIR, (DWORD)"." },
    { NCSP_ANMT_INTERVAL, 100 },
    {0, 0}
};
//END_OF_PIC

NCS_RDR_ELEMENT btn_rdr_elements[] =
{
    { NCS_MODE_USEFLAT, 1},
    { -1, 0 }
};

static NCS_RDR_INFO btn_rdr_info[] =
{
    {"flat","flat", NULL}
};

NCS_RDR_ELEMENT animate_rdr_elements[] =
{
    { NCS_MODE_USEFLAT, 1},
    { -1, 0 }
};

static NCS_RDR_INFO animate_rdr_info[] =
{
    {"flat", "flat", NULL}
};

//START_OF_KEY_EVENT
static void btn_notify(mWidget *button, int id, int nc, DWORD add_data)
{
    mAnimate *anim = (mAnimate *)ncsGetChildObj(GetParent(button->hwnd), IDC_ANI);

    switch (id)
    {
        case IDC_BTN1 :
            ncsAnimateStart(anim);
            break;
        case IDC_BTN2 :
            ncsAnimatePauseResume(anim);
            break;
        case IDC_BTN3 :
            ncsAnimateStop(anim);
            break;
    }

}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
    {0, NULL}
};
//END_OF_KEY_EVENT

//START_OF_TMPL
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_ANIMATE,
        IDC_ANI,
        50, 50, 300, 300,
        WS_BORDER | WS_VISIBLE |NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOPLAY,
        WS_EX_NONE,
        "test",
        animate_props, //props,
        animate_rdr_info,
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_ANIMATE,
        IDC_ANIM,
        0, 230, 300, 300,
        WS_BORDER | WS_VISIBLE | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOPLAY,
        WS_EX_NONE,
        "test2",
        animate_props_ex, //props,
        animate_rdr_info,
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN1,
        450, 100, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Start",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN2,
        450, 200, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Pause",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN3,
        450, 300, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Stop",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
};
//END_OF_TMPL

static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 600, 600,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "animate Test ....",
    NULL,
    NULL,
    mymain_handlers,
    _ctrl_templ,
    sizeof(_ctrl_templ)/sizeof(NCS_WND_TEMPLATE),
    0,
    0, 0,
};

int MiniGUIMain(int argc, const char* argv[])
{
    ncsInitialize();
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect(&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);


    MainWindowThreadCleanup(mydlg->hwnd);
    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
```

- Set loading image

```cpp
static NCS_PROP_ENTRY animate_props [] = {
    { NCSP_ANMT_GIFFILE, (DWORD)"tuzi1.gif" },
    { NCSP_ANMT_INTERVAL, 6 },
    {0, 0}
};

static NCS_PROP_ENTRY animate_props_ex [] = {
    { NCSP_ANMT_DIR, (DWORD)"." },
    { NCSP_ANMT_INTERVAL, 100 },
    {0, 0}
};
```

- Set key information

```cpp
static void btn_notify(mWidget *button, int id, int nc, DWORD add_data)
{
    mAnimate *anim = (mAnimate *)ncsGetChildObj(GetParent(button->hwnd), IDC_ANI);

    switch (id)
    {
        case IDC_BTN1 :
            ncsAnimateStart(anim);
            break;
        case IDC_BTN2 :
            ncsAnimatePauseResume(anim);
            break;
        case IDC_BTN3 :
            ncsAnimateStop(anim);
            break;
    }
}

static NCS_EVENT_HANDLER btn_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_BUTTON_PUSHED, btn_notify),
    {0, NULL}
};
```

- Set display interface template

```cpp
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_ANIMATE,
        IDC_ANI,
        50, 50, 300, 300,
        WS_BORDER | WS_VISIBLE |NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOPLAY,
        WS_EX_NONE,
        "test",
        animate_props, //props,
        animate_rdr_info,
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_ANIMATE,
        IDC_ANIM,
        0, 230, 300, 300,
        WS_BORDER | WS_VISIBLE | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOPLAY,
        WS_EX_NONE,
        "test2",
        animate_props_ex, //props,
        animate_rdr_info,
        NULL, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN1,
        450, 100, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Start",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN2,
        450, 200, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Pause",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
    {
        NCSCTRL_BUTTON,
        IDC_BTN3,
        450, 300, 70, 30,
        WS_VISIBLE | NCSS_NOTIFY,
        WS_EX_NONE,
        "Stop",
        NULL,
        btn_rdr_info,
        btn_handlers,
        NULL,
        0,
        0
    },
};
```

----

[&lt;&lt; Edit Box and Derived Control Classes](MiniGUIProgGuidePart2Chapter13.md) |
[Table of Contents](README.md) |
[Other Advanced Control Classes &gt;&gt;](MiniGUIProgGuidePart2Chapter15.md)

[Release Notes for MiniGUI 3.2]: /supplementary-docs/Release-Notes-for-MiniGUI-3.2.md
[Release Notes for MiniGUI 4.0]: /supplementary-docs/Release-Notes-for-MiniGUI-4.0.md
[Showing Text in Complex or Mixed Scripts]: /supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md
[Supporting and Using Extra Input Messages]: /supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md
[Using CommLCD NEWGAL Engine and Comm IAL Engine]: /supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md
[Using Enhanced Font Interfaces]: /supplementary-docs/Using-Enhanced-Font-Interfaces.md
[Using Images and Fonts on System without File System]: /supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md
[Using SyncUpdateDC to Reduce Screen Flicker]: /supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md
[Writing DRM Engine Driver for Your GPU]: /supplementary-docs/Writing-DRM-Engine-Driver-for-Your-GPU.md
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
