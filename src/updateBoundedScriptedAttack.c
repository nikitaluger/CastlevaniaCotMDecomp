extern s32 isPointInActiveCameraBounds(s32, s32, s32, s32, s32, s32);
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 _call_via_r1(void *, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern s32 stepAnimationTrack(void *, void *);
extern s32 moveEntityWithCollision(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gBoundedAttackStepTable[];
extern s32 gScriptEventCallbacks;

/* Despawn a scripted attack when it leaves the active camera rectangle, tick
 * its step timer and hit/visibility flags, dispatch one script command from
 * gBoundedAttackStepTable, then move it and place its sprite in camera space. */
void updateBoundedScriptedAttack(u8 *script) {
    u8 *sprite;
    u8 *work;
    u8 *stepState;
    u8 *animTrack;
    u8 *scriptBase;
    u8 *cameraTable;
    u8 *scrollXBase;
    u8 *frameCounterPtr;
    u32 scrollOffset;
    u32 scrollX;
    u32 scrollY;
    u32 stepOpcode;
    s32 stepOffset;
    u8 *currentStep;
    u8 *nextStep;
    s32 wasHit;
    s32 *eventCallbacks;

    sprite = *(u8 **)(script + 0x38);
    work = *(u8 **)(script + 0x3C);
    animTrack = work + 0x34;
    stepState = work + 0x48;
    if (isPointInActiveCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC), -8, 8, -8, 8) == 0) {
        _call_via_r1(script, *(u32 *)(script + 0x24));
        return;
    }
    if (*(s16 *)(stepState + 2) > 0) {
        *(u16 *)(stepState + 2) = (u16)(*(s16 *)(stepState + 2) - 1);
    }
    if (isOutsideCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC)) == 1) {
        s32 keptFlags = ATTACK_SPRITE_SHOW_MASK & ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag;
        u8 zero = 0;
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag = keptFlags;
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = zero;
    } else {
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag = ATTACK_SPRITE_HIDE_FLAG | ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag;
        if (*(s16 *)(stepState + 2) > 0) {
            ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_CLEAR;
        } else {
            ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_PENDING;
            if (hitTestEntities(*(u8 **)(work + 0x28)) != 0) {
                ((struct AttackHitFlags *)work)->flag |= SCRIPT_OBJ_HIT_FLAG;
            }
        }
    }
    wasHit = *(u16 *)work & SCRIPT_OBJ_HIT_FLAG;
    scriptBase = script + SCRIPT_STEP_BASE_OFFSET;
    if (wasHit) {
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_CLEAR;
        stepOffset = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2;
        currentStep = (u8 *)((s32)stepOffset + (s32)script);
        if (*(u8 *)(currentStep + 0x1A) != 1) {
            *(u8 *)(currentStep + 0x1B) = 0;
            eventCallbacks = &gScriptEventCallbacks;
            _call_via_r3(scriptBase, script + SCRIPT_STEP_INDEX_OFFSET, 1, *eventCallbacks);
        }
    }
    *(u32 *)(script + SCRIPT_STEP_TABLE_OFFSET) = (u32)gBoundedAttackStepTable;
    *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) + 1;
    nextStep = (u8 *)((u32)(*(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)script);
    *(u8 *)(nextStep + 0x19) = *(u8 *)(nextStep + 0x19) + 1;
    stepOffset = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2;
    stepOpcode = *(u8 *)((u32)scriptBase + (u32)stepOffset);
    _call_via_r1(script, *(u32 *)(*(u32 *)(script + SCRIPT_STEP_TABLE_OFFSET) + stepOpcode * 4));
    *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) - 1;
    if ((*(u16 *)(script + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) return;
    stepAnimationTrack(sprite, animTrack);
    moveEntityWithCollision(work, *(u32 *)(stepState + 8));
    cameraTable = gCameraState;
    frameCounterPtr = gMainWorkspace;
    frameCounterPtr += 0x18A8;
    scrollOffset = ((u32)*frameCounterPtr + 1) * 0x40;
    scrollXBase = cameraTable + 0x1278;
    scrollX = *(u32 *)(scrollXBase + scrollOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollOffset = ((u32)*frameCounterPtr + 1) * 0x40;
    cameraTable += 0x127C;
    scrollY = *(u32 *)(cameraTable + scrollOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
