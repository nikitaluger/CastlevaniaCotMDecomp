extern void startEffectTimer(u32, u32, u32);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern s32 scalePercentSaturate16(u16, s32);
extern void releaseActorEffectParts(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern struct S_FF0
{
  u8 _0[0x14EF];
  u8 f14EF;
  u8 _1[0x20];
  u8 f1510;
} gMainWorkspace;
extern u8 D_080E51D4[];
extern s32 gMainObjTimerCallbacks;
struct R3
{
  u8 _0;
  u8 f01;
  u8 f02;
  u8 f03;
  u16 f04;
  u16 f06;
  u16 f08;
  u16 f0A;
  u16 f0C;
  u16 f0E;
  u32 f10;
  u8 _14[2];
  u16 f16;
  u16 f18;
};
struct R6
{
  u32 f00;
  u32 f04;
  u32 f08;
  u32 f0C;
  u8 _10[8];
  u32 f18;
  u8 _1C[0x10];
  struct R3 *f2C;
  u32 f30;
  u32 f34;
  u32 f38;
  u32 f3C;
  u8 _40[0x14];
  u32 f54;
  u32 f58;
  u32 f5C;
};
struct R8
{
  u8 _0[4];
  u32 f04;
  u8 _08[0x4D];
  u8 f55;
};
struct R5
{
  u8 _0[2];
  u16 f02;
  u8 _04[0x20];
  u32 f24;
};
struct RT
{
  u16 f00;
  u16 f02;
  s16 f04;
  u16 f06;
  u32 f08;
  u32 f0C;
  u32 f10;
  u32 f14;
  u32 f18;
  u32 f1C;
  u32 f20;
  u32 f24;
  u32 f28;
  u32 f2C;
  u32 f30;
  u32 f34;
  u8 _38[0xA];
  u16 f42;
  u8 _44[4];
  u32 f48;
};
void sub_0807678C(u8 *arg0)
{
  struct R8 *r7 = *((struct R8 **) (arg0 + 0x6C));
  struct R6 *r5 = (struct R6 *) (((u8 *) r7) + 4);
  struct R6 *r8;
  struct R5 *sl = *((struct R5 **) (arg0 + 0x38));
  struct RT *t;
  struct R3 *r3;
  struct R3 *rp;
  u8 *new_var2;
  u32 zero;
  u32 mode;
  s16 *new_var;
  s32 tmp;
  s16 v;
  s16 idx;
  r8 = r5;
  r3 = allocEffectPart();
  r5->f2C = r3;
  if (r3 == 0)
  {
    cleanupFailedEffectSpawn(arg0);
    return;
  }
  zero = 0;
  r5->f30 = zero;
  r5->f34 = zero;
  r5->f38 = zero;
  r5->f3C = zero;
  t = (struct RT *) (D_080E51D4 + ((*((u32 *) (arg0 + 0x7C))) * 0x4C));
  r3->f01 = gMainWorkspace.f1510 & 1;
  r5->f2C->f02 = 2;
  r5->f2C->f03 = 8;
  rp = r5->f2C;
  rp->f04 = gGameStatus[0xC1 << 2];
  r5->f2C->f06 = t->f00;
  r5->f2C->f08 = t->f02;
  r5->f2C->f0A = zero;
  r5->f2C->f0C = zero;
  tmp = (v = t->f04);
  if (v == 0)
  {
    tmp = scalePercentSaturate16(*((u16 *) (gGameStatus + 0x2E2)), t->f06);
  }
  rp->f0E = tmp;
  r5->f2C->f16 = 5;
  r5->f2C->f18 = t->f42;
  r5->f2C->f10 = (u32) sl;
  r5->f18 = *((u32 *) (arg0 + 0x24));
  *((u32 *) (arg0 + 0x24)) = (u32) (&releaseActorEffectParts);
  r7->f55 = gMainWorkspace.f14EF;
  *((u32 *) (((u8 *) sl) + 0x24)) = t->f08;
  startEffectTimer((u32) (((u8 *) r7) + 0x20), zero, t->f0C);
  arg0 = (u8 *) (&gMainWorkspace);
  r7->f04 = *((u32 *) (arg0 + 0x1728));
  new_var2 = arg0 + 0x14;
  r5->f04 = *((u32 *) (arg0 + 0x172C));
  mode = *((u32 *) (arg0 + 0x1740));
  switch (mode)
  {
    case 1:
      tmp = r7->f04;
      if (sl->f02 & 0x10)
    {
      tmp -= t->f10;
    }
    else
    {
      tmp += t->f10;
    }
      r8->f00 = tmp;
      r8->f04 += t->f14;
      break;

    case 2:
      tmp = r7->f04;
      if (sl->f02 & 0x10)
    {
      tmp -= t->f18;
    }
    else
    {
      tmp += t->f18;
    }
      r8->f00 = tmp;
      r8->f04 += t->f1C;
      break;

    case 0:
      tmp = r7->f04;
      if (sl->f02 & 0x10)
    {
      tmp -= t->f20;
    }
    else
    {
      tmp += t->f20;
    }
      r8->f00 = tmp;
      r8->f04 += t->f24;
      break;

  }

  tmp = t->f28;
  if (sl->f02 & 0x10)
  {
    tmp = -tmp;
  }
  r8->f08 = tmp;
  r5->f0C = t->f2C;
  r5->f54 = t->f34;
  r5->f5C = t->f48;
  r5->f58 = (*t).f30;
  idx = *((s16 *) (arg0 + 0x22));
  *((u8 *) ((arg0 + (idx * 2)) + 0x19)) = zero;
  new_var = &(*((s16 *) (arg0 + 0x22)));
  {
    s32 *lit = &gMainObjTimerCallbacks;
    u8 *a18 = arg0 + 0x18;
    sub_080C31E4(a18, arg0 + 0x22, *lit);
    idx = *new_var;
    *((u8 *) ((arg0 + (idx * 2)) + 0x19)) += 1;
    idx = *new_var;
    a18 += idx * 2;
    sub_080C31E0(arg0, *((void **) (((*((u8 *) a18)) * 4) + (*((u32 *) new_var2)))));
  }
}

