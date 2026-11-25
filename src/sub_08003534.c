extern void sub_080034CC(void);
extern void sub_080034EC(void);
extern void sub_0800350C(void);

/* Reset the display-engine state flags: clear the two low bits of the byte at
 * 0x0300291C and set bits 0x1000 and 0x0040 in the state word at 0x03000830. */
void sub_08003534(void) {
    sub_080034CC();
    sub_080034EC();
    sub_0800350C();
}
