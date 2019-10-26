# Show Text in Complex or Mixed Scripts

_Lay out, shape, and render text in complex or mixed scripts._

Table of Contents

- [Overview](#overview)
- [APIs for Text Processing](#apis-for-text-processing)
  * [Changes of Character and Glyph APIs](#changes-of-character-and-glyph-apis)
  * [New APIs Conforming to Unicode 12.0](#new-apis-conforming-to-unicode-120)
  * [Processing Text in Standard Scripts](#processing-text-in-standard-scripts)
  * [Processing Text in Complex Scripts](#processing-text-in-complex-scripts)
- [Internals](#internals)
- [Restrictions](#restrictions)

## Overview

As described in [Using Enhanced Font Interfaces](Using-Enhanced-Font-Interfaces),
in order to support complex or mixed scripts, we tuned and enhanced
MiniGUI's font interfaces in version 4.0.0.

But this is only a small part of the whole story. To show a text paragraph in
complex/mixed scripts, we must implement complete APIs which conform
to Unicode standards and specifications, including Unicode
Bidirectional Algorithm (UAX#9), Unicode Line Breaking Algorithm
(UAX#14), Unicode Normalization Forms (UAX#15), Unicode Script Property
(UAX#24), Unicode Text Segmentation (UAX#29), Unicode Vertical
Text Layout (UAX#50), and so on.

On the basis of full support for Unicode, we provide APIs for laying out,
shaping, and rendering the text in complex or mixed scripts. This document
describes how to use these APIs.

Before we continue, let's clarify a few terms and concepts first.

A `script` means a set of letters of one human language, for example, Latin,
Han, Arabic, Hangul, and so on.

The `writing system` means the specific writing convention of a
language/script. For example, we write letters in Latin from left to right
horizontally then from top to bottom vertically, while we write traditional
Chinese words from top to bottom vertically then from right to left
horizontally.

The common languages, such as English and modern Chinese, are
`standard scripts`. In these scripts, there is a one-to-one relationship
between an encoded character (e.g. 0x4E2D in UTF-8) and the glyph (中)
that represents it. And we write the characters in standard scripts
often from left to right horizontally then from top to bottom vertically.

A `glyph` is a set of data which represents a specific character in a
visual or printable form. In computer, a glyph may be a bitmap or a
vector path data.

Generally, one `font` contains a lot of glyphs in bitmap or vector path data
for the characters in a specific language or script or a few similar
languages or scripts. For example, today, most fonts for East Asia markets
contain almost all glyphs for Chinese (both traditional and simplified),
Japanese, and Korea characters.

Systems and applications that handle the standard scripts do not need to
make a distinction between character processing and glyph processing.
In working with text in a standard script, it is most often convenient to
think only in terms of character processing, or simply text processing:
that is, the sequential rendering of glyphs representing character codes
as input in logical order.

The term `complex script` refers to any writing system that requires
some degree of character reordering and/or glyph processing to display,
print or edit. In other words, scripts for which Unicode logical order
and nominal glyph rendering of codepoints do not result in acceptable text.
Such scripts, examples of which are Arabic and the numerous Indic scripts
descended from the Brahmi writing system, are generally identifiable by
their morphographic characteristics: the changing of the shape or position
of glyphs as determined by their relationship to each other. It should be
noted that such processing is not optional, but is essential to correctly
rendering text in these scripts. Additional glyph processing to render
appropriately sophisticated typography may be desirable beyond the minimum
required to make the text readable.

The situation becomes more complicated when we process text in
`mixed scripts`. That is, the text contains characters from different
scripts, for example, Latin, Arabic, and Han.

## APIs for Text Processing

### Changes of Character and Glyph APIs

In early versions, we did not significantly distinguish
characters and glyphs. This will lead to some confusion when processing
text in complex script. Therefore, we introduce a new type called `Achar32`,
which is the character's index value under a certain charset/encoding.
While the new type `Glyph32` is the index value of a glyph in a font.

In order to reflect the correct character and glyph concepts,
the following functions are removed:

  * GetGlyphType, use GetACharType instead.
  * GetGlyphShape, use GetShapedAChar instead.
  * GetGlyphBIDIType, use GetACharBidiType.

The names of the following functions are changed:

  * BIDIGetTextLogicalGlyphs -> BIDIGetTextLogicalAChars
  * BIDIGetTextVisualGlyphs -> BIDIGetTextVisualAChars
  * BIDILogAChars2VisGlyphs -> BIDILogAChars2VisAChars
  * BIDILogAChars2VisGlyphsEx -> BIDILogAChars2VisACharsEx

But the following functions are deprecated, you should use
the new Unicode version instead:

  * BIDIGetTextLogicalAChars
  * BIDIGetTextVisualAChars
  * BIDILogAChars2VisAChars
  * BIDILogAChars2VisACharsEx
  * BIDIGetTextRangesLog2Vis
  * BIDIGetLogicalEmbedLevelsEx

The following functions are deprecated:

  * GetGlyphBitmap, use GetGlyphInfo instead.

The fields `height` and `descent` have been removed from GLYPHINFO structure.
You should get the font metrics information by calling function `GetFontMetrics()` 
if you want to get the height and descent data of one font.

The basic glyph type and break type have been removed from GLYPHINFO
structure. You should use `GetACharType()` instead.

### New APIs Conforming to Unicode 12.0

- New types:
  1. `Uchar32`: the Unicode code point value of a Unicode character.
  1. `Achar32`: the abstract character index value under a certain
      charset/encoding. Under Unicode charset or encodings, the
      abstract character index value will be identical to the Unicode
      code point, i.e., Achar32 is equivalent to Uchar32 under this
      situation.
  1. `Glyph32`: the glyph index value in a device font. Note that
      a Glyph32 value is always bound to a specific logfont object.

- New functions to determine the Unicode character properties:
  1. `UCharGetCategory` for getting the general category of
      a Unicode character.
  1. `UCharGetBreakType` for getting the breaking type of
      a Unicode character.
  1. `UStrGetBreaks` for getting the breaking types of
      a Unicode string.
  1. `UCharGetBidiType` for getting the bidi type of
      a Unicode character.
  1. `UStrGetBidiTypes` for getting the bidi types of a Unicode
      character string.
  1. `UCharGetBracketType` for getting the bracketed character of a
      Uchar32 character.
  1. `UStrGetBracketTypes` for getting the bracketed characters of a
      Uchar32 string.
  1. `UCharGetMirror` for getting the mirrored character of a Uchar32
      character.
  1. `UCharGetJoiningType` for getting the joining type of a Uchar32
      character.
  1. `UStrGetJoiningTypes` for getting the joining types of a Uchar32
      string.
  1. `UBidiGetParagraphDir` for getting the base paragraph direction
      of a single paragraph.
  1. `UBidiGetParagraphEmbeddingLevels` for getting the bidi embedding
      levels of a paragraph.
  1. `UBidiReorderLine`, `UBidiShapeMirroring`, `UBidiJoinArabic`,
      ` UBidiShapeArabic`, and `UBidiShape` for doing bidi-aware
      mirroring, joining, and shaping.
  1. `UCharGetScriptType` for getting the script type of a Uchar32
      character.

MiniGUI also provides some utilities/helpers for Unicode character
conversion, such as from lower case to upper case, single width to
full width. Please see MiniGUI API reference document for detailed
description.

### Processing Text in Standard Scripts

If you can determine the text to process is in standard scripts, you
can still to use MiniGUI GDI functions (`TextOut`, `DrawText` and so on)
to show the text. For more information, please refer to:

<http://www.minigui.com/doc-api-ref-minigui-sa-4.0.0/html/group__text__output__fns.html>

### Process Text in Complex Scripts

Before dealing with the bidirectional algorithm and the glyph shaping,
we first need to divide the text into paragraphs and get the relevant
properties of the characters, such as whether there is a breaking
opportunity before or after each character.

Moreover, all of the above processing needs to be done with the Unicode
character set.

Therefore, you call `GetUCharsUntilParagraphBoundary()` function to convert
a multi-byte string to a Unicode string under the specified white space
rule. For example, you can convert a general C string in `UTF-8` or
`GB18030` charset to a `Uchar32` string by calling this function.

```cpp
LOGFONT* lf;
int left_len_text;

char* text = "中华人民共和国万岁！\n中国共产党万岁！";

if (!(lf = CreateLogFontForMChar2UChar("utf-8"))) {
    _ERR_PRINTF("%s: failed to create logfont for utf-8 charset\n",
            __FUNCTION__);
    exit(1);
}

left_len_text = strlen(text);
while (left_len_text > 0) {
    Uchar32* ucs = NULL;
    int consumed, n;

    consumed = GetUCharsUntilParagraphBoundary(lf, text, left_len_text,
            WSR_NOWRAP, &ucs, &n);
    if (consumed > 0) {

        // got a paragraph and go on.
        ...

        // when we are done.
        free (ucs);
        ucs = NULL;
    }

    text += consumed;
    left_len_text -= consumed;
}

DestroyLogFont(lf);
```

In the code above, we call `CreateLogFontForMChar2UChar()` function to create
a dummy logfont object only for converting C-string in UTF-8 to Uchar32 string.
The logfont object created by `CreateLogFontForMChar2UChar()` will expense
a minimal memory. But note that if you use the logfont object returned by this
function to show a text, you will see nothing.

Obviously, the original text has two paragraphs. So we use a `while` loop
to deal with a paragraph in one loop.

Next, you should call `UStrGetBreaks()` to get the breaking opportunities of
each characters in the paragraph. This information is very important to the
layout algorithm.

If the text is in a standard script, like Latin or Chinese, you can call
function `GetGlyphsExtentFromUChars()` to lay out the paragraph to a line.
This function returns a glyph string which can fit in a line with the
specified maximal extent and rendering flags. After this, you call
`DrawGlyphStringEx()` function to draw the glyph string to the
specific position of a DC.

If there are characters left to lay out, you can call this function again,
until there is no character left.

For a complete sample, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/drawglyphstringex.c>

If the text is in complex and/or mixed scripts, like Arabic, Thai,
and Indic, you should create a TEXTRUNS object first by calling
`CreateTextRuns()` function, then initialize the shaping engine for
laying out the text.

For the usage sample of TEXTRUNS object, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/createtextruns.c>

MiniGUI provides two types of shaping engine. One is the basic
shaping engine. The corresponding function is `InitBasicShapingEngine()`.
The other is called complex shaping engine, which is based on HarfBuzz.
The corresponding function is `InitComplexShapingEngine()`. The latter
one can give you a better shaping result.

For the sample of the basic shaping engine, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/basicshapingengine.c>

Note that, to use the complex shaping engine, you need to compile MiniGUI
with the option `--enable-complexscripts`, and HarfBuzz should be installed
in your system. Also note that, you should use OpenType fonts with the
complex shaping engine.

For the sample of the complex shaping engine, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/complexshapingengine.c>

After this, you should call `CreateLayout()` to create a LAYOUT object
for laying out the text, then call `LayoutNextLine()` to lay out the lines
one by one.

You can render the laid out lines by calling `DrawLayoutLine()` function.

Finally, you call `DestroyLayout()` and `DestroyTextRuns()` to destroy
the layout object and text runs object.

Before rendering the glyphs laid out, you can also call `GetLayoutLineRect()`
to get the line rectangle, or call `CalcLayoutBoundingRect()` to get
the bounding rectangle of one paragraph.

For the sample for layout object, please refer to:

<https://github.com/VincentWei/mg-tests/blob/master/4.0/createlayout.c>

For detailed API description related to complex/mixed scripts,
please refer to:

<http://www.minigui.com/doc-api-ref-minigui-sa-4.0.0/html/group__complex__scripts.html>

Note that, the white space rule, character transformation rule, word breaking rule,
line breaking policy, and layout flags used by the new APIs conform
to the specifications of [CSS Text Module Level 3]
and [CSS Writing Modes Level 3].

## Internals

These new APIs provide a very flexible implementation for your apps
to process complex scripts. The implementation was derived from
LGPL'd Pango, but we optimized and simplified the original implementation
in the following respects:

* We split the layout process into two stages. We get the text runs
  (Pango items) in the first stage, and the text runs will keep as
  constants for subsequent different layouts. In the second stage,
  we create a layout object for a set of specific layout parameters,
  and generate the lines one by one for the caller. This is useful
  for an app like browser, it can reuse the text runs if the output
  width or height changed, and it is no need to re-generate the text
  runs because of the size change of the output rectangle.

* We use MiniGUI's fontname for the font attributes of text, and leave
  the font selection and the glyph generating to MiniGUI's logfont
  module. In this way, we simplify the layout process greatly.

* We always use Uchar32 string for the whole layout process. So the
  code and the structures are clearer than the original implementation.

* We provide two shaping engines for rendering the text. One is a
  basic shaping engine and other is the complex shaping engine based
  on HarfBuzz. The former can be used for simple applications.

## Restrictions

The current implementation of `CreateLayout` does not provide support
for the following layout flags:

- `GRF_HANGING_PUNC_FORCE_END`
- `GRF_HANGING_PUNC_ALLOW_END`
- `GRF_HANGING_PUNC_OPEN`
- `GRF_HANGING_PUNC_CLOSE`
- `GRF_SPACES_KEEP`
- `GRF_SPACES_REMOVE_START`
- `GRF_SPACES_REMOVE_END`
- `GRF_SPACES_HANGE_END`

When you use the basic shaping engine, only `GRF_TEXT_ORIENTATION_UPRIGHT`
flag is supported, and the basic shaping engine can not support scripts
which need to re-position the glyphs, such as Indic, Tibetan. For this
purpose, you must use the complex shaping engine with OpenType fonts.

[CSS Text Module Level 3]: https://www.w3.org/TR/css-text-3/
[CSS Writing Modes Level 3]: https://www.w3.org/TR/css-writing-modes-3/
