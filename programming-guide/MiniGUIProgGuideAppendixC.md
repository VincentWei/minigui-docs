# Public Structures and Definitions of mGNCS

## Alignment Values

Horizontal alignment enumeration values:

```cpp
enum enumNCSAlign {
    NCS_ALIGN_LEFT = 0,
    NCS_ALIGN_RIGHT,
    NCS_ALIGN_CENTER,
};
```

Vertical alignment enumeration values:

```cpp
enum enumNCSVAlign {
    NCS_VALIGN_TOP = 0,
    NCS_VALIGN_BOTTOM,
    NCS_VALIGN_CENTER,
};
```

## Image Drawing Modes

```cpp
enum enumNCSImageDrawMode {
    NCS_DM_NORMAL = 0,
    NCS_DM_SCALED,
    NCS_DM_TILED,
};

```

- `NCS_DM_NORMAL`  
Draw in normal mode without stretching and tiling. Under default condition, display
the image in the center (horizontal and vertical direction) Certain controls
such as Image can be changed through the alignment setting of control itself
- `NCS_DM_SCALED`  
Stretch image to fit to the filling region.
- `NCS_DM_TILED`  
When the image size is smaller than the filling region, tile the image to fill
the whole region.

_TBC_

----

[&lt;&lt; Specification for the Image Resources Used by mGNCS Skin Renderer](MiniGUIProgGuideAppendixB.md) |
[Table of Contents](README.md) |
[Specification for the mGNCS-compliant Widget Components &gt;&gt;](MiniGUIProgGuideAppendixD.md)

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

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building MiniGUI]: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]: /user-manual/MiniGUIUserManualCompiletimeConfiguration.md
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md

[MiniGUI Overview]: /MiniGUI-Overview.md
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI Supplementary Documents]: /supplementary-docs/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
