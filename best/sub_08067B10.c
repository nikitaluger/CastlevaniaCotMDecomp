struct Arg0
{
  u8 _0[0x18];
  u8 f18;
  u8 _19[9];
  s16 f22;
  u8 _24[0x14];
  u32 f38;
  u8 _3C[0x30];
  u32 f6C;
};
struct G4
{
  u8 _0[8];
  u32 f08;
  s32 f0C;
  u8 _10[0x30];
  u32 f40;
  u32 f44;
  u8 _48[4];
  u32 f4C;
  u32 f50;
  u8 _54[0x64];
  u32 fB8;
  u8 _BC[8];
  u32 fC4;
};
struct S_02025FF0
{
  u8 _0[0x24];
  u32 f24;
  u16 f28;
};
struct S_02021E90
{
  u8 _0[0x146C];
  u16 f146C;
};
extern struct S_02025FF0 gMainWorkspace;
extern struct S_02021E90 gCameraState;
extern u8 gGameStatus[];
extern u8 D_080E03A0[];
extern void *gScriptStepCallbacks;
extern void *D_084A67FC;
extern void *D_084A6814;
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_08068704(void *, void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
void sub_08067B10(struct Arg0 *arg0)
{
  u32 *new_var2;
  struct G4 *g4;
  struct G4 *g4b;
  u32 a;
  u8 *base;
  u8 *r9;
  u8 *r4v;
  u32 temp;
  do { g4b = (struct G4 *) (arg0->f6C + 4); } while (0);
  a = arg0->f38;
  new_var2 = &(g4 = g4b)->f44;
  base = gGameStatus;
  if (syncViewPosition(g4, g4) != 0)
  {
    return;
  }
  resetActionResultState(arg0, (void *) a, g4, g4);
  sub_0806BA20((void *) a, g4, g4);
  {
    u8 *tbl;
    u32 off;
    s32 cur;
    s32 lim;
    tbl = D_080E03A0;
    off = (*new_var2) * 0x58;
    do { do { g4->f0C = (cur = g4->f0C + (*((s32 *) (tbl - (-off))))); } while (0); } while (0);
    temp = off + 4;
    lim = *((s32 *) (tbl + temp));
    if (cur > lim)
    {
      g4->f0C = lim;
    }
  }
  sub_08068704((void *) a, g4, g4);
  if (gMainWorkspace.f24 != 0)
  {
    if ((gMainWorkspace.f28 & (*((u16 *) (base + 0x3BC)))) != 0)
    {
      goto block_bba;
    }
    r4v = ((u8 *) g4b) + 0x28;
    r9 = r4v;

  
    goto block_bee;
  }
  else
  {
    s32 aa;
    aa = *((u16 *) (base + 0x3BC));
    r4v = ((u8 *) g4b) + 0x28;
    r9 = r4v;
    if ((gCameraState.f146C & aa) == 0)
    {
      goto block_bee;
    }
  }
  block_bba:
  r4v = ((u8 *) g4b) + 0x28;

  startEffectTimer(r4v, 0, D_084A67FC);
  *((u32 *) (((u8 *) g4b) + 0xB8)) = 0;
  *((u8 *) (((((u32) arg0->f22) * 2) + ((u32) arg0)) + 0x19)) = 0;
  {
    void *fn;
    fn = &gScriptStepCallbacks;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x27, *((void **) fn));
  }
  block_bec:
  r9 = r4v;

  block_bee:
  D_0806AB04(arg0, (void *) a, g4b, g4);

  if (g4b->f40 == 1)
  {
    g4b->f4C = 0;
    g4b->f50 = 0;
    if (arg0->f18 == 0x27)
    {
      *((u8 *) (((((u32) arg0->f22) * 2) + ((u32) arg0)) + 0x19)) = 0;
      {
        void *fn;
        fn = &gScriptStepCallbacks;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x26, *((void **) fn));
      }
      g4->f08 = 0;
    }
    else
    {
      startEffectTimer(r9, 0, D_084A6814);
      *((u8 *) (((((u32) arg0->f22) * 2) + ((u32) arg0)) + 0x19)) = 0;
      {
        void *fn;
        fn = &gScriptStepCallbacks;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0x24, *((void **) fn));
      }
    }
  }
  sub_0806A884((void *) a, g4);
  {
    u32 ret;
    u32 *pp;
    ret = sub_0806BCD8(arg0, (void *) a, g4b, g4);
    pp = (u32 *) (((u8 *) g4b) + 0xC4);
    *pp = (u16) ret;
    if ((*pp) != 0)
    {
      *((u8 *) (((((u32) arg0->f22) * 2) + ((u32) arg0)) + 0x19)) = 0;
      {
        void *fn;
        fn = &gScriptStepCallbacks;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *pp, *((void **) fn));
      }
    }
  }
  stepDelayTimer(r9, (void *) a);
  sub_0806C6B0(arg0, (void *) a, g4b, g4);
}
