/* Set bit 0 of the shared display-engine flag byte at 0x0300291C. */
void sub_080034DC(void) {
    u8 *flags = (u8 *)0x0300291C;
    *flags |= 1;
}
