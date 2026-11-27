extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_08019254(u8 *, u8 *);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern void sub_080191DC(void *);

/* Render layer allocated by allocEffectPart and hung off the effect's work state. */
struct EffectGfx {
    u8 mode;          /* 0x00: playback mode */
    u8 renderKind;    /* 0x01 */
    u8 layer;         /* 0x02: 8 */
    u8 priority;      /* 0x03: 1 */
    u16 gfxIndex;     /* 0x04: tile id from gEffectGfxTable */
    u16 affine0;      /* 0x06 */
    u16 affine1;      /* 0x08 */
    u16 affine2;      /* 0x0A */
    u16 affine3;      /* 0x0C */
    u16 palette;      /* 0x0E */
    u32 sprite;       /* 0x10: allocated sprite object */
    u16 tail;         /* 0x14 */
};
/* Effect work state stored in the entity's slot at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;       /* 0x08: 16.16 fixed point */
    s32 worldY;       /* 0x0C */
    u32 radiusA;      /* 0x10 */
    u32 radiusB;      /* 0x14 */
    u32 spawning;     /* 0x18: set to 1 while spawning */
    s16 kind;         /* 0x1C */
    u8 _1E[4];
    s16 animSlot;     /* 0x22 */
    u32 updateCb;     /* 0x24: previous update handler */
    struct EffectGfx *gfx; /* 0x28 */
};
struct MainObj {
    u8 _0[2];
    u16 flags;        /* 0x02 */
    u8 _4[0x22-4];
    s16 index;        /* 0x22 */
    u8 _24[0x38-0x24];
    u8 *sprite;       /* 0x38 */
    struct OwnerEffect *work; /* 0x3C */
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
struct EffectKindEntry { u8 _0[8]; u16 gfxIndex; u16 palette; u8 _A[0x1C]; };
extern struct EffectKindEntry gEffectGfxTable[];
extern u16 gKind55EffectLayerAttrs[];
extern u8 gSpriteAnimDataTable[];

/* Spawn the kind-0x55 graphics effect from a script entity's position parameters:
 * allocate a sprite and work block, install the update handler, build the render
 * layer, place it against the camera scroll, patch variant attributes and resume. */
void spawnKind55Effect(struct MainObj *entity) {
    u8 *sprite;
    struct OwnerEffect *work;
    u8 *animState;
    u8 *layer;
    s32 animSlot;
    u32 oamFlags;
    u32 zero;
    u8 *scrollRows;

    sprite = allocSpriteObject();
    work = NULL;
    animState = NULL;
    animSlot = 0;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, KIND55_EFFECT_WORK_SLOT, 0), work = entity->work, work == NULL) ||
        (animState = (u8 *)work + 0x34, work->updateCb = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = (u32)sub_080191DC,
         work->kind = SPRITE_KIND_FIXED_EFFECT, work->spawning = 1,
         work->worldX = *(s16 *)((u8 *)entity + 0x4C) << 16, work->worldY = *(s16 *)((u8 *)entity + 0x54) << 16,
         animSlot = findKindIndex(SPRITE_KIND_FIXED_EFFECT), work->animSlot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + work->kind * 0xC), layer = allocEffectPart(), work->gfx = (struct EffectGfx *)layer, layer == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    zero = 0;
    work->gfx->renderKind = zero;
    work->gfx->layer = EFFECT_LAYER_KIND;
    work->gfx->priority = EFFECT_LAYER_PRIORITY;
    work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->gfx->affine0 = gKind55EffectLayerAttrs[0];
    work->gfx->affine1 = gKind55EffectLayerAttrs[1];
    work->gfx->affine2 = gKind55EffectLayerAttrs[2];
    work->gfx->affine3 = gKind55EffectLayerAttrs[3];
    work->gfx->palette = gEffectGfxTable[work->kind].palette;
    work->gfx->sprite = (u32)sprite;
    work->gfx->tail = zero;
    oamFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = oamFlags;
    *(u16 *)sprite = oamFlags | gMainWorkspace.flags;
    *(u32 *)(sprite + 0x1C) = KIND55_EFFECT_GFX_ID;
    scrollRows = (u8 *)&gCameraState;
    { u32 offset = BEHAVIOR_SCROLL_X_OFFSET; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(scrollRows + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + BEHAVIOR_SCROLL_BIAS_X) & BEHAVIOR_FRAC_MASK); }
    { u32 offset = BEHAVIOR_SCROLL_Y_OFFSET; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(scrollRows + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + BEHAVIOR_SCROLL_BIAS_Y) & BEHAVIOR_FRAC_MASK); }
    setAnimationFrame(sprite, animState, KIND55_EFFECT_ANIM_FRAME, 0);
    sub_08019254((u8 *)entity, sprite);
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = zero;
    {
        s32 *timerCallbackWord = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *timerCallbackWord);
    }
}
