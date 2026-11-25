extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C2E68(void *, u32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern u8 D_081007D8[];

/* Each frame, spawn two particle objects whose offsets come from a fixed table
 * and whose positions are jittered randomly; when the countdown ends, reset
 * it and dispatch the script callback. */
void sub_08093924(u8 *arg0)
{
  u8 *entity = arg0;
  int yJitterRange;
  int tableShift;
  u8 *sprite;
  u8 *motion;
  u8 *animTrack;
  u8 offsets[0x40];
  u8 *offsets2;
  s32 i;
  int yBias;
  s32 rawIndex;
  long posShift;
  s32 signedIndex;
  s32 byteOffset;
  s32 xOffset;
  s32 yOffset;
  s32 xPos;
  s32 yPos;
  s32 heading;
  s32 duration;
  int xBias;
  u32 newFrame;
  sprite = *((u8 **) (entity + 0x38));
  motion = *((u8 **) (entity + 0x3C));
  animTrack = motion + 0x34;
  if ((*((s16 *) (animTrack + 0xC))) <= 3)
  {
    *((u8 *) ((*((u8 **) (animTrack + 4))) + 1)) = 0;
    *((u8 *) (sprite + 0x2A)) &= 0xBF;
  }
  sub_080C2E68(offsets, (u32) D_081007D8, 0x40);
  i = 0;
  offsets2 = offsets + 4;
  do
  {
    yBias = 0xFFFC0000;
    rawIndex = ((*((s16 *) (animTrack + 0xC))) * 2) + i;
    signedIndex = rawIndex;
    if (rawIndex < 0)
    {
      signedIndex = rawIndex + 7;
    }
    tableShift = 3;
    byteOffset = 3;
    posShift = 19;
    byteOffset = (rawIndex - ((signedIndex >> 3) << 3)) << 3;
    xOffset = *((u32 *) (offsets + byteOffset));
    yOffset = *((u32 *) (offsets2 + byteOffset));
    xBias = 0xFFF40000;
    xPos = ((*((u32 *) (motion + 8))) + sub_0800583C(0x80 << 11)) + ((xOffset << posShift) + xBias);
    yJitterRange = (0x80 << 7) << 4;
    yPos = ((*((u32 *) (motion + 0xC))) + sub_0800583C(yJitterRange)) + ((yOffset << posShift) + yBias);
    heading = sub_08005820(0x80 << 6) + (0x80 << 4);
    {
      s32 cond = (((*((s16 *) (animTrack + 0xC))) * 2) + i) & 3;
      duration = 1;
      if (cond != 0)
        duration = 0;
    }
    sub_0808E348(xPos, yPos, 0, heading, 0x80 << 7, duration, 8);
    i++;
  }
  while (i <= 1);
  newFrame = (*((u16 *) (animTrack + 0xC))) - 1;
  *((u16 *) (animTrack + 0xC)) = newFrame;
  if (((s32) (newFrame << 16)) <= 0)
  {
    *((u16 *) (animTrack + 0xC)) = 0xB4;
    *((u8 *) ((entity + (((u32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x17)) = 0;
    {
      u32 *pl = (u32 *) 0x08671BB4;
      sub_080C31E4(entity + 0x18, entity + 0x22, *pl);
    }
  }
}
