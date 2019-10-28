# Other Programming Topics

## Timer

MiniGUI application can call function `SetTimer` to create a timer. When the
created timer is expired, the target window will receive message `MSG_TIMER`,
the 
identifier of the timer, and the system tick value that the timer is triggered.
When the time is not needed, application program can call `KillTimer` to delete
the timer. `SetTimerEx` and `ResetTimerEx` are provided since MiniGUI version
2.0.4/1.6.10; they support timer callback procedure. The prototypes are as
follow:

```
```

The meaning of each parameter in `TIMERPROC` is as follows：
- The window handle passed when creating the timer. If no use, it can be any
32-bit value.
- The timer `ID`.
- The system tick value that the timer is triggered.

When `TIMERPROC` return `FALSE`, MiniGUI will delete the timer automatically. 
It 
can be used to create one-shot timer.

The timer mechanism of MiniGUI provides application with a comparatively
convenient timing mechanism. However, the timer mechanism of MiniGUI has the
following constraints:
- Each message queue of MiniGUI-Threads only can manage 32 timers. Note that
when creating a new thread, there will be a new message queue created to
correspond, that is, each thread can have maximum 32 timers.
- MiniGUI-Processes has only one message queue, which can manage maximum 32
timers.
- The process of timer message is relatively special. Its implementation is
similar to the signal mechanism of `UNIX` operating system. System will ignore
this new timer message when a certain timer message has not been processed but
new timer message occurs. It is because that if the frequency of certain timer
is very high while the window processing this timer responds too slowly, when
the message still needs to be posted, the message queue will be finally choked
up.
- Timer message has the lowest priority. When there is not other type of
messages in the message queue (such as posted message, notification message,
and painting message), system will go to check if there is any expired timer.

When the timer frequency is very high, it is possible that such situation like
timer message lost or interval asymmetry occurs. If application needs to use
relatively accurate timer mechanism, it should use setitimer system call of
Linux/UNIX with `SIGALRM` signal. What needs to note is that the server process
(mginit program) of MiniGUI-Processes has called setitimer system call to
install the timer. Therefore, the program `mginit` realized by application
itself 
cannot use setitimer to realize the timer. However, the client program of
MiniGUI-Processes still can call setitimer. MiniGUI-Threads has no such
constraint.

Code in List 1 creates a timer with interval of one second, then use current
time to set static text when timer is expired so as to display the clock.
Finally, program will delete the timer while closing window.

##### List 1 Use of Timer

```
```

It is necessary to explain that the third argument of `SetTimer` is used to
specify the interval of timer. The default unit is 10 milliseconds.

Application can also call `ResetTimer` to reset interval of a timer. The usage
of 
the function is similar to `SetTimer`.

Moreover, MiniGUI provides the other two functions to query system timer
status. `IsTimerInstalled` is used to check whether a timer is installed in the
assigned window. `HaveFreeTimer` is used to check whether system have free 
timer 
resources.

## Clipboard

Clipboard is a tool to transfer data, and can be used for data communication
among applications and application internals. Its principle is very simple,
that is, a program places data on the clipboard, and another application takes
the data from the clipboard. Clipboard is a data interchange station among
applications.

Edit box control in MiniGUI supports clipboard operations, when the user
selects text and press down *CTRL+C* keys, the data is copied to the text
clipboard by default; when the users press down *CTRL+V* keys, the data is
copied from the clipboard into edit box.

### Creating and Destroying Clipboard

MiniGUI provides a default text clipboard, named as `CBNAME_TEXT` (string name
“text”), used for copying and pasting of text. Applications can use the
clipboard directly without other additional operations. A clipboard defined by
an application itself need to be created with `CreateClipBoard` function, and 
to 
be destroyed with `DestroyClipBoard` after using it.

There are at most `NR_CLIPBOARDS` clipboards in MiniGUI, including the system
default text clipboard and clipboards defined by user. `NR_CLIPBOARDS` macro is
defined to be 4 in `minigui/window.h` header file by default.

`CreateClipBoard` function creates a clipboard with specified name, this name
can 
not be same as the name of existing clipboards (system defined or user
defined):

```
```

Argument `cb_name` specifies the name of a clipboard; argument size specifies
the 
size of data to be stored by the clipboard. If creates successfully, the
function returns `CBERR_OK`; if the name is reduplicate, the function returns
`CBERR_BADNAME`; if the memory is not enough, the function returns 
`CBERR_NOMEM`. 

The `DestroyClipBoard` function destroys a user defined clipboard created by
`CreateClipBoard` function:

```
```

### Transferring Data to Clipboard

`SetClipBoardData` function transfers data to a specified clipboard.

```
```

Here, the argument `cb_name` specifies the name of clipboard; data is the
pointer 
to data buffer; n is the size of data; cbop is the operation type, which can
be:
- `CBOP_NORMAL`: Default overwriting operation. The new data overwrites the
existing data on the clipboard;
- `CBOP_APPEND`: Appending operation. The new data will be appended to the
existing data on the clipboard

### Getting Data from Clipboard

`GetClipBoardDataLen` function is used to get the size of data on clipboard.

```
```

`GetClipBoardData` function is used to copy the data on clipboard to the
specified data buffer:

```
```

Here the argument `cb_name` specifies the name of the clipboard; data is the
pointer to the data buffer; n specifies the size of specified data buffer. The
function returns the size of gotten data from the clipboard

Generally speaking, you can use `GetClipBoardDataLen` function to get the size
of 
data before using `GetClipBoardData` function to get data of clipboard, so that
you can specify an appropriate data buffer to save data.

`GetClipBoardByte` function is used to get a byte from the specified position 
of 
data on clipboard.

```
```

Here the argument index specifies the index position of specified data; byte is
used to save the gotten byte data.

## Reading/Writing Configuration File

The configuration file of MiniGUI (default as /usr/local/etc/MiniGUI.cfg file)
uses Windows `INI-like` file format. This format is very simple, seen as
follows: 

```
```

The information of such configuration file is grouped by section, then uses
key=value format to appoint parameter and its value. Application can also use
this format to store some configuration information. So, MiniGUI provides
following functions (minigui/minigui.h):

```
```

The use of first three functions is as follows:
- `GetValueFromEtcFile`: To get a specified key value from a specified
configuration file. The value of the key returns as a string.
- `GetIntValueFromEtcFile`: To get a specified key integer value from a
specified 
configuration file. This function converts the accepted string to integer
value (using strtol function) and then returns the value.
- `SetValueToEtcFile`: This function stores the given key value into a 
specified 
configuration file. If the configuration file does not exist, this function
will create new configuration file. If the file exists, the old value will be
covered.

The next five functions are new configuration file reading/writing function
since MiniGUI version 1.6.x; the use of them is as follows:
- `LoadEtcFile`: Read a specified configuration file into memory and returns a
configuration object handle, then the related functions can visit the
configuration information in memory through this handle.
- `UnloadEtcFile`: Release the configuration information in memory.
- `GetValueFromEtc`: The way of use is similar to `GetValueFromEtcFile`; But 
its 
first argument is the configuration object handle, not the file name. This
function can be used to get configuration information from memory.
- `GetIntValueFromEtc`: The way of use is similar to `GetIntValueFromEtcFile`.
- `SetValueToEtc`: Similar to `SetValueToEtcFile`, but this function only
changes 
the configuration key value in memory, does not affect the content in the
file.

The last seven functions are new configuration file reading/writing function
since MiniGUI version 2.0.4/1.6.10; the use of them is as follows:
- `RemoveSectionInEtcFile`: Remove a specified section from a specified
configuration file.
- `RemoveSectionInEtc`: Remove a specified section from the configuration
information in memory.
- `GetValueFromEtcSec`: Get value from a specified section in memory. Similar 
to 
`GetValueFromEtc`.
- `GetIntValueFromEtcSec`: Get an integer value from specified section in
memory. 
Similar to `GetIntValueFromEtc`.
- `SetValueToEtcSec`: Set the value in a specified section in memory. Similiar
to 
`SetValueToEtc` and `SetValueToEtc`.
- `FindSectionInEtc`: Find or create a specified section from the configuration
information in memory.
- `SaveEtcToFile`: Save the configuration information in memory into a 
specified 
file.

These functions are usually used to read all information of configuration file
for once. When need to get relatively more key values, this function will first
use `LoadEtcFile` to read in a configuration file, and then use 
`GetValueFromEtc` 
to get key value. When there is no need to visit configuration information, use
`UnloadEtcFile` to release the configuration object handle.

Assuming that certain configuration file records some application information,
and has the following formats:

```
```

The section [mginit] records the number of applications and its
automatically-startup index (autostart key). The section [appX] records
information of each application program, including the path, the name, and the
icon of the application. Code in List 2 illustrates how to use the functions
above to get such information (the code comes from program `mginit` of
mg-samples).

##### List 2 Using MiniGUI configuration file functions to get information

```
```

If using `LoadEtcFile`, `GetValueFromEtc`, and `UnloadEtcFile` to implement
above 
example, the code will be as follows:

```
```

We also need change `GetValueFromEtcFile` of function `get_app_info` to
`GetValueFromEtc`.

## Writing Portable Program

As we know, the `CPU` used by most embedded system has totally different
construction and characteristic from the `CPU` of normal desktop `PC`. However,
operating system and advanced language can hide these differences to a great
extent. With the support of advanced language programming, the compiler and
operating system can help programs solve most problems related to `CPU`
architecture and characteristic in order to save developing time and increase
developing efficiency. However, application programs have to face some certain
`CPU` characteristics; the following aspects need to be paid more attention:

- The order of byte. Generally, when `CPU` stores integer data of multi-bytes,
it 
will store the low-bit byte in low address unit, such as Intel x86 series.
Some `CPU` uses opposite order to store. For example, the popularly used 
`PowerPC` 
in embedded system stores low-bit byte in high address unit. The former is
called little-endian system while the latter is called big-endian system.
- The Linux kernel on some platforms may lack of some advanced system calls,
the most popular one is the system calls related to virtual memory mechanism.
The Linux system running on certain `CPU` cannot provide virtual memory
mechanism 
because of the limitation of `CPU` capability. For example, `CPU` lack of `MMU`
unit 
cannot provide the sharing memory of System V `IPC` mechanism.

In order to make the portable code have most popular adaptability, application
programs must notice these differences and write code according to different
situations. Here we will describe how to write portable code in MiniGUI
applications.

### Using Endian-Specific Read/Write Functions of MiniGUI

In order to solve the first problem mentioned above, MiniGUI provides several
endian-related read/write functions. These functions can be divided into two
categories:

- Functions used to swap the order of byte, including `ArchSwapLE16`,
`ArchSwapBE16` and so on.
- Functions used to read/write standard I/O stream, including `MGUI_ReadLE16`,
`MGUI_ReadBE16` and so on.

The first category is used to convert the 16-bit, 32-bit, or 64-bit integer
into system native byte from certain byte order. For example:

```
```

The above code first uses read system call to read an integer value from the a
specified file descriptor to variable `len_header.` The integer value saved in
this file is in little-endian, so the byte order of this integer value has to
be swapped if this integer value is used in big-endian system. We can use
`ArchSwapLE32` to convert 32-bit integer value into system native byte order.
Also, we can swap the bytes only for big-endian system, and then we just need
to use `ArchSwap32` function.

The functions (or macro) used to swap bytes are as follow:
- `ArchSwapLE16(X`) converts the specified 16-bit integer value (stored in
little 
endian byte order) to system native integer value. If system is little
endian, this function will directly return X; if system is big endian, the
function will call `ArchSwap16` to swap the bytes.
- `ArchSwapLE32(X`) converts the specified 32-bit integer value (stored in
little 
endian byte order) to system native integer value. If system is little
endian, this function will directly return X; if system is big endian, the
function will call `ArchSwap32` to swap the bytes.
- `ArchSwapBE16(X`) converts the specified 16-bit integer value (stored in big
endian byte order) to system native integer value. If system is big endian,
this function will directly return X; if system is little endian, the function
will call `ArchSwap16` to swap the bytes.
- `ArchSwapBE32(X`) converts the specified 32-bit integer value (stored in big
endian byte order) to system native integer value. If system is big endian,
this function will directly return X; if system is little endian, the function
will call `ArchSwap32` to swap the bytes.

The second category of functions provided by MiniGUI is used to read/write
integer value from standard I/O file object. If the file is stored in little
endian byte order, the function uses `MGUI_ReadLE16` and `MGUI_ReadLE32` to 
read 
integer value by converting integer value to system native byte order, whereas
uses `MGUI_ReadBE16` and `MGUI_ReadBE32`. If the file is stored as little 
endian 
byte order, the function will use `MGUI_WriteLE16` and `MGUI_WriteLE32` to 
write 
integer value after converting integer value from system native byte order to
little endian; whereas use `MGUI_WriteBE16` and `MGUI_WriteBE32`. The following
code explains the above functions:

```
```

### Using Condition Compilation to Write Portable Code

When regarding problems related to portability, we can easily use the way
described above to perform function wrap in order to provide well portable
code. However, sometime we cannot use such way to provide the portable code, so
we can only use conditional compilation. Code in List 3 illustrates how to use
conditional compilation to ensure the program running well (the code come from
MiniGUI src/kernel/sharedres.c).

List 3 The usage of conditional compilation

```
```

The MiniGUI-Processes server program to load sharing resource uses the above
code fragment. If system supports shared memory, it will initialize the shared
memory object and associate the shared resource with the shared memory object,
then write the shared memory object `ID` into a file; if system does not 
support 
shared memory, it will write all initialized sharing resource into a file. If
the system support shared memory, clients can get shared memory object `ID` 
from 
the file and directly attach it; if the system does not support shared memory,
clients can use mmap system call to map the file to the address space of them.
Code of clients can be seen in List 4.


List 4 The usage of conditional compilation (cont.)

```
```

## Fixed-Point Computing

Usually when we perform math operations, we will use float-point to represent
real number, and use <math.h> head file to calculate the float-point number.
However, float-point calculation is a time-consuming process. Therefore, in
order to reduce extra `CPU` instructions caused by float-point calculation, 
some 
three-dimension graphics application always use fixed-point number to represent
real number, which will greatly accelerate the calculation of three-dimension
graphical rendering. MiniGUI also provides some fixed-point computing
functions, divided into the following categories:

- Conversion among integer, float-point number and fixed-point number. itofix
converts integer to fixed-point number, while fixtoi converts fixed-point to
integer; ftofix converts float-point number to fixed-point number, while fixtof
converts fixed-point number to float-point number.
- The basic arithmetic computing such as add, subtract, multiple, and divide of
fixed-point numbers: fixadd, fixsub, fixmul, fixdiv, fixsqrt.
- The triangle compute of fixed-point number: fixcos, fixsin, fixtan, fixacos,
fixasin.
- Matrix and vector computing. Matrix and vector related computing are
important for three-dimension graphics. Readers can refer to
`minigui/fixedmath.h` for the functions.

Code in List 5 illustrates the use of fixed-point number. This code converts
plane rectangular coordinates to screen coordinates.

##### List 5 fixed-point computing

```
```

The calculation of above program is very simple. The steps are as follow:

- Converts the input parameters to fixed-point values.
- Does the calculation by using the fixed-point values.
- Converts the result values to float-point values.

----

[&lt;&lt; Look and Fee and UI Effects](MiniGUIProgGuidePart1Chapter10.md) |
[Table of Contents](README.md) |
[Using mGUtils &gt;&gt;](MiniGUIProgGuidePart1Chapter12.md)

[Release Notes for MiniGUI 3.2]:
/supplementary-docs/Release-Notes-for-MiniGUI-3.2.md 
[Release Notes for MiniGUI 4.0]:
/supplementary-docs/Release-Notes-for-MiniGUI-4.0.md 
[Showing Text in Complex or Mixed Scripts]:
/supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md 
[Supporting and Using Extra Input Messages]:
/supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md 
[Using `CommLCD` `NEWGAL` Engine and Comm `IAL` Engine]:
/supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md 
[Using Enhanced Font Interfaces]:
/supplementary-docs/Using-Enhanced-Font-Interfaces.md 
[Using Images and Fonts on System without File System]:
/supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md 
[Using `SyncUpdateDC` to Reduce Screen Flicker]:
/supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md 
[Writing `DRI` Engine Driver for Your `GPU]`:
/supplementary-docs/Writing-DRI-Engine-Driver-for-Your-GPU.md 
[Writing MiniGUI Apps for 64-bit Platforms]:
/supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md 

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building `MiniGUI]`: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]:
/user-manual/MiniGUIUserManualCompiletimeConfiguration.md 
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md

[MiniGUI Overview]: /MiniGUI-Overview.md
[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI Supplementary Documents]: /supplementary-docs/README.md
[MiniGUI `API` Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing `FMSoft` Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
