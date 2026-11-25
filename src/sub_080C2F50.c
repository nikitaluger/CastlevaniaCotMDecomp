/* Copy `count` bytes from src to dst, one byte at a time. */
void sub_080C2F50(u8 *src, u8 *dst, s32 count) {
    while (--count != -1) {
        *dst++ = *src++;
    }
}
