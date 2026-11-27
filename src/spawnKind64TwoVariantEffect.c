struct AnimEntry { s16 animId; s16 _2; };

/* Global graphics flags OR'ed into every newly created sprite. */
extern struct FixedEffectWorkspace gMainWorkspace;
extern struct PairedEffectKindEntry gSpriteKindTable[];
extern u32 gKind64EffectGfxIds[];
extern u8 gKind64EffectTemplateIds[];
extern struct AnimEntry gKind64EffectAnimIds[];
extern u16 gKind64EffectLayerAttrs[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteFromTemplate(void *, void *, u8, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void releaseActorEffectSubObject(void);

/* Spawns the two-variant kind-0x64 effect: allocate the sprite and work block,
 * set up graphics/animation from the per-variant tables, attach one render layer
 * and install the variant's step script. Failures run the saved cleanup callback. */
void spawnKind64TwoVariantEffect(u8 *obj) {
    s32 sprite; struct FixedEffectState *owner; u8 *gfxState; u8 *defaults; u8 *kindPtr; u8 one; s32 animSlot; struct FixedEffectSpriteLayer *layer;
    u32 *gfxTable; s32 kind;
    sprite = (s32)allocSpriteObject();
    if (sprite == 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    *(u32 *)(obj + 0x38) = sprite;
    allocWorkSlot(obj, 0, 0x48, 0);
    if (*(u32 *)(obj + 0x3C) == 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    gfxTable = gKind64EffectGfxIds;
    kindPtr = obj + 0x4C;
    *(u32 *)(sprite + 0x1C) = gfxTable[*(u8 *)kindPtr];
    owner = (struct FixedEffectState *)*(u32 *)(obj + 0x3C);
    gfxState = (u8 *)owner + 0x34;
    installUpdateHandler(obj, (u8 *)owner, releaseActorEffectSubObject);
    owner->kind = 0x64;
    animSlot = findKindIndex(0x64);
    owner->animSlot = animSlot;
    if ((animSlot << 16) < 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    *(u16 *)sprite |= gMainWorkspace.gfxFlags;
    initSpriteFromTemplate((void *)sprite, gfxState, gKind64EffectTemplateIds[*(u8 *)kindPtr], 2);
    setObjectAnimation((void *)sprite, gfxState, gKind64EffectAnimIds[*(u8 *)kindPtr].animId, 0);
    defaults = (u8 *)gKind64EffectLayerAttrs;
    layer = allocEffectPart();
    owner->spriteLayer = layer;
    if (layer == NULL) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }
    layer->active = 5;
    owner->spriteLayer->param2 = 8;
    owner->spriteLayer->param3 = (one = 1);
    owner->spriteLayer->gfxIndex = gSpriteKindTable[*(s16 *)((u8 *)owner + 0x1C)].gfxIndex;
    owner->spriteLayer->anim0 = *(u16 *)(defaults + 0);
    owner->spriteLayer->anim1 = *(u16 *)(defaults + 2);
    owner->spriteLayer->anim2 = *(u16 *)(defaults + 4);
    owner->spriteLayer->anim3 = *(u16 *)(defaults + 6);
    owner->spriteLayer->palette = gSpriteKindTable[*(s16 *)((u8 *)owner + 0x1C)].palette;
    owner->spriteLayer->object = sprite;
    *(u8 *)(obj + 0x50) = 0;
    *(u16 *)(obj + 2) |= 0x1000;
    *(u16 *)(obj + 2) |= 0x800;
    kind = *kindPtr;
    switch (kind) {
    case 0:
        *(u32 *)(obj + 0x14) = 0x080AF1AD;
        *(u16 *)(obj + 0x22) = one;
        sub_080C31E0(obj, (void *)0x080AF1AD);
        break;
    case 1:
        *(u32 *)(obj + 0x14) = 0x080AF28D;
        *(u16 *)(obj + 0x22) = kind;
        sub_080C31E0(obj, (void *)0x080AF28D);
        break;
    }
}
