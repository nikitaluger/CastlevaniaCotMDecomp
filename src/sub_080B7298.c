void *sub_0805FAEC(s32, s32);

struct S_02025FF0_1870 {
    u8 _0[0x1870];
    u32 v;
};
extern struct S_02025FF0_1870 D_02025FF0;

/* Spawn a type-0x1C5 effect object at the position stored in the parent's
 * state record (+8 = x, +0xC = y). */
void sub_080B7298(void *parent) {
    void *state = *(void **)((u8 *)parent + 0x3C);
    void *child = sub_0805FAEC(D_02025FF0.v, 0x1C5);
    if (child != 0) {
        *(s32 *)((u8 *)child + 0x4C) = *(s32 *)((u8 *)state + 8);
        *(s32 *)((u8 *)child + 0x5C) = *(s32 *)((u8 *)state + 0xC);
    }
}
