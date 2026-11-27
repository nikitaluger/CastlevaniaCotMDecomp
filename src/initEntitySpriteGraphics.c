struct EntityDef { u8 _0[4]; s16 *coords; };
struct SpriteLayer { u8 _0; u8 byte1; u8 byte2; u8 byte3; u16 attr0; u16 attr1; u16 attr2; u16 attr3; u16 attr4; u16 attr5; void *sprite; u16 flags14; };
struct AnimBuf { u16 f0; u8 _2[0x12]; u32 f14; u32 f18; u32 f1C; };
struct GfxState { s32 x; s32 y; u32 savedCb; struct SpriteLayer *layer; };
struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _4[0x10];
    u32 callbackTable;
    u8 _18[0x0A];
    s16 childIndex;
    u32 callback;
    u8 _28[0x10];
    u32 sprite;
    u32 gfxState;
    u8 _40[0x6C];
    void *def;
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gCameraState[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void*, s32, s32, s32);
extern void initSpriteGraphics(void*, void*, void*);
extern void setAnimationFrame(void*, void*, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void*, s32);       /* indirect cleanup callback */
extern void sub_080C31E4(void*, void*, s32); /* indirect script handler */
extern void updateEntitySprite(void);
extern s32 gScriptStepCallbackTable[];

/* Builds an entity's graphics from its definition: allocates a sprite, gfx
 * state and render layer, picks the start frame from the entity kind, places
 * the sprite against the camera, then advances the entity's script. */
void initEntitySpriteGraphics(struct Entity *entity) {
    struct EntityDef *def;
    void *sprite;
    struct GfxState *gfx;
    void *stateTmp;
    u8 *work;
    s16 *coords;
    u32 kind;
    s32 *lit;

    def = entity->def;
    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;
    entity->sprite = (u32)sprite;
    allocWorkSlot(entity, 0, ENTITY_SPRITE_WORK_SLOT, 0);
    stateTmp = entity->gfxState;
    if (stateTmp == 0)
        goto fail;
    gfx = stateTmp;
    work = (u8 *)gfx + 0x10;
    gfx->savedCb = entity->callback;
    entity->callback = (u32)updateEntitySprite;
    coords = (s16*)def->coords;
    gfx->x = (s32)coords[0] << 16;
    gfx->y = (s32)coords[1] << 16;
    initSpriteGraphics(sprite, work, (void*)gEntitySpriteAnimTable);
    kind = *(u16 *)entity & ENTITY_SPRITE_KIND_MASK;
    switch (kind) {
    case ENTITY_SPRITE_KIND_A: setAnimationFrame(sprite, work, ENTITY_SPRITE_ANIM_A, 1); break;
    case ENTITY_SPRITE_KIND_B: setAnimationFrame(sprite, work, ENTITY_SPRITE_ANIM_B, 1); break;
    }
    gfx->layer = allocEffectPart();
    if (gfx->layer != 0)
        goto body;
fail:
    sub_080C31E0(entity, entity->callback);
    goto end;
body:
    gfx->layer->byte1 = 4;
    gfx->layer->byte2 = 8;
    gfx->layer->byte3 = 0;
    gfx->layer->attr0 = 0;
    gfx->layer->attr1 = 4;
    gfx->layer->attr2 = 6;
    gfx->layer->attr3 = 0;
    gfx->layer->attr4 = 0xFFF9;
    gfx->layer->attr5 = 0;
    gfx->layer->sprite = sprite;
    gfx->layer->flags14 = 0;
    *(u16 *)sprite |= gMainWorkspace.f18C2;
    ((struct AnimBuf*)sprite)->f1C = ENTITY_SPRITE_GFX_ID;
    {
        u8 *base = (u8 *)&gCameraState;
        { u32 k = 0x1278; *(u32 *)((u8 *)sprite + 0x14) = gfx->x - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 k = 0x127C; *(u32 *)((u8 *)sprite + 0x18) = gfx->y - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }
    entity->flags = (u16)(entity->flags | ENTITY_SPRITE_READY);
    *(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) = 0;
    lit = gScriptStepCallbackTable;
    work = (u8 *)entity + 0x18;
    sub_080C31E4(work, &entity->childIndex, *lit);
    *(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) = (u8)(*(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) + 1);
    work += entity->childIndex * 2;
    sub_080C31E0(entity, *(u32*)(entity->callbackTable + 4*(*work)));
end:
    return;
}
