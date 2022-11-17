# 动画控件类

## 1 动画控件简介
动画控件通过对图片组和 gif 动态图片的绘制和显示，为用户提供了丰富的视觉体验。 mGNCS 中的动画控件源于 Minigui 3.0 的 animation 控件，在其基础上增加了对图片组播放和gif图片播放控制的支持。 同时， 用户可以通过设置图片播放间隔时间， 来控制播放速度。

- Animate 类层次关系
   - [mStatic](MiniGUIProgGuidePart2Chapter14-zh.md#2-mstatic)
      - [mAnimate](#2-manimate)
- 控件创建方法
   - 自动创建：通过 mStudio 中的界面设计器，拖拽对应的动画控件，在属性栏中选择需要加载的 GIF 图片或图片目录，mStudio 将自动创建控件，并提供可视化的控件配置，同时自动生成创建代码。
   - 手动生成：按照 mGNCS 控件创建过程，通过编程，传入对应控件窗口类 ID，生成控件，手动编程设置控件属性、事件处理。

## 2 `mAnimate`

- 控件窗口类: `NCSCTRL_ANIMATE`
- 控件英文名: Animate
- 简介: 动画控件。通过在控件上加载不同的图片处理对象， 来显示绘制动态图片。
- 示意图: 

### 2.1 `mAnimate` 风格

继承自 [mStatic](MiniGUIProgGuidePart2Chapter14-zh.md#2-mstatic) 的风格

| 风格 ID | mStudio 属性名 |  说明 |
|:-------|:--------------|:------|
| `NCSS_ANMT_AUTOLOOP` | `Loop` | 设置动画播放是否为自动循环， 设置为 `True` 时，图片循环播放， 设置为 `False` 时，图片播放完毕则停止  |
| `NCSS_ANMT_SCALE` | `Scale->ImageScaled `| 设置图片播放面积为控件区域面积， 可以对图片进行扩大或缩减播放  |
| `NCSS_ANMT_AUTOFIT` | `Scale->AutoFit` | 设置控件区域自动匹配为图片面积 |
| `NCSS_ANMT_AUTOPLAY` | `Autoplay` | 设置图片是否为自动播放， `True` 时， 图片自动播放，`False` 时， 需要用户发送命令控制播放 |

### 2.2 `mAnimate` 属性

继承自 [mStatic](MiniGUIProgGuidePart2Chapter14-zh.md#2-mstatic) 的属性

| 属性 ID 名 | mStudio 属性名 |  类型 | 权限 | 说明 |
|:----------|:--------------|:-----|:-----|:----|
| `NCSP_ANMT_GIFFILE` | `GIFFile` | String | `RW` | 动画控件加载的GIF图片文件名 |
| `NCSP_ANMT_DIR` | `Dir` | String | `RW` | 动画控件加载的目录名， 控件加载目录内的所有图片, 图片播放是按照所支持图片首字母ascii码顺序 |
| `NCSP_ANMT_INTERVAL` | `Interval` | int | `RW`| 播放图片时帧与帧之间的时间间隔 |

### 2.3 `mAnimate` 事件

继承自[mStatic](MiniGUIProgGuidePart2Chapter14-zh.md#2-mstatic) 的事件

### 2.4 `mAnimate` 渲染器

非客户区的绘制请查阅[[MStudioMGNCSV1dot0PGP2C4#mStatic][mStatic]]的渲染器

### 2.5 `mAnimate` 方法
#### 2.5.1 `ncsAnimateStart`

```c
BOOL ncsAnimateStart(mAnimate* self);
```
- 参数：
   - self -- 需要操作的动画控件指针
- 说明：<BR>
   开始播放 self 对应的动画控件， 如果动画控件已经在播放， 则回到动画起始处开始播放。
- 示例：

```c
//播放anim动画
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStart(anim);    
```

#### 2.5.2 `ncsAnimatePauseResume`

```c
BOOL ncsAnimatePauseResume(mAnimate* self);
```
- 参数：
   - elf -- 需要操作的动画控件指针
- 说明：<BR>
   如果当前动画为暂停，此方法会继续播放动画， 如果动画为播放中， 此方法会暂停动画。
- 示例：

```c
//暂停anim动画
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStart(anim);
    ncsAnimatePauseResume(anim);    
```

#### 2.5.3 `ncsAnimateStop`

```c
BOOL ncsAnimateStop(mAnimate* self);
```
- 参数：
   - self -- 需要操作的动画控件指针
- 说明：<BR>
  停止动画， 并将动画重置回第一帧。
- 示例：

```c
//暂停anim动画
    mAnimate *anim = (mAnimate *)ncsGetChildObj(hwnd, IDC_ANI);
    ncsAnimateStop(anim);
```

### 2.6 `mAnimate` 编程示例

-  运行截图: 

![animation_screenshot](figures/animation_screenshot.PNG)

-  本程序窗口区域上边的图片为 gif 动态图片， 下面是对程序所在目录中图片的幻灯片播放， 三个按钮start, pause, stop 是对 gif 播放的控制。
-  普通按钮完整示例代码：[animation.c](samples/animation.c)

__清单 1__  animation.c

```c
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
		WS_BORDER | WS_VISIBLE |NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOLOOP | \
		NCSS_ANMT_AUTOPLAY,
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
		WS_BORDER | WS_VISIBLE | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOFIT | \
		NCSS_ANMT_AUTOPLAY,,
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

- 设置加载图片

```c
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

- 设置按键消息

```c
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

- 设置显示界面模板

```c
static NCS_WND_TEMPLATE _ctrl_templ[] = {
        {
                NCSCTRL_ANIMATE, 
                IDC_ANI,
                50, 50, 300, 300,
                WS_BORDER | WS_VISIBLE |NCSS_ANMT_AUTOFIT | NCSS_ANMT_AUTOLOOP | \		NCSS_ANMT_AUTOPLAY,
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
                WS_BORDER | WS_VISIBLE | NCSS_ANMT_AUTOLOOP | NCSS_ANMT_AUTOFIT | \		NCSS_ANMT_AUTOPLAY,,
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
 
