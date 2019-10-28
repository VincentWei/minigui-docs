# 第二部分第十三章 动画控件类
# Chapter 13 of Part 2 Animation Control Class


---++动画控件简介
---++Brief Introduction of Animation Control
动画控件通过对图片组和gif动态图片的绘制和显示，为用户提供了丰富的视觉体验。 `mGNCS中的动画控件源于Minigui`
3.0的animation控件，在其基础上增加了对图片组播放和gif图片播放控制的支持。 同时， 用户可以通过设置图片播放间隔时间， 来控制播放速度。

Animation control provides rich visual experience to the users through drawing
and displaying image group and gif dynamic images. Animation control in mGNCS 
is derived from animation control of minigui 3.0, and based on it, support to
image group play and gif image play control is added. At the same time, users
can control the play speed through setting image play interval.

- Animate类层次关系
- [ `mStatic` ](MStudioMGNCSV1dot0PGP2C4#mStatic)
* [ `mAnimate` ](MStudioMGNCSV1dot0PGP2C13#mAnimate)

- 控件创建方法
-
自动创建：通过miniStudio中的界面设计器，拖拽对应的动画控件，在属性栏中选择需要加载的GIF图片或图片目录，miniStudio将自动创建控件，并提供可视化的控件配置，同时自动生成创建代码。 
- 手动生成：按照mGNCS控件创建过程，通过编程，传入对应控件窗口类ID，生成控件，手动编程设置控件属性、事件处理。

- Animate class hierarchical relation
- [ `mStatic` ](MStudioMGNCSV1dot0PGP2C4#mStatic)
* [ `mAnimate` ](MStudioMGNCSV1dot0PGP2C13#mAnimate)

- Control creating method
- Automatic creation: through interface designer in miniStudio, drag
corresponding animation control, select `GIF` image or image directory that 
need to load in the property column, and miniStudio will automatically create
control and provides visual control configuration, at the same time, creation
codes are generated automatically.
- Manual generation: according to mGNCS control creating process, through
programming, corresponding control window class `ID` is imported, and control 
is generated. Manual programming sets control property and event handling.

---++mAnimate

- *控件窗口类*: `NCSCTRL_ANIMATE`
- *控件英文名*: Animate
- *简介*: 动画控件。通过在控件上加载不同的图片处理对象， 来显示绘制动态图片。
- *示意图*:


- *Control window class*: `NCSCTRL_ANIMATE`
- *Control English name*: Animate
- *Brief introduction*: Animation control. Display drawn dynamic images through
loading different image processing objects on the control.
- *Schematic diagram*:

---+++mAnimate风格
---+++Style of `mAnimate`
继承自[mStatic](MStudioMGNCSV1dot0PGP2C4)的风格

| * 风格ID * | * `miniStudio属性名` * | * 说明 * |
| `NCSS_ANMT_AUTOLOOP` | Loop | 设置动画播放是否为自动循环， 设置为True时，图片循环播放， 设置为False时，图片播放完毕则停止 |
| `NCSS_ANMT_SCALE` | Scale->ImageScaled | 设置图片播放面积为控件区域面积， 可以对图片进行扩大或缩减播放 |
| `NCSS_ANMT_AUTOFIT` | Scale->AutoFit | 设置控件区域自动匹配为图片面积 |
| `NCSS_ANMT_AUTOPLAY` | Autoplay | 设置图片是否为自动播放， True时， 图片自动播放，False时， 需要用户发送命令控制播放 |

It is inherited from the style of [mStatic](MStudioMGNCSV1dot0PGP2C4)

| *Style name* | *mstudio property name* | *Explanation* |
| `NCSS_ANMT_AUTOLOOP` | Loop | Set animation play as automatic circle or not. When setting as True, the images are played in circle. When setting as False, it will stop after the images are all played. |
| `NCSS_ANMT_SCALE` | Scale->ImageScaled | Set the image play area as control region area, and the images can be played enlarged or reduced |
| `NCSS_ANMT_AUTOFIT` | Scale->AutoFit | Set the control region automatic matched as image area |
| `NCSS_ANMT_AUTOPLAY` | Autoplay | Set images as automatic play or not. When it is True, the images are played automatically. When it is False, it is necessary for the users to send order to control the play |

---+++mAnimate属性
---+++Property of `mAnimate`
继承自[mStatic](MStudioMGNCSV1dot0PGP2C4)的属性

| * 属性ID名 * | * `miniStudio属性名` * | * 类型 * | * 权限 * | * 说明 * |
| `NCSP_ANMT_GIFFILE` | `GIFFile` | String | `RW` | 动画控件加载的GIF图片文件名 |
| `NCSP_ANMT_DIR` | Dir | String | `RW` | 动画控件加载的目录名， 控件加载目录内的所有图片, 图片播放是按照所支持图片首字母ascii码顺序 |
| `NCSP_ANMT_INTERVAL` | Interval | int | `RW` | 播放图片时帧与帧之间的时间间隔 |

It is inherited from the property of [mStatic](MStudioMGNCSV1dot0PGP2C4)

| *Property* | *mstudio property name* | *Type* | *Authority* | *Explanation* |
| `NCSP_ANMT_GIFFILE` | `GIFFile` | String | `RW` | Name of the `GIF` image file loaded by the animation control |
| `NCSP_ANMT_DIR` | Dir | String | `RW` | Name if the directory loaded by the animation control. The control loads all the images in the directory. Image play is according to the first letter ascii code sequence of the images supported |
| `NCSP_ANMT_INTERVAL` | Interval | int | `RW` | Time interval between the frames when the images are played |

---+++mAnimate事件
---+++Event of `mAnimate`

继承自[mStatic](MStudioMGNCSV1dot0PGP2C4)的事件

It is inherited from the event of [mStatic](MStudioMGNCSV1dot0PGP2C4)

---+++mAnimate渲染器
---+++Renderer of `mAnimate`

非客户区的绘制请查阅[mStatic](MStudioMGNCSV1dot0PGP2C4#mStatic)的渲染器

For the drawing of non client area, please refer to the renderer of
[mStatic](MStudioMGNCSV1dot0PGP2C4#mStatic) 

---+++mAnimate方法
---+++Method of `mAnimate`

---++++ncsAnimateStart
%CODE{cpp}%
`BOOL` `ncsAnimateStart(mAnimate*` self);
```
```

---++++ncsAnimatePauseResume
%CODE{cpp}%
`BOOL` `ncsAnimatePauseResume(mAnimate*` self);
```
```

---++++ncsAnimateStop
%CODE{cpp}%
`BOOL` `ncsAnimateStop(mAnimate*` self);
```
```


---+++mAnimate编程示例
---+++Programming Example of `mAnimate`

- 运行截图: <br />
- Operation screen shot: <br />

![alt](figures/animation.png)

- 本程序窗口区域上边的图片为gif动态图片， 下面是对程序所在目录中图片的幻灯片播放， 三个按钮start, pause, stop是对gif播放的控制。
- 普通按钮完整示例代码：[animation.c](%ATTACHURL%/animation.c.txt)

- Images on the top of the window region of this program are gif dynamic 
images, and on the bottom, it is the slide play of the images in the directory
of the program. The three buttons start, pause and stop are control of gif 
play. 
- Common button complete example 
code:[animation.c](%ATTACHURL%/animation.c.txt) 

<p align=center>清单 p2c13-1 <a
href="%ATTACHURL%/animation.c.txt">animation.c</a></p> 

<p align=center>List p2c13-1 <a
href="%ATTACHURL%/animation.c.txt">animation.c</a></p> 

- 设置加载图片

- Set loading image
```
```

- 设置按键消息
- Set key information
```
```


- 设置显示界面模板
- Set display interface template
```
```


[Next](MStudioMGNCSV1dot0PGP2C12][Previous]] < [[MStudioMGNCSV1dot0PG][Index]] 
> [[MStudioMGNCSV1dot0PGP2C14)




-- Main.XiaodongLi - 22 Feb 2010


----

[&lt;&lt; ](MiniGUIProgGuidePart.md) |
[Table of Contents](README.md) |
[ &gt;&gt;](MiniGUIProgGuidePart.md)

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
