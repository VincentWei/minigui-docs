# Release Notes

## Version 1.5.0

The MiniGUI development team announces the availability of mGNCS 1.5.0.

All users of MiniGUI are encouraged to use this version, and
report any bugs and incompatibilities on GitHub:

<https://github.com/VincentWei/mgncs/tree/rel-5-0>

### What's new in this version

- Tune code to comply with MiniGUI 5.0.0.

## Version 1.2.5

The MiniGUI development team announces the availability of mGNCS 1.2.5,
which is compliant to MiniGUI 4.0.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

<https://github.com/VincentWei/mgncs>

### What's new in this version

This version mainly fixed some minor issues:

- Tune some API description.
- Tune format string `size_t` values.

## Version 1.2.4

The MiniGUI development team announces the availability of mGNCS 1.2.4,
which is compliant to MiniGUI 4.0.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

<https://github.com/VincentWei/mgncs>

### What's new in this version

  * Tune code to comply with MiniGUI 4.0.x.

## Version 1.2.2

The MiniGUI development team announces the availability of mGNCS 1.2.2,
which is compliant to MiniGUI 3.2.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

    https://github.com/VincentWei/mgncs

### What's new in this version

  * Fix som bugs by merged pull requests from https://github.com/10km.

## Version 1.2.0

The MiniGUI development team announces the availability of mGNCS 1.2.0,
which is compliant to MiniGUI 3.2.x.

All users of MiniGUI are encouraged to use this version with your new MiniGUI
apps, and report any bugs and incompatibilities to:

    https://github.com/VincentWei/mgncs

### What's new in this version

  * Tune code to comply with MiniGUI 3.2.x.
  * Tune code for 64-bit platform.
  * Tune code to eliminate all warnings.

### API changes

#### HPACKAGE

The handle type `HPACKAGE` is now defined as aliases of `PVOID` 
(`typedef void* PVOID`). You may need to check your code to 
reflect this change. 

#### Window procedure

MiniGUI V3.2 now uses a `UINT` instead of an `int` integer for 
the message identifier, and uses a `LRESULT` integer for the return 
value of a window callback procedure. 

Therefore, the property `wndProc` of `mWidget` changed from

    int (*wndProc)(clsName* , int, WPARAM, LPARAM);
to

    LRESULT (*wndProc)(clsName* , UINT, WPARAM, LPARAM);

the property of `callUserHandler` of `mWidget` changed from

    BOOL (*callUserHandler)(clsName* self, void *handler, int message, \
        WPARAM wParam, LPARAM lParam, int *pRet);

to

    BOOL (*callUserHandler)(clsName* self, void *handler, UINT message, \
        WPARAM wParam, LPARAM lParam, LRESULT *pRet);

#### Wiget identifier

We now use a `intptr_t` integer for the identifier of a mWidget object. 
So you can pass a pointer as the identifier of the animation on 64-bit 
platform. 

As a result, the definition of the struct `NCS_MNWND_TEMPLATE` changed:

        typedef struct _NCS_MNWND_TEMPLATE{
            const char*         class_name;
            intptr_t            id;
            int                 x, y, w, h;

            ...

            intptr_t            count;
            DWORD               user_data;

            ...
        } NCS_MNWND_TEMPLATE;

## Version 1.0.9

The MiniGUI development team announces the availability of mGNCS 1.0.9.
All users of MiniGUI are encouraged to test this version carefully, and 
report any bugs and incompatibilities to

    https://github.com/VincentWei/mgncs

### What's new in this version

  * The autoconf/automake config scripts are cleaned up.

### API changes

(none).
