extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 palette; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallback;
struct Entity {
  u8 _0[2]; u16 flags; u8 _1[0x14 - 4]; u32 stepHandlers; u8 _2[0x22 - 0x18];
  s16 stepIndex; u32 failHandler; u8 _3[0x38 - 0x28]; u32 sprite; u32 motion;
  u8 _4[0x4C - 0x40]; u32 posX; u8 _5[0x5C - 0x50]; u32 posY;
};
struct Sprite { u16 attrs; u16 flags; u8 _0[0x1C - 4]; u32 kind; };
struct Motion {
  u8 _0[8]; u32 x; u32 y; u8 _1[0x14 - 0x10]; u32 base;
  u8 _2[0x1C - 0x18]; s16 spriteIndex; u8 _3[0x22 - 0x1E]; s16 spriteBase;
};

/*
 * Spawns and initializes an entity's child sprite: allocates the object, sets
 * its pose and position from the entity, then starts the entity's script at
 * its first step handler.
 */
void sub_0809FF70(struct Entity *entity)
{
  struct Sprite *sprite;
  struct Motion *motion;
  u8 *status;
  s32 spriteBase;
  u8 *stepBase;
  u32 handler;
  s16 stepIdx;
  u16 *words;
  u16 *stepPtr;
  sprite = (struct Sprite *) allocSpriteObject();
  if (sprite == NULL) goto Lend;
  entity->sprite = (u32) sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (entity->motion == 0) goto Lend;
  sprite->kind = 0x8000000B;
  motion = (struct Motion *) entity->motion;
  status = ((u8 *) motion) + 0x34;
  motion->spriteIndex = 0x4C;
  spriteBase = findKindIndex();
  motion->spriteBase = (s16) spriteBase;
  if (((s32) (((u32) spriteBase) << 16)) >= 0) goto Lcont;
Lend:
  sub_080C31E0(entity, entity->failHandler);
  return;
Lcont:
  spriteBase = motion->spriteBase;
  spriteBase <<= 6;
  spriteBase += 0x200;
  spriteBase &= 0xFC0;
  sprite->attrs = spriteBase;
  sprite->attrs = sprite->attrs | gMainWorkspace.palette;
  motion->x = entity->posX;
  motion->y = entity->posY;
  motion->base = 0xFFFF8000;
  sprite->flags = sprite->flags | 0x400;
  initSpriteGraphics(sprite, status, (void *)(0x080CD400 + (u32)motion->spriteIndex * 12));
  setAnimationFrame(sprite, status, 0x0D, 0);
  entity->flags = entity->flags | 0x1000;
  stepIdx = entity->stepIndex;
  words = (u16 *)entity;
  ((u8 *)(&words[stepIdx]))[0x19] = 0;
  {
    u32 *scriptTable = &gMainObjTimerCallback;
    stepBase = ((u8 *)entity) + 0x18;
    sub_080C31E4(stepBase, ((u8 *)entity) + 0x22, *scriptTable);
  }
  stepIdx = entity->stepIndex;
  words = (u16 *)entity;
  ((u8 *)(&words[stepIdx]))[0x19] = ((u8 *)(&words[stepIdx]))[0x19] + 1;
  stepIdx = entity->stepIndex;
  words = (u16 *)stepBase;
  stepPtr = &words[stepIdx];
  handler = *((u32 *)(((u8 *)entity->stepHandlers) + (((u8 *)stepPtr)[0] * 4)));
  sub_080C31E0(entity, handler);
}
