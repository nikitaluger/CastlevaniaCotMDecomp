/* Advances a scripted crossfade effect: bumps its frame counter, samples the
 * 0..16 blend wave into the object and the gfx state, then dispatches the
 * script-step handler on the timed or button-driven milestones. */
extern void playSound(u16);
extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void sub_080C0384(void);
extern void sub_080C050C(s32);
extern s64 sub_080C1BF0(s64, s64);
extern s64 sub_080C1C58(s64, s64);
extern s64 sub_080C237C(s32);
extern s32 sub_080C23F8(void);
extern u8 *moduloInt(s32, s32);
extern void (*gScriptStepCallbacks)(void *, void *, s32);
extern s32 gMenuState;
extern u8 gCrossfadeBlendWave[];
/* Global gfx state: highlight colour, packed blend weights and tint colour. */
struct CrossfadeGfxState {
    u8 _0[4];
    u16 color;
    u16 weights;
    u16 color2;
};
extern struct CrossfadeGfxState D_03000830;
/* Global game-state control/status flags. */
struct S_02021E90b { u8 _0[0x146C]; u16 control; u16 status; };
extern struct S_02021E90b gCameraState;

void updateCrossfadeEffect(u8 *self)
{
  s32 frame = ++(*((s32 *) (self + 4)));
  s64 frameFloat = sub_080C237C(frame);
  u8 *waveIndex;
  u8 blend;
  u8 zero;
  u8 one;
  if (frame < 0)
  {
    frameFloat = sub_080C1BF0(frameFloat, 0x0000000041F00000ULL);
  }
  sub_080C1C58(frameFloat, 0x000000003FE00000ULL);
  waveIndex = moduloInt(sub_080C23F8(), 0x2E);
  zero = 0;
  D_03000830.color = 0xFD << 6;
  blend = *((u8 *) (gCrossfadeBlendWave + ((u32) waveIndex)));
  *((s32 *) (self + 0x3C)) = blend;
  *((s32 *) (self + 0x4C)) = 16 - blend;
  D_03000830.weights = (u16) (blend | ((16 - blend) << 8));
  if (((u32) (*((s32 *) (self + 4)))) > 0x2EE)
  {
    sub_08005FC4(0, 1, 6, 0, &sub_080C0384);
    gMenuState = 2;
    {
      u8 *stepTimer = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      stepTimer[0x19] = zero;
    }
    gScriptStepCallbacks(self + 0x18, self + 0x22, 7);
    return;
  }
  if (((gCameraState.status & 0x302) == 0x302) && ((gCameraState.status & 1) != 0))
  {
    if ((gCameraState.control & 4) != 0)
    {
      one = 1;
      *((u8 *) (self + 0x5C)) = one;
      *((u8 *) (self + 0x60)) = one;
      D_03000830.color = 0xEF;
      D_03000830.color2 = 0xA;
      {
        u8 *stepTimer = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
        stepTimer[0x19] = zero;
      }
      gScriptStepCallbacks(self + 0x18, self + 0x22, 5);
      return;
    }
  }
  ;
  if ((gCameraState.control & 8) != 0)
  {
    gMenuState = 3;
    sub_080C050C(0x159);
    sub_080C050C(0xAD << 1);
    playSound(0x151);
    {
      u8 *stepTimer = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      stepTimer[0x19] = zero;
    }
    gScriptStepCallbacks(self + 0x18, self + 0x22, 7);
  }
}
