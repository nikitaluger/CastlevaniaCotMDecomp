extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallback;

/* Script step advance: marks the work state's mode byte, resets the step
 * counter, advances the script and dispatches the handler for the new step;
 * if the work object is missing it runs the fallback handler instead. */
void sub_080563CC(void *arg0)
{
    s16 stepIndex;
    u8 *stepBase;
    u8 *workAux;
    s32 zero;

    allocWorkSlot(arg0, 0, 0x64, 0);

    if (*(u32 *)((u8 *)arg0 + 0x3C) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    workAux = *(u8 **)((u8 *)arg0 + 0x3C);
    workAux += 0x48;
    zero = 0;
    workAux[9] = 1;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19] = zero;

    {
        void **scriptHandlers = &gMainObjTimerCallback;
        stepBase = (u8 *)arg0 + 0x18;
        sub_080C31E4(stepBase, (u8 *)arg0 + 0x22, *scriptHandlers);
    }

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19]++;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBase = stepBase + stepIndex * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + stepBase[0] * 4));
}
