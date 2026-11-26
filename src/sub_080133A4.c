extern u8 gTilemapPages[];
extern u8 gTileTerrainFlags[];
struct SGlobalsMap { u8 pad[0x18A8]; u8 mapIndex; };
extern struct SGlobalsMap gMainWorkspace;
s32 getTileTerrain(u8 *, s32, s32);

/* Tests whether the terrain under fixed-point world position (x, y), looked up
 * in the current map, has one of the 0xA flags set in the terrain-property table. */
u32 sub_080133A4(s32 x, s32 y) {
    s32 terrain;
    u32 flagsBase;
    terrain = getTileTerrain(gTilemapPages + (gMainWorkspace.mapIndex << 6), x, y);
    flagsBase = (u32)gTileTerrainFlags;
    if ((0xA & *(u16 *)(flagsBase + ((u32)(terrain << 16) >> 15))) != 0) return 1;
    return 0;
}
