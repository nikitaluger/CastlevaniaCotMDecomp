extern u32 D_02021E90[];
extern u8 D_080CB007[];

/* Set up the status-screen background: store the horizontal scroll offset
 * (arg1 - 88) in 16.16 fixed point and select the character base block
 * from D_080CB007[arg0]. */
void sub_0800F3C8(u8 arg0, s32 arg1) {
    u32 scrollOff = 0x12BC;
    u32 controlOff = 0x12A2;
    s32 offset;
    u32 stored;
    u16 *control;
    u16 cur;
    u32 masked;
    u8 charBase;
    offset = (arg1 << 24) >> 8;
    stored = offset + 0xFFA80000;
    *(u32 *)((u8 *)D_02021E90 + scrollOff) = stored;
    control = (u16 *)((u8 *)D_02021E90 + controlOff);
    cur = *(vu16 *)control;
    masked = cur & 0xFFF3;
    *control = masked;
    charBase = D_080CB007[arg0];
    *control = (charBase << 2) | masked;
}
