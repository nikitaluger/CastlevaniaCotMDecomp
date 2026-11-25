extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31F0(void *);

/* Restarts the object's animation: resets the current animation slot, sets up
 * the slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_080417C8(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *started = self + 0x4C;
    u8 zero = 0;
    const u32 *frameRoutine;
    u8 *slot;
    *started = 2;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    frameRoutine = (const u32 *)0x08671BB0;
    slot = self + 0x18;
    sub_080C31E4(slot, self + 0x22, *frameRoutine);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    slot += (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)slot * 4));
}
