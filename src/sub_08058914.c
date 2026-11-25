void *sub_0805FAEC(s32, s32);
struct S_02025FF0 { u8 _p[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

/* Allocate an object at fixed-point world coordinates (x, y), storing the
 * integer part of each at 0x4C/0x54 plus two extra 32-bit parameters. */
void *sub_08058914(s32 x, s32 y, s32 param0, s32 param1) {
    void *obj;
    s32 xRound, yRound;
    s32 xHi, yHi;
    obj = sub_0805FAEC(D_02025FF0.v, 0x161);
    if (obj == NULL) return NULL;
    xRound = x;
    if (xRound < 0) xRound += 0xFFFF;
    xHi = xRound >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = xHi;
    yRound = y;
    if (yRound < 0) yRound += 0xFFFF;
    yHi = yRound >> 16;
    *(s16 *)((u8 *)obj + 0x54) = yHi;
    *(u32 *)((u8 *)obj + 0x5C) = param0;
    *(u32 *)((u8 *)obj + 0x6C) = param1;
    return obj;
}
