extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_08014668(u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern void sub_0802A030(void);

struct EffectGfx {
    u8 _0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
    u16 tail;
};
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;
    s32 worldY;
    u32 radiusA;
    u32 radiusB;
    u32 active;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateCb;
    struct EffectGfx *gfx;
    u8 _2C[0x1C];
    u16 timer;
    u16 timerMax;
};
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 scriptStep;
    u8 _24[0x38-0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C-0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
    u8 _56[0x6C-0x56];
    u32 scriptTable;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 renderFlags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollTable gCameraState;
struct EffectDef { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x20]; };
extern struct EffectDef gEffectGfxTable[];
extern u16 gKind2CLayerAttrs[];
extern u8 gSpriteAnimDataTable[];

/* Spawns a timed effect for an object: allocates its sprite and work state,
 * fills its single render part, places it in world/screen space, gives it a
 * lifetime and a radius from the object's script table, then advances the
 * object's script. */
void spawnKind2CEffect(struct MainObj *owner) {
    u8 *sprite;
    struct OwnerEffect *effect;
    u8 *animState;
    struct EffectGfx *renderPart;
    s32 slot;
    u32 spriteAttr;
    u8 *camera;
    s32 *valueTable;
    s32 *timerTable;
    u16 *lifetime;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    _call_via_r1((u8 *)owner, *(s32 *)((u8 *)owner + 0x24));
    return;
ok0:
    owner->object = sprite;
    allocWorkSlot((u8 *)owner, 0, 0x4C, 0);
    effect = owner->effect;
    if (effect == NULL) goto fail;
    animState = (u8 *)effect + 0x34;
    effect->updateCb = *(u32 *)((u8 *)owner + 0x24);
    *(u32 *)((u8 *)owner + 0x24) = (u32)sub_0802A030 + 1;
    effect->kind = EFFECT_KIND_TIMED;
    effect->active = 1;
    effect->worldX = owner->posX << 16;
    effect->worldY = owner->posY << 16;
    slot = findKindIndex(EFFECT_KIND_TIMED);
    effect->slot = slot;
    if ((s32)(slot << 16) < 0) goto fail;
    initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + effect->kind * 0xC);
    renderPart = allocEffectPart();
    effect->gfx = renderPart;
    if (renderPart == NULL) goto fail;
    goto fields;
fail:
    _call_via_r1((u8 *)owner, *(s32 *)((u8 *)owner + 0x24));
    return;
fields:
    effect->gfx->type = 0;
    effect->gfx->layer = 8;
    effect->gfx->priority = 1;
    effect->gfx->gfxIndex = gEffectGfxTable[effect->kind].gfxIndex;
    effect->gfx->anim0 = gKind2CLayerAttrs[0];
    effect->gfx->anim1 = gKind2CLayerAttrs[1];
    effect->gfx->anim2 = gKind2CLayerAttrs[2];
    effect->gfx->anim3 = gKind2CLayerAttrs[3];
    effect->gfx->palette = gEffectGfxTable[effect->kind].palette;
    effect->gfx->object = (u32)sprite;
    effect->gfx->tail = 0;
    spriteAttr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)effect + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)effect + 0x22) + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = effect->worldX - ((*(u32 *)(camera + xOff + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = effect->worldY - ((*(u32 *)(camera + yOff + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    lifetime = (u16 *)((u8 *)effect + 0x48);
    { u16 initialTimer = EFFECT_TIMER_INITIAL; *lifetime = initialTimer; }
    lifetime[1] = EFFECT_TIMER_INTERVAL;
    valueTable = (s32 *)0x08671BFC;
    effect->radiusA = (u32)((s64)_call_via_r1((u8 *)owner->scriptTable + 0x4000, *valueTable) * 3);
    effect->radiusB = (u32)((s64)_call_via_r1((u8 *)owner->scriptTable, *valueTable) * 3);
    *(u16 *)((u8 *)effect + 4) = 2;
    sub_08014668(sprite, effect->radiusA);
    setAnimationFrame(sprite, animState, 0x0B, 1);
    owner->flags |= 0x1000;
    *(u8 *)((u8 *)owner + 2 * owner->scriptStep + 0x19) = 0;
    timerTable = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)owner + 0x18, (u8 *)owner + 0x22, *timerTable);
}
