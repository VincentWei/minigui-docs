# 其他编程主题

## 1.1 定时器

在 MiniGUI 中，应用程序可以调用 `SetTimer` 函数创建定时器。当创建的定时器到期时，创建定时器时指定的窗口就会收到 `MSG_TIMER` 消息，并传递到期的定时器标识号和定时器被触发时的系统滴答值。在不需要定时器时，应用程序可以调用 `KillTimer` 函数删除定时器。在 MiniGUI 2.0.4/1.6.10 及其后版本中，MiniGUI 新增了 `SetTimerEx` 和 `ResetTimerEx` 两个函数。使用 `SetTimerEx` 函数可指定定时器回调函数，而 `SetTimer` 和 `ResetTimer` 被定义为 `SetTimerEx` 和 `ResetTimerEx` 的宏。相关的函数接口定义如下：

```c
typedef BOOL (* TIMERPROC)(HWND, int, DWORD);

BOOL GUIAPI ResetTimerEx (HWND hWnd, int id, unsigned int speed,
TIMERPROC timer_proc);

BOOL GUIAPI SetTimerEx (HWND hWnd, int id, unsigned int speed,
TIMERPROC timer_proc);

#define SetTimer(hwnd, id, speed) \
SetTimerEx(hwnd, id, speed, NULL)

#define ResetTimer(hwnd, id, speed) \
ResetTimerEx(hwnd, id, speed, (TIMERPROC)0xFFFFFFFF)
```

其中，`TIMERPROC` 回调函数的三个参数含义分别为：

- 创建定时器时传入的窗口句柄。如果没有必要使用，可传任何 32 位值。
- 定时器 ID。传入 `SetTimerEx` 的定时器 ID 号。
- 该定时器被触发时的系统滴答值。

当 `TIMERPROC` 返回值为 `FALSE` 时，MiniGUI 将自动删除该定时器，该特性用于创建单次（one-shot）定时器。

MiniGUI 的定时器机制给应用程序提供了一种比较方便的定时机制。但是，在 MiniGUI 中，定时器机制存在如下一些限制：

- MiniGUI-Threads 中，每个消息队列最多能管理 32 个定时器。注意，每创建一个线程，将创建一个新消息队列与之对应。另外，每个应用程序最多也只能设置 32 个定时器。
- MiniGUI-Processes 模式下，每个进程只有一个消息队列，这个消息队列最多可以管理 32 个定时器。
- 定时器消息的处理比较特殊，在实现上，和 Linux 的信号机制类似。当一次定时器消息尚未处理而又出现一次新的定时器消息时，系统将忽略这个新的定时器消息。这是因为当某个定时器的频率很高，而处理这个定时器的窗口的反应速度又很慢时，如果仍然采用邮寄消息的方式，消息队列最终就会塞满。
- 定时器消息是优先级最低的消息类型，只有消息队列中不存在其它类型的消息（比如邮寄消息、通知消息、退出消息、绘图消息）时，系统才会去检查是否有定时器到期。

这样，当设定的定时器频率很高时，就有可能出现定时器消息丢失或者间隔不均匀的情况。如果应用程序需要比较精确的定时器机制，则应该采用其它操作系统的机制。比如在 Linux 操作系统中，可以使用 `setitimer` 系统调用，并自行处理 `SIGALRM` 信号。需要注意的是，MiniGUI-Processes 的服务器进程，即 `mginit` 程序已经调用 `setitimer` 系统调用安装了定时器，因此，应用程序自己实现的 `mginit` 程序不应该再使用 `setitimer` 实现自己的定时器，但 MiniGUI-Processes 的客户程序仍可以调用 `setitimer` 函数。MiniGUI-Threads 则没有这样的限制。

__清单 1.1__ 中的程序建立了一个间隔为 1 秒的定时器，然后在定时器到时时用当前的时间设置静态框的文本，从而达到显示时钟的目的，最后，在关闭窗口时删除这个定时器。

__清单 1.1__ 定时器的使用

```c
#define _ID_TIMER 100
#define _ID_TIME_STATIC 100

static char* mk_time (char* buff)
{
        time_t t;
        struct tm * tm;
        
        time (&t);
        tm = localtime (&t);
        sprintf (buff, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
        
        return buff;
}

static int TaskBarWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        char buff [20];
        
        switch (message) {
                case MSG_CREATE:
                {
                        CreateWindow (CTRL_STATIC, mk_time (buff), 
                        WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
                        _ID_TIME_STATIC, g_rcExcluded.right - _WIDTH_TIME - _MARGIN, _MARGIN,
                        _WIDTH_TIME, _HEIGHT_CTRL, hWnd, 0);
                        
                        /* 创建一个间隔为 1 秒的定时器，其标识号为 _ID_TIMER，接收定时器消息的窗口为 hWnd */
                        SetTimer (hWnd, _ID_TIMER, 100);
                        break;
                        
                        case MSG_TIMER:
                        {
                                /* 接收到定时器消息。
                                * 严格的程序还应该在这里判断 wParam 是否等于期望的定时器标识符，这里是 _ID_TIMER。
                                */
                                SetDlgItemText (hWnd, _ID_TIME_STATIC, mk_time (buff));
                                break;
                        }
                        
                        case MSG_CLOSE: 
                        /* 删除定时器 */
                        KillTimer (hWnd, _ID_TIMER);
                        DestroyAllControls (hWnd);
                        DestroyMainWindow (hWnd);
                        PostQuitMessage (hWnd);
                        return 0;
                }
                
                return DefaultMainWinProc (hWnd, message, wParam, lParam);
        }
```

需要说明的是，`SetTimer` 的第三个参数用来指定定时器的间隔，默认以 10 毫秒为单位，取值 100 即 1 秒。

应用程序还可以调用 `ResetTimer` 函数重新设定定时器的间隔，这个函数的参数意义和 `SetTimer` 一样。

另外，还有两个函数用于查询系统中的定时器使用状态。`IsTimerInstalled` 函数用于检查一个定时器是否被安装到指定的窗口上。`HaveFreeTimer` 用于检测系统中是否还有可用的定时器资源。

## 1.2 剪贴板

剪贴板是一个数据传送的工具，可以用于应用程序之间和应用程序内部的数据交互。它的原理比较简单，就是一个程序把数据放到剪贴板上，另一个应用程序从剪贴板上把数据取下来，剪贴板是应用程序间的一个数据中转站。

MiniGUI 中的编辑框控件支持剪贴板操作，当用户选择文本然后按“CTRL+C”键时，数据将被复制到系统默认的文本剪贴板；当用户按“CTRL+V”键时，数据将从剪贴板复制到编辑框中。

### 1.2.1 创建和销毁剪贴板

MiniGUI 提供了一个默认的文本剪贴板，名字为 `CBNAME_TEXT`（字符串名”text”），用于文本的复制和粘贴。应用程序可以直接使用该剪贴板，不需要其它额外的操作。应用程序自定义的剪贴板需要使用 `CreateClipBoard` 函数创建，使用完之后用 `DestroyClipBoard` 函数进行销毁。

MiniGUI 中最多只能有 `NR_CLIPBOARDS` 个剪贴板，包括系统默认的文本剪贴板和用户自定义的剪贴板。`NR_CLIPBOARDS` 宏在 window.h 头文件中默认定义为 4。

`CreateClipBoard` 函数创建一个指定名字的剪贴板，该名字不能和已有的剪贴板（系统定义的或者用户定义的）名字重复。

```c
int GUIAPI CreateClipBoard (const char* cb_name, size_t size);
```

`cb_name` 参数指定剪贴板的名字，`size` 参数指定剪贴板存储数据的大小。如果创建成功，函数返回 `CBERR_OK`；如果名字重复，返回 `CBERR_BADNAME`；如果内存不足，返回 `CBERR_NOMEM`。

`DestroyClipBoard` 函数销毁一个使用 `CreateClipBoard` 函数创建的自定义剪贴板。

```c
int GUIAPI DestroyClipBoard (const char* cb_name);
```

### 1.2.2 把数据传送到剪贴板

`SetClipBoardData` 函数把数据传送到指定的剪贴板。

```c
int GUIAPI SetClipBoardData (const char* cb_name, void* data, size_t n, int cbop);
```

`cb_name` 指定剪贴板的名字，`data` 为数据缓冲区指针，`n` 为数据的大小。`cbop` 为剪贴板操作类型，可以是：

- `CBOP_NORMAL`：默认的覆盖操作，新的数据覆盖剪贴板已有的数据；
- `CBOP_APPEND`：追加操作，新的数据将被附加到剪贴板已有数据之后。

### 1.2.3 从剪贴板上获取数据

`GetClipBoardDataLen` 函数用来获取剪贴板上数据的大小。

```c
size_t GUIAPI GetClipBoardDataLen (const char* cb_name);
```

`GetClipBoardData` 函数用把剪贴板上的数据复制到指定的数据缓冲区中。

```c
size_t GUIAPI GetClipBoardData (const char* cb_name, void* data, size_t n);
```

`cb_name` 指定剪贴板的名字，`data` 为数据缓冲区指针，`n` 指定缓冲区的大小。函数返回所获取的剪贴板数据的大小。

一般来说，可以在使用 `GetClipBoardData` 函数获取剪贴板数据之前先用 `GetClipBoardDataLen` 函数获取数据的大小，以便分配一个合适的数据缓冲区来保存数据。

`GetClipBoardByte` 函数用来从剪贴板数据的指定位置获取一个字节。

```c
int GUIAPI GetClipBoardByte (const char* cb_name, int index, unsigned char* byte);
```

`index` 指定数据的索引位置，`byte` 用来保存获取的字节数据。

## 1.3 读写配置文件

MiniGUI 的配置文件（默认为 `/usr/local/etc/MiniGUI.cfg ` 文件）采用了类似 Windows INI 文件的格式。这种文件格式非常简单，如下所示：

```c
[section-name1]
key-name1=key-value1
key-name2=key-value2

[section-name2]
key-name3=key-value3
key-name4=key-value4
```

这种配置文件中的信息以 `section` 分组，然后用 `key=value` 的形式指定参数及其值。应用程序也可以利用这种配置文件格式保存一些配置信息，为此，MiniGUI 提供了如下函数（<minigui/minigui.h>）：

```c
int GUIAPI GetValueFromEtcFile (const char* pEtcFile, const char* pSection,
const char* pKey, char* pValue, int iLen);

int GUIAPI GetIntValueFromEtcFile (const char* pEtcFile, const char* pSection,
const char* pKey, int* value);

int GUIAPI SetValueToEtcFile (const char* pEtcFile, const char* pSection,
const char* pKey, char* pValue);

GHANDLE GUIAPI LoadEtcFile (const char* pEtcFile);

int GUIAPI UnloadEtcFile (GHANDLE hEtc);

int GUIAPI GetValueFromEtc (GHANDLE hEtc, const char* pSection, 
const char* pKey, char* pValue, int iLen);

int GUIAPI GetIntValueFromEtc (GHANDLE hEtc, const char* pSection, 
const char* pKey, int *value);

int GUIAPI SetValueToEtc (GHANDLE hEtc, const char* pSection,
const char* pKey, char* pValue);

int GUIAPI RemoveSectionInEtcFile (const char* pEtcFile, const char* pSection);

int GUIAPI GetValueFromEtcSec (GHANDLE hSect, 
const char* pKey, char* pValue, int iLen);

int GUIAPI GetIntValueFromEtcSec (GHANDLE hSect, 
const char* pKey, int* pValue);

int GUIAPI SetValueToEtcSec (GHANDLE hSect, 
const char* pKey, char* pValue);

int GUIAPI SaveEtcToFile (GHANDLE hEtc, const char* file_name);

GHANDLE GUIAPI FindSectionInEtc (GHANDLE hEtc, 
const char* pSection, BOOL bCreateNew);

int GUIAPI RemoveSectionInEtc (GHANDLE hEtc, const char* pSection);
```

前三个函数的用途如下：

- `GetValueFromEtcFile`：从指定的配置文件当中获取指定的键值，键值以字符串形式返回。
- `GetIntValueFromEtcFile`：从指定的配置文件当中获取指定的整数型键值。该函数将获得的字符串转换为整数值返回（采用`strtol` 函数转换）。
- `SetValueToEtcFile`：该函数将给定的键值保存到指定的配置文件当中，如果配置文件不存在，则将新建配置文件。如果给定的键已存在，则将覆盖旧值。

下面五个函数为 MiniGUI 1.6.x 版新增的配置文件读写函数，使用方法如下：

- `LoadEtcFile`：把指定的配置文件读入内存，返回一个配置对象句柄，之后相关的函数可以通过该句柄来访问内存中的配置信息。
- `UnloadEtcFile`: 释放内存中的配置文件信息。
- `GetValueFromEtc`：使用方法和 `GetValueFromEtcFile` 类似，不过它的第一个参数为配置对象句柄而不是配置文件名，使用该函数将从内存中获取配置信息。
- `GetIntValueFromEtc`：使用方法和 `GetIntValueFromEtcFile` 类似。
- `SetValueToEtc`：使用方法和 `SetValueToEtcFile` 类似，不过该函数只改变内存中的配置键值，不影响配置文件的内容。

后七个函数为 MiniGUI 2.0.4/1.6.10 版新增的配置文件读写函数，使用方法如下：

- `RemoveSectionInEtc`：从内存中的配置文件信息中删除指定的段信息。
- `RemoveSectionInEtcFile`：从指定的配置文件当中删除指定的段信息。
- `GetValueFromEtcSec`：从内存中的配置文件信息的指定段中获取指定的键值。
- `GetIntValueFromEtcSec`：从内存中的配置文件信息的指定段中获取指定的整数型键值。
- `SetValueToEtcSec`：保存键值到内存中的配置文件信息的指定段中。
- `SaveEtcToFile`：将内存中的配置文件信息保存到指定的文件中。
- `FindSectionInEtc`：在内存中的配置文件信息中查找指定的字段，如果没有指定的字段存在，当参量 `bCreateNew` 为 `TRUE` 时将新建一空字段。

这几个函数一般用于一次性读入配置文件中的全部信息。在需要一次性获取较多的配置键值的情况下，先使用 `LoadEtcFile` 读入一个配置文件，然后使用 `GetValueFromEtc` 获取键值，在不再需要访问配置信息时用 `UnloadEtcFile` 释放掉，这样做会比每次都使用 `GetValueFromEtcFile` 从文件中获取键值效率高。

假定某个配置文件记录了一些应用程序信息，并具有如下格式：

```c
[mginit]
nr=8
autostart=0

[app0]
path=../tools/
name=vcongui
layer=
tip=Virtual&console&on&MiniGUI
icon=res/konsole.gif

[app1]
path=../bomb/
name=bomb
layer=
tip=Game&of&Minesweaper
icon=res/kmines.gif

[app2]
path=../controlpanel/
name=controlpanel
layer=
tip=Control&Panel
icon=res/kcmx.gif
```

其中的 [mginit] 段记录了应用程序个数（nr 键），以及自动启动的应用程序索引（autostart 键）。而 [appX] 段记录了每个应用程序的信息，包括该应用程序的路径、名称、图标等等。__清单 1.2__ 中的代码演示了如何使用 MiniGUI 的配置文件函数获取这些信息（该代码段来自 mde 演示包中的 mginit 程序）。

__清单 1.2__ 使用 MiniGUI 的配置文件函数获取信息

```c
#define APP_INFO_FILE “mginit.rc”

static BOOL get_app_info (void)
{
        int i;
        APPITEM* item;
        
        /* 获取应用程序个数信息 */
        if (GetIntValueFromEtcFile (APP_INFO_FILE, "mginit", "nr", &app_info.nr_apps) != ETC_OK)
        return FALSE;
        
        if (app_info.nr_apps <= 0)
        return FALSE;
        
        /* 获取自动启动的应用程序索引 */
        GetIntValueFromEtcFile (APP_INFO_FILE, "mginit", "autostart", &app_info.autostart);
        
        if (app_info.autostart >= app_info.nr_apps || app_info.autostart < 0)
        app_info.autostart = 0;
        
        /* 分配应用程序信息结构 */
        if ((app_info.app_items = (APPITEM*)calloc (app_info.nr_apps, sizeof (APPITEM))) == NULL) {
                return FALSE;
        }
        /* 获取每个应用程序的路径、名称、图标等信息 */
        item = app_info.app_items;
        for (i = 0; i < app_info.nr_apps; i++, item++) {
                char section [10];
                
                sprintf (section, "app%d", i);
                if (GetValueFromEtcFile (APP_INFO_FILE, section, "path", 
                item->path, PATH_MAX) != ETC_OK)
                goto error;
                
                if (GetValueFromEtcFile (APP_INFO_FILE, section, "name", 
                item->name, NAME_MAX) != ETC_OK)
                goto error;
                
                if (GetValueFromEtcFile (APP_INFO_FILE, section, "layer", 
                item->layer, LEN_LAYER_NAME) != ETC_OK)
                goto error;
                
                if (GetValueFromEtcFile (APP_INFO_FILE, section, "tip", 
                item->tip, TIP_MAX) != ETC_OK)
                goto error;
                
                strsubchr (item->tip, '&', ' ');
                
                if (GetValueFromEtcFile (APP_INFO_FILE, section, "icon", 
                item->bmp_path, PATH_MAX + NAME_MAX) != ETC_OK)
                goto error;
                
                if (LoadBitmap (HDC_SCREEN, &item->bmp, item->bmp_path) != ERR_BMP_OK)
                goto error;
                
                item->cdpath = TRUE;
        }
        return TRUE;
        error:
        free_app_info ();
        return FALSE;
}
```

上述例子如果使用 `LoadEtcFile`、`GetValueFromEtc` 和 `UnloadEtcFile` 函数来实现的话，大概过程如下：

```c
GHANDLE hAppInfo;
HAppInfo = LoadEtcFile (APP_INFO_FILE);
//…
get_app_info ();
//…
UnloadEtcFile (hAppInfo);
```

当然，需要把 `get_app_info` 函数中的 `GetValueFromEtcFile` 改为 `GetValueFromEtc`。

## 1.4 编写可移植程序

我们知道，许多嵌入式系统所使用的 CPU 具有和普通台式机 CPU 完全不同的构造和特点。但有了操作系统和高级语言，可以最大程度上将这些不同隐藏起来。只要利用高级语言编程，编译器和操作系统能够帮助程序员解决许多和 CPU 构造及特点相关的问题，从而节省程序开发时间，并提高程序开发效率。然而某些 CPU 特点却是应用程序开发人员所必须面对的，这其中就有如下几个需要特别注意的方面：

- 字节顺序。一般情况下，我们接触到的 CPU 在存放多字节的整数数据时，将低位字节存放在低地址单元中，比如常见的 Intel x86 系列 CPU。而某些 CPU 采用相反的字节顺序。比如在嵌入式系统中使用较为广泛的 PowerPC 就将低位字节存放在高地址单元中。前者叫 Little Endian 系统；而后者叫 Big Endian 系统。
- 在某些平台上的 Linux 内核，可能缺少某些高级系统调用，最常见的就是与虚拟内存机制相关的系统调用。在某些 CPU 上运行的 Linux 操作系统，因为 CPU 能力的限制，无法提供虚拟内存机制，基于虚拟内存实现的某些 IPC 机制就无法正常工作。比如在某些缺少 MMU 单元的 CPU 上，就无法提供 System V IPC 机制中的共享内存。

为了编写具有最广泛适应性的可移植代码，应用程序开发人员必须注意到这些不同，并且根据情况编写可移植代码。这里，我们将描述如何在 MiniGUI 应用程序中编写可移植代码。

### 1.4.1 理解并使用 MiniGUI 的 Endian 读写函数

为了解决上述的第一个问题，MiniGUI 提供了若干 Endian 相关的读写函数。这些函数可以划分为如下两类：

- 用来交换字节序的函数。包括 `ArchSwapLE16`、`ArchSwapBE16`  等。
- 用来读写标准 I/O 流的函数。包括 `MGUI_ReadLE16`、`MGUI_ReadBE16` 等。

前一类用来将某个 16 位、32 位或者 64 位整数从某个特定的字节序转换为系统私有（native）字节序。举例如下：

```c
int fd, len_header;

...

if (read (fd, &len_header, sizeof (int)) == -1)
goto error;
#if MGUI_BYTEORDER == MGUI_BIG_ENDIAN
len_header = ArchSwap32 (len_header);    // 如果是 Big Endian 系统，则转换字节序
#endif
...
```

在上面的程序段中，首先通过 `read` 系统调用从指定的文件描述符中读取一个整数值到 `len_header` 变量中。该文件中保存的整数值是 Little Endian 的，因此如果在 Big Endian 系统上使用这个整数值，就必须进行字节顺序交换。这里可以使用 `ArchSwapLE32`，将 Little Endian 的 32 位整数值转换为系统私有的字节序。也可以如上述程序段那样，只对 Big Endian 系统进行字节序转换，这时，只要利用 `ArchSwap32` 函数即可。

MiniGUI 提供的用来转换字节序的函数（或者宏）如下：

- `ArchSwapLE16(X)` 将指定的以 Little Endian 字节序存放的 16 位整数值转换为系统私有整数值。如果系统本身是 Little Endian 系统，则该函数不作任何工作，直接返回 X；如果系统本身是 Big Endian 系统，则调用 `ArchSwap16` 函数交换字节序。
- `ArchSwapLE32(X)` 将指定的以 Little Endian 字节序存放的 32 位整数值转换为系统私有整数值。如果系统本身是 Little Endian 系统，则该函数不作任何工作，直接返回 X；如果系统本身是 Big Endian 系统，则调用 `ArchSwap32` 函数交换字节序。
- `ArchSwapBE16(X)` 将指定的以 Big Endian 字节序存放的 16 位整数值转换为系统私有整数值。如果系统本身是 Big Endian 系统，则该函数不作任何工作，直接返回 X；如果系统本身是 Little Endian 系统，则调用 `ArchSwap16` 函数交换字节序。
- `ArchSwapBE32(X)` 将指定的以 Big Endian 字节序存放的 32 位整数值转换为系统私有整数值。如果系统本身是 Big Endian 系统，则该函数不作任何工作，直接返回 X；如果系统本身是 Little Endian 系统，则调用 `ArchSwap32` 函数交换字节序。

MiniGUI 提供的第二类函数用来从标准 I/O 的文件对象中读写 Endian 整数值。如果要读取的文件是以 Little Endian 字节序存放的，则可以使用 `MGUI_ReadLE16` 和 `MGUI_ReadLE32` 等函数读取整数值，这些函数将把读入的整数值转换为系统私有字节序，反之使用 `MGUI_ReadBE16` 和 `MGUI_ReadBE32` 函数。如果要写入的文件是以 Little Endian 字节序存放的，则可以使用 `MGUI_WriteLE16` 和 `MGUI_WriteLE32` 等函数写入整数值，这些函数将把要写入的整数值从系统私有字节序转换为 Little Endian 字节序，然后写入文件，反之使用 `MGUI_WriteBE16` 和 `MGUI_WriteBE32` 函数。下面的代码段说明了上述函数的用法：

```c
FILE* out;
int count;
...
MGUI_WriteLE32 (out, count);  // 以 Little Endian 字节序保存 count 到文件中。
...
```

### 1.4.2 利用条件编译编写可移植代码

在涉及到可移植性问题的时候，有时我们能够方便地通过 4.1 中描述的方法进行函数封装，从而提供具有良好移植性的代码，但有时我们无法通过函数封装的方法提供可移植性代码。这时，恐怕只能使用条件编译了。__清单 1.3__ 中的代码说明了如何使用条件编译的方法确保程序正常工作（该代码来自 MiniGUI `src/kernel/sharedres.c`）。

__清单 1.3__ 条件编译的使用

```c
/* 如果系统不支持共享内存，则定义 _USE_MMAP
#undef  _USE_MMAP 
/* #define _USE_MMAP 1 */

void *LoadSharedResource (void)
{
        #ifndef _USE_MMAP
        key_t shm_key;
        void *memptr;
        int shmid;
        #endif
        
        /* 装载共享资源 */
        ...
        
        #ifndef _USE_MMAP /* 获取共享内存对象 */
        if ((shm_key = get_shm_key ()) == -1) {
                goto error;
        }
        shmid = shmget (shm_key, mgSizeRes, SHM_PARAM | IPC_CREAT | IPC_EXCL); 
        if (shmid == -1) { 
                goto error;
        } 
        
        // Attach to the share memory. 
        memptr = shmat (shmid, 0, 0);
        if (memptr == (char*)-1) 
        goto error;
        else {
                memcpy (memptr, mgSharedRes, mgSizeRes);
                free (mgSharedRes);
        }
        
        if (shmctl (shmid, IPC_RMID, NULL) < 0) 
        goto error;
        #endif
        
        /* 打开文件 */
        if ((lockfd = open (LOCKFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        goto error;
        
        #ifdef _USE_MMAP
        /* 如果使用 mmap，就将共享资源写入文件 */
        if (write (lockfd, mgSharedRes, mgSizeRes) < mgSizeRes)
        goto error;
        else
        {
                free(mgSharedRes);
                mgSharedRes = mmap( 0, mgSizeRes, PROT_READ|PROT_WRITE, MAP_SHARED, lockfd, 0);
        }
        #else
        /* 否则将共享内存对象 ID 写入文件 */
        if (write (lockfd, &shmid, sizeof (shmid)) < sizeof (shmid))
        goto error;
        #endif
        
        close (lockfd);
        
        #ifndef _USE_MMAP
        mgSharedRes = memptr;
        SHAREDRES_SHMID = shmid;
        #endif
        SHAREDRES_SEMID = semid;
        
        return mgSharedRes; 
        
        error:
        perror ("LoadSharedResource"); 
        return NULL;
}
```

上述程序段是 MiniGUI-Processes 服务器程序用来装载共享资源的。如果系统支持共享内存，则初始化共享内存对象，并将装载的共享资源关联到共享内存对象，然后将共享内存对象 ID 写入文件；如果系统不支持共享内存，则将初始化后的共享资源全部写入文件。在客户端，如果支持共享内存，则可以从文件中获得共享内存对象 ID，并直接关联到共享内存；如果不支持共享内存，则可以使用 mmap 系统调用，将文件映射到进程的地址空间。客户端的代码段见__清单 1.4__。

__清单 1.4__ 条件编译的使用（续）

```c
void* AttachSharedResource (void)
{
        #ifndef _USE_MMAP
        int shmid;
        #endif
        int lockfd;
        void* memptr;
        
        if ((lockfd = open (LOCKFILE, O_RDONLY)) == -1)
        goto error;
        
        #ifdef _USE_MMAP
        /* 使用 mmap 将共享资源映射到进程地址空间 */
        mgSizeRes = lseek (lockfd, 0, SEEK_END );
        memptr = mmap( 0, mgSizeRes, PROT_READ, MAP_SHARED, lockfd, 0);
        #else
        /* 否则获取共享内存对象 ID，并关联该共享内存 */
        if (read (lockfd, &shmid, sizeof (shmid)) < sizeof (shmid))
        goto error;
        close (lockfd);
        
        
        memptr = shmat (shmid, 0, SHM_RDONLY);
        #endif
        if (memptr == (char*)-1) 
        goto error;
        return memptr;
        
        error:
        perror ("AttachSharedResource"); 
        return NULL;
}
```

## 1.5 定点数运算

通常在进行数学运算时，我们采用浮点数表示实数，并利用 <math.h> 头文件中所声明的函数进行浮点数运算。我们知道，浮点数运算是一种非常耗时的运算过程。为了减少因为浮点数运算而带来的额外 CPU 指令，在一些三维图形库当中，通常会采用定点数来表示实数，并利用定点数进行运算，这样，将大大提高三维图形的运算速度。MiniGUI 也提供了一些定点数运算函数，分为如下几类：

- 整数、浮点数和定点数之间的转换。利用 `itofix` 和 `fixtoi` 函数可实现整数和定点数之间的相互转换；利用 `ftofix` 和 `fixtof` 函数可实现浮点数和定点数之间的转换。
- 定点数加、减、乘、除等基本运算。利用 `fixadd`、`fixsub`、`fixmul`、`fixdiv`、`fixsqrt` 等函数可实现定点数加、减、乘、除以及平方根运算。
- 定点数的三角运算。利用 `fixcos`、`fixsin`、`fixtan`、`fixacos`、`fixasin` 等函数可求给定定点数的余弦、正弦、正切、反余弦、反正弦值。
- 矩阵、向量等运算。矩阵、向量相关运算在三维图形中非常重要，限于篇幅，本文不会详细讲述这些运算，读者可参阅 MiniGUI 的 <minigui/fixedmath.h> 头文件。

__清单 1.5__ 中的代码段演示了定点数的用法，该程序段将输入的平面直角坐标系的坐标转换成相对应的屏幕坐标。

__清单 1.5__ 定点数运算

```c
void scale_to_window (const double * in_x, const double * in_y, double * out_x, double * out_y)
{
        fixed  f_x0 = ftofix (get_x0());
        fixed  f_y0 = ftofix (get_y0());
        fixed  f_in_x = ftofix (*in_x);
        fixed  f_in_y = ftofix (*in_y);
        fixed  f_p = ftofix (get_pixel_length());
        
        *out_x = fixtof(fixmul(fixsub(f_in_x, f_x0), f_p));
        *out_y = -fixtof(fixmul(fixsub(f_in_y, f_y0), f_p));
}
```

上述程序的计算非常简单，步骤如下：

- 先将输入值转换成定点数。
- 再将数值减去屏幕边界的定点数，乘以比例尺。
- 最后，将运算结果转换成浮点数。
