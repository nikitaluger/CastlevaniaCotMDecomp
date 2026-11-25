/* Trim the allocated block whose header sits at data-4 down to `requested`
 * bytes (rounded up to a whole word) and leave the leftover tail as a new free
 * block. Returns the block's resulting size in bytes, or -1 if it is too small. */
s32 sub_08000BA4(u8 *data, u32 requested) {
    u32 words, bytes;
    u8 *hdr;
    s32 blockSize, remain, tmp;
    requested += 3;
    words = requested >> 2;
    bytes = words << 2;
    hdr = data - 4;
    blockSize = *(s32 *)hdr >> 8;
    if ((u32)blockSize < bytes)
        return -1;
    tmp = blockSize - bytes;
    remain = tmp - 4;
    if (remain > 0) {
        u8 *next = hdr + (bytes + 4);
        *(volatile u8 *)next = 0;
        *(u32 *)next = ((u32)remain << 8) | *(volatile u8 *)next;
        *(u32 *)hdr = (words << 10) | *(volatile u8 *)hdr;
    }
    return *(s32 *)hdr >> 8;
}
