/* Script command: retarget the actor's command table to the alternate set at
 * 0x0866DEF4, run one of its handlers at a temporary next step (then restore
 * the step), and refresh the linked view when its 0x40 flag is set. */
void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);

void sub_0803959C(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *view = *(u8 **)(self + 0x38);
    s32 stepOffset;
    u8 *cmdSlot;
    u8 cmd;
    sub_080144D8(actor, view);
    *(u32 *)(self + 0x14) = 0x0866DEF4;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stepOffset = *(s16 *)(self + 0x22) * 2;
    *(u8 *)((u32)stepOffset + (u32)self + 0x19) = *(u8 *)((u32)stepOffset + (u32)self + 0x19) + 1;
    stepOffset = *(s16 *)(self + 0x22) * 2;
    cmdSlot = self;
    cmdSlot += 0x18;
    cmdSlot += stepOffset;
    cmd = *(u8 *)cmdSlot;
    sub_080C31E0(actor, *(void **)(cmd * 4 + *(u32 *)(self + 0x14)));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    {
        u8 *flagPtr = view;
        flagPtr += 0x2A;
        if (0x40 & *(u8 *)flagPtr) sub_080144FC(actor, view);
    }
}
