/* identical to unregisterChildObject (matched), with its names changed by decompdecomp */
extern void *spawnBudgetedEffect(s32, s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

void *sub_0801C9A0(s32 arg0, s32 arg1)
{
    void *temp_r0 = spawnBudgetedEffect(gMainWorkspace.v, 0x90);
    s32 var_r0;
    s32 var_r1;

    if (temp_r0 == 0)
        return 0;

    var_r0 = arg0;
    if (var_r0 < 0)
        var_r0 += 0xFFFF;
    {
        s32 s0 = var_r0 >> 16;
        *(s16 *)((u8 *)temp_r0 + 0x4C) = (s16)s0;
    }

    var_r1 = arg1;
    if (var_r1 < 0)
        var_r1 += 0xFFFF;
    {
        s32 s1 = var_r1 >> 16;
        *(s16 *)((u8 *)temp_r0 + 0x54) = (s16)s1;
    }

    return temp_r0;
}

// Clears this entity from the graphics manager's 3-entry slot table (unless
// the flag at +0x6C is set), used when its graphics state is released.
void sub_0802279C(void *entity)
{
    if (!(2 & *(u16 *)((u8 *)entity + 0x6C)))
    {
        u32 *slotTable = *(u32 **)(*(u8 **)((u8 *)entity + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slotTable + 0x16;
        s32 i = 2;
        do
        {
            if (*slot == (u32)entity)
                *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}

void sub_08021630(void *arg0)
{
    void *r4 = *(void **)((u8 *)arg0 + 0x3C);
    setAnimationFrame(*(s32 *)((u8 *)arg0 + 0x38), (u8 *)r4 + 0x34, 0x26, 0);
    if (2 & *(u8 *)((u8 *)r4 + 0x34))
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}

void sub_0802165C(void *arg0)
{
    u8 *r1 = *(u8 **)((u8 *)arg0 + 0x3C);
    void *r4 = r1 + 0x34;
    *(u32 *)(r1 + 0x14) = 0;
    *(u32 *)(r1 + 0x10) = 0;
    setAnimationFrame(*(s32 *)((u8 *)arg0 + 0x38), r4, 0x2D, 0);
    if (2 & *(u8 *)r4)
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
