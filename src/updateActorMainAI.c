/* Main AI update for this actor: skip while a camera-controlled mode is active,
 * run the per-frame AI helpers, drive scripted animations/effects for special
 * states, then hand off to the final AI pass. */
struct Actor {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 animIndex; u8 _24[0x14];
    u32 refPtr; u8 _3C[0x30]; u32 aiPtr;
};
struct AIWork { u8 _0[0xD0]; u16 fD0; u16 fD2; };
struct AIState {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 mode;
    u8 _2E[0x12]; u32 idleTimer; u8 _44[8]; u32 flag4C;
    u8 _50[0x68]; u32 flagB8; u8 _BC[8]; u32 aiResult;
};
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern s32 scaleByRandom(s32);
extern void sub_08005E80(s32);
extern void spawnEntity(void *, s32, s32, s32);
extern void *gScriptStepCallbacks;
/* Main AI update for this actor: skip while a view-controlled mode is active, run the per-frame AI helpers, drive scripted animations/effects for special states, spawn a random minion in mode 2, then hand off to the final AI pass. */ void updateActorMainAI(struct Actor *entity) {
    struct AIWork *ai;
    struct AIState *aiState;
    struct AIState *aiStateB;
    s32 ref;
    s32 timerResult;
    u8 *timerPtr;
    aiStateB = (struct AIState *)((u8 *)entity->aiPtr + 4);
    ref = entity->refPtr;
    ai = (struct AIWork *)entity->aiPtr;
    aiState = aiStateB;
    if (syncViewPosition(aiState, aiState) != 0) return;
    resetActionResultState(entity, (void *)ref, aiState, aiState);
    D_0806AB04(entity, (void *)ref, aiState, aiState);
    if (aiState->idleTimer == 0) {
        aiStateB->flag4C = 1;
        *(u8 *)((u32)entity->animIndex * 2 + (u32)entity + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 0x27, *(void **)fn); }
    }
    sub_0806A884((void *)ref, aiState);
    timerPtr = (u8 *)ai + 0x2C;
    timerResult = stepDelayTimer(timerPtr, (void *)ref);
    if (timerResult == 0) {
        startEffectTimer(timerPtr, 0, (void *)0x084A6814);
        *(u8 *)((u32)entity->animIndex * 2 + (u32)entity + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 0x24, *(void **)fn); }
    }
    if (aiState->mode == 2 && *(s32 *)((u8 *)ai + 0xBC) == 0) {
        if (scaleByRandom(8) != 0) {
            spawnEntity(entity, 0x3A, 0x0A, 0x12);
        } else {
            spawnEntity(entity, 0x3B, 0x0A, 0x12);
        }
        sub_08005E80(0x94);
        aiStateB->flagB8 = 1;
    }
    aiStateB->aiResult = sub_0806BCD8(entity, (void *)ref, aiStateB, aiState);
    if (aiStateB->aiResult != 0) {
        stepDelayTimer((u8 *)aiStateB + 0x28, (void *)ref);
        *(u8 *)((u32)entity->animIndex * 2 + (u32)entity + 0x19) = 0;
        { void *fn = &gScriptStepCallbacks; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, aiStateB->aiResult, *(void **)fn); }
    }
    sub_0806C6B0(entity, (void *)ref, aiStateB, aiState);
}
