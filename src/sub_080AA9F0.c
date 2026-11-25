struct S_02025FF0_1870 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0_1870 D_02025FF0;
void *sub_0805FAEC(void *, s32);

/* Spawn a projectile at fixed-point (x, y) with a launch angle and subtype:
 * allocate a 0x19C object, fill in its position, angle and subtype, and return
 * it (NULL when the pool is exhausted). */
void *sub_080AA9F0(s32 x, s32 y, s32 angle, u8 subtype) {
    void *obj = sub_0805FAEC((void *)D_02025FF0.p, 0xCE << 1);
    if (obj == NULL) return NULL;
    {
        u8 *p = obj;
        *(s32 *)(p + 0x4C) = x;
        *(s32 *)(p + 0x5C) = y;
        *(s32 *)(p + 0x6C) = angle;
        p += 0x7C;
        *(u8 *)p = subtype;
    }
    return obj;
}
