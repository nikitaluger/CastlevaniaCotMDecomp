extern u32 D_086706F0[];

/* Action-script step dispatcher: install handler table 0x086706F0, advance one
 * script step, bump that step's sub-step counter, run the step's command handler
 * with the object, then restore the step index. */
void sub_080BCBE8(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_086706F0;
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
