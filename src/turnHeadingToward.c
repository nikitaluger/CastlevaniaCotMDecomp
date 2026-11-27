u8 sub_08072280(s32, s32, s32, s32);

/* Turn the heading byte at arg3+4 (one step of arg3+5 per call) toward the
 * direction from position (arg0+0, arg0+4) to (arg1, arg2); returns the heading. */
u8 turnHeadingToward(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    u8 target = sub_08072280(*(s32 *)arg0, *(s32 *)((u8 *)arg0 + 4), arg1, arg2);
    u8 diff = target - *(u8 *)((u8 *)arg3 + 4);
    if (diff != 0) {
        if (diff > 0x80)
            *(u8 *)((u8 *)arg3 + 4) = *(u8 *)((u8 *)arg3 + 4) - *(u8 *)((u8 *)arg3 + 5);
        else
            *(u8 *)((u8 *)arg3 + 4) = *(u8 *)((u8 *)arg3 + 4) + *(u8 *)((u8 *)arg3 + 5);
    }
    return *(u8 *)((u8 *)arg3 + 4);
}
