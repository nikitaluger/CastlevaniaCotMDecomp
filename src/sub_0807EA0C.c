extern u32 D_0866F3C0[];

/* Enter one command step of an entity's command script: install the script's
 * handler table at +0x14, descend one nesting level (+0x22), bump the repeat
 * counter of the current command slot (+0x19), call the handler named by that
 * slot, then restore the nesting level. */
void sub_0807EA0C(void *entity)
{
    u8 *obj = (u8 *)entity;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866F3C0;
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
