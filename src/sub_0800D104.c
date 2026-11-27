struct S_020278D0 { u8 _pad[0x65]; u8 v; };
extern struct S_020278D0 gMenuState;
extern u32 D_0866CF0C[];
extern u32 gScriptStepCallbacks;

void sub_080C31E0(void *a, void *fp);
void sub_080C31E8(void *a, void *b, s32 c, void *fp);

/* Runs the current game mode's handler, then clears the active script step's
 * action byte, advances the script through its runner callback and dispatches
 * the next state handler selected by the step's action byte. */
void sub_0800D104(u8 *self)
{
    u8 modeIndex;
    u8 *stepPtr;
    u32 *modeHandlers = D_0866CF0C;
    u32 *scriptCb;

    modeIndex = gMenuState.v;
    sub_080C31E0(self, (void *)modeHandlers[modeIndex]);

    {
        s16 stepIndex = *(s16 *)(self + 0x22);
        *(self + stepIndex * 2 + 0x19) = 0;
    }

    scriptCb = &gScriptStepCallbacks;
    stepPtr = self + 0x18;
    {
        void *stepIndexPtr = self + 0x22;
        void *runStep = (void *)*scriptCb;
        sub_080C31E8(stepPtr, stepIndexPtr, 4, runStep);
    }

    {
        s16 stepIndex = *(s16 *)(self + 0x22);
        self[stepIndex * 2 + 0x19] = self[stepIndex * 2 + 0x19] + 1;
    }

    {
        s16 stepIndex = *(s16 *)(self + 0x22);
        u8 action;
        stepPtr = stepPtr + stepIndex * 2;
        action = *stepPtr;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + action * 4));
    }
}
