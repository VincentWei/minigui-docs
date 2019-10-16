1 Introduction to MiniGUI
=========================

1.1 A Brief Introduction
------------------------

MiniGUI, developed by Beijing FMSoft Technologies Co. Ltd.[^1],
originates from a world famous free software project, which is initiated
by Wei Yongming. MiniGUI aims to provide a fast, stable and lightweight
graphics user interface (GUI) support system for real-time embedded
systems. MiniGUI is “a cross-operating-system graphics user interface
support system for embedded devices”, and “an embedded graphics
middleware”. After over nine years of development since the end of 1998,
MiniGUI has become a stable and reliable one for widespread application
in a variety of products and programs; it can run on Linux/uClinux,
eCos, VxWorks, pSOS, ThreadX, Nucleus, OSE, and even uC/OS-II, also on
the Win32 platform.

MiniGUI defines a set of lightweight windowing and graphics interfaces
for applications. Using these interfaces, an application can create
multiple main windows and controls in them, such as buttons and edit
boxes. MiniGUI provides powerful graphics functions for developers,
helping to display all kinds of bitmaps and draw complicated graphics in
windows.

However, the versions that you download freely from our site would be
only used to develop GPL applications. If you are using MiniGUI for
developing commercial applications or other software that are not
covered by the terms listed in GPL, you should have a commercial license
for MiniGUI from Feynman Software.

Currently, MiniGUI V3.0.x provides support for multi-process-based
operating systems, like Linux; and provides support for traditional
real-time embedded operating systems, which are multi-thread- or
multi-task- based. The former provides support for the runtime modes
MiniGUI-Processes and MiniGUI-Threads, and the later provides support
for the runtime mode MiniGUI-Threads.

The official release of MiniGUI and its components source code package,
sample package, etc., can be downloaded from the MiniGUI official
website[^2].

In addition, the complete source code of MiniGUI and its components is
now hosted on GitHub, which contains the source code repository for the
under development (yet to be released) MiniGUI and its components[^3].

MiniGUI 3.0 is divided into a series of products according to the
operating systems, please see Table 1.1. Table 1.1 also illustrates the
runtime mode(s) provided by the products.

Table 1.1 MiniGUI os and runtime modes supported

  ------------------------------------------------------------
  **Products and versions**    **Runtime mode(s) supported**
  ---------------------------- -------------------------------
  MiniGUI 3.0.x for Linux      MiniGUI-Processes
                               
                               MiniGUI-Threads
                               
                               MiniGUI-Standalone

  MiniGUI 3.0.x for uClinux    MiniGUI-Threads
                               
                               MiniGUI-Standalone

  MiniGUI 3.0.x for VxWorks    MiniGUI-Threads
                               
                               MiniGUI-Standalone

  MiniGUI 3.0.x for ThreadX    MiniGUI-Threads
                               
                               MiniGUI-Standalone

  MiniGUI 3.0.x for uC/OS-II   MiniGUI-Threads
                               
                               MiniGUI-Standalone
  ------------------------------------------------------------

Except for the difference of runtime modes supported, these two versions
have the almost same features.

For the detailed description about runtime modes and MiniGUI features,
please refer to *MiniGUI Technology White paper for V3.0* and *Datasheet
for MiniGUI V3.0*.

1.2 Documents for MiniGUI
-------------------------

Except for this manual, Feynman Software have provided the following
documents available through the official website of MiniGUI download or
visit[^4]:

*MiniGUI Programming Guide* Version 3.0-5. This guide describes in
detail the foundation knowledge of MiniGUI on developing embedded
application software, technical documents and development skills, the
content of which involves various aspects of MiniGUI programming,
include message looping, window procedure, dialog box, controls,
graphics interfaces, and so on.

Datasheet for MiniGUI V3.0.x. MiniGUI feature table.

*MiniGUI API Reference Manual* for MiniGUI Version 3.0. This manual
describes the APIs of MiniGUI V3.0.x (MiniGUI-Processes runtime mode) in
detail[^5].

*MiniGUI Technology White paper* *for V3.0.*

MiniGUI developers also maintain a wiki[^6] site to maintain the latest
version of the above documents, please visit.

1.3 MiniGUI Source Code and Samples
-----------------------------------

In the download area of MiniGUI official website, the following MiniGUI
source code package and sample package are listed:

MiniGUI Core Lib: libminigui-3.0.x-&lt;os&gt;.tar.gz, MiniGUI V3.0.x
library source code for &lt;os&gt; (such as linux) operating system.

MiniGUI Resources: minigui-res-3.0.x.tar.gz, the resources used by
MiniGUI, including basic fonts, icons, bitmaps and mouse cursors.

MiniGUI Samples: mg-samples-3.0.x.tar.gz, a sample program of "MiniGUI
Programming Guide".

Also provide the following source code package:

MiniGUI component.

Tools and dependencies, virtual buffer program GVFB and freetype,
libjpeg, libpng, zlib and other libraries.

1.4 Optional Components of MiniGUI
----------------------------------

Except for the MiniGUI product, Feynman Software also provides some
MiniGUI component products and other MiniGUI applications such as
mSpider. Figure 1.1 shows the product line of Feynman Software.

![](media/image2.jpeg){width="4.760884733158355in"
height="2.801240157480315in"}\
Figure 1.1 Product line of Feynman Software

mGUtils provides users with several functional templates that allow
users to write code for commonly used functions.

mGPlus component is an extension and enhancement of the MiniGUI graphics
rendering interface. It mainly provides support for 2D vector graphics
and advanced graphics algorithms such as paths, gradient fills and color
combinations.

mGEff provides an animation framework for MiniGUI applications. mGEff
provides a large number of stable and efficient effects for developers
to quickly flip, enlarge, scroll, pages and other commonly used
animation has facilitated. In addition, mGEff can be combined with
MiniGUI to develop an animation interface for the main window animation
based on double buffering.

mGNCS - In the development of miniStudio, in order to the WYSWYG design
of visual graphical interface, Feynman Software has developed a new set
of controls based on the existing interface of MiniGUI. The new control
set introduced by miniStudio is based on the original MiniGUI control
set. It is distinguished from MiniGUI Intrinsic Control Set and is
called "New Control Set". As a new MiniGUI Component mGNCS is released.
mGNCS is mainly used with miniStudio. It can also be directly used as a
component of MiniGUI 3.0 and can be mixed with the control of the
centralized control. We strongly recommend that the new MiniGUI
application be developed using mGNCS instead of the MiniGUI built-in
control.

mGi provides input method framework for applications based on MiniGUI.
mGi now provides the framework for soft-keyboard and hand writing input
methods. mGi also provides an IME container for user to add self-defined
IME to it. On the other hand, you can use self-defined keyboard bitmap
for the soft-keyboard and add your self-defined translation method to
it.

mGp provides a printing engine for applications based on MiniGUI so that
applications using mGp will have the printing function. At present, mGp
provides printing support for Epson, HP and some other printers. Note
that mGp only provides the support for Linux operating system.

mG3d is a 3D rendering library for applications based on MiniGUI. By
using this library, you can render 3D objects in your applications.

Except for these three component products above, Feynman Software also
provides MiniGUI SDK for Win32. By using MiniGUI SDK for Win32, you can
run MiniGUI and its applications on Win32 platform. You can even write
and debug MiniGUI applications by using Visual Studio IDE tool. However,
there are some limitations:

MiniGUI SDK for Win32 only provides the support for the runtime
MiniGUI-Threads.

When you use MiniGUI SDK for Win32 to develop MiniGUI application,
please do not invoke any function specific to Win32, because the
function may not exist on your target operating system.

For the complete Feynman products, please visit the following web page:

http://www.minigui.com/en/download/

1.5 miniStudio development tools 
---------------------------------

MiniStudio is an integrated development environment for MiniGUI,
providing users with WYSWYG interface design, automatic generation and
maintenance of MiniGUI program framework, code editing, compiling,
running and debugging based on Eclipse, speeding up the development of
MiniGUI applications and reducing Use the threshold of MiniGUI. When
using MiniGUI, users can focus more on the specific applications related
to the business and greatly reduce the R & D costs of MiniGUI related
applications and provide better products.

miniStudio is a non-open source commercial software product developed by
Feynman Software. It provides two versions of Windows and Ubuntu Linux.
You can visit MiniGUI's official website to download the product for
evaluation or trial license.

1.6 About this Manual
---------------------

This manual mainly describes the compile-time configuration options and
the runtime configuration options of MiniGUI.

