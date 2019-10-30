# Universal Startup API for RTOSes

- [Malloc Initialization Interface](#malloc-initialization-interface)
- [Standard Output Initialization Interface](#standard-output-initialization-interface)
- [POSIX Threads Initialization Interface](#posix-threads-initialization-interface)


MiniGUI provides universal startup API for RTOSes and spare startup
reference files in V2.0.4/1.6.9. MiniGUI 3.0 continues to use these files.
These files are saved in the MiniGUI source code `rtos/` directory. The rules of
nomenclature in these files are like `<os_name>_startup.c`. In startup
file, there are an introduction to malloc, printf and POSIX thread
initialization interface. The following is detailed description.

## Malloc Initialization Interface

MiniGUI provides an own-implemented malloc set of functions. We can use macro
`_MGUSE_OWN_MALLOC` to open it. MiniGUI provides the following interface to
initialize MiniGUI malloc set of functions.

```cpp
int init_minigui_malloc (unsigned char* heap, unsigned int heap_size,
int (*lock_heap) (void), int (*unlock_heap) (void));
```

To use MiniGUI malloc set of functions, you should pass the information of heap
address, lock and unlock heap function pointer, and stack size.

The following is the reference implementation on ThreadX OS.

```cpp
#include "tx_api.h"

/* use a static array as the heap */
#define HEAPSIZE  (1024*1024*3)
static unsigned char __threadx_heap [HEAPSIZE];
static unsigned int __threadx_heap_size = HEAPSIZE;

static TX_MUTEX __threadx_malloc_mutex;

#define NAME_MUTEX_MALLOC   "Mutex4Malloc"

static int __threadx_heap_lock (void)
{
        UINT status;

        status = tx_mutex_get (&__threadx_malloc_mutex, TX_WAIT_FOREVER);
        if (status == TX_SUCCESS)
            return 0;

        return -1;
}

static int __threadx_heap_unlock (void)
{
        UINT status;

        status = tx_mutex_put (&__threadx_malloc_mutex);
        if (status == TX_SUCCESS)
            return 0;

        return -1;
}

...

    /*
     * Initialize MiniGUI's heap memory management module secondly.
     */
    if (tx_mutex_create (&__threadx_malloc_mutex, NAME_MUTEX_MALLOC, TX_NO_INHERIT) = TX_SUCCESS) {
        fprintf (stderr, "Can not init mutex object for heap.\n");
        return;
    }

    if (init_minigui_malloc (__threadx_heap, __threadx_heap_size, __threadx_heap_lock, __threadx_heap_unlock)) {
        fprintf (stderr, "Can not init MiniGUI heap system.\n");
        return;
    }

```

## Standard Output Initialization Interface

MiniGUI provides an own-implemented printf set of functions. We can use macro
`_MGUSE_OWN_STDIO` to open it. MiniGUI provides the following interface to
initialize MiniGUI printf set of functions.

```cpp
int init_minigui_printf (int (*output_char) (int ch), int (*input_char) (void));
```

The following is a reference implementation.
```cpp
extern int serial_write (int ch);
extern int serial_read (void);

/* init MiniGUI's own printf system */
init_minigui_printf (serial_write, serial_read);
```

So the information which is printed to standard output and standard error by
printf/fprintf functions will be printed to serial port of the device.

## POSIX Threads Initialization Interface

MiniGUI provides an own-implemented POSIX threads system. We can use macro
`_MGUSE_OWN_PTHREAD` to open it. MiniGUI provides the following interface to
initialize RTOS POSIX threads system.

```cpp
#define MAIN_PTH_MIN_STACK_SIZE (1024)
#define MAIN_PTH_DEF_STACK_SIZE (1024*4)

int start_minigui_pthread (int (* pth_entry) (int argc, const char* argv []), int argc, const char* argv[], char* stack_base, unsigned int stack_size);
```

The first argument `pth_entry` will run as main thread. In reality, we can pass
`minigui_entry` for it. For example:

```cpp
...

/* the stack for main thread */
static char main_stack [MAIN_PTH_DEF_STACK_SIZE];

char* argv[] = {"pth_entry", NULL};

    /*
     * Initialize MiniGUI's POSIX thread module and call minigui_entry thirdly.
     */
    if (start_minigui_pthread (minigui_entry, 0, NULL, main_stack, MAIN_PTH_DEF_STACK_SIZE)) {
        fprintf (stderr, "Can not init MiniGUI pthread system for ThreadX.\n");
        return;
    }
```

The following list shows the relationship between RTOS and macros above.

| *RTOS* | *Macro* |
|--------|---------|
| VxWorks | `_MGUSE_OWN_STDIO` <br/> `_MGUSE_OWN_MALLOC` <br/> `_MGUSE_OWN_PTHREAD` |
| uC/OS-II | `_MGUSE_OWN_STDIO` <br/> `_MGUSE_OWN_MALLOC` <br> `_MGUSE_OWN_PTHREAD` |
| `eCos` | none |
| `pSOS` | `_MGUSE_OWN_PTHREAD` |
| Win32 | `_MGUSE_OWN_STDIO`|
| `OSE` | `_MGUSE_OWN_PTHREAD`|
| ThreadX | `_MGUSE_OWN_STDIO` <br/> `_MGUSE_OWN_MALLOC` <br/> `_MGUSE_OWN_PTHREAD` |
| Nucleus | `_MGUSE_OWN_STDIO` <br/> `_MGUSE_OWN_MALLOC` <br/> `_MGUSE_OWN_PTHREAD` |

----

[&lt;&lt; GAL and IAL Engines](MiniGUIProgGuidePart5Chapter03.md) |
[Table of Contents](README.md) |
[Static Control &gt;&gt;](MiniGUIProgGuidePart6Chapter01.md)

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
