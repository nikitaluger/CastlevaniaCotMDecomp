/* Set SRAM wait states to 4 cycles (WAITCNT low bits), then copy count bytes. */
void sub_080C3060(u8 *src, u8 *dst, s32 count) {
    *(vu16 *)0x04000204 = (*(vu16 *)0x04000204 & 0xFFFC) | 3;
    while (--count != -1) {
        *dst++ = *src++;
    }
}
