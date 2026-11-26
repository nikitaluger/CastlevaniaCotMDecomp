extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern s32 sub_08014B1C(s32, s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BFC;
extern s32 gMainObjTimerCallback;
extern s32 D_08671BD0;
static inline s32 add2(s32 a, s32 b) { return a + b; }
static inline u16 zeroU16(void) { return 0; }
/* Steer the entity toward a point at a fixed angle and speed; on arrival or
 * when the countdown expires, set up its state and dispatch a script callback. */
void sub_080273E4(void *arg0)
{
  u8 *entity = arg0;
  s32 *failFunc;
  u8 *motion = *((u8 **) (entity + 0x3C));
  u8 *motionEx = motion + 0x48;
  s32 *trigFunc = (s32 *) 0x08671BFC;
  s32 *successFunc;
  u8 *globals;
  u8 *baseXPtr;
  s32 speed;
  s32 targetX;
  s32 targetY;
  s32 cosVal;
  s32 trigVal;
  cosVal = sub_080C31E0((*((u16 *) ((*((u8 **) (motionEx + 0x58))) + 2))) + 0x4000, *trigFunc);
  globals = (u8 *) 0x02025FF0;
  baseXPtr = globals + 0x1728;
  speed = 0x5A;
  targetX = add2(*((s32 *) baseXPtr), speed * cosVal);
  trigVal = sub_080C31E0(*((u16 *) ((*((u8 **) (motionEx + 0x58))) + 2)), *trigFunc);
  targetY = add2(*((s32 *) (globals + 0x172C)), speed * trigVal);
  if (sub_08014A04(motion, targetX, targetY, 0x80000, 0x80000) == 1)
  {
    u8 *attackState = motion + 0x74;
    s32 z = 0;
    *(u16 *)(attackState + 0x18) = z;
    *(u32 *)(attackState + 0x24) = z;
    *(u32 *)(attackState + 0x28) = z;
    *((u32 *) (attackState + 0x1C)) = 0x3C;
    *((u32 *) (attackState + 0x20)) = 0x18000;
    {
      u16 old = *((u16 *) (attackState + 0x1A));
      u32 m = 0x19;
      u16 zz = zeroU16();
      trigVal = m | old;
      *((u16 *) (attackState + 0x1A)) = trigVal;
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = (u8) zz;
    }
    successFunc = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *successFunc);
    return;
  }
  {
    s32 countdown = (*((u16 *) (motionEx + 0x28))) - 1;
    *((u16 *) (motionEx + 0x28)) = (u16) countdown;
    if (((s32) (countdown << 16)) < 0)
    {
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = 0;
      failFunc = (s32 *) 0x08671BD0;
      sub_080C31E8(entity + 0x18, entity + 0x22, 3, *failFunc);
      return;
    }
  }
  sub_08014B1C((s32) motion, (s32) (motion + 0x74), targetX, targetY);
}
