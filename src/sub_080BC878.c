struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u8 _18[4]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[8]; u16 a34; u16 a36; u16 a38; u16 a3A;
};
struct ActorContext {
    u16 f0; u16 f2; u8 _4[0x14-0x4]; void *f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A];
    s16 f22; void *f24; u8 _28[0x38-0x28]; void *f38; void * volatile f3C;
    u8 _40[0x4C-0x40]; u32 f4C; u8 _50[0xC]; u32 f5C; u8 _60[0xC]; s32 f6C;
};
struct SpawnParams { u8 _0[4]; u16 f4; u16 f6; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 D_08102F30[];
extern char D_08102F24[];
extern u32 gMainObjTimerCallback;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void sub_08014668(void *, s32);
extern s32 sub_0800583C(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/*
 * Build the graphics/sub-object pair for an actor, set up its animation and
 * palette (with a size-based scale), copy in the spawn defaults, then advance
 * the actor's script index.
 */
void sub_080BC878(struct ActorContext *actor) {
    s32 gfx;
    struct HostObject *host;
    u8 *animState;
    u16 *defaults;
    u32 value;
    u8 *scriptPtr;
    void **scriptTablePtr;
    u8 *scriptEntry;

    gfx = (s32)allocSpriteObject();
    if (gfx == 0) goto fail;
    actor->f38 = (void *)gfx;
    allocWorkSlot(actor, 0, 0x48, 0);
    if (actor->f3C == NULL) goto fail;
    *((u32 *)(gfx + 0x1C)) = 0x80000009;
    host = (struct HostObject *)actor->f3C;
    animState = ((u8 *)host) + 0x34;
    installUpdateHandler(actor, (u8 *)host, sub_08097DC8);
    host->f1C = 0x68;
    value = findKindIndex();
    host->f22 = value;
    if ((s16)value < 0) goto fail;
    value = host->f22;
    value = value << 6;
    value = value + 0x200;
    value &= 0xFC0;
    *((u16 *)gfx) = value;
    *((u16 *)gfx) |= gMainWorkspace.gfxFlags;
    host->f8 = actor->f4C;
    host->fC = actor->f5C;
    sub_08014668((void *)gfx, -actor->f6C);
    {
        s32 scale = sub_0800583C(0x8000) + 0x40000;
        host->f10 = actor->f6C * scale;
        host->f14 = scale;
    }
    initSpriteGraphics((void *)gfx, animState, (s32)D_08102F24);
    setAnimationFrame((void *)gfx, animState, 0, 1);
    defaults = D_08102F30;
    host->f28 = allocEffectPart();
    if (host->f28 == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->f24);
    return;
ok:
    host->f28->f1 = 5;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = gEffectGfxTable[host->f1C].f8;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = gEffectGfxTable[host->f1C].fA;
    host->f28->f10 = (void *)gfx;
    actor->f2 |= 0x1000;
    {
        s16 idx = actor->f22;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = 0;
    }
    scriptTablePtr = &gMainObjTimerCallback;
    scriptPtr = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, (s32)(*scriptTablePtr));
    {
        s16 idx = actor->f22;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
        idx = actor->f22;
        scriptEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(actor, *((void **)(actor->f14 + ((*scriptEntry) * 4))));
    }
}
