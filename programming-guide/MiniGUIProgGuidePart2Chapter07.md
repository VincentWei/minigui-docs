# Chapter 6 of Part 2 Panel and Its Derived Class


## Brief Introduction of Panel Class Control

This class of control is the container class controls that accommodate other classes of controls, which are generally combination control class and main window class.

The class inheritance relation of panel and its derived class is as follows:

- [mWidget ](MStudioMGNCSV1dot0PGENP2C3#mWidget)
   - [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md)
         * [mComboBox](MiniGUIProgGuidePart2Chapter07#mComboBox.md)
         * [mMainWnd](MiniGUIProgGuidePart2Chapter07#mMainWnd.md)
            * [mDialogBox](MiniGUIProgGuidePart2Chapter07#mDialogBox.md)

## mPanel

- *Control name*:  NCSCTRL_PANEL
- *English name*: Panel
- *Brief introduction*: Container of other controls, mainly used for carrying out grouped operation to the controls. Through grouping the controls into the panel control, a group of controls can be conveniently displayed or hidden.
- *Schematic diagram*: <br/>
<img src="%ATTACHURLPATH%/panel.png" alt="panel.png"  />

Panel must exist in MainWnd, DialogBox, another Panel control or other controls. Besides other controls, it can contain content such as texts and images etc.

### Style of mPanel

It is inherited from the style of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

### Property of mPanel

It is inherited from the property of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

---+++Event of mPanel

It is inherited from the event of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

### Method of mPanel

It is inherited from the method of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

The class does not have newly added methods

### Renderer of mPanel

It is inherited from the renderer of [mWidget](MStudioMGNCSV1dot0PGENP2C3#mWidget).

mPanel does not have newly added renderer method

### Example of mPanel

This example demonstrates how to use panel to group multiple controls to the users.

<p>
<img src="%ATTACHURLPATH%/panel_demo.png" alt="panel_demo.png"/><br>
Figure p2c6-1 Output of panel Program
</p>

<p align=center>List p2c6-1 panel.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/panel.c.txt"}%
```

## mCombobox

- *Control name*:  NCSCTRL_COMBOBOX
- *English name*: Combobox
- *Brief introduction*: An edit box and a list box are integrated. Users can directly key text in the edit box and can select an existing item from the options listed in the list box. Input and selection functions of users can be well completed. Address column in general browser is a good application.
- *Schematic diagram*: <br/>     <img src="%ATTACHURLPATH%/combo.png" alt="combo.png" width='143' height='93' />

### Style of mCombobox

It is inherited from the style of [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md). 

| *Style name* | *miniStudio property name* | *Explanation* |
| NCSS_CMBOX_SIMPLE | Type->Simple | Simple combination box |
| NCSS_CMBOX_DROPDOWNLIST | Type->DropDownList | Dropdown combination box |
| NCSS_CMBOX_SORT | Sort->TRUE | Character string automatic sorting |
| NCSS_CMBOX_EDITNOBORDER | EditHasBorder->FALSE | The edit box does not have border |
| NCSS_CMBOX_EDITBASELINE | EditHasBaseLine->TRUE | The edit box displays underlined characters |
| NCSS_CMBOX_READONLY | ReadOnly | Content displayed by the edit box is read only |
| NCSS_CMBOX_UPPERCASE | Case->Upper | All the display content of the edit box is converted to capital letter display |
| NCSS_CMBOX_LOWERCASE | Case->Lower | All the display content of the edit box is converted to lowercase letter display |
| NCSS_CMBOX_AUTOFOCUS | AutoFocus->TRUE  | The control gets focus and automatically transfers to the edit box |

### Property of mCombobox

It is inherited from the property of [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md). 

| *Property name* | *miniStudio property name* | *Type* | *RW* | *Explanation* |
| NCSP_COMB_DROPDOWNHEIGHT | DropDownHeight | int | RW | Height of the dropdown list |
| NCSP_COMB_ITEMHEIGHT | ItemHeight | int | RW | Height of the list item |
| NCSP_COMB_ITEMCOUNT | ItemCount | int | RO | Number of the list items |
| NCSP_COMB_TEXTLIMIT| TextLimit | int | RW | Limit of the edit box |
| NCSP_COMB_SELECT | -- | int | RW | Selection items index |

### Event of mCombobox

It is inherited from the event of [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md). 

| *Event ID* | *Parameter* | *Explanation* |
| NCSN_CMBOX_SELCHANGE | -- | The selected item changes |
| NCSN_CMBOX_SETFOCUS | -- | Get focus |
| NCSN_CMBOX_KILLFOCUS | -- | Lose focus |
| NCSN_CMBOX_EDITCHANGE | -- | Content of the edit box changes |
| NCSN_CMBOX_DROPDOWN | -- | Dropdown list pops up |
| NCSN_CMBOX_CLOSEUP | -- | Dropdown list is closed |
| NCSN_CMBOX_SELECTOK | -- | Select an item when the dropdown list is closed |
| NCSN_CMBOX_SELECTCANCEL | -- | No selection when the dropdown list is closed |

### Method of mCombobox

It is inherited from the method of [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md). 

---++++ addItem

%CODE{cpp}%
BOOL addItem(mCombobox *self, const char *item, DWORD addData);
```
- Parameter:<BR>
   - item – add the content of selected item
   - addData – additional data of the item
- Explanation:<BR>
      Add selected items to the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
char *items = {
    "first item --- Chinese",
    "second item --- German",
    "third item -- English"
};
//Add three items to the dropdown list
for (i = 0; i < 3; i++)
{
    _c(combo)->addItem(combo, items[i]， 0);
}
```

---++++ removeItem

%CODE{cpp}%
 BOOL removeItem(mCombobox *self, int index);
```
- Parameter:<BR>
   - index – index of the items to be deleted
- Explanation:<BR>
      Delete certain selected item from the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
//Delete the first item of the dropdown list
_c(combo)->removeItem(combo, 0);
```

---++++ setItem

%CODE{cpp}%
BOOL setItem(mCombobox *self, int index, const char *item); 
```
- Parameter:<BR>
   - index – index of the items to be modified
- Explanation:<BR>
      Modify content of certain selected item in the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
//Modify the content of the first item in the dropdown list to "new content"
_c(combo)->setItem(combo, 0, "new content");
```

---++++ getItem

%CODE{cpp}%
const char* getItem(mCombobox *self, int index); 
```
- Parameter:<BR>
   - index – index of the items to get
- Explanation:<BR>
      Get content of certain selected item in the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
const char *item_1 = _c(combo)->getItem(combo, 0);
```

---++++ setAddData
%CODE{cpp}%
void* setAddData(mCombobox *self, int index, DWORD addData); 
```
- Parameter:<BR>
   - index – index of the items to set additional data
   - addData – information of additional data
- Explanation:<BR>
      Set additional data of certain selected item in the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
PBITMAP pbmp;
LoadBitmap (......);
_c(combo)->setAddData(combo, 0, (DWORD)pbmp);
```

---++++ getAddData
%CODE{cpp}%
DWORD getAddData(mCombobox *self, int index); 
```
- Parameter:<BR>
   - index – index of the items to get additional data
- Explanation:<BR>
      Get additional data of certain selected item in the dropdown list of combobox
- Example:<BR>

%CODE{cpp}%
DWORD add = _c(combo)->getAddData(combo, 0);
```

### Renderers of mCombobox

They are inherited from the renderers of [mPanel](MiniGUIProgGuidePart2Chapter07#mPanel.md).

---++++ mCombobox Classic Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
| NCS_BGC_3DBODY | ColorBg3DBody | DWORD(ARGB) |  | Draw color of the dropdown button |
| NCS_FGC_WINDOW | ColorFgWindow | DWORD(ARGB) |  | Draw color of the arrow of the dropdown button |

---++++ mCombobox Fashion Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
| NCS_BGC_3DBODY | ColorBg3DBody | DWORD(ARGB) |  | Draw color of the dropdown button |
| NCS_FGC_WINDOW | ColorFgWindow | DWORD(ARGB) |  | Draw color of the arrow of the dropdown button |
| NCS_METRICS_3DBODY_ROUNDX | RoundX | int | | Round corner x radius of the dropdown button |
| NCS_METRICS_3DBODY_ROUNDY | RoundY | int | | Round corner y radius of the dropdown button |
| NCS_MODE_BGC | GradientMode | int |  | Drawing mode of the gradual change effect (horizontal gradual change or vertical gradual change) |

---++++ mCombobox Skin Renderer

Refer to [Appendix B](MStudioMGNCSV1dot0PGENAppB][Image Specification]] in the Specification for the Image Resource Used by Skin Renderer ([[MStudioMGNCSV1dot0PGENAppB)).

---++++ mCombobox Flat Renderer

| *Property name* | *miniStudio property name* | *Type* | *Schematic diagram* | *Explanation* |
|NCS_BGC_3DBODY | ColorBg3DBody | DWORD(ARGB) |  | Draw color of the dropdown button |
| NCS_FGC_WINDOW | ColorFgWindow | DWORD(ARGB) |  | Draw color of the arrow of the dropdown button |

### Example of mCombobox

     <img src="%ATTACHURLPATH%/com.png" alt="com.png" width='296' height='247' />

<p align=center>List p2c6-1 combobox.c</p>
```cplusplus
%INCLUDE{"%ATTACHURL%/combobox"}%
```


[Next](MStudioMGNCSV1dot0PGENP2C5][Previous]] < [[MStudioMGNCSV1dot0PGEN][Index]] > [[MStudioMGNCSV1dot0PGENP2C7)


-- Main.XiaodongLi - 28 Feb 2010

