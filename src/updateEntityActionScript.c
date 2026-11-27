/* Prototypes of the helpers shared by the script-driven entity family. */
void stepAnimationTrack(void *, void *);
void moveEntityWithCollision(void *, u32);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r3(void *, void *, u32, u32);

/* Per-frame update of a script-driven entity: apply contact/animation state,
 * run the death response on a hit, dispatch one handler from the object's
 * action-script step table, then mirror work flags onto the step target. */
void updateEntityActionScript(struct ScriptEntityActionObject *obj) {
    void *sprite;
    struct ScriptEntityActionWorkFlags *work;
    u8 *animTrack;
    u8 *stepState;
    u8 *scriptPtr;
    u32 *eventCallbacks;
    u8 *stepSlot;
    u8 opcode;
    u32 stepTable;
    s32 stepHandler;
    s32 stepOffset;

    sprite = (void *)obj->sprite;
    work = (struct ScriptEntityActionWorkFlags *)obj->work;
    animTrack = (u8 *)work + 0x34;
    stepState = (u8 *)work + 0x48;
    if (checkActorViewBounds(sprite, work) != 1) {
        u16 skipFlags;

        applySpritePaletteVariant(obj, sprite);
        if (detectActorHit(sprite, work, *(void **)((u8 *)work + 0x28)) != 0)
            spawnContactEffectOnHit(obj, *(void **)((u8 *)work + 0x28));
        uploadPendingSpriteGraphic(obj, *(void **)((u8 *)work + 0x28));
        if (work->hitFlags & SCRIPT_ENTITY_ACTION_HIT) {
            if (*(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1A) != 2) {
                updateActorWorldPosition(obj);
                *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1B) = 0;
                eventCallbacks = (u32 *)SCRIPT_ENTITY_ACTION_EVENT_TABLE;
                _call_via_r3((u8 *)obj + 0x18, (u8 *)obj + 0x22, SCRIPT_ENTITY_ACTION_HIT_EVENT, *eventCallbacks);
            }
        }
        if (updateObjectDisplayState(sprite, work) == 0) {
            *(u32 *)((u8 *)obj + 0x14) = SCRIPT_ENTITY_ACTION_STEP_TABLE;
            *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
            stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(stepSlot + 0x19) = *(u8 *)(stepSlot + 0x19) + 1;
            stepOffset = (s32)(s16)(*(s16 *)((u8 *)obj + 0x22)) * 2;
            scriptPtr = (u8 *)obj;
            scriptPtr += 0x18;
            scriptPtr += stepOffset;
            opcode = *scriptPtr;
            stepTable = *(u32 *)((u8 *)obj + 0x14);
            stepHandler = *(s32 *)((u32)(opcode * 4) + stepTable);
            _call_via_r1((s32)obj, stepHandler);
            *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
            skipFlags = *(u16 *)((u8 *)obj + 2) & SCRIPT_ENTITY_ACTION_SKIP_ANIM;
            if (skipFlags != 0) {
                return;
            }
            stepAnimationTrack(sprite, animTrack);
            if (*(s16 *)(stepState + 6) == SCRIPT_ENTITY_ACTION_SPECIAL_MOVE) {
                moveEntityWithCollision(work, SCRIPT_ENTITY_ACTION_MOVE_SPEED);
                if (work->contactFlags & SCRIPT_ENTITY_ACTION_CONTACT) {
                    *(s16 *)(stepState + 6) = skipFlags;
                }
            }
        }
        if (work->contactFlags & SCRIPT_ENTITY_ACTION_MIRROR) {
            work->statusFlags |= SCRIPT_ENTITY_ACTION_MIRROR;
        } else {
            work->statusFlags &= SCRIPT_ENTITY_ACTION_MIRROR_CLEAR;
        }
        *(u16 *)((u8 *)*(void * volatile *)stepState + 4) = work->targetGfx;
        *(u16 *)((u8 *)*(void * volatile *)stepState + 6) = work->targetFrame + 1;
        syncSpriteToWorldPosition(obj, sprite);
    }
}
