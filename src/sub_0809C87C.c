struct S_02025FF0 { u8 _0[0x1870]; u32 parent; };
extern struct S_02025FF0 gMainWorkspace;

void *spawnBudgetedEffect(void *, s32);

/* Spawn a case-1 object at fixed-point position (x, y): allocate one from the
 * entity pool and store its position. */
void sub_0809C87C(s32 x, s32 y) {
    void *obj = spawnBudgetedEffect((void *)gMainWorkspace.parent, 0xBC << 1);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
    }
}
