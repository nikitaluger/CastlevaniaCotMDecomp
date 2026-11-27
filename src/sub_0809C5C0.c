extern void *spawnBudgetedEffect(s32 parent, s32 type);

/*
 * Spawns one effect object of type 0x17E under `parent` and stores position x
 * at +0x4C, y at +0x5C and clears the field at +0x6C.  Does nothing when the
 * spawn budget is exhausted.
 */
void sub_0809C5C0(s32 parent, s32 x, s32 y) {
    void *obj;

    obj = spawnBudgetedEffect(parent, 0x17E);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(s32 *)((u8 *)obj + 0x6C) = 0;
    }
}
