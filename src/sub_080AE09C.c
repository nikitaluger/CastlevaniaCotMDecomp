extern void advanceMotion(s32 pos, s32 gravity);

/* Spin the object's sprite by one 1/32 turn (0x800 in 0x10000-per-turn angle
 * units), then advance the object's position by its velocity with no gravity. */
void sub_080AE09C(void *obj) {
    void *sprite = *(void **)((u8 *)obj + 0x38);
    s32 pos = *(s32 *)((u8 *)obj + 0x3C);
    *(u16 *)((u8 *)sprite + 8) = (u16)(*(u16 *)((u8 *)sprite + 8) + 0x800);
    advanceMotion(pos, 0);
}
