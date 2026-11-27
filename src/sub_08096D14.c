s64 sub_08096F00(void *);
void setObjectAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* When the player is out of range (sub_08096F00 returns 0), switch the
 * entity's animation/rotation state to 7, mark it as engaged and hand
 * control to the next script handler. */
void sub_08096D14(void *self) {
    void *animator;
    u8 *work;
    u8 *animState;
    u32 *handlerTable;
    u32 zero;

    animator = *(void **)((u8 *)self + 0x38);
    work = *(u8 **)((u8 *)self + 0x3C);
    animState = work + 0x18;
    if ((s32)sub_08096F00(self) != 0) return;
    setObjectAnimationFrame(animator, animState, 7, 0);
    zero = 0;
    *(u16 *)(work + 0x16) = 1;
    *(u8 *)(*(u8 **)(work + 4) + 1) = 7;
    *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = zero;
    handlerTable = (u32 *)0x08671BB0;
    sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *handlerTable);
}
