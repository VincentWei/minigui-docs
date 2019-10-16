# 3 Window and Message
Window and message/event are two important concepts in graphics user interface programming. A window is a rectangle region on the screen, and the application uses windows to display the output or accept the user input. Popular GUI programming generally adopts the event driven mechanism. Meaning of event driven is that, program process is not the serial executive line with only an entrance and an exit; in contrast, program will be in a loop status all the time. Program gets some events continuously from outside and inside, such as keystrokes or cursor moving by the user, then responds based on these events and achieves certain functions. The loop would not terminate until it receives a certain message. Generally said, “message queue” and “message loop” are the bottom facility of “event driven”. 

This chapter will describe in detail the window model and the message handling mechanism of MiniGUI, several important functions for handling messages, and the difference between MiniGUI-Threads and MiniGUI-Processes in implementation of message loop.
## 3.1 Window System and Window
### 3.1.1 What Is Window System
Computers with graphics user interface manage the display on the screen of an application by the window system. The components of a graphics user interface usually have the relationship as shown in Fig.3.1.

<center>     <img src="%ATTACHURLPATH%/3.1.jpeg" alt="3.1.jpeg"  ALIGN="CENTER" /> </center>

<center>Fig. 3.1 Components of graphics user interface</center>

The window system is a software system, which helps the user managing and controlling different display environments by dividing the display screen into different parts. The window system provides a working model based on windows, and each window is a rectangle region on the screen and is parallel to the boundary of screen. Applications can own one or more windows. The window system generally adopts the concept and mechanism of “overlap windows” to manage windows display and individual windows are overlapped on the screen. The window system overcomes the shortcomings of older terminal machines that only one job can be done on one screen; The window system makes the user able to monitor several jobs simultaneously on one screen, and switch between the jobs conveniently as well.

### 3.1.2 Concept of Window
A window is a rectangle region on the screen. In traditional windowing system model, the vision part is comprised of one or more windows. Each window represents one drawing region on the screen, and the windowing system controls the mapping of the drawing region to the actual screen, that is, to control the position, size, and vision region of the window. Each window is allocated a screen drawing region to display part or whole of the window, even if it is not allocated screen region at all (this window is overlapped and hidden by other overlap windows).

Overlapping windows on the screen generally has the following relationship:
- Windows are generally organized in the form of hierarchy (or form of tree structure).
- The root window is the ancestor of all windows, and occupies the whole screen; it is also referred as desktop window.
- All the other windows have parent windows except the root window, and each window may have child windows, brother windows, ancestor windows, or descendant windows etc.
- A child window is contained in a parent window, and the child windows of the same parent window are regarded as windows of the same level.
- The visibility of overlapped windows depends on their relationship. A window is visible only when its parent window is visible, and its parent window can clip a child window.
- Windows of the same level can be overlapped, but only one window can be outputted to the overlapped region at a time.
- A frame window/main window comprises a usable client region and a decorate region (also referred as “non client region”) managed by the windowing system.
- A child window of the desktop window is generally a frame window.
- Windows have subordinate relationship, that is, their owner determines the life cycle and visibility of some windows. A parent window generally owns their child windows.

An application window usually includes the following parts:
- A visible border.
- A window ID, which is used by programs to operate the window and is referred as “window handle” in MiniGUI.
- Some other characteristics, such as, height, width and background color etc.
- Additional window elements such as menu and scrollbars may exist.

## 3.2 Window of MiniGUI
### 3.2.1 Window Type
MiniGUI has three window types: main window, dialog box, and control window (child window). Each MiniGUI application generally creates a main window, which is used as the main interface or start interface of the application. The main window generally includes some child windows, and these child windows are generally control windows or user-defined window classes. An application can also create windows of other types such as dialog box or message box. A dialog box is actually a main window, and the application usually prompts the user to perform input operation within a dialog box. Message box is built-in dialog box used to display some prompt or warning for the user.

<center>     <img src="%ATTACHURLPATH%/3.2.jpeg" alt="3.2.jpeg"  ALIGN="CENTER" /> </center>

<center>Fig. 3.2 Typical main windows (classic style) of MiniGUI</center>

<b>[Prompt] You can change the appearance style of MiniGUI window when configuring MiniGUI. Fig. 3.2, Fig. 3.3 illustrates display effect with different styles. Please refer to MiniGUI User Manual for relative information about MiniGUI appearance styles.</b>

<center>     <img src="%ATTACHURLPATH%/3.3.jpeg" alt="3.3.jpeg"  ALIGN="CENTER" /> </center>

<center>Fig. 3.3 A typical dialog box (flat style) of MiniGUI</center>

### 3.2.2 Creation of Main Window
The main window in MiniGUI has no concept of window class; you should initialize a MAINWINCREATE structure, and then call CreateMainWindow function to create a main window. Meanings of the members of MAINWINCREATE structure are as follow:

```
CreateInfo.dwStyle	the style of the window
CreateInfo.spCaption	the caption of the window
CreateInfo.dwExStyle	the extended style of the window
CreateInfo.hMenu	the handle of the menu attached to the window
CreateInfo.hCursor	the handle of the cursor of the window
CreateInfo.hIcon	the icon of the window
CreateInfo.MainWindowProc	the window procedure of the window
CreateInfo.lx	absolute x-coordinate of upper-left corner of window relative to screen in pixel
CreateInfo.ty	absolute y-coordinate of upper-left corner of window relative to screen in pixel
CreateInfo.rx	absolute x-coordinate of lower-right corner of window relative to screen in pixel
CreateInfo.by	absolute x-coordinate of lower-right corner of window relative to screen in pixel
CreateInfo.iBkColor	the background pixel value of the window
CreateInfo.dwAddData	a 32-bit additional value attached to the window
CreateInfo.hHosting	the handle of the hosting window of the window
```
Wherein the following members need to be illustrated specially:

1. CreateInfo.dwAddData: During C language coding, static variables should be reduced as far as possible, but how to transfer parameters to window without using static variables? At this situation, you can use this field. This field is a 32-bit value; therefore all the parameters needed to transfer to the window can be organized into a structure, and assigns the pointer to this structure to this field. In a window procedure, the pointer can be obtained by using GetWindowAdditionalData function, so that the parameters that needed to be transferred can be obtained.

2. CreateInfo.hHosting: This field means the message queue of which main window is used for the main window to be created. We call the main window as a “hosted” main window when it uses message queue of other main window. Concept of host is very important in MiniGUI, and the following rules should generally be obeyed:
- MiniGUI-Threads: The hosting window of the first main window created by each thread in MiniGUI-Threads must be the desktop, namely HWND_DESKTOP. Other windows of this thread must adopt the existed main window belonging to the same thread as the hosting window. The system creates a new message queue when the hosting window is HWND_DESKTOP, while uses the message queue of the hosting window when a non-desktop window is specified as hosting window. That is to say, all the main windows of the same thread should use the same message queue.
- All the main windows in MiniGUI-Processes should specify hosting window according to similar rules, therefore it is enough to regard all main window as belonging to the same thread.

There are two functions on the above mentioned can create one main window, one is CreateMainWindow, another is CreateMainWindowEx.
CreateMainWindow's function prototype is:

```cplusplus
HWND GUIAPI CreateMainWindow (PMAINWINCREATE pCreateInfo)
```
We can create a main window if passes a given assigned pCreateInfo, a pointer to structure.

CreateMainWindowEx's function prototype is:
```cplusplus
HWND GUIAPI CreateMainWindowEx (PMAINWINCREATE pCreateInfo,
                        const char* werdr_name, const WINDOW_ELEMENT_ATTR* we_attrs,
                        const char* window_name, const char* layer_name);
```
All other arguments' value can be NULL except the pointer to the structure, pCreateInfo, in this function. It equals to CreateMainWindow when the last four arguments' value are NULL. You can set the name of renderer and some arguments in CreateMainWindowEx. Please refer to "Look and Feel Render and the property of window element" in chapter 11, "Look and Feel, Effects", for more details. window_name and layer_name are reserved arguments, please just set them as NULL.

### 3.2.3 Window Style
Window style is used to control some appearances and behaviors of windows, such as border type of window, visibility of window, and usability of window etc. In MiniGUI, window styles can be divided to normal style and extended style, which is specified by dwStyle and dwExStyle argements. We will describe the special style of controls in following Part III of this guide. Some common styles are listed in Table 3.1. The identifiers for these styles are defined in minigui/window.h, with prefix of WS_ or WS_EX.

                         <center>Table 3.1  Common styles of a window</center>

|*Style identifier* | *Meaning* | *Comment* |
|WS_NONE | no any style | |
|WS_VISIBLE | creating initially visible window | |
|WS_DISABLED | creating initially disabled window | |
|WS_CAPTION | creating main window with caption | limited to main window |
|WS_SYSMENU | creating main window with system menu | limited to main window |
|WS_BORDER | creating window with border | |
|WS_THICKFRAME | creating window with thick border | |
|WS_THINFRAME | creating window with thin border | |
|WS_VSCROLL | creating window with vertical scroll bar  | |
|WS_HSCROLL | creating window with horizontal scroll bar | |
|WS_MINIMIZEBOX | caption bar with the minimization button | limited to main window |
|WS_MAXIMIZEBOX | caption bar with maximization button  | limited to main window |
|WS_EX_NONE | no extended style | |
|WS_EX_USEPRIVATECDC | using private DC | limited to main window |
|WS_EX_TOPMOST | creating main window always on top-most | limited to main window |
|WS_EX_TOOLWINDOW | creating ToolTip main window | limited to main window. ToolTip main window wouldn’t own input focus, but can receive mouse information |
|WS_EX_TRANSPARENT | transparent window | limited to partial controls, such as the List Box, List View and Tree View. |
|WS_EX_USEPARENTFONT | using the font of the parent as the default font |  |
|WS_EX_USEPARENTCURSOR | using the icon of the parent as the default icon |  |
|WS_EX_NOCLOSEBOX | caption bar without close button |  |
|WS_EX_CTRLASMAINWIN | creating control which can be displayed out of main window | limited to specific controls. |
|WS_EX_TROUNDCNS  | creating a window which has rounded top left and right corners | |
|WS_EX_BROUNDCNS  | creating a window which has rounded lower left and right corners | |
|WS_EX_CLIPCHILDREN | the region of the child will be clipped when paint the parent’s client area. | This style will cause additional memory demand and impact the render efficiency. So only use this style when the window output overlap with child window output. General dialog window and property control don't need this style. |

### 3.2.4 Create Irregular Window
You can use SetWindowMask to create irregular window or control after the window or control is created.

```cplusplus
BOOL GUIAPI SetWindowMask (HWND hWnd, const MYBITMAP* new_mask)
```
new_mask argement is a MYBITMAP structure, application should use the transparency in MYBITMAP structure to indicate the mask. It means transparent pixel is outside the created main window, the position of transparent pixel will display background color.

The following codes show how to create irregular window.

```cplusplus
    pal = (RGB *)malloc (256 * sizeof (RGB));
    LoadMyBitmap (&mybmp, pal, "11.bmp");

//set the transparent code in palette, the code of white is 255
mybmp.transparent = 255;

    hMainWnd = CreateMainWindow (&CreateInfo);
    if (!SetWindowMask(hMainWnd, &mybmp))
        return -1;
    InvalidateRect(hMainWnd, NULL, TRUE);
    if (hMainWnd == HWND_INVALID)
        return -1;
```

<center>     <img src="%ATTACHURLPATH%/WindowMask.png" alt="WindowMask.png"  ALIGN="CENTER" /> </center>
<center>Fig. 3.4 a irregular window (transparent color is white)</center>

The following codes show how to create irregular control.
```cplusplus
            pal = (RGB *)malloc (256 * sizeof (RGB));
            LoadMyBitmap (&mybmp, pal, "./33.bmp");

//set the transparent code in palette, the code of white is 255
            mybmp.transparent = 255;
            btn1 = CreateWindowEx(
        CTRL_MLEDIT,"",
        WS_VISIBLE | WS_BORDER | WS_VSCROLL 
            | ES_BASELINE | ES_AUTOWRAP | ES_NOHIDESEL | ES_NOHIDESEL,
                    WS_EX_TROUNDCNS,
                    0,
                    0, 0, mybmp.w, mybmp.h,
                    hWnd, 0);

            if (!SetWindowMask(btn1, &mybmp))
                return -1;
            SetWindowBkColor(btn1, PIXEL_red); 

```

<center>     <img src="%ATTACHURLPATH%/EditMask.png" alt="EditMask.png"  ALIGN="CENTER" /> </center>
<center>Fig. 3.5 a MultiLineEdit which's background color is red</center>

For creating irregular window or control, you can also call the following functions to change existing window or color's visible area besides above method.
```cplusplus
HWND GUIAPI SetWindowRegion (HWND hwnd, const REGION* region);
```

Example:
```cplusplus
HWND btn;
            btn = CreateWindow (CTRL_BUTTON,
                    0, 
                    WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_SORT | LBS_MULTIPLESEL | WS_VSCROLL, 
                    0, 
                    100, 140, 200, 100, hWnd, 0);

            BLOCKHEAP cliprc_heap;
            CLIPRGN circle_rgn;

            InitFreeClipRectList (&cliprc_heap, 50);
            InitClipRgn (&circle_rgn, &cliprc_heap);
            InitCircleRegion (&circle_rgn, 20, 20, 20);

            if (!SetWindowRegion (btn, &circle_rgn))
                printf ("Error calling SetWindowRegion. \n");

            EmptyClipRgn (&circle_rgn);
            DestroyFreeClipRectList (&cliprc_heap);
```

<center>     <img src="%ATTACHURLPATH%/RoundBtn.png" alt="RoundBtn.png"  ALIGN="CENTER" /> </center>
<center>Fig. 3.6 circle button</center> 

MiniGUI created two extended styles,  WS_EX_TROUNDCNS and WS_EX_BROUNDCNS, to implement rounded-corner window for convenience. You can just add these two styles to implement this kind of irregular window without calling SetWindowMask and SetWindowRegion.

Example:
```cplusplus
int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

    CreateInfo.dwStyle = 
        WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE | WS_EX_TROUNDCNS | WS_EX_BROUNDCNS;
    CreateInfo.spCaption = HL_ST_CAP;
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 320;
    CreateInfo.by = 240;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;
    
    hMainWnd = CreateMainWindow (&CreateInfo);
    
    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);

    return 0;
}
```
<center>     <img src="%ATTACHURLPATH%/RoundWindow.png" alt="RoundWindow.png"  ALIGN="CENTER" /> </center>
<center>Fig. 3.7 rounded-corner window</center>

### 3.2.5 Destroying Main Window
DestroyMainWindow function can be used to destroy a main window. This function sends MSG_DESTROY message to the window procedure, and terminates the destroy process when the message return a non-zero value.

Application generally calls this function to destroy a main window when receiving MSG_CLOSE message in main window procedure, and then calls PostQuitMessage message to terminate the message loop, as shown below:

```cplusplus
case MSG_CLOSE:
    //Destroy main window
    DestroyMainWindow (hWnd);
    //Send MSG_QUIT message
    PostQuitMessage(hWnd);
    return 0;
```
DetroyMainWindow destroys a main window, but does not destroy the message queue used by the main window and the window object itself. So, the application should use MainWindowCleaup to finally destroy the message queue used by the main window and the window object itself at the end of thread or process.

MiniGUI will call DetroyMainWindow to destroy all hosted windows when a main window is destroyed.

### 3.2.6 Dialog Box
A dialog box is a special main window, which is usually created by DialogBoxIndirectParam function in an application:
```cplusplus
int  GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate,
                    HWND hOwner, WNDPROC DlgProc, LPARAM lParam);
```
The dialog box created by this function is called as model dialog box. Users need to prepare dialog box template and window procedure function of dialog box for this function. Above function is compatible with DialogBoxIndirectParamEx.
```cplusplus
MG_EXPORT int GUIAPI DialogBoxIndirectParamEx (PDLGTEMPLATE pDlgTemplate,
        HWND hOwner, WNDPROC DlgProc, LPARAM lParam,
        const char* werdr_name, WINDOW_ELEMENT_ATTR* we_attrs,
        const char* window_name, const char* layer_name);

static inline int GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate,
        HWND hOwner, WNDPROC DlgProc, LPARAM lParam)
{
    return DialogBoxIndirectParamEx (pDlgTemplate, hOwner, DlgProc, lParam,
                                    NULL, NULL, NULL, NULL);
}
```
DialogBoxIndirectParamEx is a more powerful dialog box create function, it can not only specify dialog box template and dialog box's window procedure function but also can specify renderer and related render arguments, get dialog box look and feel in different style. We will describe it in details later.

We will describe the basic programming technique for dialog box in Chapter 4 in this guide.

### 3.2.7 Control and Control Class
Each control of MiniGUI is an instance of a certain control class, and each control class has a corresponding control procedure, which is shared by all control instance of the same class.

The definition of control class in MiniGUI is as follows:

```cplusplustypedef struct _WNDCLASS
{
    /** the class name */
    char*   spClassName;

    /** internal field, operation type */
    DWORD   opMask;

    /** window style for all instances of this window class */
    DWORD   dwStyle;

    /** extended window style for all instances of this window class */
    DWORD   dwExStyle;

    /** cursor handle to all instances of this window class */
    HCURSOR hCursor;

    /** background color pixel value of all instances of this window class */
    int     iBkColor;

    /** window callback procedure of all instances of this window class */
    int     (*WinProc) (HWND, int, WPARAM, LPARAM);

    /** the private additional data associated with this window class */
    DWORD dwAddData;
} WNDCLASS;
typedef WNDCLASS* PWNDCLASS;
```
The main elements of control class are as follow:
- Class name spClassName: class name different from other control classes.
- Window procedure function WinProc: all control instances of this class use this window procedure function, which handles all the messages posted/sent to the control and define appearance, behavior, and features of the controls.
- Class style dwStyle: define the style such as the appearance and behavior, and all instances of this class have this normal style.
- Extension style dwExStyle: define the extension style of the window, and all instances of this class have this extension style.
- Class cursor hCursor: define the shape of the cursor of the control class.
- Background color iBkColor: define the pixel value of the background color of the control class.
- Class private additional data dwAddData: additional space reserved for the class by MiniGUI.

Functions related to control class operation in MiniGUI are as follow:

```cplusplus
BOOL GUIAPI RegisterWindowClass (PWNDCLASS pWndClass) ;
```

This function registers a control class.
```cplusplus
BOOL GUIAPI UnregisterWindowClass (const char *szClassName) ;
```

This function unregisters a control class.
```cplusplus
const char* GUIAPI GetClassName (HWND hWnd) ;
```

This function retrieves the class name of a specific control.
```cplusplus
BOOL GUIAPI GetWindowClassInfo (PWNDCLASS pWndClass) ;
```

This function retrieves the class information of a specific control class.
```cplusplus
BOOL GUIAPI SetWindowClassInfo (const WNDCLASS *pWndClass) ;
```

This function sets the class information of a specific control class.

The following code illustrates how to use WNDCLASS structure, RegisterWindowClass function, and UnregisterWindowClass function to register a user-defined control class in application:
```cplusplus
/* Define the name of control class */
#define MY_CTRL_NAME "mycontrol"

static int MyControlProc (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    switch (message) {
    case MSG_PAINT:
        /* Only output “hello, world! – from my control” */
        hdc = BeginPaint (hwnd);
        TextOut (hdc, 0, 0, "Hello, world! – from my control");
        EndPaint (hwnd, hdc);
        return 0;
    }

    return DefaultControlProc (hwnd, message, wParam, lParam);
}

/* This function registers “mycontrol” control into MiniGUI */
static BOOL RegisterMyControl (void)
{
    WNDCLASS MyClass;

    MyClass.spClassName = MY_CTRL_NAME;
    MyClass.dwStyle     = 0;
    MyClass.hCursor     = GetSystemCursor (IDC_ARROW);
    MyClass.iBkColor    = COLOR_lightwhite;
    MyClass.WinProc     = MyControlProc;

    return RegisterWindowClass (&MyClass);
}

/* Unregister the control from system */
static void UnregisterMyControl (void)
{
    UnregisterWindowClass (MY_CTRL_NAME);
}
```
The control class created above only implements a task, namely displaying “Hello, world!” after creating a control instance. The general process of using the user-defined control class in a user’s application is as follows:

```cplusplus
/* Register the control class */
RegisterMyControl();

...

/* Creat an instance of the control class in a certain main window */
hwnd = CreateWindow (MY_CTRL_NAME, “”, WS_VISIBLE, IDC_STATIC, 0, 0, 200, 20, parent, 0);

...

/* Destroy the control and unregister the control class after using it */
DestroyWindow (hwnd);
UnregisterMyControl();
```
The window shown in Fig. 3.8 creates an instance of the user-defined control class described above, in which “Hello, world! - from my control.” is displayed. Please refer to mycontrol.c file in the demo program package mg-sample of this guide to get the complete list of this program.

<center>     <img src="%ATTACHURLPATH%/3.4.jpeg" alt="3.4.jpeg"  ALIGN="CENTER" /> </center>
<center>Fig. 3.8 Display “Hello, world!” using the user-defined control</center>

We will describe in detail the foundation knowledge of control programming in Chapter 5; and discusses the advanced programming techniques related to controls in Chapter 6. We will introduce all predefined controls of MiniGUI in Part IV in this guide.

### 3.2.8 Input Method
Input method is the mechanism introduced by MiniGUI for supporting multi-byte char-sets such as Chinese, Korean, and Japanese etc. It is similar to the input method in windows system. Input method generally appears in a form of a window in the top-most, catches the key down message of the system and performs appropriate handling, and sends the translated characters to the current active window. In MiniGUI 3.0, input method has been enhanced and divided as a component to user. Please see introduction of mGi component for details.

## 3.3 Message and Message Handling
### 3.3.1 Message
MiniGUI application communicates with the outside by receiving messages. Messages are generated by the system or the application itself. The system generates messages for input events, and also generates messages for corresponding to applications. Applications can complete a certain task or communicate with other windows by sending messages. Generally speaking, MiniGUI is a message driven system, in which all the operations are performed around messages.

System sends messages to the window procedure of application. Window procedure has four arguments: window handle, message identifier and two 32-bit message parameters. Window handle determines the target window to which messages are sent, through which MiniGUI determines to which window procedure the massages are sent. Message identifier is an integer constant, which identifies the type of a message. If window procedure receives a message, it determines the type of the message and how to handle it according to the message identifier. Message parameters give further description of the message contents, meaning of which usually depends on the message itself. It can be an integer, a flag or a pointer to a data structure. For example, for mouse message, lParam usually includes the position information of the mouse, while wParam parameter includes the correspondence status information of SHIFT keys when the message happens. For other different message types, wParam and lParam also have clear definition. Applications usually need to check message parameters to determine how to handle the message.

It has been mentioned in Chapter 2 that a message is defined in MiniGUI as follows (minigui/window.h):
```cplusplus
typedef struct _MSG
   {
       HWND             hwnd;
       int              message;
       WPARAM           wParam;
       LPARAM           lParam;
       unsigned int    time;
   #ifndef _LITE_VERSION
       void*            pAdd;
   #endif
   }MSG;
   typedef MSG* PMSG;

```
Members of MSG message structure include the window that the message belonging to (hwnd), message identifier (message), WPARAM type parameter (wParam) of the message, LPARAM type parameter (lParam) of message and the time when the message happens.

### 3.3.2 Message Type
The predefined general messages of MiniGUI have the following types:
- System messages: include MSG_IDLE, MSG_TIMER, and MSG_FDEVENT etc.
- Dialog box messages: include MSG_COMMAND, MSG_INITDIALOG, MSG_ISDIALOG, MSG_SETTEXT, MSG_GETTEXT, and MSG_FONTCHANGED etc.
- Window painting messages: include MSG_PAINT and MSG_ERASEBKGND etc.
- Window creating and destroying messages: include MSG_CREATE, MSG_NCCREATE, MSG_DESTROY, and MSG_CLOSE etc.
- Keyboard and mouse event messages: include MSG_KEYDOWN, MSG_CHAR, MSG_LBUTTONDOWN, and MSG_MOUSEMOVE etc.
- Keyboard/mouse post-handling messages: include MSG_SETCURSOR, MSG_SETFOCUS, MSG_KILLFOCUS, MSG_MOUSEMOVEIN etc., which is the window event message caused by mouse/keyboard messages. 
You can define messages yourself, and define the meaning of wParam and lParam. To let users be able to define messages themselves, MiniGUI defines MSG_USER macro, and application can define its own messages as follow:

```cplusplus
#define MSG_MYMESSAGE1    (MSG_USER + 1)
#define MSG_MYMESSAGE2    (MSG_USER + 2)
```
You can use the user-defined message in your programs, and transfer data by using your customized messages.

### 3.3.3 Message Queue
MiniGUI has the following two methods for sending messages to a window procedure:
- Post the message to a first-in-first-out message queue, which is a memory region for storing messages in system with each message stored in a message structure;
- Or send the message directly to window procedure, i.e. call window procedure function directly through message sending function.

Messages posted into message queue are mainly the mouse/keyboard event messages from mouse and keyboard input, such as MSG_LBUTTONDOWN, MSG_MOUSEMOVE, MSG_KEYDOWN, and MSG_CHAR etc. Messages posted into message queue also include time message MSG_TIMER, paint message MSG_PAINT and exit message MSG_QUIT etc.

Why need message queue? We know that system displays multiple application windows simultaneously, and device driver generates mouse and keyboard messages continuously when the user moves the mouse or clicks the keyboard. These messages need to be sent to the corresponding application and window for handling. With message queue, system can manage various events and messages better, and the communication between system and applications becomes more convenient. 

System posts messages to a message queue of the application by filling a MSG structure and then copying it to the message queue. Information in the MSG structure is as described above, including the target window handle of the message, the message identifier, two message parameters, and message time.

An application can get a message from its message queue through GetMessage function; this function fills a MSG message structure with information of the message. An application can also call HavePendingMessage function to check whether there exists any message in the message queue, which is not gotten out.

```cplusplus
int GUIAPI GetMessage (PMSG pMsg, HWND hWnd);
BOOL GUIAPI HavePendingMessage (HWND hMainWnd);
```
Messages that don’t queue up are sent to the window procedure of the target window directly without trough message queue. System generally completes some events that need to be handled immediately by sending messages that don’t queue up, such as MSG_ERASEBKGND message.

### 3.3.4 Message Handling
An application must handle the messages that are posted to its message queue in time. Application generally handles the messages in the message queue through message loop in MiniGUIMain function.

A message loop is a loop, in which the program gets messages from the message queue continuously, then dispatches the message to a specified window through DispatchMessage function, namely, calls the window procedure of the specified window and passes the message parameters. A typical message loop is as follows:
```cplusplus
MSG  Msg;
HWND hMainWnd;
MAINWINCREATE CreateInfo;

InitCreateInfo (&CreateInfo);

hMainWnd = CreateMainWindow (&CreateInfo);
if (hMainWnd == HWND_INVALID)
        return -1;

while (GetMessage (&Msg, hMainWnd)) {
       TranslateMessage (&Msg);
       DispatchMessage (&Msg);
}
```

As shown above, an application starts a message loop after creating the main window. GetMessage function gets a message from the message queue to which the hMainWnd window belongs, and then calls TranslateMessage function to translate the keystroke messages of MSG_KEYDOWN and MSG_KEYUP into character message MSG_CHAR, and finally calls DispatchMessage function to dispatch the message to the specific window in the end.

GetMessage will not return until getting a message from the message queue, and generally return a non-zero value; it will return 0 if the gotten message is MSG_QUIT, thereby terminates the message loop. Terminating the message loop is the first step to close an application, and the application generally quits message loop by calling PostQuitMessage function.

Under MiniGUI-Threads, we can use HavePendingMessage function when we need to return immediately to handle other works during waiting messages. For example:
```cplusplus
 do {
        /* It is time to read from master pty, and output. */
        ReadMasterPty (pConInfo);

        if (pConInfo->terminate)
            break;

        while (HavePendingMessage (hMainWnd)) {
            if (!GetMessage (&Msg, hMainWnd))
                break;
            DispatchMessage (&Msg);
        }
    } while (TRUE);
```
When the program above cannot get any message or get a MSG_QUIT message, it will return immediately and call ReadMasterPty function to read data from a certain file descriptor.

Under MiniGUI-Thread, each GUI thread, which creates window, has its own message queue; furthermore, all windows belonging to the same thread share the same message queue. So GetMessage function will get all messages of the windows belonging to the same thread with hMainWnd window. Whereas, there is only a message queue under MiniGUI-Processes, GetMessage gets all messages from this message queue, and ignores hMainWnd parameter. A message queue needs only a message loop, no matter how many windows the application has. DispatchMessage function can dispatch the message to its target window because the MSG message structure includes the target window handle of a message.

What DispatchMessage does is to get the window procedure of the target window of the message, and then call the window procedure function directly to handle the message.

The window procedure is a function of special type, which is used for receiving and handling all the messages sent to the window. Each control has a window procedure, all controls belonging to the same control class share the same window procedure to handle messages.

Generally, window procedure must pass a message to system for default handling if the window procedure does not handle this message. The main window procedure generally calls DefaultMainWinProc(PreDefMainWinProc as default) to complete the default handling work for the message, and returns the return value of the function:
```cplusplus
int PreDefMainWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```
Most window procedures only handle messages of several types, and other messages are handled by system through DefaultMainWinProc.

The default message handling of dialog boxes is completed by DefaultDialogProc(PreDefDialogProc as default) function:
```cplusplus
int PreDefDialogProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```
The default message handling of a control is completed by DefaultcontrolProc (PreDefControlProc as default) function:
```cplusplus
int PreDefControlProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
```

### 3.3.5 Sending and Posting Message
Posting (mailing) a message is to copy the message into message queue, and sending a message is to send the message to window procedure function.

Several important message handling functions in MiniGUI are listed below.

PostMessage: This function posts a message to the message queue of a specific window and then returns immediately. This form is called “posting message”. If the posting message buffer of the message queue is full, the function will return an error value. The window will not handle the message until GetMessage function gets the message. PostMessage is usually used for posting some non-key messages. For example, mouse and keyboard messages are posted by PostMessage function in MiniGUI.

SendMessage: Application usually informs the window procedure to complete a certain task immediately by sending a message. This function is different from PostMessage function in that it sends a message to the window procedure of a specific window and will not return until the window procedure handles the message. When it needs to know the handling result of a certain message, you should use this function to send the message, and then perform handling according to the return value of the function. In MiniGUI-Threads, if the thread to send messages is not the same as the thread to receive messages, the sender thread will be blocked and wait the handling result of another thread, and then continue to run; if the thread sender is the same as the receiver thread, the window procedure function of the window which receives message is called directly like SendMessage in MiniGUI-Processes.

SendNotifyMessage: Similar to PostMessage message, this function returns immediately without waiting the message to be handled. But it is different from PostMessage message in that the messages sent by this function will not be lost due to full of the buffer because system adopts a linked-list to maintain messages of this type. The messages sent by this function are called “notification message”, which is generally used to send notification messages from a control to its parent window.

PostQuitMessage: This message will set a QS_QUIT flag in the message queue. GetMessage will check the flag when getting a message from a specific message queue. If the flag is QS_QUIT, GetMessage message will return zero; thus this return value can be used to terminate the message loop.

The following are some other message handling functions:

```cplusplus
int GUIAPI BroadcastMessage ( int iMsg, WPARAM wParam, LPARAM lParam );
```
This function broadcasts a message to all main windows on the desktop.

```cplusplus
int GUIAPI ThrowAwayMessages (  HWND pMainWnd );
```
This function removes all the messages in the message queue associated with a window, and returns the number of removed messages.

```cplusplus
BOOL GUIAPI WaitMessage ( PMSG pMsg, HWND hMainWnd );
```
This function waits for the message in the message queue of the main window, and it will return as soon as there is a message in the queue. Unlike the GetMessage function, this function doesn’t remove the message from the message queue.

### 3.3.6 Message Handling Function Specific to MiniGUI-Processes
MiniGUI defines some message handling functions specific to MiniGUI-Processes, which can be used to send messages from the MiniGUI-Processes server program to other client programs.

```cplusplus
int GUIAPI Send2Client ( MSG * msg,  int cli );
```
Send2Client function sends a message to a specified client. The function is defined for MiniGUI-Processes and can only be called by the server program mginit.

Msg is a pointer to a message structure; cli can either be the identifier of the target client or one of the following values:
- CLIENT_ACTIVE: The current active client on the topmost layer.
- CLIENTS_TOPMOST: All clients in the topmost layer.
- CLIENTS_EXCEPT_TOPMOST: All clients except clients in the topmost layer.CLIENTS_ALL: All clients.
Return values:
- SOCKERR_OK: Read data successfully.
- SOCKERR_IO: There are some I/O errors occurred.
- SOCKERR_CLOSED: The peer has closed the socket.
- SOCKERR_INVARG: You passed invalid arguments

```cplusplus
BOOL GUIAPI Send2TopMostClients (  int iMsg, WPARAM wParam, LPARAM lParam );
```
Send2TopMostClients sends a message to all clients in the topmost layer. The function is defined for MiniGUI-Processes and can only be called by the server program mginit.
```cplusplus
BOOL GUIAPI Send2ActiveWindow (const MG_Layer* layer,
                 int iMsg, WPARAM wParam, LPARAM lParam); 
```
Send2ActiveWindow  function sends a message to the current active window in the specific layer. The function is defined for MiniGUI-Processes and can only be called by the server program mginit.

Generally speaking, the message sent from the server to a client will be sent to the virtual desktop of the client in the end, and handled by the virtual desktop window procedure, which is similar to that MiniGUI-Threads program receives the events from the keyboard and mouse.

MiniGUI-Processes also defines a special message - MSG_SRVNOTIFY. The server can send this message and its parameters to the specified client, and the desktop of the client will broadcast the message to all main windows of the client after receiving the message.

## 3.4 Several Important Messages and Corresponding Handling
Several import messages need to be handled carefully in the life cycle of windows (include main windows and child windows). Concepts and typical handling of these messages will be described below.

### 3.4.1 MSG_NCCREATE 
This message is sent to window procedure during MiniGUI creates a main window. The parameter lParam is the pointer to pCreatInfo structure passed to CreateMainWindow. You can modify some values in pCreateInfo structure during the message is being handled. It should be noted that the window object has not been created when the system sends the message to the window procedure, so the window device context can not be gotten by functions, such as GetDC etc., during the messages is being handled, and child window can not be created in MSG_NCCREAT message.

For the input method window, you must register the input method window during handling the message, for example:

```cplusplus
case MSG_NCCREATE:
            if (hz_input_init())
                /* Register before show the window. */
                SendMessage (HWND_DESKTOP, MSG_IME_REGISTER, (WPARAM)hWnd, 0);
            else
                return -1;
        break;
```

### 3.4.2 MSG_SIZECHANGING 
This message is sent to the window procedure to determine the size of the window when the size of the window is changing or a window is being created. The parameter wParam includes the expected size of the window, while lParam is used to save result value. The default handling of MiniGUI is as follows:

```cplusplus
case MSG_SIZECHANGING:
    memcpy ((PRECT)lParam, (PRECT)wParam, sizeof (RECT));
    return 0;
```
You can catch the message handling to let the window to be created locate in the specific position or has a fixed size, for example, the spin box control handle the message in order to have a fixed size:

```cplusplus
case MSG_SIZECHANGING:
{
    const RECT* rcExpect = (const RECT*) wParam;
    RECT* rcResult = (RECT*) lPraram;

    rcResult->left = rcExpect->left;
    rcResult->top = rcExpect->top;
    rcResult->right = rcExpect->left +  _WIDTH;
    rcResult->bottom = rcExpect->left +  _HEIGHT;
    return 0;
}

```
### 3.4.3 MSG_SIZECHANGED 和 MSG_CSIZECHANGED
This message is sent to the window procedure to determine the size of client region of the window when the size of a window is changed. The parameters of this message are similar to MSG_SIZECHANGING. WParam includes the size of the window, while lParam is a pointer to a RECT object used to save the size of client region of the window and has a default value. If handling of the message returns a non-zero value, the size value in the lParam will be used as the size of the client region; otherwise, the message handling will be ignored. For example, the message is handled to let the client region occupy the entire window rectangle in spin box control:

```cplusplus
case MSG_SIZECHANGED
{
    RECT* rcClient = (RECT*) lPraram;

    rcClient->right = rcClient->left  +  _WIDTH;
    rcClient->bottom = rcClient->top +  _HEIGHT;
    return 0;
}

```
MSG_CSIZECHANGED message is a notification message sent to the window after the size of the client area of the window has changed. You can handle this message to reflect the new size of the client area. The parameters wParam and lParam of this message contain the new width and new height of the client area respectively.

### 3.4.4 MSG_CREATE 
This message is sent to the window procedure after the window is created successfully and added to the window management module of MiniGUI. At this time, applications can create child windows. If the message returns non-zero value, the newly created window will be destroyed.

---+++3.4.5  MSG_FONTCHANGING
The message is sent to the window procedure when the application calls SetWindowFont to change the default font of the window. In general, the application will pass this message to the default window procedure; but if the window does not allow the user to change the default font, the message can be caught and a non-zero value is returned. For example, the simple edit box of MiniGUI can only deal with equal width font, so the message can be handled as follows:

```cplusplus
case MSG_FONTCHANGING:
            return -1;

```
SetWindowFont function will terminate handling and return after application handles the message and returns a non-zero value, that is to say, the default font of the window will not be changed.

### 3.4.6 MSG_FONTCHANGED
This message will be sent to the window procedure when the application calls SetWindowFont and has changed the default font of the window. At this time, the window procedure should perform some handling to reflect the new font set. For example, the edit box of MiniGUI will deal with this message, and redraw the edit box ultimately:
```cplusplus
case MSG_FONTCHANGED:
        {
            sled =(PSLEDITDATA) GetWindowAdditionalData2 (hWnd);

            sled->startPos = 0;
            sled->editPos = 0;
            edtGetLineInfo (hWnd, sled);

            /* Recreate the caret appropraite for the new font */
            DestroyCaret (hWnd);
            CreateCaret (hWnd, NULL, 1, GetWindowFont (hWnd)->size);
            SetCaretPos (hWnd, sled->leftMargin, sled->topMargin);
            /* Invalidate the control to redraw the content */
            InvalidateRect (hWnd, NULL, TRUE);
            return 0;
        }

```

### 3.4.7 MSG_ERASEBKGND
This message is sent to the window procedure when the system needs to erase the window background. In general, when the application calls functions such as InvalidateRect or UpdateWindow etc. and pass TRUE to bErase argument, the system will send this message to inform the window to erase the background. The default window procedure will refresh the client region of the window with the background color. For some special windows, which usually refresh the entire client region in MSG_PAINT message, you can ignore the handling of the message in this case:

```cplusplus
MSG_EARSEBKGND:
    return 0;

```
There are also some windows, which expect to fill the background with a bitmap, which can be done during handling MSG_ERASEBKGND message:

```cplusplus
MSG_EARSEBKGND:
    HDC hdc = (HDC)wParam;
    const RECT* clip = (const RECT*) lParam;
    BOOL fGetDC = FALSE;
    RECT rcTemp;
            
    if (hdc == 0) {
        hdc = GetClientDC (hDlg);
        fGetDC = TRUE;
    }       
            
    if (clip) {
        rcTemp = *clip;
        ScreenToClient (hDlg, &rcTemp.left, &rcTemp.top);
        ScreenToClient (hDlg, &rcTemp.right, &rcTemp.bottom);
        IncludeClipRect (hdc, &rcTemp);
    }

    /* Fill the background with a BITMAP object */
    FillBoxWithBitmap (hdc, 0, 0, 0, 0, &bmp_bkgnd);

    if (fGetDC)
        ReleaseDC (hdc);
    return 0;

```
Please refer to bmpbkgnd.c program in the sample package of this guide for the complete implementation of filling the window background with a bitmap, the effect of the program is as shown in Fig. 3.9.
<center>     <img src="%ATTACHURLPATH%/3.5.jpeg" alt="3.5.jpeg"  ALIGN="CENTER" /> </center>

<center>Fig 3.9 Using image as window background</center>

### 3.4.8 MSG_PAINT 
This message is sent to the window procedure when the window needs to be repainted. MiniGUI determines whether to repaint by judging whether the window has invalid region. When a window is initially displayed, changes from hidden status to visible status, or from partially invisible to visible, or the application calls InvalidateRect function to invalidate a certain rectangle region, the window will have invalid region. At this time, MiniGUI will handle the invalid region and send MSG_PAINT message to the window procedure after finishing handling all the posted messages and notification messages. The typical handling of the message is as follows:

```cplusplus
case MSG_PAINT:
{
    HDC hdc;

    hdc = BeginPaint (hWnd);

    /* Paint window with hdc */
    ...

    EndPaint (hWnd, hdc);
    return 0;
}

```
It should be noted that, application should return directly after handling the message, and should not pass this message to the default window procedure. Device contexts and graphics APIs will be described in detail in Part II of this guide.

### 3.4.9 MSG_CLOSE
MiniGUI sends MSG_CLOSE message to the window procedure when the user click the “Close” button on the window caption bar. The application should call DestroyMainWindow to destroy the main window during handling the message. If the window has the style of WS_MINIMIZEBOX and WS_MAXMIZEBOX, the caption bar of the window should display “Minimization” and “Maximization” buttons. At present, MiniGUI has not realized handling of these buttons, but application can utilize these two styles to display other buttons, such as “Ok” and “Help” button, and then deal with MSG_MINIMIZE and MSG_MAXIMIZE messages in the window procedure.

### 3.4.10 MSG_DESTROY 
This message is sent to the window procedure when DestroyMainWindow or DestroyWindow is called, which is used to inform the system to destroy a window. You can destroy your private objects when receiving this message. If a non-zero value is returned for handling this message, the destroy process will be canceled.

When the application destroys a certain hosting main window, DestroyMainWindow will destroy the hosted main windows first. Certainly, when modal dialog box is used, logic of modal dialog box will ensure that there is no any hosted main window existing when destroying the hosting main window. But when using modeless dialog box or normal main window, application should deal with the hosted main windows according to the following rules, in order that the hosted main window and its related resource can be destroyed correctly when the user destroys a certain hosting main window: 

- The application should destroy the resource of the hosted main window, such as bitmaps and fonts etc., in the MSG_DESTROY message:

```cplusplus
case MSG_DESTROY:
            DestroyIcon (icon1);
            DestroyIcon (icon2);
            DestroyAllControls (hWnd);
            return 0;

```
- DestroyMainWindow and MainWindowCleanup functions should be called when the hosted main window responds to MSG_CLOSE message:

```cplusplus
case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            MainWindowCleanup (hWnd);
        return 0;

```
- Handle MSG_CLOSE message and call DestroyMainWindow function in the hosting main window. 

We also can release the resource of the hosting main window when handling MSG_DESTROY message. Thus, no matter the user closes the hosting main window or the hosted main window, the window itself and its related resource both can be released completely.

## 3.5 Common Window Operation Functions
MiniGUI provides some general window operation functions, which can be used for the main windows or controls, as shown in Table 3.2. In this guide, we use the term “window” to refer generally to main windows or controls. The functions for windows can be used for main windows or controls if no particular note.

<center>Table 3.2 Common window operation functions</center>
| *Function* | *Purpose* | *Note* |
| UpdateWindow | Update the whole window immediately | |
| ShowWindow |Show or hide a window ||
| IsWindowVisible | Determine whether a window is visible | Both control and window can use it |
| EnableWindow | Enable or disable a window | |
| IsWindowEnabled  | Determine whether a window is enabled | |
| GetClientRect | Get the client rectangle of a window | |
| GetWindowRect | Get the window rectangle of a window | window size in screen coordinate system|
| GetWindowBkColor | Get the background pixel value of a window | |
| SetWindowBkColor | Set the background pixel value of a window | |
| GetWindowFont      | Get the default font of a window | |
| SetWindowFont       | Set the default font of a window | |
| GetWindowCursor   | Get the cursor of a window | |
| SetWindowCursor   | Set the cursor of a window | |
| GetWindowStyle     | Get the style of a window | |
| GetWindowExStyle   | Get the extended style of a window | |
| GetFocusChild       | Get the focus child of a window | |
| SetFocusChild        | Set the focus child of a window | |
| GetWindowCallbackProc  | Get the window procedure of a window | |
| SetWindowCallbackProc   | Set the window procedure of a window | |
| GetWindowAdditionalData | Get the first additional data attached to a window | |
| SetWindowAdditionalData | Set the first additional data attached to a window | |
| GetWindowAdditionalData2     | Get the second additional data attached to a window | Dialog box and controls has already used the second additional data internally, and reserve the first data for application. |
| SetWindowAdditionalData2   | Set the second additional data attached to a window  | ^ |
| GetWindowCaption     | Get the caption of a window |often for main window | 
| SetWindowCaption  | Set the caption of a window | ^ |
| InvalidateRect    | Makes a rectangle region in the client area of a window invalid |Would result in repainting of a window |
| GetUpdateRect   | Retrieves the bounding box of the update region of a window | |
| ClientToScreen      | Converts the client coordinates of a point to screen coordinates | |
| ScreenToClient    | Converts the screen coordinates of a point to client coordinates | |
| WindowToScreen     | Converts the window coordinates of a point to screen coordinates | |
| ScreenToWindow   | Converts the screen coordinates of a point to window coordinates | |
| IsMainWindow   | Determines whether a window is a main window | |
| IsControl      | Determines whether a window is a control | |
| IsDialog   | Determines whether a window is a dialog box | |
| GetParent     | Retrieves the handle to a child window's parent window |The parent of main window always be HWND_DESKTOP|
| GetMainWindowHandle | Retrieves the handle to the main window contains a window | |
| GetNextChild    | Retrieves the next control in a window |used for traveling all the children of a windows|
| GetNextMainWindow  | Retrieves the next main window in the system | used for traveling all the main windows|
| GetHosting | Retrieves the hosting main window of a main window | |
| GetFirstHosted | Retrieves the first hosted main window of a main window |used for traveling all hosted main window a hosting main window|
| GetNextHosted | Retrieves the next hosted main window of a main window |^|
| GetActiveWindow | Retrieves the main window handle to the active main window ||
| SetActiveWindow | Sets a main window to be the active main window | |
| GetCapture | Retrieves the handle to the window (if any) that has captured the mouse | Relevant contents will be described in Chapter 9 |
| SetCapture | Sets the mouse capture to the specified window |^|
| ReleaseCapture | Releases the mouse capture from a window and restores normal mouse input processing |^|
| MoveWindow | Changes the position and size of a window | |
| ScrollWindow | Scrolls the content of a window's client area |Since MiniGUI 1.6.8,  ScrollWindow function can adjust the position of child window in the window according to the scroll status of client area. In specific, the position of child window will be changed when it is in the range of given rectangle from passed second argument. All child windows' position will be changed when passed second argument is NULL|

-- Main.XiaodongLi - 27 Oct 2009

