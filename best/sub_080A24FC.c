extern u8 D_02025FF0[];
extern u8 D_02021E90[];
void sub_08005E80(s32);

void sub_080A24FC(void *arg0)
{
    u8 *a = (u8 *)arg0;
    u8 *r8 = *(u8 **)(a + 0x38);
    u8 *r5 = *(u8 **)(a + 0x3C);
    u8 *r7 = r5 + 0x48;
    u8 *p4 = a + 0x4C;
    u8 *p5 = a + 0x50;
    u8 b3 = *p4;
    s8 sa = *(s8 *)p4;
    s8 sb = *(s8 *)p5;
    u8 *d = D_02025FF0;

    if (sa != sb)
    {
        u8 fl;
        *p5 = b3;
        if (*(s8 *)p4 == 0)
        {
            fl = 0;
        }
        else
        {
            s32 *q = (s32 *)(d + 0x1754);
            if (*q <= 0x40)
                *q = 0x41;
            sub_08005E80(0x171);
            fl = 1;
            *p4 = 0;
        }
        {
            s32 i = 0;
            u32 *qp = (u32 *)r7;
            do
            {
                u8 *u = (u8 *)*qp;
                qp++;
                u[1] = fl;
                i++;
            } while (i == 0);
        }
    }
    {
        u8 *pt = D_02021E90;
        u8 *pb = D_02025FF0;
        u8 *base1;
        u8 *base2;
        u32 idx;

        pb += 0x18A8;

        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)(r8 + 0x14) = *(u32 *)(r5 + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)(r8 + 0x18) = *(u32 *)(r5 + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
