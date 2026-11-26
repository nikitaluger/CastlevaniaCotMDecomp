extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *);
extern void registerScriptObject(u8 *, s32);
extern s16 sub_08005820(s32);
extern void sub_0804EA20(u8 *);
extern void sub_0804E9F0(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  u32 f10;
  u16 f14;
};
struct P
{
  u8 _0[8];
  s32 f8;
  s32 fC;
  u32 f10;
  u32 f14;
  u32 f18;
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u32 f24;
  struct E *f28;
};
struct H
{
  u8 _0[4];
  s16 *f4;
};
struct Arg0
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x22 - 4];
  s16 f22;
  u8 _24[0x38 - 0x24];
  u8 *f38;
  struct P *f3C;
  u8 _40[0x4C - 0x40];
  s16 f4C;
  u8 _4E[6];
  s16 f54;
  u8 _56[0xAC - 0x56];
  struct H *fAC;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
extern struct S_02021E90 gCameraState;
struct TBL
{
  u16 f0;
  s16 f2;
  u16 f4;
  u8 _6[0x14 - 6];
};
extern struct TBL gSpriteKindTable[];
extern u16 D_080CFA3C[];
extern u8 gSpriteAnimDataTable[];
void sub_0804E584(struct Arg0 *arg0)
{
  struct Arg0 *new_var2;
  struct H *e = arg0->fAC;
  u32 *new_var3;
  u8 *obj;
  struct P *r5;
  s16 new_var;
  u8 *r10;
  u8 *s;
  s32 r0_3;
  u32 tmp;
  u32 zero;
  u32 tblv;
  u8 *base;
  u8 *r4b;
  u8 *r2b;
  obj = allocSpriteObject();
  r5 = NULL;
  new_var3 = &zero;
  s = NULL;
  r0_3 = 0;
  if ((((obj == NULL) || ((arg0->f38 = obj, allocWorkSlot((u8 *) arg0, 0, 0x88, 0), r5 = arg0->f3C, r5 == NULL))) || ((r10 = ((u8 *) r5) + 0x34, r5->f24 = *((u32 *) (((u8 *) arg0) + 0x24)), *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_0804E9F0, zero = 0, r5->f1C = 0x5D, tblv = (u32) gSpriteKindTable, r5->f18 = ((struct TBL *) tblv)[r5->f1C].f2, r5->f8 = e->f4[0] << 16, r5->fC = e->f4[1] << 16, r0_3 = findKindIndex(0x5D), r5->f22 = r0_3, ((s32) (r0_3 << 16)) < 0))) || ((initSpriteGraphics(obj, r10, ((s32) gSpriteAnimDataTable) + (r5->f1C * 0xC)), s = allocEffectPart(), r5->f28 = (struct E *) s, s == NULL)))
  {
    if (1)
    {
    }
    sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
    return;
  }
  r5->f28->f1 = zero;
  r5->f28->f2 = 8;
  r5->f28->f3 = 1;
  r5->f28->f4 = ((struct TBL *) tblv)[r5->f1C].f0;
  r5->f28->f6 = D_080CFA3C[0];
  r5->f28->f8 = D_080CFA3C[1];
  r5->f28->fA = D_080CFA3C[2];
  r5->f28->fC = D_080CFA3C[3];
  r5->f28->fE = ((struct TBL *) tblv)[r5->f1C].f4;
  r5->f28->f10 = (u32) obj;
  r5->f28->f14 = zero;
  {
    s32 v = ((*((u16 *) obj)) & 0xC00) | ((((*((s16 *) (((u8 *) r5) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) r5) + 0x22))) + 8) << 12));
    *((u16 *) obj) = v;
    *((u16 *) obj) = v | gMainWorkspace.f18C2;
  }
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  base = (u8 *) (&gCameraState);
  {
    u32 k = 0x1278;
    u32 coord = *((u32 *) ((base + k) + ((gMainWorkspace.f18A8 + 1) << 6)));
    tblv = 0x8000;
    *((u32 *) (obj + 0x14)) = r5->f8 - ((coord + tblv) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (obj + 0x18)) = r5->fC - (((*((u32 *) ((base + (k & 0xFFFF)) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  if (gSpriteKindTable)
  {
    r4b = ((u8 *) r5) + 0x48;
    *((s32 *) (((u8 *) r5) + 0x48)) = r5->f8;
    *((s32 *) (r4b + 4)) = r5->fC;
    *((u16 *) (r4b + 0x10)) = zero;
    *((u16 *) (r4b + 0x12)) = sub_08005820(0xB4);
    sub_0804EA20((u8 *) arg0);
    new_var = *((s16 *) (r4b + 0x10));
    r2b = ((u8 *) r5) + 0x5C;
    *((u32 *) (((u8 *) r5) + 0x5C)) = zero;
  }
  else
  {
    r4b = ((u8 *) r5) + 0x48;
    do
    {
      *((s32 *) (((u8 *) r5) + 0x48)) = r5->f8;
      *((s32 *) (r4b + 4)) = r5->fC;
      *((u16 *) (r4b + 0x10)) = *new_var3;
    }
    while (0);
    *((u16 *) (r4b + 0x12)) = sub_08005820(0xB4);
    sub_0804EA20((u8 *) arg0);
    new_var = *((s16 *) (r4b + 0x10));
    r2b = ((u8 *) r5) + 0x5C;
    *((u32 *) (((u8 *) r5) + 0x5C)) = zero;
  }
  {
    u32 v1 = 0;
    if (new_var == 1)
    {
      do
      {
        v1 = tblv;
      }
      while (0);
    }
    *((u32 *) (r2b + 4)) = v1;
  }
  *((u32 *) (r2b + 8)) = 0x800;
  *((u32 *) (r2b + 0x0C)) = 0x6000;
  new_var2 = arg0;
  *((u32 *) (r2b + 0x10)) = 0x200;
  *((u32 *) (r2b + 0x14)) = 0x200;
  setSpriteFlip(obj);
  setAnimationFrame(obj, r10, 0, 1);
  registerScriptObject((u8 *) new_var2, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * new_var2->f22)) + 0x19)) = zero;
  {
    u8 *p18;
    s32 *lit;
    p18 = ((u8 *) arg0) + 0x18;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4(p18, ((u8 *) arg0) + 0x22, *lit);
    *((u8 *) ((((u8 *) new_var2) + (2 * arg0->f22)) + 0x19)) = (*((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19))) + 1;
    p18 = p18 + (2 * arg0->f22);
    sub_080C31E0((u8 *) new_var2, *((u32 *) ((*((u32 *) (((u8 *) new_var2) + 0x14))) + (4 * (*((u8 *) p18))))));
  }
}
