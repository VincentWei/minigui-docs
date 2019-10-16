# 6 Advanced Programming of Control

## 6.1 User-Defined Control

You can also register your own control class by calling RegisterWindowClass function, and create an instance of your control class. If the program will not use a certain user-defined control class any more, it should use UnregisterWindowClass function to unregister this user-defined control class. Please refer to “control class” of section 3.2.4 of this guide for the usage of the above two functions.

## 6.2 Subclassing of Control

Using the framework of a control class and control instance can not only improve the code reusability, but also extend the existing control class conveniently. For example, when you need to create an edit box which only allows inputting digits, you can realize by overriding the existing edit box control class rather than write a new control class. In MiniGUI, this technique is called subclassing or window derived. Methods of subclassing have three types:
- The first one is to perform subclassing on the created control instance, and the result of subclassing only affects this control instance.
- The second one is to perform subclassing on a certain control class, which will affect all the control instances created later of this control class.
- The last one is to register a subclassing control class based on a certain control class, which will not affect the original control class. In Windows, this technique is also called super-subclassing.

In MiniGUI, the subclassing of a control is actually implemented by replacing the existing window procedure. The codes in List 6.1 create two subclassing edit boxes by subclassing: one only allows inputting digits, and the other only allows inputting letters:

<center>List 6.1 Subclassing of control</center>

```cplusplus
#define IDC_CTRL1     100
#define IDC_CTRL2     110
#define IDC_CTRL3     120
#define IDC_CTRL4     130

#define MY_ES_DIGIT_ONLY    0x0001
#define MY_ES_ALPHA_ONLY    0x0002

static WNDPROC old_edit_proc;

static int RestrictedEditBox (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
    if (message == MSG_CHAR) {
        DWORD my_style = GetWindowAdditionalData (hwnd);
        /* Determine the key-pressed type being shielded */
        if ((my_style & MY_ES_DIGIT_ONLY) && (wParam < '0' || wParam > '9'))
            return 0;
        else if (my_style & MY_ES_ALPHA_ONLY)
            if (!((wParam >= 'A' && wParam <= 'Z') || (wParam >= 'a' && wParam <= 'z')))
                /* Receive the key-pressed message being shielded, and returns directly */
                return 0;
    }
    /* Handle the other messages by the old window procedure */
    return (*old_edit_proc) (hwnd, message, wParam, lParam);
}
static int ControlTestWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_CREATE:
    {
        HWND hWnd1, hWnd2, hWnd3;
        CreateWindow (CTRL_STATIC, "Digit-only box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                    10, 10, 180, 24, hWnd, 0);
        hWnd1 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER, IDC_CTRL1, 
                    200, 10, 180, 24, hWnd, MY_ES_DIGIT_ONLY);
        CreateWindow (CTRL_STATIC, "Alpha-only box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                    10, 40, 180, 24, hWnd, 0);
        hWnd2 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_BORDER | WS_VISIBLE, IDC_CTRL2, 
                    200, 40, 180, 24, hWnd, MY_ES_ALPHA_ONLY);
        CreateWindow (CTRL_STATIC, "Normal edit box:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 
                    10, 70, 180, 24, hWnd, 0);
        hWnd3 = CreateWindow (CTRL_EDIT, "", WS_CHILD | WS_BORDER | WS_VISIBLE, IDC_CTRL2, 
                    200, 70, 180, 24, hWnd, MY_ES_ALPHA_ONLY);
        CreateWindow ("button", "Close", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, IDC_CTRL4, 
                    100, 100, 60, 24, hWnd, 0);
        /* Replace the window procedure of the edit box with the 
         * user-defined window procedure, and save the old window procedure. */
        old_edit_proc = SetWindowCallbackProc (hWnd1, RestrictedEditBox);
        SetWindowCallbackProc (hWnd2, RestrictedEditBox);
        break;
    }
    ......
    }
    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}
```

## 6.3 Combined Use of Controls

We can also combine two different controls together to achieve a certain special effect. In fact, the predefined control class of the combo box is a typical one of combining controls. When we combine different controls, we can encapsulate and register the combined control to be a new control class, and can also use it directly without encapsulation.

To illustrate the method to combine controls more clearly, we can assume that we want to implement a time editor. This time editor displays the time in form of “08:05:30”, and we need further add a method to edit the time neatly according the user’s requirement. To meet this requirement, we combine the edit box and the spin box together which implement the following functions, respectively:
- The edit box displays the time in form of “HH:MM:SS”.
- When the input focus is in the edit box, the user can not edit the time directly, but must control the time value where the caret is with the arrow keys and PageDown and PageUp keys. So we must subclass this edit box to catch the key-pressed in it and perform the appropriate handling.
- Place a spin box beside the edit box. The user can adjust the time element where the caret is to increase or decrease by clicking the spin box. To achieve this goal, we can use the function of the spin box, and set the handle of the target window to be the edit box.

Thus, the time editor can work normally. Partial codes of this program are listed in List 6.2, and please refer to timeeditor.c file of the sample program package of this guide for the complete source code. Fig 6.1 shows the running effect of the timeeditor.

<center>List 6.2 Time Editor</center>

```cplusplus
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>

#define IDC_EDIT    100
#define IDC_SPINBOX 110

/* font for edit control. Use TrueType font to get better effect *'/
static PLOGFONT timefont;

/* save old edit window procedure */
static WNDPROC old_edit_proc;

/* Change time value according to the position of current caret */
static void on_down_up (HWND hwnd, int offset)
{
    char time [10];
    int caretpos;
    int hour, minute, second;

    GetWindowText (hwnd, time, 8);
    caretpos = SendMessage (hwnd, EM_GETCARETPOS, 0, 0);

    hour = atoi (time);
    minute = atoi (time + 3);
    second = atoi (time + 6);

    if (caretpos > 5) { /* change second */
    /* second position */
        second += offset;
        if (second < 0)
            second = 59;
        if (second > 59)
            second = 0;
    }
    else if (caretpos > 2) { /* change minute */
    /* minute position */
        minute += offset;
        if (minute < 0)
            minute = 59;
        if (minute > 59)
            minute = 0;
    }
    else { /* change hour */
    /* hour position */
        hour += offset;
        if (hour < 0)
            hour = 23;
        if (hour > 23)
            hour = 0;
    }

    /* put changed time string in edit box */
    sprintf (time, "%02d:%02d:%02d", hour, minute, second);
    SetWindowText (hwnd, time);

    /* recover caret position */
    SendMessage (hwnd, EM_SETCARETPOS, 0, caretpos);
}

/* This is edit box's SubClassing window procedure function */
static int TimeEditBox (HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
    /* Only handle button press message. When the following keys are pressed, 
     * call on _down_up function to modify time value */
    if (message == MSG_KEYDOWN) {
        switch (wParam) {
        case SCANCODE_CURSORBLOCKUP:
            on_down_up (hwnd, 1);
            return 0;
        case SCANCODE_CURSORBLOCKDOWN:
            on_down_up (hwnd, -1);
            return 0;
        case SCANCODE_PAGEUP:
            on_down_up (hwnd, 10);
            return 0;
        case SCANCODE_PAGEDOWN:
            on_down_up (hwnd, -10);
            return 0;

        case SCANCODE_CURSORBLOCKLEFT:
        case SCANCODE_CURSORBLOCKRIGHT:
                break;
        default:
                return 0;
        }
    }

    /* ignore the following two messages, user can only operate by using above keys */
    if (message == MSG_KEYUP || message == MSG_CHAR)
        return 0;

    return (*old_edit_proc) (hwnd, message, wParam, lParam);
}

static int TimeEditorWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_CREATE:
    {
        HWND hwnd;
        HDC hdc;
        HWND timeedit, spin;
        SIZE size;

        /* create descriptive static */
        hwnd = CreateWindow (CTRL_STATIC, 
                        "This is a time editor.\n\n"
                        "Pressing <Down-Arrow>, <Up-Arrow>, <PgDn>, and <PgUp> keys"
                        " when the box has input focus will change the time.\n\n"
                        "You can also change the time by clicking the SpinBox.\n",
                        WS_CHILD | WS_VISIBLE | SS_LEFT, 
                        IDC_STATIC, 
                        10, 10, 220, 200, hWnd, 0);

        /* create logic font for edit box */
        timefont = CreateLogFont (NULL, "Arial", "ISO8859-1", 
                        FONT_WEIGHT_BOOK, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
                        FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 
                        30, 0);

        /* calculate the size and width of output time */
        hdc = GetClientDC (hWnd);
        SelectFont (hdc, timefont);
        GetTextExtent (hdc, "00:00:00", -1, &size);
        ReleaseDC (hdc);

        /* create edit box according to calculated value */
        timeedit = CreateWindow (CTRL_SLEDIT, 
                        "00:00:00", 
                        WS_CHILD | WS_VISIBLE | ES_BASELINE, 
                        IDC_EDIT, 
                        40, 220, size.cx + 4, size.cy + 4, hWnd, 0);

        /* set the font of edit box */
        SetWindowFont (timeedit, timefont);

        /* SubClassing edit box */
        old_edit_proc = SetWindowCallbackProc (timeedit, TimeEditBox);

        /* Create Spin Box */
        spin = CreateWindow (CTRL_SPINBOX, 
                        "", 
                        WS_CHILD | WS_VISIBLE, 
                        IDC_SPINBOX, 
                        40 + size.cx + 6, 220 + (size.cy - 14) / 2, 0, 0, hWnd, 0);

        /* Set the target window of spin box as edit box,
         * so when user clicks spin box, it will emulate and send 
         * MSG_KEYDOWN message to edit box */
        SendMessage (spin, SPM_SETTARGET, 0, timeedit);
        break;
    }

    case MSG_DESTROY:
        DestroyAllControls (hWnd);
        DestroyLogFont (timefont);
	return 0;

    case MSG_CLOSE:
        DestroyMainWindow (hWnd);
        PostQuitMessage (hWnd);
        return 0;
    }

    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

/* the codes for creating main window is omitted */
```

<center>
<img src="%ATTACHURLPATH%/6.1.jpeg" alt="6.1.jpeg"  ALIGN="CENTER" /><br>
Fig. 6.1 Running effect of time editor
</center>

-- Main.XiaodongLi - 29 Oct 2009

