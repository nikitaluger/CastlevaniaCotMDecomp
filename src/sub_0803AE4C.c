void sub_08005E80(s32);
void sub_08011344(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Starts a short scripted effect: plays sound 0x18A, clears a byte in the work
 * object's resource block, plays animation frame 0x28, then clears the step
 * byte, runs the script interpreter and dispatches the new step's handler. */
void sub_0803AE4C(void *arg0)
{
    u8 *self = arg0;
    u8 *work;
    void *sprite;
    u8 *animator;
    u8 *stepBase;
    s32 *scriptHandlers;

    sprite = *(void **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    animator = work + 0x34;
    sub_08005E80(0xC5 << 1);
    *(u8 *)(*(u8 **)(work + 0x28) + 1) = 0;
    sub_08011344(sprite, animator, 0x28, 0);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptHandlers = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *scriptHandlers);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase = stepBase + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)((u32)*stepBase * 4 + *(u32 *)(self + 0x14)));
}
