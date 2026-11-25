extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Starts the animation in the object's current animation slot: sets up the
 * slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_08039DC8(void *obj) {
    void *started = obj + 0x4C;
    u8 zero = 0;
    void *slot;
    const u32 *frameRoutine;
    *(u8 *)started = 1;
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    frameRoutine = (const u32 *)0x08671BB0;
    slot = obj + 0x18;
    sub_080C31E4(slot, obj + 0x22, *frameRoutine);
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
    slot += (s32)*(s16 *)(obj + 0x22) * 2;
    sub_080C31E0(obj, *(u32 *)((u8 *)*(u32 *)((u8 *)obj + 0x14) + *(u8 *)slot * 4));
}
