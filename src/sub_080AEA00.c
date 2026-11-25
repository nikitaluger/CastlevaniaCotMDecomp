extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern u8 D_02025FF0[];

/* Actor script step: when the actor's state byte (self+0x4C) is nonzero, set the
 * sprite highlight bit 0x40, clear self+0x50, and advance the script (clear the
 * step flag, run the step callback, bump the flag, dispatch the step's handler).
 * When the state is zero, clear the global flag at D_02025FF0+0x18BC and clear
 * the sprite highlight bit. */
void sub_080AEA00(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 state = *(u8 *)(self + 0x4C);
    if (state != 0) {
        u8 *highlight = sprite + 0x2A;
        u8 oldHighlight = *highlight;
        u32 newHighlight;
        u8 zero;
        s16 stepIndex;
        u8 *stepData;
        s32 *scriptTable;
        newHighlight = 0x40;
        zero = 0;
        newHighlight |= oldHighlight;
        *highlight = (u8)newHighlight;
        *(u8 *)(self + 0x50) = zero;
        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) = zero;
        scriptTable = (s32 *)0x08671BB0;
        stepData = self + 0x18;
        sub_080C31E4(stepData, self + 0x22, *scriptTable);
        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) += 1;
        stepIndex = *(s16 *)(self + 0x22);
        stepData += stepIndex * 2;
        {
            u8 stepCmd = *stepData;
            s32 *handlers = *(s32 **)(self + 0x14);
            sub_080C31E0(self, handlers[stepCmd]);
        }
    } else {
        u32 globalFlags = (u32)D_02025FF0;
        *(u16 *)(globalFlags + 0x18BC) = state;
        *(u8 *)(sprite + 0x2A) &= 0xBF;
    }
}
