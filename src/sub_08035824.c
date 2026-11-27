extern void stepAnimationTrack(void *, void *);
extern void sub_08035DB4(void *, void *, void *);
extern void sub_0803B140(s32, void *, void *, s32);
extern void sub_0803B194(void *);
extern void spawnBudgetedEffect(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gScriptStepCallbackTable[];

/* Enemy step: advance animation, spawn a one-shot effect under a state
 * condition, run the next script step when the animation flag is set, then
 * refresh the graphics for the current state. */
void sub_08035824(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *moveState = work + 0x48;
    s32 *scriptTable;
    sub_0803B194(work + 0x54);
    stepAnimationTrack(sprite, animState);
    if ((*(u16 *)(sprite + 0x28) == 0x1C) && (*(u8 *)(moveState + 0x18) == 0)) {
        *(u8 *)(moveState + 0x18) = 1;
        spawnBudgetedEffect(self, 0xE7);
        sub_08035DB4(self, work, sprite);
    }
    if (*(u8 *)animState & 2) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
    sub_0803B140(7, sprite, moveState + 0xC, 0x080CEF12);
}
