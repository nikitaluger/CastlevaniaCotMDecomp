void sub_08010DF8(void *arg0, void *arg1, void *arg2) {
    u8 *a0 = (u8 *)arg0;
    u8 *a1 = (u8 *)arg1;
    u8 *a2 = (u8 *)arg2;
    u8 f2;
    u8 entry;
    u8 *r4;
    u16 t3;
    u16 t3b;
    f2 = a1[0] & 2;
    if (f2 == 0) {
        *(s32 *)(a1 + 4) = *(s32 *)(a1 + 4) + 1;
        if (*(s32 *)(a1 + 4) > *(u16 *)(a1 + 2)) {
            u32 mask;

            entry = a1[1];
            r4 = a2 + entry * 4;
            t3 = *(u16 *)r4;
            mask = 0x8000;
            if ((t3 & mask) == 0) {
                *(u16 *)(a1 + 2) = t3;
                *(s32 *)(a1 + 4) = 1;
                a1[1] = a1[1] + 1;
                *(u16 *)(a0 + 0x28) = *(u16 *)(r4 + 2);
            } else {
                if (a1[0] & 1) {
                    a1[1] = 0;
                    t3b = *(u16 *)a2;
                    if ((t3b & mask) == 0) {
                        *(u16 *)(a1 + 2) = t3b;
                        *(s32 *)(a1 + 4) = 1;
                        a1[1] = 1;
                        *(u16 *)(a0 + 0x28) = *(u16 *)(a2 + 2);
                    }
                } else {
                    a1[0] = a1[0] | 2;
                }
            }
        }
    }
}
