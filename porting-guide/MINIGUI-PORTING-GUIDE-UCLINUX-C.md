![](media/image1.jpeg){width="2.234027777777778in"
height="1.3743055555555554in"}

MiniGUI for uClinux

实验指导书

适用于 MiniGUI Ver 1.6.x

北京飞漫软件技术有限公司

2004 年 8 月

版权声明
========

《MiniGUI for uClinux 实验指导书》 for MiniGUI Version 1.6.x。

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

1.4实验设备及工具 1

1.5实验原理 1

1.6实验步骤 2

1.6.1 分析MiniGUI应用程序helloworld。 2

1.6.2 编译并运行helloworld应用程序 7

实验2 MiniGUI的图形绘制 10

2.1实验目的 10

2.2实验内容 10

2.3预备知识 10

2.4实验工具 10

2.5实验原理 10

2.5.1 MiniGUI图形系统的架构 10

2.5.2 MiniGUI的绘图机制 11

2.6实验步骤 12

2.6.1 分析gdidemo应用程序 12

2.6.2编译并运行gdidemo程序 15

实验3 MiniGUI 的输入引擎 17

3.1实验目的 17

3.2实验内容 17

3.3预备知识 17

3.4实验设备及工具 17

3.5实验原理 17

3.5.1触摸屏与显示器的配合 17

3.5.2 MiniGUI对触摸屏的支持原理 18

3.6实验步骤 19

3.6.1分析触摸屏程序 19

3.6.2校正触摸屏坐标 20

实验四 移植MiniGUI到uClinux 22

4.1实验目的 22

4.2实验内容 22

4.3预备知识 22

4.4实验设备及工具 22

4.5实验步骤 22

4.5.1开发环境的配置 22

4.5.2 MiniGUI的编译选项设置 23

4.5.3 MINIGUI内建资源的设置 24

4.5.4编译及安装过程 24

实验1 MiniGUI的程序架构
=======================

1.1实验目的
-----------

1)  []{#_Toc79758209 .anchor}了解MiniGUI的基本结构。

2)  了解MiniGUI程序设计的基本方法。

3)  了解MiniGUI应用程序的编译和运行。

1.2实验内容
-----------

1)  []{#_Toc79758210 .anchor}分析并了解MiniGUI应用程序helloworld。

2)  在开发板上运行helloworld程序。

1.3预备知识
-----------

1)  []{#_Toc79758211
    .anchor}掌握在uClinux集成开发环境中编写和调试程序的基本过程。

2)  了解ARM应用程序的框架结构。

3)  掌握Linux下的程序编译与交叉编译。

1.4实验设备及工具
-----------------

硬件：NET-ARM3000嵌入式试验仪，PC机pentumn500以上，硬盘40G以上，内存大于128M。

软件：PC机操作系统redhat linux9.0+minicom+uClinux开发环境。

1.5实验原理
-----------

MiniGUI是一个著名的自由软件项目，项目的目标是为基于Linux的实时嵌入式系统提供一个轻量级的图形用户界面支持系统。MiniGUI为应用程序定义了一组轻量级的窗口和图形设备接口。利用这些接口，每个应用程序可以建立多个窗口，而且可以在这些窗口中绘制图形且互不影响。用户也可以利用MiniGUI建立菜单、按钮、列表框等常见的GUI元素。

MiniGUI可以具有两种截然不同的运行时模式：”MiniGUI-Threads”或者”MiniGUI-Lite”。运行在MiniGUI-Threads上的程序可以在不同的线程中建立多个窗口，但所有的窗口在一个进程中运行。相反，运行在MiniGUI-Lite上的每个程序是单独的进程，每个进程也可以建立多个窗口。MiniGUI-Threads适合于具有单一功能的实时系统，而MiniGUI-Lite则适合于具有良好扩展性的嵌入式系统，比如要下载并运行第三方应用程序的智能手持终端。

1.6实验步骤
-----------

### 1.6.1 分析MiniGUI应用程序helloworld。

该程序的源代码在mgsamples-1.6.0-uclinux/src目录下。

1)  头文件

helloworld.c的开始所包括的四个头文件是所有MiniGUI应用程序都必须包括的头文件。

-   common.h 包括MiniGUI常用的宏及数据类型的定义。

-   minigui.h 包含了全局的和通用的接口函数以及某些杂项函数的定义。

-   gdi.h 包含了MiniGUI绘图函数的接口定义。

-   window.h
    > 包含了窗口有关的宏、数据类型、数据结构的定义以及函数接口声明

-   control.h 包含了libminigui中所有内建控件的接口定义。

1)  程序入口点

一个c程序的入口点为main函数，而一个MiniGUI程序的入口点为MiniGUIMain，该函数的圆型如下：

int MiniGUIMain (int argc, const char\* argv\[\])

main函数已经在MiniGUI的函数库中定义了，该函数在进行一些MiniGUI的初始化工作之后调用MiniGUIMain函数。所以，每个MiniGUI应用程序(无论是服务器端程序mginit还是客户端应用程序)的入口点均为MiniGUIMain函数。参数argc和argv与C程序main函数的参数argc和argv的含义是样的，分别为命令行参数个数和参数字符串数组指针。

1)  创建和显示主窗口

hMainWnd = CreateMainWindow(&CreateInfo);

每个MiniGUI应用程序的初始界面一般都是一个主窗口，你可以通过调用CreateMainWindow函数来创建一个主窗口，其参数是一个指向MAINWINCREATE结构的指针，本例中就是CreateInfo，返回值为所创建的主窗口的句柄。MAINWINCREATE结构描述一个主窗口的属性，你在使用CreateInfo创建主窗口之前，需要设置它的各项属性。

CreateInfo.dwStyle = WS\_VISIBLE | WS\_BORDER | WS\_CAPTION;

设置主窗口风格，这里把窗口设为初始可见的，并具有边框和标题栏。

CreateInfo.deExStyle = WS\_EX\_NONE;

设置主窗口的扩展风格，该窗口没有扩展风格。

CreateInfo.spCaption = “HelloWorld”

设置主窗口的标题为”HelloWorld”。

CreateInfo.hMenu = 0;

设置主窗口的主菜单，该窗口没有主菜单。

CreateInfo.hCursor = GetSystemCursor(0);

设置主窗口的光标为系统缺省光标。

CreateInfo.hIcon = 0;

设置主窗口的图标，该窗口没有图标。

CreateInfo.MainWindowProc = HelloWinProc;

设置主窗口的窗口过程函数为HelloWinProc，所有发往该窗口的消息由该函数处理。

CreateInfo.lx = 0;

CreateInfo.ty = 0;

CreateInfo.rx = 320;

CreaetInfo.by=240;

设置主窗口在屏幕上的位置，该窗口左上角位于(0, 0)，右下角位于(320, 240)。

CreateInfo.iBkColor = PIXEL\_lightwhite;

设置主窗口的背景色为白色，PIXEL\_lightwhite是MiniGUI预定义的象素值。

CreateInfo.dwAddData = 0;

设置主窗口的附加数据，该窗口没有附加数据。

CreateInfo.hHosting = HWND\_DESKTOP;

设置主窗口的托管窗口为桌面窗口。

ShowWindow(hMainWnd, SW\_SHOWNORMAL);

创建完主窗口之后，还需要调用ShowWindow函数才能把所创建的窗口显示在屏幕上。ShowWindow的第一个参数为所要显示的窗口句柄，第二个参数指明显示窗口的方式(显示还是隐藏)，SW\_SHOWNORMAL说明要显示主窗口，并把它置为顶层窗口。

1)  进入消息循环

在调用ShowWindow函数之后，主窗口就会显示在屏幕上。和其他GUI一样，现在是进入消息循环的时候了。MiniGUI为每一个MiniGUI程序维护一个消息队列。在发生事件之后，MiniGUI将事件转换为一个消息，并将消息放入目标程序的消息队列之中。应用程序现在的任务就是执行如下的消息循环代码，不断地从消息队列中取出消息，进行处理：

while (GetMessage(&Msg, hMainWnd) {

TranslateMessage(&Msg);

DispatchMessage(&Msg);

}

Msg变量是类型为MSG的结构，MSG结构在window.h中。

GetMessage函数调用从应用程序的消息队列中取出一个消息：

GetMessage(&Msg, hMainWnd);

该函数调用的第二个参数为要获取消息的主窗口的句柄，第一个参数为一个指向MSG结构的指针，GetMessage函数将用从消息队列中取出的消息来填充该消息结构的各个域，包括：

-   hwnd
    > 消息发往的窗口的句柄。在helloworld.c程序中，该值与hMainWnd相同。

-   message
    > 消息标志符。这是一个用于标志消息的整数值。每一个消息均有一个对应的预定义标志符，这些标志符定义在window.h头文件中，以前缀MSG开头。

-   wParam 一个32位的消息参数，其含义和值根据消息的不同而不同。

-   lParam 一个32位的消息参数，其含义和值取决于消息的类型。

-   time
    > 消息放入消息队列中的时间。只要从消息队列中取出的消息不为MSG\_QUIT，GetMessage就返回一个非0值，消息循环将持续下去。MSG\_QUIT消息使GetMessage返回0，导致消息循环的终止。

TranslateMessage(&Msg);

TranslateMessage函数把击键消息转换为MSG\_CHAR消息，然后直接发送到窗口过程函数。

DispatchMessage(&Msg);

DispatchMessage函数最终把消息发往该消息的目标窗口的窗口过程，让他进行处理，在本例中，该窗口过程就是HelloWinProc。也就是说，MiniGUI在DispatchMessage函数中调用主窗口的窗口过程函数(回调函数)对发往该主窗口的消息进行处理。处理完消息之后，应用程序的窗口过程函数将返回到DispatchMessage函数中，而DispatchMessage函数最后又将返回到应用程序代码中，应用程序又从下一个GetMessage函数调用开始消息循环。

1)  窗口过程函数

窗口过程函数是MiniGUI程序的主体部分，应用程序实际所作的工作大部分都发生在窗口过程函数中，因为GUI程序的主要任务就是接受和处理窗口收到的各种消息。

在helloworld.c程序中，窗口过程是名为HelloWinProc的函数。窗口过程函数可以由程序员任意命名，CreateMainWindow函数根据MAINWINCREATE结构类型的参数中指定的窗口过程创建主窗口。

窗口过程函数总是定义为如下形式：

static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM
lParam)

窗口过程的4个参数与MSG结构的前四个域是相同的。第一个参数hWnd是接受消息的窗口的句柄，它与CreateMainWindow函数的返回值相同，该值标识了接受该消息的特定窗口。第二个参数与MSG结构中的message域相同，它是一个标识窗口所收到消息的整数值。最后两个参数都是32位的消息参数，它提供和消息相关的特定信息。

程序通常不直接调用窗口过程函数，而是由MiniGUI进行调用；也就是说，它是一个回调函数。

窗口过程函数不予处理的消息应该传给DefaultMainWinProc函数进行缺省处理，从DefaultMainWinProc返回的值必须由窗口过程返回。

1)  屏幕输出

程序在响应MSG\_PAINT消息时进行屏幕输出。应用程序应首先通过调用BeginPaint函数来获得设备上下文句柄，并用它调用GDI函数来执行绘制操作。这里，程序使用TextOut文本输出函数在客户区的中部显示了一个”Hello
world!”字符串。绘制结束之后，应用程序应调用EndPaint函数释放设备上下文句柄。

1)  程序的退出

用户单击窗口右上角的关闭按钮时窗口过程函数将收到一个MSG\_CLOSE消息。Helloworld程序在收到MSG\_CLOSE消息时调用DestroyMainWindow函数销毁主窗口，并调用PostQuitMessage函数在消息队列中投入一个MSG\_QUIT消息。当GetMessage函数取出MSG\_QUIT消息时将返回0，最终导致程序退出消息循环。

程序最后调用MainWindowThreadCleanup清除主窗口所使用的消息队列等系统资源并由MiniGUIMain返回。

### 1.6.2 编译并运行helloworld应用程序

1)  解压缩mgsamples-1.6.0.tar.gz包，生成mgsamples-1.6.0-uclinx目录。

tar zxvf mgsamples-1.6.0.tar.gz

1)  进入mgsamples-1.6.0-uclinux目录。

cd mgsamples-1.6.0-uclinux

1)  生成configure脚本和Makefile文件，主要利用了GNU的autoconf和automake工具软件

./autogen.sh

1)  运行configure脚本，因为是交叉编译，所以有一些比较特殊的配置。

./build-uclinux-arm3000

这是为此开发板专门编写的编译脚本。CC=arm-uclibc-gcc表示使用的交叉编译器的名称，CFLAGS和LDFLAGS指定了uClinux，uClibc的库和头文件路径，另外还指定了MiniGUI的头文件和库的路径。--build(指定编译的机器)，--host(表示宿主系统名)，--target(目标运行的系统类型)，因为我们的开发板系统是arm-linux，所以在这里指定—host=arm-elf-linux，--target=arm-elf-linux，
--build=i386-linux。

1)  进行应用程序的编译

make

make完成没有出现错误表示编译成功，此时在src目录下出现了很多可执行的应用程序。

1)  将应用程序拷贝到/uclinux目录下

cp src/helloworld /uclinux/demos

1)  接下来就可以通过minicom连接开发板运行应用程序了。先打开minicom通讯终端。

minicom

连接好开发板和主机，打开开发板电源，就可以在minicom上操作开发板了。首先要将主机的/uclinux装载到开发板上。

mount –t nfs 192.168.1.xx:/uclinux /host

这里的IP地址是PC主机的IP地址。这是通过nfs方式将主机的文件系统装载到开发板上。

然后需要对开发板做一些运行MiniGUI应用程序的准备工作。

ln –s /dev/fb/0 /dev/fb0

建立符号连接，/dev/fb0是MiniGUI应用程序要打开的一个设备。

mknod /dev/tty0 c 4 0

建立/dev/tty0设备，这也是MiniGUI应用程序输出所必需的设备。

运行helloworld应用程序

./helloworld

实验2 MiniGUI的图形绘制
=======================

2.1实验目的
-----------

1)  了解MiniGUI的绘图原理。

2)  分析gdidemo程序。

3)  编译并运行gdidemo程序。

2.2实验内容
-----------

1)  在开发板上运行gdidemo程序，观察运行效果。

2.3预备知识
-----------

1)  掌握在uClinux开发环境中编写和调试程序的基本过程。

2)  了解ARM应用程序的框架结构。

3)  了解MiniGUI运行环境的编译，安装和配置。

2.4实验工具
-----------

硬件：NET-ARM3000嵌入式实验仪，PC机pentumn500以上，硬盘40G以上，内存大于128M。

软件：PC机操作系统redhat linux9.0 + minicom + uClinux开发环境。

2.5实验原理
-----------

### 2.5.1 MiniGUI图形系统的架构

图形设备接口(GDI : Graphics Device
Interface)是GUI系统的一个重要组成部分。通过GDI，GUI程序就可以在计算机屏幕上，或者其他的显示设备上进行图形输出，包括基本绘图和文本输出。

为了把底层图形设备和上层图形接口分离开来，提高MiniGUI图形系统的可移植性，MiniGUI中引入了图形抽象层(Graphics
Abstract
Layer，GAL)的概念。图形抽象层定义了一组不依赖于任何特殊硬件的抽象接口。所有顶层的图形操作都建立在这些抽象接口之上。而用于实现这一抽象接口的底层代码称为”图形引擎”，类似操作系统中的驱动程序。

在新的GAL和GDI接口设计中，我们将GAL的接口进行了限制，而将原有许多由GAL引擎完成的图形输出函数，提高到上层GDI函数中完成。这样，NEWGAL主要实现的绘图功能限制在位块操作上，比如矩形填充和Blitting操作；而其他的高级图形功能，则全部由NEWGDI函数实现。

新的NEWGAL接口能够有效利用显示卡上的显示内存，并充分利用硬件加速功能。NEWGAL引擎能够管理未使用的显示内存并分配给应用程序使用。这样，一方面可以节省系统内存的使用，另一方面，可以充分利用显示卡提供的加速功能，在显示内存的两个不同内存区域之间进行快速的位块操作，也就是常说的Blitting。上层NEWGDI接口在建立内存DC设备时，将首先在显示内存上分配内存，如果失败，才会考虑使用系统内存。这样，如果NEWGAL引擎提供了硬件加速功能，两个不同DC设备之间的Blitting操作(即GDI函数BitBlt)，将以最快的速度运行。

### 2.5.2 MiniGUI的绘图机制

应用程序使用窗口来作为主要的输出设备，也就是说，MiniGUI应用程序在它的窗口之内进行绘制。MiniGUI对整个屏幕上的显示输出进行管理。如果窗口移动之类的动作引起窗口内容的改变，MiniGUI对窗口内应该被更新的区域打上标志，然后给相应的应用程序窗口发送一个MSG\_PAINT消息，应用程序收到该消息后就进行必要的绘制，以刷新窗口的显示。如果窗口内容的改变是由应用程序自己引起的，应用程序可以把受影响而需更新的窗口区域打上标志，并产生一个MSG\_PAINT消息。如果需要在一个窗口内绘制，应用程序首先要获得该窗口的设备上下文句柄。应用程序的大部分绘制操作是在处理MSG\_PAINT消息的过程中执行的，这时，应用程序应调用BeginPaint函数来获得设备上下文句柄。如果应用程序的某个操作要求立即的反馈，例如处理键盘和鼠标消息时，它可以立刻进行绘制而不用等待MSG\_PAINT消息。应用程序在其他时候绘制时可以调用GetDC或GetClientDC来获得设备上下文句柄。

应用程序一般在一个图形上下文(graphics
context)上调用图形系统提供的绘制原语进行绘制。上下文是一个记录了绘制原语所使用的图形属性的对象。当你想在一个图形设备(如显示器屏幕)上绘图时，你首先必须获得一个设备上下文句柄。然后在GDI函数中将该句柄作为一个参数，标志你在绘图时所要使用的图形设备上下文。设备上下文中包含许多确定GDI函数如何在设备上工作的当前属性，这些属性使得传递给GDI函数的参数可以只包含起始坐标或者尺寸信息，而不必包含在设备上显示对象时需要的其他信息，因为这些信息是设备上下文的一部分。设备上下文实际上是GDI内部保存的数据结构，与特定的显示设备相关。设备上下文句柄是一个代表设备上下文的数值，程序适用该句柄。

2.6实验步骤
-----------

### 2.6.1 分析gdidemo应用程序

该程序的源代码在mde-1.6.0-uclinux/gdidemo目录下

这个程序的消息处理函数是GDIDemoWinProc，对于按键信息有不同的响应。

1)  ‘1’键的响应函数

当点击数字键‘1’时，会调用GDIDemo\_NormalLines函数，该函数的功能是画普通的直线和曲线。

SetPenColor (hdc, PIXEL\_yellow);

LineTo (hdc, tox, toy);

设置画笔颜色为PIXEL\_yellow，在循环中每次改变画笔颜色并进行绘制直线的操作。

Circle (hdc, tox, toy, rand() % DEFAULT\_X);

在后一个循环中，进行画圆的操作。

Ellipse (hdc, tox, toy, rand() % DEFAULT\_X, rand() % DEFAULT\_Y);

CircleArc (hdc, tox, toy, rand() % DEFAULT\_X, rand() % 360, rand() %
360);

如果使用NEWGAL的话，还将进行绘制ellipse和arc的操作。

1)  ‘2’键的响应函数

点击‘2’键时，会调用GDIDemo\_XoredLines函数，该函数的功能是绘制异或的直线和曲线。

SetRasterOperation (hdc, ROP\_XOR);

设置异或模式，然后再进行绘制操作，操作部分与上面的一样。

1)  ‘3’键的响应函数

点击‘3’键时，会调用GDIDemo\_Filling函数，该函数的功能是填充区域。

首先是fillbox的循环

SetBrushColor (hdc, rand() % nr\_colors);

设置画刷颜色

FillBox (hdc, tox, toy, rand() % DEFAULT\_X, rand() % DEFAULT\_Y);

进行填充。然后是fillrect循环

SetRasterOperation (hdc, ROP\_XOR);

设置异或模式

FillBox (hdc, tox, toy, rand，rand() % DEFAULT\_X, rand() % DEFAULT\_Y);

后面两个循环分别是以异或模式填充circle和ellipse

1)  ‘4’键的响应函数

点击‘4’键时，会调用GDIDemo­\_NormalBitmaps函数，该函数的功能是绘制普通位图。

先从本机导入一个位图

LoadBitmap (hdc, &bitmap, “res/sample.bmp”);

在循环中，进行填充位图的操作

FillBoxWithBitmap (hdc, tox, toy, 0, 0, &bitmap);

在使用NEWGAL的情况下，还用或模式和异或模式进行填充位图的操作

SetRasterOperation (hdc, ROP\_XOR);

SetRasterOperation (hdc, ROP\_OR);

最后要清除导入的位图资源

UnloadBitmap (&bitmap)

1)  ‘5’键的响应函数

点击‘5’键时，会调用GDIDemo\_TransparentBitmaps函数，该函数的功能是绘制透明位图。

主要是对bitmap进行 ColorKey的设置

bitmap.bmType = BMP\_TYPE\_COLORKEY;

bitmap.bmColorKey =- GetPixelInBitmap (&bitmap, 0, 0);

然后再进行填充位图的操作

FillBoxWithBitmap (hdc, tox, toy, 0, 0, &bitmap);

1)  ‘6’键的响应函数

点击‘6’键时，会调用GDIDemo\_AlphaBlendedBitmaps函数，该函数的功能是绘制alpha混合位图

先导入位图文件

LoadBitmap (hdc, &bitmap, “res/icon.bmp”);

然后将bitmap的类型设为Alpha模式

bitmap.bmType = BMP\_TYPE\_ALPHACHANNEL;

在循环中填充位图

bitmap.bmAlpha = rand() % 256;

FillBoxWithBitmap (hdc, tox, toy, 0, 0, &bitmap);

再设置alpha模式和透明模式

bitmap.bmType=BMP\_TYPE\_ALPHACHANNEL|BMP\_TYPE\_COLORKEY;

bitmap.bmColorKey = GetPixelInBitmap (&bitmap, 0, 0);

在循环中填充位图

bitmap.bmAlpha = rand() % 256;

FillBoxWithBitmap (hdc, tox, toy, 0, 0, &bitmap);

1)  ‘7’键的响应函数

点击‘7’键时，会调用GDIDemo\_MemDC函数，该函数的功能是MemoryDC的操作。

先得到一个memorydc

mem\_dc = CreateCompatibleDC (hdc);

设置画刷颜色

SetBrushColor (mem\_dc, 0);

进行填充操作

FillBox (mem\_dc, 0, 0, 65535, 65535);

在循环中进行各种绘制操作

SetPenColor (mem\_dc, rand() % DEFAULT\_WIDTH);

LineTo (mem\_dc, tox, toy);

Circle (mem\_dc, tox, toy, rand() % DEFAULT\_X);

BitBlt(mem\_dc,0,0,rand()%DEFAULT\_WIDTH,rand()%DEFAULT\_WIDTH, hdc,
rand() % DEFAULT\_WIDTH, rand() % DEFAULT\_WIDTH, 0);

如果使用NEWGAL，还可以进行对MemoryDC设置ColorKey的操作

SetMemDCColorKey (mem\_dc, MEMDC\_FLAG\_SRCCOLORKEY, 0);

还可以用Alpha模式设置MemoryDC

mem\_dc = CreateMemDC (400, 100, 16, MEMDC\_FLAG\_HWSURFACE |
MEMDC\_FLAG\_SRCALPHA, 0x0000F000, 0x00000F00, 0x000000F0, 0x0000000F);

同样也可以对MemoryDC设置Alpha和ColorKey

mem\_dc = CreateMemDC (400, 100, 32, MEMDC\_FLAG\_HWSURFACE |
MEMDC\_FLAG\_SRCALPHA | MEMDC\_FLAG\_SRCCOLORKEY, 0x00FF0000,
0x0000FF00, 0x000000FF, 0x00000000);

### 2.6.2编译并运行gdidemo程序

解压缩mde-1.6.0.tar.gz包，生成mde-1.6.0-uclinux目录

tar zxvf mde-1.6.0.tar.gz

进入mde-1.6.0-uclinux目录

cd mde-1.6.0-uclinux

生成configure脚本和Makefile文件

./autogen.sh

运行configure脚本

./build-uclinux-arm3000

这个脚本与实验一中编译helloworld的脚本相同，在此不再重复。

进行应用程序的编译

cd gdidemo

make

编译完成后在gdidemo目录下会生成gdidemo可执行程序

将应用程序拷贝到/uclinux目录下

cp gdidemo /uclinux

将运行gdidemo所需的资源拷贝到/uclinux目录下

cp –r res /uclinux

在minicom中运行gdidemo应用程序

./gdidemo

实验3 MiniGUI 的输入引擎
========================

3.1实验目的
-----------

1)  了解触摸屏的基本结构，原理。

2)  了解MiniGUI对触摸屏的支持原理。

3)  练习对触摸屏进行校正。

3.2实验内容
-----------

启动Linux下的minicom，在开发板进行正确的环境配置，运行触摸屏校正程序，对触摸屏进行校正，为后续试验做准备。

3.3预备知识
-----------

1)  掌握在uClinux集成开发环境中编写和调试程序的基本过程。

2)  了解ARM应用程序的框架结构。

3)  熟悉MiniGUI运行环境的编译，安装和配置。

3.4实验设备及工具
-----------------

硬件：NET-ARM3000嵌入式试验仪，PC机pentumn500以上，硬盘40G以上，内存大于128M。

软件：PC机操作系统redhat linux9.0 + minicom + uClinux开发环境。

3.5实验原理
-----------

### 3.5.1触摸屏与显示器的配合

ADS7843送回控制器的X与Y值仅是对当前触摸点的电压值的A/D转换值，它不具有实用价值。这个值的大小不但与触摸屏的分辨率有关，而且也与触摸屏与LCD贴合的情况有关。而且，LCD分辨率与触摸屏的分辨率一般来说是不一样的，坐标也不一样，因此，如果想得到体现LCD坐标的触摸屏位置，还需要在程序中进行转换。假设LCD分辨率是320x240，坐标原点在左上角；触摸屏分辨率是900x900，则转换公式如下：

xLCD = \[320 \* (x – x2) / (x1 – x2)\];

yLCD = \[240 \* (y – y2) / (y1 – y2)\];

如果坐标原点不一致，比如LCD坐标原点在右下角，而触摸屏原点在左上角，则还可以进行如下转换：

xLCD = 320 – \[320 \* (x – x2) / (x1 – x2)\];

yLCD = 240 – \[240 \* (y – y2) / (y1 – y2)\];

最后得到的值，便可以尽可能得使LCD坐标与触摸屏坐标一致，这样，更具有实际意义。

### 3.5.2 MiniGUI对触摸屏的支持原理

在MiniGUI中，我们引入了输入抽象层的概念，它定义了一组不依赖于任何特殊硬件的抽象接口，所有顶层的输入处理都建立在抽象接口之上。而用于实现这一抽象接口的底层代码称为”输入引擎”，类似操作系统中的驱动程序。这实际是一种面向对象的程序结构。利用这种抽象接口，我们可以将MiniGUI非常方便地移植到其他POSIX系统上，只需要根据我们的抽象层接口实现新的输入引擎即可。

在minigui/src/ial/ial.c中，定义了MiniGUI支持的所有输入引擎信息，每个输入引擎由一个INPUT结构表示，所有输入引擎构成了inputs结构数组。每个输入引擎在初始时定义了三个INPUT结构的成员：

-   id : 引擎名称，用作标志符。

-   init\_input :
    > 输入引擎的初始化函数。该函数负责对INPUT结构的其他成员赋值。

-   term\_input : 输入引擎的终止清除函数。

对于此开发板，我们的输入引擎为arm3000，同时实际的IAL引擎程序是arm3000.c，其中有包括对触摸屏和小键盘的支持。

3.6实验步骤
-----------

### 3.6.1分析触摸屏程序

我们首先对这块开发板的输入引擎源程序进行分析，源程序的位置在libminigui-1.6.0-uclinux/src/ial/arm3000.c。

在此主要分析其中几个比较重要的接口函数实现：

InitARM3000Input函数就是我们在src/ial/ial.c中所定义的arm3000输入引擎的初始化函数。该函数打开了两个设备：/dev/touchscreen/0raw和/dev/keyboard/0raw。前者是触摸屏的设备文件，后者是小键盘的设备文件。类似PC机上的/dev/psaux设备和/dev/tty设备。在成功打开这两个设备文件之后，该函数设置了INPUT结构的一些成员。注意，其中一些成员被赋值为NULL。

mouse\_update函数始终返回1，表明更新鼠标状态成功。

mouse\_getxy 函数返回由其他函数准备好的鼠标位置数据。

mouse\_getbutton
函数返回了触摸屏的状态，即用户是否触摸了屏幕，相当于是否按下了左键。

keyboard\_update
函数根据其他函数准备好的键盘信息，适当填充了state数组。对于按键信息，我们有两个初始化函数，分别表示了在NumLock键按下和非按下的时候的不同处理。

keyboard\_state 函数直接返回了state数组的地址。

wait\_event
函数是输入引擎的核心函数。这个函数首先将先前打开的两个设备的文件描述符与传入的in文件描述符集合并在了一起，然后调用了select系统调用。当select系统调用返回大于0的值时，该函数检查在两个文件描述符上是否有可读的数据等待读取，如果是，则分别从两个文件描述符中读取触摸屏和按键数据。

### 3.6.2校正触摸屏坐标

首先进入minigui源代码。

cd libminigui-1.6.0-uclinux

修改minigui源文件中的输入引擎，打印输出坐标的位置。

vi src/ial/arm3000.c

在wait\_event函数中，if (e &gt; 0)循环和if (ts &gt; 0 &&
FD\_ISSET(ts,in))循环中，有从底层读出坐标值的语句：

pos.x = data\[1\];

pos.y = data\[2\];

然后加上你的打印语句如

printf(“posx = %d, posy = %d\\n”, pos.x, pos.y);

保存退出。

重新编译MiniGUI并安装，具体安装步骤可以参考实验四。

make

编译MiniGUI

make install

安装MiniGUI

编译应用程序，在此我们还是以helloworld程序为例，可参考实验一。

cd mgsamples-1.6.0-uclinux

首先进行清空操作

make clean

然后进行编译

make

连接好PC机及目标板(Target)，在宿主机上运行minicom。

在触摸屏点击左上角，会在minicom中显示左上角坐标，记录下来为lx、ly，接着点击右下角，记录下minicom中显示的右下角坐标rx、ry。因为此开发板的分辨率是320x240，使用下列公式进行坐标转换：

mousex = (pos.x – lx) \* 320 / (rx – lx);

mousey = (pos.y – ly ) \* 240 / (ry – ly);

实验四 移植MiniGUI到uClinux
===========================

4.1实验目的
-----------

1)  了解MiniGUI与uClinux之间的联系。

2)  了解并掌握MiniGUI的编译和安装。

3)  了解如何移植MiniGUI到uClinux

4.2实验内容
-----------

编译和安装MiniGUI。熟悉针对不同的嵌入式操作系统如uClinux，MiniGUI应如何编译。

4.3预备知识
-----------

1)  掌握在uClinux集成开发环境中编写和调试程序的基本过程。

2)  了解ARM应用程序的框架结构。

3)  掌握Linux下的程序编译与交叉编译。

4.4实验设备及工具
-----------------

硬件：NET-ARM3000嵌入式试验仪，PC机pentumn500以上，硬盘40G以上，内存大于128M。

软件：PC机操作系统redhat linux9.0+minicom+uClinux开发环境。

4.5实验步骤
-----------

### 4.5.1开发环境的配置

在博创公司提供的开发光盘中包含了需要的开发工具软件，使用光盘中的install.sh脚本就可以把交叉编译器装上，交叉编译器安装在/usr/local/arm-linux-uClibc中。在根目录下创建了uclinux目录，里面包含了uClinux和uClibc及一些示例程序。然后编译uClinux内核（编译过程将在后面介绍），编译完成后开发环境也配置完成。在这个板子的开发过程中uClibc不需要重新编译，因为安装时就已经编译好了，只需编译内核即可。

### 4.5.2 MiniGUI的编译选项设置

MINIGUI的编译选项设置比较复杂，包括头文件的指定，链接库的指定，还有MINIGUI自身所要进行的一些配置。

关于这块开发板所用到的编译选项都在minigui的源文件中的buildlib-44b0-uptech这个脚本文件里定义，用文本编辑器打开此脚本文件可以看到文件内容。其中在行开头带有\#的表示注释，可以略过。

CC指定了使用的交叉编译器的名称为arm-uClibc-gcc。

CFLAGS和LDFLAGS的指定，分别表示头文件和链接库的指定。头文件须指定uClinux内核以及uClibc的include目录，链接库须指定uClibc的lib目录和uClinux内核的lib目录。

接下来是一些交叉编译时的基本配置了，--prefix指定了执行make
install时安装MINIGUI的路径，如果没有此选项将安装到默认的/usr/local下面，为了不与系统库发生冲突和编译方便，我们指定安装路径为/uclinux/minigui，然后是编译的基本选项包括—build(指定编译的机器)，--host（表示宿主系统名）--target(将要运行的系统类型)，--with-osname(表示目标主机的操作系统)。

然后是MINIGUI的编译选项。--enable-static，--disable-shared，这两个选项指定了MINIGUI以静态库的方式进行编译（这也是uClinux所要求的）。此版本的MINIGUI编译为线程版，这样可以单独运行我们的示例程序，所以不需要加上—enable-lite选项，当需要编译为进程版，则要加上。然后是—enable-incores，此选项指定MINIGUI以内建资源的方式进行编译，一般情况下，在编译完MINIGUI后还要把所需的资源文件下载到目标板上，但是如果使用内建资源方式的话，MINIGUI运行需要的一些位图，图标和字体等资源将被编译到代码中，运行时就不需要单独的资源文件了。不过使用内建资源方式不需要MiniGUI.cfg配置文件，所以需要手动修改源代码以符合特定的配置(在下面的内容中将会讲到)。然后是输入输出引擎的指定，—enable-newgal指定新的GAL，NEWGAL只支持8位色以上的线性显示模式，由于我们的板子上的LCD为256色，所以指定newgal，--enable-dummyial指定哑输入引擎（当没有输入设备时可以先指定为哑引擎）。其他的配置大多都是字体和图形支持的配置，为了节省空间一般都disable了，具体可以参考《MINIGUI用户手册》。

### 4.5.3 MINIGUI内建资源的设置

如果MINIGUI在编译的时候指定了—enable-incores选项，则使用内建资源方式进行编译，此时需要修改MINIGUI源代码的src/sysres/mgetc-uptech.c文件，在其中定义了SYSTEM\_VALUE数组，此数组包含了MINIGUI的输入输出设备信息，我们填上正确的输入输出设备名称如下

static char \*SYSTEM\_VALUES\[\] = {“fbcon”, “arm3000”, “/dev/mouse”,
“IMPS2”};

这行代码表示使用的输出设备为fbcon，输入设备为console，如果没有此输入设备将会自动使用dummy输入。然后在fbcon的显示信息中填写正确的显示设备信息如下

static char \*FBCON\_VALUES\[\] = {“320x240-8bpp”};

表示显示设备的大小为320x240，显示的颜色为8bpp即256色。

### 4.5.4编译及安装过程

1)  安装开发环境（包括交叉编译器及uClinux内核，uClibc）

将光盘放入光驱中，一般情况下系统会自动识别，如果没有识别的话，用mount –t
iso9660 /dev/hdb
/mnt/cdrom(此处假设光驱作为从盘)。用root用户执行开发光盘中的install脚本：

su –

password:（输入root用户的口令）

cd /mnt/cdrom

./install.sh

此安装脚本在/usr目录下安装了arm-linux-uclibc交叉编译器，其中还包括了uClibc的库，在/usr/local下面安装了arm-elf交叉编译器，但是在这块板子的移植过程中并没有用到，另外在根目录/下面创建了/uclinux目录，包含了uClinux的内核以及uClibc目录都拷贝到下面，可将此目录作为工作目录。

1)  编译uClinux内核

cd /uclinux/uClinux-2.4.x

make menuconfig

对uClinux进行基本的配置，如选择芯片，各种系统程序等。

make dep

对uClinux进行编译所关联的依赖性进行检查。

make

编译uClinux 。

1)  编译MINIGUI

进入MiniGUI源代码所在目录

cd libminigui-1.6.0-uclinux

使用autoconf/automake工具生成configure脚本和Makefile文件

./autogen.sh

执行编译脚本configure

./buildlib-uclinux-arm3000

使用已经为此开发板写好的编译脚本，关于脚本的内容参考4.5.2所写的MiniGUI的编译选项设置。进行编译：

make

1)  安装编译好的MiniGUI

make install

此时会将minigui安装到/uclinux目录下的minigui目录中。

在/uclinux/minigui目录中会有etc，include，lib三个目录。Etc中包含了MINIGUI的配置文件MiniGUI.cfg，由于我们使用内建资源的方式进行编译，所以此文件对于我们没有用处。include中是MINIGUI的头文件定义，lib中是MINIGUI编译的库，这都是我们编译开发MINIGUI应用程序所需要的东西。
