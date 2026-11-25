extern u32 D_0866DBD0[];

/* Installs an entity's script handler table, advances the current script step's
 * counter, and dispatches that step's command through the table. */
void sub_0802E91C(void *entity)
{
    u8 *bytes = (u8 *)entity;
    s16 stepIndex;
    u8 commandId;

    *(u32 *)(bytes + 0x14) = (u32)D_0866DBD0;
    *(u16 *)(bytes + 0x22) += 1;

    stepIndex = *(s16 *)(bytes + 0x22);
    *(u8 *)(bytes + 0x19 + stepIndex * 2) += 1;

    stepIndex = *(s16 *)(bytes + 0x22);
    {
        s32 slotOffset = stepIndex * 2;
        u8 *slot = bytes;
        slot += 0x18;
        slot = slot + slotOffset;
        commandId = *slot;
    }

    ((void (**)(void *))*(u32 *)(bytes + 0x14))[commandId](entity);

    *(u16 *)(bytes + 0x22) -= 1;
}
