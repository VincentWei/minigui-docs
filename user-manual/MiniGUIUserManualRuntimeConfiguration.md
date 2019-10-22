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

In GNU development environment, after installing MiniGUI by default
configuration, the file `etc/MiniGUI-classic.cfg` in MiniGUI source
tree will be installed in `/usr/local/etc/` directory, and rename to
`MiniGUI.cfg`. When MiniGUI application starts, It will find
`MiniGUI.cfg` as follow:

- the application first search `MiniGUI.cfg` in current directory, then
search `.MiniGUI.cfg` in home directory.
- then search `MiniGUI.cfg` in `/usr/local/etc`, at last in `/etc/`.

If user don’t create the file `MiniGUI.cfg` in current directory and
home directory, the application will use the file `MiniGUI.cfg` in
`/usr/local/etc/` as default configuration file.

When we compile MiniGUI with `--enable-incoreres` option, MiniGUI
application doesn’t need the file `MiniGUI.cfg`. The required options
are given in the file `src/sysres/mgetc.c`.

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

### Section `system`

The section `system` not only defines the graphics engine
(`gal_engine`) and the input engine (`ial_engine`) in runtime
MiniGUI, which must be one of engines configured on MiniGUI compiling,
but also defines the mouse device (`mdev`) and the mouse protocol type
(`mtype`).

The definition of the keys in section `system` is as follows:

- `gal_engine`: The graphics engine used.
- `defaultmode`: The graphics engine display mode used, its format is widthxheight-bpp.
- `ial_engine`: The input engine used.
- `mdev`: The mouse device file.
- `mtype`: The mouse protocol type.

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

### Section `pc_xvfb`

The section `pc_xvfb` is only available when you define the
`gal_engine` in section `system` for `pc_xvfb`. It has been
supported by Linux(Ubuntu) and Window.

The definition of the keys in section `pc_xvfb` is as follows:

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

### Section `fbcon`

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

### Section `dri`

### Section `libinput`

### Section `systemfont`

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

- `<type>` is the desired device font type, if you do not want to
specify it, use `*`.
- `<facename>` is to define the font face name, such as courier
and times etc.
- `<style>` is the string of six alphabets to define style of a
logic font, such as italic, bold, underline or strike through etc.
- `<width>` is to define the width of the logic font. Usually do
not need to specify, use `*` instead.
- `<height>` is to define the height of the logic font.
- `<charset>` is to define charset of the logic font being created.

Furthermore, MiniGUI V2.0.x provides auto-scaling the font glyph. If you
want to use this function, you only need use ‘S’ in forth character when
you define logical font styles. Note that you don’t need to use this
style when you use vector font, such as TrueType, because vector font
can produce corresponding font glyph according to desired logical font
size.

The definition of the keys in section `systemfont` is as follows:

- `font_number`: The number of system fonts created.
- `font<NR>`: The number `<NR>` logical font name.
- `default`: System default font (single character set). Its value is the
number of logical font.
- `wchar_def`: Default font used by multiple character set. Its value
is the number of above logical font.
- `fixed`: The font used by fixed width character set. Its value is the
number of above logical font.
- `caption`: The caption font. Its value is the number of above logical
font.
- `menu`: The menu font. Its value is the number of above logical font.

You can change the number of system font created. But you must create a
single character set (for example: `ISO8859-1`) at least. MiniGUI defines
the system default charsets according to `default`, `wchar_def`
system fonts, and this would affect the return value of
`GetSysCharset`, `GetSysCharWidth`, `GetSysCCharWidth` and
`GetSysHeight` functions. Commonly, `default` and `wchar_def`
must fixed width dot-matrix font, i.e RBF. And the width of multiply
character set must be twice with the width of single character set.

The content of the section in `MiniGUI.cfg` is as follows:

```ini
# The first system font must be a logical font using RBF device font.
[systemfont]
font_number=6
font0=rbf-fixed-rrncnn-8-16-ISO8859-1
font1=*-fixed-rrncnn-*-16-GB2312
font2=*-Courier-rrncnn-*-16-GB2312
font3=*-SansSerif-rrncnn-*-16-GB2312
font4=*-Times-rrncnn-*-16-GB2312
font5=*-Helvetica-rrncnn-*-16-GB2312
default=0
wchar_def=1
fixed=1
caption=2
menu=3
control=3
```

### Section `cursorinfo`

### Section `resinfo`

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
