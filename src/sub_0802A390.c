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
extern u32 sScriptStepCallbacks;
extern u8 D_0866DAA0[];
void stepAnimationTrack(void *, void *);
void moveObjectHorizontally(void *, s32, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void sub_08015974(void);
void sub_0802A7A4(void *, void *);
void sub_0802A390(struct Entity *entity)
{
  u8 *sprite = entity->sprite;
  struct Control *control = (struct Control *) entity->control;
  struct Motion *motion = (struct Motion *) entity->motion;
  u8 *animState = ((u8 *) motion) + 0x34;
  if (checkActorViewBounds(sprite, motion) == 1)
  {
    ((void (*)(void *)) entity->callback)(entity);
    return;
  }
  applySpritePaletteVariant(entity, sprite);
  if (sub_08013558(sprite, motion, motion->target) != 0)
  {
    spawnContactEffectOnHit(entity, motion->target);
  }
  if (control->child->mode == 0)
  {
    uploadPendingSpriteGraphic(entity, motion->target);
  }
  if (((motion->flags & 1) != 0) && ((*((u8 *) ((((u8 *) entity) + 0x1A) + (2 * entity->animIndex)))) != 4))
  {
    if (control->child->mode == 0)
    {
      updateActorWorldPosition(entity);
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
    ((void (*)(void *, void *, s32)) sScriptStepCallbacks)(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 4);
  }
  if (updateObjectDisplayState(sprite, motion) == 0)
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
    stepAnimationTrack(sprite, animState);
    moveObjectHorizontally(motion, 0x100000, 0x100000);
  }
  sub_0802A7A4(sprite, motion);
  sub_08013C8C(entity, sprite);
}
