s32 sub_08005820(s32);
void sub_080B074C(s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Spawn effect 0x1AA at a random point inside the visible area: X in
 * [0x108000, 0x108000+0xD00000] and Y in [0xF8000, 0xF8000+0x180000] above
 * the current camera origin. */
void sub_080B0778(void) {
    u8 *coordTable;
    u8 *cameraIndex;
    u8 *xBase;
    u8 *yBase;
    u32 coordOffset;
    s32 spawnX;
    s32 spawnY;

    coordTable = D_02021E90;
    cameraIndex = D_02025FF0;
    cameraIndex += 0x18A8;
    xBase = coordTable + 0x1278;
    spawnX = sub_08005820(0xD00000);
    spawnX += 0x108000;
    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    spawnX += *(s32 *)(coordOffset + (u32)xBase);
    yBase = coordTable + 0x127C;
    spawnY = sub_08005820(0x180000);
    spawnY += 0xF8000;
    coordOffset = ((u32)*cameraIndex + 1) * 0x40;
    spawnY += *(s32 *)(coordOffset + (u32)yBase);
    sub_080B074C(spawnX, spawnY);
}
