s32 scaleByRandom(s32);
s32 sub_08026C7C(s32, s32, s32, s32, s32);
void sub_080C31E0(void *, s32);

/* While the object's effect flag (bit 0 at +0x64) is set, spawn a 0xB0-byte
 * effect object at the work object's fixed-point position with a random
 * 0x2000..0x3FFF parameter, then run the object's handler at +0x24. */
void sub_08027970(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    if (1 & *(u16 *)((u8 *)arg0 + 0x64)) {
        sub_08026C7C(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0,
                     scaleByRandom(0x2000) + 0x2000, (s32)*(s16 *)(work + 0x1C));
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
