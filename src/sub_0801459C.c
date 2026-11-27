extern s32 fixedPointDistance(s32, s32);

/* Return 1 when the object's (x,y) is within radius (per fixedPointDistance's
 * distance metric) of the shared focus point at 0x02025FF0+0x174C/0x1750. */
s32 sub_0801459C(void *obj, s32 radius) {
    u8 *base = (u8 *)0x02025FF0;
    s32 dx = *(s32 *)(base + 0x174C) - *(s32 *)((u8 *)obj + 8);
    s32 dy = *(s32 *)(base + 0x1750) - *(s32 *)((u8 *)obj + 0xC);
    if (fixedPointDistance(dx, dy) > radius) {
        return 0;
    }
    return 1;
}
