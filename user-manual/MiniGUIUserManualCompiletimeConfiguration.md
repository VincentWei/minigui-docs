# Compile-time Configuration

- [Configuration Options and Macros](#configuration-options-and-macros)
   * [Operating System](#operating-system)
   * [Target Board](#target-board)
   * [Runtime Mode](#runtime-mode)
   * [Graphics Engine](#graphics-engine)
   * [Input Engine](#input-engine)
   * [Keyboard Layout](#keyboard-layout)
   * [Global Options and Macros](#global-options-and-macros)
   * [Character Set](#character-set)
   * [Font](#font)
   * [Image File Format](#image-file-format)
   * [Appearance Renderer](#appearance-renderer)
   * [Control](#control)
   * [Others](#others)
- [Minimal Configuration Options](#minimal-configuration-options)
- [Changes in Version 4.0](#changes-in-version-40)

## Configuration Options and Macros

In this chapter, we will give detailed descriptions on most important
compile-time configuration options of MiniGUI. MiniGUI has many
such options; you can combine these options to generate your own
MiniGUI library.

### Operating System

MiniGUI provides support for multiple operating systems, you can specify
operating system when execute configuration script, the default operating
system is Linux. If you want to run MiniGUI on eCos, you can execute command
as follow:

```
$ ./configure --with-osname=ecos
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

In MiniGUI Core, some code is related to a specific target board,
especially when you use `Shadow` NEWGAL engine or `CommLCD` NEWGAL
engine for certain operating systems. More precisely, when you use
these two engines, you need to specify which sub-drivers should be
contained in MiniGUI Core via a configuration option.

For this purpose, you can use `--with-targetname` option to define
the name for your target board. You use this option to distinguish
the differences among various target boards for a specific
operating system. This occurs often when you use a real-time
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
Core by defining some external functions. In this way, we reduce the
amount of work required to port MiniGUI to a new target board.

Since MiniGUI 4.0.0, the NEWGAL engine `dri` for Linux also supports
the target name `external`. So you can implement the sub-driver of
`dri` engine outside MiniGUI Core.

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

`MiniGUI-Processes` is the default mode for Linux operating system,
while `MiniGUI-Threads` is the default mode for other operating systems.

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
`NEWGAL` engine to support a kind of graphics device via
the device driver provided by the operating system. A `NEWGAL`
engine is a software module which provides an implementation
for `NEWGAL` to drive a real graphics device or a virtual
graphics device.

The commonly used `NEWGAL` engines are as follow:

- `Dummy`: A pure software implementation; it does not make
any actual output. It is not associated with any hardware and
only provides a software implementation for easily debugging MiniGUI.
- `XVFB`: A pure software engine which implements a universal
virtual frame buffer. It is associated with a window on Linux or MS Windows,
so we can see the MiniGUI screens in the window. This engine is
helpful for developing MiniGUI apps on Linux or MS Windows.
- `FBCon`: A `NEWGAL` engine uses Linux frame buffer device driver
(`/dev/fb`).
- `DRI` (Since MiniGUI 4.0): A `NEWGAL` engine uses Linux DRI/DRM
to support modern graphics devices with 2D/3D hardware acceleration.
- `CommLCD`: A simple `NEWGAL` engine to support LCD without hardware
acceleration. We often use this engine on traditional real-time
operating systems.
- `Shadow`: This engine can be used to support a graphics display device
which have color format lower than 8 bit color. It can be used to support
screen rotation.

The table below lists the common `NEWGAL` engines.

##### Table: Options and macros related to `NEWGAL` engine

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

Note that `qvfb`/`wvfb` `NEWGAL` engines are deprecated since MiniGUI 3.2.
These two engines use `QVFB/WVFB` to show MiniGUI screens.
You should use `XVFB `(`pc_xvfb`) engine for MiniGUI 3.0 or later.

`XVFB` is a newly designed general purpose virtual buffer graphics engine;
it provides a universal virtual frame buffer engine for MiniGUI, and any
program conforms to the specification of the universal frame buffer
can act as the virtual frame buffer to show MiniGUI screens. In other words,
You do not need to write an engine for a specific virtual frame buffer program.

Please use one of the following `XVFB` programs to work with `pc_xvfb` engine:

- `GVFB`: Use this on a Linux+GNOME environment; Public repo: <https://github.com/VincentWei/gvfb>.
- `QVFB2`: Use this on a Linux+KDE environment; Public repo: <https://github.com/VincentWei/qvfb2>.
- `WVFB2`: Use this on a MS Windows platform; Public repo: <https://github.com/VincentWei/wvfb2>.

The `shadow` graphics engine uses the sub-driver concept. Only one
sub-driver can be contained at one time, and this is determined by
the target board option. The sub-drivers of the `Shadow` graphics in
MiniGUI are (in MiniGUI source code directory `src/newgal/shadow`):

- `unknown`: the default sub-driver, similar to the dummy graphics
engine, you may modify this sub-driver in order to operate and visit
the underlying graphics devices.
- `fbcon`: sub-driver for Linux console frame buffer;
supporting display mode less than 8-bit color and screen rotation.
- `qvfb`: sub-driver for Linux `QVFB` (Qt virtual frame buffer);
supporting display mode less than 8-bit color and screen rotation.
- `wvfb`: sub-driver for `WVFB` (MS Windows virtual frame buffer);
supporting display mode less than 8-bit color and screen rotation.

The `CommLCD` engine also uses the sub-driver structure like `Shadow`
graphics engine. At present, sub-drivers for `CommLCD` graphics engine
are:

- `external`: Use the sub-driver implemented outside MiniGUI Core.
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
`IAL` engine to support a kind of input device via
the device driver provided by the operating system. An `IAL`
engine is a software module which provides an implementation
for `NEWGAL` to drive a real input device or a virtual
input device.

The commonly used `IAL` engines are as follow:

- `Dummy`: Like `Dummy` `NEWGAL` engine, this `IAL` engine is not connected to
any actual input device, and it does not generate any input events.
Therefore, if the input engine for your target board is not ready, you can
run MiniGUI by using this input engine for debugging. Note that MiniGUI
will use this input engine when it cannot find the matched input engine
specified in the runtime configuration.
- `Auto`/`Random`: Like `Dummy` input engine, MiniGUI provide other two software
input engines, both are not associated to any device. One is
`Auto` engine and the other is called `Random`. The former can generate
input events automatically and the later generates input events randomly.
These two engines may be used for auto-test of MiniGUI and its apps.
- `XVFB`: This input engine works with `XVFB` `NEWGAL` engine, so it is controlled
by `videopcxvfb` switch option (`_MGGAL_PCXVFB_`).
- `Console`: This input engine works with `FBCon` `NEWGAL` engine on Linux.
It gets input events from Linux keyboard and mouse devices.
- `Comm`: Like `CommLCD` `NEWGAL` engine, you can use this input engine to
implement a driver for input devices without changing the source code of
MiniGUI core.
- `libinput` (since MiniGUI 4.0): This engine provides support for
all modern input devices on Linux systems, it depends on `libinput`
introduced by [Free Desktop](https://www.freedesktop.org/wiki/) project.

The table below lists the common `IAL` engines.

##### Table: Options and macros related to `IAL` engines

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

The Console input engine provides support for the console of
Linux operating system. This input engine supports the standard PC
keyboard as well as many kinds of mouse protocol. You need to configure
`mtype` and `mdev` fields in `system` section of the runtime configuration
to set the correct mouse protocol and the mouse device when you use
this engine.

For more information about the settings, please refer to
[Runtime Configuration].

There are some configuration options for the mouse protocols supported.
The table below lists them.

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

**Note that new projects should use `libinput` engine of MiniGUI 4.0
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
to enable the support for a specific keyboard layout in MiniGUI Core
before using it.

The table below lists the options and macros related to
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

The table below lists the system global configuration options and macros.

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
bitmaps, cursors, and icons used by MiniGUI Core are built within
MiniGUI Core library instead of loading them from file system.
This option is very useful for traditional embedded operating system.
Because in the most situation, the tradition embedded operating
system has not support for file system. By enabling `incoreres`,
the resource used by MiniGUI Core will be built in the library, so
you can run MiniGUI and its apps without file system. Note that,
when we use incore resource, the runtime configuration options
will be compiled into the libraries, so you can not change
the runtime configuration without re-building the library.
- `miniguientry`  
The `miniguientry` option is used to control how to implement the
function `MiniGUIMain`. In the default situation  (this option is disabled),
The function `MiniGUIMain` (it is a macro actually) will be expanded to
a call to the function `main`, so a MiniGUI app does not need to define
`main` function explicitly. This works on Linux well. However, on some
traditional embedded operating systems, it is not a good idea to implement
the entry of a MiniGUI app in `main` function. To resolve this issue,
you can enable `miniguientry` option. When this option is enabled,
the function `MiniGUIMain` will be expanded to a call to the function
`minigui_entry` instead of `main`. And you can call `minigui_entry` in
the system `main` function.
- `develmode`, `debug`, `tracemsg`, `msgstr`  
These options are used for debugging MiniGUI Core, it is not suggested
to enable them for a real MiniGUI app.
- `cursor`  
MiniGUI shows mouse cursor on screen by default. When the target system
does not have any pointing device like mouse or touch screen, you do not need
to show the mouse cursor. Under this situation, disable this option.
- `fixedmath`  
The `fixedmath` option is used to control whether fixed point math is included
in MiniGUI Core library, such as `fixcos` and so on.
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

### Character Set

MiniGUI provides a good support for character sets. The character sets
supported by MiniGUI Core library can be flexibly configured as well.
The table below lists the options and macros related to character sets.

##### Table: Options and macros related to character sets

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

The options `latin2support`, `latin3support`, `cyrillicsupport`,
`arabicsupport`, `greeksupport`, `hebrewsupport`, `latin5support`,
`latin6support`, `thaisupport`, `latin7support`, `latin8support`,
`latin9support`, and `latin10support` control the support for ISO8859-2
to ISO8859-16 character sets respectively.
The support for ASCII and ISO8859-1 character sets are built in MiniGUI,
and no configuration options applied to these two character sets.

The options `gbsupport`, `gbksupport`, `gb18030support`, `big5support`,
`euckrsupport`, `eucjpsupport`, and `shiftjissupport` control
the support for GB2312, GBK, GB18030, BIG5, EUCKR, EUCJP, SHIFTJIS
character sets or encodings respectively. And the option `unicodesupport`
controls the support for UNICODE character set, i.e., the encodings of
UTF-16LE, UTF-16BE, and UTF-8.

**Currently, in most cases you only need to enable the support for Unicode
character set. If you need to support a particular character set or encoding
in your app, or if you need to convert a string encoded in a specific
character set or encoding, you need to enable the support for those character
sets or encodings.**

### Fonts

MiniGUI provides support for various font types. It supports RBF font,
VBF font, and UPF font, these three kinds of font are defined by MiniGUI.
It also provides support for QPF font, TrueType font, OpenType font, and
Adobe Type 1 font.

The table below lists the options and macros related to fonts.

##### Table: Options and macros related to font

| Options                  | Macro                          |  Default  | Comments
|--------------------------|--------------------------------|-----------|---------
| `rbfsupport`             | `_MGFONT_RBF`                  |  Enabled  | Include support for RBF font
| `vbfsupport`             | `_MGFONT_VBF`                  |  Enabled  | Include support for VBF font
| `upfsupport`             | `_MGFONT_UPF`                  |  Enabled  | Include support for UPF font
| `qpfsupport`             | `_MGFONT_QPF`                  |  Enabled  | Include support for QPF font
| `--with-ttfsupport=none` |                                |  Yes      | Do not support TrueType font; Version 3.2 only
| `--with-ttfsupport=ft1`  | `_MGFONT_TTF`                  |  no       | Use FreeType 1 to support TrueType font; Version 3.2 only
| `--with-ttfsupport=ft2`  | `_MGFONT_FT2`                  |  no       | Use FreeType 2 to support TrueType font; Version 3.2 only
| `ttfsupport`             | `_MGFONT_FT2`                  |  Enabled  | Use FreeType 2 to support TrueType font; Since version 4.0
| `complexscripts`         | `_MGCOMPLEX_SCRIPTS`           |  Enabled  | Support complex scripts; Since version 4.0
| `rbfvgaoem`              | `_MGINCORERBF_LATIN1_VGAOEM`   |  Enabled  | Include incore RBF font of ISO8859-1 (8x16)
| `rbfterminal`            | `_MGINCORERBF_LATIN1_TERMINAL` |  Enabled  | Include incore RBF font of ISO8859-1 (12x24)
| `rbffixedsys`            | `_MGINCORERBF_LATIN1_FIXEDSYS` |  Enabled  | Include incore RBF font of ISO8859-1 (6x12)
| `fontsserif`             | `_MGINCOREFONT_SANSSERIF`      |  Enabled  | Include incore VBF font SansSerif
| `fontcourier`            | `_MGINCOREFONT_COURIER`        |  Enabled  | Include incore VBF font Courier
| `fontsystem`             | `_MGINCOREFONT_SYSTEM`         |  Enabled  | Include incore VBF font System
| `fonttimes`              | `_MGINCOREFONT_TIMES`          |  Enabled  | Include incore UPF font Times
| `ttfcache`               | `_MGFONT_TTF_CACHE`            |  Enabled  | Use cache for TrueType fonts
| `mttfcachenum=10`        | `_MGMAX_TTF_CACHE`             |  10       | The number of TrueType font cache blocks
| `ttfcachesize=256`       | `_MGTTF_CACHE_SIZE`            |  256      | The size of each TrueType font cache block

The option `rbfsupport` controls whether to include the support for
Raw Bitmap Font (RBF) font, it is enabled by default. Because RBF
is a basic font format, you should not disable the support for
this font type.

The option `vbfsupport` controls whether to include the support for
Variable Bitmap Font (VBF) font.

The option `upfsupport` controls whether to include the support for
FMSoft Unicode Pre-rendered Font (UPF) font. Because
UPF fonts use UNICODE encoding, enabling the support for UPF font will
automatically enable the support for UNICODE character set.

The option `qpfsupport` controls whether to include the support for
Qt/Embedded Pre-rendered Font (QPF). Because QPF font uses UNICODE encoding,
if you enable the support for QPF font, the support for UNICODE character
set will be enabled automatically.

The option `ttfsupport` controls whether to include the support for
TrueType in MiniGUI library. In version 3.2, this option uses the form
`--with-ttfsupport`, you can specify a value to tell MiniGUI supports
TrueType by using FreeType 1 or FreeType 2.

Since version 4.0, this option changes as a switch option, i.e., only
FreeType 2 is supported. If you enable this option, MiniGUI will
use FreeType 2 to render TrueType fonts.

Note that, when we use FreeType 2 as the font engine, MiniGUI can
not only render TrueType font (font file with `.ttf` or `.ttc` suffix),
but also OpenType font (with `.otf` suffix) and Adobe Type 1 font
(with `.pfb` suffix).

The option `complexscripts` controls whether to include the support for
the complex scripts like Arabic, Thai, and Indic. When enabled, you can
use the APIs of MiniGUI to lay out, shape, and render glyphs from complex
and mixed scripts. For more information, please refer to
[Showing Text in Complex or Mixed Scripts]. Note that this option works
since MiniGUI 4.0, and when you enable this option with `ttfsupport`
option, MiniGUI will use [HarfBuzz] as the shaping engine to shape the
text in complex scripts.

The `rbfvgaoem`, `rbfterminal`, and `rbffixedsys` options control
whether to include the built-in `VGAOEM`, `Terminal`, and `FixedSys` RBF
fonts in MiniGUI core library respectively. These options are enabled by
default, so that MiniGUI can show text even if there is no external font
was loaded.

The `fontsserif`, `fontcourier`, and `fontsystem` options control
whether to include the built-in `SanSerif`, `Courier` and `System` VBF
fonts in MiniGUI Core library respectively.

The `fonttimes` option controls whether to include the built-in `Times`
UPF fonts in MiniGUI Core library.

The option `ttfcache` control whether to support TrueType cache.

The option `--with-mttfcachenum` is used to specify the number of the
cache blocks when TrueType cache is enabled. The default value is 10.
The following table gives all possible values for this option.

##### Table: Possible values for mttfcachenum

| Configure option         | Macro              | Macro value | Comments
|--------------------------|--------------------|-------------|---------------
| `--with-mttfcachenum=10` | `_MGMAX_TTF_CACHE` | 10          | Default value
| `--with-mttfcachenum=20` | `_MGMAX_TTF_CACHE` | 20          |
| `--with-mttfcachenum=40` | `_MGMAX_TTF_CACHE` | 40          |

The option `--with-ttfcachesize` is used to specify the size of one
cache block when TrueType cache is enabled. The default value is 256 (256KB).
The table below gives all possible values for this option.

##### Table: Possible values for ttfcachesize

| Configure option           | Macro               | Macro value | Comments
|----------------------------|---------------------|-------------|---------
| `--with-ttfcachesize=64`   | `_MGTTF_CACHE_SIZE` | 64          | Default value
| `--with-ttfcachesize=128`  | `_MGTTF_CACHE_SIZE` | 128         |
| `--with-ttfcachesize=256`  | `_MGTTF_CACHE_SIZE` | 256         |
| `--with-ttfcachesize=512`  | `_MGTTF_CACHE_SIZE` | 512         |
| `--with-ttfcachesize=1024` | `_MGTTF_CACHE_SIZE` | 1024        |
| `--with-ttfcachesize=2048` | `_MGTTF_CACHE_SIZE` | 2048        | Since 4.0

### Image File Format

MiniGUI provides support for multiple image file formats, including
MS Windows BMP, GIF, JPEG, PNG, PCX, LBM/PBM, and TGA. The support for
MS Windows BMP is a built-in feature, so there is no corresponding configuration
option. The support for other image formats can be controlled by
the options described in this section.

The table below lists the options and macros related to image file format.

##### Table: Options and macros related to image file format

| Switch option | Macro          | Default  | Comments
|---------------|----------------|----------|---------
| `gifsupport`  | `_MGIMAGE_GIF` | Enabled  | Support for GIF file
| `jpgsupport`  | `_MGIMAGE_JPG` | Enabled  | Support for JPEG file; Depend on LibJPEG v7.
| `pngsupport`  | `_MGIMAGE_PNG` | Enabled  | Support for PNG file; Depend on LibPNG 1.2.x or 1.6.x.
| `pcxsupport`  | `_MGIMAGE_PCX` | Disabled | Support for PCX file
| `lbmsupport`  | `_MGIMAGE_LBM` | Disabled | Support for LBM/PBM file
| `tgasupport`  | `_MGIMAGE_TGA` | Disabled | Support for TGA file

It should be noted that the support for JPEG and PNG image formats
depends on the third-party libraries. For more information, please refer to
[Building MiniGUI].

### Appearance Renderer

In MiniGUI 3.0, we introduced the look and feel renderer. The original
classic, flat, and skin window appearance styles were re-designed as three
appearance renderers (`LFRDR` for short). The classic LFRDR is built-in
MiniGUI core, and there is no configuration option for this renderer.
The flat and skin renderers are controlled by two configuration options
respectively. The following table shows the options and the corresponding
macros.

##### Table: Options and macros related to appearance renderers

| Switch option | Macro            | Default | Comments
| --------------|------------------|---------|-----------
| `flatlf`      | `_MGLF_RDR_FLAT` | Enabled | Simple flat style
| `skinlf`      | `_MGLF_RDR_SKIN` | Enabled | Skin style, window and control decorated by using bitmaps

### Control

MiniGUI provides configuration options for all basic controls. The
basic controls are the controls contained in the MiniGUI Core
library. The table below shows the options and macros for
the basic controls.

##### Table: Options and macros for basic controls

| Switch option    | Macro                 | Default  | Comments
| -----------------|-----------------------|----------|---------
| `ctrlstatic`     | `_MGCTRL_STATIC`      | Enabled  | Include STATIC control
| `ctrlbutton`     | `_MGCTRL_BUTTON`      | Enabled  | Include BUTTON control
| `ctrlsledit`     | `_MGCTRL_SLEDIT`      | Enabled  | Include SLEDIT (single line edit) control
| `ctrlbidiedit`   | `_MGCTRL_BIDIEDIT`    | Disabled | Include BIDI EDIT control; Deprecated
| `newtextedit`    | `_MGCTRL_TEXTEDIT`    | Enabled  | Include new TEXTEDIT control
| `ctrllistbox`    | `_MGCTRL_LISTBOX`     | Enabled  | Include LISTBOX control
| `ctrlpgbar`      | `_MGCTRL_PROGRESSBAR` | Enabled  | Include PROGRESSBAR control
| `ctrlcombobox`   | `_MGCTRL_COMBOBOX`    | Enabled  | Include COMBOBOX control
| `ctrlpropsheet`  | `_MGCTRL_PROPSHEET`   | Enabled  | Include MENUBUTTON control
| `ctrltrackbar`   | `_MGCTRL_TRACKBAR`    | Disabled | Include TRACKBARcontrol
| `ctrlscrollbar`  | `_MGCTRL_SCROLLBAR`   | Disabled | Include SCROLLBAR control
| `ctrlnewtoolbar` | `_MGCTRL_NEWTOOLBAR`  | Disabled | Include NEWTOOLBAR control
| `ctrlmenubtn`    | `_MGCTRL_MENUBUTTON`  | Disabled | Include MENUBUTTON control
| `ctrlscrollview` | `_MGCTRL_SCROLLVIEW`  | Disabled | Include SCROLLVIEW control
| `ctrltextedit`   | `_MGCTRL_TEXTEDIT`    | Disabled | Include old TEXTEDIT control
| `ctrlmonthcal`   | `_MGCTRL_MONTHCAL`    | Disabled | Include MONTHCALENDAR control
| `ctrltreeview`   | `_MGCTRL_TREEVIEW`    | Disabled | Include TREEVIEW control
| `ctrlspinbox`    | `_MGCTRL_SPINBOX`     | Disabled | Include SPINBOX control
| `ctrlcoolbar`    | `_MGCTRL_COOLBAR`     | Disabled | Include COOLBAR control
| `ctrllistview`   | `_MGCTRL_LISTVIEW`    | Disabled | Include LISTVIEW control
| `ctrliconview`   | `_MGCTRL_ICONVIEW`    | Disabled | Include ICONVIEW control
| `ctrlgridview`   | `_MGCTRL_GRIDVIEW`    | Disabled | Include GRIDVIEW control
| `ctrlanimation`  | `_MGCTRL_ANIMATION`   | Enabled  | Include ANIMATION control and support for GIF89a files

**Since MiniGUI 3.0, we provide a new set of controls through the
mGNCS component. The new control set is well-designed and elegantly
interfaced, it can completely replace the basic control set.
Therefore, we strongly suggest that new MiniGUI applications
developed use mGNCS instead of MiniGUI built-in basic controls.
Because there is a better mGNCS, most of the basic controls
are disabled by default. If your application uses these controls, please
enable them by yourself.**

### Others

You must define the macro `__MINIGUI_LIB__` when you
use your own makefiles or building environment to build MiniGUI
Core library. MiniGUI components also need such macros. The table below
shows the macros must defined for MiniGUI Core and components when compiling
them.

##### Table: Macros must be defined to compile MiniGUI Core and components

| Component     | Macro
|---------------|-----------------
| MiniGUI Core  | `__MINIGUI_LIB__`
| mGUtils       | `__MGUTILS_LIB__`
| mGEff         | `__MGEFF_LIB__`
| mGPlus        | `__MGPLUS_LIB__`
| mGNCS         | `__MGNCS_LIB__`
| mGNCS4Touch   | `__MGNCS4TOUCH_LIB__`

Since MiniGUI 3.0, you can specify a suffix for MiniGUI library name
through a configure option. By default, the name of the
MiniGUI library varies depending on the runtime mode, for example,
`libminigui-ths.so`, `libminigui-procs.so`, and `libminigui-sa.so`
for `MiniGUI-Threads`, `MiniGUI-Processes`, and `MiniGUI-Standalone` respectively.
You can specify a specific library name suffix with the option `--with-libsuffix`.

Moreover, in order to support some small embedded real-time operating systems,
We have implemented some standard C functions:

1. `malloc` function family, including `malloc`, `calloc`, and `free`.
1. stdio format input and output functions, such as `printf`, `sprintf`,
`vsprintf`, and so on.
1. POSIX thread functions, such as `pthread_create`, `sem_post`,
and so on.

By default, the configuration options for these functions are disabled.
If you want to enable these functions for some operating systems, you
can enable these options. The table below lists the configuration options
and corresponding macros related to these functions.

##### Table: Options and macros for own implementation of standard C functions

| Switch option | Macro                | Default  | Comments
|---------------|----------------------|----------|---------
| `ownmalloc`   | `_MGUSE_OWN_MALLOC`  | Disabled | Use `malloc` function family implemented by MiniGUI
| `ownstdio`    | `_MGUSE_OWN_STDIO`   | Disabled | Use stdio format input and output functions implemented by MiniGUI
| `ownpthread`  | `_MGUSE_OWN_PTHREAD` | Disabled | Use POSIX thread functions implemented by MiniGUI; Only for uC/OS-II, VxWorks, ThreadX, pSOS, and Nucleus

## Minimal Configuration Options

In this section, we will give an example of minimum configuration
options in MiniGUI.

There is a `buildlib-min` script in the `build/` directory of MiniGUI
source tree:

```bash
#!/bin/sh

./configure \
    --with-runmode=ths \
    --with-ttfsupport=none \
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
    --disable-latin9support   \
    --disable-gbsupport       \
    --disable-gbksupport      \
    --disable-unicodesupport  \
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

Using this script, you can configure MiniGUI to the minimal function
library that only supports ISO8859-1 charset:

- Compiling MiniGUI to be MiniGUI-Threads.
- No support for double click.
- No support for cursor.
- No support for mouse calibration.
- No support for clipboard.
- No incore VGAOEM/Terminal fonts.
- No support for VBF font.
- No support for Qt Prerendered Font (QPF).
- No support for UPF Prerendered Font (UPF).
- No support for TrueType font.
- No support bitmap font.
- No support for Latin 9(ISO-8859-15, West Extended) charset.
- No support for EUC GB2312 charset.
- No support for GBK charset.
- No support for BIG5 charset.
- No support for UNICODE (ISO-10646-1 and UTF-8).
- No support for BITMAP saving function.
- No support for JPG image format.
- No support for PNG image format.
- No support for GIF image format.
- No including “About MiniGUI” dialog box.
- No support for advanced 2D graphics APIs
- No include new TEXTEDIT support.
- No building the console engine subdriver for PS2 mouse.
- No building the console engine subdriver for IntelligentMouse (IMPS/2).
- No building the console engine subdriver for old MS serial mouse.
- No building the console engine subdriver for MS3 mouse.
- No building the console engine subdriver for GPM daemon.
- No support for Skin and Flat renderer.

Based on the configuration above, you can also delete some functions if
you want. For example, if you do not use the animation control in your
application, you can add `--disable-ctrlanimation` option in the
configuration script above, so there is no GIF animation control in
your compiled functions library.

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

[Showing Text in Complex or Mixed Scripts]: https://github.com/VincentWei/minigui/wiki/Showing-Text-in-Complex-or-Mixed-Scripts
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
