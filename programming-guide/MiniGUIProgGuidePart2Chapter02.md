# Chapter 1 of Part 2 Quick Start

## helloworld Program of mGNCS

mGNCS packages the main window of MiniGUI and brings it into the control 
system, therefore, the whole programming will become very simple and easy to
learn. Please look at the helloworld program source codes based on mGNCS:

<p align=center>List p2c1-1 helloworld.c</p>

```
```

The program creates a 300x200 main window on the screen and displays “Hello,
world!”: 

<p align=center>

![alt](figures/helloworld.png)

Figure p1c1-1 Output of helloworld program
</p>

### Head File

Besides the four head files of MiniGUI (<minigui/common.h>, 
<minigui/minigui.h>, <minigui/gdi.h> and <minigui/window.h>), helloworld.c 
shall contain its specific file:

- <mGNCS/mGNCS.h>: mGNCS head file

Therefore, normally, head file of a mGNCS program is:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/helloworld.c.txt" pattern="^.*?// `START_OF_INCS(.*?)//`
`END_OF_INCS`. 
```
```

Afterwards, a main window can be directly created through calling
`ncsCreateMainWindow` function, which has many parameters, but a lot of default
parameters can be used for creating default window:

%CODE{cpp}%
`mWidget*` mymain = `ncsCreateMainWindow` (
`NCSCTRL_MAINWND`, // Class name of the main window, class name macro of NCS
control starts with `NCSCTRL_`
"Hello World!", // Title text of the appointed main window
`WS_CAPTION` | `WS_BORDER` | `WS_VISIBLE`, // Style of the appointed window,
create a visible window with title bar and border
`WS_EX_NONE`, // Extension style of appointed main window, use 0 or 
`WS_EX_NONE` to show that there is no extension style
1, // Identifier value of the appointed main window, any integer value >0
0, 0, 300, 200, // Location and size of the appointed main window, x, y, width
and height by sequence
`HWND_DESKTOP`, // Host of the appointed main window, which usually is
`HWND_DESKTOP` 
0, 0, // Icon and menu bar sentence handle of the main window, empty by default
`NULL,` // Initial property information of the appointed main window, empty by
default 
`NULL,` // Initial renderer information of the appointed main window, empty by
default 
`mymain_handlers,` // Event handler of the appointed main window, see the next
section 
0); // Additional data of the appointed main window, 0 here

```
```

Therefore, we define the two functions, and establish mapping array of the 
event and event handler:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/helloworld.c.txt" pattern="^.*?(// `START_OF_HANDLERS`.
`END_OF_HANDLERS).*"}%` 
```
```

### Create Modal Main Window

We know that the main window is divided into modal and non-modal. The above
example program establishes a standard non-modal main window. If we hope to
create modal main window, we only need to use `doModal` to replace the existing
message circulation, as shown below:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/helloworld_domodal.c.txt" pattern="^.*?(//
`START_OF_MINIGUIMAIN`. `END_OF_MINIGUIMAIN).*"}%`
```cplusplus
```cplusplus
%INCLUDE{"%ATTACHURL%/wnd_template.c.txt"}%
```
```

It needs to be noted that `NCS_WND_TEMPLATE` also contains a pointer member
pointing to child control template structure array, thus multi-level nested
template can be formed.

### Set Window Property

In the example, we define the initial property values of the progress bar
control through `NCS_PROP_ENTRY` structure array, which include:
- Maximum value of the progress bar
- Minimum value of the progress bar.
- Step value of the progress bar
- Initial location of the progress bar.


Concrete codes are as below:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/wnd_template.c.txt" pattern="^.*?//
`START_OF_PROPERTIES(.*?)//` `END_OF_PROPERTIES`.
```
```

If MiniGUI intrinsic control set is used, to implement this function, it is a
must to call `SendMessage?` in `MSG_INITDIALOG` message of the dialog box. 
While in the new control set, it is only necessary to set a `NCS_PROP_ENTRY`
array, and the function can be implemented automatically. It is not only for
reducing code amount and simplifying programming, more importantly, it provides
a uniform interface. Users can store the initial information into the external
files in a unified way through this interface. Resources management module of
NCS can finish similar functions, and miniStudio utilizes this convenience.

### Dynamically Set the Property

Property can be dynamically set in the program running process. It can be
implemented through `setProperty` (inherited and implemented by its child 
class) of `mComponentClass` (this is visible component, which is basic class of
control and invisible component). Similarly, there is `getProperty` method,
which is used to get value of given property. Prototypes of the two methods are
as below:

%CODE{cpp}%
`BOOL` (*setProperty) (clss *self, int id, `DWORD` value);
`DWORD` (*getProperty) (clss *self, int id);
```
```

## Use Renderer

Renderer is a big feature of the new control set. Its main functions are:
1. On the foundation of not changing the realization of internal logic of the
control, customize the look and feel of the control
1. Renderers change along with the variety changes of the controls, and adding
and deleting a control will not generate effect on other controls, in this
respect, they are different from the renderers of the old control set

As users of control, developers don’t need to implement a complete renderer, 
but only need to use the due renderer. The above example uses the method 
similar to window template to define information of the renderers used by a
control. 

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/wnd_template.c.txt" pattern="^.*?//
`START_OF_RDRINFO(.*?)//` `END_OF_RDRINFO`.
```
```

Among them,
- `glb_rdr` refers to global renderer, mainly used for the drawing style of non
client areas. MiniGUI is responsible for drawing these areas.
- `ctrl_rdr` refers to control renderer, mainly used for the drawing of control
itself. 


`NCS_RDR_INFO` can be given in the template, thus control using given renderer
can be created directly.

## Event Listening and Connection

mGNCS provides a signal and slot mechanism similar to `QT,` which is able to
link the event of an object to any object.

### Basic Principle

Event listening link mechanism of mGNCS provides a mode to decouple the event
sender and event observer. It corresponds to the relation between the sender 
and the receiver through global data sheet. As shown in the figure below:

<p align=center>

![alt](figures/event-listener.png)

<br>Figure p1c1-3 Event Listening and Connection
</p>

When an object is deleted:
- All the connections listening to the object will be deleted
- Connections that the object listens to will also be deleted

### Main Interface Functions

Interfaces adding event listener are given below:

%CODE{cpp}%
/**
* \typedef typedef `BOOL` (*NCS_CB_ONOBJEVENT) (mObject* self, `mObject`
*sender, 
int `event_id,` `DWORD` param);
* \brief The callback of connection
*
* \note For widgets, only support notification
*
* \param self The listener pointer
* \param sender The sender of event
* \param `event_id` the id of event
* \param param the param of event
*
* \return `TRUE` - continue dispatch the event; `FALSE` - stop the event.
*/
typedef `BOOL` (*NCS_CB_ONOBJEVENT)(mObject* self, `mObject` *sender,
int `event_id,` `DWORD` param);

#define `NCS_CB_ONPIECEEVENT` `NCS_CB_ONOBJEVENT`

/**
* \fn `BOOL` `ncsAddEventListener(mObject` *sender, \
* `mObject*` listener, \
* `NCS_CB_ONOBJEVENT` `event_proc,` \
* int `event_id);`
* \brief connect sender object to listener object
*
* \param sender The sender of event
* \param listener The listener of event
* \param `event_proc` The processing callback of event
* \param `event_id` The id of event
*
* \return `TRUE` - Sucessed, `FALSE` - Failed
*
* \sa `ncsAddEventListener,` `ncsAddEventListeners,` `NCS_CB_ONOBJEVENT`
*/
`BOOL` `ncsAddEventListener(mObject` *sender,
`mObject*` listener,
`NCS_CB_ONOBJEVENT` `event_proc,`
int `event_id);`

/**
* `BOOL` `ncsAddEventListeners(mObject` *sender,\
* `mObject*` listener,\
* `NCS_CB_ONOBJEVENT` `event_proc,\`
* int* `event_ids);`
* \brief connect a group of events from sender to listener
*
* \param sender The sender of events
* \param listener The listener of events
* \param `event_proc` The processing callback of events
* \param `event_ids` The id array of events, end by 0
*
* \return `TRUE` - Sucessed, `FALSE` - Failed
*
* \sa `ncsAddEventListener,` `ncsAddEventListeners,` `NCS_CB_ONOBJEVENT`
*/
`BOOL` `ncsAddEventListeners(mObject` *sender,
`mObject*` listener,
`NCS_CB_ONOBJEVENT` `event_proc,`
int* `event_ids);`
```
```

Among them,
- Delete a listener or event sender. Because as long as either listener or
sender does not exist, the whole connection does not have the sense of 
existence and will be deleted.
- The two functions are automatically called by `mOBject,` and normally active
calling is not needed

Interfaces exciting an event connection are given below:

%CODE{cpp}%
/**
* \fn void `ncsRaiseEvent` (mObject *sender, int `event_id,` `DWORD` param);
* \biref Raise an event to listeners
*
* \note It will call the callback of \ref `NCS_CB_ONOBJEVENT`
* added by \ref `ncsAddEventListeners,` or \ref `ncsAddEventListener`
*
* \param sender event sender
* \param `event_id` the id of event
* \param param the event param
*
* \sa `NCS_CB_ONOBJEVENT`, `ncsAddEventListener,` `ncsAddEventListeners`
*/
void `ncsRaiseEvent(mObject` *sender, int `event_id,` `DWORD` param);
```
```

When the window is initialized, the two event listeners are connected to the
clicking events of the above two controls:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/event_listener.c.txt" pattern="^.*?//
`START_OF_HANDLERS(.*?)//` `END_OF_HANDLERS`.
```
```

Finish the above data binding, and the program only does the setting work as
shown below when the dialog box is created:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/data_binding.c.txt" pattern="^.*?//
`START_OF_BINDING(.*?)//` `END_OF_BINDING`.
```
```

To implement the above data source function, the program completes work in the
following three aspects:

First step, define data source:

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/data_source.c.txt" pattern="^.*?//
`START_OF_DEFINEDS(.*?)//` `END_OF_DEFINEDS`.
```
```

The above codes define the two kinds of data into “listview/header” and
“listview/content”. When it is necessary to quote the two kinds of data, just
use the names given here.

Third step, use data source

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/data_source.c.txt" pattern="^.*?// 
`START_OF_SETDATA(.*?)//` `END_OF_SETDATA`.

----

[&lt;&lt; ](MiniGUIProgGuidePart.md) |
[Table of Contents](README.md) |
[ &gt;&gt;](MiniGUIProgGuidePart.md)

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
