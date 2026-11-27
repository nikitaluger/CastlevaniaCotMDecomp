extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void updateEffectWithCleanup(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

/* Render layer allocated by allocEffectPart. */
struct PadEffectLayer {
    u8 _0;
    u8 active;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
    u16 timer;
};
/* Work state at the parent's +0x3C. */
struct PadEffectWork {
    u8 _0[8];
    s32 x;
    s32 y;
    u32 f10;
    u32 f14;
    u32 param;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateFn;
    struct PadEffectLayer *layer;
};
/* Parent entity. */
struct PadEntity {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22 - 4];
    s16 index;
    u8 _24[0x38 - 0x24];
    u8 *sprite;
    struct PadEffectWork *work;
    u8 _40[0x4C - 0x40];
    s16 spawnX;
    u8 _4E[6];
    s16 spawnY;
    u8 _56[0x5C - 0x56];
    u32 f5C;
    u8 _60[0x84 - 0x60];
    u16 kind;
};
struct PadGfxEntry { u8 _0[4]; u16 gfxA; u16 gfxB; u8 _8[0x28 - 8]; };
extern struct PadGfxEntry gEffectGfxTable[];
extern u16 gEntityKindEffectAffineParams[];
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallbacks[];
extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;

/* Spawn the kind-selected effect sprite for an entity: allocate a sprite, work state and render part, initialise their graphics/animation and screen position from the entity's spawn coordinates minus camera scroll; on any allocation failure, run the entity's saved update handler. */ void spawnEntityKindEffectSprite(struct PadEntity *entity) {
    u8 *sprite;
    struct PadEffectWork *work;
    u8 *anim;
    u8 *layerBuf;
    s32 slot;
    u32 attrs;
    u32 zeroByte;
    u32 zeroWord;
    u8 *camera;
    s32 *callbacks;

    sprite = allocSpriteObject();
    work = NULL;
    anim = NULL;
    slot = 0;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x4C, 0), work = entity->work, work == NULL) ||
        (anim = (u8 *)work + 0x34,
         work->updateFn = *(u32 *)((u8 *)entity + 0x24),
         *(u32 *)((u8 *)entity + 0x24) = (u32)updateEffectWithCleanup,
         work->kind = entity->kind, zeroByte = 0, zeroWord = 0, work->param = 1,
         work->x = entity->spawnX << 16, work->y = entity->spawnY << 16,
         slot = findKindIndex(work->kind), work->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC),
         layerBuf = allocEffectPart(), work->layer = (struct PadEffectLayer *)layerBuf, layerBuf == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }

    work->layer->active = zeroByte;
    work->layer->layer = 8;
    work->layer->priority = 1;
    work->layer->gfxIndex = gEffectGfxTable[work->kind].gfxA;
    work->layer->anim0 = gEntityKindEffectAffineParams[0];
    work->layer->anim1 = gEntityKindEffectAffineParams[1];
    work->layer->anim2 = gEntityKindEffectAffineParams[2];
    work->layer->anim3 = gEntityKindEffectAffineParams[3];
    work->layer->palette = gEffectGfxTable[work->kind].gfxB;
    work->layer->object = (u32)sprite;
    work->layer->timer = zeroByte;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 off = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(camera + off + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 off = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(camera + off + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    work->f10 = *(u32 *)((u8 *)entity + 0x5C);
    work->f14 = zeroWord;
    setAnimationFrame(sprite, anim, 0x18, 1);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = zeroWord;
    callbacks = gMainObjTimerCallbacks;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbacks);
}
