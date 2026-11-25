/* Script command: set the actor's flag byte at +0x3C to 1, then clear the
 * current step's flag byte (self+0x19 + step*2, step = s16 at self+0x22),
 * advance one script command via sub_080C31E4(self+0x18, self+0x22,
 * *scriptTable), set that flag back to 1 and dispatch the new command's
 * handler from the actor's command table (self+0x14, indexed by the command
 * byte at self+0x18 + step*2). */
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_08052160(void *actor) {
    u8 *flagPtr = (u8 *)actor + 0x3C;
    u8 zero;
    u8 *stepSlot;
    void **scriptTable;
    zero = 0;
    *flagPtr = 1;
    *(u8 *)((u8 *)actor + (s32)*(s16 *)((u8 *)actor + 0x22) * 2 + 0x19) = zero;
    scriptTable = (void **)0x08671BB0;
    stepSlot = (u8 *)actor + 0x18;
    sub_080C31E4(stepSlot, (u8 *)actor + 0x22, (s32)*scriptTable);
    *(u8 *)((u8 *)actor + (s32)*(s16 *)((u8 *)actor + 0x22) * 2 + 0x19) += 1;
    stepSlot += (s32)*(s16 *)((u8 *)actor + 0x22) * 2;
    sub_080C31E0(actor, *(u32 *)((u8 *)*(u32 *)((u8 *)actor + 0x14) + *(u8 *)stepSlot * 4));
}
