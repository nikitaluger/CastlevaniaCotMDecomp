struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;
void *sub_0805FAEC(s32, s32);

/* Spawn a kind-1 object at fixed-point position (x, y) with 16-bit parameter
 * `param`: allocate it, fill in its position and parameter, then tag its kind. */
void *sub_0808DBF8(s32 x, s32 y, u16 param) {
    void *obj = sub_0805FAEC(D_02025FF0.v, 0x202);
    if (obj == NULL) return NULL;
    {
        u8 *p = obj;
        *(s32 *)(p + 0x4C) = x;
        *(s32 *)(p + 0x5C) = y;
        p += 0x6C;
        *(u16 *)p = param;
    }
    *(u8 *)((u8 *)obj + 0x74) = 1;
    return obj;
}
