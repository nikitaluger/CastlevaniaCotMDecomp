#define V1C (*(s16 *)(p + 0x1C))
#define CB2X (((struct CB2 *)(gSpriteKindTable + V1C * 20))->f0)
#define CB2B (((struct CB2 *)(gSpriteKindTable + V1C * 20))->f4)
struct B7R
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
struct CB2
{
  u16 f0;
  u16 f2;
  u16 f4;
  u16 f6;
};
struct D20
{
  u8 pad[0x40];
  u32 f40;
};
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initWorkStateForKind(void *, void *, void *, u32, u32);
extern void installUpdateHandler(void *, void *, void *);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void loadEffectPalette(u32);
extern void sub_080036C0(s32);
extern void *allocEffectPart(void);
extern void spawnChainedEffectObjects(void *, s32, s32, u32);
extern void *spawnBudgetedEffect(void *, u32);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u16 D_08102DA4[];
extern u8 gSpriteKindTable[];
extern u8 gSpriteAnimDataTable[];
extern struct D20 gMainWorkspace;
extern void *gMainObjTimerCallbacks;
extern void sub_080B8514(void);
inline static void *inline_fn(u8 *arg0)
{
  return spawnBudgetedEffect(arg0, 0x1CB);
}

void sub_080B76A4(u8 *arg0)
{
  u8 *p34;
  u8 *p;
  void *new_var;
  u8 *p48;
  void *a;
  u32 r9v;
  u8 *d1c;
  u8 *d1c8;
  u8 *p18;
  u32 eight;
  u8 *cb;
  void **new_var2;
  r9v = *((u32 *) (arg0 + 0xAC));
  eight = 8;
  a = allocSpriteObject();
  if (a == NULL)
  {
    goto fail;
  }
  *((void **) (arg0 + 0x38)) = a;
  allocWorkSlot(arg0, 0, 0x54, 0);
  if ((*((u32 * volatile) (arg0 + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (((u8 *) a) + 0x1C)) = eight;
  p = *((u8 **) (arg0 + 0x3C));
  p34 = p + 0x34;
  p48 = p + 0x48;
  installUpdateHandler(arg0, p, sub_080B8514);
  initWorkStateForKind(arg0, a, p, r9v, 0x67);
  initSpriteGraphics(a, p34, gSpriteAnimDataTable + (V1C * 12));
  setAnimationFrame(a, p34, 0, 0);
  loadEffectPalette(0x0841EA84);
  sub_080036C0(0x0A);
  d1c = (u8 *) D_08102DA4;
  if ((*((void **) (p + 0x28)) = allocEffectPart()) == NULL)
  {
    goto fail;
  }
  ((struct B7R *) (*((void **) (p + 0x28))))->f1 = 5;
  ((struct B7R *) (*((void **) (p + 0x28))))->f2 = eight;
  ((struct B7R *) (*((void **) (p + 0x28))))->f3 = 1;
  ((struct B7R *) (*((void **) (p + 0x28))))->f4 = CB2X;
  ((struct B7R *) (*((void **) (p + 0x28))))->f6 = *((u16 *) (d1c + 0));
  ((struct B7R *) (*((void **) (p + 0x28))))->f8 = *((u16 *) (d1c + 2));
  ((struct B7R *) (*((void **) (p + 0x28))))->fA = *((u16 *) (d1c + 4));
  ((struct B7R *) (*((void **) (p + 0x28))))->fC = *((u16 *) (d1c + 6));
  ((struct B7R *) (*((void **) (p + 0x28))))->fE = CB2B;
  ((struct B7R *) (*((void **) (p + 0x28))))->f10 = (u32) a;
  d1c8 = d1c + 8;
  cb = gSpriteKindTable;
  if ((*((void **) (p48 + 4)) = allocEffectPart()) == NULL)
  {
    fail:
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));

  }
  else
  {
    ((struct B7R *) (*((void **) (p48 + 4))))->f1 = 5;
    ((struct B7R *) (*((void **) (p48 + 4))))->f2 = eight;
    ((struct B7R *) (*((void **) (p48 + 4))))->f3 = 1;
    ((struct B7R *) (*((void **) (p48 + 4))))->f4 = CB2X;
    ((struct B7R *) (*((void **) (p48 + 4))))->f6 = *((u16 *) (d1c + 8));
    ((struct B7R *) (*((void **) (p48 + 4))))->f8 = *((u16 *) (d1c8 + 2));
    ((struct B7R *) (*((void **) (p48 + 4))))->fA = *((u16 *) (d1c8 + 4));
    new_var = *((void **) (p48 + 4));
    ((struct B7R *) new_var)->fC = *((u16 *) (d1c8 + 6));
    ((struct B7R *) new_var)->fE = CB2B;
    ((struct B7R *) (*((void **) (p48 + 4))))->f10 = (u32) a;
    spawnChainedEffectObjects(arg0, 2, 10, *((u32 *) (((u8 *) a) + 0x1C)));
    *((void **) (p + 0x48)) = inline_fn(arg0);
    gMainWorkspace.f40 = 0;
    registerScriptObject(arg0, 0);
    *((u16 *) (arg0 + 0x02)) |= 0x1000;
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19] = 0;
    p18 = arg0 + 0x18;
    new_var2 = (void **) gMainObjTimerCallbacks;
    sub_080C31E4(p18, arg0 + 0x22, *new_var2);
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19]++;
    p18 += (*((s16 *) (arg0 + 0x22))) * 2;
    sub_080C31E0(arg0, *((void **) ((*((u32 *) (arg0 + 0x14))) + (p18[0] * 4))));
  }
}

