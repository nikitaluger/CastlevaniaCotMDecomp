void sub_08000E54(s32, s32, s32, s32, s32);
void postDisplaySprite(s32, s32, s32, s32, s32);
void sub_0800EB44(u16, s32, s32);
extern u8 D_0865FDF4[];
extern u8 D_080D00EC[];
extern u16 D_080CFF98[];
extern u8 gCameraState[];
extern u8 D_0865E2F4[];

/* Loads a graphic set's tiles and palette into VRAM/PALRAM from the compressed
 * graphics bank. id 0xFF is a special full load; id 0 shares the base tiles. */
void sub_0800EF3C(u8 gfxId) {
    u8 id = gfxId;
    u32 tileSrcOffset, palSrcOffset;
    u16 entryIndex, tileInfo;
    u8 *tileInfoTable = D_0865FDF4;
    u8 *gfxIndexTable = D_080D00EC;
    entryIndex = *(u16*)(gfxIndexTable + id * 4);
    tileInfo = *(u16*)(tileInfoTable + entryIndex * 8 + 4);
    tileSrcOffset = (tileInfo & 0x3FF) << 5;
    palSrcOffset = (tileInfo >> 12) << 5;

    if (id == 0xFF) {
        u8 *vramBase = gCameraState;
        u32 vramCfgOffset = 0x1262;
        u32 vramCfgAddr = (u32)(vramBase + vramCfgOffset);
        u32 vramDest = ((*(u16*)vramCfgAddr & 0xC) << 12) + 0x06000040;
        sub_08000E54(1, 0, vramDest, 0x6C0, 0x10);
    } else {
        u16 tileIndex = D_080CFF98[id];
        sub_0800EB44(tileIndex, 2, 0x6C0);
    }

    if (id == 0xFF || id == 0) {
        u8 *vramBase = gCameraState;
        u32 vramCfgOffset = 0x1262;
        u32 vramCfgAddr = (u32)(vramBase + vramCfgOffset);
        u32 vramDest = ((*(u16*)vramCfgAddr & 0xC) << 12) + 0x06005EC0;
        sub_08000E54(1, 0, vramDest, 0x80, 0x10);
    } else {
        u32 tileSrc = (u32)D_0865E2F4 + tileSrcOffset;
        u8 *vramBase = gCameraState;
        u32 vramCfgOffset = 0x1262;
        u32 vramCfgAddr = (u32)(vramBase + vramCfgOffset);
        u32 vramDest = ((*(u16*)vramCfgAddr & 0xC) << 12) + 0x06005EC0;
        postDisplaySprite(1, tileSrc, vramDest, 0x80, 0x10);
        postDisplaySprite(1, palSrcOffset + 0x05000200, 0x05000080, 0x20, 0x10);
    }
}
