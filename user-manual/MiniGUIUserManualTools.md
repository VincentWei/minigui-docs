# Tools

- [Font Converter](#font-converter)
- [Incore Resource Tools](#incore-resource-tools)
- [miniStudio](#ministudio)

In this chapter, we introduce some tools commonly used.

## Font Tools

In package `mg-tools` (<https://github.com/VincentWei/mg-tools>), we
provide some font converters. You can use them to convert
TrueType fonts to UPF fonts or QPF fonts:

- `ttf2upf` converts a TrueType font to a UPF font with a specific size.
- `ttf2qpf` converts a TrueType font to a QPF font with a specific size.

Note that both tools use FreeType 1 to parse and render glyphs in
a TrueType font. So you need to install FreeType 1 library first.

Also note that you should check the license of TrueType fonts you
want to convert for the rights to use the converted UPF/QPF fonts
in commercial products.

In `font-tools/` directory of the `mg-tools` package, there are some 
tools. You can use them to convert a bitmap font to a C source
file, which can be used as an incore resource file to compile into
MiniGUI Core or your MiniGUI app.

- `vbf2c` converts a VBF font file into a C source file.
- `upf2c` converts a UPF font file into a C source file.

For a RBF font, you use `bin2c` in `tools/` directory to convert
it to a C source file. Note that a RBF font does not include format
information, so the C source file just defines a `unsigned char` array.

There are also other font tools in this directory:

- `bdf2vbf` converts a BDF font file into VBF font file.
- `qpf2upf` converts a QPF font file into UPF font file.
- `upfmerge` merges two UPF fonts into a one UPF font file.

## Incore Resource Tools

We provide a tool which converts a MiniGUI runtime configuration
file into a C source file. It is the `mgcfg-trans` tool in `mgcfg-trans/`
directory.

You can use this tool to convert a `MiniGUI.cfg` file or the runtime
configuration files of MiniGUI components (mGNCS and mGNCS4Touch) to
C source files.

The `mg-inner-res-trans` tool in `inner-res-trans/` directory can convert
images, fonts, icons used by MiniGUI into C source files in batch.
For the usage of this tool, you can refer to the README file in that directory.

## miniStudio

miniStudio is an Eclipse-based integrated development environment (IDE) for MiniGUI.
It provides a WYSIWYG UI designer for developers, and can generate and maintain
MiniGUI apps easily. You can use miniStudio to edit code, compile, run, and debug
your MiniGUI apps.

FMSoft now releases miniStudio under GPLv3. Basically, you can download, install,
and use it for free. You can also modify it under terms and conditions of GPLv3
for your own needs. You can find the public repositories of miniStudio at:

<https://github.com/FMSoftCN/ministudo-guibuilder>

and

<https://github.com/FMSoftCN/ministudio-eclipse-plugin>

---

[&lt;&lt; Runtime Configuration](MiniGUIUserManualRuntimeConfiguration.md) |
[Table of Contents](README.md) |
[Feature List &gt;&gt;](MiniGUIUserManualFeatureList.md)

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
