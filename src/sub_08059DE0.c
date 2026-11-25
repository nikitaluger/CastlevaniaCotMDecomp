extern void *sub_0805FAEC(s32, s32);
struct S_02025FF0 { u8 pad[0x1874]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

/* Allocate an object at fixed-point world coordinates: store the integer part
 * of each at 0x4C/0x54 and a 16-bit parameter at 0x5C. */
void *sub_08059DE0(s32 x, s32 y, u16 param) {
    void *obj = sub_0805FAEC(D_02025FF0.v, 0x166);
    s32 xHi, yHi;
    s32 xRound, yRound;
    if (obj == NULL)
        return NULL;
    xRound = x;
    if (xRound < 0)
        xRound += 0xFFFF;
    xHi = xRound >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xHi;
    yRound = y;
    if (yRound < 0)
        yRound += 0xFFFF;
    yHi = yRound >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yHi;
    *(u16 *)((u8 *)obj + 0x5C) = param;
    return obj;
}
