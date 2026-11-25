extern u32 D_0866F980[];

/* Script step dispatcher: install the handler table 0x0866F980 at +0x14, bump
 * the current step's sub-counter, read the command byte and call its handler
 * with the actor, then restore the step index. */
void sub_08090A9C(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866F980;
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
