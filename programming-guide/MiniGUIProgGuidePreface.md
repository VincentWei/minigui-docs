# Preface


MiniGUI is a mature cross-platform windowing system and a GUI
(Graphics User Interface) support system for embedded systems and
smart IoT devices.

MiniGUI aims to provide a fast, stable, full-featured, tailorable,
and cross-platform windowing and GUI support system, which is especially
fit for embedded systems or smart IoT devices based-on Linux/uClinux,
eCos, and other traditional RTOSes, such as ThreadX, FreeRTOS, RTEMS,
RT-Thread, VxWorks, Nucleus, pSOS, uC/OS-II, and OSE.

This handbook is the programming guide for the MiniGUI version 3.2 or later.
It describes how to develop applications based on MiniGUI core and the following
MiniGUI components:

- mGUtils: This component contains miscellaneous utilities like
  `ColorSelectionDialogBox`, `FileOpenDialogBox`, and so on.
- mGPlus: This component provides support for 2D vector graphics functions like
  path, gradient, anti-aliased stretch, and color combination.
- mGEff: This component provides an animation framework for MiniGUI app.
  It also provides some popular UI/UE special effects.
- mGNCS: This component provides a new control set for MiniGUI app, and a new
  framework for MiniGUI apps as well. By using mGNCS, you can use miniStudio to
  develop MiniGUI app in WYSIWYG way.
- mGNCS4Touch: This component provides some new controls, which are
  compliant to the new control API spec of mGNCS, for devices with
  touch screens.

This handbook is a complete guide on MiniGUI programming, which describes the
foundation knowledge of MiniGUI programming and various programming methods and
skills, and describes the main API functions in detail. Though the handbook
tries to describe various aspects of MiniGUI programming at length, it is not
a complete reference manual about MiniGUI APIs; please refer to
[MiniGUI API Reference Manuals] for relevant information.

## Related Documents

The documents related to this guide:

- [MiniGUI Overview] - The goals, features, advantages, and road map of MiniGUI.
- [MiniGUI User Manual] - How to configure, install, and run MiniGUI.
- [MiniGUI Supplementary Documents] - Supplementary documents about new features.
- API Reference Manuals for MiniGUI Core:
   * [MiniGUI 4.0 API Reference (MiniGUI-Processes mode)](http://www.minigui.com/doc-api-ref-minigui-procs-4.0.0/html/index.html) - The API reference for MiniGUI V4.0 multi-process runmode.
   * [MiniGUI 4.0 API Reference (MiniGUI-Threads mode)](http://www.minigui.com/doc-api-ref-minigui-ths-4.0.0/html/index.html) - The API reference for MiniGUI V4.0 multi-thread runmode.
   * [MiniGUI 4.0 API Reference (MiniGUI-Standalone mode)](http://www.minigui.com/doc-api-ref-minigui-sa-4.0.0/html/index.html) - The API reference for MiniGUI V4.0 standalone runmode.
   * [MiniGUI 3.2 API Reference (MiniGUI-Processes mode)](http://www.minigui.com/api_ref/minigui-3.2.0/procs/index.html) - The API reference for MiniGUI V3.2 multi-process runmode.
   * [MiniGUI 3.2 API Reference (MiniGUI-Threads mode)](http://www.minigui.com/api_ref/minigui-3.2.0/ths/index.html) - The API reference for MiniGUI V3.2 multi-thread runmode.
   * [MiniGUI 3.2 API Reference (MiniGUI-Standalone mode)](http://www.minigui.com/api_ref/minigui-3.2.0/sa/index.html) - The API reference for MiniGUI V3.2 standalone runmode.
- API Reference for MiniGUI Components:
   * [mGUtils 1.2 API Reference](http://www.minigui.com/doc-api-ref-mgutils-1.2.2/html/index.html) - The API reference for mGUtils V1.2.
   * [mGPlus 1.4 API Reference](http://www.minigui.com/doc-api-ref-mgplus-1.4.0/html/index.html) - The API reference for mGUtils V1.4.
   * [mGEff 1.2 API Reference](http://www.minigui.com/doc-api-ref-mgeff-1.2.2/html/index.html) - The API reference for mGEff V1.2.
   * [mGNCS 1.2 API Reference](http://www.minigui.com/doc-api-ref-mgncs-1.2.4/html/index.html) - The API reference for mGNCS V1.2.
   * [mGNCS4Touch 1.2 API Reference](http://www.minigui.com/doc-api-ref-mgncs4touch-1.2.2/html/index.html) - The API reference for mGNCS4Touch V1.2.
- Links to Release Notes:
   * [MiniGUI Core](https://github.com/VincentWei/minigui/blob/master/RELEASE-NOTES.md)
   * [mGUtils](https://github.com/VincentWei/mgutils/blob/master/RELEASE-NOTES.md)
   * [mGPlus](https://github.com/VincentWei/mgplus/blob/master/RELEASE-NOTES.md)
   * [mGEff](https://github.com/VincentWei/mgeff/blob/master/RELEASE-NOTES.md)
   * [mGNCS](https://github.com/VincentWei/mgncs/blob/master/RELEASE-NOTES.md)
   * [mGNCS4Touch](https://github.com/VincentWei/mgncs4touch/blob/master/RELEASE-NOTES.md)

## Organization of this Guide

Except this preface, the text is divided into six parts (dozens chapters)
and an appendix in total:

- Part I: Foundation of MiniGUI Programming.
  We describe the foundation concepts of MiniGUI programming in this part.
   - [Beginning MiniGUI Programming](MiniGUIProgGuidePart1Chapter01.md)
   - [Window and Message](MiniGUIProgGuidePart1Chapter02.md)
   - [Foundation of Dialog Box Programming](MiniGUIProgGuidePart1Chapter03.md)
   - [Foundation of Control Programming](MiniGUIProgGuidePart1Chapter04.md)
   - [Advanced Programming of Control](MiniGUIProgGuidePart1Chapter05.md)
   - [Menu](MiniGUIProgGuidePart1Chapter06.md)
   - [Scrollbar](MiniGUIProgGuidePart1Chapter07.md)
   - [Keyboard and Mouse](MiniGUIProgGuidePart1Chapter08.md)
   - [Icon, Cursor, and Caret](MiniGUIProgGuidePart1Chapter09.md)
   - [Look-and-feel and UI effects](MiniGUIProgGuidePart1Chapter10.md)
   - [Other Programming Topics](MiniGUIProgGuidePart1Chapter11.md)
   - [Using mGUtils](MiniGUIProgGuidePart1Chapter12.md)
- Part II: Using mGNCS.
  We describe the concepts and the use of main APIs of mGNCS in this part.
   - [Brief Introduction to mGNCS](MiniGUIProgGuidePart2Chapter01.md)
   - [Getting Started](MiniGUIProgGuidePart2Chapter02.md)
   - [Renderer and Resources Management](MiniGUIProgGuidePart2Chapter03.md)
   - [Foundation Class](MiniGUIProgGuidePart2Chapter04.md)
   - [Static Box Series Control Class ](MiniGUIProgGuidePart2Chapter05.md)
   - [Button Series Control Class](MiniGUIProgGuidePart2Chapter06.md)
   - [Panel and Its Derived Class](MiniGUIProgGuidePart2Chapter07.md)
   - [Container and Its Derived Class](MiniGUIProgGuidePart2Chapter08.md)
   - [Slider Series Control Class](MiniGUIProgGuidePart2Chapter09.md)
   - [Spinner Series Control Class](MiniGUIProgGuidePart2Chapter10.md)
   - [Progress Bar Control Class](MiniGUIProgGuidePart2Chapter11.md)
   - [Property Sheet Control Class](MiniGUIProgGuidePart2Chapter12.md)
   - [Edit Box Series Control Class](MiniGUIProgGuidePart2Chapter13.md)
   - [Animation Control Class](MiniGUIProgGuidePart2Chapter14.md)
   - [Other Advanced Control Class](MiniGUIProgGuidePart2Chapter15.md)
   - [Invisible Control Class](MiniGUIProgGuidePart2Chapter16.md)
   - [Other Class](MiniGUIProgGuidePart2Chapter17.md)
- Part III: MiniGUI Graphics Programming.
  We describe the use and concepts of MiniGUI graphics related APIs in this part.
   - [Graphics Device Interfaces](MiniGUIProgGuidePart3Chapter01.md)
   - [Handling and Rendering of Text](MiniGUIProgGuidePart3Chapter02.md)
   - [Advanced GDI Functions](MiniGUIProgGuidePart3Chapter03.md)
   - [Using mGPlus for Vector Graphics](MiniGUIProgGuidePart3Chapter04.md)
- Part IV: Visual Effects and Animations.
  We describe how to program for visual effects and animations in this part.
   - [Using mGEff for Visual Effects and Animations](MiniGUIProgGuidePart4Chapter01.md)
   - [Using mGNCS4Touch](MiniGUIProgGuidePart4Chapter02.md)
   - [Integrating OpenGL ES and/or OpenVG with MiniGUI](MiniGUIProgGuidePart4Chapter03.md)
- Part V: MiniGUI Advanced Programming Topics.
  We describe the concepts of MiniGUI-Processes related advanced programming
  and the development of customizing GAL and IAL engine in this part.
   - [Inter-Process Communication and Asynchronous Event Process](MiniGUIProgGuidePart5Chapter01.md)
   - [Developing Customized MiniGUI-Processes Server Program](MiniGUIProgGuidePart5Chapter02.md)
   - [GAL and IAL Engines](MiniGUIProgGuidePart5Chapter03.md)
   - [Universal Startup API for RTOSes](MiniGUIProgGuidePart5Chapter04.md)
- Part VI: Using MiniGUI Inherent Controls.
  We describe the use of various controls provided by MiniGUI core in this part.
   - [Static Control](MiniGUIProgGuidePart6Chapter01.md)
   - [Button Control](MiniGUIProgGuidePart6Chapter02.md)
   - [List Box Control](MiniGUIProgGuidePart6Chapter03.md)
   - [Edit Box Control](MiniGUIProgGuidePart6Chapter04.md)
   - [Combo Box Control](MiniGUIProgGuidePart6Chapter05.md)
   - [Menu Button Control](MiniGUIProgGuidePart6Chapter06.md)
   - [Progress Bar Control](MiniGUIProgGuidePart6Chapter07.md)
   - [Track Bar Control](MiniGUIProgGuidePart6Chapter08.md)
   - [Toolbar Control](MiniGUIProgGuidePart6Chapter09.md)
   - [Property Sheet Control](MiniGUIProgGuidePart6Chapter10.md)
   - [Scroll Window Control](MiniGUIProgGuidePart6Chapter11.md)
   - [Scroll View Control](MiniGUIProgGuidePart6Chapter12.md)
   - [Tree View Control](MiniGUIProgGuidePart6Chapter13.md)
   - [List View Control](MiniGUIProgGuidePart6Chapter14.md)
   - [Month Calendar Control](MiniGUIProgGuidePart6Chapter15.md)
   - [Spin Box Control](MiniGUIProgGuidePart6Chapter16.md)
   - [Cool Bar Control](MiniGUIProgGuidePart6Chapter17.md)
   - [Animation Control](MiniGUIProgGuidePart6Chapter18.md)
   - [GridView Control](MiniGUIProgGuidePart6Chapter19.md)
   - [IconView Control](MiniGUIProgGuidePart6Chapter20.md)
   - [Independent Scrollbar Control](MiniGUIProgGuidePart6Chapter21.md)
- Appendix: Specifications for MiniGUI Developers.
  We provide some information for MiniGUI developers in this appendix.
   - [Code Style and Project Specification](MiniGUIProgGuideAppendixA.md)
   - [Specification for the Picture Resources Used by mGNCS Skin Renderer](MiniGUIProgGuideAppendixB.md)
   - [Specification for the mGNCS-compliant Widget Components](MiniGUIProgGuideAppendixD.md)

## Obtaining Samples of the Guide

We organize the sample programs in this guide into a complete Autoconf/Automake
project package called `mg-samples`. You can download this source tarball from
the download zone of MiniGUI website:

<http://www.minigui.com/en/download>

or fetch the source code from the public repository:

<https://github.com/VincentWei/mg-samples>

## Compiling and Running Environment of the Samples

This guide assumes that you run MiniGUI 3.2 or later on Linux operating system.
Therefore, some samples are described on the assumption that you are using Linux
and GNU GCC toolchain. However, most of the samples in this guide can run on
other operating systems.

## Copyright and Licensing

FMSoft releases the sample code (mg-samples) under Apache 2.0 license. The original
text of Apache 2.0 license can be obtained by following means:

- LICENSE file in `mg-samples` software package
- <http://www.apache.org/licenses/LICENSE-2.0.html>

----

[Table of Contents](README.md) |
[Beginning MiniGUI Programming](MiniGUIProgGuidePart1Chapter01.md) &gt;&gt;


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
