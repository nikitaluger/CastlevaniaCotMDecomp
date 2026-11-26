extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C2E68(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

// Applies a frame id to this entity's animation state, then advances and dispatches its step callbacks.
void sub_0803C548(void *obj)
{
    u8 *self = (u8 *)obj;
    s16 frameIds[4];
    void *animGfx = *(void **)(self + 0x38);
    u8 *animState = *(u8 **)(self + 0x3C) + 0x34;
    u8 *stepData;
    s32 *stepFunc;

    sub_080C2E68(frameIds, (void *)0x080CF3AC, 8);
    setAnimationFrame(animGfx, animState, ((s16 *)frameIds)[*(u8 *)(self + 0x8C)], 0);
    *(u8 *)((s16)*(u16 *)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFunc = (s32 *)0x08671BB0;
    stepData = self + 0x18;
    sub_080C31E4(stepData, self + 0x22, *stepFunc);
    *(u8 *)((s16)*(u16 *)(self + 0x22) * 2 + self + 0x19) += 1;
    stepData += (s16)*(u16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)stepData * 4));
}
