struct S_02025FF0_ab { u8 _0x000[0x1868]; s32 v1868; u8 _pad[0x1874 - 0x186C]; s32 v1874; };
extern struct S_02025FF0_ab D_02025FF0;
void *sub_0805FAEC(s32, s32);

/* Spawns a type-0x20F object under the global parent and fills its position
 * (+0x4C/+0x5C), a u16 field at +0x74 and three extra parameter fields
 * (+0x7C, +0x8C, +0x9C). */
void *sub_080918B0(s32 x, s32 y, s32 param2, s32 param3, s32 param4, u16 half) {
    void *obj = sub_0805FAEC(D_02025FF0.v1868, 0x20F);
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
