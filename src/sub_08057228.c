extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

/* Copy the attached object's position into its script state, then run the
 * entity's update routine and dispatch the handler for the next script frame. */
void sub_08057228(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *attached = *(u8 **)(self + 0x3C);
    u8 *state = attached + 0x48;
    s16 frameIndex;
    u8 *framePtr;
    void **animTablePtr;

    state[0] = 0;
    *(u32 *)(state + 4) = *(u32 *)(attached + 8);
    *(u32 *)(state + 8) = *(u32 *)(attached + 0xC);

    frameIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + frameIndex * 2 + 0x19) = 0;

    animTablePtr = &gScriptStepCallbackTable;
    framePtr = self + 0x18;
    sub_080C31E4(framePtr, self + 0x22, *animTablePtr);

    frameIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + frameIndex * 2 + 0x19) += 1;

    frameIndex = *(s16 *)(self + 0x22);
    framePtr += frameIndex * 2;
    sub_080C31E0(self, *(void **)(*(u8 **)(self + 0x14) + *(u8 *)framePtr * 4));
}
