/* Dispatch to the IWRAM-resident sound routine whose Thumb entry point is
 * 0x030041D0 (the caller has already stopped timer 1). */
void sub_080C0430(void) {
    ((void (*)(void))0x030041D1)();
}
