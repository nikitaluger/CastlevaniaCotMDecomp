extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallback;

void sub_080AD8D4(void *arg0)
{
    s16 stepIndex;
    u8 *stepBase;
    u8 *workAux;
    s32 zero;
    u16 flags;
    u16 mask;
    void **scriptHandlers;

    sub_0800168C(arg0, 0, 0x64, 0);

    workAux = *(u8 **)((u8 *)arg0 + 0x3C);
    if (workAux == NULL) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    zero = 0;
    *(s16 *)(workAux + 0x1C) = 0x64;
    ((u8 *)arg0)[0x7C] = zero;

    *(u16 *)((u8 *)arg0 + 2) |= 0x1000;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19] = zero;

    scriptHandlers = &gMainObjTimerCallback;
    stepBase = (u8 *)arg0 + 0x18;
    sub_080C31E4(stepBase, (u8 *)arg0 + 0x22, *scriptHandlers);

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[stepIndex * 2 + 0x19]++;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBase = stepBase + stepIndex * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + stepBase[0] * 4));
}
