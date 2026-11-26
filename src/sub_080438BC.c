extern void *sub_0805FAEC(s32, s32);
struct S_02025FF0 { u8 pad[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

/* Spawn a 0x114-byte object at the given 16.16 fixed-point x/y position, with
 * two extra u16 parameters stored at +0x5C and +0x64. NULL if allocation fails. */
void *sub_080438BC(s32 arg0, s32 arg1, u16 arg2, u16 arg3) {
    void *obj;
    s32 x, y;
    s32 fx, fy;
    u8 *fieldBase;
    u16 *fieldPtr;

    obj = sub_0805FAEC(gMainWorkspace.v, 0x114);
    if (obj == NULL)
        return NULL;
    fx = arg0;
    if (fx < 0)
        fx += 0xFFFF;
    x = fx >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = x;
    fy = arg1;
    if (fy < 0)
        fy += 0xFFFF;
    y = fy >> 16;
    fieldBase = (u8 *)obj + 0x54;
    *(s16 *)fieldBase = y;
    fieldPtr = (u16 *)(fieldBase + 8);
    *fieldPtr = arg2;
    fieldPtr += 8;
    *fieldPtr = arg3;
    return obj;
}
