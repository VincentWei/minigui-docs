# Integrating with GPU

## Introduction

The graphics stack on Linux has had a long evolution.

Initially, graphics applications on Linux mainly used the old `SVGALib`;
the Linux kernel did not provide any driver for graphics or GPU.
In 2000s, the Linux kernel introduced the frame buffer driver to support
the various graphics devices. However, the frame buffer driver did not provide
a good implementation to support modern GPUs. If a software want to use
the powerful GPU functions to render 3D objects, it has to write a lot of
code for a specific GPU in application space. For desktop systems,
it is not a problem, because the XFree86 project provided a complete
graphics stack for 2D/3D rendering. But it is a nightmare for embedded systems.

Around 2010, the Free Destkop project introduced a new graphics stack for
Linux system called DRI (Direct Rendering Infrastructure).
As the name suggests, DRI provides applications with the ability to
directly access the GPU for 2D/3D rendering. With or without X Window,
applications can get the direct GPU rendering capabilities through DRI.
This greatly improves the performance and user experience of Linux
desktop systems.

After more than ten years of development, DRI technology has matured.
Now, Linux-based desktop systems have switched from the traditional
frame buffer driver to DRI. And the Linux-based embedded systems are
switching from frame buffer to DRI.

Therefore, we introduced the support DRI in MiniGUI version 4.0.4,
and developed the EGL implementation for MiniGUI based on Mesa,
also the MiniGUI back-end for Cairo.

Now, it is very easy to integrate MiniGUI with your GPU. Your MiniGUI
app can exploit the GPU accelerated functions to render 2D/3D objects.

## Architecture and Infrastructure

The following chart shows the graphics stack on MiniGUI platform:

```
    -------------------------------------------------
    |           MiniGUI/HybridOS Apps               |
    -------------------------------------------------
    |           |         (Graphics Stack)          |
    |           |              ---------------------|
    |           |              | hiMesa             |
    |           | hiCairo      |  ------------------|
    |           | MiniGUI      |  | EGL for MiniGUI |
    | C++ libs  | hiDRMDrivers |  | GL, GLES, VG    |
    | C libs    | hiDRM        |  | GPU drivers     |
    -------------------------------------------------
    |  Linux Kernel                                 |
    |           ------------------------------------|
    |           |        DRI and DRI Drivers        |
    -------------------------------------------------
```

## The EGL Implementation for MiniGUI

## 3D Rendering on MiniGUI

## Cairo and MiniGUI

----

[&lt;&lt; Using mGPlus for Vector Graphics](MiniGUIProgGuidePart3Chapter04.md) |
[Table of Contents](README.md) |
[Using mGEff for Visual Effects and Animations &gt;&gt;](MiniGUIProgGuidePart4Chapter01.md)

[Release Notes for MiniGUI 3.2]: /supplementary-docs/Release-Notes-for-MiniGUI-3.2.md
[Release Notes for MiniGUI 4.0]: /supplementary-docs/Release-Notes-for-MiniGUI-4.0.md
[Showing Text in Complex or Mixed Scripts]: /supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md
[Supporting and Using Extra Input Messages]: /supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md
[Using CommLCD NEWGAL Engine and Comm IAL Engine]: /supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md
[Using Enhanced Font Interfaces]: /supplementary-docs/Using-Enhanced-Font-Interfaces.md
[Using Images and Fonts on System without File System]: /supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md
[Using SyncUpdateDC to Reduce Screen Flicker]: /supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md
[Writing DRM Engine Driver for Your GPU]: /supplementary-docs/Writing-DRM-Engine-Driver-for-Your-GPU.md
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
