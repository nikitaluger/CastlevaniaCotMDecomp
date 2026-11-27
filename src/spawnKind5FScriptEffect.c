struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 f0,f1,f2,f3; u16 f4,f6,f8,fA,fC,fE; u32 f10; };
struct HostObject { u8 _0[8]; u32 f8,fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4]; struct SubObject *f28; u8 _2C[0x1C]; u32 f48; };
struct SpawnParams { u8 _0[0xC]; u16 fC,fE; u8 _10[0x18]; };
extern struct SpawnParams gEffectGfxTable[];
extern s16 D_0810216C[];
extern u32 D_08102170[];
extern u8 D_0810215C[];
extern void *gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s16, s32);
extern s32 scaleByRandom(s32);
extern void installUpdateHandler(void *, void *, void *);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);
void spawnKind5FScriptEffect(u8 *arg0)
{
    s32 gfx;
    struct HostObject *host;
    u8 *animState;
    u16 *defaults;
    u8 *p7c;
    s16 *tbl16;
    u8 *scriptPtr;
    void **scriptTablePtr;
    u8 *scriptEntry;
    s32 v;
    gfx = (s32)allocSpriteObject();
    if (gfx == 0) {
sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
return;
}
    *(u32 *)(arg0 + 0x38) = gfx;
    allocWorkSlot(arg0, 0, 0x48, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) {
sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
return;
}
    *(u32 *)(gfx + 0x1C) = 0x80000009;
    host = (struct HostObject *)*(u32 *)(arg0 + 0x3C);
    animState = (u8 *)host + 0x34;
    installUpdateHandler(arg0, (u8 *)host, updateActorEffectSubObject);
    host->f1C = 0x5F;
    host->f8 = *(u32 *)(arg0 + 0x4C);
    host->fC = *(u32 *)(arg0 + 0x5C);
    *(u16 *)gfx = gMainWorkspace.gfxFlags;
    initSpriteGraphics((void *)gfx, animState, (void *)0x08102150);
    tbl16 = D_0810216C;
    p7c = arg0 + 0x7C;
    setAnimationFrame((void *)gfx, animState, *(s16 *)((u8 *)tbl16 + (*p7c * 2)), 0);
    v = scaleByRandom(0x3CA);
    *(u32 *)(arg0 + 0x6C) = D_08102170[*p7c] + v;
    defaults = (u16 *)(D_0810215C + (*p7c * 8));
    host->f28 = allocEffectPart();
    if (host->f28 != NULL) goto cont;

    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;
cont:
    host->f28->f1 = 5;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = gEffectGfxTable[*(s16 *)((u8 *)host + 0x1C)].fC;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = gEffectGfxTable[*(s16 *)((u8 *)host + 0x1C)].fE;
    host->f28->f10 = gfx;
    *(u16 *)(arg0 + 2) |= 0x1000;
    *(u8 *)(((*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0) + 0x19) = 0;
    scriptTablePtr = &gScriptStepCallbackTable;
    scriptPtr = arg0 + 0x18;
    sub_080C31E4(scriptPtr, arg0 + 0x22, (s32)*scriptTablePtr);
    *(u8 *)(((*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0) + 0x19) += 1;
    scriptEntry = scriptPtr + (*(s16 *)(arg0 + 0x22) * 2);
    sub_080C31E0(arg0, *(void **)(*(u32 *)(arg0 + 0x14) + (*(u8 *)scriptEntry * 4)));
}
