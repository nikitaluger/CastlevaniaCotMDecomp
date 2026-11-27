struct S_02025FF0 { u8 pad[0x14AC]; s32 state14AC; };
extern struct S_02025FF0 gMainWorkspace;
s32 stepDelayTimer(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Tick of a grounded actor: when its movement timer has run out, switch the
 * global state to 3, clear the current script step and advance the script. */
void sub_0808C4C8(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *mover = *(void **)(self + 0x6C);
    void *sprite = *(void **)(self + 0x38);
    s32 *stepTable;
    s32 timerDone = stepDelayTimer((u8 *)mover + 0x20, sprite);
    if (timerDone == 0) {
        gMainWorkspace.state14AC = 3;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = (u8)timerDone;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
    }
}
