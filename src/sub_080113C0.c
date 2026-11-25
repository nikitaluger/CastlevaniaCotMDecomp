/* Set the current frame index in the sprite descriptor and load that frame
 * from the descriptor's frame table: a direct entry when `single` is
 * non-negative, otherwise scan forward to the entry flagged with 0x8000. */
void sub_08010D50(s32 obj, void *desc, s32 frame, u8 flags);
void sub_08010D84(s32 obj, void *desc, s32 frame, u8 flags);

void sub_080113C0(s32 obj, void *desc, u16 index, s32 single, s32 flags) {
    u16 idx;
    u8 flagByte;

    idx = index;
    flagByte = (u8)flags;
    *(u16 *)((u8 *)desc + 0xE) = idx;
    if (single >= 0) {
        sub_08010D50(obj, desc, *(*(s32 **)((u8 *)desc + 8)) + ((s32)(idx << 0x10) >> 0xE), flagByte);
        return;
    }
    sub_08010D84(obj, desc, *(*(s32 **)((u8 *)desc + 8)) + ((s32)(idx << 0x10) >> 0xE), flagByte);
}
