# 第二部分 第十二章 编辑框系列控件
# Chapter 12 of Part 2 Edit Box Series Control


## 编辑框控件简介
## Brief Introduction of Edit Box Control
编辑框控件（Edit）是GUI系统中不可或缺的的重要控件之一，主要用于接受用户的字符输入，实现用户交互和文本编辑的功能。实现上分为单行编辑框（Single
Line Edit）和多行编辑框（Multiline
Edit），单行编辑框用来接受用户内容相对简单的单行文本输入，与之相对，多行文本用来接受复杂的、大量的文本的输入。 

Edit box control is one of the essential controls in GUI system, which is 
mainly used to receive character input of the users and realize the function of
user interaction and text edition. In Realization, it is divided into single
line edit and multiline edit. Single line edit box is used to receive single
line text input with comparatively simple user content, in comparison, 
multiline text is used to receive complicated and large volume of text input.

- 编辑框类层次关系
- Class hierarchical relation of edit box
- [ `mWidget` ](MStudioMGNCSV1dot0PGP2C3#mWidget)
* [ `mScrollWidget` ](MStudioMGNCSV1dot0PGP2C7#m_ScrollWidget)
* [ `mItemView` ](MStudioMGNCSV1dot0PGP2C)
* [ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)
* [ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)
* [ `mSlEdit` ](MStudioMGNCSV1dot0PGP2C12#m_SlEdit)
* [ `mMlEdit` ](MStudioMGNCSV1dot0PGP2C12#m_MlEdit)

- 示例图: <br />
- Example diagram<br />

![alt](figures/edit.png)


## `mEdit`
- *控件窗口类*: `NCSCTRL_EDIT`
- *控件英文名*: Edit
- *简介*: 编辑框系列控件的基础类，是单行编辑框和多行编辑框的抽象父类，定义了两者共同的使用接口。
- *示意图*: %RED%抽象类,不能直接使用%ENDCOLOR%

- *Control window class*: `NCSCTRL_EDIT`
- *Control English name*: Edit
- *Brief introduction*: Foundation class of edit box series controls, it is the
abstract parent class of single line edit box and multiline edit box, which
defines the common use interface of the two.
- *Schematic diagram*: %RED%Abstract class, and cannot be used
directly%ENDCOLOR% 

### `mEdit风格`
### Style of `mEdit`
继承自[ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)的风格
| *风格名* | *mstudio属性名* | *说明* |
| `NCSS_EDIT_LEFT` | Align->Left | 左对齐 |
| `NCSS_EDIT_CENTER` | Align->Center | 水平居中 |
| `NCSS_EDIT_RIGHT` | Align->Right | 右对齐 |
| `NCSS_EDIT_UPPERCASE` | Case->Upper | 输入内容自动转成大写 |
| `NCSS_EDIT_LOWERCASE` | Case->Lower | 输入内容自动转成小写 |
| `NCSS_EDIT_NOHIDESEL` | `HideSel->FALSE` | 当编辑框失去焦点的时候，选中的内容依然保持选中状态 |
| `NCSS_EDIT_READONLY` | `ReadOnly->TRUE` | 内容只读 |
| `NCSS_EDIT_BASELINE` | `BaseLine->TRUE` | 内容带下划线显示 |

It is inherited from the style of [ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)
| *Style name* | *mstudio property name* | *Explanation* |
| `NCSS_EDIT_LEFT` | Align->Left | Left aligned |
| `NCSS_EDIT_CENTER` | Align->Center | Horizontal centering |
| `NCSS_EDIT_RIGHT` | Align->Right | Right aligned |
| `NCSS_EDIT_UPPERCASE` | Case->Upper | The input content is automatically converted to capital letter |
| `NCSS_EDIT_LOWERCASE` | Case->Lower | The input content is automatically converted to lower case letter |
| `NCSS_EDIT_NOHIDESEL` | `HideSel->FALSE` | When the edit box loses focus, the selected content still remains selected status |
| `NCSS_EDIT_READONLY` | `ReadOnly->TRUE` | The content is read only |
| `NCSS_EDIT_BASELINE` | `BaseLine->TRUE` | Content underlined display |

### `mEdit属性`
### Property of `mEdit`
继承自[ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)的属性
| *属性* | *mstudio属性名* | *类型* | *权限* | *说明* |
| `NCSP_EDIT_LIMITTEXT` | `MaxLength` | int | `RW` | 字符数目限定值 |
| `NCSP_EDIT_CARETPOS` | -- | int | `RW` | 光标位置 |

It is inherited from the property of [ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)
| *Property* | *mstudio property name* | *Type* | *Authority* | *Explanation* |
| `NCSP_EDIT_LIMITTEXT` | `MaxLength` | int | `RW` | Character number limit value |
| `NCSP_EDIT_CARETPOS` | -- | int | `RW` | Cursor location |

### `mEdit事件`
### Event of `mEdit`
继承自[ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)的事件
| *事件ID* | *参数* | *说明* |
| `NCSN_EDIT_CHANGE` | -- | 内容变化 |
| `NCSN_EDIT_CONTCHANGED` | -- | 当edit失去焦点时，内容发生变化了 |
| `NCSN_EDIT_UPDATE` | -- | 内容被刷新，当通过setText, `resetContent,方法改变时，或改变属性时` |
| `NCSN_EDIT_SELCHANGED` | -- | 选中部分改变 |
| `NCSN_EDIT_MAXTEXT` | -- | 字符数量饱和 |
| `NCSN_EDIT_SETFOCUS` | -- | 获得焦点 |
| `NCSN_EDIT_KILLFOCUS` | -- | 失去焦点 |

It is inherited from the event of [ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)
| *Event `ID*` | *Parameter* | *Explanation* |
| `NCSN_EDIT_CHANGE` | -- | Content changes |
| `NCSN_EDIT_CONTCHANGED` | -- | When edit loses the focus, the content changes |
| `NCSN_EDIT_UPDATE` | -- | The content is refreshed when changed through `setText` and `resetContent` method or the property is changed |
| `NCSN_EDIT_SELCHANGED` | -- | The selected part changes |
| `NCSN_EDIT_MAXTEXT` | -- | Character number is saturated |
| `NCSN_EDIT_SETFOCUS` | -- | Get the focus |
| `NCSN_EDIT_KILLFOCUS` | -- | Lose the focus |

### `mEdit方法`
### Method of `mEdit`
继承自[ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)的方法

It is inherited from the method of[ `mScrollView` ](MStudioMGNCSV1dot0PGP2C)
---++++ `setContent`
%CODE{cpp}%
void `setContent(mEdit` *self, const char* str, int start, int len)
```
```

---++++ `replaceText`
%CODE{cpp}%
void `replaceText(mEdit` *self, const char* str,
int start, int len, int `replace_start,` int `replace_end)`
```
```

---++++ insert
%CODE{cpp}%
void insert(mEdit *self, const char* str, int start, int len, int at)
```
```

---++++ append
%CODE{cpp}%
void append(mEdit *self, const char* str, int start, int len)
```
```

---++++ `getTextLength`
%CODE{cpp}%
int `getTextLength(mEdit` *self)
```
```

---++++ `getContent`
%CODE{cpp}%
int `getContent(mEdit` *self, char *strbuff, int `buf_len,` int start, int end)
```
```

---++++ `setSel、getSel`
%CODE{cpp}%
int `setSel(mEdit` *self, int start, int end)
int `getSel(mEdit` *self, int *pstart, int *pend)
```
```

---++++ `setMargin`
%CODE{cpp}%
void `setMargin(mEdit` *self, int left, int top, int right, int bottom)
```
```

---++++ copy、paste、cut
%CODE{cpp}%
void copy(mEdit *self)
void cut(mEdit *self)
void paste(mEdit *self)
`TextCopyPaste` * `setCopyPaste(mEdit` *self, `TextCopyPaste*` cp)
```
```
- 参数：<BR>
- pos -- 需要可见的位置
- 说明：<BR>
控制编辑区的滚动，使<pos>位置的字符变为可见。
- 示例：<BR>

- Parameter: <BR>
- pos -- location needs to be visible
- Explanation: <BR>
Control scrolling of the edit region, making the characters of the location
<pos> become visible.
- Example: <BR>
%CODE{cpp}%
//是第201个字符处可见

// Visible at No. 201 character
_c(edit)- >makevisible(edit, 201);
```
```

## `mMlEdit`
- *控件窗口类*: `NCSCTRL_MLEDIT`
- *控件英文名*: Multiline Edit 或者 `MlEdit`
- *简介*: 多行文本编辑框
- *示意图*:

- *Control window class*: `NCSCTRL_MLEDIT`
- *Control English name*: Multiline Edit 或者 `MlEdit`
- *Brief introduction*: Multiline text edit box
- *Schematic diagram*:

![alt](figures/mledit.png)


### `mMlEdit风格`
### Style of `mMIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的风格
| *风格名* | *mstudio属性名* | *说明* |
| `NCSS_MLEDIT_AUTOWRAP` | `AutoWrap->TRUE` | 自动换行 |

It is inherited from the style of [ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)
| *Style name* | *mstudio property name* | *Explanation* |
| `NCSS_MLEDIT_AUTOWRAP` | `AutoWrap->TRUE` | Automatic wrap |

### `mMlEdit属性`
### Property of `mMIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的属性
| *属性* | *mstudio属性名* | *类型* | *权限* | *说明* |
| `NCSP_MLEDIT_LINECOUNT|` -- | int | `RO` | 行数 |
| `NCSP_MLEDIT_LINEHEIGHT|` `LineHeight` | int | `RW` | 行高 |
| `NCSP_MLEDIT_LINEFEEDISPCHAR` | -- | char | `WO` | 换行符改用该字符显示出来 |
| `NCSP_MLEDIT_LINESEP` | `LineSeperator` | char | `RW` | 换行符标记，默认是‘\n’ |
| `NCSP_MLEDIT_CARETSHAPE` | `CaretShap` | int | `RW` | 光标形状ED_CARETSHAPE_LINE 或者 `ED_CARETSHAPE_BLOCK` |
| `NCSP_MLEDIT_NUMOFPARAGRAPHS` | -- | int | `RO` | 段落的数目 |

It is inherited from the property of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit) 
| *Property* | *mstudio property name* | *Type* | *Authority* | *Explanation* |
| `NCSP_MLEDIT_LINECOUNT|` -- | int | `RO` | Row number |
| `NCSP_MLEDIT_LINEHEIGHT|` `LineHeight` | int | `RW` | Row height |
| `NCSP_MLEDIT_LINEFEEDISPCHAR` | -- | char | `WO` | Line break is displayed by this character |
| `NCSP_MLEDIT_LINESEP` | `LineSeperator` | char | `RW` | Line break symbol, “\n” by default |
| `NCSP_MLEDIT_CARETSHAPE` | `CaretShap` | int | `RW` | Cursor shape `ED_CARETSHAPE_LINE` or `ED_CARETSHAPE_BLOCK` |
| `NCSP_MLEDIT_NUMOFPARAGRAPHS` | -- | int | `RO` | Number of paragraphs |


### `mMlEdit事件`
### Event of `mMIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的事件<BR>
%RED%没有新引入的事件%ENDCOLOR%

It is inherited from the event of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit)<BR> 
%RED%There is no newly introduced event%ENDCOLOR%

### `mMlEdit方法`
### Method of `mMIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的方法<BR>

It is inherited from the method of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit)<BR> 

### `mMlEdit编程示例`
### Programming Example of `mMIEdit`

- `MlEdit示例代码` ：[edit.c](%ATTACHURL%/edit.c.txt)
- 我们这样来定义MlEdit的使用模板

- `MlEdit` Example code: [edit.c](%ATTACHURL%/edit.c.txt)
- We define the use template of `MIEdit` in this way

%CODE{cpp}%
%INCLUDE{"%ATTACHURL%/edit.c.txt"
pattern="^.*?//START_OF_MLEDIT_TEMPLATE(.*?)//END_OF_MLEDIT_TEMPLATE.*"}% 

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
