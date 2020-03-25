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

Also note that, we changed the driver interface since MiniGUI 4.0.7.
In fact, we changed the interface when developing MiniGUI 5.0.0, and
introduced the changes to MiniGUI 4.0.7. Now, no matter which version
you use, we will keep the driver interface is consistent for MiniGUI
4.0.7 or later and 5.0.x.

Therefore, this document conforms to both MiniGUI 4.0.7 or later and
MiniGUI 5.0.x. We recommend that you upgrade to MiniGUI 4.0.7 or
MiniGUI 5.0.0 as soon as possible.

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
double_buffering=true   # only MiniGUI 5.0.0 or later.
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
Note that only 8/16/24/32 bits per pixel formats are supported.

You can use the key `drm.exdriver` to specify the SO name of the
shared library, which implements the DRM driver for your GPU and
export an external symbol called `__drm_ex_driver_get` to
initialize the DRM driver.

For MiniGUI 5.0.0 or later, you can also use another runtime configuration
option `drm.double_buffering`. This option specifies whether double buffering
is enabled. Use `true` or `yes` for enabled, anything else for disabled.
Note that under compositing schema, double buffering is always enabled.

## Implementing a DRM driver

The header file `<minigui/exstubs.h>` defines the external stubs and
the driver operations (a set of callback functions) you need to implement
for your GPU externally.

First, you need to implement the following external stub:

```cpp
DrmDriverOps* __drm_ex_driver_get (const char* driver_name, int device_fd,
        int* version);
```

This function takes three arguments and returns NULL or a valid pointer of
`DrmDriverOps`to MiniGUI.

This function can return different `DrmDriverOps`to MiniGUI according to
the driver name and device file descriptor. In this way, your DRM engine
driver implementation can support multiple GPUs.

If the external stub returns NULL, MiniGUI will try to use the dumb
frame buffer instead. The arguments of this function have the following
meanings:

- `driver_name`: This argument gives the driver name determined
 by MiniGUI. Generally, it is the kernel driver name for your GPU.
 For example, for Intel i915/i965 GPUs, the driver name will be `i915`.
- `device_fd`: This argument gives the file descriptor of the
 opened DRI device.
- `version`: A pointer to an integer which will be used to return the
 interface version of the DRM engine driver.

Note that We use the version control since 4.0.7. It will be initialized
to zero by MiniGUI before calling this function. Because an old
driver for MiniGUI 4.0.6 or earlier will not change the value, MiniGUI
will deny to load the old driver.

The constant `DRM_DRIVER_VERSION` defines the current interface version code.
A correctly implemented DRM engine driver should always return this constant
value to MiniGUI.

The `DrmDriverOps` is a structure type consisting of a set of operations
(callbacks):

```cpp
/**
 * The structure type defines the operations for a DRM driver.
 */
typedef struct _DrmDriverOps {
    /**
     * This operation creates the DrmDriver object.
     *
     * \note The driver must implement this operation.
     */
    DrmDriver* (*create_driver) (int device_fd);

    /**
     * This operation destroys the DrmDriver object.
     *
     * \note The driver must implement this operation.
     */
    void (*destroy_driver) (DrmDriver *driver);

    /**
     * This operation flushes the batch buffer of the driver or
     * the hardware cache.
     *
     * \note This operation can be NULL.
     */
    void (* flush_driver) (DrmDriver *driver);

    /**
     * This operation creates a surface buffer with the specified pixel format,
     * header size, width, and height. If succeed, a valid DrmSurfaceBuffer
     * object will be returned; NULL on error. Note that the field of `buff`
     * of the DrmSurfaceBuffer object is NULL until the \a map_buffer was called.
     *
     * \note The driver must implement this operation and fill all fields of
     *  the new DrmSurfaceBuffer object.
     */
    DrmSurfaceBuffer* (* create_buffer) (DrmDriver *driver,
            uint32_t drm_format, uint32_t hdr_size,
            uint32_t width, uint32_t height);

    /**
     * This operation creates a buffer from a given and possibly foreign handle
     * with the size of the buffer. If succeed, a valid DrmSurfaceBuffer object
     * will be returned; NULL on error.
     *
     * \note This operation can be NULL. Note that the handle might was created
     *  by a foreign module. If implemented, the driver must
     *  fill the correct prime_fd, handle, name, and size fields of the new
     *  DrmSurfaceBuffer object.
     */
    DrmSurfaceBuffer* (* create_buffer_from_handle) (DrmDriver *driver,
            uint32_t handle, size_t size);

    /**
     * This operation creates a buffer for the given system global name
     * If succeed, a valid DrmSurfaceBuffer object will be returned;
     * NULL on error.
     *
     * \note This operation can be NULL. If implemented, the driver must
     *  fill the correct prime_fd, handle, name, and size fields of the new
     *  DrmSurfaceBuffer object.
     */
    DrmSurfaceBuffer* (* create_buffer_from_name) (DrmDriver *driver,
            uint32_t name);

    /**
     * This operation creates a buffer for the given PRIME file descriptor
     * with the specified pixel format, width, height, and pitch. If succeed,
     * a valid DrmSurfaceBuffer object will be returned; NULL on error.
     *
     * \note This operation can be NULL. If implemented, the driver must
     *  fill the correct prime_fd, handle, name, and size fields of the new
     *  DrmSurfaceBuffer object.
     */
    DrmSurfaceBuffer* (* create_buffer_from_prime_fd) (DrmDriver *driver,
            int prime_fd, size_t size);

    /**
     * This operation maps the buffer into the current process's virtual memory
     * space, and returns the virtual address. If failed, it returns NULL.
     *
     * When \a for_scanout is not zero, the buffer will be used for scan out
     * frame buffer.
     *
     * \note The driver must implement this operation. The driver must
     *  set a valid value for buff field of the DrmSurfaceBuffer object
     *  on success.
     */
    uint8_t* (* map_buffer) (DrmDriver *driver, DrmSurfaceBuffer* buffer,
            int for_scanout);

    /**
     * This operation un-maps a buffer.
     *
     * \note The driver must implement this operation. The driver must
     *  set NULL for buff field of the DrmSurfaceBuffer object
     *  on success.
     */
    void (* unmap_buffer) (DrmDriver *driver, DrmSurfaceBuffer* buffer);

    /**
     * This operation destroys a buffer.
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
     * the driver does not support any hardware accelerated blitting operation.
     */
    int (* check_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, DrmSurfaceBuffer* dst_buf);

    /**
     * This operation copies bits from a source buffer to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated copy blitting.
     *
     * \note Currently, the logical operation is ignored.
     */
    int (* copy_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            ColorLogicalOp logic_op);

    /**
     * This operation blits pixels from a source buffer with the source alpha
     * value specified to a destination buffer.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blitting with alpha.
     */
    int (* alpha_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            uint8_t alpha);

    /**
     * This operation blits pixels from a source buffer to a destination buffer,
     * but skipping the pixel value specified by \a color_key.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blitting with color key.
     */
    int (* key_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            uint32_t color_key);

    /**
     * This operation blits pixels from a source buffer with the source alpha
     * value specified to a destination buffer, but skipping the pixel value
     * specified.
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blitting with alpha and color key.
     */
    int (* alpha_key_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            uint8_t alpha, uint32_t color_key);

    /**
     * This operation blits pixels from a source buffer with the source alpha
     * value of pixels to the destination buffer, and with the specified color
     * compositing/blending method (\a ColorBlendMethod).
     *
     * \note If this operation is set as NULL, the driver does not support
     * hardware accelerated blitting with alpha on basis per pixel.
     *
     * \note Currently, the color compositing/blending method is ignored.
     */
    int (* alpha_pixel_blit) (DrmDriver *driver,
            DrmSurfaceBuffer* src_buf, const GAL_Rect* src_rc,
            DrmSurfaceBuffer* dst_buf, const GAL_Rect* dst_rc,
            ColorBlendMethod blend_method);

```

If the external stub `__drm_ex_driver_get` returns a valid pointer
of `DrmDriverOps` and the version code is matched, MiniGUI will call
the operation `create_driver` to initialize the DRM driver. The operation
will return a pointer to the type of `DrmDriver`. All other operations of
`DrmDriverOps` need this pointer as the context of your DRM driver.

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
underlying windowing system. The HybridOS project maintains the
DRM drivers for MiniGUI in the following repo (`hiDRMDrivers`):

<https://github.com/FMSoftCN/hidrmdrivers>

By using DRM engines and DRM drivers, MiniGUI and HybridOS now provide
the GPU integration via `hiMesa` and `hiCairo`:

- [hiMesa](https://github.com/FMSoftCN/himesa) is the Mesa derivative for HybridOS.
- [hiCairo](https://github.com/FMSoftCN/hicairo) is the Cairo derivative for HybridOS.

For the usage and samples, please refer to the chapter
[Integrating with GPU](/programming-guide/MiniGUIProgGuidePart3Chapter05.md)
in the [MiniGUI Programming Guide](/programming-guide/README.md).

## Precautions

Since MiniGUI 4.0.7/5.0.0, the DRM engine provides complete support for
the MiniGUI-Processes runtime mode. However, you need to pay attention
for the following matter:

The server (`mginit`) needs the root privilege to call `drmSetMaster` to act
as the master process of Linux DRI. Only after a client was authenticated
through the server (`mginit`), the client can get the rights to allocate buffers
from the GPU. Otherwise, the client processes will failed to initialize the
hardware accelerated DRM engine driver.

Also note that, only the server (`mginit`) needs the root privilege.

## Known Issues

The following known issues are about hardware cursor of DRM engine (only
for MiniGUI 5.0.0):

- `drmSetCursor2` and `drmMoveCursor` do not work correctly in DRM engine.
  Libdrm does not provide an interface to set the correct cursor plane, and
  it seems that X held the cursor plane on my Linux PC.
- When using a AR24 plane for cursor, `drmSetPlane` seems having a bad
  performance.

## Future Features

In the near future, the MiniGUI team will:

* Enhance `drm` engine to support video plane/overlay.

