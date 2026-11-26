struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct P { u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4]; struct E *f28; u8 _2C[0x1C]; u32 f48; };
struct BD { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x20]; };
extern struct BD gEffectGfxTable[];
extern u16 D_08102508[];
extern void *gMainObjTimerCallback;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void sub_08097DC8(void);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern s32 sub_080057F8(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
static inline int inline_fn(s32 arg0, int arg1) { return arg0 + arg1; }
static inline u16 orMode(u16 flags, u16 mask) { s32 tmp = mask; tmp |= flags; return tmp; }

void sub_080ADCA0(u8 *arg0)
{
  s32 a;
  struct P *p;
  unsigned short new_var;
  u8 *r7;
  u16 *t;
  u32 r;
  u8 *p18;
  void **fn;
  s32 one;
  u32 zero;
  struct E *e;
  u16 w;
  u8 *entry;
  u8 value;
  a = (s32) allocSpriteObject();
  if (a == 0) goto fail;
  *((u32 *) (arg0 + 0x38)) = a;
  allocWorkSlot(arg0, 0, 0x48, 0);
  if ((*((u32 *) (arg0 + 0x3C))) == 0) goto fail;
  one = 1;
  *((u32 *) inline_fn(a, 0x1C)) = one;
  p = (struct P *) (*((u8 * volatile *) (arg0 + 0x3C)));
  r7 = ((u8 *) p) + 0x34;
  installUpdateHandler(arg0, (u8 *) p, sub_08097DC8);
  zero = 0;
  p->f1C = 0x64;
  p->f8 = *((u32 *) (arg0 + 0x4C));
  new_var = 0xFFEF;
  p->fC = *((u32 *) (arg0 + 0x5C));
  r = findKindIndex(0x64);
  *((u16 *) ((u8 *) p + 0x22)) = (u16) r;
  if (((s16) r) < 0) goto fail;
  r = *((s16 *) (((u8 *) p) + 0x22));
  r = r << 6;
  r = r + 0x200;
  r &= 0xFC0;
  w = (u16) r;
  *((u16 *) a) = w;
  w |= gMainWorkspace.w;
  *((u16 *) a) = w;
  initSpriteGraphics((void *) a, r7, inline_fn((*((s16 *) (((u8 *) p) + 0x1C))) * 0xC, (s32) 0x080CD400));
  setAnimationFrame((void *) a, r7, 0, 0);
  t = D_08102508;
  e = allocEffectPart();
  p->f28 = e;
  if (e != NULL) goto cont;
  fail:
  sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
  return;
  cont:
  e->f1 = (u8) zero;
  p->f28->f2 = 8;
  p->f28->f3 = (u8) one;
  p->f28->f4 = gEffectGfxTable[*((s16 *) (((u8 *) p) + 0x1C))].f4;
  p->f28->f6 = t[0];
  p->f28->f8 = t[1];
  p->f28->fA = t[2];
  p->f28->fC = t[3];
  p->f28->fE = gEffectGfxTable[*((s16 *) (((u8 *) p) + 0x1C))].f6;
  p->f28->f10 = (u32) a;
  if (sub_080057F8() & one)
  {
    *((u16 *) inline_fn(a, 2)) |= 0x10;
  }
  else
  {
    *((u16 *) inline_fn(a, 2)) &= new_var;
  }
  *((u16 *) (arg0 + 2)) = orMode(*((u16 *) (arg0 + 2)), 0x1000);
  *((u8 *) inline_fn(inline_fn(((u32) (*((s16 *) (arg0 + 0x22)))) * 2, (u32) arg0), 0x19)) = (u8) zero;
  fn = (void **) (&gMainObjTimerCallback);
  p18 = arg0;
  p18 += 0x18;
  { void **__fence_fn; do { __fence_fn = fn; } while (0); sub_080C31E4(p18, (void *) (arg0 + 0x22), (s32) (*__fence_fn)); }
  *((u8 *) inline_fn(inline_fn(((u32) (*((s16 *) (arg0 + 0x22)))) * 2, (u32) arg0), 0x19)) += 1;
  entry = p18 + (*((s16 *) (arg0 + 0x22))) * 2;
  value = *entry;
  sub_080C31E0(arg0, ((void **) (*((u8 **) (arg0 + 0x14))))[value]);
}

