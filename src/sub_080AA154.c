extern s32 sub_080C31E0(s32, s32);
struct Owner
{
  u8 _0[0x3C];
  u8 *object;
};
struct SoundState
{
  u8 _0[0x20];
  s32 baseLevel[2];
  u8 _1[0x48 - 0x28];
  s32 output;
  u8 _2[0x58 - 0x4C];
  s32 amplitude[2];
  s32 phase[2];
  s32 phaseStep[2];
  s32 phase2[2];
  s32 phaseStep2[2];
};

/* Advance two sound channels' LFO phases and refresh their output levels. */
void sub_080AA154(void *arg0)
{
  struct Owner *owner = arg0;
  u8 *p = owner->object;
  u8 *outAddr;
  u8 *base = p + 0x48;
  u32 i = 0;
  s32 *pWaveFunc = (s32 *) 0x08671BFC;
  u32 j = 0;
  do
  {
    ((struct SoundState *) base)->phase[i] += ((struct SoundState *) base)->phaseStep[i];
    *((s32 *) ((outAddr = (u8 *) (&((struct SoundState *) base)->output)) + j)) = ((struct SoundState *) base)->baseLevel[i] + sub_080C31E0(((struct SoundState *) base)->phase[i], *pWaveFunc);
    ((struct SoundState *) base)->phase2[i] += ((struct SoundState *) base)->phaseStep2[i];
    ((struct SoundState *) base)->amplitude[i] = (sub_080C31E0(((struct SoundState *) base)->phase2[i], *pWaveFunc) >> 6) + (0xC0 << 6);
    j += 0xC;
    i++;
  }
  while (i <= 1);
}
