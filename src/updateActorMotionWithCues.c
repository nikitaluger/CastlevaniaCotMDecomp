s32 syncViewPosition(void *, void *);
void resetActionResultState(void *, void *, void *, void *);
void sub_0806AB04(void *, void *, void *, void *);
void startEffectTimer(void *, s32, s32);
void sub_08005E80(s32);
void sub_0806A7AC(void *, void *, s32);
void sub_0806A884(void *, void *);
void stepDelayTimer(void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
void spawnRoom34Object(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
extern s32 gMainObjTimerCallbacks;
extern s32 gMenuScriptCallback;

/* Advance a spawned effect's motion from its profile table at 0x080E03A0 and,
   when its action flag is set, fire the kind-specific hit/sound/animation cues. */
/* Advance an actor's capped motion from its kind's row in the 0x080E03A0 parameter table; when its action flag is set, zero the motion fields, fire the kind-specific form/sound/spawn cues and dispatch a script step. */ void updateActorMotionWithCues(void *actor) {
    void *spawnState = *(void **)((u8 *)actor + 0x6C);
    void *workBase = (void *)((u32)spawnState + 4);
    void *work;
    void *target = *(void **)((u8 *)actor + 0x38);
    s32 result;
    u8 *paramTable;
    s32 entryOffset;
    s32 maxMotion;
    s32 cueKind;
    u8 *stepState;
    s32 *callbackTable;

    work = workBase;
    result = syncViewPosition(work, work);
    if (result != 0) return;
    resetActionResultState(actor, target, work, work);
    paramTable = (u8 *)0x080E03A0;
    entryOffset = *(s32 *)((u8 *)work + 0x44) * 0x58;
    *(s32 *)((u8 *)work + 0x0C) += *(s32 *)(entryOffset + paramTable);
    paramTable += 4;
    maxMotion = *(s32 *)(entryOffset + paramTable);
    if (*(s32 *)((u8 *)work + 0x0C) > maxMotion)
        *(s32 *)((u8 *)work + 0x0C) = maxMotion;
    sub_0806AB04(actor, target, work, work);
    if (*(s32 *)((u8 *)work + 0x40) == 1) {
        *(s32 *)((u8 *)work + 8) = result;
        *(s32 *)((u8 *)work + 0x0C) = result;
        cueKind = *(s32 *)((u8 *)spawnState + 0xA0);
        switch (cueKind) {
        case 1:
            sub_0806A7AC(target, work, 0x26);
            sub_08005E80(0x7A);
            spawnRoom34Object(actor, work);
            stepState = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
            stepState[0x17] = result;
            callbackTable = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x1A, *callbackTable);
            break;
        case 3:
            sub_0806A7AC(target, work, 0x25);
            sub_08005E80(0x79);
            spawnRoom34Object(actor, work);
            *(s32 *)((u8 *)work + 0x10) = result;
            stepState = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
            stepState[0x17] = result;
            callbackTable = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x1B, *callbackTable);
            break;
        default:
            startEffectTimer((u8 *)spawnState + 0x2C, 0, 0x0846EC44);
            stepState = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
            stepState[0x19] = result;
            callbackTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, *callbackTable);
            break;
        }
    }
    sub_0806A884(target, work);
    stepDelayTimer((u8 *)workBase + 0x28, target);
    sub_0806C6B0(actor, target, workBase, work);
}
