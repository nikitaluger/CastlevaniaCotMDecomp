extern vu32 gMainWorkspace;
extern vu32 gScriptStepCallbackTable;

void *spawnBudgetedEffect(s32, s32);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    u32 unk_0x3C;
};

struct ResultObj {
    u8 pad_0x00[0x4C];
    s16 unk_0x4C;
    u8 pad_0x4E[0x54 - 0x4E];
    s16 unk_0x54;
};

/* Allocate a type-0x89 result object owned by the current world state and set
 * its two screen coordinates from 16.16 fixed-point arguments (negatives are
 * rounded up by 0xFFFF before the >>16). */
void *ResultObj_New(s32 arg0, s32 arg1) {
    s32 x16;
    s32 y16;
    void *result;
    u8 *worldState;

    worldState = (u8 *)&gMainWorkspace;
    result = spawnBudgetedEffect(*(vu32 *)(worldState + 0x1870), 0x89);
    if (result == NULL) {
        return NULL;
    }
    x16 = arg0;
    if (x16 < 0) {
        x16 += 0xFFFF;
    }
    ((struct ResultObj *)result)->unk_0x4C = (s16)(x16 >> 16);
    y16 = arg1;
    if (y16 < 0) {
        y16 += 0xFFFF;
    }
    ((struct ResultObj *)result)->unk_0x54 = (s16)(y16 >> 16);
    return result;
}

/* Play animation 0x2B on the actor and, once the current script step has run
 * for more than 30 ticks, clear its progress byte and advance the step. */
void sub_08019170(struct MainObj *arg0) {
    u8 *stepState;
    s16 step;
    u32 stepFn;

    setAnimationFrame(arg0->unk_0x38, (u8 *)arg0->unk_0x3C + 0x34, 0x2B, 1);
    step = arg0->unk_0x22;
    stepState = (u8 *)((step << 1) + (u32)arg0);
    if (stepState[0x19] > 0x1E) {
        stepState[0x19] = 0;
        stepFn = gScriptStepCallbackTable;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, stepFn);
    }
}
