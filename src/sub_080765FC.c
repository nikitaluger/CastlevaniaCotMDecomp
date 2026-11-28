extern s32 stepDelayTimer(void *, void *);
extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);

struct S_765FC {
    u8 _pad0[0x10];
    u32 field10;
    u8 _pad1[0x14ED - 0x14];
    u8 byte14ED;
    u8 _pad2[0x173A - 0x14EE];
    u8 byte173A;
    u8 _pad3[0x174C - 0x173B];
    s32 word174C;
    s32 word1750;
    u8 _pad4[0x18C2 - 0x1754];
    u16 word18C2;
};
extern struct S_765FC gMainWorkspace;

/* Copy the global player/view coordinates into the entity's control object,
 * run its reposition action, and tick a timer; fire the script callback when
 * the timer expires or a game-mode condition holds. */
void sub_080765FC(void *arg0) {
    void *ctrl;
    void *pos;
    void *mainObj;
    struct S_765FC *state;

    ctrl = *(void **)((u8 *)arg0 + 0x6C);
    pos = (u8 *)ctrl + 4;
    mainObj = *(void **)((u8 *)arg0 + 0x38);
    if (applyAreaSpecialBehavior(arg0, mainObj, pos) != 0)
        return;
    state = &gMainWorkspace;
    *(s32 *)((u8 *)ctrl + 4) = state->word174C;
    *(s32 *)((u8 *)pos + 4) = state->word1750;
    sub_0806D588(mainObj, pos);
    *(u16 *)mainObj = state->word18C2;
    if (stepDelayTimer((u8 *)ctrl + 0x20, mainObj) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    if (state->byte173A == 0x1C || (state->byte14ED == 0 && state->field10 != 0))
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
}
