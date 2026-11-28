struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_080B07EC(void)
{
    void *r2 = *(void **)((u8 *)(void *)gMainWorkspace.v + 0x30);
    while (r2 != 0) {
        if (*(s16 *)r2 == 0x1AA) {
            u16 *p = *(u16 **)((u8 *)r2 + 0x3C);
            *p |= 1;
        }
        r2 = *(void **)((u8 *)r2 + 0x2C);
    }
}

extern void initCrossfadeGfxState(void);

/* If the entity's current command byte is 0x28, clear it and reload the
 * entity's command script from the default table. */
void sub_080B0E40(void *arg0)
{
    u8 *self = arg0;
    s16 slot = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + slot * 2 + 0x19) == 0x28) {
        s32 *lit;
        initCrossfadeGfxState();
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}

void sub_080B0EC4(void *arg0)
{
    u8 *self = arg0;
    s32 zero = 0;
    u8 *base18;
    s32 *lit;
    *(u8 *)(*(u8 **)(self + 0x3C) + 0x48 + 7) = zero;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    base18 = self + 0x18;
    sub_080C31E4(base18, self + 0x22, *lit);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    base18 += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)base18 * 4));
}

extern void sub_080B1960(void *, void *);

void sub_080B1180(void *arg0)
{
    u8 *self = arg0;
    void *r5 = *(void **)(self + 0x4C);
    sub_080B1960(*(void **)(self + 0x3C), r5);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 0x3C) {
        u8 v = *(u8 *)((u8 *)r5 + 0x25);
        if (v == 0) {
            s32 *lit;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = v;
            lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
