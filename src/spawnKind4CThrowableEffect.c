extern struct FixedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectKindEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 gKind4CThrowableLayerAttrs[];
extern u32 gScriptStepCallbackTable;
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

/* Spawns the kind-0x4C throwable: allocate the sprite and work state, build its
 * animation and graphics, fill the render layer from the defaults table, then
 * advance the script; a failed allocation runs the actor's saved cleanup callback. */
void spawnKind4CThrowableEffect(struct Kind59EffectActor *actor) {
    s32 sprite;
    struct FixedEffectState *state;
    u8 *animState;
    u16 *defaultParams;
    u32 slot;
    u8 *scriptData;
    void **scriptTable;
    u8 *commandPtr;
    u8 zero;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->sprite = (void *)sprite;
    allocWorkSlot(actor, 0, 0x48, 0);
    if (actor->work == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = 0x8000000A;
    state = (struct FixedEffectState *)actor->work;
    animState = ((u8 *)state) + 0x34;
    installUpdateHandler(actor, (u8 *)state, updateActorEffectSubObject);
    zero = 0;
    state->kind = 0x4C;
    slot = findKindIndex();
    state->animSlot = slot;
    if ((s16)slot < 0) goto fail;
    slot = state->animSlot;
    slot = slot << 6;
    slot = slot + 0x200;
    slot &= 0xFC0;
    *((u16 *)sprite) = slot;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    initSpriteGraphics((void *)sprite, animState, (s32)(gSpriteAnimDataTable + state->kind * 12));
    setAnimationFrame((void *)sprite, animState, 5, 0);
    *((u8 *)sprite + 0x2A) &= 0xBF;
    defaultParams = gKind4CThrowableLayerAttrs;
    state->spriteLayer = allocEffectPart();
    if (state->spriteLayer == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->cleanup);
    return;
ok:
    state->spriteLayer->active = zero;
    state->spriteLayer->param2 = 8;
    state->spriteLayer->param3 = 1;
    state->spriteLayer->gfxIndex = gEffectGfxTable[state->kind].gfxIndex;
    state->spriteLayer->anim0 = defaultParams[0];
    state->spriteLayer->anim1 = defaultParams[1];
    state->spriteLayer->anim2 = defaultParams[2];
    state->spriteLayer->anim3 = defaultParams[3];
    state->spriteLayer->palette = gEffectGfxTable[state->kind].palette;
    state->spriteLayer->object = (void *)sprite;
    actor->flags |= 0x1000;
    {
        s16 stepIndex = actor->step;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) = zero;
    }
    scriptTable = &gScriptStepCallbackTable;
    scriptData = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptData, ((u8 *)actor) + 0x22, (s32)(*scriptTable));
    {
        s16 stepIndex = actor->step;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) += 1;
        stepIndex = actor->step;
        commandPtr = scriptData + ((u32)stepIndex * 2);
        sub_080C31E0(actor, *((void **)(actor->scriptTable + ((*commandPtr) * 4))));
    }
}
