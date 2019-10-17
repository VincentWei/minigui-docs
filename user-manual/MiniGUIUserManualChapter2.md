# Building MiniGUI

In general, embedded systems are special systems, and they have
various requirements for different applications. For example, some
systems require a basic graphics function to show images, but others may
require a complete support for windowing and controls/widgets, even needs
a HTML5 web browser. Therefore, an embedded graphics system like MiniGUI
must be tailorable.

For easy tailoring MiniGUI, MiniGUI provides a lot of compile-time
configuration options to specify the features of MiniGUI core.

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
a most suitable MiniGUI for your target devices.

We will also show you how to build MiniGUI core too.

## Compile-time Configuration Options

A file named **mgconfig.h** is located in the root directory of
MiniGUI source code. A lot of ANSI C macros are defined in this file.
We can configure MiniGUI by enabling or disabling these macros.
Generally, we can modify this file in order to configure MiniGUI. You
must recompile MiniGUI if this file is modified. After that you should
install the header files and the libraries on your system. If your
applications are static linking to MiniGUI, you should rebuild your
applications, too. Please note that you should placed the
**mgconfig.h** in a MiniGUI header file directory which your compiler
can find it and overwrite the old one.

In general, the content of **mgconfig.h** is as follow:

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

Above produces is a piece of **mgconfig.h**. Macro \_\_VXWORKS\_\_ is
defined in this file and this macro will open the VxWorks support code
in the MiniGUI source code. Macro \_MGHAVE\_CLIPBOARD is defined in this
file, too. It will open the clipboard support code. Macro \_MGIAL\_AUTO
is not defined in this file and MiniGUI will not support for Auto input
engine.

The attention, in **mgconfig.h** also contains other some macro
definitions, for instance MiniGUI version number and so on. Please
maintain these macro definitions to be invariable; do not have
voluntarily to revise these macro definitions.

The handwork revises **mgconfig.h** the procedure extremely tediously,
moreover is easy to make a mistake. If you use the GNU development
environment, then may use the configure script to configure MiniGUI. The
following section introduces how to use the configure script
automatically to produce the **mgconfig.h** file in the GNU development
environment.

### Using Configure Script in GNU Development Environment

It’s known that we can conveniently maintain the program package using
makefile. Through makefile, we may compile, clean or install the
function library, [executable
file](http://www.iciba.com/?s=executable%2520file) and header files in
the software package, etc. Although it is possible to organize a big
project with makefile, it is not an easy job to create such a makefile
manually. When we need to maintain a large-scale source code directory
tree, the makefile maintenance work can greatly increase. Therefore, the
Free Software Foundation's GNU project has developed the
Autoconf/Automake tool for many software projects, which is based on the
C language. Using this tool, we may automatically produce the makefile,
and can check the system configuration information, which helps
enhancement application software probability.

MiniGUI (MiniGUI library and sample programs package) is through the GNU
Automake/Autoconf script organization. Therefore, if you use the GNU
compatible development environment, for instance the Linux platform or
Cygwin environment in Windows platform and so on, you may use MiniGUI’s
Automake/Autoconf configuration script to configure MiniGUI. Uses
MiniGUI’s Automake/Autoconf configuration script, certainly does not
need to install Automake/Autoconf tool itself, but you just run the
configure script in the MiniGUI source code package then to complete the
configuration.\
If you run the configure script, it can produce not only makefile, but
also **mgconfig.h** file base on each of option in the configure script.
Afterwards, we just need run make and make install commands to compile
MiniGUI, and then MiniGUI library and header files will be installed to
the directory, which you assigned.

**\[NOTE\] The MiniGUI configure script only can be used in the GNU
compatible development environment. The GNU compatible development
environment usually has: the Linux system, the cygwin environment
running on Windows and so on, It may apply to MiniGUI product version
like Linux, uClinux, eCos.**

There are lot of options in the MiniGUI configure script, and each
configuration option corresponds a certain macro in **mgconfig.h**. If
you enable an option when run configure, then the correspondence macro
will be defined; otherwise can’t define this macro. Run the following
command.

```
user$ ./configure --help
```

You can obtain the whole options detailed list. For instance, supposing
you use Ubuntu Linux 16.04(i386) as your development environment, the
command runs in the MiniGUI source code directory and the running result
as follows (this command output may have differently on other Linux
release version):

```
$ ./configure --help
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
  --enable-standalone      build MiniGUI-Standalone version <default=no>
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

Above these parameters were already configured parameter which
established in the configure script, and these parameters are allowed to
control which function codes were supported when compile MiniGUI. For
example, run:

```
user$ ./configure --enable-procs --with-ttfsupport=ft2
```

You may configure MiniGUI that is the Freetype2 Truetype font support
and the MiniGUI-Process runtime mode. If you run:

```
user$ ./configure --disable-cursor --disable-screensaver
```

Then configure MiniGUI that is disable the cursor and default screen
saver function.

**./configure** command will produce a Makefile with default
configuration options. Each compiling configuration option has provided
a default setting in its explanation: &lt;**default=yes**&gt; (Expressed
this compiling configuration option is enabled default) or
&lt;**default=no**&gt; (Expressed this compiling configuration option is
disabled default).

Besides the MiniGUI has defined configuration options, the configure
script also has some important general compiling configuration options.

#### 1) Prefix Option

This compiling configuration option assigns the MiniGUI library where to
install. The default installation path is **/usr/local**. If you run:

```
user$ ./configure --prefix=/home/test
```

After executing ‘make install’ command, the function library, header
files and reference document are installed in **/home/test/lib**,
**/home/test/include** and **/home/test/man** directory.

#### Cross Compiling Options

The compiling configuration options **--build**, **--host** and
**--target** are very important to cross compile applications. For
example, if you use the arm-linux cross compiling toolchain, then you
may assign option like **--build**, thus let the configure script
produces the makefile file used to complete the arm-linux’s cross
compiling:

```
user$ CC=arm-linux-gcc ./configure
    --prefix=/usr/local/arm/2.95.3/arm-linux/ \
    --build=i386-linux \
    --host=arm-unknown-linux \
    --target=arm-unknown-linux
```

In above command, the **--prefix** option is used to set the installing
MiniGUI configuration file, the function library and the header files
directory’s prefix, when you executed **make install** command, MiniGUI
configuration file, the library file and header files will be installed
in the following position:

- `/usr/local/arm/2.95/arm-linux/etc/`
- `/usr/local/arm/2.95.3/arm-linux/lib/`
- `/usr/local/arm/2.95.3/arm-linux/include/`

#### --enable-static and --enable-shared

The two configuration options assign whether generating static function
library or dynamic function library. If you do not need to produce the
static library, then you may use the **--disable-static** configuration
option, it will take less time to compile the library than default.

There are several predefined targets in the makefile, which produced by
the configure script supply for user, here only several summaries as
follow:

The function storehouse, a document and so on are installed in the way,
which assigns

make all: Produce the target set. Only run make command also to be
allowed, this time can start to compile the source code, then link it
and produces the executable file or function library.

- `make clean`: Clean the previous object files(\*.o).
- `make install`: Install the function library, header files and so on to
the directory which you assigned.

### Configuration under Non-GNU environment

A majority of traditional embedded operating system supported by
MiniGUI, user usually can use the integrated development environment
running on Windows platform, such as Tornado, ADS, etc. Because these
environment provide the development tools chain that is not GNU
compatible, therefore, we are unable to use the configure script that is
described in section 2.1.1 to produce makefile and the **mgconfig.h**
file automatically. In this kind of situation, we need voluntarily to
revise the **mgconfig.h** file to complete the MiniGUI compiling
configuration. Fortunately, Feynman Software already prepares the
**mgconfig.h** file for the majority operating system, which can
directly be used (store in MiniGUI source code **build/** directory);
moreover Feynman Software also prepared the corresponding development
environment project file. You may directly manually revise the
**mgconfig.h** file based on these project environments, and compile the
MiniGUI library. For more detail information, please refer to the
section 2.4.2.

## Detailed Description on Compiling, Configuration Options of MiniGUI

In this chapter, we will give detailed description on all compiling,
configuration options of MiniGUI. MiniGUI has many compiling,
configuration options, for your actual demand; you can combine these
options to generate MiniGUI function library.

In GNU development environment, we implement the most of configuration
options of MiniGUI that based on **--disable-FEATURE** and
**--enable-FEATURE**, while MiniGUI configuration script also provides
**--with-configuration** option, you can use this configuration option
to choose one option from multiple specified configuration. For example,
you can use **--with-style** configuration option to specify the style
of window and control of MiniGUI. Finally, these configuration options
were defined macros, whatever use **--disable-FEATURE** or
**--enable-FEATURE** or **--with-configuration** option to specify
configuration option.

In the next chapter, we will give configuration option of MiniGUI by
classify. We will description on configuration names of configure script
and macro names in the **mgconfig.h** file.

### Operating System Options and Macros

MiniGUI provides support for multiple operating systems, you can specify
operating system when execute configure script, default operating system
is Linux. If you want to run MiniGUI on uClinux, you can execute command
as the follow:

```
user$ ./configure --with-osname=uclinux
```

If you specify an operating system, the corresponding macro was defined
in **mgconfig.h**. For some operating systems, we will open other some
macros. Table 2.1 lists relevant options and macros of operating
systems.

Table 2.1 operating systems relevant options and macros

  ----------------------------------------------------------------------------------------------------------------------------------------------
  Configuration options   Macro                      Other relevant macro   Memo
  ----------------------- -------------------------- ---------------------- --------------------------------------------------------------------
  --with-osname=linux     \_\_LINUX\_\_                                     Default value, for Linux operating system

  --with-osname=uclinux   \_\_uClinux\_\_                                   For uClinux operating system

  --with-osname=ecos      \_\_ECOS\_\_               \_\_NOUNIX\_\_         For eCos operating system

  --with-osname=ucos2     \_\_UCOSII\_\_             \_\_NOUNIX\_\_         For uC/OS-II operating system
                                                                            
                                                     \_INCORE\_RES          
                                                                            
                                                     \_USE\_OWN\_MALLOC     
                                                                            
                                                     \_USE\_OWN\_STDIO      
                                                                            
                                                     \_USE\_OWN\_PTHREAD    

  --with-osname=swlinux   \_\_WINBOND\_SWLINUX\_\_                          For SWLinux operating system, mutation of uClinux operating system

  --with-osname=vxworks   \_\_VXWORKS\_\_            \_\_NOUNIX\_\_         For VxWorks operating system
                                                                            
                                                     \_USE\_OWN\_STDIO      
                                                                            
                                                     \_USE\_OWN\_PTHREAD    

  --with-osname=cygwin    \_\_CYGWIN\_\_             \_\_NOUNIX\_\_         For cygwin environment

  --with-osname=win32     WIN32                      \_\_NOUNIX\_\_         For Win32 platform

  --with-osname=darwin    \_\_DARWIN\_\_             \_\_NOUNIX\_\_         For MacOS X operating system

  --with-osname=threadx   \_\_THREADX\_\_            \_\_NOUNIX\_\_         For ThreadX operating system
                                                                            
                                                     \_INCORE\_RES          
                                                                            
                                                     \_USE\_OWN\_MALLOC     
                                                                            
                                                     \_USE\_OWN\_STDIO      
                                                                            
                                                     \_USE\_OWN\_PTHREAD    

  --with-osname=nucleus   \_\_NUCLEUS\_\_            \_\_NOUNIX\_\_         For Nucleus operating system
                                                                            
                                                     \_INCORE\_RES          
                                                                            
                                                     \_USE\_OWN\_MALLOC     
                                                                            
                                                     \_USE\_OWN\_STDIO      
                                                                            
                                                     \_USE\_OWN\_PTHREAD    

  --with-osname=ose       \_\_OSE\_\_                \_\_NOUNIX\_\_         For OSE operating system
                                                                            
                                                     \_INCORE\_RES          
                                                                            
                                                     \_USE\_OWN\_PTHREAD    

  --with-osname=psos      \_\_PSOS\_\_               \_\_NOUNIX\_\_         For pSOS operating system
                                                                            
                                                     \_INCORE\_RES          
                                                                            
                                                     \_USE\_OWN\_PTHREAD    
  ----------------------------------------------------------------------------------------------------------------------------------------------

According to operating system, we divide MiniGUI value-added release, so
the MiniGUI value-added release product for certain operating system
cannot run on anther operating system. In order to run MiniGUI
value-added release product on corresponding operating system, you make
sure that the above macros were defined when you modify configuration.

### Target Board Related Options and Macros

In MiniGUI certain codes are related with a special target board; if you
want run MiniGUI must on these target boards correctly, you need to
assign the name of these development boards. When you run configure
script, through the **--with-targetname** option, may assign the special
target board name and the default name is unknown. The target board
related options usually use for assign the sub-driver of graphics engine
when MiniGUI uses the Shadow graphics engine or the CommLCD graphics
engine, in other words, when uses these two engines, through the target
board name you can determine which sub-driver contains. The table 2.2
lists the target board related options and macros.

Table 2.2 target board related options and macros

  Configuration options       Macro                      Memo
  --------------------------- -------------------------- ----------------------------------------------------------
  --with-targetname=stb810    \_\_TARGET\_STB810\_\_     Philips STB810 development board base on Linux
  --with-targetname=vfanvil   \_\_TARGET\_VFANVIL\_\_    VisualFone development board base on ThreadX
  --with-targetname=vxi386    \_\_TARGET\_VXI386\_\_     i386 target base on VxWorks
  --with-targetname=qvfb      \_\_TARGET\_QVFB\_\_       Include qvfb sub-driver of Shadow engine base on Linux
  --with-targetname=wvfb      \_\_TARGET\_WVFB\_\_       Include wvfb sub-driver of Shadow engine base on Windows
  --with-targetname=fbcon     \_\_TARGET\_FBCON\_\_      Include fbcon sub-driver of Shadow engine base on Linux
  --with-targetname=mx21      \_\_TARGET\_MX21\_\_       MX21 development board base on OSE
  --with-targetname=c33l05    \_\_TARGET\_C33L05\_\_     Epson C33L05 development board base on axLinux
  --with-targetname=bfin      \_\_TARGET\_BLACKFIN\_\_   BlackFin537 development board base on uClinux
  --with-targetname=vxppc     \_\_TARGET\_PPC\_\_        PowerPC target base on VxWorks
  --with-targetname=monaco    \_\_TARGET\_MONACO\_\_     monaco development board base on Nucleus
  --with-targetname=unkown    \_\_TARGET\_UNKNOWN\_\_    Unknown development board: default value

### 2.2.3 Runtime Mode Related Options and Macros

We can configure MiniGUI as one of three kind of runtime mode:
MiniGUI-Processes runtime mode base on multi-processes, MiniGUI-Threads
runtime mode base on multi-thread, as well as MiniGUI-Standalone runtime
mode base on non-multi-processes also non-multi-thread. MiniGUI-Threads
runtime mode is the default mode when MiniGUI use the default
configuration option. The table 2.3 lists runtime mode related options
and macros.

Table 2.3 runtime mode related options and macros

  Configuration options   Macro                Memo                                                                  Default
  ----------------------- -------------------- --------------------------------------------------------------------- ----------
  not assigned            \_MGRM\_THREADS      MiniGUI-Threads runtime mode                                          Enabled
  procs                   \_MGRM\_PROCESSES    MiniGUI-Processes runtime mode, support Linux operating system only   Disabled
  standalone              \_MGRM\_STANDALONE   MiniGUI-Standalone runtime mode, support all operating system.        Disabled

### 2.2.4 Graphics Engine Related Options and Macros

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

### 2.2.5 Input Engine Related Options and Macros

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

### 2.2.6 Keyboard Layout Related Options and Macros

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

### 2.2.7 System Global Configuration Options and Macros

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

### 2.2.8 Character Set and Font Related Options and Macros

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

### 2.2.9 Image File Format Related Options and Macros

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

### 2.2.10 Appearance Style Related Options and Macros

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

### 2.2.11 Control Related Options and Macros

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

### 2.2.12 Other Options and Macros

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

Otherwise, you must define this macro: \_\_MINIGUI\_LIB\_\_ , when you
use yourself makefile to compile MiniGUI function library in the Non-GNU
development environment.

Table 2.20 other compile macros

  Macro                  Comment                         Memo
  ---------------------- ------------------------------- ----------------------------------------------------------------
  \_\_MINIGUI\_LIB\_\_   Compile MiniGUI library macro   You must define this macros, when you use the Non-GNU makefile

Start with MiniGUI 3.0, you can specify the name suffix of the MiniGUI
library through the configure option. By default, the name of the
MiniGUI library varies depending on the operating mode, for example,
libminigui-ths.so, libminigui-procs.so, libminigui-sa.so , Respectively,
corresponding to MiniGUI-Threads, MiniGUI-Processes and
MiniGUI-Standalone mode of operation.

You can specify a special library name suffix with the --with-libsuffix
option.

2.3 Minimum Configuration Options
---------------------------------

In this chapter, we will give an example of minimum configuration
options in MiniGUI.

### 2.3.1 Using GNU Configure Script

There is a buildlib-min script in the MiniGUI source codes build
directory. The buildlib-min script will be as the following:

\#!/bin/sh

./configure \\

--disable-dblclk \\

--disable-cursor \\

--disable-mousecalibrate \\

--disable-clipboard \\

--disable-adv2dapi \\

--disable-splash \\

--disable-screensaver \\

--disable-flatlf \\

--disable-skinlf \\

--disable-rbfvgaoem \\

--disable-rbfterminal \\

--disable-vbfsupport \\

--disable-qpfsupport \\

--disable-upfsupport \\

--disable-bmpfsupport \\

--disable-latin9support \\

--disable-gbsupport \\

--disable-gbksupport \\

--disable-unicodesupport \\

--disable-savebitmap \\

--disable-jpgsupport \\

--disable-pngsupport \\

--disable-gifsupport \\

--disable-aboutdlg \\

--disable-savescreen \\

--disable-mousecalibrate \\

--disable-ctrlanimation \\

--disable-ctrlnewtextedit \\

--disable-consoleps2 \\

--disable-consoleimps2 \\

--disable-consolems \\

--disable-consolems3 \\

--disable-consolegpm

By this script, you can configure MiniGUI to the minimum function
library that only supports ISO8859-1 charset.

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

No support for screen save function.

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

### 2.3.2 Corresponding mgconfig.h

The **mgconfig.h** file to be generated in the configuration script
above, listed as follows:

...

/\* MiniGUI configure file name \*/

\#define ETCFILENAME "MiniGUI.cfg"

...

/\* Binary age of MiniGUI \*/

\#define MINIGUI\_BINARY\_AGE 0

/\* Interface age of MiniGUI \*/

\#define MINIGUI\_INTERFACE\_AGE 0

/\* Major version of MiniGUI \*/

\#define MINIGUI\_MAJOR\_VERSION 3

/\* Micro version of MiniGUI \*/

\#define MINIGUI\_MICRO\_VERSION 13

/\* Minor version of MiniGUI \*/

\#define MINIGUI\_MINOR\_VERSION 0

...

/\* Define if support Arabic charset \*/

/\* \#undef \_MGCHARSET\_ARABIC \*/

/\* Define if support BIG5 charset \*/

/\* \#undef \_MGCHARSET\_BIG5 \*/

/\* Define if support Cyrillic charset \*/

/\* \#undef \_MGCHARSET\_CYRILLIC \*/

/\* Define if support EUCJP charset \*/

/\* \#undef \_MGCHARSET\_EUCJP \*/

/\* Define if support EUCKR charset \*/

/\* \#undef \_MGCHARSET\_EUCKR \*/

/\* Define if support GB2312 charset \*/

/\* \#undef \_MGCHARSET\_GB \*/

/\* Define if support GB18030 charset \*/

/\* \#undef \_MGCHARSET\_GB18030 \*/

/\* Define if support GBK charset \*/

/\* \#undef \_MGCHARSET\_GBK \*/

/\* Define if support Greek charset \*/

/\* \#undef \_MGCHARSET\_GREEK \*/

/\* Define if support Hebrew charset \*/

/\* \#undef \_MGCHARSET\_HEBREW \*/

/\* Define if support Latin 10 charset \*/

/\* \#undef \_MGCHARSET\_LATIN10 \*/

/\* Define if support Latin 2 charset \*/

/\* \#undef \_MGCHARSET\_LATIN2 \*/

/\* Define if support Latin 3 charset \*/

/\* \#undef \_MGCHARSET\_LATIN3 \*/

/\* Define if support Latin 4 charset \*/

/\* \#undef \_MGCHARSET\_LATIN4 \*/

/\* Define if support Latin 5 charset \*/

/\* \#undef \_MGCHARSET\_LATIN5 \*/

/\* Define if support Latin 6 charset \*/

/\* \#undef \_MGCHARSET\_LATIN6 \*/

/\* Define if support Latin 7 charset \*/

/\* \#undef \_MGCHARSET\_LATIN7 \*/

/\* Define if support Latin 8 charset \*/

/\* \#undef \_MGCHARSET\_LATIN8 \*/

/\* Define if support Latin 9 charset \*/

/\* \#undef \_MGCHARSET\_LATIN9 \*/

/\* Define if support SHIFTJIS charset \*/

/\* \#undef \_MGCHARSET\_SHIFTJIS \*/

/\* Define if support Thai charset \*/

/\* \#undef \_MGCHARSET\_THAI \*/

/\* Define if support UNICODE \*/

/\* \#undef \_MGCHARSET\_UNICODE \*/

/\* Define if include GPM mouse subdriver \*/

/\* \#undef \_MGCONSOLE\_GPM \*/

/\* Define if include IMPS2 mouse subdriver \*/

/\* \#undef \_MGCONSOLE\_IMPS2 \*/

/\* Define if include MS mouse subdriver \*/

/\* \#undef \_MGCONSOLE\_MS \*/

/\* Define if include MS3 mouse subdriver \*/

/\* \#undef \_MGCONSOLE\_MS3 \*/

/\* Define if include PS2 mouse subdriver \*/

/\* \#undef \_MGCONSOLE\_PS2 \*/

/\* Define if your Linux have text mode \*/

\#define \_MGCONSOLE\_TEXTMODE 1

/\* Define if include ANIMATION control \*/

/\* \#undef \_MGCTRL\_ANIMATION \*/

/\* Define if include BIDISLEDIT control \*/

/\* \#undef \_MGCTRL\_BIDISLEDIT \*/

/\* Define if include BUTTON control \*/

\#define \_MGCTRL\_BUTTON 1

/\* Define if include COMBOBOX control \*/

\#define \_MGCTRL\_COMBOBOX 1

/\* Define if include COOLBAR control \*/

/\* \#undef \_MGCTRL\_COOLBAR \*/

/\* Define if include GRIDVIEW control \*/

/\* \#undef \_MGCTRL\_GRIDVIEW \*/

/\* Define if include ICONVIEW control \*/

/\* \#undef \_MGCTRL\_ICONVIEW \*/

/\* Define if include LISTBOX control \*/

\#define \_MGCTRL\_LISTBOX 1

/\* Define if include LISTVIEW control \*/

/\* \#undef \_MGCTRL\_LISTVIEW \*/

/\* Define if include MENUBUTTON control \*/

/\* \#undef \_MGCTRL\_MENUBUTTON \*/

/\* Define if include MONTHCALENDAR control \*/

/\* \#undef \_MGCTRL\_MONTHCAL \*/

/\* Define if include NEWTOOLBAR control \*/

/\* \#undef \_MGCTRL\_NEWTOOLBAR \*/

/\* Define if include PROGRESSBAR control \*/

\#define \_MGCTRL\_PROGRESSBAR 1

/\* Define if include PROPSHEET control \*/

\#define \_MGCTRL\_PROPSHEET 1

/\* Define if include SCROLLBAR control \*/

/\* \#undef \_MGCTRL\_SCROLLBAR \*/

/\* Define if include SCROLLVIEW control \*/

/\* \#undef \_MGCTRL\_SCROLLVIEW \*/

/\* Define if include SLEDIT control \*/

\#define \_MGCTRL\_SLEDIT 1

/\* Define if include SPINBOX control \*/

/\* \#undef \_MGCTRL\_SPINBOX \*/

/\* Define if include STATIC control \*/

\#define \_MGCTRL\_STATIC 1

/\* Define if include TEXTEDIT control \*/

/\* \#undef \_MGCTRL\_TEXTEDIT \*/

/\* Define if use new implementation of TEXTEDIT control \*/

/\* \#undef \_MGCTRL\_TEXTEDIT\_USE\_NEW\_IMPL \*/

/\* Define if include TRACKBAR control \*/

/\* \#undef \_MGCTRL\_TRACKBAR \*/

/\* Define if include TREEVIEW control \*/

/\* \#undef \_MGCTRL\_TREEVIEW \*/

/\* Define if include TREEVIEWRDR control \*/

/\* \#undef \_MGCTRL\_TREEVIEW\_RDR \*/

/\* Define if support Bitmap fonts \*/

/\* \#undef \_MGFONT\_BMPF \*/

/\* Define if support TrueType font based on FreeType2 \*/

/\* \#undef \_MGFONT\_FT2 \*/

/\* Define if support QPF font \*/

/\* \#undef \_MGFONT\_QPF \*/

/\* Define if support raw bitmap fonts \*/

\#define \_MGFONT\_RBF 1

/\* Define if support SEF scripteary font \*/

/\* \#undef \_MGFONT\_SEF \*/

/\* Define if support TrueType font \*/

/\* \#undef \_MGFONT\_TTF \*/

/\* Define if include ttf cache \*/

/\* \#undef \_MGFONT\_TTF\_CACHE \*/

/\* Define if support UPF font \*/

/\* \#undef \_MGFONT\_UPF \*/

/\* Define if support var bitmap fonts \*/

/\* \#undef \_MGFONT\_VBF \*/

/\* Define if include NEWGAL engine for BF533 OSD via SPI \*/

/\* \#undef \_MGGAL\_BF533 \*/

/\* Define if include NEWGAL engine for Common LCD \*/

/\* \#undef \_MGGAL\_COMMLCD \*/

/\* Define if include custom NEWGAL engine \*/

/\* \#undef \_MGGAL\_CUSTOMGAL \*/

/\* Define if include NEWGAL engine for DirectFB \*/

/\* \#undef \_MGGAL\_DFB \*/

/\* Define if include ST7167 subdriver for NEWGAL engine of DirectFB \*/

/\* \#undef \_MGGAL\_DFB\_ST7167 \*/

/\* Define if include dummy NEWGAL engine \*/

\#define \_MGGAL\_DUMMY 1

/\* Define if include NEWGAL engine for EM85xx OSD \*/

/\* \#undef \_MGGAL\_EM85XXOSD \*/

/\* Define if include NEWGAL engine for EM85xx YUV \*/

/\* \#undef \_MGGAL\_EM85XXYUV \*/

/\* Define if include NEWGAL engine for EM86xx GFX \*/

/\* \#undef \_MGGAL\_EM86GFX \*/

/\* Define if include FrameBuffer console NEWGAL engine \*/

\#define \_MGGAL\_FBCON 1

/\* Define if include GDL Video NEWGAL engine \*/

/\* \#undef \_MGGAL\_GDL \*/

/\* Define if include Hi35XX Video NEWGAL engine \*/

/\* \#undef \_MGGAL\_HI3510 \*/

/\* Define if include Hi35XX Video NEWGAL engine \*/

/\* \#undef \_MGGAL\_HI3560 \*/

/\* Define if include Hi3560A Video NEWGAL engine \*/

/\* \#undef \_MGGAL\_HI3560A \*/

/\* Define if include NEWGAL engine for mb93493 YUV FrameBuffer driver
\*/

/\* \#undef \_MGGAL\_MB93493 \*/

/\* Define if include MLShadow NEWGAL engine \*/

/\* \#undef \_MGGAL\_MLSHADOW \*/

/\* Define if include mstar NEWGAL engine \*/

/\* \#undef \_MGGAL\_MSTAR \*/

/\* Define if include nexus NEWGAL engine \*/

/\* \#undef \_MGGAL\_NEXUS \*/

/\* Define if include PC Virtual FrameBuffer NEWGAL engine \*/

\#define \_MGGAL\_PCXVFB 1

/\* Define if include Qt Virtual FrameBuffer NEWGAL engine \*/

/\* \#undef \_MGGAL\_QVFB \*/

/\* Define if include RTOS Virtual FrameBuffer NEWGAL engine \*/

/\* \#undef \_MGGAL\_RTOSXVFB \*/

/\* Define if include s3c6410 NEWGAL engine \*/

/\* \#undef \_MGGAL\_S3C6410 \*/

/\* Define if include Shadow NEWGAL engine \*/

/\* \#undef \_MGGAL\_SHADOW \*/

/\* Define if include sigma8654 NEWGAL engine \*/

/\* \#undef \_MGGAL\_SIGMA8654 \*/

/\* Define if include NEWGAL engine for STGFB \*/

/\* \#undef \_MGGAL\_STGFB \*/

/\* Define if include NEWGAL engine for SVPXX OSD \*/

/\* \#undef \_MGGAL\_SVPXXOSD \*/

/\* Define if include NEWGAL engine for UTPMC \*/

/\* \#undef \_MGGAL\_UTPMC \*/

/\* Define if include windows Virtual FrameBuffer NEWGAL engine \*/

/\* \#undef \_MGGAL\_WVFB \*/

/\* Define if include advanced 2D graphics APIs \*/

/\* \#undef \_MGHAVE\_ADV\_2DAPI \*/

/\* Define if include clipboard support \*/

/\* \#undef \_MGHAVE\_CLIPBOARD \*/

/\* Define if include cursor support \*/

/\* \#undef \_MGHAVE\_CURSOR \*/

/\* Define if include fixed math routines \*/

\#define \_MGHAVE\_FIXED\_MATH 1

/\* Define if support menu \*/

\#define \_MGHAVE\_MENU 1

/\* Define if include code for mouse calibration \*/

/\* \#undef \_MGHAVE\_MOUSECALIBRATE \*/

/\* Define if include message string names \*/

/\* \#undef \_MGHAVE\_MSG\_STRING \*/

/\* Define if PCIAccess lib is available \*/

/\* \#undef \_MGHAVE\_PCIACCESS \*/

/\* Define if trace message dispatching of MiniGUI \*/

/\* \#undef \_MGHAVE\_TRACE\_MSG \*/

/\* Define if include the 2440 IAL engine \*/

/\* \#undef \_MGIAL\_2440 \*/

/\* Define if include the automatic IAL engine \*/

/\* \#undef \_MGIAL\_AUTO \*/

/\* Define if include IAL engine for Cisco touchpad \*/

/\* \#undef \_MGIAL\_CISCO\_TOUCHPAD \*/

/\* Define if include the common IAL engine \*/

/\* \#undef \_MGIAL\_COMM \*/

/\* Define if include console (Linux console) IAL engine \*/

\#define \_MGIAL\_CONSOLE 1

/\* Define if include IAL engine for customer's board \*/

/\* \#undef \_MGIAL\_CUSTOM \*/

/\* Define if include the DAVINCI6446 IAL engine \*/

/\* \#undef \_MGIAL\_DAVINCI6446 \*/

/\* Define if include the DFB IAL engine \*/

/\* \#undef \_MGIAL\_DFB \*/

/\* Define if include dlcustom IAL engine \*/

/\* \#undef \_MGIAL\_DLCUSTOM \*/

/\* Define if include the dummy IAL engine \*/

\#define \_MGIAL\_DUMMY 1

/\* Define if include IAL engine for iPAQ H3600 \*/

/\* \#undef \_MGIAL\_IPAQ\_H3600 \*/

/\* Define if include IAL engine for iPAQ H5400 \*/

/\* \#undef \_MGIAL\_IPAQ\_H5400 \*/

/\* Define if include the JZ4740 IAL engine \*/

/\* \#undef \_MGIAL\_JZ4740 \*/

/\* Define if include the lide IAL engine \*/

/\* \#undef \_MGIAL\_LIDE \*/

/\* Define if include IAL engine for MStar \*/

/\* \#undef \_MGIAL\_MSTAR \*/

/\* Define if include IAL engine for net's board \*/

/\* \#undef \_MGIAL\_NET \*/

/\* Define if include IAL engine for Nexus \*/

/\* \#undef \_MGIAL\_NEXUS \*/

/\* Define if include the QEMU IAL engine \*/

/\* \#undef \_MGIAL\_QEMU \*/

/\* Define if include the QVFB IAL engine \*/

/\* \#undef \_MGIAL\_QVFB \*/

/\* Define if include the random IAL engine \*/

/\* \#undef \_MGIAL\_RANDOM \*/

/\* Define if include IAL engine for TSLIB \*/

/\* \#undef \_MGIAL\_TSLIB \*/

/\* Define if include the WVFB IAL engine \*/

/\* \#undef \_MGIAL\_WVFB \*/

/\* Define if support GIF bmp file format \*/

/\* \#undef \_MGIMAGE\_GIF \*/

/\* Define if support JPEG bmp file format \*/

/\* \#undef \_MGIMAGE\_JPG \*/

/\* Define if support LBM bmp file format \*/

/\* \#undef \_MGIMAGE\_LBM \*/

/\* Define if support PCX bmp file format \*/

/\* \#undef \_MGIMAGE\_PCX \*/

/\* Define if support PNG bmp file format \*/

/\* \#undef \_MGIMAGE\_PNG \*/

/\* Define if support TGA bmp file format \*/

/\* \#undef \_MGIMAGE\_TGA \*/

/\* Define if include in-core font: Courier \*/

/\* \#undef \_MGINCOREFONT\_COURIER \*/

/\* Define if include in-core font: SansSerif \*/

/\* \#undef \_MGINCOREFONT\_SANSSERIF \*/

/\* Define if include in-core font: System \*/

/\* \#undef \_MGINCOREFONT\_SYSTEM \*/

/\* Define if include in-core UPF Times fonts \*/

/\* \#undef \_MGINCOREFONT\_TIMES \*/

/\* Define if include in-core FixedSys RBF for ISO8859-1 \*/

\#define \_MGINCORERBF\_LATIN1\_FIXEDSYS 1

/\* Define if include in-core Terminal RBF for ISO8859-1 \*/

/\* \#undef \_MGINCORERBF\_LATIN1\_TERMINAL \*/

/\* Define if include in-core VGAOEM RBF for ISO8859-1 \*/

/\* \#undef \_MGINCORERBF\_LATIN1\_VGAOEM \*/

/\* Define if build MiniGUI for no file I/O system (use in-core
resources) \*/

/\* \#undef \_MGINCORE\_RES \*/

/\* Define if use the Arabic PC keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_ARABICPC \*/

/\* Define if use the German keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_DE \*/

/\* Define if use the German-Latin1 keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_DELATIN1 \*/

/\* Define if use the Spanish keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_ES \*/

/\* Define if use the Spanish CP850 keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_ESCP850 \*/

/\* Define if use the French keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_FR \*/

/\* Define if use the French PC keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_FRPC \*/

/\* Define if use the Hebrew PC keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_HEBREWPC \*/

/\* Define if use the Italian keyboard layout \*/

/\* \#undef \_MGKBDLAYOUT\_IT \*/

/\* Define if include flat Look and Feel \*/

/\* \#undef \_MGLF\_RDR\_FLAT \*/

/\* Define if include skin Look and Feel \*/

/\* \#undef \_MGLF\_RDR\_SKIN \*/

/\* MiniGUI library suffix \*/

\#define \_MGLIB\_SUFFIX "ths"

/\* Define if compile max ttf cahce number for 10 (default value) \*/

/\* \#undef \_MGMAX\_TTF\_CACHE \*/

/\* Define if include About MiniGUI Dialog Box \*/

/\* \#undef \_MGMISC\_ABOUTDLG \*/

/\* Define if mouse button can do double click \*/

/\* \#undef \_MGMISC\_DOUBLE\_CLICK \*/

/\* Define if include SaveBitmap function \*/

/\* \#undef \_MGMISC\_SAVEBITMAP \*/

/\* Define if include code for screenshots \*/

/\* \#undef \_MGMISC\_SAVESCREEN \*/

/\* Define if build MiniGUI-Processes \*/

/\* \#undef \_MGRM\_PROCESSES \*/

/\* Define if build MiniGUI-Standalone \*/

/\* \#undef \_MGRM\_STANDALONE \*/

/\* Define if build MiniGUI-Threads \*/

\#define \_MGRM\_THREADS 1

/\* Define if the unit of timer is 10ms \*/

\#define \_MGTIMER\_UNIT\_10MS 1

/\* Define if compile max ttf cahce size for 256k \*/

/\* \#undef \_MGTTF\_CACHE\_SIZE \*/

/\* Define if use own implementation of malloc functions \*/

/\* \#undef \_MGUSE\_OWN\_MALLOC \*/

/\* Define if use own implementation of pthread functions \*/

/\* \#undef \_MGUSE\_OWN\_PTHREAD \*/

/\* Define if use own implementation of stdio functions \*/

/\* \#undef \_MGUSE\_OWN\_STDIO \*/

/\* Define if build the mgeff support version \*/

/\* \#undef \_MG\_MINIMALGDI \*/

/\* Define if insert a productid into the library file \*/

/\* \#undef \_MG\_PRODUCTID \*/

/\* Define if build MiniGUI-Standalone (back-compatibility definition)
\*/

/\* \#undef \_STAND\_ALONE \*/

/\* Define if use minigui\_entry function in MiniGUI \*/

/\* \#undef \_USE\_MINIGUIENTRY \*/

/\* Define if compile for Cygwin platform \*/

/\* \#undef \_\_CYGWIN\_\_ \*/

/\* Define if compile for OpenDarwin \*/

/\* \#undef \_\_DARWIN\_\_ \*/

/\* Define if compile for eCos \*/

/\* \#undef \_\_ECOS\_\_ \*/

/\* Define if compile for Linux \*/

\#define \_\_LINUX\_\_ 1

/\* Define if compile for non-UNIX like OS \*/

/\* \#undef \_\_NOUNIX\_\_ \*/

/\* Define if compile for Nucleus \*/

/\* \#undef \_\_NUCLEUS\_\_ \*/

/\* Define if compile for OSE \*/

/\* \#undef \_\_OSE\_\_ \*/

/\* Define if compile for pSOS \*/

/\* \#undef \_\_PSOS\_\_ \*/

/\* Define for Blackfin run uClinux \*/

/\* \#undef \_\_TARGET\_BLACKFIN\_\_ \*/

/\* Define for EPSON C33L05 (axLinux) \*/

/\* \#undef \_\_TARGET\_C33L05\_\_ \*/

/\* Define for FMSoft internal use \*/

/\* \#undef \_\_TARGET\_FMSOFT\_\_ \*/

/\* Define for Monaco ANVIL target \*/

/\* \#undef \_\_TARGET\_MONACO\_\_ \*/

/\* Define for FMSoft miniStudio \*/

/\* \#undef \_\_TARGET\_MSTUDIO\_\_ \*/

/\* Define for OSE on mx21 \*/

/\* \#undef \_\_TARGET\_MX21\_\_ \*/

/\* Define for VxWorks on PowerPC \*/

/\* \#undef \_\_TARGET\_PPC\_\_ \*/

/\* Define for Philips STB810 target \*/

/\* \#undef \_\_TARGET\_STB810\_\_ \*/

/\* Define for unknown target \*/

\#define \_\_TARGET\_UNKNOWN\_\_ 1

/\* Define for VirualFone ANVIL target \*/

/\* \#undef \_\_TARGET\_VFANVIL\_\_ \*/

/\* Define for VxWorks on i386 \*/

/\* \#undef \_\_TARGET\_VXI386\_\_ \*/

/\* Define if compile for ThreadX \*/

/\* \#undef \_\_THREADX\_\_ \*/

/\* Define if compile for uC/OS-II \*/

/\* \#undef \_\_UCOSII\_\_ \*/

/\* Define if compile for VxWorks \*/

/\* \#undef \_\_VXWORKS\_\_ \*/

/\* Define if compile for Winbond SWLinux \*/

/\* \#undef \_\_WINBOND\_SWLINUX\_\_ \*/

/\* Define if compile for uClinux \*/

/\* \#undef \_\_uClinux\_\_ \*/

...

2.4 Compiling and Installing MiniGUI 
-------------------------------------

### 2.4.1 compile and install the dependent library

Before running MiniGUI, you need to install the dependent libraries
required by MiniGUI. MiniGUI mainly uses LibFreeType, LibPNG, LibJPEG,
LibZ and other third-party dependent libraries.

These dependent library source code packages basically use the GNU
Automake / Autoconf script to organize projects and compile and install
these libraries by specifying specific environment variables and certain
options when running ./configure commands. We can also check the
acceptable switch parameters for each configure script by running the
./configure --help command in these dependent source files.

Currently, these dependencies are basically standard configurations of
mainstream Linux distributions (such as Ubuntu, RedHat, etc.). However,
if you want to find these libraries while compiling MiniGUI, you need to
install these SDKs. For example, on Ubuntu Linux, FreeType 2, LibPNG,
LibJPEG development kits can be installed by executing the following
command:

This section is given below in the source code package based on the
compiler, install these dependent libraries steps, for reference only.

\$ sudo apt-get install libfreetype6-dev libpng12-dev libjpeg-dev

***LibFreeType***

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

\$ ./configure --prefix=/usr/local

\$ make

\$ sudo make install

The FreeType 2 library and header files will be installed in /usr/local
directory.

***LibJPEG, LibPNG, LibZ and other dependent libraries***

The library on which MiniGUI runs depends on libjpeg for JPEG images,
libpng for PNG images, and more. Like the FreeType library, these
libraries are included in common Linux distributions.

First install the LibZ library. The LibZ library provides the
compression and decompression function of the Z algorithm, while the PNG
image format uses the same compression algorithm, so before installing
and installing LibPNG, first install the LibZ library. Download and
unzip LibZ library source code package, and then enter the source root
directory, execute the following command:

\$ ./configure --prefix=/usr/local

\$ make

\$ sudo make install

The LibZ library and header files will be installed in /usr/local
directory.

Download LibPng library source code, untied into the root directory of
the source code, execute the following command:

\$ ./configure --prefix=/usr/local

\$ make

\$ sudo make install

Download LibJPEG library source code, untied into the root directory of
the source code, execute the following command:

\$ ./configure --prefix=/usr/local --enable-shared

\$ make

\$ sudo make install

The installation process may be prompted to create certain files, then
you need to see the directory you want to install there is no
corresponding directory, if you do not have to create your own. This
JPEG library header files, dynamic libraries and static libraries will
be installed to the /usr/local directory.

### 2.4.2 compile and install the virtual framebuffer program

The default virtual framebuffer graphics engine in MiniGUI 3.0 is
pc\_xvfb. The graphics engine defines a virtual frame buffer program
(XVFB) specification that does not depend on a specific implementation.
Under this specification, we can use the gvfb program on Linux Use Gtk+
development), or use the qvfb2 program (developed using Qt) to display
the output of MiniGUI and its application in the window of gvfb or qvfb.

***gvfb***

gvfb is a virtual framebuffer program that is compatible with MiniGUI
3.0 XVFB specification and was developed using Gtk+ 2.0. To compile and
install gvfb, to ensure that the system has been installed Gtk+ 2.0
development kits. Under Ubuntu Linux, use the following command to
install the appropriate development kit:

\$ sudo apt-get install libgtk2.0-dev

Then enter the gvfb source code directory, run the following command:

\$ ./configure --prefix=/usr/local

\$ make

\$ sudo make install

***qvfb2***

qvfb2 is an upgraded version of qvfb that is compatible with the XVFB
specification proposed by MiniGUI 3.0.

To compile qvfb2, you need to install Qt development package, and Qt
version needs to be greater than or equal to 3.0.3. Specific
installation process can refer to the source code in the README file.
Here's an example of the specific process of installing qvfb2 in ubuntu
environment.

\$ sudo apt-get install build-essential xorg-dev

Qt3 library and its header files and other related content installation:

\$ sudo apt-get install libqt3-headers libqt3-mt libqt3-mt-dev

Then enter the qvfb2 source code directory, run the following command:

\$ ./configure --prefix=/usr/local \\

--with-qt-includes=/usr/include/qt3/ \\

--with-qt-libraries=/usr/lib/qt3/

\$ make

\$ sudo make install

The --prefix option specifies the installation path for qvfb2;
*--with-qt-includes* option specifies the Qt3 header file path; -
with-qt-libraries option specifies the Qt3 library file path.

If the above command is successful, then qvfb2 program will be installed
to /usr/ local/bin directory.

### 2.4.3 Compiling and Installing MiniGUI in the GNU Development Environment

If you configure MiniGUI with configure script in GNU development
environment, you can compile and install MiniGUI with make tool.

For example, assuming that you used MiniGUI for Linux product, in the PC
computer for running Linux, you can execute several commands as the
following in your MiniGUI source code directory to configure, compile
and install MiniGUI to your system.

user\$ ./configure

user\$ make

user\$ su -c ‘make install’

You can also use configure script to specify a cross-compiling directory
and installing directory and so on.

### 2.4.4 Install MiniGUI Resource Package

MiniGUI resource package (minigui-res) is also organized by GNU
autoconf/automake script, so just run the following command to install:

user\$ ./configure

user\$ make

user\$ sudo make install

Similarly, we can also specify the installation path using the --prefix
option.

### 2.4.5 compile and run MiniGUI sample

After compiling and installing MiniGUI according to the above steps, you
can compile and run the sample in mg-samples. By default, MiniGUI will
use the pc\_xvfb graphics and input engine, and the actual virtual
framebuffer is gvfb.

Run the following command to configure and compile the mg-samples code
package:

user\$ sudo ldconfig

user\$ ./configure

user\$ make

The first command to refresh the Linux system dynamic library cache
system. Because by default MiniGUI dynamic libraries are installed in
the /usr/local/lib directory, the system uses a cache to maintain a list
of all the dynamic libraries installed in the system. If the cache is
not refreshed, It may not be found installed dynamic library problem.

To run the demo in MiniGUI-Processes runtime mode, you need to start the
mginit program first and then run the other sample programs. The
following is the process of running the same game in MiniGUI-Processes
mode:

user\$ cd mginit

user\$ ./mginit &

user\$ cd ../same

user\$ ./same

On MiniGUI-Threads runtime mode to run the demo program, more simple,
direct run sample demo. Here's how to run the same game in thread mode:

user\$ cd same

user\$ ./same

2.5 Compiling and Installing MiniGUI in Non-GNU Development Environment
-----------------------------------------------------------------------

In the Non-GNU development environment (generally, it is Windows
platform), we first organize MiniGUI source code solution for project of
special Integration Development Environment (for example, Tornado and
ADS). Secondly, we compile MiniGUI. At last, we compile MiniGUI
application.

But using cygwin development environment for Windows platform, it is
very convenient. We can compile and install MiniGUI. In theory, this
method is applicable to any development environment, which runs on
Windows platform, so we will give detailed description on this method in
this chapter.

Cygwin is an open source software project and Linux-like environment for
Windows. After installing cygwin on Windows, we can execute many
applications of Linux platform, for example, BASH script, VIM editor,
PERL script interpreter, make tool of Linux, gcc compiler and so on. In
the cygwin environment, we can also call other Windows applications.
Thus, if we write makefile for MiniGUI according to GNU rules and use
make tool of cygwin to call corresponding compiler and linker, we can
compile and generate MiniGUI functions library.

Many OSes (Operating System) development environments include cygwin
such as OSE. If there is not cygwin in your development environment, you
can download and install it from
[*http://www.cygwin.com*](http://www.cygwin.com). Please make sure you
have installed make tool, compiler and BASH shell script software
package and so on.

In MiniGUI source code, in order to compile MiniGUI conveniently in the
Non-GNU development environment, the following things have been done.

In order to distinguish makefile of cygwin from GNU makefile, the GNU
makefile is generated by configure tool, the makefile of cygwin has
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
Lastly, we compile MiniGUI using cygwin make command. For example, we
want to compile MiniGUI for VxWorks X86 platform (rules file
corresponding with **build/rules-pc.vxworks**[^7]), we need follow the
following step:

Copy build/config-vxworks-i386.h to MiniGUI source code top directory,
and rename it as mgconfig.h (we resume that current directory is MiniGUI
source code top directory):

cygwin\$ cp build/config-vxworks-i386.h mgconfig.h

Modify TARGET\_RULES value in rules.make file:

TARGET\_RULES=build/rules-pc.vxworks

Then we compile MiniGUI using make tool of cygwin:

cygwin\$ /usr/bin/make –f makefile.ng

Note that **makefile.ng** supports commands of clean and make. If you
execute the command as follow:

cygwin\$ /usr/bin/make –f makefile.ng install

You can install MiniGUI header files and library to the directory, which
is specified by **rules-&lt;platform&gt;.&lt;os&gt;**. If you execute
the command as the following:

cygwin\$ /usr/bin/make –f makefile.ng clean

You can clean all object files to compile afresh.

Note: if you modify **mgconfig.h** and other files in the cygwin
environment, first of all you execute the command above to clean all
object files, then compile MiniGUI afresh.

By using cygwin environment and **makefile.ng** to compile MiniGUI, our
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

\#vxworks

TARGET\_DIR=C:/Tornado2.2x86/target

INCS+=-I\${TARGET\_DIR}/h

CFLAGS+=-g -mcpu=pentium -march=pentium -Wall -DTOOL\_FAMILY=gnu
-DTOOL=gnu -D\_WRS\_KERNEL -DCPU=PENTIUM

Note that the make tool will install MiniGUI header files to the
**\$PREFIX/include/minigui** directory under the **makefile.ng** project
file of cygwin, the function libraries were installed to the
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

user\$ make –f makefile.ng

About other contents related with portion and configuration of MiniGUI,
please refer to Chapter 18 “*GAL and IAL Engines*” and Appendix A “*A
Universal Startup API for RTOSes*” in MiniGUI Programming Guide V3.0-5.

2.6 Use Ubuntu on Windows to configure and compile MiniGUI
----------------------------------------------------------

Specifically, since Windows 10, Microsoft has reinstated the
POSIX-compliant subsystem on the Windows platform with WSL(Windows
Subsystem for Linux) as well as an Ubuntu distribution through the
Microsoft Store. In this way, we can use the Ubuntu environment running
on Windows 10 to configure and compile MiniGUI. This will bring us a lot
of convenience because Ubuntu running on Windows is a complete GNU
development environment so we can use the GNU *autoconf/automake* script
to configure MiniGUI for operating systems like VxWorks and its
development environment.

---

[Previous Chapter](MiniGUIUserManualChapter1.md)  
[Table of Contents](README.md)  
[Next Chapter](MiniGUIUserManualChapter3.md)

[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[MiniGUI Official Website]: http://www.minigui.com
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md
