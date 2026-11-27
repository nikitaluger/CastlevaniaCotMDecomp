void stepDelayTimer(void *, void *);
void startEffectTimer(void *, s32, void *);
void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;
extern u8 gMainWorkspace[];

/* Readable aliases for the game's helpers (preprocessor-only, no code effect). */
#define RunSpriteTimer  stepDelayTimer
#define InitFxRequest   startEffectTimer
#define AdvanceScript   sub_080C31E4

/*
 * Mover script step: run the sprite countdown timer, then when the mover's two
 * completion flags are set in game mode 2, start the effect sequence at
 * 0x0862ED30 and restart the script step.
 */
void sub_0808C460(void *arg0)
{
    u8 *self = arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    void *sprite = *(void **)(self + 0x38);
    u8 *timer = mover + 0x20;

    RunSpriteTimer(timer, sprite);

    if (*(u16 *)(pos + 0x20) == 1 && *(u16 *)(pos + 0x1E) == 1) {
        u8 *state = gMainWorkspace;
        if (*(s32 *)(state + 0x14AC) == 2) {
            InitFxRequest(timer, 0, (void *)0x0862ED30);
            {
                s16 idx = *(s16 *)(self + 0x22);
                self[idx * 2 + 0x19] = 0;
                {
                    void **lit = &gMainObjTimerCallbacks;
                    AdvanceScript(self + 0x18, self + 0x22, *lit);
                }
            }
        }
    }
}
