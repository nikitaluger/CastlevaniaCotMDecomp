struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct P {
  u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u32 f18; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
  struct E *f28; u8 _2C[8]; u16 a34; u16 a36; u16 a38; u16 a3A;
};
struct Sarg {
  u16 f0; u16 f2; u8 _4[0x14-0x4]; void *f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A];
  s16 f22; void *f24; u8 _28[0x38-0x28]; void *f38; void * volatile f3C;
  u8 _40[0x4C-0x40]; u32 f4C; u8 _50[0x1C]; u32 f6C;
};
struct BD { u8 _0[4]; u16 f4; u16 f6; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct BD gEffectGfxTable[];
extern u16 D_08101A58[];
extern void *gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

void sub_080A19B0(struct Sarg *arg0) {
  struct P *new_var;
  s32 a;
  struct P *p;
  u8 *aux;
  u8 *tbl;
  u32 r;
  u8 *p18;
  void **fn;
  u8 *q;
  u32 one;

  a = (s32) allocSpriteObject();
  if (a == 0) goto fail;
  arg0->f38 = (void *) a;
  allocWorkSlot(arg0, 0, 0x48, 0);
  if (arg0->f3C == NULL) goto fail;
  *((u32 *)(a + 0x1C)) = 0x80000009;
  p = (struct P *) arg0->f3C;
  aux = ((u8 *)p) + 0x34;
  installUpdateHandler(arg0, (u8 *)p, updateActorEffectSubObject);
  p->f1C = 0x54;
  one = 1;
  p->f18 = one;
  p->f10 = (arg0->f6C * 9) << 15;
  p->f14 = 0x14000;
  r = findKindIndex(0x54);
  p->f22 = r;
  if (((s16)r) < 0) goto fail;
  r = p->f22;
  r = r << 6;
  r = r + 0x200;
  new_var = p;
  r &= 0xFC0;
  *((u16 *)a) = r;
  *((u16 *)a) |= gMainWorkspace.w;
  initSpriteGraphics((void *)a, aux, (p->f1C * 0xC) + ((u32)0x080CD400));
  setAnimationFrame((void *)a, aux, 6, 0);
  tbl = (u8 *) D_08101A58;
  p->f28 = allocEffectPart();
  if (p->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(arg0, arg0->f24);
  return;
ok:
  p->f28->f1 = one;
  p->f28->f2 = 8;
  p->f28->f3 = one;
  p->f28->f4 = gEffectGfxTable[p->f1C].f8;
  p->f28->f6 = *((u16 *)tbl);
  p->f28->f8 = *((u16 *)(tbl + 2));
  p->f28->fA = *((u16 *)(tbl + 4));
  p->f28->fC = *((u16 *)(tbl + 6));
  p->f28->fE = gEffectGfxTable[p->f1C].fA;
  new_var->f28->f10 = (void *)a;
  arg0->f2 |= 0x1000;
  {
    s16 idx = arg0->f22;
    *((u8 *)(((u32)idx * 2) + (u32)arg0 + 0x19)) = 0;
  }
  fn = &gMainObjTimerCallbacks;
  p18 = ((u8 *)arg0) + 0x18;
  sub_080C31E4(p18, ((u8 *)arg0) + 0x22, (s32)(*fn));
  {
    s16 idx = arg0->f22;
    *((u8 *)(((u32)idx * 2) + (u32)arg0 + 0x19)) += 1;
    idx = arg0->f22;
    q = p18 + ((u32)idx * 2);
    sub_080C31E0(arg0, *((void **)(arg0->f14 + ((*q) * 4))));
  }
}
