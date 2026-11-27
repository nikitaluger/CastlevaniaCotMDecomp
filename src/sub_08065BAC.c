extern void *gMenuScriptCallback;
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern u16 selectTileActionStep(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *spawnEntity(void *, s32, s32, s32);
extern void sub_0806D7B4(void *, s32);
extern void spawnRoom34Object(void *, void *);
extern void sub_080C31E8(void *, void *, u16, void *);

/* Updates an entity's action: when its countdown expires, clears the effect
 * state, applies any pending acceleration, spawns a child object and calls the
 * action callback, then runs the common follow-up updates. */
void sub_08065BAC(u8 *entity)
{
  u8 *state = *((u8 **) (entity + 0x6C));
  int scale;
  u8 *vec = state + 4;
  u8 *obj = *((u8 **) (entity + 0x38));
  u8 *pos = vec;
  s32 timerResult;
  if (syncViewPosition(vec, vec) == 0)
  {
    resetActionResultState(entity, obj, pos, pos);
    sub_0806A884(obj, pos);
    timerResult = stepDelayTimer(state + 0x2C, obj);
    if (timerResult == 0)
    {
      u32 *modeAddr = (u32 *) (state + 0xA0);
      u8 *globals;
      u32 mode = *modeAddr;
      globals = (u8 *) 0x02025FF0;
      if (mode != 4)
      {
        *((u32 *) (globals + 0x180C)) = timerResult;
      }
      if ((*modeAddr) != 2)
      {
        *((u32 *) (globals + 0x1810)) = timerResult;
      }
      *((u32 *) (globals + 0x1820)) = timerResult;
      *((u32 *) (globals + 0x1824)) = timerResult;
      *((u32 *) (globals + 0x182C)) = timerResult;
      *((u32 *) (globals + 0x1828)) = timerResult;
      spawnRoom34Object(entity, pos);
      {
        u32 *accelAddr = (u32 *) (state + 0xC4);
        u32 accel = *accelAddr;
        if (accel != 0)
        {
          void *spawned;
          sub_0806D7B4(pos, accel << 16);
          spawned = spawnEntity(entity, 0x3C, 0xA, 0x12);
          if (spawned != 0)
          {
            globals = (u8 *) spawned;
            *((u16 *) (globals + 0x7C)) = 1;
          }
          *accelAddr = timerResult;
        }
      }
      *((u8 *) (((s16) *((s16 *) (entity + 0x22))) * (scale = 2) + (u32)entity + 0x17)) = 0;
      {
        void **callbackSlot = &gMenuScriptCallback;
        u8 *cbArg0 = entity + 0x18;
        u8 *cbArg1 = entity + 0x22;
        u16 cbArg2 = selectTileActionStep(entity, obj, vec, pos);
        sub_080C31E8(cbArg0, cbArg1, cbArg2, *callbackSlot);
      }
    }
    sub_0806AB04(entity, obj, vec, pos);
    sub_0806C6B0(entity, obj, vec, pos);
  }
}
