extern u8 gMainWorkspace[];

extern s32 stepDelayTimer(void *, void *);
extern s32 checkGlobalStateChange(void *, void *, void *);
extern void setSpriteScreenPosition(void *, void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);

/* Shrink the target sprite, ease the effect toward its source a twentieth at a
 * time, refresh its screen position, and advance the script step when the
 * animation ends or the source no longer matches. */
void updateScaledMainObjectEffect(void *arg0) {
    struct ScaledFxHeader *stateHeader = *(void **)((u8 *)arg0 + 0x6C);
    struct ScaledFxState *state = (u8 *)stateHeader + 4;
    struct ScaledFxTarget *target = *(void **)((u8 *)arg0 + 0x38);
    struct ScaledFxSource *source;
    s32 goal, value;
    s32 zero;
    s32 *stepCallbacks;
    s32 *timerCallbacks;

    if (checkGlobalStateChange(arg0, target, state) != 0) {
        return;
    }

    {
        s32 v = target->scaleX - 0x10;
        zero = 0;
        target->scaleX = v;
    }
    target->scaleY -= 0x10;
    stepDelayTimer((u8 *)stateHeader + 0x20, target);
    source = *(void **)((u8 *)state + 0x4C);

    if (source->kind != stateHeader->kind) {
        ((u8 *)state->gfx)[1] = zero;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        stepCallbacks = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
        _call_via_r3((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 4, *stepCallbacks);
        return;
    }

    goal = source->goalX;
    value = stateHeader->copy0;
    value = value + divInt32(goal - value, 0x14);
    stateHeader->copy0 = value;
    goal = source->goalY;
    value = state->copy1;
    value = value + divInt32(goal - value, 0x14);
    state->copy1 = value;

    setSpriteScreenPosition(target, state);

    if (*(s16 *)((u8 *)target + 4) == 0x100) {
        ((u8 *)state->gfx)[1] = (u8)(gMainWorkspace[GWS_PARITY_FIELD] & 1);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        timerCallbacks = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *timerCallbacks);
    }

    if (gMainWorkspace[GWS_SCREEN_MODE_FIELD] == 0x1C ||
        (gMainWorkspace[GWS_TIMER_FIELD] == 0 && *(u32 *)(gMainWorkspace + 0x10) != 0)) {
        _call_via_r1(arg0, *(void **)((u8 *)arg0 + 0x24));
    }
}
