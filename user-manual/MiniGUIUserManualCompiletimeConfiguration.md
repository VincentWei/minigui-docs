# Compile-time Configuration

- [Configuration Options and Macros](#configuration-options-and-macros)
   * [Operating System](#operating-system)
   * [Target Board](#target-board)
   * [Runtime Mode](#runtime-mode)
   * [Graphics Engine](#graphics-engine)
   * [Input Engine](#input-engine)
   * [Keyboard Layout](#keyboard-layout)
   * [Global Options and Macros](#global-options-and-macros)
   * [Character Set and Font](#character-set-and-font)
   * [Image File Format](#image-file-format)
   * [Appearance Renderer](#appearance-renderer)
   * [Control](#control)
   * [Others](#others)
- [Minimal Configuration Options](#minimal-configuration-options)
- [Changes in Version 4.0](#changes-in-version-40)

## Configuration Options and Macros

In this chapter, we will give detailed description on most important
compile-time configuration options of MiniGUI. MiniGUI has many
such options; you can combine these options to generate your own
MiniGUI library.

### Operating System

MiniGUI provides support for multiple operating systems, you can specify
operating system when execute configuration script, the default operating
system is Linux. If you want to run MiniGUI on eCos, you can execute command
as the follow:

```
user$ ./configure --with-osname=ecos
```

If you specify an operating system, some macros will be defined
in `mgconfig.h`. For some operating systems, the configuration script
will also enable other macros. The following table lists the options and
macros about operating systems.

##### Table: Options and macros for different operation systems

| Configuration options    | Macro                | Other macros         | Comments
| -------------------------|----------------------|----------------------|-------------------------------------------
| `--with-osname=linux`    | `__LINUX__`          |                      | For Linux operating system; Default value
| `--with-osname=uclinux`  | `__uClinux__`        |                      | For uClinux operating system
| `--with-osname=ucos2`    | `__UCOSII__`         | `__NOUNIX__`<BR/>`_MGINCORE_RES`<BR/>`_MGUSE_OWN_MALLOC`<BR/>`_MGUSE_OWN_STDIO`<BR/>`_MGUSE_OWN_PTHREAD` | For uC/OS-II operating system
| `--with-osname=vxworks`  | `__VXWORKS__`        | `__NOUNIX__`<BR/>`_MGUSE_OWN_STDIO`<BR/>`_MGUSE_OWN_PTHREAD` | For VxWorks operating system
| `--with-osname=ecos`     | `__ECOS__`           | `__NOUNIX__`         | For eCos operating system
| `--with-osname=threadx`  | `__THREADX__`        | `__NOUNIX__`<BR/>`_MGINCORE_RES`<BR/>`_MGUSE_OWN_MALLOC`<BR/>`_MGUSE_OWN_STDIO`<BR/>`_MGUSE_OWN_PTHREAD` | For ThreadX operating system
| `--with-osname=nucleus`  | `__NUCLEUS__`        | `__NOUNIX__`<BR/>`_MGINCORE_RES`<BR/>`_MGUSE_OWN_MALLOC`<BR/>`_MGUSE_OWN_STDIO`<BR/>`_MGUSE_OWN_PTHREAD` | For Nucleus operating system |
| `--with-osname=ose`      | `__OSE__`            | `__NOUNIX__`<BR/>`_MGINCORE_RES`<BR/>`_MGUSE_OWN_PTHREAD` | For OSE operating system
| `--with-osname=psos`     | `__PSOS__`           | `__NOUNIX__`<BR/>`_MGINCORE_RES`<BR/>`_MGUSE_OWN_PTHREAD` | For pSOS operating system
| `--with-osname=rtthread` | `__RTTHREAD__`       | `__NOUNIX__`         | For RT-Thread operating system; Since MiniGUI 4.0.2
| `--with-osname=rtems`    | `__RTEMS__`          | `__NOUNIX__`         | For RTEMS operating system; Since MiniGUI 4.0.2
| `--with-osname=freertos` | `__FREERTOS__`       | `__NOUNIX__`         | For FreeRTOS operating system; Since MiniGUI 4.0.2
| `--with-osname=cygwin`   | `__CYGWIN__`         | `__NOUNIX__`         | For Cygwin environment
| `--with-osname=win32`    | `WIN32`              | `__NOUNIX__`         | For Windows platform
| `--with-osname=darwin`   | `__DARWIN__`         | `__NOUNIX__`         | For MacOS X operating system
| `--with-osname=swlinux`  | `__WINBOND_SWLINUX__`|                      | Deprecated; for SWLinux operating system

### Target Board

In MiniGUI core, some code are related with a special target board,
especially when you use `Shadow` NEWGAL engine or `CommLCD` NEWGAL
engine for certain operating systems. In other words, when you use
these two engines, the configuration script will determine which sub-drivers
will be contained in MiniGUI core by using a configuration option.

You can use `--with-targetname` option to define the name for your
target board, especially when you use a real-time operating system.

The default target board name is `unknown`. We recommend to define a
target board name when you port MiniGUI to a new target system for a
traditional real-time operating system, such as uC/OS-II, eCos, ThreadX,
or others.

Since MiniGUI 3.2.2, we introduce a new target name `external`.
When you use `CommLCD` NEWGAL engine or `Comm` IAL engine to support
your target board, you can define the target name as `external`.
By using the target name, you do not need to change the source code
of MiniGUI core. Instead, you implement the engines outside the MiniGUI
core by defining some external functions.

Since MiniGUI 4.0.0, the NEWGAL engine `dri` for Linux also support
the target name `external`. So you can implement the sub-driver of
`dri` engine outsize MiniGUI core.

For more information, please refer to:

- [Using CommLCD NEWGAL Engine and Comm IAL Engine](https://github.com/VincentWei/minigui/wiki/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine)
- [Writing DRI Engine Driver for Your GPU](https://github.com/VincentWei/minigui/wiki/Writing-DRI-Engine-Driver-for-Your-GPU)

The table lists the options and macros related to various target boards.

##### Table: Options and macros for target board

| Configuration options         | Macro                    | Comments
|-------------------------------|--------------------------|----------------------------------------------------------
| `--with-targetname=unknown`   | `__TARGET_UNKNOWN__`     | Unknown development board: default value
| `--with-targetname=external`  | `__TARGET_EXTERNAL__`    | Define this target name when you want to use NEWGAL and/or IAL engine which is implemented outside MiniGUI core.
| `--with-targetname=fmsoft`    | `__TARGET_FMSOFT__`      | Only for FMSoft's internal use
| `--with-targetname=mstudio`   | `__TARGET_MSTUDIO__`     | Only for miniStudio
| `--with-targetname=stb810`    | `__TARGET_STB810__`      | Philips STB810 development board base on Linux
| `--with-targetname=vfanvil`   | `__TARGET_VFANVIL__`     | VisualFone development board base on ThreadX
| `--with-targetname=vxi386`    | `__TARGET_VXI386__`      | i386 target base on VxWorks
| `--with-targetname=qvfb`      | `__TARGET_QVFB__`        | Include qvfb sub-driver of Shadow engine base on Linux
| `--with-targetname=wvfb`      | `__TARGET_WVFB__`        | Include wvfb sub-driver of Shadow engine base on Windows
| `--with-targetname=fbcon`     | `__TARGET_FBCON__`       | Include fbcon sub-driver of Shadow engine base on Linux
| `--with-targetname=mx21`      | `__TARGET_MX21__`        | MX21 development board base on OSE
| `--with-targetname=c33l05`    | `__TARGET_C33L05__`      | Epson C33L05 development board base on axLinux
| `--with-targetname=bfin`      | `__TARGET_BLACKFIN__`    | BlackFin537 development board base on uClinux
| `--with-targetname=vxppc`     | `__TARGET_PPC__`         | PowerPC target base on VxWorks
| `--with-targetname=monaco`    | `__TARGET_MONACO__`      | Monaco development board base on Nucleus

### Runtime Mode

We can configure MiniGUI as one of three kind of runtime mode:

- MiniGUI-Processes runtime mode base on multi-processes;
- MiniGUI-Threads runtime mode base on multi-thread;
- MiniGUI-Standalone runtime mode based on a single task architecture.

MiniGUI-Processes is the default mode for Linux operating system,
while MiniGUI-Threads is the default mode for other operating systems.

The following table lists the options and macros for runtime mode.

##### Table: Options and macros for runtime mode

| Configuration options   | Macro              | Comments
|-------------------------|--------------------|--------------------------------------------------------------------------------------
| `--with-runmode=procs`  | `_MGRM_PROCESSES`  | MiniGUI-Processes runtime mode, support Linux operating system only; Default for Linux
| `--with-runmode=ths`    | `_MGRM_THREADS`    | MiniGUI-Threads runtime mode, support all operating system; Default for operating systems other than Linux
| `--with-runmode=sa`     | `_MGRM_STANDALONE` | MiniGUI-Standalone runtime mode, support all operating system

### Graphics Engine

MiniGUI supports many kinds of graphics engine. The commonly used
graphics engine mainly includes the Dummy graphics engine, Qt Virtual
FrameBuffer engine, Linux FrameBuffer console graphics engine, the
COMMLCD graphics engine, the Shadow graphics engine, Windows Virtual
FrameBuffer graphics engine and so on. Through the configuration option
or macro, we may contain a certain graphics engine to MiniGUI. But if
you assign MiniGUI to use a certain graphics engine, then you need to
assign a special runtime configuration option. For instance, if you
assign MiniGUI to use the dummy graphics engine, you may assign the
runtime configuration option **gal\_engine=dummy** in \[**system**\]
section, the graphics engine name is on the right of the equal sign. The
attention, the engine name is case sensitivity. About how to revises the
runtime configuration option, please refer the 3rd chapter of *MiniGUI
Runtime Configuration Options* this handbook. The table 2.5 lists the
graphics engine related options, macros and the name.

Table 2.5 graphics engine related options and macros

  Configuration options   Macro              Engine name   Memo                                                                                                                         Default
  ----------------------- ------------------ ------------- ---------------------------------------------------------------------------------------------------------------------------- ----------
  videodummy              \_MGGAL\_DUMMY     dummy         All operating system                                                                                                         Enabled
  videofbcon              \_MGGAL\_FBCON     fbcon         Linux/uClinux                                                                                                                Enabled
  videoqvfb               \_MGGAL\_QVFB      qvfb          Linux                                                                                                                        Enabled
  videowvfb               \_MGGAL\_WVFB      wvfb          Win32；virtual buffer graphics engine，use Win32 。                                                                          Disabled
  videowvfb               \_MGGAL\_PCXVFB    pc\_xvfb      Linux/Win32 Suitable for the PC's virtual buffer graphics engine, does not depend on the specific implementation platform.   Disabled
  videocommlcd            \_MGGAL\_COMMLCD   commlcd       All operating system                                                                                                         Disabled
  videoshadow             \_MGGAL\_SHADOW    shadow        All operating system, MiniGUI-Threads, MiniGUI-Standalone runtime mode                                                       Disabled
  videodfb                \_MGGAL\_DFB       dfb           Run MiniGUI on DirectFB, Linux                                                                                               Disabled

The Dummy is a graphics engine ("mute" graphics engine), which it does
not make any actual output. Therefore, if the graphics engine for your
development board still cannot work, you can run MiniGUI using this
graphics engine.

The Qvfb graphics engine uses in the Linux operating system. Using qvfb,
we can run the MiniGUI program in X Window; it may greatly facilitate
the application debugging. Similar with the qvfb graphics engine, when
uses MiniGUI SDK for Win32 run MiniGUI program on Win32 platform, it run
on Windows Virtual in the FrameBuffer actually, and use the wvfb
graphics engine.

It should be noted that the original QVFB (Qt Virtual Frame Buffer) and
WVFB (Windows Virtual Frame Buffer) have been replaced with the newly
designed XVFB general purpose virtual buffer graphics engine in MiniGUI
3.0.

In MiniGUI also has a special Shadow graphics engine, uses the Shadow
graphics engine, MiniGUI may support the graphic display devices which
it is lower than 8 bit colors, also support the screen rotation. The
Shadow graphics engine has used the sub-driver concept; it determined
which sub-driver contains through the target board name. Only one
sub-driver can be contained at one time, it determined by the target
board configuration option (sees section 2.2.2). The attention, the
Shadow graphics engine is disabled as the default; moreover it is only
suitable for the MiniGUI-Threads and MiniGUI-Standalone runtime mode at
present.

The sub-drivers of the Shadow graphics in MiniGUI are (in MiniGUI source
code directory **src/newgal/shadow**):

**unknown**: the default sub-driver, similar with the dummy graphics
engine, user may modify this sub-driver in order to operate and visit
the low graphics devices.

**qvfb**: sub-driver for Linux QVFB all display mode, support low than
8-bit color display mode and screen rotation.

**fbcon**: sub-driver for Linux console FrameBuffer, support low than
8-bit color display mode and screen rotation.

**wvfb**: sub-driver for Windows Virtual FrameBuffer(wvfb), support low
than 8-bit color display mode and screen rotation.

We can rotate the screen by Shadow engine. Table 2.6 lists the screen
rotation related options and macros.

Table 2.6 screen rotation related options and macros

  Configuration options   Macro           Macro value      Comment   Default
  ----------------------- --------------- ---------------- --------- ----------------------------- ----------
  coortrans\_cw           \_COOR\_TRANS   \_ROT\_DIR\_CW   1         Rotate screen clockwise       Disabled
  coortrans\_ccw                          \_ROT\_DIR\_CW   0         Rotate screen anticlockwise   Disabled

The CommLCD graphics engine is the most used graphics engine when
MiniGUI run on the tradition embedded operating system. CommLCD also
uses the sub-driver structure like Shadow graphics engine. At present,
sub-drivers for CommLCD graphics engine are:

**vxi386**: Sub-driver for VxWorks i386 target board.

**unknown**: If is eCos operating system, then use standard interface of
eCos to implement a sub-driver. Otherwise, the sub-driver needs to be
defined by the user. The rtos/ directory of the MiniGUI source tree
contains the CommLCD graphics engine implementation for each operating
system. You can modify this file to support your own LCD controller.

### Input Engine

MiniGUI provides some input engine, which can be used directly for many
kinds of development board. Generally the input engines include the
Dummy input engine, Qt Virtual FrameBuffer engine, Linux FrameBuffer
console input engine, the COMM input engine, the Random input engine,
Windows Virtual FrameBuffer input engine and so on. Through the
configuration options or macros, we can contain an input engine to
MiniGUI. But if assign MiniGUI to use a certain input engine, then you
need to assign a special runtime configuration option. For instance, If
you assign MiniGUI to use the dummy input engine, you may assign the
runtime configuration option **ial\_engine=dummy** in \[**system**\]
section, the input engine name is on the right of the equal sign. The
attention, the engine name is case sensitivity. About how to revises the
runtime configuration option, please refer the 3rd chapter of *MiniGUI
Runtime Configuration Options* this handbook. The table 2.7 lists the
input engine related options and macros.

Table 2.7 input engines related options and macros

  Configuration options   Macro              Engine name   Comment                                                                            Default
  ----------------------- ------------------ ------------- ---------------------------------------------------------------------------------- ----------
  dummyial                \_MGIAL\_DUMMY     dummy         Dummy input engine, for all operating system                                       Enabled
  autoial                 \_MGIAL\_AUTO      auto          Automatic input engine, for all operating system                                   Disabled
  qvfbial                 \_MGIAL\_QVFB      qvfb          QVFB input engine, Linux, use QVFB graphics engine                                 Enabled
  consoleial              \_MGIAL\_CONSOLE   console       Linux console input engine, Linux                                                  Enabled
  randomial               \_MGIAL\_RANDOM    random        Random input engine, for all operating system                                      Disabled
  wvfbial                 \_MGIAL\_WVFB      wvfb          WVFB input engine, Win32, use WVFB graphics engine                                 Disabled
  commial                 \_MGIAL\_COMM      comm          COMM input engine, for all operating system                                        Disabled
  dfbial                  \_MGIAL\_DFB       dfb           Base on DirectFBinput engine, Linux, use DFB graphics engine                       Disabled
  tslibial                \_MGIAL\_TSLIB     tslib         Base on tab engine, Linux, use DFB graphics engine                                 Disabled
  qemuial                 \_MGIAL\_QEMU      qemu          QEMU input IAL, Linux.                                                             Disabled
  custodial               \_MGIAL\_CUSTOM    custom        Use on graphics engine that custom by MiniGUI application; any operating system.   Disabled

The Dummy input engine ("mute" input engine) is not connected to any
actual input device; therefore it can’t get any input. Therefore, if the
input engine for your development board still cannot to work, you can
run MiniGUI using this input engine. Attention, MiniGUI use Dummy input
engine when it cannot find the matched input engine in configuration
options.

Like the Dummy input engine, MiniGUI provide other two input engine,
which it is not associated to any device, for instance Auto input engine
and Random input engine. The Auto engine may circulation produce the
events automatic according the previous setting; But the Random input
engine produce the random input event. These two engines may use for
MiniGUI and its application software test automation.

The Console input engine aims at the PC console of Linux operating
system. This input engine supports the standard PC keyboard as well as
many kinds of mouse protocol. You need configure mtype and mdev field in
\[**system**\] section assign the mouse protocol and the mouse device
when use the console input engine.

Mouse protocol related options and macros, which console input engine
supported, are listed in table 2.8. Attention, although MiniGUI support
intelligence mouse, but MiniGUI does not support in the middle key and
the hoop input event.

Table 2.8 Mouse protocol related options and macros

  configuration options   Macro                Comment                                       Default
  ----------------------- -------------------- --------------------------------------------- ---------
  consoleps2              \_MGCONSOLE\_PS2     Support PS2 mouse protocol                    Enabled
  consoleimps2            \_MGCONSOLE\_IMPS2   Support intelligence mouse(IMPS/2) protocol   Enabled
  consolems               \_MGCONSOLE\_MS      Support old MS serial-port mouse              Enabled
  consolems3              \_MGCONSOLE\_MS3     Support MS3 mouse protocol                    Enabled
  consolegpm              \_MGCONSOLE\_GPM     Support GPM Daemon processes                  Enabled

Except the options above, MiniGUI has also provided mouse and touch
screen adjustment interfaces for applications. If you want to use this
interfaces, you need to open the option about touch screen adjusts. The
table 2.9 lists touch screen adjustment related options and macros.

Table 2.9 mouse and touch screen adjustment related options and macros

  configuration options   Macro                      Comment                           Default
  ----------------------- -------------------------- --------------------------------- ---------
  mousecalibrate          \_MGHAVE\_MOUSECALIBRATE   Support touch screen adjustment   Enabled

### Keyboard Layout

The MiniGUI keyboard layout uses for control the behavior of function
TranslateMessage. Different keyboard layout will translate a same key as
a different character (distinguish by the scan code). This translation
process is implemented through query the scan code mapping table. At
present, in MiniGUI contains the Western Europe country commonly used
keyboard layout support, standard American 1.01/102 keyboard as default.
If you want to use different keyboard layout in your program, you should
call the function SetKeyboardLayout by the keyboard layout name. For
more information, please refer *MiniGUI Programming Guide V3.0-5*. Table
2.10 listed the keyboard layout related options, macros and the name.

Table 2.10 keyboard layout related options and macros

  configuration options   Macro                     Keyboard layout name   Comment                                                    Default
  ----------------------- ------------------------- ---------------------- ---------------------------------------------------------- ----------
  Kbdfrpc                 \_MGKBDLAYOUT\_FRPC       frpc                   Keyboard layout for French PC keyboard (non-US 102 keys)   Disabled
  Kbdfr                   \_MGKBDLAYOUT\_FR         fr                     Keyboard layout for French                                 Disabled
  Kbdde                   \_MGKBDLAYOUT\_DE         de                     Keyboard layout for German                                 Disabled
  kbddelatin1             \_MGKBDLAYOUT\_DELATIN1   delatin1               Keyboard layout for German Latin1                          Disabled
  Kbdit                   \_MGKBDLAYOUT\_IT         it                     Keyboard layout for Italian                                Disabled
  Kbdes                   \_MGKBDLAYOUT\_ES         es                     Keyboard layout for Spanish                                Disabled
  kbdescp850              \_MGKBDLAYOUT\_ESCP850    escp850                Keyboard layout for Spanish CP850                          Disabled
  kbdhebrewpc             \_MGKBDLAYOUT\_HEBREWPC   hebrewpc               Keyboard layout for Hebrew PC keyboard                     Disabled
  kbdarabicpc             \_MGKBDLAYOUT\_ARABICPC   arabicpc               Keyboard layout for Arabic PC keyboard                     Disabled

### Global Options and Macros

The table 2.11 lists system global configuration options and macros.

Table 2.11 system global configuration options and macros

  configuration options   Macro                       Comment                                  Default
  ----------------------- --------------------------- ---------------------------------------- ----------
  incoreres               \_MGINCORE\_RES             Use MiniGUI in-core resource             Disabled
  miniguientry            \_USE\_MINIGUIENTRY         Use MiniGUI minigui\_entry function      Disabled
  debug                   \_DEBUG                     Include debug information                Disabled
  tracemsg                \_MGHAVE\_TRACE\_MSG        Trace MiniGUI message                    Disabled
  msgstr                  \_MGHAVE\_MSG\_STRING       Include the string name of the message   Disabled
  dblclk                  \_MGMISC\_DOUBLE\_CLICK     Support mouse double click               Enabled
  cursor                  \_MGHAVE\_CURSOR            Support mouse cursor                     Enabled
  clipboard               \_MGHAVE\_CLIPBOARD         Support clipboard                        Enabled
  savebitmap              \_MGMISC\_SAVESCREEN        Support SaveBitmap related functions     Enabled
  aboutdlg                \_MGHAVE\_FIXED\_MATH       Include About dialog box                 Enabled
  savescreen              \_MGHAVE\_SAVESCREN         Support screen capture                   Enabled
  splash                  \_MG\_ENABLE\_SPLASH        MiniGUI Splash screen                    Enabled
  fixedmath               \_MGHAVE\_FIXED\_MATH       Use fixed math functions                 Enabled
  adv2dapi                \_MGHAVE\_ADV\_2DAPI        Support advanced 2D graphics API         Enabled
  screensaver             \_MG\_ENABLE\_SCREENSAVER   Screen saver                             Enabled

Some important configurations are introduced as the follow:

The **incoreres** option is used to control whether MiniGUI needs fonts,
bitmaps, cursors, icons and so on construct in the function library.
This option is very useful for tradition embedded operating system.
Because in the majority situation, the tradition embedded operating
system has not file system support, supporting by the in-core resource,
it was allowed to construct the above resources in the function library,
and MiniGUI can run without file system. Attention in, when uses in-core
resources, MiniGUI runtime configuration options can be compiled into
MiniGUI library directly.

The **miniguientry** option uses for control how to implement the
function MiniGUIMain. In the default situation (disabled this option),
The function MiniGUIMain can be expanded to the function main, so
application should not define the main function. The function
MiniGUIMain can be expanded to the function **minigui\_entry** when
option **miniguientry** is enabled. It is easy for debug and system
integration for some tradition embedded operating system.

The **fixedmath** option uses for control whether fixed math is included
in MiniGUI library, such as fixcos and so on. The clipboard option uses
for control whether MiniGUI is support clipboard or not; if this option
is disabled, and the editor cannot support cut and copy. The **adv2api**
option is control whether the MiniGUI include the advanced 2D graphics
API.

The debug, **tracemsg** and **msgstr** use for MiniGUI debugging, it is
not suggested user use it.

MiniGUI supports mouse cursor default. When target system has not any
fix point device like mouse or touch screen, we do not need display the
mouse cursor, so we can disabled the mouse cursor supporting from the
configuration options.

Splash and screensaver options are used to define the splash screen and
MiniGUI built-in screen saver program. In the actual project, you can
usually close these two options.

### Character Set and Font

MiniGUI has rich support for font. It supports RBF font, VBF font (these
two kinds of font are defined by MiniGUI), UPF/QPF font, TrueType font,
Adobe Type1 font and so on. Because MiniGUI supports many kinds of font,
so there are many flexible configuration options for font.

Like the type of font, MiniGUI provides a well support for character
set. A special character set support also can be flexible configured.
Table 2.13 lists character set and font related options and macros.

Table 2.13 character set and font related options and macros

  configuration options   Macro                             Comment                                                                    Default
  ----------------------- --------------------------------- -------------------------------------------------------------------------- ----------
  latin2support           \_MGCHARSET\_LATIN2               Include East European (Latin 2, ISO-8859-2) charset support                Disabled
  latin3support           \_MGCHARSET\_LATIN3               Include South European (Latin 3, ISO-8859-3) charset support               Disabled
  latin4support           \_MGCHARSET\_LATIN4               Include North European (Latin 4, ISO-8859-4) charset support               Disabled
  cyrillicsupport         \_MGCHARSET\_CYRILLIC             Include Cyrillic (ISO-8859-5) charset support                              Disabled
  arabicsupport           \_MGCHARSET\_ARABIC               Include Arabic (ISO-8859-6) charset support                                Disabled
  greeksupport            \_MGCHARSET\_GREEK                Include Greek (ISO-8859-7) charset support                                 Disabled
  hebrewsupport           \_MGCHARSET\_HEBREW               Include Hebrew (ISO-8859-8) charset support                                Disabled
  latin5support           \_MGCHARSET\_LATIN5               Include Turkish (Latin 5, ISO-8859-9) charset support                      Disabled
  latin6support           \_MGCHARSET\_LATIN6               Include Nordic, Latin 6, ISO-8859-10) charset support                      Disabled
  thaisupport             \_MGCHARSET\_THAI                 Include Thai (ISO-8859-11) charset support                                 Disabled
  latin7support           \_MGCHARSET\_LATIN7               Include Latin 7 (ISO-8859-13) charset support                              Disabled
  latin8support           \_MGCHARSET\_LATIN8               Include Latin 8 (ISO-8859-14) charset support                              Disabled
  latin9support           \_MGCHARSET\_LATIN9               Include Latin 9 (ISO-8859-15, West Extended) charset support               Disabled
  latin10support          \_MGCHARSET\_LATIN10              Include Latin 10 (ISO-8859-16, Romanian) charset support                   Disabled
  gbsupport               \_MGCHARSET\_GB                   Include EUC encoding of GB2312 charset support                             Enabled
  gbksupport              \_MGCHARSET\_GBK                  Include GBK charset support                                                Enabled
  gb18030support          \_MGCHARSET\_GB18030              Include GB18030-0 charset support                                          Disabled
  big5support             \_MGCHARSET\_BIG5                 Include BIG5 charset support                                               Enabled
  euckrsupport            \_MGCHARSET\_EUCKR                Include support for EUC encoding of KSC5636 and KSC5601 charsets           Disabled
  eucjpsupport            \_MGCHARSET\_EUCJP                Include support for EUC encoding of JISX0201 and JISX0208 charsets         Disabled
  shiftjissupport         \_MGCHARSET\_SHIFTJIS             Include support for Shift-JIS encoding of JISX0201 and JISX0208 charsets   Disabled
  unicodesupport          \_MGCHARSET\_UNICODE              Include UNICODE (ISO-10646-1 and UTF-8 encoding) support                   Enabled
  rbfsupport              \_MGFONT\_RBF                     Include RBFfont support                                                    Enabled
  rbfvgaoem               \_MGINCORERBF\_LATIN1\_VGAOEM     Include incore RBF font of ISO8859-1 8x16 fixed font                       Disabled
  rbfterminal             \_MGINCORERBF\_LATIN1\_TERMINAL   Include incore RBF font of ISO8859-1 12x24 fixed font                      Disabled
  rbffixedsys             \_MGINCORERBF\_LATIN1\_FIXEDSYS   Include incore RBF font of GB2312 12x12 fixed/song font                    Enabled
  vbfsupport              \_MGFONT\_VBF                     Include var bitmap font support                                            Enabled
  fontsserif              \_MGINCOREFONT\_SANSSERIF         Include incore VBF font sansserif                                          Enabled
  fontcourier             \_MGINCOREFONT\_COURIER           Include incore VBF font courier                                            Enabled
  fontsystem              \_MGINCOREFONT\_SYSTEM            Include incore VBF font symbol                                             Disabled
  upfsupport              \_MGFONT\_UPF                     Support FMSoft Unicode Prerendered Font(UPF).                              Enabled
  fonttimes               \_MGINCOREFONT\_TIMES             Include income Times UPF font                                              Enabled
  qpfsupport              \_MGFONT\_QPF                     Include Qt Prerendered Font (QPF) support                                  Enabled
  ttfsupport=ft1          \_MGFONT\_TTF                     Include TrueType Library support                                           Disabled
  ttfsupport=ft2          \_MGFONT\_FT2                     Include FreeType2 font support                                             Disabled
  ttfcachesize=256        \_MGTTF\_CACHE\_SIZE              Include TrueType cache support                                             256
  mttfcachenum=10         \_MGMAX\_TTF\_CACHE               Include TrueType cache num                                                 10

The options latin2support, latin3support, cyrillicsupport,
arabicsupport, greeksupport, hebrewsupport, latin5support,
latin6support, thaisupport, latin7support, latin8support, latin9support,
latin10support control ISO8859-2 to ISO8859-16 character set support,
they are single byte character set. There are supporting for ASCII
character and ISO8859-1 (Latin1) build in MiniGUI. No configuration
options for these two character sets.

The options gbsupport, gbksupport, gb18030support, big5support,
euckrsupport, eucjpsupport, shiftjissupport, unicodesupport control
GB2312, GBK, GB18030, BIG5, EUCKR, EUCJP, SHIFTJIS, UNICODE character
set/code system support.

The option rbfsupport control whether include the support for Raw Bitmap
Font (RBF) font, it is enabled as the default. Because RBF is the
default font format, so it is not suggested that user disable the
support for this font type.

rbfvgaoem, rbfterminal, rbffixedsys and other configuration options to
control whether the corresponding RBF dot matrix font built in MiniGUI
library. These compiler configuration options are enabled by default, so
that MiniGUI can still run normally when no font is loaded.

The option vbfsupport control whether include support for Variable
Bitmap Font (VBF) font, it is enabled default. If this option is
disabled, you not only disable the support for VBF font but also disable
the VBF font build in MiniGUI. When MiniGUI is running, the runtime
option \[**varbitmapfonts**\] section is ignored.

The fontsserif configuration options as well as fontcourier, fontsystem
compilation configuration options to control whether the MiniGUI library
built-in SanSerif, Courier and System VBF fonts. These built-in font
options are on by default and are not affected by the incoreres option.

The option upfsupport controls whether support for FMSoft Unicode
Prerendered Font (UPF) fonts is included in the MiniGUI library. Because
UPF fonts use UNICODE encoding, allowing UPF fonts support will
automatically enable MiniGUI's UNICODE character set support.

The option qpfsupport control whether support for Qt/Embedded
Prerendered Font (QPF). Because QPF font uses UNICODE coding, so if
support QPF font in MiniGUI, the UNICODE support is enabled
automatically. If incoreres option is enabled, some QPF fonts will be
built in MiniGUI.

The option ft2support control whether support for FreeType2 library in
MiniGUI library. MiniGUI can render the TrueType font by FreeType2
library version 2.3.4. If FreeType2 library is not installed in your
system, the configuration will disable this option automatically.

The option ttfsupport control whether support for TrueType in MiniGUI
library. MiniGUI also can render the TrueType font by FreeType library
version 1.3.0. If FreeType library version 1.3.0 is not installed in
your system, the configuration will disable this option automatically.
The attention, the interfaces of FreeType 2 are not compatible with
FreeType 1.

The option ttfcache control whether support TrueType cache for
FreeType1, it is enabled default. If ttfcache need enable, the option
ttfsupport should be enabled first.

The option **--with-mttfcachenum** uses for appoint the number of the
cache block when TrueType cache is enabled. The default value is 10.

The option **--with-ttfcachesize** uses for appoint the size of cache
block when TrueType cache is enabled, the default value is 64k.

Table 2.14 and table 2.15 list the TrueType cache related parameters,
options and macros.

Table 2.14 TrueType cache related options and macros

  Configure option         Macro                 Macro value   Memo
  ------------------------ --------------------- ------------- ---------------
  --with-mttfcachenum=10   \_MGMAX\_TTF\_CACHE   10            Default value
  --with-mttfcachenum=20                         20            
  --with-mttfcachenum=40                         40            

Table 2.15 TrueType cache related options and macros

  Configure option           > Macro                Macro value   Memo
  -------------------------- ---------------------- ------------- ---------------
  --with-ttfcachesize=64     \_MGTTF\_CACHE\_SIZE   64            Default value
  --with-ttfcachesize=128                           128           
  --with-ttfcachesize=256                           256           
  --with-ttfcachesize=512                           512           
  --with-ttfcachesize=1024                          1024          

### Image File Format

MiniGUI support for multiple image file formats, idiographic, MiniGUI
include Windows BMP, GIF, JPEG, PNG, PCX, LBM/PBM, TGA and so on.
Thereinto, MiniGUI only support Windows BMP in incore resource, so there
is not corresponding configuration option; The configuration option of
GIF, JPEG, PNG file is enabled; The configuration option of PCX,
LBM/PBM, TGA is disabled. It should be noted that if you want to MiniGUI
support JECG and PNG picture format, you need to install corresponding
libjpeg and libpng libraries into your system, there is the source code
of these two function libraries in the MiniGUI official website.

The table 2.16 listed image file format related configuration options
and macros.

Table 2.16 image file format related configuration options and macros

  configuration option   Macro            Comment                    Default value
  ---------------------- ---------------- -------------------------- ---------------
  gifsupport             \_MGIMAGE\_GIF   Support for GIF file       Enable
  jpgsupport             \_MGIMAGE\_JPG   Support for JPG file       Enable
  pngsupport             \_MGIMAGE\_PNG   Support for PNG file       Enable
  pcxsupport             \_MGIMAGE\_PCX   Support for PCX file       Disable
  lbmsupport             \_MGIMAGE\_LBM   Support for LBM/PBM file   Disable
  tgasupport             \_MGIMAGE\_TGA   Support for TGA file       Disable

### Appearance Renderer

In MiniGUI 3.0, we introduced Look and Feel (LF) concept. The original
flat, classic, fashion window style abstraction as a new LF renderer
(LFRDR), retained flat, classic renderer, while introducing a skin
renderer, while the original Fashion style through mGPlus. Where the
classic renderer is built-in, flat and skin renderers are controlled by
configuration options. Table 2.17 shows the appearance renderer
configuration options and the corresponding macros.

Table 2.17 appearance style related configuration options and macros

  configuration option   Macro               Comment                                          Memo
  ---------------------- ------------------- ------------------------------------------------ ---------
  --enable-flatlf        \_MGLF\_RDR\_FLAT   Simple flat style                                Enabled
  --enable-skinlf        \_MGLF\_RDR\_SKIN   Skin style, window and control fill by bitmap.   Enabled

### Control

MiniGUI provides configuration options for all base controls. MiniGUI
base controls refer to the controls contained in the MiniGUI core
library. From MiniGUI 3.0, we provide a new set of controls through the
mGNCS component. The new control set is well-designed and elegantly
interfaced, which completely replaces the MiniGUI's base control set.
Therefore, we strongly suggest that the new MiniGUI application be
developed using mGNCS instead of the MiniGUI built-in base control.
Because there is a better mGNCS, MiniGUI most of the base control
configuration options are turned off by default. If your application
uses these controls, please open the relevant configuration items.

Table 2.18 give all controls related configuration options and macros.

Table 2.18 control related configuration options and macros

  -------------------------------------------------------------------------------------------------------------------------------------------------
  configuration option   Macro                                Comment                                                               Default value
  ---------------------- ------------------------------------ --------------------------------------------------------------------- ---------------
  ctrlstatic             \_MGCTRL\_STATIC                     Include STATIC control                                                Enable

  ctrlbutton             \_MGCTRL\_BUTTON                     Include BUTTON control                                                Enable

  ctrlsledit             \_MGCTRL\_SLEDIT                     Include Simple EDITcontrol                                            Enable

  ctrlbidiedit           \_MGCTRL\_BIDIEDIT                   Include BIDI EDIT control                                             Disable

  newtextedit            \_MGCTRL\_TEXTEDIT\                  Include new textedit control                                          Enable
                         \_MGCTRL\_TEXTEDIT\_USE\_NEW\_IMPL                                                                         

  ctrllistbox            \_MGCTRL\_LISTBOX                    Include LISTBOX control                                               Enable

  ctrlpgbar              \_MGCTRL\_PROGRESSBAR                Include PROGRESSBAR control                                           Enable

  ctrlcombobox           \_MGCTRL\_COMBOBOX                   Include COMBOBOX control                                              Enable

  ctrlpropsheet          \_MGCTRL\_PROPSHEET                  Include MENUBUTTON control                                            Enable

  ctrltrackbar           \_MGCTRL\_TRACKBAR                   Include TRACKBARcontrol                                               Disable

  ctrlscrollbar          \_MGCTRL\_SCROLLBAR                  Include SCROLLBAR control                                             Disable

  ctrlnewtoolbar         \_MGCTRL\_NEWTOOLBAR                 Include NEWTOOLBAR control                                            Disable

  ctrlmenubtn            \_MGCTRL\_MENUBUTTON                 Include MENUBUTTON control                                            Disable

  ctrlscrollview         \_MGCTRL\_SCROLLVIEW                 Include SCROLLVIEW control                                            Disable

  ctrltextedit           \_MGCTRL\_TEXTEDIT                   Include base ScrollView support textedit control                      Disable

  ctrlmonthcal           \_MGCTRL\_MONTHCAL                   Include MONTHCALENDAR control                                         Disable

  ctrltreeview           \_MGCTRL\_TREEVIEW                   Include TREEVIEW control                                              Disable

  ctrlspinbox            \_MGCTRL\_SPINBOX                    Include SPINBOX control                                               Disable

  ctrlcoolbar            \_MGCTRL\_COOLBAR                    Include COOLBAR control                                               Disable

  ctrllistview           \_MGCTRL\_LISTVIEW                   Include LISTVIEW control                                              Disable

  ctrliconview           \_MGCTRL\_ICONVIEW                   Include ICONVIEW control                                              Disable

  ctrlgridview           \_MGCTRL\_GRIDVIEW                   Include gridview control                                              Disable

  ctrlanimation          \_MGCTRL\_ANIMATION                  Include the ANIMATION control and provides support for GIF89a files   Enable
  -------------------------------------------------------------------------------------------------------------------------------------------------

### Others

MiniGUI implemented some function families of the standard C function
libraries to be fit in with all kinds of embedded operating system
environment, it include malloc function family (malloc, calloc, free
function and so on), stdio format input and output function family
(printf, sprintf and so on) and POSIX thread function library interface
(pthread\_create, sem\_post and so on). Default, these function families
compile configuration options is disabled, and that they are useful in
the some traditional embedded operating system based on thread and task.
If you want to enable these options in the some operating systems, you
can refer to 2.2.1 chapter. Table 2.19 listed MiniGUI implemented C
library interface configuration options and corresponding macros.

Table 2.19 MiniGUI implemented C library interface related
configurations and macros

  configuration option   Macro                   Comment                                                                 Default value
  ---------------------- ----------------------- ----------------------------------------------------------------------- ---------------
  ownmalloc              \_MGUSE\_OWN\_MALLOC    Use MiniGUI implemented malloc function family                          Disable
  ownstdio               \_MGUSE\_OWN\_STDIO     Use MiniGUI implemented stdio format input and output function family   Disable
  ownpthread             \_MGUSE\_OWN\_PTHREAD   Use MiniGUI implemented thread function family                          Disable

Otherwise, you must define this macro: `__MINIGUI\_LIB__` , when you
use yourself makefile to compile MiniGUI function library in the Non-GNU
development environment.

Table 2.20 other compile macros

  Macro                  Comment                         Memo
  ---------------------- ------------------------------- ----------------------------------------------------------------
  `__MINIGUI\_LIB__`   Compile MiniGUI library macro   You must define this macros, when you use the Non-GNU makefile

Start with MiniGUI 3.0, you can specify the name suffix of the MiniGUI
library through the configure option. By default, the name of the
MiniGUI library varies depending on the operating mode, for example,
libminigui-ths.so, libminigui-procs.so, libminigui-sa.so , Respectively,
corresponding to MiniGUI-Threads, MiniGUI-Processes and
MiniGUI-Standalone mode of operation.

You can specify a special library name suffix with the --with-libsuffix
option.

## Minimal Configuration Options

In this chapter, we will give an example of minimum configuration
options in MiniGUI.

There is a buildlib-min script in the MiniGUI source codes build
directory. The buildlib-min script will be as the following:

```bash

#!/bin/sh

./configure \
    --disable-dblclk \
    --disable-cursor \
    --disable-mousecalibrate \
    --disable-clipboard \
    --disable-adv2dapi \
    --disable-splash \
    --disable-screensaver \
    --disable-flatlf \
    --disable-skinlf \
    --disable-rbfvgaoem \
    --disable-rbfterminal \
    --disable-vbfsupport \
    --disable-qpfsupport \
    --disable-upfsupport \
    --disable-bmpfsupport \
    --disable-latin9support \
    --disable-gbsupport \
    --disable-gbksupport \
    --disable-unicodesupport \
    --disable-savebitmap \
    --disable-jpgsupport \
    --disable-pngsupport \
    --disable-gifsupport \
    --disable-aboutdlg \
    --disable-savescreen \
    --disable-mousecalibrate \
    --disable-ctrlanimation \
    --disable-ctrlnewtextedit \
    --disable-consoleps2 \
    --disable-consoleimps2 \
    --disable-consolems \
    --disable-consolems3 \
    --disable-consolegpm
```

By using this script, you can configure MiniGUI to the minimum function
library that only supports ISO8859-1 charset:

Compiling MiniGUI to be MiniGUI-Threads.
No support for double click mouse button.
No support for cursor.
No support for code doing mouse calibration.
No support for clipboard.
No including VGAOEM/Terminal incoreres font.
No support for VBF font.
No support for Qt Prerendered Font(QPF).
No support for UPF Prerendered Font(UPF).
No support for TrueType font.
No support bitmap font.
No support for Latin 9(ISO-8859-15, West Extended) charset.
No support for EUC GB2312 charset.
No support for GBK charset.
No support for BIG5 charset.
No support for UNICODE (ISO-10646-1and UTF-8).
No support for BITMAP saving function.
No support for JPG image format.
No support for PNG image format.
No support for GIF image format.
No including “About MiniGUI” dialog box.
No support for advanced 2D graphics APIs
No include new TEXTEDIT support.
No building the console engine subdriver for PS2 mouse.
No building the console engine subdriver for IntelligentMouse (IMPS/2).
No building the console engine subdriver for old MS serial mouse.
No building the console engine subdriver for MS3 mouse.
No building the console engine subdriver for GPM daemon.
No Skin and Flat support.

Based on the configuration above, you can also delete some functions if
you want. For example, if you do not use menu button control in your
application, you can add **—disable-ctrlanimation** option in the
configuration script above, so there is not GIF animation control in
your compiled functions library, the MiniGUI functions library is made
smaller.

The `mgconfig.h` file to be generated in the configuration script
above, listed as follows:

```
```

## Changes in Version 4.0

---

[Previous Chapter](MiniGUIUserManualBuildingMiniGUI.md)  
[Table of Contents](README.md)  
[Next Chapter](MiniGUIUserManualRuntimeConfiguration.md)

[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[MiniGUI Official Website]: http://www.minigui.com
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md
