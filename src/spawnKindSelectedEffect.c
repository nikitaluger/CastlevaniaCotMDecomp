extern u16 gKindEffectAffineParams[];
/* Allocates a sprite plus a render layer for the effect kind stored in the parent entity,
 * initialises their graphics/animation state and world position from the scroll tables,
 * installs releaseEffectState as the parent's new handler, then calls the finished-spawn
 * timer callback. On an allocation failure or invalid kind it clears the entity's tracking
 * slot and forwards to its previous handler instead. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void releaseEffectState(void);
extern void unregisterEffectEntity(u8 *);
/* Indirect-call trampolines: _call_via_r1 calls its second argument with the first,
 * _call_via_r2 calls its third argument with the first two. */
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);

extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern struct KindEffectGfxEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallbacks[];

void spawnKindSelectedEffect(struct KindEffectEntity *entity) {
    u8 *sprite;
    struct KindEffectWork *work;
    u8 *gfxState;
    u8 *layerBuf;
    s32 slot;
    u32 oamAttrs;
    /* Two separately materialised zeros: agbcc keeps the byte/halfword and word
     * zeros in different registers, and both forms are needed below. */
    u32 zeroByte;
    u32 zeroWord;
    u8 *scrollRows;
    u8 *workTail;
    s32 *callbackTable;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        unregisterEffectEntity((u8 *)entity);
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, EFFECT_WORK_SLOT_SIZE, 0);
    work = entity->work;
    if (work == NULL) {
        unregisterEffectEntity((u8 *)entity);
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    gfxState = (u8 *)work + 0x34;
    work->updateFn = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)releaseEffectState;
    work->kind = entity->kind;
    zeroByte = 0;
    zeroWord = 0;
    work->param = 1;
    work->x = entity->spawnX << 16;
    work->y = entity->spawnY << 16;
    slot = findKindIndex(work->kind);
    work->slot = slot;
    if ((s32)(slot << 16) < 0) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(sprite, gfxState, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    layerBuf = allocEffectPart();
    work->layer = (struct KindEffectLayer *)layerBuf;
    if (layerBuf == NULL) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }

    work->layer->active = zeroByte;
    work->layer->layer = EFFECT_LAYER_KIND;
    work->layer->priority = EFFECT_LAYER_PRIORITY;
    work->layer->gfxA = gEffectGfxTable[work->kind].gfxA;
    work->layer->affine0 = gKindEffectAffineParams[0];
    work->layer->affine1 = gKindEffectAffineParams[1];
    work->layer->affine2 = gKindEffectAffineParams[2];
    work->layer->affine3 = gKindEffectAffineParams[3];
    work->layer->gfxB = gEffectGfxTable[work->kind].gfxB;
    work->layer->object = (u32)sprite;
    work->layer->timer = zeroByte;
    oamAttrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttrs;
    *(u16 *)sprite = oamAttrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = EFFECT_SPRITE_GFX_ID;
    scrollRows = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(scrollRows + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(scrollRows + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    workTail = (u8 *)work + 0x48;
    *(u32 *)(workTail + 0x10) = zeroWord;
    *(u32 *)(workTail + 0x58) = (u32)((s32)entity->effectParam * 8 + (s32)gKindEffectParamTable);
    setAnimationFrame(sprite, gfxState, EFFECT_ANIM_FRAME, 0x01);
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = zeroWord;
    callbackTable = gMainObjTimerCallbacks;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackTable);
}
