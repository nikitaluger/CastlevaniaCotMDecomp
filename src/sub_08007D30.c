extern u16 D_080C98D0[][8][8];
extern s32 sub_08004740(s32, s32, s32);

/* Look up the metatile at the given map position and return its low 6-bit
 * index when its 0x80 attribute bit is set, otherwise 0. */
s32 sub_08007D30(s32 mapCtx, s32 x, s32 y) {
    s32 metatile = sub_08004740(mapCtx, x, y);
    if (metatile == -1)
        return 0;
    metatile = D_080C98D0[metatile][(y >> 16) & 7][(x >> 16) & 7];
    return (metatile & 0x80) ? (metatile & 0x3F) : 0;
}
