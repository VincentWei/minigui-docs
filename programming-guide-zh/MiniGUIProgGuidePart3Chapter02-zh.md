# 文本的处理和显示

前面已经讲到，MiniGUI 的文本处理和显示部分有一些自己的特色。本章将详细介绍和文本处理相关的一些基本概念，并介绍 MiniGUI 中用于文本处理和显示的 `API`。

## 1 字符集和编码

字符集（charset），是为了表示某种语言而定义的字符集合；编码则是为了在计算机中表示某个字符集中的字符而设定的编码规则，它通常以固定的顺序排列字符，并以此做为记录、存贮、传递、交换的统一内部特征。接触过计算机的人都知道美国国家标准局定义的 `ASCII` 码。我们可以将 `ASCII` 理解为美国英语字符集的一种编码形式；这种编码形式使用一个 7 位字节来表示一个字符，字符范围从 0x00 到 0x7F。

> 【提示】在 Linux 命令行键入 `man ASCII` 可查阅 `ASCII` 码的定义。

在计算机的应用范围扩大到全球各个地区的时候，仅仅使用 `ASCII` 无法满足非英语国家的需求。为此，几乎所有的国家都定义了针对官方语言的字符集以及编码规范或者标准。大家都熟悉的 `GB2312-80` 标准就是中国定义的简体中文字符集标准，其中含有 682 个符号、6763 个汉字，它共分 87 个区，每个区含 94 个字符。类似的还有用于单字节字符集的 `ISO8859` 字符集系列，日本的`JISX0201`、`JISX0208` 字符集，以及台湾省制定的 `BIG5` 繁体中文字符集标准等等。

一个字符集可以有不同的编码形式。拿 `GB2312` 字符集来讲，通常我们使用的是 `EUC` 编码（即扩展 `UNIX` 编码），它将每个 `GB2312` 字符编码为 2 个字节，高低两个字节的范围均为 0xA1\~0xFE。高字节表示的是 `GB2312` 字符的区码，低字节表示的 `GB2312` 字符的位码。还有一种常见的 `GB2312` 编码形式是 `HZ` 编码，它去掉了 `EUC` 编码的最高位，使得汉字可以用 `ASCII` 码中的字符来表示，比如 `EUC` 编码中的汉字“啊”编码为“0xB1A1”，而 `HZ` 编码则为“\~{1!~}”。

随着各个国家和地区字符集标准的出台和升级，又引入了兼容性问题。比如，一个采用 `GB2312` `EUC` 编码的文本文件就无法在采用 `BIG5` 编码的系统上正常显示。为此，一些国际组织开始致力于全球统一字符集标准的开发，也就是我们熟知的 `UNICODE` 字符集。

国际标准组织于 1984 年 4 月成立 `ISO/IEC` `JTC1/SC2/WG2` 工作组，针对各国文字、符号进行统一性编码。1991 年美国跨国公司成立 Unicode Consortium，并于 1991 年 10 月与 `WG2` 达成协议，采用同一编码字集。目前，`UNICODE 2.0` 版本包含符号 6811 个，汉字 20902 个，韩文拼音 11172 个，造字区 6400 个，保留 20249 个，共计 65534 个字符。`UNICODE` 字符集具有多种编码形式，最常见的是采用 16 位的双字节来表示所有字符，又称 `UCS2`；另外一种是 `UTF8` 编码形式，这种编码形式能够和 `ASCII` 及 `ISO8859-1` 字符集兼容，它是一种变宽的编码形式，也就是说，用来表示字符的字节个数是变化的。

> 【提示】在 Linux 命令行键入 `man unicode` 和 `man utf-8` 可查阅 `UNICODE` 字符集及 `UTF8` 编码的相应信息。

使用 `UNICODE` 可以解决字符集的兼容性问题。但是，许多国家和地区从本地区习惯等方面出发，并不认同 `UNICODE` 字符集。比如中国政府就要求所有操作系统类软件产品，必须支持 `GB18030` 字符集，而不是 `UNICODE` 字符集。原因是 `GB18030` 字符集和中国大陆地区广泛使用的 `GB2312` 和 `GBK` 字符集兼容；而 `UNICODE` 却不兼容。

`UNICODE` 对于通用性操作系统提供了解决字符集兼容性的办法，但对于嵌入式系统来讲，通过 `UNICODE` 来支持各种各样的字符集并不是最好的解决办法。MiniGUI 在内部并没有采用 `UNICODE` 为基础实现多字符集的支持。MiniGUI 的策略是，对某个特定的字符集，在内部使用和该字符集默认编码完全一致的内码表示。然后，通过一系列抽象的接口，提供对某个特定字符集文本的一致分析接口。该接口既可以用于对字体模块，也可以用来实现多字节字符串的分析功能。如果要增加对某个字符集的支持，只需要实现该字符集的接口即可。到目前为止，MiniGUI 已经实现了 `ISO8859-x` 的单字节字符集支持，以及 `GB2312`、`GBK`、`GB18030`、`BIG5`、`EUCKR`、`Shift-JIS`、`EUCJP` 等多字节字符集，甚至变宽字符集编码形式的支持。通过我们的字符集抽象接口，MiniGUI 也对 `UNICODE` 中的 `UTF-8`和 `UTF-16` 编码提供了支持。

> 【提示】你可以将 MiniGUI 中的字符集支持理解为对该字符集特定编码形式的支持。

MiniGUI 对多字符集的支持通过逻辑字体接口来实现。应用程序在显示文本时，通常要建立逻辑字体，并指定该字体使用的字符集编码名称。在创建逻辑字体之后，应用程序就可以使用该逻辑字体显示文本或者分析文本结构。

## 2 设备字体

设备字体是直接与底层字体相关联的数据结构。每个设备字体有一个操作集（即 `font_ops`），其中包含了 `get_char_width`、`get_char_bitmap` 等抽象接口。每个 MiniGUI 所支持的字体类型，比如等宽光栅字体（`RBF`）、变宽光栅字体（`VBF`）、`TrueType` 字体、`Adobe Type1` 字体等均对应一组字体操作集。通过这个字体操作集，我们就可以从相应的字体文件中获得某个字符的点阵（对光栅字体而言）或者轮廓（对矢量字体而言）。之后，MiniGUI 上层的绘图函数就可以将这些点阵输出到屏幕上，最终就可以看到显示在屏幕上的文字。

除字符集之外，要正确显示文本，还需要获得各个字符对应的形状数据，这些形状数据称为字型，保存在某个特定类型的文件中，这个文件通常称为“字体”文件。字体文件的类型有许多，最常见的是点阵字体，其中以位图形式保存了各个字符的点阵字型信息，通常只针对某个特定的大小。另外一种应用更为广泛的是矢量字体，它保存的是各个字符的轮廓信息，可通过特定的算法进行缩放处理。常见的矢量字体类型有 `TrueType` 和 `Adobe Type1` 等等。

和字符集类似，MiniGUI 也针对字体定义了一系列抽象接口，如果要增加对某种字体的支持，只需实现该字体类型的接口即可。到目前为止，MiniGUI 已经实现了对 `RBF`、`VBF` 字体（这是 MiniGUI 定义的两种点阵字体格式）、`TrueType`、`Adobe Type1` 字体等的支持。同时 MiniGUI 还提供了对 `QPF`（Qt Pre-rendered Fonts）字体的支持。MiniGUI 可以对点阵字体进行自动放大处理，并可针对电视等特殊显示设备实现防锯齿功能。

 此外，MiniGUI 还实现了位图字体，它是一种使用位图 `BITMAP` 来显示文字的设备字体。这种字体可以根据用户自己制做的位图来构建字型，可以与其它逻辑字体接口一样提供给应用程序及控件使用；

`VBF V3.0` 字体是对 `VBF V2.0` 的升级版本，扩大了其能适用的字符集范围，不再限制只能用于支持 Latin 体系的字符集，单个 `VBF` 字体可包含的字型数目不再限制于 255 以内。

`UPF` 字体是 `QPF` 字体的优化版本，便于 MiniGUI 通过内存映射的方式使用，降低了 MiniGUI-Processes 模式下使用 `QPF` 字体时的内存占用。支持阿拉伯文，希伯莱文等双向文本的显示。MiniGUI 在初始化时，要读取 `MiniGUI.cfg` 中的字体定义并装载指定字体文件，装载后的字体在 MiniGUI 内部称为“设备字体”。设备字体定义了这种字体的样式名、风格、大小以及它所支持的字符集。MiniGUI 在创建逻辑字体时，要根据已装载的设备字体，以及应用程序指定的字体类型、样式名、大小、字符集等信息寻找合适的设备字体来显示文本。

MiniGUI 提供了动态加载和卸载设备字体的功能，函数接口定义如下：

```c
BOOL GUIAPI LoadDevFontFromFile(const char *devfont_name, 
const char *file_name, DEVFONT** devfont);

void GUIAPI DestroyDynamicDevFont (DEVFONT **devfont);
```

### 2.1 位图设备字体

位图设备字体有点特殊，别的设备字体在配置文件 `MiniGUI.cfg` 中就可以配置，但是位图设备字体在应用程序里面进行创建。下面是相关的函数：

```c
DEVFONT *CreateBMPDevFont (const char *bmpfont_name, const BITMAP* glyph_bmp,
const char* start_mchar, int nr_glyphs, int glyph_width);
BOOL AddGlyphsToBMPFont (DEVFONT* dev_font, BITMAP* glyph_bmp,
const char* start_mchar, int nr_glyphs, int glyph_width)

void DestroyBMPFont (DEVFONT* dev_font)
```

- `CreateBMPDevFont`   该函数用来创建位图设备字体，并将创建成功的设备字体加入到设备字体链表。需要传给函数的参数有：包含有字体的类别、样式名、风格、大小以及它所支持的字符集的设备字体名、位图结构体指针、设备字体所包含字符的第一个字符的数据、设备字体所包含字符的个数以及每个字符的显示宽度。需要注意的是，位图设备字体里面每一个位图所包含的字符必须是连续的，而且字符是等宽字符。

- `AddGlyphsToBMPFont`   该函数用来往已创建的位图设备字体里面增加字符，使位图字体能显示更多的字符。函数的第一个参数就是设备字体指针，其他的参数和 `CreateBMPDevFont` 一样。

- `DestroyBMPFont`   该函数用来销毁位图设备字体。

下面的代码，首先创建能够显示 0 至 9 的位图设备字体，字体样式为“led”，然后，往该设备字体里面增加 ABCDEF、加号等字符的显示，然后创建 led 样式的逻辑字体：

```c
#define BMP_FILE_DIGIT    "digits1.png"
#define BMP_FILE_LETTER   "digits2.png"
#define BMP_FILE_SYMBOL   "digits3.png"
#define BMP_FILE_DDOT     "digits4.png"

static LOGFONT *logfont, *old ;
static DEVFONT *dev_font;


if (LoadBitmap (HDC_SCREEN, &digit_bmp, BMP_FILE_DIGIT)) {
        fprintf (stderr, "Fail to load bitmap. \n");
        return 1;
}

if (LoadBitmap (HDC_SCREEN, &letter_bmp, BMP_FILE_LETTER)) {
        fprintf (stderr, "Fail to load bitmap. \n");
        return 1;
}

if (LoadBitmap (HDC_SCREEN, &symbol_bmp, BMP_FILE_SYMBOL)) {
        fprintf (stderr, "Fail to load bitmap. \n");
        return 1;
}

if (LoadBitmap (HDC_SCREEN, &ddot_bmp, BMP_FILE_DDOT)) {
        fprintf (stderr, "Fail to load bitmap. \n");
        return 1;
}

dev_font = CreateBMPDevFont ("bmp-led-rrncnn-10-15-ISO8859-1",
&letter_bmp, "A", 6, 10);
AddGlyphsToBMPFont (dev_font, &digit_bmp, "0", 10, 10);
AddGlyphsToBMPFont (dev_font, &symbol_bmp, "+", 4, 10);
AddGlyphsToBMPFont (dev_font, &ddot_bmp, ":", 1, 10);

logfont = CreateLogFont (FONT_TYPE_NAME_BITMAP_BMP, "led",
"ISO8859-1",
FONT_WEIGHT_REGULAR, FONT_SLANT_ROMAN,
FONT_SETWIDTH_NORMAL, FONT_SPACING_CHARCELL,
FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
10, 0);
```

下面的图片是代码里面用到的图片，图片名称依次是：digits1.png、digits2.png、digits3.png、digits4.png 

![digits1](figures/Part2Chapter02-digits1.png) 

![digits2](figures/Part2Chapter02-digits2.png)

![digits3](figures/Part2Chapter02-digits3.png)

![digits4](figures/Part2Chapter02-digits4.png) 

> 【提示】有关设备字体的定义及名称格式信息，请参阅《MiniGUI 用户手册》 3.1.4 小节。

## 3 逻辑字体

逻辑字体是一个 `GDI` 物件，它的代号储存在 `HFONT` 型态的变数中，逻辑字体是字体的描述。和逻辑画笔及逻辑画刷一样，它是抽象的物件，只有当应用程式呼叫 `SelectObject` 将它选入装置内容时，它才成为真实的物件。

MiniGUI 的逻辑字体功能强大，它包括了字符集、字体类型、风格等等丰富的信息，不仅仅可以用来输出文本，而且可以用来分析多语种文本的结构。这在许多文本排版应用中非常有用。在使用 MiniGUI 的逻辑字体之前，首先要创建逻辑字体，并且将其选择到要使用这种逻辑字体进行文本输出的设备上下文当中。每个设备上下文的默认逻辑字体是 `MiniGUI.cfg` 中定义的系统默认字体。你可以调用 `CreateLogFont`、`CreateLogFontByName` 以及 `CreateLogFontIndirect` 三个函数来建立逻辑字体，并利用 `SelectFont` 函数将逻辑字体选择到指定的设备上下文中，在使用结束之后，用 `DestroyLogFont` 函数销毁逻辑字体。注意你不能销毁正被选中的逻辑字体。这几个函数的原型如下（`minigui/gdi.h`）：

```c
PLOGFONT GUIAPI CreateLogFont (const char* type, const char* family, 
const char* charset, char weight, char slant, char flip, 
char other, char underline, char struckout, 
int size, int rotation);
PLOGFONT GUIAPI CreateLogFontByName (const char* font_name);
PLOGFONT GUIAPI CreateLogFontIndirect (LOGFONT* logfont);
void GUIAPI DestroyLogFont (PLOGFONT log_font);

void GUIAPI GetLogFontInfo (HDC hdc, LOGFONT* log_font);

PLOGFONT GUIAPI GetSystemFont (int font_id);

PLOGFONT GUIAPI GetCurFont (HDC hdc);
PLOGFONT GUIAPI SelectFont (HDC hdc, PLOGFONT log_font);
```

下面的程序段建立了多个逻辑字体：

```c
static LOGFONT  *logfont, *logfontgb12, *logfontbig24;

logfont = CreateLogFont (NULL, "SansSerif", "ISO8859-1", 
FONT_WEIGHT_REGULAR, FONT_SLANT_ITALIC, FONT_FLIP_NIL,
FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_LINE, 
16, 0);
logfontgb12 = CreateLogFont (NULL, "song", "GB2312", 
FONT_WEIGHT_REGULAR, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
FONT_OTHER_NIL, FONT_UNDERLINE_LINE, FONT_STRUCKOUT_LINE, 
12, 0);
logfontbig24 = CreateLogFont (NULL, "ming", "BIG5", 
FONT_WEIGHT_REGULAR, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
FONT_OTHER_AUTOSCALE, FONT_UNDERLINE_LINE, FONT_STRUCKOUT_NONE, 
24, 0);
```

其中，第一个字体，即 `logfont` 是属于字符集 `ISO8859-1` 的字体，并且选用 `SansSerif` 体，大小为 16 象素高；`logfontgb12` 是属于字符集 `GB2312` 的字体，并选用 `song` 体（宋体），大小为 12 象素高；`logfontbig24` 是属于字符集 `BIG5` 的字体，并选用 `ming` 体（明体），期望大小为 24 象素高，并且指定了 `FONT_OTHER_AUTOSCALE`，表示可以对字体进行自动放大，以便满足期望的字体大小。

我们还可以调用 `GetSystemFont`  函数返回指定的系统逻辑字体，其中 `font_id` 参数可取如下值：

- `SYSLOGFONT_DEFAULT`：系统默认字体，必须是单字节字符集逻辑字体，必须由 `RBF` 设备字体组成。
- `SYSLOGFONT_WCHAR_DEF`：系统默认多字节字符集字体，通常由 `RBF` 设备字体组成，并且多字节字体的宽度是`SYSLOGFONT_DEFAULT` 逻辑字体的两倍。
- `SYSLOGFONT_FIXED`：固定宽度的系统字体。
- `SYSLOGFONT_CAPTION`：用于显示标题栏文本的逻辑字体。
- `SYSLOGFONT_MENU`：用于显示菜单文本的逻辑字体。
- `SYSLOGFONT_CONTROL`：用于控件的默认逻辑字体。

上述这些系统逻辑字体在 MiniGUI 初始化时根据 `MiniGUI.cfg` 文件中的定义创建。

> 【提示】有关系统逻辑字体的定义及名称格式信息，请参阅《MiniGUI 用户手册》 3.1.5 小节。

`GetCurFont` 函数返回当前选中的逻辑字体，注意不要调用 `DesroyLogFont` 删除系统逻辑字体。

## 4 文本分析

在建立了逻辑字体之后，应用程序就可以利用逻辑字体进行多语种混和文本的分析。这里的多语种混和文本是指，两个不相交字符集的文本组成的字符串，比如 `GB2312` 和 `ISO8859-1`，或者 `BIG5` 和 `ISO8859-2`，通常是多字符集和单字符集之间的混和。利用下面的函数，可以实现多语种混和文本的文本组成分析（`minigui/gdi.h`）：

```c
// Text parse support
int GUIAPI GetTextMCharInfo (PLOGFONT log_font, const char* mstr, int len, 
int* pos_chars);
int GUIAPI GetTextWordInfo (PLOGFONT log_font, const char* mstr, int len, 
int* pos_words, WORDINFO* info_words);
int GUIAPI GetFirstMCharLen (PLOGFONT log_font, const char* mstr, int len);
int GUIAPI GetFirstWord (PLOGFONT log_font, const char* mstr, int len,
WORDINFO* word_info);
```

`GetTextMCharInfo` 函数返回多语种混和文本中每个字符的字节位置。比如对“ABC汉语”字符串，该函数将在 `pos_chars` 中返回 {0, 1, 2, 3, 5} 5 个值。`GetTextWordInfo` 函数则将分析多语种混和文本中每个单词的位置。对单字节字符集文本，单词以空格、`TAB` 键为分界，对多字节字符集文本，单词以单个字符为界。`GetFirstMCharLen` 函数返回第一个混和文本字符的字节长度。
`GetFirstWord` 函数返回第一个混和文本单词的单词信息。

## 5 文本转换

MiniGUI 通过下面一系列接口可以实现多个字符集/编码和 `UNICODE` 内码的相互转换功能。 

```c
typedef unsigned short  UChar16;
typedef signed int    UChar32;

int GUIAPI MB2WCEx (PLOGFONT log_font, void* dest, BOOL wc32, 
const unsigned char* mstr, int n);
#define MB2WC(log_font, dest, mstr, n) \
MB2WCEx (log_font, dest, sizeof(wchar_t) == 4, mstr, n)

int GUIAPI WC2MBEx (PLOGFONT log_font, unsigned char *s, UChar32 wc);
#define WC2MB(log_font, s, wc) \
WC2MBEx (log_font, s, (UChar32)wc);

int GUIAPI MBS2WCSEx (PLOGFONT log_font, void* dest, BOOL wc32, 
const unsigned char* mstr, int mstr_len, int n,
int* conved_mstr_len);

#define MBS2WCS(log_font, dest, mstr, mstr_len, n) \
MBS2WCSEx(log_font, dest, sizeof (wchar_t) == 4, mstr, \
mstr_len, n, NULL)

int GUIAPI WCS2MBSEx (PLOGFONT log_font, unsigned char* dest,  
const void *wcs, int wcs_len, BOOL wc32, int n,
int* conved_wcs_len);

#define WCS2MBS(log_font, dest, wcs, wcs_len, n) \
WCS2MBSEx (log_font, dest, wcs, wcs_len, sizeof (wchar_t) == 4, \
n, NULL)
```

其中 `MB2WCEx` 和 `MBS2WCSEx` 是用于将多字节字符集/编码（如 `GB2312`、`ISO8859`、`UTF-8`、`GBK`、`BIG5` 等）转换为 `UNICODE` 内码的接口。前者一次只转换一个字符，后者一次可转换多个字符。

其中 `WC2MBEx` 和 `WCS2MBSEx` 函数的功能和上述函数恰好相反。目前在 MiniGUI 中，包含了 `UNICODE` 到 `ISO8859`、`GB2312`、`GBK`、`BIG5` 以及 `UTF-8` 的转换码表。

## 6 文本输出

以下函数可以用来计算逻辑字体的输出长度和高度信息（`minigui/gdi.h`）：

```c
int GUIAPI GetTextExtentPoint (HDC hdc, const char* text, int len, int max_extent, 
int* fit_chars, int* pos_chars, int* dx_chars, SIZE* size);
int GUIAPI GetTabbedTextExtentPoint (HDC hdc, const char *text, int len, int max_extent, 
int *fit_chars, int *pos_chars, int *dx_chars, SIZE *size);

// Text output support
int GUIAPI GetFontHeight (HDC hdc);
int GUIAPI GetMaxFontWidth (HDC hdc);
void GUIAPI GetTextExtent (HDC hdc, const char* spText, int len, SIZE* pSize);
void GUIAPI GetTabbedTextExtent (HDC hdc, const char* spText, int len, SIZE* pSize);
```

`GetTextExtentPoint`  函数计算在给定的输出宽度内输出多字节文本时（即输出的字符限制在一定的宽度当中），可输出的最大字符个数、每个字符所在的字节位置、每个字符的输出位置，以及实际的输出高度和宽度。`GetTextExtentPoint`  函数是个综合性的函数，它对编辑器类型的应用程序非常有用，比如 MiniGUI 的单行和多行编辑框控件中，就使用这个函数来计算插入符的位置信息。

`GetTabbedTextExtentPoint` 函数在 `GetTextExtentPoint` 函数的基础上，增加了对回车、换行和TAB键等格式化字符的处理。

`GetFontHeight` 和 `GetMaxFontWidth` 则返回逻辑字体的高度和最大字符宽度。`GetTextExtent` 计算文本的输出高度和宽度。`GetTabbedTextExtent` 函数返回格式化字符串的输出高度和宽度。

以下函数用来输出文本（`minigui/gdi.h`）：

```c
int GUIAPI TextOutLen (HDC hdc, int x, int y, const char* spText, int len);
int GUIAPI TabbedTextOutLen (HDC hdc, int x, int y, const char* spText, int len); 
int GUIAPI TabbedTextOutEx (HDC hdc, int x, int y, const char* spText, int nCount,
int nTabPositions, int *pTabPositions, int nTabOrigin);
void GUIAPI GetLastTextOutPos (HDC hdc, POINT* pt);

// Compatiblity definitions
#define TextOut(hdc, x, y, text)    TextOutLen (hdc, x, y, text, -1)
#define TabbedTextOut(hdc, x, y, text)  TabbedTextOutLen (hdc, x, y, text, -1)

# #define DrawText(hdc, text, n, rc, format)   DrawTextEx2 (hdc, text, n, rc, 0, format, NULL) 

#define DrawTextEx(hdc, text, n, rc, indent, format)   DrawTextEx2 (hdc, text, n, rc, indent, format, NULL)
...

int GUIAPI DrawTextEx2 (HDC hdc, const char *pText, int nCount, RECT *pRect, int nIndent, 
UINT nFormat, DTFIRSTLINE *firstline);

```

`TextOutLen`  函数用来在给定位置输出指定长度的字符串，若长度为 -1，则字符串必须是以 '\0' 结尾的。`TabbedTextOutLen`  函数用来输出格式化字符串。`TabbedTextOutEx` 函数用来输出格式化字符串，但可以指定字符串中每个 `TAB` 键的位置。

图 1 是 `TextOut`、`TabbedTextOut` 以及 `TabbedTextOutEx` 函数的输出效果。

![TextOut、TabbedTextOut 以及 TabbedTextOutEx 函数的输出效果](figures/Part2Chapter02-01.jpeg)

__图 1__  TextOut、TabbedTextOut 以及 TabbedTextOutEx 函数的输出效果

`DrawText` 系列函数是功能最复杂的文本输出函数，可以以不同的对齐方式在指定的矩形内部输出文本。
`DrawTextEx`  函数在 `DrawText` 函数的基础上增加了对输入文本首行缩进字符数的指定。
`DrawTextEx2`  函数在前两者的基础上，增加了对首行能显示的字符个数的计算。这在多行编辑框里面非常有用处，因为多行编辑框需要根据编辑框的宽度计算一行能显示多少字符，以便知道第二行应该从哪个字符开始显示。参数 `firstline` 就包含了第一行所能显示字符个数，并且将它显示出来了。

目前 `DrawText` 系列函数尚不支持对 `UTF-16` 编码的文本输出。表 1 给出了 `DrawText` 支持的格式。

__表 1__  `DrawText` 的输出格式

| 格式标识符 | 含义 | 备注 |
|:---------|:-----|:----|
|`DT_TOP`        |在垂直方向顶端对齐|只对单行输出有效(`DT_SINGLELINE`)|
|`DT_VCENTER`    |在垂直方向居中|同上|
|`DT_BOTTOM`     |在垂直方向底端对齐|同上|
|`DT_LEFT`       |水平方向左对齐||
|`DT_CENTER`     |水平对中||
|`DT_RIGHT`      |水平方向右对齐||
|`DT_WORDBREAK`  |当文本输出超过矩形区时按单词换行输出||
|`DT_CHARBREAK`  |当文本输出超过矩形区时按字符换行输出||
|`DT_SINGLELINE` |单行输出                   |无此标志时会忽略垂直方向的对齐标志。|
|`DT_EXPANDTABS` |扩展 `TAB` 字符||
|`DT_TABSTOP`    |格式参数的高 8 位用来指定 `TAB` 键宽度||
|`DT_NOCLIP`     |不作输出剪切。默认将把输出剪切到指定矩形||
|`DT_CALCRECT`   |不作实际输出,只计算实际的输出矩形大小||


清单 1 中的程序段，就根据要输出的字符串所描述的那样，调用 `DrawText` 函数进行对齐文本输出。该程序的完整源代码见 `MDE` 中的 `fontdemo.c` 程序。图 2 是该程序段的输出效果。

__清单 1__  `DrawText` 函数的使用

```c
void OnModeDrawText (HDC hdc)
{
        RECT rc1, rc2, rc3, rc4;
        const char* szBuff1 = "This is a good day. \n"
        "这是利用 DrawText 绘制的文本, 使用字体 GB2312 Song 12. "
        "文本垂直靠上, 水平居中";
        const char* szBuff2 = "This is a good day. \n"
        "这是利用 DrawText 绘制的文本, 使用字体 GB2312 Song 16. "
        "文本垂直靠上, 水平靠右";
        const char* szBuff3 = "单行文本垂直居中, 水平居中";
        const char* szBuff4 = 
        "这是利用 DrawTextEx 绘制的文本, 使用字体 GB2312 Song 16. "
        "首行缩进值为 32. 文本垂直靠上, 水平靠左";
        
        rc1.left = 1; rc1.top  = 1; rc1.right = 401; rc1.bottom = 101;
        rc2.left = 0; rc2.top  = 110; rc2.right = 401; rc2.bottom = 351;
        rc3.left = 0; rc3.top  = 361; rc3.right = 401; rc3.bottom = 451;
        rc4.left = 0; rc4.top  = 461; rc4.right = 401; rc4.bottom = 551;
        
        SetBkColor (hdc, COLOR_lightwhite);
        
        Rectangle (hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
        Rectangle (hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
        Rectangle (hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
        Rectangle (hdc, rc4.left, rc4.top, rc4.right, rc4.bottom);
        
        InflateRect (&rc1, -1, -1);
        InflateRect (&rc2, -1, -1);
        InflateRect (&rc3, -1, -1);
        InflateRect (&rc4, -1, -1);
        
        SelectFont (hdc, logfontgb12);
        DrawText (hdc, szBuff1, -1, &rc1, DT_NOCLIP | DT_CENTER | DT_WORDBREAK);
        
        SelectFont (hdc, logfontgb16);
        DrawText (hdc, szBuff2, -1, &rc2, DT_NOCLIP | DT_RIGHT | DT_WORDBREAK);
        
        SelectFont (hdc, logfontgb24);
        DrawText (hdc, szBuff3, -1, &rc3, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        
        SelectFont (hdc, logfontgb16);
        DrawTextEx (hdc, szBuff4, -1, &rc4, 32, DT_NOCLIP | DT_LEFT | DT_WORDBREAK);
}
```

![DrawText 函数的输出效果](figures/Part2Chapter02-02.jpeg)

__图 2__  DrawText 函数的输出效果

除上述文本输出函数之外，MiniGUI 还提供了表 2 所列出的函数，可用来设定（或查询）文本输出的字符间隔、行前间隔和行后间隔等等信息。

__表 2__  设定文本输出间隔的函数

| 函数名称 | 含义 |
|:--------|:----|
|`GetTextCharacterExtra`  |获取当前字符间距值|
|`SetTextCharacterExtra`  |设置字符间距值|
|`GetTextAboveLineExtra`  |获取行前间隔值|
|`SetTextAboveLineExtra`  |设置行前间隔值|
|`GetTextBellowLineExtra` |获取行后间隔值|
|`SetTextBellowLineExtra` |设置行后间隔值|


有关逻辑字体和文本输出函数的详细使用方法，可参阅 `MDE` 包中的 `fontdemo` 示例程序。

## 7 字体的渲染特效

MiniGUI 支持多种字体的渲染特效。比如加粗、斜体、下划线、删除线等等。和 2.0.3/1.6.9 版本一样，3.0 版本通过低通滤波算法增加了字体边缘的防锯齿效果、字型的水平和垂直镜像、以及将点阵字型自动放大从而适应逻辑字体的期望大小的功能等等。该版本通过对 `FreeType2` 的支持，使得上层应用可以在 `FreeType2` 和 MiniGUI的sub-pixels 渲染间进行自由选择；这需要在使用系统提供的 `FreeType2` 库前，确认该库的配置中已打开相应的宏开关
`FT_CONFIG_OPTION_SUBPIXEL_RENDERING`。

__清单 2__ `Sub-Pixel` 渲染的使用

```c
LOGFONT* mg_font;
mg_font = CreateLogFont (FONT_TYPE_NAME_SCALE_TTF, "times", "ISO8859-1",
FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL,
FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
15, 0);
...........
SelectFont(hdc, mg_font);
ft2SetLcdFilter (mg_font, MG_SMOOTH_NONE);
TextOut(hdc, 0,0, "text with MiniGUI sub-pixels smooth");

......
ft2SetLcdFilter (mg_font, MG_SMOOTH_DEFAULT);
TextOut(hdc, 0,0, "text with FreeType2 sub-pixels smooth");
```

字体的渲染特效一般通过逻辑字体的风格指定。比如，在创建逻辑字体时，如果指定 `FS_WEIGHT_BOOK` 风格，则将使用低通滤波算法来处理矢量字体的字型边缘，在 MiniGUI 放大点阵字体的字型时，也会采用低通滤波算法来处理字型的边缘，从而消除因为自动放大而产生的边缘锯齿。表 3 给出了 MiniGUI 支持的字体渲染特效。

__表 3__ MiniGUI 支持的字体渲染特效

| 逻辑字体风格名称 | 逻辑字体名称中的风格字符 | 对应的逻辑字体风格值 | 含义 |
|:--------------|:----------------------|:-----------------|:----|
|weight:<br>`FONT_WEIGHT_REGULAR` |第一位“r” |`FS_WEIGHT_REGULAR` |不作特殊处理|
|weight:<br>`FONT_WEIGHT_BOLD` |第一位“b”  |`FS_WEIGHT_BOLD` |加粗显示|
|weight:<br>`FONT_WEIGHT_LIGHT` |第一位“l” |`FS_WEIGHT_LIGHT` |使用背景色描绘字型的边缘,其他地方透明显示|
|weight:<br>`FONT_WEIGHT_BOOK` |第一位“b” |`FS_WEIGHT_BOOK` |采用低通滤波算法处理矢量字型边缘或者放大后的字型边缘|
|weight:<br>`FONT_WEIGHT_DEMIBOLD` |第一位“d” |`FS_WEIGHT_DEMIBOLD` |加粗的同时,采用低通滤波算法处理矢量字型边缘或者放大后的字型边缘 |           
|weight:<br>`FONT_WEIGHT_SUBPIXEL` |第一位“s” |`FS_WEIGHT_SUBPIXEL` |采用 `sub-pixel` 技术渲染字型|
|slant:<br>`FONT_SLANT_ROMAN` |第二位“r” |`FONT_SLANT_ROMAN` |不作特殊处理|
|slant:<br>`FONT_SLANT_ITALIC` |第二位“i” |`FONT_SLANT_ITALIC` |斜体显示字型|
|flip:<br>`FONT_OTHER_NIL` |第 三 位 是 除 H/V/T 之外的其他任意字符 |N/A |不作任何处理|
|flip:<br>`FONT_FLIP_HORZ` |第三位“H” |`FS_FLIP_HORZ` |将字型水平翻转显示|
|flip:<br>`FONT_FLIP_VERT` |第三位“V” |`FS_FLIP_VERT` |将字型垂直翻转显示|
|flip:<br>`FONT_FLIP_HORZVERT` |第三位“T” |`FS_FLIP_HORZVERT` |将字型同时做水平和垂直翻转后显示|
|other:<br>`FONT_OTHER_NIL` |第四位是除 S/N 之外的其他任意字符 |N/A |不作任何处理|
|other:<br>`FONT_OTHER_AUTOSCALE` |第四位“S” |`FS_OTHER_AUTOSCALE` |根据逻辑字体期望的大小自动放大显示设备字体字型,仅适用于点阵字体|
|other:<br>`FONT_OTHER_TTFNOCACHE` |第四位“N” |`FS_OTHER_TTFNOCACHE` |在 使 用 `TrueType` 字体渲染该逻辑时,关闭缓存|
|other: <br>`FONT_OTHER_LCDPORTRAIT` |第四位“P” |`FS_OTHER_LCDPORTRAIT` |在 使 用 `TrueType` 字 体渲 染 该 逻 辑 时 , `LCD` 为 `PORTRAIT` 模式|
|underline: <br>`FONT_UNDERLINE_NONE` |第五位“n” |`FS_UNDERLINE_NONE` |无下划线线|
|underline:<br>`FONT_UNDERLINE_LINE` |第五位“u” |`FS_UNDERLINE_LINE` |添加下划线 |             
|struckout:<br>`FONT_STRUCKOUT_NONE` |第六位“n” |`FS_STRUCKOUT_NONE` |无删除线|
|struckout:<br>`FONT_STRUCKOUT_LINE` |第六位“s” |`FS_STRUCKOUT_LINE` |添加删除线|

表 3 中给出的风格字符可以在定义逻辑字体的名称时使用。

## 8 `BIDI` 文本的使用

一般情况下，`Latin` 等文本都是以左到右的顺序存储以及显示，但也有部分中亚国家(如阿拉伯文)语言是从右到左进行显示的，当这些文本混合在一起时，就形成了复杂的双向文本显示问题.

支持双向文本显示，只需要打开相关的字符集支持，配置其字体就可以了下面以阿拉伯字体举例。

- 首先打开 `ISO8859-6` 字符集支持，MiniGUI 是默认支持阿拉伯字体的.
- 然后在 MiniGUI 配置文件中配置 `vbf` 字体。

```c
[varbitmapfonts]
font_number=1
name0=vbf-naskhi-rrncnn-18-21-ISO8859-6
fontfile0=/usr/local/share/minigui/res/font/naskhi-18-21-iso8859-6.vbf
```

下面是阿拉伯文的演示：

![阿拉伯字体演示](figures/Part2Chapter02-03.jpeg)

__图 3__  阿拉伯字体演示
