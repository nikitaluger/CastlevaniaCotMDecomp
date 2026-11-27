extern u32 gMainWorkspace[];
extern void *spawnBudgetedEffect(void *, s32);

/* Spawn the variant-0 falling effect at fixed-point position (x, y) with an
 * initial X velocity of velX: allocate it, fill in position and velocity, then
 * tag its variant as 0. Returns NULL when the pool is exhausted. */
void *sub_0808DBB4(s32 x, s32 y, u16 velX) {
    s32 r4 = x;
    s32 r5 = y;
    u16 r6 = velX;
    u32 off = 0x1874;
    void *obj = spawnBudgetedEffect(*(void **)((u8 *)gMainWorkspace + off), 0x201);
    if (obj == 0) return 0;
    *(s32 *)((u8 *)obj + 0x4C) = r4;
    *(s32 *)((u8 *)obj + 0x5C) = r5;
    {
        u8 *p = (u8 *)obj + 0x6C;
        u8 *q = p;
        s32 zero = 0;
        *(u16 *)p = r6;
        q += 8;
        *(u8 *)q = zero;
    }
    return obj;
}
