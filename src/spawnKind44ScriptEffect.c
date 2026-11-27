extern u16 gKind44ScriptEffectLayerAttrs[];
/* Spawns the kind-0x44 script effect: allocate a sprite and a work block in the
 * entity's +0x3C slot, seed animation/render-layer attributes from the kind and
 * layer tables, then dispatch the next script step. On failure run the entity's
 * saved cleanup callback. */
struct Kind44Workspace { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct Kind44Workspace gMainWorkspace;
struct Kind44RenderLayer {
    u8 _0, kind, layer, priority;
    u16 gfxIndex, affine0, affine1, affine2, affine3, palette;
    u32 sprite;
};
struct Kind44WorkState {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 kind; u8 _1E[4]; u16 animSlot; u8 _24[4];
    struct Kind44RenderLayer *layer; u8 _2C[0x1C]; u32 f48;
};
struct Kind44KindEntry { u16 gfxIndex; u8 _2[2]; u16 palette; u8 _6[0xE]; };
extern struct Kind44KindEntry gSpriteKindTable[];
extern void *gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_0809C2F0(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

void spawnKind44ScriptEffect(u8 *entity) {
    s32 spriteObj; struct Kind44WorkState *work; u8 *animData; u8 one; s32 animSlot; u16 *layerAttrs; u8 *scriptSteps; void **scriptCallbacks; u8 *scriptCommand;
    spriteObj = (s32)allocSpriteObject();
    if (spriteObj == 0) goto fail;
    *(u32 *)(entity + 0x38) = spriteObj;
    allocWorkSlot(entity, 0, KIND44_SCRIPT_EFFECT_WORK_SIZE, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    one = KIND44_SCRIPT_EFFECT_GFX_ID;
    *(u32 *)(spriteObj + 0x1C) = one;
    work = (struct Kind44WorkState *)*(u8 **)(entity + 0x3C);
    animData = (u8 *)work + 0x34;
    installUpdateHandler(entity, (u8 *)work, releaseActorEffectSubObject);
    work->kind = KIND44_SCRIPT_EFFECT_KIND;
    animSlot = findKindIndex(KIND44_SCRIPT_EFFECT_KIND);
    work->animSlot = animSlot;
    if ((animSlot << 16) < 0) goto fail;
    *(u16 *)spriteObj = gMainWorkspace.gfxFlags;
    sub_0809C2F0((void *)spriteObj, animData, 0, 8);
    setObjectAnimation((void *)spriteObj, animData, KIND44_SCRIPT_EFFECT_FRAME, 0);
    *(u8 *)(entity + 0x88) = KIND44_SCRIPT_EFFECT_INIT_TIMER;
    layerAttrs = gKind44ScriptEffectLayerAttrs;
    work->layer = allocEffectPart();
    if (work->layer != NULL) goto cont;
fail:
    sub_080C31E0(entity, *(void **)(entity + 0x24));
    return;
cont:
    work->layer->kind = KIND44_SCRIPT_LAYER_KIND;
    work->layer->layer = KIND44_SCRIPT_LAYER_INDEX;
    work->layer->priority = one;
    work->layer->gfxIndex = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].gfxIndex;
    work->layer->affine0 = layerAttrs[0];
    work->layer->affine1 = layerAttrs[1];
    work->layer->affine2 = layerAttrs[2];
    work->layer->affine3 = layerAttrs[3];
    work->layer->palette = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].palette;
    work->layer->sprite = spriteObj;
    *(u16 *)(entity + 2) |= KIND44_SCRIPT_EFFECT_READY;
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
    scriptCallbacks = &gMainObjTimerCallbacks;
    scriptSteps = entity;
    scriptSteps += 0x18;
    sub_080C31E4(scriptSteps, entity + 0x22, (s32)*scriptCallbacks);
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) += 1;
    scriptCommand = scriptSteps + (u32)(*(s16 *)(entity + 0x22)) * 2;
    sub_080C31E0(entity, *(void **)(*(u8 **)(entity + 0x14) + *(u8 *)scriptCommand * 4));
}
