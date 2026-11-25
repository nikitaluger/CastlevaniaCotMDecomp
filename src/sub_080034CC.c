/* Clear bit 0 of the shared display-engine flag byte at 0x0300291C. The
 * companion helpers set this bit and clear/set bit 1 of the same byte. */
void sub_080034CC(void) {
    u8 *flags = (u8 *)0x0300291C;
    *flags &= 0xFE;
}
