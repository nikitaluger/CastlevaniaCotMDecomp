extern void stepAnimationTrack(void *, void *);
extern s32 detectActorHit(void *, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void applySpritePaletteVariant(void *, void *);
extern void syncSpriteToWorldPosition(void *, void *);
extern s32 sub_08014090(s16);
extern s32 checkActorViewBounds(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern s32 _call_via_r1(s32, s32);
extern void _call_via_r3(void *, void *, u32, u32);
extern void *gScriptEventCallbacks;

/*
 * Per-frame update of a scripted attack object: view-cull its sprite, handle
 * contact with its target, advance the current step of its script and dispatch
 * that step's handler, then mark both contact targets blocked while the
 * attack's kind is unavailable.
 */
void updateScriptedAttackObjectTick(void *entity)
{
    void *sprite;
    void *work;
    void *animTrack;
    u8 *contactTargets;
    u32 *eventCallback;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    animTrack = (u8 *)work + 0x34;
    contactTargets = (u8 *)work + 0x48;

    if (checkActorViewBounds(sprite, work) == 1)
        return;

    applySpritePaletteVariant(entity, sprite);
    if (detectActorHit(sprite, work, *(void **)((u8 *)work + 0x28)) != 0)
        spawnContactEffectOnHit(entity, *(void **)((u8 *)work + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)work + 0x28));

    if (*(u16 *)work & 1)
    {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity + 0x1A) != 4)
        {
            updateActorWorldPosition(entity);
            *(u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity + 0x1B) = 0;
            eventCallback = (u32 *)&gScriptEventCallbacks;
            _call_via_r3((u8 *)entity + SCRIPT_STEP_BASE_OFFSET, (u8 *)entity + SCRIPT_STEP_INDEX_OFFSET, 4, *eventCallback);
        }
    }

    if (updateObjectDisplayState(sprite, work) == 0)
    {
        u8 *stepEntry;
        u8 *stepStream;
        s32 stepOffset;
        u8 opcode;
        u32 stepHandlers;
        s32 stepHandler;

        ((struct ScriptAttackContactTarget *)*(u8 **)contactTargets)->flags &= SCRIPT_TARGET_UNBLOCK_MASK;
        ((struct ScriptAttackContactTarget *)*(u8 **)(contactTargets + 4))->flags &= SCRIPT_TARGET_UNBLOCK_MASK;

        *(u32 *)((u8 *)entity + SCRIPT_STEP_TABLE_OFFSET) = SCRIPT_ATTACK_OBJ_STEP_TABLE;
        *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) + 1;
        stepEntry = (u8 *)((u32)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
        *(u8 *)(stepEntry + 0x19) = *(u8 *)(stepEntry + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET)) * 2;
        stepStream = (u8 *)entity;
        stepStream += SCRIPT_STEP_BASE_OFFSET;
        stepStream += stepOffset;
        opcode = *stepStream;
        stepHandlers = *(u32 *)((u8 *)entity + SCRIPT_STEP_TABLE_OFFSET);
        stepHandler = *(s32 *)((u32)(opcode * 4) + stepHandlers);
        _call_via_r1((s32)entity, stepHandler);
        *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) = *(u16 *)((u8 *)entity + SCRIPT_STEP_INDEX_OFFSET) - 1;

        if (*(u16 *)((u8 *)entity + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM)
            return;
        stepAnimationTrack(sprite, animTrack);
    }
    else
    {
        if (sub_08014090(*(s16 *)((u8 *)work + 0x1C)) == 0)
        {
            ((struct ScriptAttackContactTarget *)*(u8 **)contactTargets)->flags |= SCRIPT_TARGET_BLOCKED_FLAG;
            ((struct ScriptAttackContactTarget *)*(u8 **)(contactTargets + 4))->flags |= SCRIPT_TARGET_BLOCKED_FLAG;
        }
    }

    syncSpriteToWorldPosition(entity, sprite);
}
