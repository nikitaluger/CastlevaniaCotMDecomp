#define V1C (*(s16 *)(p + 0x1C))
#define CB2V(o) (*(u16 *)((cb = gSpriteKindTable) + V1C * 20 + (o)))
struct A5R
{
  u8 f0;
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
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initSpawnedObject(void *, void *, void *, u32, u32);
extern void sub_080AA9C8(void *, void *, u32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080A80B4(void *, void *);
extern void *sub_0805FAEC(void *, u32);
extern void sub_080AAD08(void);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_0810201C[];
extern u16 D_08101D1C[];
extern u8 gSpriteKindTable[];
extern u8 gEffectGfxTable[];
extern u32 gMainWorkspace[];
extern void *gMainObjTimerCallback;
extern void sub_080A806C(void);
void sub_080A5AE0(u8 *arg0)
{
  u8 *p;
  void *a;
  u32 r8v;
  u8 *cb;
  u8 *p34;
  u8 *idxp;
  void *sp4;
  u8 *d1c;
  u8 *p18;
  u8 *tbl;
  u8 *cbddbase;
  r8v = *((u32 *) (arg0 + 0xAC));
  a = allocSpriteObject();
  if (a == NULL)
  {
    goto fail;
  }
  *((void **) (arg0 + 0x38)) = a;
  allocWorkSlot(arg0, 0, 0x188, 0);
  if ((*((void **) (arg0 + 0x3C))) == NULL)
  {
    goto fail;
  }
  *((void **) (((u8 *) a) + 0x1C)) = (void *) 1;
  p = (u8 *) (*((u32 *) (arg0 + 0x3C)));
  p34 = p + 0x34;
  sp4 = p + 0x48;
  installUpdateHandler(arg0, p, sub_080A806C);
  initSpawnedObject(arg0, a, p, r8v, 0x5F);
  tbl = D_0810201C;
  cbddbase = gEffectGfxTable;
  idxp = arg0 + 0x4C;
  sub_080AA9C8(a, p34, tbl[*idxp], 4);
  setObjectAnimation(a, p34, 0, 0);
  d1c = (u8 *) D_08101D1C;
  if ((*((void **) (p + 0x28)) = allocEffectPart()) == NULL)
  {
    goto fail;
  }
  ((struct A5R *) (*((void **) (p + 0x28))))->f1 = 5;
  ((struct A5R *) (*((void **) (p + 0x28))))->f2 = 8;
  ((struct A5R *) (*((void **) (p + 0x28))))->f3 = 1;
  ((struct A5R *) (*((void **) (p + 0x28))))->f4 = CB2V(0);
  ((struct A5R *) (*((void **) (p + 0x28))))->f6 = *((u16 *) (d1c + 0));
  ((struct A5R *) (*((void **) (p + 0x28))))->f8 = *((u16 *) (d1c + 2));
  ((struct A5R *) (*((void **) (p + 0x28))))->fA = *((u16 *) (d1c + 4));
  ((struct A5R *) (*((void **) (p + 0x28))))->fC = *((u16 *) (d1c + 6));
  ((struct A5R *) (*((void **) (p + 0x28))))->fE = *((u16 *) ((cb + (V1C * 20)) + 4));
  ((struct A5R *) (*((void **) (p + 0x28))))->f10 = (u32) a;
  p34 = d1c + 8;
  if ((*((void **) (p + 0x15C)) = allocEffectPart()) == NULL)
  {
    fail:
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));

  }
  else
  {
    ((struct A5R *) (*((void **) (p + 0x15C))))->f1 = 5;
    ((struct A5R *) (*((void **) (p + 0x15C))))->f2 = 8;
    ((struct A5R *) (*((void **) (p + 0x15C))))->f3 = 1;
    ((struct A5R *) (*((void **) (p + 0x15C))))->f4 = *((u16 *) (cb + (V1C * 20)));
    ((struct A5R *) (*((void **) (p + 0x15C))))->f6 = *((u16 *) (d1c + 8));
    ((struct A5R *) (*((void **) (p + 0x15C))))->f8 = *((u16 *) (p34 + 2));
    ((struct A5R *) (*((void **) (p + 0x15C))))->fA = *((u16 *) (p34 + 4));
    ((struct A5R *) (*((void **) (p + 0x15C))))->fC = *((u16 *) (p34 + 6));
    ((struct A5R *) (*((void **) (p + 0x15C))))->fE = *((u16 *) ((cb + (V1C * 20)) + 4));
    ((struct A5R *) (*((void **) (p + 0x15C))))->f10 = (u32) a;
    sub_080A80B4(arg0, sp4);
    if ((*idxp) == 0)
    {
      *((void **) (p + 0x180)) = sub_0805FAEC(arg0, 0x19D);
    }
    {
      void *t;
      t = sub_0805FAEC((void *) gMainWorkspace[0x1870 / 4], 0x1A3);
      *((void **) (p + 0x184)) = t;
      *((u32 *) (((u8 *) t) + 0x4C)) = *idxp;
    }
    sub_080AAD08();
    *((u16 *) (p + 0x04)) |= 0x100;
    *((u8 *) (arg0 + 0x7C)) = 0;
    *((u32 *) (arg0 + 0x8C)) = *((u32 *) (p + 0x18));
    *((u32 *) ((*((u32 *) (arg0 + 0x28))) + 0x5C)) = *((s16 *) ((cbddbase + (V1C * 40)) + 0x24));
    registerScriptObject(arg0, 0);
    *((u16 *) (arg0 + 0x02)) |= 0x1000;
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19] = 0;
    do { p18 = arg0 + 0x18; } while (0);
    do { sub_080C31E4(p18, arg0 + 0x22, gMainObjTimerCallback); } while (0);
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19]++;
    p = (void *) (*((s16 *) (arg0 + 0x22))); p18 += (u32) p * 2;
    do { sub_080C31E0(arg0, *((void **) ((*((u32 *) (arg0 + 0x14))) + (p18[0] * 4)))); } while (0);
  }
}

