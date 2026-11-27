extern u32 gMainWorkspace[];
s32 stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Script step: tick the actor's animation timer; when it expires set the
 * global mode word (gMainWorkspace+0x1C) to 2 and advance the script, then keep
 * the sprite locked to the actor's position. */
void sub_080889A4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *actor = *(u8 **)(self + 0x6C);
    u8 *mover = actor + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *handlers;
    s32 timer = stepDelayTimer(actor + 0x20, sprite);
    if (timer == 0) {
        gMainWorkspace[7] = 2;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = timer;
        handlers = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlers);
    }
    sub_0806D588(sprite, mover);
}
