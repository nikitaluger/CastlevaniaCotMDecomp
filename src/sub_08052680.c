void sub_080113A8(void *, void *);
void sub_08011368(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Arms a hit reaction on the target once its hitbox reports contact: shows the
 * hit effect, resets the animation frame and runs the frame setup routine. */
void sub_08052680(void *self) {
    void *view;
    void *target;
    u8 *hitbox;
    u32 *frameRoutine;
    u8 zero;
    u8 *victim;
    view = *(void **)((u8 *)self + 0x38);
    target = *(void **)((u8 *)self + 0x3C);
    hitbox = (u8 *)target + 0x34;
    sub_080113A8(view, hitbox);
    if (2 & *hitbox) {
        sub_08011368(view, hitbox, 3, 0);
        victim = *(u8 **)((u8 *)target + 0x28);
        zero = 0;
        *(victim + 2) = 8;
        *((u8 *)*(void **)((u8 *)target + 0x28) + 3) = 1;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = zero;
        frameRoutine = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *frameRoutine);
    }
}
