void sub_080C31E0(void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Script step: pick the interpreter's next step index (1, bumped by the phase
 * byte at +0x80), clear the step byte, run the script interpreter, advance the
 * step byte and dispatch the handler for the new step. */
void sub_080A9E48(void *arg0) {
    s32 nextStep = 1;
    s16 stepIndex;
    u8 *stepBase;
    s32 *interpreter;
    switch (*(u8 *)((u8 *)arg0 + 0x80)) {
    case 1: nextStep = 2; break;
    case 2: nextStep = 3; break;
    }
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;
    interpreter = (s32 *)0x08671BD0;
    stepBase = (u8 *)arg0 + 0x18;
    sub_080C31E8(stepBase, (u8 *)arg0 + 0x22, nextStep, *interpreter);
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBase += stepIndex * 2;
    {
        u8 step = *stepBase;
        s32 *handlers = *(s32 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, handlers[step]);
    }
}
