void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

/* Restart the actor on command table 0x0866D7C0: play animation 0, install the
 * table at +0x14, push one script step (+0x22), dispatch that step's handler
 * once, then pop the step again. */
void sub_0801F90C(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 baseOffset;
    s32 stepOffset;
    sub_08011368(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D7C0;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    baseOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(baseOffset + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

/* Set the linked part's four u16 fields at +6/+8/+0xA/+0xC from the constant
 * table D_080CE794; when the object's animation code at +0x28 is in 0x29..0x32,
 * also clear the linked part's byte at +1. */
void sub_08020498(void *arg0, void *arg1) {
    u16 *rectTable = (u16 *)0x080CE794;
    void *obj = arg1;
    if ((u16)(*(u16 *)((u8 *)arg0 + 0x28) - 0x29) <= 9) {
        *(u8 *)(*(void **)((u8 *)obj + 0x28) + 1) = 0;
    }
    *(u16 *)((u8 *)*(void **)((u8 *)obj + 0x28) + 6) = rectTable[0];
    *(u16 *)((u8 *)*(void **)((u8 *)obj + 0x28) + 8) = rectTable[1];
    *(u16 *)((u8 *)*(void **)((u8 *)obj + 0x28) + 0xA) = rectTable[2];
    *(u16 *)((u8 *)*(void **)((u8 *)obj + 0x28) + 0xC) = rectTable[3];
}
