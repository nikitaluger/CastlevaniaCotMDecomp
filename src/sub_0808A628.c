extern s32 sub_08003740(s32, s32);
extern s32 sub_08003A6C(s32, s32, s32);
extern s32 sub_08005E80(s32);
extern s32 sub_0806D588(s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Event phase counter in the large game state block. */
struct GameGlobals { u8 _0[0x1C]; u32 eventPhase; };
extern struct GameGlobals gMainWorkspace;

/* Scripted actor step: once the event phase is 1, spawn the effect described
 * by D_08502D90, move the phase to 0x10, stop sound 0x1BF, clear the script
 * step byte and advance, then keep the actor timer and sprite position up. */
void sub_0808A628(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 actor;
    s32 sprite;
    s32 actorState;

    actor = *(s32 *)(self + 0x6C);
    actorState = actor + 4;
    sprite = *(s32 *)(self + 0x38);
    if (gMainWorkspace.eventPhase == 1) {
        sub_08003A6C(actor + 0x20, 0, 0x08502D90);
        gMainWorkspace.eventPhase = 0x10;
        sub_08005E80(0x1BF);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
    sub_08003740(actor + 0x20, sprite);
    sub_0806D588(sprite, actorState);
}
