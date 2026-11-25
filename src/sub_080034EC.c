/* Clear bit 1 of the shared display-engine flag byte at 0x0300291C. */
void sub_080034EC(void) {
    u8 *flags = (u8 *)0x0300291C;
    *flags &= 0xFD;
}
