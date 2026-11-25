extern u32 D_0866FA8C[];

/* Command-script step dispatcher: installs the handler table this object is
 * moving to, ticks the current command slot's counter, and calls the handler
 * registered for that command. */
void sub_080946C0(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866FA8C;
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

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}
