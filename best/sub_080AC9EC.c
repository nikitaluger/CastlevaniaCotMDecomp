extern void sub_0801165C(void *a, s32 b);
extern u8 D_081021F4[];
void sub_080AC9EC(void *p2, void *p1, void *p0) {
    u8 *base = (u8 *)p2 + 0x0C;
    s8 b = *(s8 *)((u8 *)p2 + 0x2E);
    switch (b) {
    case 0:
        return;
    case 1:
        *(s32 *)((u8 *)p1 + 0x10) =
            (*(u16 *)((u8 *)p0 + 0x02) & 0x10) ? 0x1000 : -0x1000;
        if (*(s32 *)((u8 *)p2 + 0x20) < 0) sub_0801165C(p1, 0);
        break;
    case -1:
        *(s32 *)((u8 *)p1 + 0x10) =
            (*(u16 *)((u8 *)p0 + 0x02) & 0x10) ? -0x1000 : 0x1000;
        if (*(s32 *)((u8 *)p2 + 0x20) > 0) sub_0801165C(p1, 0);
        break;
    }
    {
        u32 i = 0;
        u8 *base2 = (u8 *)p2 + 0x20;
        s32 *lo = (s32 *)D_081021F4;
        s32 *hi = (s32 *)(D_081021F4 + 4);
        do {
            s32 *obj = *(s32 **)(base + i * 4);
            s32 *vel = (s32 *)(base2 + i * 4);
            s32 val = *(s32 *)((u8 *)obj + 0x5C) + *vel;
            *(s32 *)((u8 *)obj + 0x5C) = val;
            if (val > *hi) {
                *(s32 *)((u8 *)obj + 0x5C) = *hi;
                *vel = -(*vel);
            } else if (val < *lo) {
                *(s32 *)((u8 *)obj + 0x5C) = *lo;
                *vel = -(*vel);
            }
            lo += 4;
            hi += 4;
            i++;
        } while (i < 2);
    }
}
