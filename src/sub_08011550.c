extern s32 sub_08010F5C(s32, void *, s32, s32, s32, s32, s32);
extern s32 sub_08010FA4(s32, void *, s32, s32, s32, s32, s32);

/* Set the animator's frame index at +0xE, then start that frame through the
 * front helper when direction >= 0, or the back helper otherwise. */
void sub_08011550(s32 arg0, void *arg1, u16 arg2, s32 arg3, s32 arg4) {
    u16 frameIndex;
    u8 flagByte;
    void *frameTable;
    void *frameTable2;

    frameIndex = arg2;
    flagByte = (u8) arg4;
    *(u16 *)((s8 *)arg1 + 0xE) = frameIndex;
    if (arg3 >= 0) {
        frameTable = *((void **)((s8 *)arg1 + 8));
        sub_08010F5C(arg0, arg1, *(s32 *)((s8 *)frameTable + 0) + ((s32)(frameIndex << 0x10) >> 0xE), *(s32 *)((s8 *)frameTable + 4), *(s32 *)((s8 *)frameTable + 8), *(s32 *)((s8 *)arg1 + 0x10), (s32)flagByte);
        return;
    }
    frameTable2 = *((void **)((s8 *)arg1 + 8));
    sub_08010FA4(arg0, arg1, *(s32 *)((s8 *)frameTable2 + 0) + ((s32)(frameIndex << 0x10) >> 0xE), *(s32 *)((s8 *)frameTable2 + 4), *(s32 *)((s8 *)frameTable2 + 8), *(s32 *)((s8 *)arg1 + 0x10), (s32)flagByte);
}
