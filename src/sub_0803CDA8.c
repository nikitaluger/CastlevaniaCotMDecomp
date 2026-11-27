s32 setAnimationFrame(s32, s32, s32, s32);
s32 stepAnimationTrack(s32, s32);
s32 sub_080148D8(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Script step: refresh the sprite's facing flag and animation from the work
 * object; when the animator's done bit is set, switch to frame 0xC, clear this
 * step's action byte and advance the script. */
void sub_0803CDA8(void *self) {
    s32 animator;
    void *work;
    s32 sprite;
    s8 *workBytes;
    s32 *advanceCmd;
    void *body;
    sprite = *((s32 *)(((s8 *)self) + 0x38));
    work = *((void **)(((s8 *)self) + 0x3C));
    body = work;
    animator = (s32)body + 0x34;
    sub_080148D8(sprite, *((s32 *)(((s8 *)body) + 8)));
    workBytes = (s8 *)body;
    stepAnimationTrack(sprite, animator);
    if (2 & (*((u8 *)(workBytes + 0x34)))) {
        setAnimationFrame(sprite, animator, 0xC, 0);
        *(((s8 *)(((*((s16 *)(((s8 *)self) + 0x22))) * 2) + self)) + 0x19) = 0;
        advanceCmd = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *advanceCmd);
    }
}
