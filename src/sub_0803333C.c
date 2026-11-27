void sub_0803B194(void *);
void stepAnimationTrack(void *, void *);
void sub_08011344(void *, void *, s32, s32);
void sub_0803B140(s32, void *, void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Enemy-AI update: refresh three sub-object states, advance the animation, and
 * on the animation's turn frame set a facing-dependent horizontal speed, reset
 * the movement timer and advance the script step; then set up movement graphics. */
void sub_0803333C(void *self)
{
    void *sprite = *(void **)((u8 *)self + 0x38);
    void *work = *(void **)((u8 *)self + 0x3C);
    void *animState = (u8 *)work + 0x34;
    void *moveState = (u8 *)work + 0x48;

    sub_0803B194((u8 *)work + 0x54);
    stepAnimationTrack(sprite, animState);
    if (*(u8 *)animState & 2) {
        if (*(u16 *)((u8 *)sprite + 2) & 0x10)
            *(s32 *)((u8 *)work + 0x10) = 0x40000;
        else
            *(s32 *)((u8 *)work + 0x10) = (s32)0xFFFC0000;
        sub_08011344(sprite, animState, 0xF, 0);
        *(u8 *)((u8 *)moveState + 0x18) = 0;
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *scriptCb = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptCb);
        }
    }
    sub_0803B140(7, sprite, (u8 *)moveState + 0xC, 0x080CED6E);
}
