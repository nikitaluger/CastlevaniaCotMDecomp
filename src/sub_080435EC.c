struct S_02025FF0 {
    u8 _0x000[0x1870];
    u32 v;
};
extern struct S_02025FF0 D_02025FF0;

void *sub_0805FAEC(u32, s32);

/* Spawn one type-0x113 effect/entity object from the shared pool at a 16.16
 * fixed-point position, then store its three setup parameters. */
void *sub_080435EC(s32 xFixed, s32 yFixed, s32 param5C, s32 param6C, u16 param7C)
{
    void *obj;
    s32 xScaled;
    s32 yScaled;
    s32 x, y;

    obj = sub_0805FAEC(D_02025FF0.v, 0x113);
    if (obj == 0) {
        return 0;
    }

    xScaled = xFixed;
    if (xScaled < 0) {
        xScaled += 0xFFFF;
    }
    x = xScaled >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = x;

    yScaled = yFixed;
    if (yScaled < 0) {
        yScaled += 0xFFFF;
    }
    y = yScaled >> 16;
    *(s16 *)((u8 *)obj + 0x54) = y;

    *(s32 *)((u8 *)obj + 0x5C) = param5C;
    *(s32 *)((u8 *)obj + 0x6C) = param6C;
    *(u16 *)((u8 *)obj + 0x7C) = param7C;

    return obj;
}
