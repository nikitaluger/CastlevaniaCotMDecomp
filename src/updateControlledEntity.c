extern u8 gControlledEntityStepHandlers[];
/* Update a controlled entity: view-cull, resolve hit/link state, advance its
 * script step and motion, then write camera-relative sprite coordinates. */
struct EntityControlChild { u8 _00[6]; u16 mode; };
struct EntityControl { u16 flags; u8 _02[2]; struct EntityControlChild *child; };
struct MotionLinkFlags { u8 _00[2]; u16 flags; };
struct EntityMotion {
    u16 flags; u8 _02[0x26]; void *target; void *cleanupPtr;
    struct MotionLinkFlags *linkFlags; u8 animState[1];
};
struct ControlledEntity {
    u8 _00[2]; u16 flags; u8 _04[0x10]; u32 stepHandlerTable; u8 _18[0x0A];
    s16 stepIndex; u32 callback; u8 _28[0x10]; u8 *sprite; u8 *motion;
    u8 _40[0xAC - 0x40]; struct EntityControl *control;
};
extern u32 gScriptEventCallbacks;
void stepAnimationTrack(void *, void *);
void moveObjectHorizontally(void *, s32, s32);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void freeMotionTracker(void);
void copyFormSpriteOffsets(void *, void *);
void updateControlledEntity(struct ControlledEntity *entity)
{
  u8 *sprite = entity->sprite;
  struct EntityControl *control = (struct EntityControl *) entity->control;
  struct EntityMotion *motion = (struct EntityMotion *) entity->motion;
  u8 *animState = ((u8 *) motion) + 0x34;
  if (checkActorViewBounds(sprite, motion) == 1)
  {
    ((void (*)(void *)) entity->callback)(entity);
    return;
  }
  applySpritePaletteVariant(entity, sprite);
  if (detectActorHit(sprite, motion, motion->target) != 0)
  {
    spawnContactEffectOnHit(entity, motion->target);
  }
  if (control->child->mode == 0)
  {
    uploadPendingSpriteGraphic(entity, motion->target);
  }
  if (((motion->flags & CONTROLLED_MOTION_ACTIVE_FLAG) != 0) && ((*((u8 *) ((((u8 *) entity) + 0x1A) + (2 * entity->stepIndex)))) != CONTROLLED_HIT_STEP))
  {
    if (control->child->mode == 0)
    {
      updateActorWorldPosition(entity);
    }
    else
    {
      if (control != NULL)
      {
        control->flags |= CONTROLLED_CONTROL_BUSY_FLAG;
      }
      if (motion->cleanupPtr != NULL)
      {
        freeMotionTracker();
        motion->cleanupPtr = NULL;
      }
      if (motion->linkFlags != NULL)
      {
        motion->linkFlags->flags |= CONTROLLED_LINK_BUSY_FLAG;
      }
    }
    *((u8 *) ((((u8 *) entity) + 0x1B) + (2 * entity->stepIndex))) = 0;
    ((void (*)(void *, void *, s32)) gScriptEventCallbacks)(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, CONTROLLED_HIT_STEP);
  }
  if (updateObjectDisplayState(sprite, motion) == 0)
  {
    entity->stepHandlerTable = (u32) gControlledEntityStepHandlers;
    *((u16 *) (&entity->stepIndex)) = (*((u16 *) (&entity->stepIndex))) + 1;
    *((u8 *) ((((u8 *) entity) + 0x19) + (2 * entity->stepIndex))) += 1;
    {
      s32 idx2 = 2 * ((s32) (*((s16 *) (&(*entity).stepIndex))));
      u8 *p18 = ((u8 *) entity) + 0x18;
      ((void (*)(void *)) (*((u32 *) (entity->stepHandlerTable + (4 * (*((u8 *) (p18 + idx2))))))))(entity);
    }
    *((u16 *) (&entity->stepIndex)) = (*((u16 *) (&entity->stepIndex))) - 1;
    if (entity->flags & CONTROLLED_ENTITY_SKIP_FLAG)
    {
      return;
    }
    stepAnimationTrack(sprite, animState);
    moveObjectHorizontally(motion, CONTROLLED_MOVE_STEP, CONTROLLED_MOVE_STEP);
  }
  copyFormSpriteOffsets(sprite, motion);
  syncSpriteToWorldPosition(entity, sprite);
}
