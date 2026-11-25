extern u32 D_02025B74, D_02025B78, D_02025B7C;

/* Reclaim free blocks at the top of the object pool: starting one block below
 * the allocation cursor, walk downward in 0xBC-byte steps while the probe is
 * still inside the pool and the block's s16 marker is 0 (free); store the last
 * free block back as the pool's end pointer. */
void sub_08001448(void) {
    u32 block = D_02025B78;
    u32 probe = block - 0xBC;
    u32 lowerBound = D_02025B7C;
    u32 *endPtr = &D_02025B74;
    while (lowerBound <= probe && *(s16 *)probe == 0) {
        block = probe;
        probe -= 0xBC;
    }
    *endPtr = block;
}
