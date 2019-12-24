_MiniGUI 常见问题（中文版）_

## 控件问题

### 目前支持的控件类型有哪些

MiniGUI 核心库中提供了二十多种内置控件（详情可见[Datasheet for MiniGUI 3.2 (PDF)]）。
从 MiniGUI 3.0 版本开始，我们推荐开发者使用 mGNCS 组件中提供的控件，这些控件有：

  - Static Control
  - Button Control
  - List Box Control
  - Edit Box Control
  - Combo Box Control
  - Menu Button Control
  - Progress Bar Control
  - Track Bar Control
  - Toolbar Control
  - Property Sheet Control
  - Scroll Window Control
  - Scroll View Control
  - Tree View Control
  - List View Control
  - Month Calendar Control
  - Spin Box Control
  - Cool Bar Control
  - Animation Control
  - GridView Control
  - IconView Control
  - Scrollbar Control

有关 mGNCS 控件的使用示例，可见 mg-samples 示例程序包，或者如下链接：

https://github.com/VincentWei/mg-samples/tree/master/mgncs

在 mGNCS4Touch 组件中，我们提供了适合触摸屏操作的若干控件（这些控件常见于智能手机），
主要有：

  * 按钮导航栏
  * 图片导航栏
  * 日期、时间滚轮选择器
  * 封面流
  * 条目栏
  * 跟踪条
  * 动画开关

有关 mGNCS4Touch 控件的使用示例，请访问：

https://github.com/VincentWei/mgncs4touch/tree/master/samples

更加综合的 mGNCS 及 mGNCS4Touch 组件演示程序，请参阅：

https://github.com/VincentWei/cell-phone-ux-demo

### 是否支持双击事件

支持。请在窗口过程中处理 `MSG_LBUTTONDBLCLK` 或 `MSG_RBUTTONDBLCLK` 消息。
前者为鼠标左键的双击事件，后者为鼠标右键的双击事件。通常，用户在触摸屏上的
快速连续按击会被处理为 `MSG_LBUTTONDBLCLK` 消息。

### 是否支持移动事件，指针滑动触发，用于拖动、划屏等操作

支持，处理 `MSG_MOUSEMOVE` 相关消息即可。用户在触摸屏上的滑动，通常也会被处理为该消息。

### 是否支持聚焦、失焦事件，用于判断选中。

支持。请分别处理 `MSG_SETFOCUS` 和 `MSG_KILLFOCUS` 消息。

### 是否区分按下状态、弹起状态、使能状态、失能状态等并且分别配置效果

支持。通过使用不同的外观渲染器，或者自定义外观渲染器可定制按钮等控件的这些外观和效果。

可参阅如下示例程序：

  * [外观渲染器](https://github.com/VincentWei/mg-samples/tree/master/look_feel)
  * [自定义简单渲染器](https://github.com/VincentWei/mg-samples/tree/master/lf_tiny)
  * [自定义皮肤渲染器](https://github.com/VincentWei/mg-samples/tree/master/lf_skin)


### 是否支持渐变色填充FillBox

MiniGUI 核心库提供的 FillBox 不支持渐变色的填充，需要使用 mGPlus 矢量图形组件提供的
相关功能。mGPlus 是对 MiniGUI 核心库绘制功能的一个补充，其中包含了常见的 2D 矢量绘图
功能，包括路径、渐变色填充、颜色组合等。

具体示例代码，请访问：

  * [mGPlus 画刷示例](https://github.com/VincentWei/mg-samples/tree/master/mgplus/brush)

### 是否支持动态的图标

可使用 mGNCS 提供的动画控件，相关示例见 mg-demos 中的 cbplusui：

https://github.com/VincentWei/mg-demos/tree/master/cbplusui

### 没有滑轮控件，只能通过加减的方式来实现

请使用 mGNCS4Touch 中提供的滚轮控件。

### ListView控件中，不能加载图片

建议使用 mGNCS 中的 ListView 控件，该控件的条目内容可以非常灵活地调整。
比如 WiFi 选择列表，在 mg-demos 中就有相关的实现。

https://github.com/VincentWei/mg-demos/tree/master/cbplusui

### ListView控件，选中的行数是什么函数？有没有相关控件的获取控件行列信息的文档说明？

若使用 MiniGUI 核心库提供的 ListView 控件，请发送消息`LVM_GETSELECTEDITEM`获取当前选择的行。

有关 ListView 控件的文档，请阅读：

http://wiki.minigui.com/twiki/bin/view/Products/MiniGUIPGV32Part6Chapter14

### MessageBox 怎么改字体和文字大小？

`MessageBox` 使用的字体是默认控件字体，可通过修改 MiniGUI.cfg 配置文件中的
`systemfonts` 段设置来修改系统字体的大小。

MiniGUI 核心库提供的消息框是 PC 风格的，建议根据的应用场景自定义消息框，
可参考 mg-demos 中的相关示例。

https://github.com/VincentWei/mg-demos/tree/master/cbplusui

### 在miniStudio中设置了MENUBUTTON的字体，但是下拉框文字是乱码

一般是字符集设置错误引起，建议字体的字符集为 UTF8。另外，需要确认 MiniGUI.cfg
中 systemfont 段中的 menu 字体设置，是否为匹配的字体及字符集。

另外需要说明的是，miniStudio 工具不太成熟，我们建议 miniStudio 主要用于原型设计，
不建议在正式项目中使用。

## 显示问题

### 长字符串的显示

长字符串的滚动显示，需要自己实现。可参考 mgutils 中的 `mywins` , 里面有长文本上下滚动显示。

具体示例代码，请访问：

  * [长文本示例](https://github.com/VincentWei/mgutils/tree/master/src/mywins)

### 动态调节显示比例

这个需要应用自己处理，比如可以根据不同分辨率定义控件配置数据，在不同分辨率下使用不同的配置。


### 鼠标如何配置显示或隐藏

编译minigui时，可以通过选项 `--enable-cursor` , `--disable-cursor` 来打开/关闭鼠标的显示，
在 `--enable-cursor` 情况下，运行时可以通过函数 `ShowCursor` 来显示/隐藏鼠标。

函数原型如下:

    /**
     * \fn int GUIAPI ShowCursor (BOOL fShow)
     * \brief Shows or hides cursor.
     *
     * This function shows or hides cursor according to the argument \a fShow.
     * Show cursor when \a fShow is TRUE, and hide cursor when \a fShow is FALSE.
     * MiniGUI maintains a showing count value. Calling \a ShowCursor once, the
     * count will increase when \a fShow is TRUE, or decrease one when FALSE.
     * When the count is less than 0, the cursor will disapear actually.
     *
     * \param fShow Indicates show or hide the cursor.
     *
     * \return Cursor showing count value.
     */
    MG_EXPORT int GUIAPI ShowCursor (BOOL fShow);

### 如何在未连接任何显示设备的情况下，启动MiniGUI

正常使用时，要确保显示设备初始化正常后，再启动MiniGUI，比如用一个守护进程确认显示设备正常后，再启动MiniGUI。
在开发移植阶段，如果需要可以通过修改配置文件 `MiniGUI.cfg` ，配置 dummy 作为GAL engine。


### 两个显示设备（分辨率不一致），如何做动态的切换方案

这个需要应用自己处理，比如可以根据不同分辨率定义控件配置数据，在不同分辨率下使用不同的配置。

### 主界面画的圆弧边缘有锯齿(如图所示)

建议使用 `mGPlus` 进行绘制。mGPlus 是对 MiniGUI 核心库绘制功能的一个补充，其中包含了常见的 2D 矢量绘图功能，包括路径、渐变色填充、颜色组合等。

如果有性能问题，可以使用预先设计的png图片，也可以达到很好的效果。

## 输入设备

### 能否直接支持游戏手柄

MiniGUI 4.0 版本提供所有输入设备的支持，包括游戏杆、多点触摸屏、手势、平板笔等等。


### 多输入设备的支持

MiniGUI 4.0 版本提供所有输入设备的支持，包括游戏杆、多点触摸屏、手势、平板笔等等。

### 如何在应用层支持多点触控

MiniGUI 4.0 版本提供所有输入设备的支持，包括游戏杆、多点触摸屏、手势、平板笔等等。

## 系统功能

### 是否支持系统按键音

按键音与MiniGUI显示没有关系，需要自己实现，可以在收到按键事件(`MSG_KEYDOWN` 和 `MSG_KEYUP`)时自己播放按键音。

### 蓝牙、WiFi功能的对接

蓝牙、WiFi功能的部分界面可以参考我们的示例程序，比如 WiFi 选择列表，在 mg-demos 中就有相关的实现。
具体实际功能需要自己对接。

[WiFi列表示例](https://github.com/VincentWei/mg-demos/tree/master/cbplusui)

### 丰富字库的支持，包括多国语言的配置及裁剪

MiniGUI 支持多种字库及编码, 多语言支持是通过 Unicode 来实现的。MiniGUI 4.0 将支持完整 Unicode 12.0规范。
字体推荐使用 TrueType 字体, 如果 TrueType 字体文件太大，可以使用 MiniGUI 自带有转换工具将其转换为点阵字体，但是要注意字体版权问题。

转换工具，请访问：

[字体工具](https://github.com/VincentWei/mg-tools/tree/master/font-tools)


### 是否支持文档阅读器，包括常见的PDF、DOC、TXT

TXT文本文件可以直接加载使用, PDF, DOC等复杂格式的解析等操作，建议找第三方进行支持， 比如红樱枫等。


### 进程间通信有没有标准
MiniGUI与其它进程间的通讯没有特定的标准，依赖于操作系统平台，如在 Linux 上可以使用 Linux 进程通讯相关函数。
MiniGUI进程版进程之间的简单通讯可以使用函数 `ClientRequest` 和 `ServerSendReply`来进行，复杂通讯MiniGUI 提供了经过封装的 UNIX 域套接字。

函数原型如下：

    /**
     * \fn int ClientRequest (const REQUEST* request, void* result, int len_rslt)
     * \brief Sends a request to the server and wait reply.
     *
     * If \a result is NULL or \a len_rslt is zero, the function will return
     * immediately after sent the data to the server.
     *
     * This function is a simplified version of ClientRequestEx, i.e.
     * there is no extra data to be sent.
     *
     * \param request The pointer to REQUEST, which contains the data of
     *        the request.
     * \param result The buffer receives the reply.
     * \param len_rslt The lenght of the buffer.
     *
     * \return Zero on success, no-zero on error.
     *
     * \note Only used by clients to send a request to the server of
     *       MiniGUI-Processes.
     *
     * \sa ClientRequestEx, ServerSendReply
     */
    static inline int ClientRequest (const REQUEST* request,
                    void* result, int len_rslt)


    /**
     * \fn int GUIAPI ServerSendReply (int clifd, const void* reply, int len)
     * \brief Sends the reply to the client.
     *
     * This function sends a replay pointed to by \a reply which is
     * \a len bytes long to the client.
     *
     * \note Only used by the server to send the reply to the client.
     *       This function typically called in your customized request handler.
     *
     * \param clifd The fd connected to the client.
     * \param reply The buffer contains the reply data.
     * \param len The length of the reply data in bytes.
     * \return Zero on success, no-zero on error.
     *
     * \sa ClientRequest, RegisterRequestHandler
     */
    MG_EXPORT int GUIAPI ServerSendReply (int clifd, const void* reply, int len);



    /**
     * \fn int serv_listen (const char* name)
     * \brief Creates a listen socket.
     *
     * This function is used by the server to create a listening socket.
     * Any MiniGUI-Processes application can call this function to create a
     * listening socket. The server, i.e. \a mginit, of MiniGUI-Processes uses
     * this function to create its listening socket, and named the socket
     * to '/var/tmp/minigui'.
     *
     * \param name The path name of the listening socket.
     * \return The file discriptor of the listening socket created, -1 on error.
     *
     * \note As a convention, you should located the socket in '/var/tmp/'
     * directory.
     */
    MG_EXPORT int serv_listen (const char* name);
    
    /**
     * \fn int serv_accept (int listenfd, pid_t *pidptr, uid_t *uidptr)
     * \brief Waits for a client connection to arrive, and accept it.
     *
     * This function is used by the server to wait a connection and accept it.
     *
     * After creating a listening socket by calling \a serv_listen, you can
     * call this function to create a connection with a client. We also obtain
     * the client's PID and UID from the pathname that it must bind before
     * calling us.
     *
     * \param listenfd The fd of listen socket.
     * \param pidptr The client PID will be saved to this buffer when this
     *        function returns.
     * \param uidptr The client UID will be saved to this buffer when this
     *        function returns.
     *
     * \return The new connected fd if all OK, < 0 on error.
     *
     * \sa serv_listen, cli_conn
     */
    MG_EXPORT int serv_accept (int listenfd, pid_t *pidptr, uid_t *uidptr);
    
    /**
     * \fn int cli_conn (const char* name, char project)
     * \brief Used by clients to connect to a server.
     *
     * This function is used by clients to connect to a server.
     *
     * The created socket will be located at the directory '/var/tmp',
     * and with name of '/var/tmp/xxxxx-c', where 'xxxxx' is the pid of client.
     * and 'c' is a character to distinguish different projects.
     *
     * Note that MiniGUI itself uses 'a' as the project character to
     * create socket between 'mginit' and clients.
     *
     * \param name The name of the well-known listen socket (created by server).
     * \param project A character to distinguish different projects
     *        (Do \em NOT use 'a').
     * \return The new connected fd if all OK, < 0 on error.
     *
     * \sa serv_listen, serv_accept
     */
    MG_EXPORT int cli_conn (const char* name, char project);
    
    #define SOCKERR_IO          -1
    #define SOCKERR_CLOSED      -2
    #define SOCKERR_INVARG      -3
    #define SOCKERR_TIMEOUT     -4
    #define SOCKERR_OK          0
    
    /**
     * \fn int sock_write_t (int fd, const void* buff,\
                    int count, unsigned int timeout)
     * \brief Writes data to socket.
     *
     * This function writes the data block pointed to by \a buff
     * which is \a count bytes long to the socket \a fd.
     *
     * \param fd The file descriptor of the socket.
     * \param buff The buffer contains the data.
     * \param count The length in bytes of the buffer.
     * \param timeout An upper bound on the amount of time elapsed before
     *        \a sock_write_t returns. When it is zero, \a sock_write_t can
     *        block indefinitely. The timeout value is in tick count, and
     *        tick count of MiniGUI is in unit of 10 milliseconds.
     * \return SOCKERR_OK if all OK, < 0 on error.
     *
     * \retval SOCKERR_OK       Read data successfully.
     * \retval SOCKERR_IO       There are some I/O errors occurred.
     * \retval SOCKERR_CLOSED   The socket has been closed by the peer.
     * \retval SOCKERR_INVARG   You passed invalid arguments.
     * \retval SOCKERR_TIMEOUT  Timeout.
     *
     * \note The \a timeout only goes into effect when this function called
     *       by the server of MiniGUI-Processes, i.e. \a mginit.
     *
     * \sa sock_read_t
     */
    MG_EXPORT int sock_write_t (int fd, const void* buff,
                    int count, unsigned int timeout);
    
    /**
     * \fn int sock_read_t (int fd, void* buff, int count, unsigned int timeout)
     * \brief Reads data from socket.
     *
     * This function reads data which is \a count bytes long to the buffer \a buff
     * from the socket \a fd.
     *
     * \param fd The file descriptor of the socket.
     * \param buff The buffer used to save the data.
     * \param count The length in bytes of the buffer.
     * \param timeout An upper bound on the amount of time elapsed before
     *        \a sock_read_t returns. When it is zero, \a sock_read_t can
     *        block indefinitely. The timeout value is in the tick count of MiniGUI,
     *        and tick count of MiniGUI is in unit of 10 milliseconds.
     * \return SOCKERR_OK if all OK, < 0 on error.
     *
     * \retval SOCKERR_OK       Read data successfully.
     * \retval SOCKERR_IO       There are some I/O errors occurred.
     * \retval SOCKERR_CLOSED   The socket has been closed by the peer.
     * \retval SOCKERR_INVARG   You passed invalid arguments.
     * \retval SOCKERR_TIMEOUT  Timeout.
     *
     * \note The \a timeout only goes into effect when this function called
     *       by the server of MiniGUI-Processes, i.e. \a mginit.
     *
     * \sa sock_write_t
     */
    MG_EXPORT int sock_read_t (int fd, void* buff, int count, unsigned int timeout);
    
    /**
     * \def sock_write(fd, buff, count)
     * \brief The blocking version of \a sock_write_t function.
     *
     * \sa sock_write_t
     */
    #define sock_write(fd, buff, count) sock_write_t(fd, buff, count, 0)
    
    /**
     * \def sock_read(fd, buff, count)
     * \brief The blocking version of \a sock_read_t function.
     *
     * \sa sock_read_t
     */
    #define sock_read(fd, buff, count) sock_read_t(fd, buff, count, 0)

### 是否支持直接应用截图保存

需要在编译 MiniGUI 时开启选项 `--enable-savescreen`, 并使用函数 `SaveScreenRectContent` 来实现截图，

函数原型如下:

    /**
     * \fn BOOL GUIAPI SaveScreenRectContent (const RECT* rc, \
                    const char* filename)
     * \brief Saves content of a rectangle in the screen to a file.
     *
     * This function saves the content of the rect \a rc to the image
     * file \a filename. MiniGUI uses the extension name of the file to
     * determine the format of the image file.
     *
     * \param rc The RECT object defined the rectangle in the screen.
     * \param filename The name of the image file.
     *
     * \return TRUE on success, otherwise FALSE.
     *
     * \note Only defined for _MGMISC_SAVESCREEN.
     *
     * \sa bmp_load_fns
     */
    MG_EXPORT BOOL GUIAPI SaveScreenRectContent (const RECT* rcWin,
                    const char* filename);

### 支持中英文输入法

mg-demos 中的 softkbd 提供了中英文输入法的示例，可以直接使用，需要注意的是该示例中的码表比较老，字数较少，
如果想要更好的输放法，建议找一些商业机构提供的输入法或者自己移植一些开源输入法，比如：小企鹅输入法

具体示例代码，请访问：
  * [输入法示例](https://github.com/VincentWei/mg-demos/tree/master/softkbd)


## 页面刷新

### 刷新非当前页面的方法

将目标窗口的句柄作为参数调用 `InvalidateRect`，即可实现刷新非当前页面。

函数原型如下:

    /**
     * \fn BOOL GUIAPI InvalidateRect (HWND hWnd, const RECT* prc, BOOL bEraseBkgnd)
     * \brief Makes a rectangle region in the client area of a window invalid.
     *
     * This function adds a rectangle pointed to by \a prc to the specified
     * window's update region. The update region represents the portion of
     * the window's client area that must be redrawn, and erase background
     * if argument \a bReaseBkgnd is set.
     *
     * \param hWnd The handle to the window.
     * \param prc The pointer to a RECT structure which defines the
     *        invalid rectangle.
     * \param bEraseBkgnd Indicates whether the background should be erased.
     *
     * \return TRUE on success, otherwise FALSE.
     *
     * \sa MSG_PAINT
     */
    MG_EXPORT BOOL GUIAPI InvalidateRect (HWND hWnd,
                    const RECT* prc, BOOL bEraseBkgnd);


### 页面存在较多按钮控件时 刷新页面时会有短暂白屏？

所在窗口背景绘制过于耗时或按钮本身绘制过于耗时会出现白屏现象。
在 MiniGUI 3.0及以上版本, 可以通过为窗口增加 `WS_EX_AUTOSECONDARYDC` 属性启用双缓冲，
这样可以解决白屏闪烁问题，但同时会消耗更多的内存。

建议在编程时只刷新必要的区域，这样也能降低白屏出现的机率。

### 主界面刷新的时候，有时候有闪烁状态

所在窗口背景绘制过于耗时或按钮本身绘制过于耗时会出现白屏现象。
在 MiniGUI 3.0及以上版本, 可以通过为窗口增加 `WS_EX_AUTOSECONDARYDC` 风格启用双缓冲，
这样可以解决白屏闪烁问题，但同时会消耗更多的内存。

建议在编程时只刷新必要的区域（在调用 InvalidateRect 函数时，传入需要刷新的最小矩形），
这样也能降低白屏出现的机率。

----

[&lt;&lt; FAQs](MiniGUIUserManualFAQsEN.md) |
[Table of Contents](README.md)

[Quick Start]: /user-manual/MiniGUIUserManualQuickStart.md
[Building MiniGUI]: /user-manual/MiniGUIUserManualBuildingMiniGUI.md
[Compile-time Configuration]: /user-manual/MiniGUIUserManualCompiletimeConfiguration.md
[Runtime Configuration]: /user-manual/MiniGUIUserManualRuntimeConfiguration.md
[Tools]: /user-manual/MiniGUIUserManualTools.md
[Feature List]: /user-manual/MiniGUIUserManualFeatureList.md
[FAQs]: /user-manual/MiniGUIUserManualFAQsEN.md
[常见问题]: /user-manual/MiniGUIUserManualFAQsZH.md

[Release Notes for MiniGUI 3.2]: /supplementary-docs/Release-Notes-for-MiniGUI-3.2.md
[Release Notes for MiniGUI 4.0]: /supplementary-docs/Release-Notes-for-MiniGUI-4.0.md
[Showing Text in Complex or Mixed Scripts]: /supplementary-docs/Showing-Text-in-Complex-or-Mixed-Scripts.md
[Supporting and Using Extra Input Messages]: /supplementary-docs/Supporting-and-Using-Extra-Input-Messages.md
[Using CommLCD NEWGAL Engine and Comm IAL Engine]: /supplementary-docs/Using-CommLCD-NEWGAL-Engine-and-Comm-IAL-Engine.md
[Using Enhanced Font Interfaces]: /supplementary-docs/Using-Enhanced-Font-Interfaces.md
[Using Images and Fonts on System without File System]: /supplementary-docs/Using-Images-and-Fonts-on-System-without-File-System.md
[Using SyncUpdateDC to Reduce Screen Flicker]: /supplementary-docs/Using-SyncUpdateDC-to-Reduce-Screen-Flicker.md
[Writing DRM Engine Driver for Your GPU]: /supplementary-docs/Writing-DRM-Engine-Driver-for-Your-GPU.md
[Writing MiniGUI Apps for 64-bit Platforms]: /supplementary-docs/Writing-MiniGUI-Apps-for-64-bit-Platforms.md

[MiniGUI User Manual]: /user-manual/README.md
[MiniGUI Programming Guide]: /programming-guide/README.md
[MiniGUI Porting Guide]: /porting-guide/README.md
[MiniGUI API Reference Manuals]: /api-reference/README.md

[MiniGUI Official Website]: http://www.minigui.com
[Beijing FMSoft Technologies Co., Ltd.]: https://www.fmsoft.cn
[FMSoft Technologies]: https://www.fmsoft.cn
[HarfBuzz]: https://www.freedesktop.org/wiki/Software/HarfBuzz/
