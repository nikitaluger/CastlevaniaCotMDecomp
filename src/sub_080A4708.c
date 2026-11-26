extern void sub_08005E80(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Actor step: advance a saturating frame counter on the sprite; once it passes
 * 0xFF, clamp it, free resource 0x174, start animation 0x23 on the animator,
 * set the work flag, clear the script step and dispatch the handler. */
void sub_080A4708(void *actor) {
    void *self;
    void *sprite;
    void *work;
    void *anim;
    int counter;
    s16 idx;
    s32 *handlerTable;

    self = actor;
    sprite = *((void **)((s8 *)self + 0x38));
    work = *((void **)((s8 *)self + 0x3C));
    anim = work + 0x34;

    counter = *((u16 *)((s8 *)sprite + 4)) + 8;
    *((u16 *)((s8 *)sprite + 4)) = counter;
    *((u16 *)((s8 *)sprite + 6)) = counter;
    if ((s16)counter > 0xFF) {
        counter = 0x100;
        *((u16 *)((s8 *)sprite + 4)) = counter;
        *((u16 *)((s8 *)sprite + 6)) = counter;
        sub_08005E80(counter + 0x74);
        setAnimationFrame(sprite, anim, 0x23, 1);
        *((u8 *)((s8 *)*((void **)((s8 *)work + 0x28)) + 1)) = 1;
        idx = *((s16 *)((s8 *)self + 0x22));
        *((u8 *)((s8 *)self + idx * 2 + 0x19)) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)self + 0x18, (s8 *)self + 0x22, *handlerTable);
    }
}
