/* Spawn/init this effect/projectile: allocate its object and work state, seed
 * the animation and parameter tables, then fire the first script step. */
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct EffectChild { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct WorkState {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct EffectChild *f28; u8 _2C[0x1C]; u32 f48;
};
struct ParamEntry { u16 f0; u8 _2[2]; u16 f4; u8 _6[0xE]; };
extern struct ParamEntry gSpriteKindTable[];
extern u16 D_081017E8[];
extern void *gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_0809C2F0(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

void sub_0809B6D0(u8 *entity) {
    s32 obj; struct WorkState *p; u8 *animState; u8 one; s32 r; u16 *paramTable; u8 *framePtr; void **fn; u8 *q;
    obj = (s32)allocSpriteObject();
    if (obj == 0) goto fail;
    *(u32 *)(entity + 0x38) = obj;
    allocWorkSlot(entity, 0, 0x48, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    one = 1;
    *(u32 *)(obj + 0x1C) = one;
    p = (struct WorkState *)*(u8 **)(entity + 0x3C);
    animState = (u8 *)p + 0x34;
    installUpdateHandler(entity, (u8 *)p, releaseActorEffectSubObject);
    p->f1C = 0x44;
    r = findKindIndex(0x44);
    p->f22 = r;
    if ((r << 16) < 0) goto fail;
    *(u16 *)obj = gMainWorkspace.w;
    sub_0809C2F0((void *)obj, animState, 0, 8);
    setObjectAnimation((void *)obj, animState, 0x1A, 0);
    *(u8 *)(entity + 0x88) = 0xFF;
    paramTable = D_081017E8;
    p->f28 = allocEffectPart();
    if (p->f28 != NULL) goto cont;
fail:
    sub_080C31E0(entity, *(void **)(entity + 0x24));
    return;
cont:
    p->f28->f1 = 5;
    p->f28->f2 = 8;
    p->f28->f3 = one;
    p->f28->f4 = gSpriteKindTable[*(s16 *)((u8 *)p + 0x1C)].f0;
    p->f28->f6 = paramTable[0];
    p->f28->f8 = paramTable[1];
    p->f28->fA = paramTable[2];
    p->f28->fC = paramTable[3];
    p->f28->fE = gSpriteKindTable[*(s16 *)((u8 *)p + 0x1C)].f4;
    p->f28->f10 = obj;
    *(u16 *)(entity + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
    fn = &gScriptStepCallbackTable;
    framePtr = entity;
    framePtr += 0x18;
    sub_080C31E4(framePtr, entity + 0x22, (s32)*fn);
    *(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x19) += 1;
    q = framePtr + (u32)(*(s16 *)(entity + 0x22)) * 2;
    sub_080C31E0(entity, *(void **)(*(u8 **)(entity + 0x14) + *(u8 *)q * 4));
}
