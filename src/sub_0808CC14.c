/* Allocate a sprite resource for the entity, then pick and install its next
 * action callback from the entity's action table; if allocation fails, fall
 * back to the stored callback and return. */
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0808CC14(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *entryBase;
    s32 *cbTable;
    s32 entryAddr;
    if (allocWorkSlot(entity, 0, 0x10, 3) == 0) {
        sub_080C31E0(entity, *(s32 *)(self + 0x24));
        return;
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    cbTable = (s32 *)0x08671BB0;
    entryBase = self + 0x18;
    sub_080C31E4(entryBase, self + 0x22, *cbTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *entryPtr = entryBase + *(s16 *)(self + 0x22) * 2;
        entryAddr = *(u8 *)entryPtr;
        {
            s32 tableBase = *(s32 *)(self + 0x14);
            entryAddr = entryAddr << 2;
            entryAddr = entryAddr + tableBase;
        }
        sub_080C31E0(entity, *(s32 *)entryAddr);
    }
}
