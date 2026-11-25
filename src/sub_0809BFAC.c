struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;
struct E { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct P { u8 _0[8]; u32 f8, fC; u8 _10[0xC]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4]; struct E *f28; };
struct BD { u8 _0[8]; u16 f4; u16 f6; u8 _8[0x1C]; };
extern struct BD D_080CBDD0[];
extern u8 D_080CD400[];
extern u16 D_08101814[];
extern u32 D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/* Creates a weapon/projectile under its parent: allocate the main object and its
 * sub-object, link the update callback, configure the sprite/animation sub-object from
 * the parameter tables, dispatch the first state handler and register the completion
 * callback. On allocation failure the parent's callback is freed and the function returns. */
void sub_0809BFAC(u8 *parent) {
  s32 mainObj;
  struct P *subObj;
  u8 *subState;
  u32 animIndex;
  u8 *slotArea;
  void **callbackTable;
  u8 *slot;
  u16 *spriteParams;

  mainObj = (s32)sub_0800355C();
  if (mainObj == 0) goto fail;
  *(u32 *)(parent + 0x38) = mainObj;
  sub_0800168C(parent, 0, 0x4C, 0);
  if (*(u32 *)(parent + 0x3C) == 0) goto fail;
  *(u32 *)(mainObj + 0x1C) = 0x80000009;
  subObj = (struct P *)*(u32 *)(parent + 0x3C);
  subState = (u8 *)subObj + 0x34;
  sub_08014288(parent, subObj, sub_08097DC8);
  subObj->f1C = 0x44;
  subObj->f8 = *(u32 *)(parent + 0x4C);
  subObj->fC = *(u32 *)(parent + 0x5C);
  animIndex = sub_08013C2C(0x44);
  subObj->f22 = animIndex;
  if (((s16)animIndex) < 0) goto fail;
  animIndex = *(s16 *)((u8 *)subObj + 0x22);
  animIndex = animIndex << 6;
  animIndex = animIndex + 0x200;
  animIndex &= 0xFC0;
  *(u16 *)mainObj = animIndex;
  *(u16 *)mainObj |= D_02025FF0.w;
  *(u16 *)(mainObj + 2) |= 0x400;
  sub_0801131C((void *)mainObj, subState, (subObj->f1C * 0xC) + (u32)D_080CD400);
  sub_08011368((void *)mainObj, subState, 0x0C, 0);
  spriteParams = D_08101814;
  subObj->f28 = sub_08016190();
  if (subObj->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(parent, *(void **)(parent + 0x24));
  return;
ok:
  subObj->f28->f1 = 1;
  subObj->f28->f2 = 8;
  subObj->f28->f3 = 1;
  subObj->f28->f4 = D_080CBDD0[subObj->f1C].f4;
  subObj->f28->f6 = spriteParams[0];
  subObj->f28->f8 = spriteParams[1];
  subObj->f28->fA = spriteParams[2];
  subObj->f28->fC = spriteParams[3];
  subObj->f28->fE = D_080CBDD0[subObj->f1C].f6;
  subObj->f28->f10 = mainObj;
  *(u16 *)(parent + 2) |= 0x1000;
  {
    s16 stateIdx = *(s16 *)(parent + 0x22);
    *(u8 *)(parent + (u32)stateIdx * 2 + 0x19) = 0;
  }
  callbackTable = &D_08671BB0;
  slotArea = parent + 0x18;
  sub_080C31E4(slotArea, parent + 0x22, *callbackTable);
  {
    s16 stateIdx = *(s16 *)(parent + 0x22);
    *(u8 *)(parent + (u32)stateIdx * 2 + 0x19) += 1;
    stateIdx = *(s16 *)(parent + 0x22);
    slot = slotArea + (u32)stateIdx * 2;
    sub_080C31E0(parent, *(void **)(*(u8 **)(parent + 0x14) + *(u8 *)slot * 4));
  }
}
