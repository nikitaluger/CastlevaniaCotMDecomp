/* Per-frame update of a scripted gravity attack: drop the object when its target
 * leaves the tight camera box, refresh the target's hit state and the sprite's
 * visibility, dispatch the current script step through gGravityAttackStepTable,
 * apply gravity with collision, then place the sprite relative to the camera. */
extern s32 isPointInActiveCameraBounds(s32, s32, s32, s32, s32, s32);
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 _call_via_r1(void *, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern s32 moveEntityWithCollision(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gGravityAttackStepTable[];
extern s32 gScriptEventCallbacks;

void updateGravityScriptedAttack(u8 *entity) {
    u8 *sprite;
    u8 *work;
    u8 *stepEntry;
    u8 *scrollRows;
    u8 *scrollXRow;
    u8 *frameCounter;
    u32 scrollOffset;
    u32 scrollX;
    u32 scrollY;
    u32 opcode;
    u8 *stepStream;
    s32 stepByteOffset;
    u8 *scriptEntry;
    s32 hitLanded;
    s32 *callbackTable;

    sprite = *(u8 **)(entity + 0x38);
    work = *(u8 **)(entity + 0x3C);
    if (isPointInActiveCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC), -8, 8, -8, 8) == 0) {
        _call_via_r1(entity, *(u32 *)(entity + 0x24));
        return;
    }
    if (isOutsideCameraBounds(*(s32 *)(work + 8), *(s32 *)(work + 0xC)) == 1) {
        s32 visibleFlags = ATTACK_SPRITE_SHOW_MASK & ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag;
        u8 clearHit = ATTACK_TARGET_CLEAR;
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag = visibleFlags;
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = clearHit;
    } else {
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_PENDING;
        ((struct AttackSpriteFlags *)(sprite + 0x2A))->flag |= ATTACK_SPRITE_HIDE_FLAG;
        if (hitTestEntities(*(u8 **)(work + 0x28)) != 0) {
            ((struct AttackHitFlags *)work)->flag |= 1;
        }
    }
    hitLanded = *(u16 *)work & 1;
    stepStream = entity + 0x18;
    if (hitLanded) {
        ((struct AttackTargetState *)(*(u8 **)(work + 0x28)))->hitState = ATTACK_TARGET_CLEAR;
        stepByteOffset = *(s16 *)(entity + 0x22) * 2;
        scriptEntry = (u8 *)((s32)stepByteOffset + (s32)entity);
        if (*(u8 *)(scriptEntry + 0x1A) != 1) {
            *(u8 *)(scriptEntry + 0x1B) = 0;
            callbackTable = &gScriptEventCallbacks;
            _call_via_r3(stepStream, entity + 0x22, 1, *callbackTable);
        }
    }
    *(u32 *)(entity + 0x14) = (u32)gGravityAttackStepTable;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepEntry + 0x19) = *(u8 *)(stepEntry + 0x19) + 1;
    stepByteOffset = *(s16 *)(entity + 0x22) * 2;
    opcode = *(u8 *)((u32)stepStream + (u32)stepByteOffset);
    _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + opcode * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) return;
    moveEntityWithCollision(work, SCRIPT_TIMED_ATTACK_GRAVITY);
    scrollRows = gCameraState;
    frameCounter = gMainWorkspace;
    frameCounter += 0x18A8;
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    scrollXRow = scrollRows + 0x1278;
    scrollX = *(u32 *)(scrollXRow + scrollOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollOffset = ((u32)*frameCounter + 1) * 0x40;
    scrollRows += 0x127C;
    scrollY = *(u32 *)(scrollRows + scrollOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
