extern s32 sub_08005820(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Throw step: clear the grabbed target's action byte, reset the hold state,
 * pick a random throw direction (2..4) and clear the step byte, then run the
 * script interpreter, advance the step and dispatch the next step. */
void sub_080BB0D4(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *attach = *(u8 **)(self + 0x3C) + 0x48;
    u8 *target = *(u8 **)(self + 0x4C) + 0x34;
    s32 zero = 0;
    u8 *stepBase;
    s32 *interpreter;
    s16 stepIndex;
    u8 stepByte;

    *target = (u8)zero;
    *(s32 *)(attach + 0x40) = zero;
    *(s32 *)(attach + 0x4C) = sub_08005820(3) + 2;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)zero;

    interpreter = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *interpreter);

    stepIndex = *(s16 *)(self + 0x22);
    stepByte = *(u8 *)(self + stepIndex * 2 + 0x19);
    stepByte++;
    *(u8 *)(self + stepIndex * 2 + 0x19) = stepByte;

    stepBase += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)(*(u8 **)(self + 0x14) + *stepBase * 4));
}
