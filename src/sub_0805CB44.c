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
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02021E90[];
extern void *sub_0800355C(void);
extern void sub_0800168C(void*, s32, s32, s32);
extern void sub_0801131C(void*, void*, void*);
extern void sub_08011368(void*, void*, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void*, s32);
extern void sub_080C31E4(void*, void*, s32);
extern void sub_0805CEA0(void);
extern s32 D_08671BB0[];

/* Builds an entity's graphics: allocates a sprite and gfx state, fills a sprite
 * layer, positions the sprite, then updates the entity's child bookkeeping. */
void sub_0805CB44(struct Entity *entity) {
    struct EntityDef *def;
    void *sprite;
    struct GfxState *gfx;
    void *stateTmp;
    u8 *work;
    s16 *coords;
    u32 kind;
    s32 *lit;

    def = entity->def;
    sprite = sub_0800355C();
    if (sprite == 0)
        goto fail;
    entity->sprite = (u32)sprite;
    sub_0800168C(entity, 0, 0x24, 0);
    stateTmp = entity->gfxState;
    if (stateTmp == 0)
        goto fail;
    gfx = stateTmp;
    work = (u8 *)gfx + 0x10;
    gfx->savedCb = entity->callback;
    entity->callback = (u32)sub_0805CEA0;
    coords = (s16*)def->coords;
    gfx->x = (s32)coords[0] << 16;
    gfx->y = (s32)coords[1] << 16;
    sub_0801131C(sprite, work, (void*)0x080D0008);
    kind = *(u16 *)entity & 0x3FFF;
    switch (kind) {
    case 0x1DE: sub_08011368(sprite, work, 0x42, 1); break;
    case 0x1DF: sub_08011368(sprite, work, 0x46, 1); break;
    }
    gfx->layer = sub_08016190();
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
    *(u16 *)sprite |= D_02025FF0.f18C2;
    ((struct AnimBuf*)sprite)->f1C = 0x8000000E;
    {
        u8 *base = (u8 *)&D_02021E90;
        { u32 k = 0x1278; *(u32 *)((u8 *)sprite + 0x14) = gfx->x - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 k = 0x127C; *(u32 *)((u8 *)sprite + 0x18) = gfx->y - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }
    entity->flags = (u16)(entity->flags | 0x1000);
    *(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) = 0;
    lit = D_08671BB0;
    work = (u8 *)entity + 0x18;
    sub_080C31E4(work, &entity->childIndex, *lit);
    *(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) = (u8)(*(u8 *)((u8 *)entity + 0x19 + 2*entity->childIndex) + 1);
    work += entity->childIndex * 2;
    sub_080C31E0(entity, *(u32*)(entity->callbackTable + 4*(*work)));
end:
    return;
}
