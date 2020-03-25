# Using Compositing Schema

_How to use compositing schema, and write a customized compositor._

Table of Contents

## Overview

In this version, we enhanced the MiniGUI-Processes runtime mode to support
the compositing schema. Under compositing schema, regardless a main window
is created by the server (`mginit`) or a client, it renders the content in
a separate rendering buffer, and the server composites the contents from
all visible main windows to the ultimate scan-out frame buffer according to
the z-order information.

On the contrary, the legacy schema of MiniGUI-Processes uses the same
frame buffer for all processes (and all main windows) in the system.
So the legacy schema is also called the shared frame buffer schema.

Note that we often call a rendering buffer as a `surface`.

MiniGUI Core implements a compositor called 'fallback' as the built-in
compositor, which composites the contents of all windows in the classical
overlapped way.

But you can implement your own compositor by writing your
own server, i.e., `mginit`. You can also implement your customized compositor
in a shared library which can be loaded by MiniGUI Core dynamically.

By enabling the compositing schema, MiniGUI now provides a better
implementation for multi-process environment:

- Easy to implement advanced user interfaces with rounded corners, shadows,
  alpha blending, blurring, and so on.
- Easy to implement animations for switching among main windows.
- Better security. One client created by different user cannot
  read/write contents in/to another windows owned by other clients.

The major flaws of the compositing schema are as follow:

- It needs larger memory than the legacy schema to show multiple
  windows at the same time. Therefore, we may need a client manager
  to kill a client which runs in background and in full screen mode
  if you are running MiniGUI on an embedded system, like Android
  or iOS does.
- It may need a hardware-accelerated NEWGAL engine to get a smooth
  user experience.

### Compile-time configuration for compositing schema

- Use `--enable-compositing` to enable the compositing
  schema when you configure the runtime mode of MiniGUI as
  MiniGUI-Processes (`--with-runmode=procs`).
- Use `--disable-compositing` to disable the compositing schema
  and enable the legacy schema (the shared frame buffer schema).

Note that, the compositing schema only works under MiniGUI-Processes runtime
mode.

### Runtime configuration for compositing schema

```
[compositing_schema]
# The size of wallpaper pattern surface (the fake screen for clients).
# Optional values: <w>x<h>, full, half, quarter, octant, and empty.
# Default value is empty.
wallpaper_pattern_size=full
# wallpaper_pattern_size=half
# wallpaper_pattern_size=quarter
# wallpaper_pattern_size=octant
# wallpaper_pattern_size=empty
# wallpaper_pattern_size=32x32
compositor=my_compositor.so
```

As mentioned above, when using the compositing schema, the client processes
can not access the ultimate scan out frame buffer. However, MiniGUI provides
a graphics device context called `HDC_SCREEN` for apps. In order to provide
a backward compatibility, we implement the `HDC_SCREEN` as a special surface
which can be shared among all processes under MiniGUI-Processes runtime mode,
and one compositor can use the contents in this surface to render the wallpaper.

We call the special surface as the wallpaper pattern. You can specify the
size via the runtime configuration key `compsoting_schema.wallpaper_patter_size`.
All contents you rendered by using `HDC_SCREEN` in your applications will
appears in the shared surface ultimately. And the compositor can use the contents
in the shared surface to show a wallpaper or just ignore it.

The key in the runtime configuration `compsoiting_schema.compsoitor` specify
the shared library to load as the default compositor. If it is not specified, or
failed to load it, MiniGUI will use the built-in compositor: the fallback
compositor.

The fallback compositor implement a group of basic compositing actions. It renders
the contents of all visible main windows in the classical overlapped way in their
intrinsic z-order information. It keeps as simple as possible, so it does not
implement the following features:

- no border shadows.
- no support for complex compositing types, e.g., blurred.
- no any visual animations.

## New APIs for compositing schema

In order to use the compositing schema under MiniGUI-Processes runtime mode,
we introduce some new APIs for the app:

- `CreateMainWindowEx2`: This function is an extension of `CreateMainWindowEx`.
  It creates a main window by using the legacy create information and the
  specified compositing type, the compositing argument, the surface type,
  the background color, and returns the handle to the new main window:
   + The compositing type: one of `CT_OPAQUE`, `CT_COLORKEY`,
     `CT_ALPHACHANNEL`, `CT_ALPHAPIXEL`, `CT_BLURRED`, or other compositing
     types defined by a customized compositor. By using this argument, you
     specify how the contents in a main window will be composited to the
     screen.
   + The compositing argument: one DWORD value. You generally pass a color
     for this argument. For example, for the compositing type `CT_COLORKEY`,
     you need to use this argument to tell the compositor the color acts
     as the key.
   + The surface type: you can specify the new main window uses a different
     surface type instead of the one same as the screen. Here the surface type
     mainly means the pixel format of the surface. For example, on a screen
     with RGB656 pixel format, if you want to use the compositing type
     `CT_ALPHAPIXEL`, you need to create a surface with type `ST_PIXEL_ARGB8888`
     or `ST_PIXEL_ARGB4444`.
   + The background color in DWORD representation. When you use a surface type
     other than `ST_PIXEL_DEFAULT`, you need this argument to pass the background
     color of the main window in a DWORD value. This is because that
     you can only pass a pixel value in the default screen surface type via
     the legacy create information structure (`MAINWINCREATE`).
- `SetMainWindowCompositing`: This function sets the compositing type and
  the compositing argument of a main window. By using this function,
  you can change the compositing type and the argument of a main window on the fly.

MiniGUI defines the following built-in compositing types:

- `CT_OPAQUE`: The main window is opaque. This is the default compositing type
  if you create a main window by calling legacy `CreateMainWindow` and
  `CreateMainWindowEx` functions.
- `CT_COLORKEY`: Use a specific color as the transparency key when composting
  the contents of the main window to the screen. You should specify
  the color along with the compositing argument in a DWORD representation.
- `CT_ALPHACHANNEL`: Use a specific alpha channel value when compositing the
  contents of the main window to the screen.
- `CT_ALPHAPIXEL`: Use the alpha component of the rendering buffer when
  composting the contents of the main window.
- `CT_BLURRED`: Apply a Gaussian blur to the contents blew of the main window.
  Generally, when using this composting type, the alpha component of the pixels
  will go into effect.

Note that MiniGUI allows a customized compositor to define new compositing types.

## Writing a Customized Compositor

If you want to develop a new compositor, you may need the following new APIs:

- `ServerRegisterCompositor`: Register a compositor.
- `ServerUnregisterCompositor`: Unregister a compositor.
- `ServerSelectCompositor`: Select a compositor.
- `ServerGetCompositorOps`: Get the operations of a specific compositor.

As mentioned before, MiniGUI will try to load the default compositor defined
by the runtime configuration key `compositing_schema.compositor` first.
MiniGUI will call a stub called `__ex_compositor_get` in the shared library to
get the pointer to the compositor operation structure for the default compositor,
and select the compositor as the current compositor.

When implementing your customized compositor, you may need the following APIs
to get the z-order information and the information of a z-order node:

- `ServerGetNextZNode` or `ServerGetPrevZNode`: travels the z-order nodes.
- `ServerGetWinZNodeHeader` and `ServerReleaseWinZNodeHeader`: get/lock and
  release a z-node of a main window.
- `ServerGetPopupMenusCount`, `ServerGetPopupMenuZNodeHeader`, and
  `ServerReleasePopupMenuZNodeHeader`: get/lock and release a z-order node
  of pop-up menus.
- `ServerGetPopupMenuZNodeRegion` and `ServerGetWinZNodeRegion`:
- `ServerSetWinZNodePrivateData` and `ServerGetWinZNodePrivateData`:
- `ServerSetPopupMenuZNodePrivateData` and `ServerGetPopupMenuZNodePrivateData`:

By using the information returned by the functions above and the basic GDI
functions of MiniGUI, you can easily implement a customized compositor.

Note that:

- A compositor always runs in the server, i.e., `mginit`. A client of
  MiniGUI-Processes can not call these functions.
- A compositor always compositing the contents from z-nodes to the special DC
  called `HDC_SCREEN_SYS`. This DC is the only one represents the ultimate
  screen under compositing schema.
- You should call `SyncUpdateDC (HDC_SCREEN_SYS);` when you need to update the
  rendering result to the screen.
- You can use a third-party graphics library like Cairo, OpenGL, OpenGL ES, or
  mGPlus to render the contents in your customized compositor.

You can refer to the source code of the fallback compositor for the usage of
the functions above:

```
minigui/src/kernel/compsor-fallback.c
```

