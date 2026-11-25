void sub_080113A8(s32, void *);
void sub_0801165C(void *, s32);
void sub_080146D0(void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* One frame of a travelling object: advance its animation, shorten its step
 * length by 0x1000 (the length used by the polar-move helper), move it, and
 * once the length reaches 0 clear its trail-slot byte and dispatch its
 * per-object handler. */
void sub_080B59C0(void *self) {
    s32 animId = *(s32 *)((u8 *)self + 0x38);
    void *mover = *(void **)((u8 *)self + 0x3C);
    s32 step;
    sub_080113A8(animId, (u8 *)mover + 0x34);
    step = *(s32 *)((u8 *)self + 0x6C) - 0x1000;
    *(s32 *)((u8 *)self + 0x6C) = step;
    if (step <= 0) {
        *(s32 *)((u8 *)self + 0x6C) = 0;
    }
    sub_080146D0(mover, *(s32 *)((u8 *)self + 0x7C), *(s32 *)((u8 *)self + 0x6C));
    sub_0801165C(mover, 0);
    if (*(s32 *)((u8 *)self + 0x6C) == 0) {
        s32 slot = *(s16 *)((u8 *)self + 0x22);
        s32 *handlers;
        *(u8 *)((u8 *)self + slot * 2 + 0x19) = 0;
        handlers = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *handlers);
    }
}
