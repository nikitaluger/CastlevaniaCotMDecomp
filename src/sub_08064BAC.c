void *syncViewPosition(void *, void *);
void resetActionResultState(void *, void *, void *, void *);
void sub_0806AB04(void *, void *, void *, void *);
void sub_0806A884(void *, void *);
s32 stepDelayTimer(void *, void *);
s32 sub_0806B2C8(void *, void *, void *, void *);
void resetActorForm(void *, void *);
void sub_080849A4(void *, void *);
u32 sub_0806BCD8(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);
inline u8 *inline_fn(void *arg0)
{
  return (u8 *) arg0;
}

/*
 * Companion/boss update: picks a position mode, runs the state setup helpers,
 * then fires attack routines from the gScriptStepCallbacks table based on state flags,
 * sub-system results and the current pose index.
 */
void sub_08064BAC(void *arg0)
{
  void *mgr = arg0;
  void *sub;
  void *state;
  void *ent;
  void *subNext;
  void *owner;
  s32 result;
  u32 code;
  u32 *codeSlot;
  s32 *attackTableA;
  s32 *attackTableB;
  void **new_var;
  s32 *attackTableC;

  sub = *((void **) (((u8 *) mgr) + 0x6C));
  state = ((u8 *) sub) + 4;
  owner = *(new_var = (void **) (((u8 *) mgr) + 0x38));
  ent = state;
  if (syncViewPosition(ent, ent) != 0)
  {
    return;
  }
  resetActionResultState(mgr, owner, ent, ent);
  sub_0806AB04(mgr, owner, ent, ent);
  if ((*((s32 *) (inline_fn(ent) + 0x40))) == 0)
  {
    *((s32 *) (inline_fn(ent) + 0x4C)) = 1;
    *((u8 *) ((inline_fn(mgr) + ((*((s16 *) (inline_fn(mgr) + 0x22))) * 2)) + 0x19)) = 0;
    attackTableA = (s32 *) 0x08671BD0;
    sub_080C31E8(((u8 *) mgr) + 0x18, inline_fn(mgr) + 0x22, 0x13, *attackTableA);
  }
  sub_0806A884(owner, ent);
  subNext = ((u8 *) sub) + 0x2C;
  if ((stepDelayTimer(subNext, owner) == 0) && ((*((s32 *) (((u8 *) ent) + 0x40))) == 1))
  {
    result = sub_0806B2C8(mgr, owner, ent, ent);
    if (result != 0)
    {
      stepDelayTimer(subNext, owner);
    }
    else
    {
      resetActorForm(owner, ent);
      *((s32 *) (inline_fn(ent) + 0x48)) = (float) result;
      stepDelayTimer(subNext, owner);
      *inline_fn((((u8 *) mgr) + ((*((s16 *) (inline_fn(mgr) + 0x22))) * 2)) + 0x19) = (u8) result;
      attackTableB = (s32 *) 0x08671BD0;
      sub_080C31E8(inline_fn(mgr) + 0x18, inline_fn(mgr) + 0x22, 4, *attackTableB);
    }
  }
  sub_080849A4(mgr, state);
  code = sub_0806BCD8(mgr, owner, state, ent);
  codeSlot = (u32 *) (((u8 *) state) + 0xC4);
  *codeSlot = (u16)code;
  if ((u16)code != 0)
  {
    stepDelayTimer(((u8 *) state) + 0x28, owner);
    *((u8 *) ((((u8 *) mgr) + ((*((s16 *) (((u8 *) mgr) + 0x22))) * 2)) + 0x19)) = 0;
    attackTableC = (s32 *) 0x08671BD0;
    sub_080C31E8(inline_fn(mgr) + 0x18, ((u8 *) mgr) + 0x22, *codeSlot, *attackTableC);
  }
  sub_0806C6B0(mgr, owner, state, ent);
}
