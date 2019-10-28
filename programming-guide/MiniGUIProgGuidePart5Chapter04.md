# Appendix A Universal Startup `API` for `RTOSes`

MiniGUI provides universal startup `API` for `RTOSes` and spare startup
reference files in V2.0.4/1.6.9. MiniGUI 3.0 continues to use these files. 
These files are saved in the MiniGUI source code rtos/ directory. The rules of
nomenclature in these files are like &gt;os_name&lt;_startup.c. In startup 
file, there are an introduction to malloc, printf and `POSIX` pthread
initialization interface. The following is detailed description.

## Malloc Initialization Interface

MiniGUI provides an own-implemented malloc set of functions. We can use macro
_USE_OWN_MALLOC to open it. MiniGUI provides the following interface to
initialize MiniGUI malloc set of functions.

```
```

To use MiniGUI malloc set of functions, you should pass the information of heap
address, lock and unlock heap function pointer, and stack size.

The following is the reference implementation on ThreadX OS.
```
```

## Standard Output Initialization Interface

MiniGUI provides an own-implemented printf set of functions. We can use macro
_USE_OWN_STDIO to open it. MiniGUI provides the following interface to
initialize MiniGUI printf set of functions.

```
```

The following is a reference implementation.
```
```

So the information which is printed to standard output and standard error by
printf/fprintf functions will be printed to serial port of the device.

## `POSIX` Threads Initialization Interface

MiniGUI provides an own-implemented `POSIX` threads system. We can use macro
_USE_OWN_PTHREAD to open it. MiniGUI provides the following interface to
initialize RTOS `POSIX` threads system.
```
```

The first argument `pth_entry` will run as main thread. In reality, we can pass
`minigui_entry` for it. For example:

```
```

The following list shows the relationship between RTOS and macros above.


| *RTOS* | *Macro* |
| VxWorks | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |
| uC/OS-II | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br> _MGUSE_OWN_PTHREAD |
| `eCos` | none |
| `pSOS` | _MGUSE_OWN_PTHREAD |
| Win32 | _MGUSE_OWN_STDIO|
| `OSE` | _MGUSE_OWN_PTHREAD|
| ThreadX | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |
| Nucleus |_MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |


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
