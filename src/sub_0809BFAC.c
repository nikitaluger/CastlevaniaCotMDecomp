struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct E { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct P { u8 _0[8]; u32 f8, fC; u8 _10[0xC]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4]; struct E *f28; };
struct BD { u8 _0[8]; u16 f4; u16 f6; u8 _8[0x1C]; };
extern struct BD gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 D_08101814[];
extern u32 gScriptStepCallbackTable;
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

  mainObj = (s32)allocSpriteObject();
  if (mainObj == 0) goto fail;
  *(u32 *)(parent + 0x38) = mainObj;
  allocWorkSlot(parent, 0, 0x4C, 0);
  if (*(u32 *)(parent + 0x3C) == 0) goto fail;
  *(u32 *)(mainObj + 0x1C) = 0x80000009;
  subObj = (struct P *)*(u32 *)(parent + 0x3C);
  subState = (u8 *)subObj + 0x34;
  installUpdateHandler(parent, subObj, updateActorEffectSubObject);
  subObj->f1C = 0x44;
  subObj->f8 = *(u32 *)(parent + 0x4C);
  subObj->fC = *(u32 *)(parent + 0x5C);
  animIndex = findKindIndex(0x44);
  subObj->f22 = animIndex;
  if (((s16)animIndex) < 0) goto fail;
  animIndex = *(s16 *)((u8 *)subObj + 0x22);
  animIndex = animIndex << 6;
  animIndex = animIndex + 0x200;
  animIndex &= 0xFC0;
  *(u16 *)mainObj = animIndex;
  *(u16 *)mainObj |= gMainWorkspace.w;
  *(u16 *)(mainObj + 2) |= 0x400;
  initSpriteGraphics((void *)mainObj, subState, (subObj->f1C * 0xC) + (u32)gSpriteAnimDataTable);
  setAnimationFrame((void *)mainObj, subState, 0x0C, 0);
  spriteParams = D_08101814;
  subObj->f28 = allocEffectPart();
  if (subObj->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(parent, *(void **)(parent + 0x24));
  return;
ok:
  subObj->f28->f1 = 1;
  subObj->f28->f2 = 8;
  subObj->f28->f3 = 1;
  subObj->f28->f4 = gEffectGfxTable[subObj->f1C].f4;
  subObj->f28->f6 = spriteParams[0];
  subObj->f28->f8 = spriteParams[1];
  subObj->f28->fA = spriteParams[2];
  subObj->f28->fC = spriteParams[3];
  subObj->f28->fE = gEffectGfxTable[subObj->f1C].f6;
  subObj->f28->f10 = mainObj;
  *(u16 *)(parent + 2) |= 0x1000;
  {
    s16 stateIdx = *(s16 *)(parent + 0x22);
    *(u8 *)(parent + (u32)stateIdx * 2 + 0x19) = 0;
  }
  callbackTable = &gScriptStepCallbackTable;
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
