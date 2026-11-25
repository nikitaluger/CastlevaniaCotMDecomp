extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void sub_08011674(void *, s32, s32);
extern void sub_08013AC4(void *);
extern void sub_08013C5C(void *, s32);
extern void sub_08013C8C(void *, void *);
extern s32 sub_080141AC(s32, void *);
extern void sub_080142C0(void *, void *);
extern s32 sub_08014F14(s32, void *, void *, void *);
extern void sub_0801534C(void *, void *, void *, void *, void *);
extern s32 sub_0801576C(s32, void *, void *, void *, void *, void *);
extern void sub_0804E470(void *, s32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern u32 D_0866E530[];

/* Per-frame update for a mover entity: reset the two sub-part states, run the
 * view-bounds and two-entity collision checks (which may advance the script),
 * then refresh the sprite animation. */
void sub_0804DFC4(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *motion = *((u8 **) (entity + 0x3C));
  u8 *animState = motion + 0x34;
  u8 *motionExt = motion + 0x48;
  u8 normal = 0;
  u8 translucent;
  u8 *oamParts;
  u8 *partsBase;
  u8 **partPtr;
  s32 i;
  u8 *part;
  s32 res;
  u8 *stateB;
  u8 *stateA;

  oamParts = motion;
  oamParts += 0x50;
  partsBase = motion;
  partsBase += 0x50;
  partPtr = (u8 **) partsBase;
  for (i = 1; i >= 0; i--)
  {
    part = *(partPtr++);
    part[1] = normal;
  }
  if (sub_080141AC(sprite, motion) == 1)
  {
    *((u8 *) (*((u32 *) (motionExt + 0x10)) + 1)) = 0;
    return;
  }
  *((u8 *) (*((u32 *) (motionExt + 0x10)) + 1)) = 5;
  sub_08013C5C(entity, sprite);
  res = sub_08014F14(sprite, motion, *((u32 *) (motion + 0x28)), *((u32 *) (motionExt + 0x10)));
  stateA = motion + 0x2C;
  stateB = motionExt + 0x14;
  if (res != 0)
  {
    sub_0801534C(entity, *((u32 *) (motion + 0x28)), *((u32 *) (motionExt + 0x10)), stateA, stateB);
  }
  sub_080142C0(entity, *((u32 *) (motion + 0x28)));
  sub_080142C0(entity, *((u32 *) (motionExt + 0x10)));
  sub_080142C0(entity, *((u32 *) (motionExt + 0x08)));
  sub_080142C0(entity, *((u32 *) (motionExt + 0x0C)));
  if ((*((u16 *) motion) & 1) != 0)
  {
    u8 *scriptSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (scriptSlot[0x1A] != 2)
    {
      sub_08013AC4(entity);
      sub_08005E80(0x8A);
      {
        u8 *scriptSlot2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        scriptSlot2[0x1B] = 0;
        {
          u32 *scriptDispatch = (u32 *) 0x08671BDC;
          _call_via_r3(entity + 0x18, entity + 0x22, 2, *scriptDispatch);
        }
      }
    }
  }
  if (sub_0801576C(sprite, motion, *((u32 *) (motion + 0x28)), *((u32 *) (motionExt + 0x10)), stateA, stateB) == 0)
  {
    *((u32 *) (entity + 0x14)) = (u32) D_0866E530;
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
      _call_via_r1(entity, *((u32 *)(handlerTable + (command * 4))));
    }
    *((u16 *) (entity + 0x22)) = *((u16 *) (entity + 0x22)) - 1;
    if ((*((u16 *)(entity + 2)) & 0x8000) != 0)
    {
      return;
    }
    sub_080113A8(sprite, animState);
    sub_08011674(motion, 0x200000, 0x200000);
  }
  if ((*((u16 *) motion) & 0x0D) == 0)
  {
    translucent = 1;
    partPtr = (u8 **) oamParts;
    for (i = 1; i >= 0; i--)
    {
      part = *(partPtr++);
      part[1] = translucent;
    }
  }
  sub_0804E470(entity, sprite);
  sub_08013C8C(entity, sprite);
}
