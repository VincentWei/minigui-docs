![](media/image1.jpeg){width="2.234027777777778in"
height="1.3743055555555554in"}

MiniGUI for VxWorks

移植指南

适用于 MiniGUI Ver 1.6.x

北京飞漫软件技术有限公司

2004 年 10 月

版权声明
========

《MiniGUI for VxWorks 移植指南》 for MiniGUI Version 1.6.x。

版权所有 (C) 2004，2005 北京飞漫软件技术有限公司，保留所有权利。

无论您以何种方式获得该手册的全部或部分文字或图片资料，无论是普通印刷品还是电子文档，北京飞漫软件技术有限公司仅仅授权您阅读的权利，任何形式的格式转换、再次发布、传播以及复制其内容的全部或部分，或将其中的文字和图片未经书面许可而用于商业目的，均被视为侵权行为，并可能导致严重的民事或刑事处罚。

目 录
=====

版权声明 I

目 录 II

1 移植MiniGUI到VxWorks 1

1.1原理 1

1.2在cygwin环境中编译MiniGUI库 1

1.2.1Tornado 开发环境 1

1.2.2 cygwin 编译环境 2

1.2.3 MiniGUI的配置头文件 3

1.2.4 MiniGUI的资源配置文件 6

1.2.5 确定编译规则 7

1.2.6编译MiniGUI 8

1.3图形引擎 9

1.4输入引擎 10

1.5 MiniGUI入口函数 13

1.6编译minigui应用程序。 14

1 移植MiniGUI到VxWorks
======================

1.1原理
-------

MiniGUI
软件架构的设计充分考虑了可移植性，核心的主要结构包括消息处理、窗口管理和图形绘制等主要模块都是建立在得到广泛支持的POSIX线程库接口的基础之上；其次，MiniGUI通过操作系统和硬件抽象层（porting
layer）隐藏了特定操作系统及底层硬件的细节，这大大减轻了MiniGUI移植到不同操作系统和硬件平台的工作量。

由于VxWorks操作系统提供了POSIX相关API的支持，因此，将 MiniGUI 移植到
VxWorks 是相对容易的一项工作。

我们把MiniGUI for
VxWorks版本移植到不同的硬件平台上时，通常需要针对该硬件平台的LCD驱动和输入驱动（触摸屏、鼠标、键盘）对图形引擎和输入引擎做相应的修改。

1.2在cygwin环境中编译MiniGUI库
------------------------------

MiniGUI for
VxWorks的配置和编译方法取决于开发主机的操作系统类型、编译环境和编译器。一般而言，我们可以在类Linux的环境下把MiniGUI库交叉编译为一个静态库，如libminigui.a，然后在编译MiniGUI应用程序时指定MiniGUI头文件搜索路径和指定链接libminigui.a库，最后生成一个包括VxWorks、MiniGUI和应用程序代码在内的可执行文件（映像）。编译应用程序和链接生成目标映像的工作一般在Tornado开发环境中进行。

### 1.2.1Tornado 开发环境

Tornado
是VxWorks的集成开发环境，提供了包括代码编辑、编译和调试在内的丰富功能。不过，编译MiniGUI库时我们只需用到它提供的编译器和相关工具。Tornado
提供的ARM编译器是ccarm，在windows平台上安装之后位于{Tornado2.2安装目录}/host/x86-win32/bin目录下。

### 1.2.2 cygwin 编译环境

MiniGUI在Windows环境下使用makefile编译时，我们需要一个Unix模拟环境－cygwin。cygwin（[*http://www.cygwin.com*](http://www.cygwin.com)）是一个运行Windows操作系统之上的Unix模拟环境，该环境的功能非常强大，提供了包括makfile工具、autoconf/automake工具和交叉编译器在内的完整配置和编译环境和其它相关的工具程序。

由于autoconf/automake工具和GCC编译器的关系非常密切，如果使用别的交叉编译器（如Tornado提供的ccarm）的话，autoconf/automake工具有时候会出现问题。所以，在cygwin环境下，如果我们使用Tornado提供的ccarm作为交叉编译器的话，需要使用单独的一套MiniGUI
makefile（在各个目录及子目录下的文件名为makefile.ng）来编译，而不是由autoconf/automake自动生成makefile。

我们需要修改cygwin中用户目录下的.bash\_profile配置文件，增加针对Tornado编译器的相关环境变量设置：

\# for vxworks

WIND\_BASE=/cygdrive/c/Tornado2.2 (假设Tornado安装在c:\\Tornado2.2目录)

WIND\_HOST\_TYPE=x86-win32

PATH=\$WIND\_BASE/host/\$WIND\_HOST\_TYPE/bin:\$PATH

export WIND\_BASE WIND\_HOST\_TYPE

export PATH

这样cygwin中的make工具就能找到Tornado的编译器相关工具。

注意：必须在PATH环境变量中把Tornado工具所在的路径设在最前面，否则不能正常编译！另外，由于Tornado也提供了自己的make工具，所以我们编译时需要把cygwin提供的make和Tornado提供的make区分开。我们编译MiniGUI应该用cygwin提供的make工具而不是Tornado提供的，所以我们需要输入绝对路径来指定使用cygwin提供的/usr/bin目录下的make工具。如下：

\$./usr/bin/make –f GNUmakefile nognu

Tornado的PATH定义在cygwin之前，如果我们直接输入make –f GNUmakefile
nognu的话，使用的make将是Tornado提供的make，会出现莫名其妙的错误。

### 1.2.3 MiniGUI的配置头文件

编译minigui之前，我们首先需要确定minigui的配置，这是在配置头文件config.h中指定的。

MiniGUI的配置头文件config.h中以条件编译宏的方式定义了MiniGUI的一些特性和选项。如果我们在cygwin运行configure脚本对minigui进行配置的话，脚本会根据我们给出的选项自动生成该头文件；如果我们不采用上面提到的configure脚本方式，就需要在config.h头文件中手工定义一些相关的宏。MiniGUI库中已经针对VxWorks
WiFi开发板提供了一个定义好的配置头文件config-vxworks-wifi.h，位于build目录下，可以直接使用该头文件。

把该头文件拷贝到libminigui-1.6.0目录，改名为config.h：

\$.cp build/config-vxworks-wifi.h config.h

config.h中比较重要的配置选项如下：

使用auto输入引擎。Auto引擎在没有键盘等输入设备时可以用来模拟键盘和鼠标的输入，该引擎自动地产生键盘和鼠标的输入事件，在移植或测试时非常有用。如果在release版本使用键盘和触摸屏作为输入设备，就可以把该支持去掉。

/\* Define if include the automatic IAL engine \*/

\#define \_AUTO\_IAL 1

使用dummy输入引擎。该引擎什么也不干，在没有其它引擎时，使用该引擎可以使MiniGUI正常运作和显示，但是没有输入，主要用于移植和测试。

/\* Define if include the dummy IAL engine \*/

\#define \_DUMMY\_IAL 1

使用针对VxWorks操作系统的通用输入引擎，驱动需要实现该引擎定义的相应驱动接口。

/\* Define if include the common IAL engine \*/

\#define \_COMM\_IAL 1

内嵌式资源支持。没有文件系统时必须打开该选项。

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

Shift-JIS日文字符集支持。如果要使用日文的话，必须打开该选项。

\#define \_SHIFTJIS\_SUPPORT 1

下面分别是日文半角字符12点阵、日文全角12和16点阵字体（gothic）的支持，如果要使用某种字体，必须把对应的选项打开。

\#define \_INCORERBF\_RK\_6x12 1

\#define \_INCORERBF\_GOTHIC\_12 1

\#define \_INCORERBF\_KAN16 1

RBF字体支持，必须打开。上述字体都是RBF字体。

\#define \_RBF\_SUPPORT 1

I/O函数支持，如果需要的话打开。

/\* Define if use own implementation of stdio functions \*/

\#define \_USE\_OWN\_STDIO 1

非Linux的操作系统（如VxWorks）必须打开该选项。

/\* Define if compile for non-Linux like OS \*/

\#define \_\_NOLINUX\_\_ 1

VxWorks操作系统必须打开该选项。

/\* Define if compile for VxWorks \*/

\#define \_\_VXWORKS\_\_ 1

针对ccarm编译器的选项，使用ccarm编译器时必须打开。

\#define inline \_\_inline

**针对图形显示的选项：**

使用newgal图形引擎。Newgal图形引擎支持8位色及以上的显示。

/\* Define if use new GAL interfaces \*/

\#define \_USE\_NEWGAL 1

使用newgal中针对LCD的通用图形引擎，必须打开该选项。LCD驱动需要实现该引擎定义的相应访问接口。

\#define \_NEWGAL\_ENGINE\_COMMLCD 1

### 1.2.4 MiniGUI的资源配置文件

src/sysres/目录下的mgetc.c文件中定义了MiniGUI内建式资源及其它的配置，根据MiniGUI实际应用的操作系统和硬件平台的不同，该文件包含了针对目标系统的特定配置文件，对于WiFi开发平台而言就是mgetc-wifi.c文件。我们一般不需要修改mgetc文件，而是修改mgetc-wifi.c文件。

\#include "mgetc-pc.c"

\#include "mgetc-wifi.c"

mgetc-wifi.c文件中定义了当前使用的输入和图形引擎、屏幕分辨率和颜色、字体等配置属性。

static char \*SYSTEM\_VALUES\[\] = {"commlcd", "comm", "/dev/ts",
"none"};

static char \*FBCON\_VALUES\[\] = {"106x120-16bpp"};

static char \*SYSTEMFONT\_KEYS\[\] =

{"font\_number", "font0", "font1", "font2", "font3", "default",
"wchar\_def", "fixed", "caption", "menu", "control"};

static char \*SYSTEMFONT\_VALUES\[\] =

{

"4","rbf-fixed-rrncnn-6-12-ISO8859-1",
"rbf-gothic-rrncnn-6-12-JISX0201-1",
"rbf-gothic-rrncnn-12-12-JISX0208-1",

"\*-fixed-rrncnn-\*-16-JISX0208-1",

"0", "2", "2", "2", "3", "2"

};

SYSTEM\_VALUES的前两项分别指定图形引擎和输入引擎，在VxWorks版本中默认是commlcd通用图形引擎和comm通用输入引擎，一般不需要修改。后面的两项针对使用鼠标的输入引擎，这里没有意义，可以不管。

FBCON\_VALUES指定LCD的屏幕分辨率和颜色深度，需要根据实际的LCD分辨率大小和颜色进行调整，对应于WiFi开发板就是106x120-16bpp。

SYSTEMFONT\_KEYS和SYSTEMFONT\_VALUES项定义了MiniGUI使用的系统字体，可根据实际需要修改。需要注意的是，除了rbf-fixed-rrncnn-6-12-ISO8859-1字体外，别的字体如果要用的话，需要在配置MiniGUI时把相应的选项enable，具体请参考MiniGUI用户手册的相关部分。

### 1.2.5 确定编译规则

libminigui-1.6.0目录下的rules.make文件用来指定makefile.ng的通用编译规则，该文件的开始处包含了build目录下的针对某个目标系统的编译规则，相应于WiFi开发板就是build/rules-wifi.vxworks文件。如果rules.make包含的文件不是rules-wifi.vxworks或者需要它包含我们自己另外定义的编译规则文件，就需要把此处的名字更改为该文件名。

\# changes to your own rule specific to platform.

include \$(TOPDIR)/build/rules-wifi.vxworks

rules-wifi.vxworks文件指定了针对WiFi开发板和VxWorks的编译选项，内容如下：

\# rules for tornado

AS=

CC=ccarm

CXX=cpparm

CPP=ccarm

AR=ararm

RANLIB=ranlibarm

MAKE=/usr/bin/make

TARGET\_DIR=/cygdrive/c/Tornado2.2/target

DEFS=-D\_\_MINIGUI\_LIB\_\_ -D\_REENTRANT -D\_\_NOUNIX\_\_
-D\_\_VXWORKS\_\_

INCS=\${LOCAL\_INC} -I\${TARGET\_DIR}/h

CFLAGS=\${DEFS} \${INCS} \${LOCAL\_CFLAGS} -O2 -mapcs-32 -mlittle-endian
-march=armv5 -fno-builtin -Wall -DCPU=ARMARCH5 -DCPU\_946E
-DARMMMU=ARMMMU\_946E -DARMCACHE=ARMCACHE\_946 -DTOOL\_FAMILY=gnu
-DTOOL=gnu -DRW\_MULTI\_THREAD

COFLAG=-c

ARFLAGS=crus

文件的第一部分指定了所使用的编译器和相关工具，对于Tornado就是ccarm等，如果使用Tornado开发环境的话就不需要修改。**INCS**
变量指定了VxWorks头文件的搜索路径，可以是绝对路径或者相对路径。

rules-wifi.vxworks文件中的DEFS变量指定编译时宏定义。\_\_MINIGUI\_LIB\_\_宏说明是在编译minigui库，\_\_VXWORKS\_\_说明目标操作系统是VxWorks，\_\_NOLINUX\_\_说明目标操作系统是非Unix类的操作系统，这几个宏定义对于VxWorks上的minigui编译来说是必需的。

CFLAGS变量指定了Tornado编译器的编译选项。-DCPU=ARMARCH5
-DCPU\_946E指定目标处理器为ARM9的核心，如果处理器有变化，需要根据处理器的类型和ccarm编译器对其的命名进行相应的修改；
-O2指定ccarm编译器进行优化，适用于release版本；-c指定编译c文件为目标文件。需要注意的是，minigui的编译选项最好和Tornado开发环境中的应用程序的编译选项保持一致，否则可能会出现意想不到的编译时或运行时错误。

### 1.2.6编译MiniGUI

在 libminigui-1.6.0目录下运行如下命令将编译minigui库和mgext库：

\$./usr/bin/make –f GNUmakefile nognu

-f GNUmakefile指定make工具使用的makefile为GNUmakefile文件。

编译完成之后将在src目录下生成libminigui.a库文件，在ext目录下生成libmgext.a库文件。

如果需要清除以前的编译结果，如下：

\$./usr/bin/make –f GNUmakefile cleanall

1.3图形引擎
-----------

MiniGUI for
VxWorks版本中对LCD的驱动使用统一的通用LCD图形引擎comm2lcd，该图形引擎的相关文件位于
src/newgal/commlcd/ 目录下，包括commlcd.c和commlcd.h文件。

commlcd 引擎定义了统一的两个由底层驱动程序提供的LCD函数接口，如下：

int drv\_lcd\_init (void);

int drv\_lcd\_getinfo (struct lcd\_info \*li);

drv\_lcd\_init函数用来进行LCD的初始化，drv\_lcd\_getinfo函数用来获取LCD的相关信息，其中lcd\_info结构的定义如下：

struct lcd\_info {

short height, width; // 屏幕的高和宽

short bpp; // 位深度（bits per pixel）

short type; // 象素类型

short rlen; // 每行象素所占用的字节数

void \*fb; // Frame buffer 的起始地址

};

把MiniGUI
移植到新的硬件平台时，LCD驱动或者应用程序必须实现这两个函数。如下：

extern void\* uglGetFbAddress();

int drv\_lcd\_init(void)

{

return 0;

}

struct lcd\_info {

short height, width;

short bpp;

short type;

short rlen;

void \*fb;

};

int drv\_lcd\_getinfo(struct lcd\_info \*li)

{

/\* extern int fb\_address\_is\_ok; \*/

li-&gt;width = 106;

li-&gt;height = 120;

li-&gt;bpp = 16;

li-&gt;rlen = 106\*2;

li-&gt;type = 1;

li-&gt;fb = uglGetFbAddress();

return 0;

}

uglGetFbAddress
函数为驱动提供的获取framebuffer地址的函数，根据平台和驱动的不同而改变。

1.4输入引擎
-----------

MiniGUI for
VxWorks版本中对触摸屏和键盘的驱动使用统一的通用输入引擎comm2ial，该引擎的相关文件位于
src/ial/ 目录，包括comminput.c和comminput.h文件。

commial引擎需要操作系统或者底层驱动提供如下的三个函数接口：

int comm\_ts\_getdata (short \*x, short \*y, short \*button);

int comm\_kb\_getdata (short \*key, short \*status);

int comm\_wait\_for\_input (void);

comm\_wait\_for\_input函数用来查询是否有输入数据。如果没有输入事件的话，该函数返回0；如果有鼠标或触摸屏事件的话，返回值的第1位置1；如果有键盘事件的话，返回值的第2位置1。

comm\_ts\_getdata函数用来获取触摸屏的输入数据，x和y值返回位置数据，button返回按下状态（如果笔按下，返回非0值）。comm\_ts\_getdata获取数据成功时应该返回0，否则返回负值。

comm\_kb\_getdata函数用来获取键盘的输入数据，key返回键盘的keycode，status返回按键状态（1表示键按下）。comm\_kb\_getdata获取数据成功时应该返回0，否则返回负值。这里的keycode是指MiniGUI中定义的键盘各按键的键码（参考
include/common.h中定义的scancode），底层驱动键盘驱动程序需要在收到键盘的扫描码（scancode）时，把scancode转换为对应的keycode（MiniGUI定义的scancode）返回。

MiniGUI中外部事件的输入处理作为一个单独的系统线程存在，在没有外部事件时，该线程应该进入睡眠。所以，驱动实现comm\_wait\_for\_input函数时需要提供一个等待机制，如信号量或者其它事件。comm\_wait\_for\_input函数中查询是否有输入数据时等待一个输入信号量，让调用该函数的MiniGUI输入任务进入睡眠，有输入时由底层驱动程序（中断处理程序）发出信号唤醒该任务。comm\_ts\_getdata和comm\_kb\_getdata函数直接返回输入数据。

另外的一个选择方案是：comm\_wait\_for\_input
函数中不等待，直接返回有输入的信息；comm\_ts\_getdata函数或者comm\_kb\_getdata函数中实现等待机制。如下：

/\* not used in fact \*/

int comm\_ts\_getdata (short \*x, short \*y, short \*button)

{

return 0;

}

static unsigned int mg\_scancode\_convert(unsigned int keypress)

{

//转换为MiniGUI的键码，略

}

/\*

\* get keyboard event, defined for minigui common IAL engine.

\*/

int comm\_kb\_getdata (short \*key, short \*status)

{

unsigned int keypress;

keydatatype keydata;

if( msgQReceive( IAL\_KeypadQ, (char \*)&keydata, sizeof( keydata ),
WAIT\_FOREVER ) == ERROR )

{

return -1;

}

keypress = (unsigned int)keydata.keypress;

if( keydata.tag == KEY\_PRESSED ) {

\*status = 1;

}

else /\* on key release \*/

{

\*status = 0;

}

\*key = mg\_scancode\_convert(keypress);

return 0;

}

int comm\_wait\_for\_input (void)

{

/\* only keyboard events \*/

return 2;

}

上述驱动实现中，comm\_wait\_for\_input函数直接返回有键盘事件的信息；由于没有触摸屏支持，comm\_ts\_getdata直接返回0；comm\_kb\_getdata函数中通过msgQReceive函数由事件消息队列中获取键盘事件的数据，从而通过该函数实现了等待机制。

1.5 MiniGUI入口函数
-------------------

VxWorks版本的minigui函数库的入口函数是minigui\_entry，该函数是为main函数不存在或者定义在minigui外部的情况下定义的（普通情况下，如Linux上，minigui把main函数封装在库里面）。

int minigui\_entry (int argc, const char\* argv\[\]);

在使用minigui的其它函数之前应该先调用该函数。也就是说，通过该函数启动MiniGUI函数库及MiniGUI应用程序。

VxWorks上我们可以参考如下的方式来启动minigui。

\#include "pthread.h"

extern int minigui\_entry (int args, const char\* agr\[\]);

static void\* start\_minigui (void\* data)

{

minigui\_entry (0, NULL);

return NULL;

}

void create\_minigui (void)

{

pthread\_t th;

pthread\_attr\_t new\_attr;

pthread\_attr\_init (&new\_attr);

pthread\_attr\_setdetachstate (&new\_attr, PTHREAD\_CREATE\_DETACHED);

pthread\_attr\_setstacksize (&new\_attr, 48 \* 1024);

printf ("create thread for minigui\\n");

pthread\_create(&th, &new\_attr, start\_minigui, NULL);

pthread\_attr\_destroy (&new\_attr);

}

这里调用pthread\_create函数创建一个线程，在该线程中调用minigui\_entry函数开始minigui，该线程就是minigui的主线程。

建议只在POSIX线程中使用minigui相关的内容，也就是说，不直接在VxWorks的任务中调用minigui\_entry启动minigui或者调用minigui的函数。

minigui应用程序部分的入口函数（主线程的入口函数）仍然是MiniGUIMain，minigui的其它应用程序线程一般在主线程中创建。

1.6编译minigui应用程序。
------------------------

可以参考MiniGUI库的编译方法在cgywin环境下编译为一个静态库，然后在Tornado开发环境中和项目其它代码链接生成目标映像。
