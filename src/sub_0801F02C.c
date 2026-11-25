/* Unregister the entity from its owner's 6-slot tracking table (unless the
 * bit-2 flag at +0x5C is set) by clearing its matching entry. */
void sub_0801F02C(void *entity)
{
    if (!(*(u16 *)((u8 *)entity + 0x5C) & 2))
    {
        u32 *slotTable = *(u32 **)((u8 *)*(void **)((u8 *)entity + 0x6C) + 0x3C);
        u32 zero = 0;
        u32 *slot = (u32 *)((u8 *)slotTable + 0x58);
        s32 i = 5;
        do
        {
            if (*slot == (u32)entity)
                *slot = zero;
            slot++;
            i--;
        } while (i >= 0);
    }
}
