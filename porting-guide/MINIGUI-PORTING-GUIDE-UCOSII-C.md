![](media/image1.jpeg){width="2.234027777777778in"
height="1.3743055555555554in"}

MiniGUI for uC/OS-II

实验指导书

适用于 MiniGUI Ver 1.6.x

北京飞漫软件技术有限公司

2004 年 8 月

版权声明
========

《MiniGUI for uC/OS-II 实验指导书》 for MiniGUI Version 1.6.x。

版权所有 (C) 2003，2004，北京飞漫软件技术有限公司，保留所有权利。

无论您以何种方式获得该手册的全部或部分文字或图片资料，无论是普通印刷品还是电子文档，北京飞漫软件技术有限公司仅仅授权您阅读的权利，任何形式的格式转换、再次发布、传播以及复制其内容的全部或部分，或将其中的文字和图片未经书面许可而用于商业目的，均被视为侵权行为，并可能导致严重的民事或刑事处罚。

目 录
=====

版权声明 I

目 录 II

实验1 MiniGUI的程序架构 1

1.1实验目的 1

1.2实验内容 1

1.3预备知识 1

1.4实验步骤 1

1.4.1打开Exp1目录中的SimpleUCOS.mcp工程文件 1

1.4.2打开mgapp组中的helloworld.c文件，理解minigui应用程序的基本结构 1

1.4.3理解minigui在uC/OS-II操作系统中的入口函数 3

1.4.4 查看minigui头文件所在目录 3

1.4.5 查看minigui库文件所在目录 4

1.4.6编译和运行helloworld程序 4

1.5思考题 4

实验2 移植MiniGUI到uC/OS-II 5

2.1实验目的 5

2.2实验内容 5

2.3预备知识 5

2.4实验原理 5

2.5实验步骤 6

2.5.1在cygwin环境中编译MiniGUI库。 6

2.5.2在ADS环境中编译MiniGUI库。 14

2.5.3图形引擎 17

2.5.4输入引擎 17

2.5.5动态（堆）内存管理 18

2.5.6 POSIX线程实现 20

2.5.7 MiniGUI入口函数 21

2.5.8编译minigui应用程序。 23

实验1 MiniGUI的程序架构
=======================

1.1实验目的
-----------

了解MiniGUI程序的基本结构，掌握MiniGUI应用程序设计的基本方法。掌握MiniGUI的程序的编译和运行方法。

1.2实验内容
-----------

1)  编写MiniGUI应用程序helloworld。

2)  在开发板上运行helloworld程序。

1.3预备知识
-----------

1)  MiniGUI和C编程基础知识。

2)  uC/OS-II的基本结构和编程接口。

3)  ADS开发环境的使用。

1.4实验步骤
-----------

### 1.4.1打开Exp1目录中的SimpleUCOS.mcp工程文件

### 1.4.2打开mgapp组中的helloworld.c文件，理解minigui应用程序的基本结构

MiniGUI是一个图形用户界面支持系统，通常的GUI编程概念均适用于MiniGUI编程，如窗口和事件驱动编程等。MiniGUI提供类Win32的API，熟悉Win32编程的读者可以很快地掌握MiniGUI编程的基本方法和各个API接口函数。

一个C程序的入口点为main函数，而一个MiniGUI程序的入口点为MiniGUIMain。

每个MiniGUI应用程序的初始界面一般都是一个主窗口，你可以通过调用CreateMainWindow函数来创建一个主窗口，其参数是一个指向MAINWINCREATE结构的指针，本例中就是CreateInfo，返回值为所创建主窗口的句柄。MAINWINCREATE结构描述一个主窗口的属性，你在使用CreateInfo创建主窗口之前，需要设置它的各项属性。

创建完主窗口之后，还需要调用ShowWindow函数才能把所创建的窗口显示在屏幕上。ShowWindow的第一个参数为所要显示的窗口句柄，第二个参数指明显示窗口的方式（显示还是隐藏），SW\_SHOWNORMAL说明要显示主窗口，并把它置为顶层窗口。

在调用ShowWindow函数之后，主窗口就会显示在屏幕上。和其它GUI一样，现在是进入消息循环的时候了。MiniGUI为每一个MiniGUI程序维护一个消息队列。在发生事件之后，MiniGUI将事件转换为一个消息，并将消息放入目标程序的消息队列之中。应用程序现在的任务就是执行如下的消息循环代码，不断地从消息队列中取出消息，进行处理：

while (GetMessage(&Msg, hMainWnd)) {

TranslateMessage(&Msg);

DispatchMessage(&Msg);

}

只要从消息队列中取出的消息不为MSG\_QUIT，GetMessage就返回一个非0值，消息循环将持续下去。MSG\_QUIT消息使GetMessage返回0，导致消息循环的终止。TranslateMessage函数把击键消息转换为MSG\_CHAR消息，然后直接发送到窗口过程函数。DispatchMessage函数最终将把消息发往该消息的目标窗口的窗口过程，让它进行处理，在本例中，该窗口过程就是HelloWinProc。也就是说，MiniGUI在DispatchMessage函数中调用主窗口的窗口过程函数（回调函数）对发往该主窗口的消息进行处理。处理完消息之后，应用程序的窗口过程函数将返回到DispatchMessage函数中，而DispatchMessage函数最后又将返回到应用程序代码中，应用程序又从下一个GetMessage函数调用开始消息循环。

窗口过程函数是MiniGUI程序的主体部分，应用程序实际所做的工作大部分都发生在窗口过程函数中，因为GUI程序的主要任务就是接收和处理窗口收到的各种消息。程序通常不直接调用窗口过程函数，而是由MiniGUI进行调用；也就是说，它是一个回调函数。窗口过程函数不予处理的消息应该传给DefaultMainWinProc函数进行缺省处理，从DefaultMainWinProc返回的值必须由窗口过程返回。

程序在响应MSG\_PAINT消息时进行屏幕输出。应用程序应首先通过调用BeginPaint函数来获得设备上下文句柄，并用它调用GDI函数来执行绘制操作。这里，程序使用TextOut文本输出函数把收到的键盘键码和鼠标按键打印到窗口上。绘制结束之后，应用程序应调用EndPaint函数释放设备上下文句柄。

用户单击窗口右上角的关闭按钮时窗口过程函数将收到一个MSG\_CLOSE消息。helloworld程序在收到MSG\_CLOSE消息时调用DestroyMainWindow函数销毁主窗口，并调用PostQuitMessage函数在消息队列中投入一个MSG\_QUIT消息。当GetMessage函数取出MSG\_QUIT消息时将返回0，最终导致程序退出消息循环。

程序最后调用MainWindowThreadCleanup清除主窗口所使用的消息队列等系统资源并最终由MiniGUIMain返回。

### 1.4.3理解minigui在uC/OS-II操作系统中的入口函数

打开SRC组中的MiniGUI.c文件，该文件实现了minigui库中libminigui-1.6.0/include/目录下mgdrv-ucosii.c文件定义的驱动函数接口和入口函数。minigui的入口函数为minigui\_app\_entry，该函数在main.c的Main\_Task函数中被调用。

### 1.4.4 查看minigui头文件所在目录

minigui的头文件和POSIX线程库的头文件放在Exp1工程的include目录下，必须在Access
Paths设置选项中的System
Paths中加入该路径，这样编译minigui应用程序时才能找到头文件。如果minigui库的配置或者头文件有改动，必须更新相应的头文件。

### 1.4.5 查看minigui库文件所在目录

minigui库文件包括libminigui.a和libmgext.a放在lib目录下，对应于工程中的lib组。

### 1.4.6编译和运行helloworld程序

编译工程，通过仿真器运行。点击屏幕和按键，观察程序的输出。

1.5思考题
---------

1)  把mg-samples例子包中的演示程序加入到工程中，编译和运行。

实验2 移植MiniGUI到uC/OS-II
===========================

2.1实验目的
-----------

1)  了解MiniGUI核心的主要结构。

2)  掌握将MiniGUI移植到uC/OS-II操作系统上的要点。

2.2实验内容
-----------

1)  将MiniGUI移植到运行uC/OS-II操作系统的NETARM3000开发板上。

2.3预备知识
-----------

1)  掌握在ARM ADS1.2集成开发环境中编写和调试程序的基本过程。

2)  掌握ADS编译器的基本概念和用法。

3)  了解uC/OS-II操作系统的核心概念和主要接口的用法。

4)  了解MiniGUI的基本原理和应用程序的编写。

2.4实验原理
-----------

MiniGUI
软件架构的设计充分考虑了可移植性，核心的主要结构包括消息处理、窗口管理和图形绘制等主要模块都是建立在得到广泛支持的POSIX线程库接口的基础之上；其次，MiniGUI通过操作系统和硬件抽象层（porting
layer）隐藏了特定操作系统及底层硬件的细节，这大大减轻了MiniGUI移植到不同操作系统和硬件平台的工作量。

不过，将 MiniGUI 移植到 uC/OS-II 是相对复杂的一项工作。因为 uC/OS-II
只是一个简单的实时操作系统内核，缺乏标准C库的支持，例如象 malloc/free
甚至是 printf/fprintf/sprintf
这样的函数接口；不过，最重要的还是缺乏POSIX线程的接口。因此，把MiniGUI移植到uC/OS-II操作系统的最重要工作就是在uC/OS-II上实现
POSIX线程库的接口，以及 malloc/free等堆内存管理接口和
printf/sprintf/fprintf 等I/O接口。

MiniGUI中uC/OS-II线程库的实现对不同硬件平台上的uC/OS-II版本都是一样的，基本上不需要修改；堆内存管理模块需要根据当前平台的内存模型进行适当的小调整。

我们把MiniGUI for
UC/OS-II版本移植到不同的硬件平台上时，通常需要针对该硬件平台的LCD驱动和输入驱动（触摸屏、鼠标、键盘）对图形引擎和输入引擎做相应的修改。

2.5实验步骤
-----------

### 2.5.1在cygwin环境中编译MiniGUI库。

MiniGUI
使用了自由软件常用的“automake”和“autoconf”接口来组织源代码的配置和编译，因而在Linux环境下，MiniGUI
的配置和编译非常容易，最简单的情况下（Linux
PC），我们只需在MiniGUI源代码目录下执行如下命令就可以编译和安装MiniGUI：

\$./configure

\$ make

\$ make install

MiniGUI for
uC/OS-II的配置和编译方法取决于开发主机的操作系统类型、编译环境和编译器。一般而言，我们可以在类Linux的环境下把MiniGUI库交叉编译为一个静态库，如libminigui.a，然后在编译MiniGUI应用程序和uC/OS-II时指定MiniGUI头文件搜索路径和指定链接libminigui.a库，最后生成一个包括uC/OS-II、MiniGUI和应用程序代码在内的可执行文件（映像）。

当然，我们也可以把MiniGUI的源代码放在ADS基础开发环境中编译，不过这样的话需要MiniGUI做很多手工配置的工作，例如修改MiniGUI的配置头文件中config.h的配置宏定义。

MiniGUI既可以在Linux环境下编译，也可以在Windows环境下编译。在Windows环境下使用makefile维护和编译时，我们需要一个Unix模拟环境－cygwin。

cygwin（[*http://www.cygwin.com*](http://www.cygwin.com)）是一个运行Windows操作系统之上的Unix模拟环境，该环境的功能非常强大，提供了包括makfile工具、autoconf/automake工具和交叉编译器在内的完整配置和编译环境和其它相关的工具程序。

如果使用GCC交叉编译器的话，MiniGUI for
uC/OS-II在cygwin环境下的配置和编译和在Linux环境下是基本相同的，只需做很少的改动。

由于autoconf/automake工具和GCC编译器的关系非常密切，如果使用别的交叉编译器（如ADS提供的armcc）的话，autoconf/automake工具有时候会出现问题。所以，在cygwin环境下，如果我们使用ADS提供的armcc作为交叉编译器的话，需要使用单独的一套MiniGUI
makefile（在各个目录及子目录下的文件名为makefile.ng）来编译，而不是由autoconf/automake自动生成makefile。

在cygwin环境下使用ADS提供的armcc编译器进行配置和编译的过程如下：

***1. 点击cygwin桌面图标启动cygwin环境***

***2. 在某个工作目录（如minigui\_prj）下解开minigui库的压缩包***

\$.cd minigui\_prj

\$.tar zxvf libminigui-1.6.0-ucos2.tar.gz

\$.cd libminigui-1.6.0

***3. 配置minigui***

编译minigui之前，我们首先需要确定minigui的配置，这是在配置头文件config.h中指定的。

MiniGUI的配置头文件config.h中以条件编译宏的方式定义了MiniGUI的一些特性和选项。如果我们在cygwin运行configure脚本对minigui进行配置的话，脚本会根据我们给出的选项自动生成该头文件；如果我们不采用上面提到的configure脚本方式，就需要在config.h头文件中手工定义一些相关的宏。MiniGUI库中已经针对NETARM3000开发板提供了一个定义好的配置头文件config-ucosii-s3c44b0x.h，位于build目录下，可以直接使用该头文件。

把该头文件拷贝到libminigui-1.6.0目录，改名为config.h：

\$.cp build/config-ucosii-s3c44b0x.h config.h

config.h中比较重要的配置选项如下：

使用auto输入引擎。Auto引擎在没有键盘等输入设备时可以用来模拟键盘和鼠标的输入，该引擎自动地产生键盘和鼠标的输入事件，在移植或测试时非常有用。如果在release版本使用键盘和触摸屏作为输入设备，就可以把该支持去掉。

/\* Define if include the automatic IAL engine \*/

\#define \_AUTO\_IAL 1

使用dummy输入引擎。该引擎什么也不干，在没有其它引擎时，使用该引擎可以使MiniGUI正常运作和显示，但是没有输入，主要用于移植和测试。

/\* Define if include the dummy IAL engine \*/

\#define \_DUMMY\_IAL 1

使用针对uC/OS-II操作系统的通用输入引擎，驱动需要实现该引擎定义的相应驱动接口。

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

RBF字体支持，必须打开。上述字体都是RBF字体。

\#define \_RBF\_SUPPORT 1

内存管理函数malloc等的支持。必须打开该选项。

/\* Define if use own implementation of malloc functions \*/

\#define \_USE\_OWN\_MALLOC 1

I/O函数支持，如果需要的话打开。

/\* Define if use own implementation of stdio functions \*/

\#define \_USE\_OWN\_STDIO 1

非Linux的操作系统（如uC/OS-II）必须打开该选项。

/\* Define if compile for non-Linux like OS \*/

\#define \_\_NOLINUX\_\_ 1

uC/OS-II操作系统必须打开该选项。

/\* Define if compile for uC/OS-II \*/

\#define \_\_UCOSII\_\_ 1

针对ADS编译器的选项，使用ADS编译器时必须打开。

\#define inline \_\_inline

**针对256色彩屏的选项：**

使用newgal图形引擎。Newgal图形引擎支持8位色及以上的显示。

/\* Define if use new GAL interfaces \*/

\#define \_USE\_NEWGAL 1

使用newgal中针对LCD的通用图形引擎，必须打开该选项。LCD驱动需要实现该引擎定义的相应访问接口。

/\* Define if use newgal engine for ucos2 \*/

\#define \_NEWGAL\_ENGINE\_COMMLCD 1

**针对8位色以下LCD的选项：**

首先不能打开 \_USE\_NEWGAL 选项。

使用native图形引擎，必须打开。

/\* Define if include native graphics engine \*/

\#define \_NATIVE\_GAL\_ENGINE 1

使用针对LCD屏颜色位数的图形子引擎，必须打开。例如单色屏就是：

/\* Define if include 1BPP FB subdriver (MSB is left) \*/

\#define \_FBLIN1L\_SUPPORT 1

使用nativegal中针对LCD的通用图形引擎，必须打开该选项。LCD驱动需要实现该引擎定义的相应访问接口。

/\* Define if support native graphics engine on common LCD \*/

\#define \_NATIVE\_GAL\_COMMLCD 1

***4. minigui的资源配置文件***

src/sysres/目录下的mgetc.c文件中定义了MiniGUI内建式资源及其它的配置，根据MiniGUI实际应用的操作系统和硬件平台的不同，该文件包含了针对目标系统的特定配置文件，对于NETARM3000开发平台而言就是mgetc-ucosii-arm3000.c文件。我们一般不需要修改mgetc文件，而是修改mgetc-ucosii-arm3000.c文件。

\#include "mgetc-pc.c"

\#include "mgetc-ucosii-arm3000.c"

mgetc-ucosii-arm3000.c文件中定义了当前使用的输入和图形引擎、屏幕分辨率和颜色、字体等配置属性。

static char \*SYSTEM\_VALUES\[\] = {"commlcd", "comm", "/dev/mouse",
"IMPS2"};

static char \*FBCON\_VALUES\[\] = {"320x240-8bpp"};

static char \*SYSTEMFONT\_KEYS\[\] =

{"font\_number", "font0", "font1", "font2", "default", "wchar\_def",
"fixed", "caption", "menu", "control"};

static char \*SYSTEMFONT\_VALUES\[\] =

{

"3","rbf-fixed-rrncnn-6-12-ISO8859-1", "\*-fixed-rrncnn-\*-16-GB2312",
"\*-Helvetica-rrncnn-\*-16-GB2312",

"0", "1", "1", "2", "2", "2"

};

SYSTEM\_VALUES的前两项分别指定图形引擎和输入引擎，在uC/OS-II版本中默认是commlcd通用图形引擎和comm通用输入引擎，一般不需要修改。后面的两项针对使用鼠标的输入引擎，这里没有意义，可以不管。

FBCON\_VALUES指定LCD的屏幕分辨率和颜色深度，需要根据实际的LCD分辨率大小和颜色进行调整，对应于NETARM3000开发板就是320x240-8bpp。

SYSTEMFONT\_KEYS和SYSTEMFONT\_VALUES项定义了MiniGUI使用的系统字体，可根据实际需要修改。需要注意的是，除了rbf-fixed-rrncnn-6-12-ISO8859-1字体外，别的字体如果要用的话，需要在配置MiniGUI时把相应的选项enable，具体请参考MiniGUI用户手册的相关部分。

***5. 确定编译规则***

libminigui-1.6.0目录下的rules.make文件用来指定makefile.ng的通用编译规则，该文件的开始处包含了build目录下的针对某个目标系统的编译规则，相应于NETARM3000开发板就是build/rules-s3c44b0x.ucosii文件。如果rules.make包含的文件不是rules-s3c44b0x.ucosii或者需要它包含我们自己另外定义的编译规则文件，就需要把此处的名字更改为该文件名。

\# changes to your own rule specific to platform.

include \$(TOPDIR)/build/rules-s3c44b0x.ucosii

rules-s3c44b0x.ucosii文件指定了针对NETARM3000开发板和uC/OS-II的编译选项，内容如下：

\# rules for S3C44B0X on ucosii

AS=

CC=armcc

CXX=armcpp

CPP=armcc -E

AR=armar

RANLIB=echo

MAKE=make

\# should be changed

UCOSII\_INC=D:\\ucos\\minigui\_prj\\include

DEFS=-D\_\_MINIGUI\_LIB\_\_ -D\_REENTRANT -D\_\_TARGET\_S3C44B0X\_\_
-D\_\_NOLINUX\_\_ -D\_\_UCOSII\_\_

INCS=\${LOCAL\_INC} -I\${UCOSII\_INC}

CFLAGS=\${DEFS} \${INCS} \${LOCAL\_CFLAGS} -O2 -cpu ARM7TDMI -Ec -c

\#COFLAG=-o

ARFLAGS=-create

文件的第一部分指定了所使用的编译器和相关工具，对于ADS就是armcc等，如果使用ADS开发环境的话就不需要修改。**UCOSII\_INC**
变量指定了uC/OS-II头文件的搜索路径，可以是绝对路径或者相对路径，建议在工作目录minigui\_prj下建一个include目录，把uC/OS-II头文件和其它的系统头文件放在该目录中，然后指定搜索路径为该目录。

\$.cd minigui\_prj

\$.mkdir include

\$.把 os\_cfg.h os\_cpu.h ucos\_ii.h 三个ucos2头文件复制到此目录

libminigui-1.6.0/build目录下的minigui\_ads\_prj.zip压缩文件是用于ADS的工程文件包，其中包含了minigui的ADS工程文件和系统include目录及头文件，把它在minigui\_prj目录下解压缩：

\$.unzip minigui\_ads\_prj.zip

解压之后将生成libminigui.mcp和libmgext.mcp文件、libminigui\_Data和libmgext\_Data目录，这些是用于ADS的工程文件和目录；还将生成一个include目录，包含了minigui库和minigui应用程序需要用到的pthread.h和semaphore.h系统头文件，以及uC/OS-II的三个头文件。如果uC/OS-II头文件的内容有改动，需要更新include目录下的相应文件，使之和编译uC/OS-II时的系统头文件保持一致。

rules-s3c44b0x.ucosii文件中的DEFS变量指定编译时宏定义。\_\_MINIGUI\_LIB\_\_宏说明是在编译minigui库，\_\_UCOSII\_\_说明目标操作系统是uC/OS-II，\_\_NOLINUX\_\_说明目标操作系统是非Linux类的操作系统，这几个宏定义对于uC/OS-II上的minigui编译来说是必需的。\_\_TARGET\_S3C44B0X\_\_是针对使用s3c44b0x处理器的NETARM3000开发板的定义，如果开发板有变化，需要命名和更改为相应的名字。

CFLAGS变量指定了ADS编译器的编译选项。-cpu
ARM7TDMI指定目标处理器为ARM7TDMI的核心，如果处理器有变化，需要根据处理器的类型和ADS编译器对其的命名进行相应的修改；-Ec告诉ADS编译器不要把隐型类型转换当作错误处理，如果没有该选项的话编译minigui时可能会出现一大堆错误；-O2指定ADS编译器进行优化，适用于release版本，如果是debug版本的话，应该为
-O0
–g+；-c指定编译c文件为目标文件。需要注意的是，minigui的编译选项要和ADS开发环境中的uC/OS-II操作系统及应用程序的编译选项保持一致，否则可能会出现意想不到的编译时或运行时错误。

***6. 编译minigui***

在 libminigui-1.6.0目录下运行如下命令将编译minigui库和mgext库：

\$.make –f GNUmakefile nognu

-f GNUmakefile指定make工具使用的makefile为GNUmakefile文件。

编译完成之后将在src目录下生成libminigui.a库文件，在ext目录下生成libmgext.a库文件。

如果需要清除以前的编译结果，如下：

\$.make –f GNUmakefile cleanall

### 2.5.2在ADS环境中编译MiniGUI库。

***1. 打开工程文件***

libminigui-1.6.0/build目录下的minigui\_ads\_prj.zip压缩文件是用于ADS的工程文件包，把它在minigui\_prj目录下解压缩。

双击libminigui.mcp工程文件打开libminigui工程。

![C:\\Documents and Settings\\Administrator\\My Documents\\My
Pictures\\libminigui.bmp](media/image3.png){width="4.095833333333333in"
height="3.542361111111111in"}\
图2.1 minigui库的工程视图

![C:\\Documents and Settings\\Administrator\\My Documents\\My
Pictures\\libmgext.bmp](media/image4.png){width="3.404166666666667in"
height="2.5in"}\
图2.2 mgext库的工程视图

libminigui工程中包含了libmgext子工程，用于libmgext库的编译。

***2. 配置***

![C:\\Documents and Settings\\Administrator\\My Documents\\My
Pictures\\settings.bmp](media/image5.png){width="4.553472222222222in"
height="3.39375in"}\
图2.3 设置视图

Access Paths项指定用户和系统头文件搜索路径，ARM C
Compiler指定编译器选项，ARM
fromELF指定连接选项，一般不需要做太多的修改。各编译选项的含义请参考上一步骤。

### 2.5.3图形引擎

MiniGUI for
uC/OS-II版本中对LCD的驱动使用统一的通用LCD图形引擎comm2lcd，该图形引擎的相关文件位于
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

把MiniGUI 移植到新的硬件平台时，LCD驱动或者应用程序必须实现这两个函数。

libminigui-1.6.0/include/目录下的mgdrv-ucosii.c文件中定义了这两个接口函数，请在此基础上实现NETARM3000平台上的相关函数内容。

### 2.5.4输入引擎

MiniGUI for
uC/OS-II版本中对触摸屏和键盘的驱动使用统一的通用输入引擎comm2ial，该引擎的相关文件位于
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

libminigui-1.6.0/include/目录下的mgdrv-ucosii.c文件中定义了这三个接口函数，请在此基础上实现NETARM3000平台上的相关函数内容。

### 2.5.5动态（堆）内存管理

相关的函数接口定义在 include/own\_malloc.h头文件中，具体的实现文件是
src/libc/malloc.c。如果需要使用该malloc实现的话，config.h头文件中应该定义
\_USE\_OWN\_MALLOC
宏。如果是使用configure脚本对MiniGUI进行配置的话，在uC/OS-II操作系统上默认情况将定义该宏。

malloc.c文件中实现了
malloc、free、calloc和realloc等堆内存管理的函数。这些函数的接口定义和使用方法和标准C中定义的是一样的。

int ucos2\_malloc\_init (void);

在使用这些内存管理函数之前必须首先调用ucos2\_malloc\_init函数进行系统的初始化，我们一般必须在使用pthread和minigui的相关函数之前调用该函数进行堆内存管理模块的初始化，因为pthread和minigui都用到了动态内存分配函数。

malloc.c文件的大约281行处是NETARM3000开发板的相关实现部分，如果堆内存分配的方式或地址有变化，需要修改此处。这里堆的地址由外部变量bottom\_of\_heap确定。

\#elif \_\_TARGET\_S3C44B0X\_\_

\#ifndef HEAPEND

\#define HEAPEND 0x0c700000

\#endif

//extern char Image\$\$RW\$\$Limit\[\];

extern unsigned int bottom\_of\_heap; /\* defined in heap.s \*

static char\* \_\_ucos2\_heap;

static void\* \_\_ucos2\_MoreCore (int size)

{

void\* start;

if (size &gt;= 0 && (int)\_\_ucos2\_heap + size &lt;= HEAPEND) {

start = \_\_ucos2\_heap;

\_\_ucos2\_heap += size;

return start;

}

return MORECORE\_FAILURE;

}

\#else

malloc.c中用到一个uC/OS-II互斥量，优先级定义为42，可根据实际情况修改。

/\* mutex priority of the malloc \*/

\#define UCOS2\_MALLOC\_MUTEX\_PRIO 42

### 2.5.6 POSIX线程实现

相关的函数接口定义在include/ucos2\_pthread.h和include/ucos2\_semaphore.h中，具体的实现文件是src/libc/ucos2\_pthread.c、src/libc/ucos2\_mutex.c和src/libc/ucos2\_sem.c。

使用这些pthread函数之前必须首先调用ucos2\_posix\_pthread\_init函数进行初始化，一般我们必须在使用minigui的相关函数之前和在调用ucos2\_malloc\_init函数之后调用该初始化函数。

int ucos2\_posix\_pthread\_init (void);

ucos2\_pthread.h中定义了该pthread库的一些配置，应用程序可以根据实际需要进行修改，不过必须满足minigui对线程的基本需求。

\#define NR\_POSIX\_PTHREAD\_THREADS\_MAX 16 // This can not be less
than 5.

最大线程个数。因为minigui启动之后创建了一些系统线程，所以该值不能小于5。此外，该实现的每一个POSIX线程都对应于一个ucos2任务，所以，该值还受到ucos2任务数量的限制。

\#define HIGHEST\_UCOSII\_PTHREAD\_PRIORITY 16

\#define LOWEST\_UCOSII\_PTHREAD\_PRIORITY
(HIGHEST\_UCOSII\_PTHREAD\_PRIORITY + NR\_POSIX\_PTHREAD\_THREADS\_MAX -
1)

和线程对应的ucos2任务优先级范围。Pthread的任务优先级范围在HIGHEST\_UCOSII\_PTHREAD\_PRIORITY和LOWEST\_UCOSII\_PTHREAD\_PRIORITY之间，默认情况下就是16－31。

\#undef PTHREAD\_STACK\_MIN

\#define PTHREAD\_STACK\_MIN (PTHREAD\_KEYS\_MAX \* sizeof(void \*) +
1024\*8)

线程栈的最小值。一般来说，8K左右的栈大小可以满足一个minigui线程的栈需求。

POSIX互斥量和信号量的实现分别在ucos2\_mutex.c和ucos2\_sem.c文件中，是在UC/OS-II提供的信号量的基础之上实现的。

MiniGUI本身用到了一些信号量和互斥型信号量，而且，可能用到的信号量数不是定值。此外，每增加一个MiniGUI线程，需要的信号量都会至少增加3个。Minigui所使用的POSIX互斥量和信号量都是在UCOS2信号量的基础上实现的，每一个POSIX信号量对应一个UCOS2信号量，所以，系统最好为MiniGUI本身保留至少10个事件控制块，每增加一个MiniGUI线程则增加4个事件控制块。建议把OS\_CFG.H文件中的OS\_MAX\_EVENTS值定义为大于32的值。

每个minigui线程所所需的栈大小为8K左右，在创建线程或任务的时候指定一个8K－24K左右大小的栈是比较合适的。

### 2.5.7 MiniGUI入口函数

uC/OS-II版本的minigui函数库的入口函数是minigui\_entry，该函数是为main函数不存在或者定义在minigui外部的情况下定义的（普通情况下，如Linux上，minigui把main函数封装在库里面）。

int minigui\_entry (int argc, const char\* argv\[\]);

在使用minigui的其它函数之前应该先调用该函数。也就是说，通过该函数启动MiniGUI函数库及MiniGUI应用程序。

uC/OS-II上我们可以参考如下的方式来启动minigui。

static void\* mg\_main\_task (void\* args)

{

OSTimeDly (400);

minigui\_entry (0, NULL);

return NULL;

}

void minigui\_app\_entry (void)

{

pthread\_t main\_thread;

if (ucos2\_malloc\_init ()) {

fprintf (stderr, "Can not init our own malloc implementation for
uC/OS-II.\\n");

return;

}

if (ucos2\_posix\_pthread\_init ()) {

fprintf (stderr, "Can not init our own pthread implementation for
uC/OS-II.\\n");

return;

}

pthread\_create (&main\_thread, NULL, mg\_main\_task, NULL);

}

上述参考代码在include/mgdrv-ucosii.c文件中。

在使用minigui之前，我们需要调用ucos2\_malloc\_init和ucos2\_posix\_pthread\_init函数进行堆内存管理模块和POSIX线程模块的初始化，然后调用pthread\_create函数创建一个线程，在该线程中调用minigui\_entry函数开始minigui，该线程就是minigui的主线程。

建议只在POSIX线程中使用minigui相关的内容，也就是说，不直接在UCOS2的任务中调用minigui\_entry启动minigui或者调用minigui的函数。

minigui应用程序部分的入口函数（主线程的入口函数）仍然是MiniGUIMain，minigui的其它应用程序线程一般在主线程中创建。

### 2.5.8编译minigui应用程序。

编译好minigui库之后，把库文件加入到实验1的工程中，重新编译工程，查看运行结果。
