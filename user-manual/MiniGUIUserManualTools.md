4 Developing MiniGUI Application in Windows
===========================================

Feynman provides two methods for developer, which is accustomed to
develop application in Window platform.

Using the package of MiniGUI for Win32. It is pre-compiled standard
development package in Win32. It contains wvfb, MiniGUI function library
(libminigui and libmgext) and header files.

Using MiniGUI SDK for Win32. This is an optional component in MiniGUI.
It contains the whole source codes and provides users the convenience
for customizing the package of MiniGUI for Win32.

By using the package of MiniGUI for Win32 or the component product of
MiniGUI SDK for Win32, developer can compile and debug MiniGUI
application in Windows.

This chapter describes how to use the package of MiniGUI for Win32. User
can contact Feynman to purchase the component product of MiniGUI SDK for
Win32.

To develop MiniGUI application in Windows, you must install MS Visual
Studio 98. First, you decompress arbitrary directory in windows.
Secondly you open the helloworld project file in VC according to README.
Figure 4.1 shows it.

After compiling successfully, you should run wvfb first and run
helloworld. Note that you need copy **helloworld.ext** to directory dll.
Fig 4.2 shows running result.

![](media/image3.png){width="2.830917541557305in"
height="2.004750656167979in"}\
Fig 4.1 open MiniGUI helloworld project

![](media/image4.png){width="3.272584208223972in"
height="2.7902088801399825in"}\
Fig 4.2 Compiling and Running MiniGUI Application in Windows

Refer to above helloworld, you can create, develop and compile new
MiniGUI application in VC. But give your attention to the following:

Because the package of MiniGUI for Win32 is pre-compiled library, the
function, compiling configuration options, and running configuration
options are fixed, and only support MiniGUI-Threads runtime mode.

Using the package of MiniGUI for Win32 to develop applications, please
don’t call Windows special API, which isn’t supported possibility by
target OS.

---

[&lt;&lt; Runtime Configuration](MiniGUIUserManualRuntimeConfiguration.md) |
[Table of Contents](README.md) |
[Feature List &gt;&gt;](MiniGUIUserManualFeatureList.md)

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building MiniGUI]: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]: /user-manual/MiniGUIUserManualCompiletimeConfiguration.md
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md
[FAQs]: /user-manual/MiniGUIUserManualFAQsEN.md
[常见问题]: /user-manual/MiniGUIUserManualFAQsZH.md

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

[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
