extern void *spawnBudgetedEffect(void *, s32);
extern void *gMainWorkspace;
void sub_080B72F4(void *arg0, s32 arg1)
{
    u8 *src;
    void *r2;
    u32 flag;
    s32 v;
    void **nv;
    nv = (void **) (((u8 *) gMainWorkspace) + 0x1870);
    src = *(u8 **)((u8 *)arg0 + 0x3C);
    r2 = spawnBudgetedEffect(*nv, 0xE3 * 2);
    if (r2 != 0)
    {
        unsigned long long tmp;
        s32 x;
        *(u32 *)((u8 *)r2 + 0x4C) = *(u32 *)(src + 8);
        x = (tmp = *(u32 *)(src + 0xC));
        *(u32 *)((u8 *)r2 + 0x5C) = x + 0xFFEC0000;
        flag = (*(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x38) + 2) & 0x10);
        v = -1;
        if (flag)
            v = 1;
        *(s8 *)((u8 *)r2 + 0x6C) = v;
        *(s8 *)((u8 *)r2 + 0x70) = arg1;
    }
}
