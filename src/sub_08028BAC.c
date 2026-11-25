struct S_02025FF0_1870 { u8 _0[0x1870]; s32 v; };
extern struct S_02025FF0_1870 D_02025FF0;
extern void *sub_0805FAEC(s32, s32);

/* Spawn a type-0xB6 entity at fixed-point position (x, y) and store arg2 in
 * its field 0x5C. Returns the new entity, or NULL if allocation failed. */
void *sub_08028BAC(s32 x, s32 y, u16 arg2) {
    void *entity;
    s32 fixedX, fixedY, tileX, tileY;
    entity = sub_0805FAEC(D_02025FF0.v, 0xB6);
    if (entity == NULL) return NULL;
    fixedX = x;
    if (fixedX < 0) fixedX += 0xFFFF;
    tileX = fixedX >> 16;
    *(s16 *)((u8 *)entity + 0x4C) = (s16)tileX;
    fixedY = y;
    if (fixedY < 0) fixedY += 0xFFFF;
    tileY = fixedY >> 16;
    *(s16 *)((u8 *)entity + 0x54) = (s16)tileY;
    *(u16 *)((u8 *)entity + 0x5C) = arg2;
    return entity;
}
