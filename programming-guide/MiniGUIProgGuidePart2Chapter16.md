# Invisible Control Class

- [Brief Introduction to Invisible Control Class](#brief-introduction-to-invisible-control-class)
- [`mInvsbComp`](#minvsbcomp)
   + [Style of `mInvsbComp`](#style-of-minvsbcomp)
   + [Property of `mInvsbComp`](#property-of-minvsbcomp)
   + [Method of `mInvsbComp`](#method-of-minvsbcomp)
   + [Event of `mInvsbComp`](#event-of-minvsbcomp)
- [`mTimer`](#mtimer)
   + [Style of `mTimer`](#style-of-mtimer)
   + [Property of `mTimer`](#property-of-mtimer)
   + [Method of `mTimer`](#method-of-mtimer)
   + [Event of `mTimer`](#event-of-mtimer)
   + [Example of `mTimer`](#example-of-mtimer)


## Brief Introduction to Invisible Control Class

Invisible control refers to the components which cannot be displayed on the
window but have certain functions.

These components is encapsulation to some functional templates, guaranteeing
that they can be edited in miniStudio like control

- `mObject`
   - `mComponent`
      * `mInvsbComp`

## `mInvsbComp`

- *Control name*: None
- *English name*: Invisible Component
- *Brief introduction*: Basic class of invisible component
- *Schematic diagram*: _Foundation class, cannot be used directly_

### Style of `mInvsbComp`

It is inherited from the style of `mComponent`.

### Property of `mInvsbComp`

It is inherited from the property of `mComponent`.

### Method of `mInvsbComp`

`mInvsbComp` provides realization of the following methods:

- `setId`
- `getId`
- `setReleated`
- `getReleated`
- `getChild`

In addition, for the convenience of use of `mInvsbComp`, the following
functions are provided

- Create invisible component

```cpp
/**
 * \fn mInvsbComp * ncsCreateInvsbComp(const char* class_name, \
                         mComponent* parent, \
                         int id, NCS_PROP_ENTRY *props, \
                         NCS_EVENT_HANDLER * handlers, \
                         DWORD user_data);
 * \brief create an Invisible Component
 *
 * \param class_name  the class name of Invisible Component
 * \param parent the parent of creating Invisible Component
 * \param id  the id of Invisible Component
 * \param props the properties array of Invisible Component
 * \param handlers the event handler array of Invisible Component
 * \param user_data user data
 *
 * \return mInvsbComp * - the new created Invisible Component pointer, NULL or failed
 *
 * \sa NCS_INVSB_CREATE_INFO, ncsCreateInvsbCompIndirect
 */
mInvsbComp * ncsCreateInvsbComp(const char* class_name, \
                                     mComponent* parent, \
                                     int id, \
                                     NCS_PROP_ENTRY *props, \
                                     NCS_EVENT_HANDLER * handlers, \
                                     DWORD user_data);

/**
 * \fn mInvsbComp * ncsCreateInvsbCompIndirect(const char* class_name, \
                NCS_INVSB_CREATE_INFO *create_info);
 * \brief create an Invisible Component from creating info
 *
 * \param class_name the class name of Invisible Component
 * \param create_info the creating information pointer
 *
 * \return mInvsbComp * - the Invisible Component pointer if success, NULL or failed
 *
 * \sa NCS_INVSB_CREATE_INFO, ncsCreateInvsbComp
 */
mInvsbComp * ncsCreateInvsbCompIndirect(const char* class_name, \
                NCS_INVSB_CREATE_INFO *create_info);


```

`NCS_INVSB_CREATE_INFO` structure used by function `ncsCreateInvsbCompIndirect`
is defined as below:

```cpp
/**
 * A struct include Invisible Component Create info
 *
 * \sa ncsCreateInvsbCompIndirect
 */
typedef struct _NCS_INVSB_CREATE_INFO {
    /**
     * The parent Component
     */
    mComponent        * parent;
    /**
     * The id of component
     */
    int                 id;
    /**
     * The property of Component
     *
     * \sa NCS_PROP_ENTRY
     */
    NCS_PROP_ENTRY    * props;
    /**
     * The event handlers array
     *
     * \sa NCS_EVENT_HANDLER
     */
    NCS_EVENT_HANDLER * handlers;

    /**
     * Use defined data
     */
    DWORD               user_data;
}NCS_INVSB_CREATE_INFO;
```

Note that it is not encouraged to directly use the function to create invisible
component, and they have no advantage in handwritten codes. The advantage is
that resources provided by miniStudio can be utilized to load.

So example is omitted.

### Event of `mInvsbComp`

It is inherited from the event of `mComponent`.

## `mTimer`

- *Control name*: `NCSCTRL_TIMER`
- *English name*: Timer
- *Brief introduction*: Encapsulation to MiniGUI `SetTimerEx` and `KillTimer`

![alt](figures/mtimer.png)

Inheritance relationship:

- `mObject`
- `mComponent`
   * `mInvsbComp`
   * `mTimer`

### Style of `mTimer`

It is inherited from the style of `mInvsbComp`.

### Property of `mTimer`

It is inherited from the property of `mInvsbComp`.

| *Property ID*| *miniStudio name* | *Type* | *Authority* | *Explanation* |
|--------------|-------------------|--------|-------------|---------------|
| `NCSP_TIMER_INTERVAL` | interval | `DWORD` | `RW` | Set time interval of Timer, with 10ms as the unit. If Timer is operating, it will restart Timer |

### Method of `mTimer`

It is inherited from the method of `mInvsbComp`.

- start

```cpp
BOOL (*start)(clss *_this);
```

- Start Timer
- Return `TRUE` for start successful, `FALSE` for start failed.

- stop
```cpp
void (*stop)(clss *_this);
```
- Stop the timer in operation

- `getParent`

```cpp
HWND (*getParent)(clss *_this);
```
- Get the window with Timer

### Event of `mTimer`

It is inherited from the event of `mInvsbComp`.

| *Event notification code* | *Explanation* | *Parameter* |
|---------------------------|---------------|-------------|
| `MSG_TIMER` | Directly utilize the definition of MiniGUI | Total time amount that timer walks by, which is `lParam` value of `MSG_TIMER` |

- Note that the callback of the event is:

```cpp
BOOL (*NCS_CB_ONTIMER)(mTimer* timer, DWORD total_count);
```
- Return `TRUE` to continue Timer, `FALSE` to stop Timer
- Params
   * `DWORD total_count` - Total time amount since Timer starts

### Example of `mTimer`

The example below demonstrates using timer to show a digital clock, and the
operation effect drawing is as below:

![alt](figures/timer-show.png)

- Declare Timer uses the same structure as the control

```cpp
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_TIMER,
        100,
        10, 10, 0, 0,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL, //props,
        NULL, //rdr_info
        NULL, //timer_props, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
```

- Initialize Timer, establish a connection with Static control, and start Timer

```cpp
static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //TODO : initialize
    mTimer * timer = SAFE_CAST(mTimer,
                    _c(self)->getChild(self, 100));
    if(timer)
    {
        ncsAddEventListener((mObject*)timer,
                        (mObject*)ncsGetChildObj(self->hwnd, 101),
                        (NCS_CB_ONPIECEEVENT)update_time,
                        MSG_TIMER);
        _c(timer)->start(timer);
    }
    return TRUE;
}
```

- When `MSG_TIMER` event occurs, update the time

```cpp
static BOOL update_time(mStatic *listener,
        mTimer* sender,
        int id,
        DWORD total_count)
{
    char szText[100];
    time_t tim;
    struct tm *ptm;
    static int old_count = 0;

    time(&tim);
    ptm = localtime(&tim);

    sprintf(szText,
            "%02d:%02d:%d",
            ptm->tm_hour,
            ptm->tm_min,
            ptm->tm_sec);
    old_count = total_count;

    SetWindowText(listener->hwnd, szText);
    InvalidateRect(listener->hwnd, NULL, TRUE);

    return FALSE;
}
```

For complete code, refer to the following List.

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <mgncs/mgncs.h>
#include <time.h>

//START_UPDATE_TIME
static BOOL update_time(mStatic *listener,
        mTimer* sender,
        int id,
        DWORD total_count)
{
    char szText[100];
    time_t tim;
    struct tm *ptm;
    static int old_count = 0;

    time(&tim);
    ptm = localtime(&tim);

    sprintf(szText,
            "%02d:%02d:%d",
            ptm->tm_hour,
            ptm->tm_min,
            ptm->tm_sec);
    old_count = total_count;

    SetWindowText(listener->hwnd, szText);
    InvalidateRect(listener->hwnd, NULL, TRUE);

    return FALSE;
}
//END_UPDATE_TIME


//START_TIMER_CONNECT
static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
    //TODO : initialize
    mTimer * timer = SAFE_CAST(mTimer,
                    _c(self)->getChild(self, 100));
    if(timer)
    {
        ncsAddEventListener((mObject*)timer,
                        (mObject*)ncsGetChildObj(self->hwnd, 101),
                        (NCS_CB_ONPIECEEVENT)update_time,
                        MSG_TIMER);
        _c(timer)->start(timer);
    }
    return TRUE;
}
//END_TIMER_CONNECT

static void mymain_onClose(mWidget* self, int message)
{
    DestroyMainWindow(self->hwnd);
    PostQuitMessage(0);
}

//Controls
//START_DECLARE_TIMER
static NCS_WND_TEMPLATE _ctrl_templ[] = {
    {
        NCSCTRL_TIMER,
        100,
        10, 10, 0, 0,
        WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "",
        NULL, //props,
        NULL, //rdr_info
        NULL, //timer_props, //handlers,
        NULL, //controls
        0,
        0 //add data
    },
//END_DECLARE_TIMER
    {
        NCSCTRL_STATIC,
        101,
        10,10, 100, 30,
        WS_VISIBLE,
        0,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0
    }
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
    {MSG_CREATE, mymain_onCreate},
    {MSG_CLOSE, mymain_onClose},
    {0, NULL}
};

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
    NCSCTRL_DIALOGBOX,
    1,
    0, 0, 150, 80,
    WS_CAPTION | WS_BORDER | WS_VISIBLE,
    WS_EX_NONE,
    "Digital Clock",
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
    mDialogBox* mydlg = (mDialogBox *)ncsCreateMainWindowIndirect
                                (&mymain_templ, HWND_DESKTOP);

    _c(mydlg)->doModal(mydlg, TRUE);

    MainWindowThreadCleanup(mydlg->hwnd);
    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
```
----

[&lt;&lt; Other Advanced Control Classes](MiniGUIProgGuidePart2Chapter15.md) |
[Table of Contents](README.md) |
[Other Classes &gt;&gt;](MiniGUIProgGuidePart2Chapter17.md)

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
