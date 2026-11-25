extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31F0(void *);

/* Restarts the object's animation: resets the current animation slot, sets up
 * the slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_08043AB0(void *obj) {
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

void sub_08041458(void *arg0) {
    void *p3C;
    u32 fn;
    u32 var_r4;
    void *p28;
    void *var_r1;
    p3C = *(void **)((u8 *)arg0 + 0x3C);
    var_r4 = 0;
    fn = 0x0804148D;
    p28 = *(void **)((u8 *)arg0 + 0x28);
    var_r1 = (u8 *)p3C + 4;
    do {
        *(s32 *)var_r1 = *(s32 *)((u8 *)p28 + 0x4C);
        *(s32 *)((u8 *)var_r1 + 8) = *(s32 *)((u8 *)p28 + 0x5C);
        var_r1 = (u8 *)var_r1 + 4;
        var_r4 += 1;
    } while (var_r4 <= 1U);
    *(u32 *)((u8 *)arg0 + 0x14) = fn;
    *(u16 *)((u8 *)arg0 + 0x22) = 1;
    sub_080C31F0(arg0);
}
