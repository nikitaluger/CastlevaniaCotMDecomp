extern void sub_08057AF8(void *);
extern void sub_08057B6C(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks; /* RAM script table */

/* Spinning projectile update: keeps advancing its spin angle during the first
 * 32 frames; on frame 47 it resets the frame counter, advances its RAM script,
 * reverses its travel direction, clears two object flags, then refreshes its
 * position and sprite from the parameter block. */
void sub_080575BC(void *arg0)
{
    void *view;
    void *work;
    u8 *params;
    s16 stepIndex;
    s32 stepOffset;
    u8 *stepPtr;

    view = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    params = (u8 *)work + 0x48;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    if (*(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) <= 0x20) {
        *(u32 *)(params + 0x0C) += 0x800;
    }

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepOffset = stepIndex * 2;
    stepPtr = (u8 *)stepOffset + (s32)(u8 *)arg0;
    if (stepPtr[0x19] == 0x2F) {
        u8 *flagPtr;
        s32 zero;

        stepPtr[0x19] = 0;

        {
            u32 *scriptHandlers = &gScriptStepCallbacks;
            u8 *stepBase = (u8 *)arg0 + 0x18;
            u8 *stepIndexPtr = (u8 *)arg0 + 0x22;
            sub_080C31E8(stepBase, stepIndexPtr, 1, *scriptHandlers);
        }
        sub_08057AF8(params);

        flagPtr = (u8 *)arg0 + 0x8C;
        zero = 0;
        *flagPtr = (u8)zero;
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x30) + 0x8C) = (u8)zero;
    }

    sub_08057B6C(arg0, view, work, params);
}
