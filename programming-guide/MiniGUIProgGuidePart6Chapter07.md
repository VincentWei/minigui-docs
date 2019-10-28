# Progress Bar Control

The progress bar is generally used to prompt the progress of a task for the
user, and is frequently used for tasks such as copying file, installing
software. Calling `CreateWindow` function with `CTRL_PROGRESSBAR` as the 
control class name can create a progress bar. Figure 1 is the typical running
effect of a progress bar.



![alt](figures/25.1.jpeg)

Figure 1 Progress bar control


## Styles of Progress Bar

Progress bar has only the following two styles available:
- `PBS_NOTIFY:` The progress bar control with this style can generate
notification messages.。
- `PBS_VERTICAL:` Display the progress bar vertically, as shown in Figure 2.



![alt](figures/25.2.jpeg)

Figure 2 Vertical progress bar control


The combination of styles commonly used by a progress bar controls is:

```
```

## Messages of Progress Bar
### Setting Range of Progress Bar

The range of a progress bar is 0 to 100 by default, and an application can set
its own progress bar range by calling `PBM_SETRANGE` message:

```
```

***
[Prompt] The range of a progress bar can be set to be a negative value.
***

### Setting Step Value of Progress Bar

We can set the step value for a progress bar, and make the progress bar 
stepping forward when each stage task is complete. The step value is 10 by
default, and can be changed by sending `PBM_SETSTEP` message, as shown in the
following: 

```
```

The above message changes the step value of a progress bar to be 5.

***
[Prompt] The step value of a progress bar can be set to be a negative value.
***

You should set the position of the progress bar as the max value of its range
when the step value is a negative and the progress bar will decrease from its
max range to min.

### Setting Position of Progress Bar

We can also set the current position of a progress bar optionally with
`PBM_SETPOS` message:

```
```

The above message sets the current position of a progress bar to be 50.

### Setting Offset Based-on Current Position

We can also set the offset of the new position based on the current position to
change the progress position:

```
```

The above message will add 10 to the new position based on the current 
position, i.e., new position is the current position plus 10.

***
[Prompt] The offset of a progress bar can be set to be a negative value.
***

### Advancing Position by One Step

`PBM_STEPIT` can be sent to advance the current position, and the new position
equals the result of the current position plus the step value:

```
```

***
[Note] The present progress bar control does not provide any messages for
getting the current position, the current step increment, and the current
position range.
***

## Notification Codes of Progress Bar

Progress bar with `PBS_NOTIFY` style may possibly generate the following
notification codes:
- `PBN_REACHMAX:` Reach the maximum position.
- `PBN_REACHMIN:` Reach the minimum position.

## Sample Program

List 1 gives an example of using the progress bar control. This program 
provides two functions. Calling `createProgressWin` function will create a main
window with a progress bar and then return. We can control the progress bar of
the main window in our own program, and call `destroyProgressWin` function to
destroy the progress main window after completing the task. The two functions
actually come from `MiniGUIExt` library of MiniGUI. List 1 gives the example of
the implementation and the usage of these two functions, and the running effect
is as shown in Figure 3. Please refer to progressbar.c of the sample program
package `mg-samples` of this guide for the complete source code.


List 1 Example of using progress bar

```
```



![alt](figures/25.3.jpeg)

Figure 3 Example of progress bar control


-- Main.XiaodongLi - 26 Oct 2009


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
