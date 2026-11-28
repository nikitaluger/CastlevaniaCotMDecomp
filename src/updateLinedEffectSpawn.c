s32 randomSignedOffset(s32);
s32 sub_08012A94(s32, s32, s32);
void sub_0805077C(s32, s32, s16);
void _call_via_r2(void *, void *, s32);
s32 signedRemainder(s16, s32);

/* Every 12 ticks, place one of ten type-0x142 entities at a tile-spaced X
 * taken from the direction table, snapping its Y to the terrain below and
 * jittering X to match the neighbouring columns; then end the script step. */
void updateLinedEffectSpawn(void *arg0)
{
  s16 dirValue;
  s16 dirValueNeg;
  s16 upperTarget;
  s16 upperTargetNeg;
  s32 clearance;
  s32 halfStep;
  s32 halfStepNeg;
  s32 spawnX;
  s32 baseX;
  s32 xOffset;
  u16 *dirEntry;
  u8 *dirTable;
  s32 *timerCallbacks;
  void *body;
  void *entity;
  s32 stepOffset;
  u16 mask = 1;
  entity = *((void **) (((u8 *) arg0) + 0x3C));
  body = entity + 0x48;
  if ((signedRemainder(*((s16 *) body), 0xC) << 0x10) == 0)
  {
    stepOffset = *((s16 *) (((u8 *) body) + 4)) * 2;
    dirTable = (u8 *)entity + 0x52;
    dirEntry = (u16 *)(dirTable + stepOffset);
    if (*dirEntry & mask)
    {
      dirValue = (s16) (*dirEntry);
      halfStep = ((s32) (dirValue + (((u32) dirValue) >> 0x1F))) >> 1;
      upperTarget = *((s16 *) (((u8 *) body) + 8));
      if (halfStep == (upperTarget + 1))
      {
        xOffset = 0x60000;
      }
      else
        if (halfStep == upperTarget)
      {
        xOffset = 0xFFFA0000;
      }
      else
      {
        xOffset = randomSignedOffset(0x10000) * 4;
      }
      baseX = (*((s32 *) (((u8 *) entity) + 8))) + ((halfStep + 1) * 0x160000);
    }
    else
    {
      dirValueNeg = (s16) (*dirEntry);
      halfStepNeg = ((s32) (dirValueNeg + (((u32) dirValueNeg) >> 0x1F))) >> 1;
      upperTargetNeg = *((s16 *) (((u8 *) body) + 6));
      if (halfStepNeg == (upperTargetNeg + 1))
      {
        xOffset = 0xFFFA0000;
      }
      else
        if (halfStepNeg == upperTargetNeg)
      {
        xOffset = 0x60000;
      }
      else
      {
        xOffset = randomSignedOffset(0x10000) * 4;
      }
      baseX = (*((s32 *) (((u8 *) entity) + 8))) - ((halfStepNeg + 1) * 0x160000);
    }
    spawnX = baseX + xOffset;
    clearance = sub_08012A94(spawnX, *((s32 *) (((u8 *) entity) + 0xC)), 9);
    if (clearance <= 0x3FFFFF)
    {
      sub_0805077C(spawnX, (*((s32 *) (((u8 *) entity) + 0xC))) + clearance, *((s16 *) (((u8 *) entity) + 0x1C)));
    }
    *((s16 *) (((u8 *) body) + 4)) = (*((s16 *) (((u8 *) body) + 4))) + 1;
  }
  *((s16 *) body) = (*((s16 *) body)) + 1;
  if ((*((s16 *) (((u8 *) body) + 4))) > 9)
  {
    *((s16 *) body) = 0xB4;
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
    timerCallbacks = (s32 *)0x08671BB0;
    _call_via_r2(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *timerCallbacks);
  }
}
