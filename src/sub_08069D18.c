/* Per-frame actor update: reset the shared result state, and while the game is
 * in mode 5 clear the current script step's phase byte and advance the script,
 * then run the ordinary actor update. */
void resetActionResultState(void *, s32, s32, s32);
void sub_0806C6B0(void *, s32, s32, s32);
void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

/* The word at 0x14AC selects the current game mode. */
struct GameMode { u8 _0[0x14AC]; u32 mode; };
extern struct GameMode gMainWorkspace;

/* An action-list slot at self + stepIndex*2; 0x19 holds the step's phase byte. */
struct ActionSlot { u8 _0[0x18]; u8 stepId; u8 phase; };

void sub_08069D18(void *arg0)
{
    u8 *self = arg0;
    s32 work = *(s32 *)(self + 0x6C) + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    resetActionResultState(arg0, sprite, work, work);
    if (gMainWorkspace.mode == 5) {
        ((struct ActionSlot *)(self + *(s16 *)(self + 0x22) * 2))->phase = 0;
        {
            void **scriptCb = &gScriptStepCallbackTable;
            u8 *stepBase = self;
            u8 *stepIndex = self;
            stepBase += 0x18;
            stepIndex += 0x22;
            sub_080C31E4(stepBase, stepIndex, *scriptCb);
        }
    }
    sub_0806C6B0(arg0, sprite, work, work);
}
