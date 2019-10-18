# Building MiniGUI

- [Introduction](#introduction)
- [Configuration Header File](#configuration-header-file)
- [Configuring MiniGUI in GNU Environment](#configuring-minigui-in-gnu-environment)
- [Configuring MiniGUI in Non-GNU Environment](#configuring-minigui-in-non-gnu-environment)
- [Compiling and Installing MiniGUI](#compiling-and-installing-minigui)
   * [Dependent libraries and tools](#dependent-libraries-and-tools)
   * [Building in GNU environment](#building-in-gnu-environment)
   * [Building in Non-GNU environment](#building-in-non-gnu-environment)
- [Building MiniGUI Components](#building-minigui-components)

## Introduction

In general, embedded systems are special systems, and they have
various requirements for different applications. For example, some
systems require a basic graphics function to show images, but others may
require a complete support for windowing and controls/widgets, even needs
to run a HTML5 web browser. Therefore, an embedded graphics system like
MiniGUI must be tailorable.

For easy tailoring MiniGUI, MiniGUI provides a lot of compile-time
macros to control the features of MiniGUI.

Generally, we can configure MiniGUI core in the following aspects:

- The operating system and the target board on which MiniGUI runs.
- The MiniGUI runtime mode: MiniGUI-Threads, MiniGUI-Processes, or MiniGUI-Standalone.
- The graphics engine and the input engine, as well as the options of these engines.
- The font types supported.
- The character sets supported.
- The image file formats supported: Windows BMP, GIF, JPEG, and PNG.
- The controls/widgets supported.
- The look-and-feel renderers supported.

In this chapter, we will show you the compile-time configuration options
of MiniGUI core and the ways to configure it, in order that you can build
a most suitable MiniGUI for your target devices. We will also show you how
to build MiniGUI core too.

## Configuration Header File

A file named `mgconfig.h.in` is located in the root directory of
the source tree of MiniGUI core. There are many C language macros
listed in the file, but there are all undefined:

```cpp
...

/* Define to 1 if using `alloca.c'. */
#undef C_ALLOCA

/* MiniGUI configure file name */
#undef ETCFILENAME

/* Define to 1 if you have `alloca', as a function or macro. */
#undef HAVE_ALLOCA

...
```

When a C compiler building MiniGUI from source code, the MiniGUI source
will include a file named `mgconfig.h`. We can tailor MiniGUI by
enabling some macros in `mgconfig.h`, while all macros supported are listed
in `mgconfig.h.in` mentioned above.

Generally, we can copy `mgconfig.h.in` to `mgconfig.h` and modify `mgconfig.h`
file manually in order to tailor MiniGUI.

In general, the content of `mgconfig.h` is as follow:

```cpp
...

/* Define if compile for VxWorks operating system */
#define __VXWORKS__ 1

/* Define if include advanced 2D graphics APIs */
#define _MGHAVE_ADV_2DAPI 1

/* Define if support Arabic charset */
/* #undef _MGCHARSET_ARABIC */

/* Define if include the 2440 IAL engine */
/* #undef _MGIAL_2440 */

/* Define if include the automatic IAL engine */
/* #undef _MGIAL_AUTO */

/* Define if support BIG5 charset */
#define _MGCHARSET_BIG5 1

/* Define if include clipboard support */
#define _MGHAVE_CLIPBOARD 1

...

```

The above code is a snippet of a real `mgconfig.h`. The macro `__VXWORKS__` is
defined in this file and this macro will enable the support code for VxWorks
in the MiniGUI source code. The macro `_MGHAVE_CLIPBOARD` is defined in this
file tool, it will enable the support for clipboard. Macro `_MGIAL_AUTO`
is not defined (commented out) in this file and MiniGUI will not support
the `auto` input engine.

It will be very hard to modify `mgconfig.h` manually to meet our needs.
Fortunately, when you use GNU GCC toolchain, you can use the `configure`
script to configure MiniGUI and generate `mgconfig.h` file automatically.

Note that you must rebuild MiniGUI if this header file is modified.
Once MiniGUI is built, you should install the MiniGUI headers and
`mgconfig.h` to your system's header file directory.

## Configuring MiniGUI in GNU Environment

It’s known that we can conveniently maintain the program package using
makefile. By using makefile, we can easily compile and install
the function libraries, executable files, and header files to system.

Although it is possible to organize a big project with makefile,
it is not an easy job to create such a makefile
manually. When we need to maintain a large-scale source code directory
tree, the makefile maintenance work will greatly increase. Therefore, the
Free Software Foundation's GNU project has developed the
Autoconf/Automake tool for many software projects which is based on the
C and C++ language. Using this tool, we can automatically generate the
makefile, and can check the system configuration information, which helps
enhancement the customizability of the software.

MiniGUI (MiniGUI core, components, and sample packages) uses the GNU
Automake/Autoconf to organize the source code. Therefore, if you use
the GNU GCC toolchain for your target system, you may use MiniGUI’s
Automake/Autoconf configuration script to configure MiniGUI and generate
the makefiles.

We know many embedded system vendors are now using the GNU GCC toolchain,
which can easily run on a Linux PC box. Therefore, we can configure
and build MiniGUI on a Linux PC box for your target system.

If you get MiniGUI source code from the tarball (`libminigui-x.y.z.tar.gz`),
there will be a ready-to-use `configure` script. Run this script with some options,
MiniGUI will be configured. After this, run `make` command to build
MiniGUI:

    $ ./configure; make;

If you fetch MiniGUI source code from a public Git repository, there will
not be a ready-to-use `configure` script. For this situation, you should
make sure have `autoconf` installed in your system, and run `autogen.sh`
script to generate `configure` script:

    $ ./autogen.sh

You can also play the above commands in Cygwin environment on
Windows platform. For more information about Cygwin, please refer to:

<https://www.cygwin.com/>

If you run `configure` script, it will generate not only makefile, but
also `mgconfig.h` file base on the options for the configuration script.
Afterwards, we just need run `make` and `make install` commands to compile
MiniGUI, and MiniGUI library and header files will be installed to
the system default directory or one directory which is specified by
using an option.

There are lot of options defined by MiniGUI configuration script, and each
option corresponds to a certain macro in `mgconfig.h`. If
you enable an option when running `configure` script, then the
correspondence macro will be defined; otherwise the macro will be undefined.

You can run the following command for all options supported by the configuration
script:

```
user$ ./configure --help
```

You can obtain the whole options detailed list. For instance, supposing
you use Ubuntu Linux 18.04 LTS as your development environment, the
command runs in the MiniGUI source code directory and the running result
as follow (this command output may be different on other Linux distribution):

```
`configure' configures libminigui 3.2.2 to adapt to many kinds of systems.

Usage: ./configure [OPTION]... [VAR=VALUE]...

To assign environment variables (e.g., CC, CFLAGS...), specify them as
VAR=VALUE.  See below for descriptions of some of the useful variables.

Defaults for the options are specified in brackets.

Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print `checking ...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for `--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or `..']

Installation directories:
  --prefix=PREFIX         install architecture-independent files in PREFIX
                          [/usr/local]
  --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                          [PREFIX]

By default, `make install' will install all the files in
`/usr/local/bin', `/usr/local/lib' etc.  You can specify
an installation prefix other than `/usr/local' using `--prefix',
for instance `--prefix=$HOME'.

For better control, use the options below.

Fine tuning of the installation directories:
  --bindir=DIR            user executables [EPREFIX/bin]
  --sbindir=DIR           system admin executables [EPREFIX/sbin]
  --libexecdir=DIR        program executables [EPREFIX/libexec]
  --sysconfdir=DIR        read-only single-machine data [PREFIX/etc]
  --sharedstatedir=DIR    modifiable architecture-independent data [PREFIX/com]
  --localstatedir=DIR     modifiable single-machine data [PREFIX/var]
  --runstatedir=DIR       modifiable per-process data [LOCALSTATEDIR/run]
  --libdir=DIR            object code libraries [EPREFIX/lib]
  --includedir=DIR        C header files [PREFIX/include]
  --oldincludedir=DIR     C header files for non-gcc [/usr/include]
  --datarootdir=DIR       read-only arch.-independent data root [PREFIX/share]
  --datadir=DIR           read-only architecture-independent data [DATAROOTDIR]
  --infodir=DIR           info documentation [DATAROOTDIR/info]
  --localedir=DIR         locale-dependent data [DATAROOTDIR/locale]
  --mandir=DIR            man documentation [DATAROOTDIR/man]
  --docdir=DIR            documentation root [DATAROOTDIR/doc/libminigui]
  --htmldir=DIR           html documentation [DOCDIR]
  --dvidir=DIR            dvi documentation [DOCDIR]
  --pdfdir=DIR            pdf documentation [DOCDIR]
  --psdir=DIR             ps documentation [DOCDIR]

Program names:
  --program-prefix=PREFIX            prepend PREFIX to installed program names
  --program-suffix=SUFFIX            append SUFFIX to installed program names
  --program-transform-name=PROGRAM   run sed PROGRAM on installed program names

System types:
  --build=BUILD     configure for building on BUILD [guessed]
  --host=HOST       cross-compile to build programs to run on HOST [BUILD]
  --target=TARGET   configure for building compilers for TARGET [HOST]

Optional Features:
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --enable-silent-rules   less verbose build output (undo: "make V=1")
  --disable-silent-rules  verbose build output (undo: "make V=0")
  --enable-shared=PKGS  build shared libraries default=yes
  --enable-static=PKGS  build static libraries default=yes
  --enable-fast-install=PKGS  optimize for fast installation default=yes
  --enable-dependency-tracking
                          do not reject slow dependency extractors
  --disable-dependency-tracking
                          speeds up one-time build
  --disable-libtool-lock  avoid locking (might break parallel builds)
  --enable-develmode       developer mode <default=no>
  --enable-detaildebug     detailed debug info <default=no>
  --enable-tracemsg        trace messages of MiniGUI <default=no>
  --enable-msgstr          include symbol name of message <default=no>
  --enable-incoreres       use incore resource instead file IO to initialize MiniGUI <default=no>
  --enable-miniguientry    use minigui_entry function in MiniGUI <default=no>
  --enable-fixedmath       include fixed math routines <default=yes>
  --enable-dblclk          mouse button can do double click <default=yes>
  --enable-cursor          include cursor support <default=yes>
  --enable-clipboard       include clipboard support <default=yes>
  --enable-ownstdio        use own implementation of stdio functions <default=no>
  --enable-ownmalloc       use own implementation of malloc functions <default=no>
  --enable-ownpthread      use own implementation of pthread functions <default=no>
  --enable-adv2dapi        include advanced 2D graphics APIs <default=yes>
  --enable-syncupdate      include implementation of SyncUpdateDC <default=yes>
  --enable-minimalgdi      build a minimal GDI library only <default=no>
  --enable-productid       insert a productid into the library file <default=no>
  --enable-splash          enable splash <default=yes>
  --enable-screensaver     enable screensaver <default=no>
  --enable-flatlf          include flat Look and Feel renderer <default=yes>
  --enable-skinlf          include skin Look and Feel renderer <default=yes>
  --enable-customial       build the customer IAL engine <default=no>
  --enable-dlcustomial     build the dlcustom IAL engine <default=no>
  --enable-netial          build the IAL engine for net <default=no>
  --enable-cisco_touchpad_ial    build the IAL engine for Cisco Touchpad <default=no>
  --enable-mstar_ial       build the IAL engine for MStar <default=no>
  --enable-ipaqh3600ial    build the IAL engine for iPAQ H3600 <default=no>
  --enable-nexusial        build the IAL engine for Nexus <default=no>
  --enable-ipaqh5400ial    build the IAL engine for iPAQ H5400 <default=no>
  --enable-tslibial        build the IAL engine for TSLIB <default=no>
  --enable-dummyial        build the Dummy IAL engine <default=yes>
  --enable-autoial         build the Automatic IAL engine <default=no>
  --enable-randomial       build the Random IAL engine <default=no>
  --enable-commial         build the COMM IAL engine <default=no>
  --enable-qvfbial         build the QVFB IAL engine <default=no>
  --enable-qemuial         build the QEMU IAL engine <default=no>
  --enable-wvfbial         build the WVFB IAL engine <default=no>
  --enable-jz4740ial       build the JZ4740 IAL engine <default=no>
  --enable-lide            build the lide IAL engine <default=no>
  --enable-2440ial         build the 2440 IAL engine <default=no>
  --enable-davinci6446ial  build the DAVINCI6446 IAL engine <default=no>
  --enable-dfbial          build the DFB IAL engine <default=no>
  --enable-consoleial      build the console (Linux console) IAL engine <default=yes>
  --enable-consoleps2      build the console engine subdriver for PS2 mouse <default=yes>
  --enable-consoleimps2    build the console engine subdriver for IntelligentMouse (IMPS/2) mouse <default=yes>
  --enable-consolems       build the console engine subdirver for old MS serial mouse <default=yes>
  --enable-consolems3      build the console engine subdirver for MS3 mouse <default=yes>
  --enable-consolegpm      build the console engine subdirver for GPM daemon <default=no>
  --enable-textmode        Linux system have console (text mode) on FrameBuffer <default=yes>
  --enable-rbfsupport      include raw bitmap font support <default=yes>
  --enable-rbfvgaoem       include incore RBF font of ISO8859-1 VGAOEM (8x8) font <default=yes>
  --enable-rbfterminal     include incore RBF font of ISO8859-1 Terminal (8x12) font <default=yes>
  --enable-rbffixedsys     include incore RBF font of ISO8859-1 FixedSys (8x15) font <default=yes>
  --enable-vbfsupport      include var bitmap font support <default=yes>
  --enable-fontsserif      include incore font SansSerif (11x13) <default=yes>
  --enable-fontcourier     include incore font Courier (8x13) <default=yes>
  --enable-fontsystem      include incore font System (14x16) <default=yes>
  --enable-upfsupport      build support for FMSoft Unicode Prerendered Font (UPF) <default=yes>
  --enable-fonttimes       include incore Times UPF fonts (12x10 and 17x14) <default=yes>
  --enable-qpfsupport      build support for Qt Prerendered Font (QPF) <default=no>
  --enable-sefsupport      build support for koxomo scripteasy (SEF) <default=no>
  --enable-ttfcache        include ttf cache support <default=no>
  --enable-bmpfsupport     build support for Bitmap Font (bmpf) <default=yes>
  --enable-latin2support   include East European (Latin 2, ISO8859-2) charset support <default=no>
  --enable-latin3support   include South European (Latin 3, ISO8859-3) charset support <default=no>
  --enable-latin4support   include North European (Latin 4, ISO8859-4) charset support <default=no>
  --enable-cyrillicsupport include Cyrillic (ISO8859-5) charset support <default=no>
  --enable-arabicsupport   include Arabic (ISO8859-6) charset support <default=no>
  --enable-greeksupport    include Greek (ISO8859-7) charset support <default=no>
  --enable-hebrewsupport   include Hebrew (ISO8859-8) charset support <default=no>
  --enable-latin5support   include Turkish (Latin 5, ISO8859-9) charset support <default=no>
  --enable-latin6support   include Nordic, Latin 6, ISO8859-10) charset support <default=no>
  --enable-thaisupport     include Thai (ISO8859-11) charset support <default=yes>
  --enable-latin7support   include Latin 7 (ISO8859-13) charset support <default=no>
  --enable-latin8support   include Latin 8 (ISO8859-14) charset support <default=no>
  --enable-latin9support   include Latin 9 (ISO8859-15, West Extended) charset support <default=yes>
  --enable-latin10support  include Latin 10 (ISO8859-16, Romanian) charset support <default=no>
  --enable-gbsupport       include EUC encoding of GB2312 charset support <default=yes>
  --enable-gbksupport      include GBK charset support <default=yes>
  --enable-gb18030support  include GB18030-0 charset support <default=no>
  --enable-big5support     include BIG5 charset support <default=no>
  --enable-euckrsupport    include support for EUC encoding of KSC5636 and KSC5601 charsets <default=no>
  --enable-eucjpsupport    include support for EUC encoding of JISX0201 and JISX0208 charsets <default=no>
  --enable-shiftjissupport include support for Shift-JIS encoding of JISX0201 and JISX0208 charsets <default=no>
  --enable-unicodesupport  include UNICODE (ISO-10646-1 and UTF-8 encoding) support <default=yes>
  --enable-kbdhebrewpc     include keyboard layout for Hebrew PC keyboard <default=no>
  --enable-kbdarabicpc     include keyboard layout for Arabic PC keyboard <default=no>
  --enable-kbdfrpc         include keyboard layout for French PC keyboard (non-US 102 keys) <default=no>
  --enable-kbdfr           include keyboard layout for French <default=no>
  --enable-kbdde           include keyboard layout for German <default=no>
  --enable-kbddelatin1     include keyboard layout for German Latin1 <default=no>
  --enable-kbdit           include keyboard layout for Italian <default=no>
  --enable-kbdes           include keyboard layout for Spanish <default=no>
  --enable-kbdescp850      include keyboard layout for Spanish CP850 <default=no>
  --enable-savebitmap      include SaveBitmap-related functions <default=yes>
  --enable-pcxsupport      include PCX file support <default=no>
  --enable-lbmsupport      include LBM/PBM file support <default=no>
  --enable-tgasupport      include TGA file support <default=no>
  --enable-gifsupport      include GIF file support <default=yes>
  --enable-jpgsupport      include JPG file support <default=yes>
  --enable-pngsupport      include PNG file support <default=yes>
  --enable-menu            include menu support <default=yes>
  --enable-mousecalibrate  include code doing mouse calibration <default=yes>
  --enable-aboutdlg        include About Dialog Box <default=yes>
  --enable-savescreen      include code for screenshots <default=yes>
  --enable-ctrlstatic      include STATIC control <default=yes>
  --enable-ctrlbutton      include BUTTON control <default=yes>
  --enable-ctrlsledit      include Single-Line EDIT control <default=yes>
  --enable-ctrlbidisledit  include Single-Line BIDI EDIT control <default=no>
  --enable-ctrlnewtextedit include the new implementation of TEXTEDIT control <default=yes>
  --enable-ctrllistbox     include LISTBOX control <default=yes>
  --enable-ctrlpgbar       include PROGRESSBAR control <default=yes>
  --enable-ctrlcombobox    include COMBOBOX control <default=yes>
  --enable-ctrlpropsheet   include PROPSHEET control <default=yes>
  --enable-ctrltrackbar    include TRACKBAR control <default=no>
  --enable-ctrlscrollbar   include SCROLLBAR control <default=no>
  --enable-ctrlnewtoolbar  include NEWTOOLBAR control <default=yes>
  --enable-ctrlmenubtn     include MENUBUTTON control <default=yes>
  --enable-ctrlscrollview  include SCROLLVIEW and SCROLLWINDOW controls <default=no>
  --enable-ctrltextedit    include old TEXTEDIT control implementation <default=no>
  --enable-ctrlmonthcal    include MONTHCALENDAR control <default=no>
  --enable-ctrltreeview    include TREEVIEW control <default=no>
  --enable-ctrltreeview-rdr    include TREEVIEWRDR control using LFRDR <default=no>
  --enable-ctrlspinbox     include SPINBOX control <default=yes>
  --enable-ctrlcoolbar     include COOLBAR control <default=no>
  --enable-ctrllistview    include LISTVIEW control <default=yes>
  --enable-ctrliconview    include ICONVIEW control <default=no>
  --enable-ctrlgridview    include GRIDVIEW control (test) <default=no>
  --enable-ctrlanimation   include ANIMATION control and GIF87a/GIF89a support <default=yes>
  --enable-videodummy      include dummy NEWGAL engine <default=yes>
  --enable-videofbcon      include FrameBuffer console NEWGAL engine <default=yes>
  --enable-videoqvfb       include Qt Virtual FrameBuffer NEWGAL engine <default=yes>
  --enable-videopcxvfb     include PC Virtual FrameBuffer NEWGAL engine, such as qvfb, mvfb, gvfb or wvfb <default=yes>
  --enable-videortosxvfb   include RTOS Virtual FrameBuffer NEWGAL engine <default=no>. Please disable pcxvfb to enable rtosxvfb
  --enable-videowvfb       include Windows Virtual Frame Buffer NEWGAL engine <default=no>
  --enable-videousvfb    include NEWGAL/IAL engines for UnixSocket Virtual Frame Buffer <default=no>
  --enable-videocommlcd    include NEWGAL engine for Common LCD <default=no>
  --enable-videomlshadow   include MLShadow NEWGAL engine <default=no>
  --enable-videoshadow     include Shadow NEWGAL engine <default=no>
  --enable-videoem86gfx    include NEWGAL engine for EM86xx GFX <default=no>
  --enable-videoem85xxyuv  include NEWGAL engine for EM85xx YUV <default=no>
  --enable-videoem85xxosd  include NEWGAL engine for EM85xx OSD <default=no>
  --enable-videosvpxxosd   include SVPXXOSD NEWGAL engine <default=no>
  --enable-videobf533      include NEWGAL engine for BF533 OSD via SPI <default=no>
  --enable-videomb93493    include NEWGAL engine for mb93493 YUV FrameBuffer driver <default=no>
  --enable-videoutpmc      include NEWGAL engine for UTPMC <default=no>
  --enable-videodfb        include NEWGAL engine for DirectFB <default=no>
  --enable-videost7167     include NEWGAL engine for ST7167 on DirectFB <default=no>
  --enable-videostgfb      include NEWGAL engine for STGFB <default=no>
  --enable-videohi35xx     include Hi35xx Video  NEWGAL engine <default=no>
  --enable-videohi3560a    include Hi3560A Video  NEWGAL engine <default=no>
  --enable-videogdl        include GDL Video NEWGAL engine <default=no>
  --enable-videosigma8654  include sigma8654 NEWGAL engine <default=no>
  --enable-videomstar      include mstar NEWGAL engine <default=no>
  --enable-videocustom     include custom NEWGAL engine <default=no>
  --enable-videonexus      include nexus NEWGAL engine <default=no>
  --enable-videos3c6410    include s3c6410 NEWGAL engine <default=no>

Optional Packages:
  --with-PACKAGE[=ARG]    use PACKAGE [ARG=yes]
  --without-PACKAGE       do not use PACKAGE (same as --with-PACKAGE=no)
  --with-gnu-ld           assume the C compiler uses GNU ld default=no
  --with-pic              try to use only PIC/non-PIC objects default=use both
  --with-runmode=procs/ths/sa  the MiniGUI runtime mode <default=procs>
  --with-ttfsupport=ft1/ft2/none   How to support TrueType font (FreeType 1/FreeType 2/None) <default=none>
  --with-nexus-includedir=DIR  Where to find header files of nexus library
  --with-nexus-libdir=DIR      Where to find .so files of nexus library
  --with-libsuffix=ARG     Configure the suffix of MiniGUI library name.
  --with-osname=linux/uclinux/ecos/ucos2/swlinux/vxworks/win32/darwin/threadx/cygwin/nucleus/ose/psos
  --with-targetname=unknown/external/fmsoft/mstudio/stb810/vfanvil/vxi386/qvfb/fbcon/mx21/monaco/c33l05/bfin/vxppc/
                        S3C6410/S3C2440/S3C2410/hi3560a     Define the target board name
  --with-ttfcachesize=64/128/256/512/1024
  --with-mttfcachenum=10/20/40
  --with-ft1-includes=DIR    where the FreeType1 includes are
  --with-ft2-includes=DIR    where the FreeType2 includes are

Some influential environment variables:
  CC          C compiler command
  CFLAGS      C compiler flags
  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
              nonstandard directory <lib dir>
  LIBS        libraries to pass to the linker, e.g. -l<library>
  CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
              you have headers in a nonstandard directory <include dir>
  CPP         C preprocessor

Use these variables to override the choices made by `configure' or to help
it to find libraries and programs with nonstandard names/locations.

Report bugs to the package provider.
```

By using the options listed as the output of `configure` script, we can
tailor the features of MiniGUI easily. For example:

```
user$ ./configure --with-runmode=sa --enable-incoreres
```

The above command will configure MiniGUI to MiniGUI-Standalone runtime
mode, and use the incore resource.

As another example, if you run:

```
user$ ./configure --disable-cursor --disable-screensaver
```

Your MiniGUI version will lack of support for cursor and screen saver function.

For the detailed description of the options, please refer to
[Compile-time Configuration].

If you run `./configure` command without any option, it will generate
makefiles and `mgconfig.h` file with the default configuration options.

Each compile-time configuration option has provided a default setting in
its explanation: `<default=yes>` (the compile-time configuration option
is enabled by default) or `<default=no>` (the compile-time configuration
option is disabled by default).

Besides the configuration options defined by MiniGUI, the `configure`
script also provides some important general compile-time configuration
options.

### Prefix Option

This compile-time configuration option assigns the MiniGUI library where to
install. The default installation path is `/usr/local`. If you run:

```
user$ ./configure --prefix=/home/test
```

After executing `make install` command, the function library, the header
files and the reference documents will be installed in `/home/test/lib`,
`/home/test/include`, and `/home/test/man` directory respectively.

#### Cross Compiling Options

The compile-time configuration options `--build`, `--host` and
`--target` are very important for cross compilation.

For example, if you use the `arm-linux-gcc` cross compiling toolchain,
you should correctly specify `--build` option, which lets `configure`
script generating the makefile suitable for cross compilation for ARM:

```
user$ CC=arm-linux-gcc ./configure
    --prefix=/usr/local/arm/2.95.3/arm-linux/ \
    --build=i386-linux \
    --host=arm-unknown-linux \
    --target=arm-unknown-linux
```

Once you configured MiniGUI by using the command above, you can run
`make` command to cross-build MiniGUI for your target system. In this
situation, the C source files will be compiled by using `arm-linux-gcc`
command instead of the default `gcc` command in your system.

In above command, the `--prefix` option is used to set the installing
directory’s prefix. After cross-building MiniGUI, when you executed
`make install` command, the runtime configuration file, the library file
and header files will be installed in the following directories respectively.

- `/usr/local/arm/2.95/arm-linux/etc/`
- `/usr/local/arm/2.95.3/arm-linux/lib/`
- `/usr/local/arm/2.95.3/arm-linux/include/`

#### --enable-static and --enable-shared

These two configuration options control whether generating static function
library or dynamic function library. If you do not need to generate the
static library, then you may use the `--disable-static` configuration
option, it will take less time to compile the library than default.

## Configuring MiniGUI in Non-GNU Environment

For some traditional embedded operating system supported by
MiniGUI, the user usually can use the integrated development environment
running on Windows, such as Tornado, ADS, etc. Because these
environment does not provide the toolchain that is GNU compatible,
we are unable to use the configuration script to generate makefile
and `mgconfig.h` file automatically.

In this kind of situation, we need to revise the `mgconfig.h` file
manually for the compile-time configuration. Fortunately, FMSoft
already prepares a basic `mgconfig.h` file for these operating systems
in `build/` directory of MiniGUI source tree. For example, the file
`config-vxworks-i386.h` in this directory can be used for VxWorks
operating system running on i386.

As an alternative way, you can use the Autoconf configuration script
on Linux or Cygwin on Windows to generate a `mgconfig.h` file
automatically for your target operating system. For example:

```
user$ ./configure ./configure --with-osname=vxworks --with-targetname=vxi386 --with-runmode=ths --enable-incoreres
```

The above command will generate a `mgconfig.h` for VxWorks operating system.
Note that his file is not the ultimate version, but it can be used as
a starting point for your target system:

```cpp
...

/* Binary age of MiniGUI */
#define MINIGUI_BINARY_AGE 2

/* Interface age of MiniGUI */
#define MINIGUI_INTERFACE_AGE 0

/* Major version of MiniGUI */
#define MINIGUI_MAJOR_VERSION 3

/* Micro version of MiniGUI */
#define MINIGUI_MICRO_VERSION 2

/* Minor version of MiniGUI */
#define MINIGUI_MINOR_VERSION 2

/* Name of package */
#define PACKAGE "libminigui"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "libminigui"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libminigui 3.2.2"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libminigui"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.2.2"

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Version number of package */
#define VERSION "3.2.2"

/* Define if compile for Win32 platform */
/* #undef WIN32 */

/* Define if have math library */
#define _HAVE_MATH_LIB 1

/* Define if build MiniGUI-Processes (back-compatibility definition) */
/* #undef _LITE_VERSION */

/* Define if support Arabic charset */
/* #undef _MGCHARSET_ARABIC */

/* Define if support BIG5 charset */
/* #undef _MGCHARSET_BIG5 */

/* Define if support Cyrillic charset */
/* #undef _MGCHARSET_CYRILLIC */

/* Define if support EUCJP charset */
/* #undef _MGCHARSET_EUCJP */

/* Define if support EUCKR charset */
/* #undef _MGCHARSET_EUCKR */

/* Define if support GB2312 charset */
#define _MGCHARSET_GB 1

/* Define if support GB18030 charset */
/* #undef _MGCHARSET_GB18030 */

/* Define if support GBK charset */
#define _MGCHARSET_GBK 1

/* Define if support Greek charset */
/* #undef _MGCHARSET_GREEK */

/* Define if support Hebrew charset */
/* #undef _MGCHARSET_HEBREW */

/* Define if support Latin 10 charset */
/* #undef _MGCHARSET_LATIN10 */

/* Define if support Latin 2 charset */
/* #undef _MGCHARSET_LATIN2 */

/* Define if support Latin 3 charset */
/* #undef _MGCHARSET_LATIN3 */

/* Define if support Latin 4 charset */
/* #undef _MGCHARSET_LATIN4 */

/* Define if support Latin 5 charset */
/* #undef _MGCHARSET_LATIN5 */

/* Define if support Latin 6 charset */
/* #undef _MGCHARSET_LATIN6 */

/* Define if support Latin 7 charset */
/* #undef _MGCHARSET_LATIN7 */

/* Define if support Latin 8 charset */
/* #undef _MGCHARSET_LATIN8 */

/* Define if support Latin 9 charset */
#define _MGCHARSET_LATIN9 1

/* Define if support SHIFTJIS charset */
/* #undef _MGCHARSET_SHIFTJIS */

/* Define if support Thai charset */
/* #undef _MGCHARSET_THAI */

/* Define if support UNICODE */
#define _MGCHARSET_UNICODE 1

/* Define if include GPM mouse subdriver */
/* #undef _MGCONSOLE_GPM */

/* Define if include IMPS2 mouse subdriver */
#define _MGCONSOLE_IMPS2 1

/* Define if include MS mouse subdriver */
#define _MGCONSOLE_MS 1

/* Define if include MS3 mouse subdriver */
#define _MGCONSOLE_MS3 1

/* Define if include PS2 mouse subdriver */
#define _MGCONSOLE_PS2 1

/* Define if your Linux have text mode */
#define _MGCONSOLE_TEXTMODE 1

/* Define if include ANIMATION control */
#define _MGCTRL_ANIMATION 1

/* Define if include BIDISLEDIT control */
/* #undef _MGCTRL_BIDISLEDIT */

/* Define if include BUTTON control */
#define _MGCTRL_BUTTON 1

/* Define if include COMBOBOX control */
#define _MGCTRL_COMBOBOX 1

/* Define if include COOLBAR control */
/* #undef _MGCTRL_COOLBAR */

/* Define if include GRIDVIEW control */
/* #undef _MGCTRL_GRIDVIEW */

/* Define if include ICONVIEW control */
/* #undef _MGCTRL_ICONVIEW */

/* Define if include LISTBOX control */
#define _MGCTRL_LISTBOX 1

/* Define if include LISTVIEW control */
#define _MGCTRL_LISTVIEW 1

/* Define if include MENUBUTTON control */
#define _MGCTRL_MENUBUTTON 1

/* Define if include MONTHCALENDAR control */
/* #undef _MGCTRL_MONTHCAL */

/* Define if include NEWTOOLBAR control */
#define _MGCTRL_NEWTOOLBAR 1

/* Define if include PROGRESSBAR control */
#define _MGCTRL_PROGRESSBAR 1

/* Define if include PROPSHEET control */
#define _MGCTRL_PROPSHEET 1

/* Define if include SCROLLBAR control */
#define _MGCTRL_SCROLLBAR 1

/* Define if include SCROLLVIEW control */
#define _MGCTRL_SCROLLVIEW 1

/* Define if include SLEDIT control */
#define _MGCTRL_SLEDIT 1

/* Define if include SPINBOX control */
#define _MGCTRL_SPINBOX 1

/* Define if include STATIC control */
#define _MGCTRL_STATIC 1

/* Define if include TEXTEDIT control */
#define _MGCTRL_TEXTEDIT 1

/* Define if use new implementation of TEXTEDIT control */
#define _MGCTRL_TEXTEDIT_USE_NEW_IMPL 1

/* Define if include TRACKBAR control */
#define _MGCTRL_TRACKBAR 1

/* Define if include TREEVIEW control */
/* #undef _MGCTRL_TREEVIEW */

/* Define if include TREEVIEWRDR control */
/* #undef _MGCTRL_TREEVIEW_RDR */

/* Define if support Bitmap fonts */
#define _MGFONT_BMPF 1

/* Define if support TrueType font based on FreeType2 */
#define _MGFONT_FT2 1

/* Define if support QPF font */
/* #undef _MGFONT_QPF */

/* Define if support raw bitmap fonts */
#define _MGFONT_RBF 1

/* Define if support SEF scripteary font */
/* #undef _MGFONT_SEF */

/* Define if support TrueType font */
/* #undef _MGFONT_TTF */

/* Define if include ttf cache */
#define _MGFONT_TTF_CACHE 1

/* Define if support UPF font */
#define _MGFONT_UPF 1

/* Define if support var bitmap fonts */
#define _MGFONT_VBF 1

/* Define if include NEWGAL engine for BF533 OSD via SPI */
/* #undef _MGGAL_BF533 */

/* Define if include NEWGAL engine for Common LCD */
/* #undef _MGGAL_COMMLCD */

/* Define if include custom NEWGAL engine */
/* #undef _MGGAL_CUSTOMGAL */

/* Define if include NEWGAL engine for DirectFB */
/* #undef _MGGAL_DFB */

/* Define if include ST7167 subdriver for NEWGAL engine of DirectFB */
/* #undef _MGGAL_DFB_ST7167 */

/* Define if include dummy NEWGAL engine */
#define _MGGAL_DUMMY 1

/* Define if include NEWGAL engine for EM85xx OSD */
/* #undef _MGGAL_EM85XXOSD */

/* Define if include NEWGAL engine for EM85xx YUV */
/* #undef _MGGAL_EM85XXYUV */

/* Define if include NEWGAL engine for EM86xx GFX */
/* #undef _MGGAL_EM86GFX */

/* Define if include FrameBuffer console NEWGAL engine */
#define _MGGAL_FBCON 1

/* Define if include GDL Video NEWGAL engine */
/* #undef _MGGAL_GDL */

/* Define if include Hi35XX Video NEWGAL engine */
/* #undef _MGGAL_HI3510 */

/* Define if include Hi35XX Video NEWGAL engine */
/* #undef _MGGAL_HI3560 */

/* Define if include Hi3560A Video NEWGAL engine */
/* #undef _MGGAL_HI3560A */

/* Define if include NEWGAL engine for mb93493 YUV FrameBuffer driver */
/* #undef _MGGAL_MB93493 */

/* Define if include MLShadow NEWGAL engine */
/* #undef _MGGAL_MLSHADOW */

/* Define if include mstar NEWGAL engine */
/* #undef _MGGAL_MSTAR */

/* Define if include nexus NEWGAL engine */
/* #undef _MGGAL_NEXUS */

/* Define if include PC Virtual FrameBuffer NEWGAL engine */
#define _MGGAL_PCXVFB 1

/* Define if include Qt Virtual FrameBuffer NEWGAL engine */
/* #undef _MGGAL_QVFB */

/* Define if include RTOS Virtual FrameBuffer NEWGAL engine */
/* #undef _MGGAL_RTOSXVFB */

/* Define if include s3c6410 NEWGAL engine */
/* #undef _MGGAL_S3C6410 */

/* Define if include Shadow NEWGAL engine */
/* #undef _MGGAL_SHADOW */

/* Define if include sigma8654 NEWGAL engine */
/* #undef _MGGAL_SIGMA8654 */

/* Define if include NEWGAL engine for STGFB */
/* #undef _MGGAL_STGFB */

/* Define if include NEWGAL engine for SVPXX OSD */
/* #undef _MGGAL_SVPXXOSD */

/* Define if include NEWGAL engine for UnixSocket Virtual Frame Buffer */
/* #undef _MGGAL_USVFB */

/* Define if include NEWGAL engine for UTPMC */
/* #undef _MGGAL_UTPMC */

/* Define if include windows Virtual FrameBuffer NEWGAL engine */
/* #undef _MGGAL_WVFB */

/* Define if include advanced 2D graphics APIs */
#define _MGHAVE_ADV_2DAPI 1

/* Define if include clipboard support */
#define _MGHAVE_CLIPBOARD 1

/* Define if include cursor support */
#define _MGHAVE_CURSOR 1

/* Define if include fixed math routines */
#define _MGHAVE_FIXED_MATH 1

/* Define if support menu */
#define _MGHAVE_MENU 1

/* Define if include code for mouse calibration */
#define _MGHAVE_MOUSECALIBRATE 1

/* Define if include message string names */
/* #undef _MGHAVE_MSG_STRING */

/* Define if PCIAccess lib is available */
#define _MGHAVE_PCIACCESS 1

/* Define if trace message dispatching of MiniGUI */
/* #undef _MGHAVE_TRACE_MSG */

/* Define if include the 2440 IAL engine */
/* #undef _MGIAL_2440 */

/* Define if include the automatic IAL engine */
/* #undef _MGIAL_AUTO */

/* Define if include IAL engine for Cisco touchpad */
/* #undef _MGIAL_CISCO_TOUCHPAD */

/* Define if include the common IAL engine */
/* #undef _MGIAL_COMM */

/* Define if include console (Linux console) IAL engine */
#define _MGIAL_CONSOLE 1

/* Define if include IAL engine for customer's board */
/* #undef _MGIAL_CUSTOM */

/* Define if include the DAVINCI6446 IAL engine */
/* #undef _MGIAL_DAVINCI6446 */

/* Define if include the DFB IAL engine */
/* #undef _MGIAL_DFB */

/* Define if include dlcustom IAL engine */
/* #undef _MGIAL_DLCUSTOM */

/* Define if include the dummy IAL engine */
#define _MGIAL_DUMMY 1

/* Define if include IAL engine for iPAQ H3600 */
/* #undef _MGIAL_IPAQ_H3600 */

/* Define if include IAL engine for iPAQ H5400 */
/* #undef _MGIAL_IPAQ_H5400 */

/* Define if include the JZ4740 IAL engine */
/* #undef _MGIAL_JZ4740 */

/* Define if include the lide IAL engine */
/* #undef _MGIAL_LIDE */

/* Define if include IAL engine for MStar */
/* #undef _MGIAL_MSTAR */

/* Define if include IAL engine for net's board */
/* #undef _MGIAL_NET */

/* Define if include IAL engine for Nexus */
/* #undef _MGIAL_NEXUS */

/* Define if include the QEMU IAL engine */
/* #undef _MGIAL_QEMU */

/* Define if include the QVFB IAL engine */
/* #undef _MGIAL_QVFB */

/* Define if include the random IAL engine */
/* #undef _MGIAL_RANDOM */

/* Define if include IAL engine for TSLIB */
/* #undef _MGIAL_TSLIB */

/* Define if include IAL engine for UnixSocket Virtual Frame Buffer */
/* #undef _MGIAL_USVFB */

/* Define if include the WVFB IAL engine */
/* #undef _MGIAL_WVFB */

/* Define if support GIF bmp file format */
#define _MGIMAGE_GIF 1

/* Define if support JPEG bmp file format */
#define _MGIMAGE_JPG 1

/* Define if support LBM bmp file format */
/* #undef _MGIMAGE_LBM */

/* Define if support PCX bmp file format */
/* #undef _MGIMAGE_PCX */

/* Define if support PNG bmp file format */
/* #undef _MGIMAGE_PNG */

/* Define if support TGA bmp file format */
/* #undef _MGIMAGE_TGA */

/* Define if include in-core font: Courier */
#define _MGINCOREFONT_COURIER 1

/* Define if include in-core font: SansSerif */
#define _MGINCOREFONT_SANSSERIF 1

/* Define if include in-core font: System */
#define _MGINCOREFONT_SYSTEM 1

/* Define if include in-core UPF Times fonts */
#define _MGINCOREFONT_TIMES 1

/* Define if include in-core FixedSys RBF for ISO8859-1 */
#define _MGINCORERBF_LATIN1_FIXEDSYS 1

/* Define if include in-core Terminal RBF for ISO8859-1 */
#define _MGINCORERBF_LATIN1_TERMINAL 1

/* Define if include in-core VGAOEM RBF for ISO8859-1 */
#define _MGINCORERBF_LATIN1_VGAOEM 1

/* Define if build MiniGUI for no file I/O system (use in-core resources) */
#define _MGINCORE_RES 1

/* Define if use the Arabic PC keyboard layout */
/* #undef _MGKBDLAYOUT_ARABICPC */

/* Define if use the German keyboard layout */
/* #undef _MGKBDLAYOUT_DE */

/* Define if use the German-Latin1 keyboard layout */
/* #undef _MGKBDLAYOUT_DELATIN1 */

/* Define if use the Spanish keyboard layout */
/* #undef _MGKBDLAYOUT_ES */

/* Define if use the Spanish CP850 keyboard layout */
/* #undef _MGKBDLAYOUT_ESCP850 */

/* Define if use the French keyboard layout */
/* #undef _MGKBDLAYOUT_FR */

/* Define if use the French PC keyboard layout */
/* #undef _MGKBDLAYOUT_FRPC */

/* Define if use the Hebrew PC keyboard layout */
/* #undef _MGKBDLAYOUT_HEBREWPC */

/* Define if use the Italian keyboard layout */
/* #undef _MGKBDLAYOUT_IT */

/* Define if include flat Look and Feel */
#define _MGLF_RDR_FLAT 1

/* Define if include skin Look and Feel */
#define _MGLF_RDR_SKIN 1

/* MiniGUI library suffix */
#define _MGLIB_SUFFIX "ths"

/* Define if compile max ttf cahce number for 10 (default value) */
#define _MGMAX_TTF_CACHE 10

/* Define if include About MiniGUI Dialog Box */
#define _MGMISC_ABOUTDLG 1

/* Define if mouse button can do double click */
#define _MGMISC_DOUBLE_CLICK 1

/* Define if include SaveBitmap function */
#define _MGMISC_SAVEBITMAP 1

/* Define if include code for screenshots */
#define _MGMISC_SAVESCREEN 1

/* Define if build MiniGUI-Processes */
/* #undef _MGRM_PROCESSES */

/* Define if build MiniGUI-Standalone */
/* #undef _MGRM_STANDALONE */

/* Define if build MiniGUI-Threads */
#define _MGRM_THREADS 1

/* Define if the unit of timer is 10ms */
#define _MGTIMER_UNIT_10MS 1

/* Define if compile max ttf cahce size for 256k */
#define _MGTTF_CACHE_SIZE 256

/* Define if use own implementation of malloc functions */
/* #undef _MGUSE_OWN_MALLOC */

/* Define if use own implementation of pthread functions */
/* #undef _MGUSE_OWN_PTHREAD */

/* Define if use own implementation of stdio functions */
/* #undef _MGUSE_OWN_STDIO */

/* Define if include implementation of SyncUpdateDC */
/* #undef _MGUSE_SYNC_UPDATE */

/* Define if build the mgeff support version */
/* #undef _MG_MINIMALGDI */

/* Define if insert a productid into the library file */
/* #undef _MG_PRODUCTID */

/* Define if build MiniGUI-Standalone (back-compatibility definition) */
/* #undef _STAND_ALONE */

/* Define if use minigui_entry function in MiniGUI */
/* #undef _USE_MINIGUIENTRY */

/* Define if compile for Cygwin platform */
/* #undef __CYGWIN__ */

/* Define if compile for OpenDarwin */
/* #undef __DARWIN__ */

/* Define if compile for eCos */
/* #undef __ECOS__ */

/* Define if compile for Linux */
/* #undef __LINUX__ */

/* Define if compile for non-UNIX like OS */
#define __NOUNIX__ 1

/* Define if compile for Nucleus */
/* #undef __NUCLEUS__ */

/* Define if compile for OSE */
/* #undef __OSE__ */

/* Define if compile for pSOS */
/* #undef __PSOS__ */

/* Define for Blackfin run uClinux */
/* #undef __TARGET_BLACKFIN__ */

/* Define for EPSON C33L05 (axLinux) */
/* #undef __TARGET_C33L05__ */

/* Define for targets which use GAL and/or IAL engines and define the
   interfaces externally */
/* #undef __TARGET_EXTERNAL__ */

/* Define for FMSoft internal use */
/* #undef __TARGET_FMSOFT__ */

/* Define for Monaco ANVIL target */
/* #undef __TARGET_MONACO__ */

/* Define for FMSoft miniStudio */
/* #undef __TARGET_MSTUDIO__ */

/* Define for OSE on mx21 */
/* #undef __TARGET_MX21__ */

/* Define for VxWorks on PowerPC */
/* #undef __TARGET_PPC__ */

/* Define for Philips STB810 target */
/* #undef __TARGET_STB810__ */

/* Define for unknown target */
/* #undef __TARGET_UNKNOWN__ */

/* Define for VirualFone ANVIL target */
/* #undef __TARGET_VFANVIL__ */

/* Define for VxWorks on i386 */
#define __TARGET_VXI386__ 1

/* Define if compile for ThreadX */
/* #undef __THREADX__ */

/* Define if compile for uC/OS-II */
/* #undef __UCOSII__ */

/* Define if compile for VxWorks */
#define __VXWORKS__ 1

/* Define if compile for Winbond SWLinux */
/* #undef __WINBOND_SWLINUX__ */

/* Define if compile for uClinux */
/* #undef __uClinux__ */

...

```

The above code shows you the MiniGUI macros (with `_MG` prefix) for
your target system. For the detailed description of the MiniGUI macros,
please refer to [Compile-time Configuration].

However, you need to check the macros with `HAVE_` prefix in the file
to meet the abilities of your target system. For example, you may comment
out the following macros for most RTOSes:

```cpp

/* Define to 1 if you have `alloca', as a function or macro. */
/* #undef HAVE_ALLOCA */

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
/* #undef HAVE_ALLOCA_H */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_DIRENT_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the `getpagesize' function. */
/* undef HAVE_GETPAGESIZE */

/* Define to 1 if you have a working `mmap' system call. */
/* undef HAVE_MMAP */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

...

```

After you got a suitable `mgconfig.h` file for your target system,
you can use `makefile.ng` makefiles shipped in MiniGUI source tree
to build the MiniGUI library.

For more information, please refer to the section
[Building in Non-GNU environment](#building-in-non-gnu-environment).

## Compiling and Installing MiniGUI

### Dependent libraries and tools

Before running MiniGUI, you need to install the dependent libraries
required by MiniGUI. MiniGUI mainly uses LibFreeType, LibPNG, LibJPEG,
LibZ and other third-party dependent libraries.

These dependent library source code packages basically use the GNU
Automake/Autoconf script to organize projects and compile and install
these libraries by specifying specific environment variables and certain
options when running `./configure` commands. We can also check the
acceptable switch parameters for each configure script by running the
`./configure --help` command in these dependent source files.

Currently, these dependencies are basically standard configurations of
Linux distributions (such as Ubuntu, RedHat, etc.). However,
if you want to find these libraries while compiling MiniGUI, you need to
install these SDKs. For example, on Ubuntu Linux, FreeType 2, LibPNG,
LibJPEG development kits can be installed by executing the following
command:

This section is given below in the source code package based on the
compiler, install these dependent libraries steps, for reference only.

    $ sudo apt-get install libfreetype6-dev libpng12-dev libjpeg-dev

#### LibFreeType

The FreeType Library is an open source, high quality, and portable font
engine that provides a unified interface for accessing a variety of font
format files including TrueType, OpenType, Type1, CID, CFF, Windows FON
/ FNT, X11 PCF, etc. . MiniGUI uses the FreeType library to render
TrueType fonts. Historically, FreeType has two major versions, one is
FreeType 1, such as FreeType v1.3.1; the other is FreeType 2, such as
FreeType v2.5.2. As mentioned above, MiniGUI can choose to use TrueType
font with FreeType 1 or FreeType 2. Currently, FreeType 1 development
has been stagnant, while FreeType 2 is the mainstream. Therefore,
FreeType 2 should be given priority to support TrueType fonts if there
is no special case.

Download the source code package of FreeType 2 from the official website
of MiniGUI or the FreeType official website and unzip it into the source
directory, then run the following command:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

The FreeType 2 library and header files will be installed in /usr/local
directory.

#### LibJPEG, LibPNG, and LibZ

The library on which MiniGUI runs depends on libjpeg for JPEG images,
libpng for PNG images, and more. Like the FreeType library, these
libraries are included in common Linux distributions.

First install the LibZ library. The LibZ library provides the
compression and decompression function of the Z algorithm, while the PNG
image format uses the same compression algorithm, so before installing
and installing LibPNG, first install the LibZ library. Download and
unzip LibZ library source code package, and then enter the source root
directory, execute the following command:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

The LibZ library and header files will be installed in /usr/local
directory.

Download LibPng library source code, untied into the root directory of
the source code, execute the following command:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

Download LibJPEG library source code, untied into the root directory of
the source code, execute the following command:

    $ ./configure --prefix=/usr/local --enable-shared
    $ make
    $ sudo make install

The installation process may be prompted to create certain files, then
you need to see the directory you want to install there is no
corresponding directory, if you do not have to create your own. This
JPEG library header files, dynamic libraries and static libraries will
be installed to the /usr/local directory.

#### gvfb

The default virtual frame buffer graphics engine in MiniGUI 3.0 is
pc\_xvfb. The graphics engine defines a virtual frame buffer program
(XVFB) specification that does not depend on a specific implementation.
Under this specification, we can use the gvfb program on Linux Use Gtk+
development), or use the qvfb2 program (developed using Qt) to display
the output of MiniGUI and its application in the window of gvfb or qvfb.

gvfb is a virtual framebuffer program that is compatible with MiniGUI
3.0 XVFB specification and was developed using Gtk+ 2.0. To compile and
install gvfb, to ensure that the system has been installed Gtk+ 2.0
development kits. Under Ubuntu Linux, use the following command to
install the appropriate development kit:

    $ sudo apt-get install libgtk2.0-dev

Then enter the gvfb source code directory, run the following command:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

### Building In the GNU Environment

If you configure MiniGUI with configure script in GNU development
environment, you can compile and install MiniGUI with `make` command.

After MiniGUI is configured successfully, you execute `make` command at
the top directory of MiniGUI source tree to build MiniGUI:

```
user$ make
```

This command will do the default building work. But you can also specify
a different target to `make` command to do other building work, for example,

```
user$ make clean
```

This will remove previously generated object files or libraries.

There are several predefined targets in the makefile generated by
`configure` script. The frequently-used targets are listed as follow:

- `make all` or `make`: The default building process: compile the source code,
   then link the object files to generate the library or the executable files.
- `make clean`: Clean the object files.
- `make install`: Install the executables, libraries, header files, and so on
   to the installation directory.

Therefore, we commonly use the following commands to configure, build,
and install MiniGUI:

```
user$ ./configure
user$ make
user$ sudo make install
```

You can also use `configure` script to specify a cross-compiling options
and the prefix for installation directories.

#### Install MiniGUI Resource Package

MiniGUI resource package (`minigui-res`) is also organized by GNU
Autoconf/Automake script, so just run the following command to install:

```
user$ ./configure
user$ make
user$ sudo make install
```

Similarly, we can also specify the installation path using the --prefix
option.

#### Compile and run MiniGUI sample

After compiling and installing MiniGUI according to the above steps, you
can compile and run the sample in mg-samples. By default, MiniGUI will
use the `pc_xvfb` graphics and input engine, and the actual virtual
frame buffer program is `gvfb`.

Run the following command to configure and compile the `mg-samples` code
package:

```
user$ sudo ldconfig
user$ ./configure
user$ make
```

The first command to refresh the Linux system dynamic library cache
system. Because by default MiniGUI dynamic libraries are installed in
the `/usr/local/lib` directory, the system uses a cache to maintain a list
of all the dynamic libraries installed in the system. If the cache is
not refreshed, It may not be found installed dynamic library problem.

To run the demo in MiniGUI-Processes runtime mode, you need to start the
`mginit` program first and then run the other sample programs. The
following is the process of running the same game in MiniGUI-Processes
mode:

```
user$ cd mginit
user$ ./mginit &
user$ cd ../same
user$ ./same
```

On MiniGUI-Threads runtime mode to run the demo program, more simple,
direct run sample demo. Here's how to run the same game in thread mode:

```
user$ cd same
user$ ./same
```

### Building In Non-GNU Environment

In the Non-GNU development environment (generally, it is Windows
platform), we first organize MiniGUI source code solution for project of
special Integration Development Environment (for example, Tornado and
ADS). Secondly, we compile MiniGUI. At last, we compile MiniGUI
application.

But using Cygwin development environment for Windows platform, it is
very convenient. We can compile and install MiniGUI. In theory, this
method is applicable to any development environment, which runs on
Windows platform, so we will give detailed description on this method in
this chapter.

Cygwin is an open source software project and Linux-like environment for
Windows. After installing Cygwin on Windows, we can execute many
applications of Linux platform, for example, BASH script, VIM editor,
PERL script interpreter, make tool of Linux, gcc compiler and so on. In
the Cygwin environment, we can also call other Windows applications.
Thus, if we write makefile for MiniGUI according to GNU rules and use
make tool of Cygwin to call corresponding compiler and linker, we can
compile and generate MiniGUI functions library.

Many OSes (Operating System) development environments include Cygwin
such as OSE. If there is not Cygwin in your development environment, you
can download and install it from
[*http://www.cygwin.com*](http://www.cygwin.com). Please make sure you
have installed make tool, compiler and BASH shell script software
package and so on.

In MiniGUI source code, in order to compile MiniGUI conveniently in the
Non-GNU development environment, the following things have been done.

In order to distinguish makefile of Cygwin from GNU makefile, the GNU
makefile is generated by configure tool, the makefile of Cygwin has
**.ng** suffix (the **.ng** expresses non-GNU).

Provide template header file for special platform and operating system,
the rules of nomenclature is like config-&lt;os&gt;-&lt;platform&gt;.h.

Provide a self-compiled rule file (the name is **rules.make**). The
**rules.make** is in the MiniGUI source code top directory. In
rules.make, we need provide different TARGET\_RULES value for different
OS development environment.

Provide some spare **rules.make** files for different OS (Operating
System) development environment. We save these files to the MiniGUI
source code **build/** directory. The rules of nomenclature in these
files is like **rules-&lt;platform&gt;.&lt;os&gt;.**

Firstly, we copy build/ config-&lt;os&gt;-&lt;platform&gt;.h to MiniGUI
source code top directory, and rename it as mgconfig.h. Secondly we
modify **rules.make** file according to actual development environment.
Lastly, we compile MiniGUI using Cygwin make command. For example, we
want to compile MiniGUI for VxWorks X86 platform (rules file
corresponding with **build/rules-pc.vxworks**[^7]), we need follow the
following step:

Copy build/config-vxworks-i386.h to MiniGUI source code top directory,
and rename it as mgconfig.h (we resume that current directory is MiniGUI
source code top directory):

    cygwin$ cp build/config-vxworks-i386.h mgconfig.h

Modify TARGET\_RULES value in rules.make file:

TARGET\_RULES=build/rules-pc.vxworks

Then we compile MiniGUI using make tool of Cygwin:

    cygwin$ /usr/bin/make –f makefile.ng

Note that **makefile.ng** supports commands of clean and make. If you
execute the command as follow:

    cygwin$ /usr/bin/make –f makefile.ng install

You can install MiniGUI header files and library to the directory, which
is specified by **rules-&lt;platform&gt;.&lt;os&gt;**. If you execute
the command as the following:

    cygwin$ /usr/bin/make –f makefile.ng clean

You can clean all object files to compile afresh.

Note: if you modify `mgconfig.h` and other files in the Cygwin
environment, first of all you execute the command above to clean all
object files, then compile MiniGUI afresh.

By using Cygwin environment and **makefile.ng** to compile MiniGUI, our
main work is in editing right **rules.make** file, actually. You must
define variables accurately in the table 2.21, when you compile
**rules.make** under yourself development environment.

Table 2.21 the variables needed by makefile.ng

  Variants name   Purpose                                                               Memo
  --------------- --------------------------------------------------------------------- ---------------------------------------------------------------------
  CC              Specify C compiler                                                    
  CPP             Specify C++ compiler                                                  
  AR              Specify archiving tool, the tool is used to generate static library   
  RANLIB          Specify static library index tool                                     
  MAKE            Specify make tool                                                     Generally, the make tool is /usr/bin/make in the cygwin environment
  ARFLAGS         The option that controls the archiving tool generate static library   
  COFLAG          The option that it control the compiler to compile, but not link      
  OBJ             The suffix name of the object file                                    
  LIBA            The suffix of the static library file                                 
  PREFIX          The prefix of the installation directory                              
  INCS            Specify the search directory option of head file                      
  CFLAGS          The C compiler option                                                 

**build/rules-pc.vxworks** file was listed as follows:

```
\# rules for pc-vxworks
AS=
CC=ccpentium
CXX=c++pentium
CPP=ccpentium
AR=arpentium
RANLIB=ranlibpentium
MAKE=/usr/bin/make
ARFLAGS=crus
COFLAG=-c
OBJ=o
LIBA=a
PREFIX=c:/cross

#vxworks
TARGET\_DIR=C:/Tornado2.2x86/target
INCS+=-I\${TARGET\_DIR}/h
CFLAGS+=-g -mcpu=pentium -march=pentium -Wall -DTOOL\_FAMILY=gnu -DTOOL=gnu -D\_WRS\_KERNEL -DCPU=PENTIUM
```

Note that the make tool will install MiniGUI header files to the
**\$PREFIX/include/minigui** directory under the **makefile.ng** project
file of Cygwin, the function libraries were installed to the
**\$PREFIX/lib/** directory. The **rules.make** file above will install
MiniGUI header files to the **c:/cross/include/minigui** directory and
MiniGUI libraries to the **c:/cross/lib** directory.

Referring to table 2.21 and the **rules.make** file above, you can write
correct rules.make file based on actually development environment.

Because the format of the **makefile.ng** is compatible with GNU
makefile, so we can use **makefile.ng** to compile MiniGUI in the Linux
environment, actually. This kind of circumstance usually occurs during
using cross-compile tool chain for uClinux. If you work in the Linux
environment, you can execute make command.

```
user\$ make –f makefile.ng
```

About other contents related with portion and configuration of MiniGUI,
please refer to Chapter 18 “*GAL and IAL Engines*” and Appendix A “*A
Universal Startup API for RTOSes*” in MiniGUI Programming Guide V3.0-5.

## Building MiniGUI Components

---

[Previous Chapter](MiniGUIUserManualQuickStart.md)  
[Table of Contents](README.md)  
[Next Chapter](MiniGUIUserManualCompiletimeConfiguration.md)

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
