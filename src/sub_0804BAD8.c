void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Enemy AI script step: set animation frame 0x1F on the sprite and tick the
 * u16 move timer at work+0x48; when that timer underflows or the mover flag at
 * work+0x28 -> +0x14 is set, clear the script action byte and advance the script. */
void sub_0804BAD8(void *self) {
    void *sprite;
    void *work;
    u8 *animState;
    u8 *moveTimer;
    s32 timeLeft;
    u32 *scriptTable;
    sprite = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    animState = (u8 *)work + 0x34;
    moveTimer = (u8 *)work + 0x48;
    setAnimationFrame(sprite, animState, 0x1F, 1);
    timeLeft = *(u16 *)moveTimer - 1;
    *(u16 *)moveTimer = timeLeft;
    if (((timeLeft << 16) < 0) || (1 & *(u16 *)((u8 *)*(void **)((u8 *)work + 0x28) + 0x14))) {
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = 0;
        scriptTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptTable);
    }
}
