extern void sub_0803B1A4(void *state);

/* When either of flags 2/3 is set in `flags`, clear the three sub-state bytes
 * held by the state block passed in `state`. */
void sub_0803B1B4(u16 *flags, void *state) {
    if (0xC & *flags) {
        sub_0803B1A4(state);
    }
}
