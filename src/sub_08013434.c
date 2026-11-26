extern u8 D_02023130[];
extern u8 D_080CB278[];
struct S_02025FF0_18A8 { u8 _0x000[0x18A8]; u8 v; };
extern struct S_02025FF0_18A8 gMainWorkspace;
s32 getTileTerrain(u8 *, s32, s32);

/* Return the tile-behavior word for the terrain under (x, y): look up the
 * terrain id in the current map and index the behavior table with it. */
u16 sub_08013434(s32 x, s32 y) {
    u8 *tbl = D_080CB278;
    s32 terrain = getTileTerrain(D_02023130 + (gMainWorkspace.v << 6), x, y);
    return *(u16 *)(tbl + ((u32)(terrain << 16) >> 15));
}
