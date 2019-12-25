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

_[NOTE]_ The above fetching script may changed in the future.

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

The following words give the official definition for EGL:

> EGL™ is an interface between Khronos rendering APIs such as
> OpenGL ES or OpenVG and the underlying native platform window system.
> It handles graphics context management, surface/buffer binding, and
> rendering synchronization and enables high-performance, accelerated,
> mixed-mode 2D and 3D rendering using other Khronos APIs.
> EGL also provides interop capability between Khronos to enable
> efficient transfer of data between APIs – for example between a
> video subsystem running OpenMAX AL and a GPU running OpenGL ES.

Obviously, to integrate OpenGL and other graphics APIs with MiniGUI,
we must implement EGL for MiniGUI.

As mentioned before, Mesa uses DRI to drive various GPUs and implement
the graphics APIs.
The EGL implementation for MiniGUI in Mesa is a sub driver of `egl_dri2`,
which supports many platforms including `x11`, `wayland`, `drm`, and
`surfaceless`.

Basically, the EGL implementation for MiniGUI depends on the
DRM engine of MiniGUI.
On the other hand, if one MiniGUI instance was not using DRM engine,
the EGL implementation for MiniGUI can still use the
software driver in Mesa to render the graphics objects.

For more information about EGL, please refer to:

- EGL Specification: <https://www.khronos.org/egl/>
- EGL in Mesa: <https://mesa3d.org/egl.html>

### New APIs for GPU integration

MiniGUI introduced some new APIs for GPU integration:

- `GetVideoHandle` gets the handle of the video engine which corresponds to
  the given device context. By using the video engine handle returned by this
  function, you can call `drmGetDeviceFD` to get the DRI device file descriptor
  opened by MiniGUI DRM engine.
- `drmGetDeviceFD` returns the DRI device file descriptor opened by MiniGUI
  DRM engine.
- `drmGetSurfaceInfo` returns the DRM surface information from a specific
   device context.
- `drmCreateDCFromName` creates a memory DC with a DRM surface which is
  created by a foreign process and identified by a global name handle.
- `drmCreateDCFromPrimeFd` creates a memory DC with a DRM surface which
  is created by a foreign process and identified by a PRIME file descriptor.
- `drmCreateDCFromHandle` creates a memory DC with a DRM surface which is
  created by a foreign graphics component.

Note that all functions prefixed by `drm` is only available when support
for Linux DRM NEWGAL engine (`_MGGAL_DRM`) is enabled.

### Specification of EGL implementation for MiniGUI

The following text gives the specification of EGL implementation for MiniGUI:

```
Name

    EXT_platform_minigui

Name Strings

    EGL_EXT_platform_minigui

Contributors

    Vincent Wei <vincent@minigui.org>

Contacts

    Vincent Wei <vincent@minigui.org>

Status

    Beta

Version

    Version 1, 2019-12-10

Number

    EGL Extension <N/A>

Extension Type

    EGL client extension

Dependencies

    Requires EGL_EXT_client_extensions to query its existence without
    a display.

    Requires EGL_EXT_platform_base.

    This extension is written against the wording of version 7 of the
    EGL_EXT_platform_base specification.

Overview

    This extension defines how to create EGL resources from native MiniGUI
    resources using the functions defined by EGL_EXT_platform_base.

New Types

    None

New Procedures and Functions

    None

New Tokens

    Accepted as the <platform> argument of eglGetPlatformDisplayEXT:

        EGL_PLATFORM_MINIGUI_EXT                0x34A0

Additions to the EGL Specification

    None.

New Behavior

    To determine if the EGL implementation supports this extension, clients
    should query the EGL_EXTENSIONS string of EGL_NO_DISPLAY.

    To obtain an EGLDisplay backed by a MiniGUI video, call
    eglGetPlatformDisplayEXT with <platform> set to EGL_PLATFORM_MINIGUI_EXT.
    The <native_display> parameter specifies the MiniGUI video to use and must
    either a handle to video (returned by `GetVideoHandle()` or be EGL_DEFAULT_DISPLAY.
    If <native_display> is EGL_DEFAULT_DISPLAY, then EGL will use the video
    handle returned by `GetVideoHandle(HDC_SCREEN)`.

    To obtain an on-screen rendering surface from a MiniGUI window, call
    eglCreatePlatformWindowSurfaceEXT with a <dpy> that belongs to MiniGUI and
    a <native_window> that is a window handle.

    It is not valid to call eglCreatePlatformPixmapSurfaceEXT with a <dpy>
    that belongs to MiniGUI. Any such call fails and generates
    EGL_BAD_PARAMETER.

Issues

    1. Should this extension permit EGL_DEFAULT_DISPLAY as input to
       eglGetPlatformDisplayEXT()?

       Yes. When given EGL_DEFAULT_DISPLAY, eglGetPlatformDisplayEXT
       returns a display backed by the default MiniGUI video engine.

    2. Should this extension support creation EGLPixmap resources from MiniGUI
       memory DC?

       No. The implementation has no pixmap type.

Revision History

    Version 1, 2019-12-10 (Vincent)
        - Initial draft
```

## Using MiniGUI EGL for OpenGL and OpenGL ES

HybridOS project gives some samples to use MiniGUI EGL for OpenGL and OpenGL ES
in the directory `/device-side/samples/himesa` of the following repo:

<https://github.com/FMSoftCN/hybridos>

To check whether the EGL implementation contains the support for
MiniGUI platform, you can use the following code:

```c
#include <EGL/egl.h>
#include <EGL/eglext.h>

static EGLDisplay get_default_minigui_display (void)
{
    const char *extensions;
    extensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);

    if (extensions) {
        if (strstr (extensions, "EGL_EXT_platform_base")) {

            PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay =
                (PFNEGLGETPLATFORMDISPLAYEXTPROC)
                eglGetProcAddress ("eglGetPlatformDisplayEXT");

           if (strstr (extensions, "EGL_EXT_platform_minigui"))
                return getPlatformDisplay (EGL_PLATFORM_MINIGUI_EXT,
                                          EGL_DEFAULT_DISPLAY, NULL);
    }

    return EGL_NO_DISPLAY;
}
```

The function `get_default_minigui_display` checks and returns the
default MiniGUI `EGLDisplay`. If failed, it returns `EGL_NO_DISPLAY`.

Before calling this function, you should call `InitGUI` to initialize MiniGUI.
Note that if you use `MiniGUIMain` instead of `main`, this function will be
called automatically.

Generally, you call the following code to initialize MiniGUI and MiniGUI EGL
in your `main` function:

```c
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

static void _fatal(const char* msg)
{
    fprintf (stderr, msg);
    fprintf (stderr, "\n");
    exit (1);
}

int init_minigui_and_egl(int argc, char* argv[])
{
    EGLNativeDisplayType native_dpy;
    EGLDispaly dpy;
    EGLint major, minor;

    if (InitGUI (argc, (const char**)argv) != 0)
        _fatal("failed to initialize native display");

    native_dpy = (EGLNativeDisplayType)GetVideoHandle (HDC_SCREEN);
    dpy = eglGetDisplay (native_dpy);

    if (!eglInitialize (dpy, &major, &minor))
      _fatal("failed to initialize EGL display");

    return 0;
}

```

After initialized MiniGUI and EGL, you call the following EGL function
on a MiniGUI window to create a window surface:

```c
// Make sure to call eglChooseConfig to choose config before calling
// this function.
static EGLSurface create_window_surface (EGLDisplay dpy, EGLConfig config, HWND hwnd)
{
    EGLContext context;
    EGLSurface surface;
    EGLint context_attribs[4];
    EGLint api, i;

    i = 0;
    context_attribs[i] = EGL_NONE;

    // use OpenGL ES v2
    api = EGL_OPENGL_ES_API;
    context_attribs[i++] = EGL_CONTEXT_CLIENT_VERSION;
    context_attribs[i++] = 2;
    context_attribs[i] = EGL_NONE;

    eglBindAPI (api);

    context = eglCreateContext (dpy,
         config, EGL_NO_CONTEXT, context_attribs);
    if (!context)
        _fatal ("failed to create context");

    surface = eglCreateWindowSurface(dpy,
            config, (EGLNativeWindowType)hwnd, NULL);
    if (surface == EGL_NO_SURFACE)
      _fatal ("failed to create surface");

    if (!eglMakeCurrent(dpy, surface, surface, context))
      _fatal ("failed to make window current");

    // use additional data to store the surface
    SetWindowAdditionalData(hwnd, (DWORD)surface);

    return surface;
}
```

_[TIP]_ You can use the extended style `WS_EX_USEPRIVATECDC` when creating
MiniGUI main window or control for EGL window surface. This extended style
can provide a performance improvement.

After we created a window surface and make the context as the current context,
we can call OpenGL or OpenGL ES APIs to draw our graphics object. When we
finished the rendering, we call `eglSwapBuffers` to swap the content in the
window surface to the MiniGUI window. This generally happens in the handler
of `MSG_PAINT`:

```c
    case MSG_PAINT: {
        EGLSurface surface =
            (EGLSurface)GetWindowAdditionalData(hWnd);

        HDC hdc = BeginPaint (hWnd);
        eglSwapBuffers (dpy, surface);
        EndPaint (hWnd, hdc);
        return 0;
    }
```


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
