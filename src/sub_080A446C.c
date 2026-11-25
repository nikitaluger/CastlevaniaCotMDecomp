struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState D_02025FF0;
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct HostObject {
    u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u8 _18[4]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[8]; u16 a34; u16 a36; u16 a38; u16 a3A;
};
struct ActorContext {
    u16 f0; u16 f2; u8 _4[0x14-0x4]; void *f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A];
    s16 f22; void *f24; u8 _28[0x38-0x28]; void *f38; void * volatile f3C;
    u8 _40[0xC]; u32 f4C; u8 _50[0xC]; u32 f5C; u8 _60[0xC]; s32 f6C;
};
struct SpawnParams { u8 _0[4]; u16 f4; u16 f6; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct SpawnParams D_080CBDD0[];
extern u16 D_08101CCC[];
extern char D_080CD400[];
extern u32 D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/*
 * Build the graphics/sub-object pair for an actor, set up its animation and
 * palette, copy in the spawn defaults, then advance the actor's script index.
 */
void sub_080A446C(struct ActorContext *arg0) {
    s32 gfx;
    struct HostObject *host;
    u8 *animState;
    u16 *defaults;
    u32 value;
    u8 *scriptPtr;
    void **scriptTablePtr;
    u8 *scriptEntry;
    u32 zero;

    gfx = (s32)sub_0800355C();
    if (gfx == 0) goto fail;
    arg0->f38 = (void *)gfx;
    sub_0800168C(arg0, 0, 0x48, 0);
    if (arg0->f3C == NULL) goto fail;
    *((u32 *)(gfx + 0x1C)) = 0x80000009;
    host = (struct HostObject *)arg0->f3C;
    animState = ((u8 *)host) + 0x34;
    sub_08014288(arg0, (u8 *)host, sub_08097DC8);
    zero = 0;
    host->f1C = 0x59;
    host->f8 = arg0->f4C;
    host->fC = arg0->f5C;
    value = sub_08013C2C(0x59);
    host->f22 = value;
    if ((s16)value < 0) goto fail;
    value = host->f22;
    value = value << 6;
    value = value + 0x200;
    value &= 0xFC0;
    *((u16 *)gfx) = value;
    *((u16 *)gfx) |= D_02025FF0.gfxFlags;
    sub_0801131C((void *)gfx, animState, (host->f1C * 0xC) + ((u32)0x080CD400));
    sub_08011368((void *)gfx, animState, 0x1E, 1);
    *((u16 *)((u8 *)gfx + 2)) |= 0x400;
    defaults = D_08101CCC;
    host->f28 = sub_08016190();
    if (host->f28 == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(arg0, arg0->f24);
    return;
ok:
    host->f28->f1 = zero;
    host->f28->f2 = 8;
    host->f28->f3 = 1;
    host->f28->f4 = D_080CBDD0[host->f1C].f8;
    host->f28->f6 = defaults[0];
    host->f28->f8 = defaults[1];
    host->f28->fA = defaults[2];
    host->f28->fC = defaults[3];
    host->f28->fE = D_080CBDD0[host->f1C].fA;
    host->f28->f10 = (void *)gfx;
    arg0->f2 |= 0x1000;
    {
        s16 idx = arg0->f22;
        *((u8 *)(((u32)idx * 2) + (u32)arg0 + 0x19)) = zero;
    }
    scriptTablePtr = &D_08671BB0;
    scriptPtr = ((u8 *)arg0) + 0x18;
    sub_080C31E4(scriptPtr, ((u8 *)arg0) + 0x22, (s32)(*scriptTablePtr));
    {
        s16 idx = arg0->f22;
        *((u8 *)(((u32)idx * 2) + (u32)arg0 + 0x19)) += 1;
        idx = arg0->f22;
        scriptEntry = scriptPtr + ((u32)idx * 2);
        sub_080C31E0(arg0, *((void **)(arg0->f14 + ((*scriptEntry) * 4))));
    }
}
