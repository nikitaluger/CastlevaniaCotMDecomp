extern void sub_0808BB54(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080B722C(void *);
extern void sub_080B7454(void *);
extern void sub_0808D0A4(s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallback;

/* Sets up the entity's graphics and children, signals the four child objects,
 * cleans up stale children, initializes the movement deltas, plays two sounds,
 * then clears the script step, posts a message and advances to the next step.
 */
void sub_080B48F4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *fx = *(u8 **)(self + 0x38);
    u8 *component = *(u8 **)(self + 0x3C);
    u8 *children = component + 0x48;
    s16 stepIdx;
    u8 *stepBase;

    sub_0808BB54();
    {
        u8 *child = *(u8 **)(children + 4);
        sub_080C31E0(child, *(void **)(child + 0x24));
    }
    {
        u8 *child = *(u8 **)(children + 8);
        sub_080C31E0(child, *(void **)(child + 0x24));
    }
    {
        u8 *child = *(u8 **)(children + 0xC);
        sub_080C31E0(child, *(void **)(child + 0x24));
    }
    {
        u8 *child = *(u8 **)(children + 0x10);
        sub_080C31E0(child, *(void **)(child + 0x24));
    }
    sub_080B722C(arg0);
    sub_080B7454(arg0);
    *(u32 *)(component + 0x14) = 0xFFFD0000;
    *(u32 *)(component + 0x10) = (*(u16 *)(fx + 2) & 0x10) ? 0xFFFE8000 : (0xC0 << 9);
    sub_0808D0A4(0x12);
    sub_08005E80(0xCC << 1);
    stepIdx = *(s16 *)(self + 0x22);
    self[stepIdx * 2 + 0x19] = 0;
    {
        void **msgPtr = &gMainObjTimerCallback;
        stepBase = self + 0x18;
        sub_080C31E4(stepBase, self + 0x22, *msgPtr);
    }
    stepIdx = *(s16 *)(self + 0x22);
    self[stepIdx * 2 + 0x19]++;
    stepIdx = *(s16 *)(self + 0x22);
    stepBase = stepBase + stepIdx * 2;
    sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + stepBase[0] * 4));
}
