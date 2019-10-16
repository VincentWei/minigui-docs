3 MiniGUI runtime configuration options
=======================================

In this chapter, we describe the MiniGUI runtime configuration options,
which effect some actions about MiniGUI running, for example, running
GAL and IAL used, device font, bitmap, and cursor etc. It is known that
MiniGUI runtime configuration options is loaded from **MiniGUI.cfg**,
but if compiling MiniGUI with in-core options, the options is included
MiniGUI libraries.

MiniGUI.cfg

In GNU development environment, after installing MiniGUI by default
configuration, the file **etc/MiniGUI-classic.cfg** in MiniGUI source
tree will be installed in **/usr/local/etc/** directory, and rename to
**MiniGUI.cfg**. When MiniGUI application starts, It will find
MiniGUI.cfg as follow:

the application first search **MiniGUI.cfg** in current directory, then
search **.MiniGUI.cfg** in home directory.

then search **MiniGUI.cfg** in **/usr/local/etc**, at last in **/etc/**.

If user don’t create the file **MiniGUI.cfg** in current directory and
home directory, the application will use the file MiniGUI.cfg in
**/usr/local/etc/** as default configuration file.

When we compile MiniGUI with **--enable-incoreres** option, MiniGUI
application doesn’t need the file **MiniGUI.cfg**. The required options
are given in the file **src/sysres/mgetc.c**.

***Look And Feel Renderer***

MiniGUI 3.0 appearance of the window and the control drawing
implementation, using a completely different from the previous old
version of the implementation mechanism. Previous versions had to be
compiled and configured before compilation, the style was chosen, and
only one of three styles fashion, classic and flat was chosen. MiniGUI
3.0 uses Look And Feel renderer technology to draw the appearance of
windows and controls. MiniGUI support four kinds of renderers, in
practical applications choose one. The advantage of the renderer
technology is that the appearance can be modified through the
MiniGUI.cfg file, and the appearance can also be controlled by API. The
user can even customize its own renderer, which provides great
convenience for the application to flexibly customize its own appearance
based on the actual application environment. For details about MiniGUI
renderer interface, please refer to MiniGUI Programming Manual.

MiniGUI Look and Feel divide the window and control attribute to some
parts, and then use the drawing interface definition how to draw,
forming a complete set of appearance renderer mechanism. MiniGUI 3.0
provides four kinds of renderer: classic, flat, fashion, skin. classic
is the default renderer, that is when MiniGUI is initialized, the
classic renderer is used to draw windows and controls by default. The
fashion renderer needs support by mGPlus component. MiniGUI itself does
not provide support for the fashion renderer.

The application can choose to use a particular renderer for a window and
define the appearance of the window's elements. Applications can also
define their own renderer to draw.

This chapter first describes the runtime configuration options when
using configuration files and then describes how to specify runtime
configuration options in built-in resources.

Below, we first describe running configuration options with
configuration file, and with incore resources.

3.1 Configuration File
----------------------

The section describes configuration options in detail by
**MiniGUI.cfg**.

The format of configuration file is compact, and you can modify it
easily. The following shows the format.

\[section-name1\]

key-name1=key-value1

key-name2=key-value2

\[section-name2\]

key-name3=key-value3

key-name4=key-value4

The parameters in the configuration file are grouped in sections, such
as notation (\#), section, key, and key value. The line that the first
character is ‘\#’ is notation line. The values of the section are
specified in the form of **section-name**. The values of the key and key
value are specified in the form of **key=value**. Some important
sections are listed as follows.

### 3.1.1 Section system

The section **system** not only defines the graphics engine
(**gal\_engine**) and the input engine (**ial\_engine**) in runtime
MiniGUI, which must be one of engines configured on MiniGUI compiling,
but also defines the mouse device (**mdev**) and the mouse protocol type
(**mtype**).

The definition of the keys in section **system** is as follows:

**gal\_engine**: The graphics engine used.

**defaultmode**: The graphics engine display mode used, its format is
widthxheight-bpp.

**ial\_engine**: The input engine used.

**mdev**: The mouse device file.

**mtype**: The mouse protocol type.

The contents of the section **system** in **MiniGUI.cfg** are as follow:

\[system\]

\# GAL engine and default options

gal\_engine=qvfb

defaultmode=800x600-16bpp

\# IAL engine

ial\_engine=qvfb

mdev=/dev/input/mice

mtype=IMPS2

Since MiniGUI Version 1.6.8, you can modify the graphics and input
engine via environment variable. For example, if you define **fbcon**
and **qvfb** graphics engine and **console** and **qvfb** input engine,
and you choose the qvfb engine in **MiniGUI.cfg** or in-core resources.
Then when configure MiniGUI, you can change the engine to fbcon and
console in runtime by the following method, and needn’t modify
**MiniGUI.cfg** or in-core resources configuration file.

\$ export gal\_engine=fbcon

\$ export ial\_engine=console

\$ export mdev=/dev/input/mice

\$ export mtype=ps2

\$ export defaultmode=1024x768-16bpp

### 3.1.2 Section fbcon

The section **fbcon** is only available when you define the
**gal\_engine** in section **system** for fbcon. It define default
display mode of the **fbcon** engine. When the section is undefined or
key value is empty, the fbcon engine using the key value of system
section.

The definition of the key in section **fbcon** is as follows:

**defaultmode**: The display mode of graphics engine used, the format is
**widthxheight-bpp**.

The content of the section in **MiniGUI.cfg** is as follows:

\[fbcon\]

defaultmode=1024x768-16bpp

### 3.1.3 Section qvfb

The section **qvfb** is only available when you define the
**gal\_engine** in section **system** for qvfb. It shows display and
display mode of X window used when running qvfb.

The definition of the keys in section **qvfb** is as follows:

**defaultmode**: The display mode of graphics engine used, its format is
**widthxheight-bpp**.

**display**: Display mode of X window used when running qvfb, default
value is 0.

The content of the section in **MiniGUI.cfg** is as follows:

\[qvfb\]

defaultmode=640x480-16bpp

display=0

### 3.1.4 Section pc\_xvfb

The section pc\_x**vfb** is only available when you define the
**gal\_engine** in section **system** for pc\_xvfb. It has been
supported by Linux(Ubuntu) and Window.

The definition of the keys in section pc\_x**vfb** is as follows:

**defaultmode**: The display mode of graphics engine used, its format is
**widthxheight-bpp**.

**window\_caption**: Window caption title of XVFB window.

**exec\_file**: gvfb exe file path.

The content of the section in **MiniGUI.cfg** is as follows:

\#{{ifdef \_MGGAL\_PCXVFB

\[pc\_xvfb\]

defaultmode=800x600-16bpp

window\_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)

exec\_file=/usr/local/bin/gvfb

\#}}

### 3.1.5 Section rawbitmapfonts, varbitmapfonts, qpf, truetypefonts, and type1fonts

These sections define information of loading device fonts**,** number of
fonts, and name and file of fonts.

The format of device fonts used by MiniGUI is as follows:

&lt;type&gt;-&lt;facename&gt;-&lt;style&gt;-&lt;width&gt;-&lt;height&gt;-&lt;charset1\[,charset2,...\]&gt;

The definitions for each part of device **font** are as follow:

**&lt;type&gt;**: The type of device font, for example, RBF, VBF, QPF,
TrueType, and Adobe Type1 device font are rbf, vbf, qpf, ttf, and tlf.

**&lt;facename&gt;**: The name of device font. Such as courier, Times
etc.

**&lt;style&gt;**: The style of device font, it is grouped into six
alphabets. Such as bold, italic, underline or strikethrough etc.
Generally the string is "rrncnn".

**&lt;width&gt;**: The width of device font, for var-width fonts set to
be maximum width; for vector fonts set to be 0.

**&lt;height&gt;**: The height of device font, for vector fonts set to
be 0.

**&lt;charset1, charset2&gt;**: The charset of device font supported.

Each of these sections defines font\_number, name**&lt;NR&gt;**, and
fontfile**&lt;NR&gt;** keys.

**font\_number**: The number of device font loaded.

**name&lt;NR&gt;**: The name of device font that number is
**&lt;NR&gt;**.

**fontfile&lt;NR&gt;**: The font file of device font that number is
**&lt;nr&gt;**.

If you don't need to use a specific type of device font, you can skip
the configuration option by set **font\_number = 0**.

The content of these sections in **MiniGUI.cfg** are as follow:

\[rawbitmapfonts\]

font\_number=4

name0=rbf-fixed-rrncnn-8-16-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin

name1=rbf-fixed-rrncnn-16-16-GB2312-0

fontfile1=/usr/local/lib/minigui/res/font/song-16-gb2312.bin

name2=rbf-fixed-rrncnn-6-12-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/6x12-iso8859-1.bin

name3=rbf-fixed-rrncnn-12-12-GB2312-0

fontfile3=/usr/local/lib/minigui/res/font/song-12-gb2312.bin

\[varbitmapfonts\]

font\_number=6

name0=vbf-Courier-rrncnn-8-13-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/Courier-rr-8-13.vbf

name1=vbf-Helvetica-rrncnn-11-12-ISO8859-1

fontfile1=/usr/local/lib/minigui/res/font/Helvetica-rr-11-12.vbf

name2=vbf-Times-rrncnn-10-12-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/Times-rr-10-12.vbf

name3=vbf-Courier-rrncnn-10-15-ISO8859-1

fontfile3=/usr/local/lib/minigui/res/font/Courier-rr-10-15.vbf

name4=vbf-Helvetica-rrncnn-15-16-ISO8859-1

fontfile4=/usr/local/lib/minigui/res/font/Helvetica-rr-15-16.vbf

name5=vbf-Times-rrncnn-13-15-ISO8859-1

fontfile5=/usr/local/lib/minigui/res/font/Times-rr-13-15.vbf

\[upf\]

font\_number=0

\[qpf\]

font\_number=3

name0=qpf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312-0,GBK,BIG5

fontfile0=/usr/local/lib/minigui/res/font/unifont\_160\_50.qpf

name1=qpf-times-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile1=/usr/local/lib/minigui/res/font/smoothtimes\_100\_50.qpf

name2=qpf-helvetica-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile2=/usr/local/lib/minigui/res/font/helvetica\_100\_50.qpf

name3=qpf-micro-rrncnn-4-4-ISO8859-1,ISO8859-15

fontfile3=/usr/local/lib/minigui/res/font/micro\_40\_50.qpf

\[truetypefonts\]

font\_number=3

name0=ttf-arial-rrncnn-0-0-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/arial.ttf

name1=ttf-times-rrncnn-0-0-ISO8859-1

fontfile1=/usr/local/lib/minigui/res/font/times.ttf

name2=ttf-pinball-rrncnn-0-0-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/pinball.ttf

### 3.1.5 Section systemfont

The section **systemfont** defines MiniGUI system font and font number,
and defines system default font, which would be used to render text on
captions, menus, and controls, as well as the default font of a window.

System font is the logic font^10^ that is created by the function
**CreateLogFontFromName** based on device fonts, which is defined by
MiniGUI sections such as **rawbitmapfonts**, **varbitmapfonts**,
**qpf**, **truetypefonts**, and **t1fonts**.

The content of the section in **MiniGUI.cfg** is as follows:

&lt;type&gt;-&lt;facename&gt;-&lt;style&gt;-&lt;width&gt;-&lt;height&gt;-&lt;charset1&gt;

The definition of each part of a logic font name is as follows:

**&lt;type&gt;** is the desired device font type, if you do not want to
specify it, use **\***.

**&lt;facename&gt;** is to define the font face name, such as courier
and times etc.

**&lt;style&gt;** is the string of six alphabets to define style of a
logic font, such as italic, bold, underline or strikethrough etc.

**&lt;width&gt;** is to define the width of the logic font. Usually do
not need to specify, use **\*** instead.

**&lt;height&gt;** is to define the height of the logic font.

**&lt;charset&gt;** is to define charset of the logic font being
created.

Furthermore, MiniGUI V2.0.x provides auto-scaling the font glyph. If you
want to use this function, you only need use ‘S’ in forth character when
you define logical font styles. Note that you don’t need to use this
style when you use vector font, such as TrueType, because vector font
can produce corresponding font glyph according to desired logical font
size.

The definition of the keys in section **systemfont** is as follows:

**font\_number**: The number of system fonts created

**font&lt;NR&gt;**: The number &lt;NR&gt; logical font name

**default**: System default font(single character set). Its value is the
number of logical font.

**wchar\_def**: Default font used by multiple character set. Its value
is the number of above logical font.

**fixed**: The font used by fixed width character set. Its value is the
number of above logical font.

**caption**: The caption font. Its value is the number of above logical
font.

**menu**: The menu font. Its value is the number of above logical font.

You can change the number of system font created. But you must create a
single character set (for example: ISO8859-1) at least. MiniGUI defines
the system default charsets according to **default**, **wchar\_def**
system fonts, and this would affect the return value of
**GetSysCharset**, **GetSysCharWidth**, **GetSysCCharWidth** and
**GetSysHeight** functions. Commonly, **default** and **wchar\_def**
must fixed width dot-matrix font, i.e RBF. And the width of multiply
character set must be twice with the width of single character set.

The content of the section in **MiniGUI.cfg** is as follows:

\# The first system font must be a logical font using RBF device font.

\[systemfont\]

font\_number=6

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

font1=\*-fixed-rrncnn-\*-16-GB2312

font2=\*-Courier-rrncnn-\*-16-GB2312

font3=\*-SansSerif-rrncnn-\*-16-GB2312

font4=\*-Times-rrncnn-\*-16-GB2312

font5=\*-Helvetica-rrncnn-\*-16-GB2312

default=0

wchar\_def=1

fixed=1

caption=2

menu=3

control=3

### 3.1.6 Section mouse

The section **mouse** defines the time of mouse **double clicked**. It
is used to handle with system inner events. Generally, it is unnecessary
changed.

The definition of the keys in the section is as follows:

**dblclicktime**: The mouse double clicked time in ms

The content of the section in **MiniGUI.cfg** is as follows:

\[mouse\]

dblclicktime=300

### 3.1.7 Section event

The section **event** defines event timeout and auto-repeat time used by
system internal event process. Generally, it is unnecessary changed.

The definition of the keys in the section is as follows:

**timeoutusec**: Event timeout time in ms

**repeatusec**: Event repeat time in ms

The content of the section in **MiniGUI.cfg** is as follows:

timeoutusec=300000

repeatusec=50000

### 3.1.8 Section classic

The section **classic** defines default window element color used.
Generally, it is unnecessary changed.

Table 3.1 window element division and name in the configuration file and
code

  **Configure Option**       **Code name**                    **Comment**
  -------------------------- -------------------------------- ----------------------------------------------------------------------------------------------------
  caption                    WE\_METRICS\_CAPTION             Caption size
                             WE\_FONT\_CAPTION                Caption fonts
  fgc\_active\_caption       WE\_FGC\_ACTIVE\_CAPTION         Focus status caption foreground color
  bgca\_active\_caption      WE\_BGCA\_ACTIVE\_CAPTION        Focus status caption background color gradient starting color
  bgcb\_active\_caption      WE\_BGCB\_ACTIVE\_CAPTION        Focus Status caption background color gradient ending Color
  fgc\_inactive\_caption     WE\_FGC\_INACTIVE\_CAPTION       Non-focus status caption foreground color
  bgca\_inactive\_caption    WE\_BGCA\_INACTIVE\_CAPTION      Non-focus status caption background color gradient starting color
  bgcb\_inactive\_caption    WE\_BGCB\_INACTIVE\_CAPTION      Non-focus status caption background color gradient ending color
  menu                       WE\_METRICS\_MENU                Menu item, height of the menu bar
                             WE\_FONT\_MENU                   Menu font
  fgc\_menu                  WE\_FGC\_MENU                    Menu foreground color
  bgc\_menu                  WE\_BGC\_MENU                    Menu background color
  border                     WE\_METRICS\_WND\_BORDER         Window border width
  fgc\_active\_border        WE\_FGC\_ACTIVE\_WND\_BORDER     Focus status window border color
  fgc\_inactive\_border      WE\_FGC\_INACTIVE\_WND\_BORDER   Non-focus status window border color
  scrollbar                  WE\_METRICS\_SCROLLBAR           Scroll bar size
  fgc\_msgbox                WE\_FGC\_MESSAGEBOX              Message box foreground color
  fgc\_msgbox                WE\_FONT\_MESSAGEBOX             Message box font
  fgc\_tip                   WE\_FGC\_TOOLTIP                 Prompt box foreground color
  bgc\_tip                   WE\_BGC\_TOOLTIP                 Prompt box background color
                             WE\_FONT\_TOOLTIP                Prompt box font
  fgc\_window                WE\_FGC\_WINDOW                  Window foreground
  bgc\_window                WE\_BGC\_WINDOW                  Window background color
  fgc\_3dbox                 WE\_FGC\_THREED\_BODY            The color of the symbol on the surface of the 3D box, such as the color of check mark, arrow, etc.
  mainc\_3dbox               WE\_MAINC\_THREED\_BODY          Three-dimensional box border and surface color
  fgc\_selected\_item        WE\_FGC\_SELECTED\_ITEM          The foreground color of the selected menu item (list item)
  bgc\_selected\_item        WE\_BGC\_SELECTED\_ITEM          The background color of the selected menu item (list item)
  bgc\_selected\_lostfocus   WE\_BGC\_SELECTED\_LOSTFOCUS     The background color after the selected menu item (list item) loses focus
  fgc\_disabled\_item        WE\_FGC\_DISABLED\_ITEM          Foreground color of invalid menu item (list item)
  bgc\_disabled\_item        WE\_BGC\_DISABLED\_ITEM          Invalid menu item (list item) background color
  fgc\_hilight\_item         WE\_FGC\_HIGHLIGHT\_ITEM         Highlight the foreground color of the menu item (list item)
  bgc\_hilight\_item         WE\_BGC\_HIGHLIGHT\_ITEM         Highlight the background color of the menu item (list item)
  fgc\_significant\_item     WE\_FGC\_SIGNIFICANT\_ITEM       Foreground color of important menu item (list item)
  bgc\_significant\_item     WE\_BGC\_SIGNIFICANT\_ITEM       Background color of important menu items (list items)
  bgc\_desktop               WE\_BGC\_DESKTOP                 Desktop background color

The content of the section in **MiniGUI.cfg** is as follows:

\[classic\]

\# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

\# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

\# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

\# bitmap used by BUTTON control

radiobutton=classic\_radio\_button.bmp

checkbutton=classic\_check\_button.bmp

\# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

\#window element metrics

caption=20

menu=25

border=2

scrollbar=16

\#window element colors

fgc\_active\_caption=0xFFFFFFFF

bgca\_active\_caption=0xFF6A240A

bgcb\_active\_caption=0xFF6A240A

fgc\_menu=0xFF000000

bgc\_menu=0xFFCED3D6

fgc\_msgbox=0xFF000000

fgc\_tip=0xFF000000

bgc\_tip=0xFFE7FFFF

fgc\_active\_border=0xFFCED3D6

fgc\_inactive\_border=0xFFCED3D6

fgc\_inactive\_caption=0xFFC8D0D4

bgca\_inactive\_caption=0xFF808080

bgcb\_inactive\_caption=0xFF808080

fgc\_window=0xFF000000

bgc\_window=0xFFFFFFFF

fgc\_3dbox=0xFF000000

mainc\_3dbox=0xFFCED3D6

fgc\_selected\_item=0xFFFFFFFF

bgc\_selected\_item=0xFF6B2408

bgc\_selected\_lostfocus=0xFFBDA69C

fgc\_disabled\_item=0xFF848284

bgc\_disabled\_item=0xFFCED3D6

fgc\_hilight\_item=0xFFFFFFFF

bgc\_hilight\_item=0xFF6B2408

fgc\_significant\_item=0xFFFFFFFF

bgc\_significant\_item=0xFF6B2408

bgc\_desktop=0xFFC08000

### 3.1.9 Default Configuration File

Below is the default runtime configuration file for MiniGUI library:

\# MiniGUI Ver 3.0.x

\# This configuration file is for classic window style.

\#

\# Copyright (C) 2002\~2017 Feynman Software

\# Copyright (C) 1998\~2002 Wei Yongming.

\#

\# Web: http://www.minigui.com

\# Web: http://www.minigui.org

\#

\# This configuration file must be installed in /etc,

\# /usr/local/etc or your home directory. When you install it in your

\# home directory, it should be named ".MiniGUI.cfg".

\#

\# The priority of above configruation files is \~/.MiniGUI.cfg,

\# /usr/local/etc/MiniGUI.cfg, and then /etc/MiniGUI.cfg.

\#

\# If you change the install path of MiniGUI resource, you should

\# modify this file to meet your configuration.

\#

\# NOTE:

\# The format of this configuration file has changed since the last
release.

\# Please DONT forget to provide the latest MiniGUI.cfg file for your
MiniGUI.

\#

\[system\]

\# GAL engine and default options

gal\_engine=pc\_xvfb

defaultmode=800x600-16bpp

\# IAL engine

ial\_engine=pc\_xvfb

mdev=/dev/input/mice

mtype=IMPS2

\[fbcon\]

defaultmode=1024x768-16bpp

\[qvfb\]

defaultmode=640x480-16bpp

display=0

\#{{ifdef \_MGGAL\_PCXVFB

\[pc\_xvfb\]

defaultmode=800x600-16bpp

window\_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)

exec\_file=/usr/local/bin/gvfb

\#}}

\# The first system font must be a logical font using RBF device font.

\[systemfont\]

font\_number=6

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

font1=\*-fixed-rrncnn-\*-16-GB2312

font2=\*-Courier-rrncnn-\*-16-GB2312

font3=\*-SansSerif-rrncnn-\*-16-GB2312

font4=\*-Times-rrncnn-\*-16-GB2312

font5=\*-Helvetica-rrncnn-\*-16-GB2312

default=0

wchar\_def=1

fixed=1

caption=2

menu=3

control=3

\[rawbitmapfonts\]

font\_number=4

name0=rbf-fixed-rrncnn-8-16-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin

name1=rbf-fixed-rrncnn-16-16-GB2312-0

fontfile1=/usr/local/lib/minigui/res/font/song-16-gb2312.bin

name2=rbf-fixed-rrncnn-6-12-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/6x12-iso8859-1.bin

name3=rbf-fixed-rrncnn-12-12-GB2312-0

fontfile3=/usr/local/lib/minigui/res/font/song-12-gb2312.bin

\[varbitmapfonts\]

font\_number=6

name0=vbf-Courier-rrncnn-8-13-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/Courier-rr-8-13.vbf

name1=vbf-Helvetica-rrncnn-11-12-ISO8859-1

fontfile1=/usr/local/lib/minigui/res/font/Helvetica-rr-11-12.vbf

name2=vbf-Times-rrncnn-10-12-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/Times-rr-10-12.vbf

name3=vbf-Courier-rrncnn-10-15-ISO8859-1

fontfile3=/usr/local/lib/minigui/res/font/Courier-rr-10-15.vbf

name4=vbf-Helvetica-rrncnn-15-16-ISO8859-1

fontfile4=/usr/local/lib/minigui/res/font/Helvetica-rr-15-16.vbf

name5=vbf-Times-rrncnn-13-15-ISO8859-1

fontfile5=/usr/local/lib/minigui/res/font/Times-rr-13-15.vbf

\[qpf\]

font\_number=3

name0=qpf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312-0,GBK,BIG5

fontfile0=/usr/local/lib/minigui/res/font/unifont\_160\_50.qpf

name1=qpf-times-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile1=/usr/local/lib/minigui/res/font/smoothtimes\_100\_50.qpf

name2=qpf-helvetica-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile2=/usr/local/lib/minigui/res/font/helvetica\_100\_50.qpf

name3=qpf-micro-rrncnn-4-4-ISO8859-1,ISO8859-15

fontfile3=/usr/local/lib/minigui/res/font/micro\_40\_50.qpf

\[upf\]

font\_number=0

\[truetypefonts\]

font\_number=3

name0=ttf-arial-rrncnn-0-0-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/arial.ttf

name1=ttf-times-rrncnn-0-0-ISO8859-1

fontfile1=/usr/local/lib/minigui/res/font/times.ttf

name2=ttf-pinball-rrncnn-0-0-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/pinball.ttf

\[mouse\]

dblclicktime=300

\[event\]

timeoutusec=300000

repeatusec=50000

\[cursorinfo\]

\# Edit following line to specify cursor files path

cursorpath=/usr/local/lib/minigui/res/cursor/

cursornumber=23

cursor0=d\_arrow.cur

cursor1=d\_beam.cur

cursor2=d\_pencil.cur

cursor3=d\_cross.cur

cursor4=d\_move.cur

cursor5=d\_sizenwse.cur

cursor6=d\_sizenesw.cur

cursor7=d\_sizewe.cur

cursor8=d\_sizens.cur

cursor9=d\_uparrow.cur

cursor10=d\_none.cur

cursor11=d\_help.cur

cursor12=d\_busy.cur

cursor13=d\_wait.cur

cursor14=g\_rarrow.cur

cursor15=g\_col.cur

cursor16=g\_row.cur

cursor17=g\_drag.cur

cursor18=g\_nodrop.cur

cursor19=h\_point.cur

cursor20=h\_select.cur

cursor21=ho\_split.cur

cursor22=ve\_split.cur

\[resinfo\]

respath=/usr/local/share/minigui/res/

\[classic\]

\# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

\# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

\# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

\# bitmap used by BUTTON control

radiobutton=classic\_radio\_button.bmp

checkbutton=classic\_check\_button.bmp

\# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

\# bgpicpos=upleft

\# bgpicpos=downleft

\# bgpicpos=upright

\# bgpicpos=downright

\# bgpicpos=upcenter

\# bgpicpos=downcenter

\# bgpicpos=vcenterleft

\# bgpicpos=vcenterright

\# bgpicpos=none

\#window element metrics

caption=20

menu=25

border=2

scrollbar=16

\#window element colors

fgc\_active\_caption=0xFFFFFFFF

bgca\_active\_caption=0xFF6A240A

bgcb\_active\_caption=0xFF6A240A

fgc\_menu=0xFF000000

bgc\_menu=0xFFCED3D6

fgc\_msgbox=0xFF000000

fgc\_tip=0xFF000000

bgc\_tip=0xFFE7FFFF

fgc\_active\_border=0xFFCED3D6

fgc\_inactive\_border=0xFFCED3D6

fgc\_inactive\_caption=0xFFC8D0D4

bgca\_inactive\_caption=0xFF808080

bgcb\_inactive\_caption=0xFF808080

fgc\_window=0xFF000000

bgc\_window=0xFFFFFFFF

fgc\_3dbox=0xFF000000

mainc\_3dbox=0xFFCED3D6

fgc\_selected\_item=0xFFFFFFFF

bgc\_selected\_item=0xFF6B2408

bgc\_selected\_lostfocus=0xFFBDA69C

fgc\_disabled\_item=0xFF848284

bgc\_disabled\_item=0xFFCED3D6

fgc\_hilight\_item=0xFFFFFFFF

bgc\_hilight\_item=0xFF6B2408

fgc\_significant\_item=0xFFFFFFFF

bgc\_significant\_item=0xFF6B2408

bgc\_desktop=0xFFC08000

\#{{ifdef \_MGLF\_RDR\_FLAT

\[flat\]

\# Note that max number defined in source code is 5.

iconnumber=5

icon0=form-flat.ico

icon1=failed-flat.ico

icon2=help-flat.ico

icon3=warning-flat.ico

icon4=excalmatory-flat.ico

\# default icons for new OpenFileDialogBox

dir=folder-flat.ico

file=textfile-flat.ico

\# default icons for TreeView control

treefold=fold-flat.ico

treeunfold=unfold-flat.ico

\# bitmap used by BUTTON control

radiobutton=flat\_radio\_button.bmp

checkbutton=flat\_check\_button.bmp

\# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

\#window element metrics

caption=20

menu=25

border=1

scrollbar=16

\#window element colors

fgc\_active\_caption=0xFFFFFFFFF

bgca\_active\_caption=0xFF000000

bgcb\_active\_caption=0xFF000000

fgc\_inactive\_caption=0xFF000000

bgca\_inactive\_caption=0xFFFFFFFF

bgcb\_inactive\_caption=0xFFFFFFFF

fgc\_menu=0xFF000000

bgc\_menu=0xFFD8D8D8

fgc\_msgbox=0xFF000000

fgc\_tip=0xFF000000

bgc\_tip=0xFFE7FFFF

fgc\_active\_border=0xFF000000

fgc\_inactive\_border=0xFF848284

fgc\_window=0xFF000000

bgc\_window=0xFFFFFFFF

fgc\_3dbox=0xFF000000

mainc\_3dbox=0xFFFFFFFF

fgc\_selected\_item=0xFFFFFFFF

bgc\_selected\_item=0xFF000000

bgc\_selected\_lostfocus=0xFFBDA69C

fgc\_disabled\_item=0xFF848284

bgc\_disabled\_item=0xFF000000

fgc\_hilight\_item=0xFFFFFFFF

bgc\_hilight\_item=0xFF664E4A

fgc\_significant\_item=0xFFFFFFFF

bgc\_significant\_item=0xFF000000

bgc\_desktop=0xFFC08000

flat\_tab\_normal\_color=0xFFC6D2CF

\#}}

\#{{ifdef \_MGLF\_RDR\_SKIN

\[skin\]

\# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

\# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

\# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

\# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

\#window element metrics

caption=25

menu=25

border=1

scrollbar=17

fgc\_active\_caption=0xFFFFFFFF

bgca\_active\_caption=0xFFE35400

bgcb\_active\_caption=0xFF686868

fgc\_menu=0xFF000000

bgc\_menu=0xFFD4D6FF

fgc\_msgbox=0xFF000000

fgc\_tip=0xFF000000

bgc\_tip=0xFFFFFFFF

fgc\_active\_border=0xFFC8D0D4

fgc\_inactive\_border=0xFFC8D0D4

fgc\_inactive\_caption=0xFFF8E4D8

bgca\_inactive\_caption=0xFFDF967A

bgcb\_inactive\_caption=0xFF686868

fgc\_window=0xFF000000

bgc\_window=0xFFFFFFFF

fgc\_3dbox=0xFF000000

mainc\_3dbox=0xFFD8E9EC

fgc\_selected\_item=0xFFFFFFFF

bgc\_selected\_item=0xFFC56A31

bgc\_selected\_lostfocus=0xFFD8E9EC

fgc\_disabled\_item=0xFF99A8AC

bgc\_disabled\_item=0xFFFFFFFF

fgc\_hilight\_item=0xFFFFFFFF

bgc\_hilight\_item=0xFFC56A31

fgc\_significant\_item=0xFFFFFFFF

bgc\_significant\_item=0xFFC56A31

bgc\_desktop=0xFF984E00

skin\_bkgnd=skin\_bkgnd.bmp

skin\_caption=skin\_caption.gif

skin\_caption\_btn=skin\_cpn\_btn.gif

\#for scrollbar

skin\_scrollbar\_hshaft=skin\_sb\_hshaft.bmp

skin\_scrollbar\_vshaft=skin\_sb\_vshaft.bmp

skin\_scrollbar\_hthumb=skin\_sb\_hthumb.bmp

skin\_scrollbar\_vthumb=skin\_sb\_vthumb.bmp

skin\_scrollbar\_arrows=skin\_sb\_arrows.bmp

\#for border

skin\_tborder=skin\_tborder.bmp

skin\_bborder=skin\_bborder.bmp

skin\_lborder=skin\_lborder.bmp

skin\_rborder=skin\_rborder.bmp

skin\_arrows=skin\_arrows.gif

skin\_arrows\_shell=skin\_arrows\_shell.bmp

skin\_pushbtn=skin\_pushbtn.gif

skin\_radiobtn=skin\_radiobtn.gif

skin\_checkbtn=skin\_checkbtn.bmp

\#for treeview

skin\_tree=skin\_tree.bmp

skin\_header=skin\_header.bmp

skin\_tab=skin\_tab.gif

\#for trackbar

skin\_tbslider\_h=skin\_tbslider\_h.gif

skin\_tbslider\_v=skin\_tbslider\_v.gif

skin\_trackbar\_horz=skin\_tb\_horz.gif

skin\_trackbar\_vert=skin\_tb\_vert.gif

\#for progressbar

skin\_progressbar\_htrack=skin\_pb\_htrack.gif

skin\_progressbar\_vtrack=skin\_pb\_vtrack.gif

skin\_progressbar\_hchunk=skin\_pb\_htruck.bmp

skin\_progressbar\_vchunk=skin\_pb\_vtruck.bmp

\#}}

\[fashion\]

\# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

\# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

\# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

\# bitmap used by BUTTON control

radiobutton=fashion\_radio\_btn.bmp

checkbutton=fashion\_check\_btn.bmp

\# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

\#window element metrics

caption=25

menu=25

border=1

scrollbar=17

fgc\_active\_caption=0xFFFFFFFF

bgca\_active\_caption=0xFFE35400

bgcb\_active\_caption=0xFFFF953D

fgc\_menu=0xFF000000

bgc\_menu=0xFFFFE4BF

fgc\_msgbox=0xFF000000

fgc\_tip=0xFF000000

bgc\_tip=0xFFFFFFFF

fgc\_active\_border=0xFFC8D0D4

fgc\_inactive\_border=0xFFC8D0D4

fgc\_inactive\_caption=0xFFF8E4D8

bgca\_inactive\_caption=0xFFDF967A

bgcb\_inactive\_caption=0xFFEBB99D

fgc\_window=0xFF000000

bgc\_window=0xFFEBB99D

fgc\_3dbox=0xFF000000

mainc\_3dbox=0xFFD8E9EC

fgc\_selected\_item=0xFFFFFFFF

bgc\_selected\_item=0xFFC56A31

bgc\_selected\_lostfocus=0xFFD8E9EC

fgc\_disabled\_item=0xFF99A8AC

bgc\_disabled\_item=0xFFFFFFFF

fgc\_hilight\_item=0xFFFFFFFF

bgc\_hilight\_item=0xFFC56A31

fgc\_significant\_item=0xFFFFFFFF

bgc\_significant\_item=0xFFC56A31

bgc\_desktop=0xFF984E00

3.2 Incore Configuration Options
--------------------------------

When use incore resources, MiniGUI don’t need the file **MiniGUI.cfg**.
The appropriate configuration options are defined in the file
**src/sysres/mgetc.c**.

Similar with the structure in **MiniGUI.cfg**, MiniGUI defines an
structure ETCSECTION, array **\_etc\_sections** and variable MGETC in
**mgetc.c**. The array mgetc\_sections is appropriate with section in
configuration file. MGETC that is ETC\_S type is appropriate with
configuration file.

### 3.2.1 Structure ETCSETCTION

The structure **ETCSECTION** is defined in the file named
‘**minigui.h**’. The following is in detail.

/\*\* Etc The current config section information \*/

typedef struct \_ETCSECTION

{

/\*\* Allocated number of keys \*/

int key\_nr\_alloc;

/\*\* Key number in the section \*/

int key\_nr;

/\*\* Name of the section \*/

char \*name;

/\*\* Array of keys \*/

char\*\* keys;

/\*\* Array of values \*/

char\*\* values;

} ETCSECTION;

The **key\_nr\_alloc** is the interface of other configuration options.
Its value must be 0 in incore. The **key\_nr** defines the number of the
key in section. The name defines the name of section. The keys and
values is the array of key and value. The number of key array and value
array is corresponded with the number of the **key\_nr**.

Below is the definition of \_etc\_sections in the **mgetc.c** file.

static ETCSECTION \_etc\_sections \[\] = {

{0, 5, "system", \_system\_keys,\_system\_values },

{0, 1, "fbcon", \_fbcon\_keys,\_fbcon\_values },

{0, 2, "qvfb", \_qvfb\_keys,\_qvfb\_values },

\#ifdef \_MGGAL\_PCXVFB

{0, 3, "pc\_xvfb", \_pc\_xvfb\_keys,\_pc\_xvfb\_values },

\#endif

{0, 1, "rtos\_xvfb", \_rtos\_xvfb\_keys,\_rtos\_xvfb\_values },

\#ifdef \_MGGAL\_SHADOW

{0, 3, "shadow", \_shadow\_keys,\_shadow\_values },

\#endif

\#ifdef \_MGGAL\_MLSHADOW

{0, 4, "mlshadow", \_mlshadow\_keys,\_mlshadow\_values },

\#endif

{0, 12, "systemfont", \_systemfont\_keys,\_systemfont\_values },

{0, 1, "rawbitmapfonts", \_rawbitmapfonts\_keys,\_rawbitmapfonts\_values
},

{0, 1, "varbitmapfonts", \_varbitmapfonts\_keys,\_varbitmapfonts\_values
},

{0, 1, "upf", \_upf\_keys,\_upf\_values },

{0, 1, "qpf", \_qpf\_keys,\_qpf\_values },

{0, 1, "truetypefonts", \_truetypefonts\_keys,\_truetypefonts\_values },

{0, 1, "mouse", \_mouse\_keys,\_mouse\_values },

{0, 2, "event", \_event\_keys,\_event\_values },

{0, 25, "cursorinfo", \_cursorinfo\_keys,\_cursorinfo\_values },

{0, 1, "resinfo", \_resinfo\_keys,\_resinfo\_values },

{0, 45, "classic", \_classic\_keys,\_classic\_values },

\#ifdef \_MGLF\_RDR\_FLAT

{0, 46, "flat", \_flat\_keys,\_flat\_values },

\#endif

\#ifdef \_MGLF\_RDR\_SKIN

{0, 71, "skin", \_skin\_keys,\_skin\_values },

\#endif

{0, 45, "fashion", \_fashion\_keys,\_fashion\_values }

};

The section in **\_etc\_sections** must be defined (fbcon or qvfb is
optional.). Other notation sections are optional. The meaning of
sections is same as the sections in MiniGUI.cfg. Commonly, you can only
change the GAL engine, the IAL engine, display mode and the sections of
system and fbcon: SYSTEM\_VALUES and FBCON\_VALUES defined in the
**mgetc-xxx.c** file, such as **mgetc-pc.c**.

The **systemfont** section defines incore font used by system.
Currently, MiniGUI 3.0.x supports ISO8859-1, GB2312, RBF, BIG5,
SHIFT\_JIS, and QPF. MiniGUI doesn’t support the TTF and Type1 font in
incore resources.

### 3.2.2 ETC\_S Structure

**ETC\_S** structure was defined in the file minigui.h, the content of
ETC\_S listed as the follow:

/\*\* ETC\_S The current config file information\*/

typedef struct \_ETC\_S

{

/\*\* Allocated number of sections \*/

int sect\_nr\_alloc;

/\*\* Number of sections \*/

int section\_nr;

/\*\* Pointer to section arrays \*/

PETCSECTION sections;

} ETC\_S;

Therefore, **sect\_nr\_alloc** is the interface of the other
configuration options, it’s value must be 0 in incore, **sect\_nr**
specify the number of section, sections is ETCSECTION type structure
array, the number of item is not less than the value, the first item
specified this value.

The **mgetc\_sections** array was defined as the follow in the
**mgetc.c** file.

static ETC\_S \_ETC = {

0,

sizeof(\_etc\_sections)/sizeof(ETCSECTION),

\_etc\_sections

};

The number of section is sizeof(\_etc\_sections)/sizeof(ETCSECTION) in
the MGETC structure; the section array is mgetc\_sections array above.

### 3.2.3 Listing of mgetc.c

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

\* This is inside mode of system res configuation \*

\* It's generated by the mgcfg-trans, version 1.0 \*

\* author : dongjunjie in feynman \*

\* please donnot modify this file, if you want, \*

\* please change your input file and regenerate \*

\* this file \*

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

\#include &lt;stdio.h&gt;

\#include "common.h"

\#include "minigui.h"

\#ifdef \_MGINCORE\_RES

// This configuration file is for MiniGUI V3.0.x

//

// Copyright (C) 2002\~2008 Feynman Software

// Copyright (C) 1998\~2002 Wei Yongming.

//

// Web: http://www.minigui.com

//

// This configuration file must be installed in /etc,

// /usr/local/etc or your home directory. When you install it in your

// home directory, it should be named ".MiniGUI.cfg".

//

// The priority of above configruation files is \~/.MiniGUI.cfg,

// /usr/local/etc/MiniGUI.cfg, and then /etc/MiniGUI.cfg.

//

// If you change the install path of MiniGUI resource, you should

// modify this file to meet your configuration.

//

// NOTE:

// The format of this configuration file has changed since the last
release.

// Please DONT forget to provide the latest MiniGUI.cfg file for your
MiniGUI.

//

// Section: system

static char\* \_system\_keys\[\]={

// GAL engine and default options

"gal\_engine",

"defaultmode",

// IAL engine

"ial\_engine",

"mdev",

"mtype"

};

static char\* \_system\_values\[\]={

// GAL engine and default options

"pc\_xvfb",

"800x600-16bpp",

// IAL engine

"pc\_xvfb",

"/dev/input/mice",

"IMPS2"

};

// Section: fbcon

static char\* \_fbcon\_keys\[\]={

"defaultmode"

};

static char\* \_fbcon\_values\[\]={

"1024x768-16bpp"

};

// Section: qvfb

static char\* \_qvfb\_keys\[\]={

"defaultmode",

"display"

};

static char\* \_qvfb\_values\[\]={

"640x480-16bpp",

"0"

};

\#ifdef \_MGGAL\_PCXVFB

// Section: pc\_xvfb

static char\* \_pc\_xvfb\_keys\[\]={

"defaultmode",

"window\_caption",

"exec\_file"

};

static char\* \_pc\_xvfb\_values\[\]={

"800x600-16bpp",

"XVFB-for-MiniGUI-3.0-(Gtk-Version)",

"/usr/local/bin/gvfb"

};

\#endif

// Section: rtos\_xvfb

static char\* \_rtos\_xvfb\_keys\[\]={

"defaultmode"

};

static char\* \_rtos\_xvfb\_values\[\]={

"800x600-16bpp"

};

\#ifdef \_MGGAL\_SHADOW

// Section: shadow

static char\* \_shadow\_keys\[\]={

"real\_engine",

"defaultmode",

"rotate\_screen"

};

static char\* \_shadow\_values\[\]={

"pc\_xvfb",

"800x600-16bpp",

"normal"

};

\#endif

\#ifdef \_MGGAL\_MLSHADOW

// Section: mlshadow

static char\* \_mlshadow\_keys\[\]={

"real\_engine",

"defaultmode",

"def\_bgcolor",

"double\_buffer"

};

static char\* \_mlshadow\_values\[\]={

"qvfb",

"800x600-16bpp",

"0x00FF00",

"enable"

};

\#endif

// The first system font must be a logical font using RBF device font.

// Section: systemfont

static char\* \_systemfont\_keys\[\]={

"font\_number",

"font0",

"font1",

"font2",

"font3",

"font4",

"default",

"wchar\_def",

"fixed",

"caption",

"menu",

"control"

};

static char\* \_systemfont\_values\[\]={

"5",

"rbf-FixedSys-rrncnn-8-16-ISO8859-1",

"\*-FixedSys-rrncnn-\*-16-ISO8859-1",

"\*-Courier-rrncnn-\*-16-ISO8859-1",

"\*-SansSerif-rrncnn-\*-16-ISO8859-1",

"\*-System-rrncnn-\*-16-ISO8859-1",

"0",

"4",

"1",

"4",

"2",

"3"

};

// Section: rawbitmapfonts

static char\* \_rawbitmapfonts\_keys\[\]={

"font\_number"

};

static char\* \_rawbitmapfonts\_values\[\]={

"0"

};

// Section: varbitmapfonts

static char\* \_varbitmapfonts\_keys\[\]={

"font\_number"

};

static char\* \_varbitmapfonts\_values\[\]={

"0"

};

// Section: upf

static char\* \_upf\_keys\[\]={

"font\_number"

};

static char\* \_upf\_values\[\]={

"0"

};

// Section: qpf

static char\* \_qpf\_keys\[\]={

"font\_number"

};

static char\* \_qpf\_values\[\]={

"0"

};

// Section: truetypefonts

static char\* \_truetypefonts\_keys\[\]={

"font\_number"

};

static char\* \_truetypefonts\_values\[\]={

"0"

};

// Section: mouse

static char\* \_mouse\_keys\[\]={

"dblclicktime"

};

static char\* \_mouse\_values\[\]={

"300"

};

// Section: event

static char\* \_event\_keys\[\]={

"timeoutusec",

"repeatusec"

};

static char\* \_event\_values\[\]={

"300000",

"50000"

};

// Section: cursorinfo

static char\* \_cursorinfo\_keys\[\]={

// Edit following line to specify cursor files path

"cursorpath",

"cursornumber",

"cursor0",

"cursor1",

"cursor2",

"cursor3",

"cursor4",

"cursor5",

"cursor6",

"cursor7",

"cursor8",

"cursor9",

"cursor10",

"cursor11",

"cursor12",

"cursor13",

"cursor14",

"cursor15",

"cursor16",

"cursor17",

"cursor18",

"cursor19",

"cursor20",

"cursor21",

"cursor22"

};

static char\* \_cursorinfo\_values\[\]={

// Edit following line to specify cursor files path

"/usr/local/share/minigui/res/cursor/",

"23",

"d\_arrow.cur",

"d\_beam.cur",

"d\_pencil.cur",

"d\_cross.cur",

"d\_move.cur",

"d\_sizenwse.cur",

"d\_sizenesw.cur",

"d\_sizewe.cur",

"d\_sizens.cur",

"d\_uparrow.cur",

"d\_none.cur",

"d\_help.cur",

"d\_busy.cur",

"d\_wait.cur",

"g\_rarrow.cur",

"g\_col.cur",

"g\_row.cur",

"g\_drag.cur",

"g\_nodrop.cur",

"h\_point.cur",

"h\_select.cur",

"ho\_split.cur",

"ve\_split.cur"

};

// Section: resinfo

static char\* \_resinfo\_keys\[\]={

"respath"

};

static char\* \_resinfo\_values\[\]={

"/usr/local/share/minigui/res/"

};

// Section: classic

static char\* \_classic\_keys\[\]={

// Note that max number defined in source code is 5.

"iconnumber",

"icon0",

"icon1",

"icon2",

"icon3",

"icon4",

// default icons for new OpenFileDialogBox

"dir",

"file",

// default icons for TreeView control

"treefold",

"treeunfold",

// bitmap used by BUTTON control

"radiobutton",

"checkbutton",

// background picture, use your favirate photo

"bgpicture",

"bgpicpos",

// bgpicpos=upleft

// bgpicpos=downleft

// bgpicpos=upright

// bgpicpos=downright

// bgpicpos=upcenter

// bgpicpos=downcenter

// bgpicpos=vcenterleft

// bgpicpos=vcenterright

// bgpicpos=none

//window element metrics

"caption",

"menu",

"border",

"scrollbar",

//window element colors

"fgc\_active\_caption",

"bgca\_active\_caption",

"bgcb\_active\_caption",

"fgc\_menu",

"bgc\_menu",

"fgc\_msgbox",

"fgc\_tip",

"bgc\_tip",

"fgc\_active\_border",

"fgc\_inactive\_border",

"fgc\_inactive\_caption",

"bgca\_inactive\_caption",

"bgcb\_inactive\_caption",

"fgc\_window",

"bgc\_window",

"fgc\_3dbox",

"mainc\_3dbox",

"fgc\_selected\_item",

"bgc\_selected\_item",

"bgc\_selected\_lostfocus",

"fgc\_disabled\_item",

"bgc\_disabled\_item",

"fgc\_hilight\_item",

"bgc\_hilight\_item",

"fgc\_significant\_item",

"bgc\_significant\_item",

"bgc\_desktop"

};

static char\* \_classic\_values\[\]={

// Note that max number defined in source code is 5.

"5",

"form.ico",

"failed.ico",

"help.ico",

"warning.ico",

"excalmatory.ico",

// default icons for new OpenFileDialogBox

"folder.ico",

"textfile.ico",

// default icons for TreeView control

"fold.ico",

"unfold.ico",

// bitmap used by BUTTON control

"classic\_radio\_button.bmp",

"classic\_check\_button.bmp",

// background picture, use your favirate photo

"none",

"center",

// bgpicpos=upleft

// bgpicpos=downleft

// bgpicpos=upright

// bgpicpos=downright

// bgpicpos=upcenter

// bgpicpos=downcenter

// bgpicpos=vcenterleft

// bgpicpos=vcenterright

// bgpicpos=none

//window element metrics

"20",

"25",

"2",

"16",

//window element colors

"0xFFFFFFFF",

"0xFF6A240A",

"0xFF6A240A",

"0xFF000000",

"0xFFCED3D6",

"0xFF000000",

"0xFF000000",

"0xFFE7FFFF",

"0xFFCED3D6",

"0xFFCED3D6",

"0xFFC8D0D4",

"0xFF808080",

"0xFF808080",

"0xFF000000",

"0xFFFFFFFF",

"0xFF000000",

"0xFFCED3D6",

"0xFFFFFFFF",

"0xFF6B2408",

"0xFFBDA69C",

"0xFF848284",

"0xFFCED3D6",

"0xFFFFFFFF",

"0xFF6B2408",

"0xFFFFFFFF",

"0xFF6B2408",

"0xFFC08000"

};

\#ifdef \_MGLF\_RDR\_FLAT

// Section: flat

static char\* \_flat\_keys\[\]={

// Note that max number defined in source code is 5.

"iconnumber",

"icon0",

"icon1",

"icon2",

"icon3",

"icon4",

// default icons for new OpenFileDialogBox

"dir",

"file",

// default icons for TreeView control

"treefold",

"treeunfold",

// bitmap used by BUTTON control

"radiobutton",

"checkbutton",

// background picture, use your favirate photo

"bgpicture",

"bgpicpos",

//window element metrics

"caption",

"menu",

"border",

"scrollbar",

//window element colors

"fgc\_active\_caption",

"bgca\_active\_caption",

"bgcb\_active\_caption",

"fgc\_inactive\_caption",

"bgca\_inactive\_caption",

"bgcb\_inactive\_caption",

"fgc\_menu",

"bgc\_menu",

"fgc\_msgbox",

"fgc\_tip",

"bgc\_tip",

"fgc\_active\_border",

"fgc\_inactive\_border",

"fgc\_window",

"bgc\_window",

"fgc\_3dbox",

"mainc\_3dbox",

"fgc\_selected\_item",

"bgc\_selected\_item",

"bgc\_selected\_lostfocus",

"fgc\_disabled\_item",

"bgc\_disabled\_item",

"fgc\_hilight\_item",

"bgc\_hilight\_item",

"fgc\_significant\_item",

"bgc\_significant\_item",

"bgc\_desktop",

"flat\_tab\_normal\_color"

};

static char\* \_flat\_values\[\]={

// Note that max number defined in source code is 5.

"5",

"form-flat.ico",

"failed-flat.ico",

"help-flat.ico",

"warning-flat.ico",

"excalmatory-flat.ico",

// default icons for new OpenFileDialogBox

"folder-flat.ico",

"textfile-flat.ico",

// default icons for TreeView control

"fold-flat.ico",

"unfold-flat.ico",

// bitmap used by BUTTON control

"flat\_radio\_button.bmp",

"flat\_check\_button.bmp",

// background picture, use your favirate photo

"none",

"center",

//window element metrics

"20",

"25",

"1",

"16",

//window element colors

"0xFFFFFFFFF",

"0xFF000000",

"0xFF000000",

"0xFF000000",

"0xFFFFFFFF",

"0xFFFFFFFF",

"0xFF000000",

"0xFFD8D8D8",

"0xFF000000",

"0xFF000000",

"0xFFE7FFFF",

"0xFF000000",

"0xFF848284",

"0xFF000000",

"0xFFFFFFFF",

"0xFF000000",

"0xFFFFFFFF",

"0xFFFFFFFF",

"0xFF000000",

"0xFFBDA69C",

"0xFF848284",

"0xFF000000",

"0xFFFFFFFF",

"0xFF664E4A",

"0xFFFFFFFF",

"0xFF000000",

"0xFFC08000",

"0xFFC6D2CF"

};

\#endif

\#ifdef \_MGLF\_RDR\_SKIN

// Section: skin

static char\* \_skin\_keys\[\]={

// Note that max number defined in source code is 5.

"iconnumber",

"icon0",

"icon1",

"icon2",

"icon3",

"icon4",

// default icons for new OpenFileDialogBox

"dir",

"file",

// default icons for TreeView control

"treefold",

"treeunfold",

// background picture, use your favirate photo

"bgpicture",

"bgpicpos",

//window element metrics

"caption",

"menu",

"border",

"scrollbar",

"fgc\_active\_caption",

"bgca\_active\_caption",

"bgcb\_active\_caption",

"fgc\_menu",

"bgc\_menu",

"fgc\_msgbox",

"fgc\_tip",

"bgc\_tip",

"fgc\_active\_border",

"fgc\_inactive\_border",

"fgc\_inactive\_caption",

"bgca\_inactive\_caption",

"bgcb\_inactive\_caption",

"fgc\_window",

"bgc\_window",

"fgc\_3dbox",

"mainc\_3dbox",

"fgc\_selected\_item",

"bgc\_selected\_item",

"bgc\_selected\_lostfocus",

"fgc\_disabled\_item",

"bgc\_disabled\_item",

"fgc\_hilight\_item",

"bgc\_hilight\_item",

"fgc\_significant\_item",

"bgc\_significant\_item",

"bgc\_desktop",

"skin\_bkgnd",

"skin\_caption",

"skin\_caption\_btn",

//for scrollbar

"skin\_scrollbar\_hshaft",

"skin\_scrollbar\_vshaft",

"skin\_scrollbar\_hthumb",

"skin\_scrollbar\_vthumb",

"skin\_scrollbar\_arrows",

//for border

"skin\_tborder",

"skin\_bborder",

"skin\_lborder",

"skin\_rborder",

"skin\_arrows",

"skin\_arrows\_shell",

"skin\_pushbtn",

"skin\_radiobtn",

"skin\_checkbtn",

//for treeview

"skin\_tree",

"skin\_header",

"skin\_tab",

//for trackbar

"skin\_tbslider\_h",

"skin\_tbslider\_v",

"skin\_trackbar\_horz",

"skin\_trackbar\_vert",

//for progressbar

"skin\_progressbar\_htrack",

"skin\_progressbar\_vtrack",

"skin\_progressbar\_hchunk",

"skin\_progressbar\_vchunk"

};

static char\* \_skin\_values\[\]={

// Note that max number defined in source code is 5.

"5",

"form.ico",

"failed.ico",

"help.ico",

"warning.ico",

"excalmatory.ico",

// default icons for new OpenFileDialogBox

"folder.ico",

"textfile.ico",

// default icons for TreeView control

"fold.ico",

"unfold.ico",

// background picture, use your favirate photo

"none",

"center",

//window element metrics

"25",

"25",

"1",

"17",

"0xFFFFFFFF",

"0xFFE35400",

"0xFF686868",

"0xFF000000",

"0xFFD4D6FF",

"0xFF000000",

"0xFF000000",

"0xFFFFFFFF",

"0xFFC8D0D4",

"0xFFC8D0D4",

"0xFFF8E4D8",

"0xFFDF967A",

"0xFF686868",

"0xFF000000",

"0xFFFFFFFF",

"0xFF000000",

"0xFFD8E9EC",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFFD8E9EC",

"0xFF99A8AC",

"0xFFFFFFFF",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFF984E00",

"skin\_bkgnd.bmp",

"skin\_caption.gif",

"skin\_cpn\_btn.gif",

//for scrollbar

"skin\_sb\_hshaft.bmp",

"skin\_sb\_vshaft.bmp",

"skin\_sb\_hthumb.bmp",

"skin\_sb\_vthumb.bmp",

"skin\_sb\_arrows.bmp",

//for border

"skin\_tborder.bmp",

"skin\_bborder.bmp",

"skin\_lborder.bmp",

"skin\_rborder.bmp",

"skin\_arrows.gif",

"skin\_arrows\_shell.bmp",

"skin\_pushbtn.gif",

"skin\_radiobtn.gif",

"skin\_checkbtn.bmp",

//for treeview

"skin\_tree.bmp",

"skin\_header.bmp",

"skin\_tab.gif",

//for trackbar

"skin\_tbslider\_h.gif",

"skin\_tbslider\_v.gif",

"skin\_tb\_horz.gif",

"skin\_tb\_vert.gif",

//for progressbar

"skin\_pb\_htrack.gif",

"skin\_pb\_vtrack.gif",

"skin\_pb\_htruck.bmp",

"skin\_pb\_vtruck.bmp"

};

\#endif

// Section: fashion

static char\* \_fashion\_keys\[\]={

// Note that max number defined in source code is 5.

"iconnumber",

"icon0",

"icon1",

"icon2",

"icon3",

"icon4",

// default icons for new OpenFileDialogBox

"dir",

"file",

// default icons for TreeView control

"treefold",

"treeunfold",

// bitmap used by BUTTON control

"radiobutton",

"checkbutton",

// background picture, use your favirate photo

"bgpicture",

"bgpicpos",

//window element metrics

"caption",

"menu",

"border",

"scrollbar",

"fgc\_active\_caption",

"bgca\_active\_caption",

"bgcb\_active\_caption",

"fgc\_menu",

"bgc\_menu",

"fgc\_msgbox",

"fgc\_tip",

"bgc\_tip",

"fgc\_active\_border",

"fgc\_inactive\_border",

"fgc\_inactive\_caption",

"bgca\_inactive\_caption",

"bgcb\_inactive\_caption",

"fgc\_window",

"bgc\_window",

"fgc\_3dbox",

"mainc\_3dbox",

"fgc\_selected\_item",

"bgc\_selected\_item",

"bgc\_selected\_lostfocus",

"fgc\_disabled\_item",

"bgc\_disabled\_item",

"fgc\_hilight\_item",

"bgc\_hilight\_item",

"fgc\_significant\_item",

"bgc\_significant\_item",

"bgc\_desktop"

};

static char\* \_fashion\_values\[\]={

// Note that max number defined in source code is 5.

"5",

"form.ico",

"failed.ico",

"mg\_help.ico",

"warning.ico",

"excalmatory.ico",

// default icons for new OpenFileDialogBox

"folder.ico",

"textfile.ico",

// default icons for TreeView control

"fold.ico",

"unfold.ico",

// bitmap used by BUTTON control

"fashion\_radio\_btn.bmp",

"fashion\_check\_btn.bmp",

// background picture, use your favirate photo

"none",

"center",

//window element metrics

"25",

"25",

"1",

"17",

"0xFFFFFFFF",

"0xFFE35400",

"0xFFFF953D",

"0xFF000000",

"0xFFFFE4BF",

"0xFF000000",

"0xFF000000",

"0xFFFFFFFF",

"0xFFC8D0D4",

"0xFFC8D0D4",

"0xFFF8E4D8",

"0xFFDF967A",

"0xFFEBB99D",

"0xFF000000",

"0xFFEBB99D",

"0xFF000000",

"0xFFD8E9EC",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFFD8E9EC",

"0xFF99A8AC",

"0xFFFFFFFF",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFFFFFFFF",

"0xFFC56A31",

"0xFF984E00"

};

static ETCSECTION \_etc\_sections \[\] = {

{0, 5, "system", \_system\_keys,\_system\_values },

{0, 1, "fbcon", \_fbcon\_keys,\_fbcon\_values },

{0, 2, "qvfb", \_qvfb\_keys,\_qvfb\_values },

\#ifdef \_MGGAL\_PCXVFB

{0, 3, "pc\_xvfb", \_pc\_xvfb\_keys,\_pc\_xvfb\_values },

\#endif

{0, 1, "rtos\_xvfb", \_rtos\_xvfb\_keys,\_rtos\_xvfb\_values },

\#ifdef \_MGGAL\_SHADOW

{0, 3, "shadow", \_shadow\_keys,\_shadow\_values },

\#endif

\#ifdef \_MGGAL\_MLSHADOW

{0, 4, "mlshadow", \_mlshadow\_keys,\_mlshadow\_values },

\#endif

{0, 12, "systemfont", \_systemfont\_keys,\_systemfont\_values },

{0, 1, "rawbitmapfonts", \_rawbitmapfonts\_keys,\_rawbitmapfonts\_values
},

{0, 1, "varbitmapfonts", \_varbitmapfonts\_keys,\_varbitmapfonts\_values
},

{0, 1, "upf", \_upf\_keys,\_upf\_values },

{0, 1, "qpf", \_qpf\_keys,\_qpf\_values },

{0, 1, "truetypefonts", \_truetypefonts\_keys,\_truetypefonts\_values },

{0, 1, "mouse", \_mouse\_keys,\_mouse\_values },

{0, 2, "event", \_event\_keys,\_event\_values },

{0, 25, "cursorinfo", \_cursorinfo\_keys,\_cursorinfo\_values },

{0, 1, "resinfo", \_resinfo\_keys,\_resinfo\_values },

{0, 45, "classic", \_classic\_keys,\_classic\_values },

\#ifdef \_MGLF\_RDR\_FLAT

{0, 46, "flat", \_flat\_keys,\_flat\_values },

\#endif

\#ifdef \_MGLF\_RDR\_SKIN

{0, 71, "skin", \_skin\_keys,\_skin\_values },

\#endif

{0, 45, "fashion", \_fashion\_keys,\_fashion\_values }

};

///////////////////////////////////////////////////

static ETC\_S \_ETC = {

0,

sizeof(\_etc\_sections)/sizeof(ETCSECTION),

\_etc\_sections

};

GHANDLE \_\_mg\_get\_mgetc (void)

{

return (GHANDLE) &\_ETC;

}

\#endif /\* \_MGINCORE\_RES \*/

3.3 Sample of Configuration
---------------------------

Under most circumstances, we modify runtime configuration file, we will
be limited to several sections. The system section and font related
several sections are primary sections. In this chapter, we will give two
configuration examples.

### 3.3.1 Runtime Configuration when only Support for ISO8859-1 Charset

#### 1) Configuration File

\# The first system font must be a logical font using RBF device font.

\[systemfont\]

font\_number=1

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

default=0

wchar\_def=0

fixed=0

caption=0

menu=0

control=0

\[rawbitmapfonts\]

font\_number=1

name0=rbf-fixed-rrncnn-8-16-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin

\[varbitmapfonts\]

font\_number=0

\[qpf\]

font\_number=0

\[truetypefonts\]

font\_number=0

\[type1fonts\]

font\_number=0

#### 2) Incore Configuration Options

static char \*SYSTEMFONT\_KEYS\[\] =

{"font\_number", "font0", "default", "wchar\_def", "fixed", "caption",
"menu", "control"};

static char \*SYSTEMFONT\_VALUES\[\] =

{

"1","rbf-fixed-rrncnn-8-16-ISO8859-1", "0", "0", "0", "0", "0", "0"

};

### 3.3.2 Specifying Different Graphic Engine and Input Engine

#### 1) Configuration File

\[system\]

\# GAL engine and default options

gal\_engine=commlcd

\# IAL engine

ial\_engine=auto

mdev=/dev/ts

mtype=IMPS2

#### 2) Incore Configuration Option

static char \*SYSTEM\_KEYS\[\] = {"gal\_engine", "ial\_engine", "mdev",
"mtype"};

static char \*SYSTEM\_VALUES\[\] = {"commlcd", "auto", "/dev/ts",
"IMPS2"};

