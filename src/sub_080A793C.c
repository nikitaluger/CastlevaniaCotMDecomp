typedef s32 M2C_UNK;
M2C_UNK sub_080A845C(void *, void *);
M2C_UNK sub_080A8B70(void *);
s16 divideInt(s32, s32);
s32 sub_080C31E0(s32, s32);
M2C_UNK sub_080C31E8(void *, void *, s32, s32);

/*
 * Updates an entity's action timer: scales two motion parameters by the time
 * left, then resets the script step or advances the animation when a timer or
 * state threshold is reached.
 */
void sub_080A793C(void *entity)
{
  s32 timer;
  void *motionEx;
  s32 *scriptTable;
  void *motion;
  u32 *scaleFunc;
  u8 scratch;
  s16 newStep;
  void *subComp;

  motion = *((void **) (((s8 *) entity) + 0x3C));
  motionEx = (void *) (((s8 *) motion) + 0x48);
  timer = (*((s32 *) (((s8 *) motion) + 0x134))) - 1;
  *((s32 *) (((s8 *) motion) + 0x134)) = timer;
  if (timer < 0)
  {
    *((s32 *) (((s8 *) motion) + 0x134)) = 0;
  }
  scaleFunc = (u32 *) 0x08671BFC;
  *((s32 *) (((s8 *) motion) + 0xFC)) = (s32) (((s32) (sub_080C31E0((*((s32 *) (((s8 *) motion) + 0x130))) + 0x4000, *scaleFunc) * (*((s32 *) (((s8 *) motion) + 0x134))))) >> 7);
  *((s32 *) (((s8 *) motion) + 0x100)) = (s32) (((s32) (sub_080C31E0(*((s32 *) (((s8 *) motion) + 0x130)), *scaleFunc) * (*((s32 *) (((s8 *) motion) + 0x134))))) >> 7);
  sub_080A845C(entity, motionEx);
  if (((*((u8 *) (((s8 *) motion) + 0x148))) != 3) && (((s32) (*((s32 *) (((s8 *) motion) + 0x134)))) <= 0x31))
  {
    scratch = 0x19;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + ((s8 *) entity))) + scratch)) = 0;
    scriptTable = (s32 *) 0x08671BD0;
    sub_080C31E8(((s8 *) entity) + 0x18, ((s8 *) entity) + 0x22, 4, *scriptTable);
    return;
  }
  if ((*((s32 *) (((s8 *) motionEx) + 0xEC))) == 0)
  {
    newStep = divideInt((*((s16 *) (((s8 *) (*((void **) (((s8 *) motion) + 0x28)))) + 0xE))) * 5, 4);
    subComp = *((void **) (((s8 *) motion) + 0x28));
    scratch = 0;
    *((s16 *) (((s8 *) subComp) + 0xE)) = newStep;
    *((s16 *) (((s8 *) (*((void **) (((s8 *) motionEx) + 0x114)))) + 0xE)) = divideInt((*((s16 *) (((s8 *) (*((void **) (((s8 *) motionEx) + 0x114)))) + 0xE))) * 5, 4);
    sub_080A8B70(entity);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + ((s8 *) entity))) + 0x17)) = scratch;
    {
      s32 *pBD8 = (s32 *) 0x08671BD8;
      sub_080C31E8(((s8 *) entity) + 0x18, ((s8 *) entity) + 0x22, 0, *pBD8);
    }
  }
}
