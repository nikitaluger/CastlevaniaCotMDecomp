/* Visibility test for a 16.16 fixed-point world point: translate it by the
 * camera position, transform by the view matrix rows, then reject the point if
 * the resulting coordinates fall outside the perspective view volume. */
s32 sub_080055B0(s32 worldX, s32 worldY, s32 z)
{
    s32 dx, dy, viewX, viewY, viewZ;
    s32 t, t2;

    t = worldX - *(s32 *)0x030026B0;
    if (t < 0) t += 0xFFFF;
    dx = t >> 16;

    t = worldY - *(s32 *)0x03002698;
    if (t < 0) t += 0xFFFF;
    dy = t >> 16;

    t = z - *(s32 *)0x030026AC;
    if (t < 0) t += 0xFFFF;
    z = t >> 16;

    t = dx * *(s32 *)0x02025FE8 + dy * *(s32 *)0x02025BC0 + z * *(s32 *)0x02025FD4;
    if (t < 0) t += 0xFF;
    viewX = t >> 8;

    if ((u32)(viewX - 0x80) > 0xF80) return 0;

    t2 = dx * *(s32 *)0x02025B90 + dy * *(s32 *)0x02025FD8 + z * *(s32 *)0x02025FE0;
    if (t2 < 0) t2 += 0xFF;
    viewY = t2 >> 8;

    t = dx * *(s32 *)0x02025B94 + dy * *(s32 *)0x02025B98 + z * *(s32 *)0x02025FD0;
    if (t < 0) t += 0xFF;
    viewZ = t >> 8;

    t = -(((((viewX << 1) + viewX) << 3) - viewX) << 3);
    if (t < 0) t += 0xFF;
    if (viewY <= t >> 8) return 0;

    t = 0xB8 * viewX;
    if (t < 0) t += 0xFF;
    if (viewY >= t >> 8) return 0;

    t = 0 - (viewX * 0x90);
    if (t < 0) t += 0xFF;
    if (viewZ <= t >> 8) return 0;
    if (viewZ > 0x8F) return 0;

    return 1;
}
