void sub_08003A6C(s32, s32, s32);
void sub_08003740(s32, s32);
void sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);
void sub_0806D588(s32, s32);

struct S_02025FF0_14 { u8 _0x000[0x14]; s32 gamePhase; };
extern struct S_02025FF0_14 gMainWorkspace;

/* Effect-actor step: on game phase 0x16, arm the work state's effect timer and
 * timer callback, free resource 0x19C, clear the current script byte and run
 * the actor's script handler; then always refresh screen coords from the body. */
void sub_08089CDC(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *workState = *(u8 **)(self + 0x6C);
    u8 *bodyPos = workState + 4;
    s32 gfx = *(s32 *)(self + 0x38);
    s32 *handlerTable;
    if (gMainWorkspace.gamePhase == 0x16) {
        workState += 0x20;
        sub_08003A6C((s32)workState, 0, (s32)0x08507DF4);
        sub_08003740((s32)workState, gfx);
        sub_08005E80(0x19C);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
    sub_0806D588(gfx, (s32)bodyPos);
}
