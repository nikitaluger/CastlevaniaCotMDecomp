s32 sub_080141AC(void *, void *);
s32 signOf(s32);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, s32);
void sub_08013978(void *, s32);
void sub_080142C0(void *, s32);
void sub_08013AC4(void *);
void sub_08005E80(s32);
s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, s32);
void stepAnimationTrack(void *, void *);
void sub_08013C8C(void *, void *);
void _call_via_r3(void *, void *, s32, s32);
struct SpriteFlags { u16 attr; u16 flags; };

/*
 * Updates an entity: runs its state and attack checks, finishes on the death
 * path, otherwise dispatches the handler for the current script step and
 * finally closes out the entity's update.
 */
void sub_08024370(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *motion = *((u8 **) (entity + 0x3C));
  u8 *status = motion + 0x34;
  u8 *motionEx = motion + 0x48;

  if (sub_080141AC(sprite, motion) == 1)
  {
    u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (stepData[0x1A] != 1)
    {
      if (signOf(*((s32 *) (motion + 8))) > 0)
      {
        ((struct SpriteFlags *) sprite)->flags |= 0x10;
      }
      else
      {
        ((struct SpriteFlags *) sprite)->flags &= 0xFFEF;
      }
      return;
    }
  }
  sub_08013C5C(entity, sprite);
  if (sub_08013558(sprite, motion, *((s32 *) (motion + 0x28))) != 0)
  {
    sub_08013978(entity, *((s32 *) (motion + 0x28)));
  }
  sub_080142C0(entity, *((s32 *) (motion + 0x28)));
  if (((*((u16 *) (motion + 0))) & 1) != 0)
  {
    u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (stepData[0x1A] != 2)
    {
      sub_08013AC4(entity);
      sub_08005E80(0x86);
      {
        u8 *stepData2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        stepData2[0x1B] = 0;
        {
          u32 *scriptFn = (u32 *) 0x08671BDC;
          _call_via_r3(entity + 0x18, entity + 0x22, 2, *scriptFn);
        }
      }
    }
  }
  if (updateObjectDisplayState(sprite, motion) != 0)
  {
    goto call_c8c;
  }
  *((u32 *) (entity + 0x14)) = 0x0866D8F8;
  *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) + 1;
  {
    u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    stepData[0x19] = stepData[0x19] + 1;
  }
  {
    s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
    u8 *stepTable = entity + 0x18;
    u8 stepByte = *(stepTable + stepOffset);
    u32 handlerTable = *((u32 *) (entity + 0x14));
    _call_via_r1(entity, *((u32 *) (handlerTable + (stepByte * 4))));
  }
  *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) - 1;
  if (((*((u16 *) (entity + 2))) & 0x8000) != 0)
  {
    return;
  }
  if ((*((s16 *) (motionEx + 2))) == 1)
  {
    stepAnimationTrack(sprite, status);
  }
  call_c8c:
  sub_08013C8C(entity, sprite);
}
