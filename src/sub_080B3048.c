void *sub_0805FAEC(void *, s32);
struct S_02025FF0_1870 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0_1870 D_02025FF0;

/* Spawn a type-0x1BA effect object and store its position (x, y) plus the
 * given angle/parameter. */
void sub_080B3048(s32 x, s32 y, u16 angle) {
    void *obj = sub_0805FAEC((void *)D_02025FF0.p, 0xDD << 1);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(u32 *)((u8 *)obj + 0x6C) = angle;
    }
}
