struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 D_02025FF0;

extern u32 D_08671BB0[];

/* Starts the effect: reserve slot 3, allocate the graphics object, initialise
 * its fields, then run the setup callback and dispatch the first callback.
 * If either allocation fails, dispatch the completion callback instead. */
void sub_080898D0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *gfx;

    if (sub_0800168C(arg0, 0, 0x3C, 3) == 0)
    {
        _call_via_r1(arg0, *(s32 *)(self + 0x24));
        return;
    }

    gfx = sub_0800355C();
    if (gfx == 0)
    {
        _call_via_r1(arg0, *(s32 *)(self + 0x24));
        return;
    }

    *(void **)(self + 0x38) = gfx;
    *(u32 *)((u8 *)gfx + 0x1C) = 0x80000006;
    {
        u16 globalWord = D_02025FF0.w;
        u32 zero = 0;
        *(u16 *)gfx = globalWord;

        {
            s32 idx = *(s16 *)(self + 0x22);
            *(u8 *)(self + idx * 2 + 0x19) = zero;
        }
    }

    {
        const u32 *cbTable = (const u32 *)0x08671BB0;
        void *frameEntry = self + 0x18;
        _call_via_r2(frameEntry, self + 0x22, *cbTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        frameEntry = (u8 *)frameEntry + *(s16 *)(self + 0x22) * 2;
        _call_via_r1(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)frameEntry * 4));
    }
}
