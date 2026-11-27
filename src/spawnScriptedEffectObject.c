extern u16 gScriptObjectAffineParams[];
/* Initialises an entity spawned from an action script: allocates its sprite and work state,
 * configures OAM/animation and a render layer, places the sprite against the camera scroll,
 * hands the work state's handler to a per-frame updater, then dispatches the script's next
 * command through the entity's command table. Allocation or kind failures fall back to the
 * entity's previous handler. */
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern u32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void *allocEffectPart(void);
extern void updateScriptedEffectObject(void);
/* Indirect-call trampolines used to run saved handlers and script commands. */
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, s32);

extern struct FixedEffectWorkspace gMainWorkspace;
extern struct KindEffectGfxEntry gEffectGfxTable[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

void spawnScriptedEffectObject(struct ScriptedSpawnEntity *entity)
{
    struct ScriptedObjectSprite *sprite;
    struct KindEffectWork *work;
    u8 *layerBuf;
    u8 *anim;
    u32 kindOffset;
    u32 oamAttrs;
    u32 *callbackTable;
    u8 *stepClear;
    u8 *stepAdvance;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        _call_via_r1(entity, (void *)entity->updateFn);
        return;
    }
    entity->sprite = (u32)sprite;
    allocWorkSlot(entity, 0, SCRIPT_OBJECT_WORK_SLOT, 0);
    if (entity->work == 0) {
        _call_via_r1(entity, (void *)entity->updateFn);
        return;
    }
    sprite->gfxId = SCRIPT_OBJECT_GFX_ID;
    work = (struct KindEffectWork *)(*(void *volatile *)((u8 *)entity + 0x3C));
    anim = (u8 *)work + 0x34;
    installUpdateHandler(entity, work, (void *)updateScriptedEffectObject);
    work->kind = SCRIPT_OBJECT_KIND;
    kindOffset = findKindIndex();
    work->slot = (u16)kindOffset;
    if ((s32)((u16)kindOffset << 16) < 0) {
        _call_via_r1(entity, (void *)entity->updateFn);
        return;
    }
    oamAttrs = ((u32)((s32)work->slot << 6)) + 0x200;
    oamAttrs |= (kindOffset + 8) << 12;
    sprite->attrs = (u16)oamAttrs;
    sprite->attrs |= gMainWorkspace.gfxFlags;
    work->x = entity->spawnX;
    work->y = entity->spawnY;
    if (entity->flip)
        sprite->attrs2 |= ORIGIN_FLIP_X;
    else
        sprite->attrs2 &= 0xFFEF;
    initSpriteGraphics(sprite, anim, (void *)SCRIPT_OBJECT_ANIM_DATA);
    if (entity->variant)
        setAnimationFrame(sprite, anim, SCRIPT_OBJECT_FRAME_FLIP, 0);
    else
        setAnimationFrame(sprite, anim, SCRIPT_OBJECT_FRAME_BASE, 0);
    {
        u16 *affineParams = gScriptObjectAffineParams;
        layerBuf = allocEffectPart();
        work->layer = (struct KindEffectLayer *)layerBuf;
        if (layerBuf == NULL) {
            _call_via_r1(entity, (void *)entity->updateFn);
            return;
        }
        work->layer->active = 1;
        work->layer->layer = 8;
        work->layer->priority = 1;
        work->layer->gfxA = gEffectGfxTable[work->kind].gfxA;
        work->layer->affine0 = affineParams[0];
        work->layer->affine1 = affineParams[1];
        work->layer->affine2 = affineParams[2];
        work->layer->affine3 = affineParams[3];
        work->layer->gfxB = gEffectGfxTable[work->kind].gfxB;
        work->layer->object = (u32)sprite;
    }
    {
        u8 *cam = gCameraState;
        u32 off;
        off = 0x1278;
        sprite->posX = work->x - ((*(u32 *)(cam + off + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000);
        off = 0x127C;
        sprite->posY = work->y - ((*(u32 *)(cam + off + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    entity->flags |= EFFECT_SPRITE_READY;
    stepClear = (u8 *)(((u32)entity->stateIndex * 2) + (u32)entity);
    stepClear[0x19] = 0;
    callbackTable = &gMainObjTimerCallbacks;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)(*callbackTable));
    stepAdvance = (u8 *)(((u32)entity->stateIndex * 2) + (u32)entity);
    stepAdvance[0x19] = stepAdvance[0x19] + 1;
    {
        u8 *script = (u8 *)entity + 0x18;
        s32 stepOffset = entity->stateIndex * 2;
        u8 command = *(script + stepOffset);
        _call_via_r1(entity, *((void **)((u8 *)entity->scriptTable + (command * 4))));
    }
}
