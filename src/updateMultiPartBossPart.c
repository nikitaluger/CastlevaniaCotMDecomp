struct UpdateObj {
    u8 _0[0x18]; u8 f18; u8 _19[9]; s16 f22; u8 _24[0x14];
    u32 f38; u8 _3C[0x30]; u32 f6C;
};
struct PartState {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 f2A; u16 f2C;
    u8 _2E[0x12]; u32 f40; u32 f44; u8 _48[4]; u32 f4C; u32 f50;
    u8 _54[0x64]; u32 fB8; u8 _BC[8]; u32 fC4;
};
struct S_02025FF0 { u8 _0[0x24]; u32 f24; u16 f28; };
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02025FF0 gMainWorkspace;
extern struct S_02021E90 gCameraState;
extern u8 gGameStatus[];                     /* level/enemy data block */
extern u8 D_080E03A0[];                      /* per-state value/clamp table */
extern void *gScriptStepCallbacks;

extern s32 syncViewPosition(void *, void *);     /* select movement/camera mode */
extern void resetActionResultState(void *, void *, void *, void *); /* reset state block */
extern void sub_0806BA20(void *, void *, void *);
extern void sub_080694D8(void *, void *, void *);
extern void sub_0806926C(void *);
extern void sub_080693E0(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *); /* update state position */
extern void sub_0806A884(void *, void *);    /* clamp/adjust sprite position */
extern void startEffectTimer(void *, s32, void *); /* initialise a control struct */
extern u16 sub_0806BCD8(void *, void *, void *, void *); /* choose a script action */
extern void sub_0806C6B0(void *, void *, void *, void *); /* main per-frame update */
extern s32 stepDelayTimer(void *, void *);     /* decrement a counter, dispatch when zero */
extern void sub_080C31E8(void *, void *, s32, void *); /* run a script handler */

/* Updates one part of a multi-part boss: applies a state-table value, handles its
   death/reset cue and script transitions, then runs the full per-frame update. */
void updateMultiPartBossPart(struct UpdateObj *obj) {
    struct PartState *stateHeader; struct PartState *state; s32 sprite; u8 *levelData; u8 *counter;
    stateHeader = (struct PartState *)((u8 *)obj->f6C + 4);
    sprite = obj->f38;
    state = stateHeader;
    levelData = (u8 *)0x02025368;
    if (syncViewPosition(state, state) != 0) return;
    resetActionResultState(obj, (void *)sprite, state, state);
    sub_0806BA20((void *)sprite, state, state);
    {
        u8 *stateTable = D_080E03A0;
        u32 rowOffset = (2 * state->f44) * 44;
        s32 currentValue = state->f0C + *(u32 *)(stateTable + rowOffset);
        u32 valueLimit;
        state->f0C = currentValue;
        valueLimit = *(u32 *)((u8 *)D_080E03A0 + rowOffset + 4);
        if (currentValue > (s32)valueLimit) state->f0C = valueLimit;
    }
    sub_080694D8((void *)sprite, state, state);
    if (gMainWorkspace.f24 != 0) {
        if ((gMainWorkspace.f28 & *(u16 *)(levelData + 0x3BC)) != 0) goto block8;
        goto block9;
    } else {
        if ((gCameraState.f146C & *(u16 *)(levelData + 0x3BC)) == 0) goto block9;
    }
block8:
    sub_0806926C(stateHeader);
    *(u32 *)((u8 *)stateHeader + 0xB8) = 0;
    *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
    { void *callback = &gScriptStepCallbacks; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x2C, *(void **)callback); }
    goto merged;
block9:
    sub_080693E0(obj, (void *)sprite, stateHeader, state);
merged:
    D_0806AB04(obj, (void *)sprite, stateHeader, state);
    {
        s32 mode = stateHeader->f40;
        counter = (u8 *)stateHeader + 0x28;
        if (mode == 1) {
            stateHeader->f4C = 0;
            stateHeader->f50 = 0;
            if (obj->f18 == 0x2C) {
                *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
                { void *callback = &gScriptStepCallbacks; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x2B, *(void **)callback); }
                *(u32 *)((u8 *)state + 0x08) = 0;
            } else {
                startEffectTimer(counter, 0, (void *)0x084FCA3C);
                *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
                { void *callback = &gScriptStepCallbacks; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x29, *(void **)callback); }
            }
        }
    }
    sub_0806A884((void *)sprite, state);
    stateHeader->fC4 = sub_0806BCD8(obj, (void *)sprite, stateHeader, state);
    if (stateHeader->fC4 != 0) {
        *(u8 *)((u32)obj->f22 * 2 + (u32)obj + 0x19) = 0;
        { void *callback = &gScriptStepCallbacks; sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, stateHeader->fC4, *(void **)callback); }
    }
    stepDelayTimer(counter, (void *)sprite);
    sub_0806C6B0(obj, (void *)sprite, stateHeader, state);
}
