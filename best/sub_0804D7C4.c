extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlipForDirection(u8 *);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, u32);
extern u32 *gMainObjTimerCallbacks;
extern u8 gSpriteAnimDataTable[];
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
  u8 _56[0x5C - 0x56];
  u32 f5C;
  u8 _60[0x6C - 0x60];
  u32 f6C;
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
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x28 - 8];
};
extern struct TBL gEffectGfxTable[];
extern u16 D_080CF9D4[];
void sub_0804D7C4(struct Arg0 *arg0)
{
  u8 *new_var;
  u8 *p18;
  u8 *obj;
  struct P *r5;
  u8 *r9;
  u8 *s;
  s32 r0_3;
  u32 tmp;
  u32 zero;
  u8 *base;
  obj = allocSpriteObject();
  r5 = NULL;
  s = NULL;
  r0_3 = 0;
  if ((((obj == NULL) || ((arg0->f38 = obj, allocWorkSlot((u8 *) arg0, 0, 0x48, 0), r5 = arg0->f3C, r5 == NULL))) || ((r9 = ((u8 *) r5) + 0x34, r5->f24 = *((u32 *) (((u8 *) arg0) + 0x24)), *((u32 *) (((u8 *) arg0) + 0x24)) = 0x0804DBFD, zero = 0, r5->f1C = 0x4E, r5->f18 = 1, r5->f8 = arg0->f4C << 16, r5->fC = arg0->f54 << 16, r0_3 = findKindIndex(0x4E), r5->f22 = r0_3, ((s32) (r0_3 << 16)) < 0))) || ((initSpriteGraphics(obj, r9, ((s32) gSpriteAnimDataTable) + (r5->f1C * 0xC)), s = allocEffectPart(), r5->f28 = (struct E *) s, s == NULL)))
  {
    sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
    return;
  }
  r5->f28->f1 = zero;
  r5->f28->f2 = 8;
  r5->f28->f3 = 1;
  r5->f28->f4 = gEffectGfxTable[r5->f1C].f4;
  r5->f28->f6 = D_080CF9D4[0];
  r5->f28->f8 = D_080CF9D4[1];
  r5->f28->fA = D_080CF9D4[2];
  r5->f28->fC = D_080CF9D4[3];
  r5->f28->fE = gEffectGfxTable[r5->f1C].f6;
  r5->f28->f10 = (u32) obj;
  r5->f28->f14 = 0;
  tmp = ((*((u16 *) obj)) & 0xC00) | ((((*((s16 *) (((u8 *) r5) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) r5) + 0x22))) + 8) << 12));
  *((u16 *) obj) = tmp;
  *((u16 *) obj) = tmp | gMainWorkspace.f18C2;
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  base = (u8 *) (&gCameraState);
  {
    u32 k = 0x1278;
    *((u32 *) (obj + 0x14)) = r5->f8 - (((*((u32 *) ((base + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (obj + 0x18)) = r5->fC - (((*((u32 *) ((base + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  *((u32 *) (((u8 *) r5) + 0x10)) = arg0->f5C;
  *((u32 *) (((u8 *) r5) + 0x14)) = arg0->f6C;
  setSpriteFlipForDirection(obj);
  setAnimationFrame(obj, r9, 9, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = zero;
  {
    u32 *fp = (u32 *) 0x08671BB0;
    p18 = ((u8 *) arg0) + 0x18;
    sub_080C31E4(p18, ((u8 *) arg0) + 0x22, *fp);
  }
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = (*((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19))) + 1;
  new_var = (u8 *) arg0;
  p18 = p18 + (2 * arg0->f22);
  sub_080C31E0((u8 *) arg0, *((u32 *) ((*((u32 *) (new_var + 0x14))) + (4 * (*p18)))));
}
