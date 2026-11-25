extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Starts the animation in the object's current animation slot: sets up the
 * slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_0804945C(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *started = self + 0x3C;
    u8 zero;
    u8 *slot;
    void **frameRoutine;
    zero = 0;
    *started = 1;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    frameRoutine = (void **)0x08671BB0;
    slot = self + 0x18;
    sub_080C31E4(slot, self + 0x22, (s32)*frameRoutine);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    slot += (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(obj, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)slot * 4));
}
