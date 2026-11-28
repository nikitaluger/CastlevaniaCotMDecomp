/* Main-object script updater: apply the entity's palette/variant, cull it when
 * it leaves the camera view, resolve a contact hit and flush pending sprite
 * graphics, then either run the finished-step callback path or advance the
 * script step (falling back to a render-part/world-position refresh). */
void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void clearMotionSpriteOverride(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r2(void *, void *, u32);

extern u32 gMainObjectStepHandlers;
extern u32 gMainObjTimerCallbacks;

void updateMainObject(void *entity) {
    void *sprite;
    void *work;
    struct MainObjectParts *parts;
    s32 stepHandler;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    parts = (struct MainObjectParts *)((u8 *)work + 0x48);
    applySpritePaletteVariant(entity, sprite);
    if (checkActorViewBounds(sprite, work) == 1) {
        ((u8 *)parts->partA)[1] = 0;
        ((u8 *)parts->partB)[1] = 0;
        return;
    }
    if (detectActorHit(sprite, work, *(void **)((u8 *)work + 0x28)) != 0)
        spawnContactEffectOnHit(entity, *(void **)((u8 *)work + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)work + 0x28));
    uploadPendingSpriteGraphic(entity, parts->partA);
    uploadPendingSpriteGraphic(entity, parts->partB);
    if (*(u16 *)work & 1) {
        u32 *timerCallback;
        u8 *steps;
        u8 opcode;
        u32 handlers;
        s32 stepOffset;
        updateActorWorldPosition(entity);
        ((u8 *)parts->partA)[1] = 0;
        ((u8 *)parts->partB)[1] = 0;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = 0;
        }
        timerCallback = (u32 *)&gMainObjTimerCallbacks;
        steps = (u8 *)entity + SCRIPT_STEP_BASE_OFFSET;
        _call_via_r2(steps, (u8 *)entity + SCRIPT_STEP_INDEX_OFFSET, *timerCallback);
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2;
        steps += stepOffset;
        opcode = *steps;
        handlers = *(u32 *)((u8 *)entity + SCRIPT_STEP_TABLE_OFFSET);
        stepHandler = *(s32 *)((u32)(opcode * 4) + handlers);
        _call_via_r1((s32)entity, stepHandler);
        return;
    } else {
        if (updateObjectDisplayState(sprite, work) == 0) {
            u8 *stepData;
            u8 *steps;
            u8 opcode;
            u32 handlers;
            s32 stepOffset;
            *(u32 *)((u8 *)entity + SCRIPT_STEP_TABLE_OFFSET) = (u32)&gMainObjectStepHandlers;
            *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) + 1;
            stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
            stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2;
            steps = (u8 *)entity;
            steps += SCRIPT_STEP_BASE_OFFSET;
            steps += stepOffset;
            opcode = *steps;
            handlers = *(u32 *)((u8 *)entity + SCRIPT_STEP_TABLE_OFFSET);
            _call_via_r1((s32)entity, *(s32 *)((u32)(opcode * 4) + handlers));
            *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) - 1;
        } else {
            clearMotionSpriteOverride(work, parts->partA);
            clearMotionSpriteOverride(work, parts->partB);
        }
        syncSpriteToWorldPosition(entity, sprite);
    }
}
