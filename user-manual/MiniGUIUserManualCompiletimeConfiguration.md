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

If you specify an operating system, a macro for this operating system will
be defined in `mgconfig.h`. For some operating systems, the configuration
script will also enable other macros. The following table lists the options
and macros about operating systems.

##### Table: Options and macros for different operation systems

| Configuration options    | Macro                | Other macros         | Comments
| -------------------------|----------------------|----------------------|---------
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

In MiniGUI core, some code is related with a special target board,
especially when you use `Shadow` NEWGAL engine or `CommLCD` NEWGAL
engine for certain operating systems. More precisely, when you use
these two engines, you need to specify which sub-drivers should be
contained in MiniGUI core by a configuration option.

For this purpose, you use `--with-targetname` option to define
the name for your target board. We use this option to distinguish
the differences among various target boards for a specific
operating system. This occurs often when we use a real-time
operating system, because device drivers on such operating systems
tend to be relatively simple, but their design is not well abstracted
to hide the hardware details.

The default target board name is `unknown`. For the Linux operating system,
there is not much need to define a target board name, so we keep the
default in most cases. However, we recommend to define a target board
name when you port MiniGUI to a new target system for a traditional
real-time operating system, such as uC/OS-II, eCos, ThreadX, or others.

Since MiniGUI 3.2.2, we introduce a new target name `external`.
When you use `CommLCD` NEWGAL engine or `Comm` IAL engine to support
your target board, you can define the target name as `external`.
By using the target name, you do not need to change the source code
of MiniGUI core. Instead, you implement the engines outside the MiniGUI
core by defining some external functions. In this way, we reduce the
amount of work required to port MiniGUI to a new target board.

Since MiniGUI 4.0.0, the NEWGAL engine `dri` for Linux also support
the target name `external`. So you can implement the sub-driver of
`dri` engine outsize MiniGUI core.

For more information, please refer to:

- [Using CommLCD NEWGAL Engine and Comm IAL Engine](https://github.com/VincentWei/minigui/wiki/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine)
- [Writing DRI Engine Driver for Your GPU](https://github.com/VincentWei/minigui/wiki/Writing-DRI-Engine-Driver-for-Your-GPU)

The following table lists the options and macros related to
various target boards.

##### Table: Options and macros for target board

| Configuration options         | Macro                    | Comments
|-------------------------------|--------------------------|----------------------------------------------------------
| `--with-targetname=unknown`   | `__TARGET_UNKNOWN__`     | Unknown development board; Default value
| `--with-targetname=external`  | `__TARGET_EXTERNAL__`    | Define this target name when you want to implement the sub-drivers outside MiniGUI core for some NEWGAL and/or IAL engines
| `--with-targetname=fmsoft`    | `__TARGET_FMSOFT__`      | For FMSoft's internal use
| `--with-targetname=mstudio`   | `__TARGET_MSTUDIO__`     | For miniStudio
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

We can configure MiniGUI as one of three runtime modes:

- MiniGUI-Processes runtime mode base on multi-processes;
- MiniGUI-Threads runtime mode base on multi-thread;
- MiniGUI-Standalone runtime mode based on a single task architecture.

MiniGUI-Processes is the default mode for Linux operating system,
while MiniGUI-Threads is the default mode for other operating systems.

The following table lists the options and macros for runtime mode.

##### Table: Options and macros for runtime mode

| Configuration options   | Macro              | Comments
|-------------------------|--------------------|--------------------------------------------------------------------------------------
| `--with-runmode=procs`  | `_MGRM_PROCESSES`<BR/>`_LITE_VERSION` (back-compatibility definition)  | MiniGUI-Processes runtime mode, support Linux operating system only; Default for Linux
| `--with-runmode=ths`    | `_MGRM_THREADS`    | MiniGUI-Threads runtime mode, support all operating system; Default for operating systems other than Linux
| `--with-runmode=sa`     | `_MGRM_STANDALONE`<BR/>`_LITE_VERSION` (back-compatibility definition)<BR/>`_STAND_ALONE` (back-compatibility definition) | MiniGUI-Standalone runtime mode, support all operating system

### Graphics Engine

MiniGUI supports many kinds of graphics devices through
an abstract software layer called `NEWGAL`. We use a specific
NEWGAL engine to support a kind of graphics device via
the device driver provided by the operating system. A NEWGAL
engine is a software module which provides an implementation
for NEWGAL to drive a real graphics device or a virtual
graphics device.

The commonly used NEWGAL engines are as follow:

- `Dummy`: A pure software implementation; which does not make
any actual output. It is not associated with any hardware and
only provides a software implementation for easily debugging MiniGUI.
- `XVFB`: A pure software engine which implements a universal
virtual frame buffer. It is associated with a window on Linux or Windows,
so we can see the MiniGUI screens in the window. This engine is
helpful for developing MiniGUI apps on Linux or Windows PC.
- `FBCon`: A NEWGAL engine which uses Linux frame buffer device driver
(`/dev/fb`).
- `DRI` (Since MiniGUI 4.0): A NEWGAL engine which uses Linux DRI/DRM
to support modern graphics devices with 2D/3D hardware acceleration.
- `CommLCD`: A simple NEWGAL engine to support LCD without hardware
acceleration. We often use this engine on traditional real-time
operating systems.
- `Shadow`: This engine can be used to support a graphics display device
which have color format lower than 8 bit color. It can be used to support
the screen rotation.

The following table lists the common NEWGAL engines.

##### Table: Options and macros related to NEWGAL engine

| Switch option  | Macro            | Engine name | Default  | Comments
| ---------------|------------------|-------------|----------|---------
| `videodummy`   | `_MGGAL_DUMMY`   | `dummy`     | Enabled  | All operating system
| `videopcxvfb`  | `_MGGAL_PCXVFB`  | `pc_xvfb`   | Enabled  | Linux/Windows PC; The universal virtual buffer engine
| `videodri`     | `_MGGAL_DRI`     | `dri`       | Enabled  | Linux
| `videofbcon`   | `_MGGAL_FBCON`   | `fbcon`     | Enabled  | Linux/uClinux
| `videocommlcd` | `_MGGAL_COMMLCD` | `commlcd`   | Disabled | All operating system
| `videoshadow`  | `_MGGAL_SHADOW`  | `shadow`    | Disabled | All operating system, but only for MiniGUI-Threads and MiniGUI-Standalone runtime modes
| `videodfb`     | `_MGGAL_DFB`     | `dfb`       | Disabled | Run MiniGUI on DirectFB on Linux; Deprecated, use DRI instead
| `videoqvfb`    | `_MGGAL_QVFB`    | `qvfb`      | Disabled | Linux PC; The virtual buffer engine for QVFB; Deprecated
| `videowvfb`    | `_MGGAL_WVFB`    | `wvfb`      | Disabled | Win32; virtual buffer graphics engine for Win32; Deprecated

Note that `qvfb`/`wvfb` NEWGAL engines are deprecated since MiniGUI 3.2.
These two engines use QVFB/WVFB to show MiniGUI screens.
You should use XVFB (`pc_xvfb`) engine for MiniGUI 3.0 or later.

XVFB is a newly designed general purpose virtual buffer graphics engine;
it provides a universal virtual frame buffer engine for MiniGUI, and any
program which conforms to the specification of the universal frame buffer
can act as the virtual frame buffer to show MiniGUI screens. In other words,
we do not need to write an engine for a specific virtual frame buffer program.

Please use one of the following XVFB programs to work with `pc_xvfb` engine:

- GVFB: Use this on a Linux+GNOME environment; Public repo: <https://github.com/VincentWei/gvfb>.
- QVFB2: Use this on a Linux+KDE environment; Public repo: <https://github.com/VincentWei/qvfb2>.
- WVFB2: Use this on a Windows platform; Public repo: <https://github.com/VincentWei/wvfb2>.

The `shadow` graphics engine uses the sub-driver concept. Only one
sub-driver can be contained at one time, and this is determined by
the target board option. The sub-drivers of the Shadow graphics in
MiniGUI are (in MiniGUI source code directory `src/newgal/shadow`):

- `unknown`: the default sub-driver, similar with the dummy graphics
engine, user may modify this sub-driver in order to operate and visit
the underlying graphics devices.
- `fbcon`: sub-driver for Linux console frame buffer;
supporting display mode less than 8-bit color and screen rotation.
- `qvfb`: sub-driver for Linux QVFB (Qt virtual frame buffer);
supporting display mode less than 8-bit color and screen rotation.
- `wvfb`: sub-driver for WVFB (Windows virtual frame buffer);
supporting display mode less than 8-bit color and screen rotation.

The CommLCD engine also uses the sub-driver structure like Shadow
graphics engine. At present, sub-drivers for CommLCD graphics engine
are:

- `external`: Use the sub-driver implemented outside MiniGUI core.
- `vxi386`: Sub-driver for VxWorks i386 target board.
- `unknown`: If it is eCos operating system, the engine will use
the standard interface of eCos to implement a sub-driver.

Through the configuration option or macro, we can configure MiniGUI
to contain a certain graphics engine. But if you want MiniGUI to use
a certain graphics engine, you need to set the specific runtime
configuration option.

For instance, if you want MiniGUI to use the `dummy` graphics engine,
you can set the runtime configuration option as follow:

```
[system]
gal_engine=dummy
```

For more information about this settings, please refer to
[Runtime Configuration].

### Input Engine

MiniGUI supports many kinds of input devices through
an abstract software layer called `IAL`. We use a specific
IAL engine to support a kind of input device via
the device driver provided by the operating system. A IAL
engine is a software module which provides an implementation
for NEWGAL to drive a real input device or a virtual
input device.

The commonly used IAL engines are as follow:

- `Dummy`: Like `Dummy` NEWGAL engine, this IAL engine is not connected to
any actual input device, and it does not generate any input events.
Therefore, if the input engine for your target board is not ready, you can
run MiniGUI by using this input engine for debugging. Note that MiniGUI
will use this input engine when it cannot find the matched input engine
specified in the runtime configuration.
- `Auto`/`Random`: Like `Dummy` input engine, MiniGUI provide other two software
input engines, which both are not associated to any device. One is
`Auto` engine and the other is called `Random`. The former can generate
input events automatically and the later generates input events randomly.
These two engines may be used for auto-test of MiniGUI and its apps.
- `XVFB`: This input engine works with `XVFB` NEWGAL engine, so it is controlled
by `videopcxvfb` switch option (`_MGGAL_PCXVFB_`).
- `Console`: This input engine works with `FBCon` NEWGAL engine on Linux.
It gets input events from Linux keyboard and mouse devices.
- `Comm`: Like `CommLCD` NEWGAL engine, you can use this input engine to
implement a driver for input devices without changing the source code of
MiniGUI core.
- `libinput` (since MiniGUI 4.0): This engine provides support for
all modern input devices on Linux system, it depends on `libinput`
introduced by [Free Desktop](https://www.freedesktop.org/wiki/) project.

The following table lists the common IAL engines.

##### Table: Options and macros related to IAL engines

| Switch option    | Macro              | Engine name | Default   | Comments
|------------------|--------------------|-------------|-----------|---------
| `dummyial`       |  `_MGIAL_DUMMY`    | `dummy`     | Enabled   | Dummy input engine, for all operating system
| `consoleial`     |  `_MGIAL_CONSOLE`  | `console`   | Enabled   | Console input engine for Linux
| `libinputial`    |  `_MGIAL_LIBINPUT` | `libinput`  | Enabled   | The input engine based on `libinput` for Linux; Since MiniGUI 4.0
| `autoial`        |  `_MGIAL_AUTO`     | `auto`      | Disabled  | Automatic input engine, for all operating system
| `randomial`      |  `_MGIAL_RANDOM`   | `random`    | Disabled  | Random input engine, for all operating system
| `commial`        |  `_MGIAL_COMM`     | `comm`      | Disabled  | COMM input engine, for all operating system
| `customial`      |  `_MGIAL_CUSTOM`   | `custom`    | Disabled  | Use this engine when you want to implement the engine outside MiniGUI
| `tslibial`       |  `_MGIAL_TSLIB`    | `tslib`     | Disabled  | The input engine based on `tslib` for Linux; Deprecated
| `qvfbial`        |  `_MGIAL_QVFB`     | `qvfb`      | Disabled  | QVFB input engine for Linux, works with QVFB graphics engine; Deprecated
| `wvfbial`        |  `_MGIAL_WVFB`     | `wvfb`      | Disabled  | WVFB input engine for Win32, works with WVFB graphics engine; Deprecated
| `dfbial`         |  `_MGIAL_DFB`      | `dfb`       | Disabled  | This engine runs on DirectFB on Linux; Deprecated
| `qemuial`        |  `_MGIAL_QEMU`     | `qemu`      | Disabled  | QEMU input IAL, Linux; Deprecated

Through the configuration option or macro, we can configure MiniGUI
to contain a certain input engine. But if you want MiniGUI to use
a certain input engine, you need to set the specific runtime
configuration option.

For instance, if you want MiniGUI to use the `dummy` input engine,
you can set the runtime configuration option as follow:

```
[system]
ial_engine=dummy
```

The Console input engine provides support for the PC console of
Linux operating system. This input engine supports the standard PC
keyboard as well as many kinds of mouse protocol. You need configure
`mtype` and `mdev` field in `system` section of the runtime configuration
to set the correct mouse protocol and the mouse device when you use
this engine.

For more information about this settings, please refer to
[Runtime Configuration].

There are some configuration options for the mouse protocols supported.
The following table lists them.

##### Table: Options and macros related to mouse protocols

| Switch option  |  Macro              | Default | Comments
|----------------|---------------------|---------|---------
| `consoleps2`   |  `_MGCONSOLE_PS2`   | Enabled | Support PS2 mouse protocol
| `consoleimps2` |  `_MGCONSOLE_IMPS2` | Enabled | Support intelligence mouse(IMPS/2) protocol
| `consolems`    |  `_MGCONSOLE_MS`    | Enabled | Support old MS serial-port mouse
| `consolems3`   |  `_MGCONSOLE_MS3`   | Enabled | Support MS3 mouse protocol
| `consolegpm`   |  `_MGCONSOLE_GPM`   | Enabled | Support GPM Daemon processes

Except the options above, MiniGUI also provides mouse and touch
screen calibration interfaces for applications. If you want to use this
interfaces, you need to enable the option. The following table
lists the option and macro related to the mouse or touch screen
calibration interface.

##### Table: Option and macro related to mouse calibration interface

| Switch options   | Macro                    | Default | Comments
|------------------|--------------------------|---------|---------
| `mousecalibrate` | `_MGHAVE_MOUSECALIBRATE` | Enabled | Support touch screen calibration

**Note that new project should use `libinput` engine of MiniGUI 4.0
instead of `console` input engine on Linux. Because `libinput` engine
provides support for all modern input devices including keyboard, mouse,
multiple touch panel, gesture, joystick, tablet tool, table pad,
and even switch.**

### Keyboard Layout

MiniGUI uses keyboard layout to control the behavior of function
`TranslateMessage`. MiniGUI translates a same key press as
a different character or character sequence under different keyboard layout.

At present, MiniGUI contains support for the standard American 101/102
keyboard as the default keyboard layout. If you want to use a different
keyboard layout in your program, you can call `SetKeyboardLayout` by the
keyboard layout name. For more information about these functions,
please refer to [MiniGUI Programming Guide]. However, you need
to enable the support for a specific keyboard layout in MiniGUI core
before using it.

The following table lists the options and macros related to
the keyboard layout.

##### Table: Options and macros related to keyboard layout

| Switch option | Macro                   | Keyboard layout name | Default  | Comments
|---------------|-------------------------|----------------------|----------|---------
| `Kbdfrpc`     | `_MGKBDLAYOUT_FRPC`     | `frpc`               | Disabled | Keyboard layout for French PC keyboard (non-US 102 keys)
| `Kbdfr`       | `_MGKBDLAYOUT_FR`       | `fr`                 | Disabled | Keyboard layout for French
| `Kbdde`       | `_MGKBDLAYOUT_DE`       | `de`                 | Disabled | Keyboard layout for German
| `kbddelatin1` | `_MGKBDLAYOUT_DELATIN1` | `delatin1`           | Disabled | Keyboard layout for German Latin1
| `Kbdit`       | `_MGKBDLAYOUT_IT`       | `it`                 | Disabled | Keyboard layout for Italian
| `Kbdes`       | `_MGKBDLAYOUT_ES`       | `es`                 | Disabled | Keyboard layout for Spanish
| `kbdescp850`  | `_MGKBDLAYOUT_ESCP850`  | `escp850`            | Disabled | Keyboard layout for Spanish CP850
| `kbdhebrewpc` | `_MGKBDLAYOUT_HEBREWPC` | `hebrewpc`           | Disabled | Keyboard layout for Hebrew PC keyboard
| `kbdarabicpc` | `_MGKBDLAYOUT_ARABICPC` | `arabicpc`           | Disabled | Keyboard layout for Arabic PC keyboard

### Global Options and Macros

The following table lists the system global configuration options and macros.

##### Table: System global configuration options and macros

| Switch option   | Macro                    | Default  | Comments
|-----------------|--------------------------|----------|---------
| `incoreres`     | `_MGINCORE_RES`          | Disabled | The MiniGUI resource will be built in MiniGUI core instead of loading them from file system.
| `miniguientry`  | `_USE_MINIGUIENTRY`      | Disabled | Use MiniGUI `minigui_entry` function.
| `develmode`     | `_DEBUG`                 | Disabled | Developer mode; internal use for MiniGUI developer.
| `debug`         | `_DEBUG`                 | Disabled | Including debug output
| `tracemsg`      | `_MGHAVE_TRACE_MSG`      | Disabled | Trace MiniGUI message
| `msgstr`        | `_MGHAVE_MSG_STRING`     | Disabled | Include the string name of the message
| `cursor`        | `_MGHAVE_CURSOR`         | Enabled  | Support mouse cursor
| `fixedmath`     | `_MGHAVE_FIXED_MATH`     | Enabled  | Use fixed math functions
| `clipboard`     | `_MGHAVE_CLIPBOARD`      | Enabled  | Support clipboard
| `adv2dapi`      | `_MGHAVE_ADV_2DAPI`      | Enabled  | Support advanced 2D graphics API
| `aboutdlg`      | `_MGMISC_ABOUTDLG`       | Enabled  | Include About dialog box
| `savebitmap`    | `_MGMISC_SAVEBITMAP`     | Enabled  | Support `SaveBitmap` related functions
| `savescreen`    | `_MGHAVE_SAVESCREEN`     | Enabled  | Support screen capture
| `dblclk`        | `_MGMISC_DOUBLE_CLICK`   | Enabled  | Support mouse double click
| `splash`        | `_MG_ENABLE_SPLASH`      | Enabled  | Splash screen
| `screensaver`   | `_MG_ENABLE_SCREENSAVER` | Disabled | Screen saver; deprecated

Some important configuration options are described as follow:

- `incoreres`  
The `incoreres` option is used to control whether the fonts,
bitmaps, cursors, and icons used by MiniGUI core are built within
MiniGUI core library instead of loading them from file system.
This option is very useful for traditional embedded operating system.
Because in the most situation, the tradition embedded operating
system has not support for file system. By enabling `incoreres`,
the resource used by MiniGUI core will built in the library, so
we can run MiniGUI and its apps without file system. Note that,
when we use incore resource, the runtime configuration options
will be compiled into the libraries, so we can not change
the runtime configuration without re-building the library.
- `miniguientry`  
The `miniguientry` option is used to control how to implement the
function `MiniGUIMain`. In the default situation (disabled this option),
The function `MiniGUIMain` (it is a macro actually) will be expanded to
a call to the function `main`, so a MiniGUI app does not need to define
`main` function explicitly. This works on Linux well. However, on some
tradition embedded operating systems, it is not good to implement
the entry of a MiniGUI app in `main` function. To resolve this issue,
you can enable `miniguientry` option. When this option is enabled,
the function `MiniGUIMain` will be expanded to a call to the function
`minigui_entry` instead of `main`. And you can call `minigui_entry` in
the system `main` function.
- `develmode`, `debug`, `tracemsg`, `msgstr`  
These options are used for debugging MiniGUI core, it is not suggested
to enable them for a real MiniGUI app.
- `cursor`  
MiniGUI shows mouse cursor on screen by default. When the target system
has not any pointing device like mouse or touch screen, we do not need
to show the mouse cursor. In this situation, we disable this option.
- `fixedmath`  
The `fixedmath` option is used to control whether fixed math is included
in MiniGUI core library, such as `fixcos` and so on.
- `clipboard`  
The `clipboard` option is used to control whether MiniGUI supports
clipboard or not. If this option is disabled, the editor control cannot
support copy-and-paste function.
- `adv2dapi`  
The `adv2api` option is used to control whether MiniGUI includes the
advanced 2D graphics API.
- `splash` and `screensaver`
These two options are used to define the splash screen and
MiniGUI built-in screen saver. In an actual project, you can
disable both options.

### Character Set and Font

MiniGUI has rich support for font. It supports RBF font, VBF font (these
two kinds of font are defined by MiniGUI), UPF/QPF font, TrueType font,
Adobe Type1 font and so on. Because MiniGUI supports many kinds of font,
so there are many flexible configuration options for font.

Like the type of font, MiniGUI provides a well support for character
set. A special character set support also can be flexible configured.
Table 2.13 lists character set and font related options and macros.

Table 2.13 character set and font related options and macros

| Options           | Macro                          |  Default  | Comments
|-------------------|--------------------------------|-----------|---------
| `latin2support`   | `_MGCHARSET_LATIN2`            |  Disabled | Include East European (Latin 2, ISO-8859-2) charset support
| `latin3support`   | `_MGCHARSET_LATIN3`            |  Disabled | Include South European (Latin 3, ISO-8859-3) charset support
| `latin4support`   | `_MGCHARSET_LATIN4`            |  Disabled | Include North European (Latin 4, ISO-8859-4) charset support
| `cyrillicsupport` | `_MGCHARSET_CYRILLIC`          |  Disabled | Include Cyrillic (ISO-8859-5) charset support
| `arabicsupport`   | `_MGCHARSET_ARABIC`            |  Disabled | Include Arabic (ISO-8859-6) charset support
| `greeksupport`    | `_MGCHARSET_GREEK`             |  Disabled | Include Greek (ISO-8859-7) charset support
| `hebrewsupport`   | `_MGCHARSET_HEBREW`            |  Disabled | Include Hebrew (ISO-8859-8) charset support
| `latin5support`   | `_MGCHARSET_LATIN5`            |  Disabled | Include Turkish (Latin 5, ISO-8859-9) charset support
| `latin6support`   | `_MGCHARSET_LATIN6`            |  Disabled | Include Nordic, Latin 6, ISO-8859-10) charset support
| `thaisupport`     | `_MGCHARSET_THAI`              |  Disabled | Include Thai (ISO-8859-11) charset support
| `latin7support`   | `_MGCHARSET_LATIN7`            |  Disabled | Include Latin 7 (ISO-8859-13) charset support
| `latin8support`   | `_MGCHARSET_LATIN8`            |  Disabled | Include Latin 8 (ISO-8859-14) charset support
| `latin9support`   | `_MGCHARSET_LATIN9`            |  Disabled | Include Latin 9 (ISO-8859-15, West Extended) charset support
| `latin10support`  | `_MGCHARSET_LATIN10`           |  Disabled | Include Latin 10 (ISO-8859-16, Romanian) charset support
| `gbsupport`       | `_MGCHARSET_GB`                |  Enabled  | Include EUC encoding of GB2312 charset support
| `gbksupport`      | `_MGCHARSET_GBK`               |  Enabled  | Include GBK charset support
| `gb18030support`  | `_MGCHARSET_GB18030`           |  Disabled | Include GB18030-0 charset support
| `big5support`     | `_MGCHARSET_BIG5`              |  Enabled  | Include BIG5 charset support
| `euckrsupport`    | `_MGCHARSET_EUCKR`             |  Disabled | Include support for EUC encoding of KSC5636 and KSC5601 charsets
| `eucjpsupport`    | `_MGCHARSET_EUCJP`             |  Disabled | Include support for EUC encoding of JISX0201 and JISX0208 charsets
| `shiftjissupport` | `_MGCHARSET_SHIFTJIS`          |  Disabled | Include support for Shift-JIS encoding of JISX0201 and JISX0208 charsets
| `unicodesupport`  | `_MGCHARSET_UNICODE`           |  Enabled  | Include UNICODE (ISO-10646-1 and UTF-8 encoding) support
| `rbfsupport`      | `_MGFONT_RBF`                  |  Enabled  | Include RBFfont support
| `rbfvgaoem`       | `_MGINCORERBF_LATIN1_VGAOEM`   |  Disabled | Include incore RBF font of ISO8859-1 8x16 fixed font
| `rbfterminal`     | `_MGINCORERBF_LATIN1_TERMINAL` |  Disabled | Include incore RBF font of ISO8859-1 12x24 fixed font
| `rbffixedsys`     | `_MGINCORERBF_LATIN1_FIXEDSYS` |  Enabled  | Include incore RBF font of GB2312 12x12 fixed/song font
| `vbfsupport`      | `_MGFONT_VBF`                  |  Enabled  | Include var bitmap font support
| `fontsserif`      | `_MGINCOREFONT_SANSSERIF`      |  Enabled  | Include incore VBF font sansserif
| `fontcourier`     | `_MGINCOREFONT_COURIER`        |  Enabled  | Include incore VBF font courier
| `fontsystem`      | `_MGINCOREFONT_SYSTEM`         |  Disabled | Include incore VBF font symbol
| `upfsupport`      | `_MGFONT_UPF`                  |  Enabled  | Support FMSoft Unicode Prerendered Font(UPF).
| `fonttimes`       | `_MGINCOREFONT_TIMES`          |  Enabled  | Include income Times UPF font
| `qpfsupport`      | `_MGFONT_QPF`                  |  Enabled  | Include Qt Prerendered Font (QPF) support
| `ttfsupport=ft1`  | `_MGFONT_TTF`                  |  Disabled | Include TrueType Library support
| `ttfsupport=ft2`  | `_MGFONT_FT2`                  |  Disabled | Include FreeType2 font support
| `ttfcachesize=256`| `_MGTTF_CACHE_SIZE`            |  256      | Include TrueType cache support
| `mttfcachenum=10` | `_MGMAX_TTF_CACHE`             |  10       | Include TrueType cache num

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

| Configure option         | Macro              | Macro value | Comments
|--------------------------|--------------------|-------------|---------------
| `--with-mttfcachenum=10` | `_MGMAX_TTF_CACHE` | 10          | Default value
| `--with-mttfcachenum=20` | `_MGMAX_TTF_CACHE` | 20          |
| `--with-mttfcachenum=40` | `_MGMAX_TTF_CACHE` | 40          |

Table 2.15 TrueType cache related options and macros

| Configure option           | Macro               | Macro value | Comments
|----------------------------|---------------------|-------------|---------
| `--with-ttfcachesize=64`   | `_MGTTF_CACHE_SIZE` | 64          | Default value
| `--with-ttfcachesize=128`  | `_MGTTF_CACHE_SIZE` | 128         |
| `--with-ttfcachesize=256`  | `_MGTTF_CACHE_SIZE` | 256         |
| `--with-ttfcachesize=512`  | `_MGTTF_CACHE_SIZE` | 512         |
| `--with-ttfcachesize=1024` | `_MGTTF_CACHE_SIZE` | 1024        |

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

| Switch option | Macro          | Default  | Comments
|---------------|----------------|----------|---------
| `gifsupport`  | `_MGIMAGE_GIF` | Enabled  | Support for GIF file
| `jpgsupport`  | `_MGIMAGE_JPG` | Enabled  | Support for JPG file
| `pngsupport`  | `_MGIMAGE_PNG` | Enabled  | Support for PNG file
| `pcxsupport`  | `_MGIMAGE_PCX` | Disabled | Support for PCX file
| `lbmsupport`  | `_MGIMAGE_LBM` | Disabled | Support for LBM/PBM file
| `tgasupport`  | `_MGIMAGE_TGA` | Disabled | Support for TGA file

### Appearance Renderer

In MiniGUI 3.0, we introduced Look and Feel (LF) concept. The original
flat, classic, fashion window style abstraction as a new LF renderer
(LFRDR), retained flat, classic renderer, while introducing a skin
renderer, while the original Fashion style through mGPlus. Where the
classic renderer is built-in, flat and skin renderers are controlled by
configuration options. Table 2.17 shows the appearance renderer
configuration options and the corresponding macros.

Table 2.17 appearance style related configuration options and macros

| Switch option | Macro            | Default | Comments
| --------------|------------------|---------|-----------
| `flatlf`      | `_MGLF_RDR_FLAT` | Enabled | Simple flat style
| `skinlf`      | `_MGLF_RDR_SKIN` | Enabled | Skin style, window and control fill by bitmap

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

| Switch option    | Macro                 | Default  | Comments
| -----------------|-----------------------|----------|---------
| `ctrlstatic`     | `_MGCTRL_STATIC`      | Enabled  | Include STATIC control
| `ctrlbutton`     | `_MGCTRL_BUTTON`      | Enabled  | Include BUTTON control
| `ctrlsledit`     | `_MGCTRL_SLEDIT`      | Enabled  | Include Simple EDITcontrol
| `ctrlbidiedit`   | `_MGCTRL_BIDIEDIT`    | Disabled | Include BIDI EDIT control
| `newtextedit`    | `_MGCTRL_TEXTEDIT`    | Enabled  | Include new textedit control
| `ctrllistbox`    | `_MGCTRL_LISTBOX`     | Enabled  | Include LISTBOX control
| `ctrlpgbar`      | `_MGCTRL_PROGRESSBAR` | Enabled  | Include PROGRESSBAR control
| `ctrlcombobox`   | `_MGCTRL_COMBOBOX`    | Enabled  | Include COMBOBOX control
| `ctrlpropsheet`  | `_MGCTRL_PROPSHEET`   | Enabled  | Include MENUBUTTON control
| `ctrltrackbar`   | `_MGCTRL_TRACKBAR`    | Disabled | Include TRACKBARcontrol
| `ctrlscrollbar`  | `_MGCTRL_SCROLLBAR`   | Disabled | Include SCROLLBAR control
| `ctrlnewtoolbar` | `_MGCTRL_NEWTOOLBAR`  | Disabled | Include NEWTOOLBAR control
| `ctrlmenubtn`    | `_MGCTRL_MENUBUTTON`  | Disabled | Include MENUBUTTON control
| `ctrlscrollview` | `_MGCTRL_SCROLLVIEW`  | Disabled | Include SCROLLVIEW control
| `ctrltextedit`   | `_MGCTRL_TEXTEDIT`    | Disabled | Include base ScrollView support textedit control
| `ctrlmonthcal`   | `_MGCTRL_MONTHCAL`    | Disabled | Include MONTHCALENDAR control
| `ctrltreeview`   | `_MGCTRL_TREEVIEW`    | Disabled | Include TREEVIEW control
| `ctrlspinbox`    | `_MGCTRL_SPINBOX`     | Disabled | Include SPINBOX control
| `ctrlcoolbar`    | `_MGCTRL_COOLBAR`     | Disabled | Include COOLBAR control
| `ctrllistview`   | `_MGCTRL_LISTVIEW`    | Disabled | Include LISTVIEW control
| `ctrliconview`   | `_MGCTRL_ICONVIEW`    | Disabled | Include ICONVIEW control
| `ctrlgridview`   | `_MGCTRL_GRIDVIEW`    | Disabled | Include gridview control
| `ctrlanimation`  | `_MGCTRL_ANIMATION`   | Enabled  | Include the ANIMATION control and provides support for GIF89a files

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

| Switch option | Macro                | Default  | Comments
|---------------|----------------------|----------|---------
| `ownmalloc`   | `_MGUSE_OWN_MALLOC`  | Disabled | Use MiniGUI implemented malloc function family
| `ownstdio`    | `_MGUSE_OWN_STDIO`   | Disabled | Use MiniGUI implemented stdio format input and output function family
| `ownpthread`  | `_MGUSE_OWN_PTHREAD` | Disabled | Use MiniGUI implemented thread function family

Otherwise, you must define this macro: `__MINIGUI\_LIB__` , when you
use yourself makefile to compile MiniGUI function library in the Non-GNU
development environment.

##### Table Other macros

| Macro             | Comments
| ------------------|----------
| `__MINIGUI_LIB__` | Compile MiniGUI library macro; You must define this macro

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

[Building MiniGUI](MiniGUIUserManualBuildingMiniGUI.md) | [Table of Contents](README.md) | [Runtime Configuration](MiniGUIUserManualRuntimeConfiguration.md)

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
[Feature List]: MiniGUIDataSheet.md
[FAQs]: MiniGUIUserManualFAQsEN.md
