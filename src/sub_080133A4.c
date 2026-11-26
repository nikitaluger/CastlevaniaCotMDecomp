extern u8 D_02023130[];
extern u8 D_080CB278[];
struct SGlobalsMap { u8 pad[0x18A8]; u8 mapIndex; };
extern struct SGlobalsMap gMainWorkspace;
s32 sub_08007D7C(u8 *, s32, s32);

/* Tests whether the terrain under fixed-point world position (x, y), looked up
 * in the current map, has one of the 0xA flags set in the terrain-property table. */
u32 sub_080133A4(s32 x, s32 y) {
    s32 terrain;
    u32 flagsBase;
    terrain = sub_08007D7C(D_02023130 + (gMainWorkspace.mapIndex << 6), x, y);
    flagsBase = (u32)D_080CB278;
    if ((0xA & *(u16 *)(flagsBase + ((u32)(terrain << 16) >> 15))) != 0) return 1;
    return 0;
}
