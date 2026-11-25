extern void _call_via_r1(void *, void *);

/* Script step: switch the entity to the script table at 0x0866E00C, advance to
 * the next script slot and mark it active, run the handler for that slot's
 * opcode, restore the slot index, then (when the motion object's flag bit 0 is
 * set) stop it and clear a negative vertical velocity. */
void sub_0803D85C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *motion = *(u8 **)(self + 0x3C);
    u32 zero;
    s32 slotOffset;
    u32 entryAddr;
    u8 opcode;
    u16 scriptPos;

    *(u32 *)(self + 0x14) = 0x0866E00C;
    scriptPos = *(u16 *)(self + 0x22);
    scriptPos = scriptPos + 1;
    zero = 0;
    *(u16 *)(self + 0x22) = scriptPos;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;

    slotOffset = *(s16 *)(self + 0x22) * 2;
    entryAddr = (u32)self;
    entryAddr += 0x18;
    entryAddr += slotOffset;
    opcode = *(u8 *)entryAddr;
    _call_via_r1(arg0, *(void **)((u8 *)*(u32 *)(self + 0x14) + opcode * 4));

    *(u16 *)(self + 0x22) -= 1;
    if (*(u16 *)(motion + 0x02) & 1) {
        *(u32 *)(motion + 0x10) = zero;
        if (*(s32 *)(motion + 0x14) < 0) {
            *(u32 *)(motion + 0x14) = zero;
        }
    }
}
