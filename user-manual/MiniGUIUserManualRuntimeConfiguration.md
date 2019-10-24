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
- The fonts device to load.
- The system fonts for caption, menu, and control.
- The mouse cursors.
- The icons, and bitmaps to decorate window.

Generally, the runtime configuration is loaded from `MiniGUI.cfg` file.
But if you've configured MiniGUI with built-in resources in building stage,
the runtime configuration will be compiled into the MiniGUI Core library.

In this chapter, we first describe the runtime configuration
using the configuration file, then describe how to specify runtime
configuration if you've configured MiniGUI with resources in MiniGUI Core .
For convenience, we call the later situation as `incore configuration`.

## Configuration File

On Linux, after building and installing MiniGUI using the default
configuration, the file `etc/MiniGUI.cfg` in MiniGUI source tree will
be installed into `/usr/local/etc/` directory. However, you can deploy
your own version of `MiniGUI.cfg` in your home directory. And this version
will have a higher priority.

Actually, when MiniGUI starts, it tries to locate the correct `MiniGUI.cfg`
according to the following steps:

1. search `MiniGUI.cfg` in current working directory. If not found,
1. search `.MiniGUI.cfg` in home directory of the current user. If not found,
1. search `MiniGUI.cfg` in `/usr/local/etc`. If not found,
1. search `MiniGUI.cfg` in `/etc/`.

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

You can use the section `system` to specify the effective `NEWGAL`
engine and `IAL` engine. For historical reasons, you can also use
this section to specify the mouse device and mouse protocol for
`console` `IAL` engine.

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

For example, if you want to use `fbcon` `NEWGAL` engine and `console` `IAL `engine,
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
`system.gal_engine` with value `pc_xvfb`.

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
`system.gal_engine` with value `fbcon`.

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
`system.gal_engine` with value `dri`.

The valid keys in the section `dri` are listed as follow:

- `defaultmode`: The display mode of the graphics engine `fbcon`.
- `dpi`: The pixel density of the display, in dots (physical pixels) per inch;
   the default value is 96.
- `pixelformat`: The pixel format.
- `device`: The DRI device.

The key `defaultmode` also defines the default display mode for the `dri`
engine. This key value will override the value defined by `system.defaultmode`.
If the section is undefined or the key value is invalid, the `dri`
engine will use the key value of `system.gal_engine`.

For `dri` engine, we introduced a new key `pixelformat` to
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
`system.ial_engine` with value `libinput`.

The valid keys in the section `libinput` are listed as follow:

- `seat`: The seat identifier; the default value is `seat0`.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[libinput]
seat=seat0
```

### Section `systemfont`

The section `systemfont` defines system fonts. A system
font is a logical font which will be used to render the text
in the window captions, menus, and controls in MiniGUI.

A logical font (`logfont` for short) is an object used by
MiniGUI app to render paragraphs, words, or characters.
While a device font (`devfont` for short) is a underlying object
containing the glyphs of all or some characters in a specific
language or script. Basically, one logfont corresponds to one
or multiple devfonts.

MiniGUI creates the system font by calling the function
`CreateLogFontFromName` based on loaded device fonts, which are
defined in sections such as `rawbitmapfonts`, `varbitmapfonts`,
`upf`, `qpf`, and `truetypefonts`
(see [Sections for devfonts](#sections-for-devfonts)).

A logfont name is a string which has the following form:

    <type>-<family>-<style>-<width>-<height>-<charset>

The definitions of each part of a logfont name are as follow:

- `<type>` specifies the desired device font type. For example, if you
want to use TrueType fonts for this logfont, use `ttf`.
If you do not want to specify the font type, use `*`.
- `<family>` specifies the font face name, such as `courier`,
`times`, and so on.
- `<style>` is a string of six alphabets used to define the style
of a logfont, such as italic, bold, underline, etc.
- `<width>` specifies the width of the logfont in pixels.
Usually do not need to specify the width, so use `*` instead.
- `<height>` specifies the height of the logfont in pixels.
- `<charset>` specifies the charset or encoding of the logfont created.

As an example, the logfont name `rbf-FixedSys-rrncnn-8-16-ISO8859-1` will
create a logfont by using RBF devfonts. The face name of the logfont is
`FixedSys`, the height is 16, and the charset is `ISO8859-1`.

For more information about logfont, please refer to [MiniGUI Programming Guide].

The valid keys in the section `systemfont` are listed as follow:

- `font_number`: The number of system fonts to be created.
**Note that the maximal number of system logfonts is 6. You should not
set this key value larger than 6.**
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
names for `default` and `wchar_def` will affect the return value of functions：
`GetSysCharset`, `GetSysCharWidth`, `GetSysCCharWidth` and
`GetSysHeight`. Commonly, `default` and `wchar_def`
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

#### Changes in MiniGUI 4.0.0

Since version 4.0.0, you can specify up to 7 family names for a logfont name, for example:

    ttf-Courier,宋体,Naskh,SansSerif-rrncns-U-16-UTF-8

In this way, you can specify a logfont to use multiple devfonts to render a complex text.

Moreover, the previous width field of a logfont name is used for the glyph orientation:

- `U`: Glyphs stand upright (default).
- `S`: Glyphs are rotated 90 degrees clockwise (sideways).
- `D`: Glyphs are upside-down.
- `L`: Glyphs are rotated 90 degrees counter-clockwise (sideways left).

### Section `cursorinfo`

This section specifies the cursors used by MiniGUI.

The valid keys in the section `cursorinfo` are listed as follow:

- `cursorpath`: The path in which the cursor files are located.
- `cursornumber`: The number of cursors to be loaded.
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

This section specifies the path of the resource files used by MiniGUI.

The valid key in section `resinfo` is listed as follow:

- `respath`: The path in which the resource files located.

When MiniGUI loads a resource file, it will use the key value
as the prefix for the ultimate full path of the resource file:

- The icon files should be stored in the sub directory of `icon/` of
  the resource path specified by the key `resinfo.respath`.
- The font files should be stored in the sub directory of `font/` of
  the resource path specified by the key `resinfo.respath`.
- The image files should be stored in the sub directory of `bmp/` of
  the resource path specified by the key `resinfo.respath`.
- The cursor files should be stored in the sub directory of `cursor/` of
  the resource path specified by the key `resinfo.respath`.

The content of this section in the default `MiniGUI.cfg` is as follow:

```ini
[resinfo]
respath=/usr/local/share/minigui/res/
```

### Sections for devfonts

These sections specify the information of the devfonts which are
loaded by MiniGUI.

MiniGUI can load a devfont from a font file or from
font data stored in memory.
Generally, you specify the devfonts which should be loaded
at the starting stage of MiniGUI in the runtime configuration.

Note that since MiniGUI 3.0.0, there are some built-in devfonts
compiled into the MiniGUI Core library by default. Therefore, if you
do not specify any devfont to load in the runtime configuration,
MiniGUI still runs.

In the runtime configuration, we use a section for each font type:

- `rawbitmapfonts` for RBF (Raw Bitmap Font) fonts.
- `varbitmapfonts` for VBF (Variable Bitmap Font) fonts.
- `upf` for UPF (Unicode Pre-rendered Font) fonts.
- `qpf` for QPF (Qt Pre-rendered Font) fonts.
- `truetypefonts` for TrueType fonts. When using FreeType 2, also for
   OpenType and Adobe Type 1 fonts.

Each of these sections defines the following keys:

- `font_number`: The number of devfonts to be loaded.
- `name<NR>`: The name of the devfont numbered `<NR>`.
- `fontfile<NR>`: The font file of the devfont numbered `<NR>`.

For example, you can define the `upf` section as follow to load one UPF devfont:

```ini
[upf]
font_number=1
name0=upf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312,BIG5,GBK,UTF-8,UTF-16LE,UTF-16BE
fontfile0=../res/fonts/unifont_160_50.upf
```

If you don't need to use a specific type of devfont, you can skip
the configuration section by setting `font_number=0`.

Like logfont, a string is used as the devfont name to specify the
family name, style, size, and charsets of a devfont object. The format of
a devfont name is as follow:

    <fonttype>-<family>-<styles>-<width>-<height>-<charset1[,charset2,...]>

The definitions for each part of the devfont name are as follow:

- `<fonttype>`: The type of device font, for example, RBF, VBF, QPF,
TrueType, and Adobe Type1 device fonts are rbf, vbf, qpf, ttf, and tlf.
- `<family>`: The name of device font. Such as courier, Times
etc.
- `<styles>`: The style of device font, it is grouped into six
alphabets. Such as bold, italic, underline etc. Generally the string is
`rrncnn`.
- `<width>`: The width of device font, for variable width fonts, set it to
the maximal width; for vector fonts, set it to 0.
- `<height>`: The height of device font, for vector fonts, set it to 0.
- `<charset1, charset2>`: The charsets supported by the devfont.

For example,

    ttf-Arial-rrncnn-0-0-ISO8859-1,UTF-8

It means that the devfont is a TrueType vector font, the family name of
the devfont is `Arial`, the styles are represented by a string `rrncnn`,
the size can be any value (a vector font can be arbitrarily scaled), and
the charsets/encodings of the devfont are `ISO8859-1` and `UTF-8`.

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
```

#### Changes in MiniGUI 4.0.0

Since version 4.0.0, you can specify the aliases for the family name of a devfont:

    <fonttype>-<family[,aliase]*>-<styles>-<width>-<height>-<charset[,charset]*>

For example:

    ttf-Arial,Sans Serif-rrncnn-0-0-ISO8859-1,UTF-8
    ttf-courier,monospace,serif-rrncnn-0-0-ISO8859-1,UTF-8

Note that the length of a devfont name can not exceed 255 bytes.

The following `truetypefonts` section uses new format for devfont name:

```ini
# Free Adobe TrueType or OpenType fonts
# https://github.com/adobe-fonts/
[truetypefonts]
font_number=3
name0=ttf-Source Sans Pro,SansSerif-rrncnn-0-0-ISO8859-1,UTF-8
fontfile0=font/SourceSansPro-Regular.ttf
name1=ttf-Source Serif Pro,Serif-rrncnn-0-0-ISO8859-1,UTF-8
fontfile1=font/SourceSerifPro-Regular.ttf
name2=ttf-Source Code,Monospace-rrncnn-0-0-ISO8859-1,UTF-8
fontfile2=font/SourceCodeVariable-Roman.ttf
```

### Sections for appearance renderers

Since version 3.0, MiniGUI Core introduced the concept of appearance renderer
(also called `look and feel renderer`).
You can change the look and feel of a main window or a basic control
by specifying an appearance renderer for it.
An appearance renderer defines a set of operations to draw the window
elements such as caption, borders, and scrollbars of a window.
As in the previous version, you can only
choose one style among three pre-defined window styles by using the
compile-time configuration option.

The appearance renderer provides a very flexible implementation to
customize the appearance of the main window and controls. You can
easily customize the sizes and colors of a specific appearance renderer
by specifying different values to the runtime configuration keys.
Or you can change the appearance on the fly via MiniGUI APIs.
You can even write your own appearance renderer to customize the
look and feel of MiniGUI.

The MiniGUI component mGNCS, also uses the concept of appearance renderer
to customize the look and feel of mGNCS controls.

For more information about appearance renderer, please refer to
[MiniGUI Programming Guide].

MiniGUI Core defines some attributes to control the rendering
behaviours for main windows or controls. MiniGUI Core provides
four appearance renderers:

- `classic` renderer draws the window elements in 3D style like Windows XP.
- `flat` renderer draws the window elements in flat style, which is suitable
   to gray screen.
- `skin` renderer draws the window elements using bitmaps.
- `fashion` renderer draws the window elements using macOS like style.

Note that the `classic` renderer is built-in MiniGUI Core library, you
can not disable this renderer.

Note that MiniGUI Core does not implement the `fashion` renderer. This
renderer draws the window elements by using 2D vector graphics functions,
so it is implemented by mGPlus component.

In runtime configuration, MiniGUI uses `classic`, `flat`, `skin`,
and `fashion` sections to define the options for these four appearance
renderers.

The following table gives the key names for the options and the corresponding
macros which referring to the specific window elements in MiniGUI code.

##### Table: Key names for various window elements

| Key name                 | Macro                        | Comments
|--------------------------|------------------------------|---------
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

In addition to the keys above, one renderer section must include the following keys:

- `iconnumber`: The number of system icons to be loaded.
   **Note that the maximal number of system icons is 5.**
- `icon0`: The default application icon (`IDI_APPLICATION`).
- `icon1`: The hand/stop icon (`IDI_HAND` or `IDI_STOP`).
- `icon2`: The question icon (`IDI_QUESTION`).
- `icon3`: The exclamation icon (`IDI_EXCLAMATION`).
- `icon4`: The information/asterisk icon (`IDI_INFORMATION` or `IDI_ASTERISK`).
- `dir`: The icon used to represent a directory entry (`OpenFileDialogBox`).
- `file`: The icon used to represent a file entry (`OpenFileDialogBox`).
- `treefold`: The icon used to represent a folded tree node.
- `treeunfold`: The icon used to represent a unfolded tree node.
- `radiobutton`: The bitmap used by a radio button control.
- `checkbutton`: The bitmap used by a check button control.
- `bgpicture`: The desktop background image. Set to `none` if no background image.
- `bgpicpos`: The position of the background image. Set to one of the following values:
   + `center`
   + `upleft`
   + `downleft`
   + `upright`
   + `downright`
   + `upcenter`
   + `downcenter`
   + `vcenterleft`
   + `vcenterright`
   + `upleft`
   + `downleft`
   + `upright`
   + `downright`
   + `upcenter`
   + `downcenter`
   + `vcenterleft`
   + `vcenterright`
   + `none`

For `skin` appearance renderer, it uses the following extra keys to define
the bitmaps for various window elements:

- `skin_bkgnd`: The window background.
- `skin_caption`: The caption background.
- `skin_caption_btn`: The buttons on caption.
- `skin_scrollbar_hshaft`: The tray of horizontal scrollbar.
- `skin_scrollbar_vshaft`: The tray of vertical scrollbar.
- `skin_scrollbar_hthumb`: The thumb on the horizontal scrollbar.
- `skin_scrollbar_vthumb`: The thumb on the vertical scrollbar.
- `skin_scrollbar_arrows`: The arrows on the scrollbar.
- `skin_tborder`: The top border.
- `skin_bborder`: The bottom border.
- `skin_lborder`: The left border.
- `skin_rborder`: The right border.
- `skin_arrows`: The arrows on menu item.
- `skin_arrows_shell`:
- `skin_pushbtn`: The push button.
- `skin_radiobtn`: The radio button.
- `skin_checkbtn`: The check button.
- `skin_tree`:
- `skin_header`:
- `skin_tab`:
- `skin_tbslider_h`:
- `skin_tbslider_v`:
- `skin_trackbar_horz`:
- `skin_trackbar_vert`:
- `skin_progressbar_htrack`:
- `skin_progressbar_vtrack`:
- `skin_progressbar_hchunk`:
- `skin_progressbar_vchunk`:

The content of the appearance renderer sections in `MiniGUI.cfg` is as follow:

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

The section `mouse` defines parameters for mouse event.

The key in the section is as follow:

- `dblclicktime`: The mouse button double click time in milliseconds.

The content of the section in the default `MiniGUI.cfg` is as follow:

```ini
[mouse]
dblclicktime=300
```

The section `event` defines event timeout and auto-repeat time used by
the internal event process.

The keys in the section are as follow:

- `timeoutusec`: Event timeout time in microseconds.
- `repeatusec`: Event repeat time in microseconds.

The content of the section in the default `MiniGUI.cfg` is as follow:

```ini
[event]
timeoutusec=300000
repeatusec=50000
```

Generally, it is unnecessary to change these sections.

## Incore Configuration

If you compiled MiniGUI with `--enable-incoreres` option, MiniGUI
will not use the file `MiniGUI.cfg`. Instead, you specify the runtime
configuration options in the source file `src/sysres/mgetc.c`, and
the options will be compiled into the MiniGUI Core library.

Therefore, except the options that can be changed via environment
variables, you should change the source file to modify the runtime
configuration options and rebuild MiniGUI Core library after changing
the file.

Similar to the structure of `MiniGUI.cfg`, MiniGUI defines an
structure `ETCSECTION`, an static array `_etc_sections` and a static
variable `_ETC` in `mgetc.c`. The array `mgetc_sections` corresponds
to the sections in the configuration file, and `_ETC` which has `ETC_S`
type corresponds to the whole configuration file.

The following code snippet shows the skeleton of the `mgetc.c` source file:

```cpp
// Section: system
static char* _system_keys[]={
// GAL engine and default options
    "gal_engine",
    "defaultmode",
// IAL engine
    "ial_engine",
    "mdev",
    "mtype"
};
static char* _system_values[]={
// GAL engine and default options
    "pc_xvfb",
    "800x600-16bpp",
// IAL engine
    "pc_xvfb",
    "/dev/input/mice",
    "IMPS2"
};

// Section: pc_xvfb
static char* _pc_xvfb_keys[]={
    "defaultmode",
    "window_caption",
    "exec_file"
};
static char* _pc_xvfb_values[]={
    "800x600-16bpp",
    "XVFB-for-MiniGUI-3.0-(Gtk-Version)",
    "/usr/local/bin/gvfb"
};

// Other sections go here...
...

static ETCSECTION _etc_sections [] = {
    {0, 5, "system", _system_keys, _system_values },
    {0, 3, "pc_xvfb", _pc_xvfb_keys,_pc_xvfb_values },
    // other sections go here...
    ...
}

static ETC_S _ETC = {
    0,
    sizeof(_etc_sections)/sizeof(ETCSECTION),
    _etc_sections
};

GHANDLE __mg_get_mgetc (void)
{
    return (GHANDLE) &_ETC;
}

```

The function `__mg_get_mgetc` returns the pointer to `_ETC` as a `GHANDLE`
variable to the caller. After getting the handle to the ETC object, you can use
MiniGUI APIs to get the value of a key in a section.

For more information, please refer to [MiniGUI Programming Guide].

You can modify the file `mgetc.c` manually to reflect your
runtime configuration. However, you can use the tool `mgcfg-trans` to
generate your `mgetc.c` file based on a `MiniGUI.cfg` file.

For more information, please refer to [Tools].

### Structure `ETCSETCTION`

The structure `ETCSECTION` is defined in the header file `minigui/minigui.h`:

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

The field `key_nr_alloc` is used internally, and must be set to 0.
The field `key_nr` defines the number of the keys in section.
The field `name` defines the name of section. The field `keys` and
the field `values` are the string array of the keys and values.
The size of the key array and the value array should match the
number of `key_nr`.

### Structure `ETC_S`

`ETC_S` structure is also defined in the header file `minigui/minigui.h`:

```cpp
/** The config file information */
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

The field `sect_nr_alloc` is used internally, and must be set to 0.
The field `section_nr` specifies the number of the sections, and
the field `sections` is the pointer to the array of `ETCSECTION`.

## Samples

In practice, we often change the section `system`, `systemfont`,
and `devfonts` sections for a specific project. Therefore,
the samples in this section will only give the changed sections.

The following sample runtime configuration comes from
the `MiniGUI.cfg` used by `mGUXDemo`:

```ini
[system]
# GAL engine and default options
gal_engine=pc_xvfb
defaultmode=360x480-16bpp

# IAL engine
ial_engine=pc_xvfb
mdev=/dev/input/event0
mtype=IMPS2

[fbcon]
defaultmode=1024x768-16bpp

[pc_xvfb]
defaultmode=360x480-32bpp
skin=etc/gvfb.skin
window_caption=XVFB-for-MiniGUI-3.0-(Gtk-Version)
exec_file=/usr/local/bin/gvfb

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

[rawbitmapfonts]
font_number=0

[varbitmapfonts]
font_number=0

[upf]
font_number=0

[qpf]
font_number=0

[truetypefonts]
font_number=1
name0=ttf-helvetica-rrncnn-0-0-ISO8859-1,GB2312-0,UTF-8
fontfile0=font/Helvetica.ttf
```

The following sample runtime configuration comes from
the `MiniGUI.cfg` file used by `CBPlusUI` in `mg-demos` package:

```ini
[system]
# GAL engine and default options
gal_engine=pc_xvfb
defaultmode=240x240-16bpp
# IAL engine
ial_engine=pc_xvfb
mdev=/dev/input/mice
mtype=IMPS2

[fbcon]
defaultmode=1024x768-16bpp

[qvfb]
defaultmode=1024x768-16bpp
display=0

#{{ifdef _MGGAL_PCXVFB
[pc_xvfb]
defaultmode=240x240-16bpp.rgb565
window_caption=CBPlus
exec_file=/usr/local/bin/gvfb
#}}

# The first system font must be a logical font using RBF device font.
[systemfont]
font_number=3
font0=rbf-FixedSys-rrncnn-8-16-ISO8859-1
font1=upf-unifont-rrncnn-16-16-UTF-8
font2=ttf-HanSans-srncnn-*-16-UTF-8
default=0
wchar_def=1
fixed=1
caption=1
menu=1
control=2

[rawbitmapfonts]
font_number=0

[varbitmapfonts]
font_number=0

[qpf]
font_number=0

[upf]
font_number=1
name0=upf-unifont-rrncnn-16-16-ISO8859-1,ISO8859-15,GB2312,BIG5,GBK,UTF-8,UTF-16LE,UTF-16BE
fontfile0=../res/fonts/unifont_160_50.upf

[truetypefonts]
font_number=1
name0=ttf-HanSans-rrncnn-*-*-ISO8859-1,ISO8859-15,GB2312,BIG5,GBK,UTF-8,UTF-16LE,UTF-16BE
fontfile0=../res/fonts/SourceHanSans-Normal.ttc

```

---

[&lt;&lt; Compile-time Configuration](MiniGUIUserManualCompiletimeConfiguration.md) |
[Table of Contents](README.md) |
[Tools &gt;&gt;](MiniGUIUserManualTools.md)

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
[Writing DRI Engine Driver for Your GPU]: /supplementary-docs/Writing-DRI-Engine-Driver-for-Your-GPU.md
[Writing MiniGUI Apps for 64-bit Platforms]: /supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md

[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
