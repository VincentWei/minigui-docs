# Runtime configuration options

- [Configuration File](#configuration-file)
   * [Section `system`](#section-system)
   * [Section `pc_xvfb`](#section-pc_xvfb)
   * [Section `fbcon`](#section-fbcon)
   * [Section `dri`](#section-dri)
   * [Section `libinput`](#section-libinput)
   * [Section `systemfont`](#section-systemfont)
   * [Section `cursorinfo`](#section-cursorinfo)
   * [Section `resinfo`](#section-resinfo)
   * [Sections for devfonts](#sections-for-devfonts)
   * [Sections for appearance renderers](#sections-for-appearance-renderers)
   * [Other sections](#other-sections)
- [Incore Configuration](#incore-configuration)
   * [Structure `ETCSETCTION`](#structure-etcsetction)
   * [Structure `ETC_S`](#structure-etc_s)
- [Samples](#samples)

In this chapter, we describe the MiniGUI runtime configuration,
which affects the runtime behavior of MiniGUI. For example, you
can use the runtime configuration to specify:

- The effective graphics and input engines.
- The device fonts to load.
- The system fonts for caption, menu, and control.
- The mouse cursors.
- The icons, and bitmaps to decorate window.

Generally, the runtime configuration is loaded from `MiniGUI.cfg` file.
But if you configured MiniGUI with built-in resource in building stage,
the runtime configuration will be compiled into the MiniGUI Core library.

In this chapter, we first describe the runtime configuration when
using the configuration file, then describe how to specify runtime
configuration if you configured MiniGUI with incore resource.
For convenience, we call the later situation as `incore configuration`.

## Configuration File

On Linux, after building and installing MiniGUI by using the default
configuration, the file `etc/MiniGUI.cfg` in MiniGUI source tree will
be installed to `/usr/local/etc/` directory. However, you can deploy
your own version of `MiniGUI.cfg` in your home directory. And this version
will have a high priority.

Actually, when MiniGUI starts, it will locate the correct `MiniGUI.cfg`
according to the following steps:

1. search `MiniGUI.cfg` in current working directory. If not found,
1. search `.MiniGUI.cfg` in home directory of the current user. If not found,
1. search `MiniGUI.cfg` in `/usr/local/etc`. If not found,
1. search `MiniGUI.cofg` in `/etc/`.

In other words, if you don't create `MiniGUI.cfg` file in the current
directory or `.MiniGUI.cfg` file in your home directory either, MiniGUI
will use the file `MiniGUI.cfg` in `/usr/local/etc/` as the default
configuration file.

The format of the MiniGUI configuration file is simple, and you can modify
it easily. The following code shows the format:

```ini
# This is a comment line
[section-name1]
key-name1=key-value1
key-name2=key-value2

[section-name2]
key-name3=key-value3
key-name4=key-value4
```

The options in the configuration file are grouped in sections.
The line which starts with the character `#` is a comment line.
A line in the form of `[section-name]` defines a new section.
And a pair of key and value in the form of `key=value` defines
an option in a section.

Note that we often use the notation `section_name.key_name` to refer to
an option with `key_name` in the section `section_name`.

Some important sections are listed as follow.

### Section `system`

You can use the section `system` to specify the effective NEWGAL
engine and IAL engine. For historical reasons, you can also use
this section to specify the mouse device and mouse protocol for
`console` IAL engine.

The keys of this section are listed as follow:

- `gal_engine`: The graphics engine.
- `defaultmode`: The display mode for the graphics engine.
- `ial_engine`: The input engine.
- `mdev`: The mouse device file.
- `mtype`: The mouse protocol type.

For a display mode, MiniGUI uses the following notation: `<XRES>x<YRES>-<DEPTH>bpp`.
Here `<XRES>` means the horizontal resolution of the display mode,
and `<YRES>` means the vertical resolution, and `<DEPTH>` means
the color depth of bits per pixel. For example, `640x480-32bpp`.

The default content of the section `system` is as follow:

```ini
[system]
# GAL engine and default options
gal_engine=pc_xvfb
defaultmode=800x600-16bpp

# IAL engine
ial_engine=pc_xvfb
mdev=/dev/input/mice
mtype=IMPS2
```

Since MiniGUI 1.6.8, you can specify the graphics and input
engines via environment variables. The definition of the
environment variables will override the runtime configuration,
whatever you are using the configuration file or the incore configuration.
The environment variables are listed as follow:

- `MG_GAL_ENGINE`: `system.gal_engine`
- `MG_IAL_ENGINE`: `system.ial_engine`
- `MG_DEFAULTMODE`: `system.defaultmode`
- `MG_MDEV`: `system.mdev`
- `MG_MTYPE`: `system.mtype`

For example, if you want to use `fbcon` NEWGAL engine and `console` IAL engine,
you can use the following commands to specify the environment variables:

```shell
$ export MG_GAL_ENGINE=fbcon
$ export MG_IAL_ENGINE=console
$ export MG_DEFAULTMODE=1024x768-16bpp
$ export MG_MDEV=/dev/input/mice
$ export MG_MTYPE=ps2
```

### Section `pc_xvfb`

The section `pc_xvfb` is only effective when you define the key
`system.gal_engine` having the value `pc_xvfb`.

The valid keys in the section `pc_xvfb` are listed as follow:

- `defaultmode`: The display mode of graphics engine.
   This value will override the value defined by `system.defaultmode`.
- `window_caption`: Window caption text of the XVFB window.
- `exec_file`: the path of the execute file of the XVFB program.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[pc_xvfb]
defaultmode=800x600-16bpp
window_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)
exec_file=/usr/local/bin/gvfb
```

### Section `fbcon`

The section `fbcon` is only effective when you define the key
`system.gal_engine` having the value `fbcon`.

The valid keys in the section `fbcon` are listed as follow:

- `defaultmode`: The display mode of the graphics engine `fbcon`.
- `dpi`: The pixel density of the display, in dots (physical pixels) per inch;
   the default value is 96.

The key `defaultmode` also defines the default display mode for the
`fbcon` engine.
This key value will override the value defined by `system.defaultmode`.
When the section is undefined or the key value is invalid, the `fbcon`
engine will use the key value of `system.gal_engine`.

The content of the section in the default `MiniGUI.cfg` is as follow:

```ini
[fbcon]
defaultmode=1024x768-16bpp
dpi=96
```

### Section `dri`

This section is dedicated to the `dri` graphics engine which runs on
Linux DRI/DRM.
It is available since MiniGUI 4.0.0.

The section `dri` is only effective when you define the key
`system.gal_engine` having the value `dri`.

The valid keys in the section `dri` are listed as follow:

- `defaultmode`: The display mode of the graphics engine `fbcon`.
- `dpi`: The pixel density of the display, in dots (physical pixels) per inch;
   the default value is 96.
- `pixelformat`: The pixel format.
- `device`: The DRI device.

The key `defaultmode` also defines the default display mode for the `dri`
engine. This key value will override the value defined by `system.defaultmode`.
When the section is undefined or the key value is invalid, the `dri`
engine will use the key value of `system.gal_engine`.

For `dri` engine, we introduce a new key `pixelformat` in order to
define the pixel format precisely. We use DRM fourcc code (like `XR24`)
to define the pixel format of the video surface. For more information,
please see the header file `drm/drm_fourcc.h` of libdrm.
Note that only 8/16/24/32 bpp RGB formats are supported.

The content of the section in the default `MiniGUI.cfg` is as follow:

```ini
[dri]
defaultmode=1024x768-32bpp

# We use DRM fourcc code to defined the pixel format of the video surface.
# For more information, please see <drm/drm_fourcc.h> header file.
# Note that only 8/16/24/32 bpp RGB formats are supported.
pixelformat=XR24

# The DRI device
device=/dev/dri/card0
# The resolution of the display
# It is defined in dots (physical pixels) per inch
# The default value is 96.
dpi=96
```

### Section `libinput`

This section is dedicated to the `libinput` input engine which runs on Linux.
It is available since MiniGUI 4.0.0.

The section `libinput` is only effective when you define the key
`system.ial_engine` having the value `libinput`.

The valid keys in the section `libinput` are listed as follow:

- `seat`: The seat identifier; the default value is `seat0`.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[libinput]
seat=seat0
```

### Section `systemfont`

The section `systemfont` defines the system fonts. One system
font will be used to render the text in the window captions,
menus, and controls in MiniGUI.

A system font is a logfont (`logfont` for short) that is created
by calling the function `CreateLogFontFromName`. MiniGUI creates
a logfont based on loaded device fonts, which are defined in
sections such as `rawbitmapfonts`, `varbitmapfonts`, `upf`, `qpf`,
and `truetypefonts`
(see [Sections for devfonts](#sections-for-devfonts)).

A logfont name is a string which has the following form:

    <type>-<facename>-<style>-<width>-<height>-<charset>

The definitions of each part of a logfont name are as follow:

- `<type>` specifies the desired device font type. For example, if you
want to use TrueType fonts for this logfont, use `ttf`.
If you do not want to specify the font type, use `*`.
- `<facename>` specifies the font face name, such as `courier`,
`times`, and so on.
- `<style>` is a string of six alphabets used to define the style
of a logfont, such as italic, bold, underline, etc.
- `<width>` specifies the width of the logfont in pixels.
Usually do not need to specify the width, so use `*` instead.
- `<height>` specifies the height of the logfont in pixels.
- `<charset>` specifies the charset or encoding of the logfont being created.

As an example, the logfont name `rbf-FixedSys-rrncnn-8-16-ISO8859-1` will
create a logfont by using RBF devfonts. The face name of the logfont is
`FixedSys`, and the height is 16, the charset is `ISO8859-1`.

For more information about logfont, please refer to [MiniGUI Programming Guide].

The valid keys in the section `systemfont` are listed as follow:

- `font_number`: The number of system fonts should be created.
**Note that the maximal number of system logfonts is 6. You should not
set this key value to be a number larger than 6.**
- `font<NR>`: The name for the logfont numbered `<NR>`.
- `default`: The system default logfont in the default single-byte character set.
  Its value should be a valid system logfont number.
- `wchar_def`: The system default logfont in the default multiple-byte character set.
  Its value should be a valid system logfont number.
- `fixed`: The logfont with fixed width.
  Its value should be a valid system logfont number.
- `caption`: The logfont for the text in the window caption.
  Its value should be a valid system logfont number.
- `menu`: The logfont for the text in the menu items.
  Its value should be a valid system logfont number.
- `control`: The logfont for the text in the controls.
  Its value should be a valid system logfont number.

You can change the number of system logfonts created. But note that
the maximal number of system logfonts is 6.

You must create at least one logfont in a single-byte character set
(e.g., `ISO8859-1`). MiniGUI defines the system default charsets
according to `default` and `wchar_def` system fonts. And the logfont
names for `default` and `wchar_def` will affect the return value of
`GetSysCharset`, `GetSysCharWidth`, `GetSysCCharWidth` and
`GetSysHeight` functions. Commonly, `default` and `wchar_def`
should be fixed width bitmap fonts.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[systemfont]
font_number=5
font0=rbf-FixedSys-rrncnn-8-16-ISO8859-1
font1=*-FixedSys-rrncnn-*-16-ISO8859-1
font2=*-Courier-rrncnn-*-16-ISO8859-1
font3=*-SansSerif-rrncnn-*-16-ISO8859-1
font4=*-System-rrncnn-*-16-ISO8859-1

default=0
wchar_def=4
fixed=1
caption=4
menu=2
control=3
```

### Section `cursorinfo`

This section specify the cursors used by MiniGUI.

The valid keys in the section `cursorinfo` are listed as follow:

- `cursorpath`: The path in which the cursor files located.
- `cursornumber`: The number of cursors should be loaded.
- `cursor<NR>`: The cursor file the cursor numbered `<NR>`.

Note that the cursor numbers should correspond to the system cursor
indices defined in `minigui/minigui.h` header file:

```cpp
/** System arrow cursor index. */
#define IDC_ARROW       0
/** System beam cursor index. */
#define IDC_IBEAM       1
/** System pencil cursor index. */
#define IDC_PENCIL      2
/** System cross cursor index. */
#define IDC_CROSS       3
/** System move cursor index. */
#define IDC_MOVE        4
/** System  size northwest to southeast cursor index. */
#define IDC_SIZENWSE    5
/** System size northeast to southwest cursor index. */
#define IDC_SIZENESW    6
/** System west to east cursor index. */
#define IDC_SIZEWE      7
/** System north to south cursor index. */
#define IDC_SIZENS      8
/** System up arrow cursor index. */
#define IDC_UPARROW     9
/** System none cursor index. */
#define IDC_NONE        10
/** System help cursor index. */
#define IDC_HELP        11
/** System busy cursor index. */
#define IDC_BUSY        12
/** System wait cursor index. */
#define IDC_WAIT        13
/** System right arrow cursor index. */
#define IDC_RARROW      14
/** System colomn cursor index. */
#define IDC_COLOMN      15
/** System row cursor index. */
#define IDC_ROW         16
/** System drag cursor index. */
#define IDC_DRAG        17
/** System nodrop cursor index. */
#define IDC_NODROP      18
/** System hand point cursor index. */
#define IDC_HAND_POINT  19
/** System hand select cursor index. */
#define IDC_HAND_SELECT 20
/** System horizontal split cursor index. */
#define IDC_SPLIT_HORZ  21
/** System vertical cursor index. */
#define IDC_SPLIT_VERT  22
```

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[cursorinfo]
# Edit following line to specify cursor files path
cursorpath=/usr/local/share/minigui/res/cursor/
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
```

### Section `resinfo`

This section specify the path of the resource files used by MiniGUI.

The valid key in the section `resinfo` is listed as follow:

- `respath`: The path in which the resource files located.

When MiniGUI loads a resource file, it will use the key value
as the prefix for the ultimate full path of the resource file:

- The icon files should be stored in the sub directory of `icon/` of
  the resource path specified by the key value.
- The font files should be stored in the sub directory of `font/` of
  the resource path specified by the key value.
- The image files should be stored in the sub directory of `bmp/` of
  the resource path specified by the key value.
- The cursor files should be stored in the sub directory of `cursor/` of
  the resource path specified by the key value.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[resinfo]
respath=/usr/local/share/minigui/res/
```

### Sections for devfonts

These sections define information of loading device fonts`,` number of
fonts, and name and file of fonts.

The format of device fonts used by MiniGUI is as follows:

    <type>-<facename>-<style>-<width>-<height>-<charset1[,charset2,...]>

The definitions for each part of device `font` are as follow:

- `<type>`: The type of device font, for example, RBF, VBF, QPF,
TrueType, and Adobe Type1 device font are rbf, vbf, qpf, ttf, and tlf.
- `<facename>`: The name of device font. Such as courier, Times
etc.
- `<style>`: The style of device font, it is grouped into six
alphabets. Such as bold, italic, underline or strikethrough etc.
Generally the string is "rrncnn".
- `<width>`: The width of device font, for var-width fonts set to
be maximum width; for vector fonts set to be 0.
- `<height>`: The height of device font, for vector fonts set to
be 0.
- `<charset1, charset2>`: The charset of device font supported.

Each of these sections defines `font_number`, `name<NR>`, and `fontfile<NR>` keys.

- `font_number`: The number of device font loaded.
- `name<NR>`: The name of device font that number is `<NR>`.
- `fontfile<NR>`: The font file of device font that number is `<nr>`.

If you don't need to use a specific type of device font, you can skip
the configuration option by set `font_number=0`.

The content of these sections in the default `MiniGUI.cfg` is as follow:

```ini
[rawbitmapfonts]
font_number=0

[varbitmapfonts]
font_number=0

[upf]
font_number=0

[qpf]
font_number=0

[truetypefonts]
font_number=0
# The devfont now supports multiple font family names since V4.0.0.
name0=ttf-Source Sans Pro,SansSerif-rrncnn-0-0-ISO8859-1,UTF-8
# The path of font file can be relative to the current working directory.
fontfile0=font/SourceSansPro-Regular.ttf

```

### Sections for appearance renderers

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

The section `classic` defines default window element color used.
Generally, it is unnecessary changed.

Table 3.1 window element division and name in the configuration file and
code

| Configure Option         | Macro                        | Comments
| -------------------------|------------------------------|---------
| `caption`                | `WE_METRICS_CAPTION`         | Caption size
| `menu`                   | `WE_METRICS_MENU`            | Menu item, height of the menu bar
| `border`                 | `WE_METRICS_WND_BORDER`      | Window border width
| `scrollbar`              | `WE_METRICS_SCROLLBAR`       | Scroll bar size
| `fgc_active_caption`     | `WE_FGC_ACTIVE_CAPTION`      | Focus status caption foreground color
| `bgca_active_caption`    | `WE_BGCA_ACTIVE_CAPTION`     | Focus status caption background color gradient starting color
| `bgcb_active_caption`    | `WE_BGCB_ACTIVE_CAPTION`     | Focus Status caption background color gradient ending Color
| `fgc_inactive_caption`   | `WE_FGC_INACTIVE_CAPTION`    | Non-focus status caption foreground color
| `bgca_inactive_caption`  | `WE_BGCA_INACTIVE_CAPTION`   | Non-focus status caption background color gradient starting color
| `bgcb_inactive_caption`  | `WE_BGCB_INACTIVE_CAPTION`   | Non-focus status caption background color gradient ending color
| `fgc_menu`               | `WE_FGC_MENU`                | Menu foreground color
| `bgc_menu`               | `WE_BGC_MENU`                | Menu background color
| `fgc_active_border`      | `WE_FGC_ACTIVE_WND_BORDER`   | Focus status window border color
| `fgc_inactive_border`    | `WE_FGC_INACTIVE_WND_BORDER` | Non-focus status window border color
| `fgc_msgbox`             | `WE_FGC_MESSAGEBOX`          | Message box foreground color
| `fgc_msgbox`             | `WE_FONT_MESSAGEBOX`         | Message box font
| `fgc_tip`                | `WE_FGC_TOOLTIP`             | Prompt box foreground color
| `bgc_tip`                | `WE_BGC_TOOLTIP`             | Prompt box background color
| `fgc_window`             | `WE_FGC_WINDOW`              | Window foreground
| `bgc_window`             | `WE_BGC_WINDOW`              | Window background color
| `fgc_3dbox`              | `WE_FGC_THREED_BODY`         | The color of the symbol on the surface of the 3D box, such as the color of check mark, arrow, etc.
| `mainc_3dbox`            | `WE_MAINC_THREED_BODY`       | Three-dimensional box border and surface color
| `fgc_selected_item`      | `WE_FGC_SELECTED_ITEM`       | The foreground color of the selected menu item (list item)
| `bgc_selected_item`      | `WE_BGC_SELECTED_ITEM`       | The background color of the selected menu item (list item)
| `bgc_selected_lostfocus` | `WE_BGC_SELECTED_LOSTFOCUS`  | The background color after the selected menu item (list item) loses focus
| `fgc_disabled_item`      | `WE_FGC_DISABLED_ITEM`       | Foreground color of invalid menu item (list item)
| `bgc_disabled_item`      | `WE_BGC_DISABLED_ITEM`       | Invalid menu item (list item) background color
| `fgc_hilight_item`       | `WE_FGC_HIGHLIGHT_ITEM`      | Highlight the foreground color of the menu item (list item)
| `bgc_hilight_item`       | `WE_BGC_HIGHLIGHT_ITEM`      | Highlight the background color of the menu item (list item)
| `fgc_significant_item`   | `WE_FGC_SIGNIFICANT_ITEM`    | Foreground color of important menu item (list item)
| `bgc_significant_item`   | `WE_BGC_SIGNIFICANT_ITEM`    | Background color of important menu items (list items)
| `bgc_desktop`            | `WE_BGC_DESKTOP`             | Desktop background color
|                          | `WE_FONT_MENU`               | Menu font
|                          | `WE_FONT_CAPTION`            | Caption fonts
|                          | `WE_FONT_TOOLTIP`            | Prompt box font

The content of the section in `MiniGUI.cfg` is as follows:

```ini
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
```

### Other sections

The section `mouse` defines the time of mouse `double clicked`. It
is used to handle with system inner events. Generally, it is unnecessary
changed.

The definition of the keys in the section is as follows:

- `dblclicktime`: The mouse double clicked time in ms

The content of the section in `MiniGUI.cfg` is as follows:

```ini
[mouse]
dblclicktime=300
```

The section `event` defines event timeout and auto-repeat time used by
system internal event process. Generally, it is unnecessary changed.

The definition of the keys in the section is as follows:

- `timeoutusec`: Event timeout time in ms
- `repeatusec`: Event repeat time in ms

The content of the section in `MiniGUI.cfg` is as follows:

```ini
[event]
timeoutusec=300000
repeatusec=50000
```

## Incore Configuration

When use incore resources, MiniGUI don’t need the file `MiniGUI.cfg`.
The appropriate configuration options are defined in the file
`src/sysres/mgetc.c`.

When we compile MiniGUI with `--enable-incoreres` option, MiniGUI
application doesn’t need the file `MiniGUI.cfg`. The required options
are given in the file `src/sysres/mgetc.c`.

Similar with the structure in `MiniGUI.cfg`, MiniGUI defines an
structure `ETCSECTION`, array `_etc_sections` and variable MGETC in
`mgetc.c`. The array `mgetc_sections` is appropriate with section in
configuration file. MGETC that is `ETC_S` type is appropriate with
configuration file.

### Structure `ETCSETCTION`

The structure `ETCSECTION` is defined in the file named `minigui.h`’. The following is in detail.

```cpp
/** The config section information */
typedef struct _ETCSECTION
{
    /** Allocated number of keys */
    int key_nr_alloc;
    /** Key number in the section */
    int key_nr;
    /** Name of the section */
    char *name;
    /** Array of keys */
    char** keys;
    /** Array of values */
    char** values;
} ETCSECTION;
```

The `key_nr_alloc` is the interface of other configuration options.
Its value must be 0 in incore. The `key_nr` defines the number of the
key in section. The name defines the name of section. The keys and
values is the array of key and value. The number of key array and value
array is corresponded with the number of the `key_nr`.

Below is the definition of `_etc_sections` in the `mgetc.c` file.

```cpp
```

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

### Structure `ETC_S`

`ETC_S` structure was defined in the file `minigui.h`, the content of
ETC_S listed as the follow:

```cpp
/** The config file information*/
typedef struct _ETC_S
{
    /** Allocated number of sections */
    int sect_nr_alloc;
    /** Number of sections */
    int section_nr;
    /** Pointer to section arrays */
    PETCSECTION sections;
} ETC_S;
```

Therefore, `sect_nr_alloc` is the interface of the other
configuration options, it’s value must be 0 in incore, `sect_nr`
specify the number of section, sections is ETCSECTION type structure
array, the number of item is not less than the value, the first item
specified this value.

The `mgetc_sections` array was defined as the follow in the
`mgetc.c` file.

```cpp
static ETC_S _ETC = {
    0,
    sizeof(_etc_sections)/sizeof(ETCSECTION),
    _etc_sections
};
```

The number of section is `sizeof(_etc_sections)/sizeof(ETCSECTION)` in
the MGETC structure; the section array is `mgetc_sections` array above.

## Samples

Under most circumstances, we modify runtime configuration file, we will
be limited to several sections. The system section and font related
several sections are primary sections. In this chapter, we will give two
configuration examples.

```ini
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
```

```cpp
static char *SYSTEMFONT_KEYS[] =

{"font_number", "font0", "default", "wchar_def", "fixed", "caption",
"menu", "control"};

static char *SYSTEMFONT_VALUES[] =
{
    "1","rbf-fixed-rrncnn-8-16-ISO8859-1", "0", "0", "0", "0", "0", "0"
};
```

```ini
[system]
# GAL engine and default options
gal_engine=commlcd

# IAL engine
ial_engine=auto
mdev=/dev/ts
mtype=IMPS2
```

```cpp
static char *SYSTEM_KEYS[] = {"gal_engine", "ial_engine", "mdev", "mtype"};
static char *SYSTEM_VALUES[] = {"commlcd", "auto", "/dev/ts", "IMPS2"};
```

---

[&lt;&lt; Compile-time Configuration](MiniGUIUserManualCompiletimeConfiguration.md) |
[Table of Contents](README.md) |
[Feature List &gt;&gt;](MiniGUIUserManualFeatureList.md)

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
