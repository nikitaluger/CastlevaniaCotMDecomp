struct S_02025FF0_1874 { u8 _0[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;
extern void *sub_0805FAEC(s32, s32);

/* Spawn an effect object at fixed-point world coordinates: allocate it, store
 * the integer part of each coordinate (0x4C/0x54) and a variant id (0x74). */
void *sub_08023F34(s32 x, s32 y, u16 variant) {
    void *effect;
    s32 xRound, yRound, xHi, yHi;
    effect = sub_0805FAEC(D_02025FF0.v, 0xA3);
    if (effect == NULL) return NULL;
    xRound = x;
    if (xRound < 0) xRound += 0xFFFF;
    xHi = xRound >> 16;
    *(s16 *)((u8 *)effect + 0x4C) = (s16)xHi;
    yRound = y;
    if (yRound < 0) yRound += 0xFFFF;
    yHi = yRound >> 16;
    *(s16 *)((u8 *)effect + 0x54) = (s16)yHi;
    *(u16 *)((u8 *)effect + 0x74) = variant;
    return effect;
}
