void sub_08051F40(void *path, s32 duration);
extern void sub_080C31E8(void *, void *, s32, u32);

/* Start `path` as a nine-segment motion path spread over `duration` frames:
 * store the caller's header values at +2/+5/+6 (with the byte at +4 cleared),
 * precompute the per-segment steps, reset the script timer and advance the
 * command script with mode 5. */
void sub_08051F98(void *entity, void *path, s32 duration, s16 headerValue, s32 headerFlag) {
    s32 flag = headerFlag;
    *(u8 *)((u8 *)path + 4) = 0;
    *(u8 *)((u8 *)path + 5) = (u8)duration;
    *(u8 *)((u8 *)path + 6) = (u8)flag;
    flag = 0;
    *(s16 *)((u8 *)path + 2) = headerValue;
    sub_08051F40(path, duration);
    *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = (u8)flag;
    {
        u32 *scriptTable = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 5, *scriptTable);
    }
}
