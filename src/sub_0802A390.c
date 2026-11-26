/* Update this entity type: view-cull, resolve collision/death flags, advance
 * the state script and motion, then write camera-relative screen coordinates. */
struct ControlChild { u8 _00[6]; u16 mode; };
struct Control { u16 flags; u8 _02[2]; struct ControlChild *child; };
struct LinkFlags { u8 _00[2]; u16 flags; };
struct Motion {
    u16 flags; u8 _02[0x26]; void *target; void *cleanupPtr; struct LinkFlags *linkFlags; u8 unk34[1];
};
struct Entity {
    u8 _00[2]; u16 flags; u8 _04[0x10]; u32 stateTable; u8 _18[0x0A]; s16 animIndex; u32 callback; u8 _28[0x10]; u8 *sprite; u8 *motion; u8 _40[0xAC - 0x40]; struct Control *control;
};
extern u32 D_08671BDC;
extern u8 D_0866DAA0[];
void sub_080113A8(void *, void *);
void moveObjectHorizontally(void *, s32, s32);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
void sub_08015974(void);
void sub_0802A7A4(void *, void *);
void sub_0802A390(struct Entity *entity)
{
  u8 *sprite = entity->sprite;
  struct Control *control = (struct Control *) entity->control;
  struct Motion *motion = (struct Motion *) entity->motion;
  u8 *animState = ((u8 *) motion) + 0x34;
  if (sub_080141AC(sprite, motion) == 1)
  {
    ((void (*)(void *)) entity->callback)(entity);
    return;
  }
  sub_08013C5C(entity, sprite);
  if (sub_08013558(sprite, motion, motion->target) != 0)
  {
    sub_08013978(entity, motion->target);
  }
  if (control->child->mode == 0)
  {
    sub_080142C0(entity, motion->target);
  }
  if (((motion->flags & 1) != 0) && ((*((u8 *) ((((u8 *) entity) + 0x1A) + (2 * entity->animIndex)))) != 4))
  {
    if (control->child->mode == 0)
    {
      sub_08013AC4(entity);
    }
    else
    {
      if (control != NULL)
      {
        control->flags |= 4;
      }
      if (motion->cleanupPtr != NULL)
      {
        sub_08015974();
        motion->cleanupPtr = NULL;
      }
      if (motion->linkFlags != NULL)
      {
        motion->linkFlags->flags |= 2;
      }
    }
    *((u8 *) ((((u8 *) entity) + 0x1B) + (2 * entity->animIndex))) = 0;
    ((void (*)(void *, void *, s32)) D_08671BDC)(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 4);
  }
  if (sub_08013B5C(sprite, motion) == 0)
  {
    entity->stateTable = (u32) D_0866DAA0;
    *((u16 *) (&entity->animIndex)) = (*((u16 *) (&entity->animIndex))) + 1;
    *((u8 *) ((((u8 *) entity) + 0x19) + (2 * entity->animIndex))) += 1;
    {
      s32 idx2 = 2 * ((s32) (*((s16 *) (&(*entity).animIndex))));
      u8 *p18 = ((u8 *) entity) + 0x18;
      ((void (*)(void *)) (*((u32 *) (entity->stateTable + (4 * (*((u8 *) (p18 + idx2))))))))(entity);
    }
    *((u16 *) (&entity->animIndex)) = (*((u16 *) (&entity->animIndex))) - 1;
    if (entity->flags & 0x8000)
    {
      return;
    }
    sub_080113A8(sprite, animState);
    moveObjectHorizontally(motion, 0x100000, 0x100000);
  }
  sub_0802A7A4(sprite, motion);
  sub_08013C8C(entity, sprite);
}
