s32 checkActorViewBounds(void *, void *);
s32 signOf(s32);
void applySpritePaletteVariant(void *, void *);
s32 detectActorHit(void *, void *, s32);
void spawnContactEffectOnHit(void *, s32);
void uploadPendingSpriteGraphic(void *, s32);
void updateActorWorldPosition(void *);
void playSound(s32);
s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, s32);
void stepAnimationTrack(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void _call_via_r3(void *, void *, s32, s32);
extern void *gScriptEventCallbacks;
extern u32 gFamiliarEntityStepHandlers[];

/* Sprite OAM attribute 1: bit 0x10 mirrors the sprite horizontally. */
struct SpriteFlags { u16 attr; u16 flags; };

/*
 * Per-frame update of a scripted familiar/weapon entity: while out of camera
 * view, orient its sprite to the world-X direction and leave; otherwise run
 * hit/event handling, dispatch the current script step from the familiar
 * handler table, step its animation, and sync its screen position.
 */
void updateFamiliarEntityTick(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *work = *((u8 **) (entity + 0x3C));
  u8 *animTrack = work + 0x34;
  u8 *stepState = work + 0x48;

  if (checkActorViewBounds(sprite, work) == 1)
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
    if (scriptSlot[0x1A] != 1)
    {
      if (signOf(*((s32 *) (work + 8))) > 0)
      {
        ((struct SpriteFlags *) sprite)->flags |= SPRITE_OAM_FLIP_X;
      }
      else
      {
        ((struct SpriteFlags *) sprite)->flags &= SPRITE_OAM_FLIP_X_CLEAR;
      }
      return;
    }
  }
  applySpritePaletteVariant(entity, sprite);
  if (detectActorHit(sprite, work, *((s32 *) (work + 0x28))) != 0)
  {
    spawnContactEffectOnHit(entity, *((s32 *) (work + 0x28)));
  }
  uploadPendingSpriteGraphic(entity, *((s32 *) (work + 0x28)));
  if (((*((u16 *) (work + 0))) & 1) != 0)
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
    if (scriptSlot[0x1A] != 2)
    {
      updateActorWorldPosition(entity);
      playSound(0x86);
      {
        u8 *scriptSlot2 = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
        scriptSlot2[0x1B] = 0;
        {
          u32 *scriptDispatch = (u32 *) &gScriptEventCallbacks;
          _call_via_r3(entity + SCRIPT_STEP_BASE_OFFSET, entity + SCRIPT_STEP_INDEX_OFFSET, 2, *scriptDispatch);
        }
      }
    }
  }
  if (updateObjectDisplayState(sprite, work) != 0)
  {
    goto call_c8c;
  }
  *((u32 *) (entity + SCRIPT_STEP_TABLE_OFFSET)) = (u32) gFamiliarEntityStepHandlers;
  *((u16 *) (entity + SCRIPT_STEP_INDEX_OFFSET)) = *((u16 *) (entity + SCRIPT_STEP_INDEX_OFFSET)) + 1;
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
    scriptSlot[0x19] = scriptSlot[0x19] + 1;
  }
  {
    s32 stepOffset = (*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2;
    u8 *scriptBase = entity + SCRIPT_STEP_BASE_OFFSET;
    u8 command = *(scriptBase + stepOffset);
    u32 handlerTable = *((u32 *) (entity + SCRIPT_STEP_TABLE_OFFSET));
    _call_via_r1(entity, *((u32 *) (handlerTable + (command * 4))));
  }
  *((u16 *) (entity + SCRIPT_STEP_INDEX_OFFSET)) = *((u16 *) (entity + SCRIPT_STEP_INDEX_OFFSET)) - 1;
  if (((*((u16 *) (entity + 2))) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0)
  {
    return;
  }
  if ((*((s16 *) (stepState + 2))) == 1)
  {
    stepAnimationTrack(sprite, animTrack);
  }
  call_c8c:
  syncSpriteToWorldPosition(entity, sprite);
}
