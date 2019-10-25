# Beginning MiniGUI Programming

We describe the basic concepts and foundation knowledge of MiniGUI programming with a simple MiniGUI program in this chapter.

## Basic Programming Concepts
### Event Driven Programming

MiniGUI is a graphics user interface support system, and general GUI programming concepts are all suitable for MiniGUI programming, such as window and event driven programming etc.

In a conventional GUI graphics system model, actions of keyboard or mouse generate events that are continuously checked by application. These events are generally sent to the focused window, and are transferred by application to procedures related to this window for handling. These window procedures are generally defined by application, or one of some standard procedures. Operating system, event-handling procedure of other windows, and application code all can generate events.

The window procedure for handling events generally identifies one "window class", and windows with the same window procedure are regarded as belonging to the same window class.

Concept of focus and cursor is used for managing the transfer of input devices and input events. Mouse cursor is a small bitmap drawn on the screen, which indicates the current mouse position. It is the responsibility of the windowing system to draw the bitmap in some non-subversive form, but the application can control which bitmap to draw and whether the cursor to be shown. The application can catch mouse cursor and get cursor event even if the cursor goes beyond the display region of the application window. Keyboard input has similar concept of input focus and caret. Only the window having input focus can get the keyboard event. Changing the window focus is completed by combination of special keys or by mouse cursor event. The window having input focus usually draws a keyboard caret. The existence, form, position, and control of the caret are all performed by window event handling procedures.

Application can require redrawing the whole or part of the window by calling some system functions, which are usually handled by window procedures.

### Three Runtime Modes of MiniGUI

MiniGUI can be configured and compiled into three versions, which are completely different in architecture - MiniGUI-Processes, MiniGUI-Threads, and MiniGUI-Standalone. We call these the different runtime modes.

- MiniGUI-Threads. Programs run in MiniGUI-Threads can create multiple windows in different threads, but all the windows are run in one process or address space. This runtime mode is greatly suitable for most of the conventional embedded operating systems, for example, uC/OS-II, eCos, VxWorks, pSOS etc. Certainly, MiniGUI can be run in the runtime mode of MiniGUI-Threads on Linux and uClinux.
- MiniGUI-Processes. In opposition to MiniGUI-Threads, a program running on MiniGUI-Processes is an independent process, which can also create multiple windows. MiniGUI-Processes are fit for full-featured UNIX-like operating systems, such as Linux.
- MiniGUI-Standalone. Under this runtime mode, MiniGUI can be run in independent process form, without support of multiple threads and multiple processes, this runtime mode is suitable for applications of single function. For example, in some embedded products using uClinux, thread library support is short of because of various reasons, at this time, MiniGUI-Standalone can be used to develop applications.

Compared to UNIX-like operating systems such as Linux, traditional embedded operating systems have some particularity. Say for example, operating systems such as uClinux, uC/OS-II, eCos, VxWorks and the like are generally run on the CPU without MMU (memory management unit, used to provide support of virtual memory), here there is usually not the concept of process but the concept of thread or task, thus, runtime environments of GUI system are quite different. Therefore, to be suitable for different operating systems environments, we can configure MiniGUI into the above three runtime modes.

Generally speaking, the runtime mode of MiniGUI-Standalone has the widest adaptability, and can support almost all the operating systems, even including operating systems similar to DOS; the adaptability of the runtime mode of MiniGUI-Threads takes second place, and can real-time embedded operating systems with support of multiple tasks, or normal operating systems with complete UNIX properties; the adaptability of runtime mode of MiniGUI-Processes is smaller, and it is only suitable for normal operating system with complete UNIX properties.

The early version of MiniGUI (namely MiniGUI-Threads) adopts the mechanisms of message post based on POSIX thread and window management, which provides maximum data share, but also causes weakness in MiniGUI system architecture. The whole system will be affected if one thread terminates due to illegal data accessing. To solve this problem and make MiniGUI more appropriate for application requirements of embedded system based-one Linux, we released MiniGUI-Lite mode from version 0.98. The MiniGUI-Lite do not use the thread mechanism and pthread library, thus MiniGUI is more stable and on embedded Linux. By using MiniGUI-Lite, we can run several client processes on the basis of efficient client/server architecture, and make use of superior features like address space protection. Thus, with MiniGUI-Lite runtime mode, the flexibility, stability, and scalability of embedded system based on MiniGUI will improve greatly. For example, we can run several MiniGUI client processes on MiniGUI-Lite, and if one process terminates abnormally, other processes will still run well. Moreover, on MiniGUI-Lite, it is convenient for us to integrate third-party applications. Actually, this is why many embedded device developers use Linux as their operating systems.

Although MiniGUI-Lite runtime mode provides support for multi-process, it cannot manage windows created by different processes at one time. Therefore, MiniGUI-Lite distinguishes windows in different processes by layers. This method fits for the most embedded devices with low-resolution screen, but brings some problems for application development.

MiniGUI V2.0.x solves this problem completely. A window created by a client of MiniGUI-Lite is not a global object, i.e., a client does not know the windows created by others. However, windows created by MiniGUI-Processes are all global objects, and windows created by MiniGUI-Processes can clip each other. Thus, MiniGUI-Processes is a successor of MiniGUI-Lite; It offers full-featured support for multi-process embedded operating systems, such as Linux.

We can run multiple MiniGUI applications simultaneously with the MiniGUI-Processes mode. First, we start up a server program called mginit, and then we can start up other MiniGUI applications as clients. Server is not affected and can continue to run if the client terminates due to some reason.

__Note__ In this guide, the demo programs assume that the MiniGUI-Processes version is configured and installed. Before running these demo applications, you should run the mginit program first, which can be a user-defined mginit program or an mginit program provided by mg-samples. We have coded carefully to ensure that each demo program can be compiled and run on MiniGUI-Processes, MiniGUI-Threads, or MiniGUI-Standalone.

Further more, MiniGUI provides APIs in Win32 style. Readers familiar with Win32 programming can grasp the basic methods and APIs quickly.

## A Simple MiniGUI Program

The quickest approach to understand the basic programming method of MiniGUI is to analyze structure of a simple program. List 1 shows a “Hello World” program of MiniGUI, which will be discussed in detail.

<center>List 1 helloworld.c</center>

```cpp
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

static LRESULT HelloWinProc (HWND hWnd, LINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message) {
        case MSG_PAINT:
            hdc = BeginPaint (hWnd);
            TextOut (hdc, 60, 60, "Hello world!");
            EndPaint (hWnd, hdc);
            return 0;

        case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
    }

    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
    JoinLayer (NAME_DEF_LAYER , "helloworld" , 0 , 0);
#endif

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "HelloWorld";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor (0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 240;
    CreateInfo.by = 180;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    hMainWnd = CreateMainWindow (&CreateInfo);

    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow (hMainWnd, SW_SHOWNORMAL);

    while (GetMessage (&Msg, hMainWnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);

    return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif
```

As shown in Figure 1, the program creates an application window with size of 320x240 pixels, and displays “Hello world!” at the center of the window client region.

<center>
<img align="CENTER" alt="2.1.jpeg" src="%ATTACHURLPATH%/2.1.jpeg" /><br />
Figure 1 The window created by helloworld program
</center>

### Header Files

The four header files included in the beginning of helloworld.c, namely minigui/common.h, minigui/minigui.h, minigui/gdi.h, and minigui/window.h, should be included for all MiniGUI applications.
- common.h: Includes definitions of macros and data types commonly used in MiniGUI.
- minigui.h: Includes definitions of global and general interface functions and some miscellaneous functions.
- gdi.h: Includes definitions of interfaces of MiniGUI graphics functions.
- window.h: Includes definitions of macros, data types, data structures, which are relative to the windows and declarations of function interfaces.

Another header file must be included for MiniGUI applications using predefined controls -- minigui/control.h:

- control.h: Includes interface definitions of all the built-in controls in minigui library.

Therefore, a MiniGUI program usually includes the following MiniGUI related header files in the beginning:

```cpp
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
```

### Entrance of the Program

The entrance of a C program is the main program, while the entrance of a MiniGUI program is MiniGUIMain, and the prototype of the program is as follows:

```cpp
int MiniGUIMain (int argc, const char* argv[]);
```

This function is a encapsulated Macro for main (entrypoint function) of ANSI C.So the entrance of each MiniGUI application (no matter server function mginit or client application) is the MiniGUIMain function. Arguments of argc and argv have the same meaning as that of the main function in C program, which are the number of command line arguments and the string array pointer to the arguments, respectively.

### Join a Layer in MiniGUI-Processes

```cpp
#ifdef _MGRM_PROCESSES
    JoinLayer (NAME_DEF_LAYER , "helloworld" , 0 , 0);
#endif
```

JoinLayer is a special function of MiniGUI-Processes, and is therefore included in the conditional compilation of _MGRM_PROCESSES. In the runtime mode MiniGUI-Processes, each MiniGUI client program must call this function to join a layer (or create a new layer) before calling other MiniGUI functions.

If the program is the server of MiniGUI-Processes, you should call ServerStartup instead:

```cpp
if (!ServerStartup (0 , 0 , 0)) {
    fprintf (stderr, "Can not start the server of MiniGUI-Processes: mginit.\n");
    return 1;
}
```

We will give detailed description on interfaces specific to MiniGUI-Processes in [Developing Customized MiniGUI-Processes Server Program](MiniGUIProgGuidePart5Chapter02.md).

__Note__ MiniGUI defines different macros for three runtime modes:
- MiniGUI-Threads: _MGRM_THREADS;
- MiniGUI-Processes: _MGRM_PROCESSES and _LITE_VERSION;
- MiniGUI-Standalone: _MGRM_STANDALONE, _LITE_VERSION, and _STAND_ALONE.

### Creating and Showing Main Window

```cpp
    hMainWnd = CreateMainWindow (&CreateInfo);
```

The initial user interface of each MiniGUI application is usually a main window; you can create a main window by calling CreateMainWindow function.  The argument of CreateMainWindow function is a pointer to MAINWINCREAT structure, which is CreatInfo in this example, and the return value is the handle to the created main window. MAINWINCREAT structure describes the properties of a main window, and you need to set its properties before using CreatInfo to create a main window.

```cpp
    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
```

The above statement sets the style of the main window, herein the window is set to be visible initially, and to have border and caption bar.

```cpp
    CreateInfo.dwExStyle = WS_EX_NONE;
```

The above statement sets the extension style of the main window, and the window has no extension style.

```cpp
    CreateInfo.spCaption = "HelloWorld";
```

This statement sets the caption of the main window to be "HelloWorld".

```cpp
    CreateInfo.hMenu = 0;
```

This statement sets the main menu of the main window, and the window has no main menu.

```cpp
    CreateInfo.hCursor = GetSystemCursor (0);
```

This statement sets the cursor of the main window, and the cursor for this window is the default system cursor.

```cpp
    CreateInfo.hIcon = 0;
```

This statement sets the icon of the main window, and the window has no icon.

```cpp
    CreateInfo.MainWindowProc = HelloWinProc;
```

This statement sets the window procedure function of the main window to be HelloWinProc, and all the messages sent to the window are handled by this function.

```cpp
   CreateInfo.lx = 0;
   CreateInfo.ty = 0;
   CreateInfo.rx = 320;
   CreateInfo.by = 240;
```

The above statements set the position and the size of the main window on the screen, and the upper-left corner and lower-right corner are located in (0, 0) and (320, 240), respectively.

```cpp
   CreateInfo.iBkColor = PIXEL_lightwhite;
```

This statement sets the background color of the main window to be white, and PIXEL_lightwhite is the pixel value predefined by MiniGUI.

```cpp
   CreateInfo.dwAddData = 0;
```

This statement sets the additional data of the main window, and the window has no dditional data.

```cpp
   CreateInfo.hHosting = HWND_DESKTOP;
```

This statement sets the hosting window of the main window to be the desktop window.

```cpp
   ShowWindow (hMainWnd, SW_SHOWNORMAL);
```

ShowWindow function needs to be called to show the created window on the screen after the main window is created. The first argument of ShowWindow is the handle of the window to be shown, and the second argument specifies the style of showing the window (show or hide). SW_SHOWNORMAL means showing the main window and setting it to be the top-most window.

### Entering Message Loop

The main window will be displayed on the screen when ShowWindow function is called. Like other GUI, it is time to go into the message loop. MiniGUI maintains a message queue for each MiniGUI program. After an event happens, MiniGUI transforms the event into a message, and put the message into the message queue of the target window. Then the task of the application is to execute the following message loop code to get the message from the message queue continuously and handle them.

```cpp
    while (GetMessage (&Msg, hMainWnd)) {
        TranslateMessage (&Msg);
        DispatchMessage (&Msg);
    }
```

The type of Msg variable is a MSG structure, which is defined in minigui/window.h as follows:

```cpp
typedef struct _MSG
{
    HWND          hwnd;
    LINT          message;
    WPARAM        wParam;
    LPARAM        lParam;
    DWORD         time;
#ifndef _LITE_VERSION
    void*         pAdd;
#endif
} MSG;
typedef MSG* PMSG;
```

GetMessage function gets a message from the message queue of the application.

```cpp
     GetMessage ( &Msg, hMainWnd);
```

The second argument of this function is the handle to the main window, and the first argument is the pointer to a MSG structure. GetMessage function fills the fields of the MSG structure with the message gotten from the message queue, which includes:
- hwnd: The handle of the window to which hwnd message is sent. The value is the same with hMainWnd in the helloworld.c program.
- message: Message identifier. This is an integer for identifying a message. Each messages has a corresponding predefined identification, these identification are defined in minigui/window.h and with MSG_ prefix.
- wParam: The first 32-bit message parameter, the meaning and value of which is different for different message.
- lParam: The second 32-bit message parameter, the meaning and value of which depends on the message.
- time: The time (tick count) when the message is put into the message queue.

If only the message gotten from the message queue is not MSG_QUIT, GetMessage will return a non-zero value, and the message loop will be continued. MSG_QUIT message makes the GetMessage return zero, and results in the termination of the message loop.

```cpp
      TranslateMessage (&Msg);
```

TranslateMessage function translates a keystroke message to a MSG_CHAR message, and then sends the message to the window procedure function.

```cpp
      DispatchMessage (&Msg);
```

DispatchMessage function will finally send the message to the window procedure of the target window, and let it handle the message. In this example, the window procedure is HelloWinProc. That is to say, MiniGUI calls the window procedure function (callback function) of the main window in the DispatchMessage function to handle the messages sent to this main window. After handling the messages, the window procedure function of the application would return to DispatchMessage function, while DispatchMessage function will return to the application code in the end, and the application begins a new message loop by calling the next GetMessage function.

### Window Procedure Function

Window procedure function is the main body of MiniGUI program. The most work of an application happens in the window procedure function actually, because the main task of GUI program is to receive and handle various messages received by the window.

The window procedure is the function named as HelloWinProc in helloworld.c program. Programs may name the window procedure function arbitrarily. CreateMainWindow function creates the main window according to the window procedure specified in MAINWINCREATE structure.

The window procedure function always has the following prototype:

```cpp
static LRESULT HelloWinProc (HWND hWnd, LINT message, WPARAM wParam, LPARAM lParam);
```

The four arguments of the window procedure are the same as the first four fields of MSG structure. The first argument hWnd is the handle of the window to receive messages, which is the same with the return value of CreateMainWindow function and indicates the specific window to receive the message. The second argument is the same as the message field of MSG structure, which is an integer value indicating the received message. The last two arguments are both message parameters (two integers with pointer precision), which provide special information related to the message. The window procedure function is usually not called by the program directly, but is called by MiniGUI, that is, it is a callback function.

The messages, which are not handled by the window procedure function, should be passed to DefaultMainWinProc function to perform default handling, the return value of DefaultMainWinProc must be returned by the window procedure.

### Screen Output

The program executes screen output when responding to the MSG_PAINT message. The application gets the device context handle first by calling BeginPaint function, and uses it to call GDI functions to execute drawing operations. Herein, the program uses TextOut function to display a “Hello world!” string centered at the client region of the window. The application calls EndPaint function to release the device context handle after the drawing is completed.

We will give detailed description on MiniGUI graphics device interfaces in Part II of this guide.

### Exit of the Program

The window procedure function will receive a MSG_CLOSE message when the user clicks the close button on the upper-right corner of the window. Helloworld program calls DestroyMainWindow function to destroy the main window when it receives the MSG_CLOSE message, and calls PostQuitMessage function to throw a MSG_QUIT message into the message queue. GetMessage function will return 0 when receiving the message MSG_QUIT, and finally results in exit of the program from the message loop.

The program calls MainWindowThreadCleanup to clean the system resource such as message queue used by the main window and returns from !MiniGUIMain finally.

## Compiling, Linking and Running

### Compiling MiniGUI Program

You can input the following command in the command line to compile helloworld.c, and link it to generate the executive file helloworld:

```shell
$ gcc -o helloworld helloworld.c -lminigui_procs -ljpeg -lpng -lz
```

Following compiling options are needed if MiniGUI is configured to be MiniGUI-Threads:

```shell
$ gcc -o helloworld helloworld.c -lpthread -lminigui_ths -ljpeg -lpng -lz
```

Here, -o option tells gcc the target file name to be generated, which is herein helloworld; -l option specifies the library needed to be linked when generating helloworld, which is herein minigui library and pthread library will be linked if MiniGUI is configured to be MiniGUI-Threads. Libpthread is the library to provide POSIX compatible thread support, which must be linked when compiling a MiniGUI-Threads program; The program compiled here only uses the functions in MiniGUI core library libminigui, and does not use the functions provided by other MiniGUI libraries (such as libmgext or libvcongui), therefore only minigui library is needed to be linked and the linking option is -lminigui; other function libraries such as jpeg, png, z and so on are the function libraries which are relied on by MiniGUI internally (herein we presume that you have enabled JPEG and PNG image support when configuring MiniGUI).

Provided that you configure MiniGUI to be MiniGUI-Processes, you must first ensure the server program mginit of MiniGUI have been started up before running helloworld program. For example, you can start up mginit program in mg-samples, and then enter the directory where helloworld file exists, and input ./helloworld in the command line to start up the helloworld program.

```shell
$ ./helloworld
```

Result of running the program is as shown in Figure 1.

__Prompt__ If MiniGUI has already been configured as MiniGUI-Threads, you need not start up mginit programs. One MiniGUI-Threads application can be run directly from the console.

### Components of MiniGUI

Besides core library libminigui, MiniGUI also includes five other components (libraries): mGUtils, mGPlus, mGEff, and mGNCS. If you use functions provided by these components in your program, you may need to include the corresponding header files in your program and link the corresponding libraries when compiling the application.

## Writing Automake/Autoconf Scripts for MiniGUI Application

We have already known that Autoconf/Automake is the best tool for maintaining a software project in UNIX system, which can help us be disengaged from work of inputting repeated command lines and maintain a project, and can even help us complete cross compiling of programs. mg-samples, which is released together with MiniGUI, is such a software project organized with Autoconf/Automake.

We will build project script for helloworld referring to Autoconf/Automake script of mg-samples. We will not describe in detail on working mechanism of Autoconf/Automake, and relevant information can be obtained referring to books about Linux programming or the info pages of these two programs.

Considering that the project built in this section can also be used for organizing or maintaining the demo programs of the succeeding sections in this guide, we make samples directory as the root directory of the project in an appropriate directory of the system, and name the project as samples. For example:

```shell
$ mkdir -p ~/minigui/samples
```

__Prompt__ It is presumed that the source code of mg-samples are located in the minigui directory of your home directory, which is ~/minigui/mg-samples-3.2.x, respectively.

Then make src directory in samples to store the source code of the helloworld program. Save helloworld.c into samples/src/ directory, and then copy configure.in file from mg-samples-3.2.x.

__Prompt__ Saving source files in a single directory can help us manage the project files better. As a rule, source code of a project should be saved in the directory src/, and global header files should be saved in the directory include/.

We will modify the samples project based on mg-samples configuration script below. It should be noted that these scripts need Autoconf 2.53 and Automake 1.6 or higher version, and using lower version (such as Red Hat 7.x or lower) Autoconf and Automake will result in error.

First, we modify configure.in file. The modified file is as follows (Note the comments in the text. We only modify the commented macros):

```shell
dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.13)

dnl Specify a source file of the project in the following macro
AC_INIT(src/helloworld.c)

dnl ========================================================================
dnl needed for cross-compiling
AC_CANONICAL_SYSTEM

dnl ========================================================================
dnl Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC

dnl Specify project name (samples) and project version (1.0) in the following macro
AM_INIT_AUTOMAKE(samples,1.0)

dnl ========================================================================
dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

dnl ========================================================================
dnl Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_TIME
AC_CHECK_HEADERS(sys/time.h unistd.h)

dnl ========================================================================
dnl check for libminigui
have_libminigui="no"
AC_CHECK_HEADERS(minigui/common.h, have_libminigui=yes, foo=bar)

dnl ========================================================================
dnl check for runtime mode of MiniGUI
dnl ==========================================================
threads version=”no”
AC_CHECK_DECLS(_MGRM_THREADS, threads_version="yes", foo=bar, [#include <minigui/common.h>])

procs_version="no"
AC_CHECK_DECLS(_MGRM_PROCESSES, procs_version="yes", foo=bar, [#include <minigu
i/common.h>])

standalone_version="no"
AC_CHECK_DECLS(_MGRM_STANDALONE, standalone_version="yes", foo=bar, [#include <
minigui/common.h>])

dnl ========================================================================
dnl check for newgal or oldgal interface.
use_newgal="no"
AC_CHECK_DECLS(_USE_NEWGAL, use_newgal="yes", foo=bar, [#include <minigui/common.h>])

dnl ========================================================================
dnl Write Output

if test "$ac_cv_prog_gcc" = "yes"; then
    CFLAGS="$CFLAGS -Wall -Wstrict-prototypes -pipe"
fi

if test "x$threads_version" = "xyes"; then
    CFLAGS="$CFLAGS -D_REENTRANT"
    LIBS="$LIBS -lminigui_ths -lpthread"
else
    if test "x$standalone_version" = "xyes"; then
        LIBS="$LIBS -lminigui_sa"
    else
        LIBS="$LIBS -lminigui_procs"
fi

AC_CHECK_DECLS(_HAVE_MATH_LIB, LIBS="$LIBS -lm", foo=bar, [#include <minigui/common.h>])
AC_CHECK_DECLS(_MGIMAGE_PNG, LIBS="$LIBS -lpng", foo=bar, [#include <minigui/common.h>])
AC_CHECK_DECLS(_MGIMAGE_JPG, LIBS="$LIBS -ljpeg", foo=bar, [#include <minigui/common.h>])
AC_CHECK_DECLS(_MGFONT_TTF, LIBS="$LIBS -lttf", foo=bar, [#include <minigui/common.h>])
AC_CHECK_DECLS(_MGFONT_FT2, LIBS="$LIBS -lfreetype", foo=bar, [#include <minigui/common.h>])

dnl First comment the following macro, which will be opened in the future
dnl AM_CONDITIONAL(MGRM_PROCESSES, test "x$procs_version" = "xyes")

dnl List the Makefile file to be generated in the following macro
AC_OUTPUT(
Makefile
src/Makefile
)

if test "x$have_libminigui" = "xyes"; then
    AC_MSG_WARN([
       MiniGUI is not properly installed on the system. You need MiniGUI Ver 3.0.2
       or later for building this package. Please configure and install MiniGUI Ver 3.0.2 first.
    ])
fi
```

Following works can be done with the configuration script generated by configure.in and Makefile file:
- Generate the configuration script that appropriate for cross compilation.
- Check whether MiniGUI has been installed in the system.
- Check whether the installed MiniGUI in the system is configured to be MiniGUI-Processes, MiniGUI-Threads, or MiniGUI-Standalone, and set appropriately the function libraries to be linked into the program.
- Determine other dependent function libraries to be linked according to the configuration options of MiniGUI.
- Generate Makefile in the root directory of the project and Makefiles in the src/ subdirectory.
Next, we create Makefile.am file in the root directory of the project, the content of which is as follows:

```makefile
SUBDIRS = src
```

Above file content tells Automake to enter src/ directory to handle sequentially. Then we create Makefile.am file in the src/ subdirectory, and the content of the file is as follows:

```makefile
noinst_PROGRAMS=helloworld

helloworld_SOURCES=helloworld.c
```

The file content above tells Automake to generate a Makefile, which can be used to create helloworld program from helloworld.c. Finally, we return to the root directory of the project and create an autogen.sh file, and the content of the file is as follows:

```shell
#!/bin/sh

aclocal
automake --add-missing
autoconf
```

This file is a shell script, which calls aclocal, automake, and autoconf command successively. Note that after the file being created, chmod command should be run to make it into an executable.

```
$ chmod +x autogen.sh
```

Up to now, we can run the following command to generate the Makefile file required by the project:

```
$ ./autogen.sh
$ ./configure
```

__Prompt__ ./autogen.sh command should be run to refresh configure script and makefiles after configure.in file has been modified.

After having run above commands, you will find many file automatically generated in the root directory of the project. It is unnecessary to care the purpose of these files. Ignore them, and run the make command:

```
$ make
Making all in src
make[1]: Entering directory `/home/weiym/minigui/samples/src'
source='helloworld.c' object='helloworld.o' libtool=no \
depfile='.deps/helloworld.Po' tmpdepfile='.deps/helloworld.TPo' \
depmode=gcc3 /bin/sh ../depcomp \
gcc -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE=\"samples\" -DVERSION=\"0.1\" -DSTDC_HEADERS=1 -DHAVE_SYS_WAIT_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_UNISTD_H=1 -DHAVE_MINIGUI_COMMON_H=1 -DHAVE_DECL__MGRM_PROCESSES=1 -DHAVE_DECL__MGRM_THREADS=0 -DHAVE_DECL__MGRM_STANDALONE=0 -DHAVE_DECL__USE_NEWGAL=1  -I. -I.     -g -O2 -Wall -Wstrict-prototypes -pipe -D_REENTRANT -c `test -f 'helloworld.c' || echo './'`helloworld.c
gcc  -g -O2 -Wall -Wstrict-prototypes -pipe -D_REENTRANT -o helloworld helloworld.o -lpthread -lminigui_ths -ljpeg -lpng -lz -lfreetype
make[1]: Leaving directory `/home/weiym/minigui/samples/src'
make[1]: Entering directory `/home/weiym/minigui/samples'
make[1]: Nothing to be done for `all-am'.
make[1]: Leaving directory `/home/weiym/minigui/samples'
```

If you have a careful look at above output, you can find that make command enters src/ subdirectory first, and call gcc to compile helloworld.c into the object file helloworld.o, and then call gcc again to generate helloworld program. Notice that gcc links the functions in the libraries of pthread, minigui, jpeg, png etc. (-lpthread -lminigui) when generating helloworld program. The reason is because that the author has configured MiniGUI to be MiniGUI-Threads runtime mode, linking pthread library is needed for generating MiniGUI-Threads application, and MiniGUI provides the support for JPEG and PNG picture by using jpeg and png libraries.

If the scale of the helloworld program is very huge, and thus source code are placed into different source files, you need only modify the Makefile.am file in src/, append the names of these source files to the helloworld_SOURCES, and then run make command again in the root directory of the project. For example:

```makefile
noinst_PROGRAMS=helloworld

helloworld_SOURCES=helloworld.c helloworld.h module1.c module2.c
```

__Prompt__ Please list source files and header files on which the program depends behind foo_SOURCES.

Demo programs of other chapters in this guide can be added to this project conveniently. For example, in order to add foo program, we can modify the Makefile.am file as follows:

```makefile
noinst_PROGRAMS=helloworld foo

helloworld_SOURCES=helloworld.c
foo_SOURCES=foo.c
```

Thus, two program files, which are helloworld and foo respectively, will be generated during compilation.

__Prompt__ Foo is generally used to specify a hypothetical object or name, which should be replaced by the real name in an actual project. Demo programs after this section can all be added into samples project in this way.

Having such a simple project frame and Automake/Autoconf script template, we can enrich these scripts based on our requirements. These scripts can help us perform many works, the most important among which is to configure cross compilation option to help us porting our application into the target system. You can refer to [User Manual for MiniGUI 3.2](MiniGUIUserManualV32) to get knowledge about cross compilation of MiniGUI application.

Full demo program package of this guide is mg-samples-3.2.x.tar.gz, which includes all the demo programs of this guide and includes complete Autoconf/Automake for your reference.

----

&lt;&lt; [Preface](MiniGUIProgGuidePreface.md) |
[Table of Contents](README.md) |
[Window and Message](MiniGUIProgGuidePart1Chapter02.md) &gt;&gt;

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
