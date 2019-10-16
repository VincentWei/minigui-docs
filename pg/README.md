# Programming Guide of MiniGUI V3.2

MiniGUI is a windowing system and a graphics user interface for embedded systems and/or smart IoT devices. It aims to provide a fast, stable, and cross-platform Graphics User Interface (GUI) support system, which is especially fit for embedded Linux and popular real-time operating systems.

This document introduces the concepts and the main APIs to program MiniGUI v3.2 apps in detail.

For more information, please visit MiniGUI website:

http://www.minigui.com

## Copying

Copyright (C) 2003~2018, Beijing FMSoft Technologies Co., Ltd.
All rights reserved.

*No matter you obtain all or part of the literal or image materials of this guide in any way, no matter they are common printed matters or electronic files, Beijing FMSoft Technologies Co., Ltd. only grants you the right to read. Format conversion, re-release, spreading and reproduction of all or part of its content or using the literals and images for commercial purpose without written permission are regarded as infringement acts and may cause serious civil or criminal punishment.*

*Note that this document is currently under development.*

- [Preface](MiniGUIProgGuidePreface.md)

- Part I Foundation of MiniGUI Programming
   - [Beginning MiniGUI Programming](MiniGUIProgGuidePart1Chapter01)
   - [Window and Message](MiniGUIProgGuidePart1Chapter02)
   - [Foundation of Dialog Box Programming](MiniGUIProgGuidePart1Chapter03)
   - [Foundation of Control Programming](MiniGUIProgGuidePart1Chapter04)
   - [Advanced Programming of Control](MiniGUIProgGuidePart1Chapter05)
   - [Menu](MiniGUIProgGuidePart1Chapter06)
   - [Scrollbar](MiniGUIProgGuidePart1Chapter07)
   - [Keyboard and Mouse](MiniGUIProgGuidePart1Chapter08)
   - [Icon, Cursor, and Caret](MiniGUIProgGuidePart1Chapter09)
   - [Look-and-feel and UI effects](MiniGUIProgGuidePart1Chapter10)
   - [Other Programming Topics](MiniGUIProgGuidePart1Chapter11)
   - [Using mGUtils](MiniGUIProgGuidePart1Chapter12)

- Part II Using mGNCS
   - [Brief Introduction to mGNCS](MiniGUIProgGuidePart2Chapter01)
   - [Getting Started](MiniGUIProgGuidePart2Chapter02)
   - [Renderer and Resources Management](MiniGUIProgGuidePart2Chapter03)
   - [Foundation Class](MiniGUIProgGuidePart2Chapter04)
   - [Static Box Series Control Class ](MiniGUIProgGuidePart2Chapter05)
   - [Button Series Control Class](MiniGUIProgGuidePart2Chapter06)
   - [Panel and Its Derived Class](MiniGUIProgGuidePart2Chapter07)
   - [Container and Its Derived Class](MiniGUIProgGuidePart2Chapter08)
   - [Slider Series Control Class](MiniGUIProgGuidePart2Chapter09)
   - [Spinner Series Control Class](MiniGUIProgGuidePart2Chapter10)
   - [Progress Bar Control Class](MiniGUIProgGuidePart2Chapter11)
   - [Property Sheet Control Class](MiniGUIProgGuidePart2Chapter12)
   - [Edit Box Series Control Class](MiniGUIProgGuidePart2Chapter13)
   - [Animation Control Class](MiniGUIProgGuidePart2Chapter14)
   - [Other Advanced Control Class](MiniGUIProgGuidePart2Chapter15)
   - [Invisible Control Class](MiniGUIProgGuidePart2Chapter16)
   - [Other Class](MiniGUIProgGuidePart2Chapter17)

- Part III MiniGUI Graphics Programming
   - [Graphics Device Interfaces](MiniGUIProgGuidePart3Chapter01)
   - [Handling and Rendering of Text](MiniGUIProgGuidePart3Chapter02)
   - [Advanced GDI Functions](MiniGUIProgGuidePart3Chapter03)
   - [Using mGPlus for Vector Graphics](MiniGUIProgGuidePart3Chapter04)

- Part IV Visual Effects and Animations
   - [Using mGEff for Visual Effects and Animations](MiniGUIProgGuidePart4Chapter01)
   - [Using mGNCS4Touch](MiniGUIProgGuidePart4Chapter02)
   - [Using OpenGL ES and/or OpenVG with MiniGUI](MiniGUIProgGuidePart4Chapter03)

- Part V MiniGUI Advanced Programming
   - [Inter-Process Communication and Asynchronous Event Process](MiniGUIProgGuidePart5Chapter01)
   - [Developing Customized MiniGUI-Processes Server Program](MiniGUIProgGuidePart5Chapter02)
   - [GAL and IAL Engines](MiniGUIProgGuidePart5Chapter03)
   - [Universal Startup API for RTOSes](MiniGUIProgGuidePart5Chapter04)

- Part VI Using MiniGUI Inherent Controls
   - [Static Control](MiniGUIProgGuidePart6Chapter01)
   - [Button Control](MiniGUIProgGuidePart6Chapter02)
   - [List Box Control](MiniGUIProgGuidePart6Chapter03)
   - [Edit Box Control](MiniGUIProgGuidePart6Chapter04)
   - [Combo Box Control](MiniGUIProgGuidePart6Chapter05)
   - [Menu Button Control](MiniGUIProgGuidePart6Chapter06)
   - [Progress Bar Control](MiniGUIProgGuidePart6Chapter07)
   - [Track Bar Control](MiniGUIProgGuidePart6Chapter08)
   - [Toolbar Control](MiniGUIProgGuidePart6Chapter09)
   - [Property Sheet Control](MiniGUIProgGuidePart6Chapter10)
   - [Scroll Window Control](MiniGUIProgGuidePart6Chapter11)
   - [Scroll View Control](MiniGUIProgGuidePart6Chapter12)
   - [Tree View Control](MiniGUIProgGuidePart6Chapter13)
   - [List View Control](MiniGUIProgGuidePart6Chapter14)
   - [Month Calendar Control](MiniGUIProgGuidePart6Chapter15)
   - [Spin Box Control](MiniGUIProgGuidePart6Chapter16)
   - [Cool Bar Control](MiniGUIProgGuidePart6Chapter17)
   - [Animation Control](MiniGUIProgGuidePart6Chapter18)
   - [GridView Control](MiniGUIProgGuidePart6Chapter19)
   - [IconView Control](MiniGUIProgGuidePart6Chapter20)
   - [Independent Scrollbar Control](MiniGUIProgGuidePart6Chapter21)

- Appendix Specifications for MiniGUI Developers
   - [Code Style and Project Specification](MiniGUIProgGuideAppendixA)
   - [Specification for the Picture Resources Used by mGNCS Skin Renderer](MiniGUIProgGuideAppendixB)
   - [Specification for the mGNCS-compliant Widget Components](MiniGUIProgGuideAppendixD)
