# 19 Static Control


A static control is used to display information, such as text and digits, in the specified position of a window, and can also be used to display some static image information, such as corporation logos, product brands, etc. As suggested by its name, the behavior of a static box cannot respond dynamically to the user input. The existence of the control is basically for displaying some information, and does not receive any input from the keyboard or the mouse. Fig 19.1 shows the typical use of the static control: to be the label of other controls in a dialog box.

<center>
<img align="CENTER" alt="19.1.jpeg" src="%ATTACHURLPATH%/19.1.jpeg" /> <br />
Fig. 19.1 Typical use of the static control
</center>

You can create a static control by calling CreateWindow function with CTRL_STATIC as the control class name.

## 19.1 Types and Styles of Static Control

Styles of a static control comprise the type of the static control and some flags. We can divide the static controls into standard type (display text only), bitmap type (display icon or bitmap), and special type of group box. We will introduce the different types of static control in the following sections.

### 19.1.1 Standard Type

By setting the style of a static control to be one of SS_SIMPLE, SS_LEFT, SS_CENTER, SS_RIGHT, and SS_LEFTNOWORDWRAP, you can create a static control displaying only text. The displayed content thereof is specified in the caption argument of CreateWindow function and can be changed by calling SetWindowText.

Static controls with SS_SIMPLE style can only be used to display single-line text, that is to say, the text in such controls is not wrapped automatically, and is always align left.

Static controls with SS_LEFT, SS_CENTER, or SS_RIGHT style can be used to display multiple-line text, and align the text in the control left, center, and right respectively.

Static controls with SS_LEFTNOWORDWRAP will extend TAB characters in the text, but words are not wrapped automatically.

The following program creates static controls of the several types described above:

```cplusplus
 CreateWindow (CTRL_STATIC,
                            "This is a simple static control.",
                            WS_CHILD | SS_NOTIFY | SS_SIMPLE | WS_VISIBLE | WS_BORDER,
                            IDC_STATIC1,
                            10, 10, 180, 20, hWnd, 0);
            CreateWindow (CTRL_STATIC,
                            "This is a left-aligned static control (auto-wrap).",
                            WS_CHILD | SS_NOTIFY | SS_LEFT | WS_VISIBLE | WS_BORDER,
                            IDC_STATIC2,
                            10, 40, 100, 45, hWnd, 0);
            CreateWindow (CTRL_STATIC,
                            "This is a right-aligned static control (auto-wrap).",
                            WS_CHILD | SS_NOTIFY | SS_RIGHT | WS_VISIBLE | WS_BORDER,
                            IDC_STATIC3,
                            10, 90, 100, 45, hWnd, 0);
            CreateWindow (CTRL_STATIC,
                            "This is a center-aligned static control (auto-wrap).",
                            WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE | WS_BORDER,
                            IDC_STATIC4,
                            10, 140, 100, 45, hWnd, 0);
            CreateWindow (CTRL_STATIC,
                            "SS_LEFTNOWORDWRAP: "
                            "\tTabs are expanded, but words are not wrapped. "
                            "Text that extends past the end of a line is clipped.",
                            WS_CHILD | SS_LEFTNOWORDWRAP | WS_VISIBLE | WS_BORDER,
                            IDC_STATIC,
                            10, 290, 540, 20, hWnd, 0);
```

The appearance of the controls described above is shown in Fig. 19.2. For showing the effect clearly, all these static controls have borders.

<center>
<img align="CENTER" alt="19.2.jpeg" src="%ATTACHURLPATH%/19.2.jpeg" /> <br />
Fig. 19.2 Static controls of standard type
</center>

### 19.1.2 Bitmap Type

A static control with SS_BITMAP or SS_ICON style displays a bitmap or an icon in the control. For these two types of static control, it is needed to set the handle of an icon object or the pointer to a bitmap object to be displayed through dwAddData parameter when the static control is created. Styles associated with these two types of static control are SS_CENTERIMAGE and SS_REALSIZEIMAGE. These two styles are used to control the position of a bitmap or an icon in the control. By default, the bitmap or icon fills the whole static control by appropriate scale, but this scaling operation will be canceled when SS_REALSIZEIMAGE style is used, and the bitmap or icon aligns in the top-left of the static control. If SS_REALSIZEIMAGE style is used with SS_CENTERIMAGE style simultaneously, the bitmap or icon will be displayed in the center of the control.

The following program creates a bitmap static control and an icon static control, and creates a bitmap static control displayed in the center of the control by using SS_REALSIZEIMAGE and SS_CENTERIMAGE styles:

```cplusplus
CreateWindow (CTRL_STATIC,
                        "",
                        WS_CHILD | SS_BITMAP | WS_VISIBLE,
                        IDC_STATIC,
   1 
      1 
         1 
            1 
               1 
                  1 
                     1 
                        1 , 80, 50, 50, hWnd, (DWORD)GetSystemBitmap (SYSBMP_CHECKMARK));

        CreateWindow (CTRL_STATIC,
                        "",
                        WS_CHILD | SS_ICON | WS_VISIBLE,
                        IDC_STATIC,
   1 
      1 
         1 
            1 
               1 
                  1 
                     1 
                        1 , 20, 50, 50, hWnd, (DWORD)GetLargeSystemIcon (IDI_INFORMATION));

        CreateWindow (CTRL_STATIC,
                   "",
                  WS_CHILD | SS_BITMAP | SS_REALSIZEIMAGE | SS_CENTERIMAGE | WS_VISIBLE,
                  IDC_STATIC,
   1 
      1 
         1 
            1 
               1 
                  1 , 140, 50, 50, hWnd, (DWORD)GetSystemBitmap (SYSBMP_CHECKMARK));
```

***
[Note] Many predefined controls need you pass some initial parameters of them through dwAddData parameter of CreateWindowEx function. Here the first additional data of the window is used to pass these parameters during creating the control, and the application can also use the first additional data of the window to save private data after the control has been created.
***

The appearance of the static controls created by the above program is shown in Fig. 19.3.

<center>
<img align="CENTER" alt="19.3.jpeg" src="%ATTACHURLPATH%/19.3.jpeg" /> <br />
Fig. 19.3 Static control of bitmap type
</center>

### 19.1.3 Group Box

A static control with SS_GROUPBOX style is called a group box, which is a special type of static control. A group box is a rectangle with the caption displayed in the top, and it is usually used to include other controls. The controls that can be created in the group box include Static, Button, Edit Box, TextEdit, List Box, Track Bar, Menu Button.

The following program creates a group box, and its effect is shown in Fig. 19.4:

```cplusplus
CreateWindow (CTRL_STATIC,
                            "A Group Box",
                            WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
                            IDC_STATIC,
                            350, 10, 200, 100, hWnd, 0);
```

<center>
<img align="CENTER" alt="19.4.jpeg" src="%ATTACHURLPATH%/19.4.jpeg" /> <br />Fig. 19.4 A group box
</center>

### 19.1.4 Other static control types

Besides the static controls described above, there are several other static control types not frequently used:
- SS_WHITERECT：A rectangle filled with the light white color.
- SS_GRAYRECT：A rectangle filled with the light gray color.
- SS_BLACKRECT：A rectangle filled with the black color.
- SS_GRAYFRAME：A frame drawn with the light gray color.
- SS_WHITEFRAME：A frame drawn with the light white color.
- SS_BLACKFRAME：A frame drawn with the black color.

Appearances of the static controls using the above styles are shown in Fig. 19.5.

<center>
<img align="CENTER" alt="19.5.jpeg" src="%ATTACHURLPATH%/19.5.jpeg" /> <br />
Fig. 19.5 Other static control types
</center>

## 19.2 Static Control Messages

When the static control is of bitmap type, the bitmap can be gotten or changed by the following messages:
- STM_GETIMAGE：This message returns the pointer to the bitmap object or the handle to the icon.
- STM_SETIMAGE：To set the pointer to the bitmap or the handle to the icon through wParam parameter, and returns the old one.

## 19.3 Notification Codes of Static Control

When the style of a static control includes SS_NOTIFY, the static control can generate the following two notification messages:
- STN_DBLCLK：Indicates the user clicked the left button of the mouse in a static control.
- STN_CLICKED：Indicates the user double-clicked the left button of the mouse in a static control.

## 19.4 Sample Program

The program in List 19.1 creates a bitmap static control, and changes the text when the user double-clicks the static control. Please refer to static.c of the demo program package mg-samples of this guide to get the complete source code of the program. The running effect of the program is shown in Fig. 19.6.

<center>List 19.1 Sample program of static control</center>

```cplusplus
#include

#include &lt;minigui/common.h&gt;
#include &lt;minigui/minigui.h&gt;
#include &lt;minigui/gdi.h&gt;
#include &lt;minigui/window.h&gt;
#include &lt;minigui/control.h&gt;

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    /* When the user double-clicked the static control,
     * SetWindowText is called to change the text of the control.
     */
    if (nc == STN_DBLCLK)
        SetWindowText (hwnd, "I am double-clicked. :)");
}

static int StaticDemoWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HWND hwnd;

    switch (message) {
        case MSG_CREATE:
            /* Create a static box and set the notification callback function */
            hwnd = CreateWindow (CTRL_STATIC, "Double-click me!",
                          WS_VISIBLE | SS_CENTER | SS_NOTIFY,
                          50, 80, 100, 200, 20, hWnd, 0);
            SetNotificationCallback (hwnd, my_notif_proc);
            return 0;

        case MSG_DESTROY:
            DestroyAllControls (hWnd);
            return 0;

        case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
    }

    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

/* The Following code to create the main window are omitted  */
```

<center>
<img align="CENTER" alt="19.6.jpeg" src="%ATTACHURLPATH%/19.6.jpeg" /><br />
Fig. 19.6 The sample of static control
</center>

-- Main.XiaodongLi - 26 Oct 2009

