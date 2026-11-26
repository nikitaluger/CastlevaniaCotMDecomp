struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _04[0x10];
  u32 dispatchTable;
  u8 _18[0xA];
  s16 scriptStep;
  u32 callback;
  u8 _28[0x10];
  u32 sprite;
  u32 gfxState;
  u8 _40[0xC];
  u8 kind;
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
  s16 kind;
  u8 _1E[4];
  u16 animSlot;
  u32 savedHandler;
  u32 part0;
  u8 _2C[0x1C];
  u32 part1;
  u32 part2;
};
struct Sprite
{
  u16 oamAttr;
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
extern u8 gSpriteLayerAttrs[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallback;

/* Builds a scripted multi-part object's graphics: allocates its sprite and work
 * state, sets up animation and two render layers from the kind attribute tables,
 * positions the sprite against the camera scroll, marks the entity ready, then
 * runs the entity's final script callback. */
void initScriptedMultiPartGraphics(struct Entity *entity)
{
  struct Sprite *sprite;
  struct GfxState *gfxState;
  u8 *animState;
  u8 *layerPtrs;
  u8 *layerAttrs;
  u8 *gfxAttrs;
  u32 spriteAttr;
  u32 animSlot;
  s16 scriptStep;
  u8 *layerAttrs2;
  u32 one;

  sprite = (struct Sprite *)allocSpriteObject();
  if (sprite == NULL)
    goto fail;
  entity->sprite = (u32)sprite;
  allocWorkSlot(entity, 0, 0x50, 0);
  if (entity->gfxState == 0)
    goto fail;
  sprite->gfxId = MULTI_PART_SPRITE_GFX_ID;
  gfxState = (struct GfxState *)entity->gfxState;
  animState = (u8 *)(0x34 + (u32)gfxState);
  layerPtrs = (u8 *)gfxState + 0x48;
  installUpdateHandler(entity, gfxState, (void *)sub_08035D6C);
  gfxState->kind = MULTI_PART_SPRITE_KIND;
  animSlot = findKindIndex();
  gfxState->animSlot = (u16)animSlot;
  if (((s16)((u16)animSlot)) < 0)
    goto fail;
  spriteAttr = ((u32)(((s32)((s16)gfxState->animSlot)) << 6)) + (0x80 << 2);
  spriteAttr |= (animSlot + 8) << 12;
  sprite->oamAttr = (u16)spriteAttr;
  {
    u8 *scratch = gMainWorkspace;
    spriteAttr |= *((u16 *)(scratch + 0x18C2));
  }
  sprite->oamAttr = (u16)spriteAttr;
  initSpriteGraphics(sprite, animState, (void *)gMultiPartAnimData);
  sub_08011344(sprite, animState, 0x11, 0);
  layerAttrs = gSpriteLayerAttrs;
  gfxState->part1 = (u32)allocEffectPart();
  if (gfxState->part1 == 0)
    goto fail;
  ((u8 *)gfxState->part1)[1] = 0;
  ((u8 *)gfxState->part1)[2] = 8;
  ((u8 *)gfxState->part1)[3] = (u8)(one = 1);
  {
    u8 *firstLayer = (u8 *)gfxState->part1;
    gfxAttrs = gEffectGfxTable;
    ((struct SpriteLayer *)firstLayer)->attr0 = ((struct AttrEntry *)(gfxAttrs + (((s32)gfxState->kind) * 40)))->attr0;
  }
  ((struct SpriteLayer *)gfxState->part1)->attr1 = *((u16 *)(&layerAttrs[0]));
  ((struct SpriteLayer *)gfxState->part1)->attr2 = *((u16 *)(&layerAttrs[2]));
  ((struct SpriteLayer *)gfxState->part1)->attr3 = *((u16 *)(&layerAttrs[4]));
  ((struct SpriteLayer *)gfxState->part1)->attr4 = *((u16 *)(&layerAttrs[6]));
  ((struct SpriteLayer *)gfxState->part1)->attr5 = ((struct AttrEntry *)(gfxAttrs + (((s32)gfxState->kind) * 40)))->attr1;
  *(u32 *)(gfxState->part1 + 0x10) = (u32)sprite;
  layerAttrs2 = layerAttrs + 8;
  *(u32 *)(layerPtrs + 4) = (u32)allocEffectPart();
  if (*(u32 *)(layerPtrs + 4) != 0)
    goto success;
fail:
  sub_080C31E0(entity, entity->callback);
  return;
success:
  ((u8 *)*(u32 **)(layerPtrs + 4))[1] = 0;
  ((u8 *)*(u32 **)(layerPtrs + 4))[2] = 8;
  ((u8 *)*(u32 **)(layerPtrs + 4))[3] = (u8)one;
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr0 = ((struct AttrEntry *)(gfxAttrs + (((s32)gfxState->kind) * 40)))->attr0;
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr1 = *((u16 *)(&layerAttrs[8]));
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr2 = *((u16 *)(&layerAttrs2[2]));
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr3 = *((u16 *)(&layerAttrs2[4]));
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr4 = *((u16 *)(&layerAttrs2[6]));
  ((struct SpriteLayer *)*(u32 **)(layerPtrs + 4))->attr5 = ((struct AttrEntry *)(gfxAttrs + (((s32)gfxState->kind) * 40)))->attr1;
  *(u32 *)((u8 *)*(u32 **)(layerPtrs + 4) + 0x10) = (u32)sprite;
  {
    u8 *camera = gCameraState;
    u8 *scrollIndexPtr = gMainWorkspace;
    u8 *scrollX;
    u8 *scrollY;
    u32 scrollIndex;
    scrollIndexPtr += 0x18A8;
    scrollIndex = ((u32)*scrollIndexPtr + 1) * 0x40;
    scrollX = camera + 0x1278;
    sprite->x = gfxState->x - ((*(u32 *)(scrollX + scrollIndex) + 0x8000) & 0xFFFF0000);
    scrollIndex = ((u32)*scrollIndexPtr + 1) * 0x40;
    scrollY = camera + 0x127C;
    sprite->y = gfxState->y - ((*(u32 *)(scrollY + scrollIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= MULTI_PART_SPRITE_READY;
  scriptStep = *((s16 *)(((u8 *)entity) + 0x22));
  *((((u8 *)entity) + (((s32)scriptStep) * 2)) + 0x19) = 0;
  {
    u32 *timerTable = &gMainObjTimerCallback;
    u8 *scriptData = ((u8 *)entity) + 0x18;
    u8 *stepPtr = ((u8 *)entity) + 0x22;
    sub_080C31E4(scriptData, stepPtr, *timerTable);
    {
      s16 step = *((s16 *)stepPtr);
      u8 *command = (u8 *)((((s32)step) * 2) + (u32)entity);
      command[0x19] = (u8)(command[0x19] + 1);
    }
    {
      s16 step2 = *((s16 *)stepPtr);
      u8 *scriptWord = scriptData + (((s32)step2) * 2);
      sub_080C31E0(entity, *((u32 *)((((u32)(*scriptWord)) * 4) + entity->dispatchTable)));
    }
  }
}
