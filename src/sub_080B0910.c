extern void *spawnBudgetedEffect(s32, s32);

/* Spawn a type-0x1AE entity under `parent` at fixed-point position (x, y) and
 * store the extra byte `param` in its +0x8C field. */
void sub_080B0910(s32 parent, s32 x, s32 y, u8 param) {
    void *ent;

    ent = spawnBudgetedEffect(parent, 0xD7 << 1);
    if (ent != NULL) {
        *(s32 *)((u8 *)ent + 0x4C) = x;
        *(s32 *)((u8 *)ent + 0x5C) = y;
        *(u8 *)((u8 *)ent + 0x8C) = param;
    }
}
