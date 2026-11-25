extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_08013C5C(void *, s32);
extern void sub_08013C8C(void *, void *);
extern s32 sub_080141AC(s32, void *);
extern void sub_080142C0(void *, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_0803E4A8(void *, void *);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern u32 D_0866E038[];

/* Per-frame update for a scripted actor: cull it outside the camera view, refresh its
 * sprite flags and graphics, spawn contact effects, run one script command, apply
 * distance-based translucency, and copy its world position into the sprite. */
void sub_0803E198(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *work = *((u8 **) (entity + 0x3C));
  u8 *animTrack = work + 0x34;
  u8 partFlag = 0;
  u8 translucent;
  u8 *spriteParts;
  s32 partIndex;
  u8 *partObj;

  spriteParts = work;
  spriteParts += 0x4C;
  {
    u8 *partAddr;
    u8 **partSlot;
    partAddr = work;
    partAddr += 0x4C;
    partSlot = (u8 **) partAddr;
    for (partIndex = 1; partIndex >= 0; partIndex--)
    {
      partObj = *(partSlot++);
      partObj[1] = partFlag;
    }
  }
  if (sub_080141AC(sprite, work) == 1)
  {
    return;
  }
  sub_08013C5C(entity, sprite);
  if (sub_08013558(sprite, work, *((u32 *) (work + 0x28))) != 0)
  {
    sub_08013978(entity, *((u32 *) (work + 0x28)));
  }
  sub_080142C0(entity, *((u32 *) (work + 0x28)));
  {
    u8 **partPtr = (u8 **) spriteParts;
    for (partIndex = 1; partIndex >= 0; partIndex--)
    {
      sub_080142C0(entity, *(partPtr++));
    }
  }
  if ((*((u16 *) work) & 1) != 0)
  {
    u8 *actionSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (actionSlot[0x1A] != 2)
    {
      sub_08013AC4(entity);
      sub_08005E80(0x85);
      {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        stepSlot[0x1B] = 0;
        {
          u32 *eventTable = (u32 *) 0x08671BDC;
          _call_via_r3(entity + 0x18, entity + 0x22, 2, *eventTable);
        }
      }
    }
  }
  if (sub_08013B5C(sprite, work) == 0)
  {
    *((u32 *) (entity + 0x14)) = (u32) D_0866E038;
    *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) + 1;
    {
      u8 *stepSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
      stepSlot[0x19] = stepSlot[0x19] + 1;
    }
    {
      s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
      u8 *scriptBase = entity + 0x18;
      u8 command = *(scriptBase + stepOffset);
      u32 handlerTable = *((u32 *) (entity + 0x14));
      _call_via_r1(entity, *((u32 *)(handlerTable + (command * 4))));
    }
    *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) - 1;
    if ((*((u16 *)(entity + 2)) & 0x8000) != 0)
    {
      return;
    }
    sub_080113A8(sprite, animTrack);
    sub_08011EE8(work, 0x16C1, 0);
  }
  if ((*((u16 *) work) & 0x0D) == 0)
  {
    u16 spriteDist = *((u16 *) (sprite + 0x28));
    spriteDist = spriteDist - 0x10;
    if (spriteDist <= 0x10)
    {
      translucent = 1;
      {
        u8 **partPtr = (u8 **) spriteParts;
        for (partIndex = 1; partIndex >= 0; partIndex--)
        {
          partObj = *(partPtr++);
          partObj[1] = translucent;
        }
      }
    }
  }
  sub_0803E4A8(entity, sprite);
  sub_08013C8C(entity, sprite);
}
