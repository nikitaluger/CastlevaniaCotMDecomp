void startEffectTimer(s32, s32, s32);
void stepDelayTimer(s32, s32);
void sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);
void sub_0806D588(s32, s32);
struct S_02025FF0_14
{
  u8 _0x000[0x14];
  s32 gamePhase;
  u8 _0x18[0x4];
  s32 phaseTimer;
};
extern struct S_02025FF0_14 gMainWorkspace;
/* Effect/actor step: decrement the work-state frame timer, reloading resource
 * 0x199 and clamping a global counter when it expires; on game phase 0x0C set
 * up an attack animation, dispatch the script handler and clear the current
 * script byte; then refresh screen coordinates from the world position. */
void sub_0808A258(void *actor)
{
  u8 *self = (u8 *) actor;
  u8 *workState = (*((u8 **) (self + 0x6C))) + 4;
  s32 gfx = *((s32 *) (self + 0x38));
  s32 *handlerTable;
  u8 *globals;
  s32 counterOff;
  s32 *counter;
  u8 *attackWork;
  u8 *state = workState;
  s32 newCount = (*((s32 *) (state + 0x2C))) - 1;
  *((s32 *) (state + 0x2C)) = newCount;
  if (newCount == 0)
  {
    sub_08005E80(0x199);
    globals = (u8 *) (&gMainWorkspace);
    counterOff = 0x1754;
    counter = (s32 *) (globals + counterOff);
    if ((*counter) <= 0xE0)
    {
      *counter = 0xE1;
    }
  }
  if (gMainWorkspace.gamePhase == 0x0C)
  {
    attackWork = workState + 0x1C;
    startEffectTimer((s32) attackWork, 0, (s32) 0x08506434);
    stepDelayTimer((s32) attackWork, gfx);
    gMainWorkspace.phaseTimer = 0x10;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
  }
  sub_0806D588(gfx, (s32) state);
}
