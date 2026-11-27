/* Advance a room-anchored scripted attack: reject it when its hit box leaves
 * the camera, resolve a hit, dispatch one script command, then re-anchor the
 * attacker to the current room's scroll coordinates. */
extern s32 isOutsideCameraBounds(s32, s32);
extern void stepAnimationTrack(void *, void *);
extern s32 hitTestEntities(void *);
extern void playSound(s32);
extern s32 _call_via_r1(void *, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gScriptedAttackCmdTableAlt[];
extern s32 gScriptEventCallbacks;

void updateRoomAnchoredScriptedAttackAlt(u8 *object) {
    u8 *attacker;
    u8 *attack;
    u8 *attackAnimState;
    u8 *stepStream;
    s16 stepIndex;
    s32 stepByteOffset;
    u8 commandId;

    attacker = *(u8 **)(object + 0x38);
    attack = *(u8 **)(object + 0x3C);
    attackAnimState = attack + 0x14;

    if (isOutsideCameraBounds(*(s32 *)(attack + 0x04), *(s32 *)(attack + 0x08)) == 1) {
        _call_via_r1(object, *(s32 *)(object + 0x24));
        return;
    }

    stepIndex = *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET);
    if (*(u8 *)(object + stepIndex * ATTACK_STEP_STRIDE + ATTACK_STEP_FLAG_A_OFF) == 1) {
        stepStream = object + SCRIPT_STEP_BASE_OFFSET;
    } else {
        stepStream = object + SCRIPT_STEP_BASE_OFFSET;
        if (hitTestEntities(*(void **)(attack + 0x10)) != 0) {
            *(u8 *)(*(u8 **)(attack + 0x10) + 1) = 0;
            playSound(0x6E);
            *(u8 *)(object + *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) * ATTACK_STEP_STRIDE + ATTACK_STEP_FLAG_B_OFF) = 0;
            {
                s32 *eventCallbackSlot = &gScriptEventCallbacks;
                _call_via_r3(stepStream, object + SCRIPT_STEP_INDEX_OFFSET, 1, *eventCallbackSlot);
            }
        }
    }

    *(u32 *)(object + SCRIPT_STEP_TABLE_OFFSET) = (u32)gScriptedAttackCmdTableAlt;
    *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) = *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) + 1;
    *(u8 *)(object + *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) * ATTACK_STEP_STRIDE + ATTACK_STEP_TIMER_OFF) = *(u8 *)(object + *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) * ATTACK_STEP_STRIDE + ATTACK_STEP_TIMER_OFF) + 1;
    stepByteOffset = *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) * ATTACK_STEP_STRIDE;
    commandId = *(u8 *)((u32)stepStream + (u32)stepByteOffset);
    _call_via_r1(object, *(s32 *)(*(u32 *)(object + SCRIPT_STEP_TABLE_OFFSET) + commandId * 4));
    *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) = *(s16 *)(object + SCRIPT_STEP_INDEX_OFFSET) - 1;

    if (*(u16 *)(object + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM)
        return;

    stepAnimationTrack(attacker, attackAnimState);

    {
        u8 *camera = gCameraState;
        u8 *roomCounterPtr = gMainWorkspace;
        u8 *scrollXTable;
        u8 *scrollYTable;
        u32 scrollRowOffset;

        roomCounterPtr += ATTACK_ROOM_COUNTER_OFF;

        scrollRowOffset = ((u32)*roomCounterPtr + 1) * ATTACK_SCROLL_STRIDE;
        scrollXTable = camera + ATTACK_SCROLL_X_OFF;
        *(u32 *)(attacker + 0x14) = *(u32 *)(attack + 0x04) - ((*(u32 *)(scrollXTable + scrollRowOffset) + ATTACK_SCROLL_BIAS_X) & ATTACK_SCROLL_FRAC_MASK);

        scrollRowOffset = ((u32)*roomCounterPtr + 1) * ATTACK_SCROLL_STRIDE;
        scrollYTable = camera + ATTACK_SCROLL_Y_OFF;
        *(u32 *)(attacker + 0x18) = *(u32 *)(attack + 0x08) - ((*(u32 *)(scrollYTable + scrollRowOffset) + ATTACK_SCROLL_BIAS_Y) & ATTACK_SCROLL_FRAC_MASK);
    }
}
