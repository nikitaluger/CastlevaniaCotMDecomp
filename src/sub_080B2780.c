struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
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
  u8 _40[0x4C - 0x40];
  u32 f4C;
};
struct BD
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct BD D_080CBDD0[];
extern u16 D_08102700[];
extern void *D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(void);
extern void sub_08014668(void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/* Creates a weapon/projectile under its parent: allocate the main object and sub-object,
 * link the update callback, configure the sprite/animation sub-object from the parameter
 * tables, dispatch the first state handler and register the completion callback. On
 * allocation failure the parent's callback is freed and the function returns. */
void sub_080B2780(struct Sarg *parent)
{
  struct P *subObjAlias;
  s32 mainObj;
  struct P *subObj;
  u8 *auxPtr;
  u32 animIndex;
  u8 *slotArea;
  void **callbackTable;
  u8 *slot;

  mainObj = (s32) sub_0800355C();
  if (mainObj == 0)
  {
    goto fail;
  }
  parent->f38 = (void *) mainObj;
  sub_0800168C(parent, 0, 0x48, 0);
  if (parent->f3C == NULL)
  {
    goto fail;
  }
  *((u32 *) (mainObj + 0x1C)) = (double) 0x8000000A;
  subObj = (struct P *) parent->f3C;
  auxPtr = ((u8 *) subObj) + 0x34;
  sub_08014288(parent, (u8 *) subObj, sub_08097DC8);
  subObj->f1C = 0x65;
  animIndex = sub_08013C2C();
  subObj->f22 = animIndex;
  if (((s16) animIndex) < 0)
  {
    goto fail;
  }
  animIndex = subObj->f22;
  animIndex = animIndex << 6;
  animIndex = animIndex + 0x200;
  subObjAlias = subObj;
  animIndex &= 0xFC0;
  *((u16 *) mainObj) = animIndex;
  *((u16 *) mainObj) |= D_02025FF0.w;
  sub_08014668((void *) mainObj, parent->f4C);
  sub_0801131C((void *) mainObj, auxPtr, (subObj->f1C * 0xC) + ((u32) 0x080CD400));
  sub_08011368((void *) mainObj, auxPtr, 0x42, 0x01);
  auxPtr = (u8 *) D_08102700;
  subObj->f28 = sub_08016190();
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
  subObj->f28->f4 = D_080CBDD0[subObj->f1C].f4;
  subObj->f28->f6 = *((u16 *) auxPtr);
  subObj->f28->f8 = *((u16 *) (auxPtr + 2));
  subObj->f28->fA = *((u16 *) (auxPtr + 4));
  subObj->f28->fC = *((u16 *) (auxPtr + 6));
  subObj->f28->fE = D_080CBDD0[subObj->f1C].f6;
  subObjAlias->f28->f10 = (void *) mainObj;
  *((u16 *) (mainObj + 2)) |= 0x400;
  parent->f2 |= 0x1000;
  {
    s16 stateIdx = parent->f22;
    *((u8 *) (((((u32) stateIdx) * 2) + ((u32) parent)) + 0x19)) = 0;
  }
  callbackTable = &D_08671BB0;
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
