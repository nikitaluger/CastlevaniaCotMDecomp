void *sub_08001480(s32 arg0, s32 arg1);
extern u8 D_02025FF0[];

/* Allocate an entity into the first free slot of a range in the global slot
 * table, recording its slot index on the new entity. */
void *sub_0806D24C(s32 parent, s32 entityId, u32 startSlot, s32 slotCount)
{
    u32 slotIndex = startSlot;

    if (slotIndex < (u32)(startSlot + slotCount))
    {
        u8 *slotTable = D_02025FF0;
        u32 slotOffset = (slotIndex * 4) + (0xBC << 5);
        void **slot = (void **)(slotTable + slotOffset);
        do
        {
            if (*slot == 0)
            {
                void *entity = sub_08001480(parent, entityId);
                if (entity == 0)
                {
                    return 0;
                }
                *slot = entity;
                *(u32 *)((u8 *)entity + 0xAC) = slotIndex;
                return entity;
            }
            slot++;
            slotIndex++;
        } while (slotIndex < (u32)(startSlot + slotCount));
    }
    return 0;
}
