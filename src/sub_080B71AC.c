extern void *spawnBudgetedEffect(s32 parent, s32 type);

/* Spawn effect object kind 0x1C2 under the given parent at world position
 * (x, y), storing its spawn angle in +0x7C. */
void sub_080B71AC(s32 parent, s32 x, s32 y, s32 angle) {
    void *obj;

    obj = spawnBudgetedEffect(parent, 0x1C2);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(s32 *)((u8 *)obj + 0x7C) = angle;
    }
}
