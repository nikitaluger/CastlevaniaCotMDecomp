/* Return 1 when the global position (x at +0x174C, y at +0x1750) lies inside
   the axis-aligned box centered at (centerX, centerY) with half-size
   (halfW, halfH); otherwise return 0. */
s32 sub_080145D8(s32 centerX, s32 centerY, s32 halfW, s32 halfH) {
    u8 *global = (u8 *)0x02025FF0;
    if (*(s32 *)(global + 0x174C) < centerX - halfW) return 0;
    if (*(s32 *)(global + 0x174C) > centerX + halfW) return 0;
    if (*(s32 *)(global + 0x1750) < centerY - halfH) return 0;
    if (*(s32 *)(global + 0x1750) > centerY + halfH) return 0;
    return 1;
}
