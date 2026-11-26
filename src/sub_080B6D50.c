extern s32 setAnimationFrame(s32, u8 *, s32, s32);
extern s32 sub_080113A8(s32, u8 *);
extern s32 sub_08011898(u8 *, s32);
extern s32 sub_0809856C(s32, u8 *, s32);
extern s32 sub_080B72CC(u8 *);
extern void sub_080C31E4(void *, void *, s32);

struct ScriptStepObj {
    u8 pad0[0x22];
    s16 stepIndex;
    u8 pad24[0x38 - 0x24];
    u8 *sprite;
    u8 *work;
    u8 pad40[0x74 - 0x40];
    u16 countdown;
    u8 pad76[0x7c - 0x76];
    u8 soundCounter;
};

/* Script-step callback: each tick plays a periodic cue, moves the work object
 * under gravity, advances its animation track and releases any carried object.
 * When the countdown reaches zero it swaps the animator to frame 0x2F, clears
 * the victim and step bytes, and dispatches the next script handler. */
void sub_080B6D50(struct ScriptStepObj *self)
{
    u16 zero;
    u8 *sprite;
    u8 *work;
    u8 *animTrack;
    s32 remaining;
    s32 *handlerTable;

    sprite = self->sprite;
    work = self->work;
    animTrack = work + 0x34;
    sub_0809856C(0x18C, (u8 *)&self->soundCounter, 0x0F);
    sub_08011898(work, 0x4000);
    sub_080113A8(sprite, animTrack);
    sub_080B72CC((u8 *)self);
    remaining = self->countdown;
    remaining = remaining - 1;
    zero = 0;
    self->countdown = remaining;
    if ((remaining << 16) == 0) {
        setAnimationFrame(sprite, animTrack, 0x2F, 0);
        *(u8 *)(*(u8 **)(work + 0x28) + 1) = zero;
        *((u8 *)self + self->stepIndex * 2 + 0x19) = zero;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)&self->stepIndex, *handlerTable);
    }
}
