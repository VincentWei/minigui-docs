# Advanced `GDI` Functions Based on `NEWGAL`
It is mentioned in Chapter 13 that MiniGUI 1.1.0 has greatly improved `GAL` and
`GDI` by rewriting almost all code. Those new interfaces and functions strongly
enhance the graphics capability of MiniGUI. In this chapter we will introduce
the related concepts and interfaces of new `GDI` interface in detail.

## New Region Implementation
New `GDI` uses new region algorithm, which is popularly used in X Window and
other GUI systems. This region is called x-y-banned region, featured as follow:
- Region is constituted by non-null rectangles that is not intersected each
other. 
- Region can be divided into several non-intersected horizontal strip, each of
which has the rectangles with same width and top-aligned; In other words, all
rectangles have the same y coordinates on the upper-left corner.
- The rectangles rank from left to right at the x direction, and then form top
to bottom at y direction.

`GDI` can use the special property of x-y-banned region to optimize the 
drawing. Those drawing functions that will be added into the future version 
will use this property to optimize plotting output.

New `GDI` adds the following interfaces, which can be used to do operations
between regions (minigui/gdi.h):

```   
```
- `PtInRegion` check if the given point locates in the given region.
- `RectInRegion` check if the given rectangle intersects with the given region.
- `OffsetRegionEx` offsets the clip region located in the intersection of two
given rectangles, one is the rectangle the original clip region belongs to, and
the other is the one which offset region belongs to. And then form a clip 
region which belong to both the offset part of the orignal region and the
intersection of the two rectangles.
- `OffsetRegion` just offsets the given region.
- `IntersectRegion` can be used to calculate the intersection of two given
region. 
- `UnionRegion` can merge two different regions. The merged region is still a
region of x-y-banned.
- `SubstractRegion` subtracts one region from another.
- `XorRegion` is used to perform the `XOR` (Exclusive `OR)` operation between
two regions. The result equals to the intersection between the result A that
src1 subtracts src2 and the result B that src2 subtracts src1.

Apart from the region operation functions above, MiniGUI also provides those 
`GDI` functions that created from the closed curve such as polygon and ellipse.
These functions can limit `GDI` output within the specially closed curve. These
functions will be discussed in the following sections.

## Raster Operations
Raster operation specifies the operation between the target pixel and the pixel
existed on the screen while drawing. The most popular one is alpha blending.
Here the raster operation refers to binary bit operation, including `AND,` 
`OR,` `XOR,` and directly overwrite (SET). Application can use
`SetRasterOperation` function and `GetRasterOperation` function to set or get
current raster operation. The prototypes of these two functions are as follow
(minigui/gdi.h): 

```
```

In the function, rop is the raster operation mode. The optional parameters are
`ROP_SET` (directly set), `ROP_AND` (do bit-AND with the pixels on the screen),
`ROP_OR` (do bit-OR with the pixels on the screen) and `POP_XOR` (do
exclusive-OR with the pixels on the screen).

After setting new raster operation, the subsequent graphics output will be
affected by it. Those drawing functions include `SetPixel,` `LineTo,` Circle,
Rectangle, `FillCircle,` and `FillBox.` Please notice, new `GDI` function has a
new rectangle filling function - `FillBox.` `FillBox` function is not 
influenced by the current raster operation, just because `FillBox` realize
Rectangle filling by using Hardware acceleration function, and its filling 
speed is very high.

## Memory `DC` and `BitBlt`
New `GDI` function boosts up the memory `DC` operation function. `GDI` function
will call `GAL-related` interface while setting memory `DC` as it will fully 
use the hardware acceleration of video adapter to quickly move or copy the bit
blocks between different regions, including transparence processing and alpha
blending. Application can create a memory `DC` with the property that each 
point has different alpha value. Also, application can create the alpha value
(alpha channel of the `DC)` of all pixels of memory `DC` by using 
`SetMemDCAlpha,` then use `BitBlt` and `StretchBlt` to transfer the bits 
between `DCs.` Application also can set the transparent pixel of a source `DC,`
so as to leap over such pixel while performing `BitBlt.`

`GDI` functions regarding memory `DC` are as follow (minigui/gdi.h):

```
```

`CreateCompatibleDC` creates a memory `DC` compatible with given `DC.`
Compatibility means that the pixel format, width and height of new created
memory `DC` are same with the given `DC.` Memory `DC` based on this format can
be quickly blit to the compatible `DC.`

Now we further explain the pixel format. Pixel format includes the depth of
color (that is, the number of bits per pixel), palette, or the format of four
components of `RGBA` (red, green, blue, and alpha). The parameter alpha can be
seen as the transparence degree of one pixel point, 0 means 100% transparent,
255 means completely opaque. If the degree of color below 8, `GAL` will create 
a default palette and you can call the function `SetPalette` to modify the
palette. If the degree is higher than 8, MiniGUI will respectively appoint the
bits taken up by the `RGBA` parameters of the given pixel. Compatible memory 
`DC` has the same color degree with the given `DC,` and has the same palette or
`RGBA` parameter combination format.

Calling function `CreateMemDC` can specify the height, width, color depth, and
necessary `RGBA` components combination format of the new created memory `DC.`
MiniGUI use bit mask taken up by each pixel to represent the combination format
of `RGBA` components. For example, to create a 16-bit memory `DC` including
per-pixel alpha value, you can use four 4-bit to assign 16-bit pixel, thus the
mask of the four components of `RBGA` will respectively be: 0x0000F000,
0x00000F00, 0x000000F0, and 0x0000000F.

`ConvertMemDC` is used to convert a specified memory `DC` according to the 
pixel format of given referencing `DC.` This conversion makes the result `DC`
has the same pixel format with referencing `DC.` Thus, the converted `DC` can 
be quickly blitted to the compatible `DC.`

`SetMemDCAlpha` is used to set or delete the alpha channel value of whole 
memory `DC.` We can use `MEMDC_FLAG_RLEACCEL` to specify the memory `DC` adopt
or delete the `RLE` encoding format. Alpha channel value will function on all
pixels of the `DC.`

`SetMemDCColorKey` is used to set or delete the color key of whole memory `DC`
object, that is, the transparent pixel value. We can also use
`MEMDC_FLAG_RLEACCEL` to specify memory `DC` adopt or delete the `RLE` encoding
format. 

`CreateMemDCFromBitmap` can create a memory `DC` compatible with given `DC` 
that point to device relative Bitmap, and it can be quickly copy and exchange 
to display from bitmap.

`CreateMemDCFromMyBitmap` create a memory `DC` which point to device unrelative
bitmap. 

Similar to other `DCs,` you can also call `GDI` drawing function to perform any
drawing output operation in memory `DC` and then blit it to other `DC.` Code in
List 1 comes from gdidemo.c program of `MDE,` which demonstrates how to use
memory `DC` to realize transparent and alpha blending blitting operation 
between `DCs.`


List 1 The enhanced memory `DC` operations
```
```

## Enhanced `BITMAP` Operations
New `GDI` function enhances the `BITMAP` structure and adds support to
transparent and alpha channel as well as. By setting such memberships as 
`bmType,` `bmAlpha,` and `bmColorkey` of a `BITMAP` object, you can get certain
properties. Then you can use function `FillBoxWithBitmap/Part` to draw the
`BITMAP` object to certain `DC.` You can regard the `BITMAP` object as the
memory `DC` created in system memory, but you cannot perform drawing output to
the `BITMAP` object. Code in List 2 loads a bitmap object from an image file,
set transparency and alpha channel, and finally use function 
`FillBoxWithBitmap` to output to a `DC.` This program comes from the demo
program gdidemo.c of mg-samples.


List 2 The enhanced `BITMAP` operations
```
```
You can also convert a certain `BITMAP` object to memory `DC` object by using
function `CreateMemDCFromBitmap.` The prototype of this function is as follows
(minigui/gdi.h): 

```
```
The memory `DC` created from a `BITMAP` object directly uses the memory to 
which `bmBits` of the `BITMAP` object points. The memory lies in system memory,
but not video memory.

New `GDI` also enhances the `BITMAP-related` `MYBITMAP` structure. `MYBITMAP`
can be seen as a bitmap structure that is not dependent to the device. You can
also convert one `MYBITMAP` object to a memory `DC` by using function
`CreateMemDCFromMyBitmap.` The prototype of this function is as follows
(minigui/gdi.h): 

```
```
Most `GAL` engines are unable to provide hardware acceleration for blitting
operation which transfers pixels from system memory to video memory, therefore,
the `FillBoxWithBitmap` function, the `BITMAP` object or the memory `DC` 
created by `MYBITMAP` object are unable to be quickly blitted to other `DC`
through hardware acceleration. The support for such acceleration can be 
achieved by pre-created memory `DC` in video memory.

## New `GDI` functions
Apart from raster operation, MiniGUI also adds some useful `GDI` functions,
including `FillBox,` `FillCircle,` and so on. The new `GDI` functions are:

```
```
- `FillBox` fills specified rectangle.
- `FillCircle` fills specified circle, affected by raster operation.
- `ScaleBitmap` scales a `BITMAP` object
- `GetBitmapFromDC` copies pixels which the scope is in a specified rectangle 
to a `BITMAP` object.
- `GetPixelInBitmap` gets pixel value of a given position in a `BITMAP` object.
- `SetPixelInBitmap` sets pixel value of a given position in a `BITMAP` object.

## Advanced `GDI` functions
### Image Scaling Functions
The following functions can be used to paint and scale an image simultaneously.

```
```
- `StretchPaintImageFromFile` stretches and paints an image from file. 
Parameter hdc is device context. Parameter x and y are painting position on
device. Parameter w is the width of the stretched bitmap. Parameter h is the
height of the stretched bitmap. Parameter `spFileName` is the file name.
- `StretchPaintImageFromMem` stretches an image from memory. Parameter hdc is
device context. Parameter x and y are painting position on device. Parameter w
is the width of the stretched bitmap. Parameter h is the height of the 
stretched bitmap. Parameter mem points to memory containing image data and
parameter size is the size of the image data. Parameter ext is the type of
bitmap. 
- `StretchPaintImageEx` paints and stretches an image from data source onto
device directly. Parameter hdc is device context. Parameter x and y are 
painting position on device. Parameter w is the width of the stretched bitmap.
Parameter h is the height of the stretched bitmap. Parameter area points to 
data source and parameter ext is the extension the type of bitmap.

### Image Rotation Functions
The following functions can be used to paint an `BITMAP` object and rotate it.
```
```
- `PivotScaledBitmapFlip` rotates, stretches, shrinks, or flips a bitmap 
object. The unit of rotation is 1/64 degree in this function. Parameter hdc is
device context. Parameter bmp is a `BITMAP` object pointer. Parameter x and y
are rotation center on `DC.` Parameter (cx, cy) is the rotation center on the
bitmap. The data type of x, y, cx, cy are fixed-point values. Parameter angle 
is the degree of rotation. Parameter `scale_x` and `scale_y` are proportion of
scaling. Parameter `h_flip` and `v_flip` are flags for flipping horizontally or
flipping vertically.
- `RotateBitmap` rotates a bitmap object surrounded its center. Parameter hdc 
is the graphic device context handle. Parameter bmp is the pointer to a 
`BITMAP` object. Parameter lx and ly are upper-left coordinate of bitmap on 
`DC.` Parameter angle is the degree of rotation. The unit of rotation is 1/64
degree. 
- `PivotBitmap` aligns the point in the bitmap given by parameter (cx, cy) to
parameter (x, y) in device context. Parameter hdc is the device context.
Parameter bmp is the pointer to a `BITMAP` object. Parameter x and y are
rotation center on `DC.` Parameter (cx, cy) is the rotation center on the
bitmap. Parameter angle is the degree of rotation. The unit of rotation is 1/64
degree. 
- `RotateScaledBitmap` stretches or shrinks a bitmap object at the same as
rotating it. Parameter hdc is the device context. Parameter bmp is the pointer
to a `BITMAP` object. Parameter lx and ly are upper-left coordinates of bitmap
on `DC.` Parameter angle is the degree of rotation. The unit of rotation is 
1/64 degree. Parameter w and h are width and height of the stretched bitmap.
- `RotateBitmapVFlip` flips vertically and rotates a bitmap object. See also
`RotateBitmap.` 
- `RotateBitmapHFlip` flips horizontally and rotates a bitmap object. See also
`RotateBitmap.` 
- `RotateScaledBitmapVFlip` flips vertically, rotates, stretch or shrinks a
bitmap object. This function is similar to `RotateScaledBitmap` expect that it
flips the bitmap vertically first.
- `RotateScaledBitmapHFlip` flips horizontally, rotates, stretches or shrinks a
bitmap object. For the means of parameters, please refer to 
`RotateScaledBitmap.` 

### Rounded Corners Rectangle
The follow function draws a rounded corners rectangle

```
```
Here, hdc is the graphic device context handle. x0 and y0 are coordinates of
upper-left corner of the rectangle; x1 and y1 are coordinates of lower-right of
the rectangle; rw and rh are the x-radius and y-radius of the rounded corners
respectively. 

## Curve Generators
A general graphics system usually provides the user with the drawing functions
to plot line and complicated curve, such as ellipse, and spline. Users can use
this function to plot, but unable to do other jobs by using the existed
curve-generating algorithms. In the development of new `GDI` interface, we use 
a special design pattern to implement drawing of curve and filling of closed
curve. This way is very flexible and provides you a chance of directly using
system internal algorithm:
- System defines several functions used to create line and curve. We call these
functions curve generators.
- You need to define a callback and pass this function address to curve
generator before calling a generator. The curve generator will call this
callback while generating a point on the curve or a horizontal line of closed
curve. 
- You can finish some operations based on new point or new horizontal line. For
the MiniGUI drawing function, that means drawing the point or the line.
- As callback is frequently called on during the generator operating process,
system allows you to pass a pointer to represent context while calling the 
curve generator. The generator will pass this pointer to your callback.

We will describe curve and filling generator provided by MiniGUI in the
following sections.

### Line Clipper and Line Generator
The prototype of the line clipper and generator is as follows:

```
```
`LineClipper` is not a generator, which is used to clip the given line into a
rectangle. Cliprc is the given rectangle, while _x0, _y0, _x1, and _y1 present
the two end-points of the line that will be clipped into cliprc and then return
to the end-points of the clipped line. MiniGUI internally uses Cohen-Sutherland
algorithm to clip a line.

`LineGenerator` is the line generator using Breshenham algorithm. The generator
starts from the beginning point of given line, every time when it generates a
point it will call the callback function and pass context as well as the step
forward value or amount of difference between new point and the previous one.
For example, passing stepx = 1, stepy = 0 indicate that the new point is one
step forward then the previous point at x coordinate, while y coordinate keeps
the same. The callback function can realize the optimization at certain degree
on the basis of step forward value.

### Circle Generator
The prototypes of `MiniGUI-defined` circle generator are as follow:

```
```
You should firstly specify the coordinates of center of the circle and the
radius, and then pass information of context and the callback function. Every
time when it generates a point, the generator will call the callback function
once, at the same time it passes three values: x1, x2, and y. These three 
values actually indicate two points on the circle: (x1, y) and (x2, y). Because
of the symmetry property of circle, the generator can get all points on the
circle by calculating only 1/4 of points in the circle.

### Ellipse Generator
Similar to circle generator, the prototypes of ellipse generator are as follow:
```
```
You should firstly specify the coordinates of center of ellipse and the radius
of x coordinate and y coordinate, and then pass the context and the callback
function. Every time when it generates a point, the generator will call the
callback function once, at the same time it passes three values: x1, x2, and y.
These three values actually indicate two points in the ellipse: (x1, y) and 
(x2, y). Because of the symmetry property of ellipse, the generator can get all
points in the ellipse by calculating only half of points of the ellipse.

### Arc Generator
The `MiniGUI-defined` arc generator can be seen as follows:

```
```

You should firstly specify the center of the arc, the radius, the starting 
angle and the end angle. It is necessary to note that the unit of the starting
angle and end angle is integers in 1/64 degree, not float-point numbers. Then
you pass the callback function. Every time when it generates a point on the 
arc, the function will call the callback function and pass the coordinates 
value (x, y) of a new point on the arc.

### Vertical Monotonous Polygon Generator
Generally speaking, polygons include protruding polygons and concave polygons.
Here the vertical monotonous polygon is a special polygon produced for
optimizing polygon algorithm in the computer graphics. The definition of this
kind of polygon is: all the horizontal lines of the computer screen and the 
side of polygon can only have one or two points of intersection. Figure 1 gives
examples of protruding polygon, concave polygon, and vertical monotonous
polygon. 


<img src="%ATTACHURLPATH%/15.1_T.jpeg" alt="15.1_T.jpeg" `ALIGN="CENTER"` />

Figure 1 Polygons

It is necessary to note that a protruding polygon must be vertical monotonous
polygon, but a vertical monotonous polygon can be concave polygon. Obviously,
normal polygon filling algorithms need to determine the number of intersection
point between polygon and the screen scan line while vertical monotonous
polygons not. Therefore, the speed of polygon filling can be greatly increased.

The prototypes of `MiniGUI-defined` vertical monotonous polygon related
functions are as follow:

```
```

`PolygonIsMonotoneVertical` is used to determine if a given polygon is vertical
monotonous polygon while `MonotoneVerticalPolygonGenerator` is the generator of
vertical monotonous polygon. In MiniGUI, the vertices of the polygon represent 
a polygon. Pts represents the vertices array while vertices represents the
number of the vertices. What generator generates actually are the end-points
(x1, y) and (x2, y) of each horizontal line to filling the polygon.

### General Polygon Generator
MiniGUI also provides the general polygon generator, which can be used to
process protruding polygons and concave polygons. The prototypes are as follow:

```
```

Similar to vertical monotonous polygon generator, what this function generates
are horizontal scan lines for filling the polygon: x1 is the beginning x
coordinates of the horizontal line; x2 is the end x coordinate; y is the y
coordinate of horizontal line.

### Flood Filling Generator
with the one at the start position (Like water spreading, so called flood
filling). Between the starting point and the ending point, it fills certain
region according to a given color. During this process, we need two callback
functions, one of which is used to determine if the encountered point is the
same with the starting one; another callback function is used to generate the
horizontal scan line of the filling region. When plotting what this function
compares is pixel, but actually it can be used to compare any other values so 
as to finish the special spreading actions.

MiniGUI defines flood-filling generator as follows:

```
```

The function `cb_equal_pixel` is called to determine if the target point is 
same with the staring point. The pixel of starting point can be transferred by
context. The function `cb_flood_fill` is used to fill in a scan line. It passes
the end-points of the scan line, that is, (x1, y) and (x2, y).

### Using Curve Generator
The way of using curve and filling generator is very simple. We firstly see how
MiniGUI uses the curve and filling generator in its internal in order to deeply
understand them.

The program paragraph comes from `FloodFill` function of MiniGUI
(src/newgdi/flood.c): 
```
```

This function calls `FloodFillGenerator` after some necessary initialization 
and passes context pdc (pdc is the data structure in MiniGUI internal to
represent `DC)` and two callback functions: `equal_pixel` and
_flood_fill_draw_hline. Before this, the function gets the pixel value of
starting point and stored it in pdc->skip_pixel. Function `equal_pixel` gets 
the pixel value of the given point and returns the value after comparing to
pdc->skip_pixel; _flood_fill_draw_hline calls internal functions to plot
horizontal line.

This way can greatly decrease the complexity of codes while increase their 
reuse capability. Readers who are interested in this can compare the function
`LineTo` between old and new `GDI` interfaces.

The main aim of designing generator is to facilitate the users. For example, 
you can use `MiniGUI’s` curve generator to finish your job. The example below
assumes that you use a circle generator to plot a circle with 4-pixel wide:

```
```

The use of curve generator is very simple. Its structure is also very clear. 
You can learn this way during your own application developing.

## Plotting Complex Curve
Based on the curve generator described in 15.7, MiniGUI provides the following
basic curve plotting functions:

```
```
- `MoveTo` moves current starting point of pen to given point (x, y), specified
in logical coordinates.
- `LineTo` draws line from current starting point to a given point (x, y),
specified in logical coordinates.
- Rectangle draws a rectangle with the vertices as (x0, y0) and (x1, y0).
- `PollyLineTo` uses `LineTo` to draw a poly-line. Pts specify each of the
vertices of poly-line while vertices specify the number of vertices.
- `SplineTo` uses `LineTo` function to draw spline. Four points can determine
the only one spline, that is, pts is a pointer to a 4-point structure array.
- Circle draws a circle with the center of (sx, sy) and radius of r, specified
in logical coordinates.
- Ellipse draws an ellipse with the center of (sx, sy), x coordinate radius of
rx, and y coordinate radius of ry.
- `CircleArc` draws a circle arc. The center of the circle is (sx, sy), radius
is r, and the starting angel and ending angle of the arc is ang1 and ang2
respectively. Ang1 and ang2 use 1/64 degree as unit.

Let's see the use of Circle and Ellipse functions. Assuming there are two given
points, pts[0] and pts[1]. pts[0] is the center of circle or ellipse, while
pts[1] is a vertex of the bounding rectangle of them. Following code fragment
plots the circle or ellipse specified by the two points:

```
```

## Filling Enclosed Curve
MiniGUI provides following enclosed curve filling functions:
```
```
- `FillBox` fills a specified rectangle, the upper-left corner of which is (x,
y), the width is w and the height is h. All are specified in logical
coordinates. 
- `FillCircle` fills a given circle with center of (sx, sy), radius of r (in
logical coordinates).
- `FillEllips` fills a given ellipse with the center of (sx, sy), x coordinate
radius of rx, and y coordinate of ry (in logical coordinates).
- `FillPolygon` fills polygons. Pts means each vertex of the polygon, vertices
means the number of those vertices.
- `FloodFill` does the flood filling from given point (x, y).

Note that all filling functions use the property of current brush (color) and
affected by raster operation.

The following example illustrates how to use `FillCircle` and `FillEllipse` to
fill a circle or an ellipse. Assuming two given points: pts [0] and pts [1], 
pts [0] is the center of circle or ellipse while pts [1] is a vertex of the
bounding rectangle of the circle or the ellipse.

```
```

## Building Complex Region
Apart from using curve generator and filling generator to plot a curve or fill 
a closed curve, we can also use the generators to build a complex region
enclosed by closed curve. As we know, the region in MiniGUI is formed by
non-intersected rectangles and meets the x-y-banned rule. Using above polygon 
or enclosed curve generator can regard each scan line as a rectangle with the
height of one. Thus, we can use these generators to build complex region.
MiniGUI uses existed enclosed curve generator to implement the following 
complex region generating functions:

```
```

Using such functions we can initialize certain region as circle, ellipse, or
polygon region. Then, we can use this region to perform hit-test (PtInRegion 
and `RectInRegion),` or select into a `DC` as the clipped region to get special
painting effect. Figure 2 is a special region effect given by gdidemo.c of
mg-samples. The code building the special regions showed by Figure 2 is listed
in List 3.


List 3 Creating special regions
```
```


<img src="%ATTACHURLPATH%/15.2.jpeg" alt="15.2.jpeg" `ALIGN="CENTER"` />

Figure 2 The output effect of special regions

## Visiting Frame Buffer Directly
In new `GDI` interfaces we add the function used to directly visit the video
frame buffer. The prototype is as follows:

```
```
- `LockDC` locks the specified rectangle region of given `DC,` then returns a
pointer which points to the video frame buffer. When width, height and pitch 
are not `NULL,` the function `LockDC` will return the valid width, height and
pitch of the locked rectangle.
- `UnlockDC` function unlocks a locked `DC.`

To lock a `DC` means that MiniGUI has entered a state of using exclusive way to
visit video frame buffer. If the locked `DC` is a screen `DC,` the function 
will hide the mouse cursor when necessary and lock global clipping region. 
After locking a `DC,` program can visit locked frame buffer by using the
returned pointer of this function. `DC` cannot be locked for a long time,
neither calling other system calls while locking a `DC.`

Assuming we use the upper-left corner of locked rectangle as the origin to 
build coordinate system, x coordinate is horizontally rightward while y
coordinate is vertically downward. We can use following formula to calculate 
the address corresponding to (x, y) point (assume the returned pointer value is
`frame_buffer):` 

```
```
According to the color depth of the `DC,` we can perform read and write
operation to the pixel. The following code fragment randomly fills a locked
region: 

```
```


## Advanced Two-Dimension `GDI` Functions
We added advanced two-dimension `GDI` functions in MiniGUI 1.5.x to support the
development of advanced graphics applications. We can use these advanced
two-dimension `GDI` function to set the advanced `GDI` properties such as pen
width, pen type, and/or filling model. We will introduce the use of such
advanced two-dimension `GDI` functions in this section.

### Pen and Its Properties
Pen is a logical object used by MiniGUI to describe line drawing. We can
determine the drawing activity by setting properties of a pen. Those properties
include: 
- Pen types. A pen has following types (Fig. 15.3 gives several kinds of 
effects of pen):
- `PT_SOLID:` The Solid pen.
- `PT_ON_OFF_DASH:` The on/off dash pen, even segments are drawn; odd segments
are not drawn. The length of every dash/solid line segment is specified by
`SetPenDashes.` 
- `PT_DOUBLE_DASH:` The double dash pen, even segments are normally. Odd
segments are drawn in the brush color if the brush type is `BT_SOLID`, or in 
the brush color masked by the stipple if the brush type is `BT_STIPPLED`.


<img src="%ATTACHURLPATH%/15.3.jpeg" alt="15.3.jpeg" `ALIGN="CENTER"` />

Figure 3 Pen types

- Width of pen. The width of pen controls the width of the plotted line 
segment. The width of painting pen uses pixel as unit. The default width is
zero, we usually call the solid pen with the width of 0 as zero pen. General
two-dimension `GDI` function of MiniGUI uses zero pen.
- The cap style of pen. The cap style determines the shape of end point of the
line segment (see Figure 4). It can be divided into the following styles:
- `PT_CAP_BUTT:` The ends of the lines are drawn squared off and extending to
the coordinates of the end point.
- `PT_CAP_ROUND:` the ends of the lines are drawn as semicircles with the
diameter equal to the line width and centered at the end point.
- `PT_CAP_PROJECTING:` The ends of the lines are drawn squared off and 
extending half the width of the line beyond the end point.


<img src="%ATTACHURLPATH%/15.4.jpeg" alt="15,4.jpeg" `ALIGN="CENTER"` />

Figure 4 Cap styles of pen
- The join style of pen。The joining style of pen determines the way of the
connection between two line segments (see Figure 5). It is divided into the
following styles:
- `PT_JOIN_MITER:` The sides of each line are extended to meet at an angle.
- `PT_JOIN_ROUND:` a circular arc joins the sides of the two lines.
- `PT_JOIN_BEVEL:` the sides of the two lines are joined by a straight line,
which makes an equal angle with each line.


<img src="%ATTACHURLPATH%/15.5.jpeg" alt="15.5.jpeg" `ALIGN="CENTER"` />

Figure 5 The join styles of pen

Table 1 gives the operations on pen properties.

Table 1 Operating functions on pen properties

| *Function* |*Purpose*|
| `GetPenType/SetPenType` |Get/Set pen type|
| `GetPenWidth/SetPenWidth` |Get/Set pen width|
| `GetPenCapStyle/SetPenCapStyle` |Get/Set pen cap style|
| `GetPenJoinStyle/SetPenJoinStyle` |Get/Set pen join style|


Before using dash pen, we need use `SetPenDashes` function to set the 
dash/solid means of pen. The prototype of this function is as follows:

```
```

This function uses value in non-signed byte array to in turn represent the
length of dash/solid line segments. For example, when `dash_list` = “\1\1”, the
length of solid line segment is 1 pixel wide while length of dash line segment
is also 1 pixel wide, it is so-called dot-line; if `dash_list=”\4\1”,` it is
lineation; if `dash_list=”\4\1\1\1,` it is lineation-dotline; if
`dash_list=”\4\1\1\1\1\1”,` it is lineation-dot-dotline. The above dash model
can be seen in Figure 6. It should be noted that draw solid line segment itself
is affected by other properties of painting pen, such as cap style of pen.


<img src="%ATTACHURLPATH%/15.6.jpeg" alt="15.6.jpeg" `ALIGN="CENTER"` />

Figure 6 Dash lines

The argument `dash_offset` of function `SetPenDashes` represents the starting
place of dash/solid line segment in actual lines, usually is 0; the argument n
means the length of `dash_list` non-signed byte array.

### Brush and Its Properties
Brush is a logical object used to describe filling ways. The properties of the
brush are simpler than pen. MiniGUI provides the following brush types:
- `BT_SOLID:` The solid brush drawing with the current brush color.
- `BT_TILED:` The tiled bitmap brush drawing with a tiled bitmap.
- `BT_STIPPLED:` The transparent stippled bitmap brush drawing by using the
stipple bitmap. Pixels corresponding to bits in the stipple bitmap that are set
will be drawn in the brush color; pixels corresponding to bits that are not set
will be left untouched.
- `BT_OPAQUE_STIPPLED:` The opaque stipple bitmap brush drawing by using the
stipple bitmap. Pixels corresponding to bits in the stipple bitmap that are set
will be drawn in the brush color; pixels corresponding to bits that are not set
will be drawn with the background color.
Using function `GetBrushType/SetBrushType` can get and set the type of brush.

If the brush type is not solid, we need use `SetBrushInfo` to set the bitmap or
stippled bitmap used by the brush. The prototype of this function is as 
follows: 

```
```

The tiled bitmap is object of `BITMAP` in MiniGUI, while stippled bitmap is
represented by `STIPPLE` structure.

We can treat stippled bitmap as monochrome bitmap, each bit of which represents
a pixel. When the bit gets 1, it means that the drawing is based on brush 
color; when the bit gets 0, it means that the drawing is based on background
color (brush type is `BT_OPAQUE_STIPPLED)` or reservation (brush type is
`BT_STIPPLED).` The `STIPPLE` structure is defined as follows:

```
```
The following stipple bitmap can be used to represent slanting squares:
```
```

There is an important concept when using brush, that is, the origin point of
brush. The origin point of a brush determines the starting filling position of
the brush bitmap. The upper-left corner of tiled bitmap or stippled bitmap will
be aligned to the brush origin. By default, the brush origin is the origin of
`DC.` Sometimes application need to reset the brush origin, it can call 
function `SetBrushOrigin.`

### Advanced Two-Dimension Drawing Functions
When configuring MiniGUI, we can enable the advanced two-dimension `GDI`
functions by using option --enable-adv2dapi. When MiniGUI includes the 
interface of advanced two-dimension `GDI` functions, all of the filling-typed
functions mentioned before will be affected by the properties of current brush.
These functions include `FillBox,` `FillCircle,` `FillEllipse,` `FillPolygon,`
`FloodFill,` and so on. However, basic line/curve drawing functions will not be
affected by the properties of pen. Those functions include `MoveTo/LineTo,`
Rectangle, `PolyLineTo,` `SplineTo,` Circle, Ellipse, and `CircleArc.` These
basic line/curve drawing functions still use zero pen to draw.

We introduced some advanced two-dimension drawing functions, the activity of
which will be affected by pen and brush:

```
```
- `LineEx` function plots a beeline according to the properties of current
pen/brush. The line is from (x1, y1) to (x2, y2).
- `ArcEx` function plots an arc line according to the properties of current
pen/brush. The center of the arc is (x, y), the width of the bounding box of 
the arc is width; the height of the bounding box of the arc is height; the
starting angel the arc is ang1, in 1/64ths of a degree; ang2 is the end angel
relative to starting angel, in 1/64ths of a degree. If ang2 is positive,
representing anti-clockwise; ang2 is negative, representing clockwise. When 
ang2 is more than or equals to 360x64, it means an entire circle or ellipse, 
but not an arc.
- `FillArcEx` function fills an arc-shaped sector. The meaning of parameter is
same as `ArcEx.`
- `PolyLinEx` function plots multiple lines according to the properties of
current pen/brush. If having to joint lines, it will perform the joint 
according to the properties of current pen.
- `PolyArcEx` function plots multiple arcs according to the properties of
current painting brush. If having to joint arcs, it will perform the joint
according to the properties of pen. This function uses `ARC` structure to
describe the parameter of each arc. The structure is defined as follows:

```
```

`PolyFillArcEx` function fills multiple arcs. This function uses `ARC` 
structure to describe the parameter of each arc.

### Using Advanced Two-Dimension `GDI` Functions
The code in List 5 uses the above advanced two-dimension `GDI` function to draw
some graphics objects. Figure 7 gives the output effect of this code.


List 5 Using advanced two-dimension `GDI` functions
```
```


<img src="%ATTACHURLPATH%/15.7.jpeg" alt="15.7.jpeg" `ALIGN="CENTER"` />

Figure 7 The output of advanced two-dimension `GDI` functions

## Support for Slave Screens
MiniGUI supports the slave screens if there are multiple video devices
installed. The slave screen only can display information and cannot receive any
input at all. The slave screen is abstracted as a `DC` object. So `GDI`
functions can be called for the slave screen.

### Creating Slave Screen
The following function can used to open the slave screen:

```
```
`InitSlaveScreen` return a graphics device context handle by a special device
name and display mode. name specifies what map engine the slave screen uses, 
and mode specifies the resolution and color depth of the slave screen. The
following code is a example for opening a slave screen.

```
```
The graphics device context handle returned by `InitSlaveScreen` can call `GDI`
functions in MiniGUI to plot in the slave screen, and the process is completely
same as normal `DC.`

### Destroying Slave Screen
The following function can be used to destroy the slave screen; you should use
this function to release the internal resource associated with the slave 
screen: 

```
```
Here, hdc is a graphic device context handle returned by `InitSlaveScreen.`


-- Main.XiaodongLi - 07 Nov 2009


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
