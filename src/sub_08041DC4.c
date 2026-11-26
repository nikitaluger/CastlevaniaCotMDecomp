extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

// Sets this entity's velocity and animation frame, then advances and dispatches its step callbacks.
void sub_08041DC4(u8 *obj)
{
    u8 *sprite = *(u8 **)(obj + 0x38);
    u8 *motion = *(u8 **)(obj + 0x3C);
    u8 *animState = motion + 0x34;
    u8 *stepData;
    s32 vx;
    s32 *stepFunc;

    vx = (*(u16 *)(sprite + 0x02) & 0x10) ? 0xFFFC0000 : (0x80 << 11);
    *(u32 *)(motion + 0x10) = vx;
    *(u32 *)(motion + 0x14) = 0xFFFF8000;
    setAnimationFrame(sprite, animState, 3, 0);
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
    stepFunc = (s32 *)0x08671BB0;
    stepData = obj + 0x18;
    sub_080C31E4(stepData, obj + 0x22, *stepFunc);
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
    stepData += *(s16 *)(obj + 0x22) * 2;
    sub_080C31E0(obj, *(void **)(*(u32 *)(obj + 0x14) + *(u8 *)stepData * 4));
}
