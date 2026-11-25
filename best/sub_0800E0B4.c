extern void sub_08005E80(u16);
extern s32 sub_0800F414(s8);
extern void sub_0800F464(u8);
extern void sub_0805FDF0(void);
extern void sub_0805FE28(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

void sub_0800E0B4(u8 *arg0) {
    u8 *base = (u8 *)0x020278D0;
    u8 *p;
    s8 old;
    u16 *pm;
    u16 m;
    u8 *w;

    p = base + 0xF7;
    old = *(s8 *)p;
    w = (u8 *)0x02021E90;
    pm = (u16 *)(w + 0x1470);
    m = *pm;

    if ((m & 0xC0) != 0xC0) {
        if (m & 0x40) {
            *p = (u8)*p - 2;
        }
        if (*pm & 0x80) {
            *p = (u8)*p + 2;
        }
        *p = 7 & (u8)*p;
    }
    {
        u16 v = *pm & 0x30;
        if (v != 0x30 && v != 0) {
            u8 b = *p;
            if (b & 1) *p = b - 1;
            else *p = b + 1;
        }
    }
    if (*(s8 *)p != old) {
        sub_08005E80(0x139);
        sub_0800F464(*p);
    }
    {
        u16 m2 = *(u16 *)(w + 0x146C);
        u16 r6 = (u16)(m2 & 2);
        if (r6 != 0) {
            sub_08005E80(0x14F);
            *(u8 *)(base + 0x64) = 0;
            {
                u8 *q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                q[0x17] = 0;
            }
            {
                void **fnaddr = (void **)0x08671BD8;
                sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0xE, *fnaddr);
            }
            return;
        }
        if ((m2 & 1) != 0 && sub_0800F414(*(s8 *)p) != 0) {
            sub_08005E80(0x13B);
            sub_0805FDF0();
            sub_0805FE28(0, 2);
            {
                u8 *q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                q[0x19] = (s8)r6;
            }
            {
                void **fnaddr = (void **)0x08671BB0;
                sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *fnaddr);
            }
        }
    }
}
