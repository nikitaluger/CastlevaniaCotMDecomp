extern void sub_0800C804(u8 arg0, u16 arg1);
extern void sub_080C31E4(void *arg0, void *arg1, s32 arg2);
extern void sub_080C31E0(void *arg0, void *arg1);
extern u8 D_02021E90[];
extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern s32 D_08671BB0;

static inline u8 and0F(u8 b)
{
    u32 m = 0x0F;
    m &= b;
    return (u8)m;
}

void sub_0800C670(u8 *arg0)
{
    u8 *p4 = D_02025368;

    {
        u8 *base = D_02021E90;
        u16 *pw = (u16 *)(base + 0x1470);
        u32 m1, m2, m3;
        u16 v, r;
        u8 *p94, *q;
        v = *pw;
        m1 = 0xC0; m1 &= v;
        if (m1 != 0)
        {
            m2 = 0x40; m2 &= v;
            p94 = p4; p94 += 0x94;
            if (m2 != 0) { *p94 = *p94 - 1; }
            r = *pw;
            m3 = 0x80; m3 &= r;
            if (m3 != 0) { *p94 = *p94 + 1; }
            q = p94;
            if (*q == 0x10) { *q = 0; }
            if (*q == 0xFF) { *q = 0x0F; }
            sub_0800C804(*p94, 0x13);
        }
    }

    {
        u8 *base = D_02021E90;
        u16 *pw = (u16 *)(base + 0x1470);
        u32 m1, m2, m3;
        u16 v, r;
        u8 *p95, *q;
        v = *pw;
        m1 = 0x30; m1 &= v;
        if (m1 != 0)
        {
            m2 = 0x20; m2 &= v;
            p95 = p4; p95 += 0x95;
            if (m2 != 0) { *p95 = *p95 - 1; }
            r = *pw;
            m3 = 0x10; m3 &= r;
            if (m3 != 0) { *p95 = *p95 + 1; }
            q = p95;
            if (*q == 0x80) { *q = 0; }
            if (*q == 0xFF) { *q = 0x7F; }
            sub_0800C804(*p95, 0x33);
        }
    }

    {
        u8 *base = D_02021E90;
        u16 *pw = (u16 *)(base + 0x1470);
        u32 m1, m2, m3;
        u16 v, r;
        u8 *pf;
        v = *pw;
        m1 = 0xC0 << 2; m1 &= v;
        if (m1 != 0)
        {
            r = *pw;
            m2 = 0x80 << 2; m2 &= r;
            pf = D_02025FF0;
            if (m2 != 0) { *pf = *pf - 1; }
            r = *pw;
            m3 = 0x80 << 1; m3 &= r;
            if (m3 != 0) { *pf = *pf + 1; }
            *pf = and0F(*pf);
            sub_0800C804(*pf, 0x53);
        }
    }

    {
        u8 *base = D_02021E90;
        u16 *pw = (u16 *)(base + 0x1470);
        u32 m1;
        u16 v;
        u16 *p8c;
        s32 c;
        v = *pw;
        m1 = 0x04; m1 &= v;
        if (m1 != 0)
        {
            p8c = (u16 *)(p4 + 0x8C);
            c = *p8c + 1;
            *p8c = c;
            if ((s16)c > 4) { *p8c = 0; }
            sub_0800C804(*(u8 *)p8c, 0x73);
        }
    }

    {
        u8 *base = D_02021E90;
        u16 *pw = (u16 *)(base + 0x146C);
        u32 m1;
        u16 v;
        u8 *pf;
        u8 t;
        s32 zero;
        s16 idx;
        u8 *p18;
        s32 *fp;
        v = *pw;
        m1 = 0x09; m1 &= v;
        if (m1 != 0)
        {
            pf = D_02025FF0;
            t = *pf;
            zero = 0;
            *pf = t;
            idx = *(s16 *)(arg0 + 0x22);
            *(arg0 + idx * 2 + 0x19) = zero;
            fp = (s32 *)0x08671BB0;
            p18 = arg0 + 0x18;
            sub_080C31E4(p18, arg0 + 0x22, *fp);
            idx = *(s16 *)(arg0 + 0x22);
            *(arg0 + idx * 2 + 0x19) = *(arg0 + idx * 2 + 0x19) + 1;
            idx = *(s16 *)(arg0 + 0x22);
            p18 += idx * 2;
            {
                u8 c = *p18;
                sub_080C31E0(arg0, *(void **)(*(u32 *)(arg0 + 0x14) + c * 4));
            }
        }
    }
}
