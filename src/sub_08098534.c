/* ANDs each u16 of dst with a row mask from the 16-entry group selected by
 * maskSet in the table at 0x081013AC (0xFFFF keeps a row, 0xFFF0 clears its
 * low nibble). byteCount is in bytes; wordCount is the number of u16 words. */
void sub_08098534(s32 maskSet, u16 *dstWords, u32 byteCount) {
    u32 i = 0;
    u32 wordCount = byteCount >> 1;
    if (i < wordCount) {
        u16 *maskTable = (u16 *)0x081013AC;
        u32 rowMask = 0xF;
        u32 setBase = maskSet << 5;
        u16 *dst = dstWords;
        do {
            u32 rowOffset = (i & rowMask) << 1;
            u32 maskAddr = rowOffset + setBase;
            maskAddr += (u32)maskTable;
            *dst &= *(u16 *)maskAddr;
            dst++;
            i++;
        } while (i < wordCount);
    }
}
