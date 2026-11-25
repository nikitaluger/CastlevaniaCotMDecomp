extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

void sub_080AD8D4(void *arg0)
{
    s16 idx;
    u8 *base;
    u8 *p;
    s32 zero;

    sub_0800168C(arg0, 0, 0x64, 0);

    if (*(u32 *)((u8 *)arg0 + 0x3C) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    p = *(u8 **)((u8 *)arg0 + 0x3C);
    zero = 0;
    *(u16 *)(p + 0x1C) = 0x64;
    *(u8 *)((u8 *)arg0 + 0x7C) = zero;
    *(u16 *)((u8 *)arg0 + 2) |= 0x1000;

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[idx * 2 + 0x19] = zero;

    {
        void **lit = &D_08671BB0;
        base = (u8 *)arg0 + 0x18;
        sub_080C31E4(base, (u8 *)arg0 + 0x22, *lit);
    }

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[idx * 2 + 0x19]++;

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    base = base + idx * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + base[0] * 4));
}
