# mGNCS4Touch Programming


mGNCS4Touch component provides some new controls, which are compliant to new
control `API` spec of mGNCS, for devices with a touch screen.

Supports common touch-screen operations, like quickly sliding the
screen up and down, and has scroll rebound effect, and supports accelerated
sliding, if the faster the finger slides, the farther the screen is
slide. when the finger has been released, The screen will slowly slow down 
until it
stops.

Currently supported controls can be divided into two categories, one is the
basic controls: such as the switch button, Slider bar, etc, and the other is
a complex custom piece control: such as `mTableViewPiece`. These controls are
based on
the new control of the mGNCS structure, so the same inherited the important
idea in mGNCS: assemble complex controls with some simple pieces.

Here are some simple examples of how to use controls and pieces.

## Basic

### header file

you should first include the mGNCS4Touch head file when you use it as follow:

```cpp
#include "mgncs4touch.h"
```

### config file

if you need an different renderer, you can change follow config:
- fashion renderer config.

```cpp

#define MGNCS4TOUCH_ETCFILE "mgncs4touch.cfg"

roundrect_radius=3
bgc_block=0xFFDBDBDB
fgc_swb_on=0xFFDDDDDD
bgc_swb_on=0xFFFFB958
fgc_swb_off=0xFF000000
bgc_swb_off=0xFFFFFFFF
bgc_ntb_hitem=0xFFFFB958
bgc_ntb_ditem=0xFFFFFFFF
bgc_ntb_block=0xFFDBDBDB
bgc_bnb_button=0xFFADA9AF
fgc_bnb_button=0xFFCFD089
fgc_bnb_text=0xFF9F7431
fgc_inb_text=0xFF9F7431
bgc_pck_main=0xFF808080
bgc_pck_picker=0xFFFFFFFD
fgc_pck_picker=0xFF000001
bgc_pck_select=0xFFE5C177
fgc_pck_disable=0xFFA0A0A0
bgc_itb=0xFFE7E7E7
bgc_itb_light=0xFFE2B956
fgc_itb_tick=0XFF9F7431
fgc_itb_tick_light=0xFFFFFFFF
fgc_itb_angle=0XFF9F7431
fgc_itb_angle_light=0xFFFFFFFF
fgc_itb_ltext=0XFF000000
fgc_itb_ltext_light=0xFFFFFFFF
fgc_itb_rtext=0XFFE2B956
fgc_itb_rtext_light=0xFFFFFFFF

```

| *config key* || *Property id* *Description* |
| `roundrect_radius` | `NCS4TOUCH_RRECT_RADIUS` | round rect raidus size|
| `bgc_block` | `NCS4TOUCH_BGC_BLOCK` | background color, switch button now|
| `fgc_swb_on` | `NCS4TOUCH_FGC_SWBON` | foreground color of switch button on staus|
| `bgc_swb_on` | `NCS4TOUCH_BGC_SWBON` | background color of switch button on status|
| `fgc_swb_off` | `NCS4TOUCH_FGC_SWBOFF` | foreground color of switch button off staus|
| `bgc_swb_off` | `NCS4TOUCH_BGC_SWBOFF` | background color of switch button off status|
| `bgc_ntb_hitem` | `NCS4TOUCH_BGC_NTB_HITEM` | background color of new trackbar highlight area|
| `bgc_ntb_ditem` | `NCS4TOUCH_BGC_NTB_DITEM` | background color of new trackbar disable area|
| `bgc_ntb_block` | `NCS4TOUCH_BGC_NTB_BLOCK` | background color of new trackbar thumb area|
| `bgc_bnb_button` | `NCS4TOUCH_BGC_BNB_BUTTON` | background color of btnnavbar button|
| `fgc_bnb_button` | `NCS4TOUCH_FGC_BNB_BUTTON` | foreground color of btnnavbar button|
| `fgc_bnb_text` | `NCS4TOUCH_FGC_BNB_TEXT` | text color of btnnavbar title|
| `fgc_inb_text` | `NCS4TOUCH_FGC_INB_TEXT` | text color of itemnavbar title|
| `bgc_pck_main` | `NCS4TOUCH_BGC_PCK_MAIN` | set picker background main color|
| `bgc_pck_picker` | `NCS4TOUCH_BGC_PCK_PICKER` | set picker background picker area background|
| `fgc_pck_picker` | `NCS4TOUCH_FGC_PCK_PICKER` | set picker foreground picker area item color|
| `bgc_pck_select` | `NCS4TOUCH_BGC_PCK_SELECT` | set picker background picker item select color|
| `fgc_pck_disable` | `NCS4TOUCH_FGC_PCK_DISABLE` | set picker foreground picker item disable color|
| `bgc_itb` | `NCS4TOUCH_BGC_ITB` | set itemnavbar background item color|
| `bgc_itb_light` | `NCS4TOUCH_BGC_ITB_LIGHT` | set itemnavbar hit hightlight background item color|
| `fgc_itb_tick` | `NCS4TOUCH_FGC_ITB_TICK` | set itemnavbar foreground tick color|
| `fgc_itb_tick_light` | `NCS4TOUCH_FGC_ITB_TICK_LIGHT` | the right button is not displayed the shape|
| `fgc_itb_angle` | `NCS4TOUCH_FGC_ITB_ANGLE` | the left button is a rounded rectangular shape|
| `fgc_itb_angle_light` | `NCS4TOUCH_FGC_ITB_ANGLE_LIGHT`| the left button is not displayed the shape|
| `fgc_itb_ltext` | `NCS4TOUCH_FGC_ITB_LTEXT` | set itembar foreground left label text color|
| `fgc_itb_ltext_light` | `NCS4TOUCH_FGC_ITB_LTEXT_LIGHT`| set itembar foreground left label text color when select.|
| `fgc_itb_rtext` | `NCS4TOUCH_FGC_ITB_RTEXT` | set itembar foreground right label color|
| `fgc_itb_rtext_light` | `NCS4TOUCH_FGC_ITB_RTEXT_LIGHT` |set itembar foreground right label text color when select|


### init/uninit

init/uninit should be called.

```cpp
    ncs4TouchInitialize();
    ncsUninitialize();
```


### setProperty/getProperty


if you want to change or get property of control or piece, you can try to
follow api:


```cpp
/* define */
        BOOL (*setProperty)(clss *self, int id, DWORD value); \
        DWORD (*getProperty)(clss *self, int id); \

...

/* call it */
        _c(self)->setProperty(tl5, NCSP_BNB_MARGIN, 6);
...
        int cur = _c(trackbar)->getProperty(trackbar, NCSP_SLIDER_CURPOS);

```

### Sample entry

base require in the `MiniGUIMain` entry:
- init/uninit mGNCS.
- init/uninit mGNCS4Touch.
- init/uninit mGEff.
- register your custom piece, you can use `MGNCS_INIT_CLASS`.
- `onCreate/onClose` of main window.
- mouse event, if you need touch event, you can use default
`SpeedMeterMessageHandler`, other you can deal it yourself.

```cpp
...
static NCS_EVENT_HANDLER mymain_handlers [] = {
    {MSG_CREATE, mymain_onCreate },
    {MSG_CLOSE, mymain_onClose },
    {MSG_LBUTTONDOWN, SpeedMeterMessageHandler },
    {MSG_LBUTTONUP, SpeedMeterMessageHandler },
    {MSG_MOUSEMOVE, SpeedMeterMessageHandler },
    {0, NULL}
};

int MiniGUIMain(int argc, const char *argv[]) {
...
    ncsInitialize();
    ncs4TouchInitialize();

    MGNCS_INIT_CLASS(mSimpleTableView);

    mymain = ncsCreateMainWindow(NCSCTRL_MAINWND, "mSimpleTableViewPiece test",
            WS_CAPTION | WS_BORDER | WS_VISIBLE,
            WS_EX_AUTOSECONDARYDC,
            1,
            //0, 0, g_rcScr.right,g_rcScr.bottom,
            0, 0, 320 * 2 + 100, 580,
            HWND_DESKTOP,
            0, 0,
            NULL,
            NULL,
            mymain_handlers,
            0);

    mGEffInit();

    while(GetMessage(&Msg, mymain->hwnd)) {   
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }   

    mGEffDeinit();

    ncs4TouchUninitialize();
    ncsUninitialize();

    return 0;
}
```


`BTW`: mGNCS4Touch also need mGEff and mGPlus, mGNCS, MiniGUI, so you should
include these component head files.

### control

you can try to create mGNCS4Touch control as follow two way:

#### create with `ncsCreateMainWindowIndirect`

```cpp
//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
        {
                NCSCTRL_TIMEPICKER,
                ID_TPICKER,
                10, 20, 240, 200,
                WS_VISIBLE | NCSS_TPCK_24H | NCSS_NOTIFY,
                WS_EX_NONE,
                "timepicker",
                _props,
                &rdr_info,
                multi_handlers, //handlers,
                0, //controls
                0,
                0 //add data
        }
}

//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
        NCSCTRL_MAINWND,
        1,
        264, 60, 272, 480,
        WS_CAPTION | WS_BORDER | WS_VISIBLE,
        WS_EX_NONE,
        "mTimePicker Test ...",
        NULL,
        NULL,
        mymain_handlers,
        _ctrl_templ,
        sizeof(_ctrl_templ) / sizeof(NCS_WND_TEMPLATE),
        0,
        0,
        0,
};

{
...
        mDialogBox* mydlg = (mDialogBox*)ncsCreateMainWindowIndirect(&mymain_templ, HWND_DESKTOP);
        _c(mydlg)->doModal(mydlg, TRUE);
...
}
```

#### create with `ncsCreateWindow`.

just use `ncsCreateWindow` and give your control name.

```cpp
{
...
        mContainerCtrl* ctnr =
(mContainerCtrl*)ncsCreateWindow(NCSCTRL_CONTAINERCTRL,
                "ContainerCtrl",
                WS_VISIBLE, 0, 0,
                0, 0, 100, 100,
                self->hwnd,
                NULL, NULL, NULL, 0);
...
}
```

### pieces

#### piece register

init piece class: each piece should be init first, use `MGNCS_INIT_CLASS`,
if no init, it will be crash when you using it. the internal pieces that
provided by mGNCS4Touch will be init when call ncs4TouchInitialize(), but the
piece 
that custom by user should be call `MGNCS_INIT_CLASS` directly. else it will be
crash when you use the piece.

```cpp
/* mSimpleTableView is an custom piece. */
    MGNCS_INIT_CLASS(mSimpleTableView);
```

#### create Piece

you can use two method to create an piece, it is provided by mGNCS:

- `NEWPIECE`: just give your piece class name.
- `NEWPIECEEX`: piece class name and an private addtional data.

```cpp
    mPanelPiece* panel = NEWPIECE(mPanelPiece);
...
    mPanelPiece* panel = NEWPIECEEX(mPanelPiece, 0);
```


#### add piece to window

piece is not an independent element, it should conect with an ncs window, so
you can do it as follow:
- use `ncsCreateWindow` to create `NCSCTRL_CONTAINERCTRL` control.
- use `setBody` to set piece to control.

Then the user can see your piece.

```cpp
static BOOL mymain_onCreate(mMainWnd* self, DWORD dwAddData )
{
...
    mContainerCtrl *ctnr;
    mHScrollViewPiece *view;

    ctnr = (mContainerCtrl*)ncsCreateWindow(NCSCTRL_CONTAINERCTRL,
            "ContainerCtrl",
            WS_VISIBLE, 0, 0,
            0, 10, RECTW(rc), RECTH(rc)-10*2,
            self->hwnd,
            NULL, NULL, NULL, 0);

    view = NEWPIECE(mHScrollViewPiece);
    _c(ctnr)->setBody(ctnr, (mHotPiece*)view);
...
}
```

#### piece assemble

mGNCS and mGNCS4Touch have provided some standard simple piece, like
static/text/image pieces, you can use these simple piece to assemble your own
view layout.

The `mPanelPiece` is an container piece, you can add any piece to it, also an
other panel piece.

- `addContent:add` piece to an `mPanlePiece`.

```cpp
static BOOL mymain_onCreate(mMainWnd* self, DWORD dwAddData )
{
...
    content = (mPanelPiece*)NEWPIECE(mPanelPiece);
    /* add 18 imagePiece */
    for (i = 0; i < 18; i++) {
        mHotPiece *imagePiece = (mHotPiece*)NEWPIECE(mImagePiece);
        mHotPiece *labelPiece = (mHotPiece*)NEWPIECE(mLabelPiece);
        _c(content)->addContent (content, imagePiece, 15 + (bmp[i % 3].bmWidth
+ 15) * i, 10);
        _c(content)->addContent (content, labelPiece, 15 + (bmp[i % 3].bmWidth
+ 15) * i, bmp[i % 3].bmHeight + 15);
    }
...
}
```


## mWidget control

Follow controls are all base on mGNCS `mWidget`, it is an base control for
mGNCS, you can create these controls and add it to an MiniGUI main window,
this is not different with pieces.


### NCS4TOUCH_RENDERER

mGNCS4Touch have provide an new renderer for touch screen, you can use
`ncsSetElement/ncsGetElement` to read/write it.

This render have some follow elements, you can change it by yourself, if you
need change the default value, you need change it in the mgncs4touch.cfg file.

| *Property ID* | *Type* | *Permission* | *Description* |*Unit* |
| `NCS4TOUCH_RRECT_RADIUS` | int | R | set `mItemBar` round rect radious.|pixel |
| `NCS4TOUCH_BGC_BLOCK` | int | R | get control background color. |pixel|
| `NCS4TOUCH_FGC_SWBON` | int | R | set switchbutton foreground color for on status| |
| `NCS4TOUCH_BGC_SWBON` | int | R | set switchbutton background color for on status| |
| `NCS4TOUCH_FGC_SWBOFF` | int | R | set switchbutton forground color for off status| |
| `NCS4TOUCH_BGC_SWBOFF` | int | R | set swithbutton background color for off status| |
| `NCS4TOUCH_BGC_NTB_HITEM` | int | R | set newtrackbar left area color. | |
| `NCS4TOUCH_BGC_NTB_DITEM` | int | R | set newtrackbar right area color. |
| `NCS4TOUCH_BGC_NTB_BLOCK` | int | R | set newtrackbar thumb background color.| |
| `NCS4TOUCH_BGC_BNB_BUTTON` | int | R | set btnnavbar background color| |
| `NCS4TOUCH_FGC_BNB_BUTTON` | int | R | set btnnavbar foreground color| |
| `NCS4TOUCH_FGC_BNB_TEXT` | int | R | set btnnavbar label text color| |
| `NCS4TOUCH_FGC_INB_TEXT` | int | R | set imagenavbar label text color. ||
| `NCS4TOUCH_BGC_PCK_MAIN` | int | R | set picker background main color| |
| `NCS4TOUCH_BGC_PCK_PICKER` | int | R | set picker background picker area background| |
| `NCS4TOUCH_FGC_PCK_PICKER` | int | R | set picker foreground picker area item color.| |
| `NCS4TOUCH_BGC_PCK_SELECT` | int | R | set picker background picker item select color| |
| `NCS4TOUCH_FGC_PCK_DISABLE` | int | R | set picker foreground picker item disable color. |
| `NCS4TOUCH_BGC_ITB` | int | R | set itemnavbar background item color| |
| `NCS4TOUCH_BGC_ITB_LIGHT` | int | R | set itemnavbar hit hightlight background item color| |
| `NCS4TOUCH_FGC_ITB_TICK` | int | R | set itemnavbar foreground tick color.| |
| `NCS4TOUCH_FGC_ITB_TICK_LIGHT` | int | R | the right button is not displayed the shape| |
| `NCS4TOUCH_FGC_ITB_ANGLE` | int | R | the left button is a rounded rectangular shape. |
| `NCS4TOUCH_FGC_ITB_ANGLE_LIGHT`| int | R | the left button is not displayed the shape| |
| `NCS4TOUCH_FGC_ITB_LTEXT` | int | R | set itembar foreground left label text color| |
| `NCS4TOUCH_FGC_ITB_LTEXT_LIGHT`| int | R | set itembar foreground left label text color when select.| |
| `NCS4TOUCH_FGC_ITB_RTEXT` | int | R | set itembar foreground right label color| |
| `NCS4TOUCH_FGC_ITB_RTEXT_LIGHT`| int | R | set itembar foreground right label text color when select. | |


### mSwithButton
- <b>Control Window Class</b>: `NCSCTRL_SWBUTTON`
- <b>Control English name</b>: switchbutton
- *Introduction*: This control provied an switch button like `iOS`, it has two
status: on or off, it has supuport an switch status animation.

#### control name

```cpp
#define NCSCTRL_BTNNAVBAR          NCSCLASSNAME("switchbutton")
```

#### property

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSP_SWB_STATUS`| - | int | `RW` | switch status | `NCS_SWB_OFF/NCS_SWB_ON` |



<img align="CENTER" alt="mgncs4touch-mswitchbutton.png"
src="%ATTACHURLPATH%/mgncs4touch-mswitchbutton.png" />

`mSwitchButton` control

### mBtnNavBar

- <b>Control Window Class</b>: `NCSCTRL_BTNNAVBAR`
- <b>Control English name</b>: btnnavbar
- *Introduction*: This control provied an navigate button like `iOS`.

#### control name

```cpp
#define NCSCTRL_BTNNAVBAR          NCSCLASSNAME("btnnavbar")
```

#### style

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSS_BNB_LRECT`| - | int | R | the left button is on behalf of the triangular shape of the left| |
| `NCSS_BNB_LOPT` | - | int | R | the left button is a rounded rectangular shape. |
| `NCSS_BNB_LNONE`| - | int | R | the left button is not displayed the shape| |
| `NCSS_BNB_RRECT`| - | int | R | the right button is on behalf of the triangular shape of the right| |
| `NCSS_BNB_ROPT` | - | int | R | the right button is a rounded rectangular shape.| |
| `NCSS_BNB_RNONE`| - | int | R | the right button is not displayed the shape| |


#### property

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSP_BNB_LSTRING`| - | int | `RW` | set the string on the left button | |
| `NCSP_BNB_RSTRING`| - | int | `RW` | set the string on the rightbutton| |
| `NCSP_BNB_FONT` | - | int | `RW` | set the font size on the navigation bar | |
| `NCSP_BNB_MARGIN` | - | int | `RW` | Left and right ends of the blank reserved for control| |
| `NCSP_BNB_LEFT_W` | - | int | `RW` | The width of the left button.| |
| `NCSP_BNB_RIGHT_W`| - | int | `RW` | The width of the right button| |
| `NCSP_BNB_BTN_H` | - | int | `RW` | set Left and right buttons of the high| |


### mNewTrackBar

- <b>Control Window Class</b>: `NCSCTRL_NEWTRACKBAR`
- <b>Control English name</b>: newtrackbar
- *Introduction*: new style track bar, it is base on mGNCS `mTrackbar`, you
can set `NCS4TOUCH_RENDERER` to it, other property are all same with 
`mTrackbar`. 

#### control name

```cpp
#define NCSCTRL_BTNNAVBAR          NCSCLASSNAME("newtrackbar")
```

#### property

no new property, it include all `mTrackBar` property.

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSP_TRKBAR_MAXPOS` | - | int | `RW` | The value of the maximum position. |Pixel |
| `NCSP_TRKBAR_MINPOS` | - | int | `RW` | The value of the minimum position.|Pixel |
| `NCSP_TRKBAR_CURPOS` | - | int | `RW` | The value of the current position.|Pixel |
| `NCSP_TRKBAR_LINESTEP`| - | int | `RW` | The line step length|Pixel|
| `NCSP_TRKBAR_PAGESTEP`| - | int | `RW` | The page step length|Pixel|


<img align="CENTER" alt="mgncs4touch-mtrackbar.png"
src="%ATTACHURLPATH%/mgncs4touch-mtrackbar.png" />

`mNewTrackBar` control

### mItemBar

- <b>Control Window Class</b>: `NCSCTRL_ITEMBAR`
- <b>Control English name</b>: newtrackbar
- *Introduction*: it is an base item bar, you can use it to implement an
setting ui like `iOS`.

#### control name

```cpp
#define NCSCTRL_BTNNAVBAR          NCSCLASSNAME("itembar")
```

#### style

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSS_ITEMBAR_CHECKABLE`| - | int | R | Check whether there is support | |
| `NCSS_ITEMBAR_HASCHILD`| - | int | R | Whether child controls identified. | |

#### property

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |*Unit* |
| `NCSP_ITEMBAR_CHECKED`| - | int | `RW` | set checked status | `mItemBarStyle`|
| `NCSP_ITEMBAR_IMG`| - | int | `RW` | set image icon|bitmap |
| `NCSP_ITEMBAR_MARGIN`| - | int | `RW` | set margin |pixel |



<img align="CENTER" alt="mgncs4touch-mitembar.png"
src="%ATTACHURLPATH%/mgncs4touch-mitembar.png" />

`mItemBar` control


### mIconFlow
- <b>Control Window Class</b>: `NCSCTRL_ICONFLOW`
- <b>Control English name</b>: `IconFlow`
- *Introduction*: Animated wheel controls, a series of user-supplied options to
browse as icons,
the user can select or scroll through the keyboard and mouse operations.

#### control name

```cpp
#define NCSCTRL_ICONFLOW NCSCLASSNAME("iconflow")
```

#### property

Inherited from
[Properties](http://wiki.minigui.com/bin/view/Products/MStudioMGNCSV1dot0PGP2C14#m_ItemView)
| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NCSP_ICONFLOW_DEFITEMWIDTH` | - | int | `RW` | List Item Width | Pixel |
| `NCSP_ICONFLOW_DEFITEMHEIGHT` | - | int | `RW` | List Item Height | Pixels |
| `NCSP_ICONFLOW_BKGNDPIECE` | - | `mHotPiece*` | `RW` | Background piece | - |
| `NCSP_ICONFLOW_SPAN` | - | unsigned | `RW` | Icon Spacing | Pixel |
| `NCSP_ICONFLOW_VISITEMCOUNT` | - | int | `RW` | Visual List Items | |
| `NCSP_ICONFLOW_ICONBORDER` | - | unsigned | `RW` | Icon White Border | Pixel |
| `NCSP_ICONFLOW_ICONUSESCALE` | - | int | `RW` |Whether the icon is scaled to fit the set display area | Boolean |

#### Event

Inherited from
[event](http://wiki.minigui.com/bin/view/Products/MStudioMGNCSV1dot0PGP2C14#m_ItemView)
| *Event notification code* | *Description* | *Parameter* |

`NCSN_ICONFLOW_CLICKED` | Mouse Click Event | Clicked Entry Handle |
| `NCSN_ICONFLOW_ENTER` | `ENTER` press event | currently selected entry handle |

#### Method

Inherited from
[Method](http://wiki.minigui.com/bin/view/Products/MStudioMGNCSV1dot0PGP2C14#m_ItemView)
The iconflow control initializes the size of the list item via the 
`setIconSize` 
method and passes the `addItem`
The method adds a list item based on the list item information.

```cpp
Typedef struct _NCS_ICONFLOW_ITEMINFO
{
        Int index;
        PBITMAP bmp;
        Const char *label;
        DWORD addData;
}NCS_ICONFLOW_ITEMINFO;

Void setIconSize(mIconFlow *self, int width, int height);
HITEM addItem(mIconFlow *self, NCS_ICONFLOW_ITEMINFO *info, int *pos);
```

#### mIconFlow code example

```cpp
...
_c(self)->setIconSize(self, 90, 80);
for(i = 0; i < TABLESIZE(icon_demos); i++) {
        Pos = 0;
        Memset (&info, 0, sizeof(NCS_ICONFLOW_ITEMINFO));
        Info.bmp = &icon_demos[i];
        Info.index = TABLESIZE(icon_demos) * j + i;
        Info.label = iconlabels[i];
        info.addData = (DWORD)iconlabels[i];
        _c(self)->addItem(self, &info, &pos);
}
_c(self)->setCurSel(self, 0);
/* You can also set the private property of the control by the following method: */
_c(self)->setProperty (self, NCSP_ICONFLOW_VISITEMCOUNT, 5);
_c(self)->setProperty (self, NCSP_ICONFLOW_SPAN, 120);
...
```


<img align="CENTER" alt="mgncs4touch-miconflow.png"
src="%ATTACHURLPATH%/mgncs4touch-miconflow.png" />

iconflow control


## Piece

mGNCS4Touch have provide a large pieces, the follow is some important piece,
The usage of most part pieces is similar.


### mImagePiece

you can use it to display an image, the specify the align and draw mode.

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NCSP_IMAGEPIECE_IMAGE`| - | int | `RW` | set image with Bitmap | Bitmap|
| `NCSP_IMAGEPIECE_ICON`| - | int | `RW` | set image with Icon| Icon|
| `NCSP_IMAGEPIECE_MYBITMAP`| - | `mHotPiece*` | `RW` | set image with `MyBitmap`| `MyBitmap` |
| `NCSP_IMAGEPIECE_IMAGEFILE`| - | unsigned | `RW` | set image with an bitmap file| Pixel |
| `NCSP_IMAGEPIECE_ALIGN`| - | int | `RW` | set horizontal align value| |
| `NCSP_IMAGEPIECE_VALIGN`| - | unsigned | `RW` | set vertical align value| Pixel |
| `NCSP_IMAGEPIECE_DRAWMODE`| - | int | `RW` | set image draw mode | Boolean |

### mTextPiece

you can use it to display an text.

### mShapeBoxPiece

you can use it to display some simple shape.

### mRadioPiece

an Radio piece.

### m3DButtonPiece

an 3D button style piece.


### mPanelPiece

`mPanelPiece` is an base container piece, when you need use some pieces to
assemble an widget, you should use `mPanelPiece`, the panel manage piece with
absolute x/y coordinate, no any auto layout support.

#### concept

`mPanelPiece` is a very powerful basic piece. Its function is similar to a
container. It supports the addition of other pieces to the panel and specifies
the absolute position of the piece. Currently, other types of layout are not
supported. The added piece has no type. Restrictions, and powerful layouts can
be achieved through nesting levels.

`mPanel` also supports animation internally. For the piece added to the panel,
basic animation such as alpha change, position change, zoom, etc. can be
implemented. Animations of multiple pieces can be executed in parallel. For
example, if the animation function is similar to ios above, you need to have
Multiple elements are animated at the same time.

#### addContent

`addContent` is most important method for `mPanelPiece`, you can add an piece
to panel and specify piece x/y coordinate.

```cpp
static mPieceItem* mPanelPiece_addContent(mPanelPiece* self, mHotPiece *piece,
int x, int y)
{
    ADDREFPIECE(piece);
    return _c(self)->createItemNode(self, piece, x, y);
}
```

#### animation

Base property change:
- move piece.
- zoom piece.
- alpha piece.
- rotate piece.

Base animation include:
- move.
- zoom.
- rotate.
- alpha.

```cpp
...
    CLASS_METHOD_MAP(mPanelPiece, movePiece    )
    CLASS_METHOD_MAP(mPanelPiece, scalePiece   )
    CLASS_METHOD_MAP(mPanelPiece, rotatePiece  )
    CLASS_METHOD_MAP(mPanelPiece, setPieceAlpha)
    CLASS_METHOD_MAP(mPanelPiece, movePieceWithAnimation    )
    CLASS_METHOD_MAP(mPanelPiece, scalePieceWithAnimation   )
    CLASS_METHOD_MAP(mPanelPiece, rotatePieceWithAnimation  )
...
```


### mNavigationPanelPiece

`mNavigatePanelPiece` is a page-switching navigation container where you can 
add 
a piece to it and then switch animations from one piece page to another,
including a simple page-level pull/push animation and an alpha change of
navigation 
bar, the navigate button will be have an move animation yet.


#### mNavigationBarPiece

an navigate bar, it provide an title bar like the `iOS`, it have include two
button that used for go or back.
- left button: buttton on bar left.
- right button: button on bar right.
- title button: used to show an text title.

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NCSP_NAVIGATIONBARPIECE_BACKGROUND` | - | int | `RW` | set navigate bar backgrounp Bitmap | Bitmap|
| `NCSP_NAVIGATIONBARPIECE_BKG`| - | int | `RW` | do nothing| Icon|
| `NCSP_NAVIGATIONBARPIECE_LEFT_BUTTON`| - | `mButtonPanelPiece*` | `RW` | set left button piece | |
| `NCSP_NAVIGATIONBARPIECE_TITLE_BUTTON`| - | `mTextPiece*`| `RW` | set center title piece| |
| `NCSP_NAVIGATIONBARPIECE_RIGHT_BUTTON`| - | `mButtonPanelPiece*`| `RW` | set right button piece| |


it is used by `mNavigationPanelPiece`.

#### mNavigationItem

an navigate item, it is base `mObject`, so it is not an piece, just used for
save an navigate item info, such as:

- content: the main content, it is also an piece.
- button: left/right/center title.
- font info: font of buttons.
- style: navigate bar show or overlapped view.

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NAVIGATION_STYLE_NORMAL`| - | `mHotPiece*`| `RW` | the bar not overlapped the view, not transparent| |
| `NAVIGATION_STYLE_FULLSCREEN`| - | int | `RW` | fullscreen bar overlapped theview, transparent| |
| `NAVIGATION_STYLE_HIDE_BAR`| - | unsigned | `RW` | fullscreen no navigate bar| |


- property: support follow property.

| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NCSP_NAVIGATIONITEM_CONTENT` | - | `mHotPiece*`| `RW` | set item content| |
| `NCSP_NAVIGATIONITEM_BACKGROUND`| - | int | `RW` | set item bacground| |
| `NCSP_NAVIGATIONITEM_BAR_BKG` | - | unsigned | `RW` | set item bar background | Pixel |
| `NCSP_NAVIGATIONITEM_TITLE` | - | int | `RW` | set item title label | |
| `NCSP_NAVIGATIONITEM_STYLE` | - | unsigned | `RW` | set item style| Pixel |
| `NCSP_NAVIGATIONITEM_LEFT_BUTTON` | - | `mHotPiece*`| `RW` | set item bar left button| Boolean |
| `NCSP_NAVIGATIONITEM_TITLE_BUTTON`| - | `mHotPiece*`| `RW` | set item bar title piece| Boolean |
| `NCSP_NAVIGATIONITEM_RIGHT_BUTTON`| - | `mHotPiece*`| `RW` | set item bar right buton| Boolean |
| `NCSP_NAVIGATIONITEM_DEFAULT_BUTTON_FONT`| - | int | `RW` | set item button font| Boolean |

it is used by `mNavigationPanelPiece`.
an navigate bar panel, it is used to manage the navigate item, you can use
push to enter an navigate item, and pop to back preview.

- push: enter new navigate item.
- pop: back.
- `showNavigationBar`: show navigate bar, it is an `mNavigationBarPiece`.


| *Property ID* | *miniStudio Name* | *Type* | *Permission* | *Description* |
*Unit* |
| `NCSP_NAVIGATIONPANELPIECE_BAR`| - | int | `RW` | do nothing, no used.| |
| `NCSP_NAVIGATIONPANELPIECE_BAR_BKG`, - | int | `RW` | set navigate panel background bitmap| Bitmap|



#### sample

follow is an simple sample for use it:


```cpp

mNavigationPanelPiece *m_nav = NULL;
mNavigationItem *m_navItems[TYPE_WIN_MAX_NUM] = {NULL};
mHotPiece *m_okBtn;
mHotPiece *m_barBack;

void createNavigatorBtns(mNavigationItem* self)
{
    m3DButtonPiece *mbutton = (m3DButtonPiece*)_c(self)->createDefaultButton(self, "OK",0);

    m_okBtn = (mHotPiece *)mbutton;
    _c(self)->setProperty(self,NCSP_NAVIGATIONITEM_RIGHT_BUTTON,
(DWORD)m_okBtn);
    return;
}

int create (void) {
    ...
    mNavigationPanelPiece *nav = CreateNavigationPanelPieceWithRootView(rootItem);

    m_navItems[TYPE_MAIN_WIN_UI] = CreateNavigationItem(
            (mHotPiece *)mainWinPiece, "Settings", NAVIGATION_STYLE_NORMAL);

    m_navItems[TYPE_SUB_WIN_UI] = CreateNavigationItem(
            (mHotPiece *)subWinPiece, name, NAVIGATION_STYLE_NORMAL);


    /* you push your item and pop it */
    nextItem = getNavItem(TYPE_SUB_WIN_UI);
    assert(nextItem);
    _c(nav)->push(nav,nextItem);
    ...
}

int onBack(void)
{
    if (_c(m_nav)->currentIsRoot(m_nav))
        return 0;

    _c(m_nav)->pop(m_nav);
    return 1;
}
```

### mHScrollViewPiece

`mHScrollViewPiece` is a container piece that supports horizontal scrolling. It
inherits from `mPanelPiece` and implements horizontal scrolling, while
`mTableViewPiece` only supports vertical scrolling. It also has
turbulence-accelerating scrolling characteristics and slows down after
stopping.

When used, it must be initialized in the main form's `onCreate` function to add
the required elements. The following is a simple example of use:

- create an `mHScrollViewPiece`.
- add an `mPanel`.
- each group consists of a `mImagePiece/mLabelPiece`, one for displaying
icons, and one for displaying text, Added these item to `mPanel`.
   * use `mRectPiece` as a uniform background for `mPanel`.


This sample is an classical usage for `mPanelPiece`, it is an base container
piece and very useful.

```cpp
/* init mHScrollViewPiece */
static BOOL mymain_onCreate(mMainWnd* self, DWORD dwAddData )
{
...
    mContainerCtrl *ctnr;
    mPanelPiece *content;
    mHScrollViewPiece *view;
    mHotPiece* backPiece;

    ctnr = (mContainerCtrl*)ncsCreateWindow(NCSCTRL_CONTAINERCTRL,
            "ContainerCtrl",
            WS_VISIBLE, 0, 0,
            0, 10, RECTW(rc), RECTH(rc)-10*2,
            self->hwnd,
            NULL, NULL, NULL, 0);

    content = (mPanelPiece*)NEWPIECE(mPanelPiece);

    /* create mPanel as container, set ads body of mContainerCtrl.*/
    view = NEWPIECE(mHScrollViewPiece);
    _c(view)->addContent(view, (mHotPiece*)content, 0, 0);
    _c(ctnr)->setBody(ctnr, (mHotPiece*)view);

    /* add a rect piece as background.*/
    backPiece = (mHotPiece*)NEWPIECE(mRectPiece);
    _c(content)->addContent (content, backPiece, 0, 0);

    /* add 18 imagePiece */
    rc.left = rc.top = 0;
    for (i = 0; i < 18; i++) {
        mHotPiece *imagePiece = (mHotPiece*)NEWPIECE(mImagePiece);
        mHotPiece *labelPiece = (mHotPiece*)NEWPIECE(mLabelPiece);

        _c(content)->addContent (content, imagePiece, 15 + (bmp[i % 3].bmWidth
+ 15) * i, 10);
        _c(content)->addContent (content, labelPiece, 15 + (bmp[i % 3].bmWidth
+ 15) * i, bmp[i % 3].bmHeight + 15);
    }
...
}
```



### mTableViewPiece Using

`mTableViewPiece` is base on the `mPanelPiece` and include an list layout.

#### create piece

`mTableViewPiece` is an internal piece, it is not an control, so you can not 
use 
it directly, you should inherit it first.

- init piece class: each piece should be init first, use `MGNCS_INIT_CLASS`,
if no init, it will be crash when you using it.
- init mouse event, mGNCS4Touch has default event handler, you can use it
directly.
- create an ncs main MiniGUI control(mContainerCtrl) for your piece.
- connect your piece `mContainerCtrl` by `setBody` of `mContainerCtrl`.

```cpp
static NCS_EVENT_HANDLER mymain_handlers [] = { 
    {MSG_CREATE, mymain_onCreate },
    {MSG_LBUTTONDOWN, SpeedMeterMessageHandler },
    {MSG_LBUTTONUP, SpeedMeterMessageHandler },
    {MSG_MOUSEMOVE, SpeedMeterMessageHandler },
    {0, NULL}
};

tatic BOOL mymain_onCreate(mMainWnd* self, DWORD dwAddData )
{
...
    mContainerCtrl* ctnr = (mContainerCtrl*)ncsCreateWindow(NCSCTRL_CONTAINERCTRL,
    "ContainerCtrl",
    WS_VISIBLE, 0, 0,
    ITEM_W + 50, BTN_H + 10, ITEM_W, TABLEVIEW_ITEMNUM *ITEM_H + 2,
    self->hwnd,
    NULL, NULL, NULL, 0); 

    table_index = table = (mSimpleTableView*)NEWPIECEEX(mSimpleTableView, NCS_TABLEVIEW_INDEXLOCATE_STYLE);
    _c(table)->setSeparatorColor(table, 0xFFFF00FF);
    _c(table)->setSeparatorStyle(table, NCS_TABLEVIEW_SEPARATORSTYLE_NONE);
    _c(table)->setRect(table, &rc);
    _c(table)->reloadData(table);
    _c(ctnr)->setBody(ctnr, (mHotPiece*)table);
...
}


```

#### init piece

Definne your own piece and Inherit your piece from `mTableViewPiece`, you 
should implement the relative
method:
- `createItemForRow`: used for create one row for the list, it is the most
important method, you can create your own list row, you can use pieces to
assemble your row, you can use `mTableViewItemPiece` directly, but you can
create your any other need piece.
- `numberOfSections`: your section of data, one section is an group, like
'A', 'B', 'C', if you have no sections for your data, you do not need it.
- `numberOfRowsInSection`: the number rows in an section, it will return row
number for each setion.
- `titleForSection`: section title.
- `indexForSection`: section index, it is used to quick jump section
position.
- `onCommitDeleteRowAtIndexPath`: commit delete an row.

```cpp
static mTableViewItemPiece*
mSimpleTableView_createItemForRow(mSimpleTableView* self, const mIndexPath*
indexpath)
{
...
    ItemInfo* rowinfo = sectioninfo[indexpath->section].rows + indexpath->row;
    mHotPiece* piece = create_item_userpiece(rowinfo->text, rowinfo->picture);
    mTableViewItemPiece* item = NEWPIECEEX(mTableViewItemPiece, 0);

    _c(item)->setUserPiece(item, piece);
...
    return item;
}

BEGIN_MINI_CLASS(mSimpleTableView, mTableViewPiece)
        CLASS_METHOD_MAP(mSimpleTableView, construct)
        CLASS_METHOD_MAP(mSimpleTableView, createItemForRow)
        CLASS_METHOD_MAP(mSimpleTableView, numberOfSections)
        CLASS_METHOD_MAP(mSimpleTableView, numberOfRowsInSection)
        CLASS_METHOD_MAP(mSimpleTableView, titleForSection)
        CLASS_METHOD_MAP(mSimpleTableView, indexForSection)
        CLASS_METHOD_MAP(mSimpleTableView, onCommitDeleteRowAtIndexPath)
        CLASS_METHOD_MAP(mSimpleTableView, destroy)
END_MINI_CLASS
/* end of mSimpleTableViewPiece.*/
```


<img align="CENTER" alt="mgncs4touch-mtableview.png"
src="%ATTACHURLPATH%/mgncs4touch-mtableview.png" />

`mSimpleTableViewPiece` piece



## Comments




----

[&lt;&lt; ](MiniGUIProgGuidePart.md) |
[Table of Contents](README.md) |
[ &gt;&gt;](MiniGUIProgGuidePart.md)

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
