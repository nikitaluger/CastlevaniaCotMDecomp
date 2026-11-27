extern void sub_08005E80(s32);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void applySpritePaletteVariant(void *, s32);
extern void sub_08013C8C(void *, void *);
extern s32 checkActorViewBounds(s32, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void sub_0805CA00(void *, void *);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern u32 D_0866E938[];
extern void *gScriptEventCallbacks;

/*
 * Per-frame entity update: clears the semi-transparent flag on its five OAM
 * parts, runs motion/collision and the handler for the current script step,
 * then marks the OAM parts semi-transparent again when the entity is idle.
 */
void sub_0805C6D8(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *motion = *((u8 **) (entity + 0x3C));
  u8 *animState = motion + 0x34;
  u8 normal = 0;
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
  if (sub_08013558(sprite, motion, *((s32 *) (motion + 0x28))) != 0)
  {
    spawnContactEffectOnHit(entity, *((s32 *) (motion + 0x28)));
  }
  uploadPendingSpriteGraphic(entity, *((s32 *) (motion + 0x28)));
  if ((*((u16 *) motion) & 1) != 0)
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (scriptSlot[0x1A] != 1)
    {
      updateActorWorldPosition(entity);
      sub_08005E80(0x85);
      {
        u8 *scriptSlot2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        scriptSlot2[0x1B] = 0;
        {
          u32 *scriptDispatch = (u32 *) 0x08671BDC;
          _call_via_r3(entity + 0x18, entity + 0x22, 1, *scriptDispatch);
        }
      }
    }
  }
  if (updateObjectDisplayState(sprite, motion) == 0)
  {
    *((u32 *) (entity + 0x14)) = (u32) D_0866E938;
    *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) + 1;
    {
      u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
      scriptSlot[0x19] = scriptSlot[0x19] + 1;
    }
    {
      s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
      u8 *scriptBase = entity + 0x18;
      u8 command = *(scriptBase + stepOffset);
      u32 handlerTable = *((u32 *) (entity + 0x14));
      _call_via_r1(entity, *((u32 *) (handlerTable + (command * 4))));
    }
    *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) - 1;
    if ((*((u16 *) (entity + 2)) & 0x8000) != 0)
    {
      return;
    }
    stepAnimationTrack(sprite, animState);
    advanceMotion(motion, 0);
  }
  if ((*((u16 *) motion) & 0x0D) == 0)
  {
    translucent = 1;
    partPtr = (u8 **) oamParts;
    for (i = 4; i >= 0; i--)
    {
      part = *(partPtr++);
      part[1] = translucent;
    }
  }
  sub_0805CA00(entity, sprite);
  sub_08013C8C(entity, sprite);
}
