void *sub_0805FAEC(s32, s32); /* allocate an effect object of the given kind */

struct S_02025FF0_all {
    u8 _p1[0x14AC];
    s32 v14AC;
    u8 _p2[0x1874 - 0x14B0];
    s32 particleType; /* 0x1874: scene's particle object kind */
};
extern struct S_02025FF0_all gMainWorkspace;

/* Spawn a standard effect object at (x, y) carrying the low 12 bits of attr,
 * then activate it; returns NULL when no slot is free. */
void *sub_0808E408(s32 x, s32 y, u16 attr) {
    void *r = sub_0805FAEC(gMainWorkspace.particleType, 0x209);
    if (r == NULL) return NULL;
    *(s32 *)((u8 *)r + 0x4C) = x;
    *(s32 *)((u8 *)r + 0x5C) = y;
    {
        u16 masked = attr & 0xFFF;
        u8 *p = (u8 *)r + 0x6C;
        *(u16 *)p = masked;
        p += 0x10;
        *(u8 *)p = 1;
    }
    return r;
}
