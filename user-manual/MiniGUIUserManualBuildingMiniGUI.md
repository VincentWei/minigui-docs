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
require a complete support for windowing and controls/widgets, even need
to run a HTML5 web browser. Therefore, an embedded graphics system like
MiniGUI must be tailorable.

For easy tailoring, MiniGUI provides a lot of compile-time
macros to control the features of itself.

Generally, we can configure MiniGUI Core in the following aspects:

- The operating system and the target board on which MiniGUI runs.
- The MiniGUI runtime mode: MiniGUI-Threads, MiniGUI-Processes, or MiniGUI-Standalone.
- The graphics engine and the input engine, as well as the options of these engines.
- The font types supported.
- The character sets supported.
- The image file formats supported: MS Windows BMP, GIF, JPEG, and PNG.
- The controls/widgets supported.
- The look-and-feel renderers supported.

In this part, we will show you the compile-time configuration options
of MiniGUI Core and the ways to configure it, in order that you can build
a most suitable MiniGUI for your target devices. We will also show you how
to build MiniGUI Core.

## Configuration Header File

A file named `mgconfig.h.in` is located in the root directory of
the source tree of MiniGUI Core. There are many C language macros
listed in the file, but they are all undefined:

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

When a C compiler builds MiniGUI from source code, the MiniGUI source code
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

The code above is a snippet of a real `mgconfig.h`. Macro `__VXWORKS__` is
defined in this file and this macro will enable the support code for VxWorks
in the MiniGUI source code. Macro `_MGHAVE_CLIPBOARD` is defined in this
file too, it will enable the support for clipboard. Macro `_MGIAL_AUTO`
is not defined (commented out) in this file and MiniGUI will not support
the `auto` input engine.

`mgconfig.h` contains many MiniGUI macros (with prefix `_MG`).
For detailed description of the MiniGUI macros,
please refer to [Compile-time Configuration].

It is very hard to modify `mgconfig.h` manually to meet your needs.
Fortunately, with GNU GCC toolchain, you can use script `configure` to configure MiniGUI and generate `mgconfig.h` file automatically.

Note that you must rebuild MiniGUI if this header file is modified.
Once MiniGUI is built, you should install the MiniGUI headers and
`mgconfig.h` to your system's header file directory.

## Configuring MiniGUI in GNU Environment

It’s known that we can conveniently maintain the program package using
makefile. By using makefile, we can easily compile and install
the function libraries, executable files, and header files into systems.

Although it is possible to organize a big project with makefile,
it is not an easy job to create such a makefile
manually. When we need to maintain a large-scale source code directory
tree, the makefile maintenance work will increase greatly. Therefore, the
Free Software Foundation's GNU project has developed the
autoconf/automake tool for software projects which are based on C and C++ languages. Using this tool, we can automatically generate 
makefiles, and can check system configuration information, which helps
enhancement the customizability of the software.

MiniGUI (MiniGUI Core, components, and sample packages) uses GNU
automake/autoconf to organize source code. Therefore, if you use
the GNU GCC toolchain for your target system, you may use MiniGUI’s
automake/autoconf configuration script to configure MiniGUI and generate
makefiles.

We know many embedded system vendors are now using the GNU GCC toolchain,
which can easily run on a Linux system. Therefore, we can configure
and build MiniGUI on a Linux system for your target system.

If you get MiniGUI source code from the tarball (`libminigui-x.y.z.tar.gz`),
there will be a ready-to-use `configure` script. Run this script with some options,
MiniGUI will be configured. Then, run `make` command to build
MiniGUI:

    $ ./configure && make;

If you fetch MiniGUI source code from a public Git repository, there is 
no such a ready-to-use `configure` script. Under this situation, you need to
make sure have `autoconf` installed in your system, and run `autogen.sh`
script to generate `configure` script:

    $ ./autogen.sh

You can also run the above commands in Cygwin environment on
MS Windows platform. For more information on Cygwin, please refer to:

<https://www.cygwin.com/>

If you run `configure` script, it will generate not only makefile, but
also `mgconfig.h` file base on the options of the configuration script.
Afterwards, you just need to run `make` and `make install` commands to compile
MiniGUI, and MiniGUI library and header files will be installed into
the system's default directory or one directory which is specified by
an option.

There are lot of options defined by MiniGUI `configure` script, each
corresponding to a macro in `mgconfig.h`. If
you enable an option when running `configure` script, the
corresponding macro will be defined; otherwise the macro is undefined.

You can run the following command to list all options supported by the `configure`
script:

```
$ ./configure --help
```

You will obtain the whole options detailed list. For instance, supposing
you use Ubuntu Linux 18.04 LTS as your development environment, the
command runs in the MiniGUI source code directory and the out is 
as following (may be different on other Linux distributions):

```
'configure' configures libminigui 3.2.2 to adapt to many kinds of systems.

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

By using the options listed above, we can
tailor the features of MiniGUI easily. For example:

```
$ ./configure --with-runmode=sa --enable-incoreres
```

The command above will configure MiniGUI to MiniGUI-Standalone runtime
mode, and use the incore resource.

Another example, if you run:

```
$ ./configure --disable-cursor --disable-screensaver
```

Your MiniGUI version will lack support for cursor and screen saver function.

We implement all of the configuration options of MiniGUI based on
`--disable-FEATURE` and `--enable-FEATURE`. While MiniGUI `configure`
script also provides `--with-configuration` option, you can use this
option to choose one from multiple options. For example,
you can use `--with-osname=ecos` option to specify the
operating system on which MiniGUI runs.

For detailed description of the options, please refer to
[Compile-time Configuration].

If you run `configure` script without any option, it will generate
makefiles and `mgconfig.h` file with default configuration options.

Each compile-time configuration option provides a default setting in
its explanation: `<default=yes>` (the compile-time configuration option
is enabled by default) or `<default=no>` (the compile-time configuration
option is disabled by default).

Besides the configuration options defined by MiniGUI, the `configure`
script also provides some important general options for compile-time configuration.

### Prefix Option

This compile-time configuration option specifies where the MiniGUI library is
installed. The default installation path is `/usr/local`. If you run:

```
$ ./configure --prefix=/home/test
```

After executing `make install`, the function library, the header
files and the reference documents will be installed in `/home/test/lib`,
`/home/test/include`, and `/home/test/man` respectively.

#### Cross Compiling Options

The compile-time configuration options `--build`, `--host` and
`--target` are very important for cross compilation.

For example, if you use the `arm-linux-gcc` cross compiling toolchain,
you need to correctly specify `--build` option, which lets `configure`
script generate makefile suitable for cross compilation for ARM:

```
$ CC=arm-linux-gcc ./configure
    --prefix=/usr/local/arm/2.95.3/arm-linux/ \
    --build=i386-linux \
    --host=arm-unknown-linux \
    --target=arm-unknown-linux
```

Once you have configured MiniGUI using the command above, you can run
`make` command to cross-build MiniGUI for your target system. Under this
situation, the C source files will be compiled using `arm-linux-gcc`
command instead of the default `gcc` command in your system.

In above command, the `--prefix` option is used to set the installation
directory’s prefix. After cross-building MiniGUI, when you execute
`make install` command, the runtime configuration file, the library file
and header files will be installed in the following directories respectively.

- `/usr/local/arm/2.95/arm-linux/etc/`
- `/usr/local/arm/2.95.3/arm-linux/lib/`
- `/usr/local/arm/2.95.3/arm-linux/include/`

#### --enable-static and --enable-shared

These two configuration options control whether generating static function
libraries or dynamic function libraries. If you do not need to generate
static libraries, then you may use the `--disable-static` configuration
option, it will take less time to compile the libraries than default.

## Configuring MiniGUI in Non-GNU Environment

For some traditional embedded operating systems supported by
MiniGUI, the user can usually use Integrated Development Environments
running on MS Windows, such as Tornado, ADS, etc. Because these
environments do not provide the toolchain that is GNU compatible,
we are unable to use the configuration script to generate makefile
and `mgconfig.h` file automatically.

Under this situation, you need to revise the `mgconfig.h` file
manually for the compile-time configuration. Fortunately, FMSoft
has already prepared a basic `mgconfig.h` file for these operating systems
in `build/` directory of MiniGUI source tree. For example, the file
`config-vxworks-i386.h` in this directory can be used for VxWorks
operating system running on i386.

As an alternative way, you can use the `autoconf` configuration script
on Linux or Cygwin on MS Windows to generate a `mgconfig.h` file
automatically for your target operating system. For example:

```
$ ./configure --with-osname=vxworks --with-targetname=vxi386 --with-runmode=ths --enable-incoreres
```

The command above will generate a `mgconfig.h` for VxWorks operating system.
Note that this file is not the final version, but it can be used as
a good starting point for your target system. The following code shows some
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

Once you get a suitable `mgconfig.h` file for your target system,
you can use `makefile.ng` makefiles shipped with MiniGUI source tree
to build the MiniGUI library.

For more information, please refer to
[Building MiniGUI in Non-GNU environment](#building-minigui-in-non-gnu-environment).

## Building MiniGUI in GNU Environment

Before building MiniGUI, you need to install the dependent libraries
required by MiniGUI first. MiniGUI uses `librreetype, libpng,
libjpeg, libz` and some other third-party libraries.

These dependent library source code packages basically use GNU
automake/autoconf scripts to organize projects and compile/install
these libraries by specifying specific environment variables and certain
options when running `./configure` commands. You can also check the
acceptable options for each configuration script by running 
`./configure --help` in the source tree directory.

Currently, these dependencies have standard software packages on
Linux distributions (such as Ubuntu, or RedHat). Therefore,
if you want to develop MiniGUI apps on a Linux system, you can
directly install these software packages. For example, on Ubuntu Linux 16.04,
the development packages for `librreetype, libpng, libjpeg` can be installed by
executing the following command:

    $ sudo apt-get install libfreetype6-dev libpng12-dev libjpeg-dev

This section describes the basic commands to compile the dependent libraries
from source code.

### LibFreeType

The FreeType Library is an open sourced, high quality, and portable font
engine which provides a unified interface for accessing a variety of font
format files including TrueType, OpenType, Type1, CID, CFF, MS Windows
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

The FreeType 2 library and header files will be installed into `/usr/local`
directory.

### LibJPEG, LibPNG, and LibZ

To support various image formats, MiniGUI uses LibJPEG for JPEG images,
LibPNG for PNG images. The support for Windows BMP and GIF is self-contained,
it does not need a third-party library.

Like the FreeType library, these libraries are also included in
common Linux distributions.

To support PNG images, we first install the LibZ library. The LibZ library
provides compression and decompression functions using the Z algorithm,
while the PNG image format uses the same algorithm.

Download and unzip LibZ library source code package, enter into
the top directory of the source tree, and execute the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

The LibZ library and the header files will be installed into `/usr/local`
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
be installed into the `/usr/local` directory.

### gvfb

`gvfb` is a virtual frame buffer graphics engine. Developers use `gvfb` on
a PC as the display device of MiniGUI. In this way, we can easily
develop MiniGUI app on a Linux system.

The default virtual frame buffer graphics engine in MiniGUI 3.0 or later
is `pc_xvfb`. The graphics engine defines a virtual frame buffer
(XVFB) specification that does not depend on a specific implementation.
Under this specification, we can use the gvfb program on Linux (based on
Gtk+ 2), or use the `qvfb2` program (based on Qt) to display
the output of MiniGUI and its apps in the window of gvfb or qvfb2.

To compile and install `gvfb`, make sure that you have installed Gtk+ 2.0
development packages. With Ubuntu Linux, use the following command to
install the appropriate development packages:

    $ sudo apt-get install libgtk2.0-dev

Then enter the top directory of `gvfb` source tree, run the following commands:

    $ ./configure --prefix=/usr/local
    $ make
    $ sudo make install

### MiniGUI Core

Once MiniGUI is configured successfully, you execute `make` command at
the top directory of MiniGUI source tree to build MiniGUI:

```
$ make
```

This command will do the default building work. But you can also specify
a different target to run `make` command to do other building work, for example,

```
$ make clean
```

This will remove previously generated object files or libraries.

There are several predefined targets in the makefile generated by
`configure` script. The frequently-used targets are listed as follow:

- `make all` or `make`: The default building process: compile the source code,
   then link object files to generate the library or the executable files.
- `make clean`: Clean object files.
- `make install`: Install the executables, libraries, header files, and so on
   to the installation directory.
- `make uninstall`: Uninstall the executables, libraries, header files, and so on
   from the system.

Therefore, you genenrally use the following commands to configure, build,
and install MiniGUI:

```
$ ./configure
$ make
$ sudo make install
```

You can also use `configure` script to specify a cross-compiling options
and the prefix of installation directories.

### MiniGUI resource

MiniGUI resource package (`minigui-res`) is also organized by GNU
autoconf/automake script, so just run the following command to install:

```
$ ./configure
$ make
$ sudo make install
```

Similarly, you can also specify the installation path using the `--prefix`
option.

### MiniGUI components

After building MiniGUI Core, it is very straightforward to building MiniGUI
components, because they use the same way to organize the source code, and
there are a few configuration options.

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

After compiling and installing MiniGUI Core and components according to
the above steps, you can compile and run the sample in `mg-samples`.

By default, MiniGUI will use the `pc_xvfb` graphics and input engine,
and the actual virtual frame buffer program is `gvfb`.

Run the following commands to configure and compile the `mg-samples` code
package:

```
$ sudo ldconfig
$ ./configure
$ make
```

The first command will refresh the Linux system dynamic library cache
system. By default MiniGUI dynamic libraries are installed in
the `/usr/local/lib` directory, the system uses a cache to maintain a list
of all the dynamic libraries installed in the system. If the cache is
not refreshed, the system may complain no dynamic library found.

To run the demo in MiniGUI-Processes runtime mode, you need to start the
`mginit` program first and then run other sample programs. The
following commands give the process of running a game (`same`) in
MiniGUI-Processes mode:

```
$ cd mginit
$ ./mginit &
$ cd ../same
$ ./same
```

On MiniGUI-Threads runtime mode, you can directly run a sample.
Here's how to run the game `same`:

```
$ cd same
$ ./same
```

In the same way, you can build and run `mguxdemo` (`cell-phone-ux-demo`) and
`mg-demos` easily.

### Building MiniGUI in Non-GNU Environment

In a Non-GNU development environment (generally, a toolchain runs on MS Windows),
you can organize the source code files of MiniGUI Core and components
as one project (or multiple projects) in the Integration Development Environment
(for example, Tornado or ADS) to compile them. Before compiling, you
should make sure that there is a correct `mgconfig.h` header file for your
target system. For more information, please refer to
[Configuration Header File](#configuration-header-file).

But we recommend that you use Cygwin to build and install MiniGUI Core
and components on MS Windows. In theory, this method is suitable to any
development environment which runs on MS Windows. Therefore, we give a detailed
description on this method in this section.

Cygwin is a large collection of GNU and open source tools which provide
functionality similar to a Linux distribution on MS Windows.
You can download Cygwin from <https://www.cygwin.com/>.

After installing Cygwin on MS Windows, you can execute many
GNU and open source tools. For example, BASH scripts,
VIM editor, PERL script interpreter, make tool, gcc compiler, and so on.
Please make sure you have selected to install these packages
when you install Cygwin.

Note that in Cygwin environment, you can also execute MS Windows commands
like the building toolchain of your target system.
Thus, if you write makefiles for MiniGUI according to the GNU rules and
use make tool of Cygwin to execute the corresponding compiler and linker,
you can compile, link, and generate MiniGUI libraries easily for the
target system.

In order to compile MiniGUI conveniently in Cygwin, we provide a
separate set of makefiles with a postfix `.ng` in MiniGUI Core. Here
the postfix `ng` means `non-GNU`.

In the top directory, there is a file named `rules.make`. This file
defines the global rules for `makefile.ng`, and you need to define a
correct `TARGET_RULES` variable for your target system.

By default, `TARGET_RULES` variable is defined as:

```makefile
TARGET_RULES=build/rules-pc.linux
```
And the content of `build/rules-pc.linux` is as follow:

```makefile
# rules for pc-linux

# set your own targaet_os
TARGET_OS=linux

##################################################
# set your compile tool #
CC=gcc
CXX=g++
CPP=g++
AR=ar
AS=as
RANLIB=ranlib
MAKE=/usr/bin/make
##################################################

ARFLAGS=-rc
COFLAG=-c

OBJ=o
LIBA=a

##################################################
# set your compile flags and install prefix path # 
PREFIX=/usr/local
CFLAGS+=-g -Wall -fPIC `pkg-config --cflags freetype2`
LDFLAGS+=
##################################################
```

Note that this makefile.ng can work on Linux; we can compile
MiniGUI Core using the following commands on Linux:

```
$ ./configure
$ make -f makefile.ng
```

The first command generates `mgconfig.h` for Linux, and the
second command compiles MiniGUI Core.

Also note that makefile.ng will only build static library.

For easy usage, we have provided some ready-to-use rules files
for different target systems in `build/` directory. There are
also configuration header files for such systems.

For example, assume that you use VxWorks toolchain on MS Windows:

- `build/rules-pc.vxworks`: the rules for VxWorks on i386 target.
- `build/config-vxworks-i386.h`: the configuration header file for VxWorks on i386 target.

First, you copy the header files into the top directory and
overwrite the default `mgconfig.h`:

    cygwin$ cp build/config-vxworks-i386.h mgconfig.h -f

Second, you modify the `rules.make` file in the top directory to
use the real rules:

```makefile
TARGET_RULES=build/rules-pc.vxworks
```

Third, you compile MiniGUI using make tool of Cygwin:

    cygwin$ /usr/bin/make –f makefile.ng

Note that `makefile.ng` supports `clean` and `install` targets.
If you execute the command as follow:

    cygwin$ /usr/bin/make –f makefile.ng install

You can install MiniGUI header files and library to the directory, which
is specified by `rules-<platform>.<os>`. If you execute the command as follow:

    cygwin$ /usr/bin/make –f makefile.ng clean

You can clean all object files generated by last make command.

**Note that if you modify `mgconfig.h` and other files in the Cygwin
environment, you should execute `make -f makefile.ng clean` to clean all
object files, then re-compile MiniGUI.**

To correctly use `makefile.ng` in Cygwin environment to compile MiniGUI,
you should make sure to prepare a correct `rules.make` file.
You must define the variables accurately in the following table.

##### The variables needed by makefile.ng

| Variants name  | Purpose                                                              |Comment |
| ---------------|----------------------------------------------------------------------|--------|
| CC             | Specify C compiler                                                   |        |
| CPP            | Specify C++ compiler                                                 |        |
| AR             | Specify archiving tool, the tool is used to generate static library  |        |
| RANLIB         | Specify static library index tool                                    |        |
| MAKE           | Specify make tool                                                    | Generally, the make tool is `/usr/bin/make` in the Cygwin environment. |
| ARFLAGS        | The option that controls the archiving tool generate static library  |        |
| COFLAG         | The option that it control the compiler to compile, but not link     |        |
| OBJ            | The suffix name of the object file                                   |        |
| LIBA           | The suffix of the static library file                                |        |
| PREFIX         | The prefix of the installation directory                             |        |
| INCS           | Specify the search directories of header file                        |        |
| CFLAGS         | The C compiler option                                                |        |

The content of `build/rules-pc.vxworks` is listed as follow:

```
# rules for pc-vxworks
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

# vxworks
TARGET_DIR=C:/Tornado2.2x86/target
INCS+=-I\${TARGET_DIR}/h
CFLAGS+=-g -mcpu=pentium -march=pentium -Wall -DTOOL_FAMILY=gnu -DTOOL=gnu -D_WRS_KERNEL -DCPU=PENTIUM
```

Note that the make tool will install MiniGUI header files to the
`$PREFIX/include/minigui` directory, and the MiniGUI Core library
will be installed into the `$PREFIX/lib/` directory. Therefore,
the `rules.make` file above will install MiniGUI header files into
`c:/cross/include/minigui` directory and MiniGUI Core library into
`c:/cross/lib` directory.

By referring to the table and the `rules.make` file above, you can
write a correct `rules.make` file based on your actually development
environment and toolchain.

Because the format of the `makefile.ng` is compatible with GNU
makefile, so we can use `makefile.ng` to compile MiniGUI in the Linux
environment, actually. This kind of circumstance usually occurs while
using cross-compiling toolchain for uClinux. If you work in Linux
environment, you can execute `make` command directly:

```
$ make -f makefile.ng
```

For MiniGUI components, you can use the same way to compile them
in non-GNU environment; we do not repeat them here.

---

[&lt;&lt; Quick Start](MiniGUIUserManualQuickStart.md) |
[Table of Contents](README.md) |
[Compile-time Configuration &gt;&gt;](MiniGUIUserManualCompiletimeConfiguration.md)

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

