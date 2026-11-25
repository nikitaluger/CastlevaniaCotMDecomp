void sub_080034DC(void);
void sub_080034FC(void);
void sub_08003520(void);

/* Set the display-engine state flags for a transition: clear bit 0x1000 of the
 * state word at 0x03000830, then set the two low flag bits at 0x0300291C. */
void sub_08003548(void) {
    sub_08003520();
    sub_080034DC();
    sub_080034FC();
}
