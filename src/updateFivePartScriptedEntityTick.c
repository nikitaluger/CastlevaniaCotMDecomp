extern void playSound(u16);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 detectActorHit(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void applySpritePaletteVariant(void *, s32);
extern void syncSpriteToWorldPosition(void *, void *);
extern s32 checkActorViewBounds(s32, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void applyFivePartSpriteAttributes(void *, void *);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern u32 gFivePartEntityStepHandlers[];
extern void *gScriptEventCallbacks;

/*
 * Per-frame update of a scripted entity built from five OAM render parts:
 * clear the parts' translucency, run motion/collision and the current script
 * step's handler, then fade the parts again when the entity is idle.
 */
void updateFivePartScriptedEntityTick(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *motion = *((u8 **) (entity + 0x3C));
  u8 *animState = motion + 0x34;
  u8 normal = FIVE_PART_PART_ALPHA_OPAQUE;
  u8 translucent;
  u8 *oamParts;
  u8 *partsBase;
  u8 **partPtr;
  s32 i;
  u8 *part;

  oamParts = motion;
  oamParts += 0x84;
  partsBase = motion;
  partsBase += 0x84;
  partPtr = (u8 **) partsBase;
  for (i = 4; i >= 0; i--)
  {
    part = *(partPtr++);
    part[1] = normal;
  }
  if (checkActorViewBounds(sprite, motion) == 1)
  {
    return;
  }
  applySpritePaletteVariant(entity, sprite);
  if (detectActorHit(sprite, motion, *((s32 *) (motion + 0x28))) != 0)
  {
    spawnContactEffectOnHit(entity, *((s32 *) (motion + 0x28)));
  }
  uploadPendingSpriteGraphic(entity, *((s32 *) (motion + 0x28)));
  if ((*((u16 *) motion) & 1) != 0)
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
    if (scriptSlot[0x1A] != 1)
    {
      updateActorWorldPosition(entity);
      playSound(FIVE_PART_STEP_END_SFX);
      {
        u8 *scriptSlot2 = (u8 *)((u32)(*(s16 *)(entity + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)entity);
        scriptSlot2[0x1B] = 0;
        {
          u32 *scriptDispatch = (u32 *) &gScriptEventCallbacks;
          _call_via_r3(entity + SCRIPT_STEP_BASE_OFFSET, entity + SCRIPT_STEP_INDEX_OFFSET, 1, *scriptDispatch);
        }
      }
    }
  }
  if (updateObjectDisplayState(sprite, motion) == 0)
  {
    *((u32 *) (entity + SCRIPT_STEP_TABLE_OFFSET)) = (u32) gFivePartEntityStepHandlers;
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
    if ((*((u16 *) (entity + 2)) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0)
    {
      return;
    }
    stepAnimationTrack(sprite, animState);
    advanceMotion(motion, 0);
  }
  if ((*((u16 *) motion) & FIVE_PART_ACTIVE_FLAGS) == 0)
  {
    translucent = FIVE_PART_PART_ALPHA_FADE;
    partPtr = (u8 **) oamParts;
    for (i = 4; i >= 0; i--)
    {
      part = *(partPtr++);
      part[1] = translucent;
    }
  }
  applyFivePartSpriteAttributes(entity, sprite);
  syncSpriteToWorldPosition(entity, sprite);
}
