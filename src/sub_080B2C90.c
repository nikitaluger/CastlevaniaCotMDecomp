struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[0x1C]; u32 f48;
};
struct SpawnParams { u8 _0[8]; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 D_08102710[];
extern void *gMainObjTimerCallback;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void sub_080B2FD4(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);

/*
 * Build the graphics/sub-object pair for an actor from a linked source object,
 * copy the source's flags and parameters across, then advance the script index.
 */
void sub_080B2C90(u8 *arg0) {
    s32 gfx; struct HostObject *host; u8 *animState; u8 *source; s32 id; u16 *defaults; u8 *scriptPtr; void **scriptTablePtr; u8 *scriptEntry;
    gfx = (s32)allocSpriteObject();
    if (gfx == 0) goto fail;
    *(u32 *)(arg0 + 0x38) = gfx;
    allocWorkSlot(arg0, 0, 0x48, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
    *(u32 *)(gfx + 0x1C) = 0x8000000A;
    host = (struct HostObject *)*(u8 **)(arg0 + 0x3C);
    animState = (u8 *)host + 0x34;
    source = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x3C);
    installUpdateHandler(arg0, (u8 *)host, sub_08097D90);
    host->f1C = 0x65;
    id = findKindIndex();
    host->f22 = id;
    if ((id << 16) < 0) goto fail;
    *(u16 *)gfx |= gMainWorkspace.gfxFlags;
    host->f8 = *(u32 *)(source + 8);
    host->fC = *(u32 *)(source + 0xC);
    {
        u8 *sourceFlags = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x38);
        if (*(u16 *)(sourceFlags + 2) & 0x10) {
            *(u16 *)(gfx + 2) |= 0x10;
        } else {
            *(u16 *)(gfx + 2) &= 0xFFEF;
        }
    }
    sub_080B2FD4((void *)gfx, animState, 0xA0, 6);
    setObjectAnimation((void *)gfx, animState, 4, 0);
    defaults = D_08102710;
    host->f28 = allocEffectPart();
    if (host->f28 != NULL) goto cont;
fail:
    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;
cont:
    host->f28->f1 = 0;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = gEffectGfxTable[*(s16 *)((u8 *)host + 0x1C)].f8;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = gEffectGfxTable[*(s16 *)((u8 *)host + 0x1C)].fA;
    host->f28->f10 = gfx;
    *(u16 *)(gfx + 2) |= 0x400;
    *(u16 *)(arg0 + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
    scriptTablePtr = &gMainObjTimerCallback;
    scriptPtr = arg0;
    scriptPtr += 0x18;
    sub_080C31E4(scriptPtr, arg0 + 0x22, (s32)*scriptTablePtr);
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) += 1;
    scriptEntry = scriptPtr + (u32)(*(s16 *)(arg0 + 0x22)) * 2;
    sub_080C31E0(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + *(u8 *)scriptEntry * 4));
}
