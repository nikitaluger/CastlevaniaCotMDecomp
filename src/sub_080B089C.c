struct S_02025FF0 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0 gMainWorkspace;
extern void *spawnBudgetedEffect(void *, s32);

/* Spawn a 0x1AC entity at fixed-point position (x, y): allocate one from the
 * entity pool and store its position. */
void sub_080B089C(s32 x, s32 y) {
    void *ent = spawnBudgetedEffect((void *)gMainWorkspace.p, 0xD6 << 1);
    if (ent != NULL) {
        *(s32 *)((u8 *)ent + 0x4C) = x;
        *(s32 *)((u8 *)ent + 0x5C) = y;
    }
}
