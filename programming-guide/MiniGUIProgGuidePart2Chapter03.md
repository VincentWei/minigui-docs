# Renderer and Resources Management

## Look and Feel Renderer

The full name of renderer is “look and feel renderer”, which is developed from
MiniGUI 3.0.

Renderer separates the management logic of window from drawing of window.
`MiniGUi` is only responsible for managing window, while renderer finishes
drawing of window non-client area. Concept of renderer is similar to the
concept of skin or theme. The differences are:
1. MiniGUI provides special renderer interface, which is implemented by
concrete renderer
1. Renderer is composed of a group of interface realizations and a group of
property definitions
1. Renderer can be applied to the global, having effect on all the windows; it
can also be applied to a special window instance

MiniGUI itself provides a group of renderer interfaces, which are based on the
window itself, and known as the category of system renderer or global renderer.
mGNCS provides renderer interface for each control, and different controls have
different interfaces. It falls into the category of control renderer.

### Common properties of the Renderer

| *Property* | *Type* | *Explanation* |
|------------|--------|---------------|
| `RDR_3DBODY_FGCLR` | `DWORD` (`MakeRGBA`) | 3D object foreground color |
| `RDR_3DBODY_BGCLR` | `DWORD` (`MakeRGBA`) | 3D object background color |
| `RDR_CLIENT_FGCLR` | `DWORD` (`MakeRGBA` | Window client area foreground color |
| `RDR_CLIENT_BGCLR` | `DWORD` (`MakeRGBA` | Window client area background color |
| `RDR_SELECTED_FGCLR` | `DWORD` (`MakeRGBA`) | Foreground color of the selected object |
| `RDR_SELECTED_BGCLR` | `DWORD` (`MakeRGBA`) | Background color of the selected object |
| `RDR_SELECTED_LOSTFOCUS_CLR` | `DWORD` (`MakeRGBA`) | Color of the object losing focus |
| `RDR_DISABLE_FGCLR` | `DWORD` (`MakeRGBA`) | Foreground color of disabled object |
| `RDR_DISABLE_BGCLR` | `DWORD` (`MakeRGBA`) | Background color of disabled object |
| `RDR_HIGHLIGHT_FGCLR` | `DWORD` (`MakeRGBA`) | Foreground color of the highlighted object |
| `RDR_HIGHLIGHT_BGCLR` | `DWORD` (`MakeRGBA`) | Background color of the highlighted object |
| `RDR_METRICS_BORDER` | int | Border Size |
| `RDR_FONT` | `PLOGFONT` | Logic font used by the window |
| `RDR_BKIMAGE` | `PBITMAP` | Window background image |
| `RDR_BKIMAGE_MODE` | `enum ImageDrawMode` | Window drawing mode |

## Resources Management

In the new control set, as an independent module, resources management module
is mainly responsible for managing the resource package, including the
functions of loading, accessing and unloading the resource package. When it
accesses the resources, it gets the content needed through appointing the
resource package where the resource lies in and information such as the unique
identifier (ID) of the resource etc.

Resource package is the concept brought forward in order to manage all kinds of
resources effectively in a unified way and unifying the mapping of resource and
resource identifier (ID). A resource package can contain multiple kinds of
resource types, such as image, string and UI resource etc. Resource package
brings the following advantages to the management of resources.

Before understanding resources management, it is necessary to understand the
following two basic concepts:
- *Resource package* : Set of resources, resource set of any kind and any
number, which is the minimum unit of resource replacement.
- *Resource ID*: Unique identifier for accessing certain resource in the
resource package.

Compared to MiniGUI intrinsic control set, resources management module provided
by mGNCS has many advantages. For example:
- Separation of resources management from application codes.
- Management interfaces of all kinds of resources are unified, making it more
convenient and rapid to access resources is.
- Through simple replacement of resource package, effects can be realized, such
as multi-language, multi-style and skin change etc. .
- Resources deployment is simpler.
- Matched with visual tool miniStudio, it is convenient to generate resource
package containing all kinds of resources.

Resources management of mGNCS mainly implements all kinds of management and
accessing to resources surrounding the resource package. If you want to access
certain resource correctly, you only need to know the resource package where it
is and corresponding resource ID. The overall accessing process is normally:
1. Load the specified resource package.
1. Get resource through resource ID.
1. Use resource, for certain resources, it is necessary to release the resource
after use.
1. Unload resource package

Resource types that the current resource package supports are:

| *Resource Type ID* | *Explanation* | *Remark* |
|--------------------|---------------|----------|
| `NCSRT_UI` | UI window resource | Description information of the main window and control, such as window style, size, title and property etc |
| `NCSRT_STRING` | String resource | Fixed system constant string such as file name, renderer name and control class name etc |
| `NCSRT_TEXT` | Text resource | Text string and locale information specified by the user on UI interface |
| `NCSRT_IMAGE` | Image resource | Information of bmp, png and jpg images |
| `NCSRT_RDR` | Renderer resource | Information of setting the window element look and feel properties of the specified window renderer |
| `NCSRT_RDRSET` | Renderer set resource | Set of renderer resources of the same class |
| `NCSRT_BINARY` | User defined resource | Resource of user defined format |

### Resource Interface

#### Access Resource Package

Resource package is divided into built-in format and external file. No matter
which, it is necessary to firstly load resource package when the system starts,
and then access the internal resource, and finally unload the resource package
correctly after the system exits,. When accessing non built-in resource
package, it is necessary to use the following interfaces:

```cpp
HPACKAGE ncsLoadResPackageFromFile (const char* fileName);
#define ncsLoadResPackage  ncsLoadResPackageFromFile
void ncsUnloadResPackage (HPACKAGE package);
```

`ncsLoadResPackage` is responsible for loading resource package, and
`ncsUnloadResPackage` is responsible for unloading resource package. The two
need to be used in pairs.

If the resource package that need to be loaded is built-in memory format, it is
necessary to firstly get memory resource package information interface
(`ncsGetIncoreResPackInfo`), return the concrete information of the memory
resource package, and then use the interface (`ncsLoadResPackageFromMem`) loading
resource package from the memory to load resource package, and finally use the
same unload interface (`ncsUnloadResPackage`) as provided above to unload
resource package. `NcsGetIncoreResPackInfo` interface is provided by built-in
conversion tool, which is generated when using the built-in tool to convert the
specified resource package file to built-in resource, and application does not
need to care about its realization.

```cpp
extern BOOL ncsGetIncoreResPackInfo(char **addr, int *size);
HPACKAGE ncsLoadResPackageFromMem (const void* mem, int size);
```

These are the example codes of loading resource package file:

```cpp
    sprintf(f_package, "%s", "resmgr_demo.res");
    SetResPath("./");

    hPackage = ncsLoadResPackage (f_package);
    if (hPackage == HPACKAGE_NULL) {
        printf ("load resource package:%s failure.\n", f_package);
        return 1;
    }
```

These are the example codes of unloading resource package file:

```cpp
    ncsUnloadResPackage(hPackage);
```

#### Get and Set Locale

To set and get locale conveniently, resource management module provides the
following two interfaces:

```cpp
const char* ncsSetDefaultLocale (char* language, char* country);
const char* ncsGetDefaultLocale(void);
```

The setting interface is only valid to the resource got through the resource
package after setting, and the two parameters represent the language code and
country code:
- language code is represented by two English lower case letters.
- country code needs to be represented by two to three English lower case
letters.

If setting American English as default locale, it can be implemented through
the following statement:

```cpp
ncsSetDefaultLocale("en", "US");
```

The getting interface returns current locale information, and format of the
information is: `language_country`.

`ISO639` Language Codes Comparison Table:

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

`ISO3166` Country Codes Comparison Table:

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

#### Create Window UI

When the resource package is used, the creating main window interface provided
by mGNCS is more simple compared to creating main window of MiniGUI.
Description of the look and feel information of the main window is stored in
the resource package, and the interface can start the interface through window
resource ID.
- owner parameter refers to the hosting window;
- For `hIcon` and `hMenu`, 0 by default;
- handlers and connects are the event listening and connection associated with
the window resource ID defined by the user;
- `user_data` is additional data, 0 by default.

```cpp
mMainWnd* ncsCreateMainWindowIndirectFromID (HPACKAGE package,
                    Uint32 wndId, HWND owner, HICON hIcon,
                    HMENU hMenu, NCS_EVENT_HANDLER_INFO* handlers,
                    NCS_EVENT_CONNECT_INFO *connects,
                    DWORD user_data);
```

The method of creating dialog box through window resource ID is similar to
the main window. Creating interface through resource ID, the parameter
meaning is also similar to the interface of the main window created above:

```cpp
int ncsCreateModalDialogFromID (HPACKAGE package, Uint32 dlgId,
                    HWND owner, HICON hIcon, HMENU hMenu,
                    NCS_EVENT_HANDLER_INFO* handlers, NCS_EVENT_CONNECT_INFO *connects);
```

Create example codes of UI main window through the resource package:

```cpp
    return ncsCreateMainWindowIndirectFromID(package,
        ID_MAINWND1,
        hParent,
        h_icon,
        h_menu,
        mainwnd_Mainwnd1_handlers,
        NULL,
        user_data);
```

#### Get Character String

The method of getting string through resource package is very simple. It is
only necessary to transfer the resource ID to interface `ncsGetString`, and
the management module will return the default locale string to the application
according to the current locale information.

```cpp
const char* ncsGetString (HPACKAGE package, Uint32 resId);
```

Get example codes of string through resource package:

```cpp
    SetDefaultWindowElementRenderer(ncsGetString(hPackage, NCSRM_SYSSTR_DEFRDR));
```

- Note: mGNCS reserves the ID value from `NCSRM_SYSSTR_BASEID` to
`NCSRM_SYSSTR_MAXID` as the system ID, and public definitions can be
returned, such as default renderer: `NCSRM_SYSSTR_DEFRDR`

#### Get Bitmap

Resources management module provides the function of getting corresponding file
name through bitmap ID, making it convenient for the upper layer applications
to directly use the bitmap provided by MiniGUI to load related interface
operation bitmap after getting the file name:

```cpp
const char* ncsGetImageFileName (HPACKAGE package, Uint32 resId);
```

Besides using MiniGUI related interface to access the bitmap, mGNCS also
provides the interface to get bitmap object directly through resource ID.
After the upper layer applications use the bitmap resource provided by the
interface, it is necessary to release the bitmap object through corresponding
release interface. This is valid for setting independent bitmap and setting
dependant bitmap.

```cpp
//Set dependant bitmap interface
int ncsGetBitmap(HDC hdc, HPACKAGE package, Uint32 resId,  PBITMAP pBitmap);
void ncsReleaseBitmap (PBITMAP pBitmap);

//Set independant bitmap interface
int ncsGetMyBitmap(HPACKAGE package, Uint32 resId,
        PMYBITMAP myBmp, RGB* pal);
void ncsReleaseMyBitmap (PMYBITMAP myBmp);
```

#### Set Renderer

Through renderer ID contained in the resource pack, specified window can be
set, making it has the window element look and feel property under the renderer
configuration. But only the renderer used in the current window by the
interface has the same name as the newly set renderer, and it can be valid only
when the window class is the child class of the new renderer affiliated control
class, otherwise failure will be returned, and the setting is not successful.

```cpp
BOOL ncsSetWinRdr(HWND hWnd, HPACKAGE package, Uint32 rdrId);
```

In addition, certain renderer set can be configured as default system renderer
through renderer set resource setting.

```cpp
BOOL ncsSetSysRdr(HPACKAGE package, Uint32 rdrSetId);
```

### Example

This instance demonstrates how to use resources management part interface to
get resources to the users. This part of codes is automatically generated by
miniStudio tool.

![alt](figures/helloworld.png)

Figure 1 Output of resmgr Program

The program creates a 300x250 dialog box containing two buttons on the screen.
The main window is the look and feel effect of classic renderer, and the two
buttons are the look and feel effects of skin and flat renderer respectively.

#### List 2 resmgr_main.c

```cpp
/*
** resmgr_main.c: Sample program for mGNCS Programming Guide
**      The application entry of resource managerment.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
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

##### List 3 resmgr.c

```cpp
/*
** resmgr.c: Sample program for mGNCS Programming Guide
**      Create main window by resource managerment.
**
** Copyright (C) 2009 ~ 2019 FMSoft Technologies.
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

----

[&lt;&lt; Quick Start](MiniGUIProgGuidePart2Chapter02.md) |
[Table of Contents](README.md) |
[Introduction to the Foundation Classes &gt;&gt;](MiniGUIProgGuidePart2Chapter04.md)

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
