---+!!17 Developing Customized MiniGUI-Processes Server Program
`mginit` is the server program of MiniGUI-Processes. This program prepares
shared resource for client programs and manages windows created by clients. We
explain how to write a customized MiniGUI-Processes server program according to
the project requirement in this chapter. We first use program `mginit` of
`mg-samples` as an example to analyze the basic constitution of `mginit`
program. 

## `mginit` in `mg-samples`

`mginit` in `mg-samples` is relatively simple, which is mainly responsible for
following tasks:
- Initializing itself as the server of MiniGUI-Processes;
- Showing two dialog boxes displaying copyright information;
- Reading mginit.rc configuration file and creating a task bar;
- Starting up the default startup program specified by mginit.rc file;
- Maintaining information of MiniGUI-Processes layers and switching between
layers in the taskbar window procedure.

Now we analyze the implementation of `mginit` in mg-samples.

### Initializing Itself as the Server of MiniGUI-Processes

The following code is located in function `MiniGUIMain`:
```cpp
int MiniGUIMain (int args, const char* arg[])
{
    int pid_desktop;
    struct sigaction siga;
    MSG msg;
    
    OnNewDelClient = on_new_del_client;
    OnChangeLayer = on_change_layer;
    
    if (!ServerStartup (0, 0, 0)) {
        fprintf (stderr, "Can not start the server of MiniGUI-Processes: mginit.\n");
        return 1;
    }

    if (!InitMiniGUIExt ()) {
        fprintf (stderr, "Can not init mgext library.\n");
        return 1;
    }   
    
    ...
```
First, this function initializes variables `OnNewDelClient` and 
`OnChangeLayer`, which are the global variables owned by the server program.
After this, the function calls `ServerStartup` to start the server function of
mginit. `ServerStartup` function will create listening socket, prepare to 
accept the connection requests from clients. So far the server initialization
has finished. Let’s analyze the above process in details.

<b>1. Listen events coming from clients and layers</b>

The global variables `OnNewDelClient` and `OnChangeLayer` are only available 
for MiniGUI-Processes server program. They are two function pointer variables.
When a client connects to `mginit` or drops the socket connection with mginit,
and if the variable of `OnNewDelClient` has been set, MiniGUI will call the
function pointed to by this variable. In `minigui/minigui.h`, the declaration 
of this function prototype is as follows:

```cpp
typedef void (* ON_NEW_DEL_CLIENT) (int op, int cli);
```
The first argument indicates the operation that will be processed. When the
parameter gets `LCO_NEW_CLIENT`, it represents that there is new client being
connecting to the server; if parameter is `LCO_DEL_CLIENT`, it means that a
client is dropping the connection. The second argument cli is the client
identifier; it is an integer.

When the layer of MiniGUI-Processes changes, for example, a new client joins to
a certain layer, and if the variable of `OnChangeLayer` has been set, MiniGUI
will call the function pointed to by this variable. In `minigui/minigui.h`, the
declaration of the prototype of this function is as follows:

```cpp
typedef void (* ON_CHANGE_LAYER) (int op, MG_Layer* layer, MG_Client* client);
```

The first argument represents the event type:
- `LCO_NEW_LAYER`: A new layer has been created;
- `LCO_DEL_LAYER`: A layer has been deleted;
- `LCO_JOIN_CLIENT`: A client joined to a certain layer;
- `LCO_REMOVE_CLIENT`: A certain client is deleted from the layer it lies;
- `LCO_TOPMOST_CHANGED`: The top-most layer changes, that is, the switch of
layer occurred;

The second argument is the pointer to the relevant layer. The third argument is
the pointer to the relevant client.

The global variable `OnZNodeOperation` only available for MiniGUI-Processes
server program since MiniGUI V2.0.4/V1.6.10. It is also function pointer
variable. When the znode changes in MiniGUI-Processes and the variable of
`OnZNodeOperation` has been set, MiniGUI will call the function pointed to by
this variable. In `minigui/minigui.h`, the declaration of this function
prototype is as follows:
```cpp
typedef void (* ON_ZNODE_OPERATION) (int op, int cli, int idx_znode);
ON_ZNODE_OPERATION OnZNodeOperation;
```

The first argument represents the event type:
- `ZNOP_ALLOCATE`: The z-node has been created;
- `ZNOP_FREE`: The z-node has been destroyed;
- `ZNOP_MOVE2TOP`: The z-node has been moved to be the topmost one;
- `ZNOP_SHOW`: The z-node has been shown;
- `ZNOP_HIDE`: The z-node has been hidden;
- `ZNOP_MOVEWIN`: The z-node has been moved or its size has changed;
- `ZNOP_SETACTIVE`: The z-node has been set to be the active one;
- `ZNOP_ENABLEWINDOW`: The z-node is disabled or enabled;
- `ZNOP_STARTDRAG`: Start to drag the z-node;
- `ZNOP_CANCELDRAG`: Cancel to drag the z-node;
- `ZNOP_CHANGECAPTION`: The caption of the z-node has changed.

The second argument cli is the client identifier; it is an integer. The third
argument `idx_znode` is the znode index.

The global variables `OnLockClientReq`, `OnTrylockClientReq`, and
`OnUnlockClientReq` are available for MiniGUI-Processes client program. They 
are three function pointer variables. They can avoid thread deadlock problem in
the same process. In `minigui/minigui.h`, the declaration of this function
prototype is as follows:
```cpp
typedef int (* ON_LOCK_CLIENT_REQ) (void);
ON_LOCK_CLIENT_REQ  OnLockClientReq;

typedef int (* ON_TRYLOCK_CLIENT_REQ) (void);
ON_TRYLOCK_CLIENT_REQ  OnTrylockClientReq;

typedef int (* ON_TRYLOCK_CLIENT_REQ) (void);
ON_UNLOCK_CLIENT_REQ  OnUnlockClientReq;
```
Once having client identifier or layer pointer and client pointer, `mginit` can
easily access the internal data structure of MiniGUI library, and so can get
some system information. For doing this, MiniGUI defines the following global
variables: 
- `mgClients`: An `MG_Client` structure pointer. It points to an `MG_Client`
structure array including all clients’ information. You can use the client
identifier to access it.
- `mgTopmostLayer`: An `MG_Layer` structure pointer, pointing to the current
top-most layer.
- `mgLayers`: An `MG_Layer` structure pointer, pointing to the head of a
linked-list of all layers in the system.

`mginit` program can visit these data structure at any time to get the current
client and the current layer information. Regarding members of `MG_Client` and
`MG_Layer` structures can refer to MiniGUI `API` Reference.

`mginit` in `mg-samples` defines two functions to handle above events, and also
sets two global variables mentioned above.

The first function is `on_new_del_client,` which does not have material work,
but just simply prints the name of the client coming or dropping the socket
connection. 

The second function is `on_change_layer,` which mainly handles events
`LCO_NEW_LAYER`, `LCO_DEL_LAYER`, and `LCO_TOPMOST_CHANGED`. When system 
creates new layers, this function will create a new button in taskbar and 
assign the handle value of this button to `dwAddData` member of the current
layer; when system deletes a certain layer, the function destroys the button
corresponding the layer; when the top-most layer of system changes, the 
function calls `on_change_topmost` to adjust the state of these buttons
representing layers. The code of this function is as follows:
```cpp
static void on_change_layer (int op, MG_Layer* layer, MG_Client* client)
{
    static int nr_boxes = 0;
    static int box_width = _MAX_WIDTH_LAYER_BOX;
    int new_width;

    if (op > 0 && op <= LCO_ACTIVE_CHANGED)
        printf (change_layer_info [op], layer?layer->name:"NULL", 
                      client?client->name:"NULL");

    switch (op) {
    case LCO_NEW_LAYER:
        nr_boxes ++;
        if (box_width * nr_boxes > _WIDTH_BOXES) {
            new_width = _WIDTH_BOXES / nr_boxes;
            if (new_width < _MIN_WIDTH_LAYER_BOX) {
                new_width = _MIN_WIDTH_LAYER_BOX;
            }

            if (new_width = box_width) {
                adjust_boxes (new_width, layer);
                box_width = new_width;
            }
        }

        layer->dwAddData = (DWORD)CreateWindow (CTRL_BUTTON, layer->name,
                        WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_PUSHLIKE | BS_CENTER,
                        _ID_LAYER_BOX,
                        _LEFT_BOXES + box_width * (nr_boxes - 1), _MARGIN,
                        box_width, _HEIGHT_CTRL, hTaskBar, (DWORD)layer);
        break;

    case LCO_DEL_LAYER:
        DestroyWindow ((HWND)(layer->dwAddData));
        layer->dwAddData = 0;
        nr_boxes --; 
        if (box_width * nr_boxes < _WIDTH_BOXES) {
            if (nr_boxes = 0)
                new_width = _WIDTH_BOXES / nr_boxes;
            else
                new_width = _MAX_WIDTH_LAYER_BOX;

            if (new_width > _MAX_WIDTH_LAYER_BOX)
                new_width = _MAX_WIDTH_LAYER_BOX;

            adjust_boxes (new_width, layer);
            box_width = new_width;
        }
        break;

    case LCO_JOIN_CLIENT:
        break;
    case LCO_REMOVE_CLIENT:
        break;
    case LCO_TOPMOST_CHANGED:
        on_change_topmost (layer);
        break;
    default:
        printf ("Serious error: incorrect operations.\n");
    }
}
```

<b>2. `ServerStartup` function</b>

This function initializes the server, i.e. mginit. It creates the shared
resource, the listening socket, the default layer, and other internal objects.
Your costomized `mginit` program should call this function before calling any
other function. Note that the default layer created by the server called
“mginit" (NAME_DEF_LAYER). The prototype of this function is:
```cpp
BOOL GUIAPI ServerStartup (int nr_globals,
                int def_nr_topmosts, int def_nr_normals);
```

You can pass some arguments to this function to control the limits of the 
window management:
- `nr_globals` The number of the global z-order nodes. All z-order nodes 
created by `mginit` are global ones.
- `def_nr_topmosts` The maximal number of the topmost z-order nodes in the
default layer. It is also the default number of topmost z-order nodes of a new
layer. 
- `def_nr_normals` The maximal number of normal z-order nodes in the new layer.
It is also the default number of normal z-order nodes of a new layer.

<noscript>
### Displaying Copyright Information
Then, `mginit` calls two functions to respectively display the copyright
information of MiniGUI and `MDE`:
```cpp
AboutMiniGUI ();
    AboutMDE ();
```
</noscript>

### Creating Taskbar
As mentioned above, `mginit` uses taskbar and buttons on the taskbar to
represent the current layers of system. It also provides a simple user 
interface (see Figure 1):
- If the user clicks an icon on the taskbar, a certain application program will
be started.
- If the user clicks the buttons on the taskbar, it will switch the layer to be
the top-most layer.


<img src="%ATTACHURLPATH%/17.1.jpeg" alt="17.1.jpeg" `ALIGN="CENTER`" />

Figure 1 Taskbar created by `mginit` in `mg-samples`

This taskbar uses the cool bar control to create a toolbar used to startup
applications. It reads application configuration information from mginit.rc 
file and initializes the information, including name, description string, and
corresponding program icon of application.

Taskbar also creates a timer and a static control, which displays current time
and refreshs once per second.

As this code is not the proprietary of mginit, so we will not discuss it in
detail. 

### Startup the Default Program
mginit.rc file defines an initial application that needs to startup by default.
The following code startups this application program:
```cpp
pid_desktop = exec_app (app_info.autostart);

    if (pid_desktop == 0 || waitpid (pid_desktop, &status, WNOHANG) > 0) {
        fprintf (stderr, "Desktop already have terminated.\n");
        Usage ();
        return 1;
    }
```
Then, `mginit` catches the signal `SIGCHLD`, which helps to avoid the zombie
processes if the child exits while there is no process getting its exit state:
```cpp
siga.sa_handler = child_wait;
    siga.sa_flags  = 0;
    memset (&siga.sa_mask, 0, sizeof(sigset_t));
    sigaction (SIGCHLD, &siga, NULL);

```
The function `exec_app` used to startup client application program is very
simple. It calls vfork and execl system calls to startup a client:
```cpp
pid_t exec_app (int app)
{
    pid_t pid = 0;
    char buff [PATH_MAX + NAME_MAX + 1];

    if ((pid = vfork ()) > 0) {
        fprintf (stderr, "new child, pid: %d.\n", pid);
    }
    else if (pid == 0) {
        if (app_info.app_items [app].cdpath) {
            chdir (app_info.app_items [app].path);
        }
        strcpy (buff, app_info.app_items [app].path);
        strcat (buff, app_info.app_items [app].name);
        if (app_info.app_items [app].layer [0]) {
            execl (buff, app_info.app_items [app].name,
                        "-layer", app_info.app_items [app].layer, NULL);
        }
        else {
            execl (buff, app_info.app_items [app].name, NULL);
        }
        perror ("execl");
        _exit (1);
    }
    else {
        perror ("vfork");
    }

    return pid;
}
```

### Entering Message Loop
Now, `mginit` program enters message loop:
```cpp
while (GetMessage (&msg, hTaskBar)) {
        DispatchMessage (&msg);
    }
```
When the taskbar exits, the message loop will be terminated. Finally,
MiniGUI-Processes exits.

## A Simple `mginit` Program
`mginit` in `mg-samples` is not too complex. It illustrates a basic design
method of the MiniGUI-Processes server program. In this section, we will design
a simpler `mginit` program, which initializes itself as the server of
MiniGUI-Processes and startups helloworld program. This program also 
illustrates the use of the event hook. When the user presses the key F1, F2, 
F3, or F4, some other clients will be started up. If the user has not operated
for a long time, `mginit` will startup a screen saver program. When the user
closes all clients, `mginit` exits. List 1 lists the code of this `mginit`
program; you can refer to file mginit.c and file scrnsaver.c in the program
package mg-sample of this guide for the whole code.


List 1 The code of a simple `mginit` program
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

static BOOL quit = FALSE;

static void on_new_del_client (int op, int cli)
{       
    static int nr_clients = 0;

    if (op == LCO_NEW_CLIENT) {
        nr_clients ++;
    }   
    else if (op == LCO_DEL_CLIENT) {
        nr_clients --;
        if (nr_clients == 0) {
            printf ("There is no any client, I will quit.\n");
            quit = TRUE;
        }               
        else if (nr_clients < 0) {
            printf ("Serious error: nr_clients less than zero.\n");
        }
    }
    else
        printf ("Serious error: incorrect operations.\n");
}

static pid_t exec_app (const char* file_name, const char* app_name)
{
    pid_t pid = 0;

    if ((pid = vfork ()) > 0) {
        fprintf (stderr, "new child, pid: %d.\n", pid);
    }
    else if (pid == 0) {
        execl (file_name, app_name, NULL);
        perror ("execl");
        _exit (1);
    }
    else {
        perror ("vfork");
    }

    return pid;
}

static unsigned int old_tick_count;

static pid_t pid_scrnsaver = 0;

static int my_event_hook (PMSG msg)
{
    old_tick_count = GetTickCount ();

    if (pid_scrnsaver) {
        kill (pid_scrnsaver, SIGINT);
        ShowCursor (TRUE);
        pid_scrnsaver = 0;
    }

    if (msg->message == MSG_KEYDOWN) {
        switch (msg->wParam) {
            case SCANCODE_F1:
               exec_app ("./edit”, “edit");
               break;
            case SCANCODE_F2:
               exec_app ("./timeeditor", "timeeditor");
               break;
            case SCANCODE_F3:
               exec_app ("./propsheet", "propsheet");
               break;
            case SCANCODE_F4:
               exec_app ("./bmpbkgnd", "bmpbkgnd");
               break;
    return HOOK_GOON;
}
static void child_wait (int sig)
{
    int pid;
    int status;

    while ((pid = waitpid (-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED (status))
            printf ("--pid=%d--status=%x--rc=%d---\n", pid, status, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf ("--pid=%d--signal=%d--\n", pid, WTERMSIG (status));
    }
}

int MiniGUIMain (int args, const char* arg[])
{
    MSG msg;
    struct sigaction siga;

    siga.sa_handler = child_wait;
    siga.sa_flags  = 0;
    memset (&siga.sa_mask, 0, sizeof(sigset_t));
    sigaction (SIGCHLD, &siga, NULL);

    OnNewDelClient = on_new_del_client;

    if (!ServerStartup (0, 0, 0)) {
        fprintf (stderr, "Can not start the server of MiniGUI-Processes: mginit.\n");
        return 1;
    }
    

        SetServerEventHook (my_event_hook);

    if (args > 1) {
        if (exec_app (arg[1], arg[1]) == 0)
            return 3;
    }
    else {
        if (exec_app ("./helloworld", "helloworld") == 0)
            return 3;
    }

    old_tick_count = GetTickCount ();

    while (!quit && GetMessage (&msg, HWND_DESKTOP)) {
        if (pid_scrnsaver == 0 && GetTickCount () > old_tick_count + 1000) {
            ShowCursor (FALSE);
            pid_scrnsaver = exec_app ("./scrnsaver", "scrnsaver");
        }
        DispatchMessage (&msg);
    }

    return 0;
}
```
This program sets the `OnNewDelClient` event handling function of mginit. It
will set the global variable quit as `TRUE` when the event handling function
encounter `LCO_DEL_CLIENT`, so as to result in the stop of the message loop, 
and finally exits the server.
You can compile the program by using the following command:

```cpp
$ gcc –o mginit mginit.c –lminigui
```
As this `mginit` program need startup helloworld program when starting up, so,
we have to make sure that there is helloworld program in the current directory.
<noscript>
Certainly, we can also add this program into the sample program package in this
guide. As `mginit` program can only be compiled under MiniGUI-Processes
environment, we need to modify the file configure.in and the file Makefile.am 
of the project `mg-samples` in order to add `mginit` into `mg-samples` project.
First, we delete the notation of following line in file configure.in:
```cpp
AM_CONDITIONAL(MGRM_THREADS, test "x$threads_version" = "xyes")
AM_CONDITIONAL(MGRM_PROCESSES, test "x$procs_version" = "xyes")
AM_CONDITIONAL(MGRM_STANDALONE, test "x$standalone_version" = "xyes")
```
The lines mean that if the MiniGUI is configured as MiniGUI-Processes,
MiniGUI-Threads, or MiniGUI-Standalone, and then defines the macro
`MGRM_PROCESSES`, `MGRM_THREADS`, or `MGRM_STANDALONE` respectively. These
macros will be used in Makefile.am.

Then, we modify the file Makefile.am that is in directory src/:
```cpp
if MGRM_PROCESSES
noinst_PROGRAMS=helloworld mycontrol dialogbox input bmpbkgnd simplekey \
                scrollbar painter capture bitblt stretchblt loadbmp drawicon \
                createicon caretdemo cursordemo \
                scrnsaver mginit
else
noinst_PROGRAMS=helloworld mycontrol dialogbox input bmpbkgnd simplekey \
                scrollbar painter capture bitblt stretchblt loadbmp drawicon \
                createicon caretdemo cursordemo
endif

...

mginit_SOURCES=mginit.c
scrnsaver_SOURCES=scrnsaver.c
```
The statements above request that automake generates the makefile rules used to
create `mginit` and scrnsaver targets only if `MGRM_PROCESSES` defined. After
modifying these scripts, you should run the script ./autogen.sh to recreate
configure file, then run the script ./configure to create new makefiles for the
`mg-samples` project. If MiniGUI is configured as MiniGUI-Threads, the command
make will not compile `mginit` program and scrnsaver program.
</noscript>

## Functions Specific to Clients of MiniGUI-Processes
As you know, a client of MiniGUI-Processes should call `JoinLayer` to join
itself into a layer before calling other functions of MiniGUI. Besides
`JoinLayer`, a client can call other functions to get the information of 
layers, delete a layer or change the topmost layer.

Clients should call `JoinLayer` before calling any other MiniGUI functions. The
prototype of this function is as follows:
```cpp
GHANDLE GUIAPI JoinLayer (const char* layer_name,
                const char* client_name, 
                int max_nr_topmosts, int max_nr_normals);
```
If the layer to be joined does not exist, the server will try to create a new
one. If you passed a `NULL` pointer or a null string for `layer_name,` the
client will be tried to join to the default layer. If the client wants to 
create a new layer, you should specify the maximal number of topmost frame
objects (max_nr_topmosts) and the maximal number of normal frame objects
(max_nr_normals) in the new layer. Passing zero to `max_nr_topmosts` and
`max_nr_normals` will use the default values. Note that `ServerStartup`
specifies the default values.

You can get the information of a layer through the function `GetLayerInfo`. The
prototype of this function is as follows:
```cpp
GHANDLE GUIAPI GetLayerInfo (const char* layer_name,
                int* nr_clients, BOOL* is_topmost, int* cli_active);
```

The information of the layer will be returned through the pointer arguments if
the specific pointer is not `NULL`. The information are the number of clients 
in the layer, whether the layer is the topmost one, and the client identifier
whose window is the current active one respectively.

Clients can call `SetTopmostLayer` to set the topmost layer and call 
`DeleteLayer` to delete a layer. Detail information about these functions can 
be referred to MiniGUI `API` Reference.

## Other Functions and Interfaces Specific to `mginit`
Apart from `ServerStartup`, `OnNewDelClient`, and `mgClients`, 
MiniGUI-Processes also defines several interfaces for `mginit` program. These
interfaces are specific to the MiniGUI-Processes server programs. Detail
information about these interfaces can be referred to MiniGUI `API` Reference.
- `ServerSetTopmostLayer`: This function switches the specified layer to be the
topmost layer.
- `ServerCreateLayer`: This function creates a specified layer in the system.
- `ServerDeleteLayer`: This function deletes a specified layer from the system.
- `GetClientByPID`: This function returns the client identifier according to 
pid of a client.
- `SetTopmostClient`: This function sets the topmost layer by the specified
client identifier. It will bring the layer contains the client to be the 
topmost one.
- `SetServerEventHook`: This function sets a hook of bottom event in mginit.
When hook function return zero to MiniGUI, MiniGUI will continue the event
process, and send the event to the current active client; whereas stops the
process of the event.
- Send2Client: The server can use this function to send the specific message to
a certain client.
- Send2TopMostClients: The server can send a message to all clients in the
topmost layer.
- Send2ActiveWindow: The server can send a message to the active window in a
layer. 
- `ServerGetNextZNode：Get` the next z-node in the specified layer from the
server. 
- `ServerGetZNodeInfo：Get` the z-node information in the specified layer from
the server.
- `ServerDoZNodeOperation：Does` an operation on the z-node in the specified
layer from the server.


-- Main.XiaodongLi - 07 Nov 2009


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
