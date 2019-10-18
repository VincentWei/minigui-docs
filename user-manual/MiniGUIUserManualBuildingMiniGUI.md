# Building MiniGUI

- [Introduction](#introduction)
- [Configuration Header File](#configuration-header-file)
- [Configuring MiniGUI in GNU Environment](#configuring-minigui-in-gnu-environment)
- [Configuring MiniGUI in Non-GNU Environment](#configuring-minigui-in-non-gnu-environment)
- [Building MiniGUI in GNU environment](#building-minigui-in-gnu-environment)
   * [LibFreeType](#libfreetype)
   * [LibJPEG, LibPNG, and LibZ](#libjpeg-libpng-and-libz)
   * [gvfb](#gvfb)
   * [MiniGUI core](#minigui-core)
   * [MiniGUI resource](#minigui-resource)
   * [MiniGUI components](#minigui-components)
   * [MiniGUI samples and demos](#minigui-samples-and-demos)
- [Building MiniGUI in Non-GNU environment](#building-minigui-in-non-gnu-environment)

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

`mgconfig.h` contains many MiniGUI macros (with `_MG` prefix).
For the detailed description of the MiniGUI macros,
please refer to [Compile-time Configuration].

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
a starting point for your target system. The following code shows some
key macros defined for the target system:

```cpp
...

/* Define if compile for Win32 platform */
/* #undef WIN32 */

/* MiniGUI library suffix */
#define _MGLIB_SUFFIX "ths"

/* Define if build MiniGUI-Processes */
/* #undef _MGRM_PROCESSES */

/* Define if build MiniGUI-Standalone */
/* #undef _MGRM_STANDALONE */

/* Define if build MiniGUI-Threads */
#define _MGRM_THREADS 1

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

## Building MiniGUI in GNU Environment

Before building MiniGUI, you need to install the dependent libraries
required by MiniGUI first. MiniGUI mainly uses LibFreeType, LibPNG,
LibJPEG, LibZ and other third-party dependent libraries.

These dependent library source code packages basically use the GNU
Automake/Autoconf script to organize projects and compile/install
these libraries by specifying specific environment variables and certain
options when running `./configure` commands. We can also check the
acceptable options for each configuration script by running the
`./configure --help` command in the source tree.

Currently, these dependencies have standard software packages on
Linux distributions (such as Ubuntu, or RedHat). Therefore,
if you want to develop MiniGUI apps on a Linux PC box, you can
directly install the software packages. For example, on Ubuntu Linux 16.04,
the development packages for FreeType, LibPNG, LibJPEG can be installed by
executing the following command:

    $ sudo apt-get install libfreetype6-dev libpng12-dev libjpeg-dev

This section describe the basic commands to compile the dependent libraries
based on the source code.

### LibFreeType

The FreeType Library is an open source, high quality, and portable font
engine that provides a unified interface for accessing a variety of font
format files including TrueType, OpenType, Type1, CID, CFF, Windows
FON/FNT, X11 PCF, etc. MiniGUI mainly uses the FreeType library to render
TrueType, OpenType, and Type 1 fonts.

Historically, FreeType has two major versions, one is FreeType 1,
such as FreeType v1.3.1; the other is FreeType 2, such as FreeType v2.6.2.
Currently, FreeType 1 is deprecated, so MiniGUI provides support for
FreeType 2 only.

Download the source code package of FreeType 2 from the official website
of MiniGUI or the FreeType official website and unzip it into the source
directory, then run the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

The FreeType 2 library and header files will be installed in `/usr/local`
directory.

### LibJPEG, LibPNG, and LibZ

To support various image formats, MiniGUI uses LibJPEG for JPEG images,
LibPNG for PNG images. The support for Windows BMP and GIF is self-contained,
it does not need a third-party library.

Like the FreeType library, these libraries are also included in
common Linux distributions.

To support PNG images, we first install the LibZ library. The LibZ library
provides the compression and decompression function of the Z algorithm,
while the PNG image format uses the algorithm.

Download and unzip LibZ library source code package, enter into
the top directory of the source tree, and execute the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

The LibZ library and the header files will be installed in `/usr/local`
directory.

Download and extract the LibPNG library source code, enter into the top directory
of the source tree, and execute the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

Download and extract the LibJPEG library source code, enter into the top directory
of the source tree, execute the following commands:

    $ ./configure --prefix=/usr/local --enable-shared
    $ make
    $ sudo make install

The header files, the dynamic libraries and the static libraries will
be installed to the `/usr/local` directory.

### gvfb

`gvfb` is a virtual frame buffer graphics. The developer use `gvfb` on
a PC box as the display device of MiniGUI. In this way, we can easily
develop MiniGUI app on a Linux PC box.

The default virtual frame buffer graphics engine in MiniGUI 3.0 or later
is `pc_xvfb`. The graphics engine defines a virtual frame buffer
(XVFB) specification that does not depend on a specific implementation.
Under this specification, we can use the gvfb program on Linux (based-on
Gtk+ 2), or use the `qvfb2` program (based on Qt) to display
the output of MiniGUI and its apps in the window of gvfb or qvfb2.

To compile and install `gvfb`, make sure that you have installed Gtk+ 2.0
development packages. Under Ubuntu Linux, use the following command to
install the appropriate development packages:

    $ sudo apt-get install libgtk2.0-dev

Then enter the top directory of `gvfb` source tree, run the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

### MiniGUI core

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
- `make uninstall`: Uninstall the executables, libraries, header files, and so on
   from the system.

Therefore, we commonly use the following commands to configure, build,
and install MiniGUI:

```
user$ ./configure
user$ make
user$ sudo make install
```

You can also use `configure` script to specify a cross-compiling options
and the prefix for installation directories.

### MiniGUI resource

MiniGUI resource package (`minigui-res`) is also organized by GNU
Autoconf/Automake script, so just run the following command to install:

```
user$ ./configure
user$ make
user$ sudo make install
```

Similarly, we can also specify the installation path using the `--prefix`
option.

### MiniGUI components

After building MiniGUI core, it is very straightforward to building MiniGUI
components, because they use the same way to organize the source code, and
there are few configuration options.

Here is a Bash shell script to build the MiniGUI components:

```bash
#!/bin/bash

for comp in mgutils mgplus mgeff mgncs mgncs4touch; do
    cd $comp
    ./autogen.sh; ./configure
    make;
    sudo make install
    cd ..
done
```

### MiniGUI samples and demos

After compiling and installing MiniGUI core and components according to
the above steps, you can compile and run the sample in `mg-samples`.

By default, MiniGUI will use the `pc_xvfb` graphics and input engine,
and the actual virtual frame buffer program is `gvfb`.

Run the following commands to configure and compile the `mg-samples` code
package:

```
user$ sudo ldconfig
user$ ./configure
user$ make
```

The first command will refresh the Linux system dynamic library cache
system. Because by default MiniGUI dynamic libraries are installed in
the `/usr/local/lib` directory, the system uses a cache to maintain a list
of all the dynamic libraries installed in the system. If the cache is
not refreshed, the system may complain no dynamic library found.

To run the demo in MiniGUI-Processes runtime mode, you need to start the
`mginit` program first and then run the other sample programs. The
following commands gives the process of running a game (`same`) in
MiniGUI-Processes mode:

```
user$ cd mginit
user$ ./mginit &
user$ cd ../same
user$ ./same
```

On MiniGUI-Threads runtime mode, you can directly run a sample.
Here's how to run the game `same`:

```
user$ cd same
user$ ./same
```

In same way, you can build and run `mguxdemo` (`cell-phone-ux-demo`) and
`mg-demos` easily.

### Building in Non-GNU Environment

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
