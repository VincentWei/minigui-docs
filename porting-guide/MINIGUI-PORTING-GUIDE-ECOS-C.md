![](media/image1.jpeg){width="2.2333333333333334in"
height="1.3736111111111111in"}

MiniGUI for eCos

移植指南

适用于 MiniGUI Ver 1.6.x

北京飞漫软件技术有限公司

2005 年 2 月

版权声明
========

《MiniGUI for eCos 移植指南》 for MiniGUI Version 1.6.x。

版权所有 (C) 2005 北京飞漫软件技术有限公司，保留所有权利。

无论您以何种方式获得该手册的全部或部分文字或图片资料，无论是普通印刷品还是电子文档，北京飞漫软件技术有限公司仅仅授权您阅读的权利，任何形式的格式转换、再次发布、传播以及复制其内容的全部或部分，或将其中的文字和图片未经书面许可而用于商业目的，均被视为侵权行为，并可能导致严重的民事或刑事处罚。

目 录
=====

版权声明 2

目 录 3

1 移植MiniGUI到eCos 4

1.1原理 4

1.2在Linux环境中编译MiniGUI库 4

1.2.1eCos的获取和安装 4

1.2.2 建立eCos编译环境 4

1.2.3 编译eCos 5

1.2.4MiniGUI的配置头文件 5

1.2.5 MiniGUI的资源配置文件 6

1.3图形引擎 7

1.4输入引擎 8

1.5编译minigui应用程序 8

1.6 下载到iPAQ中 8

1 移植MiniGUI到eCos
===================

1.1原理
-------

MiniGUI
软件架构的设计充分考虑了可移植性，核心的主要结构包括消息处理、窗口管理和图形绘制等主要模块都是建立在得到广泛支持的POSIX线程库接口的基础之上；其次，MiniGUI通过操作系统和硬件抽象层（porting
layer）隐藏了特定操作系统及底层硬件的细节，这大大减轻了MiniGUI移植到不同操作系统和硬件平台的工作量。

由于eCos操作系统提供了POSIX相关API的支持，因此，将 MiniGUI 移植到 eCos
是相对容易的一项工作。

我们把MiniGUI for
eCos版本移植到不同的硬件平台上时，通常需要针对该硬件平台的LCD驱动和输入驱动（触摸屏、鼠标、键盘）对图形引擎和输入引擎做相应的修改。

1.2在Linux环境中编译MiniGUI库
-----------------------------

一般而言，我们可以在Linux的环境下把MiniGUI库交叉编译为一个静态库，如libminigui.a，然后在编译MiniGUI应用程序时指定MiniGUI头文件搜索路径和指定链接libminigui.a库，最后生成一个包括eCos、MiniGUI和应用程序代码在内的可执行文件（映像）。编译应用程序和链接生成目标映像的工作一般在Linux开发环境中进行。本文如下的内容，如无特别指明，如下涉及的移植都是基于iPAQ而言(iPAQ是基于StrongARM的一款高端手持终端产品，它含有触摸屏以及几个控制键)。

### 1.2.1eCos的获取和安装

> \#获取安装脚本
>
> \$wget –passive-ftp
> [*ftp://ecos.sourceware.org/pub/ecos/ecos-install.tcl*](ftp://ecos.sourceware.org/pub/ecos/ecos-install.tcl)
>
> \#从网络安装eCos和编译器
>
> \$sh ecos-install.tcl
>
> 获取源代码解压后在当前目录生成一个ecos-2.0目录，其中包括了ecos的源代码和ecosfonfig配置工具(详细的信息请参*http://ecos.sourceware.org/getstart.html*的说明。)。

### 1.2.2 建立eCos编译环境

获取交叉编译工具ecoscentric-gnutools-arm-elf-1.4-2.i386linux.tar.gz2,
该文件解压后在当前目录生成一个gnutools目录，编译器名为arm-elf-gcc.
修改文件：\~/.bash\_profile，增加如下定定义：

\#for eCos 2.0

\#eCos 源代码packages路径

ECOS\_REPOSITORY=/opt/ecos/ecos-2.0/packages

\#eCos 配置工具执行文件所在路径

PATH=/opt/ecos/ecos-2.0/tools/bin:\$PATH

\#eCos编译器arm-elf-gcc所在路径

PATH=/opt/ecos/gnutools/arm-elf/bin:\$PATH

export PATH

注意：必须在PATH环境变量中把eCos工具所在的路径设在最前面，否则不能正常编译！

### 1.2.3 编译eCos 

> \$ mkdir /tmp/ipaq\_ecos
>
> \$ cd /tmp/ipaq\_ecos
>
> \$ ecosconfig new ipaq net
>
> \$ ecosconfig add romfs
>
> \$ ecosconfig import
> NFD.ecm(http://sources/redhat.com/redboot/ipaq/NFD.ecm）
>
> \$ ecosconfig tree
>
> \$ make

(具体信息请参考http://sources.redhat.com/redboot/ipaq/nanox.htmp)

### 1.2.4MiniGUI的配置头文件

编译minigui之前，我们首先需要确定minigui的配置，这是在配置头文件config.h中指定的。

MiniGUI的配置头文件config.h中以条件编译宏的方式定义了MiniGUI的一些特性和选项。MiniGUI库中已经针对eCos
iPAQ开发板提供了一个生成配置文件的脚本build-ecos-ipaq-wifi，位于build目录下，可以使用该脚本生成配置文件config.h。

\$./build/build-ecos-ipaq-wifi

config.h中比较重要的配置选项如下：

使用auto输入引擎。Auto引擎在没有键盘等输入设备时可以用来模拟键盘和鼠标的输入，该引擎自动地产生键盘和鼠标的输入事件，在移植或测试时非常有用。如果在release版本使用键盘和触摸屏作为输入设备，就可以把该支持去掉。

/\* Define if include the automatic IAL engine \*/

\#define \_AUTO\_IAL 1

使用dummy输入引擎。该引擎什么也不干，在没有其它引擎时，使用该引擎可以使MiniGUI正常运作和显示，但是没有输入，主要用于移植和测试。

/\* Define if include the dummy IAL engine \*/

\#define \_DUMMY\_IAL 1

使用针对基于eCos操作系统的iPAQ输入引擎，驱动需要实现该引擎定义的相应驱动接口。

/\* Define if include the input engine for iPAQ \*/

\#define \_IPAQ\_IAL 1

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

非uinux的操作系统（如eCos）必须打开该选项。

/\* Define if compile for non-Uinux like OS \*/

\#define \_\_NOUNIX\_\_ 1

eCos操作系统必须打开该选项。

/\* Define if compile for eCos \*/

\#define \_\_ECOS\_\_ 1

**针对图形显示的选项：**

使用newgal图形引擎。Newgal图形引擎支持8位色及以上的显示。

/\* Define if use new GAL interfaces \*/

\#define \_USE\_NEWGAL 1

使用newgal中针对LCD的通用图形引擎，必须打开该选项。LCD驱动需要实现该引擎定义的相应访问接口。

\#define \_NEWGAL\_ENGINE\_COMMLCD 1

### 1.2.5 MiniGUI的资源配置文件

src/sysres/目录下的mgetc.c文件中定义了MiniGUI内建式资源及其它的配置，根据MiniGUI实际应用的操作系统和硬件平台的不同，该文件包含了针对目标系统的特定配置文件，对于iPAQ
wifi版本而言就是mgetc-ecos-ipaq-wifi文件。我们一般不需要修改mgetc文件，而是修改文mgetc-ecos-ipaq-wifi.c件。

\#include "mgetc-pc.c"

\#include "mgetc-ecos-ipaq-wifi.c"

mgetc-ecos-ipaq-wifi.c文件中定义了当前使用的输入和图形引擎、屏幕分辨率和颜色、字体等配置属性。

static char \*SYSTEM\_VALUES\[\] = {"commlcd", "ipaq", "/dev/ts",
"none"};

static char \*FBCON\_VALUES\[\] = {"106x120-16bpp"};

static char \*SYSTEMFONT\_KEYS\[\] =

{"font\_number", "font0", "font1", "font2", "default", "wchar\_def",
"fixed", "caption", "menu", "control"};

static char \*SYSTEMFONT\_VALUES\[\] =

{

"3","rbf-gothic-rrncnn-6-12-JISX0201-1",
"rbf-gothic-rrncnn-6-12-JISX0208-1", "\*-fixed-rrncnn-\*-16-JISX0208-1",

"0", "1", "1", "1", "2", "1"

};

SYSTEM\_VALUES的前两项分别指定图形引擎和输入引擎，在eCos版本中默认是commlcd通用图形引擎和iPAQ输入引擎，一般不需要修改。后面的两项针对使用鼠标的输入引擎，这里没有意义，可以不管。

FBCON\_VALUES指定LCD的屏幕分辨率和颜色深度，需要根据实际的LCD分辨率大小和颜色进行调整，对应于WiFi开发板就是106x120-16bpp。

SYSTEMFONT\_KEYS和SYSTEMFONT\_VALUES项定义了MiniGUI使用的系统字体，可根据实际需要修改。需要注意的是，除了rbf-fixed-rrncnn-6-12-ISO8859-1字体外，别的字体如果要用的话，需要在配置MiniGUI时把相应的选项enable，具体请参考MiniGUI用户手册的相关部分。

1.3图形引擎
-----------

MiniGUI for
eCos版本中对LCD的驱动使用统一的通用LCD图形引擎comm2lcd，该图形引擎的相关文件位于
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

li-&gt;fb = pSeudoGetFbAddress();

return 0;

}

pSeudoGetFbAddress
函数为驱动提供的获取framebuffer地址的函数，根据平台和驱动的不同而改变。

1.4输入引擎
-----------

MiniGUI for
eCos版本中对触摸屏和键盘的驱动针对iPAQ定制的输入引擎，该引擎的相关文件位于
src/ial/ 目录，包括ipaq.c和ipaq.h文件。

在ipaq.c里实现了如下几个比较重要的接口函数：

1）InitIPAQInput函数就是在src/ial/ial.c中所定义的iPAQ输入引擎的初始化函数。该函数打开两个设备：/dev/ts和/dev/kbd。前者是触摸屏的设备文件，后者是按键的设备文件。类似PC上的/dev/psaux设备和/dev/tty设备。在成功打开这两个设备文件之后，该函数设置了INPUT结构的其它一些成员。

2\) mouse\_update函数始终返回1, 表明更新鼠标状态成功。

3)
mouse\_getxy函数返回由其它函数准备好的鼠标位置数据，并作了适当地边界检查。

4)
mouse\_getbutton函数返回触摸屏状态，即用户是否触摸了屏幕，相当于是否按下了左键。

5)
keyboard\_update函数根据其它函数准备好的键盘信息，适当填充了state数组。

6\) keyboard\_state 函数直接返回了state数组的地址。

7)
wait\_event函数是输入引擎的核心函数。这个函数首先将先前打开的两个设备文件描述符与传入的in文件描述符集合在一起，然后调用了select系统调用。当select系统调用返回大于0的值时，该函数检查在两个文件描述符上是否有可读的数据等待读取，如果是则分别从两个文件描述符中读取触摸屏和按键数据。

1.5编译minigui应用程序
----------------------

可以参考MiniGUI库的编译方法在编译为一个静态库，然后在和项目其它代码链接生成目标映像。这里我们以fhas2应用套件为例：

编译时加上配置选项 –enable-ecos.
Ecos系统的初始化工作在main/ecos\_init.c文件中，该文件定义了main函数，因此，在MiniGUI头文件中的dti.c里，将\_\_ECOS\_\_部分定义的main函数改名为my\_ecos\_main.
ecos\_init.c文件中代码的主要作用是挂装文件系统，如果不需要文件系统，则不include该文件。编译后生成的startfhas是包含调试信息和elf文件头的执行文件，文件尺寸较大，需要用arm-elf-objcopy工具转换为raw
binary.

arm-elf-objcopy -O binary startfhas startfhas.bin

gzip startfhas.bin

如上的命令将生成startfhas.bin.gz.

1.6 下载到iPAQ中
----------------

redboot的下载请参看*http://sources.redhat.com/redboot/ipaq/*

把iPAQ放到坐架上，把数据线接到开发主机的串口，主机打开minicom，设置为38400
8N1.

打开minicom,启动iPAQ,将在minicom看到redboot的启动信息，在minicom界面迅速不断的按CTRL+C进入redboot的提示界面。输入如下命令把fhas装载到0x20000的内存地址

&lt;RedBoot&gt; lo -m xmodem -r -b 0x20000

通过minicom把startfhas.bin.gz下载到redboot.

输入如下命令可以执行下载到内存的fhas，注意，重启redboot后下载到内存的fhas将消失，需要重新下载！

&lt;RedBoot&gt; go 0x20040

如果需要将fhas
image烧写到iPAQ的flash上，首先需要把redboot中的eCos\_fhas分区删除

&lt;RedBoot&gt; fi delete eCos\_fhas

输入如下命令可以把下载到0x20000地址的fhas烧写到flash上，并重新创建一个eCos\_fhas分区

&lt;RedBoot&gt; fi cr eCos\_fhas -f 0x50600000 -l 0x300000 -b 0x20000 -r
0x20000 -e 0x20040

0x50600000为存放fhas的eCos\_fhas分区的flash地址，0x300000为eCos\_fhas区的大小。

重新启动iPAQ后会自动启动fhas.也可以在redboot中按如下命令启动fhas:

&lt;RedBoot&gt; fi loa -d eCos\_fhas

&lt;RedBoot&gt; go 0x20040
