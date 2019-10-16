# Appendix A Universal Startup API for RTOSes

MiniGUI provides universal startup API for RTOSes and spare startup reference files in V2.0.4/1.6.9. MiniGUI 3.0 continues to use these files. These files are saved in the MiniGUI source code rtos/ directory. The rules of nomenclature in these files are like &gt;os_name&lt;_startup.c. In startup file, there are an introduction to malloc, printf and POSIX pthread initialization interface. The following is detailed description.

## A.1 Malloc Initialization Interface

MiniGUI provides an own-implemented malloc set of functions. We can use macro _USE_OWN_MALLOC to open it. MiniGUI provides the following interface to initialize MiniGUI malloc set of functions.

```cplusplus
int init_minigui_malloc (unsigned char* heap, unsigned int heap_size, 
int (*lock_heap) (void), int (*unlock_heap) (void));
```

To use MiniGUI malloc set of functions, you should pass the information of heap address, lock and unlock heap function pointer, and stack size.

The following is the reference implementation on ThreadX OS.
```cplusplus
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

## A.2 Standard Output Initialization Interface

MiniGUI provides an own-implemented printf set of functions. We can use macro _USE_OWN_STDIO to open it. MiniGUI provides the following interface to initialize MiniGUI printf set of functions.

```cplusplus
int init_minigui_printf (int (*output_char) (int ch), int (*input_char) (void));
```

The following is a reference implementation.
```cplusplus
extern int serial_write (int ch);
extern int serial_read (void);

/* init MiniGUI's own printf system */
init_minigui_printf (serial_write, serial_read);
```

So the information which is printed to standard output and standard error by printf/fprintf functions will be printed to serial port of the device.

## A.3 POSIX Threads Initialization Interface

MiniGUI provides an own-implemented POSIX threads system. We can use macro _USE_OWN_PTHREAD to open it. MiniGUI provides the following interface to initialize RTOS POSIX threads system.
```cplusplus
#define MAIN_PTH_MIN_STACK_SIZE (1024)
#define MAIN_PTH_DEF_STACK_SIZE (1024*4)

int start_minigui_pthread (int (* pth_entry) (int argc, const char* argv []), int argc, const char* argv[], char* stack_base, unsigned int stack_size);
```

The first argument pth_entry will run as main thread. In reality, we can pass minigui_entry for it. For example:

```cplusplus
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

<center>
| *RTOS*  | *Macro* |
|VxWorks          | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |
|uC/OS-II         | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br> _MGUSE_OWN_PTHREAD |
|eCos             | none |
|pSOS             | _MGUSE_OWN_PTHREAD |
|Win32   | _MGUSE_OWN_STDIO|
|OSE     | _MGUSE_OWN_PTHREAD|
|ThreadX | _MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |
|Nucleus |_MGUSE_OWN_STDIO <br/> _MGUSE_OWN_MALLOC <br/> _MGUSE_OWN_PTHREAD |
</center>

-- Main.XiaodongLi - 26 Oct 2009