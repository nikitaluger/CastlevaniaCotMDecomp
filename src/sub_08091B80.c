struct S_02025FF0_ab { u8 _0x000[0x1868]; s32 v1868; u8 _pad[0x1874 - 0x186C]; s32 v1874; };
extern struct S_02025FF0_ab gMainWorkspace;
void *spawnBudgetedEffect(s32, s32);

/* Spawn a child effect: allocate one from the 0x1868 pool (type 0x210), fill
 * in its position / depth / effect-id fields, and return it (or NULL when the
 * pool is exhausted). */
void *sub_08091B80(s32 x, s32 y, s32 speed, s32 depth, s32 effectId) {
    void *effect = spawnBudgetedEffect(gMainWorkspace.v1868, 0x210);
    if (effect == NULL) return NULL;
    *(s32 *)((u8 *)effect + 0x4C) = x;
    *(s32 *)((u8 *)effect + 0x5C) = y;
    *(s32 *)((u8 *)effect + 0x7C) = speed;
    *(s32 *)((u8 *)effect + 0x8C) = depth;
    *(s32 *)((u8 *)effect + 0x9C) = effectId;
    return effect;
}
