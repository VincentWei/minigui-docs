# 公共结构和定义

## 1 AlignValues

- 水平对齐枚举值

```c
enum enumNCSAlign{
    NCS_ALIGN_LEFT = 0,
    NCS_ALIGN_RIGHT,
    NCS_ALIGN_CENTER
};
```

- 垂直对齐枚举值

```c
enum enumNCSVAlign{
    NCS_VALIGN_TOP = 0,
    NCS_VALIGN_BOTTOM,
    NCS_VALIGN_CENTER
};
```

## 2 ImageDrawModeValues

```c
enum enumNCSImageDrawMode{
    /*普通方式绘制， 不拉伸也不平铺，默认情况下，居中（水平和垂直方向）显示图片。
      对于某些控件，如Image，可以通过控件本身对齐设置来改变*/
    NCS_DM_NORMAL = 0,
    /* 拉伸或者缩写图片，以适应填充区域
    */
    NCS_DM_SCALED,
    /* 当图片的大小小于被填充区域时，平铺填满整个区域。平铺时，以行优先填充
    */
    NCS_DM_TILED
};
```

## 3 渲染器属性ID定义规范
