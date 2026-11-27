/* Runs one step of an actor's alternate action: resolves the actor's world position, resets
 * result flags, chooses an animation sequence from the scenario/story flags, starts that timer
 * and advances the action state. The cancel path selects a directional animation; a failed step
 * marks the secondary state active and dispatches a step callback. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806926C(void *);
extern s32 sub_080693E0(void *, void *, void *, void *);
extern s32 sub_080694D8(void *, void *, void *);
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

void runActionStepAlt(struct ActionActor *actor) {
    struct ActionWorkState *stateAlias;
    struct ActionWorkState *state;
    s32 contextHandle;
    u8 *flagTable;
    u8 *sequenceTimer;
    s32 scenarioChoice;
    s32 facing;

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
    sub_0806926C(state);
    stateAlias->stateA = 0;
    state->flagsB8 = 0;
    *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
    { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_ALT_STEP_CANCEL, *(void **)fn); }
    sequenceTimer = (u8 *)state + 0x28;
    goto tail;
block9:
    scenarioChoice = sub_080693E0(actor, (void *)contextHandle, state, stateAlias);
    sequenceTimer = (u8 *)state + 0x28;
    if (scenarioChoice != 0) goto tail;
    facing = sub_080694D8((void *)contextHandle, state, stateAlias);
    if (facing == 0) {
        startEffectTimer(sequenceTimer, 0, (void *)ACTION_ALT_ANIM_NO_DIR);
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_ALT_STEP_NO_DIR, *(void **)fn); }
    } else {
        state->actionFlags |= 0x0C;
    }
tail:
    D_0806AB04(actor, (void *)contextHandle, state, stateAlias);
    if (state->activeA == 0 && state->activeC == 0) {
        state->activeC = 1;
        startEffectTimer(sequenceTimer, 0, (void *)ACTION_ALT_ANIM_FAIL);
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_ALT_STEP_FAIL, *(void **)fn); }
    }
    sub_0806A884((void *)contextHandle, stateAlias);
    state->resultCode = sub_0806BCD8(actor, (void *)contextHandle, state, stateAlias);
    if (state->resultCode != 0) {
        *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, state->resultCode, *(void **)fn); }
    }
    if (gMainWorkspace.actionState == 0) {
        if (actor->kind == ACTION_ALT_KIND_RESET) {
            resetActorForm((void *)contextHandle, state);
            *(u8 *)((u32)actor->stateIndex * 2 + (u32)actor + 0x19) = 0;
            { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, ACTION_STEP_RESET, *(void **)fn); }
        }
    }
    stepDelayTimer(sequenceTimer, (void *)contextHandle);
    sub_0806C6B0(actor, (void *)contextHandle, state, stateAlias);
}
