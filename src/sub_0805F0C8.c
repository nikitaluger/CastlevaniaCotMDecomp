struct S_02025FF0_187C { u8 _0x000[0x187C]; s32 v; };
extern struct S_02025FF0_187C gMainWorkspace;
extern void *spawnBudgetedEffect(s32, s32);

/* Spawn a small effect object (kind 0x1E9) from the shared effect pool, store
 * its parameter at obj+0x4C and clear the halfword at obj+0x5C. */
void *sub_0805F0C8(u16 param)
{
    void *obj = spawnBudgetedEffect(gMainWorkspace.v, 0x1E9);
    if (obj == NULL) return NULL;
    {
        u8 *fields = (u8 *)obj + 0x4C;
        u16 zero = 0;
        *(u16 *)fields = param;
        *(u16 *)((u8 *)obj + 0x5C) = zero;
    }
    return obj;
}
