/* Set bits 0x1000 and 0x0040 in the shared u16 flags word at 0x03000830. */
void sub_0800350C(void) {
    int bits;
    u16 *flags;
    flags = (u16 *)0x03000830;
    bits = (*flags) | 0x1040;
    *flags = bits;
}
