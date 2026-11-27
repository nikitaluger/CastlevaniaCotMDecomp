struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern u16 D_08102E10[];
extern void *spawnBudgetedEffect(void *a, s32 b);

/* Spawn a projectile whose type is picked from D_08102E10 by index, then store
 * four caller-supplied init parameters on the new object. */
void sub_080B9834(s32 kind, s32 variant, s32 x, s32 y, s32 direction) {
    void *manager = (void *)gMainWorkspace.v;
    u16 typeId = D_08102E10[kind];
    void *obj = spawnBudgetedEffect(manager, typeId);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = variant;
        *(s32 *)((u8 *)obj + 0x5C) = x;
        *(s32 *)((u8 *)obj + 0x6C) = y;
        *(s32 *)((u8 *)obj + 0x7C) = direction;
    }
}
