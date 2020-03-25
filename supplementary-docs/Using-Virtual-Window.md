# Using Virtual Window

_Using virtual window for mulithreading applications._

Table of Contents


## Overview

You know that we can post or send a message to other windows which
may run in another thread under MiniGUI-Threads. The MiniGUI
messaging functions such as `PostMessage()`, `SendMessage()`,
`SendNotifyMessage()`, and the window callback procedure
provide a flexible, efficient, safe, and flexible data transfer
and synchronization mechanism for your multithreaded applications.

For example, you can send or post a message to a window from a
general purpose thread which may download a file from a remote
server under MiniGUI-Threads.

But can we use the MiniGUI messaging mechanism under
MiniGUI-Processes and MiniGUI-Standalone runtime modes for
multithreading purpose? For example, we may download a file in a
general thread and inform a window when the file is ready.

Furthermore, if we want to use the MiniGUI messaging mechanism in
a general thread to handle messages from other threads, how to do this?

The virtual window provides a solution for the requirements above.
A virtual window is a special window object which does not have
a visible window area. But after you create a virtual window in
a different thread, you can use the MiniGUI messaging mechanism
to post or send messages between the current main window thread
and the new thread.

In MiniGUI, we call a thread creating a main window as a GUI thread,
and a thread creating a virtual window as a message thread.

It is important to know the following key points about virtual
window:

- It is enabled automatically under MiniGUI-Threads runtime mode.
- It can be enabled by using the compile-time configuration option
  `--enable-virtualwindow`, or define `_MGHAVE_VIRTUAL_WINDOW` macro
  under MiniGUI-Processes and MiniGUI-Standalone runtime modes.
- You can create multiple GUI threads under MiniGUI-Threads, but you
  cannot create multiple GUI threads under MiniGUI-Processes and
  MiniGUI-Standalone runtime modes. In other words, there is only one
  GUI thread (the main thread) under MiniGUI-Processes and
  MiniGUI-Standalone runtime modes.
- Regardless of the runtime mode, you can create multiple message
  threads, and you can also create multiple virtual windows in
  one message thread.
- It is possible to create a virtual window in a GUI thread, although
  we do not encourage to do this.
- Essentially, a virtual window is a simplified main window.
  It consumes very little memory space, but provides a complete
  MiniGUI messaging mechanism for a general multithreaded app.
- When virtual window is enabled (or under MiniGUI-Threads runtime mode),
  you can use the MiniGUI messaging facilities to post or send messages
  to a window, or notify a window from a general thread.

A virtual window will get the following system messages in its life
life-cycle:

 - `MSG_CREATE`: this message will be sent to the virtual window when
   you call \a `CreateVirtualWindow` function.
 - `MSG_CLOSE`: this message will be sent to the virtual window when
   the system asks to close the virtual window.
 - `MSG_DESTROY`: this message will be sent to the virtual window when
   the system tries to destroy the virtual window, or after you
   called \a `DestroyVirtualWindow` function.
 - `MSG_IDLE`: When there is no any message in the message queue, all
   virtual windows living in the message thread will get this idle
   message.
 - `MSG_TIMER`: When a timer expired after you call `SetTimer` to
   set up a timer for a virtual window.
 - `MSG_QUIT`: quit the message loop.
 - `MSG_GETTEXT`: To query the caption of the virtual window.
 - `MSG_SETTEXT`: To set the caption of the virtual window.
 - `MSG_GETTEXTLENGTH`: To query the caption length of the virtual window.
 - `MSG_FDEVENT`: Send to the window procedure when there is a read/write/except
   event on a listened file descriptor.

You can call `DefaultVirtualWinProc` in your window procedure for a virtual
window for the default handling of the messages above.

A virtual window has the following properties:

- The additional data and the additional data 2.
- The identifier in a LINT value.
- The notification callback procedure.
- The caption.
- The local data.

Therefore, the following APIs can be called for a virtual window:

- `DefaultWindowProc`
- `GetWindowId`
- `SetWindowId`
- `GetThreadByWindow`
- `GetWindowAdditionalData`
- `SetWindowAdditionalData`
- `GetWindowAdditionalData2`
- `SetWindowAdditionalData2`
- `GetClassName`: always returns `VIRTWINDOW` for a virtual window.
- `GetWindowCallbackProc`
- `SetWindowCallbackProc`
- `GetWindowCaption`
- `SetWindowCaption`
- `GetWindowTextLength`
- `GetWindowText`
- `SetWindowText`
- `GetNotificationCallback`
- `SetNotificationCallback`
- `SetWindowLocalData`
- `GetWindowLocalData`
- `RemoveWindowLocalData`
- `RegisterEventHookWindow`
- `UnregisterEventHookWindow`
- `RegisterKeyHookWindow`
- `RegisterMouseHookWindow`
- `RegisterListenFD`
- `UnregisterListenFD`

Like a main window, when you want to create a virtual window, you call
`CreateVirtualWindow`, and when you wan to destroy a virtual window, you call
`DestroyVirtualWindow`. You must call `VirtualWindowCleanup` to cleanup the
system resource used by the virtual window after done with it, e.g., after
quitting the message loop.


