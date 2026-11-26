extern u16 D_080C98D0[][8][8];
extern s32 sub_08004740(s32, s32, s32);

/* Returns the terrain of the 8x8 cell under (x, y), both 16.16 fixed point, in
 * the given tilemap: 1 for a wall, the low 6 bits (slope id) for a slope, and
 * 0 for open ground. */
s32 getTileTerrain(s32 map, s32 x, s32 y) {
    s32 i = sub_08004740(map, x, y);
    if (i == -1)
        return 0;
    i = D_080C98D0[i][(y >> 16) & 7][(x >> 16) & 7];
    if (i & 0x80)
        return 1;
    return (i & 0x8000) ? (i & 0x3F) : 0;
}
