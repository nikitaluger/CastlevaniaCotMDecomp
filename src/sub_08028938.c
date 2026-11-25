struct S_02025FF0 { u8 _0x000[0x1870]; u32 parent; };
extern struct S_02025FF0 D_02025FF0;

void *sub_0805FAEC(u32, s32);

/* Spawn a type-0xB5 child of the object stored in D_02025FF0, then seed it from
 * a 16.16-fixed-point position (rounded toward zero) and five caller values.
 * Returns NULL when no object slot is free. */
void *sub_08028938(s32 x, s32 y, u16 param0, u16 param1, s32 param2, u16 param3, u16 param4)
{
    void *obj;
    s32 xFixed, yFixed;
    s32 xPos, yPos;

    obj = sub_0805FAEC(D_02025FF0.parent, 0xB5);
    if (obj == 0) return 0;

    xFixed = x;
    if (xFixed < 0) xFixed += 0xFFFF;
    xPos = xFixed >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xPos;

    yFixed = y;
    if (yFixed < 0) yFixed += 0xFFFF;
    yPos = yFixed >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yPos;

    *(u16 *)((u8 *)obj + 0x5C) = param0;
    *(u16 *)((u8 *)obj + 0x64) = param1;
    *(s32 *)((u8 *)obj + 0x6C) = param2;
    *(u16 *)((u8 *)obj + 0x7C) = param3;
    *(u16 *)((u8 *)obj + 0x8C) = param4;

    return obj;
}
