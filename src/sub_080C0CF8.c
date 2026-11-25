extern u8 D_0810C8F6[];
extern s16 D_0810C97A[];
extern u8 D_0810C992[];

/* Sound-driver callback: mode 4 is a direct byte lookup, other modes clamp an
 * index and interpolate between two shifted table entries, biased by 0x800. */
s32 sub_080C0CF8(u8 mode, u8 index, u8 fraction)
{
  u8 frac = fraction;
  s32 lower;
  s32 upper;
  s32 span;
  s32 scaled;
  s32 result;
  if (mode == 4)
  {
    if (((u32) index) <= 0x14U)
    {
      index = 0;
    }
    else
    {
      index = index - 0x15;
      if (((u32) index) > 0x3BU)
      {
        index = 0x3B;
      }
    }
    return D_0810C992[index];
  }
  if (((u32) index) <= 0x23U)
  {
    frac = 0;
    index = 0;
  }
  else
  {
    index = index - 0x24;
    if (((u32) index) > 0x82U)
    {
      index = 0x82;
      frac = 0xFF;
    }
  }
  lower = D_0810C8F6[index];
  lower = D_0810C97A[lower & 0xF] >> (lower >> 4);
  upper = D_0810C8F6[index + 1];
  upper = D_0810C97A[upper & 0xF] >> (upper >> 4);
  span = upper - lower;
  scaled = ((s32) frac) * span;
  result = lower + ((scaled >> 7) >> 1);
  result = result + 0x800;
  return result;
}
