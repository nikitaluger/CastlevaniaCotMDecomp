struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct E { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC; s16 fE; u32 f10; };
struct P {
    u8 _0[8]; u32 f8, fC, f10, f14; u8 _18[4]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct E *f28;
};
struct BD { u8 _0[0x14]; u16 f4; u16 f6; u8 _18[0x10]; };
struct T { s32 a; s32 b; };
extern struct BD gEffectGfxTable[];
extern struct T D_08102CFC[];
extern u16 D_08102CF4[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void initSharedSpriteGraphics(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void updateActorEffectSubObject(void);

/* Creates a weapon/projectile effect under its parent: allocate the main object and sub-object,
 * link the update callback, seed speed/camera fields and the sprite/animation sub-object
 * from the parameter tables, dispatch the first state handler and register the completion
 * callback. On allocation failure the parent's callback is freed and the function returns. */
void spawnActorEffect(u8 *parent) {
    u8 *mainObj;
    struct P *subObj;
    u8 *subState;
    u16 *spriteParams;
    u8 *slotArea;
    s32 *callbackTable;
    u8 *slot;

    mainObj = allocSpriteObject();
    if (mainObj == NULL) goto fail;
    *(u32 *)(parent + 0x38) = (u32)mainObj;
    allocWorkSlot(parent, 0, 0x48, 0);
    if (*(u32 *)(parent + 0x3C) == 0) goto fail;
    *(u32 *)(mainObj + 0x1C) = 0x8000000B;
    subObj = (struct P *)*(u32 *)(parent + 0x3C);
    subState = (u8 *)subObj + 0x34;
    installUpdateHandler(parent, subObj, updateActorEffectSubObject);
    subObj->f1C = 0x66;
    *(u16 *)mainObj |= gMainWorkspace.w;
    subObj->f8 = *(u32 *)(parent + 0x4C);
    subObj->fC = *(u32 *)(parent + 0x5C);
    subObj->f10 = D_08102CFC[*(u8 *)(parent + 0x70)].a * (s8)*(u8 *)(parent + 0x6C);
    subObj->f14 = D_08102CFC[*(u8 *)(parent + 0x70)].b;
    setSpriteFlipForDirection(mainObj, -subObj->f10);
    initSharedSpriteGraphics(mainObj, subState);
    setAnimationFrame(mainObj, subState, 7, 1);
    spriteParams = D_08102CF4;
    subObj->f28 = allocEffectPart();
    if (subObj->f28 == NULL) goto fail;
    goto cont;
fail:
    sub_080C31E0(parent, *(u32 *)(parent + 0x24));
    return;
cont:
    subObj->f28->f1 = 1;
    subObj->f28->f2 = 8;
    subObj->f28->f3 = 1;
    subObj->f28->f4 = gEffectGfxTable[*(s16 *)((u8 *)subObj + 0x1C)].f4;
    subObj->f28->f6 = spriteParams[0];
    subObj->f28->f8 = spriteParams[1];
    subObj->f28->fA = spriteParams[2];
    subObj->f28->fC = spriteParams[3];
    subObj->f28->fE = gEffectGfxTable[*(s16 *)((u8 *)subObj + 0x1C)].f6;
    subObj->f28->f10 = (u32)mainObj;
    *(u16 *)((u8 *)subObj + 4) |= 0x10;
    *(u16 *)(parent + 2) |= 0x1000;
    *(u8 *)(parent + (u32)(*(s16 *)(parent + 0x22)) * 2 + 0x19) = 0;
    callbackTable = &gScriptStepCallbackTable;
    slotArea = parent + 0x18;
    sub_080C31E4(slotArea, parent + 0x22, *callbackTable);
    *(u8 *)(parent + (u32)(*(s16 *)(parent + 0x22)) * 2 + 0x19) += 1;
    slot = slotArea + (u32)(*(s16 *)(parent + 0x22)) * 2;
    sub_080C31E0(parent, *(u32 *)(*(u32 *)(parent + 0x14) + *(u8 *)slot * 4));
}
