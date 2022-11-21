# 新控件集的开发规范

## 1 术语及其含义

- MiniGUI 新控件集（MiniGUI New Control Set，mGNCS）。新控件集不仅仅实现了多种可定制、可扩展的控件类，同时也实现了资源管理功能，以及对其他常用功能的面向对象封装，如主窗口、对话框、菜单等。
- 风格（Style）。用于控制窗口或者控件基本外观和行为的标志。
   - 新控件集的控件风格，仅用于不可动态修改的控件属性，例如进度条是垂直的还是水平的，就可以用风格来实现。在各控件的实现中，应尽量减少风格的使用。
   - 除保留 `WS_`、`WS_EX_` 等系统全局风格之外，MiniGUI 固有控件集定义的各控件风格不在新控件集中使用，新控件集中的控件风格将被重新定义。
   - 新控件集中，控件不再具有扩展风格。
- 属性（Property）。控件属性是一个新增的概念，一般用于那些可动态设置（如编辑框中的插入符位置），或动态改变（如列表框中的列表项数目）的控件特性。mGNCS 提供统一的接口（`getProperty`/`setProperty`）来获取或设置控件的属性。
- 渲染器（Renderer）。在 mGNCS 中，指控制主窗口或者控件外观的绘制方法集合，全称为“外观渲染器（Look and Feel Renderer）”，一般简称为“渲染器”。
   - 在新控件集中，每种可见的控件都会有自己的渲染器。为了和 MiniGUI 3.0 引入的渲染器相区别，我们将 MiniGUI 3.0 的渲染器称为“全局渲染器（global renderer）”，将新控件集引入的渲染器称为“控件渲染器（control renderer）”：
   - 全局渲染器作用于主窗口、老控件集以及新控件集的系统组件（如边框、标题栏、滚动条等非客户区元素）。
   - 控件渲染器仅作用于新控件集各个控件的客户区绘制。
- 窗口类名（Window Class Name）。为了和控件类的名称相区别，我们将 MiniGUI 用于子窗口的类名称为“窗口类名”。如静态框的控件类名为 `mStatic` ，而静态框的窗口类名为 `static_` 。
- 事件（Event）。在 MiniGUI 的传统编程模式中，存在消息（Message）和通知（Notification）两个概念，它们有各自的作用，但对应用程序开发者而言，它们均用于应用程序处理特定的事件。因此，从应用开发者看来，通知也好，消息也好，本质上都是一样的。因此，mGNCS 将消息和通知抽象为事件，从应用开发者角度看，每一个事件对应一个事件的处理器（Event Handler）。

## 2 新控件集的接口命名规范

新控件集的接口命名通常和类的名称有关，因此，在本文后面的规范描述中，类名的全小写方式、全大写方式、大小写混写方式、大写简写方式分别用 `<classname>`、`<CLASSNAME>`、`<ClassName>`、`<CLSNM>` 表示。

- 类名（指包含有方法，即函数指针的结构体）。新控件虽然采用 C 语言实现，但因为采用 OOP 思想，故而采用大小写混写的方式表示“类”的名称，并使用小写字母 m 作为前缀，如 `mWidget` ，以及对应的 `mWidgetClass` 。
- 一般性结构体。使用类似 MiniGUI 接口的全大写方式命名，并使用 `NCS<CLSNM>_` 作为前缀。
- 函数及参数的命名规范。
   - 新控件集新增全局的一般性函数，使用 `ncs` 作为函数名前缀，之后是描述函数功能的动宾短语，并使用大小写混写的方法命名，如 `ncsCreateWindow` 。
   - 面向控件开发者的函数接口，第一个参数应该是 `mWidget*` 或者对应的子类类型指针。
   - 控件类的方法命名：动宾短语，单词连写，除第一个单词外，其他单词的第一个字母大写，如 `void (*moveContent) (mWidget *)` 。
   - 控件类中的消息回调函数的命名规范为： `on<MessageName>` ，如 `void (*onSetFocus) (mWidget *)` 。
   - 控件消息的参数顺序和约定：按照 MiniGUI 定义的消息规范，定义其顺序和名字。
   - 控件渲染器接口的命名规范为： `<className>Renderer` 。
   - 渲染器接口的内部函数参数约定：第一个是 `mWidget*` 或者对应的子类类型指针，第二个参数一般为 `HDC` 。
   - 在新控件集中，凡是和 C++ 成员函数等同的函数，表示本对象的指针变量命名为 `self` ，而本对象对应的类指针为 `_class` 。
   - 函数接口中的参数名称，均使用 Java JDK 的风格进行命名（第一个单词全小写，其后的单词大小写混写），不再使用匈牙利命名法。
   - 只读的指针型参数类型和返回值类型，必须使用 `const` 关键词做修饰。
- 窗口类名。为了不和老控件集的窗口类名冲突，新控件集使用下划线（`_`）作为窗口类名的后缀，如 `static_` 。不使用前缀的原因，是为了在现有 MiniGUI 核心管理窗口类代码的算法下，尽量避免出现哈希冲突。窗口类名的 C 语言宏名称，则以 `NCSCTRL_` 作为前缀，如 `NCSCTRL_STATIC` 。

需要注意的是，由于我们采用的是用 C 语言来实现类似 C++ 语言的面向规则特性，为了防止不必要的错误，我们需要把命名规范当做语法规范来遵守，这样的目的在于：

- 通过各种宏来简化编程。
- 便于通过宏固定编程模式，按照固定的编程模式，易读，易实现，不易出错。
- 编译文档的生成和检索。
- 最大限度减少开发者的学习时间。

## 3 类名称及其标识符的定义规则

类名称、对应的窗口类名及其简写形式由下表给出：

| 类名称 | C 类名 | 窗口类名 Window classname | 类名简写 CLSNM | 备注 |
|:------|:------|:-------------------------|:--------------|:----|
| 超类           | mObject      | - | OBJ    | 非控件类；NCS 类层次关系中的最基础类 |
| 列表项基类     | mItem        | - | ITEM   | 非控件类；用于表述列表项的基础类 |
| 列表项管理器   | mItemManager | - | ITMMNG | 非控件类；用于管理列表项集合的方法类 |
| 列信息类       | mListColumn  | - | LSTCLM | 非控件类；描述列信息类 |
| 行列表项类     | mListItem    | - | LSTITM | 非控件类；管理一行中的列表项集合 |
| 组件基类       | mComponent   | - | CMPT   | 非控件类 |
| 不可见组件基类 | mInvsbComp   | - | IVCMPT | 非控件类 | 
| 定时器         | mTimer       | - | TIMER  | 非控件类 | 
| 控件基类       | mWidget      | `widget_`       | WIDGET | |
| 静态框         | mStatic      | `static_`       | STATIC | |
| 图片框         | mImage       | `image_`        | IMAGE  | |
| 矩形框         | mRect        | `rect_`         | RECT   | |
| 发光二极管标签 | mLEDLabel    | `ledlabel_`     | LEDLBL | |
| 分组框         | mGroupBox    | `groupbox_`     | GRPBOX | |
| 按钮组         | mButtonGroup | `buttongroup_`  | BTNGRP | |
| 按钮           | mButton      | `button_`       | BUTTON | |
| 检查钮         | mCheckButton | `checkbutton_` | CHKBTN | |
| 单选钮         | mRadioButton | `radiobutton_`  | RDOBTN | |
| 面板           | mPanel       | `panel_`        | PANEL  | |
| 组合框         | mCombobox    | `combobox_`     | CMBOX  | |
| 主窗口         | mMainWnd     | `mainwnd_`      | MNWND  | |
| 对话框         | mDialogBox   | `dialogbox_`    | DLGBOX | |
| 可滚动基类     | mScrollWidget| `scrollwidget_` | SWGT   | |
| 容器           | mContainer   | `container_`    | CTNR   | |
| 属性页         | mPage        | `page_`         | PAGE   | |
| 列表型基类     | mItemView    | `itemview_`     | ITEMV  | |
| 列表型         | mListView    | `listview_`     | LISTV  | |
| 图标型         | mIconView    | `iconview_`     | ICONV  | |
| 滚动型         | mScrollView  | `scrollview_`   | SCRLV  | |
| 列表框         | mListBox     | `listbox_`      | LSTBOX | |
| 进度条         | mProgressBar | `progressbar_`  | PRGBAR | |
| 属性表         | mPropSheet   | `propsheet_`    | PRPSHT | |
| 滑动器基类     | mSlider      | `slider_`       | SLIDER | |
| 滑动条         | mTackBar     | `trackbar_`     | TRKBAR | |
| 旋钮基类       | mSpinner     | `spinner_`      | SPNR   | |
| 旋钮框         | mSpinBox     | `spinbox_`      | SPNBOX | |
| 分隔栏         | mSeperator   | `seperator_`    | SPRTR  | |
| 月历           | mMonthCalendar | `monthcalendar_` | CDR | |
| 动画           | mAnimation   | `animation_`    | ANMT   | |
| 工具栏         | mToolBar     | `toolbar_`      | TLBAR  | |
| 滚动条         | mScrollBar     | `scrollbar_`      | SCRLBR  | |
| 编辑框基类     | mEdit        | `edit_`         | EDIT   | |
| 单行编辑框     | mSLEdit      | `sledit_`       | SLEDIT | |
| 多行编辑框     | mMLEdit      | `mledit_`       | MLEDIT | |

标识符的命名规则如下：

- 窗口类名标识符。为了不和老控件集的标识符名称冲突，新控件集使用 `NCSCTRL_<CLASSNAME>` 作为窗口类名标识符。
- 控件风格标识符。为了不和老控件集的风格名称冲突，新控件集使用 `NCSS_<CLSNM>_` 作为风格标识符的前缀。
- 控件属性标识符。新控件集使用 `NCSP_<CLSNM>_` 作为控件属性标识符的前缀。
- 控件通知码标识符。为了不和老控件集的通知码名称冲突，新控件集使用 `NCSN_<CLSNM>_` 作为控件通知码标识符的前缀。
- 类特有数据标识符。新控件集使用 `NCSSPEC_<CLSNM>_` 作为类特有数据的标识符前缀；如 mObject 类的特有数据，使用 `NCSSPEC_OBJ_` 作为前缀。 
- 类方法的参数及返回值所使用的标志、状态等。新控件集使用 `NCSF_<CLSNM>_` 作为这种标识符的前缀。 
- 函数接口及类方法的返回值标识符。新控件集使用 `NCSE_<CLSNM>_` 作为这种标识符的前缀。 
- 其他标识符。除上述标识符之外，其他类型的标识符，参照上述方法确定。

### 3.1 控件风格标识符的定义规则

在新控件集中，控件风格个数应该保持到最小，控件风格的取值范围为 0x00000000 ~ 0x0000FFFF，以免和 MiniGUI 定义的窗口风格混淆。

### 3.2 控件属性标识符的定义规则

控件属性标识符的规则：

   1. 在直系继承关系内，属性标识符的值不能重复，即子类的属性标识符不能覆盖父类及其祖先的属性标识符。
   2. 旁系继承关系内，属性标识符可以重复，即一个控件类的属性标识符可以和其兄弟控件类的属性标识符重复。

在技术上，利用 C 语言的枚举类型定义属性标识符，各控件的属性标识符前缀见上表。

   1. 每个控件属性标识符枚举变量中，最后一项定义为 `NCSP_<CLSNAM>_MAX` 。
   2. 每个控件属性标识符从其父类的最大属性标识符加一的值开始定义。
   3. 利用枚举型能够自动加一的特性，顺序定义各个属性。

例如，

```c
// mWidget 
enum mWidgetProp {
        NCSP_WIDGET_RDR,
        NCSP_WIDGET_MAX
};

// mStatic
enum mStaticProp {
        NCSP_STATIC_HALIGN = NCSP_WIDGET_MAX + 1,
        NCSP_STATIC_VALIGN,
        NCSP_STATIC_MAX
};
```

### 3.3 控件通知码的定义规则

控件通知码的规则类似属性标识符的规则。但需要注意的是，mGNCS 中不能使用 0 作为通知码。

## 4 新控件集的函数库以及头文件

尽管 mGNCS 是在开发 mStudio 的过程中引入的，但 mGNCS 也可作为 MiniGUI 3.0 上的一个组件而被单独使用。因此，我们将新控件集按照 MiniGUI 的一个组件来管理，因而定名为 mGNCS，函数库的名称为 `libmgncs`，当前版本为 1.0.0，头文件在系统头文件路径的 mgncs/ 目录下保存，主要的头文件名称为 `mgncs.h`。

当前的 mGNCS 定义了大量的通用控件，在不久的将来，我们还将在当前 mGNCS 的基础上形成针对特定领域的扩展控件集合，这时，将形成一个独立的函数库，其名称采用 `libmgncs4*` 的方式命名，头文件仍将保存在系统头文件路径的 `mgncs/` 目录下。

