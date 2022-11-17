# 渲染器及资源管理

## 1 外观渲染器

渲染器的全称为“外观渲染器（Look and Feel Renderer）”，它在 MiniGUI 3.0 中发展出来的。

渲染器将窗口的管理逻辑和窗口的绘制分离，MiniGUI 只负责管理窗口，而由渲染器完成窗口非客户区的绘制。渲染器的概念，类似于皮肤或者主题的概念。不同的是：

1. MiniGUI 提供了专门的渲染器接口，由具体的渲染器实现
2. 渲染器由一组接口实现和一组属性定义组成
3. 渲染器可以应用到全局，对所有窗口起效; 也可以应用到一个专门的窗口实例上

MiniGUI 本身提供了一组渲染器接口，这些是基于窗口本身的，属于系统渲染器，或者是全局渲染器；NCS 为每个控件提供了渲染器接口，不同的控件接口不一样，属于控件渲染器。

### 1.1 渲染器公共属性

| 属性                          | 类型                  | 说明        |
|:-----------------------------|:---------------------|:------------|
| `RDR_3DBODY_FGCLR`           | `DWORD`(`MakeRGBA`)  | 3D 对象前景色 |
| `RDR_3DBODY_BGCLR`           | `DWORD`(`MakeRGBA`)  | 3D 对象背景色 |
| `RDR_CLIENT_FGCLR`           | `DWORD`(`MakeRGBA`)  | 窗口客户区前景色 |
| `RDR_CLIENT_BGCLR`           | `DWORD`(`MakeRGBA`)  | 窗口客户区背景色 |
| `RDR_SELECTED_FGCLR`         | `DWORD`(`MakeRGBA`)  | 被选择对象的前景色 |
| `RDR_SELECTED_BGCLR`         | `DWORD`(`MakeRGBA`)  | 被选择对象的背景色 |
| `RDR_SELECTED_LOSTFOCUS_CLR` | `DWORD`(`MakeRGBA`)  | 失去焦点对象的颜色 |
| `RDR_DISABLE_FGCLR`          | `DWORD`(`MakeRGBA`)  | 不可用对象的前景色 |
| `RDR_DISABLE_BGCLR`          | `DWORD`(`MakeRGBA`)  | 不可用对象的背景色 |
| `RDR_HIGHLIGHT_FGCLR`        | `DWORD`(`MakeRGBA`)  | 高亮对象的前景色 |
| `RDR_HIGHLIGHT_BGCLR`        | `DWORD`(`MakeRGBA`)  | 高亮对象的背景色 |
| `RDR_METRICS_BORDER`         |  int                 | 边框的大小值 |
| `RDR_FONT`                   | `PLOGFONT`           | 窗口使用的逻辑字体 |
| `RDR_BKIMAGE`                | `PBITMAP`            | 窗口背景图片 |
| `RDR_BKIMAGE_MODE`           | `enum ImageDrawMode` | 窗口绘制模式 |

## 2 资源管理

在新控件集中，资源管理模块作为一个独立的模块，主要负责对资源包进行管理，其中包括资源包的装载、访问和卸载等功能。它在访问资源时是通过指定资源所在的资源包和资源的唯一标识符（ID）等信息来获取所需要的内容 。

其中资源包是为了将各种资源有效地统一管理，统一资源与资源标识符（ID）的映射而提出的概念。一个资源包内可以包含多种资源类型，如图片、字符串、UI 资源等等。资源包为资源的管理带来了诸多如下好处。

在了解资源管理前，需要了解下面两个基础概念：

- 资源包 : 资源的集合，任意种类和任意个数的资源集合，是资源替换的最小单位。
- 资源 ID : 访问资源包内某一资源的唯一标识。

mGNCS 提供的资源管理模块，相比较 MiniGUI 固有控件集来讲，具有诸多的优势。如：

- 资源管理与应用代码的分离。 
- 统一了各种资源的管理接口，访问资源更加便捷。
- 通过资源包的简单替换即可实现多语言，多风格，换肤等效果。
- 资源部署更加简单。
- 配合可视化工具 mStudio，方便地生成包含各类资源描述的资源包。

mGNCS 的资源管理主要是围绕资源包来实现对资源的各种管理和访问的。如果要正确的访问某个资源，只需要知道其所在的资源包和对应的资源 ID。整体访问流程通常为：

1. 装载指定资源包。
2. 通过资源 ID 获取资源。
3. 使用资源，某些资源需要在使用后释放资源。
4. 卸载资源包。

当前资源包支持的资源类型有：

| 资源类型 ID     | 说明        | 备注      |
|:---------------|:-----------|:---------|
| `NCSRT_UI`     | UI 窗口资源 | 对主窗口和控件的描述信息。如窗口风格、大小、标题和属性等。|
| `NCSRT_STRING` | 字符串资源  | 文件名、渲染器名和控件类名等固定的系统常量字符串。 |
| `NCSRT_TEXT`   | 文本资源    | UI 界面上用户指定的文本字符串及 locale 信息。| 
| `NCSRT_IMAGE`  | 图片资源    | 各种 bmp, png 和 jpg 等图片信息。|
| `NCSRT_RDR`    | 渲染器资源   | 对指定的窗口渲染器的窗口元素外观属性的设置信息。|
| `NCSRT_RDRSET` | 渲染器集资源 | 同类渲染器资源的集合。|
| `NCSRT_BINARY` | 自定义资源   | 自定义格式的资源。 |

### 2.1 资源接口
#### 2.1.1 访问资源包

资源包分为内建格式和外部文件 2 种，无论哪一种都应在系统启动时首先装载资源包，然后访问内部资源，最后系统退出后将资源包正确卸载。在访问非内建资源包时需要使用到如下接口：

```c
HPACKAGE ncsLoadResPackageFromFile (const char* fileName);
#define ncsLoadResPackage  ncsLoadResPackageFromFile
void ncsUnloadResPackage (HPACKAGE package);
```

其中 `ncsLoadResPackage` 负责装载资源包，`ncsUnloadResPackage` 负责卸载资源包。二者需要成对使用。

如果需要装载的资源包是内建的内存格式，则需要首先通过获取内存资源包信息接口（`ncsGetIncoreResPackInfo`），将内存资源包具体信息返回，然后使用从内存装载资源包的接口（`ncsLoadResPackageFromMem`）装载资源包，最后使用上面提供的同一卸载接口（`ncsUnloadResPackage`）卸载资源包。其中 `ncsGetIncoreResPackInfo` 接口是由内建转换工具所提供，使用内建工具将指定资源包文件转换为内建资源时即已生成，应用无须关心其实现。

```c
extern BOOL ncsGetIncoreResPackInfo(char **addr, int *size);
HPACKAGE ncsLoadResPackageFromMem (const void* mem, int size);
```

这是装载资源包文件的示例代码：

```c
sprintf(f_package, "%s", "resmgr_demo.res");
SetResPath("./");

hPackage = ncsLoadResPackage (f_package);
if (hPackage == HPACKAGE_NULL) {
        printf ("load resource package:%s failure.\n", f_package);
        return 1;
}
```

这是卸载资源包文件的示例代码：

```c
ncsUnloadResPackage(hPackage);
```

#### 2.1.2 获取与设置 Locale

为了方便的进行 locale 的设置与获取，资源管理模块提供了下面两个接口：

```c
const char* ncsSetDefaultLocale (char* language, char* country);
const char* ncsGetDefaultLocale(void);
```

其中设置接口仅对在其设置后通过资源包获取的资源有效，2 个参量分别代表代码语言和国家代码：

- language 语言代码用2个英文小写字母来表示。
- country 国家代码需要用 2 个或 3 个英文小写字母来表示。

如设置美式英文为默认 locale，可通过如下语句完成：

```c
ncsSetDefaultLocale("en", "US");
```

获取接口返回当前使用的 locale 信息，该信息的格式为：`language_country`。

`ISO639` 语言代码对照表

```
ISO 639 Codes(Languages)

Two-letter lower-case symbols are used.

aa Afar
ab Abkhazian
af Afrikaans
am Amharic
ar Arabic
as Assamese
ay Aymara
az Azerbaijani

ba Bashkir
be Byelorussian
bg Bulgarian
bh Bihari
bi Bislama
bn Bengali; Bangla
bo Tibetan
br Breton

ca Catalan
co Corsican
cs Czech
cy Welsh

da Danish
de German
dz Bhutani

el Greek
en English
eo Esperanto
es Spanish
et Estonian
eu Basque

fa Persian
fi Finnish
fj Fiji
fo Faroese
fr French
fy Frisian

ga Irish
gd Scots Gaelic
gl Galician
gn Guarani
gu Gujarati

ha Hausa
he Hebrew (formerly iw)
hi Hindi
hr Croatian
hu Hungarian
hy Armenian

ia Interlingua
id Indonesian (formerly in)
ie Interlingue
ik Inupiak
is Icelandic
it Italian
iu Inuktitut

ja Japanese
jw Javanese

ka Georgian
kk Kazakh
kl Greenlandic
km Cambodian
kn Kannada
ko Korean
ks Kashmiri
ku Kurdish
ky Kirghiz

la Latin
ln Lingala
lo Laothian
lt Lithuanian
lv Latvian, Lettish

mg Malagasy
mi Maori
mk Macedonian
ml Malayalam
mn Mongolian
mo Moldavian
mr Marathi
ms Malay
mt Maltese
my Burmese

na Nauru
ne Nepali
nl Dutch
no Norwegian

oc Occitan
om (Afan) Oromo
or Oriya

pa Punjabi
pl Polish
ps Pashto, Pushto
pt Portuguese

qu Quechua

rm Rhaeto-Romance
rn Kirundi
ro Romanian
ru Russian
rw Kinyarwanda

sa Sanskrit
sd Sindhi
sg Sangho
sh Serbo-Croatian
si Sinhalese
sk Slovak
sl Slovenian
sm Samoan
sn Shona
so Somali
sq Albanian
sr Serbian
ss Siswati
st Sesotho
su Sundanese
sv Swedish
sw Swahili

ta Tamil
te Telugu
tg Tajik
th Thai
ti Tigrinya
tk Turkmen
tl Tagalog
tn Setswana
to Tonga
tr Turkish
ts Tsonga
tt Tatar
tw Twi

ug Uighur
uk Ukrainian
ur Urdu
uz Uzbek

vi Vietnamese
vo Volapuk

wo Wolof

xh Xhosa

yi Yiddish (formerly ji)
yo Yoruba

za Zhuang
zh Chinese
zu Zulu
```

`ISO3166` 国家代码对照表

```
ISO 3166 Codes (Countries)

Country                                         A 2     A 3     Number
----------------------------------------------------------------------
AALAND ISLANDS                                  AX      ALA     248
AFGHANISTAN                                     AF      AFG     004
ALBANIA                                         AL      ALB     008
ALGERIA                                         DZ      DZA     012
AMERICAN SAMOA                                  AS      ASM     016
ANDORRA                                         AD      AND     020
ANGOLA                                          AO      AGO     024
ANGUILLA                                        AI      AIA     660
ANTARCTICA                                      AQ      ATA     010
ANTIGUA AND BARBUDA                             AG      ATG     028
ARGENTINA                                       AR      ARG     032
ARMENIA                                         AM      ARM     051  
ARUBA                                           AW      ABW     533
AUSTRALIA                                       AU      AUS     036
AUSTRIA                                         AT      AUT     040
AZERBAIJAN                                      AZ      AZE     031  
BAHAMAS                                         BS      BHS     044
BAHRAIN                                         BH      BHR     048
BANGLADESH                                      BD      BGD     050
BARBADOS                                        BB      BRB     052
BELARUS                                         BY      BLR     112  
BELGIUM                                         BE      BEL     056
BELIZE                                          BZ      BLZ     084
BENIN                                           BJ      BEN     204
BERMUDA                                         BM      BMU     060
BHUTAN                                          BT      BTN     064
BOLIVIA                                         BO      BOL     068
BOSNIA AND HERZEGOWINA                          BA      BIH     070
BOTSWANA                                        BW      BWA     072
BOUVET ISLAND                                   BV      BVT     074
BRAZIL                                          BR      BRA     076
BRITISH INDIAN OCEAN TERRITORY                  IO      IOT     086
BRUNEI DARUSSALAM                               BN      BRN     096
BULGARIA                                        BG      BGR     100
BURKINA FASO                                    BF      BFA     854
BURUNDI                                         BI      BDI     108
CAMBODIA                                        KH      KHM     116
CAMEROON                                        CM      CMR     120
CANADA                                          CA      CAN     124
CAPE VERDE                                      CV      CPV     132
CAYMAN ISLANDS                                  KY      CYM     136
CENTRAL AFRICAN REPUBLIC                        CF      CAF     140
CHAD                                            TD      TCD     148
CHILE                                           CL      CHL     152
CHINA                                           CN      CHN     156
CHRISTMAS ISLAND                                CX      CXR     162
COCOS (KEELING) ISLANDS                         CC      CCK     166
COLOMBIA                                        CO      COL     170
COMOROS                                         KM      COM     174
CONGO, Democratic Republic of (was Zaire)       CD      COD     180
CONGO, Republic of                              CG      COG     178
COOK ISLANDS                                    CK      COK     184
COSTA RICA                                      CR      CRI     188
COTE D'IVOIRE                                   CI      CIV     384
CROATIA (local name: Hrvatska)                  HR      HRV     191      
CUBA                                            CU      CUB     192
CYPRUS                                          CY      CYP     196
CZECH REPUBLIC                                  CZ      CZE     203  
DENMARK                                         DK      DNK     208
DJIBOUTI                                        DJ      DJI     262
DOMINICA                                        DM      DMA     212
DOMINICAN REPUBLIC                              DO      DOM     214
ECUADOR                                         EC      ECU     218
EGYPT                                           EG      EGY     818
EL SALVADOR                                     SV      SLV     222
EQUATORIAL GUINEA                               GQ      GNQ     226
ERITREA                                         ER      ERI     232
ESTONIA                                         EE      EST     233  
ETHIOPIA                                        ET      ETH     231
FALKLAND ISLANDS (MALVINAS)                     FK      FLK     238
FAROE ISLANDS                                   FO      FRO     234
FIJI                                            FJ      FJI     242
FINLAND                                         FI      FIN     246
FRANCE                                          FR      FRA     250
FRENCH GUIANA                                   GF      GUF     254
FRENCH POLYNESIA                                PF      PYF     258
FRENCH SOUTHERN TERRITORIES                     TF      ATF     260
GABON                                           GA      GAB     266
GAMBIA                                          GM      GMB     270
GEORGIA                                         GE      GEO     268  
GERMANY                                         DE      DEU     276
GHANA                                           GH      GHA     288
GIBRALTAR                                       GI      GIB     292
GREECE                                          GR      GRC     300
GREENLAND                                       GL      GRL     304
GRENADA                                         GD      GRD     308
GUADELOUPE                                      GP      GLP     312
GUAM                                            GU      GUM     316
GUATEMALA                                       GT      GTM     320
GUINEA                                          GN      GIN     324
GUINEA-BISSAU                                   GW      GNB     624
GUYANA                                          GY      GUY     328
HAITI                                           HT      HTI     332
HEARD AND MC DONALD ISLANDS                     HM      HMD     334
HONDURAS                                        HN      HND     340
HONG KONG                                       HK      HKG     344
HUNGARY                                         HU      HUN     348
ICELAND                                         IS      ISL     352
INDIA                                           IN      IND     356
INDONESIA                                       ID      IDN     360
IRAN (ISLAMIC REPUBLIC OF)                      IR      IRN     364
IRAQ                                            IQ      IRQ     368
IRELAND                                         IE      IRL     372
ISRAEL                                          IL      ISR     376
ITALY                                           IT      ITA     380
JAMAICA                                         JM      JAM     388
JAPAN                                           JP      JPN     392
JORDAN                                          JO      JOR     400
KAZAKHSTAN                                      KZ      KAZ     398  
KENYA                                           KE      KEN     404
KIRIBATI                                        KI      KIR     296
KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF          KP      PRK     408
KOREA, REPUBLIC OF                              KR      KOR     410
KUWAIT                                          KW      KWT     414
KYRGYZSTAN                                      KG      KGZ     417  
LAO PEOPLE'S DEMOCRATIC REPUBLIC                LA      LAO     418
LATVIA                                          LV      LVA     428  
LEBANON                                         LB      LBN     422
LESOTHO                                         LS      LSO     426
LIBERIA                                         LR      LBR     430
LIBYAN ARAB JAMAHIRIYA                          LY      LBY     434
LIECHTENSTEIN                                   LI      LIE     438
LITHUANIA                                       LT      LTU     440  
LUXEMBOURG                                      LU      LUX     442
MACAU                                           MO      MAC     446
MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF      MK      MKD     807 
MADAGASCAR                                      MG      MDG     450
MALAWI                                          MW      MWI     454
MALAYSIA                                        MY      MYS     458
MALDIVES                                        MV      MDV     462
MALI                                            ML      MLI     466
MALTA                                           MT      MLT     470
MARSHALL ISLANDS                                MH      MHL     584
MARTINIQUE                                      MQ      MTQ     474
MAURITANIA                                      MR      MRT     478
MAURITIUS                                       MU      MUS     480
MAYOTTE                                         YT      MYT     175  
MEXICO                                          MX      MEX     484
MICRONESIA, FEDERATED STATES OF                 FM      FSM     583
MOLDOVA, REPUBLIC OF                            MD      MDA     498  
MONACO                                          MC      MCO     492
MONGOLIA                                        MN      MNG     496
MONTSERRAT                                      MS      MSR     500
MOROCCO                                         MA      MAR     504
MOZAMBIQUE                                      MZ      MOZ     508
MYANMAR                                         MM      MMR     104
NAMIBIA                                         NA      NAM     516
NAURU                                           NR      NRU     520
NEPAL                                           NP      NPL     524
NETHERLANDS                                     NL      NLD     528
NETHERLANDS ANTILLES                            AN      ANT     530
NEW CALEDONIA                                   NC      NCL     540
NEW ZEALAND                                     NZ      NZL     554
NICARAGUA                                       NI      NIC     558
NIGER                                           NE      NER     562
NIGERIA                                         NG      NGA     566
NIUE                                            NU      NIU     570
NORFOLK ISLAND                                  NF      NFK     574
NORTHERN MARIANA ISLANDS                        MP      MNP     580
NORWAY                                          NO      NOR     578
OMAN                                            OM      OMN     512
PAKISTAN                                        PK      PAK     586
PALAU                                           PW      PLW     585
PALESTINIAN TERRITORY, Occupied                 PS      PSE     275
PANAMA                                          PA      PAN     591
PAPUA NEW GUINEA                                PG      PNG     598
PARAGUAY                                        PY      PRY     600
PERU                                            PE      PER     604
PHILIPPINES                                     PH      PHL     608
PITCAIRN                                        PN      PCN     612
POLAND                                          PL      POL     616
PORTUGAL                                        PT      PRT     620
PUERTO RICO                                     PR      PRI     630
QATAR                                           QA      QAT     634
REUNION                                         RE      REU     638
ROMANIA                                         RO      ROU     642
RUSSIAN FEDERATION                              RU      RUS     643
RWANDA                                          RW      RWA     646
SAINT HELENA                                    SH      SHN     654
SAINT KITTS AND NEVIS                           KN      KNA     659
SAINT LUCIA                                     LC      LCA     662
SAINT PIERRE AND MIQUELON                       PM      SPM     666
SAINT VINCENT AND THE GRENADINES                VC      VCT     670
SAMOA                                           WS      WSM     882
SAN MARINO                                      SM      SMR     674
SAO TOME AND PRINCIPE                           ST      STP     678
SAUDI ARABIA                                    SA      SAU     682
SENEGAL                                         SN      SEN     686
SERBIA AND MONTENEGRO                           CS      SCG     891
SEYCHELLES                                      SC      SYC     690
SIERRA LEONE                                    SL      SLE     694
SINGAPORE                                       SG      SGP     702
SLOVAKIA                                        SK      SVK     703  
SLOVENIA                                        SI      SVN     705  
SOLOMON ISLANDS                                 SB      SLB     090
SOMALIA                                         SO      SOM     706
SOUTH AFRICA                                    ZA      ZAF     710
SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS    GS      SGS     239
SPAIN                                           ES      ESP     724
SRI LANKA                                       LK      LKA     144
SUDAN                                           SD      SDN     736
SURINAME                                        SR      SUR     740
SVALBARD AND JAN MAYEN ISLANDS                  SJ      SJM     744
SWAZILAND                                       SZ      SWZ     748
SWEDEN                                          SE      SWE     752
SWITZERLAND                                     CH      CHE     756
SYRIAN ARAB REPUBLIC                            SY      SYR     760
TAIWAN                                          TW      TWN     158
TAJIKISTAN                                      TJ      TJK     762  
TANZANIA, UNITED REPUBLIC OF                    TZ      TZA     834
THAILAND                                        TH      THA     764
TIMOR-LESTE                                     TL      TLS     626
TOGO                                            TG      TGO     768
TOKELAU                                         TK      TKL     772
TONGA                                           TO      TON     776
TRINIDAD AND TOBAGO                             TT      TTO     780
TUNISIA                                         TN      TUN     788
TURKEY                                          TR      TUR     792
TURKMENISTAN                                    TM      TKM     795  
TURKS AND CAICOS ISLANDS                        TC      TCA     796
TUVALU                                          TV      TUV     798
UGANDA                                          UG      UGA     800
UKRAINE                                         UA      UKR     804
UNITED ARAB EMIRATES                            AE      ARE     784
UNITED KINGDOM                                  GB      GBR     826
UNITED STATES                                   US      USA     840
UNITED STATES MINOR OUTLYING ISLANDS            UM      UMI     581
URUGUAY                                         UY      URY     858
UZBEKISTAN                                      UZ      UZB     860  
VANUATU                                         VU      VUT     548
VATICAN CITY STATE (HOLY SEE)                   VA      VAT     336
VENEZUELA                                       VE      VEN     862
VIET NAM                                        VN      VNM     704
VIRGIN ISLANDS (BRITISH)                        VG      VGB     092
VIRGIN ISLANDS (U.S.)                           VI      VIR     850
WALLIS AND FUTUNA ISLANDS                       WF      WLF     876
WESTERN SAHARA                                  EH      ESH     732
YEMEN                                           YE      YEM     887
ZAMBIA                                          ZM      ZMB     894
ZIMBABWE                                        ZW      ZWE     716
```

#### 2.1.3 创建窗口 UI

在使用资源包的情况下，mGNCS 所提供的创建主窗口接口相对于 MiniGUI 的创建主窗口来说更加简单，对于主窗口的外观信息描述均已保存于资源包内，接口只需通过窗口资源 ID 即可将界面启动。其中：

- `owner` 参数指的是窗口的拖管窗口；
- `hIcon`, `hMenu` 默认为 0 即可； 
- `handlers` 和 `connects` 是用户自定义的与该窗口资源 ID 相关联的事件侦听和连接；
- `user_data` 为附加数据，默认为 0 即可。

```c 
mMainWnd* ncsCreateMainWindowIndirectFromID (HPACKAGE package,
                    Uint32 wndId, HWND owner, HICON hIcon,
                    HMENU hMenu, NCS_EVENT_HANDLER_INFO* handlers,
                    NCS_EVENT_CONNECT_INFO *connects,
                    DWORD user_data);
```

对于通过窗口资源 ID 创建对话框的方法类似于主窗口，通过资源 ID 创建界面，参数含义也与上面创建主窗口的接口类似：

```c
int ncsCreateModalDialogFromID (HPACKAGE package, Uint32 dlgId,
                    HWND owner, HICON hIcon, HMENU hMenu,
                    NCS_EVENT_HANDLER_INFO* handlers, NCS_EVENT_CONNECT_INFO *connects);
```

通过资源包创建 UI 主窗口的示例代码：

```c
return ncsCreateMainWindowIndirectFromID(package,
    ID_MAINWND1,
    hParent,
    h_icon,
    h_menu,
    mainwnd_Mainwnd1_handlers,
    NULL,
    user_data);
```

#### 2.1.4 获取字符串

通过资源包获取字符串的方法很简单，只需要将资源 ID 传递给接口 `ncsGetString`，管理模块即会根据当前的 locale 信息，将默认 locale 的字符串返回给应用。

```c
const char* ncsGetString (HPACKAGE package, Uint32 resId);
```

通过资源包获取字符串的示例代码：

```c
SetDefaultWindowElementRenderer(ncsGetString(hPackage, NCSRM_SYSSTR_DEFRDR));
```

- 注：mGNCS 保留从 `NCSRM_SYSSTR_BASEID` 到 `NCSRM_SYSSTR_MAXID` 的 ID 值作为系统 ID，可以返回公共的定义，如默认渲染器：`NCSRM_SYSSTR_DEFRDR`

#### 2.1.5 获取位图

资源管理模块提供了通过位图 ID 获取相应文件名的功能，便于上层应用在获取文件名后直接使用 MiniGUI 提供的位图装载相关接口操作位图：

```c
const char* ncsGetImageFileName (HPACKAGE package, Uint32 resId);
```

除了使用 MiniGUI 相关接口访问位图外， mGNCS 还提供了直接通过资源 ID 获取位图对象的接口，上层应用使用完该接口提供的位图资源后，需通过相对应的释放接口释放位图对象。这对设置无关和设置相关位图都有效。

```c
//设置相关位图接口
int ncsGetBitmap(HDC hdc, HPACKAGE package, Uint32 resId,  PBITMAP pBitmap);
void ncsReleaseBitmap (PBITMAP pBitmap);

//设置无关位图接口
int ncsGetMyBitmap(HPACKAGE package, Uint32 resId,
        PMYBITMAP myBmp, RGB* pal);
void ncsReleaseMyBitmap (PMYBITMAP myBmp);
```

#### 2.1.6 设置渲染器

通过资源包中所包含的渲染器 ID 可以对指定的窗口进行设置，使其具有该渲染器配置下的窗口元素外观属性。但该接口仅在当前窗口所使用的渲染器与新设置的渲染器同名，并且该窗口类是新渲染器所属控件类的子类时方可生效，否则将返回失败，设置不成功。

```c
BOOL ncsSetWinRdr(HWND hWnd, HPACKAGE package, Uint32 rdrId);
```

另外还可以通过渲染器集合资源设置将某一渲染器集合作为默认系统渲染器配置。

```c
BOOL ncsSetSysRdr(HPACKAGE package, Uint32 rdrSetId);
```

### 2.2 示例程序

本实例为用户演示了如何使用资源管理部分接口获取资源。该部分代码由 mStudio 工具自动生成。

![resmgr 程序的输出](figures/Part2Chapter03-01.jpeg)

图 1  resmgr 程序的输出

该程序在屏幕上创建一个包含 2 个按钮的 300x250 的对话框，其中主窗口是 classic 渲染器的外观效果，2 个按钮分别是 skin 和 flat 渲染器的外观效果。

__清单 1__  resmgr_main.c

```c
/*
** $Id: resmgr_main.c 534 2009-09-22 05:37:46Z xwyan $
**
** Listing P2C2.2
**
** resmgr_main.c: Sample program for mGNCS Programming Guide
**      The application entry of resource managerment.
**
** Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>

#include "resource.h"
#include "ncs-windows.h"

HPACKAGE hPackage = HPACKAGE_NULL;

int MiniGUIMain(int argc, const char* argv[])
{
        #ifdef ntStartWindowEx
        MSG Msg;
        char f_package[MAX_PATH];
        mMainWnd *mWin;
        
        ncsInitialize();
        // START_OF_LOADRESPKG
        sprintf(f_package, "%s", "resmgr_demo.res");
        SetResPath("./");
        
        hPackage = ncsLoadResPackage (f_package);
        if (hPackage == HPACKAGE_NULL) {
                printf ("load resource package:%s failure.\n", f_package);
                return 1;
        }
        // END_OF_LOADRESPKG
        
        // START_OF_GETSTRING
        SetDefaultWindowElementRenderer(ncsGetString(hPackage, NCSRM_SYSSTR_DEFRDR));
        // END_OF_GETSTRING
        
        mWin = ntStartWindowEx(hPackage, HWND_DESKTOP, (HICON)0, (HMENU)0, (DWORD)0);
        
        while(GetMessage(&Msg, mWin->hwnd))
        {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
        }
        
        MainWindowThreadCleanup(mWin->hwnd);
        // START_OF_UNLOADPKG
        ncsUnloadResPackage(hPackage);
        // END_OF_UNLOADPKG
        ncsUninitialize();
        #endif
        
        return 0;
}
```

__清单 1__  resmgr.c

```c
/*
** $Id: resmgr.c 534 2009-09-22 05:37:46Z xwyan $
**
** Listing P2C2.3
**
** resmgr.c: Sample program for mGNCS Programming Guide
**      Create main window by resource managerment.
**
** Copyright (C) 2009 Feynman Software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>

#include "resource.h"
#include "ncs-windows.h"

static NCS_EVENT_HANDLER_INFO mainwnd_Mainwnd1_handlers[] = {
        
        {-1, NULL}
};

NCS_WND_EXPORT mMainWnd* ntCreateMainwnd1Ex(HPACKAGE package, HWND hParent, HICON h_icon, HMENU h_menu, DWORD user_data)
{
        // START_OF_UIWINDOW
        return ncsCreateMainWindowIndirectFromID(package,
        ID_MAINWND1, 
        hParent,
        h_icon,
        h_menu,
        mainwnd_Mainwnd1_handlers,
        NULL,
        user_data);
        // END_OF_UIWINDOW
}
```
