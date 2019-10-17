# Quick Start

- [Introduction](#introduction)
  * [Source Tarballs and Repos](#source-tarballs-and-repos)
  * [Documents](#documents)
- [First Run](#first-run)

## Introduction

MiniGUI, developed by [FMSoft Technologies],
originates from a famous free and open source software project,
which is initiated by Wei Yongming. MiniGUI aims to provide a fast,
stable and lightweight graphics user interface (GUI) support system
for real-time embedded systems and smart IoT devices. After over 20
years of development since the end of 1998, MiniGUI has become
a stable and reliable one for widespread application in a variety
of products and programs; it can run on Linux/uClinux, ThreadX,
RT-Thread, RTEMS, FreeRTOS, eCos, VxWorks, pSOS, ThreadX, Nucleus,
OSE, and even uC/OS-II.

MiniGUI defines a set of lightweight windowing and graphics interfaces
for applications. Using these interfaces, an application can create
multiple main windows and controls in them, such as buttons and edit
boxes. MiniGUI provides powerful graphics functions for developers,
helping to display all kinds of bitmaps and draw complicated graphics in
windows.

MiniGUI consists of MiniGUI Core and multiple MiniGUI components.

MiniGUI Core provides the basic windowing and graphics interfaces
as well as a lot of standard controls (toolkit). Besides MiniGUI Core,
FMSoft also releases some components for easy development of MiniGUI apps:

- `mGUtils` contains miscellaneous utilities
  like `ColorSelectionDialogBox`, `FileOpenDialogBox`, and so on.
- `mGPlus` provides support for 2D vector
  graphics functions like path, gradient, anti-aliased stretch,
  and color combination.
- `mGEff` provides an animation framework for
  MiniGUI app. It also provides some popular UI special effects.
- `mGNCS` provides a new control set for
  MiniGUI app.
- `mGNCS4Touch` provides some new controls, which are compliant to
  the control specification of mGNCS, for devices with touch screens.

There are also some legacy MiniGUI components. But we no longer maintain
these components since MiniGUI v3.2.0:

* mGi: An input method component for MiniGUI. This component provides
  some typical input methods (such as soft keyboard, hand-writing, and
  predict text input for mobile phone) for MiniGUI apps.
* mGp: A printing component for MiniGUI. By using mGp, you can print
  out the graphics created by MiniGUI app to general-purpose printers.
* mG3d: A simple three-dimension component for MiniGUI. This component
  provides a simple 3D API for app. You can use mG3d to create simple
  3D UI.

### Source Tarballs and Repos

The source code tarballs of MiniGUI and its components can be
downloaded from the download zone of [MiniGUI Official Website]:

<http://www.minigui.com/en/download>

FMSoft had created the public repositories for MiniGUI core and
components on GitHub. You can visit them on:

<https://github.com/VincentWei>

FMSoft also releases some open source apps for MiniGUI on the site above,
for examples:

* mDolphin, licensed under Apache 2.0, is a full-featured
  WEB/WAP browser, which is developed based on the open source browser
  core WebKit and uses MiniGUI as its underlying graphics support system.
* mGallery, licensed under Apache 2.0, intends to
  provide a total solution for PMP (Portable Multimedia Player),
  which uses MiniGUI as the graphics platform.
* mSpider, licensed under GPL 3.0, intends to provide a
  light-weight MiniGUI-based web browser (HTML 3.2 and part JavaScript)
* mEagle, licensed under GPL 3.0, is an embedded GIS development platform
  which addresses the needs of map browse, query, analysis, etc

You can find the public repositories of above apps on:

<https://github.com/FMSoftCN>

Besides MiniGUI, FMSoft also releases some tools and dependencies of MiniGUI,
such as the virtual buffer program GVFB, freetype, libjpeg, libpng, zlib,
and others. Please refer to:

<http://www.minigui.com/en/download>

### Documents

FMSoft now maintains the documents of MiniGUI on GitHub:

<https://github.com/VincentWei/minigui-docs>

All documents are classified into the following volumes:

- [MiniGUI User Manual]: The user manual describes how to configure,
build, and run MiniGUI.
- [MiniGUI Programming Guide]: This guide describes in
detail the foundation knowledge of MiniGUI on developing MiniGUI apps.
- [MiniGUI Porting Guide]: This guide describes how to port MiniGUI
to various RTOSes.
- [MiniGUI API Reference Manuals]: The online API reference manuals for
MiniGUI core and MiniGUI components.

We also maintain some supplementary documents on MiniGUI Wiki:

<https://github.com/VincentWei/minigui/wiki>

## First Run

*TBC*

---

[Table of Contents](README.md)  
[Next Chapter](MiniGUIUserManualChapter2.md)

[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[MiniGUI Official Website]: http://www.minigui.com
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md
