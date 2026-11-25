extern void sub_080C31E0(void *, void *);
extern void sub_0801BC84(void *);

/* Dispatch a script step: pick a handler from the table at 0x0866D66C using
 * the current step's argument, run it, then restore the step index and refresh
 * the position history. */
void sub_0801AB6C(void *arg0)
{
    u8 *script = (u8*)arg0;
    s16 stepIndex;

    *(u32 *)(script + 0x14) = 0x0866D66C;
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) + 1;

    stepIndex = *(s16 *)(script + 0x22);
    *(u8 *)(script + stepIndex * 2 + 0x19) = *(u8 *)(script + stepIndex * 2 + 0x19) + 1;

    stepIndex = *(s16 *)(script + 0x22);
    {
        s32 stepOffset = stepIndex * 2;
        u8 *stepArgs = script + 0x18;
        sub_080C31E0(arg0, *(void **)((u8 *)*(void **)(script + 0x14) + *(u8 *)(stepArgs + stepOffset) * 4));
    }

    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) - 1;
    sub_0801BC84(arg0);
}
