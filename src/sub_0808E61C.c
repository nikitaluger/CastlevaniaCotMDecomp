void *sub_0805FAEC(s32, s32); /* allocate an effect object of the given kind */

struct S_02025FF0_all {
    u8 _p1[0x14AC];
    s32 v14AC;
    u8 _p2[0x1874 - 0x14B0];
    s32 particleType; /* 0x1874: scene's particle object kind */
};
extern struct S_02025FF0_all D_02025FF0;

/* Spawn a small effect particle of subtype 1 at (x, y) with horizontal speed vx
 * and an upward vertical speed |vy|; returns NULL when no slot is free. */
void *sub_0808E61C(s32 x, s32 y, s32 vx, s32 vy) {
    void *r = sub_0805FAEC(D_02025FF0.particleType, 0x20B);
    if (r == NULL) return NULL;
    *(s32 *)((u8 *)r + 0x4C) = x;
    *(s32 *)((u8 *)r + 0x5C) = y;
    *(s32 *)((u8 *)r + 0x6C) = vx;
    {
        s32 v = vy;
        if (v < 0) v = -v;
        *(s32 *)((u8 *)r + 0x7C) = -v;
    }
    *(u8 *)((u8 *)r + 0x94) = 1;
    return r;
}
