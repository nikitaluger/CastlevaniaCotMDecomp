extern void sub_08003740(void *a);
extern void sub_08005E80(s32 a);
extern void sub_080168C4(void);
extern void *sub_080168F8(void);
extern void sub_0806D330(void *a, void *b);
extern s32 sub_0806D518(void *a, void *b, void *c);
extern void sub_0806D588(void *a, void *b);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern u8 D_02025FF0[];
extern u8 D_000018C2[];
extern u8 D_0000173A[];
extern u8 D_000014ED[];
struct MainObj
{
  u8 _00[0x14];
  u32 scriptTable;
  u8 _18[0x0A];
  s16 index;
  u32 updateCb;
  u8 _28[0x10];
  u32 target;
  u8 _3C[0x30];
  u32 state;
};
struct EffectHeader
{
  u8 _00[0x04];
  s32 f04;
  u8 _08[0x18];
  u32 f20;
};
struct GfxDesc
{
  u8 _00[0x16];
  u16 f16;
};
struct EffectState
{
  u8 _00[0x04];
  s32 f04;
  s32 f08;
  s32 f0C;
  s32 f10;
  s32 f14;
  u8 _18[0x14];
  struct GfxDesc *gfx;
  u8 _30[0x1C];
  void *f4C;
  u8 f50;
};
struct Target
{
  u16 f00;
};
void sub_0807A24C(struct MainObj *arg0)
{
  struct EffectHeader *x;
  struct EffectState *y;
  struct Target *z;
  struct EffectState *w;
  u8 *v;
  void *t;
  u8 b;
  s32 *g;
  x = (struct EffectHeader *) arg0->state;
  y = (struct EffectState *) (((u8 *) x) + 4);
  z = (struct Target *) arg0->target;
  w = y;
  if (sub_0806D518(arg0, z, w) != 0)
  {
    return;
  }
  w->f0C = w->f0C + 0x4000;
  if (w->f0C > 0x80000)
  {
    w->f0C = 0x80000;
  }
  x->f04 = x->f04 + w->f08;
  w->f04 = w->f04 + w->f0C;
  w->f14 = w->f14 - 1;
  if (w->f14 == 0)
  {
    sub_08005E80(0x14C);
    w->f14 = 0x1E;
  }
  sub_080168C4();
  v = ((u8 *) x) + 0x20;
  while ((t = sub_080168F8()) != 0)
  {
    if ((*((void **) (((u8 *) t) + 8))) == ((void *) y->gfx))
    {
      goto found;
    }
  }

  common:
  x = (struct EffectHeader *) D_02025FF0;

  z->f00 = *((u16 *) (((u8 *) x) + ((u32) D_000018C2)));
  sub_08003740(v);
  sub_0806D588(z, w);
  if ((*((u8 *) (((u32) D_0000173A) + ((u8 *) x)))) == 0x1C)
  {
    goto fail;
  }
  if (((*((u8 *) (((u8 *) x) + ((u32) D_000014ED)))) != 0) || ((*((s32 *) (((u8 *) x) + 0x10))) == 0))
  {
    goto ok;
  }
  fail:
  sub_080C31E0(arg0, arg0->updateCb);

  return;
  found:
  y->f4C = t;

  b = *((u8 *) (((u8 *) t) + 1));
  y->f50 = b;
  y->gfx->f16 = 5;
  w->f10 = 0x12C;
  w->f14 = 1;
  *((u8 *) ((((u8 *) arg0) + (arg0->index * 2)) + 0x19)) = 0;
  g = (s32 *) 0x08671BB0;
  sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *g);
  goto common;
  ok:
  sub_0806D330(arg0, z);

}
