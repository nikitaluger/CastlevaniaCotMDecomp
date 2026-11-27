/* Actor update for game modes 2 and 0: reset the shared result state, run the
 * mode-specific scripted step, then perform the ordinary actor update. */
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gMainObjTimerCallbacks;
extern void *gScriptStepCallbacks;

/* The word at 0x14AC selects the current game mode. */
struct GameState { u8 _0[0x14AC]; u32 mode; };
extern struct GameState gMainWorkspace;

/* An action-list slot at self + stepIndex*2; 0x19 holds the step's phase byte. */
struct ActionSlot { u8 _0[0x18]; u8 stepId; u8 phase; };

struct Actor {
    u8 _0[0x22];
    s16 stepIndex;
    u8 _24[0x14];
    u32 sprite;
    u8 _3C[0x30];
    u32 work;
};

void sub_080699A8(struct Actor *arg0) {
    void *work;
    void *sprite;
    struct GameState *state;
    u32 mode;

    work = (void *)(arg0->work + 4);
    sprite = (void *)arg0->sprite;
    resetActionResultState(arg0, sprite, work, work);
    state = &gMainWorkspace;
    if (state->mode == 2) {
        ((struct ActionSlot *)((u8 *)arg0 + arg0->stepIndex * 2))->phase = 0;
        {
            void **fn = &gMainObjTimerCallbacks;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *fn);
        }
    }
    mode = state->mode;
    if (mode == 0) {
        ((struct ActionSlot *)((u8 *)arg0 + arg0->stepIndex * 2))->phase = mode;
        {
            void **fn = &gScriptStepCallbacks;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 6, *fn);
        }
    }
    sub_0806C6B0(arg0, sprite, work, work);
}
