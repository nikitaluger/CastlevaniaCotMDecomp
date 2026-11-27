extern void forceAnimationFrame(void *, void *, u16, u8);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/* Script step for an entity with a linked body: when self+0x4C is nonzero it
 * highlights the sprite (bit 0x40 at sprite+0x2A), flags the body's attached
 * object, starts animation 0x6A, then advances the script (clear step flag,
 * run the step callback, bump the flag and dispatch the step's handler). When
 * the state is zero it only clears the sprite highlight and the body flag. */
void sub_080B5EF0(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *animData = body + 0x34;
    u8 state = *(u8 *)(self + 0x4C);
    if (state != 0) {
        u8 *highlight = sprite + 0x2A;
        u8 oldHighlight = *highlight;
        u32 newHighlight;
        u8 zero;
        s16 stepIndex;
        u8 *stepData;
        s32 *scriptTable;
        newHighlight = 0x40; zero = 0; newHighlight |= oldHighlight; *highlight = (u8)newHighlight;
        *(u8 *)(*(u8 **)(body + 0x28) + 1) = 1;
        forceAnimationFrame(sprite, animData, 0x6A, 0);
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
        u8 *highlight = sprite + 0x2A;
        *highlight &= 0xBF;
        *(u8 *)(*(u8 **)(body + 0x28) + 1) = state;
    }
}
