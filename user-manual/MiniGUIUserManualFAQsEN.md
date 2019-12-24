# Frequent Ask Questions (FAQs)

Q) Do I need to pay FMSoft Technologies license fee if I use MiniGUI?

A) FMSoft releases MiniGUI under GPL; you can use them freely if
you use MiniGUI under GPL license to develop GPL'd applications.
However, the release of your applications that are based on MiniGUI
should also complies with GPL. If you use MiniGUI to develop
commercial applications, i.e., you do not want to release them
under terms and conditions of GPL, you then should get a commercial
license from [FMSoft Technologies].

Q) What kinds of products that use MiniGUI are successfully launched in
market?

A) MiniGUI is widely used in products like mobile phones, IPTVs,
digital TVs, industry control systems, information terminals, industrial
meters, and so on. For detailed introduction for some typical
products, you can visit:
<http://www.minigui.com/case-studies>.

Q) Which operating systems does MiniGUI support?

A) By now, MiniGUI provides support for many popular embedded
operating systems including Linux/uClinux, VxWorks, ThreadX, FreeRTOS,
RTEMS, RT-Thread, Nucleus, pSOS, OSE, eCos, and even uC/OS-II.
MiniGUI can also run on Win32 platform.

Q) Which CPUs have MiniGUI running on successfully so far? Moreover, what
is the lowest frequency of CPU that MiniGUI needs?

A) There are successful cases for MiniGUI running on ARM-based CPUs
(such as StongARM, xScale, S3C2410, S3C2440, EM8511, EM8620), PowerPC,
MIPS, M68k, FRV. On these CPUs, the one with lowest main frequency is
about 20 MHz (20 MIPS).

Q) Would MiniGUI support monochrome LCD?

A) Yes. Actually, MiniGUI can support almost all LCD
controllers in various modes, such as monochrome, gray, 256-color,
4096-color, and 65536-color.

Q) Which resolution of screen can MiniGUI run properly?

A) In theory, the running of MiniGUI is not influenced by the
resolution of screen.

Q) During library compilation, why does the mistake below occur
sometimes?

    can not make hard link filename.o to filename.lo.

A) Symbol links and hard links are the specialized file types in UNIX
file system. If you compile library maintained by
Automake/Autoconf script, you cannot create these links on a non-UNIX
file system. Please check your file system to make sure if it is a
FAT32 file system.

Q) When I use Open File Dialog Box, why does the mistake below
occur?

    undefined reference to ShowOpenDialog

A) The function `ShowOpenDialog` is included in the mGUtils component.
If you need to use this function, you should include the header file:
`<mgutils/mgutils.h>`. When you make the executable, please make
sure to link mGUtils(`-lmgutils`). In addition, if you run MiniGUI on
some embedded operating systems, which lacks support for file
system, you can't use the Open File Dialog Box.

Q) My system does not support 64-bit integer. Is the data type of
`Uint64` in MiniGUI essential?

A) The data type of `Uint64` in MiniGUI is used to generate complex
graphics. If your system does not support 64-bit integer, you can use
the following configuration option to disable the usage of 64-bit
integer:

    --disable-fixedmath

Q) On Linux, How do I capture the screen of MiniGUI?

A) When running MiniGUI program, you can capture the screen to a BMP
file in the current directory by pressing `PrtScr` key. The
captured screen will be saved as a BMP file named `0-<NO>.bmp`,
therein `<NO>` is the number of times of pressing `Ctrl + PrtScr` key.
You can save the BMP file of the current active main window as `<HWND>-<NO>.bmp`,
therein `<HWND>` is the handle of the active main window while
`<NO>` is the number of times of pressing `Ctrl + PrtScr` key.

Q) Under MiniGUI-Processes runtime mode, how would I switch from
MiniGUI to other console?

A) Under MiniGUI-Processes runtime mode, if you are using
`console` or `libinput` IAL engine, you can switch from MiniGUI to
other virtual console by pressing `Right_Ctrl + F<n>` key, also,
you can quit MiniGUI by pressing `Ctrl + Alt + Backspace` key.
Currently, MiniGUI-Threads mode does not provide such functions.

Q) Why does the following message show when I run programs in
mg-samples on Linux?

    AttachSharedResource: No such file or directory
    Error in step 6: Can not attach shared resource!
    Initialize minigui failure when using /etc/MiniGUI.cfg as cfg file.

A) If you configure MiniGUI as MiniGUI-Processes or
MiniGUI-Standalone, you should run `mginit` program first. As
MiniGUI-Processes mode adopts a Client/Server architecture, you
have to first start up the sever program, `mginit`, before running other client
programs. In mg-samples package, you should run `mginit` in
`mginit/` directory first, then run demo programs in other
directories.

Q) Why do I see the information below when I run MiniGUI?

    GAL ENGINE: Error when opening /dev/fb0: Permission denied. Please check your kernel config.
    GAL: Init GAL engine failure.
    Error in step 3: Can not initialize graphics engine!
    Initialize minigui failure when using /usr/local/etc/MiniGUI.cfg as cfg file

A) The main reason is that you have not activated the frame buffer
driver yet, or the permission of `/dev/fb0` is incorrect.

Q) Under MiniGUI-Processes runtime mode, why does it give error
information below when I run `mginit` in mg-samples?

    Error in step 2 : There is already an instance of minigui.
    Initialize minigui failure when using /usr/local/etc/MiniGUI.cfg as config file.

A) Usually, there are two possible reasons. One is that you have
already run an `mginit` program; the other is you did not exit
MiniGUI properly when you run `mginit` last time. If it is the second
reason, you can delete `minigui` file and `mginit` file in
`/var/tmp/` directory. If it still does not work, please restart your
computer.

Q) Why do the following statements show when I run MiniGUI?

    NEWGAL: Does not find matched engine: fbcon.
    Error in step 3: Can not get graphics engine information!

A) The possible problem is that `fbcon` NEWGAL engine
fails when initializing frame buffer device. The main reasons are that
your kernel does not support frame buffer driver, or does not activate
frame buffer driver, or you have no proper access permission to open
`/dev/fb0` device.

Q) On Linux, what is the meaning of the error message below?

    vesafb does not support changing the video mode

A) It is a warning that can be ignored. The VESA frame buffer driver
does not support display mode switching
while running. It can only set video mode by the boot option for
kernel. Moreover, once set, it cannot be changed unless you modify the
boot option and restart your system.

Q) On Linux, what is the meaning of the error message below?

    NEWGAL: No video mode large enough for the resolution specified.
    NewGAL: Set video mode failure.

A) The main reason is that the display resolution being set in
`MiniGUI.cfg` is higher than the one supported by your NEWGAL engine.
Therefore, you can try to set a lower resolution by modify
`MiniGUI.cfg` file.

----

[&lt;&lt; Feature List](MiniGUIUserManualFeatureList.md) |
[Table of Contents](README.md) |
[常见问题 &gt;&gt;](MiniGUIUserManualFAQsZH.md)

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
[Writing DRM Engine Driver for Your GPU]: /supplementary-docs/Writing-DRM-Engine-Driver-for-Your-GPU.md
[Writing MiniGUI Apps for 64-bit Platforms]: /supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md

[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
