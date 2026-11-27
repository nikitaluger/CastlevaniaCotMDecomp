extern u32 gScriptStepCallbacks[];
extern int syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern int stepDelayTimer(void *, void *);
extern void sub_08084CBC(void *, void *);
extern void sub_0806A7AC(void *, void *, int);
extern void sub_08005E80(int);
extern void sub_080C31E8(void *, void *, int, u32);
extern void sub_0806D7B4(void *, u32);
extern int sub_0806D2A0(void *, int, int, int);
extern int sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *);

/* Alternate actor action-step handler: syncs the view, resets result flags and
 * the step timer, dispatches the mode-specific attack/fallback step with its
 * script callback, then runs the shared post-step sprite/work updates. */
void runAlternateActionStep(void *actor)
{
  u8 *entityBytes;
  u8 *extra;
  u8 *work;
  u8 *context;
  u8 *workAlias;
  u8 *sequenceTimer;
  u32 stepMode;
  s16 stepIndex;
  u8 *stepEntry;
  s16 stepIndex2;
  u8 *stepEntry2;
  u8 *hitAmountPtr;
  u32 hitAmount;
  int spawnedEntity;
  u8 *spawnedFlag;
  s16 stepIndex3;
  u8 *stepEntry3;
  u32 *callbackTable;
  u8 *stepArray;
  u8 *stepIndexField;
  int actionResult;
  u16 stepId;
  u32 callback;

  entityBytes = (u8 *) actor;
  extra = *((u8 **) (entityBytes + 0x6C));
  work = extra + 4;
  context = *((u8 **) (entityBytes + 0x38));
  workAlias = work;
  if (syncViewPosition(workAlias, workAlias) != 0)
  {
    goto end;
  }
  resetActionResultState(entityBytes, context, workAlias, workAlias);
  sequenceTimer = extra + 0x2C;
  if (stepDelayTimer(sequenceTimer, context) != 0)
  {
    goto lbl_E8;
  }
  *((u32 *) (workAlias + 0x48)) = 0;
  sub_08084CBC(entityBytes, workAlias);
  stepMode = *((u32 *) (extra + 0xA0));
  switch (stepMode)
  {
    case 1:
      if ((*((u32 *) (extra + 0x98))) == 2)
    {
      sub_0806A7AC(context, workAlias, 0x2A);
      stepDelayTimer(sequenceTimer, context);
    }
    else
    {
      sub_0806A7AC(context, workAlias, 0x26);
      stepDelayTimer(sequenceTimer, context);
    }
      sub_08005E80(0x7A);
      stepIndex = *((s16 *) (entityBytes + 0x22));
      stepEntry = (u8 *)((u32)(stepIndex * 2) + (u32)entityBytes);
      stepEntry[0x19] = 0;
      {
        u32 *callbacks = gScriptStepCallbacks;
        sub_080C31E8(entityBytes + 0x18, entityBytes + 0x22, 0x1A, callbacks[0]);
      }
      break;

    case 3:
      if ((*((u32 *) (extra + 0x98))) == 2)
    {
      sub_0806A7AC(context, workAlias, 0x29);
      stepDelayTimer(sequenceTimer, context);
    }
    else
    {
      sub_0806A7AC(context, workAlias, 0x25);
      stepDelayTimer(sequenceTimer, context);
    }
      sub_08005E80(0x79);
      *((u32 *) (workAlias + 0x10)) = 0;
      stepIndex2 = *((s16 *) (entityBytes + 0x22));
      stepEntry2 = (u8 *)((u32)(stepIndex2 * 2) + (u32)entityBytes);
      stepEntry2[0x19] = 0;
      {
        u32 *callbacks = gScriptStepCallbacks;
        sub_080C31E8(entityBytes + 0x18, entityBytes + 0x22, 0x1B, callbacks[0]);
      }
      break;

    case 2:

    default:
      hitAmountPtr = work;
      hitAmountPtr += 0xC0;
      hitAmount = *((u32 *) hitAmountPtr);
      if (hitAmount != 0)
    {
      sub_0806D7B4(workAlias, hitAmount << 16);
      spawnedEntity = sub_0806D2A0(entityBytes, 0x3C, 0x0A, 0x12);
      if (spawnedEntity != 0)
      {
        spawnedFlag = ((u8 *) spawnedEntity) + 0x7C;
        *((u16 *) spawnedFlag) = 1;
      }
      *((u32 *) hitAmountPtr) = 0;
    }
      stepIndex3 = *((s16 *) (entityBytes + 0x22));
      stepEntry3 = (u8 *)((u32)(stepIndex3 * 2) + (u32)entityBytes);
      stepEntry3[0x19] = 0;
      callbackTable = gScriptStepCallbacks;
      stepArray = entityBytes + 0x18;
      stepIndexField = entityBytes + 0x22;
      actionResult = sub_08065CC8(entityBytes, context, work, workAlias);
      stepId = (u16) actionResult;
      callback = callbackTable[0];
      sub_080C31E8(stepArray, stepIndexField, stepId, callback);
      break;

  }

  lbl_E8:
  D_0806AB04(entityBytes, context, work, workAlias);

  sub_0806A884(context, workAlias);
  sub_0806C6B0(entityBytes, context, work, workAlias);
  end:
  return;
}
