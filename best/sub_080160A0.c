void sub_080160A0(s32 a0, s32 a1, s32 a2, s32 a3, u8 *arg5)
{
    u8 *q;
    s32 v4, v8;

    *(u16 *)(*(u8 * volatile *)(arg5 + 0x1C)) = *(u16 *)(arg5 + 2);
    if (*(u16 *)(arg5 + 2) & 0xF0) {
        if (*(u16 *)(arg5 + 2) & 0x60) {
            q = *(u8 * volatile *)(arg5 + 0x1C);
            v4 = *(s32 *)(arg5 + 0xC) - (*(s32 *)(arg5 + 4) + *(s32 *)(arg5 + 0x14)) + ((a0 & 0xFFFF0000) - (a2 & 0xFFFF0000));
            v8 = (a1 & 0xFFFF0000) - (a3 & 0xFFFF0000);
        } else {
            q = *(u8 * volatile *)(arg5 + 0x1C);
            v4 = (a0 & 0xFFFF0000) - (a2 & 0xFFFF0000);
            v8 = *(s32 *)(arg5 + 0x10) - (*(s32 *)(arg5 + 8) + *(s32 *)(arg5 + 0x18)) + ((a1 & 0xFFFF0000) - (a3 & 0xFFFF0000));
        }
    } else {
        q = *(u8 * volatile *)(arg5 + 0x1C);
        v4 = *(s32 *)(arg5 + 0xC) - (*(s32 *)(arg5 + 4) + *(s32 *)(arg5 + 0x14)) + ((a0 & 0xFFFF0000) - (a2 & 0xFFFF0000));
        v8 = *(s32 *)(arg5 + 0x10) - (*(s32 *)(arg5 + 8) + *(s32 *)(arg5 + 0x18)) + ((a1 & 0xFFFF0000) - (a3 & 0xFFFF0000));
    }
    *(s32 *)(q + 4) = v4;
    *(s32 *)(q + 8) = v8;
    *(s32 *)(q + 0xC) = a0 - a2;
    *(s32 *)(q + 0x10) = a1 - a3;
}
