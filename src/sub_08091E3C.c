struct S_02025FF0_ab { u8 _0x000[0x1868]; s32 v1868; u8 _pad[0x1874 - 0x186C]; s32 v1874; };
extern struct S_02025FF0_ab gMainWorkspace;
void *spawnBudgetedEffect(s32, s32);

/* Spawns a type-0x211 object under the global parent and fills its position
 * (+0x4C/+0x5C), a u16 field at +0x74 and three extra parameter fields
 * (+0x7C, +0x8C, +0x9C). */
void *sub_08091E3C(s32 x, s32 y, s32 param2, s32 param3, s32 param4, u16 half) {
    void *obj = spawnBudgetedEffect(gMainWorkspace.v1868, 0x211);
    if (obj == NULL) return NULL;
    *(s32 *)((u8 *)obj + 0x4C) = x;
    *(s32 *)((u8 *)obj + 0x5C) = y;
    {
        u8 *p = (u8 *)obj + 0x74;
        *(u16 *)p = half;
        *(s32 *)((u8 *)obj + 0x7C) = param2;
        p += 0x18;
        *(s32 *)p = param3;
    }
    *(s32 *)((u8 *)obj + 0x9C) = param4;
    return obj;
}

void *sub_080918B0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 a5) {
    void *r = spawnBudgetedEffect(gMainWorkspace.v1868, 0x20F);
    if (r == NULL) return NULL;
    *(s32 *)((u8 *)r + 0x4C) = a0;
    *(s32 *)((u8 *)r + 0x5C) = a1;
    {
        u8 *p = (u8 *)r + 0x74;
        *(u16 *)p = a5;
        *(s32 *)((u8 *)r + 0x7C) = a2;
        p += 0x18;
        *(s32 *)p = a3;
    }
    *(s32 *)((u8 *)r + 0x9C) = a4;
    return r;
}

void *sub_0808E670(s32 a0, s32 a1, s32 a2, s32 a3) {
    void *r = spawnBudgetedEffect(gMainWorkspace.v1874, 0x20C);
    if (r == NULL) return NULL;
    *(s32 *)((u8 *)r + 0x4C) = a0;
    *(s32 *)((u8 *)r + 0x5C) = a1;
    *(s32 *)((u8 *)r + 0x6C) = a2;
    {
        s32 v = a3;
        if (v < 0) v = -v;
        *(s32 *)((u8 *)r + 0x7C) = -v;
    }
    *(u8 *)((u8 *)r + 0x94) = 2;
    return r;
}
