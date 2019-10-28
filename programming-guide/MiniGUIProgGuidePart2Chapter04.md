# Chapter 3 of Part 2 Introduction of the Foundation Class

## mObject

### Introduction of mObject

mObject is the foundation class of all mGNCS, it:
- Encapsulates mGNCS inheritance and virtual function realization 
- Defines the most fundamental class member structure

At the same time, a group of operation functions are defined to control the behavior of class

*The class is foundation class and cannot be used directly*

- Direct child class:
   - mComponent

### Operation Function of mObject 

In NCS, many operations about class have mObject pointer as the parameter, and these are
- Type judgment operation: ncsInstanceOf, equivalent to instanceof of operator of java, case of judging if a pointer is the appointed class

%CODE{cpp}%

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

For the convenience of operation, macro is provided
%CODE{cpp}%
#define INSTANCEOF(obj, clss)  \
          ncsInstanceOf((mObject*)(obj), \
                      (mObjectClass*)(void*)(&Class(clss)))
```

Example

%CODE{cpp}%

   if(INSTANCEOF(obj, mWidget)) //Judge if object obj is a mWidget object
     .....

```

In addition, to judge if a pointer is mObject object, *ncsIsValidObj* can be used
%CODE{cpp}%
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

Corresponding macro is
%CODE{cpp}%
/**
 * \def CHECKOBJ
 * \brief the wrapper of ncsIsValidObj
 *
 * \sa ncsIsValidObj
 */
#define CHECKOBJ(obj)  ncsIsValidObj((mObject*)obj)

```


- Type conversion operation: ncsSafeCast, safe type conversion, similar to dynamic_cast operator of C++
%CODE{cpp}%
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

Corresponding macro is
%CODE{cpp}%
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

Example
%CODE{cpp}%

   // Convert an obj to mWidget pointer
   mWidget * widget = SAFE_CAST(mWidget, obj);

   // If obj is a mWidget type or mWidget child class type, conversion is successful, otherwise widget == NULL
   if(widget)
     ....

```

- Other functions: newObject, deleteOBject, TYPENAME macro.
%CODE{cpp}%
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

To create an object, newObject will be used, because it will call constructor function of the object.

To delete an object, deleteObject will be used, because it will call destructor function of the object

## mComponent

### Introduction of mComponent

mComponent provides the most fundamental realization of component. Component is the most fundamental element of mGNCS program

*The class is foundation class and cannot be used directly*

- Inherited from: mObject
- Direct child class
   - mWidget
   - mInvsbComp

### Method of mComponent

- setProperty <br/>
%CODE{cpp}%
BOOL (*setProperty)(clss *_this, int id, DWORD value);
```
   - Set property of the component
   - Return: TRUE – setting successful; FALSE –setting failed
   - Params
         * int id - ID of property
         * DWORD value – property value

- getProperty <br/>
%CODE{cpp}%
DWORD (*getProperty)(clss *_this, int id);
```
   - Get property of the component
   - Return: property value or DWORD(-1)
   - Params
         * int id – property ID

- setId <br/>
%CODE{cpp}%
int (*setId)(clss *_this, int id);
```
   - Set Id of the component
   - Return: return old Id
   - Params
         * int id - new id

- getId <br/>
%CODE{cpp}%
int (*getId)(clss *_this);
```
   - Get component Id
   - Return: component Id

- getReleated
%CODE{cpp}%
mComponent* (*getReleated)(clss*_this, int releated);
```
   - Get components related to the component, such as parent component, child component and brother component
   - Return: NULL or corresponding component object pointer
   - Params:
         * int releated: relation type: one of NCS_COMP_NEXT, NCS_COMP_PREV, NCS_COMP_PARENT and NCS_COMP_CHILDREN

- setReleated:
%CODE{cpp}%
mComponent* (*setReleated)(clss *_this, mComponent* comp,  int releated); 
```
   - Set associated component
   - Return: associated component pointer after setting, if the setting is not successful, NULL is returned
   - Params
         * mComponent *comp – set component pointer
         * int releated – same as getReletaed

- getChild <br/>
%CODE{cpp}%
mComponent* (*getChild)(clss* _this, int id);
```
   - Get child component appointed by id
   - Return : NULL or corresponding component pointer
   - Params:
         * int id – id of the component to get

### Operation Function of mComponent

Component supports some universal operations
- Event installation and unloading function

%CODE{cpp}%
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

- Register related functions
%CODE{cpp}%
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

## mWidget
### Introduction of mWidget

mWidget is the foundation class of all the controls

- Inherited from mComponent
- Direct child class
   - mStatic
   - mButton
   - mPanel
   - mScrollWidget
   - mProgressBar
   - mPropSheet
   - mSlider
   - mSpinbox

### Style of mWidget 

| *Style ID* | *Property Name of miniStudio* | *Explanation* ||
| NCSS_NOTIFY | Notify | Decide if the control generates Notification event |

### Property of mWidget
| *Property name* |*Property name of miniStudio* | *Type* | *RW* | *Explanation* |
| NCSP_WIDGET_RDR | Renderer |const char* | W | Set current renderer of the control | 
| NCSP_WIDGET_TEXT | Text |const char* | W | Set text content of the current control |
| NCSP_WIDGET_BKIMAGE | BkImage |PBITMAP | RW | Set or get current background image |
| NCSP_WIDGET_BKIMAGE_MODE| BkImageMode | [ImageDrawMode](MStudioMGNCSV1dot0PGAppC#ImageDrawModeValues) | Set or get current background image drawing mode |
| NCSP_WIDGET_BKIMAGE_FILE | - |const char* | Set current background image, and automatically load from the file name |

### Method of mWidget
None

### Event of mWidget

- MSG_NCCREATE
   - Description: the first message of the window when the window non client area is created. Now the window is still not built, and the functions with the window sentence handle as the parameter cannot be called
   - Callback: void (* NCS_CB_ONNCCREATE)(mWidget *);
         * Returned value: none
         * Parameter
            * mWidget * event generator object pointer

- MSG_CREATE
   - Description: generated when the window is created.
   - Callback: typedef BOOL(*) NCS_CB_ONCREATE (mWidget *, DWORD dwAddData)
         * Returned value: TRUE – continue creating; FALSE – exit creating
         * Parameter
            * mWidget *
            * DWORD dwAddData additional data

- Notification message
   - All the events generated from the notification message use the callback
   - void (* NCS_CB_NOTIFY)(mWidget *, int nc_code);
         * Returned value: none
         * Parameter
            * mWidget * event generator object pointer
            * int nc_code : event notification code, used to distinguish different events

*Note: Callback of all the notification events is NCS_CB_NOTIFY*

### Operation Function of mWidget

- Functions that create controls
%CODE{cpp}%
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
 *             DWORD style, DWORD ex_style, \
 *             int id, int x, int y, int w, int h, HWND host, \
 *             HICON hIcon, HMENU hMenu, NCS_PROP_ENTRY * props, \
 *             NCS_RDR_INFO * rdr_info, \
 *             NCS_EVENT_HANDLER * handlers, \
 *             DWORD add_data);
 *
 *    \brief create a NCS main window 
 *
 *    \param class_name the class name of widget. 
 *           the class name must be register by \ref ncsRegisterComponent. 
 *           And must be \ref CTRL_MINIMAINWND or its dirved class.
 *    \param caption the caption of the main window
 *    \param style  the style of main window
 *    \param ex_style  the extend style of main window
 *    \param id the id of main window
 *    \param x the x position of main window
 *    \param y the y position of main window
 *    \param w the width of main window
 *    \param h the height of main window
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
    DWORD                bk_color;
    PLOGFONT            font;
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
    DWORD                bk_color;
    PLOGFONT            font;

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

- Direct associated operation of object pointer and window sentence handle
%CODE{cpp}%
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

### Example of mWidget

mWidget cannot be used directly



[Next](MStudioMGNCSV1dot0PGENP1C2][Previous]] < [[MStudioMGNCSV1dot0PGEN][Index]] > [[MStudioMGNCSV1dot0PGENP2C4)


-- Main.XiaodongLi - 24 Feb 2010