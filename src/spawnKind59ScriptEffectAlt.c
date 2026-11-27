extern struct FixedEffectWorkspace gMainWorkspace;
extern struct Kind59GfxEntry gEffectGfxTable[];
extern u16 gKind59LayerAttrs[];
extern char gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

struct Kind59Actor {
    u16 f0;
    u16 flags;         /* 0x02: KIND59_EFFECT_READY */
    u8 _4[0x14 - 0x4];
    void *scriptTable; /* 0x14: script command handler table */
    u8 f18;
    u8 f19;
    u8 _1A[0x22 - 0x1A];
    s16 step;          /* 0x22: current script-step index */
    void *cleanup;     /* 0x24: cleanup callback */
    u8 _28[0x38 - 0x28];
    void *sprite;      /* 0x38 */
    void * volatile work; /* 0x3C */
    u8 _40[0xC];
    u32 spawnX;        /* 0x4C */
    u8 _50[0xC];
    u32 spawnY;        /* 0x5C */
    u8 _60[0xC];
    s32 filler;
};

/*
 * Builds the kind-0x59 script effect: allocates the sprite and work state,
 * installs the per-frame updater, seeds the render layer from the shared
 * kind/layer tables, then clears and advances the script step.
 */
void spawnKind59ScriptEffectAlt(struct Kind59Actor *actor) {
    s32 sprite;
    struct Kind59EffectWork *work;
    u8 *animState;
    u16 *layerAttrs;
    u32 kindIndex;
    u8 *scriptPtr;
    void **timerCallbacks;
    u8 *stepEntry;
    u32 zero;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->sprite = (void *)sprite;
    allocWorkSlot(actor, 0, KIND59_EFFECT_WORK_SIZE, 0);
    if (actor->work == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = KIND59_EFFECT_GFX_ID;
    work = (struct Kind59EffectWork *)actor->work;
    animState = ((u8 *)work) + 0x34;
    installUpdateHandler(actor, (u8 *)work, updateActorEffectSubObject);
    zero = 0;
    work->kind = KIND59_EFFECT_KIND;
    work->x = actor->spawnX;
    work->y = actor->spawnY;
    kindIndex = findKindIndex(KIND59_EFFECT_KIND);
    work->animSlot = kindIndex;
    if ((s16)kindIndex < 0) goto fail;
    kindIndex = work->animSlot;
    kindIndex = kindIndex << 6;
    kindIndex = kindIndex + 0x200;
    kindIndex &= 0xFC0;
    *((u16 *)sprite) = kindIndex;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    initSpriteGraphics((void *)sprite, animState, (work->kind * 0xC) + ((u32)KIND59_EFFECT_ANIM_TABLE));
    setAnimationFrame((void *)sprite, animState, KIND59_EFFECT_ANIM_FRAME, 1);
    *((u16 *)((u8 *)sprite + 2)) |= 0x400;
    layerAttrs = gKind59LayerAttrs;
    work->layer = allocEffectPart();
    if (work->layer == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->cleanup);
    return;
ok:
    work->layer->active = zero;
    work->layer->layer = 8;
    work->layer->priority = 1;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->layer->anim0 = layerAttrs[0];
    work->layer->anim1 = layerAttrs[1];
    work->layer->anim2 = layerAttrs[2];
    work->layer->anim3 = layerAttrs[3];
    work->layer->palette = gEffectGfxTable[work->kind].palette;
    work->layer->sprite = (void *)sprite;
    actor->flags |= KIND59_EFFECT_READY;
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = zero;
    }
    timerCallbacks = &gMainObjTimerCallbacks;
    scriptPtr = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, (s32)(*timerCallbacks));
    {
        s16 idx = actor->step;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
        idx = actor->step;
        stepEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(actor, *((void **)(actor->scriptTable + ((*stepEntry) * 4))));
    }
}
