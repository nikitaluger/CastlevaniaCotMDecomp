extern u32 D_08671BFC;
s32 sub_080C31E0(u32 a, u32 b);
s32 sub_080A845C(u32 a, void *b);
s32 sub_080147A4(s32 a, s32 b, s32 c);
/* Motion entity: angular state plus cached trig/velocity components. */
typedef struct
{
  u8 unk00[0xA8];
  u32 cosVal;        /* 0xA8: cos(angle) * amplitude */
  u32 sinVal;        /* 0xAC: sin(angle) * amplitude */
  u8 unkB0[4];
  s32 velX;          /* 0xB4 */
  s32 velY;          /* 0xB8 */
  u8 unkBC[4];
  u32 angle;         /* 0xC0 */
  s32 rangeLimit;    /* 0xC4 */
  s32 angularVel;    /* 0xC8 */
  s32 maxAngularVel; /* 0xCC */
  s32 angularAccel;  /* 0xD0 */
  u8 unkD4[4];
  u8 doneFlag;       /* 0xD8 */
} MotionEntity;

/* Advance an entity's angular motion: integrate and clamp angular velocity,
 * refresh its cached trig and velocity components, then report whether the
 * target angle range was crossed this frame. */
s32 sub_080A8784(u32 behav, MotionEntity *entity)
{
  u32 oldAngle;
  s32 offsetAngle;
  u32 *amplitude1;
  u32 *amplitude2;
  oldAngle = entity->angle;
  entity->angularVel += entity->angularAccel;
  if (entity->angularVel > entity->maxAngularVel)
  {
    entity->angularVel = entity->maxAngularVel;
  }
  else if (entity->angularVel < (-entity->maxAngularVel))
  {
    entity->angularVel = -entity->maxAngularVel;
  }
  entity->angle = (entity->angle + entity->angularVel) & 0xFFFF;
  amplitude1 = &D_08671BFC;
  entity->cosVal = sub_080C31E0(entity->angle + 0x4000, *amplitude1);
  entity->sinVal = sub_080C31E0(entity->angle, *amplitude1);
  if (entity->angularVel > 0)
  {
    offsetAngle = entity->angle + 0xFFFFC000;
  }
  else
  {
    offsetAngle = entity->angle + 0x4000;
  }
  offsetAngle &= 0xFFFF;
  amplitude2 = &D_08671BFC;
  entity->velX = (((entity->angularVel < 0) ? (-entity->angularVel) : (entity->angularVel)) * sub_080C31E0(offsetAngle + 0x4000, *amplitude2)) >> 10;
  entity->velY = (((entity->angularVel < 0) ? (-entity->angularVel) : (entity->angularVel)) * sub_080C31E0(offsetAngle, *amplitude2)) >> 10;
  sub_080A845C(behav, entity);
  if (entity->doneFlag)
  {
    return 0;
  }
  if (entity->angularVel > 0)
  {
    if (sub_080147A4(oldAngle, entity->angle, entity->rangeLimit) != 0)
    {
      return 1;
    }
  }
  else if (entity->angularVel < 0)
  {
    if (sub_080147A4(entity->angle, oldAngle, entity->rangeLimit) != 0)
    {
      return 1;
    }
  }
  return 0;
}
