s32 sub_080C31E0(s32, s32);

/* Script step: look up a table value from the current command byte, store the
 * adjusted result into the data block, and signal completion once the step's
 * countdown reaches zero. */
void sub_080A43AC(void *obj) {
    void *data = *(void **)((u8 *)obj + 0x3C);
    s32 tableAddr = 0x08671BFC;
    s32 cmdIdx = *(s16 *)((u8 *)obj + 0x22);
    s32 lookup = sub_080C31E0((s32)(*(u8 *)((u8 *)obj + cmdIdx * 2 + 0x19)) << 9, *(s32 *)tableAddr);
    *(s32 *)((u8 *)data + 0xC) = *(s32 *)((u8 *)obj + 0x7C) - (lookup << 1);
    {
        s32 remaining = *(s32 *)((u8 *)obj + 0x8C) - 1;
        *(s32 *)((u8 *)obj + 0x8C) = remaining;
        if (remaining == 0) {
            u16 result = 0x01 | *(u16 *)data;
            *(u16 *)data = result;
        }
    }
}
