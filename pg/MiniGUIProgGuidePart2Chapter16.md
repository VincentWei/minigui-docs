# 第二部分第十五章 不可见控件
# Chapter 15 of Part 2 Invisible Control


## 不可见控件简介
## Brief Introduction of Invisible Control

不可见控件是指那些不能在窗口上显示，但是却具有一定功能的组件。

Invisible control refers to the components which cannot be displayed on the window but have certain functions.

这些组件是对一些功能模块的封装，保证它们能够像控件一样在mStudio中被编辑

These components is encapsulation to some functional templates, guaranteeing that they can be edited in mStudio like control

- <a href="#?">mObject</a>
   - <a href="#?">mComponent</a>
         * mInvsbComp

## mInvsbComp
- *控件名称*:  无
- *英文名*:  Invisble Component
- *简要介绍*:  不可见组件的基类
- *示意图*: %RED%基础类，不能直接使用%ENDCOLOR%

- *Control name*:  None
- *English name*:  Invisble Component
- *Brief introduction*:  Basic class of invisible component
- *Schematic diagram*: %RED%Foundation class, cannot be used directly%ENDCOLOR%


### mInvsbComp风格
### Style of mInvsbComp
继承自<a href="#?">mComponent的风格</a>

It is inherited from <a href="#?">the style of mComponent</a>

### mInvsbComp属性
### Property of mInvsbComp
继承自<a href="#?">mComponent的属性</a>

It is inherited from <a href="#?">the property of mComponent</a>

### mInvsbComp方法
### Method of mInvsbComp

mInvsbComp提供了以下方法的实现：

mInvsbComp provides realization of the following methods:

- setId
- getId
- setReleated
- getReleated
- getChild

另外，为方便mInvsbComp的使用，提供了如下函数

In addition, for the convenience of use of mInvsbComp, the following functions are provided

- 创建不可见组件

- Create invisible component
%CODE{cpp}%
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

NCS_INVSB_CREATE_INFO structure used by function ncsCreateInvsbCompIndirect is defined as below

%CODE{cpp}%

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

- 注： *不鼓励直接使用该函数创建不可见组件*  ，它们在手写代码中没有优势，优势在于，可以利用mStudio提供的资源来加载。
故省略例子

- Note: * it is not encouraged to directly use the function to create invisible component, *  and they have no advantage in handwritten codes. The advantage is that resources provided by mStudio can be utilized to load.

故省略例子

So example is omitted.

### mInvsbComp事件
### Event of mInvsbComp
 继承自<a href="#?">mComponent的事件<a/>

It is inherited from <a href="#?">the event of mComponent<a/>

## mTimer

- *控件名称*: NCSCTRL_TIMER
- *英文名*: Timer
- *简要介绍*: 对MiniGUI  SetTimerEx和KillTimer的封装
- *示意图*: 无示意图，在mStudio中的图标是 <img src="%ATTACHURLPATH%/mtimer.png" alt="mtimer.png" width='30' height='29' />


- *Control name*: NCSCTRL_TIMER
- *English name*: Timer
- *Brief introduction*: Encapsulation to MiniGUI SetTimerEx and KillTimer
- *Schematic diagram*: There is no schematic diagram, and the icon in mStudio is <img src="%ATTACHURLPATH%/mtimer.png" alt="mtimer.png" width='30' height='29' />

继承关系

Inheritance relation

- <a href="#?">mObject</a>
   - <a href="#?">mComponent</a>
         * <a href="#m_InvsbComp">mInvsbComp</a>
            * mTimer

### mTimer风格
### Style of mTimer
继承自<a href="#mInvsbComp属性">mInvsbComp的风格<a/>

It is inherited from <a href="#Style of mInvsbComp">the style of mInvsbComp<a/>

### mTimer属性
### Property of mTimer

继承自<a href="#mInvsbComp属性">mInvsbComp的属性<a/>

|* 属性ID *| *mStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_TIMER_INTERVAL | interval | DWORD | RW | 设置Timer的时间间隔，以10ms为单位， 如果Timer正在运行，它会重启Timer |


It is inherited from <a href="# Property of mInvsbComp"> the property of mInvsbComp<a/>

|* Property ID *| *mStudio name*| *Type* | *Authority* |* Explanation *|
| NCSP_TIMER_INTERVAL | interval | DWORD | RW | Set time interval of Timer, with 10ms as the unit. If Timer is operating, it will restart Timer |

### mTimer方法
### Method of mTimer

继承自<a href="#mInvsbComp方法">mInvsbComp的方法<a/>

It is inherited from <a href="#Method of mInvsbComp">the method of mInvsbComp <a/>

- start
%CODE{cpp}%
BOOL (*start)(clss *_this);
```
   - 启动Timer
   - Return TRUE -- 启动成功, FALSE -- 启动失败

   - Start Timer
   - Return TRUE – start successful, FALSE – start failed

- stop
%CODE{cpp}%
void (*stop)(clss *_this);
```
   - 停止正在运行的Timer

   - Stop the Timer in operation

- getParent
%CODE{cpp}%
HWND (*getParent)(clss *_this);
```
   - 获取拥有Timer的窗口

   - Get the window with Timer

### mTimer事件
### Event of mTimer

继承自<a href="#mInvsbComp事件">mInvsbComp的事件<a/>

| * 事件通知码 * | *说明* | *参数* |
| MSG_TIMER | 直接利用MiniGUI的定义 | timer走过的总时间数，即MSG_TIMER的lParam值 |

It is inherited from<a href="#Event of mInvsbComp">the event of mInvsbComp<a/>

|* Event notification code *|* Explanation *|* Parameter *|
| MSG_TIMER | Directly utilize the definition of MiniGUI | Total time amount that timer walks by, which is 1Param value of MSG_TIMER |

- 注：该事件的回调为：

- Note: callback of the event is:
%CODE{cpp}%
BOOL (*NCS_CB_ONTIMER)(mTimer* timer, DWORD total_count);
```
   - Return : TRUE -- continue Timer, FALSE -- stop Timer
   - Params
         * DWORD total_count - Timer启动以来总时间数

   - Return : TRUE -- continue Timer, FALSE -- stop Timer
   - Params
         * DWORD total_count - Total time amount since Timer starts

### mTimer示例
### Example of mTimer

下面示例展示的是用timer显示一个数字钟表，运行效果图如下：<br />
The example below demonstrates using timer to show a digital clock, and the operation effect drawing is as below:<br />
     <img src="%ATTACHURLPATH%/timer-show.png" alt="timer-show.png" width='150' height='80' />


- 声明Timer，使用和控件一样的结构

- Declare Timer uses the same structure as the control
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/timer.c.txt" pattern="^.*?//START_DECLARE_TIMER(.*?)//END_DECLARE_TIMER.*"}%
```

- 初始化Timer，建立和一个Static控件的连接，并开始Timer

- Initialize Timer, establish a connection with Static control, and start Timer
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/timer.c.txt" pattern="^.*?//START_TIMER_CONNECT(.*?)//END_TIMER_CONNECT.*"}%
```

- 当MSG_TIMER事件发生时，更新时间

- When MSG_TIMER event occurs, update the time
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/timer.c.txt" pattern="^.*?//START_UPDATE_TIME(.*?)//END_UPDATE_TIME.*"}%
```


完整的代码参考 [timer.c](%ATTACHURL%/timer.c.txt)

For complete codes, refer to [timer.c](%ATTACHURL%/timer.c.txt)

[Next](MStudioMGNCSV1dot0PGP2C14][Previous]] < [[MStudioMGNCSV1dot0PG][Index]] > [[MStudioMGNCSV1dot0PGP2C16)




-- Main.XiaodongLi - 22 Feb 2010

