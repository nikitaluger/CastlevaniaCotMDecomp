struct S66MainWorkspace
{
  u8 _0[0x24];
  u32 f24;
  u8 _28[2];
  u16 f28;
};
extern struct S66MainWorkspace gMainWorkspace;
struct S66CameraState
{
  u8 _0[0x146C];
  u16 f146C;
};
extern struct S66CameraState gCameraState;
struct S66GameStatus
{
  u8 _0[0x3BE];
  u16 f3BE;
};
extern struct S66GameStatus gGameStatus;
extern u32 gScriptStepCallbacks;
extern u32 D_08671BC0;
extern u32 gMenuScriptCallback;
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, u16, u32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_0806C6B0(void *, void *, void *, void *);

void sub_08066A88(u8 *script)
{
  u8 *actor = *(u8 **)(script + 0x6C);
  u8 *work = actor + 4;
  u8 *state = work;
  void *sprite = *(void **)(script + 0x38);

  if (syncViewPosition(state, state) != 0)
  {
    return;
  }
  resetActionResultState(script, sprite, state, state);
  sub_0806AB04(script, sprite, state, state);
  if (*(s32 *)(state + 0x40) == 0)
  {
    *(s32 *)(state + 0x4C) = 1;
    *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = 0;
    sub_080C31E8(script + 0x18, script + 0x22, 4, gScriptStepCallbacks);
  }
  sub_0806A884(sprite, state);
  if (stepDelayTimer(actor + 0x2C, sprite) == 0)
  {
    s32 timer = *(s32 *)(actor + 0xBC) - 1;
    *(s32 *)(actor + 0xBC) = timer;
    if (timer != 0)
    {
      *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = 0;
      sub_080C31E4(script + 0x18, script + 0x22, D_08671BC0);
    }
    else
    {
      *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x17) = 0;
      {
        u8 *p18 = script;
        u8 *p22 = script;
        u32 *lit = &gMenuScriptCallback;
        u16 rv;
        p18 += 0x18;
        p22 += 0x22;
        rv = sub_08065CC8(script, sprite, state, state);
        sub_080C31E8(p18, p22, rv, *lit);
      }
    }
  }
  if (gMainWorkspace.f24 != 0)
  {
    if ((gMainWorkspace.f28 & gGameStatus.f3BE) == 0)
    {
      goto end;
    }
  }
  else
  {
    if ((gCameraState.f146C & gGameStatus.f3BE) == 0)
    {
      goto end;
    }
  }
  *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x17) = 0;
  {
    u8 *p18 = script;
    u8 *p22 = script;
    u32 *lit = &gMenuScriptCallback;
    u16 rv;
    p18 += 0x18;
    p22 += 0x22;
    rv = sub_08065CC8(script, sprite, work, state);
    sub_080C31E8(p18, p22, rv, *lit);
  }
end:
  sub_0806C6B0(script, sprite, work, state);
}
