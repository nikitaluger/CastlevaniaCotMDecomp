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
  u16 f1C;
  u8 _1E[4];
  u16 f22;
  u8 _24[4];
  struct E *f28;
};
struct BD
{
  u8 _0[0x20];
  u16 f4;
  u16 f6;
  u8 _18[0x4];
};
struct Z
{
  u32 w;
  u8 b;
};
extern struct BD gEffectGfxTable[];
extern u16 D_08102D44[];
extern s32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void sub_080B7134(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);
void sub_080B6E58(u8 *arg0)
{
  u8 *obj;
  struct P *p;
  u8 *p34;
  u16 *t;
  u8 *p18;
  u8 *q;
  s32 *fn;
  s32 b;
  s32 f10;
  u8 *p2;
  u16 upd2;
  obj = allocSpriteObject();
  if (obj == NULL)
  {
    goto fail;
  }
  *((u32 *) (arg0 + 0x38)) = (u32) obj;
  allocWorkSlot(arg0, 0, 0x48, 0);
  if ((*((u32 *) (arg0 + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (obj + 0x1C)) = 0x8000000B;
  p = (struct P *) (*((u32 *) (arg0 + 0x3C)));
  p34 = ((u8 *) p) + 0x34;
  installUpdateHandler(arg0, p, updateActorEffectSubObject);
  p->f1C = 0x66;
  *((u16 *) obj) |= gMainWorkspace.w;
  p->f8 = *((u32 *) (arg0 + 0x4C));
  p->fC = *((u32 *) (arg0 + 0x5C));
  b = (s8) (*((s8 *) (arg0 + 0x6C)));
  f10 = b * 3;
  p->f10 = f10 << 16;
  if ((*((u8 *) (arg0 + 0x70))) == 1)
  {
    p->f10 = -(f10 << 16);
  }
  setSpriteFlipForDirection(obj, -p->f10);
  sub_080B7134(obj, p34);
  setAnimationFrame(obj, p34, 2, 1);
  t = D_08102D44;
  p2 = allocEffectPart();
  *((void **) (((u8 *) p) + 0x28)) = p2;
  if (p2 != NULL)
  {
    goto success;
  }
  fail:
  sub_080C31E0(arg0, *((u32 *) (arg0 + 0x24)));

  return;
  success:
  *((u8 *) (p2 + 1)) = 1;

  *((u8 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 2)) = 8;
  *((u8 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 3)) = 1;
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 4)) = gEffectGfxTable[*((s16 *) (((u8 *) p) + 0x1C))].f4;
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 6)) = t[0];
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 8)) = t[1];
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 0xA)) = t[2];
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 0xC)) = t[3];
  *((u16 *) ((*((u8 **) (((u8 *) p) + 0x28))) + 0xE)) = gEffectGfxTable[*((s16 *) (((u8 *) p) + 0x1C))].f6;
  *((void **) ((*((u8 **) (((u8 *) p) + 0x28))) + 0x10)) = obj;
  do
  {
    struct Z z = {0, 0};
    *((u16 *) (arg0 + 0x74)) = 0x20;
    *((u32 *) (arg0 + 0x7C)) = 0;
    upd2 = *((u16 *) (arg0 + 2));
    upd2 |= 0x1000;
    *((u16 *) (arg0 + 2)) = upd2;
    *((u8 *) ((arg0 + (((u32) (*((s16 *) (arg0 + 0x22)))) * 2)) + 0x19)) = z.b;
    fn = &gScriptStepCallbackTable;
    p18 = arg0 + 0x18;
    sub_080C31E4(p18, arg0 + 0x22, *fn);
    *((u8 *) ((arg0 + (((u32) (*((s16 *) (arg0 + 0x22)))) * 2)) + 0x19)) = (*((u8 *) ((arg0 + (((u32) (*((s16 *) (arg0 + 0x22)))) * 2)) + 0x19))) + 1;
    q = p18 + (((u32) (*((s16 *) (arg0 + 0x22)))) * 2);
    sub_080C31E0(arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + ((*((u8 *) q)) * 4))));
  }
  while (0);
}

