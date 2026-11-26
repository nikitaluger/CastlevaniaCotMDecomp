extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void initSpawnedObject(u8 *, u8 *, u8 *, void *, s32);
extern void sub_080A5498(u8 *, u8 *, s32, s32);
extern void setObjectAnimation(u8 *, u8 *, s32, s32);
extern void loadEffectPalette(void *);
extern void *allocEffectPart(void);
extern s32 sub_0805FAEC(void *, s32);
extern void sub_080A5750(void);
extern void registerScriptObject(u8 *, s32);
extern void sub_080A3D34(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
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
};
struct Arg0
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x14 - 4];
  u8 *f14;
  u8 f18[10];
  s16 f22;
  u8 _24[0x38 - 0x24];
  u8 *f38;
  u8 *f3C;
  u8 _40[0xAC - 0x40];
  void *fAC;
};
struct TBL3
{
  u16 f0;
  s16 f2;
  u16 f4;
  u8 _6[0x14 - 6];
};
extern struct TBL3 gSpriteKindTable[];
extern u16 D_08101C20[];
extern u16 D_08101C50[];
extern u8 D_083DC89C[];
struct S_02025FF0
{
  u8 _0[0x1870];
  u32 v;
};
extern struct S_02025FF0 gMainWorkspace;
inline static u8 *inline_fn(u8 *arg0, s16 arg1)
{
  return (u8 *) (arg0 + (2 * arg1));
}

void sub_080A3044(struct Arg0 *a)
{
  struct Arg0 *arg0;
  u8 *obj;
  u8 *p;
  u8 *r4;
  u8 *r5;
  void *h;
  u8 *p18;
  struct TBL3 *tbl;
  u16 *data1;
  u16 *data2;
  tbl = gSpriteKindTable;
  arg0 = a;
  h = arg0->fAC;
  obj = allocSpriteObject();
  if (obj == NULL)
  {
    goto fail0;
  }
  goto ok0;
  fail0:
  sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

  return;
  ok0:
  arg0->f38 = obj;

  allocWorkSlot((u8 *) arg0, 0, 0xB8, 0);
  if ((*((volatile u32 *) (((u8 *) arg0) + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  p = arg0->f3C;
  r4 = p + 0x34;
  r5 = p + 0x48;
  installUpdateHandler((u8 *) arg0, p, (void *) sub_080A3D34);
  initSpawnedObject((u8 *) arg0, obj, p, h, 0x59);
  sub_080A5498(obj, r4, 0x70, 8);
  setObjectAnimation(obj, r4, 4, 1);
  loadEffectPalette(D_083DC89C);
  data1 = D_08101C20;
  *((void **) (p + 0x28)) = allocEffectPart();
  if ((*((void **) (p + 0x28))) == NULL)
  {
    goto fail;
  }
  ((struct E *) (*((void **) (p + 0x28))))->f1 = 5;
  ((struct E *) (*((void **) (p + 0x28))))->f2 = 8;
  ((struct E *) (*((void **) (p + 0x28))))->f3 = 1;
  ((struct E *) (*((void **) (p + 0x28))))->f4 = tbl[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (p + 0x28))))->f6 = data1[0];
  ((struct E *) (*((void **) (p + 0x28))))->f8 = data1[1];
  ((struct E *) (*((void **) (p + 0x28))))->fA = data1[2];
  ((struct E *) (*((void **) (p + 0x28))))->fC = data1[3];
  ((struct E *) (*((void **) (p + 0x28))))->fE = tbl[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (p + 0x28))))->f10 = (u32) obj;
  *((void **) (r5 + 0x50)) = allocEffectPart();
  if ((*((void **) (r5 + 0x50))) == NULL)
  {
    goto fail;
  }
  ((struct E *) (*((void **) (r5 + 0x50))))->f1 = 5;
  ((struct E *) (*((void **) (r5 + 0x50))))->f2 = 8;
  ((struct E *) (*((void **) (r5 + 0x50))))->f3 = 1;
  ((struct E *) (*((void **) (r5 + 0x50))))->f4 = tbl[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (r5 + 0x50))))->f6 = data1[4];
  ((struct E *) (*((void **) (r5 + 0x50))))->f8 = data1[5];
  ((struct E *) (*((void **) (r5 + 0x50))))->fA = data1[6];
  ((struct E *) (*((void **) (r5 + 0x50))))->fC = data1[7];
  ((struct E *) (*((void **) (r5 + 0x50))))->fE = tbl[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (r5 + 0x50))))->f10 = (u32) obj;
  data2 = D_08101C50;
  *((void **) (r5 + 0x54)) = allocEffectPart();
  if ((*((void **) (r5 + 0x54))) == NULL)
  {
    goto fail;
  }
  ((struct E *) (*((void **) (r5 + 0x54))))->f1 = 0;
  ((struct E *) (*((void **) (r5 + 0x54))))->f2 = 8;
  ((struct E *) (*((void **) (r5 + 0x54))))->f3 = 1;
  ((struct E *) (*((void **) (r5 + 0x54))))->f4 = tbl[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (r5 + 0x54))))->f6 = data2[0];
  ((struct E *) (*((void **) (r5 + 0x54))))->f8 = data2[1];
  ((struct E *) (*((void **) (r5 + 0x54))))->fA = data2[2];
  ((struct E *) (*((void **) (r5 + 0x54))))->fC = data2[3];
  ((struct E *) (*((void **) (r5 + 0x54))))->fE = tbl[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (r5 + 0x54))))->f10 = (u32) obj;
  *((void **) (r5 + 0x58)) = allocEffectPart();
  if ((*((void **) (r5 + 0x58))) != NULL)
  {
    goto body;
  }
  fail:
  sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

  return;
  body:
  ((struct E *) (*((void **) (r5 + 0x58))))->f1 = 0;

  ((struct E *) (*((void **) (r5 + 0x58))))->f2 = 8;
  ((struct E *) (*((void **) (r5 + 0x58))))->f3 = 1;
  ((struct E *) (*((void **) (r5 + 0x58))))->f4 = tbl[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (r5 + 0x58))))->f6 = data2[4];
  ((struct E *) (*((void **) (r5 + 0x58))))->f8 = data2[5];
  ((struct E *) (*((void **) (r5 + 0x58))))->fA = data2[6];
  ((struct E *) (*((void **) (r5 + 0x58))))->fC = data2[7];
  ((struct E *) (*((void **) (r5 + 0x58))))->fE = tbl[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (r5 + 0x58))))->f10 = (u32) obj;
  *((s32 *) (r5 + 0x48)) = sub_0805FAEC((void *) gMainWorkspace.v, 0x196);
  *((s32 *) (r5 + 0x4C)) = sub_0805FAEC(arg0, 0x198);
  *((s32 *) (r5 + 0x60)) = 1;
  sub_080A5750();
  *((u16 *) (p + 4)) |= 0x100;
  registerScriptObject((u8 *) arg0, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = 0;
  {
    s32 *st = (s32 *) 0x08671BB0;
    p18 = ((u8 *) arg0) + 0x18;
    sub_080C31E4(p18, ((u8 *) arg0) + 0x22, *st);
  }
  *((u8 *) ((((u8 *) arg0) + ((char) (2 * arg0->f22))) + 0x19)) += 1;
  do
  {
    do
    {
      do
      {
        sub_080C31E0((u8 *) arg0, *((s32 *) (arg0->f14 + ((*inline_fn(p18, arg0->f22)) * 4))));
      }
      while (0);
    }
    while (0);
  }
  while (0);
}

