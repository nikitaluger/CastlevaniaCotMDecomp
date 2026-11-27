extern void stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void sub_08005E80(s32);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_084FEBF0[];
extern u8 gScriptStepCallbackTable[];
struct S_02025FF0
{
  u8 pad0[0x1C];
  s32 field_1C;
  u8 pad20[0x1708];
  s32 field_1728;
};
extern struct S_02025FF0 gMainWorkspace;

/* Homing projectile: advances the child's X by its velocity, ticks a countdown timer,
 * and once within range of the global target X spawns an effect at the child's +0x20
 * position and posts a state-change message; finally it updates the FX position and timer.
 */
void sub_080884BC(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *child = *(u8 **) (self + 0x6C);
  u8 *childData = child + 4;
  void *fx = *(void **) (self + 0x38);
  s32 *msgPtr;
  u8 *childVec = childData;
  s32 targetX;
  void *fxPos;
  s32 posX;
  s32 delta;
  *(s32 *) (child + 4) += *(s32 *) (childVec + 8);
  {
    s32 timer = (*(s32 *) (childVec + 0x14)) - 1;
    *(s32 *) (childVec + 0x14) = timer;
    if (timer == 0)
    {
      sub_08005E80(0x69);
      *(s32 *) (childVec + 0x14) = 0x20;
    }
  }
  targetX = gMainWorkspace.field_1728;
  posX = *(s32 *) (child + 4);
  delta = targetX - posX;
  if (delta >= 0)
  {
    if (delta > 0x1FFFFF)
    {
      fxPos = child + 0x20;
    }
    else
    {
      goto trigger;
    }
  }
  else
  {
    s32 back = posX - targetX;
    if (back > 0x1FFFFF)
    {
      fxPos = child + 0x20;
    }
    else
    {
      fxPos = child + 0x20;
      goto trigger;
    }
  }
  goto end;
  trigger:
  fxPos = childData + 0x1C;

  startEffectTimer(fxPos, 0, D_084FEBF0);
  gMainWorkspace.field_1C = 2;
  *(u8 *) ((self + ((*(s16 *) (self + 0x22)) * 2)) + 0x19) = 0;
  msgPtr = (s32 *) gScriptStepCallbackTable;
  sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
  end:
  stepDelayTimer(fxPos, fx);

  sub_0806D588(fx, childVec);
}
