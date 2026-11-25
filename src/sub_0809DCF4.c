extern void sub_080A038C(void *);
extern void sub_08005E80(s32);
extern void sub_0808D0A4(s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);

/* Task step handler: signal related objects and play a sound, optionally run
 * an effect, then clear the step's substate, run the script interpreter,
 * advance the substate and dispatch the handler for the new step. */
void sub_0809DCF4(void *arg0) {
    u8 *task = (u8 *)arg0;
    u8 *work = *(u8 **)(task + 0x3C);
    u8 *stepBase;
    s32 *scriptHandlers;

    sub_080A038C(arg0);
    sub_08005E80(0x186);
    if (*(u16 *)work & 1) {
        sub_0808D0A4(0x0C);
    }

    *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) = 0;
    scriptHandlers = (s32 *)0x08671BB0;
    stepBase = task + 0x18;
    sub_080C31E4(stepBase, task + 0x22, *scriptHandlers);

    *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) += 1;
    stepBase = stepBase + *(s16 *)(task + 0x22) * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)(task + 0x14) + *(u8 *)stepBase * 4));
}
