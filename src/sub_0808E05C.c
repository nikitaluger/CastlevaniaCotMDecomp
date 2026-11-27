struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 v; };
extern struct S_02025FF0_1874 gMainWorkspace;
void *spawnBudgetedEffect(s32, s32);

/* Spawn an object of the given kind at fixed-point position (x, y) with a
 * 16-bit parameter: allocate it, store its position, parameter and kind, and
 * return it (NULL when the pool is exhausted). */
void *sub_0808E05C(s32 x, s32 y, u16 kind, u16 param) {
    void *obj = spawnBudgetedEffect(gMainWorkspace.v, 0x206);
    if (obj == NULL) return NULL;
    {
        u8 *p = obj;
        *(s32 *)(p + 0x4C) = x;
        *(s32 *)(p + 0x5C) = y;
        p += 0x6C;
        *(u16 *)p = param;
        *(u16 *)((u8 *)obj + 0x74) = kind;
    }
    return obj;
}
