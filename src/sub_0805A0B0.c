struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern void *sub_0805FAEC(u32, s32);

/* Spawn one type-0x167 effect/entity object from the shared pool at a 16.16
 * fixed-point position, then store its three setup parameters. */
void *sub_0805A0B0(s32 xFixed, s32 yFixed, s32 param7C, s32 param8C, u16 param74) {
    void *obj;
    s32 xScaled, yScaled;
    s32 x, y;
    obj = sub_0805FAEC(gMainWorkspace.v, 0x167);
    if (obj == 0) return 0;
    xScaled = xFixed;
    if (xScaled < 0) xScaled += 0xFFFF;
    x = xScaled >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = x;
    yScaled = yFixed;
    if (yScaled < 0) yScaled += 0xFFFF;
    y = yScaled >> 16;
    *(s16 *)((u8 *)obj + 0x54) = y;
    *(s32 *)((u8 *)obj + 0x7C) = param7C;
    *(s32 *)((u8 *)obj + 0x8C) = param8C;
    *(u16 *)((u8 *)obj + 0x74) = param74;
    return obj;
}
