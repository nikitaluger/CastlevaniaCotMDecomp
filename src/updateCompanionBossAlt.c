/* Helpers used by the companion/boss action-step updater. */
void *stepDelayTimer(void *, void *);
void sub_0806A884(void *, void *);
s32 sub_0806AB04(void *, void *, void *, void *);
s32 handleSpecialTileAction(void *, void *, void *, void *);
void resetActorForm(void *, void *);
s32 syncViewPosition(void *, void *);
void resetActionResultState(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
u32 sub_0806BCD8(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

/* Update a companion/boss actor: sync the view, initialise the action state,
 * dispatch script steps for map-tile interaction and attack results, and save
 * the chosen step id for the next frame. */
void updateCompanionBossAlt(void *actor) {
    void *self;
    void *workBase;
    void *state;
    void *owner;
    void *work;
    void *delayTimer;
    s32 result;
    u32 eventCode;
    u32 *eventSlot;
    s32 *callbackTableA;
    s32 *callbackTableB;
    s32 *callbackTableC;

    self = actor;
    workBase = *((void **) (((u8 *) self) + 0x6C));
    state = ((u8 *) workBase) + 4;
    owner = *(void **) (((u8 *) self) + 0x38);
    work = state;
    if (syncViewPosition(work, work) == 0) {
        resetActionResultState(self, owner, work, work);
        sub_0806AB04(self, owner, work, work);
        if (*(s32 *)((u8 *)work + 0x40) == 0) {
            *(s32 *)((u8 *)work + 0x4C) = 1;
            *(((u8 *)self) + (s32)*(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = 0;
            callbackTableA = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0x11, *callbackTableA);
        }
        sub_0806A884(owner, work);
        delayTimer = (u8 *)workBase + 0x2C;
        if (stepDelayTimer(delayTimer, owner) == 0 && *(s32 *)((u8 *)work + 0x40) == 1) {
            result = handleSpecialTileAction(self, owner, work, work);
            if (result != 0) {
                stepDelayTimer(delayTimer, owner);
            } else {
                resetActorForm(owner, work);
                *(s32 *)((u8 *)work + 0x48) = result;
                stepDelayTimer(delayTimer, owner);
                *(((u8 *)self) + (s32)*(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = (u8)result;
                callbackTableB = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
                sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, BOSS_STEP_RESET, *callbackTableB);
            }
        }
        eventCode = sub_0806BCD8(self, owner, state, work);
        eventSlot = (u32 *)((u8 *)state + 0xC4);
        *eventSlot = (u16)eventCode;
        if ((u16)eventCode != 0) {
            stepDelayTimer((u8 *)state + 0x28, owner);
            *(((u8 *)self) + (s32)*(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = 0;
            callbackTableC = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, *eventSlot, *callbackTableC);
        }
        sub_0806C6B0(self, owner, state, work);
    }
}
