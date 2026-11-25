struct MemBlock { u16 flags; u16 reserved; u32 size; u32 base; };
extern struct MemBlock D_02004000[];

struct MemBlockHeader { u32 type : 8; u32 dataSize : 24; };

/* Initializes allocator slot `slot` of the block table D_02004000 for the
 * region at `block` of `size` bytes: records its aligned size and base address,
 * then writes the region's own header (type 0, usable size = aligned size - 4). */
void sub_080009DC(s32 slot, struct MemBlockHeader *block, s32 size)
{
    D_02004000[slot].flags = 0x80;
    D_02004000[slot].size = (size + 3) & ~3;
    D_02004000[slot].base = ((u32)block + 3) & ~3;

    block->type = 0;
    block->dataSize = D_02004000[slot].size - 4;
}
