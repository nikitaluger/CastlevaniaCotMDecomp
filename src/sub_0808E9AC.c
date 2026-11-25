s32 sub_0808EA0C(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x30);
    s32 ret = 0;
    while (p != NULL) {
        if (*(s16 *)p == 0x20E) { ret = 1; break; }
        p = *(u8 **)(p + 0x2C);
    }
    return ret;
}

struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;
extern void *sub_0805FAEC(s32, s32);

/* Allocate a kind-0x20D object at fixed-point position (x, y) with 16-bit
 * parameter `param`, filling in its position/parameter fields; return NULL
 * when the object pool is exhausted. */
void *sub_0808E9AC(s32 x, s32 y, u16 param) {
    void *obj = sub_0805FAEC(D_02025FF0.v, 0x20D);
    if (obj == NULL) return NULL;
    {
        u8 *p = obj;
        *(s32 *)(p + 0x4C) = x;
        *(s32 *)(p + 0x5C) = y;
        p += 0x6C;
        *(u16 *)p = param;
    }
    return obj;
}
