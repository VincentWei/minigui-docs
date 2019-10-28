# Brief Introduction to mGNCS

## Introduction of the New Control Set

In the development of miniStudio, in order to realize the design of visual
graphic interface, based on MiniGUI existing interfaces, `FMSoft` developed a
new control set. The new control set introduced by miniStudio is developed on
the foundation of the original MiniGUI control set. In order to distinguish it
from MiniGUI intrinsic control set, it is referred to as “new control set 
(mGNCS in short)”.

Features of the new control set are as follows:

- Object-oriented programming idea is adopted to rearrange the inheritance
relations between the controls. C language is used to realize concepts similar
to C++ class, and C language interface is provided externally. In this respect,
the new control set introduced by miniStudio is similar to the control set of
Gtk+. 
- Interfaces and styles of the controls are standardized, enabling all controls
to access with uniform interface.
- Based on MiniGUI 3.0 look and feel renderer, the concept of look and feel
renderer is further expanded. Each control in the new control set has its own
look and feel renderer and exclusive renderer interface of each control is
defined according to the inheritance rule of the controls, enabling them to
change along with the changes of controls.
- Through developing the new control set, we settle the deficiencies of MiniGUI
intrinsic control set in the following aspects simultaneously.
- The interfaces are not uniform and standardized;
- Operating controls through messages, it is difficult to maintain codes and
easy to make mistakes;
- Hierarchical relation of intrinsic control is unclear, there are many 
repeated codes, and it is inconvenient to customize and extend control
functions; 
- Drawing efficiency of the intrinsic control is low, and twinkling problem is
serious when running on the development board.

In the new control set, there exist the following classes:

- Control class. This class is used to represent all kinds of controls (such as
main window, static box, button and list box etc.), which are the classes with
visualized feature in MiniGUI applications. It needs to be noted that the
concept of “control” stated in mGNCS has broader extension than that of the
“control” stated by MiniGUI, which includes objects such as the main window 
etc. simultaneously. While the control referred to by MiniGUI is only used for
child window. In mGNCS, all the control classes are derived from `mWidget`
class. 
- Non control class. This class is used to maintain class hierarchical 
structure and data used by the controls etc., which includes the following
kinds: 
- Super class, it is the most foundational class in mGNCS class hierarchical
structure, and all other classes are derived from this class, which is 
`mObject` class.
- General class, this class is used to realize mechanisms such as data source
and data binding etc., and it is also used to maintain the data used by the
controls, such as `mItem` class.
- Invisible component class, this class is used to represent the invisible
components used in the interface such as timer etc., which is collectively
referred to as component class together with control class (equivalent to
visible component class).

A control is composed of the following parts:

- Object and class: mGNCS uses an object structure and class structure to
represent a class. The class structure mainly defines a group of function
pointers to simulate virtual function table of C++ class, so as to realize the
inheritance and multi-status capability. While object structure defines a data
structure related to class case.
- Control class name: A unique character string identifies a control class, and
corresponding C language macro uses `NCSCTRL_` as the prefix.
- Control style: same as the style concept of MiniGUI intrinsic control set. In
the new control set, style is only used in the properties that can be 
determined at control initialization and will not change in the whole life 
cycle of the control.
- Control property: the new control set can extract the features that can be
controlled through control through get/set method and set an integer identifier
for each item, and accesses and controls the behavior and status of a control
through `setProperty` and `getProperty` method of the class structure.
- Control event: the concept of message and notification code in MiniGUI are
combined, and event of control can be responded through setting the callback
function of a specific event.
- Look and feel renderer: in mGNCS, drawing of each control is realized by
special look and feel renderer. The new control set provides classic, fashion,
skin and flat look and feel renderers by default. Control can choose any one
valid renderer and adjust the look and feel of the control through setting
specific properties (such as color and size etc.) for the renderer. For the
convenience of description, the look and feel renderers stated in this guide 
are referred to as renderer. In order to distinguish from the renderers of the
control itself, renderers defined by MiniGUI 3.0 are referred to as “global
renderer”, and renderers introduced by the new control set are referred to as
“control renderer”. Effects of the two kinds of renderers have the following
differences: 
- Global renderer acts on the main window, MiniGUI intrinsic control set and
system components of the new control set (such as non client area elements such
as border, title bar, and scroll bar etc.).
- Control renderer only acts on the client area drawing of each control of the
new control set.

In addition, the invisible components defined by the new control set have
interfaces similar to that of control class. At present, timer is realized, in
the later edition, the components planned to realize are special effect
switching component and program logic control component etc.

The new control set is mainly used in cooperation with miniStudio and can also
be directly used as a component of MiniGUI 3.0, and it can be used in mixture
with the controls in the intrinsic control set.

## Content Organization of This Guide

This guide is divided into the following appendixes:

- Part 1: It introduces the basic concept and system structure of mGNCS.
- Part 2: facing application developers, it states how to use mGNCS to develop
applications and describes the main `API` interface in detail.
- Part 3: facing the developers of the new control set, it states how to 
develop new controls and renderers etc. for mGNCS.
- Appendix: Compiling Norm for This Document and Content of Other Rapid
References etc.

[Next](MStudioMGNCSV1dot0PGEN][Index]] > [[MStudioMGNCSV1dot0PGENP1C2)

----

[&lt;&lt; Using mGUtils](MiniGUIProgGuidePart1Chapter12.md) |
[Table of Contents](README.md) |
[Quick Start &gt;&gt;](MiniGUIProgGuidePart2Chapter02.md)

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
