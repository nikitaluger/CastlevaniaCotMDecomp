/* Per-frame update of the player's follow-up action state: latches the input,
 * runs the action and body handlers, and when the action timer expires or a hit
 * connects switches either to the follow-up (form 0x14, state 0xD) or back to
 * the normal stance (state 4), otherwise to the hit result's next state. */
extern s32 syncViewPosition(u8 *, u8 *);              /* camera/view sync */
extern void resetActionResultState(u8 *, s32, u8 *, u8 *);  /* reset result flags */
extern void sub_08086744(u8 *, u8 *, u8 *, s32);  /* action handler */
extern void sub_0806AB04(u8 *, s32, u8 *, u8 *);  /* action handler */
extern void sub_08086240(u8 *, s32);              /* body part handler */
extern void sub_0806A884(s32, u8 *);              /* clamp sprite position */
extern s32 stepDelayTimer(u8 *, s32);               /* decrement timer / fire callback */
extern void setEntityForm(s32, u8 *, s32);         /* set entity form */
extern void setupEntityForRoomEntry(u8 *, u8 *);             /* follow-up action setup */
extern void resetActorForm(s32, u8 *);              /* end action */
extern void retargetActionForPhase(s32, u8 *, s32);         /* body part handler */
extern void applyActionPresetForProgress(u8 *, s32);              /* body part handler */
extern u16 sub_0806BCD8(u8 *, s32, u8 *, u8 *);   /* hit check -> next state */
extern void _call_via_r3(u8 *, u8 *, s32, s32);   /* state machine dispatch */
extern void sub_0806C6B0(u8 *, s32, u8 *, u8 *);  /* common update tail */
struct S_02025FF0
{
  u8 _0[0x24];
  u32 f24;                    /* 0x24: nonzero = use latched key state */
  u8 _28[2];
  u16 f2A;                    /* 0x2A: latched key state */
  u8 _2C[0x1514 - 0x2C];
  u32 f1514;                  /* 0x1514: reset request flag */
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90
{
  u8 _0[0x146E];
  u16 f146E;                  /* 0x146E: raw key state */
};
extern struct S_02021E90 gCameraState;
struct S_02025368
{
  u8 _0[0x3BC];
  u16 f3BC;                   /* 0x3BC: allowed-key mask */
};
extern struct S_02025368 gGameStatus;

inline static u32 zeroU32(void)
{
  u32 v = 0;
  return v;
}

inline static u8 zeroU8(void)
{
  u8 v = 0;
  return v;
}

void updatePlayerFollowUpAction(u8 *entity)
{
  u8 *work;
  s32 sprite;
  u8 *state;
  s32 flag;
  u8 *timer;
  u8 *timerBase;
  u16 keys;
  s32 timerResult;
  s32 nextState[2];
  u8 *stats;
  u32 zero70 = 0;
  work = (*((u8 **) (entity + 0x6C))) + 4;   /* action state block */
  sprite = *((s32 *) (entity + 0x38));
  state = work;                              /* alias used for call args */
  stats = (u8 *) (&gGameStatus);
  if (syncViewPosition(state, state) != 0)
  {
    return;
  }
  resetActionResultState(entity, sprite, state, state);
  if (gMainWorkspace.f24 != 0)
  {
    keys = gMainWorkspace.f2A & (*((u16 *) (stats + 0x3BC)));
  }
  else
  {
    keys = gCameraState.f146E & (*((u16 *) (stats + 0x3BC)));
  }
  if (keys == 0)
  {
    *((u32 *) (work + 0x70)) = zero70;
  }
  sub_08086744(entity, work, state, 9);
  sub_0806AB04(entity, sprite, work, state);
  flag = *((s32 *) (work + 0x40));
  if (flag == 0)
  {
    sub_08086240(work, 0xB);
    *((u32 *) (work + 0x4C)) = 1;
    *((u8 *) ((entity + (2 * (*((s16 *) (entity + 0x22))))) + 0x19)) = (u8) flag;
    {
      u32 *stateTable = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
      _call_via_r3(entity + 0x18, entity + 0x22, 0xB, *stateTable);
    }
  }
  sub_0806A884(sprite, state);
  timerBase = work + 0x28;
  timerResult = stepDelayTimer(timerBase, sprite);
  timer = timerBase;
  if (((timerResult == 0) && ((*((s32 *) (work + 0x40))) != 0)) || (gMainWorkspace.f1514 != 0))
  {
    flag = *((s32 *) (work + 0x70));
    if (flag != 0)
    {
      u8 *subObject;
      u8 zero8;
      u32 zero74;
      setEntityForm(sprite, work, 0x14);
      setupEntityForRoomEntry(entity, work);
      subObject = *((u8 **) (work + 0x130));
      for (;;)
      {
        zero8 = zeroU8();
        break;
      }
      zero74 = zeroU32();
      *((u16 *) (subObject + 0x16)) = 0xF;
      *((u32 *) (work + 0x74)) = zero74;
      stepDelayTimer(timer, sprite);
      *((u8 *) ((entity + (2 * (*((s16 *) (entity + 0x22))))) + 0x19)) = zero8;
      {
        u32 *stateTable = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
        _call_via_r3(entity + 0x18, entity + 0x22, 0xD, *stateTable);
      }
    }
    else
    {
      resetActorForm(sprite, work);
      stepDelayTimer(timer, sprite);
      *((u8 *) ((entity + (2 * (*((s16 *) (entity + 0x22))))) + 0x19)) = (u8) flag;
      {
        u32 *stateTable = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
        _call_via_r3(entity + 0x18, entity + 0x22, 4, *stateTable);
      }
    }
  }
  retargetActionForPhase(sprite, work, 9);
  applyActionPresetForProgress(work, 9);
  *((u32 *) (work + 0xC4)) = (nextState[1] = sub_0806BCD8(entity, sprite, work, state));
  if (nextState[1] != 0)
  {
    stepDelayTimer(timer, sprite);
    *((u8 *) ((entity + (2 * (*((s16 *) (entity + 0x22))))) + 0x19)) = 0;
    {
      u32 *stateTable = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
      _call_via_r3(entity + 0x18, entity + 0x22, *((s32 *) (work + 0xC4)), *stateTable);
    }
  }
  sub_0806C6B0(entity, sprite, work, state);
}
