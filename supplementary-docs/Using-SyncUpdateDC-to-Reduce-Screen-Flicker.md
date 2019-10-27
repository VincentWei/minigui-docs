# Using SyncUpdateDC to Reduce Screen Flicker

_Use MiniGUI's synchronous update mechanism to reduce screen flicker._

Table of Contents

- [Overview](#overview)
- [Principle](#principle)
- [Usage](#usage)
- [Restrictions](#restrictions)

## Overview

In the development of a GUI app, we often need to update an area on the
screen multiple times just for a user input. For example, if the user
presses the up and down keys, the highlighted item in the list box will
change. At this point, the program should perform the following operations:

1. Erase the original highlighted item with the background color of
   a normal item;
1. Draw the text of the original highlighted item with the foreground
   color of the normal item;
1. Erase the new highlighted item with the background color of the
   highlighted item;
1. Draw the text of the new highlighted item with the foreground color
   of the highlighted item.

This frequent drawing will cause the screen to flicker if we don't do
any special processing.

Generally, we can use one of the following ways to eliminate this flicker:

1. Create a memory DC and draw content to the memory DC first, then
   call `BitBlt` to blit the content to screen.
1. Use MiniGUI's double buffer main window. This is essentially the
   same method as the first one.
1. Use the new synchronous update mechanism introduced in MiniGUI 3.2.x.

This documents describes how to use the new synchronous update mechanism
to reduce the screen flicker.

## Principle

Essentially, the new synchronous update mechanism uses a shadow frame
buffer for MiniGUI, and refresh the content that needs to be updated to
the screen at one time, by calling `SyncUpdateDC` function.

In this way, we do not need to create and destroy memory DC frequently,
so we will get a certain degree of performance improvement.
And the MiniGUI app's code can keep as simple as possible.
In other words, we can improve the maintainability of the code as well.

## Usage

- Including option `--enable-syncupdate` when configuring MiniGUI.
- Using a shadow-like NEWGAL engine and implementing `UpdateRects` method
  of your NEWGAL engine to update the dirty regions to your real
  screen frame buffer.
- Calling `SyncUpdateDC(HDC_SCREEN)` when you want to update the
  screen. Generally, you can call this function after calling `EndPaint`
  function when handling `MSG_PAINT` message.

## Sample

To be added.

## Restrictions

The synchronous update mechanism provides an easy way to reduce
the screen flicker. However, it has the following restrictions:

- It is not suitable to a screen with high resolution.
- It may hide the side effects of some inefficient code in
  your MiniGUI app.
- It lacks support for hardware acceleration.

Therefore, for modern graphics stack (system shipped with a GPU),
the better way is using off-screen surface and exploiting the
hardware acceleration as much as possible.

