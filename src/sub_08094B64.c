extern void sub_0801604C(void *tracker);

/* Updates the tracker passed as `tracker`: when its flag bit 0 is set it also
 * sets the sticky 0x400 bit, then recomputes the position it follows. */
void sub_08094B64(void *self, void *tracker) {
    if (1 & *(u16 *)((s8 *)tracker + 2)) {
        *(u16 *)((s8 *)tracker + 2) = (0x80 << 3) | *(u16 *)((s8 *)tracker + 2);
    }
    sub_0801604C(tracker);
}
