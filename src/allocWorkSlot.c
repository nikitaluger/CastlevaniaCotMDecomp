extern s32 sub_08000A70(s32 heapId, s32 size, s32 align);
extern s32 sub_080C2E4C(s32 dst, s32 size);

/*
 * Allocate `size` bytes from heap `heapId` and store the block pointer in the
 * entity's slot table at +0x3C + slot*0x10. Mark the slot busy in the +0x34
 * bitmask and zero-fill the new block. Returns the stored block pointer.
 */
s32 allocWorkSlot(u8 *entity, s32 heapId, s32 size, s32 slot) {
    s32 block;
    s32 off;
    u8 *slots;
    s32 *entry;

    *(u16 *)(entity + 0x34) = (u16)((1 << slot) | *(u16 *)(entity + 0x34));
    block = sub_08000A70(heapId, size, 4);
    off = slot << 4;
    slots = (u8 *)entity + 0x3C;
    entry = (s32 *)(slots + off);
    *entry = block;
    if (block != 0) {
        sub_080C2E4C(block, size);
    }
    return *entry;
}
