_Writing a driver of the DRI engine for your GPU._

Table of Contents

- [Overview](#overview)
- [Compile-time Configuration](#compile-time-configuration)
- [Run-time Configuration](#run-time-configuration)
- [Implement DRI driver](#implementing-dri-driver)
- [Restrictions](#restrictions)
- [Example](#example)
- [Future Feature](#future-feature)

## Overview

In order to support modern graphics card or GPU, we introduced a
new NEWGAL engine of `dri`. The developer can use this engine to
run MiniGUI apps on a Linux box on which the DRI
(Direct Rendering Infrastructure) is enabled.

The `dri` engine uses `libdrm` developed by Free Desktop project:

<https://dri.freedesktop.org/wiki/>

Libdrm is a user-space library implements the Direct Rendering Manager.
MiniGUI mainly uses this library to support the dumb frame buffer
(no hardware acceleration). However, you can write a driver for your
graphics card or GPU to implement the hardware accelerated features.

To avoid modifying the MiniGUI source code when supporting a new GPU,
the `dri` engine has adopted a scalable design:

* You can directly use the `dri` engine to run MiniGUI on a GPU
which supports dumb frame buffer.
* When you want to take advantage of the hardware acceleration of
your GPU, you can write some code for your GPU as a sub driver
of `dri` engine outside MiniGUI.

This document describes how to enable `dri` engine and write a
hardware-accelerated driver for your own GPU.

Note that, generally, the driver will be implemented by the GPU
or SoC vendors. The MiniGUI app developers do not need to
care about this.

## Compile-time Configuration

There are two configure options related to the `dri` engine:

* `--enable-videodri` enables the `dri` engine, and `--disable-videodri`
  disables the `dri` engine. Note that the `dri` engine is only
  available on Linux, and you need to install the `libdrm` 2.4 or later
  first.
* `--with-targetname=external`. When you configure MiniGUI with this
  option, MiniGUI will use the external function `__dri_ex_driver_get`
  to initialize the DRI driver. If you do not implement this function,
  the link will fail.

## Run-time Configuration

For `dri` engine, we introduce a new section in MiniGUI runtime
configuration:

```
[dri]
defaultmode=1024x768-32bpp
dpi=96
pixelformat=XR24
device=/dev/dri/card0
```

Note that the `defaultmode` and `dpi` keys are standard keys for
a NEWGAL engine. These two keys define the screen resolution for
MiniGUI.

For `dri` engine, you can use the key `dri.device` to specify
your DRI device. Generally, it is `/dev/dri/card0`.

You can use the key `dri.pixelformat` to specify the DRM pixel format
of the screen. We use libdrm's fourcc code to defined the pixel format
of the screen surface in MiniGUI run-time configuration. For example,
`XR24` means `X8R8G8B8` pixel format (`DRM_FORMAT_XRGB8888`), and
`AR24` means `A8R8G8B8` pixel format (`DRM_FORMAT_ARGB8888`).

For more information, please see `<drm/drm_fourcc.h>` header file.
Note that only 8/16/24/32 bpp RGB formats are supported.

## Implementing DRI driver

The header file `<minigui/exstubs.h>` defines the external sutbs and
the driver operations (a set of callback functions) you need to implement
for your GPU externally.

First, you need to implement the following external stub:

```cpp
DriDriverOps* __dri_ex_driver_get (const char* driver_name);
```

This function takes an argument `driver_name` and returns NULL or
a valid pointer of `DriDriverOps` to MiniGUI. The argument `driver_name`
gives the driver name determined by libdrm. Generally, it is the model
or number of your GPU. For example, for Intel i915 GPU, the driver name
will be `i915`. The `__dri_ex_driver_get` can returns different
`DriDriverOps` to MiniGUI according to the driver name. In this way,
your implementation can support multiple GPUs.

If the external stub returns NULL, MiniGUI will use the dumb frame buffer
instead.

The `DriDriverOps` is a struct type consisted by a set of operations
(callbacks):

```cpp
/**
 * The struct type defines the operations for a DRI driver.
 */
typedef struct _DriDriverOps {
    /**
     * This operation creates the DriDriver object.
     *
     * \note The driver must implement this operation.
     */
    DriDriver* (*create_driver) (int device_fd);

    /**
     * This operation destroies the DriDriver object.
     *
     * \note The driver must implement this operation.
     */
    void (*destroy_driver) (DriDriver *driver);

    /**
     * This operation flushs the batch buffer of the driver or the hardware cache.
     *
     * \note This operation can be NULL.
     */
    void (* flush_driver) (DriDriver *driver);

    /**
     * This operation creates a buffer with the specified pixel format,
     * width, and height. If succeed, a valid (not zero) buffer identifier
     * and the picth (row stride in bytes) will be returned.
     * If failed, it returns 0.
     *
     * \note The driver must implement this operation.
     */
    uint32_t (* create_buffer) (DriDriver *driver,
            uint32_t drm_format,
            unsigned int width, unsigned int height,
            unsigned int *pitch);

    BOOL (* fetch_buffer) (DriDriver *driver,
            uint32_t buffer_id,
            unsigned int *width, unsigned int *height,
            unsigned int *pitch);

    /**
     * This operation maps the buffer into the current process's virtual memory
     * space, and returns the virtual address. If failed, it returns NULL.
     *
     * \note The driver must implement this operation.
     */
    DriSurfaceBuffer* (* map_buffer) (DriDriver *driver,
            uint32_t buffer_id);

    /**
     * This operation un-maps a buffer.
     *
     * \note The driver must implement this operation.
     */
    void (* unmap_buffer) (DriDriver *driver, DriSurfaceBuffer* buffer);

    /**
     * This operation destroies a buffer.
     *
     * \note The driver must implement this operation.
     */
    void (* destroy_buffer) (DriDriver *driver, uint32_t buffer_id);

    /**
     * This operation clears the specific rectangle area of a buffer
     * with the specific pixel value. If succeed, it returns 0.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated clear operation.
     */
    int (* clear_buffer) (DriDriver *driver,
            DriSurfaceBuffer* dst_buf, const GAL_Rect* rc, uint32_t pixel_value);

    /**
     * This operation checks whether a hardware accelerated blit
     * can be done between the source buffer and the destination buffer.
     * If succeed, it returns 0.
     *
     * \note If this operation is set as NULL, it will be supposed that
     * the driver does not support any hardware accelerated blit operation.
     */
    int (* check_blit) (DriDriver *driver,
            DriSurfaceBuffer* src_buf, DriSurfaceBuffer* dst_buf);

    /**
     * This operation copies bits from a source buffer to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated copy blit.
     */
    int (* copy_blit) (DriDriver *driver,
            DriSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DriSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            enum DriColorLogicOp logic_op);

    /**
     * This operation blits pixles from a source buffer with the source alpha value
     * specified to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with alpha.
     */
    int (* alpha_blit) (DriDriver *driver,
            DriSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DriSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc, uint8_t alpha);

    /**
     * This operation blits pixles from a source buffer to a destination buffer,
     * but skipping the pixel value specified by \a color_key.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with color key.
     */
    int (* key_blit) (DriDriver *driver,
            DriSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DriSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc, uint32_t color_key);

    /**
     * This operation blits pixles from a source buffer with the source alpha value
     * specified to a destination buffer, but skipping the pixel value specified.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with alpha and color key.
     */
    int (* alpha_key_blit) (DriDriver *driver,
            DriSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DriSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            uint8_t alpha, uint32_t color_key);

} DriDriverOps;
```

If the external stub `__dri_ex_driver_get` returns a valid pointer
of `DriDriverOps`, MiniGUI will call the operation `create_driver`
to initialize the DRI driver. The operation will return a pointer
to the type of `DriDriver`. All other operations of `DriDriverOps`
need this pointer as the context of your DRI driver.

Note that MiniGUI does not defined the detailed structure of
`DriDriver`, it is up to your implementation:

```cpp
/**
 * The struct type represents the DRI sub driver.
 * The concrete struct should be defined by the driver.
 */
struct _DriDriver;
typedef struct _DriDriver DriDriver;
```

For other operations, please see the comments above.

## Restrictions

In version 4.0.0, the `dri` NEWGAL engine does not provide support for
MiniGUI-Processes run-time mode. We will enhance this in the subsequent
version of MiniGUI.

Also note that when you use the hardware accelerated driver, MiniGUI app
may need the root privilege to call `drmSetMaster` to set the video mode.
However, under MiniGUI-Processes run-time mode, only the server (`mginit`) will
need this privilege when you use the future `dri` engine.

## Example

As an example, we implement the DRI driver for `i915` graphics chard
in `mg-tests/dri-engine/`. Please refer to `mg-tests` repository:

https://github.com/VincentWei/mg-tests/tree/master/dri-engine

## Future Features

In the near future, the MiniGUI team will:

* Enhance `dri` engine to support MiniGUI-Processes run-time mode.
* Enhance `dri` engine to support video plane/overlay.
* Implement the MiniGUI back-end of `cairo` and `EGL` for OpenGL,
  OpenGL ES, and OpenVG, in order to fully exploit the GPU's 2D/3D
  accelerated rendering capabilities.
* Provide some samples in `mg-tests` or `mg-samples` to integrate
  MiniGUI with `cairo` and OpenGL/OpenGL ES/OpenVG.

