struct SceneFlags
{
  u8 _0[0x18C2];
  u16 f18C2;
};
extern struct SceneFlags gMainWorkspace;
extern u32 gMainObjTimerCallbacks;

struct ScriptEntity
{
  u8 _0[2];
  u16 f02;
  u8 _1[0x14 - 4];
  u32 f14;
  u8 _2[0x22 - 0x18];
  s16 f22;
  u32 f24;
  u8 _3[0x38 - 0x28];
  u32 f38;
  u32 f3C;
};
struct Sprite
{
  u16 f00;
  u8 _0[0x1C - 2];
  u32 f1C;
  u8 _1[0x2A - 0x20];
  u8 f2A;
};
struct Actor
{
  u8 _0[0x1C];
  u16 f1C;
  u8 _1[0x22 - 0x1E];
  u16 f22;
};

extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern s32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void sub_080AA9C8(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

/* Initialise a scripted entity with a fresh sprite, set its actor's action,
 * and run one script step; fall back to the entity's default callback if the
 * sprite/actor is missing or the action roll fails. */
void sub_080A92E0(struct ScriptEntity *entity)
{
  u16 *stepEntry;
  struct Sprite *sprite;
  struct Actor *actor;
  u8 *anim;
  s32 roll;
  u8 *stepBase;
  u32 stepId;
  u32 callback;
  s16 stepIndex;
  u16 *stepArray;

  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto Lend;
  }
  entity->f38 = (u32) sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (entity->f3C == 0)
  {
    goto Lend;
    if (sprite)
    {
    }
  }
  sprite->f2A &= 0xBF;
  actor = (struct Actor *) entity->f3C;
  anim = ((u8 *) actor) + 0x34;
  installUpdateHandler(entity, actor, &releaseActorEffectSubObject);
  actor->f1C = 0x5F;
  roll = findKindIndex();
  actor->f22 = roll;
  if ((roll << 16) >= 0)
  {
    goto Lcont;
  }
  Lend:
  sub_080C31E0(entity, entity->f24);

  return;
  Lcont:
  sprite->f00 = sprite->f00 | gMainWorkspace.f18C2;

  sub_080AA9C8(sprite, anim, 0xE8, 2);
  setObjectAnimation(sprite, anim, 0x1F, 1);
  entity->f02 = entity->f02 | 0x1000;
  stepIndex = entity->f22;
  stepArray = (u16 *) entity;
  ((u8 *) (&stepArray[stepIndex]))[0x19] = 0;
  {
    u32 *scriptCallbacks = &gMainObjTimerCallbacks;
    stepBase = ((u8 *) entity) + 0x18;
    sub_080C31E4(stepBase, ((u8 *) entity) + 0x22, *scriptCallbacks);
  }
  stepIndex = entity->f22;
  stepArray = (u16 *) entity;
  ((u8 *) (&stepArray[stepIndex]))[0x19] = ((u8 *) (&stepArray[stepIndex]))[0x19] + 1;
  stepIndex = (*entity).f22;
  stepArray = (u16 *) stepBase;
  stepEntry = &stepArray[stepIndex];
  stepId = ((u8 *) stepEntry)[0];
  callback = *((u32 *) (((u8 *) entity->f14) + (stepId * 4)));
  sub_080C31E0(entity, callback);
}
