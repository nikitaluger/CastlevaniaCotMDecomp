extern u16 D_080C98D0[][8][8];
extern s32 getMetatileAttribute(s32, s32, s32);

/* Look up the metatile at the given map position and return its 8x8 tile
 * attribute word, or 0 if the position is outside the map. */
u16 getTileAttrAtPos(s32 mapCtx, s32 x, s32 y)
{
    s32 tile = getMetatileAttribute(mapCtx, x, y);
    if (tile == -1)
        return 0;
    return D_080C98D0[tile][(y >> 16) & 7][(x >> 16) & 7];
}
