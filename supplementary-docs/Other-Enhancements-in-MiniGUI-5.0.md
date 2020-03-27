# Other Enhancements in MiniGUI 5.0

_How to use the other minor enhancements in MiniGUI 5.0._

Table of Contents

## Overview

## Window identifier

Before 5.0.0, MiniGUI only provides the APIs to retrieve a control based on
the identifier. Since 5.0.0, you can calling the following APIs on a
main window or a virtual window on the basis of identifier:

- `GetWindowId`: return the identifier of a specific window.
- `SetWindowId`: set the identifier of a specific window.

Note that all main windows and/or virtual windows in a thread form a window tree.
The root window of the tree may be `HWND_DESKTOP` or the first main/virtual
window created in the thread. You can call `GetRootWindow` to retrieve the
root window of the current thread.

You can travel the window tree by calling the old API `GetNextHosted`. Since 5.0.0,
you can retrieve a hosted main window or virtual window via a specific identifier
by calling `GetHostedById` function.

## Local data of a window

Local data of a window are some void objects represented in DWORD values, and they
are bound with different string names. In a window's life cycle, you can set, get,
or remove a local data which is bound with a specific name. This provides an
easy-to-use way to manage multiple and complex objects of a window.

- `SetWindowLocalData`: set a local data.
- `GetWindowLocalData`: get a local data.
- `RemoveWindowLocalData`: remove a local data.

Note that all local data will be removed automatically when you destroy a window.

## Hardware cursor

Under the compositing schema, MiniGUI now can use the hardware cursor to show
the mouse pointer. And you can use the following APIs to load a PNG file as
the cursor:

- `LoadCursorFromPNGFile`
- `LoadCursorFromPNGMem`

For a GAL engine which supports hardware cursors, it needs to implement the
following new methods:

- `AllocDumbSurface`/`FreeDumbSurface`: allocate/free a dumb surface.
  Note that each hardware cursor uses a specific dumb surface. Here, a `dumb`
  surface is a term introduced by the DRM driver of Linux. It means that
  the surface does not provide any hardware acceleration functions.
- `SetCursor`: Set a dumb surface as the cursor, along with the hotspot of
  of the cursor.
- `MoveCursor`: Move the cursor to a new position.

## Loading an icon from bitmap files

As described before, you can create a main window to use a special surface type
under compositing schema. That is, the surface for the main window will have
a different pixel type from the screen. In other words, it is not compatible
with the screen. Therefore, we have to change some internal implementation
to reflect this enhancement. One of the changes is the icon of a window.

Since 5.0.0, an icon for a main window is always stored in a ARGB8888 surface,
so that it can be rendered correctly into the surface of any main window.

We also introduced some new APIs to load an icon from a PNG file or other bitmap
files:

- `LoadBitmapIconEx`, `LoadBitmapIconFromFile`, and `LoadBitmapIconFromMem`.

## Loading system bitmaps for private surface

Another change is about the system bitmaps. The system bitmaps are often used
by a look-and-feel renderer to render the caption bar or the border of
a main window or a control. For a main window which may have a different surface
type under compositing schema, one L&F renderer can not use the system bitmaps
loaded by `GetSystemBitmapEx` function. Because the function only loads the
system bitmaps for `HDC_SCREEN`.

Therefore, we introduce a new function to load the system bitmaps:

- `GetSystemBitmapEx2`. This function will load the system bitmaps for
   the specific device context.

We have tuned the built-in look and feel renderers to use the new function
to load the system bitmaps. If you want to use a customized look and feel
renderer under compositing schema, you must change the code to use the new
function to load the system bitmaps.

## Unified event hook functions

- `RegisterEventHookFunc`
- `RegisterEventHookWindow` and `UnregisterEventHookWindow`

## Listening file descriptor under all runtime modes

Since 5.0.0, MiniGUI provides support for listening a file descriptor
as long as the underlying system has the `select()` system call for all
runtime modes. Now you can call `RegisterListenFD()` to register a
file descriptor to be listened, and handle `MSG_FDEVENT` in your window
callback procedure to read/write from/to the file descriptor.

Before this version, this feature only available for MiniGUI-Processes
runtime mode.

By using this feature, you can listen and handle a file descriptor in
a message thread by using the virtual window. This is a powerful mechanism
for a multithreaded application.

Note that MiniGUI no longer limits the max number of listening file descriptors,
MiniGUI will try to allocate space to manage all listening file descriptors.

## Enhanced timer

Since 5.0.0, MiniGUI manages the timers per message thread.
Under MiniGUI-Threads runtime mode, you can set up 32 (64 on 64-bit
architecture) timers for each GUI threads. If you enabled virtual window,
you can also do this for each message thread.

The function `IsTimerInstalled` checks the timers installed for the current
thread, and the function `HaveFreeTimer` also checks the free timer slots
for the current thread.

## Other new APIs

For MiniGUI-Processes runtime mode:

- `IsServer`: Under MiniGUI-Processes runtime mode, return whether the process
   is the server (`mginit`) or a client.
- `MoveToLayer`: Called by a client to move itself to a specific layer. .
- `ServerMoveClientToLayer`: The server version of `MoveToLayer`.
- `ServerSendReplyEx`: The extended version of legacy `ServerSendRely`. It can
   transfer a file descriptor between the server and the client.
- `RegisterRequestHandlerV1`: To register a request handler in version 1. The
   request handler can handle the file descriptor received from the client.
- `GetRequestHandlerV1`: Get the registered request handler in version 1.
- `GetRequestHandlerEx`: Get the registered request handler and its version.

Global scope:

- `GetScreenRect`: Return a RECT as the screen rectangle.

For MiniGUI-Threads or when virtual window enabled:

- `GetThreadByWindow`: Return the thread identifier of a window.
- `IsWindowInThisThread`: Determine whether a window is created by the current
   thread.
- `IsVirtualWindow`: Determine whether a window is a virtual window.
- `CreateThreadForMessaging`: Create a thread for messaging.

For messaging mechanism:

- `SendPriorNotifyMessage`: Send a prior notification message. Generally, a
   notification message is put at the tail of the message list. This function
   put the notification message at the head of the list.
- `NotifyWindow`: Send a notification message to a specific window.
- `BroadcastMessageInThisThread`: Broadcast a message in the current thread.
- `PreDefVirtualWinProc`: The pre-defined window procedure for a virtual window.
- `DefaultVirtualWinProc`: The default window procedure for a virtual window.

- `GetDCEx`: A extended version of `GetDC` and `GetClientDC`.
- `GetEffectiveCDC`: Get a effective device context for painting a window.
- `GetDCInSecondarySurface`: Get a device content for a main window or a control
   in the secondary surface if the main window has set the secondary DC.
- `DWORD2PixelByWindow`: Convert a DWORD color to pixel value for a window..
- `AreRegionsIntersected`: Determine whether two regions are intersected.
- `SyncUpdateSurface`: Synchronize the update rectangles of the backing surface of
   a window to screen.
- `SyncUpdateDC`: Synchronize the update rectangles of the surface corresponding to
   a DC to screen.
- `LoadBitmapEx2`: The extended version of legacy `LoadBitmapEx` function. You can
   specify a callback to allocate the buffer for the MiniGUI bitmap loader.

- `MSG_MOVEWINDOW`: This message will be sent as a notification after calling
  `MoveWindow`.

