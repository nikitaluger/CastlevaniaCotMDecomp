struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct SubObject *f28;
};
struct ActorContext {
    u16 f0; u16 f2; u8 _4[0x10]; void *f14; u8 f18; u8 f19; u8 _1A[8];
    s16 f22; void *f24; u8 _28[0x10]; void *f38; void * volatile f3C;
    u8 _40[0xC]; u32 f4C; u8 _50[0xC]; u32 f5C; u8 _60[0xC]; s32 f6C;
};
struct SpawnParams { u8 _0[0x10]; u16 f10; u16 f12; u8 _14[0x14]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 D_08102FF4[];
extern u32 gMainObjTimerCallback;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_08014668(void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/* Build the graphics/sub-object pair for an actor, set up its animation and
 * rotation from heading 0x68, copy in the spawn defaults, then advance the
 * actor's script index. */
void sub_080BD578(struct ActorContext *actor) {
    s32 gfx;
    struct HostObject *host;
    u8 *animState;
    u16 *defaults;
    s32 heading;
    u8 zeroByte;
    u8 *attribs;
    u8 *scriptPtr;
    void **scriptTablePtr;
    u8 *scriptEntry;

    gfx = (s32)allocSpriteObject();
    if (gfx == 0) goto fail;
    actor->f38 = (void *)gfx;
    allocWorkSlot(actor, 0, 0x5C, 0);
    if (actor->f3C == NULL) goto fail;
    *((u32 *)(gfx + 0x1C)) = 0x80000009;
    host = (struct HostObject *)actor->f3C;
    animState = ((u8 *)host) + 0x34;
    installUpdateHandler(actor, (u8 *)host, updateActorEffectSubObject);
    zeroByte = 0;
    host->f1C = 0x68;
    heading = findKindIndex(0x68);
    host->f22 = heading;
    if ((s16)heading < 0) goto fail;
    heading = host->f22;
    heading = heading << 6;
    heading = heading + 0x200;
    heading &= 0xFC0;
    *((u16 *)gfx) = heading;
    *((u16 *)gfx) |= gMainWorkspace.gfxFlags;
    host->f8 = actor->f4C;
    host->fC = actor->f5C;
    sub_08014668((void *)gfx, -actor->f6C);
    initSpriteGraphics((void *)gfx, animState, (s32)0x08102FE8);
    setAnimationFrame((void *)gfx, animState, 0, 0);
    defaults = D_08102FF4;
    attribs = allocEffectPart();
    host->f28 = (struct SubObject *)attribs;
    if (attribs == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->f24);
    return;
ok:
    host->f28->f1 = zeroByte;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = gEffectGfxTable[host->f1C].f10;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = gEffectGfxTable[host->f1C].f12;
    host->f28->f10 = (u32)gfx;
    *((u16 *)(gfx + 2)) |= 0x400;
    actor->f2 |= 0x1000;
    {
        s16 idx = actor->f22;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = zeroByte;
    }
    scriptTablePtr = &gMainObjTimerCallback;
    scriptPtr = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, (s32)(*scriptTablePtr));
    {
        s16 idx = actor->f22;
        *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
        idx = actor->f22;
        scriptEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(actor, *((void **)((u8 *)actor->f14 + ((*scriptEntry) * 4))));
    }
}
