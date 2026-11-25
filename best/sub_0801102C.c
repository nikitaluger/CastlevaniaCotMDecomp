void sub_080111D0(s32, s32, s32, s32);

void sub_0801102C(s32 arg0, u8 *arg1, u16 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 f2 = (u8)(arg1[0] & 2);
    u16 next;

    if (f2 == 0) {
        s32 c = *(s32 *)(arg1 + 4) + 1;
        *(s32 *)(arg1 + 4) = c;
        if (c > (s32)*(u16 *)(arg1 + 2)) {
            u8 *entry = (u8 *)arg2 + arg1[1] * 4;
            u16 e0 = *(u16 *)entry;
            if (!(e0 & 0x8000)) {
                *(u16 *)(arg1 + 2) = e0;
                *(s32 *)(arg1 + 4) = 1;
                arg1[1] = arg1[1] + 1;
                next = *(u16 *)(entry + 2);
            } else {
                if (!(arg1[0] & 1)) {
                    goto flagstore;
                }
                arg1[1] = f2;
                {
                    u16 e2 = arg2[0];
                    if (e2 & 0x8000) {
                        return;
                    }
                    *(u16 *)(arg1 + 2) = e2;
                }
                *(s32 *)(arg1 + 4) = 1;
                arg1[1] = 1;
                next = arg2[1];
            }
            sub_080111D0(arg0, (next << 3) + arg3, arg4, arg5);
        }
    }
    return;

flagstore:
    arg1[0] |= 2;
    return;
}
