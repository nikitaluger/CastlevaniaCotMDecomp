/* Runs one step of an actor's action: resolves the actor's world position, resets result
 * flags, chooses an animation sequence from the scenario/story flags, starts that timer and
 * advances the action state. Failed or cancelled steps clear the current script slot and
 * dispatch a step callback; success continues with the facing-dependent update. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern s32 sub_0806865C(void *, void *, void *, void *);
extern u32 sub_08068704(void *, void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void resetActorForm(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);

extern struct ActionWorkspace gMainWorkspace;
extern struct ActionCameraState gCameraState;
extern u8 gGameStatus[];
extern void *gScriptStepCallbacks;

void runActionStep(struct ActionActor *actor) {
    struct ActionWorkState *stateAlias;
    struct ActionWorkState *state;
    s32 contextHandle;
    u8 *flagTable;
    u8 *sequenceTimer;
    s32 scenarioChoice;
    s32 facing;
    u8 *timerWork;

    state = (struct ActionWorkState *)((u8 *)actor->extra + 4);
    contextHandle = actor->context;
    stateAlias = state;
    flagTable = gGameStatus;
    if (syncViewPosition(stateAlias, stateAlias) != 0) return;
    resetActionResultState(actor, (void *)contextHandle, stateAlias, stateAlias);
    if (gMainWorkspace.modeFlags != 0) {
        if ((gMainWorkspace.modeMask & *(u16 *)(flagTable + ACTION_STATE_FLAG_OFFSET)) != 0) goto block8;
        goto block9;
    } else {
        if ((gCameraState.faceFlags & *(u16 *)(flagTable + ACTION_STATE_FLAG_OFFSET)) == 0) goto block9;
    }
block8:
    timerWork = (u8 *)state + 0x28;
    startEffectTimer(timerWork, 0, (void *)ACTION_ANIM_CANCEL);
    stateAlias->stateA = 0;
    state->flagsB8 = 0;
    *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
    { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_STEP_CANCEL, *(void **)fn); }
    sequenceTimer = timerWork;
    goto tail;
block9:
    scenarioChoice = sub_0806865C(actor, (void *)contextHandle, state, stateAlias);
    sequenceTimer = (u8 *)state + 0x28;
    if (scenarioChoice != 0) goto tail;
    facing = sub_08068704((void *)contextHandle, state, stateAlias);
    if (facing == 0) {
        startEffectTimer(sequenceTimer, 0, (void *)ACTION_ANIM_NO_DIR);
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_STEP_NO_DIR, *(void **)fn); }
    } else {
        state->actionFlags |= 0x0C;
    }
tail:
    D_0806AB04(actor, (void *)contextHandle, state, stateAlias);
    if (state->activeA == 0 && state->activeC == 0) {
        startEffectTimer(sequenceTimer, 0, (void *)ACTION_ANIM_FAIL);
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_STEP_FAIL, *(void **)fn); }
    }
    sub_0806A884((void *)contextHandle, stateAlias);
    state->resultCode = sub_0806BCD8(actor, (void *)contextHandle, state, stateAlias);
    if (state->resultCode != 0) {
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, state->resultCode, *(void **)fn); }
    }
    if (gMainWorkspace.actionState == 0) {
        if (actor->kind == ACTION_KIND_RESET) {
            resetActorForm((void *)contextHandle, state);
            *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
            { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_STEP_RESET, *(void **)fn); }
        }
    }
    stepDelayTimer(sequenceTimer, (void *)contextHandle);
    sub_0806C6B0(actor, (void *)contextHandle, state, stateAlias);
}
