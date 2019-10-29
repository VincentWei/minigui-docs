# Invisible Control Class

## Brief Introduction to Invisible Control Class

不可见控件是指那些不能在窗口上显示，但是却具有一定功能的组件。

Invisible control refers to the components which cannot be displayed on the
window but have certain functions.

这些组件是对一些功能模块的封装，保证它们能够像控件一样在miniStudio中被编辑

These components is encapsulation to some functional templates, guaranteeing
that they can be edited in miniStudio like control

- <a href="#?">mObject</a>
- <a href="#?">mComponent</a>
* `mInvsbComp`

## `mInvsbComp`
- *控件名称*: 无
- *英文名*: Invisble Component
- *简要介绍*: 不可见组件的基类
- *示意图*: %RED%基础类，不能直接使用%ENDCOLOR%

- *Control name*: None
- *English name*: Invisble Component
- *Brief introduction*: Basic class of invisible component
- *Schematic diagram*: %RED%Foundation class, cannot be used directly%ENDCOLOR%


### `mInvsbComp风格`
### Style of `mInvsbComp`
继承自<a href="#?">mComponent的风格</a>

It is inherited from <a href="#?">the style of `mComponent</a`>

### `mInvsbComp属性`
### Property of `mInvsbComp`
继承自<a href="#?">mComponent的属性</a>

It is inherited from <a href="#?">the property of `mComponent</a`>

### `mInvsbComp方法`
### Method of `mInvsbComp`

`mInvsbComp提供了以下方法的实现`：

`mInvsbComp` provides realization of the following methods:

- `setId`
- `getId`
- `setReleated`
- `getReleated`
- `getChild`

另外，为方便mInvsbComp的使用，提供了如下函数

In addition, for the convenience of use of `mInvsbComp`, the following 
functions are provided

- 创建不可见组件

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

其中，函数ncsCreateInvsbCompIndirect用到的NCS_INVSB_CREATE_INFO结构定义如下

`NCS_INVSB_CREATE_INFO` structure used by function `ncsCreateInvsbCompIndirect`
is defined as below

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

- 注： *不鼓励直接使用该函数创建不可见组件* ，它们在手写代码中没有优势，优势在于，可以利用miniStudio提供的资源来加载。
故省略例子

- Note: * it is not encouraged to directly use the function to create invisible
component, * and they have no advantage in handwritten codes. The advantage is
that resources provided by miniStudio can be utilized to load.

故省略例子

So example is omitted.

### `mInvsbComp事件`
### Event of `mInvsbComp`
继承自<a href="#?">mComponent的事件<a/>

It is inherited from <a href="#?">the event of `mComponent<a/`>

## `mTimer`

- *控件名称*: `NCSCTRL_TIMER`
- *英文名*: Timer
- *简要介绍*: 对MiniGUI `SetTimerEx和KillTimer的封装`

![alt](figures/mtimer.png)



- *Control name*: `NCSCTRL_TIMER`
- *English name*: Timer
- *Brief introduction*: Encapsulation to MiniGUI `SetTimerEx` and `KillTimer`

![alt](figures/mtimer.png)


继承关系

Inheritance relation

- <a href="#?">mObject</a>
- <a href="#?">mComponent</a>
* <a href="#m_InvsbComp">mInvsbComp</a>
* `mTimer`

### `mTimer风格`
### Style of `mTimer`
继承自<a href="#mInvsbComp属性">mInvsbComp的风格<a/>

It is inherited from <a href="#Style of `mInvsbComp">the` style of
`mInvsbComp<a/`> 

### `mTimer属性`
### Property of `mTimer`

继承自<a href="#mInvsbComp属性">mInvsbComp的属性<a/>

| * 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| `NCSP_TIMER_INTERVAL` | interval | `DWORD` | `RW` | 设置Timer的时间间隔，以10ms为单位， 如果Timer正在运行，它会重启Timer |


It is inherited from <a href="# Property of `mInvsbComp"`> the property of
`mInvsbComp<a/`> 

| * Property ID *| *miniStudio name*| *Type* | *Authority* |* Explanation *|
| `NCSP_TIMER_INTERVAL` | interval | `DWORD` | `RW` | Set time interval of Timer, with 10ms as the unit. If Timer is operating, it will restart Timer |

### `mTimer方法`
### Method of `mTimer`

继承自<a href="#mInvsbComp方法">mInvsbComp的方法<a/>

It is inherited from <a href="#Method of `mInvsbComp">the` method of 
`mInvsbComp` <a/>

- start
```cpp
BOOL (*start)(clss *_this);
```
- 启动Timer
- Return `TRUE` -- 启动成功, `FALSE` -- 启动失败

- Start Timer
- Return `TRUE` – start successful, `FALSE` – start failed

- stop
```cpp
void (*stop)(clss *_this);
```
- 停止正在运行的Timer

- Stop the Timer in operation

- `getParent`
```cpp
HWND (*getParent)(clss *_this);
```
- 获取拥有Timer的窗口

- Get the window with Timer

### `mTimer事件`
### Event of `mTimer`

继承自<a href="#mInvsbComp事件">mInvsbComp的事件<a/>

| * 事件通知码 * | *说明* | *参数* |
| `MSG_TIMER` | 直接利用MiniGUI的定义 | timer走过的总时间数，即MSG_TIMER的lParam值 |

It is inherited from<a href="#Event of `mInvsbComp">the` event of 
`mInvsbComp<a/`> 

| * Event notification code *|* Explanation *|* Parameter *|
| `MSG_TIMER` | Directly utilize the definition of MiniGUI | Total time amount that timer walks by, which is 1Param value of `MSG_TIMER` |

- 注：该事件的回调为：

- Note: callback of the event is:
```cpp
BOOL (*NCS_CB_ONTIMER)(mTimer* timer, DWORD total_count);
```
- Return : `TRUE` -- continue Timer, `FALSE` -- stop Timer
- Params
* `DWORD` `total_count` - Timer启动以来总时间数

- Return : `TRUE` -- continue Timer, `FALSE` -- stop Timer
- Params
* `DWORD` `total_count` - Total time amount since Timer starts

### `mTimer示例`
### Example of `mTimer`

下面示例展示的是用timer显示一个数字钟表，运行效果图如下：<br />
The example below demonstrates using timer to show a digital clock, and the
operation effect drawing is as below:<br />

![alt](figures/timer-show.png)



- 声明Timer，使用和控件一样的结构

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

- 初始化Timer，建立和一个Static控件的连接，并开始Timer

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

- 当MSG_TIMER事件发生时，更新时间

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


完整的代码参考 [timer.c](%ATTACHURL%/timer.c.txt)

For complete codes, refer to [timer.c](%ATTACHURL%/timer.c.txt)

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
