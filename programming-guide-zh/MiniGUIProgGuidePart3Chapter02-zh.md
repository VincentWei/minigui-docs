# 开发定制的 MiniGUI-Processes 服务器程序

`mginit` 是 MiniGUI-Processes 的服务器程序，该程序为客户应用程序准备共享资源，并管理客户创建的窗口。本章将讲述如何根据项目需求编写定制的 MiniGUI-Processes 服务器程序，并首先以 `mg-samples` 的 `mginit` 程序为例，分析 `mginit` 程序的基本组成要素。

## 1.1 `mg-samples` 中 `mginit` 程序

`mg-samples` 中的 `mginit` 程序结构比较简单，该程序主要完成的工作如下：

- 初始化 MiniGUI-Processes 的服务器功能。
- 显示两个版权信息对话框。
- 读取 `mginit.rc` 配置文件，并创建任务栏。
- 启动由 `mginit.rc` 文件指定的默认启动程序。
- 在任务栏窗口过程中，维护 MiniGUI-Processes 层的信息，并负责在层之间的切换。

接下来我们详细分析这个 `mginit` 程序的功能实现。

### 1.1.1 初始化 MiniGUI-Processes 的服务器功能

该段代码位于 `MiniGUIMain` 函数中，如下所示：

```c
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
首先，该函数初始化了 `OnNewDelClient` 和 `OnChangeLayer` 两个 `mginit` 服务器程序特有的全局变量。之后，该函数调用 `ServerStartup` 函数启动 `mginit` 的服务器功能。`ServerStartup` 函数将创建监听套接字，并准备接受来自客户的连接请求。到此为止，`mg-samples` 的 `mginit` 程序所做的初始化服务器工作就完成了。下面我们具体分析上述过程。

1. 监视来自客户和层的事件

`OnNewDelClient` 和 `OnChangeLayer` 这两个全局变量是 MiniGUI-Processes 服务器程序所特有的，是两个函数指针变量。当客户连接到 `mginit` 或者断开与 `mginit` 之间的套接字连接时，如果程序设置了 `OnNewDelClient` 这个变量，将调用这个变量指向的函数。在 `minigui/minigui.h` 中，这个函数的类型声明如下：

```c
typedef void (* ON_NEW_DEL_CLIENT) (int op, int cli);
```
第一个参数表示要进行的操作，取 `LCO_NEW_CLIENT` 表示有新客户连接到服务器；取 `LCO_DEL_CLIENT` 表示有客户断开了连接。第二个参数 `cli` 表示的是客户的标识号，是个整数。

当 MiniGUI-Processes 的层发生变化时，比如有新客户加入到某个层，如果程序设置了 `OnChangeLayer` 这个变量，则会调用这个变量指向的函数。在 `minigui/minigui.h` 中，这个函数的类型声明如下：

```c
typedef void (* ON_CHANGE_LAYER) (int op, MG_Layer* layer, MG_Client* client);
```

第一个参数表示事件类型：

- `LCO_NEW_LAYER`：系统创建了新的层。
- `LCO_DEL_LAYER`：系统删除了一个层。
- `LCO_JOIN_CLIENT`：某个层中加入了一个客户。
- `LCO_REMOVE_CLIENT`：某个客户从所在的层中删除。
- `LCO_TOPMOST_CHANGED`：最上面的层改变了，即发生了层的切换。

第二个参数是指向发生事件的层的指针，第三个参数是发生事件的客户指针。

全局变量 `OnZNodeOperation` 是 MiniGUI V2.0.4/V1.6.10版本新增的 UI-Processes 服务器程序所特有的函数指针变量。当 MiniGUI-Processes 的 Z 序节点改变时，如果程序设置了  `OnZNodeOperation` 这个变量，则会调用这个变量指向的函数。在 `minigui/minigui.h` 中，这个函数的类型声明如下： 

```c
typedef void (* ON_ZNODE_OPERATION) (int op, int cli, int idx_znode);
ON_ZNODE_OPERATION OnZNodeOperation;
```

第一个参数表示事件类型：

- `ZNOP_ALLOCATE`：`z-node` 被创建；
- `ZNOP_FREE`：`z-node` 被销毁；
- `ZNOP_MOVE2TOP`：`z-node` 被移为 `TopMost` 结点；
- `ZNOP_SHOW`：`z-node` 已被显示；
- `ZNOP_HIDE`： `z-node` 已被隐藏；
- `ZNOP_MOVEWIN`： `z-node` 已被移动或其大小已改变；
- `ZNOP_SETACTIVE`： `z-node` 已被设置为活动态；.
- `ZNOP_ENABLEWINDOW`： `z-node`被 `disabled` 或 `enabled`；
- `ZNOP_STARTDRAG`：开始对 `z-node` 的拖拽；
- `ZNOP_CANCELDRAG`：取消对 `z-node` 的拖拽；
- `ZNOP_CHANGECAPTION`：`z-node` 的名称已改变。

第二个参数 `cli` 表示的是客户的标识号，是个整数。第三个参数 `idx_znode` 表示的是结点的z序索引。

`OnLockClientReq`，`OnTrylockClientReq` 和 `OnUnlockClientReq` 这三个全局变量是 MiniGUI-Processes 客户端程序所特有的，是三个函数指针变量。这三个函数指针的使用可以避免在同一客户端进程中当多线程对客户端连接 socket 进行访问时可能导致的死锁问题。在 `minigui/minigui.h` 中，这个函数的类型声明如下：

```c
typedef int (* ON_LOCK_CLIENT_REQ) (void);
ON_LOCK_CLIENT_REQ  OnLockClientReq;

typedef int (* ON_TRYLOCK_CLIENT_REQ) (void);
ON_TRYLOCK_CLIENT_REQ  OnTrylockClientReq;

typedef int (* ON_TRYLOCK_CLIENT_REQ) (void);
ON_UNLOCK_CLIENT_REQ  OnUnlockClientReq;
```

有了客户标识号或者层的指针、客户指针，`mginit` 程序就可以方便地访问 MiniGUI 函数库中的内部数据结构，从而获得一些系统信息。为此，MiniGUI 定义了如下一些全局变量：

- `mgClients`：是个 `MG_Client` 型的结构指针，指向包含所有客户信息的 `MG_Client` 结构数组。可以通过客户标识符访问。
- `mgTopmostLayer`：是个 `MG_Layer` 型的结构指针，指向当前最上面的层。
- `mgLayers`：是个 `MG_Layer` 型的结构指针，指向系统中所有层的链表头。

`mginit` 程序可以在任何时候访问这些数据结构而获得当前的客户以及当前层的所有信息。关于 `MG_Client` 结构和 `MG_Layer` 结构的成员信息，可参阅《MiniGUI API Reference Manual》。

`mginit` 程序定义了处理上述事件的两个函数，并设置了上面提到的两个全局变量。

第一个函数是 `on_new_del_client` 函数，这个函数没有进行实质性的工作，而只是简单打印了新连接和断开的客户程序名称。

第二个函数是 `on_change_layer` 函数，这个函数主要处理了 `LCO_NEW_LAYER、LCO_DEL_LAYER` 和 `LCO_TOPMOST_CHANGED` 事件。在系统创建新的层时，这个函数在任务栏上新建一个按钮，并将该按钮的句柄赋值给当前层的 `dwAddData` 成员；在系统删除某个层时，这个函数销毁了对应该层的按钮；在系统最上面的层发生变化时，该函数调用 `on_change_topmost` 函数调整这些代表层的按钮的状态。该函数的代码如下：

```c
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
                        
                        if (new_width != box_width) {
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
                        if (nr_boxes != 0)
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

2. `ServerStartup` 函数

该函数对服务器也就是 `mginit` 进行初始化。它创建共享资源、耳机插口、默认层和其他内部对象。定制化的 `mginit` 程序应该在调用其他任何函数之前调用此函数。注意，服务器创建的默认层被命名为 `mgint`（`NAME_DEF_LAYER`）。此函数的原型为：

```c
BOOL GUIAPI ServerStartup (int nr_globals,
int def_nr_topmosts, int def_nr_normals);
```

可以给此函数传递一些参数来控制窗口管理的限定：

- `nr_globals`：全局Z序节点的数量。所有由 `mginit` 创建的Z序节点都是全局对象。
- `def_nr_topmosts`：缺省顶层Z序节点的最大数。它也是新层时的缺省顶层Z序节点的默认数。
- `def_nr_normals`：新层普通Z序节点的最大数。它也是新层普通Z序节点的默认数。

### 1.1.2 创建任务栏

上面已经提到，这个 `mginit` 程序使用任务栏以及其中的按钮表示当前系统中的层，并提供了一个简单的用户接口（见图 1.1）：

- 用户选择任务栏上的工具栏图标，就可以启动某个应用程序。
- 用户点击任务栏上的按钮，就可以将这个按钮代表的层切换到最上面显示。

![mg-samples 的 mginit 程序建立的任务栏](figures/Part3Chapter02-1.1.jpeg)
<center> 图 17.1 `mg-samples` 的 `mginit` 程序建立的任务栏

这个任务栏使用酷工具栏（CoolBar）控件建立用来启动应用程序的工具栏。它读取了 `mginit.rc` 文件中的应用程序配置信息并初始化了这些应用程序的信息，包括应用程序名称、描述字符串、对应的程序图标等等。

任务栏还建立了一个定时器以及一个静态框控件，该控件显示当前时间，每秒刷新一次。

因为这些代码并不是 `mginit` 程序所特有的，所以不再赘述。

### 1.1.4 启动默认程序

`mginit.rc` 文件中定义了一个初始要启动的应用程序，下面的代码启动了这个应用程序：

```c
pid_desktop = exec_app (app_info.autostart);

if (pid_desktop == 0 || waitpid (pid_desktop, &status, WNOHANG) > 0) {
        fprintf (stderr, "Desktop already have terminated.\n");
        Usage ();
        return 1;
}
```

然后，`mg-samples` 的 `mginit` 程序捕获了 `SIGCHLD` 信号，以免在子进程退出时因为没有进程获取其退出状态而形成僵尸进程：

```c
siga.sa_handler = child_wait;
siga.sa_flags  = 0;
memset (&siga.sa_mask, 0, sizeof(sigset_t));
sigaction (SIGCHLD, &siga, NULL);
```

用来启动客户应用程序的 `exec_app` 函数非常简单，它调用了 `vfork` 和 `execl` 系统调用启动客户：

```c
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

### 1.1.5 进入消息循环

接下来，这个 `mginit` 程序进入了消息循环：


```c
while (GetMessage (&msg, hTaskBar)) {
        DispatchMessage (&msg);
}
```

当任务栏退出时，将终止消息循环，最终退出 MiniGUI-Processes 系统。

## 1.2 最简单的 `mginit` 程序

`mg-samples` 的 `mginit` 程序其实并不复杂，它演示了一个 MiniGUI-Processes 服务器程序的基本构造方法。本节我们将构建一个最简单的 `mginit` 程序，这个程序的功能非常简单，它初始化了 MiniGUI-Processes，然后启动了 `helloworld` 程序。该程序还演示了服务器事件钩子函数的使用，当用户按 F1 到 F4 的按键时，将启动其他一些客户程序，用户在长时间没有操作时，`mginit` 会启动一个屏幕保护程序。当用户关闭所有的客户程序时，`mginit` 程序退出。__清单 1.1__ 给出了这个 `mginit` 程序的代码，其完整源代码以及屏幕保护程序的代码可见本指南示例程序包 `mg-samples` 中 `src` 目录的 `mginit.c` 和 `scrnsaver.c` 文件。

__清单 1.1__ 简单 `mginit` 程序的源代码

```c
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

这个程序设置了 `mginit` 的 `OnNewDelClient` 事件处理函数，并在产生 `LCO_DEL_CLIENT` 时将全局变量 `quit` 设置为 `TRUE`，从而导致 `mginit` 的消息循环终止，最终退出系统。
该程序可使用如下命令行编译：

```c
$ gcc –o mginit mginit.c –lminigui
```
因为这个 `mginit` 程序启动时要启动 `helloworld` 客户程序，所以，必须确保当前目录下存在 `helloworld` 程序。


## 1.3 MiniGUI-Processes 客户端专用函数

众所周知，MiniGUI-Processes 在调用 MiniGUI 的其它函数之前先调用 `JoinLayer` 用于将自己添加到一个层中。除了 `JoinLayer`，客户可以调用其他函数来得到层的消息，删除层或是改变顶层。

在调用其他 MiniGUI 函数之前，客户应该调用 `JoinLayer` 函数。该函数的原型如下：

```c
GHANDLE GUIAPI JoinLayer (const char* layer_name,
const char* client_name, 
int max_nr_topmosts, int max_nr_normals);
```

参数 `layer_name` 指定所要添加到的层的名字，如果所提供的层的名称不存在，服务器会根据该名称创建一个新的层。如果你给 `layer_name` 传递了一个 `NULL` 指针或是一个空字符串，表示加入到当前活跃的层中。如果客户想创建一个新层，应该指定创建新层时的最大顶层窗口数（`max_nr_topmosts`），以及最大普通窗口数（`max_nr_normals`）。如果给 `max_nr_topmosts` 和 `max_nr_normals` 传递零值，将使用默认值。注意，默认值由 `ServerStartup` 函数设定。

通过 `GetLayerInfo` 函数可以得到层的信息。该函数的原型如下：

```c
GHANDLE GUIAPI GetLayerInfo (const char* layer_name,
int* nr_clients, BOOL* is_topmost, int* cli_active);
```

如果指定的指针不为 `NULL`，那么通过该指针将返回层的信息。层的信息分别包括，层中客户的数量、层是否为顶层、客户标识符（哪个客户的窗口是当前活动窗口）。

客户调用 `SetTopmostLayer` 函数将指定的层设置为最顶层，调用 `DeleteLayer` 来删除层。关于这些功能的详细信息，可以参阅《MiniGUI API Reference Manual》。

## 1.4 `Mginit` 专用的其他函数和接口

除了上面介绍的 `ServerStartup`、`OnNewDelClient`、`mgClients` 等函数和变量之外，MiniGUI-Processes 还为 `mginit` 程序定义了若干接口，专用于 MiniGUI-Processes 的服务器程序。本节将简单总结这些接口，详细信息请参阅《MiniGUI API Reference》。

- `ServerSetTopmostLayer`：该函数将把指定的层切换到最上面。
- `ServerCreateLayer`：该函数将在系统中创建指定的层。
- `ServerDeleteLayer`：该函数从系统中删除指定的层。
- `GetClientByPID`：该函数根据客户的进程标识号返回客户标识号。
- `SetTopmostClient`：该函数通过指定的客户标识号来设置顶层。它将把客户所在的层切换到最上面。
- `SetServerEventHook`：该函数在 `mginit` 中设置底层事件的钩子，在钩子函数返回零给 MiniGUI 时，MiniGUI 将继续事件的处理，并最终将事件发送到当前活动客户；反之将终止事件的处理。
- `Send2Client`：服务器可利用该消息将指定的消息发送到某个客户。
- `ServerGetNextZNode`：该函数用于遍历所有的 Z 序节点。
- `ServerGetZNodeInfo`：该函数用于获得某个特定 Z 序节点的信息。
- `ServerDoZNodeOperation`：该函数用于完成切换主窗口 Z 序和/或设置某主窗口为当前活动窗口。

