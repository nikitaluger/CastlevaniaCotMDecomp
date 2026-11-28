extern void stepAnimationTrack(void *, void *);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 signOf(s32);
extern s32 signedRemainder(s32, s32);
extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 gMainWorkspace[];
extern void *gScriptStepCallbacks;

void sub_08042D58(u8 *mainObj)
{
  u8 *view = *(u8 **) (mainObj + 0x38);
  void *sl = *((void **) (mainObj + 0xAC));
  u8 *st = *(u8 **) (mainObj + 0x3C);
  u8 *anim = st + 0x34;
  u8 *frame = st + 0x48;
  u8 *base = gMainWorkspace;
  s32 *table = (s32 *) (base + (s32) 0x189C);
  s32 sum = *((s32 *) (st + 8)) + *((s32 *) (st + 0xC));
  s32 idx;
  s32 result;
  s32 chunk;
  u16 bits;
  s16 frameCount;

  if (sum < 0)
  {
    sum += 0xFFFF;
  }
  idx = sum >> 16;
  result = signedRemainder(table[0] + idx, 0xB4);
  setAnimationFrame((s32) view, anim, 0, 1);
  if ((result == 0) && ((*((u16 *) (*((void **) (sl + 4)) + 6))) & 3) == 0)
  {
    u16 bits_arm;
    if (signOf(*((s32 *) (st + 8))) > 0)
    {
      bits_arm = *((u16 *) (view + 2)) | 0x10;
    }
    else
    {
      bits_arm = 0;
    }
    *((u16 *) (view + 2)) = bits_arm;
  }
  if (result == 10)
  {
    chunk = sub_08014114(*((s32 *) (st + 8)), *((s32 *) (st + 0xC)) + (s32) 0xFFF00000, 0, 0, 0, 0);
    if (chunk == 1)
    {
      *((u16 *) (frame + 2)) = chunk;
    }
  }
  frameCount = *((s16 *) (frame + 2));
  if (frameCount == 1)
  {
    if (((u32) (result - 10)) <= 0x13)
    {
      u8 *step = (2 * *((s16 *) (mainObj + 0x22))) + mainObj;
      if ((*((u8 *) (step + 0x19)) & frameCount) == 0)
      {
do {
        chunk = *((u16 *) view); bits = chunk & 0xFFF;
        bits |= 0xE000;
        *((u16 *) view) = bits;
} while (0);
}
    }
    if (result == 30)
    {
      *((u16 *) (frame + 2)) = 0;
      {
        u8 *step = (2 * *((s16 *) (mainObj + 0x22))) + mainObj;
        *((u8 *) (step + 0x19)) = 0;
      }
      sub_080C31E8(mainObj + 0x18, mainObj + 0x22, 1, *((s32 *) gScriptStepCallbacks));
    }
  }
}
