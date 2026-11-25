extern void *sub_0800355C(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u32 D_080CA9E4[];

void sub_08008B98(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *obj = sub_0800355C();
    u8 *r4;
    u8 zero;
    u32 v;
    u32 m;
    u32 w;

    if (obj == NULL) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }
    *(void **)(self + 0x38) = obj;
    *(void **)((u8 *)obj + 0x14) = (void *)D_080CA9E4[*(u32 *)(self + 0x4C) * 2];
    *(void **)((u8 *)obj + 0x18) = (void *)D_080CA9E4[*(u32 *)(self + 0x4C) * 2 + 1];
    v = *(u16 *)((u8 *)obj + 2);
    m = 0x400;
    w = m;
    zero = 0;
    w |= v;
    *(u16 *)((u8 *)obj + 2) = (u16)w;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    {
        void **lit = (void **)0x08671BB0;
        r4 = self + 0x18;
        sub_080C31E4(r4, self + 0x22, *lit);
    }
    (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))++;
    r4 += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)r4 * 4));
}
