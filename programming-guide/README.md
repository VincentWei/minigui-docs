# Programming Guide of MiniGUI V3.2

MiniGUI is a windowing system and a graphics user interface for embedded systems and/or smart IoT devices. It aims to provide a fast, stable, and cross-platform Graphics User Interface (GUI) support system, which is especially fit for embedded Linux and popular real-time operating systems.

This document introduces the concepts and the main APIs to program MiniGUI v3.2 apps in detail.

For more information, please visit MiniGUI website:

http://www.minigui.com

## Copying

Copyright (C) 2003 \~ 2019, Beijing FMSoft Technologies Co., Ltd.
All rights reserved.

*No matter you obtain all or part of the literal or image materials of this guide in any way, no matter they are common printed matters or electronic files, Beijing FMSoft Technologies Co., Ltd. only grants you the right to read. Format conversion, re-release, spreading and reproduction of all or part of its content or using the literals and images for commercial purpose without written permission are regarded as infringement acts and may cause serious civil or criminal punishment.*

- [Preface](MiniGUIProgGuidePreface.md)
- Part I Foundation of MiniGUI Programming
   - [Beginning MiniGUI Programming](MiniGUIProgGuidePart1Chapter01.md)
   - [Window and Message](MiniGUIProgGuidePart1Chapter02.md)
   - [Foundation of Dialog Box Programming](MiniGUIProgGuidePart1Chapter03.md)
   - [Foundation of Control Programming](MiniGUIProgGuidePart1Chapter04.md)
   - [Advanced Programming of Control](MiniGUIProgGuidePart1Chapter05.md)
   - [Menu](MiniGUIProgGuidePart1Chapter06.md)
   - [Scrollbar](MiniGUIProgGuidePart1Chapter07.md)
   - [Keyboard and Mouse](MiniGUIProgGuidePart1Chapter08.md)
   - [Icon, Cursor, and Caret](MiniGUIProgGuidePart1Chapter09.md)
   - [Look-and-feel and UI effects](MiniGUIProgGuidePart1Chapter10.md)
   - [Other Programming Topics](MiniGUIProgGuidePart1Chapter11.md)
   - [Using mGUtils](MiniGUIProgGuidePart1Chapter12.md)
- Part II Using mGNCS
   - [Brief Introduction to mGNCS](MiniGUIProgGuidePart2Chapter01.md)
   - [Getting Started](MiniGUIProgGuidePart2Chapter02.md)
   - [Renderer and Resources Management](MiniGUIProgGuidePart2Chapter03.md)
   - [Foundation Class](MiniGUIProgGuidePart2Chapter04.md)
   - [Static Box Series Control Class ](MiniGUIProgGuidePart2Chapter05.md)
   - [Button Series Control Class](MiniGUIProgGuidePart2Chapter06.md)
   - [Panel and Its Derived Class](MiniGUIProgGuidePart2Chapter07.md)
   - [Container and Its Derived Class](MiniGUIProgGuidePart2Chapter08.md)
   - [Slider Series Control Class](MiniGUIProgGuidePart2Chapter09.md)
   - [Spinner Series Control Class](MiniGUIProgGuidePart2Chapter10.md)
   - [Progress Bar Control Class](MiniGUIProgGuidePart2Chapter11.md)
   - [Property Sheet Control Class](MiniGUIProgGuidePart2Chapter12.md)
   - [Edit Box Series Control Class](MiniGUIProgGuidePart2Chapter13.md)
   - [Animation Control Class](MiniGUIProgGuidePart2Chapter14.md)
   - [Other Advanced Control Class](MiniGUIProgGuidePart2Chapter15.md)
   - [Invisible Control Class](MiniGUIProgGuidePart2Chapter16.md)
   - [Other Class](MiniGUIProgGuidePart2Chapter17.md)
- Part III MiniGUI Graphics Programming
   - [Graphics Device Interfaces](MiniGUIProgGuidePart3Chapter01.md)
   - [Handling and Rendering of Text](MiniGUIProgGuidePart3Chapter02.md)
   - [Advanced GDI Functions](MiniGUIProgGuidePart3Chapter03.md)
   - [Using mGPlus for Vector Graphics](MiniGUIProgGuidePart3Chapter04.md)
- Part IV Visual Effects and Animations
   - [Using mGEff for Visual Effects and Animations](MiniGUIProgGuidePart4Chapter01.md)
   - [Using mGNCS4Touch](MiniGUIProgGuidePart4Chapter02.md)
   - [Using OpenGL ES and/or OpenVG with MiniGUI](MiniGUIProgGuidePart4Chapter03.md)
- Part V MiniGUI Advanced Programming
   - [Inter-Process Communication and Asynchronous Event Process](MiniGUIProgGuidePart5Chapter01.md)
   - [Developing Customized MiniGUI-Processes Server Program](MiniGUIProgGuidePart5Chapter02.md)
   - [GAL and IAL Engines](MiniGUIProgGuidePart5Chapter03.md)
   - [Universal Startup API for RTOSes](MiniGUIProgGuidePart5Chapter04.md)
- Part VI Using MiniGUI Inherent Controls
   - [Static Control](MiniGUIProgGuidePart6Chapter01.md)
   - [Button Control](MiniGUIProgGuidePart6Chapter02.md)
   - [List Box Control](MiniGUIProgGuidePart6Chapter03.md)
   - [Edit Box Control](MiniGUIProgGuidePart6Chapter04.md)
   - [Combo Box Control](MiniGUIProgGuidePart6Chapter05.md)
   - [Menu Button Control](MiniGUIProgGuidePart6Chapter06.md)
   - [Progress Bar Control](MiniGUIProgGuidePart6Chapter07.md)
   - [Track Bar Control](MiniGUIProgGuidePart6Chapter08.md)
   - [Toolbar Control](MiniGUIProgGuidePart6Chapter09.md)
   - [Property Sheet Control](MiniGUIProgGuidePart6Chapter10.md)
   - [Scroll Window Control](MiniGUIProgGuidePart6Chapter11.md)
   - [Scroll View Control](MiniGUIProgGuidePart6Chapter12.md)
   - [Tree View Control](MiniGUIProgGuidePart6Chapter13.md)
   - [List View Control](MiniGUIProgGuidePart6Chapter14.md)
   - [Month Calendar Control](MiniGUIProgGuidePart6Chapter15.md)
   - [Spin Box Control](MiniGUIProgGuidePart6Chapter16.md)
   - [Cool Bar Control](MiniGUIProgGuidePart6Chapter17.md)
   - [Animation Control](MiniGUIProgGuidePart6Chapter18.md)
   - [GridView Control](MiniGUIProgGuidePart6Chapter19.md)
   - [IconView Control](MiniGUIProgGuidePart6Chapter20.md)
   - [Independent Scrollbar Control](MiniGUIProgGuidePart6Chapter21.md)
- Appendix Specifications for MiniGUI Developers
   - [Code Style and Project Specification](MiniGUIProgGuideAppendixA.md)
   - [Specification for the Picture Resources Used by mGNCS Skin Renderer](MiniGUIProgGuideAppendixB.md)
   - [Specification for the mGNCS-compliant Widget Components](MiniGUIProgGuideAppendixD.md)
