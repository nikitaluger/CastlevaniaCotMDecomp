extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0804964C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;

    *(u32 *)(self + 0x14) = 0x0866E3A0;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(self + 0x18 + idx * 2) * 4));

    *(u16 *)(self + 0x22) -= 1;
}

void sub_08049692(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;

    *(u32 *)(self + 0x14) = 0x0866E3B4;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(self + 0x18 + idx * 2) * 4));

    *(u16 *)(self + 0x22) -= 1;
}

void sub_080496DC(void *arg0)
{
    void *r5;
    const u32 *lit;
    *(u8 *)(arg0 + 0x7C) = 0;
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
    lit = (const u32 *)0x08671BB0;
    r5 = arg0 + 0x18;
    sub_080C31E4(r5, arg0 + 0x22, *lit);
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
    r5 += (s32)*(s16 *)(arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)r5 * 4));
}

/* Script command: set the actor's flag byte at +0x7C to 1, then clear the
 * current step's flag byte (self+0x19 + step*2, step = s16 at self+0x22),
 * advance one script command via sub_080C31E4(self+0x18, self+0x22,
 * *scriptTable), set that flag back to 1 and dispatch the new command's
 * handler from the actor's command table (self+0x14, indexed by the command
 * byte at self+0x18 + step*2). */
void sub_080497C4(void *actor)
{
    void *flagPtr = actor + 0x7C;
    u8 zero = 0;
    void *stepSlot;
    const u32 *scriptTable;
    *(u8 *)flagPtr = 1;
    *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
    scriptTable = (const u32 *)0x08671BB0;
    stepSlot = actor + 0x18;
    sub_080C31E4(stepSlot, actor + 0x22, *scriptTable);
    *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) += 1;
    stepSlot += (s32)*(s16 *)(actor + 0x22) * 2;
    sub_080C31E0(actor, *(u32 *)((u8 *)*(u32 *)((u8 *)actor + 0x14) + *(u8 *)stepSlot * 4));
}
