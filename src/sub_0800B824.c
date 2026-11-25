extern s32 sub_08000E98(s32, s32, s32, s32, s32);
extern s32 sub_0805FE28(s32, u32);
extern s32 sub_0805FEC8(u16);
extern u16 D_02021E90[];

/* Play sound `soundId`, then DMA-copy `byteCount` bytes of tile data into the
 * background character area: from tile row (tileRow + 0x100) to tile row
 * `tileRow`, within the current VRAM character block. */
void sub_0800B824(u16 soundId, u16 tileRow, s32 byteCount) {
    u16 srcRow;
    s32 vramBase;
    srcRow = tileRow;
    sub_0805FE28(1, (u32)((tileRow << 16) + 0x01000000) >> 16);
    sub_0805FEC8(soundId);
    vramBase = (0xC & D_02021E90[0x951]) << 0x0C;
    sub_08000E98(1,
        vramBase + ((srcRow + 0x100) << 5) + 0x06000000,
        vramBase + (srcRow << 5) + 0x06000000,
        byteCount,
        0x10);
}
