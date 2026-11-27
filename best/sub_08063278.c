extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(u8 *, u8 *, u8 *, u8 *);
extern s32 sub_0806B3E8(u8 *, u8 *, u8 *, u8 *);
extern s32 sub_0806B820(u8 *, u8 *, u8 *, u8 *);
extern void resetActorForm(u8 *, u8 *);
extern void stepDelayTimer(u8 *, u8 *);
extern void sub_080C31E8(u8 *, u8 *, s32, u32);
extern void _0806AB04(u8 *, u8 *, u8 *, u8 *);
extern void setEntityForm(u8 *, u8 *, s32);
extern void sub_0806A884(u8 *, u8 *);
extern s32 _0806BCD8(u8 *, u8 *, u8 *, u8 *);
extern void sub_080C31FC(u8 *, u8 *, u32, u32);
extern void sub_0806C6B0(u8 *, u8 *, u8 *, u8 *);
extern u32 gScriptStepCallbacks;
struct D02025FF0
{
  u8 _0[0x24];
  u32 f24;
  u8 _28[2];
  u16 f2A;
};
extern struct D02025FF0 gMainWorkspace;
struct D02021E90
{
  u8 _0[0x146E];
  u16 f146E;
};
extern struct D02021E90 gCameraState;
void sub_08063278(u8 *arg0)
{
  u32 *new_var;
  u8 *r7;
  u8 *new_var2;
  u8 *r5;
  arg0 = (*((u8 **) (arg0 + 0x6C))) + 4;
  r7 = *((u8 **) (arg0 + 0x38));
  r5 = arg0;
  if (syncViewPosition(r5, r5))
  {
    return;
  }
  do { resetActionResultState(arg0, r7, r5, r5); } while (0);
  if (sub_0806B3E8(arg0, r7, r5, r5) == 0)
  {
    if (sub_0806B820(arg0, r7, r5, r5) == 0)
    {
      u16 val;
      if (gMainWorkspace.f24 != 0)
      {
        val = gMainWorkspace.f2A;
      }
      else
      {
        val = gCameraState.f146E;
      }
      if ((val & 0x40) == 0)
      {
        resetActorForm(r7, arg0);
        stepDelayTimer(arg0 + 0x28, r7);
        *((u32 *) (arg0 + 0x48)) = 0;
        *((u8 *) ((arg0 + (((s16) (*((u16 *) (arg0 + 0x22)))) * 2)) + 0x19)) = 0;
        { const u32 *D_08671BD0_ptr = &gScriptStepCallbacks; sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 4, *D_08671BD0_ptr); }
      }
    }
  }
  _0806AB04(arg0, r7, arg0, r5);
  new_var = (u32 *) (arg0 + 0xC4);
  if ((*((u32 *) (arg0 + 0x40))) == 0)
  {
    if ((*((u32 *) (arg0 + 0x4C))) == 0)
    {
      if ((*((u8 *) (arg0 + 0x18))) == 5)
      {
        setEntityForm(r7, arg0, 0x10);
        new_var2 = arg0 + 0x22;
        *((u8 *) ((arg0 + (((s16) (*((u16 *) new_var2))) * 2)) + 0x19)) = 0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, gScriptStepCallbacks);
      }
    }
  }
  sub_0806A884(r7, r5);
  {
    s32 res;
    *new_var = (u16) _0806BCD8(arg0, r7, arg0, r5);
    if ((*((u32 *) (arg0 + 0xC4))) != 0)
    {
      stepDelayTimer(arg0 + 0x28, r7);
      *((u8 *) ((arg0 + (((s16) (*((u16 *) (arg0 + 0x22)))) * 2)) + 0x19)) = 0;
      sub_080C31FC(arg0 + 0x18, arg0 + 0x22, *new_var, gScriptStepCallbacks);
    }
  }
  sub_0806C6B0(arg0, r7, arg0, r5);
}

