extern u16 D_03000830;

/* Clear bit 12 of the global display/fade state word. */
void sub_08003520(void) {
    D_03000830 &= 0xEFFF;
}
