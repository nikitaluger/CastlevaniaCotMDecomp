extern s32 sub_080C31E0(s32, s32);

/* Advance the state's phase accumulator (+0xD4) by 0x200 and store
 * sin(phase) scaled down by 16 into +0xBC. */
void sub_080A88C0(void *arg0) {
    s32 temp_r0;

    temp_r0 = *(s32 *)((u8 *)arg0 + 0xD4) + 0x200;
    *(s32 *)((u8 *)arg0 + 0xD4) = temp_r0;
    *(s32 *)((u8 *)arg0 + 0xBC) = (s32)(sub_080C31E0(temp_r0, *(s32 *)0x08671BFC) >> 4);
}
