struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState D_02025FF0;
struct SubObject { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct HostObject { u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4]; struct SubObject *f28; u8 _2C[0x1C]; u32 f48; };
struct SpawnParams { u8 _0[0x10]; u16 f10; u16 f12; u8 _14[0x14]; };
extern struct SpawnParams D_080CBDD0[];
extern u16 D_081026F8[];
extern void *D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_0801468C(void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/*
 * Build the graphics/sub-object pair for an actor, derive its motion and flags,
 * copy in the spawn defaults, then advance the actor's script index.
 */
void sub_080B2184(u8 *arg0) {
    s32 gfx; struct HostObject *host; u8 *animState; u16 *defaults; u32 value; u8 *scriptPtr; void **scriptTablePtr; u8 *scriptEntry;
    gfx = (s32)sub_0800355C();
    if (gfx == 0) goto fail;
    *(u32 *)(arg0 + 0x38) = gfx;
    sub_0800168C(arg0, 0, 0x48, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
    *(u32 *)(gfx + 0x1C) = 0x80000009;
    host = (struct HostObject *)*(u8 **)(arg0 + 0x3C);
    animState = (u8 *)host + 0x34;
    sub_08014288(arg0, (u8 *)host, sub_08097DC8);
    host->f1C = 0x65;
    host->f8 = *(u32 *)(arg0 + 0x4C);
    host->fC = *(u32 *)(arg0 + 0x5C);
    sub_080146D0((u8 *)host, *(u32 *)(arg0 + 0x6C), 0x60000);
    value = sub_08013C2C(*(s16 *)((u8 *)host + 0x1C));
    host->f22 = value;
    if ((s16)value < 0) goto fail;
    value = *(s16 *)((u8 *)host + 0x22);
    value = value << 6;
    value = value + 0x200;
    value &= 0xFC0;
    *(u16 *)gfx = value;
    *(u16 *)gfx |= D_02025FF0.gfxFlags;
    sub_0801131C((void *)gfx, animState, *(s16 *)((u8 *)host + 0x1C) * 0xC + 0x080CD400);
    sub_08011368((void *)gfx, animState, 0x4F, 0);
    sub_0801468C((void *)gfx, *(u32 *)(arg0 + 0x6C));
    defaults = D_081026F8;
    host->f28 = sub_08016190();
    if (host->f28 != NULL) goto cont;
fail:
    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;
cont:
    host->f28->f1 = 1;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = D_080CBDD0[*(s16 *)((u8 *)host + 0x1C)].f10;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = D_080CBDD0[*(s16 *)((u8 *)host + 0x1C)].f12;
    host->f28->f10 = gfx;
    *(u16 *)(gfx + 2) |= 0x400;
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
