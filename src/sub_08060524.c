struct S_02021E90_605 {
    u8 pad0[0x143C];
    u8 f143C;
    u8 pad1[5];
    u8 f1442;
    u8 pad2[2];
    u8 f1445;
    u8 pad3[0xE];
    u8 *f1454;
};
extern struct S_02021E90_605 gCameraState;
s32 sub_080609F0(void);
void sub_08060A1C(u16);

/* Script command step: once the script timer elapses, decode a 16-bit
   graphics ID from two biased command-stream bytes, dispatch the graphics
   load, and advance the script cursor; otherwise keep waiting (return 2). */
s32 sub_08060524(void) {
    if (sub_080609F0() != 0) {
        u8 *cursor = gCameraState.f1454;
        u16 gfxId = (u16)((cursor[0] - 0x0C) << 8);
        gCameraState.f1454 = cursor + 1;
        gfxId = (u16)(gfxId + cursor[1] - 0x26);
        sub_08060A1C(gfxId);
        gCameraState.f1454 += 1;
        return 0;
    }
    return 2;
}
