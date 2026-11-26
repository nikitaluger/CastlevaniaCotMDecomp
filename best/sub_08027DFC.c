extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, u32, u32);
extern volatile long findKindIndex(s16);
extern void setSpriteFlip(void *);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, u32);
extern void sub_080284E8(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080284B8(void);
extern volatile u32 gSpriteKindTable[];
extern volatile u32 gSpriteAnimDataTable[];
extern volatile u16 D_080CE940[];
extern volatile u8 gCameraState[];
extern volatile u8 gMainWorkspace[];
extern void *gMainObjTimerCallback[];
inline u8 *inline_fn(u8 *arg0, int arg1)
{
  return arg0 + arg1;
}

inline u8 **inline_fn2(u8 *arg0)
{
  return (u8 **) inline_fn(arg0, 0x28);
}

inline u32 inline_fn23(volatile u8 *arg0, u32 arg1)
{
  return *((u32 *) inline_fn(inline_fn(arg0, 0x1278), arg1));
}

void sub_08027DFC(u8 *arg0)
{
  u8 *new_var11;
  void *new_var9;
  u8 *p6;
  int new_var14;
  u8 *new_var22;
  u8 *p8;
  u8 *cb2;
  u16 *new_var21;
  u8 *new_var19;
  unsigned int h;
  u16 t;
  void **new_var15;
  u32 idx;
  u16 *new_var3;
  u32 val;
  s16 *new_var4;
  u8 *new_var17;
  int new_var10;
  unsigned int new_var8;
  s16 new_var2;
  u8 **new_var5;
  u8 *new_var20;
  u32 new_var12;
  volatile u8 *new_var7;
  volatile u32 *new_var6;
  u32 *new_var23;
  void *new_var18;
  u32 zero;
  u32 hi = 0x8000;
  unsigned int new_var;
  unsigned int new_var13;
  int new_var16;
  arg0 = *((u8 **) inline_fn(arg0, 0xAC));
  new_var18 = allocSpriteObject();
  zero = 0;
  new_var20 = new_var18;
  if (new_var20 == NULL)
  {
    sub_080C31E0(arg0, *((void **) inline_fn(arg0, 0x24)));
    return;
  }
  *((void **) inline_fn(arg0, 0x38)) = new_var20;
  allocWorkSlot(arg0, 0, 0x90, 0);
  new_var12 = (u32) ((s32) (*((s16 *) inline_fn(arg0, 2))));
  do
  {
    p6 = *((u8 **) inline_fn(arg0, 0x3C));
    if (p6 == NULL)
    {
      sub_080C31E0(arg0, *((void **) inline_fn(arg0, 0x24)));
      return;
    }
    new_var6 = gSpriteAnimDataTable;
    p8 = inline_fn(p6, 0x34);
    *((void **) inline_fn(p6, 0x24)) = *((void **) inline_fn(arg0, 0x24));
    new_var15 = &arg0;
    *((u32 *) inline_fn(*new_var15, 0x24)) = (u32) sub_080284B8;
    cb2 = (u8 *) gSpriteKindTable;
    switch (*((s16 *) inline_fn(arg0, 4)))
    {
      case 0xB3:
        *((u16 *) inline_fn(p6, 0x1C)) = 0x56;
        break;

      case 0xB4:
        *((u16 *) inline_fn(p6, 0x1C)) = 0x6F;
        break;

    }

    *((u32 *) inline_fn(p6, 0x18)) = (u32) (*((s16 *) inline_fn(inline_fn(cb2, ((s32) (*((s16 *) inline_fn(p6, 0x1C)))) * 0x14), 2)));
  }
  while (0);
  new_var3 = (u16 *) inline_fn(p8, 0x24);
  *((u32 *) inline_fn(p6, 8)) = ((u32) ((s32) (*((s16 *) inline_fn(arg0, 0))))) << 16;
  *((u32 *) inline_fn(p6, 0xC)) = new_var12;
  *((u32 *) inline_fn(p6, 0xC)) = (*((u32 *) inline_fn(p6, 0xC))) << 16;
  h = findKindIndex(*((s16 *) inline_fn(p6, 0x1C)));
  *((u16 *) inline_fn(p6, 0x22)) = (u16) h;
  new_var16 = 16;
  new_var22 = inline_fn(p6, 0x28);
  if (((s32) (((u32) h) << new_var16)) < 0)
  {
    new_var7 = new_var7;
    sub_080C31E0(arg0, *((void **) inline_fn(arg0, 0x24)));
    return;
  }
  initSpriteGraphics(new_var20, p8, inline_fn((u8 *) new_var6, ((s32) (*((s16 *) inline_fn(p6, 0x1C)))) * 12));
  new_var = 1;
  new_var15 = (void **) inline_fn(p6, 0x28);
  *((void **) inline_fn(p6, 0x28)) = allocEffectPart();
  new_var19 = (u8 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 1);
  if ((*new_var15) == NULL)
  {
    do
    {
    }
    while (0);
    sub_080C31E0(arg0, *((void **) inline_fn(arg0, 0x24)));
    h = new_var2;
    do
    {
      return;
    }
    while (0);
  }
  new_var17 = *((u8 **) inline_fn(p6, 0x28));
  *new_var19 = zero;
  *((u8 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 2)) = 8;
  *((u8 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 3)) = 1;
  *((u16 *) inline_fn(new_var17, 4)) = *((u16 *) inline_fn(cb2, ((s32) (*((s16 *) inline_fn(p6, 0x1C)))) * 0x14));
  *((u16 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 6)) = D_080CE940[0];
  new_var21 = (u16 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 0xA);
  new_var7 = gMainWorkspace;
  *((u16 *) inline_fn(*((u8 **) inline_fn(p6, 0x28)), 8)) = D_080CE940[new_var];
  new_var8 = D_080CE940[2];
  *new_var21 = new_var8;
  new_var10 = 0x22;
  *((u16 *) inline_fn(*((u8 **) new_var22), 0xC)) = D_080CE940[3];
  new_var5 = &(*inline_fn2(p6));
  *((u16 *) inline_fn(*new_var5, 0xE)) = *((u16 *) inline_fn(inline_fn(cb2, ((s32) (*((s16 *) inline_fn(p6, 0x1C)))) * 0x14), 4));
  new_var2 = *((s16 *) inline_fn(p6, new_var10));
  *((void **) inline_fn(*inline_fn2(p6), 0x10)) = new_var20;
  *((u16 *) inline_fn(*inline_fn2(p6), 0x14)) = zero;
  t = (*((u16 *) new_var20)) & 0xC00;
  new_var13 = (u16) (((u32) ((s32) h)) << 6);
  t = t | 0x200;
  t |= (u16) (((u32) ((u16) (8 + (*((u16 *) inline_fn(p6, new_var10)))))) << 12);
  t |= new_var13;
  t |= *((u16 *) inline_fn(gMainWorkspace, 0x18C2));
  new_var23 = (u32 *) inline_fn(new_var20, 0x14);
  *((u16 *) new_var20) = t;
  new_var11 = inline_fn(p6, 0xC);
  *((u32 *) inline_fn(new_var20, 0x1C)) = 0x8000000A;
  idx = ((u32) ((*((u8 *) inline_fn(new_var7, 0x18A8))) + 1)) << 6;
  val = inline_fn23(gCameraState, idx);
  *new_var23 = (*((u32 *) inline_fn(p6, 8))) - ((val + hi) & 0xFFFF0000);
  val = *((u32 *) inline_fn(inline_fn(gCameraState, 0x127C), idx));
  *((u32 *) inline_fn(new_var20, 0x18)) = (*((u32 *) inline_fn(p6, 0xC))) - ((0xFFFF8000 + val) & 0xFFFF0000);
  new_var4 = (s16 *) inline_fn(arg0, new_var10);
  *((u32 *) inline_fn(p8, 0x14)) = *((u32 *) inline_fn(p6, 8));
  *((u32 *) inline_fn(p8, 0x18)) = *((u32 *) new_var11);
  *new_var3 = zero;
  *((u32 *) inline_fn(p8, 0x2C)) = zero;
  sub_080284E8(arg0);
  *((u32 *) inline_fn(p8, 0x30)) = zero;
  *((u32 *) inline_fn(p8, 0x34)) = (!((*((s16 *) inline_fn(p8, 0x24))) == 1)) ? (zero) : (hi);
  *((u32 *) inline_fn(p8, 0x38)) = zero;
  *((u32 *) inline_fn(p8, 0x3C)) = 0x14000;
  *((u32 *) inline_fn(p8, 0x40)) = 0x1000;
  *((u32 *) inline_fn(p8, 0x44)) = 0x1000;
  new_var20 = arg0;
  setSpriteFlip(new_var20);
  setAnimationFrame(new_var20, p8, zero, 1);
  registerScriptObject(new_var20, 0);
  *((u16 *) inline_fn(arg0, 2)) |= 0x1000;
  *((u8 *) inline_fn(inline_fn(arg0, ((s32) (*((s16 *) inline_fn(arg0, new_var10)))) * 2), 0x19)) = 0;
  new_var9 = *gMainObjTimerCallback;
  sub_080C31E4(inline_fn(arg0, 0x18), inline_fn(arg0, new_var10), *gMainObjTimerCallback);
  new_var14 = ((s32) (*((s16 *) inline_fn(arg0, new_var10)))) * 2;
  ++(*((u8 *) inline_fn(inline_fn(arg0, new_var14), 0x19)));
  sub_080C31E0(arg0, *((void **) ((*((u32 *) inline_fn(arg0, 0x14))) + (((u32) (*((u8 *) inline_fn(inline_fn(arg0, 0x18), ((s32) (*new_var4)) * 2)))) * 4))));
}

