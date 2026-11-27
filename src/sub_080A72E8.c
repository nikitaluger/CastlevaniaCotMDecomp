typedef s32 M2C_UNK;
M2C_UNK refreshMotionTrail(void *, s32);
s32 sub_080C31E0(s32, s32);
M2C_UNK sub_080C31E4(void *, void *, s32);

/* Updates a shrinking spiral effect: advances a radius by a sine step, derives
 * X/Y offsets from that radius and a base angle via a sine lookup, updates the
 * target, and ends the effect when the entity's lifetime reaches 0x10. */
void sub_080A72E8(void *entity)
{
  s32 ctrlCopy;
  s32 ctrl;
  s32 *sinFunc;
  s32 radius;
  s32 radiusHigh;
  s32 angle;
  s32 angleOffset;
  void *state;
  s32 *effectTable;
  state = *((void **) (((s8 *) entity) + 0x3C));
  ctrl = (s32)((s8 *)state + 0x48);
  ctrlCopy = ctrl;
  angle = *((s32 *) (((s8 *) state) + 0x108));
  angleOffset = angle + 0xFFFFB800;
  sinFunc = &(*((s32 *) 0x08671BFC));
  radius = (*((s32 *) (((s8 *) state) + 0x144))) - (sub_080C31E0(((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19))) << 0xA) + 0x4000, *sinFunc) * 8);
  *((s32 *) (((s8 *) state) + 0x144)) = radius;
  radiusHigh = radius >> 0x10;
  *((s32 *) (((s8 *) state) + 0xFC)) = (s32) (((s32) (sub_080C31E0(angle + 0xFFFFF800, *sinFunc) * radiusHigh)) >> 8);
  *((s32 *) (((s8 *) state) + 0x100)) = (s32) (((s32) (sub_080C31E0(angleOffset, *sinFunc) * radiusHigh)) >> 8);
  refreshMotionTrail(entity, ctrl);
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19))) == 0x10)
  {
    *((s32 *) (((s8 *) state) + 0x144)) = (s32) (((*((s32 *) (((s8 *) state) + 0x144))) + 0x8000) & 0xFFFF0000);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = 0;
    effectTable = (s32 *)0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *effectTable);
  }
}
