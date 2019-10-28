---+ mGEff Programming


## mGEff Introduction
### Animation realization principle

In general, animations fall into two types: Frame animations and properties
animation. Frame animation
refers to playing a series of disparate images
prepared in advance to achieve an animation effect, such as Gif,Image and so 
on; 
and attribute animation is achieved by continuously changing
the various properties of the displayed object (such as size, position, angle,
transparency, etc.) to achieve animation effects. This animation also has the
concept of frame, but each frame is through real-time calculate and change
the object's property value to generate an animation.

mGEff

It is the property animation that is supported: the user can obtain
the changed property value at each frame when the animation is performed by
setting the start, end value, power curve, and animation duration of the
property and other related parameters. The value changes the object's
properties to make it sporty. To sum up, use mGEff the essence of the animation
is to
change the value of the object property from the starting value to the ending
value 
within the specified time range.

### Terminology

- Animation: The underlying mechanism by which the `mGEFF` component operates.
It mainly provides
the application with trajectory control mechanisms for animation objects, such
as dynamic curves and time schedules.
It also provides parallel and serial processing functions for multiple
animation objects. Users can develop their own interface special effects based
on `mGEFF's` animation mechanism.
- Special Effect: Based on the underlying animation mechanism, provides `UX`
effects that can
be used directly by upper-level applications, such as blinds, fades. mGEff
currently provides
only a single degree of freedom in the
special effects, the future can achieve multiple degrees of freedom effects.
The process of developing interface special effects directly based on the
animation mechanism is more complicated. In order to support common user
interface special effects, `mGEFF` provides directly usable interface special
effects based on the underlying animation mechanism. The use of special
effects interfaces is convenient and simple, but has some limitations. For
more complex special effects, applications still need to use animation
mechanisms directly.
- Effector: A software object or structure used to implement effects.

### Framework

mGEff is a C Language-implemented lightweight animation framework that provides
an 
efficient and flexible animation implementation. Since mGEff
The design goal is to create an animation mechanism that is independent of the
specific platform and graphics system, so it can be combined with
`MiniGUI,GTK+,` and other GUI systems combined to develop `GDI` level, control
level, 
and window level animations:

Although mGEff itself uses C Language development, but its design and
implementation use some basic
object-oriented thinking, such as simulation with struct
Class, knowing this is very helpful for using it. Here is the mGEff class
diagram: 

As you can see from the figure above, mGEff provides `EffAnimation`
/EffAnimationGroup/EffEffector For other components, the use of `mGEFF` will be
described in detail in the
section “Introduction to the use of `mGEW”.`

## `mGEFF` basics

### mGEff `API`

---++++ Header files

you only need to include one header file:

```
```

---++++ mGEff Handle

- mGEff handle is use to all mgeff api.
- it is and void pointer, you can think it as an animation object pointer.

%CODE{cpp}%
/**
* \brief The handle to the animation.
*/
`MGEFF_DECLARE_HANDLE(MGEFF_ANIMATION);`
```
```

The above two functions can be called in nested pairs, but it should be noted
that mGEff Not thread-safe, so please do not use it in multiple threads at the
same time.

---++++ Animation create/delete

create and delete animation.
- target is the animation target, you can think it as an animation object,
like an control, window, bitmap...

%CODE{cpp}%

/**
\brief Creates an animation.
**
This funcion creates an animation for the target specified by \a target.*
The animation's setproperty call back is specified by \a setproperty, id is
* the identifier for the animation, and the property of the animation is
* specified by varianttype.
*/
`MGEFF_EXPORT` `MGEFF_ANIMATION` `mGEffAnimationCreate(void` *target,
`MGEFF_SETPROPERTY_CB` setproperty, `intptr_t` id,
enum `EffVariantType` varianttype);

/**
* \brief Deletes an animation.
*
* This function deletes an animation specified by \a handle.
*/
`MGEFF_EXPORT` void `mGEffAnimationDelete(MGEFF_ANIMATION` handle);

```
```

---++++ Animation start/end value

you should set animation start value, end value, it is used to set the
relative value for animation run.

%CODE{cpp}%
`MGEFF_EXPORT` void `mGEffAnimationSetStartValue(MGEFF_ANIMATION` handle,
const void *value);

`MGEFF_EXPORT` void `mGEffAnimationSetEndValue(MGEFF_ANIMATION` handle,
const void *value);

```
```

### Animation simple sample

After `mGEFF` is initialized, you can start creating animations:
%CODE{cpp}%
#include <mgeff/mgeff.h>;

Void `onPropertyChanged(MGEFF_ANIMATION` handle, void* target, int id, void*
Value)
{
Int i;
For (i = 0; i< *((int *)value); i++) {
Printf(".");
}
Printf("\n");
}

Int main(int argc, const char *argv[])
{
Int `startValue` = 0;
Int `endValue` = 10;

`mGEffInit();` // `mGEFF` initialization
// Create an animation
`MGEFF_ANIMATION` animation = `mGEffAnimationCreate(NULL,` `onPropertyChanged,`
0, `MGEFF_INT);`
`mGEffAnimationSetStartValue(animation,` &startValue); //
Set the start value of the property
`mGEffAnimationSetEndValue(animation,` &endValue); // Set the ending value
of the property
`mGEffAnimationSetDuration(animation,` duration); // The duration of the
animation execution once
`mGEffAnimationSyncRun(animation);` // Run animation
`mGEffAnimationDelete(animation);` // Delete animation
`mGEffDeinit();` // mGEff deinitialization
}
```
```
Let's look at the property change callback function, which is called every
frame of the animation. It contains four parameters:
- handle -
Call this function's animation handle, through this handle can access
some information related to the animation in the function;
- target - the target to be animated, it is calling `mGEffAnimationCreate`
Specified when the animation is created, it can be a window, control
handle, or something else;
- id - The `ID` value of the property, also called `mGEFFAnimationCreate`
When specified, sometimes users want to share the same property change
callback in multiple animations to control the change of multiple properties
of the object. At this time, you can set different for each property.
The `ID` value allows the user to determine the current changed property in the
callback function. The current preset attribute `ID` is defined as follows:
%CODE{cpp}%
Enum `EffPropertyID` {
`ID_NULL` = 0,
`ID_POS`, /* `POINT` */
`ID_SIZE`, /* `RECT` */
`ID_RECT`, /* `RECT,` pos & size */
`ID_OPACITY`, /* int */
...
`ID_USER` = 1000;
};
```
```

Another concept in the power curve is the power curve, through which you can
control the speed of the animation. Still based on the examples in the
previous section to demonstrate the usage of the power curve:
%CODE{cpp}%
#include <mgeff/mgeff.h>;

Void `onPropertyChanged(MGEFF_ANIMATION` handle, void* target, int id, void*
Value)
{
Printf("%d\n", (int)*value);
}

Int main(int argc, const char *argv[])
{
Int `startValue` = 1;
Int `endValue` = 10;

`mGEffInit();`
`MGEFF_ANIMATION` animation = `mGEffAnimationCreate(NULL,` `onPropertyChanged,`
0, `MGEFF_INT);`
`mGEffAnimationSetStartValue(animation,` &startValue);
`mGEffAnimationSetEndValue(animation,` &endValue);
`mGEffAnimationSetDuration(animation,` duration);
`mGEffAnimationSetCurve(animation,` `InQuad);` // Set a dynamic curve for the
animation
`mGEffAnimationSyncRun(animation);`
`mGEffAnimationDelete(animation);`
`mGEffDeinit();`
}
```
```

For example by `mGEffAnimationSetProperty(animation,` `MGEFF_PROP_LOOPCOUNT`, 
5) 
You can change the number of animation animation loops to 5 times.

### Animation Group

In practical applications, users often do not only want to perform an
animation at the same time, but also need to associate multiple animations to
be executed in parallel or in series to obtain more complicated animation
effects. and so
mGEff
With the introduction of an animation group mechanism, the user can create a
Parallel or Sequential group to achieve the requirements for performing a set
of animations, as shown in the following example:
%CODE{cpp}%
// `TODO:` Improve the sample program
`mGEffAnimationCreateGroup(enum` `EffAnimationType` type);
`mGEffAnimationAddToGroup(MGEFF_ANIMATION` group, `MGEFF_ANIMATION`
Animation);
```
```
This example will output:
// `TODO:`

### Effector effector

---++++ Effector create/delete

you should create an effector first, mgeff have defined some internal
effector:
- `mGEffStr2Key` get an has code for special effector name.
- `mGEffEffectorCreate/mGEffEffectorDelete` create or delete an effector.
- `mGEffAnimationCreateWithEffector` return an animation for the special
effector.

%CODE{cpp}%
`MGEFF_EXPORT` unsigned long `mGEffStr2Key` (const char* str);

`MGEFF_EXPORT` `MGEFF_EFFECTOR` `mGEffEffectorCreate(unsigned` long key);
`MGEFF_EXPORT` void `mGEffEffectorDelete(MGEFF_EFFECTOR` handle);

`MGEFF_EXPORT` `MGEFF_ANIMATION` 
`mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR` 
effector);

```
```

---++++ Effector source/sink

Effector have two important elements:
- sink: sink is used for display, such as an MiniGUI `DC.`
- source: effector source is the input element, such as an bitmap resource.

%CODE{cpp}%

`MGEFF_EXPORT` int `mGEffEffectorAppendSource(MGEFF_EFFECTOR` effector,
`MGEFF_SOURCE` source);

`MGEFF_EXPORT` int `mGEffEffectorSetSink(MGEFF_EFFECTOR` effector, `MGEFF_SINK`
sink);

```
```

---++++ Effector fill

Fills a `DC` with a predefined effector.

- This function creates and run an animation whose `SetProperty` callback is
a effector specified by type. The sources of the effector are specified
by src1_dc and src2_dc respectively. The destination `DC` of the effector is
specified by \a `dst_dc.` The duration of the animation is specified by
duration.

%CODE{cpp}%
`MGEFF_EXPORT` int `mGEffFillEffectorAnimation(HWND` hwnd, `HDC` src1_dc, `HDC`
src2_dc,
`HDC` `dst_dc,` unsigned long key, int duration);
```
```


<img align="CENTER" alt="mgeff-effctor.png"
src="%ATTACHURLPATH%/mgeff-effctor.png" />

mGEff Effector suppport

---++++ How to use Effector

- Create Effector.

%CODE{cpp}%

/**
* \fn `MGEFF_ANIMATION` `mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR`
effector);
* \brief Creates a animation with a effector.
*
* This function creates an animation whose `SetProperty` callback is a effector
* specified by \a effector and the id of the animation is specified by \a id.
*
* \param effector the handle of the effector.
*
* \return the handle of the newly created animaiton.
*
* \sa `mGEffAnimationCreate,` `mGEffEffectorCreate.`
*/
`MGEFF_EXPORT` `MGEFF_ANIMATION` 
`mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR` 
effector);

```
```

## `mGEFF` use advanced
### Animation execution

The animation supports synchronous and asynchronous two different execution
modes. The synchronous execution function is called until the animation end
function returns. In this process, the program will not be able to respond to
the message; after the asynchronous execution function is called, the
animation will be returned immediately and the animation will still be The
schedule is executed until it is aborted or ended, and the program can respond
to the processing message. The specific function prototype is as follows:
%CODE{cpp}%
// Perform animations synchronously
Int `mGEffAnimationSyncRun(MGEFF_ANIMATION` handle);

// Perform animations asynchronously
Int `mGEffAnimationAsyncRun(MGEFF_ANIMATION` handle);

// Wait for the asynchronous animation to end
`MGEFF_BOOL` `mGEffAnimationWait(void*` `phWnd,` `MGEFF_ANIMATION` handle);
```
```

### Custom Effector

---++++ `MGEFF_EFFECTOROPS`

`MGEFF_EFFECTOROPS` contains whole info of an effector, if you want to custom 
an 
effector, implement it, In the mGEff, it has defined some effector like the
follow, when you custom an your own effector, you do not need to implement all
the callback, but the ondraw callback must be include.

%CODE{cpp}%
typedef struct _EFFECTOROPS {
char name[EFFECTORNAME_MAX_LEN + 1]; /*< name
of effector */
enum `EffVariantType` varianttype; /*<
variant type */
`MGEFF_EFFECTOR_INIT` init; /*< init
*/
`MGEFF_EFFECTOR_FINALIZE` finalize; /*<
finalize */
`MGEFF_EFFECTOR_ANIM_ONDRAW` ondraw; /*< on
draw */
`MGEFF_EFFECTOR_ONBEGINDRAW` begindraw; /*< begin
draw */
`MGEFF_EFFECTOR_ONENDDRAW` enddraw; /*< end
draw */
`MGEFF_EFFECTOR_SETPROPERTY` setproperty; /*< set
property */
`MGEFF_EFFECTOR_GETPROPERTY` getproperty; /*< get
property */
} `MGEFF_EFFECTOROPS;`

...;
#ifdef _MGEFF_ZIPEFFECTOR
extern `MGEFF_EFFECTOROPS` zipeffector;
#endif
...

```
```

---++++ Complex zoomeffector sample

if you want to implement an complex effector, you can see the zoom effector in
the mGEff:

- init/finalize: malloc or free your own context var, like `EffZoomCtxt` is
use to save zoom factor property.
- begindraw: init the start and end value of animation, such as zoom start
rect size and end rect size.
- setproperty: setproperty is used to change zoom factor strategy, you can
change it to implement your own strategy, just like zoom more quick or
zoom accelerate.
- getproperty: getproperty is used to return zoom factor for effector.

%CODE{cpp}%

typedef struct _EffZoomCtxt{
int zoom;
`RECT` `prev_rc;`
}EffZoomCtxt;

`MGEFF_EFFECTOR` `effzoomeffector_init(MGEFF_EFFECTOR` _effector)
{
`EffEffector` *effector = (EffEffector *)_effector;
`EffZoomCtxt*` `zoom_context` = (EffZoomCtxt*)calloc(1, sizeof(EffZoomCtxt));
effector->context = `zoom_context;`
return _effector;
}

void `effzoomeffector_begindraw(MGEFF_ANIMATION` animation, `MGEFF_EFFECTOR`
_effector)
{
...
`mGEffAnimationSetStartValue` (animation, &rc_s);
`mGEffAnimationSetEndValue` (animation, &rc_e);
...
}

void `effzoomeffector_finalize` (MGEFF_EFFECTOR _effector)
{
`EffEffector` *effector = (EffEffector *)_effector;
free (effector->context);
}

int `effzoomeffector_setproperty(MGEFF_EFFECTOR` _effector, int `property_id,`
int 
value)
{
`EffEffector` *effector = (EffEffector *)_effector;
`EffZoomCtxt*` `zoom_context` = (EffZoomCtxt*)effector->context;
switch (property_id)
{
case `MGEFF_PROPERTY_ZOOM:`
if (value >= `MGEFF_ZOOMIN` &&
value <= `MGEFF_ZOOMOUT)`
{
`zoom_context->zoom` = value;
return 0;
}
break;
default:
return `effbaseeffector_setproperty(_effector,` `property_id,` value);
}
return -1;
}

int `effzoomeffector_getproperty(MGEFF_EFFECTOR` _effector, int `property_id,`
int* value)
{
`EffEffector` *effector = (EffEffector *)_effector;
`EffZoomCtxt*` `zoom_context` = (EffZoomCtxt*)effector->context;
switch (property_id)
{
case `MGEFF_PROPERTY_ZOOM:`
{
if (value)
*value = `zoom_context->zoom;`
return `zoom_context->zoom;`
}

default:
return `effbaseeffector_getproperty(_effector,` `property_id,` value);
}
return -1;
}

`MGEFF_EFFECTOROPS` zoomeffector =
{
`MGEFF_MINOR_zoom`,
`MGEFF_RECT`,
`effzoomeffector_init,`
`effzoomeffector_finalize,`
`effzoomeffector_ondraw,`
`effzoomeffector_begindraw,`
`NULL,`
`effzoomeffector_setproperty,`
`effzoomeffector_getproperty`

};
```
```

An simple custom curve sample:

%CODE{cpp}%
float `calcCustom(float` t)
{
return t*t*t/3.0 + t*t/3.0 + t/3.0;
}

//Custom
`TEST(MotioncurveTest,` Custom) {
`mGEffInit();`
`MGEFF_ANIMATION` animation = `mGEffAnimationCreate(NULL,` `test_cb,` Custom,
`MGEFF_FLOAT);`
`mGEffAnimationSetStartValue(animation,` &start);
`mGEffAnimationSetEndValue(animation,` &end);
`mGEffAnimationSetDuration(animation,` duration);
`mGEffAnimationSetCurveEx(animation,` &calcCustom);
t0 = 10 * times(NULL);
`mGEffAnimationSyncRun(animation);`
`mGEffAnimationDelete(animation);`
`mGEffDeinit();`
}

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
