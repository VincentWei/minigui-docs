![](media/image1.jpeg){width="2.234027777777778in"
height="1.3743055555555554in"}

MiniGUI for ThreadX

移植指南[[]{#_Toc93915436 .anchor}]{#_Toc93915400 .anchor}

目 录

[*1. 前提* 1](#_Toc95185263)

[*1.1 用户要求* 1](#_Toc95185264)

[*1.2 移植环境* 1](#_Toc95185265)

[*1.3 相关文档* 1](#_Toc95185266)

[*2. MiniGUI与ThreadX* 1](#_Toc95185267)

[*3. 移植* 3](#_Toc95185268)

[*3.1 获取MiniGUI源码* 3](#_Toc95185269)

[*3.2 errno定义* 4](#_Toc95185270)

[*3.3 posix线程实现* 5](#_Toc95185271)

[*3.4 内存管理和相关I/O接口* 7](#_Toc95185272)

[*3.5 图形和输入引擎* 8](#_Toc95185273)

[*3.6 ThreadX下启动MiniGUI的入口* 10](#_Toc95185274)

[*4. ADS1.2中编译MiniGUI库* 10](#_Toc95185275)

[*4.1 ADS1.2中MiniGUI库工程的建立* 10](#_Toc95185276)

[*4.2 基于ThreadX编译MiniGUI应用程序* 12](#_Toc95185277)

[*4.3 可执行映象下载到RAM中的调试* 13](#_Toc95185278)

[*4.4 可执行映象下载到Flash中调试* 13](#_Toc95185279)

[]{#_Toc95185263 .anchor}1. 前提

[]{#_Toc95185264 .anchor}1.1 用户要求

在进行移植前要求用户有以下知识基础：

1)  掌握在ARM ADS1.2集成开发环境中如何编写程序和进行工程设置。

2)  掌握ARM ADS1.2的编译过程。

3)  掌握ADS编译器相关术语的含义。

4)  了解ThreadX操作系统的核心概念和主要接口的用法。

5)  了解MiniGUI的基本原理和应用程序的编写。

6)  了解posix线程接口功能。

[]{#_Toc95185265 .anchor}1.2 移植环境

硬件：VisualFone ANVIL开发板，Trace32调试器，PC机

操作系统：

> 目标机：ThreadX
>
> 宿主机：Windows XP

软件：ADS1.2 , Trace32 ICD ARM Podpar , MiniGUI

[]{#_Toc95185266 .anchor}1.3 相关文档

MiniGUI for ThreadX详细设计

MiniGUI编程指南

[]{#_Toc95185267 .anchor}2. MiniGUI与ThreadX

MiniGUI
软件架构的设计充分考虑了可移植性，核心的主要结构包括消息处理、窗口管理和图形绘制等主要模块都是建立在得到广泛支持的POSIX线程库接口的基础之上；其次，MiniGUI通过操作系统和硬件抽象层（porting
layer）隐藏了特定操作系统及底层硬件的细节，这大大减轻了MiniGUI移植到不同操作系统和硬件平台的工作量。

ThreadX操作系统是一实时操作系统，它提供了一套自己的线程接口供用户使用，但对标准posix线程接口部分中的线程局部存储（Thread-specific
Data）和线程属性等部分不支持，具体接口对照可参见下表1。

  ----------------------------------------------------------------------------------------------- ---------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **ThreadX**                                                                                     **POSIX Thread**                         **实现方法**

  N/A                                                                                             pthread\_attr\_init                      自定义 pthread\_attr\_t 类型（结构）实现相关接口。pthread\_attr\_t 接口中的参数，将控制通过 pthread\_create 函数创建的 ThreadX 任务的相关属性。
                                                                                                                                           
                                                                                                  pthread\_attr\_destroy                   本实现还需定义 struct sched\_param 结构，用来定义 ThreadX 操作系统任务的调度参数（抢占阈值、优先级、时间片）。
                                                                                                                                           
                                                                                                  pthread\_attr\_setstackaddr              ThreadX 仅支持 FIFO 调度策略，因此 不必实现 pthread\_attr\_setinheritsched、pthread\_attr\_getinheritsched、pthread\_attr\_setschedpolicy 和pthread\_attr\_getschedpolicy 接口。
                                                                                                                                           
                                                                                                  pthread\_attr\_getstackaddr              
                                                                                                                                           
                                                                                                  pthread\_attr\_setstacksize              
                                                                                                                                           
                                                                                                  pthread\_attr\_getstacksize              
                                                                                                                                           
                                                                                                  pthread\_attr\_setdetachstate            
                                                                                                                                           
                                                                                                  pthread\_attr\_getdetachstate            
                                                                                                                                           
                                                                                                  pthread\_attr\_setschedparam             
                                                                                                                                           
                                                                                                  pthread\_attr\_getschedparam             

  tx\_thread\_create                                                                              pthread\_create                          根据线程属性的定义，创建底层操作系统任务。

  tx\_thread\_terminate                                                                           pthread\_exit                            

  N/A                                                                                             pthread\_self                            线程管理函数，无对应底层服务，需自行实现。
                                                                                                                                           
                                                                                                  pthread\_equal                           
                                                                                                                                           
                                                                                                  pthread\_join                            
                                                                                                                                           
                                                                                                  pthread\_detach                          

  tx\_thread\_preemption\_change, tx\_thread\_priority\_change, tx\_thread\_time\_slice\_change   pthread\_setschedparam                   运行中修改任务的调度参数（ 抢占阈值、优先级、时间片 ）。通过调用相关操作系统服务完成。
                                                                                                                                           
                                                                                                  pthread\_getschedparam                   

  N/A                                                                                             pthread\_once                            一次执行函数，无对应操作系统服务，需自行实现。

  N/A                                                                                             pthread\_key\_create                     线程局部存储，无对应操作系统服务，需自行实现。
                                                                                                                                           
                                                                                                  pthread\_key\_delete                     
                                                                                                                                           
                                                                                                  pthread\_setspecific                     
                                                                                                                                           
                                                                                                  pthread\_getspecific                     

  N/A                                                                                             pthread\_setcancelstate                  线程取消相关函数，无对应操作系统服务，需自行实现。
                                                                                                                                           
                                                                                                  pthread\_setcanceltype                   
                                                                                                                                           
                                                                                                  pthread\_cancel                          
                                                                                                                                           
                                                                                                  pthread\_testcancel                      
                                                                                                                                           
                                                                                                  pthread\_cleanup\_push                   
                                                                                                                                           
                                                                                                  pthread\_cleanup\_pop                    

  N/A                                                                                             pthread\_mutexattr\_init                 pthread\_mutexattr\_t 类型自行定义。
                                                                                                                                           
                                                                                                  pthread\_mutexattr\_destroy              互斥锁属性。ThreadX 上的 PThread 互斥锁，只能是递归锁，可控制属性仅包括是否继承优先级。
                                                                                                                                           
                                                                                                  pthread\_mutexattr\_setpriorityinherit   
                                                                                                                                           
                                                                                                  pthread\_mutexattr\_getpriorityinherit   

  tx\_mutex\_create                                                                               pthread\_mutex\_init                     pthread\_mutex\_t 结构类型定义由与TX\_MUTEX结构相同的一变量 和名字段两部分组成。
                                                                                                                                           
                                                                                                                                           PThread 互斥锁接口可和相应的 ThreadX 互斥锁接口一一对应实现。

  tx\_mutex\_get                                                                                  pthread\_mutex\_lock                     

  tx\_mutex\_get                                                                                  pthread\_mutex\_trylock                  

  tx\_mutex\_put                                                                                  pthread\_mutex\_unlock                   

  tx\_mutex\_delete                                                                               pthread\_mutex\_destroy                  

  tx\_semaphore\_create                                                                           sem\_init                                sem\_t 结构类型定义为由与TX\_SEMAPHORE结构相同的一变量 和名字段两部分组成。
                                                                                                                                           
                                                                                                                                           PThread 信号量接口可和相应的 ThreadX 信号量接口一一对应实现。
                                                                                                                                           
                                                                                                                                           不实现命名信号量相关接口（sem\_open和sem\_close）

  tx\_semaphore\_put                                                                              sem\_post                                

  tx\_semaphore\_get                                                                              sem\_wait                                

  tx\_semaphore\_get                                                                              sem\_trywait                             

  tx\_semaphore\_delete                                                                           sem\_destroy                             

  tx\_semaphore\_info\_get                                                                        sem\_getvalue                            
  ----------------------------------------------------------------------------------------------- ---------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

表1

又ThreadX中无errno的定义，所以MiniGUI到ThreadX的移植工作主要有下面几点：

1.  自定义errno。

2.  线程接口部分，除条件变量部分外均需实现。实现方法在表1中已经列出。

3.  内存管理和I/O相关接口部分。因ThreadX对malloc/free和printf/fprintf/sprintf等函数接口不支持。

4.  图形引擎和输入引擎部分。针对硬件平台设计相应的引擎。

[]{#_Toc95185268 .anchor}3. 移植

[]{#_Toc95185269 .anchor}3.1 获取MiniGUI源码

1）在Windows下打开相应宏定义：

拷贝minigui03/build/config-ucosii-s3c2410-1.h至minigui03目录，并改名为config.h。在此文件中添加如下语句：

/\* Define if compile for ThreadX \*/

\#define \_\_THREADX\_\_ 1

/\* Define for target VisualFone ANVIL1.1 \*/

\#define \_\_TARGET\_VFANVIL\_\_ 1

//

\#define \_VFANVIL\_IAL 1

2）config.h中主要配置选项说明：

使用auto输入引擎。Auto引擎在没有键盘等输入设备时可以用来模拟键盘和鼠标的输入，该引擎自动地产生键盘和鼠标的输入事件，在移植或测试时非常有用。如果在release版本使用键盘或触摸屏作为输入设备，就可以把该支持去掉。

/\* Define if include the automatic IAL engine \*/

\#define \_AUTO\_IAL 1

使用dummy输入引擎。该引擎什么也不干，在没有其它引擎时，使用该引擎可以使MiniGUI正常运作和显示，但是没有输入，主要用于移植和测试。

/\* Define if include the dummy IAL engine \*/

\#define \_DUMMY\_IAL 1

内嵌式资源支持。

/\* Define if build MiniGUI with incore resources \*/

\#define \_INCORE\_RES 1

GB2312中文字符集支持。如果要使用中文的话，必须打开该选项。

/\* Define if support GB2312 charset \*/

\#define \_GB\_SUPPORT 1

下面分别是英文16点阵、中文12和16点阵字体（宋体）的支持，如果要使用某种字体，必须把对应的选项打开。英文12点阵字体的支持是默认的，不用配置。要注意的是，使用中文字体时，还必须打开
\_GB\_SUPPORT 中文支持选项。

\#define \_INCORERBF\_LATIN1\_16 1

\#define \_INCORERBF\_GB12 1

\#define \_INCORERBF\_GB16 1

RBF字体支持，必须打开。上述字体都是RBF字体。

\#define \_RBF\_SUPPORT 1

内存管理函数malloc等的支持。必须打开该选项。

/\* Define if use own implementation of malloc functions \*/

\#define \_USE\_OWN\_MALLOC 1

I/O函数支持。

/\* Define if use own implementation of stdio functions \*/

\#define \_USE\_OWN\_STDIO 1

ThreadX操作系统必须打开该选项。

/\* Define if compile for non-Linux like ThreadX \*/

\#define \_\_NOLINUX\_\_ 1

ThreadX操作系统必须打开该选项。

/\* Define if compile for ThreadX\*/

\#define \_\_THREADX\_\_ 1

ANVIL开发板需打开该选项。

/\* Define for target VisualFone ANVIL1.1 \*/

\#define \_\_TARGET\_VFANVIL 1

针对ADS编译器的选项，使用ADS编译器时必须打开。

\#define inline \_\_inline

针对ADS编译器若有locale.h，需打开此项。

/\* Define to 1 if you have &lt;locale.h&gt; header file. \*/

\#define HAVE\_LOCALE\_H 1

使用minigui\_entry入口时，需打开此项。

\#define \_USE\_MINIGUIENTRY 1

针对256色彩屏的选项：

使用newgal图形引擎。Newgal图形引擎支持8位色及以上的显示。

/\* Define if use new GAL interfaces \*/

\#define \_USE\_NEWGAL 1

使用newgal中的dummy引擎。

/\* Define if use dummy newgal engine \*/

\#define NEWGAL\_ENGINE\_DUMMY 1

[]{#_Toc95185270 .anchor}3.2 errno定义

因多个文件都有用到errno的值，故在minigui03/include/common.h中定义errno。

\#ifdef \_\_CC\_ARM

\# define ENOMEM 200

\# define EINVAL 201

\# define EBUSY 202

\# define EAGAIN 203

\# define ESRCH 204

\# define EDEADLK 205

\# define ENOTSUP 206

\# define ENOSYS 207

\#endif

[]{#_Toc95185271 .anchor}3.3 posix线程实现

除条件变量外所有的posix线程接口均需通过ThreadX相应接口封装或重新实现。故需创建下面几个文件置于对应路径下：

  ----------- ---------------------------------------------------------------------------
  include/    threadx\_pthread.h threadx\_semaphore.h
  src/libc/   threadx\_pprivate.h
  src/libc    threadx\_pthread.c、threadx\_mutex.c、threadx\_pprivate.c和threadx\_sem.c
  ----------- ---------------------------------------------------------------------------

1）头文件定义

在相应的头文件中需声明相关结构体、宏定义和函数接口。

-   结构体

a\. 结构体sched\_param

定义可参照如下所示：

struct sched\_param

{

UINT priority;

UINT preempt\_threshold;

ULONG time\_slice;

};

b\. 结构体pthread\_attr\_t

结构定义同src/libc/ucos2-pprivate.h中的pthread\_attr\_t定义。pthread\_info定义须与TX\_PTHREAD一致。

c\. 结构体pthread\_mutex\_t

定义可参照如下所示：

typedef struct \_pthread\_mutex\_t

{

TXPTH\_MUTEX tx\_mutex;

char name \[TXPTH\_LEN\_NAME\];

} pthread\_mutex\_t;

TXPTH\_MUTEX类型完全同与TX\_MUTEX，TXPTH\_LEN\_NAME为定义的默认名称长度。

> d\. 结构体pthread\_mutexattr\_t
>
> 定义可参照如下所示：

typedef struct \_pthread\_mutexattr\_t

{

unsigned int prio\_inherit;

} pthread\_mutexattr\_t;

e\. 结构体sem\_t

类型的定义采用如下所示：

typedef struct \_sem\_t

{

TX\_SEMAPHORE tx\_sem;

char name \[TXPTH\_LEN\_NAME\];

} sem\_t;

-   宏定义

a.  主线程中支持的最多线程数（64），默认优先级（21），阈值（21），时间片（10）；

b.  任务栈所占空间大小（约为400K）线程优先级范围（0\~31），

c.  线程的默认堆栈大小（4K）；默认的线程优先级（20），阈值（20），时间片（10）；

> 以上默认值可由移植者自己来定。下面所列宏定义可供参考：

//threadx\_pprivate.h

\#define TXPTHNUM\_POSIX\_PTHREAD\_THREADS\_MAX 64

\#define TXPTHNUM\_LIBC\_MAIN\_DEFAULT\_STACK\_SIZE (1024 \* 4)

\#define TXPTH\_THREAD\_MIN\_PRIORITY 31

\#define TXPTH\_THREAD\_MAX\_PRIORITY 0

\#define TXPTH\_THREAD\_DEF\_PRIORITY 20

\#define TXPTH\_THREAD\_DEF\_PREEMPT\_THRESHOLD 20

\#define TXPTH\_THREAD\_DEF\_TIME\_SLICE 10

\#define TXPTH\_POSIX\_MAIN\_DEF\_PRIORITY 21

\#define TXPTH\_POSIX\_MAIN\_DEF\_PREEMPT\_THRESHOLD 21

\#define TXPTH\_POSIX\_MAIN\_DEF\_TIME\_SLICE 10

\#define TXPTH\_SIZE\_BYTE\_POOL ((PTHREAD\_STACK\_DEFAULT + sizeof
(pthread\_info) + (1024\*2)) \* TXPTHNUM\_POSIX\_PTHREAD\_THREADS\_MAX)

\#define TXPTH\_NAME\_BYTE\_POOL "BytePool4PThreads"

\#define TXPTH\_NAME\_MUTEX "Mutex4PThreads"

\#define PTHREAD\_TX\_PRIORITY(pri) (TXPTH\_THREAD\_MIN\_PRIORITY-(pri))

\#define PTHREAD\_POSIX\_PRIORITY(pri)
(TXPTH\_THREAD\_MIN\_PRIORITY-(pri))

//threadx\_pthread.h

\#define PTHREAD\_STACK\_MIN (1024\*2)

\#define PTHREAD\_STACK\_DEFAULT (1024\*4)

\#define PTHREAD\_KEYS\_MAX 64

-   posix线程相关函数接口

2）实现文件

ThreadX中的各函数均有名字段变量，该段值不可重复，而在posix中无此段，故需创建一实现唯一名称的函数供线程所有实现函数使用，该函数实现含在threadx\_pprivate.c中。

除了标准posix线程接口实现外，为了调用MiniGUI主程序入口，还需创建一函数（如txpth\_posix\_pthread\_start）来实现主线程的创建，MiniGUI所有其它程序均在此主线程下运行。该主线程完成诸如开辟缓冲池，初始化全局互斥锁和全部线程的局部存储表以及主线程的各相关值，最后创建主线程。

线程具体实现可参考ucosii相关文件源代码或ecos-2.0中线程的相关实现。具体细节也可参考详细设计文档。

[]{#_Toc95185272 .anchor}3.4 内存管理和相关I/O接口

1）内存管理

内存管理相关的函数接口定义在
include/own\_malloc.h头文件中，具体的实现文件是
src/libc/malloc.c。malloc.c文件中实现了
malloc、free、calloc和realloc等堆内存管理的函数。这些函数的接口定义和使用方法和标准C中定义的是一样的。

int threadx\_malloc\_init (void);

MiniGUI for
ThreadX在该部分需增加ThreadX下的相关函数实现，具体可参照该文件ucosii部分的代码。另外此部分增加一接口int
minigui\_tx\_malloc\_init (unsigned char\* heap, unsigned int
heap\_size)，此函数实现分配一块堆栈首址为heap，大小为heap\_size内存块。该接口为应用开辟一块运转的空间。在使用这些内存管理函数之前必须首先调用minigui\_tx\_malloc\_init函数进行系统的初始化，我们一般必须在使用minigui的相关函数之前调用该函数进行堆内存管理模块的初始化，因为minigui用到了动态内存分配函数。

2）I/O接口

I/O接口部分相应的自定义接口实现在文件libc/defdev.c 中。

static int def\_seek (MG\_RWops \*context, int offset, int whence)

static int def\_read (MG\_RWops \*context, void \*ptr, int size, int
maxnum)

static int def\_write (MG\_RWops \*context, const void \*ptr, int size,
int num)

static int def\_ungetc (MG\_RWops \*context, unsigned char c)

static int def\_close (MG\_RWops \*context)

static int def\_eof (MG\_RWops \*context)

MG\_RWops \_\_mg\_def\_dev = {def\_seek, def\_read, def\_write,
def\_ungetc, def\_close, def\_eof, RWAREA\_TYPE\_UNKNOWN};

针对ThreadX需对def\_write(),
def\_read()等一系列函数重新实现。具体方式可通过串口驱动的serial\_read()和serial\_write()完成相应功能。

[]{#_Toc95185273 .anchor}3.5 图形和输入引擎

1）图形引擎

MiniGUI for
ThreadX的图形引擎文件可基于现有的LCD图形引擎comm2lcd修改来得到，该图形引擎的相关文件位于
src/newgal/commlcd/ 目录下，包括commlcd.c和commlcd.h文件。

commlcd 引擎定义了统一的两个由底层驱动程序提供的LCD函数接口，如下：

int drv\_lcd\_init (void);

int lcd\_getinfo (struct lcd\_info \*li);

drv\_lcd\_init函数用来进行LCD的初始化，drv\_lcd\_getinfo函数用来获取LCD的相关信息，其中lcd\_info结构的定义如下：

struct lcd\_info {

short height, width; // 屏幕的高和宽

short bpp; // 位深度（bits per pixel）

short type; // 象素类型

short rlen; // 每行象素所占用的字节数

void \*fb; // Frame buffer 的起始地址

};

把MiniGUI
移植到基于ThreadX的ANVIL开发板上时，LCD驱动或者应用程序必须实现这两个函数所具有的功能。

LCD驱动提供的类似函数接口如下：

SINT32 tp\_man\_lcd\_init(VOID);

SINT32 tp\_man\_lcd\_get\_info(MAN\_LCD\_SCREEN \*screen);

在commlcd.h中定义下面的映射语句：

\#define drv\_lcd\_init tp\_man\_lcd\_init

\#define drv\_lcd\_getinfo tp\_man\_lcd\_get\_info

typedef MAN\_LCD\_SCREEN lcd\_info;

\#define FB\_TRUE\_RGB565 1;

2）输入引擎

MiniGUI for
ThreadX的输入引擎可基于现有的输入引擎comm2ial做相应修改，该引擎的相关文件位于
src/ial/ 目录，包括comminput.c和comminput.h文件。

commial引擎需要操作系统或者底层键盘驱动提供如下的二个相似函数功能的接口：

int comm\_kb\_getdata (short \*key, short \*status);

int comm\_wait\_for\_input (void);

comm\_wait\_for\_input函数用来查询是否有输入数据。如果没有输入事件的话，该函数返回0；如果有鼠标或触摸屏事件的话，返回值的第1位置1；如果有键盘事件的话，返回值的第2位置1。

comm\_kb\_getdata函数用来获取键盘的输入数据，key返回键盘的keycode，status返回按键状态（1表示键按下）。comm\_kb\_getdata获取数据成功时应该返回0，否则返回负值。这里的keycode是指MiniGUI中定义的键盘各按键的键码（参考
include/common.h中定义的scancode），底层驱动键盘驱动程序需要在收到键盘的扫描码（scancode）时，把scancode转换为对应的keycode（MiniGUI定义的scancode）返回。

MiniGUI中外部事件的输入处理作为一个单独的系统线程存在，在没有外部事件时，该线程应该进入睡眠。所以，驱动实现comm\_wait\_for\_input函数时需要提供一个等待机制，如信号量或者其它事件。comm\_wait\_for\_input函数中查询是否有输入数据时等待一个输入信号量，让调用该函数的MiniGUI输入任务进入睡眠，有输入时由底层驱动程序（中断处理程序）发出信号唤醒该任务。comm\_kb\_getdata函数直接返回输入数据。

键盘驱动提供的两个函数接口如下：

SINT32 tp\_man\_kp\_get\_data(MAN\_KP\_INFO \*kp);

SINT32 tp\_man\_kp\_wait(UINT32 timeout); /\*timeout
单位：ms，粒度：10ms\*/

需建立一文件threadx-kbdrv.c，在该文件中实现驱动扫描码与MiniGUI扫描码的映射函数和下面两函数。

int comm\_kb\_getdata (short \*key, short \*status);

int comm\_wait\_for\_input (void);

另需在comminput文件中增加相应语句：

\#if defined \_\_THREADX\_\_ && defined \_\_VFANVIL\_\_

\#include "threadx\_kbdrv.c"

\#endif

3）添加配置文件

为了使上述引擎针对ThreadX生效，需定义一配置文件mgetc\_threadx.c。该文件定义可参照其它mgetc-\*.c文件。mgetc-threadx.c文件中定义ThreadX使用的输入和图形引擎、屏幕分辨率和颜色、字体等配置属性。下面是一定义范例。

static char \*SYSTEM\_VALUES\[\] = {"commlcd", "comm", "/dev/mouse",
"IMPS2"};

static char \*FBCON\_VALUES\[\] = {"320x240-16bpp"};

static char \*SYSTEMFONT\_KEYS\[\] =

{"font\_number", "font0", "default", "wchar\_def", "fixed", "caption",
"menu", "control"};

static char \*SYSTEMFONT\_VALUES\[\] =

{

"1","rbf-fixed-rrncnn-6-12-ISO8859-1",

"0", "0", "0", "0", "0", "0"

};

SYSTEM\_VALUES的前两项分别指定图形引擎和输入引擎，在ThreadX版本中默认是commlcd通用图形引擎和comm通用输入引擎，一般不需要修改。后面的两项针对使用鼠标的输入引擎。

FBCON\_VALUES指定LCD的屏幕分辨率和颜色深度，需要根据实际的LCD分辨率大小和颜色进行调整，对应于ANVIL开发板就是320x240-16bpp。

SYSTEMFONT\_KEYS和SYSTEMFONT\_VALUES项定义了MiniGUI使用的系统字体，可根据实际需要修改。

定义好图形和输入引擎后需在mgetc.c文件的相应位置加入如下代码。

\#include "mgetc-threadx.c"

[]{#_Toc95185274 .anchor}3.6 ThreadX下启动MiniGUI的入口

\#include "tx\_api.h"

\#include "serial.h"

\#include "common.h"

\#include "pthread.h"

\#define MY\_HEAP\_SIZE (2\*1024\*1024)

static unsigned char my\_heap \[MY\_HEAP\_SIZE\];

extern int minigui\_tx\_malloc\_init (unsigned char\* heap, unsigned int
heap\_size);

extern int minigui\_entry (int argc, const char\* argv\[\]);

void main\_enter()

{

serial\_init(baud\_57600);

tx\_kernel\_enter();

}

void tx\_application\_define (void \*first\_unused\_memory)

{

if (minigui\_tx\_malloc\_init (my\_heap, MY\_HEAP\_SIZE))

printf ("Can not init minigui heap.\\n");

txpth\_posix\_pthread\_start (minigui\_entry);

}

[]{#_Toc95185275 .anchor}4. ADS1.2中编译MiniGUI库

[]{#_Toc95185276 .anchor}4.1 ADS1.2中MiniGUI库工程的建立

1）建立工程文件

> ADS1.2环境下：

File -&gt;New-&gt;Project下选择ARM Object
Library，输入工程名（例：libminigui），选择工程保存路径，确定。

2）向工程中添加以下文件

  ------------------------------ ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  > 文件夹                       > 文件名
  > minigui03/src/newgdi         > tga.c advapi.c arc.c attr.c bitmap.c clip.c coor.c drawtext.c flood.c gdi.c generators.c icon.c line.c logfont.c map.c miarc.c midash.c mifillarc.c mifpolycon.c mispans.c miwideline.c palette.c pcx.c pixel.c pixel\_ops.c polygon.c readbmp.c rect.c region.c screen.c text.c
  > minigui03/src/newgal         > blit.c blit\_0.c blit\_1.c blit\_A.c blit\_N.c gamma.c newgal.c pixels.c RLEaccel.c stretch.c surface.c video.c
  > minigui03/src/newgal/dummy   > nullvideo.c
  > minigui03/src/main           > main.c
  > minigui03/src/sysres         > resource.c syscfg.c mgetc.c
  > minigui03/src/mybmp          > winbmp.c lbm.c mybmp.c gif.c
  > minigui03/src/misc           > about.c clipboard.c endianrw.c math3d.c math.c misc.c nposix.c rwops.c systext.c
  > minigui03/src/libc           > fnprintf.c fprintf.c fscanf.c printf.c scanf.c snprintf.c sscanf.c stdioinlines.c vfnprintf.c vfscanf.c malloc.c defdev.c threadx\_mutex.c threadx\_pprivate.c threadx\_pprivate.h threadx\_p thread.c threadx\_sem.c ieeefp.h vsnprintf,c vsscanf.c
  > minigui03/src/ial            > ial.c auto.c comminput.c dummy.c
  > minigui03/src/gui            > window.c accelkey.c caret.c ctrlclass.c defkeymap.c dialog.c element.c keyboard.c menu.c
  > minigui03/src/font           > varbitmap.c big5unimap.c charset.c devfont.c euckrunimap.c fontname.c freetype2.c freetype.c gb18030unimap.c gbkunimap.c gbunimap.c jisunimap.c qpf.c rawbitmap.c sjisunimap.c sysfont.c type1.c ujisunimap.c
  > minigui03/src/font/in-core   > 8\*16-iso8859-1.c song-12-gb2312.c song-16-gb2312.c 6\*12-iso8859-1.c courier\_8\*13.c sansserif\_11\*13.c
  > minigui03/src/kernel         > fixstr.c init.c message.c timer.c blockheap.c cursor.c desktop.c event.c
  > minigui03/src/control        > button.c combobox.c ctrlmisc.c edit.c listbox.c menubutton.c newtoolbar.c progressbar.c propsheet.c scrolled.c scrollview.c scrollwnd.c simedit.c static.c textedit.c toolbar.c trackbar.c listmodel.c
  > 扩展库部分：                 > (可根据需要增加相应扩展程序)
  > minigui03/ext/mywins         > colordlg.c colorspace.c filedlg.c helpwin.c mywindows.c newfiledlg.c
  > minigui03/ext/skin           > bmplabel.c chkbutton.c cmdbutton.c label.c mgcontrol.c rotslider.c skin.c slider.c
  > minigui03/ext/control        > treeview.c animation.c coolbar.c initmgext.c listview.c monthcalendar.c spinbox.c
  > minigui03/ext/image          > gif.c
  ------------------------------ ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

最终minigui工程视图如图4.1所示：

![C:\\Documents and Settings\\Administrator\\My Documents\\My
Pictures\\libminigui.bmp](media/image2.png){width="4.095833333333333in"
height="3.542361111111111in"}

图4.1 minigui库的工程视图

其中libmgext.mcp为扩展库工程，该工程视图如图4.2所示：

![C:\\Documents and Settings\\Administrator\\My Documents\\My
Pictures\\libmgext.bmp](media/image3.png){width="3.404166666666667in"
height="2.5in"}

图4.2 mgext库的工程视图

3）工程选项设置

Edit-&gt;DebugRel Settings-&gt;Language Settings中的ARM C
Compiler设置中必包含的选项

-Ec -D\_\_MINIGUI\_LIB\_\_

Edit-&gt;DebugRel Settings-&gt;Target下Access Paths的System
Paths中需添加工程的头文件所在目录。

4）make工程生成libtxMiniGUI.a文件

[]{#_Toc95185277 .anchor}4.2 基于ThreadX编译MiniGUI应用程序

1）ADS1.2下建立应用程序工程

File -&gt;New-&gt;Project下选择ARM Executable
Image，输入工程名（例：helloworld），选择工程保存路径，确定。

2）添加工程所需文件

  ------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------
  > 示例程序                                                                                  > helloworld.c
  > ThreadX相应驱动程序                                                                       > serial.h serial-driver.c serial.c dt\_main\_init.s dt\_stackheap.s tx\_ill.s
  > 链接库文件                                                                                > libthreadx.a libtxMiniGUI.a
  > ThreadX头文件（放于include下的tx目录中）和MiniGUI头文件（放于include下的minigui目录中）
  ------------------------------------------------------------------------------------------- --------------------------------------------------------------------------------

3）工程选项设置

Edit-&gt;DebugRel Settings-&gt;Target-&gt;Access Paths的System
Paths中需添加库文件所在目录及头文件所在目录。

Edit-&gt;DebugRel Settings-&gt;Language Settings的ARM Assembler设置

-keep -PD "TX\_ENABLE\_FIQ\_SUPPORT SETL {TRUE}" -g -PD
"TX\_ENABLE\_FIQ\_NESTING SETL {TRUE}" -apcs /interwork

Edit-&gt;DebugRel Settings-&gt;Language Settings的ARM C Compiler设置

-O0 -Otime -g+ -apcs /interwork -DTX\_ENABLE\_FIQ\_SUPPORT

Edit-&gt;DebugRel Settings-&gt;Linke的ARM Linker设置

-info totals -entry \_\_tx\_start -scatter 工程路径\\scatter\_ram.scf

make工程，生成可执行映象文件。

[]{#_Toc95185278 .anchor}4.3 可执行映象下载到RAM中的调试

1）ANVIL板上电，打开Trace32。

将Trace32软件中CPU-&gt;System Setting的Mode置为Up（即为上电模式）。

2）装载映象文件至RAM

File-&gt;Load选择需装载的映象文件。

3）调试

运行Run菜单下相应选项，可单步或断点调试。

[]{#_Toc95185279 .anchor}4.4 可执行映象下载到Flash中调试

> 1）设置跳线和串口。

2.  ANVIL板上电。

3.  FlashLoader设置

  -------------------- --------------
  > 选 项              > 值
  > Com port           > COM1
  > Platform           > Monaco
  > Destination Type   > Flash
  > Address            > 0x01000000
  -------------------- --------------

2.  选择Phone code
    ，即要装载的映象文件。Start开始装载。当Status栏出现Waiting for
    sync时，按ANVIL板上的复位按钮，获取同步信息。当Status显示为Done时完成下载。映象文件启动。


