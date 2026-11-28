/* Spawn a jittered particle effect at the state's position, then advance its
 * script once the step counter passes five. */
struct S_02025FF0
{
  u8 _0[0x189C];
  u32 f189C;
};
extern struct S_02025FF0 gMainWorkspace;
extern s32 randomSignedOffset(s32);
extern s32 scaleByRandom(s32);
extern s32 signedRemainder(s32, s32);
extern void sub_0802F604(s32, s32, s32, s32, s16);
extern void sub_080C31E0(void *, s32);

void sub_0802F2D8(u8 *effect)
{
  u8 *sprite;
  u8 *fxState;
  u8 flagValue;
  u32 mask;
  u8 zero;
  u8 *flag;
  s32 spawnX;
  s32 spawnY;
  s32 angle;
  s32 scale;
  u8 *sourcePtr;
  s32 tick;
  s16 frame;

  sprite = *((u8 **) (effect + 0x38));
  fxState = *((u8 **) (effect + 0x3C));
  flag = sprite + 0x2A;
  flagValue = *flag;
  mask = 0xBF;
  mask &= flagValue;
  zero = 0;
  *flag = (u8) mask;
  *((u32 *) (fxState + 0x14)) = zero;
  *((u32 *) (fxState + 0x10)) = zero;
  sourcePtr = fxState + 0x28;
  *((u8 *) ((*((u8 **) sourcePtr)) + 1)) = zero;
  *((u32 *) (fxState + 0x48)) = zero;
  do
  {
    angle = 0x80000;
    spawnX = ((*((u32 *) (fxState + 0x08))) + ((*((s16 *) ((*((u8 **) sourcePtr)) + 0x0A))) << 16)) + randomSignedOffset(angle);
    spawnY = ((*((u32 *) (fxState + 0x0C))) + ((*((s16 *) ((*((u8 **) (fxState + 0x28))) + 0x0C))) << 16)) + randomSignedOffset(angle);
  }
  while (0);
  angle = (signedRemainder(gMainWorkspace.f189C, 7) - 3) << 13;
  scale = 0x8000 - scaleByRandom(0x20000);
  tick = gMainWorkspace.f189C;
  frame = (s16) (tick % 4);
  sub_0802F604(spawnX, spawnY, angle, scale, frame);
  if ((*((u8 *) ((effect + ((*((s16 *) (effect + 0x22))) * 2)) + 0x19))) > 5)
  {
    sub_080C31E0(effect, *((u32 *) (effect + 0x24)));
  }
}
