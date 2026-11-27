struct Arg0 {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 f22; u8 _24[0x14];
    u32 f38; u8 _3C[0x30]; u32 f6C;
};
struct G { u8 _0[0xD0]; u16 fD0; u16 fD2; };
struct G4 {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 f2C;
    u8 _2E[0x12]; u32 f40; u32 f44; u8 _48[4]; u32 f4C; u32 f50;
    u8 _54[0x64]; u32 fB8; u8 _BC[8]; u32 fC4;
};
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern s32 scaleByRandom(s32);
extern void sub_08005E80(s32);
extern void sub_0806D2A0(void *, s32, s32, s32);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_08068704(void *, void *, void *);
extern void *gScriptStepCallbacks;
extern u8 D_080E03A0[];
extern u8 D_084A67F4[];

/* Updates an enemy/actor: advances its AI state and timer, handles phase
 * transitions, searches for a target and dispatches the resulting actions. */
void updateActorAiWithTimer(struct Arg0 *actor) {
    struct G *state; struct G4 *ai; struct G4 *aiSub; s32 target; s32 check; u8 *dataPtr;
    aiSub = (struct G4 *)((u8 *)actor->f6C + 4);
    target = actor->f38;
    state = (struct G *)actor->f6C;
    ai = aiSub;
    check = syncViewPosition(ai, ai);
    if (check != 0) return;
    resetActionResultState(actor, (void *)target, ai, ai);
    sub_0806BA20((void *)target, ai, ai);
    {
        u8 *timerTable = D_080E03A0;
        u32 entryOff = (2 * ai->f44) * 44;
        s32 value = ai->f0C + *(u32 *)(timerTable + entryOff);
        u32 limit;
        ai->f0C = value;
        limit = *(u32 *)((u8 *)D_080E03A0 + entryOff + 4);
        if (value > (s32)limit) ai->f0C = limit;
    }
    sub_08068704((void *)target, ai, ai);
    D_0806AB04(actor, (void *)target, ai, ai);
    if (ai->f40 == 1) {
        ai->f4C = check;
        ai->f50 = check;
        ai->f08 = check;
        *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = (u8)check;
        { void *cmdTable = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x26, *(void **)cmdTable); }
    }
    sub_0806A884((void *)target, ai);
    dataPtr = (u8 *)state + 0x2C;
    {
        s32 findResult = stepDelayTimer(dataPtr, (void *)target);
        if (findResult == 0) {
            startEffectTimer(dataPtr, 0, (void *)0x084A67F4);
            *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = (u8)findResult;
            { void *cmdTable = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x23, *(void **)cmdTable); }
        }
    }
    if (ai->f2C == 2 && *(s32 *)((u8 *)state + 0xBC) == 0) {
        if (scaleByRandom(8) != 0) {
            sub_0806D2A0(actor, 0x3A, 0x0A, 0x12);
        } else {
            sub_0806D2A0(actor, 0x3B, 0x0A, 0x12);
        }
        sub_08005E80(0x94);
        aiSub->fB8 = 1;
    }
    aiSub->fC4 = sub_0806BCD8(actor, (void *)target, aiSub, ai);
    if (aiSub->fC4 != 0) {
        stepDelayTimer((u8 *)aiSub + 0x28, (void *)target);
        *(u8 *)((u32)actor->f22 * 2 + (u32)actor + 0x19) = 0;
        { void *cmdTable = &gScriptStepCallbacks; sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, aiSub->fC4, *(void **)cmdTable); }
    }
    sub_0806C6B0(actor, (void *)target, aiSub, ai);
}
