# Runtime configuration options

- [Configuration File](#configuration-file)
- [Look And Feel Renderer](#look-and-feel-renderer)
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

In this chapter, we describe the MiniGUI runtime configuration options,
which effect some actions about MiniGUI running, for example, running
GAL and IAL used, device font, bitmap, and cursor etc. It is known that
MiniGUI runtime configuration options is loaded from `MiniGUI.cfg`,
but if compiling MiniGUI with in-core options, the options is included
MiniGUI libraries.

In GNU development environment, after installing MiniGUI by default
configuration, the file `etc/MiniGUI-classic.cfg` in MiniGUI source
tree will be installed in `/usr/local/etc/` directory, and rename to
`MiniGUI.cfg`. When MiniGUI application starts, It will find
`MiniGUI.cfg` as follow:

the application first search `MiniGUI.cfg` in current directory, then
search `.MiniGUI.cfg` in home directory.

then search `MiniGUI.cfg` in `/usr/local/etc`, at last in `/etc/`.

If user don’t create the file `MiniGUI.cfg` in current directory and
home directory, the application will use the file MiniGUI.cfg in
`/usr/local/etc/` as default configuration file.

When we compile MiniGUI with `--enable-incoreres` option, MiniGUI
application doesn’t need the file `MiniGUI.cfg`. The required options
are given in the file `src/sysres/mgetc.c`.

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

## Configuration File

The section describes configuration options in detail by `MiniGUI.cfg`.

The format of configuration file is compact, and you can modify it easily.
The following shows the format.

```ini
[section-name1]
key-name1=key-value1
key-name2=key-value2

[section-name2]
key-name3=key-value3
key-name4=key-value4
```

The parameters in the configuration file are grouped in sections, such
as notation (#), section, key, and key value. The line that the first
character is ‘#’ is notation line. The values of the section are
specified in the form of `section-name`. The values of the key and key
value are specified in the form of `key=value`. Some important
sections are listed as follows.

### Section system

The section `system` not only defines the graphics engine
(`gal_engine`) and the input engine (`ial_engine`) in runtime
MiniGUI, which must be one of engines configured on MiniGUI compiling,
but also defines the mouse device (`mdev`) and the mouse protocol type
(`mtype`).

The definition of the keys in section `system` is as follows:

`gal_engine`: The graphics engine used.

`defaultmode`: The graphics engine display mode used, its format is
widthxheight-bpp.

`ial_engine`: The input engine used.

`mdev`: The mouse device file.

`mtype`: The mouse protocol type.

The contents of the section `system` in `MiniGUI.cfg` are as follow:

```ini
[system]
# GAL engine and default options
gal_engine=qvfb
defaultmode=800x600-16bpp

# IAL engine
ial_engine=qvfb
mdev=/dev/input/mice
mtype=IMPS2
```

Since MiniGUI Version 1.6.8, you can modify the graphics and input
engine via environment variable. For example, if you define `fbcon`
and `qvfb` graphics engine and `console` and `qvfb` input engine,
and you choose the qvfb engine in `MiniGUI.cfg` or in-core resources.
Then when configure MiniGUI, you can change the engine to fbcon and
console in runtime by the following method, and needn’t modify
`MiniGUI.cfg` or in-core resources configuration file.

```
$ export MG_GAL_ENGINE=fbcon
$ export MG_IAL_ENGINE=console
$ export MG_DEFAULTMODE=1024x768-16bpp
$ export MG_MDEV=/dev/input/mice
$ export MG_MTYPE=ps2
```

### Section fbcon

The section `fbcon` is only available when you define the
`gal_engine` in section `system` for fbcon. It define default
display mode of the `fbcon` engine. When the section is undefined or
key value is empty, the fbcon engine using the key value of system
section.

The definition of the key in section `fbcon` is as follows:

`defaultmode`: The display mode of graphics engine used, the format is
`widthxheight-bpp`.

The content of the section in `MiniGUI.cfg` is as follows:

```ini
[fbcon]
defaultmode=1024x768-16bpp
```

### Section qvfb

The section `qvfb` is only available when you define the
`gal_engine` in section `system` for qvfb. It shows display and
display mode of X window used when running qvfb.

The definition of the keys in section `qvfb` is as follows:

`defaultmode`: The display mode of graphics engine used, its format is
`widthxheight-bpp`.

`display`: Display mode of X window used when running qvfb, default
value is 0.

The content of the section in `MiniGUI.cfg` is as follows:

```ini
[qvfb]
defaultmode=640x480-16bpp
display=0
```

### Section `pc_xvfb`

The section `pc_xvfb` is only available when you define the
`gal_engine` in section `system` for `pc_xvfb`. It has been
supported by Linux(Ubuntu) and Window.

The definition of the keys in section pc_x`vfb` is as follows:

- `defaultmode`: The display mode of graphics engine used, its format is `<width>x<height>-bpp`.
- `window_caption`: Window caption title of XVFB window.
- `exec_file`: the path of the execute file.

The content of the section in `MiniGUI.cfg` is as follows:

```ini
#{{ifdef _MGGAL_PCXVFB
[pc_xvfb]
defaultmode=800x600-16bpp
window_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)
exec_file=/usr/local/bin/gvfb
#}}
```

### Section rawbitmapfonts, varbitmapfonts, upf, and truetypefonts

These sections define information of loading device fonts`,` number of
fonts, and name and file of fonts.

The format of device fonts used by MiniGUI is as follows:

<type>-<facename>-<style>-<width>-<height>-<charset1[,charset2,...]>

The definitions for each part of device `font` are as follow:

`<type>`: The type of device font, for example, RBF, VBF, QPF,
TrueType, and Adobe Type1 device font are rbf, vbf, qpf, ttf, and tlf.

`<facename>`: The name of device font. Such as courier, Times
etc.

`<style>`: The style of device font, it is grouped into six
alphabets. Such as bold, italic, underline or strikethrough etc.
Generally the string is "rrncnn".

`<width>`: The width of device font, for var-width fonts set to
be maximum width; for vector fonts set to be 0.

`<height>`: The height of device font, for vector fonts set to
be 0.

`<charset1, charset2>`: The charset of device font supported.

Each of these sections defines font_number, name`<NR>`, and
fontfile`<NR>` keys.

`font_number`: The number of device font loaded.

`name<NR>`: The name of device font that number is
`<NR>`.

`fontfile<NR>`: The font file of device font that number is
`<nr>`.

If you don't need to use a specific type of device font, you can skip
the configuration option by set `font_number = 0`.

The content of these sections in `MiniGUI.cfg` are as follow:

```ini
[rawbitmapfonts]
font_number=4
name0=rbf-fixed-rrncnn-8-16-ISO8859-1
fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin
name1=rbf-fixed-rrncnn-16-16-GB2312-0
fontfile1=/usr/local/lib/minigui/res/font/song-16-gb2312.bin
name2=rbf-fixed-rrncnn-6-12-ISO8859-1
fontfile2=/usr/local/lib/minigui/res/font/6x12-iso8859-1.bin
name3=rbf-fixed-rrncnn-12-12-GB2312-0
fontfile3=/usr/local/lib/minigui/res/font/song-12-gb2312.bin

[varbitmapfonts]
font_number=6
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

[qpf]
font_number=0

[upf]
font_number=0
name0=upf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312-0,GBK,BIG5
fontfile0=/usr/local/lib/minigui/res/font/unifont_160_50.upf
name1=upf-times-rrncnn-5-10-ISO8859-1,ISO8859-15
fontfile1=/usr/local/lib/minigui/res/font/smoothtimes_100_50.upf
name2=upf-helvetica-rrncnn-5-10-ISO8859-1,ISO8859-15
fontfile2=/usr/local/lib/minigui/res/font/helvetica_100_50.upf
name3=upf-micro-rrncnn-4-4-ISO8859-1,ISO8859-15
fontfile3=/usr/local/lib/minigui/res/font/micro_40_50.upf

[truetypefonts]
font_number=3
name0=ttf-arial-rrncnn-0-0-ISO8859-1
fontfile0=/usr/local/lib/minigui/res/font/arial.ttf
name1=ttf-times-rrncnn-0-0-ISO8859-1
fontfile1=/usr/local/lib/minigui/res/font/times.ttf
name2=ttf-pinball-rrncnn-0-0-ISO8859-1
fontfile2=/usr/local/lib/minigui/res/font/pinball.ttf
```

### Section systemfont

The section `systemfont` defines MiniGUI system font and font number,
and defines system default font, which would be used to render text on
captions, menus, and controls, as well as the default font of a window.

System font is the logic font^10^ that is created by the function
`CreateLogFontFromName` based on device fonts, which is defined by
MiniGUI sections such as `rawbitmapfonts`, `varbitmapfonts`,
`qpf`, `truetypefonts`, and `t1fonts`.

The content of the section in `MiniGUI.cfg` is as follows:

<type>-<facename>-<style>-<width>-<height>-<charset1>

The definition of each part of a logic font name is as follows:

`<type>` is the desired device font type, if you do not want to
specify it, use `\`*.

`<facename>` is to define the font face name, such as courier
and times etc.

`<style>` is the string of six alphabets to define style of a
logic font, such as italic, bold, underline or strikethrough etc.

`<width>` is to define the width of the logic font. Usually do
not need to specify, use `\`* instead.

`<height>` is to define the height of the logic font.

`<charset>` is to define charset of the logic font being
created.

Furthermore, MiniGUI V2.0.x provides auto-scaling the font glyph. If you
want to use this function, you only need use ‘S’ in forth character when
you define logical font styles. Note that you don’t need to use this
style when you use vector font, such as TrueType, because vector font
can produce corresponding font glyph according to desired logical font
size.

The definition of the keys in section `systemfont` is as follows:

`font_number`: The number of system fonts created

`font<NR>`: The number <NR> logical font name

`default`: System default font(single character set). Its value is the
number of logical font.

`wchar_def`: Default font used by multiple character set. Its value
is the number of above logical font.

`fixed`: The font used by fixed width character set. Its value is the
number of above logical font.

`caption`: The caption font. Its value is the number of above logical
font.

`menu`: The menu font. Its value is the number of above logical font.

You can change the number of system font created. But you must create a
single character set (for example: ISO8859-1) at least. MiniGUI defines
the system default charsets according to `default`, `wchar_def`
system fonts, and this would affect the return value of
`GetSysCharset`, `GetSysCharWidth`, `GetSysCCharWidth` and
`GetSysHeight` functions. Commonly, `default` and `wchar_def`
must fixed width dot-matrix font, i.e RBF. And the width of multiply
character set must be twice with the width of single character set.

The content of the section in `MiniGUI.cfg` is as follows:

# The first system font must be a logical font using RBF device font.

[systemfont]

font_number=6

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

font1=\*-fixed-rrncnn-\*-16-GB2312

font2=\*-Courier-rrncnn-\*-16-GB2312

font3=\*-SansSerif-rrncnn-\*-16-GB2312

font4=\*-Times-rrncnn-\*-16-GB2312

font5=\*-Helvetica-rrncnn-\*-16-GB2312

default=0

wchar_def=1

fixed=1

caption=2

menu=3

control=3

### 3.1.6 Section mouse

The section `mouse` defines the time of mouse `double clicked`. It
is used to handle with system inner events. Generally, it is unnecessary
changed.

The definition of the keys in the section is as follows:

`dblclicktime`: The mouse double clicked time in ms

The content of the section in `MiniGUI.cfg` is as follows:

[mouse]

dblclicktime=300

### 3.1.7 Section event

The section `event` defines event timeout and auto-repeat time used by
system internal event process. Generally, it is unnecessary changed.

The definition of the keys in the section is as follows:

`timeoutusec`: Event timeout time in ms

`repeatusec`: Event repeat time in ms

The content of the section in `MiniGUI.cfg` is as follows:

timeoutusec=300000

repeatusec=50000

### 3.1.8 Section classic

The section `classic` defines default window element color used.
Generally, it is unnecessary changed.

Table 3.1 window element division and name in the configuration file and
code

  `Configure Option`       `Code name`                    `Comment`
  -------------------------- -------------------------------- ----------------------------------------------------------------------------------------------------
  caption                    WE_METRICS_CAPTION             Caption size
                             WE_FONT_CAPTION                Caption fonts
  fgc_active_caption       WE_FGC_ACTIVE_CAPTION         Focus status caption foreground color
  bgca_active_caption      WE_BGCA_ACTIVE_CAPTION        Focus status caption background color gradient starting color
  bgcb_active_caption      WE_BGCB_ACTIVE_CAPTION        Focus Status caption background color gradient ending Color
  fgc_inactive_caption     WE_FGC_INACTIVE_CAPTION       Non-focus status caption foreground color
  bgca_inactive_caption    WE_BGCA_INACTIVE_CAPTION      Non-focus status caption background color gradient starting color
  bgcb_inactive_caption    WE_BGCB_INACTIVE_CAPTION      Non-focus status caption background color gradient ending color
  menu                       WE_METRICS_MENU                Menu item, height of the menu bar
                             WE_FONT_MENU                   Menu font
  fgc_menu                  WE_FGC_MENU                    Menu foreground color
  bgc_menu                  WE_BGC_MENU                    Menu background color
  border                     WE_METRICS_WND_BORDER         Window border width
  fgc_active_border        WE_FGC_ACTIVE_WND_BORDER     Focus status window border color
  fgc_inactive_border      WE_FGC_INACTIVE_WND_BORDER   Non-focus status window border color
  scrollbar                  WE_METRICS_SCROLLBAR           Scroll bar size
  fgc_msgbox                WE_FGC_MESSAGEBOX              Message box foreground color
  fgc_msgbox                WE_FONT_MESSAGEBOX             Message box font
  fgc_tip                   WE_FGC_TOOLTIP                 Prompt box foreground color
  bgc_tip                   WE_BGC_TOOLTIP                 Prompt box background color
                             WE_FONT_TOOLTIP                Prompt box font
  fgc_window                WE_FGC_WINDOW                  Window foreground
  bgc_window                WE_BGC_WINDOW                  Window background color
  fgc_3dbox                 WE_FGC_THREED_BODY            The color of the symbol on the surface of the 3D box, such as the color of check mark, arrow, etc.
  mainc_3dbox               WE_MAINC_THREED_BODY          Three-dimensional box border and surface color
  fgc_selected_item        WE_FGC_SELECTED_ITEM          The foreground color of the selected menu item (list item)
  bgc_selected_item        WE_BGC_SELECTED_ITEM          The background color of the selected menu item (list item)
  bgc_selected_lostfocus   WE_BGC_SELECTED_LOSTFOCUS     The background color after the selected menu item (list item) loses focus
  fgc_disabled_item        WE_FGC_DISABLED_ITEM          Foreground color of invalid menu item (list item)
  bgc_disabled_item        WE_BGC_DISABLED_ITEM          Invalid menu item (list item) background color
  fgc_hilight_item         WE_FGC_HIGHLIGHT_ITEM         Highlight the foreground color of the menu item (list item)
  bgc_hilight_item         WE_BGC_HIGHLIGHT_ITEM         Highlight the background color of the menu item (list item)
  fgc_significant_item     WE_FGC_SIGNIFICANT_ITEM       Foreground color of important menu item (list item)
  bgc_significant_item     WE_BGC_SIGNIFICANT_ITEM       Background color of important menu items (list items)
  bgc_desktop               WE_BGC_DESKTOP                 Desktop background color

The content of the section in `MiniGUI.cfg` is as follows:

[classic]

# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

# bitmap used by BUTTON control

radiobutton=classic_radio_button.bmp

checkbutton=classic_check_button.bmp

# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

#window element metrics

caption=20

menu=25

border=2

scrollbar=16

#window element colors

fgc_active_caption=0xFFFFFFFF

bgca_active_caption=0xFF6A240A

bgcb_active_caption=0xFF6A240A

fgc_menu=0xFF000000

bgc_menu=0xFFCED3D6

fgc_msgbox=0xFF000000

fgc_tip=0xFF000000

bgc_tip=0xFFE7FFFF

fgc_active_border=0xFFCED3D6

fgc_inactive_border=0xFFCED3D6

fgc_inactive_caption=0xFFC8D0D4

bgca_inactive_caption=0xFF808080

bgcb_inactive_caption=0xFF808080

fgc_window=0xFF000000

bgc_window=0xFFFFFFFF

fgc_3dbox=0xFF000000

mainc_3dbox=0xFFCED3D6

fgc_selected_item=0xFFFFFFFF

bgc_selected_item=0xFF6B2408

bgc_selected_lostfocus=0xFFBDA69C

fgc_disabled_item=0xFF848284

bgc_disabled_item=0xFFCED3D6

fgc_hilight_item=0xFFFFFFFF

bgc_hilight_item=0xFF6B2408

fgc_significant_item=0xFFFFFFFF

bgc_significant_item=0xFF6B2408

bgc_desktop=0xFFC08000

### 3.1.9 Default Configuration File

Below is the default runtime configuration file for MiniGUI library:

# MiniGUI Ver 3.0.x

# This configuration file is for classic window style.

#

# Copyright (C) 2002\~2017 Feynman Software

# Copyright (C) 1998\~2002 Wei Yongming.

#

# Web: http://www.minigui.com

# Web: http://www.minigui.org

#

# This configuration file must be installed in /etc,

# /usr/local/etc or your home directory. When you install it in your

# home directory, it should be named ".MiniGUI.cfg".

#

# The priority of above configruation files is \~/.MiniGUI.cfg,

# /usr/local/etc/MiniGUI.cfg, and then /etc/MiniGUI.cfg.

#

# If you change the install path of MiniGUI resource, you should

# modify this file to meet your configuration.

#

# NOTE:

# The format of this configuration file has changed since the last
release.

# Please DONT forget to provide the latest MiniGUI.cfg file for your
MiniGUI.

#

[system]

# GAL engine and default options

gal_engine=pc_xvfb

defaultmode=800x600-16bpp

# IAL engine

ial_engine=pc_xvfb

mdev=/dev/input/mice

mtype=IMPS2

[fbcon]

defaultmode=1024x768-16bpp

[qvfb]

defaultmode=640x480-16bpp

display=0

#{{ifdef _MGGAL_PCXVFB

[pc_xvfb]

defaultmode=800x600-16bpp

window_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)

exec_file=/usr/local/bin/gvfb

#}}

# The first system font must be a logical font using RBF device font.

[systemfont]

font_number=6

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

font1=\*-fixed-rrncnn-\*-16-GB2312

font2=\*-Courier-rrncnn-\*-16-GB2312

font3=\*-SansSerif-rrncnn-\*-16-GB2312

font4=\*-Times-rrncnn-\*-16-GB2312

font5=\*-Helvetica-rrncnn-\*-16-GB2312

default=0

wchar_def=1

fixed=1

caption=2

menu=3

control=3

[rawbitmapfonts]

font_number=4

name0=rbf-fixed-rrncnn-8-16-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin

name1=rbf-fixed-rrncnn-16-16-GB2312-0

fontfile1=/usr/local/lib/minigui/res/font/song-16-gb2312.bin

name2=rbf-fixed-rrncnn-6-12-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/6x12-iso8859-1.bin

name3=rbf-fixed-rrncnn-12-12-GB2312-0

fontfile3=/usr/local/lib/minigui/res/font/song-12-gb2312.bin

[varbitmapfonts]

font_number=6

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

[qpf]

font_number=3

name0=qpf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312-0,GBK,BIG5

fontfile0=/usr/local/lib/minigui/res/font/unifont_160_50.qpf

name1=qpf-times-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile1=/usr/local/lib/minigui/res/font/smoothtimes_100_50.qpf

name2=qpf-helvetica-rrncnn-5-10-ISO8859-1,ISO8859-15

fontfile2=/usr/local/lib/minigui/res/font/helvetica_100_50.qpf

name3=qpf-micro-rrncnn-4-4-ISO8859-1,ISO8859-15

fontfile3=/usr/local/lib/minigui/res/font/micro_40_50.qpf

[upf]

font_number=0

[truetypefonts]

font_number=3

name0=ttf-arial-rrncnn-0-0-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/arial.ttf

name1=ttf-times-rrncnn-0-0-ISO8859-1

fontfile1=/usr/local/lib/minigui/res/font/times.ttf

name2=ttf-pinball-rrncnn-0-0-ISO8859-1

fontfile2=/usr/local/lib/minigui/res/font/pinball.ttf

[mouse]

dblclicktime=300

[event]

timeoutusec=300000

repeatusec=50000

[cursorinfo]

# Edit following line to specify cursor files path

cursorpath=/usr/local/lib/minigui/res/cursor/

cursornumber=23

cursor0=d_arrow.cur

cursor1=d_beam.cur

cursor2=d_pencil.cur

cursor3=d_cross.cur

cursor4=d_move.cur

cursor5=d_sizenwse.cur

cursor6=d_sizenesw.cur

cursor7=d_sizewe.cur

cursor8=d_sizens.cur

cursor9=d_uparrow.cur

cursor10=d_none.cur

cursor11=d_help.cur

cursor12=d_busy.cur

cursor13=d_wait.cur

cursor14=g_rarrow.cur

cursor15=g_col.cur

cursor16=g_row.cur

cursor17=g_drag.cur

cursor18=g_nodrop.cur

cursor19=h_point.cur

cursor20=h_select.cur

cursor21=ho_split.cur

cursor22=ve_split.cur

[resinfo]

respath=/usr/local/share/minigui/res/

[classic]

# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

# bitmap used by BUTTON control

radiobutton=classic_radio_button.bmp

checkbutton=classic_check_button.bmp

# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

# bgpicpos=upleft

# bgpicpos=downleft

# bgpicpos=upright

# bgpicpos=downright

# bgpicpos=upcenter

# bgpicpos=downcenter

# bgpicpos=vcenterleft

# bgpicpos=vcenterright

# bgpicpos=none

#window element metrics

caption=20

menu=25

border=2

scrollbar=16

#window element colors

fgc_active_caption=0xFFFFFFFF

bgca_active_caption=0xFF6A240A

bgcb_active_caption=0xFF6A240A

fgc_menu=0xFF000000

bgc_menu=0xFFCED3D6

fgc_msgbox=0xFF000000

fgc_tip=0xFF000000

bgc_tip=0xFFE7FFFF

fgc_active_border=0xFFCED3D6

fgc_inactive_border=0xFFCED3D6

fgc_inactive_caption=0xFFC8D0D4

bgca_inactive_caption=0xFF808080

bgcb_inactive_caption=0xFF808080

fgc_window=0xFF000000

bgc_window=0xFFFFFFFF

fgc_3dbox=0xFF000000

mainc_3dbox=0xFFCED3D6

fgc_selected_item=0xFFFFFFFF

bgc_selected_item=0xFF6B2408

bgc_selected_lostfocus=0xFFBDA69C

fgc_disabled_item=0xFF848284

bgc_disabled_item=0xFFCED3D6

fgc_hilight_item=0xFFFFFFFF

bgc_hilight_item=0xFF6B2408

fgc_significant_item=0xFFFFFFFF

bgc_significant_item=0xFF6B2408

bgc_desktop=0xFFC08000

#{{ifdef _MGLF_RDR_FLAT

[flat]

# Note that max number defined in source code is 5.

iconnumber=5

icon0=form-flat.ico

icon1=failed-flat.ico

icon2=help-flat.ico

icon3=warning-flat.ico

icon4=excalmatory-flat.ico

# default icons for new OpenFileDialogBox

dir=folder-flat.ico

file=textfile-flat.ico

# default icons for TreeView control

treefold=fold-flat.ico

treeunfold=unfold-flat.ico

# bitmap used by BUTTON control

radiobutton=flat_radio_button.bmp

checkbutton=flat_check_button.bmp

# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

#window element metrics

caption=20

menu=25

border=1

scrollbar=16

#window element colors

fgc_active_caption=0xFFFFFFFFF

bgca_active_caption=0xFF000000

bgcb_active_caption=0xFF000000

fgc_inactive_caption=0xFF000000

bgca_inactive_caption=0xFFFFFFFF

bgcb_inactive_caption=0xFFFFFFFF

fgc_menu=0xFF000000

bgc_menu=0xFFD8D8D8

fgc_msgbox=0xFF000000

fgc_tip=0xFF000000

bgc_tip=0xFFE7FFFF

fgc_active_border=0xFF000000

fgc_inactive_border=0xFF848284

fgc_window=0xFF000000

bgc_window=0xFFFFFFFF

fgc_3dbox=0xFF000000

mainc_3dbox=0xFFFFFFFF

fgc_selected_item=0xFFFFFFFF

bgc_selected_item=0xFF000000

bgc_selected_lostfocus=0xFFBDA69C

fgc_disabled_item=0xFF848284

bgc_disabled_item=0xFF000000

fgc_hilight_item=0xFFFFFFFF

bgc_hilight_item=0xFF664E4A

fgc_significant_item=0xFFFFFFFF

bgc_significant_item=0xFF000000

bgc_desktop=0xFFC08000

flat_tab_normal_color=0xFFC6D2CF

#}}

#{{ifdef _MGLF_RDR_SKIN

[skin]

# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

#window element metrics

caption=25

menu=25

border=1

scrollbar=17

fgc_active_caption=0xFFFFFFFF

bgca_active_caption=0xFFE35400

bgcb_active_caption=0xFF686868

fgc_menu=0xFF000000

bgc_menu=0xFFD4D6FF

fgc_msgbox=0xFF000000

fgc_tip=0xFF000000

bgc_tip=0xFFFFFFFF

fgc_active_border=0xFFC8D0D4

fgc_inactive_border=0xFFC8D0D4

fgc_inactive_caption=0xFFF8E4D8

bgca_inactive_caption=0xFFDF967A

bgcb_inactive_caption=0xFF686868

fgc_window=0xFF000000

bgc_window=0xFFFFFFFF

fgc_3dbox=0xFF000000

mainc_3dbox=0xFFD8E9EC

fgc_selected_item=0xFFFFFFFF

bgc_selected_item=0xFFC56A31

bgc_selected_lostfocus=0xFFD8E9EC

fgc_disabled_item=0xFF99A8AC

bgc_disabled_item=0xFFFFFFFF

fgc_hilight_item=0xFFFFFFFF

bgc_hilight_item=0xFFC56A31

fgc_significant_item=0xFFFFFFFF

bgc_significant_item=0xFFC56A31

bgc_desktop=0xFF984E00

skin_bkgnd=skin_bkgnd.bmp

skin_caption=skin_caption.gif

skin_caption_btn=skin_cpn_btn.gif

#for scrollbar

skin_scrollbar_hshaft=skin_sb_hshaft.bmp

skin_scrollbar_vshaft=skin_sb_vshaft.bmp

skin_scrollbar_hthumb=skin_sb_hthumb.bmp

skin_scrollbar_vthumb=skin_sb_vthumb.bmp

skin_scrollbar_arrows=skin_sb_arrows.bmp

#for border

skin_tborder=skin_tborder.bmp

skin_bborder=skin_bborder.bmp

skin_lborder=skin_lborder.bmp

skin_rborder=skin_rborder.bmp

skin_arrows=skin_arrows.gif

skin_arrows_shell=skin_arrows_shell.bmp

skin_pushbtn=skin_pushbtn.gif

skin_radiobtn=skin_radiobtn.gif

skin_checkbtn=skin_checkbtn.bmp

#for treeview

skin_tree=skin_tree.bmp

skin_header=skin_header.bmp

skin_tab=skin_tab.gif

#for trackbar

skin_tbslider_h=skin_tbslider_h.gif

skin_tbslider_v=skin_tbslider_v.gif

skin_trackbar_horz=skin_tb_horz.gif

skin_trackbar_vert=skin_tb_vert.gif

#for progressbar

skin_progressbar_htrack=skin_pb_htrack.gif

skin_progressbar_vtrack=skin_pb_vtrack.gif

skin_progressbar_hchunk=skin_pb_htruck.bmp

skin_progressbar_vchunk=skin_pb_vtruck.bmp

#}}

[fashion]

# Note that max number defined in source code is 5.

iconnumber=5

icon0=form.ico

icon1=failed.ico

icon2=help.ico

icon3=warning.ico

icon4=excalmatory.ico

# default icons for new OpenFileDialogBox

dir=folder.ico

file=textfile.ico

# default icons for TreeView control

treefold=fold.ico

treeunfold=unfold.ico

# bitmap used by BUTTON control

radiobutton=fashion_radio_btn.bmp

checkbutton=fashion_check_btn.bmp

# background picture, use your favirate photo

bgpicture=none

bgpicpos=center

#window element metrics

caption=25

menu=25

border=1

scrollbar=17

fgc_active_caption=0xFFFFFFFF

bgca_active_caption=0xFFE35400

bgcb_active_caption=0xFFFF953D

fgc_menu=0xFF000000

bgc_menu=0xFFFFE4BF

fgc_msgbox=0xFF000000

fgc_tip=0xFF000000

bgc_tip=0xFFFFFFFF

fgc_active_border=0xFFC8D0D4

fgc_inactive_border=0xFFC8D0D4

fgc_inactive_caption=0xFFF8E4D8

bgca_inactive_caption=0xFFDF967A

bgcb_inactive_caption=0xFFEBB99D

fgc_window=0xFF000000

bgc_window=0xFFEBB99D

fgc_3dbox=0xFF000000

mainc_3dbox=0xFFD8E9EC

fgc_selected_item=0xFFFFFFFF

bgc_selected_item=0xFFC56A31

bgc_selected_lostfocus=0xFFD8E9EC

fgc_disabled_item=0xFF99A8AC

bgc_disabled_item=0xFFFFFFFF

fgc_hilight_item=0xFFFFFFFF

bgc_hilight_item=0xFFC56A31

fgc_significant_item=0xFFFFFFFF

bgc_significant_item=0xFFC56A31

bgc_desktop=0xFF984E00

3.2 Incore Configuration Options
--------------------------------

When use incore resources, MiniGUI don’t need the file `MiniGUI.cfg`.
The appropriate configuration options are defined in the file
`src/sysres/mgetc.c`.

Similar with the structure in `MiniGUI.cfg`, MiniGUI defines an
structure ETCSECTION, array `_etc_sections` and variable MGETC in
`mgetc.c`. The array mgetc_sections is appropriate with section in
configuration file. MGETC that is ETC_S type is appropriate with
configuration file.

### 3.2.1 Structure ETCSETCTION

The structure `ETCSECTION` is defined in the file named
‘`minigui.h`’. The following is in detail.

/\*\* Etc The current config section information \*/

typedef struct _ETCSECTION

{

/\*\* Allocated number of keys \*/

int key_nr_alloc;

/\*\* Key number in the section \*/

int key_nr;

/\*\* Name of the section \*/

char \*name;

/\*\* Array of keys \*/

char\*\* keys;

/\*\* Array of values \*/

char\*\* values;

} ETCSECTION;

The `key_nr_alloc` is the interface of other configuration options.
Its value must be 0 in incore. The `key_nr` defines the number of the
key in section. The name defines the name of section. The keys and
values is the array of key and value. The number of key array and value
array is corresponded with the number of the `key_nr`.

Below is the definition of _etc_sections in the `mgetc.c` file.

static ETCSECTION _etc_sections [] = {

{0, 5, "system", _system_keys,_system_values },

{0, 1, "fbcon", _fbcon_keys,_fbcon_values },

{0, 2, "qvfb", _qvfb_keys,_qvfb_values },

#ifdef _MGGAL_PCXVFB

{0, 3, "pc_xvfb", _pc_xvfb_keys,_pc_xvfb_values },

#endif

{0, 1, "rtos_xvfb", _rtos_xvfb_keys,_rtos_xvfb_values },

#ifdef _MGGAL_SHADOW

{0, 3, "shadow", _shadow_keys,_shadow_values },

#endif

#ifdef _MGGAL_MLSHADOW

{0, 4, "mlshadow", _mlshadow_keys,_mlshadow_values },

#endif

{0, 12, "systemfont", _systemfont_keys,_systemfont_values },

{0, 1, "rawbitmapfonts", _rawbitmapfonts_keys,_rawbitmapfonts_values
},

{0, 1, "varbitmapfonts", _varbitmapfonts_keys,_varbitmapfonts_values
},

{0, 1, "upf", _upf_keys,_upf_values },

{0, 1, "qpf", _qpf_keys,_qpf_values },

{0, 1, "truetypefonts", _truetypefonts_keys,_truetypefonts_values },

{0, 1, "mouse", _mouse_keys,_mouse_values },

{0, 2, "event", _event_keys,_event_values },

{0, 25, "cursorinfo", _cursorinfo_keys,_cursorinfo_values },

{0, 1, "resinfo", _resinfo_keys,_resinfo_values },

{0, 45, "classic", _classic_keys,_classic_values },

#ifdef _MGLF_RDR_FLAT

{0, 46, "flat", _flat_keys,_flat_values },

#endif

#ifdef _MGLF_RDR_SKIN

{0, 71, "skin", _skin_keys,_skin_values },

#endif

{0, 45, "fashion", _fashion_keys,_fashion_values }

};

The section in `_etc_sections` must be defined (fbcon or qvfb is
optional.). Other notation sections are optional. The meaning of
sections is same as the sections in MiniGUI.cfg. Commonly, you can only
change the GAL engine, the IAL engine, display mode and the sections of
system and fbcon: SYSTEM_VALUES and FBCON_VALUES defined in the
`mgetc-xxx.c` file, such as `mgetc-pc.c`.

The `systemfont` section defines incore font used by system.
Currently, MiniGUI 3.0.x supports ISO8859-1, GB2312, RBF, BIG5,
SHIFT_JIS, and QPF. MiniGUI doesn’t support the TTF and Type1 font in
incore resources.

### 3.2.2 ETC_S Structure

`ETC_S` structure was defined in the file minigui.h, the content of
ETC_S listed as the follow:

/\*\* ETC_S The current config file information\*/

typedef struct _ETC_S

{

/\*\* Allocated number of sections \*/

int sect_nr_alloc;

/\*\* Number of sections \*/

int section_nr;

/\*\* Pointer to section arrays \*/

PETCSECTION sections;

} ETC_S;

Therefore, `sect_nr_alloc` is the interface of the other
configuration options, it’s value must be 0 in incore, `sect_nr`
specify the number of section, sections is ETCSECTION type structure
array, the number of item is not less than the value, the first item
specified this value.

The `mgetc_sections` array was defined as the follow in the
`mgetc.c` file.

static ETC_S _ETC = {

0,

sizeof(_etc_sections)/sizeof(ETCSECTION),

_etc_sections

};

The number of section is sizeof(_etc_sections)/sizeof(ETCSECTION) in
the MGETC structure; the section array is mgetc_sections array above.

### 3.2.3 Listing of mgetc.c

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

\* This is inside mode of system res configuation \*

\* It's generated by the mgcfg-trans, version 1.0 \*

\* author : dongjunjie in feynman \*

\* please donnot modify this file, if you want, \*

\* please change your input file and regenerate \*

\* this file \*

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

#include <stdio.h>

#include "common.h"

#include "minigui.h"

#ifdef _MGINCORE_RES

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

static char\* _system_keys[]={

// GAL engine and default options

"gal_engine",

"defaultmode",

// IAL engine

"ial_engine",

"mdev",

"mtype"

};

static char\* _system_values[]={

// GAL engine and default options

"pc_xvfb",

"800x600-16bpp",

// IAL engine

"pc_xvfb",

"/dev/input/mice",

"IMPS2"

};

// Section: fbcon

static char\* _fbcon_keys[]={

"defaultmode"

};

static char\* _fbcon_values[]={

"1024x768-16bpp"

};

// Section: qvfb

static char\* _qvfb_keys[]={

"defaultmode",

"display"

};

static char\* _qvfb_values[]={

"640x480-16bpp",

"0"

};

#ifdef _MGGAL_PCXVFB

// Section: pc_xvfb

static char\* _pc_xvfb_keys[]={

"defaultmode",

"window_caption",

"exec_file"

};

static char\* _pc_xvfb_values[]={

"800x600-16bpp",

"XVFB-for-MiniGUI-3.0-(Gtk-Version)",

"/usr/local/bin/gvfb"

};

#endif

// Section: rtos_xvfb

static char\* _rtos_xvfb_keys[]={

"defaultmode"

};

static char\* _rtos_xvfb_values[]={

"800x600-16bpp"

};

#ifdef _MGGAL_SHADOW

// Section: shadow

static char\* _shadow_keys[]={

"real_engine",

"defaultmode",

"rotate_screen"

};

static char\* _shadow_values[]={

"pc_xvfb",

"800x600-16bpp",

"normal"

};

#endif

#ifdef _MGGAL_MLSHADOW

// Section: mlshadow

static char\* _mlshadow_keys[]={

"real_engine",

"defaultmode",

"def_bgcolor",

"double_buffer"

};

static char\* _mlshadow_values[]={

"qvfb",

"800x600-16bpp",

"0x00FF00",

"enable"

};

#endif

// The first system font must be a logical font using RBF device font.

// Section: systemfont

static char\* _systemfont_keys[]={

"font_number",

"font0",

"font1",

"font2",

"font3",

"font4",

"default",

"wchar_def",

"fixed",

"caption",

"menu",

"control"

};

static char\* _systemfont_values[]={

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

static char\* _rawbitmapfonts_keys[]={

"font_number"

};

static char\* _rawbitmapfonts_values[]={

"0"

};

// Section: varbitmapfonts

static char\* _varbitmapfonts_keys[]={

"font_number"

};

static char\* _varbitmapfonts_values[]={

"0"

};

// Section: upf

static char\* _upf_keys[]={

"font_number"

};

static char\* _upf_values[]={

"0"

};

// Section: qpf

static char\* _qpf_keys[]={

"font_number"

};

static char\* _qpf_values[]={

"0"

};

// Section: truetypefonts

static char\* _truetypefonts_keys[]={

"font_number"

};

static char\* _truetypefonts_values[]={

"0"

};

// Section: mouse

static char\* _mouse_keys[]={

"dblclicktime"

};

static char\* _mouse_values[]={

"300"

};

// Section: event

static char\* _event_keys[]={

"timeoutusec",

"repeatusec"

};

static char\* _event_values[]={

"300000",

"50000"

};

// Section: cursorinfo

static char\* _cursorinfo_keys[]={

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

static char\* _cursorinfo_values[]={

// Edit following line to specify cursor files path

"/usr/local/share/minigui/res/cursor/",

"23",

"d_arrow.cur",

"d_beam.cur",

"d_pencil.cur",

"d_cross.cur",

"d_move.cur",

"d_sizenwse.cur",

"d_sizenesw.cur",

"d_sizewe.cur",

"d_sizens.cur",

"d_uparrow.cur",

"d_none.cur",

"d_help.cur",

"d_busy.cur",

"d_wait.cur",

"g_rarrow.cur",

"g_col.cur",

"g_row.cur",

"g_drag.cur",

"g_nodrop.cur",

"h_point.cur",

"h_select.cur",

"ho_split.cur",

"ve_split.cur"

};

// Section: resinfo

static char\* _resinfo_keys[]={

"respath"

};

static char\* _resinfo_values[]={

"/usr/local/share/minigui/res/"

};

// Section: classic

static char\* _classic_keys[]={

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

"fgc_active_caption",

"bgca_active_caption",

"bgcb_active_caption",

"fgc_menu",

"bgc_menu",

"fgc_msgbox",

"fgc_tip",

"bgc_tip",

"fgc_active_border",

"fgc_inactive_border",

"fgc_inactive_caption",

"bgca_inactive_caption",

"bgcb_inactive_caption",

"fgc_window",

"bgc_window",

"fgc_3dbox",

"mainc_3dbox",

"fgc_selected_item",

"bgc_selected_item",

"bgc_selected_lostfocus",

"fgc_disabled_item",

"bgc_disabled_item",

"fgc_hilight_item",

"bgc_hilight_item",

"fgc_significant_item",

"bgc_significant_item",

"bgc_desktop"

};

static char\* _classic_values[]={

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

"classic_radio_button.bmp",

"classic_check_button.bmp",

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

#ifdef _MGLF_RDR_FLAT

// Section: flat

static char\* _flat_keys[]={

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

"fgc_active_caption",

"bgca_active_caption",

"bgcb_active_caption",

"fgc_inactive_caption",

"bgca_inactive_caption",

"bgcb_inactive_caption",

"fgc_menu",

"bgc_menu",

"fgc_msgbox",

"fgc_tip",

"bgc_tip",

"fgc_active_border",

"fgc_inactive_border",

"fgc_window",

"bgc_window",

"fgc_3dbox",

"mainc_3dbox",

"fgc_selected_item",

"bgc_selected_item",

"bgc_selected_lostfocus",

"fgc_disabled_item",

"bgc_disabled_item",

"fgc_hilight_item",

"bgc_hilight_item",

"fgc_significant_item",

"bgc_significant_item",

"bgc_desktop",

"flat_tab_normal_color"

};

static char\* _flat_values[]={

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

"flat_radio_button.bmp",

"flat_check_button.bmp",

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

#endif

#ifdef _MGLF_RDR_SKIN

// Section: skin

static char\* _skin_keys[]={

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

"fgc_active_caption",

"bgca_active_caption",

"bgcb_active_caption",

"fgc_menu",

"bgc_menu",

"fgc_msgbox",

"fgc_tip",

"bgc_tip",

"fgc_active_border",

"fgc_inactive_border",

"fgc_inactive_caption",

"bgca_inactive_caption",

"bgcb_inactive_caption",

"fgc_window",

"bgc_window",

"fgc_3dbox",

"mainc_3dbox",

"fgc_selected_item",

"bgc_selected_item",

"bgc_selected_lostfocus",

"fgc_disabled_item",

"bgc_disabled_item",

"fgc_hilight_item",

"bgc_hilight_item",

"fgc_significant_item",

"bgc_significant_item",

"bgc_desktop",

"skin_bkgnd",

"skin_caption",

"skin_caption_btn",

//for scrollbar

"skin_scrollbar_hshaft",

"skin_scrollbar_vshaft",

"skin_scrollbar_hthumb",

"skin_scrollbar_vthumb",

"skin_scrollbar_arrows",

//for border

"skin_tborder",

"skin_bborder",

"skin_lborder",

"skin_rborder",

"skin_arrows",

"skin_arrows_shell",

"skin_pushbtn",

"skin_radiobtn",

"skin_checkbtn",

//for treeview

"skin_tree",

"skin_header",

"skin_tab",

//for trackbar

"skin_tbslider_h",

"skin_tbslider_v",

"skin_trackbar_horz",

"skin_trackbar_vert",

//for progressbar

"skin_progressbar_htrack",

"skin_progressbar_vtrack",

"skin_progressbar_hchunk",

"skin_progressbar_vchunk"

};

static char\* _skin_values[]={

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

"skin_bkgnd.bmp",

"skin_caption.gif",

"skin_cpn_btn.gif",

//for scrollbar

"skin_sb_hshaft.bmp",

"skin_sb_vshaft.bmp",

"skin_sb_hthumb.bmp",

"skin_sb_vthumb.bmp",

"skin_sb_arrows.bmp",

//for border

"skin_tborder.bmp",

"skin_bborder.bmp",

"skin_lborder.bmp",

"skin_rborder.bmp",

"skin_arrows.gif",

"skin_arrows_shell.bmp",

"skin_pushbtn.gif",

"skin_radiobtn.gif",

"skin_checkbtn.bmp",

//for treeview

"skin_tree.bmp",

"skin_header.bmp",

"skin_tab.gif",

//for trackbar

"skin_tbslider_h.gif",

"skin_tbslider_v.gif",

"skin_tb_horz.gif",

"skin_tb_vert.gif",

//for progressbar

"skin_pb_htrack.gif",

"skin_pb_vtrack.gif",

"skin_pb_htruck.bmp",

"skin_pb_vtruck.bmp"

};

#endif

// Section: fashion

static char\* _fashion_keys[]={

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

"fgc_active_caption",

"bgca_active_caption",

"bgcb_active_caption",

"fgc_menu",

"bgc_menu",

"fgc_msgbox",

"fgc_tip",

"bgc_tip",

"fgc_active_border",

"fgc_inactive_border",

"fgc_inactive_caption",

"bgca_inactive_caption",

"bgcb_inactive_caption",

"fgc_window",

"bgc_window",

"fgc_3dbox",

"mainc_3dbox",

"fgc_selected_item",

"bgc_selected_item",

"bgc_selected_lostfocus",

"fgc_disabled_item",

"bgc_disabled_item",

"fgc_hilight_item",

"bgc_hilight_item",

"fgc_significant_item",

"bgc_significant_item",

"bgc_desktop"

};

static char\* _fashion_values[]={

// Note that max number defined in source code is 5.

"5",

"form.ico",

"failed.ico",

"mg_help.ico",

"warning.ico",

"excalmatory.ico",

// default icons for new OpenFileDialogBox

"folder.ico",

"textfile.ico",

// default icons for TreeView control

"fold.ico",

"unfold.ico",

// bitmap used by BUTTON control

"fashion_radio_btn.bmp",

"fashion_check_btn.bmp",

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

static ETCSECTION _etc_sections [] = {

{0, 5, "system", _system_keys,_system_values },

{0, 1, "fbcon", _fbcon_keys,_fbcon_values },

{0, 2, "qvfb", _qvfb_keys,_qvfb_values },

#ifdef _MGGAL_PCXVFB

{0, 3, "pc_xvfb", _pc_xvfb_keys,_pc_xvfb_values },

#endif

{0, 1, "rtos_xvfb", _rtos_xvfb_keys,_rtos_xvfb_values },

#ifdef _MGGAL_SHADOW

{0, 3, "shadow", _shadow_keys,_shadow_values },

#endif

#ifdef _MGGAL_MLSHADOW

{0, 4, "mlshadow", _mlshadow_keys,_mlshadow_values },

#endif

{0, 12, "systemfont", _systemfont_keys,_systemfont_values },

{0, 1, "rawbitmapfonts", _rawbitmapfonts_keys,_rawbitmapfonts_values
},

{0, 1, "varbitmapfonts", _varbitmapfonts_keys,_varbitmapfonts_values
},

{0, 1, "upf", _upf_keys,_upf_values },

{0, 1, "qpf", _qpf_keys,_qpf_values },

{0, 1, "truetypefonts", _truetypefonts_keys,_truetypefonts_values },

{0, 1, "mouse", _mouse_keys,_mouse_values },

{0, 2, "event", _event_keys,_event_values },

{0, 25, "cursorinfo", _cursorinfo_keys,_cursorinfo_values },

{0, 1, "resinfo", _resinfo_keys,_resinfo_values },

{0, 45, "classic", _classic_keys,_classic_values },

#ifdef _MGLF_RDR_FLAT

{0, 46, "flat", _flat_keys,_flat_values },

#endif

#ifdef _MGLF_RDR_SKIN

{0, 71, "skin", _skin_keys,_skin_values },

#endif

{0, 45, "fashion", _fashion_keys,_fashion_values }

};

///////////////////////////////////////////////////

static ETC_S _ETC = {

0,

sizeof(_etc_sections)/sizeof(ETCSECTION),

_etc_sections

};

GHANDLE __mg_get_mgetc (void)

{

return (GHANDLE) &_ETC;

}

#endif /\* _MGINCORE_RES \*/

3.3 Sample of Configuration
---------------------------

Under most circumstances, we modify runtime configuration file, we will
be limited to several sections. The system section and font related
several sections are primary sections. In this chapter, we will give two
configuration examples.

### 3.3.1 Runtime Configuration when only Support for ISO8859-1 Charset

#### 1) Configuration File

# The first system font must be a logical font using RBF device font.

[systemfont]

font_number=1

font0=rbf-fixed-rrncnn-8-16-ISO8859-1

default=0

wchar_def=0

fixed=0

caption=0

menu=0

control=0

[rawbitmapfonts]

font_number=1

name0=rbf-fixed-rrncnn-8-16-ISO8859-1

fontfile0=/usr/local/lib/minigui/res/font/8x16-iso8859-1.bin

[varbitmapfonts]

font_number=0

[qpf]

font_number=0

[truetypefonts]

font_number=0

[type1fonts]

font_number=0

#### 2) Incore Configuration Options

static char \*SYSTEMFONT_KEYS[] =

{"font_number", "font0", "default", "wchar_def", "fixed", "caption",
"menu", "control"};

static char \*SYSTEMFONT_VALUES[] =

{

"1","rbf-fixed-rrncnn-8-16-ISO8859-1", "0", "0", "0", "0", "0", "0"

};

### 3.3.2 Specifying Different Graphic Engine and Input Engine

#### 1) Configuration File

```ini
[system]
# GAL engine and default options
gal_engine=commlcd

# IAL engine
ial_engine=auto
mdev=/dev/ts
mtype=IMPS2
```

#### 2) Incore Configuration Option

```cpp
static char *SYSTEM_KEYS[] = {"gal_engine", "ial_engine", "mdev", "mtype"};
static char *SYSTEM_VALUES[] = {"commlcd", "auto", "/dev/ts", "IMPS2"};
```

---

[&lt; Compile-time Configuration](MiniGUIUserManualCompiletimeConfiguration.md) | [Table of Contents](README.md) | [Feature List &gt;](MiniGUIUserManualFeatureList.md)

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
