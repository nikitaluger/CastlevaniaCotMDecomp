struct EntityDef { u8 _0[4]; void *coords; };
struct AnimBuf { u16 f0; u8 _2[0x12]; u32 f14; u32 f18; u32 f1C; };
struct SpriteLayer { u8 _0; u8 byte1; u8 byte2; u8 byte3; u16 attr0; u16 attr1; u16 attr2; u16 attr3; u16 attr4; u16 attr5; void *sprite; u16 flags14; };
struct GfxState { u8 _0[8]; u32 x; u32 y; u8 _10[8]; s32 animFlag; u8 _1C[8]; s32 savedCb; struct SpriteLayer *layer; };
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
extern s16 gEntityDefinitionAnimFrames[];
extern s32 gMainObjTimerCallbacks[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void*, s32, s32, s32);
extern void initSpriteGraphics(void*, void*, void*);
extern void setAnimationFrame(void*, void*, s16, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void*, s32);
extern void sub_080C31E4(void*, void*, s32);
extern void sub_0805E238(void);

/* Builds an entity's graphics: allocates a sprite and gfx state, picks a pose
 * from a table, fills a sprite layer, positions the sprite, then updates child
 * bookkeeping. */
void createEntityFromDefinition(struct Entity *entity) {
    struct EntityDef *def;
    void *sprite;
    struct GfxState *gfx;
    void *anim;
    s16 *coords;
    u32 poseIndex;
    s16 *poseTable;
    s32 *lit;
    u8 *work;

    def = entity->def;
    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;
    entity->sprite = (u32)sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    gfx = entity->gfxState;
    if (gfx == 0)
        goto fail;
    anim = (u8*)gfx + 0x34;
    gfx->savedCb = entity->callback;
    entity->callback = (u32)sub_0805E238;
    gfx->animFlag = 1;
    coords = (s16*)def->coords;
    gfx->x = (s32)coords[0] << 16;
    gfx->y = (s32)coords[1] << 16;
    initSpriteGraphics(sprite, anim, (void*)0x080D0094);
    poseTable = gEntityDefinitionAnimFrames;
    poseIndex = *(u16*)((u8*)def->coords + 6) & 0xF;
    setAnimationFrame(sprite, anim, poseTable[poseIndex], 1);
    gfx->layer = allocEffectPart();
    if (gfx->layer != 0)
        goto body;
fail:
    sub_080C31E0(entity, entity->callback);
    goto end;
body:
    gfx->layer->byte1 = 4;
    gfx->layer->byte2 = 0x80;
    gfx->layer->byte3 = 0;
    gfx->layer->attr0 = 0;
    gfx->layer->attr1 = 5;
    gfx->layer->attr2 = 5;
    gfx->layer->attr3 = 0;
    gfx->layer->attr4 = 0xFFFA;
    gfx->layer->attr5 = 0;
    gfx->layer->sprite = sprite;
    gfx->layer->flags14 = 0;
    *(u16*)sprite |= gMainWorkspace.f18C2;
    ((struct AnimBuf*)sprite)->f1C = 0x80000007;
    {
        u8 *base = (u8 *)&gCameraState;
        { u32 k = 0x1278; *(u32 *)((u8 *)sprite + 0x14) = gfx->x - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 k = 0x127C; *(u32 *)((u8 *)sprite + 0x18) = gfx->y - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }
    entity->flags = (u16)(entity->flags | 0x1000);
    *(u8*)((u8*)entity + 0x19 + 2*entity->childIndex) = 0;
    lit = gMainObjTimerCallbacks;
    work = (u8*)entity + 0x18;
    sub_080C31E4(work, &entity->childIndex, *lit);
    *(u8*)((u8*)entity + 0x19 + 2*entity->childIndex) = (u8)(*(u8*)((u8*)entity + 0x19 + 2*entity->childIndex) + 1);
    work += entity->childIndex * 2;
    sub_080C31E0(entity, *(u32*)(entity->callbackTable + 4*(*work)));
end:
    return;
}
