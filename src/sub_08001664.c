extern s32 sub_08000A70(s32 heapId, s32 size, s32 align);

/*
 * Allocates `size` bytes from heap `heapId` and stores the block in the
 * entity's slot table at +0x3C + slot*0x10, marking the slot busy in the
 * +0x34 bitmask. Unlike allocWorkSlot the block is not zero-filled.
 * Returns the block pointer.
 */
s32 sub_08001664(u8 *entity, s32 heapId, s32 size, s32 slot) {
    s32 block;
    u32 off;
    u8 *slotPtr;
    *(u16 *)(entity + 0x34) = (1 << slot) | *(u16 *)(entity + 0x34);
    block = sub_08000A70(heapId, size, 4);
    off = slot * 0x10;
    slotPtr = entity + 0x3C;
    slotPtr += off;
    *(u32 *)slotPtr = block;
    return block;
}
