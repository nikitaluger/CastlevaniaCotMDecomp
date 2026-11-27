void setSpriteFacingToTarget(void *, void *);
void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Enemy script step: refresh the sprite's state flag from the work object, then
 * when the current action byte is 0xF play animation frame 9, clear that action
 * byte and advance to the next script step. */
void sub_08044A6C(void *self) {
    void *sprite;
    void *work;
    u8 *animator;
    u32 *scriptHandlers;
    sprite = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    animator = (u8 *)work + 0x34;
    setSpriteFacingToTarget(sprite, *(void **)((u8 *)work + 8));
    if (*(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) == 0xF) {
        setAnimationFrame(sprite, animator, 9, 0);
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = 0;
        scriptHandlers = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptHandlers);
    }
}
