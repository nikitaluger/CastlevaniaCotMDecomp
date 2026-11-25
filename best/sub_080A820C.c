extern s32 sub_08005910(s32, s32);
extern void sub_080114DC(void *, s32, s16, s32);
extern u8 D_0810201E[];

void sub_080A820C(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4) {
    u8 *p80;
    u8 *p90;
    u8 *p94;
    u8 *pA6;
    u8 *pA7;
    s32 r5;
    u32 i;

    if (*(u8 *)(arg0 + 0x4C) == (*(u32 *)(arg0 + 0x9C) & 1)) {
        return;
    }

    r5 = sub_08005910(
        *(u32 *)(arg4 + 0x1C) - *(u32 *)(arg4 + 0x08),
        *(u32 *)(arg4 + 0x18) - *(u32 *)(arg4 + 0x04));

    i = 0;
    p90 = arg4 + 0x90;
    p94 = arg4 + 0x94;
    p80 = arg4 + 0x80;
    pA7 = arg4 + 0xA7;
    pA6 = arg4 + 0xA6;

    {
        u8 *p = arg4 + 0x10;
        s32 off = 0;
        u8 *b4 = arg4 + 0x04;
        u8 *b8 = arg4 + 0x08;
        do {
            *(s32 *)((*(u8 **)(p)) + 0x5C) = *(s32 *)(b4 + off) + *(s32 *)(arg0 + 0x5C);
            *(s32 *)((*(u8 **)(p)) + 0x6C) = *(s32 *)(b8 + off) + *(s32 *)(arg0 + 0x6C);
            *(s16 *)((*(u8 **)(p)) + 0x8C) = (s16)r5;
            p += 0x14;
            off += 0x14;
            i++;
        } while (i <= 6);
    }

    {
        s32 r3v = *(u32 *)(p90) - *(u32 *)(arg4 + 0x7C);
        s32 r2v = *(u32 *)(p94) - *(u32 *)(p80);

        if ((u32)(r5 + 0xFFFFBFFF) > 0x00007FFE) {
            *(u16 *)(arg1 + 0x02) = (u16)(*(u16 *)(arg1 + 0x02) | 0x0010);
        } else {
            *(u16 *)(arg1 + 0x02) = (u16)(*(u16 *)(arg1 + 0x02) & 0xFFEF);
        }

        *(u32 *)(arg3 + 0x08) = *(u32 *)(p90) + *(s32 *)(arg0 + 0x5C);
        *(u32 *)(arg3 + 0x0C) = *(u32 *)(p94) + *(s32 *)(arg0 + 0x6C);

        if (*(u8 *)(pA7) != 0) {
            r5 = sub_08005910(r2v, r3v);
            r5 &= 0xFFFF;
            if (*(u8 *)(pA7) == 2) {
                r5 += *(u32 *)(arg4 + 0xA0);
            }
            if (*(u16 *)(arg1 + 0x02) & 0x0010) {
                *(u16 *)(arg1 + 0x08) = (u16)r5;
            } else {
                *(u16 *)(arg1 + 0x08) = (u16)(0xFFFF8000 - r5);
            }
        }
    }

    {
        s16 tv = *(s16 *)(D_0810201E + (*(u8 *)(pA6)) * 2);
        sub_080114DC(arg1, arg2, tv, 0);
    }
}
