struct S_02025FF0_1870 {
    u8 _0x000[0x1870];
    u32 parent;
};
extern struct S_02025FF0_1870 gMainWorkspace;

void *sub_0805FAEC(u32, s32);

/* Spawn a 0x104-byte pooled object at a 16.16 fixed-point position, storing an
 * owner value at 0x8C and a u16 setup parameter at 0x64. */
void *sub_0803F758(s32 owner, s32 xFixed, s32 yFixed, u16 param64)
{
    void *obj;
    s32 xScaled;
    s32 yScaled;
    s32 pos;

    obj = sub_0805FAEC(gMainWorkspace.parent, 0x104);
    if (obj == 0) {
        return 0;
    }

    xScaled = xFixed;
    if (xScaled < 0) {
        xScaled += 0xFFFF;
    }
    pos = xScaled >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = pos;

    yScaled = yFixed;
    if (yScaled < 0) {
        yScaled += 0xFFFF;
    }
    pos = yScaled >> 16;
    *(s16 *)((u8 *)obj + 0x54) = pos;

    *(s16 *)((u8 *)obj + 0x5C) = 0;
    *(u16 *)((u8 *)obj + 0x64) = param64;
    *(u32 *)((u8 *)obj + 0x8C) = owner;

    return obj;
}
