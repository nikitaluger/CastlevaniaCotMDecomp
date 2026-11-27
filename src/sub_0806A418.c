/* Entity AI tick: while the camera is idle, round the entity's work Y coordinate,
 * run its timer and contact checks, then dispatch the resulting message id and state. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AA64(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern u16 selectTileActionStep(void *, void *, void *, void *);
extern void sub_0806C31E8(void *, void *, u16, s32);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern s32 gMenuScriptCallback;

void sub_0806A418(u8 *entity)
{
  u8 *workArg;
  u8 *state = *((u8 **) (entity + 0x6C));
  u8 *work = state + 4;
  u8 *workCopy = work;
  void *other = *((void **) (entity + 0x38));
  workArg = work;
  if (syncViewPosition(workArg, workArg) == 0)
  {
    s32 diff;
    resetActionResultState(entity, other, workArg, workArg);
    diff = (*((s32 *) (state + 0x110))) - (*((s32 *) (work + 4)));
    if (diff < 0)
    {
      diff += 7;
    }
    *((s32 *) (workArg + 4)) = (*((s32 *) (work + 4))) + (diff >> 3);
    sub_0806AA64(other, workArg);
    if (stepDelayTimer(state + 0x2C, other) == 0)
    {
      *((s32 *) (work + 4)) = *((s32 *) (state + 0x108));
      if ((*((s32 *) (work + 0x40))) == 0)
      {
        sub_0806A7AC(other, workArg, 0x10);
        stepDelayTimer(state + 0x2C, other);
        *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x17)) = 0;
        {
          u8 *msgArg0 = entity;
          u8 *msgArg1 = entity;
          s32 *msgTable = &gMenuScriptCallback;
          u16 msgId = 3;
          msgArg0 += 0x18;
          msgArg1 += 0x22;
          sub_080C31E8(msgArg0, msgArg1, msgId, *msgTable);
        }
      }
      else
      {
        *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x17)) = 0;
        {
          u8 *msgArg0 = entity;
          u8 *msgArg1 = entity;
          s32 *msgTable = &gMenuScriptCallback;
          u16 msgId;
          msgArg0 += 0x18;
          msgArg1 += 0x22;
          msgId = selectTileActionStep(entity, other, work, work);
          sub_080C31E8(msgArg0, msgArg1, msgId, *msgTable);
        }
      }
    }
    sub_0806C6B0(entity, other, workCopy, workArg);
  }
}
