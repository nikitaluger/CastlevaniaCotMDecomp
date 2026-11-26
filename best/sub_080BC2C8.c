struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 gMainWorkspace;
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
  s16 fE;
  u32 f10;
};
struct P
{
  u8 _0[8];
  u32 f8;
  u32 fC;
  u32 f10;
  u32 f14;
  u8 _18[4];
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u8 _24[4];
  struct E *f28;
};
struct BD
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct BD gEffectGfxTable[];
extern u16 D_08102F10[];
extern u16 D_08102F1C[];
extern u32 gMainObjTimerCallback;
void *allocSpriteObject(void);
void allocWorkSlot(void *, s32, s32, s32);
s32 sub_080057F8(void);
s32 sub_08005820(s32);
s32 sub_0800583C(s32);
void initSpriteGraphics(void *, s32, s32);
void setAnimationFrame(void *, s32, s32, s32);
s32 findKindIndex(s16);
void installUpdateHandler(void *, void *, void *);
void *allocEffectPart(void);
void sub_080BC73C(void *, void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08097DC8(void);
void sub_080BC2C8(u8 *arg0)
{
  u8 *r5 = arg0;
  u8 *new_var7;
  u8 *r6;
  struct P *r4;
  struct P *r4_copy;
  u8 *r7;
  u8 *new_var;
  u8 *new_var5;
  s16 idx;
  s32 r;
  int new_var2;
  u32 fn_ptr;
  unsigned long new_var4;
  int new_var3;
  u8 *arg22;
  u16 new_var6;
  u16 *tab;
  struct E *e;
  new_var7 = r5 + 0x24;
  r6 = allocSpriteObject();
  if (r6 == 0)
  {
    sub_080C31E0(r5, *((u32 *) new_var7));
    return;
  }
  *((u32 *) (r5 + 0x38)) = (u32) r6;
  allocWorkSlot(r5, 0, 0x48, 0);
  if ((*((u32 *) (r5 + 0x3C))) == 0)
  {
    sub_080C31E0(r5, *((u32 *) (r5 + 0x24)));
    return;
  }
  *((u32 *) (r6 + 0x1C)) = 0x80000009;
  r4 = (struct P *) (*((u32 *) (r5 + 0x3C)));
  r7 = ((u8 *) r4) + 0x34;
  installUpdateHandler(r5, r4, sub_08097DC8);
  r4->f1C = 0x68;
  r = findKindIndex((s16) r4->f1C);
  new_var3 = (r << 16) < 0;
  r4->f22 = (s16) r;
  if ((r << 16) < 0)
  {
    sub_080C31E0(r5, *((u32 *) new_var7));
    return;
  }
  r4_copy = r4;
  idx = r4_copy->f22;
  r = ((idx << 6) + 0x200) & 0xFC0;
  new_var6 = (u16) r;
  *((u16 *) r6) = new_var6;
  *((u16 *) r6) |= gMainWorkspace.w;
  initSpriteGraphics(r6, (s32) r7, (s32) D_08102F10);
  setAnimationFrame(r6, (s32) r7, 0, 1);
  tab = D_08102F1C;
  e = allocEffectPart();
  r4_copy->f28 = e;
  if (e == 0)
  {
    sub_080C31E0(r5, *((u32 *) (r5 + 0x24)));
    return;
  }
  r4_copy->f28->f1 = 5;
  r4_copy->f28->f2 = 8;
  r4_copy->f28->f3 = 1;
  idx = r4_copy->f1C;
  r4_copy->f28->f4 = gEffectGfxTable[idx].f4;
  r4_copy->f28->f6 = tab[0];
  r4_copy->f28->f8 = tab[1];
  r4_copy->f28->fA = tab[2];
  r4_copy->f28->fC = tab[3];
  r4_copy->f28->fE = gEffectGfxTable[r4_copy->f1C].f6;
  r4_copy->f28->f10 = (u32) r6;
  new_var = r5 + 0x7C;
  new_var2 = 2;
  new_var4 = 0x8C;
  *((u32 *) (r5 + 0x6C)) = sub_08005820(0x200000) - (-0x100000);
  *((u32 *) new_var) = 0xFFFF & sub_080057F8();
  r = (*((s32 *) (r5 + 0x8C)) = sub_0800583C(0x180));
  if (r < 0)
  {
    r = r - 0x80;
  }
  else
  {
    r = r + 0x80;
  }
  *((s32 *) (r5 + new_var4)) = r;
  *((u32 *) (r5 + 0x5C)) = 1;
  *((u32 *) (r5 + 0x9C)) = 0;
  sub_080BC73C(r5, r6);
  {
    s16 i;
    u16 flags;
    u8 *base;
    u32 fp;
    flags = *((u16 *) (r5 + 2));
    *((u16 *) (r5 + 2)) = flags | 0x1000;
    i = *((s16 *) (r5 + 0x22));
    *((u8 *) (r5 + i * 2 + 0x19)) = 0;
    fp = (s32)&gMainObjTimerCallback;
    base = r5 + 0x18;
    sub_080C31E4(base, r5 + 0x22, fp);
    i = *((s16 *) (r5 + 0x22));
    *((u8 *) (r5 + i * 2 + 0x19)) += 1;
    i = *((s16 *) (r5 + 0x22));
    sub_080C31E0(r5, *((u32 *) (*((u32 *) (r5 + 0x14)) + *((u8 *) (base + (i << 1))) * 4)));
  }
}
