# 使用 mGPlus

mGPlus 组件是对 MiniGUI 3.0 图形绘制接口的一个扩充和增强，主要提供对二维矢量图形和高级图形算法的支持，如路径、渐变填充和颜色组合等。mGPlus 用来实现 MiniGUI 3.0 中的 Fashion 外观渲染器，也用于 mDolphin 浏览器实现高级的图形功能，如 HTML 5 中的 Canvas 标记、SVG 支持等。

mGPlus 的功能：

- 支持 ALPHA、GAMMA 等变色处理，以及用户自定义的变色处理；
- 支持任意 2D 图形变换；
- 支持 SVG 和 PostScript 描述，适于网上图形生成；
- 支持高质量的图形处理，支持反走样插值等高级功能；
- 支持任意方式的惭变色处理；
- 支持所有颜色格式；
- 支持对位图的多种处理；
- 支持直线的多种处理，类似于 GDI+；
- 支持 GPC，即通用多边形裁剪方法；
- 支持多种字体输出，包括汉字的处理；
  
mGPlus 的最新版本为 1.2.0。C 程序在使用 mGPlus组件中的接口之前，应包含 <mgplus/mgplus.h> 头文件，并链接 libmgplus 库（在使用 GCC 工具链时，传入 -lmgplus 参数。） 


##  1 mGPlus 基本概念介绍
### 1.1 画笔的介绍

画笔是用于绘制线条、曲线以及勾勒形状轮廓，是基于点绘机制。画笔除了具有常见的色彩和宽度属性外,还具有对齐方式,线帽,变换方式等属性。

### 1.2 画刷的介绍

画刷是基于填充机制，用于与 Graphics 对象一起创建实心形状和呈现文本的对象。 

### 1.3 路径的介绍
#### 1.3.1 路径的定义

路径由一组有严格的顺序折线和曲线组成。其顺序很重要。路径有两种规则缠绕规则，根据规则，可以判断一个点是在路径内还是在路近外（路径不一定是闭合的).

#### 1.3.2 缠绕规则:

- 奇偶规则(Even-Odd): 从一点向右做射线，如果射线路径有奇数个交点，则该点在路径内，否则，该点不再路径内
- 非零规则(None-Zero): 从一点向右做射线，如果路径从"上"穿过射线的次数不等于从“下”穿过路径的次数，那么该点在路径内，否则，该店不再路径内。

![path](figures/path.jpeg) 

1. 奇偶规则：点 A, D, F 在路径内，而点 B,C,E,G 则不在路径内
2. 非零规则: 注意路径穿过射线的方向，点 A 有两次被从上穿过，故而点 A 在路径内。同理，点 D,F 也在路径内，而点 B,C,E,G 不在路径内。

#### 1.3.3  用扫描方法填充路径

形成路径的线段可以是折线也可以是曲线。为了方便实现路径填充算法，需要将曲线离散为折线进行处理. 下面，就重点讨论一下，全部是折线的路径填充的实现。

在填充的时候，可能存在不止一条的路径，可能是多条路径形成的区域。因此，所有路径都必须保持同样的缠绕规则，否则，就无法在不同路径之间做比较，判断一个点是否在路径内。

#### 1.3.4 路径的使用

- 路径使用方法。使用路径可以进行路径绘制、路径填充以及路径剪切。
   - 路径绘制就是把路径内所有的子路径曲线离散化为顶点，然后把所有顶点连线，便绘出了路径。
   - 路径填充就是把路径离散化，变成一个多边形，然后填充该多边形。
   - 路径剪切与路径填充相似，只是把生成的扫描线组成一个区域。
- 对路径的操作：新建路径、销毁路径、复制路径、闭合路径、向路径添加直线、向路径添加曲线等。

### 1.4 渐变填充

渐变填充是指使用一个颜色线性渐变或者按某个路径渐变的画刷，在某个指定区域，或者路径区域内，或者图形进行填充。有了渐变填充，我们就可以实现更加漂亮的更有立体感的控件了，这后续会有详细介绍。目前 mGPlus 实现的渐变方式有弧形渐变填充和线性渐变填充。

### 1.5 颜色组合

在当今非常重视产品包装的年代里，每一个应用开发者都希望能够开发出非常漂亮精致的用户界面，以获得用户的第一好感。颜色组合可谓是这方面的利器，它能够实现图片之间千变万化的组合，让你的界面获得意想不到的效果。mGPlus 实现了十二种组合模式。

## 2 体系架构介绍
### 2.1 `MGPlus` 架构
####  2.1.1 `MGPlusGraphics` 概述

- `MiniGUI` 可以通过两种方式来使用 `MGPlus`：
   - 首先创建好一个内存 `DC`，直接把 `DC` 提供给 `MGPlus`，`MGPlus` 直接在该 `DC` 上进行渲染。
   - 直接使用 `MGPlus`，完全由 `MGPlus` 自己来渲染，最后通过接口函数来获取渲染好的 `DC`。
- `MGPlus` 在内部提供一个核心的数据结构 `MGPlusGraphics`，该结构包含了图形所有的数据，包括路径、渐变、变化矩阵等渲染所需的信息。该数据结构是不对外公开的，对外只公开一个句柄（指针）。
- 围绕 `MGPlusGraphics` 结构，将提供一系列的函数接口来操作，包括初始化、参数修改、各种方式的渲染，以及各种 2D 坐标变化（比如线性变化）。
- `MGPlus` 包括以下模块：
   - 画笔（pen）
   - 画刷（brush）
   - 路径（path）
   - 转换矩阵（matrix）
   - 图片（image）
   - 字体（font）
   - 文本（text）
- 在底层，将使用 AGG 的数据和接口来实现。

#### `MGPlus` 框架图

- `MGPlus` 主要由以上 9 个大类组成，Graphic 类实现绘制相关的一切操作，包括颜色渐变，颜色组合，抗锯齿等，其他 8 个大类与 Graphic 是单向关联；
- Matrix 类与 Path 类，Image 类与 Bitmap 类，Font 类与Text 类是单向关联。

- mgplus rebuild framework:


![mgplus_framework](figures/mgplus_framework.jpeg)

## 3 API 应用
### 3.1 `Graphics`
#### 3.1.1 `Graphics`管理功能

`Graphics` 的管理功能包括创建、删除和复制的功能，详细说明如下：

__创建__

创建有两种方式。一种是直接传入 `HDC` 来创建 `MGPlusGraphics` 数据结构，调用函数 `MGPlusGraphicCreateFromDC` 即可，成功返回 `HGRAPHICS` ，一个 `MGPlusGraphics` 创建成功了。

```c
MG_EXPORT HGRAPHICS MGPlusGraphicCreateFromDC(HDC hdc);
```

另一种方式是使用 不同的像素格式来创建一个 `MGPlusGraphics` 数据结构，用 width 和 height 的初始用来指定 canvas 的大小，调用 `MGPlusGraphicCreate` 函数。需要注意的是，渲染的结果需要用户调用接口函数 `MGPlusGraphicSave` 来获取。

```c
MG_EXPORT HGRAPHICS MGPlusGraphicCreate(int width, int height);
MG_EXPORT MPStatus MGPlusGraphicSave(HGRAPHICS graphics, HDC hdc, int sx, int sy, int sw, int sh, int dx, int dy);
```

另外新增了一种创建方式。该方式为了实现直接绘制 `DC` 来创建 `MGPlusGraphics`，将直接传入的 `DC` 作为画布来操作。

```c
HGRAPHICS MGPlusGraphicCreateWithoutCanvas (HDC hdc);
```

__删除__

当不需要 `MGPlusGraphics` 时，需要释放 `MGPlusGraphics` 数据结构，通过调用 `MGPlusGraphicDelete` 函数就可以了。

```c
MPStatus MGPlusGraphicDelete (HGRAPHICS graphics);
```
  
另外有种可清除 `MGPlusGraphic` 的颜色，类似清屏，此函数是 `MGPlusGraphicClear`。一般情况下，创建 `MGPlusGraphic` 的时候，会把相关 dc 的内容也 copy 过去的。因而在使用 `MGPlusGraphicCopyFromDC` 前需要调用此函数来清理一下。用法如下：

```c
            MGPlusGraphicClear (graphics, 0);
            hdc = GetClientDC (hWnd);
            FillBox (hdc, 0, 0, 1024, 768);
            MGPlusGraphicCopyFromDC (graphics, hdc, 0, 0, 0, 0, 0, 0);
            ReleaseDC (hdc);
```

__复制__

```c
MPStatus MGPlusGraphicCopy (HGRAPHICS src_gs, HGRAPHICS dst_gs);
```

#### 3.1.2 `Graphics` 颜色组合

`mGPlus` 实现一些基本的 alpha 合成规则，将源色与目标色组合，在图形和图像中实现混合和透明效果。

实现时注意的事项：

- 许多源图像，比如一些不透明图像，没有为它们的像素存储 alpha 值。这类源图像为它们所有的像素提供了值为 1.0 的 alpha 值。

- 许多目标也没有地方存储 alpha 值（这些值是混合计算的结果）。这类目标会隐式丢弃此类产生的 alpha 值。建议这类目标将它们存储的颜色值作为未预乘的值对待，并在存储颜色值和丢弃 alpha 值之前，将得到的颜色值除以得到的 alpha 值。

- 结果的精度取决于将像素存储到目标中的方式。对于一连串十二种合成操作中的少数操作，将为每种颜色和 alpha 分量提供至少 8 个存储位的图像格式作为目标无论如何都应该足够了。在舍入误差主宰结果之前，为每个分量提供少于 8 个存储位的图像格式仅限用于一或两个合成操作。对于任何半透明混合的类型而言，不单独存储颜色分量的图像格式不是一个好的候选方式。例如，不应将需要从限定的调色板选择像素，以匹配混合方程，这样每个操作都可能引入大量错误。

- 几乎所有的格式都将像素存储为离散整数，而不是将它们存储为上述方程中使用的浮点值。该实现可以将整数像素值缩放成范围在 0.0 到 1.0 之间的浮点值，或者使用稍作修改的方程，完全在整数域内操作，从而生成与上述方程类似的结果。

- 内部实现可能近似于某些方程，它们也可以消除一些步骤，以避免不必要的操作。
    
- 因为那些通过简化方程使计算更有效的技术，在非预乘的目标上遇到值为 0.0 的结果 alpha 值时，一些实现的执行可能会有所不同。注意，如果分母 (alpha) 为 0，则在 SRC 规则下移除除以 alpha 这一简化操作技术上是不合法的。但是，因为在以预乘形式查看时只期望结果是精确的，所以，结果为 0 的 alpha 值呈现的实质上是所得到的不相关的颜色分量，因此，在这种情况下，具体的行为应该是无法预料的。 

用户如果需要颜色组合，需要创建两个 `MGPlusGraphics`，最后才能将他们的颜色进行混合，得到我们想要的颜色组合的效果。

`MGPlusGraphics` 的颜色组合共有 12 种组合模式，分别是：

```c
        MP_COMP_OP_CLEAR = 0, //目标色和目标 alpha 值都被清除（Porter-Duff Clear 规则）。源色和目标色都不被用作输入
        MP_COMP_OP_SRC,   //将源色复制到目标色（Porter-Duff Source 规则）。目标色不被用作输入
        MP_COMP_OP_DST,  //未涉及到目标色（Porter-Duff Destination 规则）
        MP_COMP_OP_SRC_OVER, //在目标色之上合成源色（Porter-Duff Source Over Destination 规则）
        MP_COMP_OP_DST_OVER,  //在源色之上合成目标色，产生的结果将替代目标色（Porter-Duff Destination Over Source 规则）
        MP_COMP_OP_SRC_IN, //目标色中的源色部分将替换目标色（Porter-Duff Source In Destination 规则）
        MP_COMP_OP_DST_IN, //源色中的目标色部分将替换目标色（Porter-Duff Destination In Source 规则）
        MP_COMP_OP_SRC_OUT,  //目标色以外的源色部分将替换目标色（Porter-Duff Source Held Out By Destination 规则）
        MP_COMP_OP_DST_OUT,  //源色以外的目标色部分将替换目标色（Porter-Duff Destination Held Out By Source 规则）
        MP_COMP_OP_SRC_ATOP, //目标色中的源色部分将被合成到目标色中（Porter-Duff Source Atop Destination 规则）
        MP_COMP_OP_DST_ATOP, //在源色之上合成源色中的目标色部分，并且将替换目标色（Porter-Duff Destination Atop Source 规则）
        MP_COMP_OP_XOR, //将目标色之外的源色部分与源色之外的目标色部分结合到一起（Porter-Duff Source Xor Destination 规则）
```

用户可依据需要设置颜色组合模式，将需要的模式传入函数 `MGPlusSetCompositingMode` 的参数 `compositingMode` 中即可。

```c
MPStatus MGPlusSetCompositingMode( HGRAPHICS graphics, CompositingMode compositingMode);
```

如果用户想要获得当前的颜色组合模式，直接调用函数 `MGPlusGetCompositingMode` 获取 `MGPlusGraphics` 组合模式。获取的组合模式存放在 `compositingMode` 指向的地址中。 

```c
MPStatus MGPlusGetCompositingMode(HGRAPHICS graphics, CompositingMode *compositingMode);
```

注意：目前颜色组合虽然支持 32 位色、24 位色、16 位色，但在 24 位 和 16 位色深情况下，只支持简单的颜色组合，即 src-over 模式。 

除了图形的颜色组合外，还可以添加图片参与颜色组合。用户想要添加图片，首先要调用函数 `MGPlusGraphicLoadBitmapFromFile` 来加载图片，然后调用函数 `MGPlusDrawImage` 将图片绘制在 `MGPlusGraphics` 中。

```c
MPStatus MGPlusGraphicLoadBitmapFromFile (HGRAPHICS graphics, int n_index, char* file);
```
注：n_index 为加载图片的素引值；file 为加载图片的路径。

```c
MPStatus MGPlusDrawImage (HGRAPHICS graphics, int n_index,int x, int y, int w, int h);
```
注：`n_index` 为加载图片的素引值；x,y 为图片的起始位置；w,h 为图片的大小，如果w和h为-1,则表示图片将以原始大小被绘制出来。

关于加载图片的方式，另外有种方式。在程序的初始化中调用MiniGUI中的函数 LoadBitmap（ 具体的用法请参考MiniGUI 的API手册），然后调用MGPlusGraphicLoadBitmap 和 MGPlusDrawImage 将图片绘制在 MGPlusGraphics中，最后记得在程序结束时调用MiniGUI中 UnloadBitmap函数释放内存空间。

```c
MPStatus MGPlusGraphicLoadBitmap (HGRAPHICS graphics,  int n_index, PBITMAP p_bitmap);
```
注：n_index为加载图片的素引值；p_bitmap为存放图片的地址。

在完成相应的工作后，一定要调用函数 MGPlusGraphicBlend ,否则颜色组合的效果是看不见的。

```c
MPStatus MGPlusGraphicBlend (HGRAPHICS src_gs, HGRAPHICS dst_gs);
```

具体如何才能进行颜色组合，请参照颜色组合的示例：

```c
#define COMP_CLEAR      310
#define COMP_SRC        311
#define COMP_DST        312
#define COMP_SRC_OVER   313
#define COMP_DST_OVER   314
#define COMP_SRC_IN     315
#define COMP_DST_IN     316
#define COMP_SRC_OUT    317
#define COMP_DST_OUT    318
#define COMP_SRC_ATOP   319
#define COMP_DST_ATOP   320
#define COMP_XOR        321


static BITMAP bmp_butterfly;
static int comp_mode = MP_COMP_OP_SRC_OVER;

static void GetCompMode(HWND hWnd, WPARAM wParam)
{

    switch (wParam) {
        case COMP_CLEAR:
            comp_mode = MP_COMP_OP_CLEAR;
            break;
        case COMP_SRC:
            comp_mode = MP_COMP_OP_SRC;
            break;
        case COMP_DST:
            comp_mode = MP_COMP_OP_DST;
            break;
        case COMP_SRC_OVER:
            comp_mode = MP_COMP_OP_SRC_OVER;
            break;
        case COMP_DST_OVER:
            comp_mode = MP_COMP_OP_DST_OVER;
            break;
        case COMP_SRC_IN:
            comp_mode = MP_COMP_OP_SRC_IN;
            break;
        case COMP_DST_IN:
            comp_mode = MP_COMP_OP_DST_IN;
            break;
        case COMP_SRC_OUT:
            comp_mode = MP_COMP_OP_SRC_OUT;
            break;
        case COMP_DST_OUT:
            comp_mode = MP_COMP_OP_DST_OUT;
            break;
        case COMP_SRC_ATOP: 
            comp_mode = MP_COMP_OP_SRC_ATOP;
            break;
        case COMP_DST_ATOP:
            comp_mode = MP_COMP_OP_DST_ATOP;
            break;
        case COMP_XOR: 
            comp_mode = MP_COMP_OP_XOR;
            break;
        default:
            return;
    }

}

#define C_POS 600
#define C_W   170

static CTRLDATA CtrlYourTaste[] =
{ 
    {
        "static",
        WS_VISIBLE | SS_GROUPBOX, 
        16+C_POS, 0, 200, 160+200,
        IDC_STATIC,
        "Composite_Mode",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON | WS_TABSTOP | WS_GROUP,
        36+C_POS, 38, C_W, 20,
        COMP_CLEAR,
        "Composite_Clear",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 64, C_W, 20,
        COMP_SRC,
        "Composite_Source",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON, 
        36+C_POS, 90, C_W, 20, 
        COMP_DST, 
        "Composite_Dst",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON| BS_CHECKED ,
        36+C_POS, 116, C_W, 20,
        COMP_SRC_OVER,
        "Composite_SourceOver",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142, C_W, 20,
        COMP_DST_OVER,
        "Composite_DstOver",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+1*26, C_W, 20,
        COMP_SRC_IN,
        "Composite_SourceIn",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+2*26, C_W, 20,
        COMP_DST_IN,
        "Composite_DstIn",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON, 
        36+C_POS, 142+3*26, C_W, 20, 
        COMP_SRC_OUT, 
        "Composite_SourceOut",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+4*26, C_W, 20,
        COMP_DST_OUT,
        "Composite_DstOut",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+5*26, C_W, 20,
        COMP_SRC_ATOP,
        "Composite_SourceAtop",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+6*26, C_W, 20,
        COMP_DST_ATOP,
        "Composite_DestAtop",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36+C_POS, 142+7*26, C_W, 20,
        COMP_XOR,
        "Composite_Xor",
        0
    },

};

static DLGTEMPLATE DlgYourTaste =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_AUTOSECONDARYDC,
    0, 0, 370+420, 300+290,
    "CompositeDemo(press F1,F2,F3...)",
    0, 0,
    TABLESIZE(CtrlYourTaste),
    NULL,
    0
};

void CompositeDrawBmpBlend(HWND hDlg)
{
    RECT rect = {20, 20, 200, 200};
   
    HBRUSH hbrush = 0;
    HGRAPHICS hgs_comp;
    HGRAPHICS hgs;
    RECT cl_rc = {0};

 HDC  hdc = BeginPaint(hDlg);

// 创建路径的模式
    HPATH  hpath = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

    /* first Clear the output_area that have draw last time.*/
    GetClientRect(hDlg, &cl_rc);
    FillBox (hdc, 0, 0, RECTW(cl_rc), RECTH(cl_rc)); 

//创建两个MGPlusGraphics
    hgs_comp = MGPlusGraphicCreateFromDC(hdc);
    hgs = MGPlusGraphicCreateFromDC(hdc);

//创建画刷
    hbrush = MGPlusBrushCreate(MP_BRUSH_TYPE_SOLIDCOLOR); 
  
//添加一个圆路径
    MGPlusPathAddArc (hpath, rect.left+RECTW(rect)/2, 
            rect.top+RECTH(rect)/2, RECTW(rect)/2, RECTH(rect)/2, 0, 360);

//清除两个MGPlusGraphics中其他颜色
    MGPlusGraphicClear(hgs_comp, 0x00000000);
    MGPlusGraphicClear(hgs, 0x00ffffff);

//加载并绘制图片
    MGPlusGraphicLoadBitmapFromFile  (hgs_comp, 1, "res/butterfly.png");
    MGPlusDrawImage(hgs_comp, 1, 220, 35, -1, -1);

//设置画笔的颜色    
    MGPlusSetSolidBrushColor (hbrush, 0xDF6FF0FD);

//设置图片与图形组合的模式
    MGPlusSetCompositingMode (hgs_comp, (MPCompositingMode)MP_COMP_OP_SRC);

//填充路径
    MGPlusFillPath(hgs_comp, hbrush, hpath); 

//重设路径
    MGPlusPathReset(hpath);

//添加新的的图形
    OffsetRect(&rect, 80, 0);
    MGPlusPathAddRoundRect(hpath, rect.left, rect.top, RECTW(rect), RECTH(rect), 50);

//设置画笔的颜色
    MGPlusSetSolidBrushColor (hbrush, 0xBFFFC17F);

//设置图形颜色组合的模式   
    MGPlusSetCompositingMode (hgs_comp, (MPCompositingMode)comp_mode);
 
   MGPlusFillPath(hgs_comp, hbrush, hpath); 

//混合两个MGPlusGraphics
   MGPlusGraphicBlend(hgs_comp, hgs);

//保存MGPlusGraphics
    if (MGPlusGraphicSave(hgs, hdc, 0, 0, 0, 0, 0, 0) != MP_OK)
        printf("save graphic failed!\n");

//释放内存空间
    MGPlusPathDelete (hpath);
    MGPlusBrushDelete (hbrush)
    MGPlusGraphicDelete(hgs_comp);
    MGPlusGraphicDelete(hgs);
    EndPaint(hDlg, hdc);

}

static int DialogBoxProc2 (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
  
    switch (message) {
        case MSG_INITDIALOG:
            SetWindowBkColor(hDlg, COLOR_lightwhite);
            return 1;
        
        case MSG_COMMAND:
            GetCompMode(hDlg, wParam);
            if(wParam >= COMP_CLEAR && wParam <= COMP_XOR) {
                RECT rc = {0, 0, 400, 300};
                InvalidateRect(hDlg, &rc, FALSE);
            }
            break;

        case MSG_PAINT:
                CompositeDrawBmpBlend(hDlg);
            return 0;

        case MSG_CLOSE:
              EndDialog(hDlg, 0);
            break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "composite" , 0 , 0);
#endif
    
    if (LoadBitmap (HDC_SCREEN, &bmp_butterfly, "res/butterfly.png"))
        return 1;

    DlgYourTaste.controls = CtrlYourTaste;
    
    DialogBoxIndirectParam (&DlgYourTaste, HWND_DESKTOP, DialogBoxProc2, 0L);

    UnloadBitmap (&bmp_butterfly);

    return 0;
}

#ifndef _MGRM_PROCESSES
#include <minigui/dti.c>
#endif

```

<center><img src="%ATTACHURLPATH%/composite.png" alt="composite.png"  ALIGN="CENTER" /> </center>
<center>颜色组合</center>

#### 3.1.3 Graphics绘制模式

Graphics绘制模式是对抗锯齿的控制，包括画刷的光滑模式、路径抗锯齿和文本抗锯齿。

__画刷的光滑模式__
   画刷的光滑模式有两种，分别为：

```c
        /* Smoothing mode with speed.*/
        MP_SMOOTHING_SPEED = 0,
        /* Smoothing mode with quality.*/
        MP_SMOOTHING_QUALITY = 1,
```

用户想要设置画刷的绘制模式，可使用MGPlusSetSmoothingMode函数，具体用法如下示例：
```c
 HPEN pen = MGPlusPenCreate (2, 0xFF505050);
 MGPlusSetSmoothingMode (hgraphics, MP_SMOOTHING_QUALITY);
 MGPlusDrawEllipse (hgraphics, pen, 0, 0, 200, 100);
```

想要获得当前画刷的绘制模式，调用 MGPlusGetSmoothingMode函数， 绘制模式的值存入 value的地址中。
```c
MPStatus MGPlusGetSmoothingMode (HGRAPHICS graphics, MPSmoothingMode* value);
```

__路径抗锯齿__

路径抗锯齿是通过MP_PATH_RENDER_HINT_ANTIALIAS_ON和MP_PATH_RENDER_HINT_ANTIALIAS_OFF来控制抗锯齿。
```c
        MP_PATH_RENDER_HINT_ANTIALIAS_ON   = 0,
        MP_PATH_RENDER_HINT_ANTIALIAS_OFF  = 1,
```

用户想要设置路径抗锯齿绘制模式，可使用MGPlusSetPathRenderingHint函数，具体用法如下示例：
```c
 HPEN pen = MGPlusPenCreate (2, 0xFF505050);
 MGPlusSetPathRenderingHint (hgraphics, MP_PATH_RENDER_HINT_ANTIALIAS_ON);
 MGPlusDrawEllipse (hgraphics, pen, 0, 0, 200, 100);
```

想要获得当前路径抗锯齿的绘制模式，调用 MGPlusGetPathRenderingHint函数， 绘制模式的值存入 value的地址中。
```c
MPStatus MGPlusGetTextRenderingHint (HGRAPHICS graphics,MPTextRenderingHint* value);
```

添加路径抗锯齿前的效果
<center> <img src="%ATTACHURLPATH%/path1.png" alt="path1.png"  ALIGN="CENTER" /> </center>
<center>添加路径抗锯齿前的效果</center>

添加路径抗锯齿后的效果
<center> <img src="%ATTACHURLPATH%/path2.png" alt="path2.png"  ALIGN="CENTER" /> </center>
<center>添加路径抗锯齿后的效果</center>

__文本抗锯齿__
文本抗锯齿是通过MP_TEXT_RENDER_HINT_ANTIALIAS_ON和MP_TEXT_RENDER_HINT_ANTIALIAS_OFF来控制抗锯齿。
```c
      MP_TEXT_RENDER_HINT_ANTIALIAS_ON   = 0,
      MP_TEXT_RENDER_HINT_ANTIALIAS_OFF  = 1,
```

用户想要设置文本抗锯齿绘制模式，可使用MGPlusSetTextRenderingHint函数，具体用法如下示例：
```c
 static  GLYPHMETRICS   metrics;
 char* test_text = "~!@#$%^&*(_)QWERTYUIOASDFGHJKL:ZXCVBNM<ertfgyubhnjgi>.";
 char text[512] = {0};
 GLYPHDATA data_size={0};

 HFONT  hfont = MGPlusCreateFont("timesi.ttf", 0,  MP_GLYPH_REN_OUTLINE,60,60,true);

    strcpy (text, ren_str[2]);
    strcat (text, test_text);
   MGPlusSetTextRenderingHint (hgraphics, MP_TEXT_RENDER_HINT_ANTIALIAS_ON);
  
   for (i = 0; i < strlen(text); i++) 
   {
	 MGPlusGetGlyphOutline(hfont,text[i],&metrics,&data_size);    
         MGPlusDrawGlyph (hgraphics, hfont, x, y,  &data_size, 0xff908070);
     
        x += metrics.adv_x;
        y += metrics.adv_y;
    }
```

想要获得当前文本抗锯齿的绘制模式，调用函数MGPlusGetTextRenderingHint， 绘制模式的值存入 value的地址中。
```c
MPStatus MGPlusGetTextRenderingHint (HGRAPHICS graphics,MPTextRenderingHint* value);
```

添加文本抗锯齿前的效果
<center> <img src="%ATTACHURLPATH%/text2.png" alt="text2.png"  ALIGN="CENTER" /> </center>
<center>添加文本抗锯齿前的效果</center>

添加文本抗锯齿后的效果
<center> <img src="%ATTACHURLPATH%/text1.png" alt="text1.png"  ALIGN="CENTER" /> </center>
<center>添加文本抗锯齿后的效果</center>

#### 3.1.4 世界坐标系转换

世界坐标系的转换是对MGPlusGraphics坐标位置的转换（平移、缩放、旋转）,mgplus还有一种路径转换，是对图形坐标位置的转换（平移、缩放、旋转）。

__设置__
用户需要设置世界坐标系可调用MGPlusSetWorldTransform 函数 。

```c
MPStatus MGPlusSetWorldTransform(HGRAPHICS graphics, MGPlusMatrix *matrix);
```

其中参数matrix的定义如下：
```c
/*
*[ sx,   shy,  0 ]
*| shx, sy  ,  0 |
*[ tx,    ty   ,  0 ]
*/
struct MgPlusMatrix
{   
        double sx, shy, shx, sy, tx, ty;;  //transformation matrix
};
```

重设函数为MGPlusResetWorldTransform。
```c
MGPlus MGPlusResetWorldTransform(HGRAPHICS graphics);
```

__平移__
用户如果想平移，需要注意的是：最开始的世界坐标是(0, 0),如果想图形绕(100, 100)点旋转的话，先平移坐标到(100, 100),也就是使用MGPlusTranslateWorldTransform (graphics，-100, -100),然后再使用Roatate旋转，最后使用MGPlusTranslateWorldTransform (graphics，100, 100),平移坐标回来。

```c
MPStatus MGPlusTranslateWorldTransform (HGRAPHICS graphics, float dx, float dy);
```

__缩放__
调用函数 MGPlusScaleWorldTransform ，用户可对MGPlusGraphics进行缩放。

```c
MGPlus MGPlusScaleWorldTransform(HGRAPHICS graphics, float sx, float sy);
```

__旋转__
调用函数MGPlusRotateWorldTransform，用户可对MGPlusGraphics进行旋转。

```c
MPStatus MGPlusRotateWorldTransform(HGRAPHICS graphics, float angle);
```

具体的用法可参考下面世界坐标系的转换的示例：

```c
......

static ARGB b [3] = {0xFFFF0000, 0xFF00FF00, 0xFFFF00FF};
static MPPOINT zeropoint = {70,105};
static RECT zerorect = {50,50,200,200};
HWND hWnd;
HDC hdc;
......

   HGRAPHICS hGraphics;
    HPATH hPath;
    HBRUSH hBrush;
......

    hdc = BeginPaint(hWnd);

   //创建graphics、路径和画刷
    hGraphics = MGPlusGraphicCreateFromDC(hdc); 
    hPath = MGPlusPathCreate(0);
    hBrush = MGPlusBrushCreate(MP_BRUSH_TYPE_PATHGRADIENT);

    //设置画刷
    MGPlusSetPathGradientBrushCenterPoint (hBrush, &zeropoint);
    MGPlusSetPathGradientBrushCenterColor (hBrush, 0xFF0000FF);
    MGPlusSetPathGradientBrushSurroundColors (hBrush,b,3);
    MGPlusSetPathGradientBrushSurroundRect (hBrush, &zerorect);

   //绘制图形并填充
    MGPlusPathAddRectangle(hPath, 100, 100, 100, 100);
    MGPlusFillPath (hGraphics, hBrush, hPath);
   
    //世界坐标系的转换（平移、缩放和旋转）
    MGPlusTranslateWorldTransform (hGraphics, -100, -100);
    MGPlusScaleWorldTransform(hGraphics, 2, 1);
    MGPlusRotateWorldTransform (hGraphics, 70);
    MGPlusTranslateWorldTransform (hGraphics, 100, 100);

   //重新填充转换后的图形 
    MGPlusFillPath (hGraphics, hBrush, hPath);
  
  //保存graphics  
  MGPlusGraphicSave (hGraphics, hdc, 0, 0, 0, 0, 0, 0);

    
   //释放内存空间
    MGPlusBrushDelete(hBrush);
    MGPlusPathDelete(hPath);
    MGPlusGraphicDelete(hGraphics);
    EndPaint(hWnd,hdc);
  ......

```

<center>     <img src="%ATTACHURLPATH%/worldtransform.png" alt="worldtransform.png"  ALIGN="CENTER" /> </center>
<center>世界坐标系的转换</center>

视图说明：底层的为原始图形，上层的为x轴放大两倍的，旋转了70度的转换的图形。

#### 3.1.5 字体渲染

目前mgplus只支持矢量字体的渲染，因此如果需要字体渲染的功能的话，首先需要在编译mgplus时打开--enable-ft2support 选项用来支持freetype2矢量字体,同时需要客户在编译应用程序的时候加上freetype的库。

用户想要绘制字体，首先用MGPlusCreateFont函数创建字体。
```c
HFONT MGPlusCreateFont (const char* font_name, unsigned face_index, MPGlyphRendering ren_type,
unsigned int width, unsigned int height, BOOL flip_y)
```


对字体渲染有6种模式，具体如下：
```c
        /* retrieves the glyph bitmap direct from ft2. */
        MP_GLYPH_REN_NATIVE_MONO,
        MP_GLYPH_REN_NATIVE_GRAY8,
        /* retrieves the curve data points in the rasterizer's native
     - format and uses the font's design units. 
     -/
        MP_GLYPH_REN_OUTLINE,
        /* retrieves the glyph bitmap from agg render. */
        MP_GLYPH_REN_AGG_MONO,
        MP_GLYPH_REN_AGG_GRAY8,
        /* only retrieves the GLYPHMETRICS structure specified by lpgm.*/
        MP_GLYPH_REN_METRICS,
```


创建字体后，要通过函数MGPlusGetGlyphOutline获取字体的轮廓数据。
```c
 MPStatus MGPlusGetGlyphOutline (HFONT hfont, unsigned uchar,LPGLYPHMETRICS lpgm, LPGLYPHDATA lpdata);
```
参数lpdata是存放字体轮廓的数据。

该函数的LPGLYPHMETRICS lpgm参数包括字体轮廓的位置和方向以及大小，具体的定义如下：
```c
typedef struct _GLYPHMETRICS {
        /* Specifies the x- and y-coordinates of the upper left 
     - corner of the smallest rectangle that completely encloses the glyph.   
     -/
        unsigned char bbox_x;
        unsigned char bbox_y;
        /* Specifies the width or height of the smallest rectangle that 
     - completely encloses the glyph (its box).  
     -/
        unsigned char bbox_w;
        unsigned char bbox_h;
        /* Specifies the horizontal/vertical distance from the origin of the current 
     - character cell to the origin of the next character cell. 
     -/
        short adv_x;
        short adv_y;
} GLYPHMETRICS, *LPGLYPHMETRICS;
```

然后就可以根据字体的轮廓数据来绘制字体，或者获取字体的路径结构对字体做旋转操作。用到的函数如下：
```c
 MPStatus MGPlusDrawGlyph (HGRAPHICS graphics, HFONT hfont,int x, int y, LPGLYPHDATA lpdata, ARGB color);
```
注：x、y指的是绘制字体的起始坐标；lpdata是存放字体轮廓的数据；color指的是字体的绘制颜色。

```c
 HPATH MGPlusGetGlyphPath (int x, int y, LPGLYPHDATA lpdata)
```
注：x、y指的是绘制字体的起始坐标。

最后，在完成相应的操作后，要删除字体，以免造成内存泄漏，函数是MGPlusDeleteFont。
```c
MGPlusDeleteFont (HFONT hfont);
```


字体旋转示例代码如下：
```c
   ......
  HDC hdc;  
  HWND hMainhWnd;
......

   hdc = GetClientDC(hMainhWnd);
   HGRAPHICS hgraphics = MGPlusGraphicCreateFromDC(hdc);
    
   int i = 0;
   float x =200;
   float y = 116;
   float angle = 5;   
 
   GLYPHMETRICS   metrics;
   char* text = "GLYPH OUTLINE: ABCDEFG HIJKLMNOPQRSTUVWXYZ,abcdefghijklmnopqrstuvwxyz.";
   GLYPHDATA glyph_data = {0};
   int orig_x = x, orig_y = y;

   //创建矢量字体
   HFONT hfont = MGPlusCreateFont ("timesi.ttf", 0, MP_GLYPH_REN_OUTLINE, 18, 18, TRUE);

   //创建画刷，以及颜色的设置 	
   hbrush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR); 
   MGPlusSetSolidBrushColor (hbrush, 0xFF009000);

   for (i = 0; i < strlen(text); i++) {

             //获取字体的轮廓
	      MGPlusGetGlyphOutline (hfont, text[i], &metrics, &glyph_data) 

             //获取字体的轮廓的路径结构
  	      hpath = MGPlusGetGlyphPath (x, y, &glyph_data);

          if (hpath != NULL){
             /* Transform used path Martix.*/

               //路径的转换
              MGPlusPathTranslate (hpath, -orig_x, -orig_y) ;	             
              MGPlusPathRotate (hpath, angle);
   	      MGPlusPathTranslate (hpath, orig_x, orig_y) ;

              MGPlusPathTransform (hpath); 

               //填充路径
              MGPlusFillPath(hgs, hbrush, hpath); 
              
              //重设路径
              MGPlusPathReset(hpath);
              MGPlusPathDelete(hpath);
  }
	   x += metrics.adv_x;
           y += metrics.adv_y;
 }
 
    MGPlusBrushDelete(hbrush);
    MGPlusGraphicSave(hgraphics, hdc, 0, 0, 0, 0, 0, 0);
    MGPlusDeleteFont (hfont);
    MGPlusGraphicDelete(hgraphics);
    ReleaseDC(hdc);
......
```

<center>     <img src="%ATTACHURLPATH%/3.png" alt="3.png"  ALIGN="CENTER" /> </center>
<center>字体旋转</center>

### 3.2 路径
#### 3.2.1 路径管理

路径：路径是由一组有严格的顺序折线和曲线组成的。可以使用路径进行填充和剪切。通过提供对路径的支持，我们可以实现矢量图形的绘画，可以支持对矢量图形的无极缩放，旋转等功能，同时还能对矢量字体提供更好的支持。 

__创建__

MGPlusPathCreate创建路径时需要选择缠绕规则，缠绕规则分为两种:.
-  MP_PATH_FILL_MODE_WINDING    // 非零规则
-  MP_PATH_FILL_MODE_ALTERNATE  // 奇偶规则

例如：
```c
HPATH path;
path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE)；//path为奇偶规则填充
```

__删除__
释放路径。
如果在应用中不释放内存，会导致内存泄露以至于coredump。

```c
MPStatus MGPlusPathDelete(HPATH path);
```

__重置__
重置路径。
清空路径中所有的内容。
```c
MPStatus MGPlusPathReset(HPATH path);
```

__填充路径__
MGPlusFillPath填充路径之前，必须确定Brush填充特性，然后使用MGPlusGraphicSave绘制到屏幕。
```c
MPStatus MGPlusFillPath (HGRAPHICS graphics, HBRUSH brush, HPATH path)
```
具体的应用在下节“添加图形到路径”中有详细的实例说明。

__添加图形到路径__

*添加直线*

传入两个点的坐标绘制出一条直线。
```c
MPStatus MGPlusAddPathLine(HPATH path, float x1, float y1, float x2, float y2);

MPStatus MGPlusAddPathLineI(HPATH path, int x1, int y1, int x2, int y2);
```

传入一组“点”，按照点的排列顺序依次绘制直线。count为顶点的个数。
```c
MGState MGPlusPathAddLines (HPATH path, const Point* points, int count);
```
例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择奇偶缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//创建一组顶点
MPPOINT point_lines[] = {{0, 0},{100, 0},{100，100},{0, 100}};

//将lines添加到路径path，并且通知顶点的数目为4。
MGPlusPathAddLines ( path, point_lines, 4);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```

     <center><img src="%ATTACHURLPATH%/lines.png" alt="lines.png" ALIGN="CENTER" /></center>
<center>绘制出效的果</center>

*添加弧线*
(cx, cy) 为椭圆的中心点坐标，rx为X轴的半径，ry 为y轴的半径，startangle为弧线开始角度，sweepAngle为开始角和结束角之间的弧度。
```c
MPStatus MGPlusPathAddArc(HPATH path, float cx, float cy, float rx, float ry,float startAngle, float sweepAngle);

MPStatus MGPlusPathAddArcI(HPATH path, int cx, int cy, int rx, int ry,float startAngle, float sweepAngle);
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择奇偶缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//(200, 200)为椭圆的圆心，（100， 100）为半径， 90为弧线开始角度，180为开始角和结束角之间的弧度。
MGPlusPathAddArc (path , 200,200,100,100,90, 180);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/arc.png" alt="arc.png" ALIGN="CENTER" /></center>

*添加贝塞尔曲线*

（x1，y1） 为起点，（x2，y2）为第一控制点，（x3， y3）为第二控制点，（x4，y4）为结束点。 

```c
MPStatus MGPlusPathAddBezier(HPATH path, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

MPStatus MGPlusPathAddBezierI(HPATH path, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择奇偶缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//创建一组顶点
MPPOINT point_lines[] = {{0, 0},{100, 0},{100，100},{0, 100}};

//将Bezier添加到路径path，（11, 11） 为起点，（88, 333）为第一控制点，（99, 0）为第二控制点，（222, 111）为结束点。 
MGPlusPathAddBezier(path, 11,11, 88,333, 99,0, 222,111);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/bezier.png" alt="bezier.png" ALIGN="CENTER"/></center>


*添加矩形*
(x, y)为矩形顶点，（width, height）为矩形的长宽。 
```c
MPStatus MGPlusPathAddRectangle(HPATH path, float x, float y, float width, float height);

MPStatus MGPlusPathAddRectangleI(HPATH path, int x, int y, int width, int height);
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择奇偶缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//添加3个矩形到路径path
MGPlusPathAddRectangle( path, 50, 100, 100, 100);
MGPlusPathAddRectangle( path, 75, 150, 100, 100);
MGPlusPathAddRectangle( path, 100, 175, 100, 100);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/rect.png" alt="rect.png" ALIGN="CENTER" /></center>

*添加圆角矩形*
(x, y)为矩形顶点，（width, height）为矩形的长宽。圆角矩形的圆角弧度是通过一个矩形计算的，而这个矩形的大小就是用（ rx, ry) 来控制的。
```c
MGPlusPathAddRoundRectEx (HPATH path, int x, int y, int width, int height, int rx, int ry)
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择奇偶缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//添加圆角矩形到路径path
MGPlusPathAddRoundRectEx(path, 100, 375, 100 ,100 ,10,10);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/Rectangle.png" alt="Rectangle.png" ALIGN="CENTER" /></center>

*添加椭圆*
（cx,  cy）为椭圆圆心, （rx,  ry）为椭圆的x-radius、y-radius, clockwise 为椭圆的绘制方向，TRUE为顺时针、FALSE为逆时针。
```c
MPStatus MGPlusPathAddEllipse(HPATH path, float cx, float cy, float rx, float ry, BOOL clockwise);

MPStatus MGPlusPathAddEllipseI(HPATH path, int cx, int cy, int rx, int ry, BOOL clockwise);
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择非零缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

//添加矩形
MGPlusPathAddRectangle( path, 625, 350, 200, 75);
//添加圆到路径path，（675, 425）为椭圆圆心, （25 ,25）为椭圆的x-radius、y-radiusTRUE为顺时针、FALSE为逆时针。
MGPlusPathAddEllipse( path, 675, 425,25 ,25, FALSE );
MGPlusPathAddEllipse( path,775, 425,25 ,25, TRUE);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/Ellipse.png" alt="Ellipse.png" ALIGN="CENTER"/></center>

*添加曲线*

 points 顶点数组，count 顶点个数。
```c
MGPStatus MGPlusPathAddCurve (HPATH path, const POINT* points, int count)；
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择非零缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

//添加矩形
                        MPPOINT point [4];

                       point [0].x = 25.6;
                       point [0].y = 128.0;
                        point [1].x = 102.4; 
                        point [1].y = 230.4;
                        pointe [2].x = 153.6;
                        pointe [2].y = 25.6;
                       point [3].x = 230.4;
                       point [3].y = 128;

                        MGPlusPathAddCurve (path, point, 4);

//填充路径
MGPlusFillPath (graphics, brush, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/Curve.png" alt="Curve.png" ALIGN="CENTER" /></center>

*添加路径*
将add_path中的内容添加到path中.
```c
MPStatus MGPlusPathAddPath (HPATH path, HPATH add_path);
```

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷，填充模式为单色。
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷的颜色为蓝色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//创建路径选择非零缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

//在path中添加路径
MGPlusPathAddRectangle( path, 625, 350, 200, 75);
MGPlusPathAddEllipse( path, 675, 425,25 ,25, FALSE );
MGPlusPathAddEllipse( path,775, 425,25 ,25, TRUE);

//创建目标路径
HPATH add_path = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

//将path中的内容添加到add_path中
MPStatus MGPlusPathAddPath (add_path, path);

//填充路径
MGPlusFillPath (graphics, brush, add_path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```

__绘制路径__
MGPlusDrawPath绘制路径，必须确定Pen绘制特性，然后使用MGPlusGraphicSave绘制到屏幕。
```c
MPStatus MGPlusDrawPath (HGRAPHICS graphics, HPEN pen, HPATH path)；
```
MGPlusDrawPath与MGPlusFillPath的用法相似。

例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//创建路径选择非零缠绕规则
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

//添加矩形
MGPlusPathAddRectangle( path, 625, 350, 200, 75);

//添加圆到路径path，（675, 425）为椭圆圆心, （25 ,25）为椭圆的x-radius、y-radiusTRUE为顺时针、FALSE为逆时针。
MGPlusPathAddEllipse( path, 675, 425,25 ,25, FALSE );
MGPlusPathAddEllipse( path,775, 425,25 ,25, TRUE);

//绘制路径
MGPlusDrawPath (graphics, pen, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawPath.png" alt="DrawPath.png" ALIGN="CENTER" /></center>

__开打和闭合__
在路径中开始一个新子路径。子路径使您可以将一个路径分成几个部分并使用。
```c
MGPStatus MGPlusPathStartFigure (HPATH path);
```

闭合路径。
一旦关闭了子路径，在路径中画的下一条线就会从另一个路径开始。
```c
MGPStatus MGPlusPathCloseFigure (HPATH paht);
```


例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔
HPEN pen = MGPlusPenCreate(9, 0xFF0000FF);

//创建路径
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//开建一个新的路径图形。 
MGPlusPathStartFigure(path);

//添加两条直线
MGPlusPathAddLine (path, 100, 100, 200, 10);
MGPlusPathAddLine (path, 200, 10, 300, 100);

//闭合路径
MGPlusPathCloseFigure(path);

//绘制路径
MGPlusDrawPath (graphics, pen, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/CloseFigure.png" alt="CloseFigure.png" ALIGN="CENTER" /></center>

__画线控制__
将当前的pen移到另一点，而不划出线。
```c
MPStatus MGPlusPathMoveto (HPATH path, float x, float y);

MPStatus MGPlusPathMovetoI (HPATH path, int x, int y);
```

以当前pen的所在点为起点向另一点画线。
```c
MPStatus MGPlusPathLineto (HPATH path, float x, float y);

MPStatus MGPlusPathLinetoI (HPATH path, int x, int y);
```


例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔
HPEN pen = MGPlusPenCreate(9, 0xFF0000FF);

//创建路径
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//设置
                        MGPlusPathMoveto (path, 100,100);
                        MGPlusPathLineto (path, 200,100);
                        MGPlusPathLineto (path, 200,200);
                        MGPlusPathMoveto (path, 100,200);
//绘制路径
MGPlusDrawPath (graphics, pen, path);

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
<center><img src="%ATTACHURLPATH%/Moveto.png" alt="Move.png" ALIGN="CENTER" /></center>

__获取路径__
```c
//获取路径顶点
MPStatus MGPlusPathGetPointCount(HPATH path, int* count);

//获取路径顶点个数
MPStatus MGPlusPathGetPoints (HPATH path, int* count, MPPOINT** pt)；

//获取指定序号的顶点，并读取顶点类型。
MPStatus MGPlusPathGetVertex (HPATH path, int idx, double* x, double* y, int* cmd)；

//设置一个点，以这个顶点为中心进行旋转路径
MGPlusPathRotateAroundPoint(HPATH path, const MPPOINT* pt, float angle)；

//设置路径的绘制方向
MPStatus MGPlusPathSetAllOrientation (HPATH path, MPOrientation orientation)；
```


例如：
```c
//定义HDC
HDC hdc ；
hdc = GetClientDC (hWnd);

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔
HPEN pen = MGPlusPenCreate(9, 0xFF0000FF);

//创建路径
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//添加一个矩形
                        MGPlusPathAddRectangleI (path, 100, 100, 200, 100);

                        int i = 0, count=0;
                        MPPOINT* pt = NULL;
                        MPPOINT  center = {100.0, 50.0};

//获取路径顶点个数
                        MGPlusPathGetPointCount (path ,&count);

//获取路径顶点
                        MGPlusPathGetPoints (path, &count, &pt);


                            double x = 0;
                            double y = 0;
                            int cmd = 0;
////获取第2的顶点，并读取顶点类型。
                            MGPlusPathGetVertex (path, 2, &x, &y, &cmd);

//设置一个点，一这个顶点为中心进行旋转
                        MGPlusPathRotateAroundPoint (path, &center, -10);

             //应用矩阵转换
           MGPlusPathTransform (path) ;

//设置路径的绘制方向
                        MGPlusPathSetAllOrientation (path, MP_ORIENTATION_CW);

//填充路径
                        MGPlusDrawPath(graphics, brush, pen); 

//将Graphics画布中的内容输出到指定设备DC上
MGPlusGraphicSave(graphics, hdc, 0, 0, 0, 0, 0, 0)；
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
<center><img src="%ATTACHURLPATH%/GetPathPoints.png" alt="GetPathPoints.png" ALIGN="CENTER" /></center>

#### 3.2.2 路径转换

mGPlus提供了矩阵对象，一个非常强大的工具，使得编写图形的旋转、平移、缩放代码变得非常容易。一个矩阵对象总是和一个图形变换对相联系在一起的，比方说，路径（PATH）有一个Transform方法，它的一个参数能够接受矩阵对象的地址，每次路径绘制时，它能够根据变换矩阵绘制。图形变换以变换矩阵存储，因而路径转换就是对图形变换。可以设置路径转换矩阵，还可以对路经进行平移、缩放和旋转的变换。


__设置__
调用MGPlusPathSetTransform 函数可设置路径的转换矩阵。
```c
MPStatus MGPlusPathSetTransform (HPATH path, MPMatrix *matrix);
```
对参数matrix的定义如下：
```c
/*
*[ sx,   shy,  0 ]
*| shx, sy  ,  0 |
*[ tx,    ty   ,  0 ]
*/
struct MgPlusMatrix
{   
        double sx, shy, shx, sy, tx, ty;;  //transformation matrix
};
```

调用MGPlusPathResetTransform 函数可重新设置路径的转换矩阵。

```c
MPStatus MGPlusPathResetTransform(HPATH path);
```

__平移__

调用MGPlusPathTranslate 函数，路径将从原始位置沿x和y轴被平移(dx, dy)。

```c
MPStatus MGPlusPathTranslate(HPATH path, float dx, float dy);
```

__缩放__

函数MGPlusPathScale 用于路径的缩放。sx , sy 的值大于1被放大，小于1被缩小。

```c
MPStatus MGPlusPathScale(HPATH path, float sx, float sy);
```


####+旋转
函数MGPlusPathRotate用于路径的旋转，参数angle为旋转的角度值。

```c
MPStatus MGPlusPathRotate(HPATH path, float angle);
```

注意：当按需要对路径进行矩阵转换后，一定要调用MGPlusPathTransform函数，此函数是应用矩阵变换，否则路径转换的效果不能显示出来。

```c
MGPLUS_EXPORT MPStatus MGPlusPathTransform (HPATH path);
```

关于路径转换的用法请参考下面示例：
```c
......

   HWND hWnd;
    HDC hdc;
......

    HGRAPHICS hgs;
    HPATH hpath;
    HBRUSH hbrush;
......

    hdc = BeginPaint(hWnd);
   
   //创建graphics，画刷和路径
    hgs = MGPlusGraphicCreateFromDC(hdc);
    hbrush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR); 
   hpath = MGPlusPathCreate (MP_PATH_FILL_MODE_WINDING);

    //设置画刷的颜色
    MGPlusSetSolidBrushColor (hbrush, 0xFF009000);

   //绘制并填充图形
    MGPlusPathAddRectangle (hpath, 50, 50, 100, 100);
    MGPlusFillPath(hgs, hbrush, hpath); 
   
    //平移
    MGPlusPathTranslate (hpath, 50, 50);
   
   //缩放
    MGPlusPathScale (hpath, 2, 1); 
    
    //旋转
    MGPlusPathRotate (hpath, 30);
    
   //应用矩阵转换
    MGPlusPathTransform (hpath);
    
   //重新填充图形，并应用了转换
    MGPlusFillPath(hgs, hbrush, hpath); 

    //保存
    MGPlusGraphicSave(hgs, hdc, 0,0,0,0,0,0);

   //释放内存空间
    MGPlusBrushDelete(hbrush);
    MGPlusPathDelete(hpath);
    MGPlusGraphicDelete(hgs);
    EndPaint(hWnd,hdc);

......
```

<center>     <img src="%ATTACHURLPATH%/PathTransform.png" alt="PathTransform.png"  ALIGN="CENTER" /> </center>
<center>路径转换</center>

### 3.3 画笔
#### 3.3.1 画笔管理

画笔是用于绘制线条、曲线以及勾勒形状轮廓，是基于点绘机制。画笔除了具有常见的色彩和宽度属性外,还具有对齐方式,线帽,变换方式等属性。

__创建画笔__
用户想要使用画笔绘制图形，需要调用函数 MGPlusPenCreate来创建画笔。
```c
HPEN MGPlusPenCreate (int width, ARGB argb);
``` 
注：width 为画笔的宽度，argb 为画笔的颜色。

__删除画笔__
当完成了相关的图形绘制后，需要释放画笔，调用 MGPlusPenDelete函数删除画笔。
```c
MPStatus MGPlusPenDelete (HPEN pen);
``` 

#### 3.3.2 画笔设置

创建完了画笔之后，用户需根据需要对画笔进行设置，如颜色、宽度、连接的方式和虚线的长度。

####+颜色设置
如果用户需要修改画笔的颜色，调用函数MGPlusPenSetColor即可。

```c  
MPStatus MGPlusPenSetColor (HPEN pen, ARGB rgba)
``` 
  
__宽度设置__
如果用户需要修改画笔的宽度，调用函数 MGPlusPenSetWidth 即可。
```c
MPStatus MGPlusPenSetWidth (HPEN pen, int width)
```

宽度的效果图
<center>     <img src="%ATTACHURLPATH%/width.png" alt="width.png"  ALIGN="CENTER" /> </center>
<center>宽度的效果图</center>
说明：线的宽度依次为1、10和30。

__虚线长度设置__
画笔在默认的状态下绘制出的是实线, 用户想要设置虚线，可调用函数 MGPlusPenSetDashes 来设置，通过参数dash_list使用一个预定义的数组来描述画笔的虚实。虚线样式依赖与一个数组, 数组的元素分别代表虚线中线与间的长度。

```c
MPStatus MGPlusPenSetDashes (HPEN pen, int dash_phase, const unsigned char* dash_list, int dash_len)
```

注：参数dash_phase为， dash_list为虚线的形状， dash_len为虚线形状的长度。
虚线的效果图
<center>     <img src="%ATTACHURLPATH%/dash.png" alt="dash.png"  ALIGN="CENTER" /> </center>
<center>虚线的效果图</center>
说明：虚线的样式依次为{5, 10, 20}、{5, 10, 20, 15}和{5, 10, 20, 15,10,}。


__连接方式设置__

连接方式是指两条直线连接时连接处形状的设置，有五种方式：JOIN_MITER（斜接）、JOIN_ROUND（圆形）、JOIN_BEVEL （斜切）、 JOIN_MILTER_REVERT、JOIN_MILTER_ROUND。调用函数MGPlusPenSetJoinStyle即修改两直线连接处的形状。
```c
 /*
     - Indicates a mitered line join style. See the class overview for an
     - illustration.
     -/
        JOIN_MITER = 0,
        /*
     - Indicates a rounded line join style. See the class overview for an
     - illustration.
     -/
        JOIN_ROUND = 1,
        /*
     - Indicates a bevelled line join style. See the class overview for an
     - illustration.
     -/
        JOIN_BEVEL = 2,
        
        /* reseverd,not used now, but surport by mgplus.*/
        JOIN_MILTER_REVERT = 3,
        
        JOIN_MILTER_ROUND = 4
```

```c
MPStatus MGPlusPenSetJoinStyle (HPEN pen, LINE_JOIN_E line_join);
```

设置的模式为JOIN_MITER的效果图
<center>     <img src="%ATTACHURLPATH%/join1.png" alt="join1.png"  ALIGN="CENTER" /> </center>
<center>模式为JOIN_MITER</center>

设置的模式为JOIN_ROUND的效果图
<center>     <img src="%ATTACHURLPATH%/join2.png" alt="join2.png"  ALIGN="CENTER" /> </center>
<center>模式为JOIN_ROUND</center>

设置的模式为 JOIN_BEVEL的效果图
<center>     <img src="%ATTACHURLPATH%/join3.png" alt="join3.png"  ALIGN="CENTER" /> </center>
<center>模式为JOIN_BEVEL</center>


用户想要修饰绘制线条的头部和尾部的形状，可调用 MGPlusPenSetCapStyle 函数。共有三种方式：CAP_BUTT（平线帽） 、CAP_ROUND（圆线帽）、CAP_SQUARE（方线帽）。

```c
/*
     - Indicates a flat line cap style. See the class overview for an
     - illustration.
     -/
        CAP_BUTT = 0,
        /*
     - Indicates a rounded line cap style. See the class overview for an
     - illustration.
     -/
        CAP_ROUND = 1,
        /*
     - Indicates a square line cap style. See the class overview for an
     - illustration.
     -/
        CAP_SQUARE = 2,
```

```c
MPStatus MGPlusPenSetCapStyle (HPEN pen, LINE_CAP_E line_cap);
```

设置模式为CAP_BUTT的效果图
<center>     <img src="%ATTACHURLPATH%/cap1.png" alt="cap1.png"  ALIGN="CENTER" /> </center>
<center>模式为CAP_BUTT</center>


设置模式为CAP_ROUND的效果图
<center>     <img src="%ATTACHURLPATH%/cap2.png" alt="cap2.png"  ALIGN="CENTER" /> </center>
<center>模式为CAP_ROUND</center>


设置模式为CAP_SQUARE的效果图
<center>     <img src="%ATTACHURLPATH%/cap3.png" alt="cap3.png"  ALIGN="CENTER" /> </center>
<center>模式为CAP_SQUARE</center>

连接方式的示例如下：
```c
static int joinstyle ;
static int capstyle ;
static int radius = 10;

static RECT rcCircle = {0, 60, 400, 300};

static const char *mode[] =
{

    "JOIN_MITER",
    "JOIN_ROUND",
    "JOIN_BEVEL",
    "JOIN_MILTER_REVERT",
    "JOIN_MILTER_ROUND",
    /*
       "CAP_BUTT",
       "CAP_ROUND",
       "CAP_SQUARE",
    -/
};

static void mode_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == CBN_SELCHANGE) {
        int cur_sel = SendMessage (hwnd, CB_GETCURSEL, 0, 0);
        if (cur_sel >= 0) {
            joinstyle = cur_sel;
            //capstyle =  cur_sel;        
            InvalidateRect (GetParent (hwnd), &rcCircle, TRUE);
        }
    }
}

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == TBN_CHANGE) {
        radius = SendMessage (hwnd, TBM_GETPOS, 0, 0);
        InvalidateRect (GetParent (hwnd), &rcCircle, TRUE);
    }
}

int PenProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

    HWND hwnd1, hwnd2;
    HDC hdc;
    int i ;  
    ARGB color = 0xFF00FF00;

    switch (message) 
    {
        case MSG_CREATE:
            {
                hwnd1 = CreateWindow (CTRL_TRACKBAR, "", 
                        WS_VISIBLE | TBS_NOTIFY, 
                        100, 
                        10, 10, 210, 50, hWnd, 0);

                SendMessage (hwnd1, TBM_SETRANGE, 0, 80);
                SendMessage (hwnd1, TBM_SETLINESIZE, 1, 0);
                SendMessage (hwnd1, TBM_SETPAGESIZE, 10, 0);
                SendMessage (hwnd1, TBM_SETTICKFREQ, 10, 0);
                SendMessage (hwnd1, TBM_SETPOS, radius, 0);

                SetNotificationCallback (hwnd1, my_notif_proc);
                SetFocus (hwnd1);

                hwnd2 = CreateWindow (CTRL_COMBOBOX,"",
                        WS_VISIBLE | CBS_DROPDOWNLIST | CBS_NOTIFY,
                        120,
                        250, 10, 150, 40, hWnd, 0 );
               
               // for (i = 0; i < 3 ; i++) {
                for (i = 0; i < 5 ; i++) {
                    SendMessage(hwnd2, CB_ADDSTRING, 0, (LPARAM)mode[i]);
                }

                SetNotificationCallback (hwnd2, mode_notif_proc);
                SendMessage(hwnd2, CB_SETCURSEL, 0, 0);
            }
            break;

        case MSG_PAINT:
            {

                hdc = BeginPaint(hWnd);
                
                //创建MGPlusGraphics和画笔
                HGRAPHICS gpc = MGPlusGraphicCreateFromDC(hdc);
                HPEN pen = MGPlusPenCreate (radius,color);
               
                //capstyle
                /*                
                MGPlusPenSetCapStyle (pen, capstyle);
                MGPlusDrawLine(gpc, pen, 50, 150, 300, 150);
             -/  
            
                 //joinstyle
                MGPlusPenSetJoinStyle (pen, joinstyle);
                MGPlusDrawRectangle(gpc, pen, 100, 100, 200, 180);

                //保存
                MGPlusGraphicSave (gpc, hdc, 0, 0, 0, 0, 0, 0);

                MGPlusPenDelete (pen);
                MGPlusGraphicDelete (gpc);
                EndPaint (hWnd, hdc);
            }
            break;
      
        case MSG_CLOSE:
            DestroyMainWindow(hWnd);
            PostQuitMessage(hWnd);
            return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}
......
```
说明：如果是运行MGPlusPenSetCapStyle的效果，打开被屏蔽的，再关闭JoinStyle的相关点。

#### 3.3.3 绘制图形

不需要MGPlusFillPath和MGPlusGraphicSave这两个过程，可以直接用画笔绘制出图像。

__绘制直线__
两点绘制成一条直线
```c
MPStatus MGPlusDrawLine(HGRAPHICS graphics, HPEN pen,  float x1, float y1, float x2, float y2);

MPStatus MGPlusDrawLineI(HGRAPHICS *graphics, HPEN pen, int x1, int y1, int x2, int y2);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制3条直线
                        MGPlusDrawLine (graphics, pen, 100, 100, 100, 200);
                        MGPlusDrawLine (graphics, pen, 100, 200, 200, 200);
                        MGPlusDrawLine (graphics, pen, 200, 200, 200, 100);
                        MGPlusDrawLine (graphics, pen, 200, 100, 100, 100);

//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawLine.png" alt="DrawLine.png" ALIGN="CENTER" /></center>

####+ 绘制弧线
(cx, cy) 为椭圆的中心点坐标，rx为X轴的半径，ry 为y轴的半径，startangle为弧线开始角度，sweepAngle为开始角和结束角之间的弧度。 
```c
MPStatus MGPlusDrawArc(HGRAPHICS graphics, HPEN pen, float cx, float cy, float rx, float ry, float startAngle, float sweepAngle);

MPStatus MGPlusDrawArcI(HGRAPHICS graphics, HPEN pen, int cx, int cy, int rx, int ry, float startAngle, float sweepAngle);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制弧线椭圆圆心为（100, 100）半径（50, 25）开始角度90，结束角度345，绘制出的结果就是椭圆90－345之间的距离
MGPlusDrawArc (graphics, pen, 100, 100, 50, 25, 90, 345);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawArc.png" alt="DrawArc.png" ALIGN="CENTER" /></center>

__绘制贝塞尔曲线__
（x1，y1） 为起点，（x2，y2）为第一控制点，（x3， y3）为第二控制点，（x4，y4）为结束点。
```c
MPStatus MGPlusDrawBezier(HGRAPHICS graphics, HPEN pen, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

MPStatus MGPlusDrawBezierI(HGRAPHICS graphics, HPEN pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制贝塞尔曲线 
MGPlusDrawBezier(graphics, pen ,11,11, 88,333, 99,0, 222,111);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawBezier.png" alt="DrawBezier.png" ALIGN="CENTER" /></center>


__绘制矩形__
(x, y)为矩形顶点，（width, height）为矩形的长宽。 
```c
MPStatus MGPlusDrawRectangle(HGRAPHICS graphics, HPEN pen, float x, float y, float width, float height);

MPStatus MGPlusDrawRectangleI(HGRAPHICS graphics, HPEN pen, int x, int y, int width, int height);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制矩形
MGPlusDrawRectangle(graphics, pen, 50, 100, 100, 100);
MGPlusDrawRectangle(graphics, pen, 75, 150, 100, 100);
MGPlusDrawRectangle(graphics, pen, 100, 175, 100, 100);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawRectangle.png" alt="DrawRectangle.png" ALIGN="CENTER" /></center>


__绘制圆角矩形__
(x, y)为矩形顶点，（width, height）为矩形的长宽。圆角矩形的圆角弧度是通过一个矩形计算的，而这个矩形的大小就是用（ rx, ry) 来控制的。 
```c
 MPStatus MGPlusDrawRoundRectIEx (HGRAPHICS graphics, HPEN pen, int x, int y, int width, int height, int rx, int ry);

MPStatus  MGPlusDrawRoundRectEx (HGRAPHICS graphics, HPEN pen, float x, float y, float width, float height, float rx, float ry);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制圆角矩形
MGPlusDrawRoundRectEx(graphics, pen, 100, 375, 100 ,100 ,10,10);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawRoundRect.png" alt="DrawRoundRect.png" ALIGN="CENTER" /></center>

__绘制椭圆__
（cx, cy）为椭圆圆心, （rx, ry）为椭圆的x-radius、y-radius
```c
MPStatus MGPlusDrawEllipse(HGRAPHICS graphics, HPEN pen, float cx, float cy,float rx, float ry, BOOL b_clock);

MPStatus MGPlusDrawEllipseI(HGRAPHICS graphics, HPEN pen, int cx, int cy, int rx, int ry, BOOL b_clock);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画笔，画笔宽度为9，颜色为蓝色。
HPEN pen = MGPlusPenCreate (9, 0xFF0000FF);

//绘制椭圆
MGPlusDrawEllipse(graphics, pen, 100, 100, 50 , 25);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawEllipse.png" alt="DrawEllipse.png" ALIGN="CENTER" /></center>


__加载图片__
mgplus的所用到的位图必须是与graphic兼容格式的，所以从其它dc加载的位图，需要转换处理一下。
加载图片的两种方式：

```c
//从文件加载一个设备相关位图
LoadBitmap (HDC hdc, PBITMAP bmp, const char* file_name);
//转换为graphic兼容格式的位图
MPStatus MGPlusGraphicLoadBitmap (HGRAPHICS graphics, int n_index, PBITMAP p_bitmap);
```

```c
//直接转换为graphic兼容格式的位图
MPStatus MGPlusGraphicLoadBitmapFromFile(HGRAPHICS graphics, int n_index, char* file);
```

__绘制图片__
绘制图片有三种方式：

```c
//n_index 图片索引值， (x, y)起始位置 ，（w, h）图片的宽高。
MPStatus MGPlusDrawImage (HGRAPHICS graphics, int n_index, int x, int y, int w, int h);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//加载图片
MGPlusGraphicLoadBitmapFromFile (graphics, 0,"File.bmp" );

//绘制图片
MGPlusDrawImage (graphics,  0, 100, 100, 200, 200);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawImage.png" alt="DrawImage.png" ALIGN="CENTER" /></center>


```c
//n_index 图片索引值， point 一组顶点，count顶点数目。
MPStatus MGPlusDrawImageWithPoints (HGRAPHICS graphics, int n_index,  const Point& point, int count);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//加载图片
                        static BITMAP Bitmap;
                        LoadBitmap (HDC_SCREEN, &Bitmap, "./res/wede.bmp");
                        MGPlusGraphicLoadBitmap (graphics, 1, &Bitmap);
//绘制图片
MPPOINT points [4];

                        points [0].x = 100;
                        points [0].y = 50;

                        points [1].x = 200;
                        points [1].y = 50;

                        points [2].x = 300;
                        points [2].y = 200;

                        points [3].x = 0;
                        points [3].y = 200;

                        MGPlusDrawImageWithPoints (graphics, 1, points, 4);

//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawImagePoints.png" alt="DrawImagePoints.png" ALIGN="CENTER" /></center>




```c
//n_index 图片索引值， path 目标路径。
MGPlusDrawImageWithPath(HGRAPHICS graphics, int n_index, HPATH path)；
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);
                       
//加载图片                       
MGPlusGraphicLoadBitmapFromFile (graphics, 0,"./res/wede.bmp" );

//必须有路径存在才能绘制出图像，所以首先创建一个路径。
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);
                        MGPlusPathAddRoundRect (path, 100, 100, 200, 200, 20);

//在路径中绘制图像
                        MGPlusDrawImageWithPath (graphics, 0, path);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/DrawImageWithPath.png" alt="DrawImageWithPath.png" ALIGN="CENTER" /></center>

### 3.4 画刷
#### 3.4.1 画刷管理

画刷基于填充机制，用于与 Graphics 对象一起创建实心形状和呈现文本的对象。

__创建__
使用MGPlusBrushCreate创建画刷时需要选择画刷风格
```c
typedef enum _MPBrushType
{
    /* Brush the path with the single color.*/
    MP_BRUSH_TYPE_SOLIDCOLOR = 0,   
    /* Brush the path with the hatchfill.*/
    MP_BRUSH_TYPE_HATCHFILL = 1,    
    /* Brush the path with the texturefill.*/
    MP_BRUSH_TYPE_TEXTUREFILL = 2,  
    /* Brush the path with the path gradient.*/
    MP_BRUSH_TYPE_PATHGRADIENT = 3, 
    /* Brush the path with linear gradient.*/
    MP_BRUSH_TYPE_LINEARGRADIENT    
}MPBrushType;

HBRUSH MGPlusBrushCreate (MGPlusBrushType type);
``` 

__删除__
释放画刷
```c
MPStatus MGPlusBrushDelete (HBRUSH brush);
``` 

#### 3.4.2 画刷设置

__实心画刷SolidBrush设置__
设置单一画刷的颜色
```c  
MPStatus MGPlusSetSolidBrushColor (HBRUSH brush, RGBA* rgba);
``` 
<noscript>
 阴影画刷Hatch brush设置
设置Hatch brush的颜色
```c  
MPStatus MGPlusSetHatchBrushColor (HBRUSH brush, RGBA fore_rgba, RGBA back_rgba);
``` 

获取Hatch brush的颜色
```c  
MPStatus MGPlusGetHatchBrushColor (HBRUSH brush, RGBA* fore_rgba, RGBA* back_rgba);
``` 

 纹理画刷TextureBrush设置。 
```c  
MPStatus MGPlusSetTextureBrushImage (HBRUSH brush, BITMAP* bitmap);
``` 

</noscript>
__渐变画刷GradientBrush设置__

*路径渐变画刷PathGradientBrush设置*

设置PathGradientBrush的中心点
```c  
MPStatus MGPlusSetPathGradientBrushCenterPoint (HBRUSH brush, POINT* point);
``` 

设置PathGradientBrush的中心点颜色
```c  
MPStatus MGPlusSetPathGradientBrushCenterColor (HBRUSH brush, RGBA* rgba);
``` 

设置PathGradientBrush缠绕颜色
```c  
MPStatus MGPlusSetPathGradientBrushSurroundColor (HBRUSH brush, RGBA rgba);
``` 

设置PathGradientBrush的弧形渐变的范围
```c  
MPStatus MGPlusSetPathGradientBrushSurroundRect (HBRUSH brush, RECT* rect);
``` 

例如：
```c  
//创建 MP_BRUSH_TYPE_PATHGRADIENT 风格的画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_PATHGRADIENT);

//创建一个路径
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//在路径中添加图形
            MGPlusPathAddRectangle (path, 25, 150, 300, 100);
            MGPlusPathAddEllipse (path, 100, 250, 50, 50, TRUE);
            MGPlusPathAddEllipse (path,250, 250, 50, 50, TRUE);

//设置中心点
                        MPPOINT point = {170,225};
                        MGPlusSetPathGradientBrushCenterPoint (brush, &point);

//设置中心点的颜色
                        MGPlusSetPathGradientBrushCenterColor (brush, 0xFF0000FF);

//设置缠绕颜色 
static ARGB SurroundColors [3] = {0xFFFF00FF, 0xFF00FF00, 0xFFFF0000};
                        MGPlusSetPathGradientBrushSurroundColors (brush, SurroundColors, 3);

//设置弧形渐变的范围
                        RECT rect = {25,150,325,250};
                        MGPlusSetPathGradientBrushSurroundRect (brush, &rect);

//填充路径
                        MGPlusFillPath (graphics, brush, path);
//保存到DC
            MGPlusGraphicSave (graphics, hdc, 0, 0, 0, 0, 0, 0);

``` 
     <center><img src="%ATTACHURLPATH%/PathGradientBrush.png" alt="PathGradientBrush.png" ALIGN="CENTER" /></center>


*线性渐变画刷LinearGradientBrus设置*
设置LinearGradientBrush模式
```c  
typedef enum _MPLinearGradientMode
{
    /* gradient horizontal.*/
    MP_LINEAR_GRADIENT_MODE_HORIZONTAL = 0,  
    /* gradient vertica.*/
    MP_LINEAR_GRADIENT_MODE_VERTICAL,        
    /* gradient forwarddiagonal.*/
    MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL, 
    /* gradient backwarddiagonal.*/
    MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL 
}MPLinearGradientMode;

MPStatus MGPlusSetLinearGradientBrushMode (HBRUSH brush, MGPlusLinearGradientMode mode);
``` 

获取LinearGradientBrush模式
```c  
MPStatus MGPlusGetLinearGradientBrushMode (HBRUSH brush, MGPlusLinearGradientMode* mode);
``` 

设置LinearGradientBrush区域
```c  
MPStatus MGPlusSetLinearGradientBrushRect (HBRUSH brush, RECT* rect);
``` 

设置LinearGradientBrush渐变颜色
```c  
MPStatus MGPlusSetLinearGradientBrushColor (HBRUSH brush, RGBA* start_color, RGBA* end_color);
``` 

例如：
```c  
//创建 MP_BRUSH_TYPE_LINEARGRADIENT 风格的画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_LINEARGRADIENT);

//创建一个路径
HPATH path = MGPlusPathCreate (MP_PATH_FILL_MODE_ALTERNATE);

//在路径中添加图形
            MGPlusPathAddRectangle (path, 25, 150, 300, 100);
            MGPlusPathAddEllipse (path, 100, 250, 50, 50, TRUE);
            MGPlusPathAddEllipse (path,250, 250, 50, 50, TRUE);

//设置画刷为MP_LINEAR_GRADIENT_MODE_HORIZONTAL 模式
  MGPlusSetLinearGradientBrushMode (brush, MP_LINEAR_GRADIENT_MODE_HORIZONTAL);

//设置LinearGradientBrush区域
    static RECT rect = {25,150,325,250};
                    MGPlusSetLinearGradientBrushRect (brush, &rect);

// 设置LinearGradientBrush渐变颜色
    static ARGB color [6] = {0xFFFF0000, 0xFF0000FF,0xFFFF00FF, 0xff00FFFF,0xff00FF00, 0xFF00FF00};
                   MGPlusSetLinearGradientBrushColors (brush, color, 6);

//填充路径
                        MGPlusFillPath (graphics, brush, path);
//保存到DC
            MGPlusGraphicSave (graphics, hdc, 0, 0, 0, 0, 0, 0);

``` 
 <center><img src="%ATTACHURLPATH%/MP_LINEAR_GRADIENT_MODE_HORIZONTAL.png" alt="MP_LINEAR_GRADIENT_MODE_HORIZONTAL.png" ALIGN="CENTER" /></center>
 <center>MP_LINEAR_GRADIENT_MODE_HORIZONTAL.</center>
以下是其他模式的演示图：
设置画刷为MP_LINEAR_GRADIENT_MODE_VERTICAL模式
 <center><img src="%ATTACHURLPATH%/MP_LINEAR_GRADIENT_MODE_VERTICAL.png" alt="MP_LINEAR_GRADIENT_MODE_VERTICAL.png" ALIGN="CENTER" /></center>
 <center>MP_LINEAR_GRADIENT_MODE_VERTICAL</center>

设置画刷为MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL模式
 <center><img src="%ATTACHURLPATH%/MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL.png" alt="MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL.png" ALIGN="CENTER" /></center>
 <center>MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL</center>

设置画刷为MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL 模式
 <center><img src="%ATTACHURLPATH%/MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL.png" alt="MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL.png" ALIGN="CENTER"/></center>
 <center>MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL </center>

#### 3.4.3 填充图形

不需要MGPlusFillPath和MGPlusGraphicSave这两个过程，可以直接用画刷绘填充图像。 

__填充弧线__
(cx, cy) 为椭圆的中心点坐标，rx为X轴的半径，ry 为y轴的半径，startangle为弧线开始角度，sweepAngle为开始角和结束角之间的弧度。 
```c
MPStatus MGPlusFillArc (HGRAPHICS graphics, HBRUSH brush, float cx, float cy, float rx, float ry, float startAngle, float sweepAngle);

MPStatus MGPlusFillArcI (HGRAPHICS graphics, HBRUSH brush, int cx, int cy, int rx, int ry, float startAngle, float sweepAngle);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷颜色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//填充弧线
                        MGPlusFillArc (graphics, brush,  100, 100, 50, 50, 90, 180);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/FillArc.png" alt="FillArc.png" ALIGN="CENTER" /></center>


__填充贝塞尔曲线__ 
（x1，y1） 为起点，（x2，y2）为第一控制点，（x3， y3）为第二控制点，（x4，y4）为结束点。 
```c
MPStatus MGPlusFillBezier (HGRAPHICS graphics, HBRUSH brush, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

MPStatus MGPlusFillBezierI (HGRAPHICS graphics, HBRUSH brush, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷颜色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//填充贝塞尔曲线 
MGPlusFillBezier (graphics, brush, 11,11, 88,333, 99,0, 222,111);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/FillBezier.png" alt="FillBezier.png" ALIGN="CENTER" /></center>

__填充矩形__
(x, y)为矩形顶点，（width, height）为矩形的长宽。 
```c
MPStatus MGPlusFillRectangle (HGRAPHICS graphics, HBRUSH brush, float x, float y, float width, float height);

MPStatus MGPlusFillRectangleI (HGRAPHICS graphics, HBRUSH brush, int x, int y, int width, int height);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷颜
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//填充矩形
MGPlusFillRectangleI (graphics, brush, 100, 175, 100, 100);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/FillBezier.png" alt="FillBezier.png" ALIGN="CENTER" /></center>

__填充圆角矩形__
(x, y)为矩形顶点，（width, height）为矩形的长宽。圆角矩形的圆角弧度是通过一个矩形计算的，而这个矩形的大小就是用（ rx, ry) 来控制的。 
```c
MPStatus MGPlusFillRoundRectIEx (HGRAPHICS graphics, HBRUSH brush, int x, int y, int width, int height, int rx, int ry);

MPStatus MGPlusFillRoundRectEx (HGRAPHICS graphics, HBRUSH brush, float x, float y, float width, float height, float rx, float ry);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷颜色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//填充圆角矩形
MGPlusFillRoundRectIEx ( graphics,  brush, 100, 375, 100 ,100 ,10,10);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/FillRoundRect.png" alt="FillRoundRect.png" ALIGN="CENTER" /></center>

__填充椭圆__
（cx, cy）为椭圆圆心, （rx, ry）为椭圆的x-radius、y-radius 
```c
MPStatus MGPlusFillEllipse (HGRAPHICS graphics, HBRUSH brush, float cx, float cy, float rx, float ry);

MPStatus MGPlusFillEllipseI (HGRAPHICS graphics, HBRUSH brush, int cx, int cy, int rx, int ry);
```

例如：
```c
//定义HDC
HDC hdc ；

//传入 HDC 创建graphics
HGRAPHICS graphics= MGPlusGraphicCreateFromDC(hdc);

//创建画刷
HBRUSH brush = MGPlusBrushCreate (MP_BRUSH_TYPE_SOLIDCOLOR);

//设置画刷颜色
MGPlusSetSolidBrushColor (brush, 0xFF0000FF);

//填充椭圆
MGPlusFillEllipse (graphics, brush, 100, 100, 50 , 25);
//                              .       
//                              .       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                              .                       
//                       Destroy....释放内存
```
     <center><img src="%ATTACHURLPATH%/FillEllipse.png" alt="FillEllipse.png" ALIGN="CENTER" /></center>
