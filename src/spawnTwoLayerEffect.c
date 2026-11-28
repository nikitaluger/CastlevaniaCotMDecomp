/* Workspace word at +0x18C2 holds the spawned sprite's OAM attribute bits. */
struct TwoLayerEffectWorkspace
{
  u8 _0[0x18C2];
  u16 gfxFlags;
};
extern struct TwoLayerEffectWorkspace gMainWorkspace;

/* Kind table holds the tile ids used by the render layer. */
extern struct AttackEffectKindEntry gSpriteKindTable[];
/* Four affine/OAM words copied into the render layer. */
extern u16 gTwoLayerEffectAffineWords[];

extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteFromTemplate(void *, void *, u8, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void releaseActorEffectSubObject(void);

/* Spawns the two-layer effect: allocate the owner sprite and its work slot,
 * initialise the graphics slot from a sprite template, fill the render layer
 * from the kind table, then arm the entity's update handler. Any allocation or
 * kind-lookup failure instead invokes the entity's cleanup callback. */
void spawnTwoLayerEffect(u8 *entity)
{
  s32 spriteHandle;
  struct KindEffectWork *work;
  u8 *anim;
  int zero;
  u8 one;
  s32 tableIndex;
  u16 *affineWords;
  struct KindEffectLayer *layer;

  spriteHandle = (s32) allocSpriteObject();
  zero = 0;
  if (spriteHandle == zero)
  {
    goto fail;
  }
  *((u32 *) (entity + 0x38)) = spriteHandle;
  allocWorkSlot(entity, zero, 0x48, zero);
  if ((*((u32 *) (entity + 0x3C))) == zero)
  {
    goto fail;
  }
  *((u32 *) (spriteHandle + 0x1C)) = TWO_LAYER_SPRITE_KIND;
  work = (struct KindEffectWork *) (*((u8 **) (entity + 0x3C)));
  anim = ((u8 *) work) + 0x34;
  installUpdateHandler(entity, (u8 *) work, releaseActorEffectSubObject);
  work->kind = TWO_LAYER_EFFECT_KIND;
  tableIndex = findKindIndex(TWO_LAYER_EFFECT_KIND);
  work->slot = tableIndex;
  if ((tableIndex << 16) < zero)
  {
    goto fail;
  }
  *((u16 *) spriteHandle) |= gMainWorkspace.gfxFlags;
  initSpriteFromTemplate((void *) spriteHandle, anim, TWO_LAYER_TEMPLATE_INDEX, 8);
  setObjectAnimation((void *) spriteHandle, anim, TWO_LAYER_ANIM_ID, zero);
  affineWords = gTwoLayerEffectAffineWords;
  layer = allocEffectPart();
  work->layer = layer;
  if (layer != NULL)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(entity, *((void **) (entity + 0x24)));

  return;
  cont:
  layer->active = RENDER_PART_KIND;

  work->layer->layer = EFFECT_LAYER_KIND;
  work->layer->priority = (one = EFFECT_LAYER_PRIORITY);
  work->layer->gfxA = gSpriteKindTable[work->kind].gfxA;
  work->layer->affine0 = affineWords[zero];
  work->layer->affine1 = affineWords[1];
  work->layer->affine2 = affineWords[2];
  work->layer->affine3 = affineWords[3];
  work->layer->gfxB = gSpriteKindTable[work->kind].gfxB;
  work->layer->object = spriteHandle;
  *((u16 *) (entity + 2)) |= EFFECT_SPRITE_READY;
  *((u16 *) (entity + 2)) |= TWO_LAYER_EFFECT_FLAG_B;
  *((u32 *) (entity + 0x14)) = TWO_LAYER_UPDATE_CALLBACK;
  *((u16 *) (entity + 0x22)) = one;
  sub_080C31E0(entity, TWO_LAYER_UPDATE_CALLBACK);
}
