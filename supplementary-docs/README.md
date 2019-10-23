# MiniGUI Supplementary Documents

Good software requires good documentation, especially system software like
MiniGUI. However, maintaining documentation for a complex software system
is a lot more difficult than maintaining source code.

It sounds like it is always better if there are documents than no documents,
but if the documents are outdated or contain errors, the damage will be
even greater. So there is a saying: "Source code is the best document."
Therefore, we don't particularly want to spend a lot of time writing and
maintaining documentation.

On the other hand, facing some new features, the developers, especially
the beginners, still need some basic documents or guides to quickly
understand how they work and how to use them.

In the past many years, we have accumulated a large number of MiniGUI
documents, including user manuals, programming guides, and so on.
With the releases of new MiniGUI versions (like MiniGUI 3.2 and
MiniGUI 4.0), it doesn't make much sense to update or rewrite these
documents throughout just for some new features.

Therefore, we plan to write some new documents or guides on this
GitHub Wiki system, by supplementing the existing documents instead
of updating the existing ones. These documents will not be very detailed,
but will point out the main points and related sample programs to
help you quickly grasp the relevant features.

We call these documents "MiniGUI Supplementary Documents".

## Features for Version 4.0 or later

* [Release Notes for MiniGUI 4.0](Release-Notes-for-MiniGUI-4.0.md) -
    Enhancements and changes of MiniGUI 4.0.x.
* [Writing DRI Engine Driver for Your GPU](Writing-DRI-Engine-Driver-for-Your-GPU.md) -
    Writing a DRI engine driver to exploit the hardware accelerated functions of your GPU.
* [Supporting and Using Extra Input Messages](Supporting-and-Using-Extra-Input-Messages.md) -
    Supporting and using extra input messages.
* [Using Enhanced Font Interfaces](Using-Enhanced-Font-Interfaces.md) -
    Understand and use enhanced font intefaces of MiniGUI 4.0.
* [Showing Text in Complex/Mixed Scripts](Showing-Text-in-Complex-or-Mixed-Scripts.md) -
    How to lay out, shape, and render text in complex or mixed scripts.

## Features for Version 3.2 or later

* [Release Notes for MiniGUI 3.2](Release-Notes-for-MiniGUI-3.2.md) -
    Enhancements and changes of MiniGUI 3.2.x.
* [Using CommLCD NEWGAL Engine and Comm IAL Engine](Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md) -
    How to define external stubs to implement your CommLCD engine and Comm
    IAL engine outside MiniGUI Core.
* [Using Images and Fonts on System without File System](Using-Images-and-Fonts-on-System-without-File-System.md) -
    How to build source for incore images and fonts, and load them for
    your MiniGUI apps.
* [Using SyncUpdateDC to Reduce Screen Flicker](Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md) -
    How to use MiniGUI's synchronous update mechanism to reduce screen flicker.
* [Writing MiniGUI Apps for 64-bit Platforms](Writing-MiniGUI-Apps-for-64-bit-Platforms.md) -
    Describe the things you need to be aware of when developing MiniGUI apps for 64-bit platforms.

