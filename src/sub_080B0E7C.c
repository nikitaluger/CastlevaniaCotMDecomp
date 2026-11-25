extern u32 D_08670294[];

/* Install command-script table 0x08670294 on the entity, advance its current
 * script slot, dispatch that slot's command byte through the table, then
 * restore the slot index. */
void sub_080B0E7C(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_08670294;
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
