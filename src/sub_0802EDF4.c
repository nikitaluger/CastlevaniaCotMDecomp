extern s32 sub_08011408(s32, void *, s32, s32, s32);
extern s32 sub_0802F89C(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
void sub_0802F238(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    u8 *effect = work + 0x48;
    s32 ticks;
    s32 *scriptTable;
    u32 zeroWord;
    zeroWord = 0;
    *(s32 *)(work + 0x48) = zeroWord;
    sub_08011408(sprite, animator, 0, 0, 1);
    ticks = *(u16 *)(effect + 8);
    ticks = ticks + 1;
    *(u16 *)(effect + 8) = ticks;
    if ((s16)ticks > 0x4F) {
        u8 zeroByte;
        sub_0802F89C(*(s32 *)(work + 8), *(s32 *)(work + 0xC));
        zeroByte = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zeroByte;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}

extern void *sub_0805FAEC(s32, s32);
struct S_02025FF0_1874 { u8 _0[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;

/* Allocate a type-0xD1 effect object owned by the current world state and set
 * its two screen coordinates from 16.16 fixed-point arguments (negatives are
 * rounded up by 0xFFFF before the >>16). */
void *sub_0802EDF4(s32 arg0, s32 arg1) {
    void *effect;
    s32 x16, y16, coord;
    effect = sub_0805FAEC(D_02025FF0.v, 0xD1);
    if (effect == NULL) return NULL;
    x16 = arg0;
    if (x16 < 0) x16 += 0xFFFF;
    coord = x16 >> 16;
    *(s16 *)((u8 *)effect + 0x4C) = (s16)coord;
    y16 = arg1;
    if (y16 < 0) y16 += 0xFFFF;
    coord = y16 >> 16;
    *(s16 *)((u8 *)effect + 0x54) = (s16)coord;
    return effect;
}
