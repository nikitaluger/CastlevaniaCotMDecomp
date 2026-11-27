extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

/* Script step advance: marks the work state's mode byte (offset 0) as 1,
 * resets the step counter, advances the script and dispatches the handler for
 * the new step; if the work object is missing it runs the fallback handler instead. */
void sub_0805B74C(void *arg0)
{
    s16 stepIndex;
    u8 *stepBase;
    u8 *workAux;
    s32 zero;

    allocWorkSlot(arg0, 0, 0x54, 0);

    if (*(u32 *)((u8 *)arg0 + 0x3C) == 0) {
        /* No work object: run the fallback handler from the object's aux pointer. */
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    workAux = *(u8 **)((u8 *)arg0 + 0x3C);
    workAux += 0x48;
    zero = 0;
    workAux[0] = 1;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19] = zero;

    {
        void **scriptHandlers = &gScriptStepCallbackTable;
        stepBase = (u8 *)arg0 + 0x18;
        sub_080C31E4(stepBase, (u8 *)arg0 + 0x22, *scriptHandlers);
    }

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19]++;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBase = stepBase + stepIndex * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + stepBase[0] * 4));
}
