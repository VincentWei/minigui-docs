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
| *Event ID* | *Parameter* | *Explanation* |
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
#### `setContent`
```cpp
void setContent(mEdit *self, const char* str, int start, int len)
```
- 参数：<BR>
- str -- 显示在edit中的文字内容
- start -- 显示开始位置(相对str的起始位置)，0表示从头开始
- len -- 显示字符数目，-1表示一直到str的结束为止
- 说明： <BR>
设置编辑框的显示内容，该方法会从str字符串中获取从第<start>个字符位置开始的一共<len>个字符，替换掉edit中现有的内容。
- 示例：<BR>

- Parameter<BR>
- str -- literal content displayed in edi
- start -- display starting location (relative to the starting location of 
str), 0 represents starting from the beginning
- len -- display character number, -1 represents ending till the end of str
- Explanation: <BR>
Set the display content of the edit box. The method will get altogether
characters from No. character location from str character string, and replace
the existing content in edit.
- Example:<BR>
```cpp
//edit中会显示字符串"dddd Show Me"从第6个字符开始一直到结尾的字符串，这里就是“Show Me”

// In edit, character string starting from the sixth character till the end of characterstring “dddd Show Me” will be displayed, and here it is “Show Me”
_c(edit)->setContent(edit, "dddd Show Me", 6, -1);
```

#### `replaceText`
```cpp
void replaceText(mEdit *self, const char* str, 
    int start, int len, int replace_start, int replace_end)
```
- 参数：<BR>
- str -- 用于替换的源字符串
- start -- 用于替换的源文本相对于str的的偏移，0表示从头开始
- len -- 用到的源文本的长度，-1表示从start开始，直到str结束
- `replace_start` -- 替换开始的位置（相对于edit中的现有内容）
- `replace_end` -- 替换结束的位置（相对于edit中的现有内容）
- 说明：<BR>

字符串的替换，该方法会从str字符串中获取从第<start>个字符位置开始的一共<len>个字符，替换掉edit中现有的从<replace_start>到<repalce_end>的内容。str是要替换成的字符串，start是相对str的起始位置，0表示从头开始，len是长度，-1表示一直到str的结束为止，replace_start、replace_end分别是要替换的位置的起点和终点，是相对于edit中现有的文本内容的位置偏移。 
- 示例：<BR>

- Parameter<BR>
- str -- source character string used for replacement
- start -- deviation of the source text used for replacement relative to str, 0
represents starting from the beginning
- len -- length used to the source text, -1 represents starting from start and
ending till str
- `replace_start` -- replace the starting location (relative to the existing
content in edit)
- `replace_end` -- replace the ending location (relative to the existing 
content in edit)
- Explanation: <BR>
Replacement of character string, the method will get altogether characters
starting from No. character location from str character string, and replaces 
the existing content from to in edit. Str is the character string to be 
replaced to, start is the starting location relative to str, 0 represents
starting from the beginning, len is the length, -1 represents ending till the
end of str, `replace_start` and `replace_end` are the starting point and ending
point of the location to be replaced, and they are location deviation relative
to the existing text content in edit.
- Example:<BR>
```cpp
//edit中会用字符串"dddd Show Me"从第6个字符开始一直到结尾的字符串（这里就是“Show Me”），
//来替换掉edit中现有文本的从第二个到第十个的字符

// In edit, character string starting from the sixth character to the end of the character string “dddd Show Me” will be used (here it is “Show Me”),
// To replace the characters from the second one to the tenth one of the existing text in edit
_c(edit)->replaceText(edit, "dddd Show Me", 6, -1, 2, 10);
```

#### insert
```cpp
void insert(mEdit *self, const char* str, int start, int len, int at)
```
- 参数：<BR>
- str -- 要插入的源字符串
- start -- 使用到的源文本的起始位置，0表示从头开始
- len -- 使用到的源文本的长度，-1表示从start开始，直到str结束
- at -- 插入点的位置（相对于edit中的现有内容）,-1表示结尾处
- 说明：<BR>

字符串的插入，该方法会从str字符串中获取从第<start>个字符位置开始的一共<len>个字符，插入到edit中现有的内容的第<at>个字符的位置。str是要插入的字符串，start是相对str的起始位置，0表示从头开始，len是长度，-1表示一直到str的结束为止, 
at参数是要插入的位置，是相对于edit中现有的文本内容的位置偏移。 
- 示例：<BR>

- Parameter<BR>
- str -- source character string to be inserted
- start -- starting location of the source text used, 0 represents starting 
from the beginning
- len -- length of the source text used, -1 represents starting from start, and
ending till str
- at -- location of the insert point (relative to the existing content in 
edit), -1 represents the end
- Explanation: <BR>
Insert of the character string, the method will get altogether characters
starting from No. character location in str character string, and it is
inserting into location of No. character of the existing content in edit. Str 
is the character string to be inserted, start is the starting location relative
to str, 0 represents starting from the beginning, len is the length, -1
represents ending till the end of str, at parameter is the location to insert,
and it is the location deviation relative to the existing text content in edit
- Example:<BR>
```cpp
//edit中会用字符串"dddd Show Me"从第6个字符开始一直到结尾的字符串（这里就是“Show Me”），
//来插入到edit中现有文本的从第二个字符之后

//In edit, character string starting from the sixth character till the end of the character string “dddd Show Me” will be used (here it is “Show Me”), 
// To insert to after the second character of the existing text in edit
_c(edit)->insert(edit, "dddd Show Me", 6, -1,  2);
```

#### append
```cpp
void append(mEdit *self, const char* str, int start, int len)
```
- 参数：<BR>
- str -- 要追加的源字符串
- start -- 使用到的源文本的起始位置，0表示从头开始
- len -- 使用到的源文本的长度，-1表示从start开始，直到str结束
- 说明：<BR>

字符串的追加，该方法会从str字符串中获取从第<start>个字符位置开始的一共<len>个字符，追加到edit中现有的内容的后面。str是要追加的字符串，start是相对str的起始位置，0表示从头开始，len是长度，-1表示一直到str的结束为止。 
- 示例：<BR>

- Parameter<BR>
- str -- source character string to append
- start -- starting location of the source text used, 0 represents starting 
from the beginning
- len -- length of the source text used, -1 represents starting from start and
ending till str
- Explanation: <BR>
Append the character string, the method will get altogether characters starting
from No. character location from str character string, and append to after the
existing content in edit. str is the character string to append, start is the
starting location relative to str, 0 represents starting from the beginning, 
len is the length, and -1 represents ending till the end of str.
- Example:<BR>
```cpp
//edit中会用字符串"dddd Show Me"从第6个字符开始一直到结尾的字符串（这里就是“Show Me”），
//来追加到edit中现有文本的末尾

// In edit, character string starting from the sixth character till the end of the character string “dddd Show Me” will be used (here it is “Show Me”),
// To append till the end of the existing text in edit
_c(edit)->append(edit, "dddd Show Me", 6, -1);
```

#### `getTextLength`
```cpp
int getTextLength(mEdit *self)                                        
```
- 说明：<BR>
获取Edit中字符串内容的长度
- 示例：<BR>

- Explanation: <BR>
Get length of the content of the character string in Edit
- Example:<BR>
```cpp
int text_len = _c(edit)->getTextLength(edit);
```

#### `getContent`
```cpp
int getContent(mEdit *self, char *strbuff, int buf_len, int start, int end)
```
- 参数：<BR>
- strbuff -- 获取到字符串的存放位置（应该提前分配好存放空间）
- `buff_len` -- strbuff的大小
- start -- 获取内容的起始位置
- end -- 获取内容的终止位置
- 说明：<BR>
获取Edit中字符串内容，从现有的内容中获取从<start>到<end>位置的内容写入到strbuff中，写入的最大数目限定为buff_len。
- 示例：<BR>

- Parameter:<BR>
- strbuff -- get storage location to the character string (storage space shall
be distributed in advance)
- `buff_len` -- size of strbuff
- start -- starting location of the obtained content
- end -- ending location of the obtained content
- Explanation:<BR>
Get character string content in edit, and get the content from to location from
the existing content and write into strbuff, and the maximum number to write in
is limited to `buff_len.`
- Example: <BR>
```cpp
char buff[128];
_c(edit)->getContent(edit, buff, 127, 0, -1);//取出edit中的全部内容，buff最多存127个字符

// Get out all the content in edit, and buff stores 127 characters to the maximum
```

#### `setSel、getSel`
```cpp
    int setSel(mEdit *self, int start, int end)
    int getSel(mEdit *self, int *pstart, int *pend)
```
- 参数：<BR>
- start \end -- 选中区域的起点、终点
- pstart\pend -- 选中区域的起点、终点，用于函数返回
- 说明：<BR>
设置、获取选中文本的区域，后两个参数分别对应选中区域的起点和终点。
- 示例：<BR>

- Parameter: <BR>
- start \end -- starting point and ending point of the selected region
- pstart\pend -- starting point and ending point of the selected region, used
for function return
- Explanation: <BR>
Set and get the region of the selected text, and the last two parameters
correspond to the starting point and ending point of the selected region
respectively 
- Example: <BR>
```cpp
_c(edit)->setSel(edit, 2, 10);//设置edit的第2~10个字符为选中状态

// Set No.2 to No.10 characters of edit as selected status

int ps,pe;
_c(edit)->getSel(edit, &ps, &pe);//获取选中区域

// Get the selected region
```

#### `setMargin`
```cpp
void setMargin(mEdit *self, int left, int top, int right, int bottom)
```
- 参数：<BR>
- left,top,right,bottom -- 上下左右的留白，这个参数不是矩形的概念，只是沿用了矩形的数据结构方便参数传递
- 说明：<BR>
设置编辑区的上下左右留白
- 示例：<BR>

- Parameter: <BR>
- left,top,right,bottom -- margin of left, top, right and bottom, the parameter
is not a concept of rectangle, and it just continues to use the data structure
of rectangle for the convenience of parameter transmission
- Explanation: <BR>
Set left, top, right and bottom margin of the edit region
- Example: <BR>
```cpp
//设置留白

// Set margin
_c(edit)- >setMargin(edit, 10,10,10,10);
```

#### copy、paste、cut
```cpp
    void copy(mEdit *self)
    void cut(mEdit *self)
    void paste(mEdit *self)
    TextCopyPaste * setCopyPaste(mEdit *self, TextCopyPaste* cp)
```
剪切、复制、粘贴都是针对选中区域的操作，edit中默认实现了一组使用minigui剪切板的操作集,用户还可以通过setCopyPaste设置自己实现的操作集。


Cut, copy and paste aim at the operation of the selected region. In edit, a
group of operation set using minigui cut board is realized by default, and the
users can set operation set realized by itself through `setCopyPaste`.

#### makevisible
```cpp
    BOOL makevisible(mEdit *self, int pos)
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
```cpp
//是第201个字符处可见

// Visible at No. 201 character
_c(edit)- >makevisible(edit, 201);
```

## `mSlEdit`
- *控件窗口类*: `NCSCTRL_SLEDIT`
- *控件英文名*: Single Line Edit 或者SlEdit
- *简介*: 单行文本编辑框
- *示意图*:

- *Control window class*: `NCSCTRL_SLEDIT`
- *Control English name*: Single Line Edit 或者SlEdit
- *Brief introduction*: Single line text edit box
- *Schematic diagram*:

![alt](figures/sledit.png)


### `mSlEdit风格`
### Style of `mSIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的风格
| *风格名* | *mstudio属性名* | *说明* |
| `NCSS_SLEDIT_PASSWORD` | Password->TRUE | 编辑框的内容以密码输入的方式屏蔽显示 |
| `NCSS_SLEDIT_AUTOSELECT` | `AutoSelect->TRUE` | 自动选中风格，获得焦点后文本自动成选中状态 |

It is inherited from the style of [ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)
| *Style name* | *mstudio property name* | *Explanation* |
| `NCSS_SLEDIT_PASSWORD` | Password->TRUE | Content of the edit box is shield displayed in the mode of password input |
| `NCSS_SLEDIT_AUTOSELECT` | `AutoSelect->TRUE` | Automatic selected style, after the focus is obtained, the text automatically becomes selected status |


### `mSlEdit属性`
### Property of `mSIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的属性
| *属性* | *mstudio属性名* | *类型* | *权限* | *说明* |
| `NCSP_SLEDIT_TIPTEXT` | `ToolTip` | char * | `RW` | 提示信息字符串，当没有输入时，用来提示用户的信息 |
| `NCSP_SLEDIT_PWDCHAR` | `PasswordChar` | char | `RW` | pass word 显示的字符，只有NCSS_SLEDIT_PASSWORD风格的有效，默认是‘*’ |

It is inherited from the property of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit) 
| *Property* | *mstudio property name* | *Type* | *Authority* | *Explanation* |
| `NCSP_SLEDIT_TIPTEXT` | `ToolTip` | char * | `RW` | Prompt information character string, when there is no input, information used to prompt users |
| `NCSP_SLEDIT_PWDCHAR` | `PasswordChar` | char | `RW` | Character displayed by pass word, only `NCSS_SLEDIT_PASSWORD` style is valid, ‘*’ by default |


### `mSlEdit事件`
### Event of `mSIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的事件
| *事件ID* | *参数* | *说明* |
| `NCSN_SLEDIT_ENTER` | -- | 捕获到enter键消息 |

It is inherited from the event of [ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)
| *Event ID* | *Parameter* | *explanation* |
| `NCSN_SLEDIT_ENTER` | -- | Capture enter key information |


### `mSlEdit方法`
### Method of `mSIEdit`
继承自[ `mEdit` ](MStudioMGNCSV1dot0PGP2C12#mEdit)的方法<BR>
%RED%没有新引入的方法%ENDCOLOR%

It is inherited from the method of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit)<BR> 
%RED%There is no newly introduced method%ENDCOLOR%

### `mSlEdit编程示例`
### Programming Example of `mSIEdit`

- `SlEdit示例代码` ：[edit.c](%ATTACHURL%/edit.c.txt)
- 我们这样来定义SlEdit的使用模板

- `SlEdit` Example code: [edit.c](%ATTACHURL%/edit.c.txt)
- We define use template of `SIEdit` in this way

```cpp
%INCLUDE{"%ATTACHURL%/edit.c.txt" pattern="^.*?//START_OF_SLEDIT_TEMPLATE(.*?)//END_OF_SLEDIT_TEMPLATE.*"}%
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
| `NCSP_MLEDIT_LINECOUNT`| -- | int | `RO` | 行数 |
| `NCSP_MLEDIT_LINEHEIGHT`| `LineHeight` | int | `RW` | 行高 |
| `NCSP_MLEDIT_LINEFEEDISPCHAR` | -- | char | `WO` | 换行符改用该字符显示出来 |
| `NCSP_MLEDIT_LINESEP` | `LineSeperator` | char | `RW` | 换行符标记，默认是‘\n’ |
| `NCSP_MLEDIT_CARETSHAPE` | `CaretShap` | int | `RW` | 光标形状ED_CARETSHAPE_LINE 或者 `ED_CARETSHAPE_BLOCK` |
| `NCSP_MLEDIT_NUMOFPARAGRAPHS` | -- | int | `RO` | 段落的数目 |

It is inherited from the property of [ `mEdit`
](MStudioMGNCSV1dot0PGP2C12#mEdit) 
| *Property* | *mstudio property name* | *Type* | *Authority* | *Explanation* |
| `NCSP_MLEDIT_LINECOUNT`| -- | int | `RO` | Row number |
| `NCSP_MLEDIT_LINEHEIGHT`| `LineHeight` | int | `RW` | Row height |
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

```cpp
%INCLUDE{"%ATTACHURL%/edit.c.txt" pattern="^.*?//START_OF_MLEDIT_TEMPLATE(.*?)//END_OF_MLEDIT_TEMPLATE.*"}%
```

[Next](MStudioMGNCSV1dot0PGP2C11][Previous]] < [[MStudioMGNCSV1dot0PG][Index]] > [[MStudioMGNCSV1dot0PGP2C13) 




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
