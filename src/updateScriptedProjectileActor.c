extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void setAttackHitbox(void *, void *);
extern s32 sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gProjectileScriptStepTable[];
extern s32 gScriptEventCallbacks[];

/* Per-frame update for the camera-relative scripted projectile actor: latch
 * hit flags, dispatch a flagged event callback, run one script step, then
 * project the work position into the sprite's screen coordinates. */
void updateScriptedProjectileActor(u8 *actor)
{
    u8 *sprite;
    u8 *work;
    u8 *animTrack;
    struct AttackTargetState *hitTarget;
    u8 *stepPtr;
    u8 *scrollTable;
    u8 *frameCounterPtr;
    u8 *scrollXPtr;
    u32 scrollIndex;
    u32 scrollX;
    u32 scrollY;
    u32 command;
    u8 *stepStream;
    s32 stepOffset;

    sprite = *(u8 **)(actor + 0x38);
    work = *(u8 **)(actor + 0x3C);
    animTrack = work + 0x34;
    hitTarget = *(struct AttackTargetState **)(work + 0x28);
    hitTarget->hitState |= SCRIPT_OBJ_HIT_FLAG;

    if ((*(u16 *)(actor + 0x6C) & SCRIPT_PROJ_ATTACK_FLAG) != 0) {
        ((struct AttackHitFlags *)work)->flag |= SCRIPT_OBJ_HIT_FLAG;
    }

    if ((*(u16 *)(work + 0x00) & SCRIPT_OBJ_HIT_FLAG) != 0) {
        u8 *stepStatePtr = (u8 *)((*(s16 *)(actor + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)actor);
        if (*(u8 *)(stepStatePtr + SCRIPT_STEP_EVENT_OFFSET) != SCRIPT_PROJ_HIT_EVENT) {
            s32 *callback;
            *(u8 *)(stepStatePtr + SCRIPT_STEP_EVENT_TIMER_OFFSET) = 0;
            callback = gScriptEventCallbacks;
            sub_080C31E8(actor + SCRIPT_STEP_BASE_OFFSET, actor + SCRIPT_STEP_INDEX_OFFSET,
                         SCRIPT_PROJ_HIT_EVENT, *callback);
        }
    }

    if (updateObjectDisplayState(sprite, work) != 0) goto common;

    *(u32 *)(actor + SCRIPT_STEP_TABLE_OFFSET) = (u32)gProjectileScriptStepTable;
    *(u16 *)(actor + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(actor + SCRIPT_STEP_INDEX_OFFSET) + 1;
    stepPtr = (u8 *)((u32)(*(s16 *)(actor + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)actor);
    *(u8 *)(stepPtr + SCRIPT_STEP_TIMER_OFFSET) = *(u8 *)(stepPtr + SCRIPT_STEP_TIMER_OFFSET) + 1;
    stepOffset = *(s16 *)(actor + SCRIPT_STEP_INDEX_OFFSET) * 2;
    stepStream = actor;
    stepStream += SCRIPT_STEP_BASE_OFFSET;
    command = *(u8 *)((u32)stepStream + (u32)stepOffset);
    sub_080C31E0((void *)actor, *(u32 *)(*(u32 *)(actor + SCRIPT_STEP_TABLE_OFFSET) + command * 4));
    *(u16 *)(actor + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(actor + SCRIPT_STEP_INDEX_OFFSET) - 1;
    if ((*(u16 *)(actor + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) return;
    stepAnimationTrack(sprite, animTrack);
    advanceMotion(work, 0);

common:
    setAttackHitbox(sprite, work);

    scrollTable = gCameraState;
    frameCounterPtr = gMainWorkspace;
    frameCounterPtr += BEHAVIOR_WORKSPACE_COUNTER;
    scrollIndex = ((u32)*frameCounterPtr + 1) * BEHAVIOR_SCROLL_STEP;
    scrollXPtr = scrollTable + BEHAVIOR_SCROLL_X_OFFSET;
    scrollX = *(u32 *)(scrollXPtr + scrollIndex);
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((scrollX + BEHAVIOR_SCROLL_BIAS_X) & BEHAVIOR_FRAC_MASK);
    scrollIndex = ((u32)*frameCounterPtr + 1) * BEHAVIOR_SCROLL_STEP;
    scrollTable += BEHAVIOR_SCROLL_Y_OFFSET;
    scrollY = *(u32 *)(scrollTable + scrollIndex);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((scrollY + BEHAVIOR_SCROLL_BIAS_Y) & BEHAVIOR_FRAC_MASK);
}
