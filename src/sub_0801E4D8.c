void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

/* Restart the actor on command table 0x0866D768: play animation 0, install the
 * table at +0x14, push one script step (+0x22), dispatch that step's handler
 * once, then pop the step again. */
void sub_0801E4D8(void *arg0) {
    u8 *obj = arg0;
    u8 baseOffset;
    s32 stepOffset;
    setAnimationFrame(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D768;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    baseOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(baseOffset + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

/* Restart the actor on command table 0x0866D75C: clear the work block's velocity
 * (+0x10/+0x14), install the table at +0x14, push one script step (+0x22),
 * dispatch that step's handler once, then pop the step again. */
void sub_0801E0DC(void *arg0) {
    u8 *obj = arg0;
    u8 baseOffset;
    s32 stepOffset;
    u32 *work = *(u32 **)(obj + 0x3C);
    work[5] = 0;
    work[4] = 0;
    *(u32 *)(obj + 0x14) = 0x0866D75C;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    baseOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(baseOffset + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}
