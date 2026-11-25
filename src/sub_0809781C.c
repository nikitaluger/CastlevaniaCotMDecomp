extern void sub_080C31E8(void *, void *, s32, s32);
static inline u8 zero_b(void) { u8 v = 0; return v; }
static inline u16 zero_h(void) { u16 v = 0; return v; }

/* Script action: when the work object's flag at +0x1C has bit 2 set, derive a
 * value from its 16.16 field into its s16 target array, clear the work counter
 * and the entity's action byte, then dispatch script step 1. */
void sub_0809781C(u8 *self)
{
  u8 *work;
  s16 *target;
  s32 fixedVal;
  s16 scaled;
  register u16 zero16;
  register u8 zero8;
  work = *((u8 **) (self + 0x3C));
  if ((*((u8 *) (work + 0x1C))) & 2)
  {
    target = *((s16 **) (work + 0x04));
    fixedVal = *((s32 *) (work + 0x10));
    if (fixedVal < 0)
    {
      fixedVal += 0xFFFF;
    }
    scaled = (fixedVal >> 16) - 0x1F;
    zero16 = zero_h();
    zero8 = zero_b();
    target[3] = scaled;
    *((u16 *) (work + 0x14)) = zero16;
    *(u8 *)((u32)((*(s16 *)(self + 0x22)) << 1) + (s32)self + 0x19) = zero8;
    {
      s32 *callbackTable = (s32 *) 0x08671BD0;
      sub_080C31E8(self + 0x18, self + 0x22, 1, *callbackTable);
    }
  }
}
