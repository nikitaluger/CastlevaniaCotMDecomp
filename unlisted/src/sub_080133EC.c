extern u8 gTilemapPages[]; /* room metatile map, 64 bytes per map */
extern u8 gTileTerrainFlags[]; /* terrain attribute table, one u16 per terrain id */
struct S_02025FF0_18A8 { u8 _0x000[0x18A8]; u8 v; };
extern struct S_02025FF0_18A8 gMainWorkspace;
s32 getTileTerrain(u8 *, s32, s32);

/* Return 1 when the terrain under world position (x, y) has any of the
 * attribute bits 0xE set, otherwise 0. */
u32 sub_080133EC(s32 x, s32 y) {
    s32 terrain;
    u32 attrTable;
    terrain = getTileTerrain(gTilemapPages + (gMainWorkspace.v << 6), x, y);
    attrTable = (u32)gTileTerrainFlags;
    if ((0xE & *(u16 *)(attrTable + ((u32)(terrain << 16) >> 15))) != 0) return 1;
    return 0;
}
