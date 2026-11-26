struct ScrollBounds {
    u32 scrollXMin;
    u32 scrollXMax;
    u32 scrollYMin;
    u32 scrollYMax;
    u8 scrollXEnabled;
    u8 scrollYEnabled;
};

extern struct ScrollBounds D_02027A00;
extern u8 gCameraState[];

/* Clamp the horizontal and vertical scroll positions to the configured
 * min/max bounds whenever that axis's scrolling is enabled. */
void sub_08061E60(void)
{
    u8 *boundsBase, *boundsBase2;
    struct ScrollBounds *bounds, *boundsAlias;
    u8 xEnabled, yEnabled;
    u32 off;
    u32 *value;
    u32 v;

    boundsBase = (u8 *)&D_02027A00;
    xEnabled = boundsBase[0x10];
    bounds = (struct ScrollBounds *)boundsBase;
    if (xEnabled != 0) {
        off = 0x1278;
        value = (u32 *)(gCameraState + off);
        if (*value > bounds->scrollXMax)
            *value = bounds->scrollXMax;
        v = *value;
        if (v + 0x80000 < bounds->scrollXMin + 0x80000)
            *value = bounds->scrollXMin;
    }
    boundsBase2 = (u8 *)&D_02027A00;
    yEnabled = boundsBase2[0x11];
    boundsAlias = (struct ScrollBounds *)boundsBase2;
    if (yEnabled != 0) {
        off = 0x127C;
        value = (u32 *)(gCameraState + off);
        if (*value > boundsAlias->scrollYMax)
            *value = boundsAlias->scrollYMax;
        v = *value;
        if (v + 0x80000 < boundsAlias->scrollYMin + 0x80000)
            *value = boundsAlias->scrollYMin;
    }
}
