extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script step: decrements the companion's timer; while it is still positive
 * clears two linked flags, and on expiry flags the sprite, changes its pose
 * and advances the script interpreter. */
void sub_08023AD4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    void *companion = *(void **)(self + 0x3C);
    void *poseObj = (u8 *)companion + 0x34;
    void *timerState = (u8 *)companion + 0x48;
    s32 timer = *(u16 *)((u8 *)timerState + 2);
    timer--;
    {
        u8 zero = 0;
        *(u16 *)((u8 *)timerState + 2) = timer;
        if (timer << 16 > 0) {
            *(u8 *)(*(u8 **)((u8 *)companion + 0x28) + 1) = zero;
            *(u8 *)(*(u8 **)((u8 *)timerState + 4) + 1) = zero;
        } else {
            u8 *spriteFlag = (u8 *)sprite + 0x2A;
            u8 flagValue = *spriteFlag | 0x40;
            *spriteFlag = flagValue;
            setAnimationFrame(sprite, poseObj, 0x1A, 0);
            *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = zero;
            {
                s32 *interpreter = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *interpreter);
            }
        }
    }
}
