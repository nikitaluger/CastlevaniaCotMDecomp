extern void *spawnBudgetedEffect(s32, s32);
struct S_02025FF0 { u8 pad[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

/* Spawn a type-0x142 entity at fixed-point position (x, y) and store arg2 in
 * its field 0x5C. Returns the new entity, or NULL if allocation failed. */
void *sub_0805077C(s32 x, s32 y, u16 arg2) {
    void *entity = spawnBudgetedEffect(gMainWorkspace.v, 0x142);
    s32 fixedX, fixedY, tileX, tileY;
    if (entity == NULL)
        return NULL;
    fixedX = x;
    if (fixedX < 0)
        fixedX += 0xFFFF;
    tileX = fixedX >> 16;
    *(s16 *)((u8 *)entity + 0x4C) = tileX;
    fixedY = y;
    if (fixedY < 0)
        fixedY += 0xFFFF;
    tileY = fixedY >> 16;
    *(s16 *)((u8 *)entity + 0x54) = tileY;
    *(u16 *)((u8 *)entity + 0x5C) = arg2;
    return entity;
}
