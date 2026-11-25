extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_0809856C(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Actor step: cycle a work counter (freeing resource 0x17A on wrap), then
 * advance a saturating sprite frame counter; once it passes 0xFF, clamp it,
 * start animation 0x47 on the animator, clear the script step and dispatch. */
void sub_080AE36C(void *actor) {
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

    sub_0809856C(0xBD << 1, (s8 *)work + 0x50, 0x0F);
    counter = *((u16 *)((s8 *)sprite + 4)) + 0x0C;
    *((u16 *)((s8 *)sprite + 4)) = counter;
    *((u16 *)((s8 *)sprite + 6)) = counter;
    if ((s16)counter > 0xFF) {
        counter = 0x100;
        *((u16 *)((s8 *)sprite + 4)) = counter;
        *((u16 *)((s8 *)sprite + 6)) = counter;
        sub_080114DC(sprite, anim, 0x47, 0);
        idx = *((s16 *)((s8 *)self + 0x22));
        *((u8 *)((s8 *)self + idx * 2 + 0x19)) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)self + 0x18, (s8 *)self + 0x22, *handlerTable);
    }
}
