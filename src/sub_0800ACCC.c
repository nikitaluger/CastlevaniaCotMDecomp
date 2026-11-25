extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Script step: mark the linked scene object (work+0x630) as triggered, then
 * clear the step byte, run the script interpreter, advance the step and
 * dispatch the next handler. */
void sub_0800ACCC(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *trigger = *(u8 **)(*(u8 **)(self + 0x3C) + 0x630) + 0x40;
    u8 zero = 0;
    u8 *stepBase;
    s32 *interpreter;
    trigger[0] = 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    interpreter = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *interpreter);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase = stepBase + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)stepBase * 4));
}
