struct GameState { u8 _0[0x18C2]; u16 field18C2; };
extern struct GameState D_02025FF0;
struct SpawnParams { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC; s16 fE; u32 f10; };
struct EffectBody {
    u8 _0[8]; u32 f8, fC, f10, f14; u8 _18[4]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4];
    struct SpawnParams *f28;
};
struct SpawnTableEntry { u8 _0[8]; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct SpawnTableEntry D_080CBDD0[];
extern u16 D_0810211C[];
extern u32 D_08671BFC;
extern u32 D_08671BB0;

extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void *sub_08016190(void);
extern s32 sub_080C2F20(s32, s32);
extern s32 sub_080C31E0(s32, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void sub_08097DC8(void);

/* Spawns a scripted effect: allocates an actor and its 0x48-byte behavior body,
 * fills the body and spawn parameters from script arguments and shared tables,
 * installs an update callback, then advances the script to its next command. */
void sub_080A9430(u8 *script)
{
    u8 *actor;
    struct EffectBody *body;
    u32 *calcFn;
    u16 *initParams;
    s32 entryIndex;
    u8 *scriptPc;
    u8 *scriptState;
    u32 *cmdTable;
    u32 firstCmd;
    u8 *scriptIdx;

    actor = sub_0800355C();
    if (actor == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + 0x24));
        return;
    }
    *(u32 *)(script + 0x38) = (u32)actor;
    sub_0800168C(script, 0, 0x48, 0);
    if (*(u32 *)(script + 0x3C) == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + 0x24));
        return;
    }

    *(u32 *)(actor + 0x1C) = 0x80000009;
    body = (struct EffectBody *)*(u32 *)(script + 0x3C);
    sub_08014288(script, body, sub_08097DC8);
    body->f1C = 0x5F;
    body->f8 = *(u32 *)(script + 0x4C);
    body->fC = *(u32 *)(script + 0x5C);

    calcFn = &D_08671BFC;
    body->f10 = ((sub_080C31E0(*(s32 *)(script + 0x6C) + 0x4000, *calcFn) >> 8) * 3) << 8;
    body->f14 = ((sub_080C31E0(*(s32 *)(script + 0x6C), *calcFn) >> 8) * 3) << 8;

    entryIndex = sub_08013C2C((s16)body->f1C);
    body->f22 = (u16)entryIndex;
    if ((entryIndex << 16) < 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + 0x24));
        return;
    }

    *(u16 *)actor |= D_02025FF0.field18C2;
    *(u32 *)(actor + 0x24) = *(u32 *)(script + 0x7C);
    *(u16 *)(actor + 8) = 0x4000 - *(u32 *)(script + 0x6C);
    *(u16 *)(actor + 2) |= 0x400;

    initParams = D_0810211C;
    body->f28 = sub_08016190();
    if (body->f28 == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + 0x24));
        return;
    }

    body->f28->f1 = 1;
    body->f28->f2 = 8;
    body->f28->f3 = 1;
    body->f28->f4 = D_080CBDD0[(s16)body->f1C].f8;
    body->f28->f6 = initParams[0];
    body->f28->f8 = initParams[1];
    body->f28->fA = initParams[2];
    body->f28->fC = initParams[3];
    body->f28->fE = D_080CBDD0[(s16)body->f1C].fA;
    body->f28->f10 = (u32)actor;

    if (*(u8 *)(script + 0x90) != 0)
        body->f28->fE = sub_080C2F20((s16)body->f28->fE * 5, 4);

    *(u16 *)(script + 2) |= 0x1000;
    *(u8 *)(script + (s16)*(u16 *)(script + 0x22) * 2 + 0x19) = 0;
    cmdTable = &D_08671BB0;
    scriptPc = script + 0x18;
    scriptIdx = script + 0x22;
    firstCmd = *cmdTable;
    sub_080C31E4(scriptPc, scriptIdx, firstCmd);
    *(u8 *)(script + (s16)*(u16 *)(script + 0x22) * 2 + 0x19) += 1;
    scriptState = scriptPc + (s16)*(u16 *)(script + 0x22) * 2;
    sub_080C31E0((s32)script, *(u32 *)(*(u32 *)(script + 0x14) + *(u8 *)scriptState * 4));
    return;
}
