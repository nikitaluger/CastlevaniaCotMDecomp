/* Spawn a two-layer graphics effect from a main object: allocate a free sprite
 * and work slot, build both render descriptors from the effect tables, set the
 * animations and arm the object's update callback. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteFromTemplate(u8 *, u8 *, s32, s32);
extern void setObjectAnimation(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080AD84C(void);
extern void sub_080AD6BC(void);

/* Main object that owns the spawned effect. */
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x14 - 4];
    u32 updateCb;
    u8 _18[0x22 - 0x18];
    u16 counter;
    u32 failCb;
    u8 _28[0x38 - 0x28];
    u8 *object;
    u8 *effect;
    u8 _40[0x4C - 0x40];
    u8 kind;
    u8 _4D[0x8C - 0x4D];
    u8 spriteOffset;
    u8 _8D[0x94 - 0x8D];
    u8 flagByte;
};
/* Effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[0x1C];
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u8 _24[4];
    void *gfxA;
    u8 _2C[0x48 - 0x2C];
    void *gfxB;
};
/* Graphics/animation descriptor hung off the effect object. */
struct EffectGfx {
    u8 _0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
};
struct GameWorkspace { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GameWorkspace gMainWorkspace;
struct EffectDef { u8 _0[8]; u16 gfxIndex; u16 palette; u8 _C[0x28 - 0xC]; };
extern struct EffectDef gEffectGfxTable[];
struct SpriteEntry { u32 base; };
extern struct SpriteEntry gTwoLayerEffectSpriteBases[];
extern u8 gTwoLayerEffectParams[];
extern s16 gTwoLayerEffectAnimIndices[];
extern u8 gTwoLayerEffectAffineParams[];

void spawnTwoLayerEffectSprite(struct MainObj *obj)
{
    u8 *sprite;
    u8 *dataPtr;
    struct OwnerEffect *owner;
    u8 *kindRef;
    s32 animSlot;
    u32 one;
    u32 eight;
    u8 **dataRef;
    struct SpriteEntry *spriteBases;

    sprite = allocSpriteObject();
    if (sprite == NULL)
    {
        goto fail;
    }
    dataRef = &dataPtr;
    obj->object = sprite;
    allocWorkSlot((u8 *)obj, 0, CHILD_SPRITE_WORK_SLOT_SIZE, 0);
    if (obj->effect == NULL)
    {
        goto fail;
    }
    spriteBases = gTwoLayerEffectSpriteBases;
    kindRef = ((u8 *)obj) + 0x4C;
    *((u32 *)(sprite + 0x1C)) = spriteBases[*kindRef].base + obj->spriteOffset;
    owner = *((struct OwnerEffect * volatile *) (((u8 *)obj) + 0x3C));
    dataPtr = ((u8 *)owner) + 0x34;
    installUpdateHandler((u8 *)obj, (u8 *)owner, sub_080AD84C);
    owner->kind = TWO_LAYER_EFFECT_KIND;
    animSlot = findKindIndex(TWO_LAYER_EFFECT_KIND);
    owner->slot = animSlot;
    if ((animSlot << 16) < 0)
    {
        goto fail;
    }
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    initSpriteFromTemplate(sprite, *dataRef, gTwoLayerEffectParams[*kindRef], 2);
    setObjectAnimation(sprite, dataPtr, gTwoLayerEffectAnimIndices[*kindRef], 0);
    dataPtr = (u8 *)(gTwoLayerEffectAffineParams + ((*kindRef) * 8));
    owner->gfxA = allocEffectPart();
    if (owner->gfxA == NULL)
    {
        goto fail;
    }
    one = 1;
    ((struct EffectGfx *)owner->gfxA)->type = one;
    ((struct EffectGfx *)owner->gfxA)->layer = (eight = 8);
    ((struct EffectGfx *)owner->gfxA)->priority = one;
    ((struct EffectGfx *)owner->gfxA)->gfxIndex = gEffectGfxTable[owner->kind].gfxIndex;
    ((struct EffectGfx *)owner->gfxA)->anim0 = *((u16 *)(dataPtr + 0));
    ((struct EffectGfx *)owner->gfxA)->anim1 = *((u16 *)(dataPtr + 2));
    ((struct EffectGfx *)owner->gfxA)->anim2 = *((u16 *)(dataPtr + 4));
    ((struct EffectGfx *)owner->gfxA)->anim3 = *((u16 *)(dataPtr + 6));
    ((struct EffectGfx *)owner->gfxA)->palette = gEffectGfxTable[owner->kind].palette;
    ((struct EffectGfx *)owner->gfxA)->object = (u32)sprite;
    dataPtr = (u8 *)(gTwoLayerEffectAffineParams + ((*kindRef) * 8));
    owner->gfxB = allocEffectPart();
    if (owner->gfxB != NULL)
    {
        goto secondGfx;
    }
fail:
    sub_080C31E0((u8 *)obj, obj->failCb);
    return;
secondGfx:
    ((struct EffectGfx *)owner->gfxB)->type = one;
    ((struct EffectGfx *)owner->gfxB)->layer = eight;
    ((struct EffectGfx *)owner->gfxB)->priority = one;
    ((struct EffectGfx *)owner->gfxB)->gfxIndex = gEffectGfxTable[owner->kind].gfxIndex;
    ((struct EffectGfx *)owner->gfxB)->anim0 = *((u16 *)(dataPtr + 0));
    ((struct EffectGfx *)owner->gfxB)->anim1 = *((u16 *)(dataPtr + 2));
    ((struct EffectGfx *)owner->gfxB)->anim2 = *((u16 *)(dataPtr + 4));
    ((struct EffectGfx *)owner->gfxB)->anim3 = *((u16 *)(dataPtr + 6));
    ((struct EffectGfx *)owner->gfxB)->palette = gEffectGfxTable[owner->kind].palette;
    ((struct EffectGfx *)owner->gfxB)->object = (u32)sprite;
    obj->flagByte = 0;
    obj->flags |= CHILD_SPRITE_READY;
    obj->flags |= TWO_LAYER_EFFECT_FLAG_B;
    obj->updateCb = (u32)sub_080AD6BC;
    obj->counter = one;
    sub_080C31E0((u8 *)obj, (u32)sub_080AD6BC);
}
