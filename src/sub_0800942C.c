/* Fills one 160-entry u16 row (row index at +0xA4, data at +0xA8): the first
 * count (+0xA0) entries are cleared and the rest get the descending value
 * count-index, i.e. a vertical wipe/gradient. */
void sub_0800942C(void *arg0) {
    u32 i = 0;
    u32 *countPtr = (u32 *)((u8 *)arg0 + 0xA0);

    if (i < *countPtr) {
        u32 *rowPtr = (u32 *)((u8 *)arg0 + 0xA4);
        u8 *data = (u8 *)arg0 + 0xA8;

        do {
            u32 off = i * 2;
            u32 row = *rowPtr;
            u32 rowOff = (row * 5) * 64;
            off += rowOff;
            *(u16 *)(data + off) = 0;
            i++;
        } while (i < *countPtr);
    }

    i = *(u32 *)((u8 *)arg0 + 0xA0);
    if (i <= 0x9F) {
        u32 *rowPtr = (u32 *)((u8 *)arg0 + 0xA4);
        u8 *data = (u8 *)arg0 + 0xA8;
        u32 *countEnd = (u32 *)((u8 *)arg0 + 0xA0);

        do {
            u32 off = i * 2;
            u32 row = *rowPtr;
            u32 rowOff = (row * 5) * 64;
            off += rowOff;
            *(u16 *)(data + off) = (u16)(*countEnd - i);
            i++;
        } while (i <= 0x9F);
    }
}
