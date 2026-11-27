struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[0x1C]; u32 f48;
};
struct SpawnParams { u8 _0[0xC]; u16 fC; u16 fE; u8 _10[0x18]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 gKind64LayerAttrs[];
extern u8 gKind64SpriteAnimTable[];
extern void *gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteFromTemplate(void *, void *, u8, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern s32 scaleByRandom(s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

/*
 * Build the graphics/sub-object pair for an actor, set up its animation, add a
 * small random offset to its state, then advance the actor's script index.
 */
/* Build the kind-0x64 scripted effect: allocate a sprite and render layer, initialise its animation and a jittered work offset from the actor's parameters, install the per-frame update handler, then advance the actor's script step. */ void spawnKind64ScriptEffect(u8 *actor) {
    s32 sprite; struct HostObject *work; u8 *animTrack; u8 *workExtra; u8 one; s32 kindIndex; u16 *layerAttrs; u8 *scriptStream; void **timerCallbacks; u8 *scriptStep;
    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    *(u32 *)(actor + 0x38) = sprite;
    allocWorkSlot(actor, 0, 0x54, 0);
    if (*(u32 *)(actor + 0x3C) == 0) goto fail;
    one = 1;
    *(u32 *)(sprite + 0x1C) = one;
    work = (struct HostObject *)*(u8 **)(actor + 0x3C);
    animTrack = (u8 *)work + 0x34;
    workExtra = (u8 *)work + 0x48;
    installUpdateHandler(actor, (u8 *)work, releaseActorEffectSubObject);
    work->f1C = 0x64;
    work->f8 = *(u32 *)(actor + 0x5C);
    work->fC = *(u32 *)(actor + 0x6C);
    kindIndex = findKindIndex(0x64);
    work->f22 = kindIndex;
    if ((kindIndex << 16) < 0) goto fail;
    *(u16 *)sprite |= gMainWorkspace.gfxFlags;
    initSpriteFromTemplate((void *)sprite, animTrack, gKind64SpriteAnimTable[*(u8 *)(actor + 0x4C)], 3);
    setObjectAnimation((void *)sprite, animTrack, 0x43, 0);
    layerAttrs = gKind64LayerAttrs;
    work->f28 = allocEffectPart();
    if (work->f28 != NULL) goto cont;
fail:
    sub_080C31E0(actor, *(void **)(actor + 0x24));
    return;
cont:
    work->f28->f1 = one;
    work->f28->f2 = 8;
    work->f28->f3 = one;
    work->f28->f4 = gEffectGfxTable[*(s16 *)((u8 *)work + 0x1C)].fC;
    work->f28->f6 = layerAttrs[0];
    work->f28->f8 = layerAttrs[1];
    work->f28->fA = layerAttrs[2];
    work->f28->fC = layerAttrs[3];
    work->f28->fE = gEffectGfxTable[*(s16 *)((u8 *)work + 0x1C)].fE;
    work->f28->f10 = sprite;
    *(u16 *)(sprite + 4) = 0x80;
    *(u16 *)(sprite + 6) = 0x80;
    *(u16 *)(sprite + 2) |= 0x400;
    *(u32 *)(workExtra + 4) = (u32)(scaleByRandom(0x4000) + 0x18000);
    *(u16 *)(actor + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor + 0x19) = 0;
    timerCallbacks = &gMainObjTimerCallbacks;
    scriptStream = actor;
    scriptStream += 0x18;
    sub_080C31E4(scriptStream, actor + 0x22, (s32)*timerCallbacks);
    *(u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor + 0x19) += 1;
    scriptStep = scriptStream + (u32)(*(s16 *)(actor + 0x22)) * 2;
    sub_080C31E0(actor, *(void **)(*(u8 **)(actor + 0x14) + *(u8 *)scriptStep * 4));
}
