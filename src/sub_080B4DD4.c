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
  u16 fE;
  u32 f10;
};
struct P
{
  u8 _0[8];
  u32 f8;
  u32 fC;
  u8 _10[0xC];
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u8 _24[4];
  struct E *f28;
  u8 _2C[8];
  u16 a34;
  u16 a36;
  u16 a38;
  u16 a3A;
};
struct Sarg
{
  u16 f0;
  u16 f2;
  u8 _4[0x14 - 0x4];
  void *f14;
  u8 f18;
  u8 f19;
  u8 _1A[0x22 - 0x1A];
  s16 f22;
  void *f24;
  u8 _28[0x38 - 0x28];
  void *f38;
  void * volatile f3C;
  u8 _40[0x5C - 0x40];
  s32 f5C;
};
struct BD
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct BD gEffectGfxTable[];
extern u16 gLayerParams[];
extern void *gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initThreePartSpriteGfx(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
extern void updateActorEffectSubObject(void);

void sub_080B4DD4(struct Sarg *parent)
{
  struct P *subObjAlias;
  s32 mainObj;
  struct P *subObj;
  u16 *auxPtr;
  s32 animIndex;
  u8 *slotArea;
  void **callbackTable;
  u8 *slot;

  mainObj = (s32) allocSpriteObject();
  if (mainObj == 0)
  {
    goto fail;
  }
  parent->f38 = (void *) mainObj;
  allocWorkSlot(parent, 0, 0x48, 0);
  if (parent->f3C == NULL)
  {
    goto fail;
  }
  *((u32 *) (mainObj + 0x1C)) = 0x80000009;
  subObj = (struct P *) parent->f3C;
  auxPtr = (u16 *) (((u8 *) subObj) + 0x34);
  installUpdateHandler(parent, (u8 *) subObj, &sub_08097D90);
  subObj->f1C = 0x66;
  animIndex = findKindIndex();
  subObj->f22 = animIndex;
  if ((animIndex << 16) < 0)
  {
    goto fail;
  }
  *((u16 *) mainObj) |= gMainWorkspace.w;
  if (parent->f5C > 0)
  {
    *((u16 *) (mainObj + 2)) |= 0x10;
  }
  initThreePartSpriteGfx((void *) mainObj, (void *) auxPtr, 0x50, 3);
  setObjectAnimation((void *) mainObj, (void *) auxPtr, 0x70, 0);
  auxPtr = (u16 *) 0x08102B84;
  subObj->f28 = allocEffectPart();
  if (subObj->f28 == NULL)
  {
    goto fail;
  }
  goto ok;
  fail:
  sub_080C31E0(parent, parent->f24);

  return;
  ok:
  subObj->f28->f1 = 1;

  subObj->f28->f2 = 8;
  subObj->f28->f3 = 1;
  subObj->f28->f4 = gEffectGfxTable[subObj->f1C].f4;
  subObj->f28->f6 = auxPtr[0];
  subObj->f28->f8 = auxPtr[1];
  subObj->f28->fA = auxPtr[2];
  subObj->f28->fC = auxPtr[3];
  subObj->f28->fE = gEffectGfxTable[subObj->f1C].f6;
  subObjAlias = subObj;
  subObjAlias->f28->f10 = (void *) mainObj;
  *((u16 *) (mainObj + 2)) |= 0x400;
  parent->f2 |= 0x1000;
  {
    s16 stateIdx = parent->f22;
    *((u8 *) (((((u32) stateIdx) * 2) + ((u32) parent)) + 0x19)) = 0;
  }
  callbackTable = &gScriptStepCallbackTable;
  slotArea = ((u8 *) parent) + 0x18;
  sub_080C31E4(slotArea, ((u8 *) parent) + 0x22, (s32) (*callbackTable));
  {
    s16 stateIdx = parent->f22;
    *((u8 *) (((((u32) stateIdx) * 2) + ((u32) parent)) + 0x19)) += 1;
    stateIdx = parent->f22;
    slot = slotArea + (((u32) stateIdx) * 2);
    sub_080C31E0(parent, *((void **) (parent->f14 + ((*slot) * 4))));
  }
}
