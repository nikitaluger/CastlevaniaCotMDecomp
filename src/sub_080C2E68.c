/* Byte-exact memcpy (returns dst): when both pointers are 4-byte aligned copy
 * in 16-byte blocks of unrolled 32-bit words, then whole words, then the
 * remaining 1-3 bytes one at a time. */
void *sub_080C2E68(void *arg0, void *arg1, u32 arg2)
{
    u8 *dst = (u8 *)arg0;
    u8 *out = dst;
    u8 *src = (u8 *)arg1;
    u32 size = arg2;

    if (size > 0xF) {
        if ((((u32)src | (u32)dst) & 3) == 0) {
            u32 *dstWords = (u32 *)out;
            u32 *srcWords = (u32 *)src;
            do {
                *dstWords++ = *srcWords++;
                *dstWords++ = *srcWords++;
                *dstWords++ = *srcWords++;
                *dstWords++ = *srcWords++;
                size -= 0x10;
            } while (size > 0xF);
            if (size > 3) {
                do {
                    *dstWords++ = *srcWords++;
                    size -= 4;
                } while (size > 3);
            }
            out = (u8 *)dstWords;
            src = (u8 *)srcWords;
        }
    }

    size--;
    if ((s32)size != -1) {
        s32 minusOne = -1;
        do {
            *out++ = *src++;
            size--;
        } while ((s32)size != minusOne);
    }
    return dst;
}
