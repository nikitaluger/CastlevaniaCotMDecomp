extern s32 isOutsideCameraBounds(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 _call_via_r1(void *, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern s32 stepAnimationTrack(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gCameraBoundedAttackStepTable[];
extern s32 gScriptEventCallbacks;

/*
 * Per-frame update of a camera-bounded scripted attack: refresh the target's
 * hit state and the sprite's visibility, dispatch the current script step,
 * advance the animation track, then place the sprite in camera space.
 */
void updateCameraBoundedScriptedAttack(u8 *script) {
    u8 *sprite;
    u8 *work;
    void *animTrack;
    u8 *nextStep;
    u8 *cameraState;
    u8 *scrollXBase;
    u8 *frameCounter;
    u32 scrollOffset;
    u32 scrollX;
    u32 scrollY;
    u32 stepOpcode;
    u8 *stepBase;
    s32 stepOffset;
    u8 *currentStep;
    s32 wasHit;
    s32 *eventCallbacks;

    sprite = *(u8 **)(script + 0x38);
    work = *(u8 **)(script + 0x3C);
    animTrack = work + 0x34;
    if (isOutsideCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC)) == 1) {
        s32 maskedBits = ATTACK_SPRITE_SHOW_MASK &
                         ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag;
        u8 zero = 0;
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag = maskedBits;
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = zero;
    } else {
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_PENDING;
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag |= ATTACK_SPRITE_HIDE_FLAG;
        if (hitTestEntities(*(u8 **)(work + 0x28)) != 0) {
            ((struct AttackHitFlags *)work)->flag |= SCRIPT_OBJ_HIT_FLAG;
        }
    }
    wasHit = *(u16 *)work & SCRIPT_OBJ_HIT_FLAG;
    stepBase = script + SCRIPT_STEP_BASE_OFFSET;
    if (wasHit) {
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_CLEAR;
        stepOffset = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2;
        currentStep = (u8 *)((s32)stepOffset + (s32)script);
        if (*(u8 *)(currentStep + 0x1A) != 1) {
            *(u8 *)(currentStep + 0x1B) = 0;
            eventCallbacks = &gScriptEventCallbacks;
            _call_via_r3(stepBase, script + SCRIPT_STEP_INDEX_OFFSET, 1, *eventCallbacks);
        }
    }
    *(u32 *)(script + SCRIPT_STEP_TABLE_OFFSET) = (u32)gCameraBoundedAttackStepTable;
    *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) + 1;
    nextStep = (u8 *)((u32)(*(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)script);
    *(u8 *)(nextStep + 0x19) = *(u8 *)(nextStep + 0x19) + 1;
    stepOffset = *(s16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2;
    stepOpcode = *(u8 *)((u32)stepBase + (u32)stepOffset);
    _call_via_r1(script, *(u32 *)(*(u32 *)(script + SCRIPT_STEP_TABLE_OFFSET) + stepOpcode * 4));
    *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) - 1;
    if ((*(u16 *)(script + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) return;
    stepAnimationTrack(sprite, animTrack);
    cameraState = gCameraState;
    frameCounter = gMainWorkspace;
    frameCounter += 0x18A8;
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    scrollXBase = cameraState + 0x1278;
    scrollX = *(u32 *)(scrollXBase + scrollOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    cameraState += 0x127C;
    scrollY = *(u32 *)(cameraState + scrollOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
