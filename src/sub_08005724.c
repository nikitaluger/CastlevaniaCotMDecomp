extern u32 D_02025BD0[];

/* Clears one flag in the bitmap at D_02025BD0: flagId packs the target word
 * index in bits 0-7 (high nibble group) and 8-15, and the bit number in 16-20. */
void sub_08005724(u32 flagId) {
    u32 *bitmap;
    u32 byteOffset;
    u32 *word;
    u32 bitIndex;
    bitmap = D_02025BD0;
    byteOffset = (flagId & 0xFF00) >> 6;
    byteOffset += (flagId & 0xFF) << 6;
    word = (u32 *)((u8 *)bitmap + byteOffset);
    bitIndex = (flagId & 0x1F0000) >> 16;
    *word &= ~(1u << bitIndex);
}
