extern s32 sub_0809C4E8(s32, u8, s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);

/* Derive a stereo-pan gain pair from a sound's phase (mirrored when a flag is
 * clear) and store it, with the sound type, into a voice object. */
void sub_0809C510(void *sound, s32 voice, u8 soundType)
{
  s32 cosGain;
  s32 *pWaveFunc;
  u16 phase;
  if (sound != NULL)
  {
    phase = (*((u16 *) (((s8 *) sound) + 0x7C))) + 0x1000;
    if (!(0x10 & (*((u16 *) (((s8 *) (*((void **) (((s8 *) sound) + 0x38)))) + 2)))))
    {
      phase = 0x8000 - phase;
    }
    pWaveFunc = (s32 *) 0x08671BFC;
    cosGain = (*((s32 *) (((s8 *) sound) + 0x4C))) + ((sub_080C31E0(phase + 0x4000, *pWaveFunc) >> 8) << 0xD);
    sub_0809C4E8(voice, soundType, cosGain, (*((s32 *) (((s8 *) sound) + 0x5C))) + ((sub_080C31E0((s32) phase, *pWaveFunc) >> 8) << 0xD), (s32) phase);
  }
}
