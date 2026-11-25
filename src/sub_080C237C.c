u64 sub_080C1764(void *w);
typedef union { u64 bits; struct { u32 lo; u32 hi; } part; } FloatMantissa;
typedef struct { s32 type; u32 sign; u32 exp; FloatMantissa mantissa; } SoftFloatWork;

/* Convert a 32-bit integer to the game's software-float value: build a
 * normalised mantissa/exponent work record and hand it to the packer, with
 * zero becoming type 2 and INT_MIN folding to the constant 0xC1E00000. */
u64 sub_080C237C(u32 value)
{
  volatile SoftFloatWork w;
  u32 signBit;
  w.type = 3;
  signBit = value >> 31;
  w.sign = signBit;
  if (value == 0)
  {
    w.type = 2;
  }
  else
  {
    w.exp = 60;
    if (signBit != 0)
    {
      if (value == 0x80000000U)
        return 0xC1E00000ULL;
      w.mantissa.bits = (u64)(s64)(-(s32)value);
    }
    else
    {
      w.mantissa.bits = (u64)(s64)(s32)value;
    }
    if (w.mantissa.part.hi <= 0x0FFFFFFFU)
    {
      u32 limit = 0x0FFFFFFFU;
      u32 e = w.exp;
      do
      {
        w.mantissa.bits <<= 1;
        e--;
      } while (w.mantissa.part.hi <= limit);
      w.exp = e;
    }
  }
  return sub_080C1764((void *)&w);
}
