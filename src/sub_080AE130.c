struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState D_02025FF0;
struct SubObject { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[0x1C]; u32 f48;
};
struct SpawnParams { u8 _0[0xC]; u16 fC; u16 fE; u8 _10[0x18]; };
extern struct SpawnParams D_080CBDD0[];
extern u16 D_08102510[];
extern u8 D_08102518[];
extern void *D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_080B05EC(void *, void *, u8, s32);
extern void sub_080114DC(void *, void *, s32, s32);
extern s32 sub_08005820(s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);

/*
 * Build the graphics/sub-object pair for an actor, set up its animation, add a
 * small random offset to its state, then advance the actor's script index.
 */
void sub_080AE130(u8 *arg0) {
    s32 gfx; struct HostObject *host; u8 *animState; u8 *randomState; u8 one; s32 id; u16 *defaults; u8 *scriptPtr; void **scriptTablePtr; u8 *scriptEntry;
    gfx = (s32)sub_0800355C();
    if (gfx == 0) goto fail;
    *(u32 *)(arg0 + 0x38) = gfx;
    sub_0800168C(arg0, 0, 0x54, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
    one = 1;
    *(u32 *)(gfx + 0x1C) = one;
    host = (struct HostObject *)*(u8 **)(arg0 + 0x3C);
    animState = (u8 *)host + 0x34;
    randomState = (u8 *)host + 0x48;
    sub_08014288(arg0, (u8 *)host, sub_08097D90);
    host->f1C = 0x64;
    host->f8 = *(u32 *)(arg0 + 0x5C);
    host->fC = *(u32 *)(arg0 + 0x6C);
    id = sub_08013C2C(0x64);
    host->f22 = id;
    if ((id << 16) < 0) goto fail;
    *(u16 *)gfx |= D_02025FF0.gfxFlags;
    sub_080B05EC((void *)gfx, animState, D_08102518[*(u8 *)(arg0 + 0x4C)], 3);
    sub_080114DC((void *)gfx, animState, 0x43, 0);
    defaults = D_08102510;
    host->f28 = sub_08016190();
    if (host->f28 != NULL) goto cont;
fail:
    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;
cont:
    host->f28->f1 = one;
    host->f28->f2 = 8;
    host->f28->f3 = one;
    host->f28->f4 = D_080CBDD0[*(s16 *)((u8 *)host + 0x1C)].fC;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = D_080CBDD0[*(s16 *)((u8 *)host + 0x1C)].fE;
    host->f28->f10 = gfx;
    *(u16 *)(gfx + 4) = 0x80;
    *(u16 *)(gfx + 6) = 0x80;
    *(u16 *)(gfx + 2) |= 0x400;
    *(u32 *)(randomState + 4) = (u32)(sub_08005820(0x4000) + 0x18000);
    *(u16 *)(arg0 + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
    scriptTablePtr = &D_08671BB0;
    scriptPtr = arg0;
    scriptPtr += 0x18;
    sub_080C31E4(scriptPtr, arg0 + 0x22, (s32)*scriptTablePtr);
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) += 1;
    scriptEntry = scriptPtr + (u32)(*(s16 *)(arg0 + 0x22)) * 2;
    sub_080C31E0(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + *(u8 *)scriptEntry * 4));
}
