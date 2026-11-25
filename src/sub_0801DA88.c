s32 sub_08011368(s32 obj, void *anim, s32 frame, s32 mode);
void sub_080C31E0(void *, s32);

/* Start animation frame 0x21 on the entity's sub-object animation state and,
 * when the state's bit 1 is set afterwards, run the entity's +0x24 callback. */
void sub_0801DA88(void *arg0)
{
    s32 obj;
    void *anim;
    u8 *state;

    obj = *(s32 *)((u8 *)arg0 + 0x38);
    anim = *(void **)((u8 *)arg0 + 0x3C);
    state = (u8 *)anim + 0x34;
    sub_08011368(obj, state, 0x21, 0);
    if (2 & *state) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
