# 36 Animation Control

Animation control is one control, which can be used to display animations; it is very simple and easy to use.

You can create an animation control by calling CreateWindow function with CTRL_ANIMATION as the control class name.

## 36.1 ANIMATION Object

Before creating an animation control, you must create an object of ANIMATION. This object is actually a linked list structure, and each node of the linked list represents a frame of the animation object. An object of ANIMATION is represented by the following two structures:

```cplusplus
/** Animation frame structure. */
typedef struct _ANIMATIONFRAME
{
    /** The disposal method (from GIF89a specification):
     *  Indicates the way in which the graphic is to be treated after being displayed.
     *  - 0\n No disposal specified. The decoder is not required to take any action.
     *  - 1\n Do not dispose. The graphic is to be left in place. 
     *  - 2\n Restore to background color. The area used by the frame must be restored to 
     *        the background color.
     *  - 3\n Restore to previous. The decoder is required to restore the area overwritten by 
     *        the frmae with what was there prior to rendering the frame.
     */
    int disposal;
    /** The x-coordinate of top-left corner of the frame in whole animation screen. */
    int off_x;
    /** The y-coordinate of top-left corner of the frame in whole animation screen. */
    int off_y;
    /** The width of the frame. */
    unsigned int width;
    /** The height of the frame. */
    unsigned int height;

    /** The time of the frame will be display, in the unit of animation time_unit. */
    unsigned int delay_time;
#ifdef _USE_NEWGAL
    /** The memdc compatible with the gif image. */
    HDC mem_dc;
    /** The bits of the mem_dc, should be freed after deleting the mem_dc. */
    Uint8* bits;
#else
    /** The bitmap of the frame. */
    BITMAP bmp;
#endif

    /** The next frame */
    struct _ANIMATIONFRAME* next;
    /** The previous frame */
    struct _ANIMATIONFRAME* prev;
} ANIMATIONFRAME;

/** Animation structure */
typedef struct _ANIMATION
{
    /** The width of the animation. */
    unsigned int width;
    /** The height of the animation. */
    unsigned int height;

    /** The background color */
    RGB bk;

    /** The number of all frames. */
    int nr_frames;
    /**
     * The unit of the time will be used count the delay time of every frame.
     * The default is 1, equal to 10ms.
     */
    int time_unit;
    /** Pointer to the animation frame.*/
    ANIMATIONFRAME* frames;
} ANIMATION;
```

What the ANIMATION structure describes are the global properties of objects of animation, and includes the width and height of an animation, number of frames, time scale used for indicating delaying (1 means 10ms), and the header pointer to the linked list of animation frames.

ANIMATIONFRAME structure presents a single animation frame, and includes the following information:
- Offset of the current animation frame in the global animation, and the width and height of the frame. Since an animation frame may only change partial image information, so including only the changed part in the frame structure will significantly reduce the amount of data for frames.
- Delay time of the current frame. Calculate the display time of the current frame with time_unit in the ANIMATION object as the scale.
- Image information of the current frame. When you use NEWGAL interface, the image is represented by a memory DC; otherwise a BITMAP object represents the image.

An application can construct an ANIMATION object itself, and can also call the following function to directly create an ANIMATION object from an image file in GIF98a format. 

```cplusplus
ANIMATION* CreateAnimationFromGIF89a (HDC hdc, MG_RWops* area);
ANIMATION* CreateAnimationFromGIF89aFile (HDC hdc, const char* file);
ANIMATION* CreateAnimationFromGIF89aMem (HDC hdc, const void* mem, int size);
```

The above-mentioned function will read the image information of the animation GIF from the data area in GIF98a format, and then create an ANIMATION object.

After an application creates an ANIMATION object, and can both display it, also can create an animation control to display the animation. When you call CreateWindow function to create an animation control, you can pass the created ANIMATION object to the animation control and the animation control will use the ANIMATION object to display the animation automatically. For example, an ANIMATION object is created from a GIF file in the following code fragment, and then using the object creates an animation control:

```cplusplus
 ANIMATION* anim = CreateAnimationFromGIF89aFile (HDC_SCREEN, "banner.gif");
        if (anim == NULL)
            return 1;

        CreateWindow (CTRL_ANIMATION, 
                          "", 
                          WS_VISIBLE | ANS_AUTOLOOP, 
                          100, 
                          10, 10, 300, 200, hWnd, (DWORD)anim);
```

It should be noted that you could pass the pointer to the ANIMATION object into an animation control through dwAddData argument when calling CreateWindow function.

## 36.2 Styles of Animation Control

At present, there are three styles for an animation control:
- ANS_AUTOLOOP: An animation control will display the animation circularly after the style is used.
- ANS_SCALED: The display image can be scaled.
- ANS_FITTOANI: Fit the control size follows the animation. 

## 36.3 Messages of Animation Control

Messages of animation controls are very simple. There are the following several message currently, which can be used to control the display action of an animation control.
- ANM_SETANIMATION: Set an ANIMATION object.
- ANM_GETANIMATION: Get the current ANIMATION object.
- ANM_STARTPLAY: Start playing the animation. Before sending ANM_STARTPLAY to an animation control, the animation control will only display the first frame image of the ANIMATION object; and only after ANM_STARTPLAY message is sent, the animation control can display an animation according to the information in ANIMATION object.
- ANM_PAUSE_RESUME: Pause/Resume playing. This message is used to pause the play of an animation (during playing), or used to resume the play of an animation (when the animation has been paused).
- ANM_STOPPLAY: Stop the play of an animation. The animation control displays the first frame of the ANIAMTION.

## 36.4 Sample Program

Code in List 36.1 illustrates the use of an animation control. Please refer to animation.c file of the demo program package mg-samples of this guide for complete source code.

<center>List 36.1 Use of animation control</center>

```cplusplus
static int AnimationWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_CREATE:
    {
        ANIMATION* anim = CreateAnimationFromGIF89aFile (HDC_SCREEN, "banner.gif");
        if (anim == NULL)
            return 1;

        SetWindowAdditionalData (hWnd, (DWORD) anim);
        CreateWindow (CTRL_ANIMATION, 
                          "", 
                          WS_VISIBLE | ANS_AUTOLOOP, 
                          100, 
                          10, 10, 300, 200, hWnd, (DWORD)anim);
        SendMessage (GetDlgItem (hWnd, 100), ANM_STARTPLAY, 0, 0);

        CreateWindow (CTRL_ANIMATION, 
                          "", 
                          WS_VISIBLE | ANS_AUTOLOOP, 
                          200, 
                          10, 210, 300, 200, hWnd, (DWORD)anim);
        break;
    }

    case MSG_LBUTTONDOWN:
        SendMessage (GetDlgItem (hWnd, 200), ANM_STARTPLAY, 0, 0);
        break;

    case MSG_DESTROY:
        DestroyAnimation ((ANIMATION*)GetWindowAdditionalData (hWnd), TRUE);
        DestroyAllControls (hWnd);
        return 0;

    case MSG_CLOSE:
        DestroyMainWindow (hWnd);
        PostQuitMessage (hWnd);
        return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

/* Following codes to create the main window are omitted */
```

<center>
<img src="%ATTACHURLPATH%/36.1.jpeg" alt="36.1.jpeg"  ALIGN="CENTER" /> <br>
Fig. 36.1 Use of an animation control
</center>

In the program within List 36.1, banner.gif file in the current directory is loaded when the main window is created, and the corresponding ANIMATION object is created. Then two animation controls are created. The first animation control start playing the animation immediately after created, and the second animation control won’t play until the user clicks the window. Fig. 36.1 shows the running effect of the sample program, in which what the first animation control displays is the second frame of banner.gif file, and the second animation control displays the first frame.

-- Main.XiaodongLi - 26 Oct 2009

