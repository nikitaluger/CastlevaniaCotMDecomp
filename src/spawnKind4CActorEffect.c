extern struct FixedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectKindEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 gKind4CActorLayerAttrs[];
extern u32 gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/* Spawns a kind-0x4C actor effect: allocates a sprite and work state, builds its OAM attributes and animation from the kind tables, fills the render layer from default attributes, then advances the actor's script step; a failed allocation runs the actor's saved cleanup callback. */
void spawnKind4CActorEffect(struct Kind59EffectActor *actor) {
    s32 spriteObj;
    struct Kind59EffectWork *workState;
    u8 *animData;
    u16 *layerAttrs;
    u32 animSlot;
    u8 *scriptSteps;
    void **scriptCallbacks;
    u8 *scriptCommand;

    spriteObj = (s32)allocSpriteObject();
    if (spriteObj == 0) goto fail;
    actor->sprite = (void *)spriteObj;
    allocWorkSlot(actor, 0, 0x48, 0);
    if (actor->work == NULL) goto fail;
    *((u32 *)(spriteObj + 0x1C)) = 0x80000009;
    workState = (struct Kind59EffectWork *)actor->work;
    animData = ((u8 *)workState) + 0x34;
    installUpdateHandler(actor, (u8 *)workState, updateActorEffectSubObject);
    workState->kind = 0x4C;
    animSlot = findKindIndex();
    workState->animSlot = animSlot;
    if ((s16)animSlot < 0) goto fail;
    animSlot = workState->animSlot;
    animSlot = animSlot << 6;
    animSlot = animSlot + 0x200;
    animSlot &= 0xFC0;
    *((u16 *)spriteObj) = animSlot;
    *((u16 *)spriteObj) |= gMainWorkspace.gfxFlags;
    *((u16 *)(spriteObj + 2)) |= 0x400;
    initSpriteGraphics((void *)spriteObj, animData, (s32)(gSpriteAnimDataTable + workState->kind * 12));
    setAnimationFrame((void *)spriteObj, animData, 0, 0);
    layerAttrs = gKind4CActorLayerAttrs;
    workState->layer = allocEffectPart();
    if (workState->layer == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->cleanup);
    return;
ok:
    workState->layer->active = 4;
    workState->layer->layer = 8;
    workState->layer->priority = 1;
    workState->layer->gfxIndex = gEffectGfxTable[workState->kind].gfxIndex;
    workState->layer->anim0 = layerAttrs[0];
    workState->layer->anim1 = layerAttrs[1];
    workState->layer->anim2 = layerAttrs[2];
    workState->layer->anim3 = layerAttrs[3];
    workState->layer->palette = gEffectGfxTable[workState->kind].palette;
    workState->layer->sprite = (void *)spriteObj;
    actor->flags |= 0x1000;
    {
        s16 stepIndex = actor->step;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) = 0;
    }
    scriptCallbacks = &gMainObjTimerCallbacks;
    scriptSteps = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptSteps, ((u8 *)actor) + 0x22, (s32)(*scriptCallbacks));
    {
        s16 stepIndex = actor->step;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) += 1;
        stepIndex = actor->step;
        scriptCommand = scriptSteps + ((u32)stepIndex * 2);
        sub_080C31E0(actor, *((void **)(actor->scriptTable + ((*scriptCommand) * 4))));
    }
}
