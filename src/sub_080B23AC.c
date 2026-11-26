void setAnimationFrame(s32, s32, s32, s32);
void sub_080113A8(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Advances the actor's animation and, once its status byte reports completion
 * (bit 1), switches to animation 0x52 with sound 1, clears the script action
 * byte and dispatches the next handler. */
void sub_080B23AC(void *self) {
    s32 animController;
    s32 *handlerTable;
    s32 animState;
    void *work;

    animController = *(s32 *)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    animState = (s32)work + 0x34;
    sub_080113A8(animController, animState);
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        setAnimationFrame(animController, animState, 0x52, 1);
        *(s8 *)((s8 *)((*(s16 *)((u8 *)self + 0x22) * 2) + self) + 0x19) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *handlerTable);
    }
}
