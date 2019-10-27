# Using Enhanced Font Interfaces

_Understand and use enhanced font intefaces of MiniGUI 4.0._

Table of Contents

- [Overview](#overview)
- [Enhancements of Font Name](#enhancements-of-font-name)
  * [Devfont name](#devfont-name)
  * [Logfont name](#logfont-name)
  * [Font style](#font-style)
- [API Enhancements](#api-enhancements)
- [Examples](#examples)

## Overview

In order to support complex or mixed scripts, we tuned and enhanced
MiniGUI's font interfaces in version 4.0.0.

Before we continue, we need to clarify a few terms and concepts:

- `devfont`: a device font object. It is the underlying object
   containing the glyphs of all or some characters in specific
   language or script.
- `logfont`: a logical font object. It is the real object used by
   MiniGUI app to render paragraphs, words, or characters.

Generally, a MiniGUI app creates one or more logfonts by specifying
the family, style, size, and charset/encoding, and calls GDI functions
to lay out, shape, and render the text.

When creating a logfont object, MiniGUI retrieves the devfonts which
matched the family, style, size, and character/encoding for the
requested logfont object in the devfonts base, which is loaded in
the starting stage of MiniGUI.

However, one logfont object does not always correspond to a
devfont object, but rather to multiple devfont objects.

For example, when we need to show a text like below:

```
“对暴徒仁慈就是对良民的残忍”
    -- Anonym
```

It is well known that, a font is often designed for a particular
language/script or a few similar languages/scripts.
So MiniGUI may retrieve the glyphs for the characters in the first line
(they are all in Chinese) in a font file named `宋体.ttf`, while in another
font file named `Arial.ttf` for the characters in the second line (they
are all in English).

Therefore, a logfont object actually corresponds to a collection of
devfont objects, which match the logfont's family, style, size, and
charset/encoding.

Before version 4.0.0, a logfont object can be represented by one or
two devfont objects. Therefore, MiniGUI can easily handle standard
languages/scripts, like Chinese, Japanese, English (Latin).

However, when we want to handle a text in the complex and mixed scripts
like Arabic and Indic, the old logfont/devfont facility does not work.

Therefore, we tuned and enhanced the font interfaces in version 4.0.0.
But don't worry, the tuned or enhanced interfaces keep backward
compatibility.

## Enhancements of Font Name

### Devfont name

We usually use a string to specify the family name,
style, size, and charsets of a devfont object:

```
ttf-Arial-rrncnn-0-0-ISO8859-1,UTF-8
```

It means that the devfont is a TrueType vector font, the family name
of the devfont is `Arial`, the style is represented by a string `rrncnn`,
the size can be any value (vector fonts can be arbitrarily scaled to
meet different size requirements.), and the charsets/encodings of the
devfont are `ISO8859-1` and `UTF-8`.

Since 4.0.0, you can specify the aliases for the family name of a devfont:

```
<fonttype>-<family[,aliase]*>-<styles>-<width>-<height>-<charset[,charset]*>
```

For example:

    ttf-Arial,Sans Serif-rrncnn-0-0-ISO8859-1,UTF-8
    ttf-courier,monospace,serif-rrncnn-0-0-ISO8859-1,UTF-8

Note that the length of one devfont name can not exceed 255 bytes.

### Logfont name

When we create a logfont object, we generally call function `CreateLogFontByName`.
The logfont name uses the similar format as devfont name:

```
<fonttype>-<family-name[,family-nameN]*>-<styles>-<width|orientation>-<height>-charset
```

Since version 4.0.0, you can specify up to 7 family names for a
logfont name, for example:

```
ttf-Courier,宋体,Naskh,SansSerif-rrncns-U-16-UTF-8
```

In this way, you can specify a logfont to use multiple devfonts
to render a complex text.

Moreover, the previous width field of a logfont name is used for
the glyph orientation:

- `U`: Glyphs stand upright (default).
- `S`: Glyphs are rotated 90 degrees clockwise (sideways).
- `D`: Glyphs are upside-down.
- `L`: Glyphs are rotated 90 degrees counter-clockwise (sideways left).

### Font style

As you've seen in above font names, we use a style string (six ASCII characters)
to define the style of a font in font name.

In version 4.0.0, we tuned the meaning of each character in the style string.

The format of the style string changed from

```
<weight><slant><flipping><other><underline><struckout>

```

to

```
<weight><slant><flipping><other><decoration><rendering>
```

The differences are as follow:

- The new `<rendering>` style added.
- `<underline>` and `<struckout>` are conbined into `<decoration>`
  in order to keep the style string still 6-character long.
- For `<weight>`, we redefined the weight styles follow OpenType specification.

The following words describe the detailed information about style changes:

- Introduced new rendering style:
  1. `FS_RENDER_MONO`: represented by ASCII character `n`.
  1. `FS_RENDER_GREY`: represented by ASCII character `g`.
  1. `FS_RENDER_SUBPIXEL`: represented by ASCII character `s`.
* The following old styles are deprecated:
  1. `FS_WEIGHT_BOOK`; use `FS_RENDER_GREY` instead.
  1. `FS_WEIGHT_SUBPIXEL`; use `FS_RENDER_SUBPIXEL` instead.
* Introduced New weight style:
  1. `FONT_WEIGHT_THIN`: Thin; represented by ASCII character `t`.
  1. `FONT_WEIGHT_EXTRA_LIGHT`: Extra light (Ultra Light); represented by ASCII character `e`.
  1. `FONT_WEIGHT_LIGHT`: Light; represented by ASCII character `l`.
  1. `FONT_WEIGHT_NORMAL`: Normal; represented by ASCII character `n`.
  1. `FONT_WEIGHT_REGULAR`: Regular; represented by ASCII character `r`.
  1. `FONT_WEIGHT_MEDIUM`: Medium; represented by ASCII character `m`.
  1. `FONT_WEIGHT_DEMIBOLD`: Demi Bold (Semi Bold); represented by ASCII character `d`.
  1. `FONT_WEIGHT_BOLD`: Bold; represented by ASCII character `b`.
  1. `FONT_WEIGHT_EXTRA_BOLD`: Extra Bold (Ultra Bold); represented by ASCII character `x`.
  1. `FONT_WEIGHT_BLACK`: Black (Heavy); represented by ASCII character `c`.
* Introduced new decoration styles and replace `FONT_UNDERLINE_LINE` and `FONT_STRUCKOUT_LINE` with them:
  1. `FONT_DECORATE_NONE`: without any decoration; represented by ASCII character `n`.
  1. `FONT_DECORATE_UNDERLINE`: underscored glyphs represented by ASCII character `u`.
  1. `FONT_DECORATE_STRUCKOUT`: overstruck glyphs represented by ASCII character `s`.
  1. `FONT_DECORATE_US`: Both `FONT_DECORATE_UNDERLINE` and `FONT_DECORATE_STRUCKOUT`; represented by ASCII character `U`.
  1. `FONT_DECORATE_REVERSE`: Glyphs have their foreground and background reversed (`r`); Reserved for future use.
  1. `FONT_DECORATE_OUTLINE`: Outline (hollow) glyphs (`o`); Reserved for future use.
* The following style are deprecated:
  1. `FONT_OTHER_LCDPORTRAIT`
  1. `FONT_OTHER_LCDPORTRAITKERN`

As an example, if you want to use the rendering method SUPIXEL for a TTF font,
please define the logfont name in the following way:

```
ttf-Courier-rrncns-*-16-UTF-8
```

## API Enhancements

For a new app, you should use the new function `CreateLogFontEx` to
create a logfont, and specify the weight and rendering method of the glyph:

```cpp
m_btnFont = CreateLogFontEx ("ttf", "helvetica", "UTF-8",
        FONT_WEIGHT_REGULAR,
        FONT_SLANT_ROMAN,
        FONT_FLIP_NONE,
        FONT_OTHER_NONE,
        FONT_DECORATE_NONE, FONT_RENDER_SUBPIXEL,
        SETTING_OK_BTN_TEXT_H, 0);
```

For backward compatibility, you can still use `CreateLogFont` to create a new
logfont. However, `FS_WEIGHT_BOOK` will be treated as `FS_WEIGHT_REGULAR` and
`FS_RENDER_GREY`, while `FS_WEIGHT_SUBPIXEL` will be treated as
`FS_WEIGHT_REGULAR` and `FS_RENDER_SUBPIXEL`.

You can still use `CreateLogFontByName` to create a new logfont. But you should
make sure to define the new logfont name in new format.

We also introduced the following new functions in version 4.0.0:

- `CreateLogFontIndirectEx`: to create a new logfont object by using the properties
   of an existing logfont object, but with a new rotation argument. This function is
   a supplementary of `CreateLogFontIndirect`.
- `CreateLogFontForMChar2UChar`: to create a logfont in order to convert a multi-byte
   character string to `Uchar32` string.
- `LoadDevFontFromIncoreData`: to load a devfont from a file. This function is
   a supplementary of `LoadDevFontFromFile`.

## Examples

For complete usage examples of new font API, you can refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/createlogfontex.c>

