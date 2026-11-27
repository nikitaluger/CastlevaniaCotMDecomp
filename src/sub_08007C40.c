extern u16 D_080C98D0[][8][8];
extern s32 getMetatileAttribute(s32, s32, s32);

/* Reads the low 6 bits of the map tile attribute at (x, y), but only when the
 * attribute word's 0x200 flag is set; off-map pixels and unset flags yield 0. */
s32 sub_08007C40(s32 map, s32 x, s32 y) {
    s32 pixel = getMetatileAttribute(map, x, y);
    if (pixel == -1)
        return 0;
    pixel = D_080C98D0[pixel][(y >> 16) & 7][(x >> 16) & 7];
    return (pixel & 0x200) ? (pixel & 0x3F) : 0;
}
