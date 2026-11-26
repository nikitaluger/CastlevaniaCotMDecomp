struct HeapGlobals { u8 _0[0x1874]; u32 pool; };
extern struct HeapGlobals gMainWorkspace;

extern void *sub_0805FAEC(u32, s32);

/* Allocate a 0x162-byte object from the runtime pool and seed its fields.
 * xFixed/yFixed are 16.16 fixed-point positions, rounded toward +infinity and
 * stored as halfwords at +0x4C/+0x54; the remaining arguments fill +0x5C,
 * +0x6C, +0x7C and +0x84. Returns 0 if the pool cannot supply an object. */
void *sub_08058D60(s32 xFixed, s32 yFixed, s32 value5C, s32 value6C, u16 value7C, u16 value84) {
    void *obj;
    s32 xRounded;
    s32 yRounded;
    s32 xWord, yWord;

    obj = sub_0805FAEC(gMainWorkspace.pool, 0x162);
    if (obj == 0) {
        return 0;
    }

    xRounded = xFixed;
    if (xRounded < 0) {
        xRounded += 0xFFFF;
    }
    xWord = xRounded >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xWord;

    yRounded = yFixed;
    if (yRounded < 0) {
        yRounded += 0xFFFF;
    }
    yWord = yRounded >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yWord;

    *(s32 *)((u8 *)obj + 0x5C) = value5C;
    *(s32 *)((u8 *)obj + 0x6C) = value6C;
    *(u16 *)((u8 *)obj + 0x7C) = value7C;
    *(u16 *)((u8 *)obj + 0x84) = value84;

    return obj;
}
