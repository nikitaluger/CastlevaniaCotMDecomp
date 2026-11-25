extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern s32 sub_08013C2C(void);
extern void sub_08014288(void *, void *, void *);
extern void sub_080AA9C8(void *, void *, s32, s32);
extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
extern u32 D_08671BB0;
struct S_Obj
{
  u8 _0[2];
  u16 flags;
  u8 _1[0x14 - 4];
  u32 handlers;
  u8 _2[0x22 - 0x18];
  s16 stepIndex;
  u32 failHandler;
  u8 _3[0x38 - 0x28];
  u32 sprite;
  u32 motion;
  u8 _4[0x4C - 0x40];
  u32 posX;
  u8 _5[0x5C - 0x50];
  u32 posY;
  u8 _6[0x6C - 0x60];
  s8 direction;
};
struct S_R6
{
  u16 attrs;
  u16 flags;
  u8 _0[0x1C - 4];
  u32 kind;
};
struct S_R4
{
  u8 _0[8];
  u32 x;
  u32 y;
  u8 _1[0x1C - 0x10];
  u16 spriteId;
  u8 _2[0x22 - 0x1E];
  u16 spriteBase;
};

/* Spawns an entity's child sprite, copies its motion/animation setup from a
 * definition object, then advances the entity's step script. */
void sub_080A9A38(struct S_Obj *entity)
{
  struct S_R6 *sprite;
  struct S_R4 *motion;
  u8 *status;
  s32 spriteBase;
  u8 *stepBase;
  u32 v;
  u32 handler;
  s16 stepIndex;
  u16 *stepWords;
  u16 *stepEntry;
  sprite = sub_0800355C();
  if (sprite == NULL)
  {
    goto fail;
  }
  entity->sprite = (u32) sprite;
  sub_0800168C(entity, 0, 0x48, 0);
  if (entity->motion == 0)
  {
    goto fail;
  }
  sprite->kind = 0x8000000B;
  motion = (struct S_R4 *) entity->motion;
  status = ((u8 *) motion) + 0x34;
  sub_08014288(entity, motion, &sub_08097D90);
  motion->spriteId = 0x5F;
  spriteBase = sub_08013C2C();
  motion->spriteBase = spriteBase;
  if ((spriteBase << 16) >= 0)
  {
    goto init;
  }
  fail:
  sub_080C31E0(entity, entity->failHandler);

  return;
  init:
  sprite->attrs = sprite->attrs | D_02025FF0.f18C2;

  motion->x = entity->posX;
  motion->y = entity->posY;
  if (((s8) entity->direction) > 0)
  {
 do { sprite->flags = sprite->flags | 0x10; } while (0);
  }
  sub_080AA9C8(sprite, status, 0xF8, 2);
  sub_080114DC(sprite, status, 0x24, 0);
  entity->flags = entity->flags | 0x1000;
  stepIndex = entity->stepIndex;
  stepWords = (u16 *) entity;
  ((u8 *) (&stepWords[stepIndex]))[0x19] = 0;
  {
    u32 *pbb0 = &D_08671BB0;
    stepBase = ((u8 *) entity) + 0x18;
    sub_080C31E4(stepBase, ((u8 *) entity) + 0x22, *pbb0);
  }
  stepIndex = entity->stepIndex;
  stepWords = (u16 *) entity;
  ((u8 *) (&stepWords[stepIndex]))[0x19] = ((u8 *) (&stepWords[stepIndex]))[0x19] + 1;
  stepIndex = entity->stepIndex;
  stepWords = (u16 *) stepBase;
  stepEntry = &stepWords[stepIndex];
  v = ((u8 *) stepEntry)[0];
  handler = *((u32 *) (((u8 *) entity->handlers) + (v * 4)));
  sub_080C31E0(entity, handler);
}
