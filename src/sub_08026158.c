void sub_08026954(void *, void *);
void sub_080269A8(void *, u16);
void sub_080C31E4(void *, void *, s32);

struct AnimState {
    u8 _0[0x1C];
    u16 delay;                  /* 0x1C: frames left before the script advances */
};

/* When the animation state's counter is non-zero, finish the current script
 * step: sync the two sub-objects, restart the delay at 360 frames, clear the
 * level's repeat counter and advance the script by one instruction. */
void sub_08026158(void *arg0) {
    void *anim;
    struct AnimState *state;
    u32 *scriptTable;
    u8 zero;
    anim = *(void **)((u8 *)arg0 + 0x3C);
    state = (struct AnimState *)((u8 *)anim + 0x48);
    if (*(s16 *)state != 0) {
        sub_08026954((u8 *)anim + 0x50, (u8 *)anim + 0x54);
        zero = 0;
        state->delay = 0x168;
        sub_080269A8(arg0, 0x22);
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = zero;
        scriptTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
