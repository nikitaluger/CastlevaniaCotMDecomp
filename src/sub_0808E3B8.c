struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 ownerId; };
extern struct S_02025FF0_1874 gMainWorkspace;
void *spawnBudgetedEffect(s32, s32);

/* Spawn effect object 0x208 for the current owner at (x, y), carrying the
 * low 12 bits of param, with its state byte cleared. Returns the new object,
 * or NULL if the pool is full. */
void *sub_0808E3B8(s32 x, s32 y, u16 param) {
    void *effect = spawnBudgetedEffect(gMainWorkspace.ownerId, 0x208);
    if (effect == NULL) return NULL;
    *(s32 *)((u8 *)effect + 0x4C) = x;
    *(s32 *)((u8 *)effect + 0x5C) = y;
    {
        u16 masked = param & 0xFFF;
        u8 *p = (u8 *)effect + 0x6C;
        u8 zero = 0;
        *(u16 *)p = masked;
        *(u8 *)((u8 *)effect + 0x7C) = zero;
    }
    return effect;
}
