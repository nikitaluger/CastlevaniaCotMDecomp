extern void sub_0806D6B4(void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Move the object with collision; when it reaches the left edge of the room
 * (x <= 128 pixels) stop it, set its landing pose (0x40) and start the landing
 * sub-script on the given frame data and advance the outer script. Finally step
 * the sub-script and update the sprite's screen position from the mover. */
void sub_08088E28(void *entity) {
    u8 *self;
    u8 *mover;
    u8 *pos;
    void *sprite;
    s32 *scriptTable;
    self = (u8 *)entity;
    mover = *(u8 **)(self + 0x6C);
    pos = mover + 4;
    sprite = *(void **)(self + 0x38);
    sub_0806D6B4(pos);
    if (*(s32 *)(mover + 4) <= 0x800000) {
        sub_08003A6C(mover + 0x20, 0, (void *)0x085096BC);
        *(s32 *)(pos + 8) = 0;
        *(s32 *)(pos + 0xC) = 0;
        *(s32 *)(pos + 0x10) = 0x40;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
    sub_08003740(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
