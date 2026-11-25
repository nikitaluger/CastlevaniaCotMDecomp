s32 sub_08005820(s32);
s32 sub_080A2E38(s32);
void sub_080A2E74(void);

void sub_080A2C38(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C);
    s32 *slotbase;
    s32 *timerbase;
    s32 *slotp;
    s32 i;

    slotbase = (s32 *)(p + 0x48);
    i = 0;
    timerbase = (s32 *)(p + 0x74);
    slotp = slotbase;

    for (; i <= 10; i++) {
        s32 off = i << 2;
        u32 base2 = (u32)((u8 *)slotbase + 0x2C);
        s32 *tp = (s32 *)((u32)off + base2);
        s32 v = *tp;
        if (v != 0) {
            v--;
            *tp = v;
            if (v == 0) {
                *slotp = sub_080A2E38(i);
            }
        }
        slotp++;
    }

    if (*(u8 *)((u8 *)arg0 + 0x4C) != 0) {
        s32 count = 0;
        s32 *cp;
        u32 j;

        cp = slotbase;
        i = 10;
        do {
            if (*cp != 0)
                count++;
            cp++;
        } while (--i >= 0);

        j = 0;
        while (j < *(u32 *)((u8 *)arg0 + 0x5C)) {
            s32 r = sub_08005820(count);
            s32 k = -1;
            s32 m = 0;
            s32 jp1 = j + 1;
            s32 cm1 = count - 1;
            for (; m <= 10; m++) {
                if (*((s32 *)((m << 2) + (u8 *)slotbase)) != 0) {
                    k++;
                    if (r == k) {
                        sub_080A2E74();
                        *((s32 *)((m << 2) + (u8 *)slotbase)) = 0;
                        *((s32 *)((m << 2) + (u8 *)timerbase)) = 0x5A;
                        break;
                    }
                }
            }
            count = cm1;
            j = jp1;
        }

        *(u8 *)((u8 *)arg0 + 0x4C) = 0;
    }
}
