extern u32 D_0866E154[];

/* Script step dispatcher: install the handler table at +0x14, bump the current
 * slot's step counter, call that table's handler for the current command with
 * the entity, then restore the slot index. */
void sub_08041780(void *entity)
{
    u8 *obj = (u8 *)entity;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E154;
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

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](entity);

    *(u16 *)(obj + 0x22) -= 1;
}
