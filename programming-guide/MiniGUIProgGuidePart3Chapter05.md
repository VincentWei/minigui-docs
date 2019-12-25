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
also the MiniGUI backend for Cairo.

Now, it is very easy to integrate MiniGUI with your GPU. Your MiniGUI
app can exploit the GPU accelerated functions to render 2D/3D objects.

## Architecture and Infrastructure

In practice, MiniGUI and the software which are used to integrated with GPU
constitute the graphics stack of HybridOS.

[HybridOS](https://hybridos.fmsoft.cn) is a totally new open source
operating system designed for smart IoT devices and cloud computing
environment. [FMSoft Technologies], the developer of MiniGUI,
initiated HybridOS project in 2018.

HybridOS uses MiniGUI as the underlying windowing system, and
the members of HybridOS project are now maintaining the whole graphics stack.

The following chart shows the graphics stack of HybridOS:

```
  -----------------------------------------------
 |           MiniGUI/HybridOS Apps               |
 |-----------------------------------------------|
 |           |         (Graphics Stack)          |
 |           |              ---------------------|
 |           |              | hiMesa             |
 |           | hiCairo      |  ------------------|
 |           | MiniGUI      |  | EGL for MiniGUI |
 | C++ libs  | hiDRMDrivers |  | GL, GLES, VG    |
 | C libs    | hiDRM        |  | GPU drivers     |
 |-----------------------------------------------|
 |  Linux Kernel                                 |
 |            -----------------------------------|
 |           |        DRI and DRI Drivers        |
  -----------------------------------------------
```

As shown in the chart above, the HybridOS graphics stack
consists of the following software:

- [hiDRM](https://github.com/FMSoftCN/hidrm) is the LibDRM derivative
  for HybridOS.
- [hiDRMDrivers](https://github.com/FMSoftCN/hidrmdrivers) contains the
  drivers for MiniGUI DRM engine. The drivers implement the basic hardware
  acclerated graphics operations of various GPUs for MiniGUI.
- [hiMesa](https://github.com/FMSoftCN/himesa) is the Mesa derivative
  for HybridOS, while Mesa is the open source implementation of OpenGL
  and other graphics APIs, including OpenGL ES (versions 1, 2, 3), OpenCL,
  OpenMAX, and Vulkan. It contains the following components:
   1. The implementatin of OpenGL, OpenGL ES (v1, 2, 3), and other
      graphics APIs.
   1. The EGL implementation for MiniGUI platform.
   1. The graphics drivers for various GPUs and a software driver called
      `swrast`.
- [hiCairo](https://github.com/FMSoftCN/hicairo) is the Cairo derivative
  for HybridOS. Cairo is a 2D vector graphics library for Gtk. We provide
  support for MiniGUI backend in hiCairo.

You can use the following script to fetch the source code of above software:

```shell
#!/bin/bash

# Use this if you want to visit GitHub via HTTPS
REPO_URL=https://github.com/FMSoftCN

# Use this one if you can visit GitHub via SSH
#REPO_URL=git@github.com:FMSoftCN

# Use this one if you are a developer of MiniGUI/HybridOS
#REPO_URL=git4os@gitlab.fmsoft.cn:hybridos

git clone $REPO_URL/hidrm -b hybridos
git clone $REPO_URL/hidrmdrivers
git clone $REPO_URL/himesa -b minigui-backend
git clone $REPO_URL/hicairo -b minigui-backend
```

_NOTE_ The above fetching script may changed in the future.

The software all ship with the GNU autotools building scripts or
the meson building scripts. You can refer to the README file for
the instructions to build and install the software to your system.

Please note that the installation order of the software:

1. hiDRM.
1. MiniGUI with DRM engine enabled.
1. hiDRMDrivers.
1. hiMesa with support for MiniGUI platform enabled.
1. hiCairo with MiniGUI backend enabled.

## The EGL Implementation for MiniGUI

> EGL™ is an interface between Khronos rendering APIs such as
> OpenGL ES or OpenVG and the underlying native platform window system.
> It handles graphics context management, surface/buffer binding, and
> rendering synchronization and enables high-performance, accelerated,
> mixed-mode 2D and 3D rendering using other Khronos APIs.
> EGL also provides interop capability between Khronos to enable
> efficient transfer of data between APIs – for example between a
> video subsystem running OpenMAX AL and a GPU running OpenGL ES.

As mentioned before, Mesa uses DRI to drive various GPUs and implement
the graphics APIs. Basically, the EGL implementation for MiniGUI depends
on the DRM engine of MiniGUI. On the other hand, if one MiniGUI instance
was not using DRM engine, the EGL implementation can still use the
software driver in Mesa to render the graphics objects.

For more information about EGL, please refer to:

- EGL Specification: <https://www.khronos.org/egl/>
- EGL in Mesa: <https://mesa3d.org/egl.html>

The EGL implementation for MiniGUI in Mesa is a sub driver of `egl_dri2`,
which supports many platforms including `x11`, `wayland`, `drm`, and
`surfaceless`.

### APIs specific to DRM engine



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
