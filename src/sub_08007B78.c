extern u16 D_080C98D0[][8][8];
extern s32 getMetatileAttribute(s32, s32, s32);

/* Looks up a 6-bit attribute for the map pixel at (x, y): reads its 4bpp tile
 * pixel index, indexes the per-index 8x8 attribute table, and returns the low
 * 6 bits when the table entry's valid flag (0x100) is set. */
s32 sub_08007B78(s32 map, s32 x, s32 y) {
    s32 pixel = getMetatileAttribute(map, x, y);
    if (pixel == -1)
        return 0;
    pixel = D_080C98D0[pixel][(y >> 16) & 7][(x >> 16) & 7];
    return (pixel & 0x100) ? (pixel & 0x3F) : 0;
}
