struct A66
{
  u8 _0[0x22];
  s16 unk22;
  u8 _24[0x14];
  u8 *unk38;
  u8 _3C[0x30];
  u8 *unk6C;
};
struct R8ptr66
{
  u8 _0[0x2C];
  u8 _2C[0x90];
  s32 unkBC;
};
struct R466
{
  u8 _0[0x40];
  s32 unk40;
  u8 _44[0x08];
  s32 unk4C;
};
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 gGameStatus[];
extern u32 gScriptStepCallbacks;
extern u32 D_08671BC0;
extern u32 gMenuScriptCallback;
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u32 stepDelayTimer(void *, void *);
extern s32 sub_08065CC8(s32, s32, void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_0806C6B0(void *, void *, void *, void *);
void sub_08066A88(struct A66 *arg0)
{
  struct R8ptr66 *r5;
  u8 *new_var6;
  struct R466 *r4;
  u8 *r8;
  int new_var7;
  long new_var8;
  s32 r6res;
  u32 t;
  u32 *new_var3;
  u8 *idx;
  u8 *p6;
  u8 *new_var2;
  u8 *p5;
  u32 *new_var4;
  struct R466 *new_var5;
  s32 rvraw;
  struct R466 *new_var;
  u32 *pd;
  u32 *pd_1;
  u32 *pd_2;
  u16 a;
  volatile char c;
  s32 d;
  r5 = (struct R8ptr66 *) (*arg0).unk6C;
  r4 = (struct R466 *) (((u8 *) r5) + 4);
  new_var6 = gGameStatus;
  r8 = arg0->unk38;
  r6res = syncViewPosition(r4, r4);
  if (r6res != 0)
  {
    return;
  }
  new_var2 = r8;
  new_var5 = r4;
  resetActionResultState(arg0, new_var2, new_var5, new_var5);
  sub_0806AB04(arg0, r8, new_var5, new_var5);
  if (new_var5->unk40 == 0)
  {
    new_var5->unk4C = 1;
    ;
    ((u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0)))[0x19] = 0;
    new_var4 = &gScriptStepCallbacks;
    pd_1 = new_var4;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *pd_1);
  }
  sub_0806A884(r8, new_var5);
  t = stepDelayTimer(((u8 *) r5) + 0x2C, r8);
  if (t == 0)
  {
    r5->unkBC = r5->unkBC - 1;
    if (!(r5->unkBC == 0))
    {
      idx = (u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0));
      idx[0x19] = 0;
      ;
      new_var3 = &D_08671BC0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *new_var3);
    }
    else
    {
      idx = (u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0));
      idx[0x17] = 0;
      a = *((u16 *) (gMainWorkspace + 0x28));
      p5 = ((u8 *) arg0) + 0x18;
      p6 = ((u8 *) arg0) + 0x22;
      d = sub_08065CC8((s32) arg0, (s32) r8, new_var5, new_var5);
      pd_2 = &gMenuScriptCallback;
      sub_080C31E8(p5, p6, ((u16) d), *pd_2);
    }
  }
  new_var7 = 0x3BE;
  if ((*((u32 *) (gMainWorkspace + 0x24))) != 0)
  {
    d = *((u16 *) (new_var7 + new_var6));
    if ((d & a) == 0)
    {
      do
      {
      }
      while (0);
      goto BE0;
    }
  }
  else
  {
    new_var8 = *((u16 *) (gCameraState + 0x146C));
    d = *((u16 *) (gGameStatus + new_var7));
    c = new_var8;
    if ((d & c) == 0)
    {
      do
      {
      }
      while (0);
      goto BE0;
    }
  }
  ;
  ((u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0)))[0x17] = 0;
  p5 = ((u8 *) arg0) + 0x18;
  p6 = ((u8 *) arg0) + 0x22;
  rvraw = sub_08065CC8((s32) arg0, (s32) r8, new_var5, new_var5);
  new_var = new_var5;
  pd = &gMenuScriptCallback;
  sub_080C31E8(p5, p6, ((u16) rvraw), *(&gMenuScriptCallback));
  BE0:
  sub_0806C6B0(arg0, r8, new_var, new_var5);

  return;
}

