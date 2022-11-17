# 基础类介绍

## 1 `mObject`

### 1.1 `mObject` 介绍

`mObject` 是所有 mGNCS 的基础类，它：

* 封装了 mGNCS 继承和虚函数实现
* 定义了最基本的类成员结构

同时，定义了一组类操作函数，以控制类的行为

__该类为基础类，不能直接使用__

* 直接子类:
   * `mComponent`

### 1.2  `mObject` 操作函数

在 NCS 中，诸多关于类的操作都是以 `mObject` 指针为参数，这些有

* 类型判断操作: `ncsInstanceOf`, 相当于 java 的 `instanceof` 操作符，判断一个指针是否是指定的类的实例

```c
/**
 * \fn BOOL ncsInstanceOf(mObject* object, mObjectClass* clss);
 * \brief check an object is the class instance or not, 
 *           same as \b instanceof operator in Java
 *
 * \param object - the pointer of object being to test
 * \param clss - the pointer of class for test
 * 
 * \return TRUE - object is instance of clss, FALSE - not
 */
BOOL ncsInstanceOf(mObject* object, mObjectClass* clss);
```

为方便操作，提供宏

```c
#define INSTANCEOF(obj, clss)  \
          ncsInstanceOf((mObject*)(obj), \
                      (mObjectClass*)(void*)(&Class(clss)))
```

使用举例

```c
   if(INSTANCEOF(obj, mWidget)) //判断对象obj是否是一个mWidget对象
     .....
```

另外，为判断一个指针是否是 `mObject` 对象，可以使用 `ncsIsValidObj`

```c
/**
 * \fn static inline mObject*  ncsIsValidObj(mObject* obj);
 * \brief Check a pointer is a valid mObject or not
 *
 * \param obj - the excpeted object pointer
 *
 * \return mObject * the pointer of obj or other NULL if obj is an invalid mObject pointer
 */
static inline mObject*  ncsIsValidObj(mObject* obj){
    return (INSTANCEOF(obj, mObject)?(obj):NULL);
}
```

对应的宏是

```c
/**
 * \def CHECKOBJ
 * \brief the wrapper of ncsIsValidObj
 *
 * \sa ncsIsValidObj
 */
#define CHECKOBJ(obj)  ncsIsValidObj((mObject*)obj)
```

* 类型转换操作 : `ncsSafeCast`, 安全的类型转换，类似 C++ 的 `dynamic_cast` 操作符

```c
/**
 * \fn mObject* ncsSafeCast(mObject* obj, mObjectClass *clss);
 * \brief safe type cast function, like the \b dynamic_cast operator in C++
 *
 * \param obj - the mObject pointer being casted
 * \param clss - the target type to cast
 *
 * \return mObject * - the object pointer if cast safe, NULL otherwise
 * 
 * \sa ncsInstanceOf
 */
mObject* ncsSafeCast(mObject* obj, mObjectClass *clss);
```

对应的宏是

```c
/**
 * \def SAFE_CAST
 * \brief wrapper of ncsSafeCast, check the class type before cast.
 *
 * \note this macro is same as \b dynamic_cast in C++
 *
 * \sa ncsSafeCast
 */
#define SAFE_CAST(Type, obj)  \
    TYPE_CAST(Type, ncsSafeCast((mObject*)obj,(mObjectClass*)(void*)(&(Class(Type)))))
```

使用举例

```c
   //将一个obj转为mWidget指针
   mWidget * widget = SAFE_CAST(mWidget, obj);

   //如果obj是一个mWidget类型或者mWidget子类类型，则转换成功，否则，widget == NULL
   if(widget)
     ....
```

* 其他函数 : `newObject`, `deleteObject`, `TYPENAME` 宏。

```c
/**
* \fn mObject * newObject(mObjectClass *_class);
* \brief new a object instance, like \b new operator in C++
*
* \param _class - the class of the object
*
* \return the new pointer of object
*
*/
mObject * newObject(mObjectClass *_class);
/**
 * \fn void deleteObject(mObject *obj);
 * \brief delete a object intance, like \b delete operator in C++
 *
 * \param obj - the object want to delete
 *
 */
void deleteObject(mObject *obj);

/**
 * \def TYPENAME
 * \brief Get the class name form a Object pointer
 */
#define TYPENAME(obj)  ((obj)?(((obj)->_class)?((obj)->_class)->typeName:""):"")
```

创建一个对象，要用 `newObject`，因为它会调用对象的构造函数。

删除一个对象，要使用 `deleteObject`，因为他会调用对象的析构函数。

## 2 `mComponent`

### 2.1 `mComponent` 介绍

`mComponent` 提供了组件最基本的实现。组件是构成 mGNCS 程序最基本的原件

__该类为基础类，不能直接使用__

* 继承自: `mObject`
* 直接子类
   * `mWidget`
   * `mInvsbComp`

### 2.2 `mComponent` 方法

* `setProperty`

```c
BOOL (*setProperty)(clss *_this, int id, DWORD value);
```
*   * 设置组件的属性
    * Return : `TRUE` -- 设置成功；`FALSE`--设置失败
    * Params
       * int id - 属性的 ID
       * `DWORD` value - 属性值

* `getProperty`

```c
DWORD (*getProperty)(clss *_this, int id);
```
*   * 获取组件的属性
    * Return: 属性值或者 `DWORD(-1)`
    * Params
       * int id - 属性 ID

* `setId`

```c
int (*setId)(clss *_this, int id);
```
*   * 设置组件的 Id
    * Return : 返回老的 Id
    * Params
       * int id - new id

* `getId`

```c
int (*getId)(clss *_this);
```
*   * 获取组件 Id
    * Return : 组件 Id

* `getReleated`

```c
mComponent* (*getReleated)(clss*_this, int releated);
```
*   * 取得和该组件相关的组件，例如父组件，子组件和兄弟组件
    * Return : `NULL` 或者对应的组件对象指针
    * Params:
       * int releated: 关系类型 :`NCS_COMP_NEXT` , `NCS_COMP_PREV` , `NCS_COMP_PARENT` , `NCS_COMP_CHILDREN` 之一
   
* `setReleated`:

```c
mComponent* (*setReleated)(clss *_this, mComponent* comp,  int releated); 
```
*   * 设置关联组件
    * Return : 设置后的关联组件指针；如果没有设置成功，返回NULL
    * Params
       * `mComponent` *comp - 被设置的组件指针
       * int releated - 同 `getReletaed`

* `getChild`

```c
mComponent* (*getChild)(clss* _this, int id);
```

*   * 获取id指定的子组件
    * Return : `NULL` 或者对应的组件指针
    * Params:
       * int id - 要获取的组件的 id

### 2.3 `mComponent` 操作函数

Component 支持一些通用的操作

* 事件安装和卸载函数

```c
/**
 * A struct of event-handler map
 *
 * \note only used for param
 *
 * \sa NCS_EVENT_HANDLER_NODE
 */
typedef struct _NCS_EVENT_HANDLER {
	/**
	 * The event code
	 */
	int message;
	/**
	 * The event callback pointer
	 */
	void *handler;
}NCS_EVENT_HANDLER;

/**
 * \fn void * ncsSetComponentHandler(mComponent* comp, int message, void *handler);
 * \brief set the component handler
 *
 * \param comp the compont to set
 * \param message the event code
 * \param handler the event callback pointer
 *
 * \return old event callback if it has been set
 *
 * \sa ncsSetComponentHandlers
 */
void * ncsSetComponentHandler(mComponent* comp, int message, void *handler);

/**
 * \fn void ncsSetComponentHandlers(mComponent* comp, \
                        NCS_EVENT_HANDLER* handlers, \
                        int count);
 * \brief set an array of event handlers
 * 
 * \param comp - the component to set
 * \param handlers - the array of \ref NCS_EVENT_HANDLER
 * \param count - the count of array handlers. 
 *
 * \note if count == -1, handlers must end by {-1, NULL};
 *   anywhere, ncsSetComponentHandlers would stop
 *   if it find an element of array handlers is equal {-1, NULL}, 
 *   whether count is equal -1 or not
 *
 * \sa ncsSetComponentHandler
 */
void ncsSetComponentHandlers(mComponent* comp, \
           NCS_EVENT_HANDLER* handlers, \
           int count);

/**
 * \fn void* ncsGetComponentHandler(mComponent* comp, int message);
 * \brief get an event callback 
 *
 * \param comp 
 * \param message - event code
 * 
 * \return void * the handler of message, or NULL if not set
 */
void* ncsGetComponentHandler(mComponent* comp, int message);
```

* 注册相关函数

```c
/**
 * \fn BOOL ncsRegisterComponent(mComponentClass *compCls, \
                         DWORD dwStyle, \
                         DWORD dwExStyle, \
                         int idCursor, \
                         int idBkColor);
 * \brief register a component class into MiniGUI, so that \ref ncsCreateWindow and
 *     \ref ncsCreateWindow can find a \mComponentClass instance
 *
 * \param compCls the \ref mComponentClass to be registered
 * \param dwStyle the default style
 * \param dwExStyle the default extend style
 * \param idCursor the default cursor
 * \param idBkColor the default background color
 *
 * \return TRUE - success, FALSE - failed
 *
 * \sa ncsGetComponentClass, ncsCreateWindow, 
 *       ncsCreateWindowIndirect, ncsCreateMainWindow, 
 *       ncsCreateMainWindowIndirect
 */
BOOL ncsRegisterComponent(mComponentClass *compCls, \
                                 DWORD dwStyle, \
                                 DWORD dwExStyle, \
                                 int idCursor, \
                                 int idBkColor);

/**
 * \fn mComponentClass * ncsGetComponentClass(const char* class_name, BOOL check);
 * \brief Get a \ref mComponentClass instance from MiniGUI
 *
 * \note the class_name must be registered into MiniGUI by calling ncsRegisterComponent
 *
 * \param class_name the class name to find
 * \param check check the class name with found mComponentClass instance, 
 *              to ensure that we found the right class
 *
 * \return the mComponentClass pointer if sucess, NULL otherwise
 */
mComponentClass * ncsGetComponentClass(const char* class_name, BOOL check);
```

## 3 `mWidget`
### 3.1 `mWidget` 介绍

`mWidget` 是所有控件的基础类

* 继承自: `mComponent`
* 直接子类
   * `mStatic`
   * `mButton`
   * `mPanel`
   * `mScrollWidget`
   * `mProgressBar`
   * `mPropSheet`
   * `mSlider`
   * `mSpinbox`

### 3.2 `mWidget` 风格

| 风格 ID        | mStudio 属性名 | 说明 |
|:--------------|:--------------|:-----|
| `NCSS_NOTIFY` | Notify        | 决定控件是否产生 Notification 事件 |

### 3.3 `mWidget` 属性

| 属性名                      | mStudio 属性名 | 类型           | RW   | 说明   |
|:---------------------------|:--------------|:--------------|:-----|:-------|
| `NCSP_WIDGET_RDR`          | Renderer      | `const char*` | W    | 设置控件当前渲染器 | 
| `NCSP_WIDGET_TEXT`         | Text          | `const char*` | W    | 设置当前控件的文本内容 |
| `NCSP_WIDGET_BKIMAGE`      | `BkImage`     | `PBITMAP`     | `RW` | 设置或获取当前背景图片 |
| `NCSP_WIDGET_BKIMAGE_MODE` | `BkImageMode` | [ImageDrawMode](programming-guide-zh/MiniGUIProgGuideAppendixC-zh.md) | 设置或者获取当前背景图片绘制模式 | |
| `NCSP_WIDGET_BKIMAGE_FILE` | -             | `const char*` | 设置当前背景图片，自动从文件名加载 | |


### 3.4 `mWidget` 方法

无

### 3.5 `mWidget` 事件

* `MSG_NCCREATE`
   * 描述: 当窗口非客户区创建时。窗口的第一个消息, 此时窗口尚未建成，以窗口句柄为参数的函数不能调用
   * 回调: void (* NCS_CB_ONNCCREATE)(mWidget *);
      * 返回值: 无
      * 参数
         * `mWidget` * 事件产生者对象指针

* `MSG_CREATE`
   * 描述: 当窗口创建时产生。
   * 回调: typedef BOOL(*) NCS_CB_ONCREATE (mWidget *, DWORD dwAddData)
      * 返回值: `TRUE` - 继续创建了；`FALSE` - 退出创建
      * 参数
         * mWidget *
         * DWORD dwAddData 附加数据

   * 通知消息
      * 所有通知消息产生的事件都使用该回调
      * void (* NCS_CB_NOTIFY)(mWidget *,  int nc_code);
         * 返回值: 无
         * 参数
            * `mWidget` * 事件产生者对象指针
            * int nc_code : 事件通知码，用于区别不通的事件

__注，所有通知事件的回调都是 `NCS_CB_NOTIFY`__

### 3.6 `mWidget` 操作函数

* 创建控件的函数

```c
/**
 * A struct wrap the NCS_CREATE_INFO
 * 
 * \note only allowed using in \ref ncsCreateMainWindow
 * Don't use it directly
 *
 * \sa NCS_CREATE_INFO, ncsCreateMainWindow , ncsCreateMainWindowIndirect
 */
typedef struct _NCS_MAIN_CREATE_INFO {
	/**
	 * The class name of a mMainWnd or its child class
	 *
	 * \note if className is NULL or an invalidate class name
	 * \ref ncsCreateMainWindow and ncsCreateMainWindowIndirect 
         *        use \ref CTRL_MINIMAINWND replaced
	 *
	 * \sa CTRL_MINIMAINWND
	 */
	const char* className;
	/**
	 * NCS_CREATE_INFO pointer
	 */
	NCS_CREATE_INFO * create_info;
}NCS_MAIN_CREATE_INFO;

/**
 * \fn mWidget* ncsCreateMainWindow (const char *class_name, const char *caption, 
 * 			DWORD style, DWORD ex_style, \
 * 			int id, int x, int y, int w, int h, HWND host, \
 * 			HICON hIcon, HMENU hMenu, NCS_PROP_ENTRY * props, \
 * 			NCS_RDR_INFO * rdr_info, \
 * 			NCS_EVENT_HANDLER * handlers, \
 * 			DWORD add_data);
 *
 *	\brief create a NCS main window 
 *
 *	\param class_name the class name of widget. 
 *	       the class name must be register by \ref ncsRegisterComponent. 
 *	       And must be \ref CTRL_MINIMAINWND or its dirved class.
 *	\param caption the caption of the main window
 *	\param style  the style of main window
 *	\param ex_style  the extend style of main window
 *	\param id the id of main window
 *	\param x the x position of main window
 *	\param y the y position of main window
 *	\param w the width of main window
 *	\param h the height of main window
 *  \param host the handle of host window, can be NULL
 *  \param hIcon the icon of main window
 *  \param hMenu the menu bar handle 
 *  \param props the properties array pointer, end by {-1, 0} if it's not NULL
 *  \param rdr_info the renderer info pointer
 *  \param handlers the handlers of event array pointer, 
 *               end by {-1, NULL}, if it's not NULL
 *  \param add_data the additional data send to callback \ref NCS_CB_ONCREATE 
 *               and \ref NCS_CB_ONINITDLG
 *
 *  \return mWidget* - a mWidget pointer, must be a mMainWnd instance 
 *
 *  \sa ncsCreateWindow,ncsCreateWindowIndirect, nscCreateMainWindowIndirect, 
 *        NCS_PROP_ENTRY, NCS_RDR_INFO, NCS_EVENT_HANDLER, NCS_CB_ONCREATE, 
 *        mWidget, mInvisibleComponent , mMainWnd
 *
 *  
 */
mWidget* ncsCreateMainWindow (const char *class_name, const char *caption, 
        DWORD style, DWORD ex_style, \
        int id, int x, int y, int w, int h, HWND host, \
        HICON hIcon, HMENU hMenu,
        NCS_PROP_ENTRY * props, \
        NCS_RDR_INFO * rdr_info, \
        NCS_EVENT_HANDLER * handlers, \
        DWORD add_data);

/**
 * A struct include all the creating info, used by ncsCreateWindowIndirect
 *
 * \sa NCS_CREATE_INFO
 */
struct _NCS_WND_TEMPLATE{
	/**
	 * The class name of mComponent, must be registered by \ref ncsRegisterComponent
	 *
	 * \note support \ref mInvisibleComponent class
	 */
	const char*         class_name;
	/**
	 * The id of commponet
	 */
	int                 id;
	/**
	 * The Location and Size of mWidget, ignored if class_name 
         *  is a \ref mInvisibleComponent
	 */
	int                 x, y, w, h;
	/**
	 * The style of mWidget, ignored if class_name is a \ref mInvisibleComponent
	 */
	DWORD               style;
	/**
	 * The extend style of mWidget, ignored if class_name is a \ref mInvisibleComponent
	 */
	DWORD               ex_style;
	/**
	 * The caption of mWidget, ignored if class_name is a \ref mInvisibleComponent
	 */
	const char*         caption;

	//same struct as NCS_CREATE_INFO
	/**
	 * Same as NCS_CREATE_INFO
	 *
	 * \sa NCS_CREATE_INFO
	 */
	NCS_PROP_ENTRY*     props;
	NCS_RDR_INFO*       rdr_info;
	NCS_EVENT_HANDLER*  handlers;
	NCS_WND_TEMPLATE*   ctrls;
	int                 count;
	DWORD               user_data;

	//FIXED ME Maybe I  should not put these two param here
	DWORD				bk_color;
	PLOGFONT			font;
};

//create control window indirect
/**
 * \fn mWidget* ncsCreateWindowIndirect( const NCS_WND_TEMPLATE* tmpl, HWND hParent);
 * \brief create a mComponent by \ref NCS_WND_TEMPLATE,
 *
 * \param tmpl the template pointer
 * \param hParent the parent handle, if NCS_WND_TEMPLATE.class_name 
 *              is a \ref mInvisibleComponent, hParent must releated a mWidget object
 *
 * \return mWidget* - then pointer of object or NULL if failed
 *
 * \sa ncsCreateWindow, NCS_WND_TEMPLATE
 */
mWidget* ncsCreateWindowIndirect( const NCS_WND_TEMPLATE* tmpl, HWND hParent);

/**
 * A struct include all the creating info for ncsCreateMainWindowIndirect,
 *
 * \note same as \ref ncsCreateMainWindow 's params
 *
 * \sa NCS_WND_TEMPLATE, ncsCreateMainWindow
 */
typedef struct _NCS_MAINWND_TEMPLATE{
	const char*         class_name;
	int                 id;
	int                 x, y, w, h;
	DWORD               style;
	DWORD               ex_style;
	const char*         caption;

	NCS_PROP_ENTRY*     props;
	NCS_RDR_INFO*       rdr_info;
	NCS_EVENT_HANDLER*  handlers;
	NCS_WND_TEMPLATE*   ctrls;
	int                 count;
	DWORD               user_data;

	//FIXED ME Maybe I  should not put these two param here
	DWORD				bk_color;
	PLOGFONT			font;

	HICON               hIcon;
	HMENU               hMenu;
}NCS_MAINWND_TEMPLATE;

/**
 * \fn mWidget* ncsCreateMainWindowIndirect(const NCS_MAINWND_TEMPLATE* tmpl, HWND hHost);
 * \biref create a main window from a template
 *
 * \param tmpl - the template of main window
 * \param hHost - the host window handler of the main window
 *
 * \return mWidget * - the Instance of mMainWnd or NULL
 *
 * \sa ncsCreateMainWindow, NCS_MAINWND_TEMPLATE
 */
mWidget* ncsCreateMainWindowIndirect(const NCS_MAINWND_TEMPLATE* tmpl, HWND hHost);
```

* 对象指针和窗口句柄直接的关联操作

```c
/**
 * \fn static inline mWidget* ncsObjFromHandle(HWND hwnd);
 * \brief Get a Object from window handle
 *
 * \param hwnd - the handle of window
 *
 * \return mWidget * the instance releated this handle, or NULL
 */
static inline mWidget* ncsObjFromHandle(HWND hwnd)
{
	if(IsWindow(hwnd))
		return (mWidget*)(GetWindowAdditionalData2(hwnd));
	return NULL;
}

/**
 * \fn static inline mWidget* ncsGetChildObj(HWND hwnd, int id);
 * \breif Get the child object pointer of window 
 *
 * \param hwnd - the handle of window, which can be a normal 
 *                           MiniGUI window or a NCS window
 * \param id - the child id. The child must be a NCS window
 *
 * \return mWidget *  the instance releated id, or NULL
 */
static inline mWidget* ncsGetChildObj(HWND hwnd, int id)
{
	return ncsObjFromHandle(GetDlgItem(hwnd,id));
}

/**
 * \fn static inline mWidget* ncsGetParentObj(HWND hwnd)
 * \brief Get the parent object pointer of window
 *
 * \param hwnd - the handle of child window, which can be a 
 *                           normal MiniGUI window or a NCS window
 * 
 * \return mWidget * the instance of parent of hwnd
 */
static inline mWidget* ncsGetParentObj(HWND hwnd)
{
	return ncsObjFromHandle(GetParent(hwnd));
}
```

### 3.7 `mWidget` 示例

不能直接使用 `mWidget`
