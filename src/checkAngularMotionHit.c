extern u32 gTrigFuncTable;
/* Thumb thunk at 0x080C31E0 (bx r1): the angle in a passes straight through to
 * the trig function whose address is passed in b, the word in gTrigFuncTable. */
s32 _call_via_r1(u32 a, u32 b);
s32 refreshMotionTrail(u32 a, void *b);
s32 sub_080147A4(s32 a, s32 b, s32 c);
/* Angular motion state of a tracked behaviour (work block at +0x48). */
typedef struct
{
  u8 unk00[0xA8];
  u32 cosVal;        /* 0xA8: cosine of the angle, scaled by the trig function */
  u32 sinVal;        /* 0xAC: sine of the angle, scaled by the trig function */
  u8 unkB0[4];
  s32 velX;          /* 0xB4 */
  s32 velY;          /* 0xB8 */
  u8 unkBC[4];
  u32 angle;         /* 0xC0: current angle, wrapped to 16 bits */
  s32 rangeLimit;    /* 0xC4: target angle the sweep must cross */
  s32 angularVel;    /* 0xC8 */
  s32 maxAngularVel; /* 0xCC */
  s32 angularAccel;  /* 0xD0 */
  u8 unkD4[4];
  u8 doneFlag;       /* 0xD8: stop checking once set */
} MotionEntity;

/* Advance an actor's angular motion: integrate and clamp angular velocity,
 * refresh the cached cos/sin and velocity components, and report whether the
 * target angle was crossed this frame. */
s32 checkAngularMotionHit(u32 actor, MotionEntity *motion)
{
  u32 angleBeforeStep;
  s32 perpAngle;
  u32 *trigFuncSlotA;
  u32 *trigFuncSlotB;
  angleBeforeStep = motion->angle;
  motion->angularVel += motion->angularAccel;
  if (motion->angularVel > motion->maxAngularVel)
  {
    motion->angularVel = motion->maxAngularVel;
  }
  else if (motion->angularVel < (-motion->maxAngularVel))
  {
    motion->angularVel = -motion->maxAngularVel;
  }
  motion->angle = (motion->angle + motion->angularVel) & 0xFFFF;
  trigFuncSlotA = &gTrigFuncTable;
  motion->cosVal = _call_via_r1(motion->angle + 0x4000, *trigFuncSlotA);
  motion->sinVal = _call_via_r1(motion->angle, *trigFuncSlotA);
  if (motion->angularVel > 0)
  {
    perpAngle = motion->angle + 0xFFFFC000;
  }
  else
  {
    perpAngle = motion->angle + 0x4000;
  }
  perpAngle &= 0xFFFF;
  trigFuncSlotB = &gTrigFuncTable;
  motion->velX = (((motion->angularVel < 0) ? (-motion->angularVel) : (motion->angularVel)) * _call_via_r1(perpAngle + 0x4000, *trigFuncSlotB)) >> 10;
  motion->velY = (((motion->angularVel < 0) ? (-motion->angularVel) : (motion->angularVel)) * _call_via_r1(perpAngle, *trigFuncSlotB)) >> 10;
  refreshMotionTrail(actor, motion);
  if (motion->doneFlag)
  {
    return 0;
  }
  if (motion->angularVel > 0)
  {
    if (sub_080147A4(angleBeforeStep, motion->angle, motion->rangeLimit) != 0)
    {
      return 1;
    }
  }
  else if (motion->angularVel < 0)
  {
    if (sub_080147A4(motion->angle, angleBeforeStep, motion->rangeLimit) != 0)
    {
      return 1;
    }
  }
  return 0;
}
