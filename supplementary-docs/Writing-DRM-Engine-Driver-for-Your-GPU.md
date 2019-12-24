# Writing DRM Engine Driver for Your GPU

_Writing a driver of the DRM engine for your GPU._

Table of Contents

- [Overview](#overview)
- [Compile-time Configuration](#compile-time-configuration)
- [Run-time Configuration](#run-time-configuration)
- [Implementing a DRM driver](#implementing-a-drm-driver)
- [DRM Drivers for HybridOS](#drm-drivers-for-hybridos)
- [Restrictions](#restrictions)
- [Future Feature](#future-features)

## Overview

In order to support modern graphics cards or GPUs, we introduced a
new NEWGAL engine of `drm`. Developers can use this engine to
run MiniGUI apps on a Linux system on which the DRI
(Direct Rendering Infrastructure) is enabled.

The `drm` engine uses `libdrm` developed by Free Desktop project:

<https://dri.freedesktop.org/wiki/>

Libdrm is a user-space library which implements the Direct Rendering Manager.
MiniGUI mainly uses this library to support the dumb frame buffer
(no hardware acceleration). However, you can write a driver for your
graphics cards or GPUs to implement the hardware accelerated features.

To avoid modifying the MiniGUI source code when supporting a new GPU,
the `drm` engine has adopted a scalable design:

* You can directly use the `drm` engine to run MiniGUI on a GPU
which supports dumb frame buffer.
* When you want to take advantage of the hardware acceleration of
your GPU, you can write some code for your GPU as a sub driver
of `drm` engine outside MiniGUI.

This document describes how to enable `drm` engine and write a
hardware-accelerating driver for your own GPU.

Note that, generally, the driver will be implemented by the GPU
or SoC vendors. The MiniGUI app developers do not need to
care about this.

## Compile-time Configuration

There is one configure options related to the `drm` engine:

* `--enable-videodrm` enables the `drm` engine, and `--disable-videodrm`
  disables the `drm` engine. Note that the `drm` engine is only
  available on Linux, and you need to install the `libdrm` 2.4 or later
  first.

Before version 4.0.4, we use the option `--with-targetname=external` to
enable the external DRM driver; when you configure MiniGUI with this
option, MiniGUI will use the external function `__drm_ex_driver_get`
to initialize the DRM driver.

Since 4.0.4, we use `dlopen` to load the DRM driver. So the above
option does not make sense for DRM engine.

## Run-time Configuration

For `drm` engine, we introduced a new section in MiniGUI runtime
configuration:

```
[drm]
defaultmode=1024x768-32bpp
dpi=96
pixelformat=XR24
device=/dev/dri/card0
exdriver=libhidrmdrivers.so.0
```

Note that the `defaultmode` and `dpi` keys are standard keys for
a NEWGAL engine. These two keys define the screen resolution for
MiniGUI.

For `drm` engine, you can use the key `drm.device` to specify
your DRI device. Generally, it is `/dev/dri/card0`.

You can use the key `drm.pixelformat` to specify the DRM pixel format
of the screen. We use libdrm's fourcc code to defined the pixel format
of the screen surface in MiniGUI run-time configuration. For example,
`XR24` means `X8R8G8B8` pixel format (`DRM_FORMAT_XRGB8888`), and
`AR24` means `A8R8G8B8` pixel format (`DRM_FORMAT_ARGB8888`).

For more information, please see `<drm/drm_fourcc.h>` header file.
Note that only 8/16/24/32 bpp RGB formats are supported.

You can use the key `drm.exdriver` to specify the SO name of the
shared library, which implements the DRM driver for your GPU and
export an external symbol called `__drm_ex_driver_get` to
initialize the DRM driver.

## Implementing a DRM driver

The header file `<minigui/exstubs.h>` defines the external stubs and
the driver operations (a set of callback functions) you need to implement
for your GPU externally.

First, you need to implement the following external stub:

```cpp
DrmDriverOps* __drm_ex_driver_get (const char* driver_name, int device_fd);
```

This function takes tow arguments and returns NULL or
a valid pointer of `DrmDriverOps` to MiniGUI. The argument `driver_name`
gives the driver name determined by libdrm. Generally, it is the kernel
driver name for your GPU. For example, for Intel i915/i965 GPUs, the
driver name will be `i915`. The argument `device_fd` gives you
the file descriptor of the opened DRI device.

The `__drm_ex_driver_get` can return different
`DrmDriverOps` to MiniGUI according to the driver name and device file
descriptor. In this way, your implementation can support multiple GPUs.

If the external stub returns NULL, MiniGUI will try to use the dumb
frame buffer instead.

The `DrmDriverOps` is a struct type consisting of a set of operations
(callbacks):

```cpp
/**
 * The struct type defines the operations for a DRM driver.
 */
typedef struct _DrmDriverOps {
    /**
     * This operation creates the DrmDriver object.
     *
     * \note The driver must implement this operation.
     */
    DrmDriver* (*create_driver) (int device_fd);

    /**
     * This operation destroies the DrmDriver object.
     *
     * \note The driver must implement this operation.
     */
    void (*destroy_driver) (DrmDriver *driver);

    /**
     * This operation flushs the batch buffer of the driver or the hardware cache.
     *
     * \note This operation can be NULL.
     */
    void (* flush_driver) (DrmDriver *driver);

    /**
     * This operation creates a buffer with the specified pixel format,
     * width, and height. If succeed, a valid DrmSurfaceBuffer object will
     * be returned; NULL on error. Note that the field of `pixels` of the
     * DrmSurfaceBuffer object is NULL until the \a map_buffer was called.
     *
     * \note The driver must implement this operation.
     */
    DrmSurfaceBuffer* (* create_buffer) (DrmDriver *driver,
            uint32_t drm_format,
            unsigned int width, unsigned int height);

    /**
     * This operation creates a buffer for the given handle
     * with the specified pixel format, width, and height. If succeed,
     * a valid DrmSurfaceBuffer object will be returned; NULL on error.
     *
     * \note This operation can be NULL.
     */
    DrmSurfaceBuffer* (* create_buffer_from_handle) (DrmDriver *driver,
            uint32_t handle, unsigned long size, uint32_t drm_format,
            unsigned int width, unsigned int height, unsigned int pitch);

    /**
     * This operation creates a buffer for the given system global name
     * with the specified pixel format, width, and height. If succeed,
     * a valid DrmSurfaceBuffer object will be returned; NULL on error.
     *
     * \note This operation can be NULL.
     */
    DrmSurfaceBuffer* (* create_buffer_from_name) (DrmDriver *driver,
            uint32_t name, uint32_t drm_format,
            unsigned int width, unsigned int height, unsigned int pitch);

    /**
     * This operation creates a buffer for the given PRIME file descriptor
     * with the specified pixel format, width, height, and pitch. If succeed,
     * a valid DrmSurfaceBuffer object will be returned; NULL on error.
     *
     * \note This operation can be NULL.
     */
    DrmSurfaceBuffer* (* create_buffer_from_prime_fd) (DrmDriver *driver,
            int prime_fd, unsigned long size, uint32_t drm_format,
            unsigned int width, unsigned int height, unsigned int pitch);

    /**
     * This operation maps the buffer into the current process's virtual memory
     * space, and returns the virtual address. If failed, it returns NULL.
     *
     * \note The driver must implement this operation.
     */
    uint8_t* (* map_buffer) (DrmDriver *driver, DrmSurfaceBuffer* buffer);

    /**
     * This operation un-maps a buffer.
     *
     * \note The driver must implement this operation.
     */
    void (* unmap_buffer) (DrmDriver *driver, DrmSurfaceBuffer* buffer);

    /**
     * This operation destroies a buffer.
     *
     * \note The driver must implement this operation.
     */
    void (* destroy_buffer) (DrmDriver *driver, DrmSurfaceBuffer* buffer);

    /**
     * This operation clears the specific rectangle area of a buffer
     * with the specific pixel value. If succeed, it returns 0.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated clear operation.
     */
    int (* clear_buffer) (DrmDriver *driver,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* rc, uint32_t pixel_value);

    /**
     * This operation checks whether a hardware accelerated blit
     * can be done between the source buffer and the destination buffer.
     * If succeed, it returns 0.
     *
     * \note If this operation is set as NULL, it will be supposed that
     * the driver does not support any hardware accelerated blit operation.
     */
    int (* check_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, DrmSurfaceBuffer* dst_buf);

    /**
     * This operation copies bits from a source buffer to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated copy blit.
     */
    int (* copy_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            enum DrmColorLogicOp logic_op);

    /**
     * This operation blits pixles from a source buffer with the source alpha value
     * specified to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with alpha.
     */
    int (* alpha_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc, uint8_t alpha);

    /**
     * This operation blits pixles from a source buffer to a destination buffer,
     * but skipping the pixel value specified by \a color_key.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with color key.
     */
    int (* key_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc, uint32_t color_key);

    /**
     * This operation blits pixles from a source buffer with the source alpha value
     * specified to a destination buffer, but skipping the pixel value specified.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blit with alpha and color key.
     */
    int (* alpha_key_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            uint8_t alpha, uint32_t color_key);

} DrmDriverOps;
```

If the external stub `__drm_ex_driver_get` returns a valid pointer
of `DrmDriverOps`, MiniGUI will call the operation `create_driver`
to initialize the DRM driver. The operation will return a pointer
to the type of `DrmDriver`. All other operations of `DrmDriverOps`
need this pointer as the context of your DRM driver.

Note that MiniGUI does not define the detailed structure of
`DrmDriver`, it is up to your implementation:

```cpp
/**
 * The struct type represents the DRI sub driver.
 * The concrete struct should be defined by the driver.
 */
struct _DrmDriver;
typedef struct _DrmDriver DrmDriver;
```

For other operations, please see the comments above.

As an example, we implement a sample DRM driver for `i915` graphics
chard in `mg-tests/drm-engine/`. Please refer to `mg-tests` repository:

<https://github.com/VincentWei/mg-tests/tree/master/drm-engine>

## DRM Drivers for HybridOS

[HybridOS](https://hybridos.fmsoft.cn) uses MiniGUI as the
underlying windowing system. So the HybridOS project maintains the
DRM drivers for MiniGUI in the following repo (`hiDRMDrivers`):

<https://github.com/FMSoftCN/hidrmdrivers>

Note that `hiDRMDrivers` depends on the LibDRM derivative for HybridOS
called `hiDRM`, not the original libdrm:

<https://github.com/FMSoftCN/hidrm>

Please use the code on the branch `hybridos` of `hiDRM`.

When you use `hiDRMDrivers`, please make sure that let MiniGUI
use `hiDRM` as well.

By using DRM engines and DRM drivers, MiniGUI and HybridOS now provide
the GPU integration via `hiMesa` and `hiCairo`:

- [hiMesa](https://github.com/FMSoftCN/himesa) is the Mesa derivative for HybridOS.
- [hiCairo](https://github.com/FMSoftCN/hicairo) is the Cairo derivative for HybridOS.

For the usage and samples, please refer to

[Integrating with GPU](/programming-guide/MiniGUIProgGuidePart3Chapter05.md)

## Restrictions

Currently (MiniGUI 4.0.4), the `drm` NEWGAL engine does not provide
support for MiniGUI-Processes run-time mode. We will enhance this in
the subsequent version of MiniGUI.

Also note that when you use the hardware accelerating driver, MiniGUI app
may need the root privilege to call `drmSetMaster` to set the video mode.
However, under MiniGUI-Processes run-time mode, only the server (`mginit`) will
need this privilege when you use the future `drm` engine.

## Future Features

In the near future, the MiniGUI team will:

* Enhance `drm` engine to support MiniGUI-Processes run-time mode.
* Enhance `drm` engine to support video plane/overlay.

