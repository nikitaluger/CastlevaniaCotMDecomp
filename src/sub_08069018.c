extern s32 gScriptStepCallbacks;
extern s32 stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void sub_0806932C(void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *);
extern s32 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_084FCA3C[];

/*
 * Companion/boss update: picks a position mode, runs the state setup helpers,
 * then fires script steps from the gScriptStepCallbacks table based on the state flags
 * and the sub-system results, and finally closes out the entity's update.
 */
void sub_08069018(u8 *mgr) {
    u8 *sub = *(u8 **)(mgr + 0x6C);
    u8 *state = sub + 4;
    u8 *owner = *(u8 **)(mgr + 0x38);
    s32 modeResult = syncViewPosition(state, state);
    u8 *subNext;
    s32 code;
    u16 code16;
    if (modeResult != 0) return;
    resetActionResultState(mgr, owner, state, state);
    D_0806AB04(mgr, owner, state, state);
    if (*(u32 *)(state + 0x40) == 0) {
        *(u32 *)(state + 0x4C) = 1;
        { u8 *stepData = (u8 *)((u32)(*(s16 *)(mgr + 0x22)) * 2 + (u32)mgr);
          *(u8 *)(stepData + 0x19) = (u8)modeResult; }
        { s32 *attackTable = &gScriptStepCallbacks;
          sub_080C31E8(mgr + 0x18, mgr + 0x22, 0x2C, *attackTable); }
    }
    sub_0806A884(owner, state);
    subNext = sub + 0x2C;
    if (stepDelayTimer(subNext, owner) == 0) {
        startEffectTimer(subNext, 0, D_084FCA3C);
        { u8 *stepData = (u8 *)((u32)(*(s16 *)(mgr + 0x22)) * 2 + (u32)mgr);
          *(u8 *)(stepData + 0x19) = (u8)modeResult; }
        { s32 *attackTable = &gScriptStepCallbacks;
          sub_080C31E8(mgr + 0x18, mgr + 0x22, 0x29, *attackTable); }
    }
    sub_0806932C(mgr, state);
    code = sub_0806BCD8(mgr, owner, state, state);
    sub += 0xC8;
    code16 = (u16)code;
    *(u32 *)sub = code16;
    if (code16 != 0) {
        stepDelayTimer(subNext, owner);
        { u8 *stepData = (u8 *)((u32)(*(s16 *)(mgr + 0x22)) * 2 + (u32)mgr);
          *(u8 *)(stepData + 0x19) = (u8)modeResult; }
        { s32 *attackTable = &gScriptStepCallbacks;
          sub_080C31E8(mgr + 0x18, mgr + 0x22, *(u32 *)sub, *attackTable); }
    }
    sub_0806C6B0(mgr, owner, state, state);
}
