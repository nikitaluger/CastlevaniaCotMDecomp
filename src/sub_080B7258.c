void sub_080113A8(s32, void *);
void sub_080148D8(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);
void *sub_0805FAEC(s32, s32);
extern u8 D_02025FF0[];

/* Play the effect's animation, face it toward the shared target X, and when the
 * screen flag at D_02025FF0+0x3C is set, restart the script step/interpreter. */
void sub_080B7A90(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    sub_080113A8(sprite, (u8 *)work + 0x34);
    sub_080148D8(sprite, *(s32 *)((u8 *)work + 8));
    if (*(u16 *)(D_02025FF0 + 0x3C) != 0) {
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *(s32 *)0x08671BD0);
    }
}

/* Spawn a type-0x1C3 object under the entity and clear its state byte. */
void *sub_080B7258(s32 parent) {
    void *obj = sub_0805FAEC(parent, 0x1C3);
    if (obj == 0) {
        return 0;
    }
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}
