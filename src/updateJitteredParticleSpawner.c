extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void spawnType207Effect(s32, s32, s32, s32, s32, s32, s32);
extern void copyBytes(void *, u32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern u8 gParticleSpawnOffsets[];

/* Spawns two jittered type-0x207 particles around the owner each frame; when
 * the countdown expires it resets the timer and fires the script callback. */
void updateJitteredParticleSpawner(u8 *entity)
{
  int yJitterRange;
  int tableShift;
  u8 *sprite;
  u8 *workState;
  u8 *animTrack;
  u8 offsets[0x40];
  u8 *yOffsets;
  s32 particleIndex;
  int yBias;
  s32 offsetIndex;
  long positionShift;
  s32 wrappedIndex;
  s32 tableOffset;
  s32 xOffset;
  s32 yOffset;
  s32 spawnX;
  s32 spawnY;
  s32 heading;
  s32 duration;
  int xBias;
  u32 framesLeft;
  sprite = *((u8 **) (entity + 0x38));
  workState = *((u8 **) (entity + 0x3C));
  animTrack = workState + 0x34;
  if ((*((s16 *) (animTrack + 0xC))) <= 3)
  {
    *((u8 *) ((*((u8 **) (animTrack + 4))) + 1)) = 0;
    *((u8 *) (sprite + 0x2A)) &= 0xBF;
  }
  copyBytes(offsets, (u32) gParticleSpawnOffsets, 0x40);
  particleIndex = 0;
  yOffsets = offsets + 4;
  do
  {
    yBias = 0xFFFC0000;
    offsetIndex = ((*((s16 *) (animTrack + 0xC))) * 2) + particleIndex;
    wrappedIndex = offsetIndex;
    if (offsetIndex < 0)
    {
      wrappedIndex = offsetIndex + 7;
    }
    tableShift = 3;
    tableOffset = 3;
    positionShift = 19;
    tableOffset = (offsetIndex - ((wrappedIndex >> 3) << 3)) << 3;
    xOffset = *((u32 *) (offsets + tableOffset));
    yOffset = *((u32 *) (yOffsets + tableOffset));
    xBias = 0xFFF40000;
    spawnX = ((*((u32 *) (workState + 8))) + randomSignedOffset(0x80 << 11)) + ((xOffset << positionShift) + xBias);
    yJitterRange = (0x80 << 7) << 4;
    spawnY = ((*((u32 *) (workState + 0xC))) + randomSignedOffset(yJitterRange)) + ((yOffset << positionShift) + yBias);
    heading = scaleByRandom(0x80 << 6) + (0x80 << 4);
    {
      s32 slotKind = (((*((s16 *) (animTrack + 0xC))) * 2) + particleIndex) & 3;
      duration = 1;
      if (slotKind != 0)
        duration = 0;
    }
    spawnType207Effect(spawnX, spawnY, 0, heading, 0x80 << 7, duration, 8);
    particleIndex++;
  }
  while (particleIndex <= 1);
  framesLeft = (*((u16 *) (animTrack + 0xC))) - 1;
  *((u16 *) (animTrack + 0xC)) = framesLeft;
  if (((s32) (framesLeft << 16)) <= 0)
  {
    *((u16 *) (animTrack + 0xC)) = 0xB4;
    *((u8 *) ((entity + (((u32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x17)) = 0;
    {
      u32 *callbackSlot = (u32 *) 0x08671BB4;
      sub_080C31E4(entity + 0x18, entity + 0x22, *callbackSlot);
    }
  }
}
