extern void sub_080C31E4(void *, void *, s32);
struct Z0801
{
  u16 w;
  u8 b;
};
/* Countdown at obj+0x58: when it expires, copy the object's animation state,
 * clear the current script step byte and advance the script. */
void sub_08017330(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *obj = *((u8 **) (self + 0x3C));
  u8 *state = obj + 0x48;
  u16 zeroWord;
  s32 countdown;
  s32 *advanceFunc;
  countdown = *((u16 *) (state + 0x16));
  countdown = countdown - 1;
  {
    struct Z0801 z = {0, 0};
    zeroWord = z.w;
    *((u16 *) (state + 0x16)) = countdown;
    if (((s32) (((u16) countdown) << 16)) < 0)
    {
      *((u16 *) (state + 0x16)) = 5;
      *((s32 *) (obj + 8)) = *((s32 *) (obj + 0x48));
      *((s32 *) (obj + 0xC)) = *((s32 *) (state + 4));
      *((s32 *) (obj + 0x14)) = zeroWord;
      *((s32 *) (obj + 0x10)) = zeroWord;
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = z.b;
      advanceFunc = (s32 *) 0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *advanceFunc);
    }
  }
}
