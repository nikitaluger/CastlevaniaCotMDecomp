/* Compare two byte arrays for count bytes: return the address of the first
 * mismatching byte in b, or 0 when all bytes are equal. */
s32 sub_080C30B8(u8 *a, u8 *b, s32 count) {
    while (--count != -1) {
        if (*b++ != *a++)
            return (s32)b - 1;
    }
    return 0;
}
