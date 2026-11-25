extern void sub_080C050C(s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct S_02025FF0_90408
{
  u8 _0[0x1848];
  u32 flags;
};
extern struct S_02025FF0_90408 D_02025FF0;

/* Counts down the effect's animation timer; on expiry clears its state, sets
 * up the four halfword animation parameters, plays sound 0x1BE and resets the
 * step byte before running script command 1. */
void sub_08090408(void *arg0)
{
  u8 *self = arg0;
  u8 *anim = *((u8 **) (self + 0x3C));
  s32 timer;
  u8 zero;
  u16 minusTen = 0xFFF6;
  if (anim)
  {
    timer = (*((u16 *) (anim + 0x18))) - 1;
    zero = 0;
    *((u16 *) (anim + 0x18)) = timer;
  }
  else
  {
    timer = (*((u16 *) (anim + 0x18))) - 1;
    zero = 0;
    *((u16 *) (anim + 0x18)) = timer;
  }
  if ((timer << 0x10) < 0)
  {
    *((u16 *) (anim + 0x16)) = zero;
    D_02025FF0.flags = D_02025FF0.flags & 0xB281FFFF;
    *((u16 *) ((*((u8 * volatile *) (anim + 4))) + 6)) = 4;
    *((u16 *) ((*((u8 * volatile *) (anim + 4))) + 8)) = 0xA;
    *((u16 *) ((*((u8 * volatile *) (anim + 4))) + 0xA)) = zero;
    *((u16 *) ((*((u8 * volatile *) (anim + 4))) + 0xC)) = minusTen;
    sub_080C050C(0xDF << 1);
    *((u8 *) (((*((s16 *) (self + 0x22))) * 2) + self + 0x19)) = 0;
    {
      s32 *scriptHandlers = (s32 *) 0x08671BD0;
      sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptHandlers);
    }
  }
}
