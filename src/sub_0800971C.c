extern void sub_08005E80(s32);
extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void sub_080C0384(void);
extern void sub_080C050C(s32);
extern s64 sub_080C1BF0(s64, s64);
extern s64 sub_080C1C58(s64, s64);
extern s64 sub_080C237C(s32);
extern s32 sub_080C23F8(void);
extern u8 *sub_080C2F24(s32, s32);
extern void (*D_08671BD0)(void *, void *, s32);
extern s32 D_020278D0;
extern u8 D_080CAA7C[];
/* Global gfx/effect state: color/highlight words and packed blend weights. */
struct S_03000830
{
  u8 _0[4];
  u16 color;
  u16 weights;
  u16 color2;
};
extern struct S_03000830 D_03000830;
/* Global game-state control/status flags. */
struct S_02021E90b { u8 _0[0x146C]; u16 control; u16 status; };
extern struct S_02021E90b D_02021E90;

/* Advances the effect's frame counter, samples a 0..16 blend wave into its
 * crossfade weights and the gfx state, then fires the script-step handler
 * (with mode changes and sounds) on the effect's milestone frames. */
void sub_0800971C(u8 *self)
{
  s32 frame = ++(*((s32 *) (self + 4)));
  s64 floatVal = sub_080C237C(frame);
  u8 *waveIndex;
  u8 blend;
  u8 zero;
  u8 one;
  if (frame < 0)
  {
    floatVal = sub_080C1BF0(floatVal, 0x0000000041F00000ULL);
  }
  sub_080C1C58(floatVal, 0x000000003FE00000ULL);
  waveIndex = sub_080C2F24(sub_080C23F8(), 0x2E);
  zero = 0;
  D_03000830.color = 0xFD << 6;
  blend = *((u8 *) (D_080CAA7C + ((u32) waveIndex)));
  *((s32 *) (self + 0x3C)) = blend;
  *((s32 *) (self + 0x4C)) = 16 - blend;
  D_03000830.weights = (u16) (blend | ((16 - blend) << 8));
  if (((u32) (*((s32 *) (self + 4)))) > 0x2EE)
  {
    sub_08005FC4(0, 1, 6, 0, &sub_080C0384);
    D_020278D0 = 2;
    {
      u8 *stepFlag = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      stepFlag[0x19] = zero;
    }
    D_08671BD0(self + 0x18, self + 0x22, 7);
    return;
  }
  if (((D_02021E90.status & 0x302) == 0x302) && ((D_02021E90.status & 1) != 0))
  {
    if ((D_02021E90.control & 4) != 0)
    {
      one = 1;
      *((u8 *) (self + 0x5C)) = one;
      *((u8 *) (self + 0x60)) = one;
      D_03000830.color = 0xEF;
      D_03000830.color2 = 0xA;
      {
        u8 *stepFlag = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
        stepFlag[0x19] = zero;
      }
      D_08671BD0(self + 0x18, self + 0x22, 5);
      return;
    }
  }
  ;
  if ((D_02021E90.control & 8) != 0)
  {
    D_020278D0 = 3;
    sub_080C050C(0x159);
    sub_080C050C(0xAD << 1);
    sub_08005E80(0x151);
    {
      u8 *stepFlag = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      stepFlag[0x19] = zero;
    }
    D_08671BD0(self + 0x18, self + 0x22, 7);
  }
}
