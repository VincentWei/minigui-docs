---+ mGEff Programming 


## mGEff Introduction
### Animation realization principle

In general, animations fall into two types: Frame animations and properties animation. Frame animation 
refers to playing a series of disparate images
prepared in advance to achieve an animation effect, such as Gif,Image and so on; 
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
properties to make it sporty. To sum up, use mGEff the essence of the animation is to 
change the value of the object property from the starting value to the ending value 
within the specified time range.

### Terminology

- Animation: The underlying mechanism by which the mGEFF component operates. It mainly provides 
the application with trajectory control mechanisms for animation objects, such as dynamic curves and time schedules.
It also provides parallel and serial processing functions for multiple
animation objects. Users can develop their own interface special effects based
on mGEFF's animation mechanism.
- Special Effect: Based on the underlying animation mechanism, provides UX effects that can 
be used directly by upper-level applications, such as blinds, fades. mGEff currently provides 
only a single degree of freedom in the
special effects, the future can achieve multiple degrees of freedom effects.
The process of developing interface special effects directly based on the
animation mechanism is more complicated. In order to support common user
interface special effects, mGEFF provides directly usable interface special
effects based on the underlying animation mechanism. The use of special
effects interfaces is convenient and simple, but has some limitations. For
more complex special effects, applications still need to use animation
mechanisms directly.
- Effector: A software object or structure used to implement effects.

### Framework

mGEff is a C Language-implemented lightweight animation framework that provides an
efficient and flexible animation implementation. Since mGEff
The design goal is to create an animation mechanism that is independent of the
specific platform and graphics system, so it can be combined with
MiniGUI,GTK+, and other GUI systems combined to develop GDI level, control level,
and window level animations: 

Although mGEff itself uses C Language development, but its design and implementation use some basic
object-oriented thinking, such as simulation with struct
Class, knowing this is very helpful for using it. Here is the mGEff class diagram: 

As you can see from the figure above, mGEff provides EffAnimation
/EffAnimationGroup/EffEffector For other components, the use of mGEFF will be described in detail in the
section “Introduction to the use of mGEW”.

## mGEFF basics

### mGEff API

---++++ Header files

you only need to include one header file:

```cplusplus
#include <mgeff/mgeff.h>;
```

---++++ mGEff Handle

- mGEff handle is use to all mgeff api.
- it is and void pointer, you can think it as an animation object pointer.

%CODE{cpp}%
/**
 * \brief The handle to the animation.
 */
MGEFF_DECLARE_HANDLE(MGEFF_ANIMATION);
```

---++++ Initialize/Deinitialize

In use Before mGEFF, it must be initialized; after use (usually at the end of the
program), deinitialize to destroy the resources occupied by the framework.

%CODE{cpp}%
MGEFF_EXPORT int mGEffInit (void); // Initialization function
MGEFF_EXPORT void mGEFFDeinit (void); // Deinitialization function
```

The above two functions can be called in nested pairs, but it should be noted
that mGEff Not thread-safe, so please do not use it in multiple threads at the same time.

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
 * the identifier for the animation,  and the property of the animation is
 * specified by varianttype.
 */
MGEFF_EXPORT MGEFF_ANIMATION mGEffAnimationCreate(void *target,
        MGEFF_SETPROPERTY_CB setproperty, intptr_t id,
        enum EffVariantType varianttype);

/**
 * \brief Deletes an animation.
 *
 * This function deletes an animation specified by \a handle.
 */
MGEFF_EXPORT void mGEffAnimationDelete(MGEFF_ANIMATION handle);

```

---++++ Animation callback

Animation has multiple callbacks, you can use relative callback to do yourself
things.
- animation finished.
- animation state changed.
- animation loop changed.
- animation direction changed.

%CODE{cpp}%

/**
 \brief Type of animation finished callback function.
 The callback is going to be called,when animation is finished.
 */
typedef void (*MGEFF_FINISHED_CB)(MGEFF_ANIMATION handle);

/**
 \brief Type of animation state change callback function.
 The callback is going to be called, when animation state specified by \a
handle*
 is changed.
 */
typedef void (*MGEFF_STATECHANGED_CB)(MGEFF_ANIMATION handle,
        enum EffState newEffState, enum EffState oldEffState);

/**
 \brief Type of animation current loop changed callback function.
 The callback is going to be called, when animation's current loop is changed.
 */
typedef void (*MGEFF_CURLOOPCHANGED_CB)(MGEFF_ANIMATION handle);

/**
 \brief Type of animation direction changed callback function.
 The callback is going to be called, when animation's direction is changed.
 */
typedef void (*MGEFF_DIRCHANGED_CB)(MGEFF_ANIMATION handle);

/**
 \brief Type of animation set property function. This fuction is used to
produce*
 every animation frame when animation is running, The callback is going to be
called every frame.
 */
typedef void (*MGEFF_SETPROPERTY_CB)(MGEFF_ANIMATION handle,
        void *target, intptr_t id, void *value);

/**
 The callback is going to be called every frame, when the animation specified
by \a handle*
 is created by mGEffAnimationCreateEx
 */
typedef void (*MGEFF_CALCVALUE_CB)(MGEFF_ANIMATION handle,
        void *s, void *e, void *v, float factor);

/**
 The callback is going to be called, when the animation is creating.*
 The animation created by mGEffAnimationCreateEx will specify the callback.
 */
typedef void *(*MGEFF_VARMALLOC_CB)(MGEFF_ANIMATION handle);

```

---++++ Animation start/end value

you should set animation start value, end value, it is used to set the
relative value for animation run.

%CODE{cpp}%
MGEFF_EXPORT void mGEffAnimationSetStartValue(MGEFF_ANIMATION handle,
        const void *value);

MGEFF_EXPORT void mGEffAnimationSetEndValue(MGEFF_ANIMATION handle,
        const void *value);

```

---++++ Animation run

Async run the animation in the default schedular asynchronous, attachs the
animation to the default schedular and start the animation. The animation run
immediately if schedular is already started, otherwise it will wait until the
schedular started.

Sync run,  Run the animation in the default schedular synchronous,  attachsthe
animation to the default schedular and start the animation. The animation run
immediately and return until the animation finished.

%CODE{cpp}%
MGEFF_EXPORT int  mGEffAnimationAsyncRun(MGEFF_ANIMATION handle);

MGEFF_EXPORT int  mGEffAnimationSyncRun(MGEFF_ANIMATION handle);

```

### Animation simple sample

After mGEFF is initialized, you can start creating animations:
%CODE{cpp}%
#include <mgeff/mgeff.h>;

Void onPropertyChanged(MGEFF_ANIMATION handle, void* target, int id, void*
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
    Int startValue = 0;
    Int endValue = 10;

    mGEffInit(); // mGEFF initialization
    // Create an animation
    MGEFF_ANIMATION animation = mGEffAnimationCreate(NULL, onPropertyChanged,
0, MGEFF_INT);
    mGEffAnimationSetStartValue(animation, &startValue); //
Set the start value of the property
    mGEffAnimationSetEndValue(animation, &endValue); // Set the ending value
of the property
    mGEffAnimationSetDuration(animation, duration); // The duration of the
animation execution once
    mGEffAnimationSyncRun(animation); // Run animation
    mGEffAnimationDelete(animation); // Delete animation
    mGEffDeinit(); // mGEff deinitialization
}
```

Through the simplest example program above, you can understand mGEff
The basic use of the method: the first to create an animation and set the
property value changes when the callback, set the property's start value and
end value, the animation duration, and then run the animation in a
synchronized manner, and finally destroy the animation. Here first introduce
the animation creation function
mGEffAnimationCreate, this function has four parameters:
- The first parameter is the target to be animated. Since the above example
     is simple enough to produce no real animation, this parameter is passed
     NULL;
- The second parameter is the function pointer to be called when the
     property changes. This function will be called in each frame of the
animation, and will be introduced later;
- The third parameter is the attribute
     ID, this value will be passed as a parameter to the property change
callback function, used to distinguish the property to modify when multiple
animations share the same property change callback function;
- The fourth parameter is the type of the property value. This parameter
     determines the data type of the start and end values of the
property, mGEff
     A set of typed enumerations is defined in the definition of the
following:
%CODE{cpp}%
Enum EffVariantType {
    MGEFF_INT = 0, // integer
    MGEFF_FLOAT = 1, // TODO: Add a comment
    MGEFF_DOUBLE = 2, // TODO: Add comment...
    MGEFF_POINT = 3,
    MGEFF_POINTF = 4,
    MGEFF_3DPOINT = 5,
    MGEFF_3DPOINTF = 6,
    MGEFF_RECT = 7
    MGEFF_COLOR = 8
    MGEFF_MAX
};
```
   Let's look at the property change callback function, which is called every
frame of the animation. It contains four parameters:
- handle -
     Call this function's animation handle, through this handle can access
some information related to the animation in the function;
- target - the target to be animated, it is calling mGEffAnimationCreate
     Specified when the animation is created, it can be a window, control
handle, or something else;
- id - The ID value of the property, also called mGEFFAnimationCreate
     When specified, sometimes users want to share the same property change
callback in multiple animations to control the change of multiple properties
of the object. At this time, you can set different for each property.
The ID value allows the user to determine the current changed property in the
callback function. The current preset attribute ID is defined as follows:
%CODE{cpp}%
   Enum EffPropertyID {
    ID_NULL = 0,
    ID_POS, /* POINT */
    ID_SIZE, /* RECT */
    ID_RECT, /* RECT, pos & size */
    ID_OPACITY, /* int */
    ...
    ID_USER = 1000;
};
```
- value - the current value of the property, the start and end values
     of the property by
     mGEffAnimationSetStartValue/mGEffAnimationSetEndValue
Two function settings, mentioned earlier mGEff
The whole process of animation is to change the property from the starting
value to the ending value, and this
Value is the intermediate value (interpolation) during this change. In this
example, the value is only printed to the standard output, so it does not
produce a substantial animation effect, but the user can use the object
properties to be animated to set this value (such as the example
By changing the printf to a circle radius, you can get a realistic animation.

### Power curve

The previous section introduced an example of creating a simple mGEFF
animation, but a callback from a property change
Printing of onPropertyChanged function can be seen, property values
from 1 to 10
The change is uniform, that is, a linear change. The actual animation effect
of this change is relatively straightforward, so users often need to perform
non-linear changes such as acceleration, deceleration, and oscillation to
achieve more flexible and realistic animation effects. This requires the use
of mGEff.

    * mGEffAnimationSetCurve: set animation curve, it have included more
      curves.

%CODE{cpp}%
/**
 * \brief Sets the motion cureve of the animation.
 *
 * This function sets the motion curve of the animation specified by \a handle
 * to the curve specified by \a type.
 */
MGEFF_EXPORT void mGEffAnimationSetCurve(MGEFF_ANIMATION handle,
        enum EffMotionType type);

```

Another concept in the power curve is the power curve, through which you can
control the speed of the animation. Still based on the examples in the
previous section to demonstrate the usage of the power curve:
%CODE{cpp}%
#include <mgeff/mgeff.h>;

Void onPropertyChanged(MGEFF_ANIMATION handle, void* target, int id, void*
Value)
{
    Printf("%d\n", (int)*value);
}

Int main(int argc, const char *argv[])
{
    Int startValue = 1;
    Int endValue = 10;

    mGEffInit();
    MGEFF_ANIMATION animation = mGEffAnimationCreate(NULL, onPropertyChanged,
0, MGEFF_INT);
    mGEffAnimationSetStartValue(animation, &startValue);
    mGEffAnimationSetEndValue(animation, &endValue);
    mGEffAnimationSetDuration(animation, duration);
    mGEffAnimationSetCurve(animation, InQuad); // Set a dynamic curve for the
animation
    mGEffAnimationSyncRun(animation);
    mGEffAnimationDelete(animation);
    mGEffDeinit();
}
```

From the results of the execution of the example, it can be seen that there is
a clear difference from the interpolation of the output of the previous
section. The output shows a change in the acceleration law. It can be imagined
that if
Printf After the statement is replaced with the code that actually sets the
object's properties (such as modifying the radius of the circle), its
animation is accelerated.

mGEff there are dozens of preset power curves that can be used to implement
different interpolation speeds to produce animated effects.

<center> <img align="CENTER" alt="mgeff-curve.png" src="%ATTACHURLPATH%/mgeff-curve.png" /></center>
<center>mGEff support curve type</center>

### Animation Properties

Before starting this section, we must first carry out a noun convention: The
above-mentioned "attribute animation" refers to the animation effect produced
by continuously modifying an attribute of an animation object; this section is
called "animation attribute" is Another meaning, it means passing

The attributes of the animated object created by mGEff can't be confused.
Through functions.

You can set the properties of the animation itself. The prototype of the
function and currently supported animation properties are enumerated as
follows:

%CODE{cpp}%
Enum EffAnimProperty {
    MGEFF_PROP_DURATION = 0, // The duration of the animation execution
    MGEFF_PROP_CURLOOP = 1, // TODO: Add comment...
    MGEFF_PROP_LOOPCOUNT = 2,
    MGEFF_PROP_DIRECTION = 3,
    MGEFF_PROP_CURFRAME = 4,
    MGEFF_PROP_STATE = 5,
    MGEFF_PROP_MAX
};

/*
 * Parameter Description:
 * handle - the property handle of the property being changed
 * id - the attribute's flag, the specific value can refer to the definition
   of EffAnimProperty
 * value - the property value to set
 */
Void mGEffAnimationSetProperty(MGEFF_ANIMATION handle, enum EffAnimProperty
Id, int value);
```

For example by mGEffAnimationSetProperty(animation, MGEFF_PROP_LOOPCOUNT, 5)
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
// TODO: Improve the sample program
    mGEffAnimationCreateGroup(enum EffAnimationType type);
    mGEffAnimationAddToGroup(MGEFF_ANIMATION group, MGEFF_ANIMATION
Animation);
```
// TODO: Add a description of the sample program
When creating an animation group, you can specify whether it is a parallel or
serial animation. The feature of parallel animation is that when the animation
group is executed, all the animations in the group are scheduled at the same
time. The effect of the performance is that these animations are being
performed at the same time; and the characteristics of the serial animation
When the animation group is executed, the intra-group animations will be
scheduled in sequence. The effect of the performance is that these animations
are performed in sequential order. %BR%
In addition, you can add an animation group to another group with the same
scheduling rules.

### Animation Context

An animation can set the context to carry more user information, and is often
used to append data to the property change callback function. The specific
method is very simple, as shown in the following code snippet:
%CODE{cpp}%
    Void onPropertyChanged(MGEFF_ANIMATION handle, void* target, int id, void*
Value)
    {
        Printf("Animation Context = %s\n",
(char*)mGEffAnimationGetContext(handle));
    }

    /* ... */
    Char* buffer = strdup("context");
    MGEFF_ANIMATION animation = mGEffAnimationCreate(NULL, onPropertyChanged,
0, MGEFF_INT);
    mGEffAnimationSetContext(animation, (void*)buffer);
    mGEffAnimationSetDuration(animation, 100);
    mGEffAnimationAsyncRun(animation);
```
This example will output:
// TODO:

### Effector effector

---++++ Effector create/delete

you should create an effector first, mgeff have defined some internal
effector:
- mGEffStr2Key get an has code for special effector name.
- mGEffEffectorCreate/mGEffEffectorDelete create or delete an effector.
- mGEffAnimationCreateWithEffector return an animation for the special
     effector.

%CODE{cpp}%
MGEFF_EXPORT unsigned long mGEffStr2Key (const char* str);

MGEFF_EXPORT MGEFF_EFFECTOR mGEffEffectorCreate(unsigned long key);
MGEFF_EXPORT void mGEffEffectorDelete(MGEFF_EFFECTOR handle);

MGEFF_EXPORT MGEFF_ANIMATION mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR
effector);

```

---++++ Effector property

Type of effector set property callback function:
- It is going to be called every frame.

Type of effector get property callback functio
- It is going to be called every frame.

Type of effector get property callback function:

%CODE{cpp}%
typedef int (*MGEFF_EFFECTOR_SETPROPERTY)(MGEFF_EFFECTOR effector,
        int property_id, int value);

typedef int (*MGEFF_EFFECTOR_GETPROPERTY)(MGEFF_EFFECTOR effector,
        int property_id, int* pValue);

```

---++++ Effector source/sink

Effector have two important elements:
- sink: sink is used for display, such as an MiniGUI DC.
- source: effector source is the input element, such as an bitmap resource.

%CODE{cpp}%

MGEFF_EXPORT int mGEffEffectorAppendSource(MGEFF_EFFECTOR effector,
        MGEFF_SOURCE source);

MGEFF_EXPORT int mGEffEffectorSetSink(MGEFF_EFFECTOR effector, MGEFF_SINK
sink);

```

---++++ Effector callback

Include follow callback function:
- Type of effector on draw callback function: It is going to be called
     every frame.
- Type of effector begin draw callback function: It is going to be called
     when you create an animation with calling.
- Type of effector end draw callback function: It is going to be called
     when the animation specified by animation is finished.
- Type of effector init/finalize callback function: It is going to be
     called when you create/delete an effector with calling

%CODE{cpp}%
typedef void (*MGEFF_EFFECTOR_ANIM_ONDRAW)(MGEFF_ANIMATION animation,
        MGEFF_EFFECTOR effector, HDC sink_dc, intptr_t id, void *value);

typedef void (*MGEFF_EFFECTOR_ONBEGINDRAW)(MGEFF_ANIMATION animation,
        MGEFF_EFFECTOR effector);

typedef void (*MGEFF_EFFECTOR_ONENDDRAW)(MGEFF_ANIMATION animation,
        MGEFF_EFFECTOR effector);

typedef MGEFF_EFFECTOR (*MGEFF_EFFECTOR_INIT)(MGEFF_EFFECTOR effector);

typedef void (*MGEFF_EFFECTOR_FINALIZE)(MGEFF_EFFECTOR effector);

```

---++++ Effector fill

Fills a DC with a predefined effector.

- This function creates and run an animation whose SetProperty callback is
     a effector specified by type. The sources of the effector are specified
by src1_dc and src2_dc respectively. The destination DC of the effector is
specified by \a dst_dc. The duration of the animation is specified by
duration.

%CODE{cpp}%
MGEFF_EXPORT int mGEffFillEffectorAnimation(HWND hwnd, HDC src1_dc, HDC
src2_dc,
        HDC dst_dc, unsigned long key, int duration);
```

---++++ Creating and Using Effects

Since mGEff The animation framework is provided, and the specific animation is
delivered to the user. However, some animation effects are relatively common.
If users are allowed to implement them each time, it is not conducive to code
reuse and it is not guaranteed that the implementation is optimal. and so
The concept of Effector was introduced in mGEff. Simply speaking, Effector
The commonly used animation effects are implemented and packaged for direct
use by the user. The following example shows how to create and execute a
Effector:

%CODE{cpp}%

// mGEff internal effector.

#define MGEFF_MINOR_leafwindow          "leafwindow"             /*< leaf
window */
#define MGEFF_MINOR_zip                 "zip"                    /*< zip
*/
#define MGEFF_MINOR_flip                "flip"                   /*< flip
*/
#define MGEFF_MINOR_cubicrotate         "cubicrotate"            /*< cubic
rotate */
#define MGEFF_MINOR_alpha               "alphablending"          /*< alpha
blending */
#define MGEFF_MINOR_scroll              "scrollpage"             /*<
scroll page */
#define MGEFF_MINOR_zoom                "zoominzoomout"          /*< zoom
*/
#define MGEFF_MINOR_push                "pushpoll"               /*< push
*/
#define MGEFF_MINOR_clear               "clear"                  /*< clear
*/
#define MGEFF_MINOR_centersplit         "centersplit"            /*<
center split */
#define MGEFF_MINOR_radarscan           "radarscan"              /*< radar
scan */
#define MGEFF_MINOR_fivepointedstar     "fivepointedstar"        /*< five
pointed star */
#define MGEFF_MINOR_roller              "roller"                 /*<
roller */
#define MGEFF_MINOR_blockflip           "blockflip"              /*< block
flip */
#define MGEFF_MINOR_es_cubicrotate      "opengles-cubicrotate"   /*<
OpenGL ES cubic rotate */
#define MGEFF_MINOR_es_rectrotate       "opengles-rectrotate"    /*<
OpenGL ES rect rotate */
#define MGEFF_MINOR_es_coverflow        "opengles-coverflow"     /*<
OpenGL ES cover flow */
#define MGEFF_MINOR_mgplus_rotate       "mgplus-rotate"          /*<
mGPlus rotate */
#define MGEFF_MINOR_mgplus_cubicrotate  "mgplus-cubicrotate"     /*<
mGPlus cubic rotate */
#define MGEFF_MINOR_mgplus_flip         "mgplus-flip"            /*<
mGPlus flip */

#define MGEFF_EFFECTOR_LEAFWINDOW
mGEffStr2Key(MGEFF_MINOR_leafwindow)         /*< leaf window */
#define MGEFF_EFFECTOR_ZIP                  mGEffStr2Key(MGEFF_MINOR_zip)
/*< zip */
#define MGEFF_EFFECTOR_FLIP                 mGEffStr2Key(MGEFF_MINOR_flip)
/*< flip */
#define MGEFF_EFFECTOR_CUBIC_ROTATE
mGEffStr2Key(MGEFF_MINOR_cubicrotate)        /*< cubic rotate */
#define MGEFF_EFFECTOR_ALPHA                mGEffStr2Key(MGEFF_MINOR_alpha)
/*< alpha */
#define MGEFF_EFFECTOR_SCROLL               mGEffStr2Key(MGEFF_MINOR_scroll)
/*< scroll */
#define MGEFF_EFFECTOR_ZOOM                 mGEffStr2Key(MGEFF_MINOR_zoom)
/*< zoom */
#define MGEFF_EFFECTOR_PUSH                 mGEffStr2Key(MGEFF_MINOR_push)
/*< push */
#define MGEFF_EFFECTOR_CLEAR                mGEffStr2Key(MGEFF_MINOR_clear)
/*< clear */
#define MGEFF_EFFECTOR_CENTERSPLIT
mGEffStr2Key(MGEFF_MINOR_centersplit)        /*< center split */
#define MGEFF_EFFECTOR_RADARSCAN
mGEffStr2Key(MGEFF_MINOR_radarscan)          /*< radar scan */
#define MGEFF_EFFECTOR_FIVEPOINTEDSTAR
mGEffStr2Key(MGEFF_MINOR_fivepointedstar)    /*< five pointed star */
#define MGEFF_EFFECTOR_ROLLER               mGEffStr2Key(MGEFF_MINOR_roller)
/*< roller */
#define MGEFF_EFFECTOR_BLOCKFLIP
mGEffStr2Key(MGEFF_MINOR_blockflip)          /*< block flip */
#define MGEFF_EFFECTOR_OPENGL_CUBICROTATE
mGEffStr2Key(MGEFF_MINOR_es_cubicrotate)     /*< OpenGL ES cubic rotate */
#define MGEFF_EFFECTOR_OPENGL_RECTROTATE
mGEffStr2Key(MGEFF_MINOR_es_rectrotate)      /*< OpenGL ES rect rotate */
#define MGEFF_EFFECTOR_OPENGL_COVERFLOW
mGEffStr2Key(MGEFF_MINOR_es_coverflow)       /*< OpenGL ES cover flow */
#define MGEFF_EFFECTOR_MGPLUS_ROTATE
mGEffStr2Key(MGEFF_MINOR_mgplus_rotate)      /*< mGPlus rotate */
#define MGEFF_EFFECTOR_MGPLUS_CUBIC_ROTATE
mGEffStr2Key(MGEFF_MINOR_mgplus_cubicrotate) /*< mGPlus cubic rotate */
#define MGEFF_EFFECTOR_MGPLUS_FLIP
mGEffStr2Key(MGEFF_MINOR_mgplus_flip)        /*< mGPlus flip */

```

<center> <img align="CENTER" alt="mgeff-effctor.png" src="%ATTACHURLPATH%/mgeff-effctor.png" /> </center>
<center>mGEff Effector suppport </center>

---++++ How to use Effector

- Create Effector.

%CODE{cpp}%

/**
 * \fn MGEFF_ANIMATION mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR
   effector);
 * \brief Creates a animation with a effector.
 *
 * This function creates an animation whose SetProperty callback is a effector
 * specified by \a effector and the id of the animation is specified by \a id.
 *
 * \param effector the handle of the effector.
 *
 * \return the handle of the newly created animaiton.
 *
 * \sa mGEffAnimationCreate, mGEffEffectorCreate.
 */
MGEFF_EXPORT MGEFF_ANIMATION mGEffAnimationCreateWithEffector(MGEFF_EFFECTOR
effector);

```

Follow sample is MGEFF_MINOR_zip, you can use all above effector that has been
support by mGEff.

%CODE{cpp}%

// follow test the MGEFF_MINOR_zip effector.

static int mGEffFillAnimation(HWND hWnd,
                              HDC src1_dc, HDC src2_dc, HDC dst_dc,
                              int duration)
{
    unsigned long key = mGEffStr2Key(MGEFF_MINOR_zip);

    MGEFF_EFFECTOR effector = mGEffEffectorCreate (key);
    MGEFF_SOURCE source1 = mGEffCreateSource (src1_dc);
    MGEFF_SOURCE source2 = mGEffCreateSource (src2_dc);
    MGEFF_SINK sink = mGEffCreateHDCSink (dst_dc);
    MGEFF_ANIMATION handle;

    mGEffEffectorAppendSource (effector, source1);
    mGEffEffectorAppendSource (effector, source2);
    mGEffSetBufferSink(sink, src1_dc);
    mGEffEffectorSetSink (effector, sink);

    mGEffEffectorSetProperty (effector, MGEFF_PROPERTY_DIRECTION,
MGEFF_DIRECTION_LDOWN2RUP);
    mGEffEffectorSetProperty (effector, MGEFF_PROPERTY_ZOOM, MGEFF_ZOOMOUT);

    handle = mGEffAnimationCreateWithEffector (effector);
    g_anim_handle = handle;

    mGEffAnimationSetDuration (handle, duration);
    mGEffAnimationSetFinishedCb (handle, anim_finished_cb);

#if 1
    mGEffAnimationAsyncRun (handle);
#else
    mGEffAnimationSyncRun (handle);
#endif

    mGEffEffectorDelete(effector);

    return 0;
}

```

## mGEFF use advanced
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
Int mGEffAnimationSyncRun(MGEFF_ANIMATION handle);

// Perform animations asynchronously
Int mGEffAnimationAsyncRun(MGEFF_ANIMATION handle);

// Wait for the asynchronous animation to end
MGEFF_BOOL mGEffAnimationWait(void* phWnd, MGEFF_ANIMATION handle);
```
Synchronous and asynchronous animation function is very simple, there is only
one animation handle parameters, create a good animation, its handle passed to
any function will run in the corresponding execution. and
mGEffAnimationWait
Function is used to wait for an asynchronous animation to complete, the first
parameter is the address of the current thread's form handle, the second
parameter is the animation handle to wait, after the call function will wait
until the animation is complete, but during the process can still be processed
Other news. %BR%
For asynchronous animation, you can pause or stop it during playback, and you
can resume or restart the animation after pause and stop:

%CODE{cpp}%
// Pause the animation
Void mGEffAnimationPause(MGEFF_ANIMATION handle);
// Resume the execution of the animation
Void mGEffAnimationResume(MGEFF_ANIMATION handle);

// stop the animation
Void mGEffAnimationStop(MGEFF_ANIMATION handle);
// restart animation
Void mGEffAnimationReStart(MGEFF_ANIMATION handle);
```

### Custom Effector

---++++ MGEFF_EFFECTOROPS

MGEFF_EFFECTOROPS contains whole info of an effector, if you want to custom an
effector, implement it, In the mGEff, it has defined some effector like the
follow, when you custom an your own effector, you do not need to implement all
the callback, but the ondraw callback must be include.

%CODE{cpp}%
typedef struct _EFFECTOROPS {
    char                         name[EFFECTORNAME_MAX_LEN + 1]; /*< name
of effector */
    enum EffVariantType          varianttype;                    /*<
variant type */
    MGEFF_EFFECTOR_INIT          init;                           /*< init
*/
    MGEFF_EFFECTOR_FINALIZE      finalize;                       /*<
finalize */
    MGEFF_EFFECTOR_ANIM_ONDRAW   ondraw;                         /*< on
draw */
    MGEFF_EFFECTOR_ONBEGINDRAW   begindraw;                      /*< begin
draw */
    MGEFF_EFFECTOR_ONENDDRAW     enddraw;                        /*< end
draw */
    MGEFF_EFFECTOR_SETPROPERTY   setproperty;                    /*< set
property */
    MGEFF_EFFECTOR_GETPROPERTY   getproperty;                    /*< get
property */
} MGEFF_EFFECTOROPS;

...;
#ifdef _MGEFF_ZIPEFFECTOR
extern MGEFF_EFFECTOROPS zipeffector;
#endif
...

```

---++++ Simple alphaeffector sample

An very easy alpha effector as follow:

%CODE{cpp}%
void effalphaeffector_ondraw(MGEFF_ANIMATION animation, MGEFF_EFFECTOR
_effector,
        HDC sink_dc, intptr_t id, void* value)
{
    EffEffector *effector = (EffEffector *)_effector;

    EffHDCSource *source1 = (EffHDCSource *) (effector->source_list.next);
    EffHDCSource *source2 = (EffHDCSource *) (source1->list.next);
    RECT rc1;
    RECT rc2;
    RECT rc_sink;

    effbaseeffector_rect(source1->hdc, &rc1);
    effbaseeffector_rect(source2->hdc, &rc2);
    effbaseeffector_rect(sink_dc, &rc_sink);

    if (sink_dc = HDC_INVALID) {
        SetMemDCAlpha (source2->hdc, MEMDC_FLAG_SRCALPHA,  (*(float*)value)
* 255);
        BitBlt (source1->hdc, rc1.left, rc1.top, RECTW(rc1),
                RECTH(rc1 ), sink_dc, rc_sink .left, rc_sink .top, 0);
        BitBlt (source2->hdc, rc2.left, rc2.top, RECTW(rc2 ),
                RECTH(rc2 ), sink_dc, rc_sink.left, rc_sink.top, 0);
    }
}

MGEFF_EFFECTOROPS alphaeffector =
{
    MGEFF_MINOR_alpha,
    MGEFF_FLOAT,
    NULL,
    NULL,
    effalphaeffector_ondraw,
    NULL,
    NULL,
    NULL
};
```

---++++ Complex zoomeffector sample

if you want to implement an complex effector, you can see the zoom effector in
the mGEff:

- init/finalize: malloc or free your own context var, like EffZoomCtxt is
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
    RECT prev_rc;
}EffZoomCtxt;

MGEFF_EFFECTOR effzoomeffector_init(MGEFF_EFFECTOR _effector)
{
    EffEffector *effector = (EffEffector *)_effector;
    EffZoomCtxt* zoom_context = (EffZoomCtxt*)calloc(1, sizeof(EffZoomCtxt));
    effector->context = zoom_context;
    return _effector;
}

void effzoomeffector_begindraw(MGEFF_ANIMATION animation, MGEFF_EFFECTOR
_effector)
{
...
    mGEffAnimationSetStartValue (animation, &rc_s);
    mGEffAnimationSetEndValue (animation, &rc_e);
...
}

void effzoomeffector_finalize (MGEFF_EFFECTOR _effector)
{
    EffEffector *effector = (EffEffector *)_effector;
    free (effector->context);
}

int effzoomeffector_setproperty(MGEFF_EFFECTOR _effector, int property_id, int
value)
{
    EffEffector *effector = (EffEffector *)_effector;
    EffZoomCtxt* zoom_context = (EffZoomCtxt*)effector->context;
    switch (property_id)
    {
        case MGEFF_PROPERTY_ZOOM:
            if (value >= MGEFF_ZOOMIN &&
                    value <= MGEFF_ZOOMOUT)
            {
                zoom_context->zoom = value;
                return 0;
            }
            break;
        default:
            return effbaseeffector_setproperty(_effector, property_id, value);
    }
    return -1;
}

int effzoomeffector_getproperty(MGEFF_EFFECTOR _effector, int property_id,
int* value)
{
    EffEffector *effector = (EffEffector *)_effector;
    EffZoomCtxt* zoom_context = (EffZoomCtxt*)effector->context;
    switch (property_id)
    {
        case MGEFF_PROPERTY_ZOOM:
        {
            if (value)
                *value = zoom_context->zoom;
            return zoom_context->zoom;
        }

        default:
            return effbaseeffector_getproperty(_effector, property_id, value);
    }
    return -1;
}

MGEFF_EFFECTOROPS zoomeffector =
{
    MGEFF_MINOR_zoom,
    MGEFF_RECT,
    effzoomeffector_init,
    effzoomeffector_finalize,
    effzoomeffector_ondraw,
    effzoomeffector_begindraw,
    NULL,
    effzoomeffector_setproperty,
    effzoomeffector_getproperty

};
```

### Custom Power Curves

The essence of the curve is a transformation function that controls the
interpolation speed between 0 and 1.

- MGEFF_MOTIONCURVE_CB: Type of the value calculating callback of the
     motion curve function, you can implement your own curve change.

%CODE{cpp}%
enum EffMotionType {
....
    SineCurve, /*< Sine Curve */
    CosineCurve, /*< Cosine Curve */
    Custom,  /*< This is returned if the user specified a custom curve
type. */
    NCurveTypes
};

MGEFF_EXPORT void  mGEffAnimationSetCurveEx(MGEFF_ANIMATION handle,
        MGEFF_MOTIONCURVE_CB cb);

typedef float (*MGEFF_MOTIONCURVE_CB)(float progress);

```

An simple custom curve sample:

%CODE{cpp}%
float calcCustom(float t)
{
    return t*t*t/3.0 + t*t/3.0 + t/3.0;
}

//Custom
TEST(MotioncurveTest, Custom) {
   mGEffInit();
    MGEFF_ANIMATION animation = mGEffAnimationCreate(NULL, test_cb, Custom,
MGEFF_FLOAT);
    mGEffAnimationSetStartValue(animation, &start);
    mGEffAnimationSetEndValue(animation, &end);
    mGEffAnimationSetDuration(animation, duration);
    mGEffAnimationSetCurveEx(animation, &calcCustom);
    t0 = 10 * times(NULL);
    mGEffAnimationSyncRun(animation);
    mGEffAnimationDelete(animation);
    mGEffDeinit();
}
```


## Comments



