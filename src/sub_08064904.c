/* Companion/boss update: run the state setup helpers, fire script events from
 * the gScriptStepCallbacks table based on state flags and sub-system results, then
 * record the resulting event id for the next frame. */
void *stepDelayTimer(void *, void *);
void sub_0806A884(void *, void *);
s32 sub_0806AB04(void *, void *, void *, void *);
s32 sub_0806B2C8(void *, void *, void *, void *);
void resetActorForm(void *, void *);
s32 syncViewPosition(void *, void *);
void resetActionResultState(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
u32 sub_0806BCD8(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

void sub_08064904(void *arg0) {
    void *mgr;
    void *sub;
    void *state;
    void *owner;
    void *ent;
    void *subNext;
    s32 result;
    u32 code;
    u32 *codeSlot;
    s32 *attackTableA;
    s32 *attackTableB;
    s32 *attackTableC;

    mgr = arg0;
    sub = *((void **) (((u8 *) mgr) + 0x6C));
    state = ((u8 *) sub) + 4;
    owner = *(void **) (((u8 *) mgr) + 0x38);
    ent = state;
    if (syncViewPosition(ent, ent) == 0) {
        resetActionResultState(mgr, owner, ent, ent);
        sub_0806AB04(mgr, owner, ent, ent);
        if (*(s32 *)((u8 *)ent + 0x40) == 0) {
            *(s32 *)((u8 *)ent + 0x4C) = 1;
            *(((u8 *)mgr) + (s32)*(s16 *)((u8 *)mgr + 0x22) * 2 + 0x19) = 0;
            attackTableA = (s32 *) 0x08671BD0;
            sub_080C31E8((u8 *)mgr + 0x18, (u8 *)mgr + 0x22, 0x11, *attackTableA);
        }
        sub_0806A884(owner, ent);
        subNext = (u8 *)sub + 0x2C;
        if (stepDelayTimer(subNext, owner) == 0 && *(s32 *)((u8 *)ent + 0x40) == 1) {
            result = sub_0806B2C8(mgr, owner, ent, ent);
            if (result != 0) {
                stepDelayTimer(subNext, owner);
            } else {
                resetActorForm(owner, ent);
                *(s32 *)((u8 *)ent + 0x48) = result;
                stepDelayTimer(subNext, owner);
                *(((u8 *)mgr) + (s32)*(s16 *)((u8 *)mgr + 0x22) * 2 + 0x19) = (u8)result;
                attackTableB = (s32 *) 0x08671BD0;
                sub_080C31E8((u8 *)mgr + 0x18, (u8 *)mgr + 0x22, 4, *attackTableB);
            }
        }
        code = sub_0806BCD8(mgr, owner, state, ent);
        codeSlot = (u32 *)((u8 *)state + 0xC4);
        *codeSlot = (u16)code;
        if ((u16)code != 0) {
            stepDelayTimer((u8 *)state + 0x28, owner);
            *(((u8 *)mgr) + (s32)*(s16 *)((u8 *)mgr + 0x22) * 2 + 0x19) = 0;
            attackTableC = (s32 *) 0x08671BD0;
            sub_080C31E8((u8 *)mgr + 0x18, (u8 *)mgr + 0x22, *codeSlot, *attackTableC);
        }
        sub_0806C6B0(mgr, owner, state, ent);
    }
}
