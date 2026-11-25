/* Large shared state block; +0x20 holds the map/tile-query flags. */
struct GameGlobals {
    u8 _0[0x20];
    u32 stateFlags;   /* bit 2: force the query result to 1; bit 1: off-map default */
};
extern struct GameGlobals D_02025FF0;

/* Per-tile-id 8x8 grid of tile attribute words (y within grid, then x). */
extern u16 D_080C98D0[];

s32 sub_08004740(s32, s32, s32);

/* Return the low 6 bits of the attribute word at bit 0x100 of the map tile
 * under the given 16.16 position; an off-map lookup (-1) falls back to bit 1
 * of the shared state flags, and bit 2 of those flags forces a 1. */
u16 sub_08007BC8(s32 arg0, s32 arg1, s32 arg2)
{
    struct GameGlobals *globals;
    s32 tile;
    u32 result;
    u16 *table;

    globals = &D_02025FF0;
    if (globals->stateFlags & 4) {
        return 1;
    }

    result = sub_08004740(arg0, arg1, arg2);
    if ((s32)result == -1) {
        result = (globals->stateFlags >> 1) & 1;
    } else {
        s32 offset;
        u32 attr;
        tile = (s32)result;
        table = D_080C98D0;
        offset = ((arg1 >> 16) & 7) * 2;
        offset += ((arg2 >> 16) & 7) * 0x10;
        offset += tile << 7;
        result = *(u16 *)((u8 *)table + offset);
        if (result & 0x100) {
            attr = result & 0x3F;
        } else {
            attr = 0;
        }
        result = attr;
    }
    return (u16)result;
}
