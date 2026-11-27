/* Alternate per-frame update of the player's action state: latches the input,
 * runs the action and body handlers, and when the action timer expires switches
 * either to a follow-up form/step or back to the idle form, otherwise to the hit
 * result's next state. */
extern s32 syncViewPosition(u8 *, u8 *);
extern void resetActionResultState(u8 *, s32, u8 *, u8 *);
extern void sub_08086744(u8 *, u8 *, u8 *, s32);
extern void sub_0806AB04(u8 *, s32, u8 *, u8 *);
extern void sub_0806A884(s32, u8 *);
extern s32 stepDelayTimer(u8 *, s32);
extern void setEntityForm(s32, u8 *, s32);
extern void setupEntityForRoomEntry(u8 *, u8 *);
extern void retargetActionForPhase(s32, u8 *, s32);
extern void applyActionPresetForProgress(u8 *, s32);
extern u16 sub_0806BCD8(u8 *, s32, u8 *, u8 *);
extern s32 _call_via_r3(u8 *, u8 *, s32, s32);
extern void sub_0806C6B0(u8 *, s32, u8 *, u8 *);
struct S_02025FF0 { u8 _0[0x24]; u32 f24; u8 _28[2]; u16 f2A; u8 _2C[0x1514-0x2C]; u32 f1514; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x146E]; u16 f146E; };
extern struct S_02021E90 gCameraState;
struct S_02025368 { u8 _0[0x3BC]; u16 f3BC; };
extern struct S_02025368 gGameStatus;
inline static u32 zeroU32(void) { u32 v = 0; return v; }
inline static u8 zeroU8(void) { u8 v = 0; return v; }
void updatePlayerAlternateAction(u8 *entity)
{
  u8 *work;
  s32 sprite;
  u8 *state;
  s32 result;
  u8 *timer;
  u8 *timerBase;
  s32 timerResult;
  u16 nextState;
  u8 *stats;
  s32 hitResult;
  s32 zero;
  work = *(u8 **)(entity + 0x6C) + 4;
  sprite = *(s32 *)(entity + 0x38);
  state = work;
  stats = (u8 *)&gGameStatus;
  if (syncViewPosition(state, state) != 0) return;
  resetActionResultState(entity, sprite, state, state);
  if (gMainWorkspace.f24 != 0) {
    if ((gMainWorkspace.f2A & *(u16 *)(stats + 0x3BC)) != 0) goto mask_done;
  } else {
    if ((gCameraState.f146E & *(u16 *)(stats + 0x3BC)) != 0) goto mask_done;
  }
  *(u32 *)(work + 0x70) = zeroU32();
mask_done:
  sub_08086744(entity, work, state, 0xA);
  sub_0806AB04(entity, sprite, work, state);
  if (*(s32 *)(work + 0x40) == 0 && (hitResult = *(s32 *)(work + 0x4C)) == 0 && entity[0x18] == 0xA) {
    *(u8 *)(entity + 2 * *(s16 *)(entity + 0x22) + 0x19) = (u8)hitResult;
    { u32 *fp = (u32 *)SCRIPT_STEP_CALLBACK_TABLE; _call_via_r3(entity + 0x18, entity + 0x22, 0xC, *fp); }
  }
  sub_0806A884(sprite, state);
  timerBase = work + 0x28;
  timerResult = stepDelayTimer(timerBase, sprite);
  timer = timerBase;
  if (timerResult == 0 || gMainWorkspace.f1514 != 0) {
    result = *(s32 *)(work + 0x70);
    if (result != 0) {
      setEntityForm(sprite, work, 0x15);
      setupEntityForRoomEntry(entity, work);
      stepDelayTimer(timer, sprite);
      *(u32 *)(work + 0x74) = zeroU32();
      zero = 0;
      *(u16 *)(*(u8 **)(work + 0x130) + 0x16) = (u16)(0x0F | zero);
      *(u8 *)(entity + 2 * *(s16 *)(entity + 0x22) + 0x19) = (u8)zero;
      { u32 *fp = (u32 *)SCRIPT_STEP_CALLBACK_TABLE; _call_via_r3(entity + 0x18, entity + 0x22, 0xE, *fp); }
    } else {
      setEntityForm(sprite, work, 5);
      stepDelayTimer(timer, sprite);
      *(u8 *)(entity + 2 * *(s16 *)(entity + 0x22) + 0x19) = (u8)result;
      { u32 *fp = (u32 *)SCRIPT_STEP_CALLBACK_TABLE; _call_via_r3(entity + 0x18, entity + 0x22, 8, *fp); }
    }
  }
  retargetActionForPhase(sprite, work, 0xA);
  applyActionPresetForProgress(work, 0xA);
  *(u32 *)(work + 0xC4) = (nextState = sub_0806BCD8(entity, sprite, work, state));
  if (nextState != 0) {
    stepDelayTimer(timer, sprite);
    *(u8 *)(entity + 2 * *(s16 *)(entity + 0x22) + 0x19) = (u8)(nextState * 0);
    { u32 *fp = (u32 *)SCRIPT_STEP_CALLBACK_TABLE; _call_via_r3(entity + 0x18, entity + 0x22, *(s32 *)(work + 0xC4), *fp); }
  }
  sub_0806C6B0(entity, sprite, work, state);
}
