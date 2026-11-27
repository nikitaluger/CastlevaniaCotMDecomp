struct S_02025FF0 { u8 _0[0x1870]; u32 parent; };
extern struct S_02025FF0 gMainWorkspace;
extern void *spawnBudgetedEffect(void *, s32);

/* Spawn a hit spark at fixed-point position (x, y): allocate one from the
 * entity pool and store its position. */
void sub_080A5644(s32 x, s32 y) {
    void *spark = spawnBudgetedEffect((void *)gMainWorkspace.parent, 0xCA << 1);
    if (spark != NULL) {
        *(s32 *)((u8 *)spark + 0x4C) = x;
        *(s32 *)((u8 *)spark + 0x5C) = y;
    }
}
