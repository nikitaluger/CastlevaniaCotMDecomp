extern u32 D_0866FB1C[];

/* Command-script step dispatcher: install the handler table at +0x14 (D_0866FB1C
 * here), advance the current script slot at +0x22, bump that slot's step counter,
 * dispatch the handler indexed by the command byte at +0x18 + slot*2, then
 * restore the slot index. */
void sub_08096854(void *arg0) {
    u8 *obj = (u8 *)arg0;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866FB1C;
    *(u16 *)(obj + 0x22) += 1;
    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;
    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }
    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](arg0);
    *(u16 *)(obj + 0x22) -= 1;
}
