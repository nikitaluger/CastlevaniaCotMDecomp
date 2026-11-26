struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _04[0x10];
  u32 x;
  u8 _18[0xA];
  s16 childIndex;
  u32 callback;
  u8 _28[0x10];
  u32 sprite;
  u32 state;
  u8 _40[0xC];
  u8 typeParam;
  u8 _4D[0xF];
  u32 param1;
  u8 _60[0xC];
  u32 param2;
  u8 _70[0xC];
  u32 param3;
};
struct GfxState
{
  u8 _0[8];
  u32 x;
  u32 y;
  u32 z;
  u8 _14[8];
  s16 spriteType;
  u8 _1E[4];
  u16 attrIndex;
  u32 prevLink;
  u32 reserved28;
  u8 _2C[0x1C];
  u32 layer1;
  u32 _4C;
};
struct Sprite
{
  u16 attr;
  u8 _02[0x12];
  u32 x;
  u32 y;
  u32 gfxId;
};
struct SpriteLayer
{
  u8 b0, b1, b2, b3;
  u16 attr0, attr1, attr2, attr3, attr4, attr5;
  u32 sprite;
};
struct AttrEntry
{
  u8 _pad[4];
  u16 attr0, attr1;
  u8 _08[0x20];
};
void *allocSpriteObject(void);
void allocWorkSlot(void *, u32, u32, u32);
void installUpdateHandler(void *, void *, void *);
s32 findKindIndex(void);
void initSpriteGraphics(void *, void *, void *);
void sub_08011344(void *, void *, u32, u32);
void *allocEffectPart(void);
void sub_08035D6C(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
extern u8 gEffectGfxTable[];
extern u8 gMultiPartAnimData[];
extern u8 D_080CEE58[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallback;

/* Builds an entity's graphics: allocates a sprite and graphics state, sets up
 * animation and two sprite layers from the type tables, positions the sprite,
 * then runs the entity's final callback. */
void initScriptedMultiPartGraphics(struct Entity *a)
{
  struct Sprite *sprite;
  struct GfxState *state;
  u8 *anim;
  u8 *layerSlot;
  u8 *params;
  u8 *attrs;
  u32 attr;
  u32 spriteIndex;
  s16 childIndex;
  u8 *params2;
  u32 one;

  sprite = (struct Sprite *)allocSpriteObject();
  if (sprite == NULL)
    goto fail;
  a->sprite = (u32)sprite;
  allocWorkSlot(a, 0, 0x50, 0);
  if (a->state == 0)
    goto fail;
  sprite->gfxId = 0x8000000A;
  state = (struct GfxState *)a->state;
  anim = (u8 *)(0x34 + (u32)state);
  layerSlot = (u8 *)state + 0x48;
  installUpdateHandler(a, state, (void *)sub_08035D6C);
  state->spriteType = 0x19;
  spriteIndex = findKindIndex();
  state->attrIndex = (u16)spriteIndex;
  if (((s16)((u16)spriteIndex)) < 0)
    goto fail;
  attr = ((u32)(((s32)((s16)state->attrIndex)) << 6)) + (0x80 << 2);
  attr |= (spriteIndex + 8) << 12;
  sprite->attr = (u16)attr;
  {
    u8 *workBase = gMainWorkspace;
    attr |= *((u16 *)(workBase + 0x18C2));
  }
  sprite->attr = (u16)attr;
  initSpriteGraphics(sprite, anim, (void *)gMultiPartAnimData);
  sub_08011344(sprite, anim, 0x11, 0);
  params = D_080CEE58;
  state->layer1 = (u32)allocEffectPart();
  if (state->layer1 == 0)
    goto fail;
  ((u8 *)state->layer1)[1] = 0;
  ((u8 *)state->layer1)[2] = 8;
  ((u8 *)state->layer1)[3] = (u8)(one = 1);
  {
    u8 *layer = (u8 *)state->layer1;
    attrs = gEffectGfxTable;
    ((struct SpriteLayer *)layer)->attr0 = ((struct AttrEntry *)(attrs + (((s32)state->spriteType) * 40)))->attr0;
  }
  ((struct SpriteLayer *)state->layer1)->attr1 = *((u16 *)(&params[0]));
  ((struct SpriteLayer *)state->layer1)->attr2 = *((u16 *)(&params[2]));
  ((struct SpriteLayer *)state->layer1)->attr3 = *((u16 *)(&params[4]));
  ((struct SpriteLayer *)state->layer1)->attr4 = *((u16 *)(&params[6]));
  ((struct SpriteLayer *)state->layer1)->attr5 = ((struct AttrEntry *)(attrs + (((s32)state->spriteType) * 40)))->attr1;
  *(u32 *)(state->layer1 + 0x10) = (u32)sprite;
  params2 = params + 8;
  *(u32 *)(layerSlot + 4) = (u32)allocEffectPart();
  if (*(u32 *)(layerSlot + 4) != 0)
    goto success;
fail:
  sub_080C31E0(a, a->callback);
  return;
success:
  ((u8 *)*(u32 **)(layerSlot + 4))[1] = 0;
  ((u8 *)*(u32 **)(layerSlot + 4))[2] = 8;
  ((u8 *)*(u32 **)(layerSlot + 4))[3] = (u8)one;
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr0 = ((struct AttrEntry *)(attrs + (((s32)state->spriteType) * 40)))->attr0;
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr1 = *((u16 *)(&params[8]));
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr2 = *((u16 *)(&params2[2]));
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr3 = *((u16 *)(&params2[4]));
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr4 = *((u16 *)(&params2[6]));
  ((struct SpriteLayer *)*(u32 **)(layerSlot + 4))->attr5 = ((struct AttrEntry *)(attrs + (((s32)state->spriteType) * 40)))->attr1;
  *(u32 *)((u8 *)*(u32 **)(layerSlot + 4) + 0x10) = (u32)sprite;
  {
    u8 *coordBase = gCameraState;
    u8 *workPtr = gMainWorkspace;
    u8 *xTable;
    u8 *yTable;
    u32 coordIndex;
    workPtr += 0x18A8;
    coordIndex = ((u32)*workPtr + 1) * 0x40;
    xTable = coordBase + 0x1278;
    sprite->x = state->x - ((*(u32 *)(xTable + coordIndex) + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*workPtr + 1) * 0x40;
    yTable = coordBase + 0x127C;
    sprite->y = state->y - ((*(u32 *)(yTable + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  a->flags |= 0x1000;
  childIndex = *((s16 *)(((u8 *)a) + 0x22));
  *((((u8 *)a) + (((s32)childIndex) * 2)) + 0x19) = 0;
  {
    u32 *dataPtr = &gMainObjTimerCallback;
    u8 *stateArr = ((u8 *)a) + 0x18;
    u8 *indexPtr = ((u8 *)a) + 0x22;
    sub_080C31E4(stateArr, indexPtr, *dataPtr);
    {
      s16 child2 = *((s16 *)indexPtr);
      u8 *entry = (u8 *)((((s32)child2) * 2) + (u32)a);
      entry[0x19] = (u8)(entry[0x19] + 1);
    }
    {
      s16 child3 = *((s16 *)indexPtr);
      u8 *q = stateArr + (((s32)child3) * 2);
      sub_080C31E0(a, *((u32 *)((((u32)(*q)) * 4) + a->x)));
    }
  }
}
