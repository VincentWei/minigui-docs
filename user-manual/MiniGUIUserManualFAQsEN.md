Appendix A Frequent Ask Questions (FAQs)
========================================

A.1 Questions Relevant to GPL Versions
--------------------------------------

Q1. Do I need to pay Feynman Software for the license fee if I use GPL
versions of MiniGUI?

A1. The GPL versions of MiniGUI are available at Feynman Software
website; you can use them freely if you use MiniGUI under GPL license.
However, the release of your applications that are based on MiniGUI GPL
versions should also complies with GPL. If you use MiniGUI to develop
commercial purpose applications, i.e., you do not want to release them
under GPL terms, you then should pay Feynman Software for the licensing
fee.

Q2. When you use MiniGUI GPL versions, what kind of behaviors would
violate Feynman Software’s legal rights?

A2. Feynman Software owns the copyright of several free software
projects. We release that software under GPL with the purpose of helping
users to understand software inner mechanism well and customize them
freely and easily. However, most users are not familiar with GPL terms;
they would sometimes act against GPL terms unconsciously. The behaviors
below would violate Feynman Software’s legal rights:

Pirate part or whole source code to use in other occasions; the worse
thing is to pirate MiniGUI and sell it as private software. Such
behavior has already seriously offended against the copyright laws.

Modify source code of free software, and use them in commercial purpose,
but they are not released according to GPL terms.

Under GPL terms, applications based-on MiniGUI should be released under
GPL. If you do not release MiniGUI applications under GPL, neither
buying MiniGUI commercial licenses, this behavior belongs to software
pirate.

A.2 Questions Relevant to MiniGUI Application Fields
----------------------------------------------------

Q3．What kinds of products that use MiniGUI are successfully launched in
market?

A3. MiniGUI is widely used in the products like mobile phones, IPTVs,
digital TVs, industry control systems, information terminals, industrial
meters, and so on. For the detailed introduction for some typical
products, you can visit:

http://www.minigui.com/en/introduction/application/

Q4. How is about the stability of MiniGUI?

A5. It is hard to answer this question as the factor that influences
system stability is sometimes due to applications instead of the
libraries. However, we can offer you some information as reference:

For a complicated MiniGUI application, a test shows that there is no
problem for the shift in between multi-windows by pressing key 100,000
times in two days.

Many industrial control systems that are developed based on MiniGUI can
now stably run under real industrial situations.

A.3 Questions Relevant to Portability
-------------------------------------

Q5. What operating systems does MiniGUI support?

A5. By now, MiniGUI provides the support for many popular embedded
operating systems including Linux/uClinux, VxWorks, ThreadX, Nucleus,
pSOS, OSE, eCos, and even uC/OS-II. MiniGUI can also run on Win32
platform.

Q6. Which CPUs have MiniGUI run on successfully so far? Moreover, what
is the lowest frequency of CPU MiniGUI needed?

A6. There are successful cases for MiniGUI running in ARM-based CPUs
(such as StongARM, xScale, S3C2410, S3C2440, EM8511, EM8620), PowerPC,
MIPS, M68k, FRV. In those CPUs, the one with lowest main frequency is
about 20 MHz (20 MIPS).

Q7. Would MiniGUI provide support for monochrome LCD?

A7. Yes. Actually, MiniGUI can provide support for almost all LCD
controllers in various modes, such as monochrome, gray, 256-color,
4096-color, and 65536-color.

Q8. Which resolution of screen can MiniGUI run properly?

A8. In theory, the running of MiniGUI is not influenced by the
resolution of screen.

A.4 Questions Relevant to Compilation
-------------------------------------

Q9. Why are there so many compilation errors when I enable the option to
support TrueType font?

A9. The main reason is that the libttf version supporting TrueType font
in your system is too high. MiniGUI uses libttf 1.3.1. In several Linux
distributions such as RedHat Linux 7, the library libttf 2.0 is
installed by the default. In this case, you can install libttf 1.3.1 or
use **--with-ttfsupport=no** option to disable the support for TrueType
font of MiniGUI.

Q10. During compiling the library, why does the mistake below occur
sometimes?

can not make hard link filename.o to filename.lo.

A10. Symbol links and hard links are the specialized file types in UNIX
file system. If you compile library being maintained by
Automake/Autoconf script, you cannot create these links on a non-UNIX
file system. Please check your file system to make sure if it is not
FAT32 file system.

Q11. When I use the Open File Dialog Box, why does the mistake below
occur?

undefined reference to ShowOpenDialog

A11. The function ShowOpenDialog is included in the mGUtils component.
If you want to use this function, you should include two header files:
&lt;**mgutils/mgutils.h**&gt;. When make the executable, please make
sure to link mGUtils(**-lmgutils**). In addition, if you run MiniGUI on
some embedded operating systems, which are lack of the support for file
system, you can’t use the Open File Dialog Box.

Q12. My system does not support 64-bit integer. Is the data type of
Uint64 in MiniGUI essential?

A12. The data type of Uint64 in MiniGUI is used to generate the complex
graphics. If your system does not support 64-bit integer, you can use
the following configuration option to disable the usage of 64-bit
integer:

--disable-fixedmath

A.5 Questions Relevant to Input Engines
---------------------------------------

Q13. On Linux PC boxes, what kinds of mouse types does MiniGUI support?

A13. Currently, the mouse protocols supported by MiniGUI are MS, MS3,
PS2, and Intelligent PS2 (IMPS2).

Q14. On Linux PC boxes, I would like to use the old serials mouse. What
should I do?

A14. MiniGUI can provide support for almost all mouse types via GPM.
Please configure it as follows:

Run **gpm –k** to kill gpm that is running.

Run **mouse-test** to confirm your mouse device and protocol.

Run **gpm** to set mouse device and protocol as follows.

gpm -R -t &lt;yourmousetype&gt; -m &lt;yourmousedevice&gt;

Edit **MiniGUI.cfg** file, set **mtype** as **gpm**; and set mdev as
**/dev/gpmdata**:

\[system\]

...

mtype=gpm

mdev=/dev/gpmdata

Then, start up MiniGUI. Please note you can use the option **–R** when
you set the mouse protocol by **gpm**. **–R** option is used to transfer
original mouse protocol to GPM defined mouse protocol, and make it shown
in **/dev/gpmdata** file.

A.6 Runtime Questions
---------------------

Q15. On Linux, How would I capture the screen of MiniGUI?

A15. When running MiniGUI program, you can capture the screen as a BMP
file in the current directory by pressing **&lt;PrtSc&gt;** key. The
file name is **0-&lt;NO&gt;.bmp**, therein **&lt;NO&gt;** is the number
of times of pressing **&lt;PrtSc&gt;** key. You can save the BMP file of
the current active main window as **&lt;HWND&gt;-&lt;NO&gt;.bmp**,
therein **&lt;HWND&gt;** is the handle of the active main window while
**&lt;NO&gt;** is the number of times of pressing **&lt;Ctrl+PrtSc&gt;**
key.

Q16. Why does the program exit after displaying two dialog boxes when I
run **mginit** in Mg-samples?

A16. The main reason is that MiniGUI being installed does not provide
support for PNG image files. In some Linux distributions (such as early
TurboLinux), as the version of their PNG graphics support library
(libpng) is too old, it would automatically disable the support for PNG
image when you configure MiniGUI. In this case, **LoadBitmapFromFile**
function of MiniGUI cannot correctly load PNG image files, while
Mg-samples **mginit** needs to load two PNG files for running. That is
why **mginit** exits.

To solve this problem, there are two ways. First, you can download and
install the latest libpng library from INTERNET. Secondly, modify **nr**
value in section **\[mginit\]** in **mginit.rc**, and make the value
less than 8.

Another reason that may cause such error is that you do not start up
**mginit** in its directory. Please change to the directory, then run
**mginit**.

Q17. Under MiniGUI-Processes runtime mode, how would I switch from
MiniGUI to other console?

A17. Under MiniGUI-Processes runtime mode, if you are using the
**console** input engine, you can switch from MiniGUI to other virtual
console by pressing **&lt;Right\_Ctrl+F*x*&gt;** key, also, you can quit
MiniGUI by pressing **&lt;Ctrl+Alt+Backspace&gt;**. Currently,
MiniGUI-Threads does not provide such functions.

A.7 Common Error Messages
-------------------------

Q18. Why is the following message shown when I run programs in
mg-samples on Linux?

AttachSharedResource: No such file or directory

Error in step 6: Can not attach shared resource!

Initialize minigui failure when using /etc/MiniGUI.cfg as cfg file.

A18. If you configure MiniGUI as MiniGUI-Processes or
MiniGUI-Standalone, you should run **mginit** program first. As
MiniGUI-Processes or MiniGUI-Standalone adopts a C/S architecture, you
have to start up the sever program, **mginit,** before running client
programs. In Mg-samples package, you should run **mginit** in
**mginit/** directory first, then run demo programs in other
directories.

Q19. Why do I see the information below when I run MiniGUI?

GAL ENGINE: Error when opening /dev/fb0: Permission denied. Please check
your kernel config.

GAL: Init GAL engine failure.

Error in step 3: Can not initialize graphics engine!

Initialize minigui failure when using /usr/local/etc/MiniGUI.cfg as cfg
file

A19. The main reason is that you have not activated the FrameBuffer
driver yet, or the permission of **/dev/fb0** is incorrect.

Q20. Under MiniGUI-Processes runtime mode, why does it give error
information below when I run mginit in mg-samples?

Error in step 2 : There is already an instance of minigui.

Initialize minigui failure when using /usr/local/etc/MiniGUI.cfg as
config file.

A20. Usually, there are two possible reasons. One is that you have
already run an **mginit** program; other is that you did not exit
MiniGUI properly when you run **mginit** last time. If it is the second
reason, you can delete **minigui** file and **mginit** file in
**/var/tmp/** directory. If it still does not work, please restart your
computer.

Q21. Why do the following statement show when I run MiniGUI?

NEWGAL: Does not find matched engine: fbcon.

Error in step 3: Can not get graphics engine information!

A21. The possible problem is that **FBCON** engine in NEWGAL interface
fails when initializing FrameBuffer device. The main reasons are that
your kernel does not support FrameBuffer driver, or does not activate
FrameBuffer driver, or you have no proper access permission to open
**/dev/fb0** device.

Q22．On Linux, what is the meaning of the error information below?

vesafb does not support changing the video mode

A22. It is a warning that can be ignored. It aims at VESA FrameBuffer
driver. VESA FrameBuffer driver does not support the display mode switch
during running. It can only set video mode by the boot option for
kernel. Moreover, once set, it cannot be changed unless you modify the
boot option and restart your system.

Q23. On Linux, what is the meaning of the error information below?

NEWGAL: No video mode large enough for the resolution specified.

NewGAL: Set video mode failure.

A23. The main reason is that the display resolution being set in
**MiniGUI.cfg** is higher than that supported by your FrameBuffer
driver. Therefore, you can try to set a smaller resolution by modify
**MiniGUI.cfg** file.

----

[&lt;&lt;Feature List](MiniGUIUserManualFeatureList.md) |
[Table of Contents](README.md) |
[常见问题 &gt;&gt;](MiniGUIUserManualFAQsZH.md)

[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[MiniGUI Official Website]: http://www.minigui.com
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[Quick Start]: MiniGUIUserManualQuickStart.md
[Building MiniGUI]: MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]: MiniGUIUserManualCompiletimeConfiguration.md
[Runtime Configuration]: MiniGUIUserManualRuntimeConfiguration.md
[Tools]: MiniGUIUserManualTools.md
[Feature List]: MiniGUIUserManualFeatureList.md
[FAQs]: MiniGUIUserManualFAQsEN.md
