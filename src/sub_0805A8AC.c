extern u32 D_0866E8A0[];

/* Advance the entity's action-script slot, bump the current step counter,
 * dispatch the command handler from the table installed at +0x14
 * (0x0866E8A0 here), then restore the slot index. */
void sub_0805A8AC(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E8A0;
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
