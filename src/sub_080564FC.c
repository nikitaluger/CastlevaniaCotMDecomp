extern u32 D_0866E7AC[]; /* command handler table */

/* Enter one command step of an entity's script: install this script's handler
 * table, descend a level, bump the current slot's repeat counter, dispatch the
 * handler named by that slot, then restore the level. */
void sub_080564FC(void *entity)
{
    u8 *obj = (u8 *)entity;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E7AC;
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
