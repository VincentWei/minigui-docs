_How to build source for incore images and fonts, and load them for your MiniGUI apps._

Table of Contents

- [Overview](#overview)
- [Tools for Generating Incore Data](#tools-for-generating-incore-data)
- [APIs for Managing Incore Data](#apis-for-managing-incore-data)
- [Restrictions](#restrictions)

## Overview

We often want to embed the raw data of images and/or fonts into the final executable
of a MiniGUI app:

- The operating system does not provide support for file system.
- You want to protect your digital intellectual properties such as icons.

For this purpose, MiniGUI provides a set of APIs and tools to embed the arbitrary
data into the final executable.

Note that, in MiniGUI term, we often call the embedded data as `incore data`,
`incore resource`, or `inner resource`.

For a complete sample, please refer to:

<https://github.com/VincentWei/mg-samples/tree/master/incore-data>

## Tools for Generating Incore Data

We provide some tools in [mg-tools](https://github.com/VincentWei/mg-tools)
to generate the source file for your incore data:

- `bin2c`: this is a general tool for generating any binary file to a
   C source file. This tool generates a `unsigned char` array for your
   program.
- `vbf2c`: this tool generates a `VBFINFO` struct from a MiniGUI VBF font
   file for your program.
- `upf2c`: this tool generates a `UPFINFO` struct from a MiniGUI UPF font
   file for your program. It also generates an external function to return
   the pointer to the struct instead of exporting a global symbol of
   the struct name.

To generate an incore source file for a UPF file, you can call `upf2c`:

```shell
 $ upf2c res/unifont_160_50.upf unifont_160_50
```

This command will generate a source file named `unifont_160_50.c`:

```cpp
/*
** In-core UPF file for upf_unifont_160_50.
**
** This file is created by 'upf2c'
** Please do not modify it manually.
**
*/
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>

#ifdef _MGFONT_UPF

typedef struct
{
    Uint8       width;
    Uint8       height;
    Sint8       ascent;
    Sint8       descent;
    Uint8       max_width;
    Uint8       underline_pos;
    Uint8       underline_width;
    Sint8       leading;
    Uint8       mono_bitmap;
    Uint8       reserved[3];
    const void* root_dir;
    Uint32      file_size;
} UPFINFO;

static const unsigned char font_data[] = {
   ...
};

static const UPFINFO upf_unifont_160_50 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0},
    font_data, sizeof (font_data)
};

const void* get_incore_font_data_upf_unifont_160_50 (void)
{
    return &upf_unifont_160_50;
}
#endif /* _MGFONT_UPF */
```

To generate the source file for incore images or RBF fonts, you can use
`bin2c`:

```shell
$ bin2c -o png_pics.inc res/*.png
```

This command will generate a large C source file which defines
some `unsigned char` arrays for the PNG files in `res/` subdirectory,
one array for each file:

```cpp
static const unsigned char _png__mguxdemo_10_data[] = {
    ...
};

static const unsigned char _png__mguxdemo_11_data[] = {
    ...
};

```

The variable name for one file is consisted with the file name and
the `_png__` prefix and `_data` suffix.

## APIs for Managing Incore Data

For fonts and images, MiniGUI provides the basic API to load them from
incore data:

```cpp
DEVFONT* GUIAPI LoadDevFontFromIncoreData (const char *devfont_name,
        const void *data);
void GUIAPI DestroyDynamicDevFont (DEVFONT **devfont);

int GUIAPI LoadBitmapFromMem (HDC hdc, PBITMAP pBitmap,
                const void* mem, int size, const char* ext);
void GUIAPI UnloadBitmap (PBITMAP pBitmap);
```

For fonts, you should load an incore font before using the font,
generally before creating any main window, and destroy the font
before exiting MiniGUI:

```cpp
#define FONTNAME_UNIFONT_160_50     "upf-unifont-rrncnn-16-16-UTF-8"
static DEVFONT* devfont_unifont_160_50;

...
    // Load incore font to create a devfont object
    if ((devfont_unifont_160_50 = LoadDevFontFromIncoreData(
            FONTNAME_UNIFONT_160_50,
            get_incore_font_data_upf_unifont_160_50())) == NULL) {
        _ERR_PRINTF("Failed to load incore UPF font.\n");
        exit (1);
    }

    // use the devfont by creating a logfont object
    logfont = CreateLogFontByName("upf-unifont-rrncnn-16-16-UTF-8");
...

    // Destroy devfont object of the incore font
    DestroyDynamicDevFont(&devfont_unifont_160_50);
```

For incore images, you can use the basic functions (`LoadBitmapFromMem`
and `UnloadBitmap`) to load and destroy the BITMAP object. Or you can
use the MiniGUI resource manager to manage the objects by using the
reference count mechanism.

By using the MiniGUI resource manager, you can use the original
file name to load a resource from incore resource. If there is
an incore resource for the specific file name, the resource manager
will load it from the incore resource, otherwise it will try to
load if from the file. On the other hand, the resource manager
will maintain a reference count for every loaded resource,
and really release the object only if the reference count reached 0.
In this way, you can avoid some bugs about object life cycle.

The sample uses the resource manager to maintain the incore images:

```cpp
#include "png_pics.inc"

static INNER_RES incore_pngs [] = {
    { 0, _png__mguxdemo_1_data,  sizeof(_png__mguxdemo_1_data),
            "res/mguxdemo-1.png" },
    { 0, _png__mguxdemo_2_data,  sizeof(_png__mguxdemo_2_data),
            "res/mguxdemo-2.png" },
    { 0, _png__mguxdemo_3_data,  sizeof(_png__mguxdemo_3_data),
            "res/mguxdemo-3.png" },
    { 0, _png__mguxdemo_4_data,  sizeof(_png__mguxdemo_4_data),
            "res/mguxdemo-4.png" },
    { 0, _png__mguxdemo_5_data,  sizeof(_png__mguxdemo_5_data),
            "res/mguxdemo-5.png" },
    { 0, _png__mguxdemo_6_data,  sizeof(_png__mguxdemo_6_data),
            "res/mguxdemo-6.png" },
    { 0, _png__mguxdemo_7_data,  sizeof(_png__mguxdemo_7_data),
            "res/mguxdemo-7.png" },
    { 0, _png__mguxdemo_8_data,  sizeof(_png__mguxdemo_8_data),
            "res/mguxdemo-8.png" },
    { 0, _png__mguxdemo_9_data,  sizeof(_png__mguxdemo_9_data),
            "res/mguxdemo-9.png" },
    { 0, _png__mguxdemo_10_data, sizeof(_png__mguxdemo_10_data),
            "res/mguxdemo-10.png" },
    { 0, _png__mguxdemo_11_data, sizeof(_png__mguxdemo_11_data),
            "res/mguxdemo-11.png" },
    { 0, _png__mguxdemo_12_data, sizeof(_png__mguxdemo_12_data),
            "res/mguxdemo-12.png" },
    { 0, _png__mguxdemo_13_data, sizeof(_png__mguxdemo_13_data),
            "res/mguxdemo-13.png" },
};

...

    // add the incore resource to MiniGUI resource manager
    for (i = 0; i < TABLESIZE(incore_pngs); i++) {
        incore_pngs[i].key = Str2Key(incore_pngs[i].additional);
        incore_pngs[i].additional = "png";
    }

    if (AddInnerRes(incore_pngs, TABLESIZE(incore_pngs), FALSE)
            != RES_RET_OK) {
        _ERR_PRINTF("Failed to add incore PNG files.\n");
        exit (1);
    }

...

    // load BITMAP object by using the file name
    bmp = LoadBitmapFromRes(hdc, "res/mguxdemo-11.png");
    if (bmp == NULL) {
        _ERR_PRINTF("Failed to loaded png picture: %s\n", png_file_name);
        return;
    }

    // use the BITMAP object
    ...


    // Release resource
    ReleaseRes(Str2Key("res/mguxdemo-11.png"));

...

    // release the resource eventually
    for (i = 0; i < TABLESIZE(incore_pngs); i++) {
        ReleaseRes(incore_pngs[i].key);
    }

```

## Restrictions

Note that, currently, MiniGUI does not support incore TrueType fonts.
