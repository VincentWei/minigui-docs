# Release Notes

## Version 1.5.0

The MiniGUI development team announces the availability of mGUtils 1.5.0.
All users of MiniGUI are encouraged to use this version, and report
any bugs and incompatibilities on GitHub:

<https://github.com/VincentWei/mgutils/tree/rel-5-0>

### What's new in this version

- Tune code for MiniGUI 5.0.0 or later.

## Version 1.2.2

The MiniGUI development team announces the availability of mGUtils 1.2.2,
which is compliant to MiniGUI 4.0.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

    https://github.com/VincentWei/mgutils

### What's new in this version

  * Tune some code to comply with MiniGUI 4.0.x.

## Version 1.2.0

The MiniGUI development team announces the availability of mGUtils 1.2.0,
which is compliant to MiniGUI 3.2.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

    https://github.com/VincentWei/mgutils

### What's new in this version

  * Tune code to comply with MiniGUI 3.2.x. 
  * Tune code for 64-bit platform.
  * Tune code to eliminate all warnings.

### API changes

The default File Open/Save Dialog callback procedure changed from

    int DefFileDialogProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);

to 

    LRESULT DefFileDialogProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
 
The default Color Selection Dialog callback procedure changed from

int DefColorDialogProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);

to

    LRESULT DefColorDialogProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
 
The default Font Selection Dialog callback procedure changed from

    int DefFontDialogProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);

to

    LRESULT DefFontDialogProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
 
The default Information Dialog callback procedure changed from

    int DefInfoDialogProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);

to

    LRESULT DefInfoDialogProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

The Skin item information structure changed to

    typedef struct skin_item_s
    {
        int id;
        DWORD style;

        int x;
        int y;

        RECT item_rc;

        /* Changed since version 1.2.
        union {
            /** The index of the item bitmap in the skin bitmap array. */
            int bmp_index;

            /** The handle to the control if the type is SI_TYPE_CONTROL. */
            HWND hwnd;
        };

        ...

    } skin_item_t;

## Version 1.0.5

The MiniGUI development team announces the availability of mGUtils 1.0.5.
All users of MiniGUI are encouraged to test this version carefully, 
and report any bugs and incompatibilities to:

    https://github.com/VincentWei/mgutils

### What's new in this version

  * The autoconf/automake config scripts are cleaned up.
  * Fix some bugs. 

### API changes

(none).
