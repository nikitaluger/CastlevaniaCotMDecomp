/* Spawns the fixed-kind (0x1E) attack effect from its parent: allocates a sprite and work
 * state, picks the starting frame from the parent's animation flags, positions the sprite
 * against the camera scroll, copies the parent's extra parameters into the work state and
 * finishes by invoking the spawn-done timer callback. Allocation/kind failures jump to a
 * shared fail path that forwards to the parent's previous handler. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void updateFixedKindEffect(void);
/* Indirect-call trampolines for saved handlers and the spawn-done callback. */
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, s32);

extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern struct FixedAttackGfxEntry gEffectGfxTable[];
extern s32 gMainObjTimerCallback[];

void spawnFixedKindEffect(struct FixedAttackEntity *entity) {
    u8 *sprite;
    struct FixedAttackWork *work;
    u8 *anim;
    s32 slot;
    u32 oamAttrs;
    u8 *scrollRows;
    s32 *callbackTable;
    struct FixedAttackWork *foundWork;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, FIXED_ATTACK_WORK_SLOT, 0);
    foundWork = entity->work;
    if (foundWork == NULL) goto fail;
    work = foundWork;
    anim = (u8 *)work + 0x34;
    work->updateFn = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)updateFixedKindEffect;
    work->kind = SPRITE_KIND_FIXED_ATTACK;
    work->param = FIXED_ATTACK_PARAM;
    work->x = entity->spawnX << 16;
    work->y = entity->spawnY << 16;
    slot = findKindIndex(SPRITE_KIND_FIXED_ATTACK);
    work->slot = slot;
    if ((s32)(slot << 16) < 0) goto fail;
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    {
        if (*(u16 *)((u8 *)entity + 0x5C) & FIXED_ATTACK_ANIM_FLAG_A)
            setAnimationFrame(sprite, anim, FIXED_ATTACK_FRAME_A, 0);
        else if (*(u16 *)((u8 *)entity + 0x5C) & FIXED_ATTACK_ANIM_FLAG_B)
            setAnimationFrame(sprite, anim, FIXED_ATTACK_FRAME_B, 0);
        else
            setAnimationFrame(sprite, anim, FIXED_ATTACK_FRAME_C, 0);
    }
    work->layer = allocEffectPart();
    if (work->layer == NULL) {
    fail:
        _call_via_r1(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    work->layer->active = 0;
    work->layer->layer = EFFECT_LAYER_KIND;
    work->layer->priority = EFFECT_LAYER_PRIORITY;
    work->layer->gfxA = gEffectGfxTable[work->kind].gfxA;
    work->layer->affine0 = gFixedAttackAffineParams[0];
    work->layer->affine1 = gFixedAttackAffineParams[1];
    work->layer->affine2 = gFixedAttackAffineParams[2];
    work->layer->affine3 = gFixedAttackAffineParams[3];
    work->layer->gfxB = gEffectGfxTable[work->kind].gfxB;
    work->layer->object = (u32)sprite;
    work->layer->timer = 0;
    oamAttrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamAttrs;
    *(u16 *)sprite = oamAttrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = EFFECT_SPRITE_GFX_ID;
    scrollRows = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(scrollRows + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(scrollRows + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    work->paramA = entity->paramA;
    work->paramB = entity->paramB;
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = 0;
    callbackTable = gMainObjTimerCallback;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackTable);
}
