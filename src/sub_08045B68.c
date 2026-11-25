/* Script command: set the actor's flag byte at +0x4C to 2, then clear the
 * current step's flag byte (self+0x19 + step*2, step = s16 at self+0x22),
 * advance one script command via sub_080C31E4(self+0x18, self+0x22,
 * *scriptTable), set that flag back to 1 and dispatch the new command's
 * handler from the actor's command table (self+0x14, indexed by the command
 * byte at self+0x18 + step*2). */
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31F0(void *);

void sub_08045B68(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *flagPtr = self + 0x4C;
    u8 zero = 0;
    const u32 *scriptTable;
    u8 *stepSlot;
    *flagPtr = 2;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    scriptTable = (const u32 *)0x08671BB0;
    stepSlot = self + 0x18;
    sub_080C31E4(stepSlot, self + 0x22, *scriptTable);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepSlot += (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)stepSlot * 4));
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
