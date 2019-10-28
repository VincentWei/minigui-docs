# mGPlus Programming



---+Basic concept introduction

mGPlus is a MiniGUI component which provides support for advanced graphics
functions like path, gradient, anti-aliase stretch, and color combination.
mGPlus is like `GDI+` of Win32 or Cario.mGPlus will provide a series of
interfaces to implement
these functions. The library allows applications to draw graphics that do not
need to be associated with device handles, that is, applications can create
applications for stand-alone devices.

- Path: It consists of a group of strictly ordered polylines and curves.
Use the path for filling and cutting.
- Color Gradient: refers to a brush that provides a color linear gradient
or path gradient. This gradient brush can be used to fill areas, path areas, 
and graphics. Gradient brushes can also be used to draw lines, curves, and
paths. 
- Color Combination: The color combination determines the color values of
the source, bottom, and intersection areas according to the combination rule.

## Introduction of pen

Pen is used to draw lines, curves, and outlines of shapes. They are
based on point-painting mechanisms. In addition to the common color and width
attributes, the brush also has properties such as alignment, caps, and
transitions.

## Brush introduction

Brushes are based on the padding mechanism used to create solid objects and
render text objects with the Graphics object.

## Introduction of the Path
### The definition of the path

The path consists of a set of strictly ordered polylines and curves. The
order is important. The path has two rule winding rules. According to the
rules, it can be determined whether a point is inside or outside the path (the
path is not necessarily closed).

### Winding rules

Even-Odd: Rays from one point to the right. If the ray path has an odd
number of intersections, the point is in the path; otherwise, the point is no
longer in the path.Non-zero rule: ray from one point to the right, if
the path from the "up" through the ray does not equal to the number of times
from the "down" through the path, then the point is in the path, otherwise,
the store No longer in the path.


<img align="CENTER" alt="path.jpeg" src="%ATTACHURLPATH%/path.jpeg"
title="path.jpeg" />

1 Even-odd rule: points A, D, F are in the path, and points B, C, E, G are
not in the path
1 Non-zero rules: Note that the path passes through the direction of the
ray, and point A is crossed twice from above, so point A is within the path.
Similarly, points D and F are within the path, and points B, C, E, and G are
not within the path.

### Fill the path with the scan method

The line segment that forms the path can be either a polyline or a
curve. In order to facilitate the implementation of the path filling
algorithm, it is necessary to dispose the curves as polylines. The following
discussion focuses on the implementation of path filling of polylines.

When filling, there may be more than one path, which may be the area formed by
multiple paths. Therefore, all paths must maintain the same winding rules,
otherwise, they cannot be compared between different paths to determine
whether a point is within the path.

### Use of path

How to use the path. Paths can be used for path drawing, path filling,
and path clipping.Path drawing is to discretize all the sub-path curves
in the path into vertices, and then connect all the vertices to draw the
path.Path filling is to discretize the path into a polygon and then fill
the polygon.Path clipping is similar to path filling, except that the
generated scan lines form an area.

Operation on the path: new path, destroyed path, copied path, closed
path, adding a straight line to the path, adding a curve to the path, and so
on.

## Gradient fill

Gradient fill refers to the use of a color linear gradient or a gradual
gradient of the brush, in a specified area, or path area, or graphics to fill.
With the gradient fill, we can achieve a more beautiful three-dimensional
control, which will be detailed in the follow-up. The current gradients
implemented by mGPlus are curved gradient fills and linear gradient fills.
## Color combination

In the age when product packaging is very important, every application
developer wants to develop a very beautiful and refined user interface to get
the user's first impression. The color combination is a powerful tool in this
area. It can realize the ever-changing combination of pictures and give your
interface an unexpected effect. mGPlus implements twelve combination modes.

---+ Architecture

## `MGPlusGraphics` summary
- MiniGUI have two way to use `MGPlus：`
- First create a memory `DC` and provide the `DC` directly to `MGPlus,` which
renders directly on the `DC.`
- Use `MGPlus` directly, completely rendered by `MGPlus` itself, and
finally get the rendered `DC` through the interface function.
- `MGPlus` internally provides a core data structure `MGPlusGraphics` , which
contains all the data of the graph, including information required for
rendering such as paths, gradients, and change matrices. The data structure is
not open to the public, only one handle (pointer) is exposed externally.
- <p>Around the `MGPlusGraphics` structure, it will provide a series of
function interfaces to operate, including initialization, parameter</p>
modification, various ways of rendering, and various 2D coordinate changes
(such as linear changes).MGPlus includes the following modules:
- `MGPlus` include follow module:
- pen
- brush
- path
- matrix
- image
- font
- text
- <p>At the bottom, it will be implemented using `AGG` data and
interfaces.</p>
## `MGPlus` Frame Diagram

- <p>MGPlus is mainly composed of the above 9 categories. The Graphic class
implements all operations related to rendering, including color
gradient,</p>
color combination, anti-aliasing, etc. The other 8 categories are associated
with Graphic in a one-way manner.
- <p>The Matrix class is associated with the Path class, the Image class
and the Bitmap class, and the Font class is associated with the Text</p>
class.

- `MGPlus` rebuild framework:

<img align="CENTER" alt="mgplus_framework.jpeg"
src="%ATTACHURLPATH%/mgplus_framework.jpeg" title="mgplus_framework.jpeg"/>

---+ `API` Applications

## Graphics
### Graphics Manage Functions

The Manage functions of Graphics include the functions of creating, deleting,
and copying. Details are as follows:

---++++ Create

There are two ways to create. One is to pass directly into `HDC` to create
`MGPlusGraphics`
Data structure, call function `MGPlusGraphicCreateFromDC` can successfully
return `HGRAPHICS,` a
`MGPlusGraphics` was created successfully.

```
```

Another way is to use a different pixel format to create a `MGPlusGraphics` 
data 
structure, using width and
The height is initially used to specify the size of the canvas, calling
`MGPlusGraphicCreate`
function. It should be noted that the result of the rendering requires the
user to call the interface function `MGPlusGraphicSave` to obtain it.

```
```

Another new way to create. This method creates a `MGPlusGraphics` for direct
drawing `DC`
, Directly incoming `DCs` operate as canvases.

```
```

---++++ Delete

When `MGPlusGraphics` is not needed, you need to release the `MGPlusGraphics`
data structure by calling
The `MGPlusGraphicDelete` function is fine.

```
```

There is another kind of color that can clear `MGPlusGraphic,` similar to
clear screen, this function is `MGPlusGraphicClear.` Under normal 
circumstances, 
when creating `MGPlusGraphics,` the contents of the relevant dc will also be
copied. Therefore, before using `MGPlusGraphicCopyFromDC,` you need to call 
this 
function to clear it. Usage is as follows:
```
```

---++++ Copy

```
```

### Graphics color combination

mGPlus implements some basic alpha
Composition rules, combining source color and target color, mixing and
transparency effects in graphics and images.

Things to note when implementing:
- Many source images, such as some opaque images, do not store alpha for
their pixels
value. This type of source image provides an alpha value of 1.0 for all
its pixels.

- Many targets also have no place to store alpha
Values ​​(these are the results of a hybrid calculation). Such
goals implicitly discard such generated alpha
value. It is recommended that such objects treat their stored color values
​​as unpremultiplied values, and store the color values
​​and discard them.
Before the alpha value, the resulting color value is divided by the resulting
alpha value.

- The accuracy of the result depends on how the pixels are stored in the
target. For a few of a series of twelve synthesis operations, each color
will be
The alpha component provides at least 8
The image format of the storage bits should be sufficient as a target anyway.
Prior to rounding error dominates the result, less than for each component is
provided
8
The image format of the memory bits is limited to one or two synthesis
operations. For any translucent mixing type, image formats that do not
separately store color components are not a good candidate. For example, you
should not need to select pixels from a defined palette to match the mixed
equations, so that each operation can introduce a large number of errors.

- Almost all formats store pixels as discrete integers, rather than storing
them as floating-point values ​​used in the above equations.
The implementation can scale integer pixel values ​​to a range of
0.0 to 1.0
The floating point value between, or using slightly modified equations,
operates entirely within the integer domain, producing similar results to the
above equation.

- Internal implementations may approximate some equations. They can also
eliminate some steps to avoid unnecessary operations.

- Because of techniques that make the calculation more efficient by
simplifying the equation, a value of 0.0 is encountered on
non-premultiplied targets.
The alpha value of the result may be different for some implementation
implementations. Note that if the denominator (alpha)
Is 0, then divide by alpha under `SRC` rules
This simplified operation is technically illegal. However, because the result
is only expected when viewed in premultiplied form, the result is
0 of alpha
The value presented is essentially the resulting uncorrelated color component,
so in this case, the specific behavior should be unpredictable.

Users need to create two `MGPlus` Graphics if they need color combinations
Finally, they can mix their colors to get the effect of the color combination
we want.

The `MGPlusGraphics` color combination has a total of 12 combination modes,
which are:

```
```

The user can set the color combination mode according to the need and put the
required mode into the function `MGPlusSetCompositingMode`
The parameter `compositingMode` can be.

```
```

If the user wants to get the current color combination mode, directly call the
function `MGPlusGetCompositingMode` to get
`MGPlusGraphics` combination mode. The acquired combination pattern is stored 
in 
the address pointed to by `compositingMode.`

```
```

Note: Although the current color combination supports 32-bit color, 24-bit
color, 16-bit color, but in 24-bit and 16
In the case of bit depth, only simple color combinations are supported, namely
src-over mode.

In addition to the color combinations of graphics, you can also add pictures
to participate in color combinations. Users want to add pictures, first call
the function
`MGPlusGraphicLoadBitmapFromFile` to load the picture and then call the 
function 
`MGPlusDrawImage`
Draw the picture in `MGPlusGraphics.`

```
```
Note: `n_index` is the prime value of the loaded image; file is the path of the
loaded image.

```
```

Note: `n_index` is the prime value of the loaded picture; x, y are the starting
position of the picture; w, h is the size of the picture; if w and h are -1,
it means that the picture will be drawn with the original size.

There is another way to load pictures. In the initialization of the program
calls the function in MiniGUI
`LoadBitmap` (For details, see MiniGUI.
`API` Manual) and then call `MGPlusGraphicLoadBitmap` and `MGPlusDrawImage` to
draw 
the picture
In `MGPlusGraphics,` remember to call MiniGUI in the end of the program
`UnloadBitmap`
The function frees memory space.

```
```
Note: `n_index` is the prime value of the loaded image; `p_bitmap` is the
address 
of the stored image.

After completing the corresponding work, be sure to call the function
`MGPlusGraphicBlend,` otherwise the effect of the color combination is
invisible. 

```
```

For details on how to combine colors, see the example of color combinations:

```
```


<img align="CENTER" alt="composite.png" src="%ATTACHURLPATH%/composite.png" />

color combination

### Graphics mode

Graphics rendering mode is anti-aliasing control, including brush smooth mode,
path anti-aliasing and text anti-aliasing.

---++++ Brush's smooth mode

There are two kinds of smooth brush modes, which are:

```
```

The user wants to set the drawing mode of the brush. The
`MGPlusSetSmoothingMode` function can be used as the following example:
```
```

To get the drawing mode of the current brush, call the `MGPlusGetSmoothingMode`
function,
The value of the drawing mode is stored in the address of the value.
```
```

---++++ Path antialiasing

Path anti-aliasing controls anti-aliasing with
`MP_PATH_RENDER_HINT_ANTIALIAS_ON` and `MP_PATH_RENDER_HINT_ANTIALIAS_OFF`.
```
```

Users want to set the path anti-aliasing drawing mode, use
`MGPlusSetPathRenderingHint` function, the specific usage is as follows:
```
```

To get the current path anti-aliased drawing mode, call
`MGPlusGetPathRenderingHint` function,
The value of the drawing mode is stored in the address of the value.
```
```

Add the effect of the path before anti-aliasing

<img align="CENTER" alt="path1.png" src="%ATTACHURLPATH%/path1.png"/>

Adding the anti-aliasing effect of the path

Added anti-aliasing effect of the path

<img align="CENTER" alt="path2.png" src="%ATTACHURLPATH%/path2.png"/>

Adding anti-aliasing effect to the path

---++++ Text Antialiasing

Anti-aliasing of text is controlled by `MP_TEXT_RENDER_HINT_ANTIALIAS_ON` and
`MP_TEXT_RENDER_HINT_ANTIALIAS_OFF`.
```
```

Users want to set the text anti-aliasing drawing mode, you can use
`MGPlusSetTextRenderingHint` function, the specific usage of the following
example:
```
```

To get the current text anti-aliasing drawing mode, call the function
`MGPlusGetTextRenderingHint,`
The value of the drawing mode is stored in the address of the value.
```
```

Add text before antialiasing

<img align="CENTER" alt="text2.png" src="%ATTACHURLPATH%/text2.png"/>

Add text anti-aliasing effect

Added text anti-aliasing effect

<img align="CENTER" alt="text1.png" src="%ATTACHURLPATH%/text1.png"/>

Add text anti-aliasing effect

### World Coordinate System Conversion

The conversion of the world coordinate system is the conversion (translation,
scaling, rotation) of the coordinates of `MGPlus` Graphics. There is also a 
path 
conversion of mgplus, which is the conversion of the coordinates of the
graphics coordinates (translation, scaling, rotation).

---++++ Settings

The user needs to set the world coordinate system to call the
`MGPlusSetWorldTransform` function.

```
```

The definition of the parameter matrix is ​​as follows:
```
```

Reset the function to `MGPlusResetWorldTransform.`
```
```

---++++ Translation

If the user wants to translate, it should be noted that: the first world
coordinate is (0, 0), if you want to figure around (100,
100) Rotate the coordinates first to (100, 100), ie using
`MGPlusTranslateWorldTransform(graphics,-100,` -100), then use Rotatate
rotation, and finally use
`MGPlusTranslateWorldTransform(graphics,` 100, 100), translate coordinates 
back. 

```
```

---++++ Zoom

Call the function `MGPlusScaleWorldTransform` , users can zoom 
`MGPlusGraphics.` 

```
```

---++++ Rotation

The function `MGPlusRotateWorldTransform` is called and the user can rotate the
`MGPlus` Graphics.

```
```

The specific usage can refer to the following example of the conversion of the
world coordinate system:

```
```


<img align="CENTER" alt="worldtransform.png"
src="%ATTACHURLPATH%/worldtransform.png" />

Conversion of world coordinate system

View Description: The bottom layer is the original graphics, the upper layer
is twice the x-axis magnification, and the rotated 70-degree conversion
graphics.

### Font Rendering

Currently, mgplus only supports rendering of vector fonts, so if you need font
rendering functionality, you first need to open it when compiling mgplus
--enable-ft2support
The option is used to support freetype2 vector fonts, and requires the client
to add freetype libraries when compiling the application.

Users want to draw fonts, first create a font using the `MGPlusCreateFont`
function.
```
```

There are six modes for font rendering, as follows:
```
```

After the font is created, the outline data of the font is obtained by the
function `MGPlusGetGlyphOutline.`
```
```
The parameter lpdata is the data for storing the font outline.

The function of `LPGLYPHMETRICS`
The lpgm parameter includes the position, direction and size of the font
outline. The specific definition is as follows:
```
```

Then the font can be drawn according to the outline data of the font, or the
path structure of the font can be used to rotate the font. The functions used
are as follows:

```
```

Note: x, y refer to the starting coordinates of the drawing font; lpdata is
the data for storing the font outline; color refers to the drawing color of
the font.

```
```
Note: x, y refer to the starting coordinates of the drawing font.

Finally, after the corresponding operation is completed, the font is deleted
to avoid memory leaks. The function is `MGPlusDeleteFont.`

```
```

The font rotation sample code is as follows:
```
```


<img align="CENTER" alt="3.png" src="%ATTACHURLPATH%/3.png" />

font rotation

## Path

### Path Management

Path: A path consists of a set of strictly ordered polylines and curves. Paths
can be used for filling and cutting. By providing support for the path, we can
achieve drawing of vector graphics, support for vector graphics, such as
infinity zooming and rotation, as well as providing better support for vector
fonts.

---++++ Create

When `MGPlusPathCreate` creates a path, you need to select the winding rule. 
The 
winding rule is divided into two types:
- `MP_PATH_FILL_MODE_WINDING` // Non-zero rule
- `MP_PATH_FILL_MODE_ALTERNATE` // odd and even rules

E.g:
```
```

---++++ Delete

Release path.
If you do not release the memory in the application, it will lead to memory
leaks and coredump.

```
```

---++++ Reset

Reset the path.
Clear all the contents of the path.
```
```

---++++ fill path

`MGPlusFillPath`
Before filling the path, you must determine the Brush fill feature and then
use `MGPlusGraphicSave` to draw to the screen.
```
```
The specific application is explained in detail in the next section "Adding a
graphic to a path".

---++++ Add graphics to the path
---+++++ Add Line

Pass the coordinates of the two points to draw a straight line.
```
```

Pass in a group of "points" and draw straight lines in order of the points.
Count is the number of vertices.
```
```
E.g:
```
```


<img align="CENTER" alt="lines.png" src="%ATTACHURLPATH%/lines.png" />

Drawing Effective Results

---+++++ Add an arc

(cx, cy) is the center point coordinate of the ellipse, rx is the radius of
the X axis, ry
For the y-axis radius, startangle is the arc start angle, and `sweepAngle` is
the radians between the start and end angles.
```
```

E.g:
```
```

<img align="CENTER" alt="arc.png" src="%ATTACHURLPATH%/arc.png" />

---+++++ Add Bezier Curve

(x1,y1) is the starting point, (x2,y2) is the first control point, (x3,
Y3) is the second control point, and (x4, y4) is the end point.

```
```

E.g:
```
```

<img align="CENTER" alt="bezier.png" src="%ATTACHURLPATH%/bezier.png" />

---+++++ Add a rectangle

(x, y) is the vertices of the rectangle, and (width, height) is the length and
width of the rectangle.
```
```

E.g:
```
```

![alt](figures/rect.png)


---+++++ Add Rounded Rectangle

(x, y) is a rectangle vertex, (width,
Height) is the length and width of the rectangle. The rounded rectangle of the
rounded rectangle is calculated by a rectangle, and the size of the rectangle
is used (
Rx, ry) to control.
```
```

E.g:
```
```

![alt](figures/Rectangle.png)


---+++++ Add ellipse

(cx, cy) is an ellipse center, (rx, ry) is an elliptical x-radius, y-radius,
clockwise
In the drawing direction of the ellipse, `TRUE` is clockwise and `FALSE` is
counterclockwise.
```
```

E.g:
```
```

![alt](figures/Ellipse.png)


---+++++ Add curves

Points Vertex array, count Number of vertices.
```
```

E.g:
```
```

![alt](figures/Curve.png)


---+++++ Add path

Add the contents of `add_path` to path.
```
```

E.g:
```
```

---++++ Drawing path

`MGPlusDrawPath`
To draw the path, you must determine the Pen drawing properties and then use
`MGPlusGraphicSave` to draw to the screen.
```
```
`MGPlusDrawPath` is similar to `MGPlusFillPath.`

E.g:
```
```

![alt](figures/DrawPath.png)


---++++ Open and close

Start a new subpath in the path. Subpaths allow you to divide a path into
sections and use it.
```
```

Closed path.
Once the subpath is closed, the next line drawn in the path starts from
another path.
```
```

E.g:
```
```

![alt](figures/CloseFigure.png)


---++++ Line Control

Move the current pen to another point without drawing a line.
```
```

Use the current pen's point as a starting point to draw another line.
```
```

E.g:
```
```

<img align="CENTER" alt="Move.png" src="%ATTACHURLPATH%/Moveto.png" />

---++++ Get path

```
```

E.g:
```
```

<img align="CENTER" alt="GetPathPoints.png"
src="%ATTACHURLPATH%/GetPathPoints.png" />

### path conversion

mGPlus provides matrix objects, a very powerful tool that makes it very easy
to write rotations, translations, and scales for graphics. A matrix object is
always associated with a graphic transformation pair. For example, the `PATH`
has a Transform method. One of its parameters can accept the address of the
matrix object. Each time the path is drawn, it can be based on the
transformation matrix. draw. The graphics transformation is stored in the
transformation matrix, so the path transformation is the transformation of the
graph. Path conversion matrices can be set, and translations, scaling, and
rotations can also be applied to the path.

---++++ Settings

Call the `MGPlusPathSetTransform` function to set the transformation matrix for
the path.
```
```
The definition of the parameter matrix is as follows:
```
```

Call the `MGPlusPathResetTransform` function to reset the conversion matrix for
the path.

```
```

---++++ Translation

Calling the `MGPlusPathTranslate` function, the path is translated from the
original position along the x and y axes (dx, dy).

```
```

---++++ Zoom

The function `MGPlusPathScale` is used to scale the path. The value of sx , sy
is greater than 1 is magnified, less than 1 is reduced.

```
```

---++++ Rotation

The function `MGPlusPathRotate` is used for the rotation of the path, and the
parameter angle is the rotation angle value.

```
```

Note: After the matrix is converted as required, the
`MGPlusPathTransform` function must be called. This function applies the matrix
transformation; otherwise, the effect of path conversion cannot be displayed.

```
```

For the usage of path conversion, please refer to the following example:
```
```


<img align="CENTER" alt="PathTransform.png"
src="%ATTACHURLPATH%/PathTransform.png" />

path conversion

## Pen
### Pen Management

Brushes are used to draw lines, curves, and outlines of shapes. They are based
on point-painting mechanisms. In addition to the common color and width
attributes, the pen also has properties such as alignment, caps, and
transitions.

---++++ Create Pen

If the user wants to use the pen to draw the shape, he needs to call the
function `MGPlusPenCreate` to create the pen.
%CODE{cpp}%
`HPEN` `MGPlusPenCreate` (int width, `ARGB` argb);
```
```

### Pen Settings

After the pen is created, the user needs to set the pen as needed, such as
the color, width, connection, and length of the dotted line.

---++++ Color Settings

If the user needs to modify the color of the pen, call the function
`MGPlusPenSetColor.`

```
```

---++++ width setting

If the user needs to modify the width of the pen, call the function
`MGPlusPenSetWidth.`
```
```

Width rendering

<img align="CENTER" alt="width.png" src="%ATTACHURLPATH%/width.png" />
Effect of <center> width</center>
Note: The width of the lines is 1, 10 and 30 in order.

---++++ Dashed length setting

The pen is drawn in the default state is a solid line, the user wants to set
the dotted line, call the function
`MGPlusPenSetDashes`
To set, use the parameter `dash_list` to use a predefined array to describe the
virtual reality of the pen . The dotted style depends on an array,
The elements of the array represent the lengths of the dashed lines and
spaces, respectively.

```
```

Note: The parameter `dash_phase` is, `dash_list` is the dotted line shape,
`dash_len` is the length of the dotted line shape.
Dotted effect chart

![alt](figures/dash.png)



Drawing effect chart
Explanation: The style of the dotted line is {5, 10, 20}, {5, 10, 20, 15} and
{5, 10, 20, 15, 10,}.

---++++ Connection settings

The connection mode refers to the setting of the shape of the connection when
two straight lines are connected. There are five ways: `JOIN_MITER` (mock),
`JOIN_ROUND` (round), `JOIN_BEVEL`
(diagonal)
`JOIN_MILTER_REVERT`, `JOIN_MILTER_ROUND`. The function `MGPlusPenSetJoinStyle`
is 
called to modify the shape of the two straight line connections.
```
```

```
```

Set the mode to the effect of `JOIN_MITER`

<img align="CENTER" alt="join1.png" src="%ATTACHURLPATH%/join1.png" />

mode is `JOIN_MITER`

The set mode is `JOIN_ROUND`

<img align="CENTER" alt="join2.png" src="%ATTACHURLPATH%/join2.png" />

mode is `JOIN_ROUND`

Set the pattern to the effect of `JOIN_BEVEL`

<img align="CENTER" alt="join3.png" src="%ATTACHURLPATH%/join3.png"/>

mode is `JOIN_BEVEL`

The user wants to modify the shape of the head and tail of the drawn line by
calling `MGPlusPenSetCapStyle`
function. There are three ways: `CAP_BUTT` (flat cap)
`CAP_ROUND` (round line cap), `CAP_SQUARE` (square line cap).

```
```

```
```

Set the mode to `CAP_BUTT` renderings

<img align="CENTER" alt="cap1.png" src="%ATTACHURLPATH%/cap1.png" />

mode is `CAP_BUTT`

Set the mode to `CAP_ROUND` renderings

<img align="CENTER" alt="cap2.png" src="%ATTACHURLPATH%/cap2.png" />

mode is `CAP_ROUND`

Effect mode for setting the mode to `CAP_SQUARE`

<img align="CENTER" alt="cap3.png" src="%ATTACHURLPATH%/cap3.png" />

mode is `CAP_SQUARE`

An example of a connection method is as follows:

```
```
Description: If you are running `MGPlusPenSetCapStyle` effect, open the masked,
then close the relevant point of `JoinStyle.`

### Drawing graphics

The `MGPlusFillPath` and `MGPlusGraphicSave` procedures are not required, and
the 
image can be drawn directly with the pen.

---++++ Draw a straight line

Two points drawn in a straight line
```
```

E.g:
```
```

<img align="CENTER" alt="DrawLine.png" src="%ATTACHURLPATH%/DrawLine.png" />

---++++ Drawing Arcs

(cx, cy) is the center point coordinate of the ellipse, rx is the radius of
the X axis, ry
For the y-axis radius, startangle is the arc start angle, and `sweepAngle` is
the radians between the start and end angles.
```
```

E.g:
```
```

<img align="CENTER" alt="DrawArc.png" src="%ATTACHURLPATH%/DrawArc.png" />

---++++ Drawing Bezier Curves

(x1,y1) is the starting point, (x2,y2) is the first control point, (x3,
Y3) is the second control point, and (x4, y4) is the end point.
```
```

E.g:
```
```

<img align="CENTER" alt="DrawBezier.png" src="%ATTACHURLPATH%/DrawBezier.png" 
/> 

---++++ draw a rectangle

(x, y) is the vertices of the rectangle, and (width, height) is the length and
width of the rectangle.
```
```

E.g:
```
```

<img align="CENTER" alt="DrawRectangle.png"
src="%ATTACHURLPATH%/DrawRectangle.png" />

---++++ Drawing Rounded Rectangle

(x, y) is a rectangle vertex, (width,
Height) is the length and width of the rectangle. The rounded rectangle of the
rounded rectangle is calculated by a rectangle, and the size of the rectangle
is used (
Rx, ry) to control.
```
```

E.g:
```
```

<img align="CENTER" alt="DrawRoundRect.png"
src="%ATTACHURLPATH%/DrawRoundRect.png" />

---++++ Draw an ellipse

(cx, cy) is an ellipse center, (rx, ry) is an elliptical x-radius, y-radius
```
```

E.g:
```
```

<img align="CENTER" alt="DrawEllipse.png" src="%ATTACHURLPATH%/DrawEllipse.png"
/> 

---++++ Load image

The bitmap used by mgplus must be format compatible with graphics, so from
other dc-loaded bitmaps, you need to convert.
Two ways to load pictures:

```
```

```
```

---++++ Drawing pictures

There are three ways to draw a picture:

```
```

E.g:
```
```

<img align="CENTER" alt="DrawImage.png" src="%ATTACHURLPATH%/DrawImage.png" />

```
```

E.g:
```
```

<img align="CENTER" alt="DrawImagePoints.png"
src="%ATTACHURLPATH%/DrawImagePoints.png" />

```
```

E.g:
```
```

<img align="CENTER" alt="DrawImageWithPath.png"
src="%ATTACHURLPATH%/DrawImageWithPath.png" />

## Brush
### Brush Management

The brush is based on a padding mechanism that is used with the Graphics
object to create a solid shape and an object that renders text.

---++++ Create

Select brush style when using `MGPlusBrushCreate` to create a brush
%CODE{cpp}%
Typedef enum _MPBrushType
{
/* Brush the path with the single color.*/
`MP_BRUSH_TYPE_SOLIDCOLOR` = 0,
/* Brush the path with the hatchfill.*/
`MP_BRUSH_TYPE_HATCHFILL` = 1,
/* Brush the path with the texturefill.*/
`MP_BRUSH_TYPE_TEXTUREFILL` = 2,
/* Brush the path with the path gradient.*/
`MP_BRUSH_TYPE_PATHGRADIENT` = 3,
/* Brush the path with linear gradient.*/
`MP_BRUSH_TYPE_LINEARGRADIENT`
}MPBrushType;

`HBRUSH` `MGPlusBrushCreate` (MGPlusBrushType type);
```
```

### Brush Settings

---++++ Solid Brush Setting

Set the color of a single brush
```
```
<noscript>
Shadow Brush Hatch brush settings
Set the color of the Hatch brush
```
```

Get the color of the Hatch brush
```
```

Texture Brushes texture brush settings.
```
```

</noscript>
---++++ `GradientBrush` `GradientBrush` Settings

---+++++ Path Gradient Brush `PathGradientBrush` Settings

Set the center point of `PathGradientBrush`
```
```

Set the color of the center of the `PathGradientBrush`
```
```

Set the `PathGradientBrush` wrapping color
```
```

Set the scope of the arc gradient of the `PathGradientBrush`
```
```

E.g:
```
```

<img align="CENTER" alt="PathGradientBrush.png"
src="%ATTACHURLPATH%/PathGradientBrush.png" />

---+++++ Linear `GradientBrush` `LinearGradientBrus` Settings

Set the `LinearGradientBrush` mode
```
```

Get `LinearGradientBrush` mode
```
```

Set the `LinearGradientBrush` area
```
```

Set the `LinearGradientBrush` gradient color
```
```

E.g:
```
```


<img align="CENTER" alt="MP_LINEAR_GRADIENT_MODE_HORIZONTAL.png"
src="%ATTACHURLPATH%/MP_LINEAR_GRADIENT_MODE_HORIZONTAL.png" />
<center>MP_LINEAR_GRADIENT_MODE_HORIZONTAL.</center>
The following is a demonstration of other modes:
Set brush to `MP_LINEAR_GRADIENT_MODE_VERTICAL` mode

![alt](figures/MP_LINEAR_GRADIENT_MODE_VERTICAL.png)

<center>MP_LINEAR_GRADIENT_MODE_VERTICAL</center>

Set brush to `MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL` mode

![alt](figures/MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL.png)

<center>MP_LINEAR_GRADIENT_MODE_FORWARDDIAGONAL</center>

Set the brush to `MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL` mode

![alt](figures/MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL.png)

<center>MP_LINEAR_GRADIENT_MODE_BACKWARDDIAGONAL </center>

### Fill graphic

There is no need for the `MGPlusFillPath` and `MGPlusGraphicSave` procedures to
fill the image directly with the paintbrush.

---++++ Fill the arc

(cx, cy) is the center point coordinate of the ellipse, rx is the radius of
the X axis, ry
For the y-axis radius, startangle is the arc start angle, and `sweepAngle` is
the radians between the start and end angles.
```
```

E.g:
```
```


<img align="CENTER" alt="FillArc.png" src="%ATTACHURLPATH%/FillArc.png" />

---++++ Fill Bezier Curve

(x1,y1) is the starting point, (x2,y2) is the first control point, (x3,
Y3) is the second control point, and (x4, y4) is the end point.
```
```

E.g:
```
```

<img align="CENTER" alt="FillBezier.png" src="%ATTACHURLPATH%/FillBezier.png" 
/> 

---++++ Fill rectangle

(x, y) is the vertices of the rectangle, and (width, height) is the length and
width of the rectangle.
```
```

E.g:

```
```


<img align="CENTER" alt="FillBezier.png" src="%ATTACHURLPATH%/FillBezier.png" 
/> 

---++++ Fill rounded rectangle

(x, y) is a rectangle vertex, (width,
Height) is the length and width of the rectangle. The rounded rectangle of the
rounded rectangle is calculated by a rectangle, and the size of the rectangle
is used (
Rx, ry) to control.
```
```

E.g:
```
```

<img align="CENTER" alt="FillRoundRect.png"
src="%ATTACHURLPATH%/FillRoundRect.png" />

---++++ Fill ellipse

(cx, cy) is an ellipse center, (rx, ry) is an elliptical x-radius, y-radius
```
```

E.g:
```
```

<img align="CENTER" alt="FillEllipse.png" src="%ATTACHURLPATH%/FillEllipse.png"
/> 





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
