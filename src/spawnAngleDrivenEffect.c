struct S_02025FF0 { u8 _0[0x18C2]; u16 spriteFlags; };
extern struct S_02025FF0 gMainWorkspace;
struct SpriteLayer { u8 _0, byte1, byte2, byte3; u16 attr0, attr1, attr2, attr3, attr4; s16 attr5; u32 sprite; };
struct GfxState {
    u8 _0[8]; u32 x, y, worldX, worldY; u8 _18[4]; u16 spriteType; u8 _1E[4]; u16 attrIndex; u8 _24[4];
    struct SpriteLayer *layer;
};
struct AttrEntry { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x20]; };
extern struct AttrEntry gEffectGfxTable[];
extern u16 gAngleEffectLayerAttrs[];
extern s32 gTrigFuncTable;
extern s32 gMainObjTimerCallbacks;

extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_080AA9C8(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern struct SpriteLayer *allocEffectPart(void);
extern u16 divideInt(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

/* Builds an entity's graphics: allocates a sprite and gfx state, sets their
 * position and attributes, fills a sprite layer, then updates child
 * bookkeeping. */
void spawnAngleDrivenEffect(u8 *entity) {
    u8 *sprite;
    struct GfxState *state;
    u8 *anim;
    s32 *tablePtr;
    s32 spriteIndex;
    u16 *attrTable;
    u8 *childArray;
    s32 *lit;
    u8 *child;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(u32 *)(entity + 0x38) = (u32)sprite;
    allocWorkSlot(entity, 0, ANGLE_EFFECT_WORK_SLOT, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = SCRIPT_OBJECT_GFX_ID;
    state = (struct GfxState *)*(u8 **)(entity + 0x3C);
    anim = (u8 *)state + 0x34;
    installUpdateHandler(entity, (u8 *)state, releaseActorEffectSubObject);
    state->spriteType = ANGLE_EFFECT_KIND;
    state->x = *(u32 *)(entity + 0x4C);
    state->y = *(u32 *)(entity + 0x5C);
    tablePtr = &gTrigFuncTable;
    state->worldX = (sub_080C31E0(*(s32 *)(entity + 0x6C) + 0x4000, *tablePtr) >> 8) * ANGLE_EFFECT_POS_SCALE;
    state->worldY = (sub_080C31E0(*(s32 *)(entity + 0x6C), *tablePtr) >> 8) * ANGLE_EFFECT_POS_SCALE;
    spriteIndex = findKindIndex(*(s16 *)((u8 *)state + 0x1C));
    state->attrIndex = spriteIndex;
    if ((spriteIndex << 16) < 0) goto fail;
    *(u16 *)sprite |= gMainWorkspace.spriteFlags;
    sub_080AA9C8(sprite, anim, 0xD4, 6);
    setObjectAnimation(sprite, anim, 0x16, 0);
    attrTable = gAngleEffectLayerAttrs;
    state->layer = allocEffectPart();
    if (state->layer != NULL) goto cont;
fail:
    sub_080C31E0((s32)entity, *(s32 *)(entity + 0x24));
    return;
cont:
    state->layer->byte1 = 1;
    state->layer->byte2 = 8;
    state->layer->byte3 = 1;
    state->layer->attr0 = gEffectGfxTable[*(s16 *)((u8 *)state + 0x1C)].f4;
    state->layer->attr1 = attrTable[0];
    state->layer->attr2 = attrTable[1];
    state->layer->attr3 = attrTable[2];
    state->layer->attr4 = attrTable[3];
    state->layer->attr5 = gEffectGfxTable[*(s16 *)((u8 *)state + 0x1C)].f6;
    state->layer->sprite = (u32)sprite;
    if (*(u8 *)(entity + 0x7C) != 0) {
        state->layer->attr5 = divideInt(state->layer->attr5 * 5, 4);
    }
    *(u16 *)(entity + 2) |= EFFECT_SPRITE_READY;
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
    lit = &gMainObjTimerCallbacks;
    childArray = entity;
    childArray += 0x18;
    sub_080C31E4(childArray, entity + 0x22, *lit);
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) += 1;
    child = childArray + (u32)(*(s16 *)(entity + 0x22)) * 2;
    sub_080C31E0((s32)entity, *(s32 *)(*(u8 **)(entity + 0x14) + *(u8 *)child * 4));
}
