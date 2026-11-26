extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void setObjectAnimation(s32, void *, int, u8);
extern s32 findKindIndex(void);
extern void installUpdateHandler(void *);
extern void *allocEffectPart(void);
extern void initThreePartSpriteGfx(void *, void *, s32, s32);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
extern u32 gMainObjTimerCallback;

struct S_02025FF0 {
  u8 _0[0x18C2];
  u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;

struct Entity {
  u8 _0[2];
  u16 flags;
  u8 _1[0x14 - 4];
  u32 funcTable;
  u8 _2[0x22 - 0x18];
  s16 animIdx;
  u32 handlerArg;
  u8 _3[0x38 - 0x28];
  u32 gfx;
  u32 child;
  u8 _4[0x5C - 0x40];
  s32 f5C;
};
struct GfxObj {
  u16 flags;
  u16 f2;
  u8 _0[0x1C - 4];
  u32 kind;
};
struct Obj28 {
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
  void *f10;
};
struct Child {
  u8 _0[0x1C];
  u16 param;
  u8 _1[0x22 - 0x1E];
  u16 result;
  u8 _2[0x28 - 0x24];
  struct Obj28 *obj28;
};
struct Table2Ent { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x28 - 8]; };
extern struct Table2Ent gEffectGfxTable[];

void sub_080B4DD4(struct Entity *arg)
{
  struct GfxObj *gfx;
  struct Child *child;
  u8 *childSub;
  s32 value;
  u16 *t1;
  struct Obj28 *obj28;
  struct Child *temp;

  gfx = allocSpriteObject();
  if (gfx == NULL)
  {
    goto Lend;
  }
  arg->gfx = (u32)gfx;
  allocWorkSlot((u8 *)arg, 0, 0x48, 0);
  if (arg->child == 0)
  {
    goto Lend;
  }
  gfx->kind = 0x80000009;
  temp = (struct Child *)arg->child;
  child = temp;
  childSub = (u8 *)child + 0x34;
  installUpdateHandler(arg);
  child->param = 0x66;
  value = findKindIndex();
  child->result = value;
  if ((value << 16) < 0)
  {
    goto Lend;
  }
  gfx->flags |= gMainWorkspace.f18C2;
  if ((s32)arg->f5C > 0)
  {
    gfx->f2 |= 0x10;
  }
  initThreePartSpriteGfx(gfx, childSub, 0x50, 3);
  setObjectAnimation((s32)gfx, childSub, 0x70, 0);
  t1 = (u16 *)0x08102B84;
  obj28 = allocEffectPart();
  child->obj28 = obj28;
  if (obj28 != NULL)
  {
    return;
  }
Lend:
  sub_080C31E0(arg, arg->handlerArg);
}
