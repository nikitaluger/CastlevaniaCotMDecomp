extern u32 D_0866E378[];

/* Install a command-script handler table on the entity, step to the next
 * command slot, and dispatch the command byte through the table. */
void sub_08048D78(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E378; /* handler table */
    *(u16 *)(obj + 0x22) += 1;              /* slot counter */

    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;    /* command slot counter */

    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;                    /* command byte for this slot */
    }

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}
