# 14 Handling and Rendering of Text
As discussed before, the handling and rendering of text has some of their own features in MiniGUI. We will elaborate the concepts related to text handling and introduce the relevant APIs in this chapter.

## 14.1 Charset and Encoding
Charset (character set) is a collection of characters defined to represent certain language; Encoding is the coding rules set to represent characters in certain charset. Encoding usually ranks the character by fixed order and uses them as the internal features of recording, storing, transfer and exchange. People who have conducted computer know the ASCII code defined by the US National Standard Authorization. ASCII code can be understood as an encoding format of American English charset; this coding format uses one 7-bit byte to represent one character scoped from 0x00 to 0x7F.

<b>[Note] Type man ascii to get the definition of ASCII on Linux command line. </b>

ASCII cannot meet the requirement of non-English speakers as the use of computer has spreads to the entire world. Therefore, almost all countries define the standard of charset and encoding based on their own official languages. The well-known standard GB2312-80 is the simplified Chinese charset standard defined by China government. GB2312-80 includes 682 symbols and 6763 Chinese words. It has 87 divisions, each of which has 94 characters. There are other standards, such as ISO8859 used for the single-byte charsets, JISX0201, JISX0208 charset defined by Japan, BIG5 traditional Chinese charset, and so on.

One charset can have different encoding format. Usually we use EUC encode (extended UNIX code) for GB2312 charset. EUC encodes each GB2312 charset as 2 bytes scoped in 0xA1~0xFE. The higher byte represents GB2312 area code while the lower one represents GB2312 position code. Another popular GB2312 code is HZ code, which removes the highest bit of EUC code, thus using ASCII to represent Chinese characters. For example, the code of Chinese word “啊” is 0xB1A1 in EUC encoding, while in HZ encoding the character is ~{1!~}.

With the publication and update of the charset of each country and area, the problem of compatibility rises. For example, a text file that uses GB2312 EUC code cannot be properly displayed on BIG5 system. Therefore, some international organizations begin to develop the globally universal charset standard, that is, the well-known UNICODE charset. 

The international standard organization established ISO/IEC JTC1/SC2/WG2 work group in April 1984. This group is responsible for integrating different characters and symbols of different countries. In 1991, some American companies established Unicode Consortium and got agreement with WG2 to use the same code-set in October 1991. At present, UNICODE 2.0 version includes 6811 characters, 20902 Chinese characters, 11172 Korean characters, 6400 make-up divisions and 20249 reserved characters, totally 65534 characters. UNICODE charset has multiple encoding formats, the most popular one is using 16-bit double bytes to express one character; it is also called USC2; another is UTF8 encoding format, which can be compatible with ASCII and ISO8859-1 charset. The byte-count used to represent a character is variable.

<b>[Prompt] Type man unicode and man utf-8 on Linux command line can get the information of UNICODE charset and UTF8 encoding. </b>

UNICODE can solve the compatibility problem of charsets. However, most countries and regions do not recognize UNICODE charset. For example, China government asks all OS software products must support GB18030 charset, not the UNICODE charset. The reason is that GB18030 is compatible with GB2312 and GBK charset popularly used in China main land areas, but not compatible with UNICODE.

UNICODE provides a way to solve charset compatibility problem for general-purpose operating systems. However, it is not the best way for the embedded systems. MiniGUI uses the internal code that is completely consistent with the default code of that charset to represent. Then, the abstract interfaces provide an universal analysis interface to text in any charset. This interface can be used to analyze both of the font module and the multi-byte character string. So far MiniGUI can support ISO8859-x (single-byte charsets), GB2312, GBK, GB18030, BIG5, EUCKR, Shift-JIS, and EUCJP (multi-byte charsets). MiniGUI also support UTF-8 and UTF-16 encode of UNICODE charset through the abstract interface of charset.

<b>[Prompt] The charset support of MiniGUI can be also understood as the support of certain encoding format of that charset. </b>

MiniGUI uses logical font interface to support multi-byte charset. When application displays text, it usually needs to set logical font and assign the encoding name of chosen charset. After creating logical font, application can use it to display text or analyze text string.

## 14.2 Device Font

Device font is a data structure which associates with font under layer. Each device font has a set of operation (font_ops) which includes some abstract interfaces, such as get_char_width, get_char_bitmap. Each type of font, which is supported by MiniGUI, has a set of operation. By using this set of operation, we can get any character's dot-matrix (for raster font) or glyph (for vector font). Then, GDIs of MiniGUI can output these dot-matrix to screen. These are the characters we can see from the screen.

To correctly display text needs to get the shape data corresponding to each character. These shape data is called glyph and is saved in a file of certain type, which is usually called a font file. The most popular type of font file is dot-matrix (bitmap) font, which uses bitmap to store the information of dot-matrix glyph of each character. Another popular type is vector font, which stores the frame information of each character and can be zoomed by certain algorithms. The popular types of vector font are TrueType and Adobe Type1.

Similar to charset, MiniGUI defines a series of abstract interfaces for font. Now MiniGUI can support RBF, VBF (two MiniGUI-defined dot-matrix font formats), TrueType and Adobe Type1 fonts. MiniGUI can also support QPF (Qt Pre-rendered Fonts) font. MiniGUI can enlarge dot-matrix (bitmap) font automatically and provide Anti-aliased feature for TV or other specified display device.

Besides, MiniGUI implements bitmap font which is a device font by using BITMAP to show characters. This font can make glyph according to customized bitmap, and is provided to application and controls like other logical font interface.

VBF V3.0 font is an upgrade version of V2.0, it enlarges the range of character set. There is no limited for the character set which is for Latin system, and the number of glyph in one VBF font can be greater than 255.

UPF font is an enhancement version of QPF font, it is convenience for MiniGUI uses the font by memory mapping. It reduces memory usage when using QPF font in MiniGUI-Processes mode. It supports BIDI text, such as Arabic and Hebrew.

<noscript>
We can enable or disable any device font in MiniGUI by changing configuration options for configure script. The followings are the options for each device font:
- --enable-rbfsupport    It is the option for RBF font. MiniGUI supports it by default. If you don't want to support it, please use --disable-rbfsupport to disable it.
- --enable-vbfsupport    It is the option for VBF font. MiniGUI supports it by default. If you don't want to support it, please use --disable-vbfsupport to disable it.
- --enable-upfsupport    It is the option for UPF font. MiniGUI supports it by default. If you don't want to support it, please use --disable-upfsupport to disable it.
- --enable-qpfsupport    It is the option for QPF font. MiniGUI supports it by default. If you don't want to support it, please use --disable-qpfsupport to disable it.
- --with-ttfsupport=ft1/ft2/none   It is the option for vector font. There are two versions of vector font engines in MiniGUI, one is freetype 1.3.1, another is freetype 2.0. Please use --with-ttfsupport=ft1 option for using 1.3.1 version and use --with-ttfsupport=ft2 to support 2.0. MiniGUI doesn't support vector font in default, so you must use ft1 or ft2 to enable vector font support. It is important to note, you must install freetype library before enable vector font support. Otherwise, you can not enable it.
</noscript>

When initializing MiniGUI, it is needed to read MiniGUI.cfg and load certain font files. The loaded font is internally called device font. Device font defines the format name, type, size and its supported charset. According to the loaded device font and the font type, name, size and character information assigned by application program, MiniGUI searches the proper device font to display text. 

The following functions provide the support for loading and destroying dynamically font (ttf or qpf) :

```cplusplus
BOOL GUIAPI LoadDevFontFromFile(const char *devfont_name, 
const char *file_name, DEVFONT** devfont);

void GUIAPI DestroyDynamicDevFont (DEVFONT **devfont);
```

### 14.2.1 Bitmap device font
Bitmap device font is different than other device fonts which can be configured in MiniGUI.cfg, it is created in application. The followings are related functions.
```cplusplus
DEVFONT *CreateBMPDevFont (const char *bmpfont_name, const BITMAP* glyph_bmp,
        const char* start_mchar, int nr_glyphs, int glyph_width);
BOOL AddGlyphsToBMPFont (DEVFONT* dev_font, BITMAP* glyph_bmp,
        const char* start_mchar, int nr_glyphs, int glyph_width)

void DestroyBMPFont (DEVFONT* dev_font)
```
- CreateBMPDevFont  It creates bitmap device font and insert the device font which is successfully created into device font list. The arguments need to be passed are font's type, name, style, size and font name of supported character set, bitmap structure pointer, the first character of device font, the number of characters in device font, width of every character. It is important to note, the characters in each bitmap of bitmap device font must be continuous and have the same width.
- AddGlyphsToBMPFont  It adds characters in bitmap device font which already has been created. So bitmap font can display more characters. The first argument is device font pointer, other arguments are as same as CreateBMPDevFont.
- DestroyBMPFont  It destroys bitmap device font.

In the following codes, it creates bitmap device font which can display '0' to '9' firstly, then adds 'ABCDEFG' and '+' into device font. Finally, it creates logical font with 'led' style.

```cplusplus
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
The following images are used in above codes.<br /> 
     <img src="%ATTACHURLPATH%/digits1.png" alt="digits1.png" width='100' height='15' />
     <img src="%ATTACHURLPATH%/digits2.png" alt="digits2.png" width='62' height='15' />
     <img src="%ATTACHURLPATH%/digits3.png" alt="digits3.png" width='40' height='15' />
     <img src="%ATTACHURLPATH%/digits4.png" alt="digits4.png" width='10' height='15' />     

<b>[Prompt] The information of definition, name and format of device font is described in 3.1.4 of MiniGUI User Manual.</b>


## 14.3 Logical font
Logical font is a GDI object, its symbol is stored in  HFONT variable. Logical font is description of font. It is abstract object, just like logical pen and logical brush. It becomes real object only when application calls SelectObject to select it into device context.

The logical font of MiniGUI has strong functions, including abundant information such as charset, font type, and style. It can be used not only to render text, but also to analyze the text string. This is very useful in most text edition applications. Before using its logical font, you need firstly build it and choose it to the device context, which will use this logical font to output text. The default logical font of each device context is the default system-defined font in MiniGUI.cfg. You can establish the logical font by calling CreateLogFont, CreateLogFontByName, and CreateLogFontIndirect. You can also use function SelectFont to select a logical font to a device context. It is DestroyLogFont that is used to destroy logical font. However, you cannot destroy the selected logical font. The prototypes of these functions are as follow (minigui/gdi.h):

```cplusplus
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

The following code fragment creates multiple logical fonts:
```cplusplus
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
The first font, logfont, belongs to ISO8859-1 charset and uses SansSerif with the height of 16 pixels; logfontgb12 belongs to GB2312 charset and uses Song with the height of 12 pixels; logfontbig24 belongs to BIG5 charset and uses Ming. The desired size of the last font is 24 pixels, and we use FONT_OTHER_AUTOSCALE style to create the logical font. The style FONT_OTHER_AUTOSCALE tells MiniGUI to auto-scale the font glyph to meet the desired font size.

We can also call GetSystemFont function to return a system logical font, the argument font_id in that can be one of the following values:
- SYSLOGFONT_DEFAULT: System default font, it has to be a single-byte charset logical font and must be formed by RBF device font.
- SYSLOGFONT_WCHAR_DEF: System default multi-byte charset font. It is usually formed by RBF device font. Its width is twice of the SYSLOGFONT_DEFAULT logical font.
- SYSLOGFONT_FIXED: System font with fixed width.
- SYSLOGFONT_CAPTION: The logical font used to display text on caption bar.
- SYSLOGFONT_MENU: The logical font used to display menu text.
- SYSLOGFONT_CONTROL: The default logical font used by controls.

The system logical fonts above are created corresponding to definition of MiniGUI.cfg when MiniGUI is initialized.

<b>[Prompt] The information of definition, name and format of system logical font is described in 3.1.5 of MiniGUI User Manual.</b>

GetCurFont function returns current logical font in a device context. You cannot call DestroyLogFont to destroy a system logical font.

## 14.4 Text Analysis
After establishing logical font, the application program can use logical font to analyze multi-language-mixed text. Here the multi-language-mixed text means the character string formed by two non-intersected charset texts, such as GB2312 and ISO8859-1, or BIG5 and ISO8859-2. You can use the following functions to analyze the text constitutes of multi-language-mixed text (minigui/gdi.h):

```cplusplus
// Text parse support
  int GUIAPI GetTextMCharInfo (PLOGFONT log_font, const char* mstr, int len, 
                  int* pos_chars);
  int GUIAPI GetTextWordInfo (PLOGFONT log_font, const char* mstr, int len, 
                  int* pos_words, WORDINFO* info_words);
  int GUIAPI GetFirstMCharLen (PLOGFONT log_font, const char* mstr, int len);
  int GUIAPI GetFirstWord (PLOGFONT log_font, const char* mstr, int len,
                  WORDINFO* word_info);
```
GetTextMCharInfo returns the byte address of each character of the multi-language-mixed text. For example, for the string “ABC汉语”, this function will return {0, 1, 2, 3, 5} five values in pos_chars. GetTextWordInfo will analyze the place of each word of the multi-language-mixed text. As for single-byte charset text, we use blank and TAB key as the delimiter; as for multi-byte charset text, the word uses single-byte character as the delimiter. GetFirstMCharLen returns the byte length of the first character. GetFirstWord returns the word information of the first word.

## 14.5 Text Transformation

MiniGUI provides the functions of converting multibyte charset text to wide charset text in UCS or wide charset text in UCS to multibyte charset text.

```cplusplus
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
MB2WCEx is used to convert a multibyte character (GB2312, ISO8859, UTF-8, GBK, BIG5, etc) to a wide character in UCS according to the charset/encoding of the logical font. And MBS2WCSEx is used to convert a multibyte string (GB2312, ISO8859, UTF-8, GBK, BIG5, etc) to a wide string in UCS according to the charset/encoding of the logical font. 

WC2MBEx is used to convert a wide character in UCS to a multibyte character (GB2312, ISO8859, UTF-8, GBK, BIG5, etc) according to the charset/encoding of the logical font. And WCS2MBSEx is used to convert a wide string in UCS to a multibyte string (GB2312, ISO8859, UTF-8, GBK, BIG5, etc) according to the charset/encoding of the logical font.

## 14.6 Text Output

The following functions can be used to calculate the output length and width of text (minigui/gdi.h):

```cplusplus
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
GetTextExtentPoint is used to calculate the maximal number of the characters can be output, the byte place of each character, the output place of each character, and the actual output width and height of multi-byte text in a given output width (that is, the width of the output character is limited in a certain extent). GetTextExtentPoint is an integrated function, which is very useful for editor-type application. For example, in the single-line and multi-line edit box control; MiniGUI uses this function to calculate the position of the caret.

On the basis of GetTextExtentPoint function, handles for 'enter', 'newline' ,'TAB' and other formatting characters were added in GetTabbedTextExtentPoint function.

GetFontHeight and GetMaxFontWidth return the height and maximum width of a font. GetTextExtent calculates the output width and height of text. GetTabbedTextExtent returns the output width and height of formatted text string.

The following function is used to output text (minigui/gdi.h):
```cplusplus
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
TextOutLen is used to output a certain text with appropriate length at given position. If length is -1, the character string must terminate with '\0'. TabbedTextOutLen is used to output formatted text string. TabbedTextOutEx is used to output formatted character string, but also can specify the position of each TAB character in the text string.

Fig. 14.1 is the output of TextOut, TabbedTextOut, and TabbedTextOutEx functions.

<center>     <img src="%ATTACHURLPATH%/14.1.jpeg" alt="14.1.jpeg"  ALIGN="CENTER" /> </center>
<center>Fig. 14.1 Output of TextOut, TabbedTextOut, and TabbedTextOutEx functions</center>
DrawText is the most complicated text output function, which can use different ways to output text in a given rectangle. 

On the basis of DrawText, DrawTextEx can configure the number of characters of text-indent.

On the basis of first two functions, DrawTextEx2 can calculate the number of characters in first line. It is very useful for multi-line-edit. Because multi-line-edit needs to know the width of edit to calculate how many characters can be displayed in first line, so the character which is the first one in second line can be known. The argument, firstline, includes the number of characters in first line and display it.

Now, DrawText doesn’t support UTF-16 text. Table 14.1 lists the formats supported by DrawText.

<center>Table 14.1 Output formats of DrawText function</center>

<center>
| *Format identifier* | *Meaning* | *Note* |
| DT_TOP | Top-justifies the text. | single line only (DT_SINGLELINE) |
| DT_VCENTER | Centers text vertically. | ^ |
| DT_BOTTOM | Justifies the text to the bottom of the rectangle. | ^ |
| DT_LEFT | Aligns text to the left. | |
| DT_CENTER | Aligns text in the center. | |
| DT_RIGHT | Aligns text to the right. | |
| DT_WORDBREAK | Lines are automatically broken between words if a word would extend past the edge of the rectangle specified by the pRect parameter. | |
| DT_CHARBREAK | Lines are automatically broken between characters if a character would extend past the edge of the rectangle specified by the pRect parameter. | |
| DT_SINGLELINE | Displays text on the single line only. Carriage returns and linefeeds do not break the line. | The vertical  align flag will be ignored when there is not this flag |
| DT_EXPANDTABS | Expands TAB characters. | |
| DT_TABSTOP | Sets tab stops. Bits 15-8 (high-order byte of the low-order word) of the uFormat parameter specify the number of characters for each TAB.  | |
| DT_NOCLIP | Draws without clipping. Output will be clipped to the specified rectangle by default. | |
| DT_CALCRECT | Do not output actually, only calculate the size of output rectangle. | |

</center>

Code in List 14.1 calls DrawText function to perform aligned text output, according to the description of character to be output. Please refer to fontdemo.c program in MDE for complete code of the program. Fig. 14.2 shows the output effect of the program.

<center>List 14.1 Using DrawText function</center>
```cplusplus
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

<center>     <img src="%ATTACHURLPATH%/14.2.jpeg" alt="14.2.jpeg"  ALIGN="CENTER" /> </center>
<center>Fig. 14.2 The output of DrawText function</center>

Besides the above output functions, MiniGUI also provides functions listed in Table 14.2, which can be used to set or get the extra space between characters and lines.

<center>Table 14.2 Functions to set/get extra space between characters and lines</center>

<center>
| *Function* | *Meaning* |
| GetTextCharacterExtra | Get the extra space between characters |
| SetTextCharacterExtra | Set the extra space between characters |
| GetTextAboveLineExtra | Get the extra space above line |
| SetTextAboveLineExtra | Set the extra space above line |
| GetTextBellowLineExtra | Get the extra space bellow line |
| SetTextBellowLineExtra | Set the extra space bellow line |

</center>

The more usage of logical font and text output functions is illustrated in fontdemo.c file of mg-samples. 

## 14.7 Special Render Effects of Font Glyph

MiniGUI provides many special effects to render the font glyphs. For example, you can specify the logical font style to render the glyph with bold, italic, underline, and/or struckout line. In version 2.0.3/1.6.9, MiniGUI provides anti-aliased effect by using low-pass filter, to flip the glyph vertically and/or horizontally, and to scale the glyph to meet the desired logical font size when using bitmap font. In version 2.0.4/1.6.10/3.0, MiniGUI provides FreeType2 support, and it makes that user can choose sub-pixel render using FreeType2 or MiniGUI; Before using sub-pixel render, please confirm that you have opened FT_CONFIG_OPTION_SUBPIXEL_RENDERING macro in FreeType2. 

<center>List 14.2 Using sub-pixel render</center>
```cplusplus
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

The render effects are specified through the logical font style when you create the logical font. For example, if you specify FS_WEIGHT_BOOK style, MiniGUI will use low-pass filter to handle the edge of the vectorial font glyph in order to anti-aliase. When MiniGUI scales the font glyph of bitmap font, this style also can be used to anti-aliase. Table 14.3 illustrates the render effects supported by MiniGUI.

<center>Table 14.3 The font glyph render effects of MiniGUI</center>

<center> 
| *Style of logical font* | *Style character in logical font name* | *Style value of logical font* | *Meaning* |
| weight：<br>FONT_WEIGHT_REGULAR | First char is ‘r’ | FS_WEIGHT_REGULAR | No any weight effect |
| weight：<br>FONT_WEIGHT_BOLD | First char is ‘b’ | FS_WEIGHT_BOLD | Bold |
| weight：<br>FONT_WEIGHT_LIGHT | First char is ‘l’ | FS_WEIGHT_LIGHT | To render glyph edge with the background color |
| weight：<br>FONT_WEIGHT_BOOK | First char is ’b’ | FS_WEIGHT_BOOK | To handle to glyph edge by using the low-pass filter to anti-aliase |
| weight：<br>FONT_WEIGHT_DEMIBOLD | Fist char is ‘d’ | FS_WEIGHT_DEMIBOLD | Both FS_WEIGHT_BOLD and FS_WEIGHT_BOOK |
| weight：<br>FONT_WEIGHT_SUBPIXEL | Fist char is ‘s’ | FS_WEIGHT_SUBPIXEL | To handle to glyph by using sub-pixel render |
| slant：<br>FONT_SLANT_ROMAN | Second char is ‘r’ | FONT_SLANT_ROMAN | No any slant effect |
| slant：<br>FONT_SLANT_ITALIC | Second char is ‘i’ | FONT_SLANT_ITALIC | Italic |
| flip：<br>FONT_OTHER_NIL | Third char is any letter but H/V/T | N/A | No any flipping effect |
| flip：<br>FONT_FLIP_HORZ | Third char is ‘H’ | FS_FLIP_HORZ | To flip the glyph horinzontally |
| flip：<br>FONT_FLIP_VERT | Third char is ‘V’ | FS_FLIP_VERT | To flip the glyph vertically |
| flip：<br>FONT_FLIP_HORZVERT | Third char is ‘T’ | FS_FLIP_HORZVERT | Both FS_FLIP_HORZ and FS_FLIP_VERT |
| other：<br>FONT_OTHER_NIL | Forth char is any letter but S/N | N/A | No any other effect |
| other：<br>FONT_OTHER_AUTOSCALE | Forth char is ‘S’ | FS_OTHER_AUTOSCALE | To scale the glyph to meet the desired logical font size, only good for bitmap font. |
| other：<br>FONT_OTHER_TTFNOCACHE | Forth char is ‘N’ | FS_OTHER_TTFNOCACHE | To close the cache when render glyph by using TrueType font.  |
| other：<br>FONT_OTHER_LCDPORTRAIT | Forth char is ‘P’ | FS_OTHER_LCDPORTRAIT | Using portrait LCD when render glyph by using TrueType font.  |
| underline：<br>FONT_UNDERLINE_NONE | Fifth char is ‘n’ | FS_UNDERLINE_NONE | No underline |
| underline：<br>FONT_UNDERLINE_LINE | Fifth char is ‘u’ | FS_UNDERLINE_LINE | Underline |
| struckout：<br>FONT_STRUCKOUT_NONE | Sixth char is ’n’ | FS_STRUCKOUT_NONE | No struckout line |
| struckout：<br>FONT_STRUCKOUT_LINE | Sixth char is ’s’ | FS_STRUCKOUT_LINE | Struckout line |
</center>

The style character given by Table 14.3 can be used to define the logial font name.

## 14.8 Usage of BIDI text

In generally, Latin and many texts store and display from left to right, but some central Asian countries' languages (Arabic) display from right to left. BIDI text problem occurs when these texts are mixed together.

To support BIDI text, please enable related character set and configure the fonts. The following is the example for Arabic font:
- enable iso8859-6 character set support, MiniGUI supports Arabic font in default
- Configure vbf font in MiniGUI configuration file

```cplusplus
[varbitmapfonts]
font_number=1
name0=vbf-naskhi-rrncnn-18-21-ISO8859-6
fontfile0=/usr/local/share/minigui/res/font/naskhi-18-21-iso8859-6.vbf
```

Arabic demo is shown as below:

<center>     <img src="%ATTACHURLPATH%/14.3.jpeg" alt="14.3.jpeg"  ALIGN="CENTER" /> </center>
<center>Fig. 14.3 Arabic font demo</center>


-- Main.XiaodongLi - 07 Nov 2009

