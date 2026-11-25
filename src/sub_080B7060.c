#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
M2C_UNK sub_080113A8(void *, s32);
M2C_UNK sub_0801165C(void *, s32);
M2C_UNK sub_0809856C(s32, void *, s32);
M2C_UNK sub_080B72CC(void *);
M2C_UNK sub_080C31E0(void *, s32);

/* Aims an attacking entity at its target, integrates its motion, nudges its
 * vertical velocity by a direction-dependent amount, and fires its callback
 * when its position lies inside the target's bounding box after the delay. */
void sub_080B7060(void *arg0)
{
  s32 bodyX;
  s32 velocity;
  s32 targetYLow;
  int targetXLow;
  s32 dummyTargetY;
  s32 targetX;
  s32 aim;
  s32 bodyYPos;
  s32 newVelocity;
  int delay;
  void *target;
  void *body;
  void *targetBody;
  s8 *pTargetY;
  target = *((void **) (((s8 *) arg0) + 0x38));
  body = *((void **) (((s8 *) arg0) + 0x3C));
  aim = body + 0x34;
  targetBody = *((void **) (((s8 *) (*((void **) (((s8 *) arg0) + 0x28)))) + 0x3C));
  sub_0809856C(0x18E, arg0 + 0x7C, 0xA);
  sub_080113A8(target, aim);
  sub_0801165C(body, 0);
  velocity = *((s32 *) (((s8 *) body) + 0x10));
  if (0x10 & *((u16 *) (((s8 *) target) + 2)))
  {
    newVelocity = velocity + 0xC00;
  }
  else
  {
    newVelocity = velocity + 0xFFFFF400;
  }
  *((s32 *) (((s8 *) body) + 0x10)) = newVelocity;
  sub_080B72CC(arg0);
  delay = *((u16 *) (((s8 *) arg0) + 0x74));
  if (delay != 0)
  {
    *((u16 *) (((s8 *) arg0) + 0x74)) = (u16) (delay - 1);
    return;
  }
  targetX = *((s32 *) (((s8 *) targetBody) + 8));
  targetXLow = targetX + 0xFFF80000;
  bodyX = *((s32 *) (((s8 *) body) + 8));
  pTargetY = ((s8 *) targetBody) + 0xC;
  if ((bodyX > ((s32) targetXLow)) && (bodyX < ((s32) ((*((s32 *) (((s8 *) targetBody) + 8))) + 0x80000))))
  {
    targetYLow = (s32) ((*((s32 *) pTargetY)) + 0xFFE00000);
    if (1)
    {
      dummyTargetY = *((s32 *) pTargetY);
    }
    bodyYPos = *((s32 *) (((s8 *) body) + 0xC));
    if ((bodyYPos > targetYLow) && (bodyYPos < (*((s32 *) pTargetY))))
    {
      sub_080C31E0(arg0, *((s32 *) (((s8 *) arg0) + 0x24)));
    }
  }
}
