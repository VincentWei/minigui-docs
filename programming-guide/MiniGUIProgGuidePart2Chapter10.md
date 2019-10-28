# 旋钮类控件
# Spinner Class Control


## 旋钮类控件简介
## Brief Introduction of Spinner Class Controls

旋钮类控件通常由一组箭头按钮（上下或者左右），通常表示一个范围，通过箭头控制，可以一步一步的改变值。

mGNCS提供两种按钮，mSpinner和mSpinbox，他们的继承关系如下
   
- [mWidget ](MStudioMGNCSV1dot0PGP2C3#mWidget)
   - [mSpinner](MStudioMGNCSV1dot0PGP2C9#mSpinner)
         * [mSpinbox](MStudioMGNCSV1dot0PGP2C9#mSpinbox)


Spinner class control is usually composed of a group of arrow buttons (up and down, or left and right), which usually represent a range. Through arrow control, value can be changed step by step.

mGNCS provides two kinds of buttons, mSpinner and mSpinbox, and their inheritance relation is as follows
   
- [mWidget ](MStudioMGNCSV1dot0PGP2C3#mWidget)
   - [mSpinner](MStudioMGNCSV1dot0PGP2C9#mSpinner)
         * [mSpinbox](MStudioMGNCSV1dot0PGP2C9#mSpinbox)


## mSpinner
## mSpinner
- *控件名称*:  NCSCTRL_SPINNER
- *英文名*: Spinner
- *简要介绍*: 由两个箭头按钮（上下或者左右）组成的能够控制在一个范围内变化的值的控件
- *示意图*: <br/>

- *Control name*:  NCSCTRL_SPINNER
- *English name*: Spinner
- *Brief introduction*: Control consisting of two arrow buttons (up and down or left and right) that can control values changing in a range
- *Schematic diagram*: <br/>

<img src="%ATTACHURLPATH%/spinner.png" alt="spinner.png"  />
   
### mSpinner风格
### Style of mSpinner

继承自[mWidget的风格 ](MStudioMGNCSV1dot0PGP2C3#mWidget)
|* 风格ID *|* miniStudio 名 *| * 说明 *|
| NCSS_SPNR_VERTICAL | Direction->Vert| 垂直风格，上下箭头，当点击上下箭头的时候，会向目标窗口发送上下方向键的键盘消息 |
| NCSS_SPNR_HORIZONTAL | Direction->Horz | 水平风格，左右箭头,当点击左右箭头的时候，会向目标窗口发送左右方向键的键盘消息 |
| NCSS_SPNR_AUTOLOOP | AutoLoop | 当到达最大或者最小值时，自动跳转到最小或者最大值处 |


It is inherited from [the style of mWidget ](MStudioMGNCSV1dot0PGP2C3#mWidget)
|* Style ID *|* miniStudio name *| * Explanation *|
| NCSS_SPNR_VERTICAL | Direction->Vert| Vertical style, up and down arrows. When clicking up and down arrows, it will send keyboard information of the up and down direction keys to the objective window |
| NCSS_SPNR_HORIZONTAL | Direction->Horz | Horizontal style, left and right arrows. When clicking the left and right arrows, it will send keyboard information of the left and right direction keys to the objective window |
| NCSS_SPNR_AUTOLOOP | AutoLoop | When reaching the maximum or minimum value, it will automatically loop to the minimum or maximum value |

### mSpinner属性
### Property of mSpinner

继承自[mWidget的属性 ](MStudioMGNCSV1dot0PGP2C3#mWidget)

|* 属性ID *| *miniStudio 名*| *类型* | *权限* |* 说明 *|
| NCSP_SPNR_MAXPOS | MaxPos | int | RW | 变化范围的最大值 |
| NCSP_SPNR_MINPOS | MinPos | int | RW | 变化范围的最小值 |
| NCSP_SPNR_CURPOS | CurPos | int | RW | 当前值 |
| NCSP_SPNR_LINESTEP | LineStep | int | RW | 步进步长 |
| NCSP_SPNR_TARGET | - | HWND | RW | 目标窗口句柄 | 


It is inherited from [the property of mWidget ](MStudioMGNCSV1dot0PGP2C3#mWidget)

|* Property ID *| *miniStudio name*| *Type* | *Authority* |* Explanation *|
| NCSP_SPNR_MAXPOS | MaxPos | int | RW | Maximum value of the change range |
| NCSP_SPNR_MINPOS | MinPos | int | RW | Minimum value of the change range |
| NCSP_SPNR_CURPOS | CurPos | int | RW | Current value |
| NCSP_SPNR_LINESTEP | LineStep | int | RW | Step length |
| NCSP_SPNR_TARGET | - | HWND | RW | Objective window sentence handle | 

### mSpinner事件
### Event of mSpinner

继承自[mWidget的事件](MStudioMGNCSV1dot0PGP2C3#mWidget)

| *事件ID* | *参数* | *说明* |
| NCSN_SPNR_CHANGED | int 当前属性值 | 当前值变化 |
| NCSN_SPNR_REACHMAX | int 当前属性值 | 当前值到达最大值 |
| NCSN_SPNR_REACHMIN | int 当前属性值 | 当前值到达最小值 |

It is inherited from [the event if mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget)

| *Event ID* | *Parameter* | *Explanation* |
| NCSN_SPNR_CHANGED | int current property value | Current value changes |
| NCSN_SPNR_REACHMAX | int current property value | The current value reaches the maximum value |
| NCSN_SPNR_REACHMIN | int current property value | The current value reaches the minimum value |

### mSpinner方法
### Method of mSpinner

继承自[mWidget的方法](MStudioMGNCSV1dot0PGP2C3#mWidget)

该类没有新增方法

It is inherited from [the method of mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget)

The class does not have newly added method

### mSpinner渲染器
### Renderer of mSpinner

---++++ mSpinner classic渲染器
---++++ mSpinner classic renderer

非客户区查看[mWidget的classic渲染器](MStudioMGNCSV1dot0PGP2C3#mWidget)

| *属性名*  | *说明* | *miniStudio属性名* | *类型* | *示意图*|
| NCS_BGC_3DBODY | 背景颜色 | ColorBg3DBody | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-bg3dcolor.png" alt="spinner-classic-bg3dcolor.png" width='42' height='37' /> | | 
| NCS_FGC_3DBODY | 前景箭头的颜色 | ColorFg3DBody | DWORD(ARGB) | <img src="%ATTACHURLPATH%/push-button-classic-fg3dcolor.png" alt="push-button-classic-fg3dcolor.png" width='38' height='38' /> | |
| NCS_BGC_DISABLED_ITEM | 无效时的背景颜色 | ColorBgDisable | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-bg3ddisable.png" alt="spinner-classic-bg3ddisable.png" width='39' height='38' /> |
| NCS_FGC_DISABLED_ITEM | 无效时的箭头颜色 | ColorFgDisable | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-fg3ddisable.png" alt="spinner-classic-fg3ddisable.png" width='36' height='37' /> |

For the non client area, refer to [classic renderer of mWidget](MStudioMGNCSV1dot0PGP2C3#mWidget)

| *Property name*  | *Explanation* | *miniStudio property name* | *Type* | *Schematic diagram*|
| NCS_BGC_3DBODY | Background color | ColorBg3DBody | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-bg3dcolor.png" alt="spinner-classic-bg3dcolor.png" width='42' height='37' /> | | 
| NCS_FGC_3DBODY | Color of the foreground arrow | ColorFg3DBody | DWORD(ARGB) | <img src="%ATTACHURLPATH%/push-button-classic-fg3dcolor.png" alt="push-button-classic-fg3dcolor.png" width='38' height='38' /> | |
| NCS_BGC_DISABLED_ITEM | Background color when it is invalid | ColorBgDisable | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-bg3ddisable.png" alt="spinner-classic-bg3ddisable.png" width='39' height='38' /> |
| NCS_FGC_DISABLED_ITEM | Color of the arrow when it is invalid | ColorFgDisable | DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-classic-fg3ddisable.png" alt="spinner-classic-fg3ddisable.png" width='36' height='37' /> |

---++++ mSpinner Skin渲染器
---++++ mSpinner Skin Renderer

参阅 [附录B : Skin 渲染器使用的图片资源规范](MStudioMGNCSV1dot0PGAppB#mSpinner)

Refer to [ Appendix B : Specification for the Image Resource Used by Skin Renderer](MStudioMGNCSV1dot0PGAppB#mSpinner)

---++++ mSpinner Fashion 渲染器
---++++ mSpinner Fashion Renderer

| *属性名*  | *说明*  | *miniStudio属性名* | *类型* | *示意图* |
| NCS_FGC_3DBODY | 按钮前景色 | ColorFg3DBody  |  DWORD(ARGB) | 同Classic渲染器 |
| NCS_FGC_DISABLED_ITEM | 窗口无效时按钮前景色 |  ColorFgDisable | DWORD(ARGB) | 同Classic渲染器 |
| NCS_BGC_3DBODY | 背景颜色 | ColorBg3DBody  |  DWORD(ARGB) | 同Classic渲染器 |
| NCS_BGC_DISABLED_ITEM | 窗口无效时文本背景色 | ColorBgDisable | DWORD(ARGB) | 同Classic渲染器 |
| NCS_MODE_BGC | 渐变填充方式 | GradientMode |  [GradientMode](MStudioMGNCSV1dot0PGP2C5#GrandientMode)  | <img src="%ATTACHURLPATH%/spinner-fashion-grandiant-mode.png" alt="spinner-fashion-grandiant-mode.png" width='74' height='38' /> |


| *Property name*  | *Explanation*  | *miniStudio property name* | *Type* | *Schematic diagram* |
| NCS_FGC_3DBODY | Button foreground color | ColorFg3DBody  |  DWORD(ARGB) | Same as Classic renderer |
| NCS_FGC_DISABLED_ITEM | Button foreground color when the window is invalid |  ColorFgDisable | DWORD(ARGB) | Same as Classic renderer |
| NCS_BGC_3DBODY | Background color | ColorBg3DBody  |  DWORD(ARGB) | Same as Classic renderer |
| NCS_BGC_DISABLED_ITEM | Text background color when the window is invalid | ColorBgDisable | DWORD(ARGB) | Same as Classic renderer |
| NCS_MODE_BGC | Gradual change fill mode | GradientMode |  [GradientMode](MStudioMGNCSV1dot0PGP2C5#GrandientMode)  | <img src="%ATTACHURLPATH%/spinner-fashion-grandiant-mode.png" alt="spinner-fashion-grandiant-mode.png" width='74' height='38' /> |


---++++ mSpinner Flat 渲染器
---++++ mSpinner Flat Renderer

| *属性名*  | *说明*  | *miniStudio属性名* | *类型* | *示意图* |
| NCS_FGC_3DBODY | 按钮前景色 | ColorFg3DBody  |  DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-flat-fgcolor.png" alt="spinner-flat-bgcolor.png" width='36' height='36' />  |
| NCS_BGC_3DBODY | 背景颜色 | ColorBg3DBody  |  DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-flat-bgcolor.png" alt="spinner-flat-fgcolor.png" width='37' height='36' /> |

| *Property name*  | *Explanation*  | *miniStudio property name* | *Type* | *Schematic diagram* |
| NCS_FGC_3DBODY | Button foreground color | ColorFg3DBody  |  DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-flat-fgcolor.png" alt="spinner-flat-bgcolor.png" width='36' height='36' />  |
| NCS_BGC_3DBODY | Background color | ColorBg3DBody  |  DWORD(ARGB) | <img src="%ATTACHURLPATH%/spinner-flat-bgcolor.png" alt="spinner-flat-fgcolor.png" width='37' height='36' /> |


### mSpinner示例
### Example of mSpinner

下面的示例（截图见mSpinner的示意图）演示了Spinner和一个Static控件关联。当Spinner的pos改变后，Static会响应的变化。
- 主要涉及的属性有
   - NCSP_SPN_MAXPOS
   - NCSP_SPN_MINPOS
   - NCSP_SPN_CURPOS
- 主要涉及的事件:
   - NCSN_SPN_CHANGED


The example below (for the screen shot, see the schematic diagram of mSpinner) demonstrates that Spinner is associated with a Static control. After pos of Spinner changes, Static will change correspondingly.
- Properties mainly involved are
   - NCSP_SPN_MAXPOS
   - NCSP_SPN_MINPOS
   - NCSP_SPN_CURPOS
- Event mainly involved is:
   - NCSN_SPN_CHANGED

为了方便我们主要数据绑定的方法来实现

-  示例 [spinner.c](%ATTACHURL%/spinner.c.txt)
  
- 在窗口的模板定义文件中设置spinner的属性


For convenience, we mainly realize through the method of data binding

-  Example [spinner.c](%ATTACHURL%/spinner.c.txt)
  
- In the template definition file of the window, set properties of spinner


%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/spinner.c.txt" pattern="^.*?//START_SET_PROPS(.*?)//END_SET_PROPS.*"}%
```

- 在主窗口的MSG_CREATE消息中，建立和static的连接
   - 获取窗口对象

- In MSG_CREATE message of the main window, establish connection with static
   - Get window object

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/spinner.c.txt" pattern="^.*?//START_GET_CTRLS(.*?)//END_GET_CTRLS.*"}%
```
   - 连接窗口属性

   - Property of the connection window
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/spinner.c.txt" pattern="^.*?//START_CONNECT_PROPS(.*?)//END_CONNECT_PROPS.*"}%
```
   - 更新当前的信息到Static中

   - Update the current information into Static
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/spinner.c.txt" pattern="^.*?//START_UPDATE_CTRLS(.*?)//END_UPDATE_CTRLS.*"}%
```

## mSpinbox
## mSpinbox
- *控件窗口类名* : NCSCTRL_SPINBOX
- *控件英文名* :  Spinbox
- *简要介绍* : 把箭头按钮和编辑框组合起来，通过箭头按钮控制编辑框内的内容 
- *示意图* : <br />

- *Control window class name* : NCSCTRL_SPINBOX
- *Control English name* :  Spinbox
- *Brief introduction* : Combine the arrow button with the edit box, and control the content in the edit box through arrow button 
- *Schematic diagram* : <br />
     <img src="%ATTACHURLPATH%/spinbox.png" alt="spinbox.png" width='300' height='70' />


### mSpinbox风格
### Style of mSpinbox

继承自<a href="#mSpinner风格">mSpinner的风格</a>

|* 风格ID *| *miniStudio名* | * 说明 *| 
| NCSS_SPNBOX_NUMBER | ContentType->Number |显示数值，可以通过相应的属性指定显示格式 |
| NCSS_SPNBOX_STRING | ContentType->String| 显示字符串 |
| NCSS_SPNBOX_SORT | Sort | 字符串自动排序 |
| NCSS_SPNBOX_EDITNOBORDER | EditBorder | 编辑框没有边框 |
| NCSS_SPNBOX_EDITBASELINE | EditBaseLine | 编辑框显示带下划线字符 |
| NCSS_SPNBOX_READONLY | ReadOnly | 编辑框显示的内容只读 |
| NCSS_SPNBOX_UPPERCASE | Case->Upper | 编辑框显示内容全部转成大写字母显示 |
| NCSS_SPNBOX_LOWERCASE | Case->Lower | 编辑框显示内容全部转成小写字母显示 |
| NCSS_SPNBOX_AUTOFOCUS | AutoFocus | 控件获取焦点自动转给编辑框 |

It is inherited from <a href="#the style of mSpinner">the style of mSpinner</a>

|* Style ID *| *miniStudio name* | * Explanation *| 
| NCSS_SPNBOX_NUMBER | ContentType->Number |Display numerical value, display format can be appointed through corresponding properties |
| NCSS_SPNBOX_STRING | ContentType->String| Display character string |
| NCSS_SPNBOX_SORT | Sort | Character string automatic sorting |
| NCSS_SPNBOX_EDITNOBORDER | EditBorder | The edit box does not have border |
| NCSS_SPNBOX_EDITBASELINE | EditBaseLine | The edit box displays the underlined characters|
| NCSS_SPNBOX_READONLY | ReadOnly | Content displayed by the edit box is read only |
| NCSS_SPNBOX_UPPERCASE | Case->Upper | All the edit box display content is converted to capital letter display  |
| NCSS_SPNBOX_LOWERCASE | Case->Lower | All the edit box display content is converted to lowercase letter display |
| NCSS_SPNBOX_AUTOFOCUS | AutoFocus | The control gets focus and automatically transfers to the edit box |

### mSpinbox属性
### Property of mSpinbox

继承自<a href="#mSpinner%E5%B1%9E%E6%80%A7">mSpinner的属性</a>

It is inherited from <a href="#mSpinner%E5%B1%9E%E6%80%A7">the property of mSpinner</a>


### mSpinbox事件
### Event of mSpinbox


继承自<a href="#mSpinner事件">mSpinner的事件</a>

It is inherited from <a href="#the event of mSpinner">the event of mSpinner</a>

### mSpinbox方法
### Method of mSpinbox


继承自<a href="#mSpinner%E6%96%B9%E6%B3%95" > mSpinner的方法</a>

It is inherited from <a href="#mSpinner%E6%96%B9%E6%B3%95" > the method of mSpinner</a>

*以下的函数只有在spinbox包含NCSS_SPNBOX_STRING风格时有效*

- addItem 增加一个新的项

*The functions below are only valid when spinbox contains NCSS_SPNBOX_STRING style*

- addItem adds a new item
%CODE{cpp}%
BOOL (*addItem)(clsName *self, char *item);
```
   - 增加一个字符串到spinbox中
   - 参数：
         *  item : 添加的字符串
   - 返回值： 成功 - TRUE; 失败 - FALSE;

   - Add a character string into spinbox
   - Parameter:
         *  item : added character string
   - Returned value: successful- TRUE; failed- FALSE;

- remove Item
%CODE{cpp}%
BOOL (*removeItem)(clsName *self, int index);
```
   - 删除一个item
   - 参数：
         * index 要删除item的索引
   - 返回值：成功 - TRUE; 失败 - FALSE;

   - Remove an item
   - Parameter:
         * index: the index of removing item 要删除item的索引
   - Returned: successful- TRUE; failed- FALSE;

- setItem
%CODE{cpp}%
BOOL (*setItem)(clsName *self, int index, char *item);
```
   - 设置一个item的字符串内容
   - 参数：
         * index 要设置的索引
         * item   新的item内容
   - 返回值：成功 - TRUE; 失败 - FALSE;

   - Set character string content of an item
   - Parameter:
         * index Index to set
         * Item content of new item
   - Returned value: successful- TRUE; failed- FALSE;

- getItem
%CODE{cpp}%
char* (*getItem)(clsName *self, int index);
```
   - 获取item的字符串内容
   - 参数：
         * index item的索引
   - 返回值：NULL - 失败；有效的字符串指针

   - Get character string content of item
   - Parameter
         * index of the index item
   - Returned value: NULL- failed; valid character string pointer.


### mSpinbox渲染器
### Renderer of mSpinbox

mSpinbox渲染的效果由<a href="#mSpinner%E6%B8%B2%E6%9F%93%E5%99%A8">mSpinner</a>和[mSlEdit](MStudioMGNCSV1dot0PGP2C12#m_SlEdit)的效果组成，该类本身没有新增的属性


Effect of mSpinbox render is composed of the effects of <a href="#mSpinner%E6%B8%B2%E6%9F%93%E5%99%A8">mSpinner</a> and[mSlEdit](MStudioMGNCSV1dot0PGP2C12#m_SlEdit), and the class itself does not have newly added properties

### mSpinbox示例
### Example of mSpinbox 
   该示例分别说明了水平风格下和垂直风格下，数字型和列表型两种形态下的spinbox。

   示意图： <br />

    The example explains spinbox under numeric type and list type under horizontal style and vertical style.

   Schematic diagram:  <br />
     <img src="%ATTACHURLPATH%/spinbox-sample.png" alt="spinbox-sample.png" width='350' height='166' />

- 源代码[spinbox.c](%ATTACHURL%/spinbox.c.txt)

- 主要代码如下:


- Source Code[spinbox.c](%ATTACHURL%/spinbox.c.txt)

- The main codes are as below:
%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/spinbox.c.txt" pattern="^.*?//START_SPINBOX(.*?)//END_SPINBOX.*"}%
```

[Next](MStudioMGNCSV1dot0PGP2C8][Previous]] < [[MStudioMGNCSV1dot0PG][Index]] > [[MStudioMGNCSV1dot0PGP2C10)




-- Main.XiaodongLi - 22 Feb 2010

