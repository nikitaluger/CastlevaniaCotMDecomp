struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;
void *sub_0805FAEC(s32, s32);

/* Spawn variant-2 effect at fixed-point position (x, y) with 16-bit parameter
 * `param`: allocate it, fill in its position and parameter, then tag its
 * variant. Returns NULL when the pool is exhausted. */
void *sub_0808DC40(s32 x, s32 y, u16 param) {
    void *obj = sub_0805FAEC(D_02025FF0.v, 0x203);
    if (obj == NULL) return NULL;
    {
        u8 *p = obj;
        *(s32 *)(p + 0x4C) = x;
        *(s32 *)(p + 0x5C) = y;
        p += 0x6C;
        *(u16 *)p = param;
    }
    *(u8 *)((u8 *)obj + 0x74) = 2;
    return obj;
}
